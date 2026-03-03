#include "fire.h"
#include <stdio.h>
#include <stdlib.h>

static const char *colors[] = {
    "\033[30m",
    "\033[31m",
    "\033[31;1m",
    "\033[33m",
    "\033[33;1m",
    "\033[37m",
    "\033[97m",
    "\033[93m",
    "\033[91m",
    "\033[97;1m"
};

Fire *fire_create(int width, int height) {
    Fire *f = malloc(sizeof(Fire));
    if (!f) return NULL;

    f->width = width;
    f->height = height;

    f->buffer = malloc(sizeof(int*) * height);
    if (!f->buffer) return NULL;

    for (int y = 0; y < height; y++) {
        f->buffer[y] = malloc(sizeof(int) * width);
        if (!f->buffer[y]) return NULL;

        for (int x = 0; x < width; x++)
            f->buffer[y][x] = 0;
    }

    return f;
}

void fire_destroy(Fire *f) {
    if (!f) return;

    for (int y = 0; y < f->height; y++)
        free(f->buffer[y]);

    free(f->buffer);
    free(f);
}

void fire_init(Fire *f) {
    for (int x = 0; x < f->width; x++)
        f->buffer[f->height - 1][x] = 9;
}

void fire_spread(Fire *f) {
    for (int y = 1; y < f->height; y++) {
        for (int x = 0; x < f->width; x++) {

            int decay = rand() % 3;
            int src = f->buffer[y][x];
            int dst = x - (rand() % 3) + 1;

            if (dst < 0) dst = 0;
            if (dst >= f->width) dst = f->width - 1;

            int new_val = src - decay;
            if (new_val < 0) new_val = 0;

            f->buffer[y - 1][dst] = new_val;
        }
    }
}

void fire_render_inside_box(Fire *f) {
    for (int y = 0; y < f->height; y++) {

        printf("║");

        for (int x = 0; x < f->width; x++) {

            int v = f->buffer[y][x];

            if (v == 0) {
                printf(" ");
            } else {
                printf("%s█", colors[v]);
            }
        }

        printf("\033[0m║\n");
    }
}
