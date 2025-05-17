// Write a program in C to implement two-dimensional rotation with respect to a pivot point.

#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>

#define M_PI 3.14159265358979323846

typedef struct {
    float x, y;
} coord;

int verts;
coord origPts[100];    // original coordinates
coord rotatePts[100];  // rotated coordinates

void init() {
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 1);
    glLineWidth(5.0);

    glBegin(GL_LINES);
    glVertex2f(-800, 0);
    glVertex2f(800, 0);
    glVertex2f(0, -800);
    glVertex2f(0, 800);
    glEnd();

    // glColor3f(0, 0, 0);  // black dot
    // glPointSize(5.0);
    // glBegin(GL_POINTS);
    // glVertex2f(pivotPt.x, pivotPt.y);
    // glEnd();

    glColor3f(0, 0.5, 0);  // green for original polygon
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < verts; i++) {
        glVertex2f(origPts[i].x, origPts[i].y);
    }
    glEnd();

    glColor3f(1, 0, 0);  // red for rotated polygon
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < verts; i++) {
        glVertex2f(rotatePts[i].x, rotatePts[i].y);
    }
    glEnd();

    glFlush();
}

void rotation2D() {
    int theta;
    coord pivotPt;

    printf("Enter the number of vertices: ");
    scanf("%d", &verts);

    printf("Enter the pivot point (x y): ");
    scanf("%f %f", &pivotPt.x, &pivotPt.y);

    printf("Enter the angle of rotation in degrees: ");
    scanf("%d", &theta);

    for (int i = 0; i < verts; i++) {
        printf("Enter vertex %d (x y): ", i + 1);
        scanf("%f %f", &origPts[i].x, &origPts[i].y);
    }

    float rad = theta * M_PI / 180.0;

    for (int i = 0; i < verts; i++) {
        rotatePts[i].x = (origPts[i].x - pivotPt.x) * cos(rad) - (origPts[i].y - pivotPt.y) * sin(rad) + pivotPt.x;
        rotatePts[i].y = (origPts[i].x - pivotPt.x) * sin(rad) + (origPts[i].y - pivotPt.y) * cos(rad) + pivotPt.y;
    }
}

int main(int argc, char *argv[]) {
    rotation2D();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(700, 150);
    glutCreateWindow("2D Rotation about Pivot");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
