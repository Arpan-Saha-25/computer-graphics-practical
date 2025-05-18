/*
Write a program in C to implement x-direction shear of an object in two-dimension.
Output depends upon user’s choice. [Use OpenGL Library]
*/

#include <GL/freeglut.h>
#include <stdio.h>

typedef struct {
    float x, y;
} coord;

int verts;
coord org_points[10];
coord shearedPts[10];

void init() {
    glClearColor(1, 1, 1, 1);  // White bg
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);
}

void shearingX() {
    float sh_x;

    printf("Enter the shear in x-direction : ");
    scanf("%f", &sh_x);

    printf("Enter the number of vertices: ");
    scanf("%d", &verts);

    for (int i = 0; i < verts; i++) {
        printf("Enter vertex %d (x y): ", i + 1);
        scanf("%f %f", &org_points[i].x, &org_points[i].y);
    }

    for (int i = 0; i < verts; i++) {
        shearedPts[i].x = org_points[i].x + sh_x * org_points[i].y;
        shearedPts[i].y = org_points[i].y;
    }
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

    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < verts; i++) {
        glVertex2f(org_points[i].x, org_points[i].y);
    }
    glEnd();

    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < verts; i++) {
        glVertex2f(shearedPts[i].x, shearedPts[i].y);
    }
    glEnd();

    glFlush();
}

int main(int args, char **ch) {
    shearingX();

    glutInit(&args, ch);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(500, 300);
    glutCreateWindow("Shearing in x-dir");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}