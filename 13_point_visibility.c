// Write a program in C to implement point visibility algorithm.

#include <GL/freeglut.h>
#include <stdio.h>

typedef struct {
    float x, y;
} Point;

Point a, b;  // Line endpoints

// Window bounds
float xL = -200, xR = 200, yB = -200, yT = 200;

enum Visibility { INVISIBLE,
                  PARTIAL,
                  VISIBLE };

void init() {
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);
}

void drawClippingWindow() {
    glColor3f(1, 0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xL, yB);
    glVertex2f(xR, yB);
    glVertex2f(xR, yT);
    glVertex2f(xL, yT);
    glEnd();
}

int checkVisibility() {
    // Totally invisible
    if ((a.x < xL && b.x < xL) || (a.x > xR && b.x > xR) ||
        (a.y < yB && b.y < yB) || (a.y > yT && b.y > yT))
        return INVISIBLE;

    // Totally visible
    if ((a.x >= xL && a.x <= xR && b.x >= xL && b.x <= xR) &&
        (a.y >= yB && a.y <= yT && b.y >= yB && b.y <= yT))
        return VISIBLE;

    // Partially visible
    return PARTIAL;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(10);

    // Draw axes
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(-500, 0);
    glVertex2f(500, 0);
    glVertex2f(0, -500);
    glVertex2f(0, 500);
    glEnd();

    drawClippingWindow();

    int vis = checkVisibility();
    if (vis == INVISIBLE)
        glColor3f(1, 0, 0);  // Red
    else if (vis == VISIBLE)
        glColor3f(0, 1, 0);  // Green
    else
        glColor3f(0, 0, 1);  // blue

    printf("Drawing line from (%.2f, %.2f) to (%.2f, %.2f)\n", a.x, a.y, b.x, b.y);

    glBegin(GL_LINES);
    glVertex2f(a.x, a.y);
    glVertex2f(b.x, b.y);
    glEnd();

    glFlush();
}

int main(int argc, char **argv) {
    printf("Enter point A (x y): ");
    scanf("%f %f", &a.x, &a.y);
    printf("Enter point B (x y): ");
    scanf("%f %f", &b.x, &b.y);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(500, 200);
    glutCreateWindow("Point Visibility Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}