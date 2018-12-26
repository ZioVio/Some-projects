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

struct pos
{
    float x;
    float y;
};

struct pos_list
{
    struct pos *pos;
    size_t capacity;
    size_t count;
};

void addPoint(struct pos_list *list, struct pos point)
{
    int Index = list->count;
    list->pos[Index] = point;
    list->count += 1;
}

int main(int argc, char *argv[])
{

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
        0};

    do
    {
        float x = r * pow(cos(t), 3);
        float y = r * pow(sin(t), 3);
        t += 0.0099 * 2;
        struct pos tmp = {
            x, y};
        addPoint(&list, tmp);
    } while (t < 2 * PI);

    t = 0;
    // int index = 0;
    // struct pos tmp = {r, 0};
    float y = 0;
    float ang = 0;
    do
    {
        Canvas_beginDraw();
        for (int i = 0; i < list.count; i++)
        {
            Canvas_setColorRGB(0, 255, 0);
            float x = list.pos[i].x;
            float y = list.pos[i].y;
            Canvas_putPixel(list.pos[i].x + w / 2, list.pos[i].y + h / 2);
        
            y = (x * sin(ang) + r * sin(ang) * cos(ang)) / cos(ang);
            Canvas_setColorRGB(255, 0, 0);
            // if (x < r * pow(cos(ang), 3) && y <  r * pow(sin(ang), 3))
            Canvas_putPixel(x + w / 2, y + h / 2);
        }
        ang += 0.001;
        Canvas_endDraw();
        // y = r*sin()
        // Canvas_setColorRGB(0, 255, 255);
        // Canvas_strokeLine(tmp.x + w/2, h/2, w/2, tmp.y + h/2);
        // if (index < list.count) index++;
        // else index = 0;
        sleepMillis(1);
    } while (1);

    return 0;
}