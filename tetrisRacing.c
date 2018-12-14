#include <stdio.h> 
#include <math.h>
#include <stdlib.h>
#include <progbase.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <progbase/console.h>
#include <progbase/canvas.h>

struct n_car {
    int x;
    int y;
};

struct car_list {
    struct n_car * cars;
    size_t capacity;
    size_t count;
};

int randInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void removeCar(struct car_list * list, int index);

void drawCar(int car[][3], int x, int y);

void addCar(struct car_list * list, struct n_car);

int main(int argc, char *argv[]) {
    time_t t = time(0);
    Console_clear();
    FILE * c = NULL;
    if ((c = fopen("c.txt", "r"))==NULL) {
        printf("Cannot open file %s\n", "c.txt");
        exit(EXIT_FAILURE);
    }
    int car[4][3];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            const char ch =  fgetc(c);
            if (ch != '\n') car[i][j] = ch - 48;
            else j--;
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", car[i][j]);
        }
        puts("");
    }


    int maxCars = 50;
    struct n_car cars[maxCars];
    struct car_list car_list = {
        &cars[0],
        maxCars,
        0
    };


    int w = 20, h = 30;
    Console_setSize(h, w);
    Canvas_setSize(w, h);
    Canvas_invertYOrientation();
    int butt = 0;
    int x = 4, y = 3;
    do {
        int time_now = time(0);
        struct n_car curr = {
            randInt(1, w - 2),
            h - 3
        };
        if (time_now - t > 0) {
            addCar(&car_list, curr);
            t = time(0);
        }
        for (int i = 0; i < car_list.count; i++) cars[i].y -= 1;
        for (int i = 0; i < car_list.count; i++) {
           if (cars[i].y < -1) removeCar(&car_list, i); // rewrite THIS
        }
        

        // draw
        Canvas_beginDraw();
        drawCar(car, x, y);
        for (int i = 0; i < car_list.count; i++) {
            drawCar(car, cars[i].x, cars[i].y);
        }
        Canvas_endDraw();
        // draw
        if (Console_isKeyDown()) {
            butt = getchar();
            switch (butt) {
                case 'a': {
                    if (x > 2)
                    x--;
                    break;
                }
                case 'd': {
                    if (x < w - 3)
                    x++;
                    break;
                }
            }
        }
        sleepMillis(100);
    } while(1);


    return 0;
}


void drawCar(int car[][3], int x, int y) {
    Canvas_setColorRGB(0, 255, 0);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (car[i][j] == 1) Canvas_putPixel( -j + x + 1, y + 2 - i);
        }
    }
}
            

void addCar(struct car_list * list, struct n_car car) {
    int Index = list ->count;
    list -> cars[Index] = car;
    list -> count += 1;
}

void removeCar(struct car_list * list, int index) {
    list -> count -= 1;
    for (int i = index; i < list -> count; i++) {
        list -> cars[i] = list -> cars[i + 1];
    }
}