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

int areaWidth = 1000, areaHeight = 1000;
float viewAngle = PI/2;

typedef struct Vec3D {
    float x;
    float y;
    float z;
}Vec;

typedef struct pos {
    int x; int y;
} Pos;

// typedef struct Cube {
//     Vec cube[8];
//     Pos cubePos;
// } Cube;

Vec createVec(float x, float y, float z);

float len(Vec vec) {
    return sqrt(vec.x*vec.x + vec.y * vec.y + vec.z * vec.z);
}
void drawVec(Vec c, Vec vec);

bool areEqualFloats(float a, float b) {
    return fabs(a - b) < 1e-3;
}

bool areEqualVects(Vec Vect1, Vec Vect2) {
    return (areEqualFloats(Vect1.x, Vect2.x) && areEqualFloats(Vect1.y, Vect2.y) && areEqualFloats(Vect1.z, Vect2.z));
}

Vec rotateVecX(Vec vec, float angle) {
    float realXY = sqrt(vec.x * vec.x + vec.z * vec.z);
    float betha = atan2(vec.z, vec.x);
    betha += angle;
    Vec result = createVec(realXY * cos(betha), vec.y ,realXY * sin(betha));

    return result;
}

Vec rotateVecY(Vec vec, float angle) {
    float realYZ = sqrt(vec.y * vec.y + vec.z * vec.z);
    float betha = atan2(vec.z, vec.y);
    betha += angle;
    Vec result = createVec(vec.x ,realYZ * cos(betha),realYZ * sin(betha));

    return result;
}

void updateCube(Pos pPos, Pos cPose, Vec cube[]);

Vec mult(Vec vec, float num);

Vec norm(Vec vec);

void test() {
    float x = 10, y = 2.2, z = -0.2222; 
    Vec vec1 = {x, y, z};
    Vec vec2 = createVec(x, y, z);
    assert(areEqualVects(vec1, vec2));

    Vec rotVec = createVec(1, 1, 1);
    rotVec = rotateVecX(rotVec, PI/2);
    // assert(areEqualFloats(rotVec.x, 0));
    assert(areEqualFloats(len(rotVec), sqrt(3)));

    float num = 5.4;
    Vec multTest = createVec(x, y, z);
    Vec expected = createVec(x * num, y * num, z * num);
    assert(areEqualVects(expected, mult(multTest, num)));

    assert(areEqualFloats(1, len(norm(vec1))));




}

void drawCube(Vec cube[], Vec c) {
    float x = c.x;
    float y = c.y;
    Canvas_strokeLine(cube[2].x + x, cube[2].y + y, cube[3].x + x, cube[3].y + y);
    Canvas_strokeLine(cube[3].x + x, cube[3].y + y, cube[1].x + x, cube[1].y + y);
    Canvas_strokeLine(cube[1].x + x, cube[1].y + y, cube[5].x + x, cube[5].y + y);
    Canvas_strokeLine(cube[5].x + x, cube[5].y + y, cube[4].x + x, cube[4].y + y);
    Canvas_strokeLine(cube[7].x + x, cube[7].y + y, cube[3].x + x, cube[3].y + y);
    Canvas_strokeLine(cube[6].x + x, cube[6].y + y, cube[2].x + x, cube[2].y + y);
    Canvas_strokeLine(cube[6].x + x, cube[6].y + y, cube[4].x + x, cube[4].y + y);
    Canvas_strokeLine(cube[5].x + x, cube[5].y + y, cube[7].x + x, cube[7].y + y);
    Canvas_strokeLine(cube[6].x + x, cube[6].y + y, cube[7].x + x, cube[7].y + y);
    Canvas_setColorRGB(0, 250, 50);
    Canvas_strokeLine(cube[0].x + x, cube[0].y + y, cube[1].x + x, cube[1].y + y);
    Canvas_strokeLine(cube[0].x + x, cube[0].y + y, cube[2].x + x, cube[2].y + y);
    Canvas_strokeLine(cube[0].x + x, cube[0].y + y, cube[4].x + x, cube[4].y + y);
}


float playerToCubeXDist(Pos pPos, Pos cPos);

Vec norm(Vec vec);


