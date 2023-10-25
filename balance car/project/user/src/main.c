/*********************************************************************************************************************
* CH32V307VCT6 Opensourec Library 即（CH32V307VCT6 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是CH32V307VCT6 开源库的一部分
*
* CH32V307VCT6 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          MounRiver Studio V1.8.1
* 适用平台          CH32V307VCT6
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期                                      作者                             备注
* 2022-09-15        大W            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"
#include "Ourcode_headfile.h"
#include "line.h"
#include "detect_line.h"

double k;
uint8 image[60][60];

void init(void) {
    tft180_set_dir(TFT180_CROSSWISE_180);
    tft180_init();     //初始化屏幕

    mt9v03x_init();

    sample_point_init();
}

int main(void) {
    clock_init(SYSTEM_CLOCK_120M);      // 初始化芯片时钟 工作频率为 120MHz

    // 此处编写用户代码 例如外设初始化代码等
    init();
    motor_init();
    servo_init();
    pit_ms_init(TIM6_PIT, 10);  //中断回调函数在isr.c里面
    PID_init();

    // exti_init(B10,EXTI_TRIGGER_FALLING);
    // 此处编写用户代码 例如外设初始化代码等
//    if(startflag==1)
//    {
//        gpio_init(A15, GPO, 1, GPIO_PIN_CONFIG);
//        system_delay_ms(50);
//        gpio_init(A15, GPO, 0, GPIO_PIN_CONFIG);


    while (1) {

        // 此处编写需要循环执行的代码
        if (mt9v03x_finish_flag) {
            img_preprocess();
            mt9v03x_finish_flag = 0;
        }
        /*显示--解析图*/

        tft180_displayimage03x(mt9v03x_image[0], 60, 60);   //原始图像
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
//        for (int i = 58; i > top; i--)    //清零Line
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






