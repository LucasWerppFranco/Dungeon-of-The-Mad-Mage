#ifndef STRUCT_H
#define STRUCT_H

typedef struct {
    int width;
    int height;
} Box;

Box box_create(int width, int height);

void print_border_top(Box *b);
void print_border_bottom(Box *b);
void print_box(Box *b, const char *text);
void print_line(Box *b, const char *text);
void print_line_center(Box *b, const char *text);
void print_line_right(Box *b, const char *text);

#endif
