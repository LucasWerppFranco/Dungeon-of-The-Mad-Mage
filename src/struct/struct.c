#define _XOPEN_SOURCE 700

#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

static int visual_width(const char *s) {
    int width = 0;
    wchar_t wc;
    mbstate_t state;
    memset(&state, 0, sizeof state);
    const char *p = s;

    while (*p) {
        size_t len = mbrtowc(&wc, p, MB_CUR_MAX, &state);
        if (len == (size_t)-1 || len == (size_t)-2) break;
        int w = wcwidth(wc);
        if (w > 0) width += w;
        p += len;
    }

    return width;
}

Box box_create(int width, int height) {
    Box b;
    b.width = width;
    b.height = height;
    return b;
}

void print_border_top(Box *b) {
    printf("╔");
    for (int i = 0; i < b->width - 2; i++)
        printf("═");
    printf("╗\n");
}

void print_border_bottom(Box *b) {
    printf("╚");
    for (int i = 0; i < b->width - 2; i++)
        printf("═");
    printf("╝\n");
}

void print_line(Box *b, const char *text) {
    printf("║");

    int content_width = visual_width(text);
    printf("%s", text);

    int padding = b->width - 2 - content_width;
    for (int j = 0; j < padding; j++)
        printf(" ");

    printf("║\n");
}

void print_line_center(Box *b, const char *text) {
    printf("║");

    int content_width = visual_width(text);
    int total_padding = b->width - 2 - content_width;
    int left = total_padding / 2;
    int right = total_padding - left;

    for (int j = 0; j < left; j++)
        printf(" ");

    printf("%s", text);

    for (int j = 0; j < right; j++)
        printf(" ");

    printf("║\n");
}

void print_line_right(Box *b, const char *text) {
    printf("║");

    int content_width = visual_width(text);
    int left = b->width - 2 - content_width;

    for (int j = 0; j < left; j++)
        printf(" ");

    printf("%s", text);
    printf("║\n");
}

void print_box(Box *b, const char *text) {

    print_border_top(b);

    char *copy = malloc(strlen(text) + 1);
    strcpy(copy, text);

    char *line = strtok(copy, "\n");

    int lines_printed = 0;
    while (line && lines_printed < b->height - 2) {
        print_line(b, line);
        line = strtok(NULL, "\n");
        lines_printed++;
    }

    for (; lines_printed < b->height - 2; lines_printed++)
        print_line(b, "");

    print_border_bottom(b);

    free(copy);
}
