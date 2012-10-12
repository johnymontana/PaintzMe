//
//  proj1.c
//  CSCI 441 Project 2
//  Simple paint program
//
//  William Lyon
//
//
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#endif

#include "stdlib.h"
#include <stdio.h>
#include <string.h>

#define KEY_ESC 27
#define KEY_h 104


GLfloat x1 = 0.0f;
GLfloat y1 = 0.0f;

int figToDraw = 0;

GLfloat windowWidth=600.0;
GLfloat windowHeight=600.0;

int pointCount =0;
int selectedColor = 1;
GLfloat sizes[2]; // Store supported point size range
GLfloat step; // Store supported point size increments

void draw_string(char* str, double x, double y ) // draws text at position (x,y)
{
    int i =0;
    glRasterPos2d(x, y);
    for (i=0; i<strlen(str); i++)
    {

        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str[i]);
    }
}
void RenderScene(void)         //. draw initial canvas, color selection
{
    glClear(GL_COLOR_BUFFER_BIT);
    glGetFloatv(GL_POINT_SIZE_RANGE,sizes);
    glGetFloatv(GL_POINT_SIZE_GRANULARITY,&step);

    glColor3f(0.0f, 0.5f, 0.5f);
    glRectf(-100.0f, -100.0f, -75.0f, -75.0f);

    glColor3f(1.0f, 0.0f, 0.5f);
    glRectf(-100.0f, -75.0f, -75.0f, -50.0f);

    draw_string("Color Picker", -99, -45);
    draw_string("Selected Color:", 35, -95);
    draw_string("Press h key for help", -75, -100);
    /*if (selectedColor==3)
        glColor3f(0.0f, 0.5f, 0.5f);
    if (selectedColor==2)
        glColor3f(0.5f, 0.5f, 0.0f);
    if (selectedColor==1)
        glColor3f(1.0f, 0.0f, 0.0f);
    if (figToDraw ==1)
        glRectf(x1, y1, x1+rsize, y1-rsize);


    */
    glFlush();
}


void SetupRC(void)          // setup scene
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void updateSelectedColor(double r, double g, double b)
{
    // add selected color
}

void ChangeSize(GLsizei w, GLsizei h)       // update scene keeping same aspect ratio (1)
{
    GLfloat aspectRatio;
    if(h==0)
        h=1;
    windowHeight=h;
    windowWidth=w;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspectRatio = (GLfloat)w / (GLfloat)h;
    if(w<=h)
        glOrtho(-100.0, 100.0, -100.0 / aspectRatio, 100.0 / aspectRatio, 1.0, -1.0);
    else
        glOrtho(-100.0*aspectRatio, 100.0*aspectRatio, -100.0, 100.0, 1.0, -1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}
void myMouse(int button, int state, int x, int y) // handle mouse click events
{

    if(button == GLUT_LEFT_BUTTON  && state == GLUT_DOWN)
    {


        glPointSize(sizes[0]+(10*step));
        int tempx=0;
        int tempy=0;

        tempx = (float) ((x/(windowWidth/2))-1.0)*100;
        tempy= (float) ((windowHeight-y)/(windowHeight/2)-1.0)*100;

        if (figToDraw==1)
        {// draw points
            glPointSize(sizes[0]+(10*step));
            glBegin(GL_POINTS);
        }
        else if (figToDraw==2 && pointCount==0)     // draw solid line
        {
            glDisable(GL_LINE_STIPPLE);
            glBegin(GL_LINES);

        }
        else if (figToDraw==3 && pointCount==0)     // draw triangles
            glBegin(GL_TRIANGLES);
        else if (figToDraw==4 && pointCount==0)     // draw quads
            glBegin(GL_QUADS);
        else if (figToDraw==5 && pointCount==0)     // figToDraw=5 -> draw dotted lines
        {

            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0x8888);
            glBegin(GL_LINES);


        }

        else if (figToDraw==6 && pointCount==0)     // figToDraw=6 -> draw dashed lines
        {

            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0xF0F0);
            glBegin(GL_LINES);


        }

        else if (figToDraw==7)
        {
            glPointSize(sizes[1]);
            glColor3f(0.0f, 0.0f, 1.0f);
            glBegin(GL_POINTS);
        }
        if (tempx< -74 && tempx>-101 && tempy < -74 && tempy>-101)
        {
            selectedColor = 3;
            glEnd();
            glColor3f(0.0f, 0.5f, 0.5f);
            glRectf(75.0, -100.0f, 100.0f, -75.0f);
            glFlush();
        }
        else if (tempx<-74 && tempx>-101 && tempy<-49 && tempy>-76)
        {
            glEnd();
            glColor3f(1.0f, 0.0f, 0.5f);
            glRectf(75.0, -100.0f, 100.0f, -75.0f);
            glFlush();
        }
        else
        {
            x1=tempx;
            y1=tempy;
            glVertex3f(x1, y1,0);
            pointCount++;
        }


        if (figToDraw==1)
        {
            glEnd();
            glFlush();
        }
        else if (figToDraw==2 && pointCount>0 && pointCount%2==0)
        {
            glEnd();
            glFlush();
            pointCount=0;
        }

        else if (figToDraw==3 && pointCount>0 && pointCount%3==0)
        {
            glEnd();
            glFlush();
            pointCount=0;
        }
        else if (figToDraw==4 && pointCount>0 && pointCount%4==0)
        {
            glEnd();
            glFlush();
            pointCount=0;
        }

        else if (figToDraw==5 && pointCount>0 && pointCount%2==0)
        {
            glEnd();
            glFlush();
            pointCount=0;
         //   glDisable(GL_LINE_STIPPLE);
        }
        else if (figToDraw==6 && pointCount>0 && pointCount%2==0)
        {
            glEnd();
            glFlush();
            pointCount=0;
        }
        else if (figToDraw==7)
        {
            glEnd();
            glFlush();
        }

       // glEnd();

        printf("X: %i ", x);
        printf("Y: %i \n", y);
        printf("X1: %f ", x1);
        printf("Y1: %f \n", y1);

    }
}

