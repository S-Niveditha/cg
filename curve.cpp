#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<cmath>
#include<vector>
#include <stdlib.h>
using namespace std;
struct Point
{
    int x;
    int y;
}pointArr[1000];
int i=0;
int cnt=0;
int ind=0;


void init()
{
    //for setting transformation matrices
    glClearColor(0,0,0,0);
    gluOrtho2D(0,640,0,480);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT );
    glColor3d(1,0,0);


    glutSwapBuffers();
}


void curve()
{
    vector<float> X;
    vector<float> Y;
    float t=0.1;
    float x,y;
    while(t<1)
    {
        glColor3d(1,1,1);
        x = pow((1-t),3)*pointArr[ind].x + 3*t*pow((1-t),2)*pointArr[ind+1].x + 3*(1-t)*pow(t,2)*pointArr[ind+2].x + pow(t,3)*pointArr[ind+3].x;
        y = pow((1-t),3)*pointArr[ind].y + 3*t*pow((1-t),2)*pointArr[ind+1].y + 3*(1-t)*pow(t,2)*pointArr[ind+2].y + pow(t,3)*pointArr[ind+3].y;
        /*glBegin(GL_LINE_STRIP);
            glVertex2d(x,y);
        glEnd();
        glFlush();*/
        X.push_back(x);
        Y.push_back(y);
        t=t+0.1;
    }


    for(int j=0; j<X.size()-1; j++)
    {
        glBegin(GL_LINE_STRIP);
            glVertex2d(X[j],Y[j]);
            glVertex2d(X[j+1],Y[j+1]);
        glEnd();
        glFlush();
    }
}


void mouse(int button, int state, int x, int y)
{
    int window_height = glutGet(GLUT_WINDOW_HEIGHT);
    if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON && cnt<4)
    {
        cnt+=1;
        glColor3f (1,1,1);
        //glPointSize(5);
        pointArr[i].x = x;
        pointArr[i].y = window_height - y;
        ++i;
        glBegin(GL_POINTS);
            glVertex2f(x, window_height - y);
        glEnd();
        glFlush();
    }


    if(cnt==4)
    {
        cnt=0;
        curve();
        ind+=4;
    }
}




int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);


    glutCreateWindow("GLUT Shapes");


    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);


    glutMainLoop();


    return EXIT_SUCCESS;
}
