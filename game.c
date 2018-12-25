#include <stdio.h>    
#include <math.h>    
#include <stdlib.h>  
#include <progbase.h> 
#include <progbase/console.h>
#include <progbase/canvas.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

int rand_int(int min, int max) {
    return rand()%(max - min + 1) + min;
}
// there are a lot of bugs
// to close the program just kill it =)
// i believe i will continue working on the snake further 
// dont pay attention on some shitcoded moments =) I only study
struct pos {
    int x;
    int y;
};
typedef struct pos pos;

void clear() {
    while(getchar() != '\n');
}

void draw_snake(int len, pos snake[]) {
    for (int i = 0; i < len; i++) {
        Canvas_putPixel(snake[i].x, snake[i].y);
    }
    
}

void draw_border(int w, int h) {
    Canvas_setColorRGB(255, 255, 255);
    Canvas_strokeRect(2, 2, w, h);
}

void update_snake(pos *head, pos snake[], int len) {
    snake[0].x = head -> x;
    snake[0].y = head -> y;
    for(int i = 1; i < len; i++) {
        snake[len - i].x = snake[len - i - 1].x;
        snake[len - i].y = snake[len - i - 1].y;
    }
}

bool create_apple(int W, int H, pos *apple) {
    apple -> x = rand_int(2, W - 1);
    apple -> y = rand_int(2, H - 1);
    return 1;
}

enum {
    RIGHT = 'd',
    LEFT = 'a',
    DOWN = 's',
    UP = 'w'
};



void move (int direction, int prev_direction, pos* head) {

    switch (direction) {
        case RIGHT: if (prev_direction == LEFT) head -> x -= 1; else head -> x += 1; break;
        case LEFT: if (prev_direction == RIGHT) head -> x += 1; else head -> x -= 1; break;
        case DOWN: if (prev_direction == UP) head -> y += 1; else head -> y -= 1; break;
        case UP: if (prev_direction == DOWN) head -> y -= 1; else head -> y += 1; break;
        case 'Q': exit(0);
    }
}

int main(int argc, char *argv[]) {
    bool eat = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[1], "-e") == 0) eat = true;
    }

    srand(time(0));
    Console_clear();
    int len = 30;


    pos apple = {-1, -1};
    pos super_apple = {-1, -1};

    Canvas_invertYOrientation();

    int W = Console_size().columns;
    int H = Console_size().rows*2;
    Canvas_setSize(W, H);

    int border_x = W - 2;
    int border_y = H - 2;

    pos snake[W*H];
    for (int i = 0; i < len; i++) {
        snake[i].x = i + W / 2;
        snake[i].y = H / 2;
    }

    pos head = snake[0];
    head.x = snake[0].x;
    head.y = snake[0].y;


    int DIRECTION = UP;
    int prev_DIRECTION;

    create_apple(W, H, &apple);
    bool s_apple = false;
    int s_apple_counter = 0;
    do {


        if (Console_isKeyDown()) {
            prev_DIRECTION = DIRECTION;
            DIRECTION = getchar();
            switch (prev_DIRECTION) {
                case UP: if (DIRECTION == DOWN) DIRECTION = UP; break;
                case RIGHT: if (DIRECTION == LEFT) DIRECTION = RIGHT; break;
                case LEFT: if (DIRECTION == RIGHT) DIRECTION = LEFT; break;
                case DOWN: if (DIRECTION == UP) DIRECTION = DOWN; break;
            }
            if (DIRECTION != UP && DIRECTION != DOWN && DIRECTION != LEFT && DIRECTION != RIGHT) DIRECTION = prev_DIRECTION;
        }


        update_snake(&head, snake ,len);
        

        for (int i = 2; i < len; i++) {
            if (head.x == snake[i].x && head.y == snake[i].y) {
                if (eat) len = i;
                else {
                    printf("YOU LOST\n");
                    return EXIT_FAILURE;
                }
            }
        }

        move(DIRECTION, prev_DIRECTION, &head);

        if (head.x == 2) head.x = border_x;
        else if (head.y == 2) head.y = border_y;
        else if (head.x == border_x + 1) head.x = 3; 
        else if (head.y == border_y + 1) head.y = 3;

        Canvas_beginDraw();
        draw_border(border_x, border_y);
        if (s_apple_counter > 0) Canvas_setColorRGB(rand_int(0, 255), rand_int(0, 255), rand_int(0,255));
        else Canvas_setColorRGB(0, 255, 0);
        draw_snake(len, snake);
        if (s_apple) {
            Canvas_setColorRGB(rand_int(0, 255), rand_int(0, 255), rand_int(0,255));
            Canvas_putPixel(super_apple.x, super_apple.y);
        } else {
            Canvas_setColorRGB(255, 0, 0);
            Canvas_putPixel(apple.x, apple.y);
        }
        Canvas_endDraw();


        Console_setCursorPosition(1, 1);
        printf("Len = %d\n", len);



        for (int i = 0; i < len; i++) {
            if (snake[i].x == apple.x && snake[i].y == apple.y) {
                if (rand_int(1, 3) == 1 && s_apple == false) {
                    s_apple = true;
                    create_apple(border_x, border_y, &super_apple);
                }
                else {
                    create_apple(border_x, border_y, &apple);
                    s_apple_counter = 0;
                    len += 1;
                }
            } else if (snake[i].x == super_apple.x && snake[i].y == super_apple.y) {
                s_apple = false;
                s_apple_counter = 1;
            }
        }


        if (s_apple_counter > 0) {
            sleepMillis(20);
            s_apple_counter++;
        } else sleepMillis(50); 

        


    } while(1);


    return 0;
}





