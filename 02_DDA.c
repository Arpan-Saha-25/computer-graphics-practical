/*
Implement DDA algorithm : Digital Differential Analyse
*/
#include <GL/glu.h>
#include <GL/glut.h>
#include <fenv.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int x1, y_1, x2, y2;

void DDA(int x1, int y_1, int x2, int y2) {
    printf("\nperforming Digital Differential Analyse.....");
    int delX = x2 - x1;
    int delY = y2 - y_1;
    float slope = delY == 0 ? 0 : (float)delX / delY;

    float newX = x1, newY = y_1;

    while (newX <= x2) {
        printf("\n(x,y) = (%.3f,%.3f)", newX, newY);
        if (delX >= delY) {
            // delX = 1;
            newX = newX + 1;
            newY = newY + slope;
        } else if (delX < delY) {
            // delY = 1;
            newX = newX + (1 / slope);
            newY = newY + 1;
        }
    }

    printf("\nDDA ended.");
}

int main(int argc, char const *argv[]) {
    printf("Enter two points...");
    printf("\nPoint 1 - (x1 y1): ");
    scanf("%d %d", &x1, &y_1);
    printf("Point 2 - (x2 y2): ");
    scanf("%d %d", &x2, &y2);

    DDA(x1, y_1, x2, y2);

    return 0;
}
