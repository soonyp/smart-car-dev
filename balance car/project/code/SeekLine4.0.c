#include "SeekLine4.0.h"
#include "string.h"

#define X 60
#define Y 60

uint8_t garage_flag;
uint8_t Straight_Flag;
uint8_t Cross_Flag;
int16 top, Left_Lost_Time, Right_Lost_Time, Both_Lost_Time;

struct point {
    int row;
    int col;
};
uint8 Line_R[60] = {0}, Line_L[60] = {0}, Line_Mid[60] = {0};

void SetBlack(uint8 View[][Y]) {
    for (int i = 0; i <= X - 1; i++) {
        View[i][0] = 0;
        View[i][Y - 1] = 0;
    }
    for (int i = 0; i <= Y - 1; i++) {
        View[0][i] = 0;
        View[X - 1][i] = 0;
    }

}

struct point SeekFirstPointDR(uint8 View[][Y])      //从中间底部（倒数第二行）开始向右找第一个黑点,返回临界白点
{
    int i;
    struct point FirstPoint;

    for (i = Y / 2; i < Y - 2; i++) {
        if (View[X - 2][i + 1] == 0 && View[X - 2][i + 2] == 0)
            break;
    }
    FirstPoint.row = X - 2;
    FirstPoint.col = i;

    return FirstPoint;
}

struct point SeekFirstPointDL(uint8 View[][Y])      //从中间底部（倒数第二行）开始向左找第一个黑点,返回临界白点
{
    int i;
    struct point FirstPoint;

    for (i = Y / 2; i > 1; i--) {
        if (View[X - 2][i - 1] == 0 && View[X - 2][i - 2] == 0)
            break;
    }
    FirstPoint.row = X - 2;
    FirstPoint.col = i;

    return FirstPoint;
}

void SetLeftLine(uint8 View[][Y]) {
    Left_Lost_Time = 0;
    memset(Line_L, 0, sizeof(Line_L));
    int i = 0, traveltime = 0, traveltime1 = 0;
    struct point NewPoint;
    struct point Rect[8];
    SetBlack(View);
    NewPoint = SeekFirstPointDL(View);
    Line_L[NewPoint.row] = NewPoint.col;

    while (traveltime < 120 && NewPoint.row > 0) {
        traveltime1 = 0;
        traveltime++;                        //防止某些情况卡死

        Rect[0].row = NewPoint.row + 1;
        Rect[0].col = NewPoint.col;
        Rect[1].row = NewPoint.row + 1;
        Rect[1].col = NewPoint.col - 1;
        Rect[2].row = NewPoint.row;
        Rect[2].col = NewPoint.col - 1;
        Rect[3].row = NewPoint.row - 1;
        Rect[3].col = NewPoint.col - 1;

        Rect[4].row = NewPoint.row - 1;
        Rect[4].col = NewPoint.col;
        Rect[5].row = NewPoint.row - 1;
        Rect[5].col = NewPoint.col + 1;
        Rect[6].row = NewPoint.row;
        Rect[6].col = NewPoint.col + 1;
        Rect[7].row = NewPoint.row + 1;
        Rect[7].col = NewPoint.col + 1;


        for (; i <= 7 && traveltime1 <= 7; i++) {
            traveltime1++;
            if (View[Rect[i].row][Rect[i].col] - View[Rect[i].row][Rect[i].col - 1] >= 1 ||
                View[Rect[i].row][Rect[i].col] - View[Rect[i].row + 1][Rect[i].col] >= 1 ||
                View[Rect[i].row][Rect[i].col] - View[Rect[i].row - 1][Rect[i].col] >= 1) {
                NewPoint = Rect[i];        //用本次的i求得新的中心点
                switch (i)                //根据本次找到边界点的编号求出下一次遍历的起点
                {
                    case 0:
                        i = 5;
                        break;
                    case 1:
                        i = 6;
                        break;
                    case 2:
                        i = 7;
                        break;
                    case 3:
                        i = 0;
                        break;
                    case 4:
                        i = 1;
                        break;
                    case 5:
                        i = 2;
                        break;
                    case 6:
                        i = 3;
                        break;
                    case 7:
                        i = 4;
                        break;
                    default:
                        break;
                }
                if (Line_L[NewPoint.row] == 0)                                //录入找到的点（不重复录入）
                {
                    Line_L[NewPoint.row] = NewPoint.col;
                    View[NewPoint.row][NewPoint.col] = 5;                    //显示左边线用
                }
                //printf("%d %d\n", NewPoint.row, NewPoint.col);		//调试NewPoint的坐标
                break;
            }
            if (i == 7) i = -1;                                            //因为一次for循环结束后i+1所以i=0-1
        }
        //if(i>=7) i=0;
    }
}

