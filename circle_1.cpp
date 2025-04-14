#include<GL/glut.h>
#include<iostream>
using namespace std;

int xc=0,yc=0,r=50;

void plotpoints(int x ,int y)
{
	glBegin(GL_POINTS);
		glVertex2i(xc+x,yc+y);
		glVertex2i(xc-x,yc+y);
		glVertex2i(xc+x,yc-y);
		glVertex2i(xc-x,yc-y);
		glVertex2i(xc+y,yc+x);
		glVertex2i(xc-y,yc+x);
		glVertex2i(xc+y,yc-x);
		glVertex2i(xc-y,yc-x);
		glEnd();
}

void circle()
{
	int x=0,y=r;
	int d=3-2*r;
	while(x<=y)
	{
		plotpoints(x,y);
		if(d<0)
		{
			d+=4*x+6;
		}else
		{
			d+=4*(x-y)+10;
			y--;
		}
		x++;
		
	}
}

void drawAxis()
{
	glColor3f(0,0,1);
	glLineWidth(2.0);
	glBegin(GL_LINES);
		glVertex2i(-100,0);
		glVertex2i(100,0);
		glVertex2i(0,-100);
		glVertex2i(0,100);
	glEnd();
	
	glLineWidth(1.0);
	glBegin(GL_LINES);
	
	for(int i=-100;i<=100;i+=10)
	{
		if(i!=0)
		{
			glVertex2i(i,-2);
			glVertex2i(i,2);
			glVertex2i(-2,i);
			glVertex2i(2,i);
		}
	}
	glEnd();
		
}

void display()

{
	glClear(GL_COLOR_BUFFER_BIT);
	drawAxis();
	glColor3f(1,1,1);
	circle();
	glFlush();
	
}
void init() {
    glClearColor(0, 0, 0, 1); // Black background
    glColor3f(1, 1, 1);
    glPointSize(2);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100); // Coordinate system
}

int main(int argc, char** argv) {
    cout << "Enter center (xc yc): ";
    cin >> xc >> yc;
    cout << "Enter radius: ";
    cin >> r;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Circle with Axes and Ticks");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}


