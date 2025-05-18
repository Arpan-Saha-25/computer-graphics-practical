#include <GL/glut.h>
#include <stdio.h>

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);  // Set display-window color to white.
    glMatrixMode(GL_PROJECTION);       // Set projection parameters.
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void lineSegment() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0.4, 0.2);

    glBegin(GL_LINES);
    glVertex2i(180, 15);
    glVertex2i(10, 145);
    glEnd();

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 300);
    glutCreateWindow("01.c Window");

    init();
    glutDisplayFunc(lineSegment);
    glutMainLoop();

    return 0;
}