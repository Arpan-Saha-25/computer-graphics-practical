#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

int x1, y_1, x2, y2;

void BLA(int x1, int y_1, int x2, int y2) {
    int x = x1;
    int y = y_1;
    int dx = x2 - x1;
    int dy = y2 - y_1;

    glBegin(GL_POINTS);

    // int p = 2 * dx + dy;
    int p = 2 * dy - dx;

    while (x <= x2) {
        printf("(%d, %d) \n", x, y);
        glVertex2i(x, y);
        x++;
        if (p < 0) {
            p = p + 2 * dy;
        } else {
            p = p + 2 * dy - 2 * dx;
            y++;
        }
    }
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    BLA(x1, y_1, x2, y2);
}

void init() {
    glClearColor(0, 0, 0, 1);
    glColor3f(1, 1, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200);

    glPointSize(5);
}

int main(int c, char **v) {
    printf("Enter two points in range (0-200,0-200)...");
    printf("\nPoint 1 (x1 y1): ");
    scanf("%d %d", &x1, &y_1);
    printf("Point 2 (x2 y2): ");
    scanf("%d %d", &x2, &y2);

    glutInit(&c, v);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(600, 100);
    glutCreateWindow("Bresenham Line Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}