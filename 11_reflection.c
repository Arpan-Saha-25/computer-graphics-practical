/*
Write a program in C to implement two-dimensional reflection with respect to a pivot point. Output depends upon user’s choice. [Use OpenGL Library]
*/

#include <GL/freeglut.h>
#include <stdio.h>

typedef struct {
    float x, y;
} coord;

int verts;
coord org_points[10];
coord reflectedPts[10];

void init() {
    glClearColor(1, 1, 1, 1);  // White bg
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2);

    // Draw axes
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(-500, 0);
    glVertex2f(500, 0);
    glVertex2f(0, -500);
    glVertex2f(0, 500);
    glEnd();

    // Original shape in blue
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < verts; i++) {
        glVertex2f(org_points[i].x, org_points[i].y);
    }
    glEnd();

    // reflected shape in red
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < verts; i++) {
        glVertex2f(reflectedPts[i].x, reflectedPts[i].y);
    }
    glEnd();

    glFlush();
}

void reflect2D() {
    int xp, yp;  // Pivot point

    printf("Enter the pivot point (xp yp): ");
    scanf("%d %d", &xp, &yp);

    printf("Enter the number of vertices: ");
    scanf("%d", &verts);

    if (verts > 10) {
        printf("Too many vertices (max 10 allowed).\n");
        exit(1);
    }

    for (int i = 0; i < verts; i++) {
        printf("Enter vertex %d (x y): ", i + 1);
        scanf("%f %f", &org_points[i].x, &org_points[i].y);
    }

    for (int i = 0; i < verts; i++) {
        reflectedPts[i].x = 2 * xp - org_points[i].x;
        reflectedPts[i].y = 2 * yp - org_points[i].y;
    }
}

int main(int argc, char **argv) {
    reflect2D();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(700, 100);
    glutCreateWindow("2D - Reflection w.r.t Pivot Point");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
