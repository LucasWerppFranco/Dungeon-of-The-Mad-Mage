#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>

#include "fire/fire.h"
#include "struct/struct.h"

void clear_screen() {
    printf("\033[H\033[J");
}

int main() {

    setlocale(LC_ALL, "");
    srand(time(NULL));

    int box_width = 103;
    int box_height = 40;

    int fire_width = box_width - 2;
    int fire_height = box_height - 2;

    Fire *fire = fire_create(fire_width, fire_height);
    if (!fire) return 1;

    Box box = box_create(box_width, box_height);

    while (1) {

        clear_screen();

        fire_init(fire);
        fire_spread(fire);

        print_border_top(&box);
        fire_render_inside_box(fire);
        print_border_bottom(&box);

        usleep(30000);
    }

    fire_destroy(fire);
    return 0;
}
