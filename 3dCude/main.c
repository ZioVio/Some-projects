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
    float z;
};
struct PosP {
    float x;
    float y;
    float z;
};

typedef struct Pos Pos;
typedef struct Pos* PosP;

void rotateCubeX(int cube[][20][20], float angle, int size, PosP points[], int z_axis);

void rotateCubeY(int cube[][20][20], float angle, int size, PosP points[], int y_axis);

void printMatrixX(int size, int z, int cube[][size][size]);

void printMatrixY(int size, int y, int cube[][size][size]);

void clearCube(int size, int cube[][size][size]);

void fillCube(int size, int cube[][size][size], Pos cubePoints[]);

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
    // printf("%d ", lower_z_axis);
    int index = 0;

    for (int i = 0; i < 4; i++) {
        upper[i].x = size * cos(angle) + 10;
        upper[i].y = size * sin(angle) + 10;
        upper[i].z = upper_z_axis;
        angle += PI/2;
        int x = upper[i].x;
        int y = upper[i].y;
        cube[x][y][upper_z_axis] = 1;
        cubePoints[index++] = upper[i]; 
    }
    angle = PI/4;
    for (int i = 0; i < 4; i++) {
        right[i].x = size * cos(angle) + 10;
        right[i].y = size * sin(angle) + 10;
        right[i].z = right_y_axis;
        angle += PI/2;
        int x = right[i].x;
        int y = right[i].y;
        cube[x][right_y_axis][y] = 1;
    }
    angle = PI/4;
    for (int i = 0; i < 4; i++) {
        left[i].x = size * cos(angle) + 10;
        left[i].y = size * sin(angle) + 10;
        left[i].z = left_y_axis;
        angle += PI/2;
        int x = left[i].x;
        int y = left[i].y;
        cube[x][left_y_axis][y] = 1;
    }
    angle = PI/4;
    for (int i = 0; i < 4; i++) {
        lower[i].x = size * cos(angle) + 10;
        lower[i].y = size * sin(angle) + 10;
        lower[i].z = lower_z_axis;
        angle += PI/2;
        int x = lower[i].x;
        int y = lower[i].y;
        cube[x][y][lower_z_axis] = 1;
        cubePoints[index++] = lower[i]; 
    }

    assert(right[0].x == upper[0].x);
    assert(upper[1].x == left[1].x);
    assert(lower[0].x == right[3].x);
    assert(right[0].x == upper[0].x);



    PosP upperP[4] = {
        &cubePoints[0],
        &cubePoints[1],
        &cubePoints[2],
        &cubePoints[3]
    };
    PosP lowerP[4] = {
        &cubePoints[4],
        &cubePoints[5],
        &cubePoints[6],
        &cubePoints[7]
    };
    PosP rightP[4] = {
        &cubePoints[0],
        &cubePoints[3],
        &cubePoints[4],
        &cubePoints[7]
    };
    PosP leftP[4] = {
        &cubePoints[2],
        &cubePoints[1],
        &cubePoints[5],
        &cubePoints[6]
    };

    // for (int i = 0; i < 8; i++) {
    //     printf("x = %f y = %f z = %f\n", cubePoints[i].x, cubePoints[i].y, cubePoints[i].z);
    // }
    // return 0;
    // clearCube(20, cube);
    fillCube(20, cube, cubePoints);


    float rotAngleX = PI/6;
    float rotAngleY = 0;
    int key = 0;
    // for (int i = 0; i < 20; i++) {
    //     Console_clear();
    //     printMatrixY(20, i, cube);
    //     sleepMillis(500);
    // }
    do {

        // rotateCubeX(cube, rotAngleX, size, upper, 20/2 + size / 2);
        // printMatrixX(20, 20/2 + size / 2, cube);
        // rotateCubeY(cube, rotAngleY, size, rightP, right_y_axis);
        // printMatrixY(20, right_y_axis, cube);
        rotateCubeX(cube, rotAngleX, size, upperP, upper_z_axis);
        rotateCubeX(cube, rotAngleX, size, lowerP, lower_z_axis);

        // key = Console_getChar();
        // switch (key) {
        //     case 'd': rotAngleX -= PI/12; break;
        //     case 'a': rotAngleX += PI/12; break;
        //     case 'w': rotAngleY += PI/12; break;
        //     case 's': rotAngleY -= PI/12; break; 
        // }
        
    } while(0);

    // fillCube(20, cube, cubePoints);
    // for (int i = 0; i < 20; i++) {
    //     Console_clear();
    //     printMatrixX(20, i, cube);
    //     sleepMillis(500);
    // }

    return 0;
}

void printMatrixX(int size, int z, int cube[][size][size]) {
    Console_clear();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cube[i][j][z] == 1 ? printf("%d ", cube[i][j][z]) : printf("  "); 
            // printf("%d ", cube[i][j][z]);
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

void rotateCubeX(int cube[][20][20], float angle, int size, PosP points[], int z_axis) {
    // clearCube(20, cube);
    float ang = PI/4 + angle;
    for (int i = 0; i < 4; i++) {
        points[i] -> x = size * cos(ang) + 10;
        points[i] -> y = size * sin(ang) + 10;
        int x = points[i] -> x;
        int y = points[i] -> y;
        // cube[x][y][z_axis] = 1;
        ang += PI/2;
    }
}

void rotateCubeY(int cube[][20][20], float angle, int size, PosP points[], int y_axis) {
    // clearCube(20, cube);
    // for (int i = 0; i < 4; i++) {
    //     int x = points[i] -> x;
    //     int y = points[i] -> y;
    //     // int z = points[i] -> z;
    //     cube[x][y_axis][y] = 0;
    // }
    float ang = PI/4 + angle;
    for (int i = 0; i < 4; i++) {
        points[i] -> x = size * cos(ang) + 10;
        points[i] -> y = size * sin(ang) + 10;
        // int x = points[i] -> x;
        // int y = points[i] -> y;
        // cube[x][y_axis][y] = 1;
        ang += PI/2;
    }
}


void clearCube(int size, int cube[][size][size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                cube[i][j][k] = 0;
            }
        }
    }
}

void fillCube(int size, int cube[][size][size], Pos cubePoints[]) {
    clearCube(size, cube);
    for (int i = 0; i < 8; i++) {
        int x = cubePoints[i].x;
        int y = cubePoints[i].y;
        int z = cubePoints[i].z;
        cube[x][y][z] = 1;
    }
}
