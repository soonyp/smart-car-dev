#include <math.h>
#include "detect_line.h"
#include "utils.h"

boolean is_black(int (*img)[IMG_RIGHT], Point p) {
    return img[p.row][p.column] == WALL;
}

boolean is_white(int (*img)[IMG_RIGHT], Point p) {
    return img[p.row][p.column] == ROAD;
}

Point find_left_start_point(int (*img)[IMG_RIGHT]) {
    Point notfound = {-1, -1};

    int center = IMG_RIGHT / 2;
    for (int r = IMG_BOTTOM - 1; r >= 0; r--) {
        for (int c = center; c >= 0; c--) {
            Point p = {r, c};
            if (is_black(img, p)) {
                return p;
            }
        }
    }
    return notfound;
}

Point find_right_start_point(int (*img)[IMG_RIGHT]) {
    Point notfound = {-1, -1};

    int center = IMG_RIGHT / 2;
    for (int r = IMG_BOTTOM - 1; r >= 0; r--) {
        for (int c = center; c < IMG_RIGHT; c++) {
            Point p = {r, c};
            if (is_black(img, p)) {
                return p;
            }
        }
    }
    return notfound;
}

Line find_left_line(int (*img)[IMG_RIGHT], Point left_start_point) {
    // initialize
    static Point points[MAX_LINE_SIZE];
    static Line line = {points, 0};
    Point current_point = left_start_point;
    Direction current_direction = UP;

    // first point
    line.points[line.length++] = current_point;

    // turn direction times
    int turn = 0;

    // check line is closed
    while (turn < 4
           && current_point.row != 0 && current_point.row != IMG_RIGHT - 1
           && current_point.column != 0 && current_point.column != IMG_BOTTOM - 1) {

        // get front point, right point and right front point
        // ○ ○
        // ● ○
        Point front_point = get_front_point(current_point, current_direction);
        Point right_point = get_right_point(current_point, current_direction);
        Point right_front_point = get_right_front_point(current_point, current_direction);

        // make sure right point is not accessible
        // if not, break, maybe end of the line or img is wrong
        // TODO need to check, if the img is wrong
        if (is_black(img, right_point)) {
            printf("error: right point [%d, %d] = %d is accessible\n", right_point.row, right_point.column, img[right_point.row][right_point.column]);
            break;
        }

        if (is_black(img, front_point)) {
            // front point is accessible
            if (is_black(img, right_front_point)) {
                // right front point is accessible
                // move to right front point
                current_point = right_front_point;
                change_direction(&current_direction, RIGHT);
                turn++;
                if (!contains(line, right_front_point)) {
                    // meets recording conditions
                    line.points[line.length++] = current_point;
                    turn = 0;
                }
                continue;
            }

            // right front point is not accessible
            current_point = front_point;
            if (!contains(line, front_point)) {
                // meets recording conditions
                line.points[line.length++] = current_point;
                turn = 0;
            }
            continue;
        }

        // both front point and right front point are not accessible
        // change direction to left
        change_direction(&current_direction, LEFT);
        turn++;
    }

    return line;
}

