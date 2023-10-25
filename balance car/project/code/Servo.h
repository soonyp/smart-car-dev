/*
 * Servo.h
 *
 *  Created on: 2023Äê10ÔÂ21ÈÕ
 *      Author: XMG
 */

#ifndef SERVO_H_
#define SERVO_H_

#include "zf_common_headfile.h"
#include "Ourcode_headfile.h"

void servo_init(void);

void Servo_Set(float duty);

void ServoPidSetAngle(void);

extern float g_PID_Out;
extern float error;

#endif /* SERVO_H_ */
