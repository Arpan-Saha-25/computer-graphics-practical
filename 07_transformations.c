/*
Transformations :
scaling rotation translation
*/

#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define M_PI 3.14159265358979323846 /* pi */

typedef float Matrix3x3[3][3];

Matrix3x3 theMatrix;  // original coord.s matrix

typedef struct {
    float x, y;
} wcPt2d;

/* converts a matrix INTO identity mat */
void setIdentityMatrix(Matrix3x3 m) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            m[i][j] = (i == j);
        }
    }
}

/* Multiplies a x b then stores it into b */
void matrix3x3_PreMultiply(Matrix3x3 a, Matrix3x3 b) {
    Matrix3x3 temp;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            temp[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j];
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            b[i][j] = temp[i][j];
        }
    }
}

void translate2d(int tx, int ty) {
    Matrix3x3 m;
    setIdentityMatrix(m);

    m[0][2] = tx;
    m[1][2] = ty;

    matrix3x3_PreMultiply(m, theMatrix);
}

void scale2d(float sx, float sy, wcPt2d refpt) {
    Matrix3x3 m;
    setIdentityMatrix(m);
    m[0][0] = sx;
    m[1][1] = sy;
    m[0][2] = (1 - sx) * refpt.x;
    m[1][2] = (1 - sy) * refpt.y;
    matrix3x3_PreMultiply(m, theMatrix);
}

void rotate2d(float a, wcPt2d refpt) {
    Matrix3x3 m;
    setIdentityMatrix(m);

    a = a * M_PI / 180.00;  // converts to RADIANS
    m[0][0] = cosf(a);
    m[0][1] = -sinf(a);
    m[0][2] = refpt.x * (1 - cosf(a)) + refpt.y * sinf(a);
    m[1][0] = sinf(a);
    m[1][1] = cosf(a);
    m[1][2] = refpt.y * (1 - cosf(a)) - refpt.x * sinf(a);
    matrix3x3_PreMultiply(m, theMatrix);
}

void transformPoint2d(int npts, wcPt2d* pts) {
    int k;
    float temp;
    for (k = 0; k < npts; k++) {
        temp = theMatrix[0][0] * pts[k].x + theMatrix[0][1] * pts[k].y + theMatrix[0][2];
        pts[k].y = theMatrix[1][0] * pts[k].x + theMatrix[1][1] * pts[k].y + theMatrix[1][2];
        pts[k].x = temp;
    }
}

wcPt2d* originalPts_ptr;
wcPt2d* transformedPts_ptr;
wcPt2d* refpt_ptr;

void setData(wcPt2d* o, wcPt2d* t, wcPt2d* r) {
    originalPts_ptr = o;
    transformedPts_ptr = t;
    refpt_ptr = r;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    wcPt2d* originalPts = originalPts_ptr;
    wcPt2d* transformedPts = transformedPts_ptr;
    wcPt2d refpt = *refpt_ptr;

    // Draw original triangle (blue)
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++)
        glVertex2f(originalPts[i].x, originalPts[i].y);
    glEnd();

    // Apply transformations to copy
    for (int i = 0; i < 3; i++)
        transformedPts[i] = originalPts[i];

    setIdentityMatrix(theMatrix);
    // scale2d(0.5, 0.5, refpt);
    // rotate2d(90.0, refpt);
    // translate2d(0, 150);
    transformPoint2d(3, transformedPts);

    // Draw transformed triangle (red)
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++)
        glVertex2f(transformedPts[i].x, transformedPts[i].y);
    glEnd();

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // white background
    glColor3f(0.0, 0.0, 0.0);          // black drawing color
    gluOrtho2D(-400, 400, -400, 400);  // centered coordinate system
}

int main(int argc, char** argv) {
    wcPt2d originalPts[3] = {
        {50.0, 50.0},
        {150.0, 50.0},
        {100.0, 150.0}};

    wcPt2d transformedPts[3];
    wcPt2d refpt = {100.0, 100.0};

    setData(originalPts, transformedPts, &refpt);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("2D Transformation");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

/*
to run :
gcc 07_transformations.c -lGL -lGLU -lglut -lm && ./a.out
*/
