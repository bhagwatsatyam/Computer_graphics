#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

int x1r, y1r, x2r, y2r;
int clickCount = 0;
bool drawRect = false;

// DDA Line Drawing
void drawDDALine(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = max(abs(dx), abs(dy));
    float xInc = dx / steps;
    float yInc = dy / steps;

    float x = x1, y = y1;
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2i(round(x), round(y));
        x += xInc;
        y += yInc;
    }
    glEnd();
}

// Rectangle using DDA lines
void drawRectangle() {
    drawDDALine(x1r, y1r, x2r, y1r);
    drawDDALine(x2r, y1r, x2r, y2r);
    drawDDALine(x2r, y2r, x1r, y2r);
    drawDDALine(x1r, y2r, x1r, y1r);
}

// Draw axes with ticks
void drawAxes() {
    glColor3f(0, 0, 1);
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2i(-100, 0); glVertex2i(100, 0); // X
        glVertex2i(0, -100); glVertex2i(0, 100); // Y
    glEnd();

    glLineWidth(1.0);
    glBegin(GL_LINES);
    for (int i = -100; i <= 100; i += 10) {
        if (i != 0) {
            glVertex2i(i, -2); glVertex2i(i, 2); // X ticks
            glVertex2i(-2, i); glVertex2i(2, i); // Y ticks
        }
    }
    glEnd();
}

// Mouse click to set rectangle corners
void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int mx = x - 300;      // center X at 0
        int my = 300 - y;      // invert Y axis

        if (clickCount == 0) {
            x1r = mx;
            y1r = my;
            clickCount = 1;
        } else if (clickCount == 1) {
            x2r = mx;
            y2r = my;
            clickCount = 0;
            drawRect = true;
            glutPostRedisplay();
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();

    if (drawRect) {
        glColor3f(1, 1, 1); // White rectangle
        drawRectangle();
    }

    glFlush();
}

void init() {
    glClearColor(0, 0, 0, 1); // Black background
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rectangle via Left Click using DDA");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutMainLoop();
    return 0;
}

