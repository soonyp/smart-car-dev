/*********************************************************************************************************************
* CH32V307VCT6 Opensourec Library ����CH32V307VCT6 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ���CH32V307VCT6 ��Դ���һ����
*
* CH32V307VCT6 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          main
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          MounRiver Studio V1.8.1
* ����ƽ̨          CH32V307VCT6
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����                                      ����                             ��ע
* 2022-09-15        ��W            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"
#include "Ourcode_headfile.h"
#include "line.h"
#include "detect_line.h"

double k;
uint8 image[60][60];

void init(void) {
    tft180_set_dir(TFT180_CROSSWISE_180);
    tft180_init();     //��ʼ����Ļ

    mt9v03x_init();

    sample_point_init();
}

int main(void) {
    clock_init(SYSTEM_CLOCK_120M);      // ��ʼ��оƬʱ�� ����Ƶ��Ϊ 120MHz

    // �˴���д�û����� ���������ʼ�������
    init();
    motor_init();
    servo_init();
    pit_ms_init(TIM6_PIT, 10);  //�жϻص�������isr.c����
    PID_init();

    // exti_init(B10,EXTI_TRIGGER_FALLING);
    // �˴���д�û����� ���������ʼ�������
//    if(startflag==1)
//    {
//        gpio_init(A15, GPO, 1, GPIO_PIN_CONFIG);
//        system_delay_ms(50);
//        gpio_init(A15, GPO, 0, GPIO_PIN_CONFIG);


    while (1) {

        // �˴���д��Ҫѭ��ִ�еĴ���
        if (mt9v03x_finish_flag) {
            img_preprocess();
            mt9v03x_finish_flag = 0;
        }
        /*��ʾ--����ͼ*/

        tft180_displayimage03x(mt9v03x_image[0], 60, 60);   //ԭʼͼ��
        tft180_show_gray_image(60, 60, &binary_img_CDM[0][0], IMG_COL, IMG_ROW, 60, 60, 1);


        for (int i = 0; i < 60; i++) {
            for (int j = 0; j < 60; j++) {
                image[i][j] = binary_img_CDM[i][j];
            }
        }
//                   Motor_Set(3000,3000);

        Line left_line = find_left_line(image, find_left_start_point(image));
        Line right_line = find_right_line(image, find_right_start_point(image));
        Line mid_line = track_left_line(left_line, left_line.length, 45);

        uint8 line_image[60][60] = {0};
        for (int i = 0; i < left_line.length; i++) {
            line_image[left_line.points[i].row][left_line.points[i].column] = 1;
        }

        for (int i = 0; i < mid_line.length; i++) {
            line_image[mid_line.points[i].row][mid_line.points[i].column] = 2;
        }

        for (int i = 0; i < right_line.length; i++) {
            line_image[right_line.points[i].row][right_line.points[i].column] = 3;
        }

//        MidLine_Cal(image);
        Strait_Detect();
        Cross_Detect();
//        cheku_Detect();
        if (Cross_Flag == 1) {

//            gpio_init(A15, GPO, 1, GPIO_PIN_CONFIG);
//            system_delay_ms(40);
//            gpio_init(A15, GPO, 0, GPIO_PIN_CONFIG);
            k = (Line_Mid[58] - Line_Mid[top]) / (58 - top);
            for (int i = 57; i > top; i--) {
                image[i][Line_Mid[i]] = 0;
                Line_Mid[i] = Line_Mid[i + 1] - k;
                image[i][Line_Mid[i]] = 5;
            }
        }
//        for (int i = 58; i > top; i--)    //����Line
//        {
//            for (int j = 0; j < 59; j++) {
//
//                if (Line_L[i] == j) {
//                    image[i][j] = 5;
//                    Line_L[i] = 0;
//                } else if (Line_R[i] == j) {
//                    image[i][j] = 5;
//                    Line_R[i] = 0;
//                }
//                if (Line_Mid[i] == j) {
//                    image[i][j] = 5;
//                    Line_Mid[i] = 0;
//                }
//            }
//        }
        tft180_show_gray_image(0, 60, &line_image[0][0], IMG_COL, IMG_ROW, 60, 60, 5);
//        tft180_show_int(60, 0, StraitFlag, 4);
//        tft180_show_int(90, 0, vari, 4);
//        tft180_show_int(60, 20, top, 2);
//
//        tft180_show_int(60, 20, Left_Up_Find, 2);
//        tft180_show_int(80, 20, Right_Up_Find, 2);
//        tft180_show_int(60, 40, Left_Down_Find, 2);
//        tft180_show_int(80, 40, Right_Down_Find, 2);
//        tft180_show_int(60, 0, garage_flag, 2);
//        tft180_show_int(60, 0, obstacles_flag, 2);
//        tft180_show_int(60, 0, obstacles_flag, 3);
//        tft180_show_int(60, 0, obstacles_flag, 2);
//        tft180_show_int(60, 0, top, 2);
//        tft180_show_int(60, 40, stoppp, 2);
//        tft180_show_int(60, 0, Straight_Flag, 2);
        tft180_show_int(60, 0, g_PID_Out, 4);

//        tft180_show_int(60, 20, g_motor_PID_Out1, 4);
//        tft180_show_int(60, 40, g_motor_PID_Out2, 4);
//
//        tft180_show_int(80, 0, Left_Up_Find, 2);
//        tft180_show_int(100, 0, Right_Up_Find, 2);
//        tft180_show_int(80, 20, Left_Down_Find, 2);
//        tft180_show_int(100, 20, Right_Down_Find, 2);
        tft180_show_int(60, 20, Cross_Flag, 2);
//        tft180_show_int(80, 0, top, 2);
//        tft180_show_int(80, 20, Both_Lost_Time, 2);
    }
}






