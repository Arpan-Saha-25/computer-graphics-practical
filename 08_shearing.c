#include <GL/freeglut.h>
#include <stdio.h>

// Original rectangle points as arrays
float original_points[4][2] = {{0, 0}, {0, 1}, {1, 1}, {1, 0}};
// Reference point
float p = -1, q = -1;
// Shear factors
float shx = 3.0, shy = 3.0;
// Transformed rectangle points
float transformed_points[4][2];

// Function to shear a single point
void shear_point(float x, float y, float* x_new, float* y_new) {
    *x_new = x + shx * (y - q);
    *y_new = y + shy * (x - p);
}

// Function to transform all rectangle points
void transform_rectangle() {
    for (int i = 0; i < 4; i++) {
        shear_point(original_points[i][0], original_points[i][1], &transformed_points[i][0], &transformed_points[i][1]);
    }
}

void drawAxes() {
    glColor3f(0.0, 0.0, 0.0);  // Black color
    glLineWidth(2.5);

    glBegin(GL_LINES);
    // X-axis
    glVertex2f(-5, 0);
    glVertex2f(5, 0);
    // Y-axis
    glVertex2f(0, -5);
    glVertex2f(0, 5);
    glEnd();

    // Label X-axis
    glRasterPos2f(4.5, 0.2);
    const unsigned char* xLabel = (const unsigned char*)"X";
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, xLabel);

    // Label Y-axis
    glRasterPos2f(0.2, 4.5);
    const unsigned char* yLabel = (const unsigned char*)"Y";
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, yLabel);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();

    // Draw original rectangle in red
    glColor3f(1, 0, 0);
    glLineWidth(2.5);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++) {
        glVertex2f(original_points[i][0], original_points[i][1]);
    }
    glEnd();

    // Draw transformed (sheared) rectangle in green
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++) {
        glVertex2f(transformed_points[i][0], transformed_points[i][1]);
    }
    glEnd();

    // Label points
    glRasterPos2f(original_points[0][0], original_points[0][1] + 0.3);
    const unsigned char* label1 = (const unsigned char*)"Original";
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, label1);

    glRasterPos2f(transformed_points[0][0], transformed_points[0][1] + 0.3);
    const unsigned char* label2 = (const unsigned char*)"Sheared";
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, label2);

    glFlush();
}

void init() {
    glClearColor(1, 1, 1, 1);  // White background
    gluOrtho2D(-5, 5, -5, 5);  // Adjusted view range for better fit
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

int main(int argc, char** argv) {
    printf("Enter the coordinates of rectangle (x1 y1 x2 y2 x3 y3 x4 y4): ");
    for (int i = 0; i < 4; i++) {
        scanf("%f %f", &original_points[i][0], &original_points[i][1]);
    }
    printf("Enter reference point (p q): ");
    scanf("%f %f", &p, &q);
    printf("Enter shear factors (shx shy): ");
    scanf("%f %f", &shx, &shy);

    transform_rectangle();

    // Initialize GLUT and create the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);  // Window size
    glutCreateWindow("2D Shearing with Respect to a Point");
    init();

    // Register the display function
    glutDisplayFunc(display);

    // Start the main GLUT loop
    glutMainLoop();

    return 0;
}
