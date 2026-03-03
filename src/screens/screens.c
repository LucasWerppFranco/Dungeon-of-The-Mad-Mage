#include "screens.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <sys/ioctl.h>
#include <unistd.h>

void term_move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

void term_hide_cursor(void) {
    printf("\033[?25l");
}

void term_show_cursor(void) {
    printf("\033[?25h");
}

void term_clear(void) {
    printf("\033[2J");
}

void term_flush(void) {
    fflush(stdout);
}

TermSize term_get_size(void) {

    struct winsize w;
    TermSize size = {0, 0};

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        size.rows = w.ws_row;
        size.cols = w.ws_col;
    }

    return size;
}

void draw_ascii_overlay(int start_row,
                        int start_col,
                        const char **art,
                        int lines) {

    for (int i = 0; i < lines; i++) {

        const char *line = art[i];

        wchar_t wline[2048];
        mbstowcs(wline, line, 2048);

        int visual_col = 0;

        for (int j = 0; wline[j] != L'\0'; j++) {

            int width = wcwidth(wline[j]);
            if (width < 0) width = 1;

            if (wline[j] != L' ') {

                term_move_cursor(start_row + i,
                                 start_col + visual_col);

                printf("%lc", wline[j]);
            }

            visual_col += width;
        }
    }

    term_flush();
}

static char *read_file(const char *filename) {

    FILE *f = fopen(filename, "r");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *buffer = malloc(size + 1);
    if (!buffer) {
        fclose(f);
        return NULL;
    }

    fread(buffer, 1, size, f);
    buffer[size] = '\0';

    fclose(f);
    return buffer;
}

static char **json_get_screen(const char *json,
                              const char *screen_name,
                              int *out_lines) {

    char key[128];
    sprintf(key, "\"%s\"", screen_name);

    char *pos = strstr(json, key);
    if (!pos) return NULL;

    pos = strchr(pos, '[');
    if (!pos) return NULL;

    pos++;

    char **lines = NULL;
    int count = 0;

    while (*pos && *pos != ']') {

        if (*pos == '"') {

            pos++;
            char *end = strchr(pos, '"');
            if (!end) break;

            int len = end - pos;

            char **tmp = realloc(lines,
                                 sizeof(char*) * (count + 1));
            if (!tmp) break;

            lines = tmp;

            lines[count] = malloc(len + 1);
            strncpy(lines[count], pos, len);
            lines[count][len] = '\0';

            count++;

            pos = end + 1;

        } else {
            pos++;
        }
    }

    *out_lines = count;
    return lines;
}

static void free_screen(char **screen, int lines) {

    if (!screen) return;

    for (int i = 0; i < lines; i++)
        free(screen[i]);

    free(screen);
}

void render_screen_from_json(const char *filename,
                             const char *screen_name,
                             int row,
                             int col) {

    char *json = read_file(filename);
    if (!json) return;

    int lines = 0;

    char **screen = json_get_screen(json,
                                    screen_name,
                                    &lines);

    if (screen) {

        term_hide_cursor();

        draw_ascii_overlay(row,
                           col,
                           (const char **)screen,
                           lines);

        term_show_cursor();

        free_screen(screen, lines);
    }

    free(json);
}
