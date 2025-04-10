#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

int xc, yc, r;  // centre(xc,yc) and radius r

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawCirclePoints(int x, int y) {
    // Plot points in all eight octants
    drawPixel(xc + x, yc + y);
    drawPixel(xc - x, yc + y);
    drawPixel(xc + x, yc - y);
    drawPixel(xc - x, yc - y);
    drawPixel(xc + y, yc + x);
    drawPixel(xc - y, yc + x);
    drawPixel(xc + y, yc - x);
    drawPixel(xc - y, yc - x);
}

void midpointCircle() {
    int x = 0;
    int y = r;
    int p = 1 - r;  // Simplified decision parameter (5/4 - r)

    drawCirclePoints(x, y);

    while (x < y) {
        printf("value of (x,y) : ", x, y);
        x++;
        if (p < 0) {
            p = p + 2 * x + 1;  // No change in y
        } else {
            y--;
            p = p + 2 * (x - y) + 1;
        }
        drawCirclePoints(x, y);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 0.0);  // yellow
    glPointSize(2.0);
    midpointCircle();
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Black background
    gluOrtho2D(-1000, 1000, -1000, 1000);
}

int main(int argc, char** argv) {
    printf("Enter the radius of the circle(take \"value\" > 200 -> good visibility): \n");
    scanf("%d", &r);

    printf("Enter the center of the circle (space separated): ");
    scanf("%d %d", &xc, &yc);

    if (abs(xc) + r > 1000 || abs(yc) + r > 1000) {
        printf("xx_WarninG_xx: Some points might be out of visible bounds.\n");
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(1000, 0);
    glutCreateWindow("Midpoint Circle Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}