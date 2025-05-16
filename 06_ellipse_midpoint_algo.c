#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

int rx, ry, xc, yc;

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawSymmetricPoints(int x, int y) {
    drawPixel(xc + x, yc + y);
    drawPixel(xc - x, yc + y);
    drawPixel(xc + x, yc - y);
    drawPixel(xc - x, yc - y);
}

void midpointEllipse() {
    float rx2 = rx * rx;
    float ry2 = ry * ry;

    // STARTING POINT
    float x = 0;
    float y = ry;

    float p1 = ry2 - (rx2 * ry) + (0.25 * rx2);
    float dx = 2 * ry2 * x;
    float dy = 2 * rx2 * y;

    // Region 1
    while (dx < dy) {
        drawSymmetricPoints((int)x, (int)y);
        x++;
        dx = dx + (2 * ry2);
        if (p1 < 0) {
            p1 = p1 + dx + ry2;
        } else {
            y--;
            dy = dy - (2 * rx2);
            p1 = p1 + dx - dy + ry2;
        }
    }

    // Region 2
    float p2 = ry2 * (x + 0.5f) * (x + 0.5f) + rx2 * (y - 1) * (y - 1) - rx2 * ry2;

    while (y >= 0) {
        drawSymmetricPoints((int)x, (int)y);
        y--;
        dy = dy - (2 * rx2);
        if (p2 > 0) {
            p2 = p2 + rx2 - dy;
        } else {
            x++;
            dx = dx + (2 * ry2);
            p2 = p2 + dx - dy + rx2;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 0.0);  // Yellow for ellipse
    glPointSize(2.0);

    midpointEllipse();

    // Draw X and Y axes
    glColor3f(1.0, 1.0, 1.0);  // White color for axes
    glBegin(GL_LINES);
    // X-axis
    glVertex2i(-500, 0);
    glVertex2i(500, 0);

    // Y-axis
    glVertex2i(0, -500);
    glVertex2i(0, 500);
    glEnd();

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(-500, 500, -500, 500);
}

int main(int argc, char** argv) {
    printf("Enter rx, ry: ");
    scanf("%d %d", &rx, &ry);
    printf("Enter center (xc, yc): ");
    scanf("%d %d", &xc, &yc);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoint Ellipse Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
