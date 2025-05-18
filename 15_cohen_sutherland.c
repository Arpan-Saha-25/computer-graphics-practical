// cohen sutherland algorithm

#include <GL/freeglut.h>
#include <stdio.h>

// Region codes
#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

float xmin, ymin, xmax, ymax;  // Clipping window
float x1, y1, x2, y2;          // Line endpoints

int computeCode(float x, float y) {
    int code = INSIDE;

    if (x < xmin)
        code = code | LEFT;  // logical OR
    if (x > xmax)
        code = code | RIGHT;
    if (y < ymin)
        code = code | BOTTOM;
    if (y > ymax)
        code = code | TOP;

    return code;
}

void cohenSutherlandClip() {
    // Duplicate vars
    float x1c = x1, y1c = y1, x2c = x2, y2c = y2;

    int code1 = computeCode(x1c, y1c);
    int code2 = computeCode(x2c, y2c);
    int accept = 0;

    // runs until max clipped is reached.
    while (1) {
        if (code1 == 0 && code2 == 0) {
            accept = 1;
            break;
        } else if ((code1 & code2) != 0) {
            break;
        } else {
            int code_out;
            float x = 0.0, y = 0.0;  // intersection with edges

            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            if (code_out & TOP) {
                x = x1c + (x2c - x1c) * (ymax - y1c) / (y2c - y1c);
                y = ymax;
            } else if (code_out & BOTTOM) {
                x = x1c + (x2c - x1c) * (ymin - y1c) / (y2c - y1c);
                y = ymin;
            } else if (code_out & RIGHT) {
                y = y1c + (y2c - y1c) * (xmax - x1c) / (x2c - x1c);
                x = xmax;
            } else if (code_out & LEFT) {
                y = y1c + (y2c - y1c) * (xmin - x1c) / (x2c - x1c);
                x = xmin;
            }

            if (code_out == code1) {
                x1c = x;
                y1c = y;
                code1 = computeCode(x1c, y1c);
            } else {
                x2c = x;
                y2c = y;
                code2 = computeCode(x2c, y2c);
            }
        }
    }

    if (accept == 1) {
        glColor3f(0.0, 1.0, 0.0);  // Green clipped line
        glBegin(GL_LINES);
        glVertex2f(x1c, y1c);
        glVertex2f(x2c, y2c);
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw axes
    glColor3f(1, 0, 1);
    glBegin(GL_LINES);
    glVertex2f(-500, 0);
    glVertex2f(500, 0);
    glVertex2f(0, -500);
    glVertex2f(0, 500);
    glEnd();

    // Draw clipping window in red
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    // Draw original line in blue
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();

    // Draw clipped line
    cohenSutherlandClip();

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // White bg
    gluOrtho2D(-500, 500, -500, 500);  // Coordinate system
}

int main(int argc, char** argv) {
    printf("Enter clipping window (xmin ymin xmax ymax): ");
    scanf("%f %f %f %f", &xmin, &ymin, &xmax, &ymax);

    printf("Enter line (x1 y1 x2 y2): ");
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cohen-Sutherland Line Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