Line find_right_line(int img[IMG_BOTTOM][IMG_RIGHT], Point right_start_point) {
    // initialize
    static Point points[MAX_LINE_SIZE];
    static Line line = {points, 0};
    Point current_point = right_start_point;
    Direction current_direction = UP;

    // first point
    line.points[line.length++] = current_point;

    // turn direction times
    int turn = 0;

    // check line is closed
    while (turn < 4
           && current_point.row != 0 && current_point.row != IMG_RIGHT - 1
           && current_point.column != 0 && current_point.column != IMG_BOTTOM - 1) {

        // get front point, right point and right front point
        // ○ ○
        // ○ ●
        Point front_point = get_front_point(current_point, current_direction);
        Point left_point = get_left_point(current_point, current_direction);
        Point left_front_point = get_left_front_point(current_point, current_direction);

        // make sure right point is not accessible
        // if not, break, maybe end of the line or img is wrong
        // TODO need to check, if the img is wrong
        if (is_black(img, left_point)) {
            printf("error: left point [%d, %d] = %d is accessible\n", left_point.row, left_point.column, img[left_point.row][left_point.column]);
            break;
        }

        if (is_black(img, front_point)) {
            // front point is accessible
            if (is_black(img, left_front_point)) {
                // left front point is accessible
                // move to left front point
                current_point = left_front_point;
                change_direction(&current_direction, LEFT);
                turn++;
                if (!contains(line, left_front_point)) {
                    // meets recording conditions
                    line.points[line.length++] = current_point;
                    turn = 0;
                }
                continue;
            }

            // right front point is not accessible
            current_point = front_point;
            if (!contains(line, front_point)) {
                // meets recording conditions
                line.points[line.length++] = current_point;
                turn = 0;
            }
            continue;
        }

        // both front point and right front point are not accessible
        // change direction to left
        change_direction(&current_direction, RIGHT);
        turn++;
    }

    return line;
}

Point find_point_in_same_height(Line line, Point p) {
    for (int i = 0; i < line.length; i++) {
        if (line.points[i].row == p.row) {
            return line.points[i];
        }
    }
    return (Point) {p.row, IMG_RIGHT};
}

Line find_middle_line(Line left_line, Line right_line) {
    // initialize
    static Point points[MAX_LINE_SIZE];
    static Line line = {points, 0};

    if (left_line.length > right_line.length) {
        for (int i = 0; i < left_line.length; i++) {
            Point left_point = left_line.points[i];
            Point right_point = find_point_in_same_height(right_line, left_point);
            Point middle_point = find_middle_point(left_point, right_point);
            line.points[i] = middle_point;
        }
    } else {
        for (int i = 0; i < right_line.length; i++) {
            Point right_point = right_line.points[i];
            Point left_point = find_point_in_same_height(left_line, right_point);
            Point middle_point = find_middle_point(left_point, right_point);
            line.points[i] = middle_point;
        }
    }

    return line;
}

Line track_left_line(Line left_line, int approx_num, float dist) {
    static Point points[MAX_LINE_SIZE];
    static Line line = {points, 0};

    // Calculate the half of the approximate number of points
    int half = approx_num / 2;

    // Iterate through each input point
    for (int i = 0; i < left_line.length; i++) {
        // Get the x and y coordinates of the current input point
        float x0 = left_line.points[i].row;
        float y0 = left_line.points[i].column;

        // Calculate the difference in x and y coordinates between the current point and the point at half the approximate number of points away
        float dx = left_line.points[clip(i + half, 0, left_line.length - 1)].row - x0;
        float dy = left_line.points[clip(i + half, 0, left_line.length - 1)].column - y0;

        // Calculate the distance between the two points
        float dn = sqrtf(dx * dx + dy * dy);

        // Normalize the difference in x and y coordinates
        dx /= dn;
        dy /= dn;

        // Calculate the new x and y coordinates based on the distance and normalized difference
        line.points[i].row = x0 + dx * dist;
        line.points[i].column = y0 + dy * dist;
    }
}

Line track_right_line(Line right_line, int approx_num, float dist) {
    static Point points[MAX_LINE_SIZE];
    static Line line = {points, 0};

    for (int i = 0; i < right_line.length; i++) {
        float dx = right_line.points[(i + approx_num, 0, right_line.length - 1)][0] - right_line.points[clip(i - approx_num, 0, right_line.length - 1)].row;
        float dy = right_line.points[clip(i + approx_num, 0, right_line.length - 1)][1] - right_line.points[clip(i - approx_num, 0, right_line.length - 1)].column;
        float dn = sqrtf(dx * dx + dy * dy);
        dx /= dn;
        dy /= dn;
        line.points[i].row = right_line.points[i].row + dy * dist;
        line.points[i].column = right_line.points[i].column - dx * dist;
    }
}
