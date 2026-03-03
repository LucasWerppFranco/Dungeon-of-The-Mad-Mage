#ifndef SCREENS_H
#define SCREENS_H

typedef struct {
    int rows;
    int cols;
} TermSize;

void term_move_cursor(int row, int col);
void term_hide_cursor(void);
void term_show_cursor(void);
void term_clear(void);
void term_flush(void);

TermSize term_get_size(void);

void draw_ascii_overlay(int start_row,
                        int start_col,
                        const char **art,
                        int lines);

void render_screen_from_json(const char *filename,
                             const char *screen_name,
                             int row,
                             int col);

#endif
