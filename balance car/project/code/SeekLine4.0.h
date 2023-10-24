#ifndef SEEKLINE_H_
#define SEEKLINE_H_

#include "zf_common_headfile.h"
#include "Ourcode_headfile.h"

#define X 60
#define Y 60

extern uint8 Line_R[60] , Line_L[60] , Line_Mid[60];
extern int16 top;
extern float vari;
extern int16 Left_Lost_Time,Right_Lost_Time,Both_Lost_Time;
extern uint8 Cross_Flag;
extern uint8 garage_flag;
extern uint8 Straight_Flag;


void SetBlack(uint8 View[][Y]);
struct point SeekFirstPointDR(uint8 View[][Y]);
struct point SeekFirstPointDL(uint8 View[][Y]);
void SetLeftLine(uint8 View[][Y]);
void SetRightLine(uint8 View[][Y]);
void MidLine_Cal(uint8 View[][Y]);
float cal_error(void);
void Cross_Detect(void);
void cheku_Detect(void);
void Strait_Detect(void);
















#endif
