//
// Created by SanseYooyea on 2023/10/22.
//

#ifndef INC_3_0SEEKFREE_CH32V307VCT6_OPENSOURCE_LIBRARY_LINE_H
#define INC_3_0SEEKFREE_CH32V307VCT6_OPENSOURCE_LIBRARY_LINE_H

#include "point.h"

typedef struct Line {
    Point *points;
    int length;
} Line;

/**
 * �ж�һ�����Ƿ�������
 * @param line ��
 * @param p ��
 * @return TRUE if the point is on the line, FALSE otherwise
 */
boolean contains(Line line, Point p);

#endif //INC_3_0SEEKFREE_CH32V307VCT6_OPENSOURCE_LIBRARY_LINE_H
