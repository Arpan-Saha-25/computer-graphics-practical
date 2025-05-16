#include <GL/glut.h>
#include <stdio.h>

typedef struct {
    float x, y;
} coord;

int verts;
int tx, ty;
coord points[100];
coord translated[100];

void init() {
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 0, 0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2f(-500, 0);
    glVertex2f(500, 0);
    glVertex2f(0, -400);
    glVertex2f(0, 400);
    glEnd();

    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < verts; i++)
        glVertex2f(points[i].x, points[i].y);
    glEnd();

    glColor3f(0, 1, 0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < verts; i++)
        glVertex2f(translated[i].x, translated[i].y);
    glEnd();

    glFlush();
}

int main(int argc, char **argv) {
    printf("Enter number of vertices: ");
    scanf("%d", &verts);

    printf("Enter translation tx and ty: ");
    scanf("%d %d", &tx, &ty);

    for (int i = 0; i < verts; i++) {
        printf("Enter x y for vertex %d: ", i);
        scanf("%f %f", &points[i].x, &points[i].y);
        translated[i].x = points[i].x + tx;
        translated[i].y = points[i].y + ty;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("2D Translation");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
