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

void drawCar(int n, int m, int car[][m], int x, int y);

void addCar(struct car_list * list, struct n_car);

void drawBoarder (int w, int h, int boarder[]);

int main(int argc, char *argv[]) {
    time_t t = time(0);
    srand(time(0));
    clock_t clocks = clock();
    Console_clear();
    FILE * c = NULL;
    if ((c = fopen("c.txt", "r"))==NULL) {
        printf("Cannot open file %s\n", "c.txt");
        exit(EXIT_FAILURE);
    }
    int n = 15, m = 15;
    int car[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(i == j) car[i][j] = 1;
            else if(i + j == n - 1) car[i][j] = 1;
            else if (j == m / 2) car[i][j] = 1;
            else if (i == n / 2) car[i][j] = 1;
            else car[i][j] = 0;
        }
    }
    // for (int i = 0; i < 4; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         printf("%d ", car[i][j]);
    //     }
    //     puts("");
    // }


    int maxCars = 5000;
    struct n_car cars[maxCars];
    struct car_list car_list = {
        &cars[0],
        maxCars,
        0
    };




    // Console_setSize(h, w);
    Canvas_invertYOrientation();
    int butt = 0;
    int w, h;
    if (argc > 1 &&  argv[1][0] == 'c' ) {
        w = Console_size().columns;
        h = Console_size().rows * 2;
    } else {
        w = 20;
        h = 30;
    }
    int x = 4, y = 3;
    Canvas_setSize(w, h);


    int boarder[h + 1];

    for (int i = 0; i < h + 1; i++) {
        boarder[i] = randInt(0, 1);
    }
    boarder[h] = 1;
    float speed = 0.0008;
    
        // Console_clear();
    int counter = 0;
    do {
        if (counter > 30) {
            struct n_car curr = {
                randInt(2, w - 3),
                h + 3
            };
            addCar(&car_list, curr);
            t = time(0);
            // Console_clear();
            counter = 0;
        }


        for (int i = 0; i < car_list.count; i++) cars[i].y -= speed * 100;
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
        drawCar(n, m, car, x, y+5);
        Canvas_setColorRGB(100, 200, 50);
        for (int i = 0; i < car_list.count; i++) {
            // Canvas_setColorRGB(randInt(0, 255),randInt(0, 255),randInt(0, 255));
            Canvas_setColorRGB(255, 255, 255);
            drawCar(n, m, car, cars[i].x, cars[i].y);
        }
        drawBoarder(w, h, boarder);
        Canvas_endDraw();
        //draw
        for (int i = 0; i < car_list.count; i++) {
            if (fabs(x - cars[i].x) < 3 && fabs(y - cars[i].y) < 4) {
                // Console_clear();
                // printf("TY PROIGRAL\n");
                // return EXIT_FAILURE;
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


void drawCar(int n, int m, int car[][m], int x, int y) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
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