void SetRightLine(uint8 View[][Y]) {
    Right_Lost_Time = 0;
    memset(Line_R, 0, sizeof(Line_R));
    int i = 0, traveltime = 0, traveltime1 = 0;
    struct point NewPoint;
    struct point Rect[8];
    SetBlack(View);
    NewPoint = SeekFirstPointDR(View);
    Line_R[NewPoint.row] = NewPoint.col;
    while (traveltime < 120 && NewPoint.row > 0) {
        traveltime1 = 0;
        traveltime++;                        //防止某些情况卡死

        Rect[0].row = NewPoint.row + 1;
        Rect[0].col = NewPoint.col;
        Rect[1].row = NewPoint.row + 1;
        Rect[1].col = NewPoint.col + 1;
        Rect[2].row = NewPoint.row;
        Rect[2].col = NewPoint.col + 1;
        Rect[3].row = NewPoint.row - 1;
        Rect[3].col = NewPoint.col + 1;

        Rect[4].row = NewPoint.row - 1;
        Rect[4].col = NewPoint.col;
        Rect[5].row = NewPoint.row - 1;
        Rect[5].col = NewPoint.col - 1;
        Rect[6].row = NewPoint.row;
        Rect[6].col = NewPoint.col - 1;
        Rect[7].row = NewPoint.row + 1;
        Rect[7].col = NewPoint.col - 1;


        for (; i <= 7 && traveltime1 <= 7; i++) {
            traveltime1++;
            if (View[Rect[i].row][Rect[i].col] - View[Rect[i].row][Rect[i].col + 1] >= 1 ||
                View[Rect[i].row][Rect[i].col] - View[Rect[i].row + 1][Rect[i].col] >= 1 ||
                View[Rect[i].row][Rect[i].col] - View[Rect[i].row - 1][Rect[i].col] >= 1) {
                NewPoint = Rect[i];        //用本次的i求得新的中心点
                switch (i)                //根据本次找到边界点的编号求出下一次遍历的起点
                {
                    case 0:
                        i = 5;
                        break;
                    case 1:
                        i = 6;
                        break;
                    case 2:
                        i = 7;
                        break;
                    case 3:
                        i = 0;
                        break;
                    case 4:
                        i = 1;
                        break;
                    case 5:
                        i = 2;
                        break;
                    case 6:
                        i = 3;
                        break;
                    case 7:
                        i = 4;
                        break;
                    default:
                        break;
                }
                if (Line_R[NewPoint.row] == 0)                                //录入找到的点（不重复录入）
                {
                    Line_R[NewPoint.row] = NewPoint.col;
                    View[NewPoint.row][NewPoint.col] = 5;                    //显示右边线用
                }
                //printf("%d %d\n", NewPoint.row, NewPoint.col);		//调试NewPoint的坐标
                break;
            }
            if (i == 7) i = -1;                                            //因为一次for循环结束后i-1所以i=0-1
        }
        //if(i<=0) i=7;
        //printf("%d\n", traveltime);				//调试进入while循环次数
    }
}

void MidLine_Cal(uint8 View[][Y]) {
    Both_Lost_Time = 0;
    SetLeftLine(View);
    SetRightLine(View);
    for (int i = X - 2; i > 0; i--) {
//		if (Line_L[i] == Line_R[i])				//左右边界相遇退出循环
//			break;
        if (Line_L[i] == 1) Left_Lost_Time++;               //左边丢线次数加1
        if (Line_R[i] == Y - 2) Right_Lost_Time++;               //右边丢线次数加1
        if (Line_L[i] == 1 && Line_R[i] == 58) { Both_Lost_Time++; }
        if (Line_L[i] != 0 && Line_R[i] != 0) {
            Line_Mid[i] = (Line_L[i] + Line_R[i]) / 2;
            //printf("%d\n", Line_Mid[i]);
            View[i][Line_Mid[i]] = 5;            //显示中线用
        } else {
            top = i;
            break;
        }
    }
}


void Strait_Detect(void) {
    int i = 0;
    int sum1 = 0, sum2 = 0;
    float aver = 0, vari = 0;

    for (i = 40; i > top; i--) {
        sum1 += Line_Mid[i];
    }
    aver = sum1 / (40 - i);
    for (i = 40; i > top; i--) {
        sum2 += pow(Line_Mid[i] - aver, 2);
    }
    vari = sum2 / (40 - i);
    if (vari <= 1 && Left_Lost_Time <= 1 && Right_Lost_Time <= 1)
        Straight_Flag = 1;
    else if (vari > 19 && (Left_Lost_Time >= 2 || Right_Lost_Time >= 2))
        Straight_Flag = 2;
    else
        Straight_Flag = 0;
}


void cheku_Detect(void) {

    int cnt = 0;
    int black_blocks = 0;
    int times = 0;
    for (int i = 40; i < 43; i++)//35,43
    {
        black_blocks = 0;
        cnt = 0;
        for (int j = 5; j < 55; j++) {
            if (binary_img_CDM[i][j] == 0) {
                cnt++;
            } else {
                if (cnt >= 2 && cnt <= 10) {
                    black_blocks++;
                    cnt = 0;
                } else {
                    cnt = 0;
                }
            }
        }

        if (black_blocks >= 3 && black_blocks <= 9)
            times++;

    }
    if (times >= 2) {
        garage_flag = 1;
    } else {
        garage_flag = 0;
    }

}

void Cross_Detect(void) {
    if (Both_Lost_Time >= 10)//十字必定有双边丢线，在有双边丢线的情况下再开始找角点
    {
        Cross_Flag = 1;//确定对应标志位，便于各元素互斥掉

    } else {
        Cross_Flag = 0;
    }
}

float cal_error(void) {
    int interval = 0;
    float error1 = 0, error2 = 0, error3 = 0;
    float k1 = 1;  //近端1
    float k2 = 0.5;  //中端0.5
    float k3 = 0.5;   //远端0.5
    interval = (58 - top) / 3;   //应该（59-top）/3

    for (int i = 58; i > 58 - interval; i--)
        error1 += Line_Mid[i] - 30;

    for (int i = 58 - interval; i > 58 - 2 * interval; i--)
        error2 += Line_Mid[i] - 30;

    for (int i = 58 - 2 * interval; i > top; i--)
        error3 += Line_Mid[i] - 30;

    return error1 * k1 + error2 * k2 + error3 * k3;
}
