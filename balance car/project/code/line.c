//
// Created by SanseYooyea on 2023/10/22.
//

#include "line.h"

boolean contains(Line line, Point p) {
    for (int i = 0; i < line.length; i++) {
        if (line.points[i].row == p.row && line.points[i].column == p.column) {
            return TRUE;
        }
    }
    return FALSE;
}