int main(int argc, char *argv[]) {
    Console_clear();
    int w = Console_size().columns;
    int h = Console_size().rows * 2;
    Canvas_invertYOrientation();
    Canvas_setSize(w, h - 5);
    test();

    Vec central_vec = createVec(w/2, h/2, 0);
    // Vec central_vec2 = createVec(w/2 + 5, h/2 + 15, 0);

    float sideLen = 50;

    Vec cube[8];

    cube[0] = createVec(sideLen / 2,sideLen / 2 , sideLen / 2);
    cube[1] = createVec(sideLen / 2,sideLen / 2 , -sideLen / 2);
    cube[2] = createVec(sideLen / 2,-sideLen / 2 , sideLen / 2);
    cube[3] = createVec(sideLen / 2,-sideLen / 2 , -sideLen / 2);
    cube[4] = createVec(-sideLen / 2,sideLen / 2 , sideLen / 2);
    cube[5] = createVec(-sideLen / 2,sideLen / 2 , -sideLen / 2);
    cube[6] = createVec(-sideLen / 2,-sideLen / 2 , sideLen / 2);
    cube[7] = createVec(-sideLen / 2,-sideLen / 2 , -sideLen / 2);

    float rotAngleX = PI/2;
    float rotAngleY = PI/3;
    float rotAng = PI/100;
    float stdLen = len(cube[0]);

    float playerStep = 20;


    Pos playerPos = {areaWidth/2, 200};
    Pos cubePos = {areaWidth/2, areaHeight/2};
    for (int i = 0; i < 8; i++)  
        {
            cube[i] = rotateVecX(cube[i], rotAngleX);
        }
    for (int i = 0; i < 8; i++)  
        {
            cube[i] = rotateVecY(cube[i], rotAngleY);
        }
    do {
        ///
        float normViewDistance = (2.0/3.0) * (float)areaHeight / 2.0;
        float scale = normViewDistance/(float)playerToCubeXDist(playerPos, cubePos);
        for (int i = 0; i < 8; i++) {
            cube[i] = mult(norm(cube[i]), stdLen * scale);
        }
        ///
        // float prev_angle = 0;
        float xoff = playerPos.x - cubePos.x;
        float angle = atan2(xoff, playerToCubeXDist(playerPos, cubePos));
        float currAngle = atan2(cube[0].z, cube[0].x);
        for (int i = 0; i < 8; i++)  
        {
            cube[i] = rotateVecX(cube[i], angle - currAngle);
        }
        // prev_angle = angle;

        ///



        ///


        // for (int i = 0; i < 8; i++) 
        // {
        //     cube[i] = rotateVecY(cube[i], rotAngleY);
        // }
        // for (int i = 0; i < 8; i++)  
        // {
        //     cube[i] = rotateVecX(cube[i], rotAngleX);
        // }

                
        Canvas_beginDraw();

        // for (int i = 0; i < 8; i++) {
        //     if (i % 2 == 0) Canvas_setColorRGB(200, 50, 0);
        //     else Canvas_setColorRGB(0, 255, 0);
        //     drawVec(central_vec, cube[i]);
        // }
        Canvas_setColorRGB(255, 255, 255);
        drawCube(cube, central_vec);

        Canvas_strokeLine(w/2, 0, central_vec.x, central_vec.y);

        Canvas_endDraw();
        
        sleepMillis(5);

        int key = Console_getChar();

        switch (key) {
            case 'w': {
                playerPos.y += playerStep;
                break;
            }
            case 's': {
                playerPos.y -= playerStep;
                break;
            }
            case 'a': {
                playerPos.x += playerStep;
                central_vec.x = w/2 - (-xoff / areaWidth)*w; 
                for (int i = 0; i < 8; i++)  
                {
                    cube[i] = rotateVecX(cube[i], angle);
                }
                break;
            }
            case 'd': {
                playerPos.x -= playerStep;
                central_vec.x = w/2 + (xoff / areaWidth)*w;
                for (int i = 0; i < 8; i++)  
                {
                    cube[i] = rotateVecX(cube[i], angle);
                }
                break;
            }
        }
        printf("dist = %f\nxoff = %f ", playerToCubeXDist(playerPos, cubePos), xoff);
        // updateCube(playerPos, cubePos, cube);
        // rotAngle += 0.0001;
    } while(1);



    return 0;
}

Vec norm(Vec vec) {
    float l = len(vec);
    Vec res = createVec(vec.x / l, vec.y / l, vec.z / l);
    return res;
}

float playerToCubeXDist(Pos pPos, Pos cPos) {
    return abs(cPos.y - pPos.y);
}

// void updateCube(Pos pPos, Pos cPos, Vec cube[]) {
//     float normViewDistance = (2.0/3.0) * (float)areaHeight / 2.0;
//     for (int i = 0; i < 8; i++) {
//         cube[i] = mult(cube[i], normViewDistance/(float)playerToCubeXDist(pPos, cPos));
//     }
// }

Vec mult(Vec vec, float num) {
    Vec res = {vec.x * num, vec.y * num, vec.z * num};
    return res;
}

Vec createVec(float x, float y, float z) {
    Vec res = {
        x, y, z
    };
    return res;
}

void drawVec(Vec c, Vec vec) {
    float x = vec.x;
    float y = vec.y;
    Canvas_strokeLine(c.x, c.y, c.x + x, c.y + y);
}