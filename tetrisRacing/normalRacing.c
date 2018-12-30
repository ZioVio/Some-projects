
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
    float x;
    float y;
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

void drawBoarder (int w, int h, int boarder[]);

int main(int argc, char *argv[]) {
    time_t t = time(0);
    clock_t clocks = clock();
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
    // for (int i = 0; i < 4; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         printf("%d ", car[i][j]);
    //     }
    //     puts("");
    // }


    int maxCars = 500;
    struct n_car cars[maxCars];
    struct car_list car_list = {
        &cars[0],
        maxCars,
        0
    };


    int w = 30, h = 30;
    // Console_setSize(h, w);
    Canvas_setSize(w, h);
    Canvas_invertYOrientation();
    int butt = 0;
    int x = 4, y = 3;


    int boarder[h + 1];

    for (int i = 0; i < h + 1; i++) {
        boarder[i] = randInt(0, 1);
    }
    boarder[h] = 1;
    float speed = 0.004;
    
        // Console_clear();
    int counter = 0;
    do {
        if (counter > 20) {
            struct n_car curr = {
                randInt(2, w - 3),
                h 
            };
            addCar(&car_list, curr);
            t = time(0);
            Console_clear();
            counter = 0;
        }


        for (int i = 0; i < car_list.count; i++) cars[i].y -= 0.03;
        for (int i = 0; i < car_list.count; i++) {
           if (cars[i].y < -1) removeCar(&car_list, i); // rewrite THIS
        }


        // printf("%f\n", clock()/(float)CLOCKS_PER_SEC);
        // printf("%zu now -> %zu  minus -> %zu    %f\n", clocks, clock(), clock() - clocks, (clock() - clocks)/(float)CLOCKS_PER_SEC);
        if ((clock() - clocks)/(float)CLOCKS_PER_SEC > speed)
        {
            int temp = boarder[0];
            for (int i = 0; i < h ; i++) {
                boarder[i] = boarder[i + 1];
            }
            boarder[h] = temp;
            clocks = clock();
            counter++;
        }
            
        

        // draw
        Canvas_beginDraw();
        Canvas_setColorRGB(200, 200, 50);
        drawCar(car, x, y);
        Canvas_setColorRGB(100, 200, 50);
        for (int i = 0; i < car_list.count; i++) {
            drawCar(car, cars[i].x, cars[i].y);
        }
        drawBoarder(w, h, boarder);
        Canvas_endDraw();
        //draw
        for (int i = 0; i < car_list.count; i++) {
            if (fabs(x - cars[i].x) < 3 && fabs(y - cars[i].y) < 4) {
                Console_clear();
                printf("TY PROIGRAL\n");
                return EXIT_FAILURE;
            }
        }

        sleepMillis(1);
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
    } while(1);


    return 0;
}


void drawCar(int car[][3], int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (car[i][j] == 1) Canvas_putPixel( -j + x + 1, y + 2 - i);
        }
    }
    // Canvas_setColorRGB(255, 50, 0);
    // Canvas_putPixel(x, y);
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


void drawBoarder (int w, int h, int boarder[]) {
    Canvas_setColorRGB(255, 255, 255);
    for (int i = 0; i < h + 1; i++) {
        if (boarder[i] == 1) {
            Canvas_putPixel(w - 1, i);
            Canvas_putPixel(0, i);
        } 
    }
}