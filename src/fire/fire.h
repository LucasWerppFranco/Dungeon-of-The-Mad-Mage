#ifndef FIRE_H
#define FIRE_H

typedef struct {
    int width;
    int height;
    int **buffer;
} Fire;

Fire *fire_create(int width, int height);
void fire_destroy(Fire *f);

void fire_init(Fire *f);
void fire_spread(Fire *f);
void fire_render_inside_box(Fire *f);

#endif
