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

struct pos {
    float x;
    float y;
};

struct pos_list {
    struct pos * pos;
    size_t capacity;
    size_t count;
};

void addPoint(struct pos_list * list, struct pos point) {
    int Index = list ->count;
    list -> pos[Index] = point;
    list -> count += 1;
}

int main(int argc, char *argv[]) {

    int w = Console_size().columns;
    int h = Console_size().rows * 2;
    Canvas_invertYOrientation();
    Canvas_setSize(w, h);
    
    float t = 0;
    float r = h / 2;
    int capasity = 10000;
    struct pos points[capasity];
    struct pos_list list = {
        &points[0],
        capasity,
        0
    };

    do {
        float x = r*pow(cos(t), 3);
        float y = r*pow(sin(t), 3);
        t += 0.008;
        struct pos tmp = {
            x, y
        };
        addPoint(&list, tmp);
    }while(t < 2*PI + 2);

    t = 0;
    Canvas_beginDraw();
    Canvas_setColorRGB(0, 255, 0);
    for (int i = 0; i < list.count; i++) {
        Canvas_putPixel(list.pos[i].x + w/2, list.pos[i].y + h/2);
    }
    Canvas_endDraw();



    
    return 0;
}