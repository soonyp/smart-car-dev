/*
 * motor.c
 *
 *  Created on: 2023��9��26��
 *      Author: Universe
 */
#include "motor.h"

//int swap;

void Motor_Init(void)
{

    gpio_init(D12, GPO, 0, GPIO_PIN_CONFIG);
    gpio_init(D15, GPO, 0, GPIO_PIN_CONFIG);
//    gpio_init(D13, GPO, 1, GPIO_PIN_CONFIG);
//    gpio_init(D14, GPO, 1, GPIO_PIN_CONFIG);


    pwm_init(TIM4_PWM_MAP1_CH2_D13, 11520, 0);
    pwm_init(TIM4_PWM_MAP1_CH3_D14, 11520, 0);

}



void Motor_Set (int motor1,int motor2) // motor1���֣�motor2����;
{
    int motorL=0,motorR=0;
    //swap=swap;
    motorL=-motor2;
    motorR=-motor1;
    //���ݲ������� ����ѡ����
    if(motorL < 0)
    {gpio_init(D12, GPO, 0, GPIO_PIN_CONFIG);

    }
    else     gpio_init(D12, GPO, 1, GPIO_PIN_CONFIG);

    if(motorR < 0)
    { gpio_init(D15, GPO, 1, GPIO_PIN_CONFIG);

    }
      else    gpio_init(D15, GPO, 0, GPIO_PIN_CONFIG);

    //motor1 �������ֵ�ת��
    if(motorL < 0)
    {


        if(motorL < -8000) motorL = -8000;//����PWM��ֵ
                 pwm_set_duty(TIM4_PWM_MAP1_CH2_D13,-motorL);

    }
    else{

        if(motorL > 8000) motorL = 8000;
                pwm_set_duty(TIM4_PWM_MAP1_CH2_D13,motorL);

    }

    //motor2 �������ֵ�ת��
    if(motorR < 0)
       {
        gpio_init(D15, GPO, 1, GPIO_PIN_CONFIG);
        if(motorR < -8000) motorR = -8000;//����PWM��ֵ
                       pwm_set_duty(TIM4_PWM_MAP1_CH3_D14,-motorR);

       }
    else{
        gpio_init(D15, GPO, 0, GPIO_PIN_CONFIG);
        if(motorR > 8000) motorR = 8000;
                         pwm_set_duty(TIM4_PWM_MAP1_CH3_D14,motorR);


       }
}

