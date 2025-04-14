#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

// Rectangle corner points
int x1r, y1r, x2r, y2r; // Top-left (x1r, y1r), Bottom-right (x2r, y2r)

// DDA Line Drawing Function
void drawDDALine(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = max(abs(dx), abs(dy));

    float xInc = dx / steps;
    float yInc = dy / steps;

    float x = x1;
    float y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2i(round(x), round(y));
        x += xInc;
        y += yInc;
    }
    glEnd();
}

// Draw Rectangle using 4 DDA lines
void drawRectangleWithDDA() {
    drawDDALine(x1r, y1r, x2r, y1r); // Top edge
    drawDDALine(x2r, y1r, x2r, y2r); // Right edge
    drawDDALine(x2r, y2r, x1r, y2r); // Bottom edge
    drawDDALine(x1r, y2r, x1r, y1r); // Left edge
}

// Draw X and Y axes with tick marks
void drawAxesWithTicks() {
    glColor3f(0, 0, 1); // Blue color
    glLineWidth(2.0);
    
    glBegin(GL_LINES);
        glVertex2i(-100, 0); glVertex2i(100, 0); // X-axis
        glVertex2i(0, -100); glVertex2i(0, 100); // Y-axis
    glEnd();

    glLineWidth(1.0);
    glBegin(GL_LINES);
    for (int i = -100; i <= 100; i += 10) {
        if (i != 0) {
            glVertex2i(i, -2); glVertex2i(i, 2); // X-axis ticks
            glVertex2i(-2, i); glVertex2i(2, i); // Y-axis ticks
        }
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxesWithTicks();

    glColor3f(1, 1, 1); // White rectangle
    drawRectangleWithDDA();

    glFlush();
}

void init() {
    glClearColor(0, 0, 0, 1); // Black background
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100); // 2D Coordinate system
}

int main(int argc, char** argv) {
    cout << "Enter top-left corner (x1 y1): ";
    cin >> x1r >> y1r;
    cout << "Enter bottom-right corner (x2 y2): ";
    cin >> x2r >> y2r;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rectangle with DDA and Axes");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

