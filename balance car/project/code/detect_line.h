#ifndef DETECTLINE_DETECT_LINE_H
#define DETECTLINE_DETECT_LINE_H

#include <malloc.h>
#include <stdio.h>
#include "common_data.h"
#include "point.h"
#include "line.h"

#define WALL 0
#define ROAD 1

#define IMG_BOTTOM 60
#define IMG_RIGHT 120

#define MAX_LINE_SIZE 100

/**
 * 判断一个点是否为黑色
 * @param img 二值化图像
 * @param p 点
 * @return 如果是黑色，返回TRUE，否则返回FALSE
 */
boolean is_black(int (*img)[IMG_RIGHT], Point p);

/**
 * 判断一个点是否为白色
 * @param img 二值化图像
 * @param p 点
 * @return 如果是白色，返回TRUE，否则返回FALSE
 */
boolean is_white(int (*img)[IMG_RIGHT], Point p);

/**
 * 寻找左边界起始点
 * @param img 二值化图像
 * @return 左边界起始点
 *         如果没有找到，返回{-1, -1}
 */
Point find_left_start_point(int (*img)[IMG_RIGHT]);

/**
 * 寻找右边界起始点
 * @param img 二值化图像
 * @return 右边界起始点
 *        如果没有找到，返回{-1, -1}
 */
Point find_right_start_point(int (*img)[IMG_RIGHT]);

/**
 * 寻找左边线
 * @param img 二值化图像
 * @param left_start_point 左边线起始点
 * @return 左边线
 */
Line find_left_line(int (*img)[IMG_RIGHT], Point left_start_point);

/**
 * 寻找右边线
 * @param img 二值化图像
 * @param right_start_point 右边线起始点
 * @return 右边线
 */
Line find_right_line(int img[IMG_BOTTOM][IMG_RIGHT], Point right_start_point);

/**
 * 寻找另一侧线上与给定点同高的点
 * @param line 另一侧边线
 * @param p 给定点
 * @return 另一侧线上与给定点同高的点
 *        如果没有找到，返回{-1, -1}
 */
Point find_point_in_same_height(Line line, Point p);

/**
 * 寻找中线
 * @param left_line 左边线
 * @param right_line 右边线
 * @return 中线
 */
Line find_middle_line(Line left_line, Line right_line);

/**
 * 左边线跟踪中线
 * @param left_line 左边
 * @param approx_num 近似点点数
 * @param dist 左边线和中线的距离
 * @return 中线
 */
Line track_left_line(Line left_line, int approx_num, float dist);

/**
 * 右边线跟踪中线
 * @param right_line 右边
 * @param approx_num 近似点点数
 * @param dist 右边线和中线的距离
 * @return 中线
 */
Line track_right_line(Line right_line, int approx_num, float dist);

#endif //DETECTLINE_DETECT_LINE_H