void select_fig(int id)         // select figure to draw menu
{
    switch(id) {
        case 1:
            // draw points
            figToDraw=1;
            pointCount=0;
            break;
        case 3:
            // draw triangles
            figToDraw = 3;
            pointCount=0;
            break;
        case 4:
            // draw quads
            figToDraw = 4;
            pointCount=0;
            break;
        case 5:
            // clear
            pointCount=0;
            figToDraw=1;
            RenderScene();
            break;
        case 6:
            figToDraw=7;
            pointCount=0;

    }
    //glutPostRedisplay();
}

void line_menu(int id)          // sub menu
{
    switch (id) {
        case 2:
            figToDraw=2;
            pointCount=0;
            // draw solid line
            break;

        case 3:
            figToDraw=5;
            pointCount=0;
            // draw dotted line

        case 4:
            figToDraw=6;
            pointCount=0;
            // draw dashed line
        default:
            break;
    }


}
void show_help()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    draw_string("Right click for menu. Select figure to draw. Click points to define figure. ", -100.0f, 96.0f);
    draw_string("Try using eraser to clear help text!", -100.0f, 90.0f);
    glFlush();
}

static void keyboard(unsigned char key, int x, int y)   /// handle keyboard input
{
	switch(key) {
        case KEY_ESC:
            exit(0);

        case KEY_h:
            show_help();
            break;



        default:
            break;
	}
}
void top_menu(int id)
{

}

int main(int argc, const char * argv[])
{

    int line_sub;



    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Paint Me!");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutMouseFunc(myMouse);

    line_sub = glutCreateMenu(line_menu);
    glutAddMenuEntry("draw solid lines", 2);
    glutAddMenuEntry("draw dotted line", 3);
    glutAddMenuEntry("draw dashed line", 4);

    glutCreateMenu(select_fig);
    glutAddMenuEntry("draw points", 1);
    glutAddSubMenu("draw lines", line_sub);

    glutAddMenuEntry("draw triangle", 3);
    glutAddMenuEntry("draw quadrilateral", 4);
    glutAddMenuEntry("clear canvas", 5);
    glutAddMenuEntry("eraser", 6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutKeyboardFunc(keyboard);

    SetupRC();

    glutMainLoop();


    return 0;
}

