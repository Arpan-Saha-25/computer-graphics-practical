#include <stdio.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

int x1, y_1, x2, y2;

void BLA(int x1, int y_1, int x2, int y2)
{
    int del_x = abs(x2 - x1);
    int del_y = abs(y2 - y_1);
    int sx = (x2 > x1) ? 1 : -1; // 1 to increase | -1 to decrease
    int sy = (y2 > y_1) ? 1 : -1;

    glBegin(GL_POINTS);

    // Check if the line is steep
    if (del_y > del_x)
    {
        int p = 2 * del_x - del_y;
        int newX = x1, newY = y_1;

        while (newY != y2 + sy)
        {
            glVertex2i(newX, newY);
            printf("Plotting: (%d, %d)\n", newX, newY);

            newY += sy;
            if (p < 0)
                p += 2 * del_x;
            else
            {
                newX += sx;
                p += 2 * del_x - 2 * del_y;
            }
        }
    }
    else
    {
        int p = 2 * del_y - del_x;
        int newX = x1, newY = y_1;

        while (newX != x2 + sx) // Fixes infinite loop issue
        {
            glVertex2i(newX, newY);
            printf("Plotting: (%d, %d)\n", newX, newY);

            newX += sx;
            if (p < 0)
                p += 2 * del_y;
            else
            {
                newY += sy;
                p += 2 * del_y - 2 * del_x;
            }
        }
    }

    glEnd();
    glFlush();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    BLA(x1, y_1, x2, y2);
}

void init()
{
    glClearColor(0, 0, 0, 1);
    glColor3f(1, 1, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 200, 0, 200);

    glPointSize(5);
}

int main(int c, char **v)
{
    printf("Enter two points...");
    printf("\nPoint 1 (x1 y1): ");
    scanf("%d %d", &x1, &y_1);
    printf("Point 2 (x2 y2): ");
    scanf("%d %d", &x2, &y2);

    glutInit(&c, v);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(600, 100);
    glutCreateWindow("Bresenham Line Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

// Try these :
/*
50 100 150 100  // Test Case 1: Horizontal Line (Left to Right)
150 100 50 100  // Test Case 2: Horizontal Line (Right to Left)
100 50 100 150  // Test Case 3: Vertical Line (Bottom to Top)
100 150 100 50  // Test Case 4: Vertical Line (Top to Bottom)
50 50 150 150   // Test Case 5: Positive Slope (m = 1, 45° line)
50 50 70 100    // Test Case 6: Positive Slope (m > 1, Steep line)
150 50 50 150   // Test Case 7: Negative Slope (m = -1, 135° line)
70 100 50 50    // Test Case 8: Negative Slope (m < -1, Steep line)
100 100 100 100 // Test Case 9: Single Point (Same Start & End)
*/