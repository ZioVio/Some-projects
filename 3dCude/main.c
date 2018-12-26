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

#define PI 3.1415926

struct Pos {
    float x;
    float y;
};

typedef struct Pos Pos;

void rotateCubeX(int cube[][20][20], float angle, int size, Pos points[], int z_axis);

void rotateCubeY(int cube[][20][20], float angle, int size, Pos points[], int y_axis);

void printMatrixX(int size, int z, int cube[][size][size]);

void printMatrixY(int size, int y, int cube[][size][size]);

int main(int argc, char *argv[]) {
    int w = Console_size().columns;
    int h = Console_size().rows * 2;
    Canvas_invertYOrientation();
    Canvas_setSize(w, h);

    int size = 6;

    int cube[20][20][20] = {0};
    Pos cubePoints[8];
    Pos upper[4];
    Pos lower[4];
    Pos right[4];
    Pos left[4];
    float angle = PI/4;
    int upper_z_axis = 20/2 - size / 2;
    int right_y_axis = 20/2 + size / 2;
    int left_y_axis = 20/2 - size / 2;
    int lower_z_axis = 20/2 + size / 2;
    for (int i = 0; i < 4; i++) {
        upper[i].x = size * cos(angle) + 10;
        upper[i].y = size * sin(angle) + 10;
        angle += PI/2;
        int x = upper[i].x;
        int y = upper[i].y;
        cube[x][y][upper_z_axis] = 1;
    }
    angle = PI/4;
    for (int i = 0; i < 4; i++) {
        right[i].x = size * cos(angle) + 10;
        right[i].y = size * sin(angle) + 10;
        angle += PI/2;
        int x = right[i].x;
        int y = right[i].y;
        cube[x][right_y_axis][y] = 1;
    }
    angle = PI/4;
    for (int i = 0; i < 4; i++) {
        left[i].x = size * cos(angle) + 10;
        left[i].y = size * sin(angle) + 10;
        angle += PI/2;
        int x = left[i].x;
        int y = left[i].y;
        cube[x][left_y_axis][y] = 1;
    }
    angle = PI/4;
    for (int i = 0; i < 4; i++) {
        lower[i].x = size * cos(angle) + 10;
        lower[i].y = size * sin(angle) + 10;
        angle += PI/2;
        int x = lower[i].x;
        int y = lower[i].y;
        cube[x][y][lower_z_axis] = 1;
    }

    assert(right[0].x == upper[0].x);
    assert(upper[1].x == left[1].x);
    assert(lower[0].x == right[3].x);
    assert(right[0].x == upper[0].x);

    int index = 0;
    for (int i = 0; i < 4; i++) {
        cube[i] = upper[]
    }
    

    float rotAngleX = 0;
    float rotAngleY = 0;
    int key = 0;
    do {

        // rotateCubeX(cube, rotAngleX, size, upper, 20/2 + size / 2);
        // printMatrixX(20, 20/2 + size / 2, cube);
        rotateCubeY(cube, rotAngleY, size, right, right_y_axis);
        printMatrixY(20, right_y_axis, cube);
        key = Console_getChar();
        switch (key) {
            case 'd': rotAngleX -= PI/12; break;
            case 'a': rotAngleX += PI/12; break;
            case 'w': rotAngleY += PI/12; break;
            case 's': rotAngleY -= PI/12; break; 
        }
        
    } while(1);


    return 0;
}

void printMatrixX(int size, int z, int cube[][size][size]) {
    Console_clear();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cube[i][j][z] == 1 ? printf("%d ", cube[i][j][z]) : printf("  "); 
        }
        puts("");
    }
}
void printMatrixY(int size, int y, int cube[][size][size]) {
    Console_clear();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cube[i][y][j] == 1 ? printf("%d ", cube[i][y][j]) : printf("  "); 
        }
        puts("");
    }
}

void rotateCubeX(int cube[][20][20], float angle, int size, Pos points[], int z_axis) {
    for (int i = 0; i < 4; i++) {
        int x = points[i].x;
        int y = points[i].y;
        cube[x][y][z_axis] = 0;
    }
    float ang = PI/4 + angle;
    for (int i = 0; i < 4; i++) {
        points[i].x = size * cos(ang) + 10;
        points[i].y = size * sin(ang) + 10;
        int x = points[i].x;
        int y = points[i].y;
        cube[x][y][z_axis] = 1;
        ang += PI/2;
    }
}

void rotateCubeY(int cube[][20][20], float angle, int size, Pos points[], int y_axis) {
    for (int i = 0; i < 4; i++) {
        int x = points[i].x;
        int y = points[i].y;
        cube[x][y_axis][y] = 0;
    }
    float ang = PI/4 + angle;
    for (int i = 0; i < 4; i++) {
        points[i].x = size * cos(ang) + 10;
        points[i].y = size * sin(ang) + 10;
        int x = points[i].x;
        int y = points[i].y;
        cube[x][y_axis][y] = 1;
        ang += PI/2;
    }
}

