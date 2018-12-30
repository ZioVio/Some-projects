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


typedef struct pos
{
    int x;
    int y;
} Pos;

typedef struct tree {
    Pos point1;
    Pos point2;
} treePoints;

int randInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// void addPoints(treePoints treePoints[], treePoints points) {

// }

treePoints createPoints(Pos point1, Pos point2) {
    treePoints res = {
        point1, point2
    };
    return res;
}

int main(int argc, char *argv[])
{
    srand(time(0));
    int nToys;
    if (argc > 1) nToys = atoi(argv[1]);
    else nToys = 20;
    int w = Console_size().columns;
    int h = Console_size().rows * 2;
    Canvas_invertYOrientation();
    Canvas_setSize(w, h);
    Pos toys[nToys];
    int r = 2;
    treePoints tree[h * 2];
    int c = 0;
    int zoneLen = h / 4;

    Pos point1 = {w/2, h};
    Pos point2 = {w/2, h};

    int ind = 0;
    tree[ind] = createPoints(point1, point2);
    for (ind = 1; ind < zoneLen; ind++) {
        point1.x -= 1;
        point2.x += 1;
        point1.y--;
        point2.y--;
        tree[ind] = createPoints(point1, point2);
        // printf("x1 = %d y1 = %d x2 = %d  y2 = %d \n", point1.x, point1.y, point2.x, point2.y);
    }
    int offset = (point2.x - w / 2) / 2;
    // for (int i = 0; i < offset; i++) {
    //     point1.x += 1;
    //     point2.x -= 1;
    //     tree[ind++] = createPoints(point1, point2);
    // }
        point1.x += offset;
        point2.x -= offset;
        tree[ind++] = createPoints(point1, point2);


    while(h - point1.y < zoneLen * 2) {
        point1.x -= 1;
        point2.x += 1;
        point1.y--;
        point2.y--;
        tree[ind++] = createPoints(point1, point2);
        // printf("x1 = %d y1 = %d x2 = %d  y2 = %d \n", point1.x, point1.y, point2.x, point2.y);
    }


    offset = (point2.x - w / 2) / 2;
    // for (int i = 0; i < offset; i++) {
    //     point1.x += 1;
    //     point2.x -= 1;
    //     tree[ind++] = createPoints(point1, point2);
    // }
    point1.x += offset;
    point2.x -= offset;
    tree[ind++] = createPoints(point1, point2);


    while(h - point1.y < zoneLen * 3) {
        point1.x -= 1;
        point2.x += 1;
        point1.y--;
        point2.y--;
        tree[ind++] = createPoints(point1, point2);
        //printf("x1 = %d y1 = %d x2 = %d  y2 = %d \n", point1.x, point1.y, point2.x, point2.y);
    }


    offset = (point2.x - w / 2) / 2;
    // for (int i = 0; i < offset; i++) {
    //     point1.x += 1;
    //     point2.x -= 1;
    //     tree[ind++] = createPoints(point1, point2);
    // }


    point1.x += offset;
    point2.x -= offset;
    tree[ind++] = createPoints(point1, point2);

    // return 0;
    for (int i = 0; i < nToys; i++) {
        toys[i].y = randInt(tree[ind - 3].point1.y + r + 2, tree[0].point1.y - r - 2);

        toys[i].x = randInt(tree[ind - toys[i].y + zoneLen].point1.x +  r + 2,tree[ind - toys[i].y + zoneLen].point2.x -  r - 2);

    }
    printf("Toys are ok\n");
    // return 0;
    time_t t = time(0);
    do {
        Canvas_beginDraw();
        Canvas_setColorRGB(0, 255, 0);
        int x1, y1, x2, y2;
        for (int i = 0; i < ind; i++) {
            x1 = tree[i].point1.x;
            x2 = tree[i].point2.x;
            y1 = tree[i].point1.y;
            y2 = tree[i].point2.y;
            if (y1 == tree[i + 1].point1.y) {
                Canvas_strokeLine(x1, y1, tree[i + 1].point1.x, y1);
                Canvas_strokeLine(x2, y2, tree[i + 1].point2.x, y2);
            } else {

                Canvas_putPixel(x1, y1);
                Canvas_putPixel(x2, y2);
            }
        }
        if (t - time(0) < -5) {

            for (int i = 0; i < nToys; i++) {
                toys[i].y = randInt(tree[ind - 3].point1.y + r + 2, tree[0].point1.y + r - 2);

                toys[i].x = randInt(tree[ind - toys[i].y + zoneLen].point1.x +  r + 2,tree[ind - toys[i].y + zoneLen].point2.x -  r - 2);

            }
            t = time(0);
        }
        for (int i = 0; i < nToys; i++) {
            Canvas_setColorRGB(randInt(0, 255), randInt(0, 255), randInt(0, 255));
            Canvas_fillCircle(toys[i].x, toys[i].y, r);
        }
        // Canvas_strokeLine(tree[zoneLen].point1.x, tree[zoneLen - 1].point1.y, tree[zoneLen].point2.x, tree[zoneLen - 1].point2.y);
        // Canvas_strokeLine(tree[zoneLen].point1.x, tree[zoneLen - 1].point1.y, tree[zoneLen].point2.x, tree[zoneLen - 1].point2.y);
        
        // Canvas_strokeLine(x1, y1, x2, y2);
            
            
        // Canvas_strokeLine(tree[ind].point1.x,
        //                     tree[ind].point2.x,
        //                     tree[ind].point1.y,
        //                     tree[ind].point2.y);
        // while(ind < zoneLen*2) {
        //     int x1 = tree[ind].point1.x;
        //     int x2 = tree[ind].point2.x;
        //     int y1 = tree[ind].point1.y;
        //     int y2 = tree[ind++].point2.y;
        //     Canvas_putPixel(x1, y1);
        //     Canvas_putPixel(x2, y2);
        // }
        // Canvas_strokeLine(tree[ind].point1.x,
        //                     tree[ind].point2.x,
        //                     tree[ind].point1.y,
        //                     tree[ind].point2.y);
        Canvas_endDraw();
        sleepMillis(500);
    } while(!Console_isKeyDown());

    return 0;
}