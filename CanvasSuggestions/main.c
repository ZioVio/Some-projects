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



void Canvas_strokeEllipse(int cx, int cy,  int a,  int b);

void Canvas_fillEllipse(int cx, int cy,  int a, int b); 

void Canvas_strokeCircle2(int cx, int cy, float r);

void Canvas_fillCircle2(int cx, int cy, float r);

int main(int argc, char *argv[]) {
    int w = Console_size().columns;
    int h = Console_size().rows * 2;
    Canvas_invertYOrientation();
    Canvas_setSize(w, h);

    Canvas_beginDraw();
    Canvas_setColorRGB(0, 255, 0);

    Canvas_fillEllipse(w/5, h/2, w/6, h/8);
    
    
    Canvas_strokeEllipse(2*w/3, h/3, w/12, h/4);
    
    
    float radius = 10;
    Canvas_setColorRGB(255, 0, 0);
    
    Canvas_strokeCircle2(2*w/3.5, 2*h/3, radius);

    Canvas_fillCircle2(w/3, h/5, radius);

    Canvas_endDraw();
    
    return 0;
    
}
    

void Canvas_strokeCircle2(int cx, int cy, float r) {
    Canvas_strokeEllipse(cx, cy, r, r);
}

void Canvas_fillCircle2(int cx, int cy, float r) {
    Canvas_fillEllipse(cx, cy, r, r);
}

void Canvas_strokeEllipse(int cx, int cy,  int a,  int b) {
    float len_ellipse = PI*(a + b);
    float additional_accuracy = 2;
    float angle = 2*PI/(len_ellipse * additional_accuracy);
    for (float tmp_angle = 0; tmp_angle <= 2 * PI; tmp_angle += angle) {
        float x = a*cos(tmp_angle);
        float y = b*sin(tmp_angle);
        Canvas_putPixel(x + cx, y + cy);
    }
}

void Canvas_fillEllipse(int cx, int cy,  int a, int b) {
    for (float x = -a; x < a; x++) {
        for (float y = -b; y < b; y++) {
            if (x*x/(a*a) + y*y/(b*b) <= 1) {
                Canvas_putPixel(x + cx, y  + cy);
            }
        }
    }
}