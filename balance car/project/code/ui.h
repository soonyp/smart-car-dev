//
// Created by SanseYooyea on 2023/10/29.
//

#ifndef SMART_CAR_DEV_UI_H
#define SMART_CAR_DEV_UI_H

#include "zf_common_typedef.h"
#include "Ourcode_headfile.h"

uint8 up = 0;
uint8 down = 0;

const uint8 total_choice = 4;
enum ChooseMode {
    P = 0,
    D = 1,
    RUN = 2,
    FORK = 3
};
enum ChooseMode choose = P;

bool running = false;
bool run_left = false;

bool forking = false;
bool fork_left = false;

extern uint8 line_image[60][60];

void on_up();

void on_down();

void on_left();

void on_right();

void show_default_image();

#endif //SMART_CAR_DEV_UI_H
