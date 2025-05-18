#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>

typedef struct {
    float x, y;
} Point;

typedef struct {
    Point p0, p1;
} Line;

#define N 4  // Number of polygon vertices (convex polygon)

Point polygon[N] = {
    {100, 100}, {400, 100}, {400, 400}, {100, 400}};

Line inputLine = {{50, 250}, {450, 300}};
Line clippedLine;

Point subtract(Point a, Point b) {
    Point r = {a.x - b.x, a.y - b.y};
    return r;
}

float dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

Point normal(Point a, Point b) {
    Point edge = subtract(b, a);
    Point n = {edge.y, -edge.x};  // outward normal
    return n;
}

void cyrusBeck(Line line) {
    Point d = subtract(line.p1, line.p0);
    float tE = 0.0, tL = 1.0;

    for (int i = 0; i < N; i++) {
        Point pi = polygon[i];
        Point pi1 = polygon[(i + 1) % N];

        Point n = normal(pi, pi1);  // outward normal
        Point w = subtract(line.p0, pi);
        float DdotN = dot(d, n);
        float WdotN = dot(w, n);

        if (DdotN == 0) {
            if (WdotN < 0) {
                clippedLine.p0 = clippedLine.p1 = (Point){-1, -1};  // outside
                return;
            }
            continue;
        }

        float t = -WdotN / DdotN;
        if (DdotN < 0) {
            if (t > tE) tE = t;
        } else {
            if (t < tL) tL = t;
        }

        if (tE > tL) {
            clippedLine.p0 = clippedLine.p1 = (Point){-1, -1};  // no visible part
            return;
        }
    }

    clippedLine.p0.x = line.p0.x + tE * d.x;
    clippedLine.p0.y = line.p0.y + tE * d.y;
    clippedLine.p1.x = line.p0.x + tL * d.x;
    clippedLine.p1.y = line.p0.y + tL * d.y;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw polygon
    glColor3f(0, 0, 1);  // Blue
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < N; i++)
        glVertex2f(polygon[i].x, polygon[i].y);
    glEnd();

    // Draw input line
    glColor3f(1, 0, 0);  // Red
    glBegin(GL_LINES);
    glVertex2f(inputLine.p0.x, inputLine.p0.y);
    glVertex2f(inputLine.p1.x, inputLine.p1.y);
    glEnd();

    // Draw clipped line
    if (clippedLine.p0.x != -1 && clippedLine.p1.x != -1) {
        glColor3f(0, 1, 0);  // Green
        glBegin(GL_LINES);
        glVertex2f(clippedLine.p0.x, clippedLine.p0.y);
        glVertex2f(clippedLine.p1.x, clippedLine.p1.y);
        glEnd();
    }

    glFlush();
}

void init() {
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 500, 0, 500);
    cyrusBeck(inputLine);
}

int main(int argc, char **argv) {
    printf("Enter line start (x y): ");
    scanf("%f %f", &inputLine.p0.x, &inputLine.p0.y);

    printf("Enter line end (x y): ");
    scanf("%f %f", &inputLine.p1.x, &inputLine.p1.y);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Cyrus-Beck Line Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
