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

    // float slope = (float)delX / delY;

    int steps = (abs(delX) >= abs(delY)) ? abs(delX) : abs(delY);

    float incX = (float)delX / steps;
    float incY = (float)delY / steps;

    float newX = x1, newY = y_1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        printf("(%.3f,%.3f)\n", (newX + 0.5), (newY + 0.5));
        glVertex2i((int)(newX + 0.5), (int)(newY + 0.5));
        newX += incX;
        newY += incY;
    }
    glEnd();
    glFlush();

    printf("\nDDA ended.");
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    DDA(x1, y_1, x2, y2);
}

void init() {
    glClearColor(0, 0, 0, 1);
    glColor3f(1, 1, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);  // 100,100

    glPointSize(5);
}

int main(int c, char **v) {
    printf("Enter two points...(max100,max100)");
    printf("\nPoint 1 - (x1 y1): ");
    scanf("%d %d", &x1, &y_1);
    printf("Point 2 - (x2 y2): ");
    scanf("%d %d", &x2, &y2);

    DDA(x1, y_1, x2, y2);

    glutInit(&c, v);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(600, 100);
    glutCreateWindow("DDA Line Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
