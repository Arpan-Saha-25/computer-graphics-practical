#include <GL/glu.h>
#include <GL/glut.h>

void myInit()
{
    glClearColor(0, 0, 0, 1); // BACKGROUND r,g,b,alpha
    glColor3f(1, 0, 0);
}

void DrawRect()
{
    glClear(GL_COLOR_BUFFER_BIT); // clears buffer and set to the color of bg

    glPointSize(5);
    glBegin(GL_POLYGON); // GL_POLYGON for solid rectangle
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(-0.5, -0.5);
    glEnd();

    glPointSize(4);
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_LOOP); // GL_POLYGON for solid rectangle
    glVertex2f(-0.2, 0.2);
    glVertex2f(0.2, 0.2);
    glVertex2f(0.2, -0.2);
    glVertex2f(-0.2, -0.2);
    glEnd();

    glFlush(); // Force OPENGL to finish drawing immediately

    /*
    Imagine OpenGL is a painter: 🎨 Without glFlush() → The painter waits and might not paint until there’s enough work to do.
🎨 With glFlush() → You tell the painter, “Stop waiting, paint it right now!”
    */
}

int main(int argc, char *argv[])
{
    // openGL Utility Toolkit
    glutInit(&argc, argv); // to call glut library

    glutInitWindowPosition(1400, 100); // initial window position

    glutInitWindowSize(500, 400); // size of the window

    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); // Uses RGB to display colors

    glutCreateWindow("My First Program"); // window creation (titleName)

    myInit();

    glutDisplayFunc(DrawRect);

    glutMainLoop(); // continuously calls main() --> refreshes the window

    return 0;
}

/*
! What is glPointSize() in OpenGL?
glPointSize() sets the size of points when using GL_POINTS to draw.
size → A floating-point value specifying the point size in pixels.
Default value is 1.0 (1 pixel).
*/