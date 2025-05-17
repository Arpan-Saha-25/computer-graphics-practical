/*
WAP TO IMPLEMENT 2D SCALING WITH RESPECT TO A PIVOT POINT.
*/

#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>

typedef struct {
    float x, y;
} coord;

int verts;
float Sx, Sy;
coord org_points[10];
coord scaledPts[10];

void init() {
    glClearColor(1, 1, 1, 1);
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

    // original points
    glColor3f(0, 0, 1);  // blue
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < verts; i++) {
        glVertex2f(org_points[i].x, org_points[i].y);
    }
    glEnd();

    // Draw scaled shape
    glColor3f(1, 0, 0);  // red
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < verts; i++) {
        glVertex2f(scaledPts[i].x, scaledPts[i].y);
    }
    glEnd();

    glFlush();
}

void scaling2D() {
    int xf, yf;  // pivot point
    printf("Enter the pivot point (xf yf): ");
    scanf("%d %d", &xf, &yf);

    printf("Enter the number of vertices: ");
    scanf("%d", &verts);

    if (verts > 10) {
        printf("Too many vertices (max 10 allowed).\n");
        exit(1);
    }

    printf("Enter the scaling factors Sx and Sy: ");
    scanf("%f %f", &Sx, &Sy);

    for (int i = 0; i < verts; i++) {
        printf("Enter vertex %d (x y): ", i + 1);
        scanf("%f %f", &org_points[i].x, &org_points[i].y);
    }

    for (int i = 0; i < verts; i++) {
        scaledPts[i].x = (org_points[i].x * Sx) + xf * (1 - Sx);
        scaledPts[i].y = (org_points[i].y * Sy) + yf * (1 - Sy);
    }
}

int main(int argc, char **argv) {
    scaling2D();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(700, 150);
    glutCreateWindow("2D - Scaling w.r.t Pivot");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
