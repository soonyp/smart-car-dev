//
// Created by SanseYooyea on 2023/10/29.
//

#include "ui.h"
#include "zf_device_tft180.h"
#include "cam_preprocess.h"

void show_default_image() {
    tft180_show_gray_image(0, 0, &binary_img_CDM[0][0], IMG_COL, IMG_ROW, 60, 60, 1);
    tft180_show_binary_image(0, 61, &line_image[0][0], IMG_COL, IMG_ROW, 60, 60);
}

void show_enum() {
    char p[20], d[20], run[20], fork[20];
    if (choose == 0) {
        sprintf(p, "○ P: %f", piderror.Kp);
        sprintf(d, "D: %f", piderror.Kd);
        sprintf(run, "发车：%s", running ? (run_left ? "向左发车" : "向右发车") : "未选择方向");
        sprintf(fork, "Y路：%s", forking ? (fork_left ? "向左进入" : "向右进入") : "未选择方向");
    } else if (choose == 1) {
        sprintf(p, "P: %f", piderror.Kp);
        sprintf(d, "○ D: %f", piderror.Kd);
        sprintf(run, "发车：%s", running ? (run_left ? "向左发车" : "向右发车") : "未选择方向");
        sprintf(fork, "Y路：%s", forking ? (fork_left ? "向左进入" : "向右进入") : "未选择方向");
    } else if (choose == 2) {
        sprintf(p, "P: %f", piderror.Kp);
        sprintf(d, "D: %f", piderror.Kd);
        sprintf(run, "○ 发车：%s", running ? (run_left ? "向左发车" : "向右发车") : "未选择方向");
        sprintf(fork, "Y路：%s", forking ? (fork_left ? "向左进入" : "向右进入") : "未选择方向");
    } else {
        sprintf(p, "P: %f", piderror.Kp);
        sprintf(d, "D: %f", piderror.Kd);
        sprintf(run, "发车：%s", running ? (run_left ? "向左发车" : "向右发车") : "未选择方向");
        sprintf(fork, "○ Y路：%s", forking ? (fork_left ? "向左进入" : "向右进入") : "未选择方向");
    }

    tft180_show_string(61, 0, p);
    tft180_show_string(61, 20, d);
    tft180_show_string(61, 40, run);
    tft180_show_string(61, 60, fork);
}

void show_ui() {
    tft180_clear();
    show_default_image();
    show_enum();
}

void on_up() {
    up++;
    choose = (down - up) % total_choice;
    show_ui();
}

void on_down() {
    down++;
    choose = (down - up) % total_choice;
    show_ui();
}

void on_left() {
    switch (choose) {
        case P:
            piderror.Kp -= 0.1f;
            break;
        case D:
            piderror.Kd -= 0.1f;
            break;
        case RUN:
            running = true;
            run_left = true;
            break;
        case FORK:
            forking = true;
            fork_left = true;
            break;
    }

    show_ui();
}

void on_right() {
    switch (choose) {
        case P:
            piderror.Kp += 0.1f;
            break;
        case D:
            piderror.Kd += 0.1f;
            break;
        case RUN:
            running = true;
            run_left = false;
            break;
        case FORK:
            forking = true;
            fork_left = false;
            break;
    }

    show_ui();
}
