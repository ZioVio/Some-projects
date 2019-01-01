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

typedef struct Vec3D {
    float x;
    float y;
    float z;
}Vec;

Vec createVec(float x, float y, float z) {
    Vec res = {
        x, y, z
    };
    return res;
}

float len(Vec vec) {
    return sqrt(vec.x*vec.x + vec.y * vec.y + vec.z * vec.z);
}
void drawVec(Vec c, Vec vec) {
    float x = vec.x;
    float y = vec.y;
    float z = vec.z;
    float len_vec = len(vec);
    Canvas_strokeLine(c.x, c.y, c.x + x, c.y + y);
}


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

void test() {
    float x = 10, y = 2.2, z = -0.2222; 
    Vec vec1 = {x, y, z};
    Vec vec2 = createVec(x, y, z);
    assert(areEqualVects(vec1, vec2));

    Vec rotVec = createVec(1, 1, 1);
    rotVec = rotateVecX(rotVec, PI/2);
    // assert(areEqualFloats(rotVec.x, 0));
    assert(areEqualFloats(len(rotVec), sqrt(3)));


}

void drawCube(Vec cube[], Vec c) {
    float x = c.x;
    float y = c.y;
    Canvas_strokeLine(cube[0].x + x, cube[0].y + y, cube[1].x + x, cube[1].y + y);
    Canvas_strokeLine(cube[0].x + x, cube[0].y + y, cube[2].x + x, cube[2].y + y);
    Canvas_strokeLine(cube[2].x + x, cube[2].y + y, cube[3].x + x, cube[3].y + y);
    Canvas_strokeLine(cube[3].x + x, cube[3].y + y, cube[1].x + x, cube[1].y + y);
    Canvas_strokeLine(cube[1].x + x, cube[1].y + y, cube[5].x + x, cube[5].y + y);
    Canvas_strokeLine(cube[5].x + x, cube[5].y + y, cube[4].x + x, cube[4].y + y);
    Canvas_strokeLine(cube[0].x + x, cube[0].y + y, cube[4].x + x, cube[4].y + y);
    Canvas_strokeLine(cube[7].x + x, cube[7].y + y, cube[3].x + x, cube[3].y + y);
    Canvas_strokeLine(cube[6].x + x, cube[6].y + y, cube[2].x + x, cube[2].y + y);
    Canvas_strokeLine(cube[6].x + x, cube[6].y + y, cube[4].x + x, cube[4].y + y);
    Canvas_strokeLine(cube[5].x + x, cube[5].y + y, cube[7].x + x, cube[7].y + y);
    Canvas_strokeLine(cube[6].x + x, cube[6].y + y, cube[7].x + x, cube[7].y + y);
}


int main(int argc, char *argv[]) {
    int w = Console_size().columns;
    int h = Console_size().rows * 2;
    Canvas_invertYOrientation();
    Canvas_setSize(w, h);
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

    // Vec testVec = createVec(5, 10, 7);
    // Vec testVec2 = createVec(-5, 20, -7);


    float rotAngleX = -PI/300;
    float rotAngleY = PI/400;
    do {
        for (int i = 0; i < 8; i++) 
        {
            cube[i] = rotateVecY(cube[i], rotAngleY);
        }
        for (int i = 0; i < 8; i++)  
        {
            cube[i] = rotateVecX(cube[i], rotAngleX);
        }
        Canvas_beginDraw();

        // for (int i = 0; i < 8; i++) {
        //     if (i % 2 == 0) Canvas_setColorRGB(200, 50, 0);
        //     else Canvas_setColorRGB(0, 255, 0);
        //     drawVec(central_vec, cube[i]);
        // }
        Canvas_setColorRGB(255, 255, 255);
        drawCube(cube, central_vec);

        Canvas_endDraw();
        
        sleepMillis(5);


        // rotAngle += 0.0001;
    } while(1);



    return 0;
}