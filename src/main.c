#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>
#include <signal.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>

#include "fire/fire.h"
#include "struct/struct.h"
#include "screens/screens.h"

volatile sig_atomic_t resized = 0;
static struct termios original_term;

void handle_resize(int sig) {
    (void)sig;
    resized = 1;
}

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_term);
    term_show_cursor();
}

void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &original_term);
    atexit(disable_raw_mode);

    struct termios raw = original_term;

    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int key_pressed() {
    char c;
    if (read(STDIN_FILENO, &c, 1) == 1) {
        return c;
    }
    return 0;
}

void clear_screen_once() {
    printf("\033[2J");
}

void move_cursor_home() {
    printf("\033[H");
}

int main() {

    setlocale(LC_ALL, "");
    signal(SIGWINCH, handle_resize);
    enable_raw_mode();

    srand(time(NULL));

    int box_width = 103;
    int box_height = 40;

    TermSize ts = term_get_size();

    if (ts.cols < box_width || ts.rows < box_height) {
        printf("Terminal muito pequeno!\n");
        printf("Minimo necessario: %dx%d\n", box_width, box_height);
        return 1;
    }

    int fire_width = box_width - 2;
    int fire_height = box_height - 2;

    Fire *fire = fire_create(fire_width, fire_height);
    if (!fire) return 1;

    Box box = box_create(box_width, box_height);

    clear_screen_once();
    term_hide_cursor();

    time_t start_time = time(NULL);
    int show_overlay = 0;
    int running = 1;

    while (running) {

        int key = key_pressed();
        if (key == 'q' || key == 'Q') {
            running = 0;
            continue;
        }

        if (resized) {
            ts = term_get_size();

            if (ts.cols < box_width || ts.rows < box_height) {
                term_clear();
                term_move_cursor(1, 1);
                printf("Terminal muito pequeno!\n");
                fflush(stdout);
                continue;
            }

            term_clear();
            resized = 0;
        }

        move_cursor_home();

        fire_init(fire);
        fire_spread(fire);

        print_border_top(&box);
        fire_render_inside_box(fire);
        print_border_bottom(&box);

        if (!show_overlay &&
            difftime(time(NULL), start_time) >= 1.0) {
            show_overlay = 1;
        }

        if (show_overlay) {
            render_screen_from_json(
                "screens/screens.json",
                "title",
                3,
                5
            );
            render_screen_from_json(
                "screens/screens.json",
                "thanks",
                3,
                5
            );
        }

        fflush(stdout);
        struct timespec ts_sleep;
        ts_sleep.tv_sec = 0;
        ts_sleep.tv_nsec = 30000000; // 30ms
        nanosleep(&ts_sleep, NULL);
    }

    fire_destroy(fire);
    return 0;
}
