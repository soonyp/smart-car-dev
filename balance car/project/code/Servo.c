/*
 * Servo.c
 *
 *  Created on: 2023Äê10ÔÂ21ÈÕ
 *      Author: XMG
 */
#include "Servo.h"

float error, g_PID_Out;

void Servo_Init(void) {
    pwm_init(TIM2_PWM_MAP1_CH1_A15, 50, 750);
}

void Servo_Set(float duty) {
    if (duty > 150)
        duty = 150;
    if (duty < -150)
        duty = -150;
    pwm_set_duty(TIM2_PWM_MAP1_CH1_A15, 750 + duty);
}

void ServoPidSetAngle(void) {
    error = cal_error();
    g_PID_Out = PID_realize(&piderror, error);
    Servo_Set(g_PID_Out);
}
