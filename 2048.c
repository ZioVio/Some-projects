#include <stdio.h> 
#include <math.h>
#include <stdlib.h>
#include <progbase.h>
#include <stdbool.h>
#include <time.h>
#include <progbase/console.h>
#include <progbase/canvas.h>

void draw(int matrix[][4]);

void add_rand(int matrix[][4]);

int rand_int(int min,int max) {
    return rand () % (max - min + 1) + min;
}

enum {
    RIGHT = 'd',
    LEFT = 'a',
    DOWN = 's',
    UP = 'w'
};

void matrix_move(int move, int matrix[][4]);


int main(int argc, char *argv[]) {
    Console_clear();
    srand(time(0));
    Canvas_invertYOrientation();

    int w = Console_size().columns;
    int h = Console_size().rows*2;
    Canvas_setSize(w, h);

    int matrix[4][4] = {0};
    
    add_rand(matrix);

    do {
        // Canvas_beginDraw();
        draw(matrix);
        // Canvas_endDraw();

        int move = Console_getChar();
        Console_clear();
        matrix_move(move, matrix);
        add_rand(matrix);


    } while (1);

    return 0;
}
void matrix_move(int move, int matrix[][4]) {
    switch (move) {
        case RIGHT: {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 3; j++) {
                    if (matrix[i][j] == matrix[i][j + 1]) {
                        matrix[i][j + 1] = matrix[i][j] * 2;
                        matrix[i][j] = 0;   
                    } 
                }
            }
            bool flag = 1;
            while(flag) {
                flag = 0;
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (matrix[i][j + 1] == 0) {
                            matrix[i][j + 1] = matrix[i][j];
                            if (matrix[i][j] != 0) flag = 1; 
                            matrix[i][j] = 0;
                        }
                    }
                }
            }
            break;

        }
        case LEFT: {
            for (int i = 0; i < 4; i++) {
                for (int j = 3; j > 0; j--) {
                    if (matrix[i][j] == matrix[i][j - 1]) {
                        matrix[i][j - 1] = matrix[i][j] * 2;
                        matrix[i][j] = 0;   
                    } 
                }
            }
            bool flag = 1;
            while(flag) {
                flag = 0;
                for (int i = 0; i < 4; i++) {
                    for (int j = 3; j > 0; j--) {
                        if(matrix[i][j - 1] == 0) {
                            matrix[i][j - 1] = matrix[i][j];
                            if (matrix[i][j] != 0) flag = 1;
                            matrix[i][j] = 0; 
                        }
                    }
                }
            }
            break;
        }
        case UP: {
            for (int i = 3; i > 0; i--) {
                for (int j = 0; j < 4; j++) {
                    if (matrix[i][j] == matrix[i - 1][j]) {
                        matrix[i - 1][j] = matrix[i][j] * 2;
                        matrix[i][j] = 0;   
                    } 
                }
            }
             bool flag = 1;
            while(flag) {
                flag = 0;
                for (int i = 3; i > 0; i--) {
                    for (int j = 0; j < 4; j++) {
                        if(matrix[i - 1][j] == 0) {
                            matrix[i - 1][j] = matrix[i][j];
                            if (matrix[i][j] != 0) flag = 1;
                            matrix[i][j] = 0; 
                        }
                    }
                }
            }
            break;
        }
        case DOWN: {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 4; j++) {
                    if (matrix[i][j] == matrix[i + 1][j]) {
                        matrix[i + 1][j] = matrix[i][j] * 2;
                        matrix[i][j] = 0;   
                    } 
                }
            }
            bool flag = 1;
            while(flag) {
                flag = 0;
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 4; j++) {
                        if(matrix[i + 1][j] == 0) {
                            matrix[i + 1][j] = matrix[i][j];
                            if (matrix[i][j] != 0) flag = 1;
                            matrix[i][j] = 0; 
                        }
                    }
                }
            }
            break;
        }
    }
}


void draw(int matrix[][4]) {
    // Canvas_setColorRGB(255, 255, 255);
    // float size = 50;
    // Canvas_strokeRect(1, 1, size, size);
    // for (int i = 1; i <= 3  ; i++) {
    //     Canvas_strokeLine(i*(size/4) + 1, 1, i*(size/4) + 1, size);
    //     Canvas_strokeLine(1, i*(size/4) + 1, size, i*(size/4) + 1);
    // }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (matrix[i][j] != 0)
            printf("%3d", matrix[i][j]);
            else printf("   ");
        }
        puts("");
    }
}
 
void add_rand(int matrix[][4]) {
    int flag = rand_int(1, 10);
    if (flag < 9) {
        int n = rand_int(0, 3);
        int m = rand_int(0, 3);
        while (matrix[n][m] != 0) {
            n = rand_int(0, 3);
            m = rand_int(0, 3);
        }
        matrix[n][m] = 2;
    } else {
        int n = rand_int(0, 3);
        int m = rand_int(0, 3);
        while (matrix[n][m] != 0) {
            n = rand_int(0, 3);
            m = rand_int(0, 3);
        }
        matrix[n][m] = 4;
    }
}