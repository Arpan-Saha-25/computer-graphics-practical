#include <GL/freeglut.h>
#include <stdio.h>

int x1, y1;
int x2, y2;
int xL, xR, yT, yB;

void generateCode(int x, int y, int xL, int xR, int yT, int yB, int code[4]) {
    code[0] = (y > yT) ? 1 : 0;  // Top
    code[1] = (y < yB) ? 1 : 0;  // Bottom
    code[2] = (x > xR) ? 1 : 0;  // Right
    code[3] = (x < xL) ? 1 : 0;  // Left
}

void printCode(int code[4]) {
    for (int i = 0; i < 4; i++)
        printf("%d", code[i]);
    printf("\n");
}

void init() {
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);
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

    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xL, yB);
    glVertex2i(xL, yT);
    glVertex2i(xR, yT);
    glVertex2i(xR, yB);
    glEnd();

    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();

    glFlush();
}

int main(int argc, char **argv) {
    // int x1, y1, x2, y2;
    // int xL, xR, yT, yB;

    int code1[4], code2[4];

    printf("Enter window boundaries in order: xL (left), xR (right), yT (top), yB (bottom): ");
    scanf("%d %d %d %d", &xL, &xR, &yT, &yB);

    if (xL > xR || yB > yT) {
        printf("Invalid window boundaries! Make sure xL < xR and yB < yT.\n");
        return 1;
    }

    printf("Enter first endpoint (x1 y1): ");
    scanf("%d %d", &x1, &y1);
    printf("Enter second endpoint (x2 y2): ");
    scanf("%d %d", &x2, &y2);

    generateCode(x1, y1, xL, xR, yT, yB, code1);
    generateCode(x2, y2, xL, xR, yT, yB, code2);

    printf("Region code for P1 (%d, %d): ", x1, y1);
    printCode(code1);
    printf("Region code for P2 (%d, %d): ", x2, y2);
    printCode(code2);

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
