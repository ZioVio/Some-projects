#include <stdio.h>    // Для друку в термінал
#include <math.h>     // Для математичних функцій
#include <stdlib.h>   // Деякі додаткові функції
#include <progbase.h> // Спрощений ввід і вивід даних у консоль
#include <progbase/console.h>
#include <progbase/canvas.h>
#include <time.h>
#include <stdbool.h>
// there are a lot of bugs
// to close the program just kill it =)
// i believe i will continue working on the snake further 
// dont pay attention on some shitcoded moments =) I only study
void clear() {
    while(getchar() != '\n');
}

void draw_snake(int len, int array_x[], int array_y[]) {
    
    Canvas_setColorRGB(0, 255, 0);
    for (int i = 0; i < len; i++) {
        Canvas_putPixel(array_x[i], array_y[i]);
    }
    
}

void draw_border(int w, int h) {
    Canvas_setColorRGB(255, 255, 255);
    Canvas_strokeRect(2, 2, w, h);
}

void update_snake(int x_head, int y_head, int array_x[], int array_y[], int len) {
    array_x[0] = x_head;
    array_y[0] = y_head;
    for(int i = 1; i < len; i++) {
        array_x[len - i] = array_x[len - i - 1];
        array_y[len - i] = array_y[len - i - 1];
    }
}

bool create_apple(int W, int H, int *apple_x, int *apple_y) {
    *apple_x = rand() % (W - 1 - 3 + 1) + 3;
    *apple_y = rand() % (H - 1 - 3 + 1) + 3;
    return 1;
}

enum {
    RIGHT = 'd',
    LEFT = 'a',
    DOWN = 's',
    UP = 'w'
};



void move (int direction, int *prev_direction, int *x_head, int * y_head) {

    switch (direction) {
        case RIGHT: if (*prev_direction == LEFT) *x_head -= 1; else *x_head += 1; break;
        case LEFT: if (*prev_direction == RIGHT) *x_head += 1; else *x_head -= 1; break;
        case DOWN: if (*prev_direction == UP) *y_head += 1; else *y_head -= 1; break;
        case UP: if (*prev_direction == DOWN) *y_head -= 1; else *y_head += 1; break;
        case 'Q': exit(0);
        default: move(*prev_direction, &*prev_direction, &*x_head, &*y_head); break;

    }
}

int main(int argc, char *argv[]) {
    srand(time(0));
    Console_clear();
    int len = 30;


    int apple_x = -1, apple_y = -1;

    Canvas_invertYOrientation();

    int W = Console_size().columns;
    int H = Console_size().rows*2;
    Canvas_setSize(W, H);

    int border_x = W - 2;
    int border_y = H - 2;

    int w = W / 5;
    int h = H / 5;

    int array_x[W*H], array_y[W*H];
    for (int i = 0; i < len; i++) {
        array_x[i] = i + W / 2;
        array_y[i] = H / 2;
    }

    int x_head = array_x[0];
    int y_head = array_y[0];


    int DIRECTION = UP;
    int prev_DIRECTION;

    create_apple(W, H, &apple_x, &apple_y);

    do {


        if (Console_isKeyDown()) {
            prev_DIRECTION = DIRECTION;
            DIRECTION = getchar();
        }


        update_snake(x_head, y_head, array_x, array_y, len);
        

        for (int i = 2; i < len; i++) {
            if (x_head == array_x[i] && y_head == array_y[i]) {
                len = i;
            }
        }

        move(DIRECTION, &prev_DIRECTION, &x_head, &y_head);

        if (x_head == 2) x_head = border_x;
        else if (y_head == 2) y_head = border_y;
        else if (x_head == border_x + 1) x_head = 3; 
        else if (y_head == border_y + 1) y_head = 3;

        Canvas_beginDraw();
        draw_border(border_x, border_y);
        draw_snake(len, array_x, array_y);
        Canvas_setColorRGB(255, 0, 0);
        Canvas_putPixel(apple_x, apple_y);
        Canvas_endDraw();

        Console_setCursorPosition(1, 1);
        printf("Len = %d\n", len);





        for (int i = 0; i < len; i++) {
            if (array_x[i] == apple_x && array_y[i] == apple_y) {
                create_apple(border_x, border_y, &apple_x, &apple_y);
                len += 1;
            }
        }

        sleepMillis(50);
    } while(1);


    return 0;
}





