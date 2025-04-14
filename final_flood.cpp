#include <GL/glut.h> 
#include <cstdlib>
#include <iostream>

using namespace std;

void my_init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // white background
    glMatrixMode(GL_PROJECTION); 
    gluOrtho2D(0, 800, 0, 800); // set coordinate system
}

void my_display() {
    glLineWidth(3);
    glPointSize(2);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINE_LOOP);
        glColor3f(1, 0, 0);
        glVertex2i(400, 600);
        glColor3f(0, 1, 0);
        glVertex2i(600, 200);
        glColor3f(0, 0, 1);
        glVertex2i(200, 200);
    glEnd(); 

    glFlush();
}

void flood_fill(int x, int y, float* oldColor, float* newColor)
{
    float current[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, current);

    if (current[0] == oldColor[0] && current[1] == oldColor[1] && current[2] == oldColor[2]) {
        glColor3f(newColor[0], newColor[1], newColor[2]);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd(); 
        glFlush();

        // Recursive fill in 4 directions
        flood_fill(x + 2, y, oldColor, newColor);
        flood_fill(x - 2, y, oldColor, newColor);
        flood_fill(x, y + 2, oldColor, newColor);
        flood_fill(x, y - 2, oldColor, newColor);
    }
}

void mouse(int btn, int state, int x, int y) {
    y = 800 - y; // flip y-axis for OpenGL coordinates

    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float oldColor[] = {1.0, 1.0, 1.0}; // background color
        float newColor[] = {0.0, 1.0, 0.0}; // fill color

        flood_fill(x, y, oldColor, newColor);
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("Flood Fill");

    cout << "Click inside the triangle to fill the color using Flood Fill" << endl; 

    glutDisplayFunc(my_display);  // ? Fixed
    glutMouseFunc(mouse);         // ? Fixed

    my_init();
    glutMainLoop();

    return 0;
}

