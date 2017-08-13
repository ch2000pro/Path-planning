/*----------------------------------------------------------------------*/
/*  graphics.h                                                          */
/*  Draws the map and the path using openGL                             */
/*  adapted code from https://www.opengl.org/discussion_boards/showthread.php/169966-How-to-control-cube-rotation-using-Keyboard-keys                                        */
/*  Fernanda Isabel, Gianluca Cagliari, Laura Vieira, Leonardo Castilho */
/*  Start: July 5, 2016                                                 */
/*----------------------------------------------------------------------*/

#include <stdlib.h>
#include <iostream>
#include <fstream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include "math.h"

#define  RADDEG  57.29577951f

float XUP[3] = {1,0,0}, XUN[3] = {-1, 0, 0},
YUP[3] = {0,1,0}, YUN[3] = { 0,-1, 0},
ZUP[3] = {0,0,1}, ZUN[3] = { 0, 0,-1},
ORG[3] = {0,0,0};

GLfloat viewangle = 0, tippangle = 0, traj[120][3];

GLfloat d[3] = {0.1, 0.1, 0.1};

GLfloat  xAngle = 0.0, yAngle = 0.0, zAngle = 0.0;


//  Use arrow keys to rotate entire scene !!!
void Special_Keys (int key, int x, int y)
{
    switch (key) {
            
        case GLUT_KEY_LEFT :  viewangle -= 5;  break;
        case GLUT_KEY_RIGHT:  viewangle += 5;  break;
        case GLUT_KEY_UP   :  tippangle -= 5;  break;
        case GLUT_KEY_DOWN :  tippangle += 5;  break;
            
        default: printf ("   Special key %c == %d\n", key, key);
    }
    
    glutPostRedisplay();
}

void Keyboard (unsigned char key, int x, int y)
{
    switch (key) {
            
        case 'j' : d[0] += 0.1;  break;
        case 'k' : d[1] += 0.1;  break;
        case 'l' : d[2] += 0.1;  break;
        case 'u' : d[0] -= 0.1;  break;
        case 'i' : d[1] -= 0.1;  break;
        case 'o' : d[2] -= 0.1;  break;
            
        case 'x' : zAngle -= 5;  break;
        //case 'y' : yAngle += 5;  break;
        case 'z' : zAngle += 5;  break;
            
        default: printf ("   Keyboard %c == %d\n", key, key);
    }
    
    glutPostRedisplay();
}

//draws the obstacles' faces, edges and the path (the latter one from a txt with the coordinates)
void Draw_Box (void)
{
    
    
    
    
    ifstream myfile("output/path.txt");
    int m;
    myfile >> m;
    if (m == 5) {
        glBegin(GL_QUADS);
        glColor3f  ( 0.9, 0.9,  0.9);
        
        //first obstacle
        glVertex3f (20,110,0);
        glVertex3f (110,110,0);
        glVertex3f (110,20,0);
        glVertex3f (20,20,0);
        
        glVertex3f (20,110,200);
        glVertex3f (110,110,200);
        glVertex3f (110,20,200);
        glVertex3f (20,20,200);
        
        glVertex3f (20,110,0);
        glVertex3f (110,110,0);
        glVertex3f (110,110,200);
        glVertex3f (20,110,200);
        
        glVertex3f (110,110,0);
        glVertex3f (110,20,0);
        glVertex3f (110,20,200);
        glVertex3f (110,110,200);
        
        glVertex3f (110,20,0);
        glVertex3f (20,20,0);
        glVertex3f (20,20,200);
        glVertex3f (110,20,200);
        
        glVertex3f (20,20,0);
        glVertex3f (20,110,0);
        glVertex3f (20,110,200);
        glVertex3f (20,20,200);
        
        glVertex3f (20,80,200);
        glVertex3f (50,80,200);
        glVertex3f (50,80,270);
        glVertex3f (20,80,270);
        
        glVertex3f (50,80,200);
        glVertex3f (50,110,200);
        glVertex3f (50,110,270);
        glVertex3f (50,80,270);
        
        glVertex3f (50,110,200);
        glVertex3f (110,110,200);
        glVertex3f (110,110,270);
        glVertex3f (50,110,270);
        
        glVertex3f (110,110,200);
        glVertex3f (110,50,200);
        glVertex3f (110,50,270);
        glVertex3f (110,110,270);
        
        glVertex3f (110,50,200);
        glVertex3f (80,50,200);
        glVertex3f (80,50,270);
        glVertex3f (110,50,270);
        
        glVertex3f (80,50,200);
        glVertex3f (80,20,200);
        glVertex3f (80,20,270);
        glVertex3f (80,50,270);
        
        glVertex3f (80,20,200);
        glVertex3f (20,20,200);
        glVertex3f (20,20,270);
        glVertex3f (80,20,270);
        
        glVertex3f (20,20,200);
        glVertex3f (20,80,200);
        glVertex3f (20,80,270);
        glVertex3f (20,20,270);
        
        glVertex3f (20,80,270);
        glVertex3f (50,80,270);
        glVertex3f (50,80,380);
        glVertex3f (20,80,380);
        
        glVertex3f (50,80,270);
        glVertex3f (50,110,270);
        glVertex3f (50,110,380);
        glVertex3f (50,80,380);
        
        glVertex3f (50,110,270);
        glVertex3f (80,110,270);
        glVertex3f (80,110,380);
        glVertex3f (50,110,380);
        
        glVertex3f (80,110,270);
        glVertex3f (80,80,270);
        glVertex3f (80,80,380);
        glVertex3f (80,110,380);
        
        glVertex3f (80,80,270);
        glVertex3f (110,80,270);
        glVertex3f (110,80,380);
        glVertex3f (80,80,380);
        
        glVertex3f (110,80,270);
        glVertex3f (110,50,270);
        glVertex3f (110,50,380);
        glVertex3f (110,80,380);
        
        glVertex3f (110,50,270);
        glVertex3f (80,50,270);
        glVertex3f (80,50,380);
        glVertex3f (110,50,380);
        
        glVertex3f (80,50,270);
        glVertex3f (80,20,270);
        glVertex3f (80,20,380);
        glVertex3f (80,50,380);
        
        glVertex3f (80,20,270);
        glVertex3f (50,20,270);
        glVertex3f (50,20,380);
        glVertex3f (80,20,380);
        
        glVertex3f (50,20,270);
        glVertex3f (50,50,270);
        glVertex3f (50,50,380);
        glVertex3f (50,20,380);
        
        glVertex3f (50,50,270);
        glVertex3f (20,50,270);
        glVertex3f (20,50,380);
        glVertex3f (50,50,380);
        
        glVertex3f (20,50,270);
        glVertex3f (20,80,270);
        glVertex3f (20,80,380);
        glVertex3f (20,50,380);
        
        glVertex3f (20,80,380);
        glVertex3f (80,80,380);
        glVertex3f (80,50,380);
        glVertex3f (20,50,380);
        
        glVertex3f (20,80,440);
        glVertex3f (80,80,440);
        glVertex3f (80,50,440);
        glVertex3f (20,50,440);
        
        glVertex3f (20,80,380);
        glVertex3f (80,80,380);
        glVertex3f (80,80,440);
        glVertex3f (20,80,440);
        
        glVertex3f (80,80,380);
        glVertex3f (80,50,380);
        glVertex3f (80,50,440);
        glVertex3f (80,80,440);
        
        glVertex3f (80,50,380);
        glVertex3f (20,50,380);
        glVertex3f (20,50,440);
        glVertex3f (80,50,440);
        
        glVertex3f (20,50,380);
        glVertex3f (20,80,380);
        glVertex3f (20,80,440);
        glVertex3f (20,50,440);
        
        //second obstacle
        glVertex3f (200,150,0);
        glVertex3f (300,150,0);
        glVertex3f (250,110,0);
        glVertex3f (200,110,0);
        
        glVertex3f (200,150,70);
        glVertex3f (300,150,70);
        glVertex3f (250,110,70);
        glVertex3f (200,110,70);
        
        glVertex3f (200,150,0);
        glVertex3f (300,150,0);
        glVertex3f (300,150,70);
        glVertex3f (200,150,70);
        
        glVertex3f (300,150,0);
        glVertex3f (250,110,0);
        glVertex3f (250,110,70);
        glVertex3f (300,150,70);
        
        glVertex3f (250,110,0);
        glVertex3f (200,110,0);
        glVertex3f (200,110,70);
        glVertex3f (250,110,70);
        
        glVertex3f (200,110,0);
        glVertex3f (200,150,0);
        glVertex3f (200,150,70);
        glVertex3f (200,110,70);
        
        glVertex3f (245,132,70);
        glVertex3f (261,145,70);
        glVertex3f (277,132,70);
        glVertex3f (261,119,70);
        
        glVertex3f (245,132,130);
        glVertex3f (261,145,130);
        glVertex3f (277,132,130);
        glVertex3f (261,119,130);
        
        glVertex3f (245,132,70);
        glVertex3f (261,145,70);
        glVertex3f (261,145,130);
        glVertex3f (245,132,130);
        
        glVertex3f (261,145,70);
        glVertex3f (277,132,70);
        glVertex3f (277,132,130);
        glVertex3f (261,145,130);
        
        glVertex3f (277,132,70);
        glVertex3f (261,119,70);
        glVertex3f (261,119,130);
        glVertex3f (277,132,130);
        
        glVertex3f (261,119,70);
        glVertex3f (245,132,70);
        glVertex3f (245,132,130);
        glVertex3f (261,119,130);
        
        //third obstacle
        glVertex3f (330,95,0);
        glVertex3f (380,95,0);
        glVertex3f (380,45,0);
        glVertex3f (330,45,0);
        
        glVertex3f (330,95,340);
        glVertex3f (380,95,340);
        glVertex3f (380,45,340);
        glVertex3f (330,45,340);
        
        glVertex3f (330,95,0);
        glVertex3f (380,95,0);
        glVertex3f (380,95,340);
        glVertex3f (330,95,340);
        
        glVertex3f (380,95,0);
        glVertex3f (380,45,0);
        glVertex3f (380,45,340);
        glVertex3f (380,95,340);
        
        glVertex3f (380,45,0);
        glVertex3f (330,45,0);
        glVertex3f (330,45,340);
        glVertex3f (380,45,340);
        
        glVertex3f (330,45,0);
        glVertex3f (330,95,0);
        glVertex3f (330,95,340);
        glVertex3f (330,45,340);
        
        //Fourth obstacle
        glVertex3f (230,220,0);
        glVertex3f (280,220,0);
        glVertex3f (280,170,0);
        glVertex3f (230,170,0);
        
        glVertex3f (230,220,262);
        glVertex3f (280,220,262);
        glVertex3f (280,170,262);
        glVertex3f (230,170,262);
        
        glVertex3f (230,220,0);
        glVertex3f (280,220,0);
        glVertex3f (280,220,262);
        glVertex3f (230,220,262);
        
        glVertex3f (280,220,0);
        glVertex3f (280,170,0);
        glVertex3f (280,170,262);
        glVertex3f (280,220,262);
        
        glVertex3f (280,170,0);
        glVertex3f (230,170,0);
        glVertex3f (230,170,262);
        glVertex3f (280,170,262);
        
        glVertex3f (230,170,0);
        glVertex3f (230,220,0);
        glVertex3f (230,220,262);
        glVertex3f (230,170,262);
        
        glVertex3f (235,215,262);
        glVertex3f (275,215,262);
        glVertex3f (275,175,262);
        glVertex3f (235,175,262);
        
        glVertex3f (235,215,269);
        glVertex3f (275,215,269);
        glVertex3f (275,175,269);
        glVertex3f (235,175,269);
        
        glVertex3f (235,215,262);
        glVertex3f (275,215,262);
        glVertex3f (275,215,269);
        glVertex3f (235,215,269);
        
        glVertex3f (275,215,262);
        glVertex3f (275,175,262);
        glVertex3f (275,175,269);
        glVertex3f (275,215,269);
        
        glVertex3f (275,175,262);
        glVertex3f (235,175,262);
        glVertex3f (235,175,269);
        glVertex3f (275,175,269);
        
        glVertex3f (235,175,262);
        glVertex3f (235,215,262);
        glVertex3f (235,215,269);
        glVertex3f (235,175,269);
        
        glVertex3f (240,210,269);
        glVertex3f (270,210,269);
        glVertex3f (270,180,269);
        glVertex3f (240,180,269);
        
        glVertex3f (240,210,276);
        glVertex3f (270,210,276);
        glVertex3f (270,180,276);
        glVertex3f (240,180,276);
        
        glVertex3f (240,210,269);
        glVertex3f (270,210,269);
        glVertex3f (270,210,276);
        glVertex3f (240,210,276);
        
        glVertex3f (270,210,269);
        glVertex3f (270,180,269);
        glVertex3f (270,180,276);
        glVertex3f (270,210,276);
        
        glVertex3f (270,180,269);
        glVertex3f (240,180,269);
        glVertex3f (240,180,276);
        glVertex3f (270,180,276);
        
        glVertex3f (240,180,269);
        glVertex3f (240,210,269);
        glVertex3f (240,210,276);
        glVertex3f (240,180,276);
        
        glVertex3f (245,205,276);
        glVertex3f (265,205,276);
        glVertex3f (265,185,276);
        glVertex3f (245,185,276);
        
        glVertex3f (245,205,283);
        glVertex3f (265,205,283);
        glVertex3f (265,185,283);
        glVertex3f (245,185,283);
        
        glVertex3f (245,205,276);
        glVertex3f (265,205,276);
        glVertex3f (265,205,283);
        glVertex3f (245,205,283);
        
        glVertex3f (265,205,276);
        glVertex3f (265,185,276);
        glVertex3f (265,185,283);
        glVertex3f (265,205,283);
        
        glVertex3f (265,185,276);
        glVertex3f (245,185,276);
        glVertex3f (245,185,283);
        glVertex3f (265,185,283);
        
        glVertex3f (245,185,276);
        glVertex3f (245,205,276);
        glVertex3f (245,205,283);
        glVertex3f (245,185,283);
        
        glVertex3f (250,200,283);
        glVertex3f (260,200,283);
        glVertex3f (260,190,283);
        glVertex3f (250,190,283);
        
        glVertex3f (250,200,290);
        glVertex3f (260,200,290);
        glVertex3f (260,190,290);
        glVertex3f (250,190,290);
        
        glVertex3f (250,200,283);
        glVertex3f (260,200,283);
        glVertex3f (260,200,290);
        glVertex3f (250,200,290);
        
        glVertex3f (260,200,283);
        glVertex3f (260,190,283);
        glVertex3f (260,190,290);
        glVertex3f (260,200,290);
        
        glVertex3f (260,190,283);
        glVertex3f (250,190,283);
        glVertex3f (250,190,290);
        glVertex3f (260,190,290);
        
        glVertex3f (250,190,283);
        glVertex3f (250,200,283);
        glVertex3f (250,200,290);
        glVertex3f (250,190,290);
        
        glVertex3f (253,197,290);
        glVertex3f (257,197,290);
        glVertex3f (257,193,290);
        glVertex3f (253,193,290);
        
        glVertex3f (253,197,305);
        glVertex3f (257,197,305);
        glVertex3f (257,193,305);
        glVertex3f (253,193,305);
        
        glVertex3f (253,197,290);
        glVertex3f (257,197,290);
        glVertex3f (257,197,305);
        glVertex3f (253,197,305);
        
        glVertex3f (257,197,290);
        glVertex3f (257,193,290);
        glVertex3f (257,193,305);
        glVertex3f (257,197,305);
        
        glVertex3f (257,193,290);
        glVertex3f (253,193,290);
        glVertex3f (253,193,305);
        glVertex3f (257,193,305);
        
        glVertex3f (253,193,290);
        glVertex3f (253,197,290);
        glVertex3f (253,197,305);
        glVertex3f (253,193,305);
        
        glEnd();
        
        //glVertex3f ();
        glBegin(GL_POLYGON);
        glColor3f  ( 0.9, 0.9,  0.9);
        
        //first obstacle
        glVertex3f (20,80,200);
        glVertex3f (50,80,200);
        glVertex3f (50,110,200);
        glVertex3f (110,110,200);
        glVertex3f (110,50,200);
        glVertex3f (80,50,200);
        glVertex3f (80,20,200);
        glVertex3f (20,20,200);
        
        glVertex3f (20,80,270);
        glVertex3f (50,80,270);
        glVertex3f (50,110,270);
        glVertex3f (110,110,270);
        glVertex3f (110,50,270);
        glVertex3f (80,50,270);
        glVertex3f (80,20,270);
        glVertex3f (20,20,270);
        
        glVertex3f (20,80,270);
        glVertex3f (50,80,270);
        glVertex3f (50,110,270);
        glVertex3f (80,110,270);
        glVertex3f (80,80,270);
        glVertex3f (110,80,270);
        glVertex3f (110,50,270);
        glVertex3f (80,50,270);
        glVertex3f (80,20,270);
        glVertex3f (50,20,270);
        glVertex3f (50,50,270);
        glVertex3f (20,50,270);
        
        glVertex3f (20,80,380);
        glVertex3f (50,80,380);
        glVertex3f (50,110,380);
        glVertex3f (80,110,380);
        glVertex3f (80,80,380);
        glVertex3f (110,80,380);
        glVertex3f (110,50,380);
        glVertex3f (80,50,380);
        glVertex3f (80,20,380);
        glVertex3f (50,20,380);
        glVertex3f (50,50,380);
        glVertex3f (20,50,380);
        
        glEnd();
        
        glLineWidth(1.3);
        
        glBegin(GL_LINES);
        glColor3f  ( 0.0, 0.0,  0.0);
        
        //first obstacle
        glVertex3f (20,110,0);
        glVertex3f (110,110,0);
        
        glVertex3f (110,110,0);
        glVertex3f (110,20,0);
        
        glVertex3f (110,20,0);
        glVertex3f (20,20,0);
        
        glVertex3f (20,20,0);
        glVertex3f (20,110,0);
        
        glVertex3f (20,110,200);
        glVertex3f (110,110,200);
        
        glVertex3f (110,110,200);
        glVertex3f (110,20,200);
        
        glVertex3f (110,20,200);
        glVertex3f (20,20,200);
        
        glVertex3f (20,20,200);
        glVertex3f (20,110,200);
        
        glVertex3f (20,110,0);
        glVertex3f (20,110,200);
        
        glVertex3f (110,110,0);
        glVertex3f (110,110,200);
        
        glVertex3f (110,20,0);
        glVertex3f (110,20,200);
        
        glVertex3f (20,20,0);
        glVertex3f (20,20,200);
        
        glVertex3f (20,80,200);
        glVertex3f (50,80,200);
        
        glVertex3f (50,80,200);
        glVertex3f (50,110,200);
        
        glVertex3f (50,110,200);
        glVertex3f (110,110,200);
        
        glVertex3f (110,110,200);
        glVertex3f (110,50,200);
        
        glVertex3f (110,50,200);
        glVertex3f (80,50,200);
        
        glVertex3f (80,50,200);
        glVertex3f (80,20,200);
        
        glVertex3f (80,20,200);
        glVertex3f (20,20,200);
        
        glVertex3f (20,20,200);
        glVertex3f (20,80,200);
        
        glVertex3f (20,80,270);
        glVertex3f (50,80,270);
        
        glVertex3f (50,80,270);
        glVertex3f (50,110,270);
        
        glVertex3f (50,110,270);
        glVertex3f (110,110,270);
        
        glVertex3f (110,110,270);
        glVertex3f (110,50,270);
        
        glVertex3f (110,50,270);
        glVertex3f (80,50,270);
        
        glVertex3f (80,50,270);
        glVertex3f (80,20,270);
        
        glVertex3f (80,20,270);
        glVertex3f (20,20,270);
        
        glVertex3f (20,20,270);
        glVertex3f (20,80,270);
        
        glVertex3f (20,80,200);
        glVertex3f (20,80,270);
        
        glVertex3f (50,80,200);
        glVertex3f (50,80,270);
        
        glVertex3f (50,110,200);
        glVertex3f (50,110,270);
        
        glVertex3f (110,110,200);
        glVertex3f (110,110,270);
        
        glVertex3f (110,50,200);
        glVertex3f (110,50,270);
        
        glVertex3f (80,50,200);
        glVertex3f (80,50,270);
        
        glVertex3f (80,20,200);
        glVertex3f (80,20,270);
        
        glVertex3f (20,20,200);
        glVertex3f (20,20,270);
        
        glVertex3f (20,80,270);
        glVertex3f (50,80,270);
        
        glVertex3f (50,80,270);
        glVertex3f (50,110,270);
        
        glVertex3f (50,110,270);
        glVertex3f (80,110,270);
        
        glVertex3f (80,110,270);
        glVertex3f (80,80,270);
        
        glVertex3f (80,80,270);
        glVertex3f (110,80,270);
        
        glVertex3f (110,80,270);
        glVertex3f (110,50,270);
        
        glVertex3f (110,50,270);
        glVertex3f (80,50,270);
        
        glVertex3f (80,50,270);
        glVertex3f (80,20,270);
        
        glVertex3f (80,20,270);
        glVertex3f (50,20,270);
        
        glVertex3f (50,20,270);
        glVertex3f (50,50,270);
        
        glVertex3f (50,50,270);
        glVertex3f (20,50,270);
        
        glVertex3f (20,50,270);
        glVertex3f (20,80,270);
        
        glVertex3f (20,80,380);
        glVertex3f (50,80,380);
        
        glVertex3f (50,80,380);
        glVertex3f (50,110,380);
        
        glVertex3f (50,110,380);
        glVertex3f (80,110,380);
        
        glVertex3f (80,110,380);
        glVertex3f (80,80,380);
        
        glVertex3f (80,80,380);
        glVertex3f (110,80,380);
        
        glVertex3f (110,80,380);
        glVertex3f (110,50,380);
        
        glVertex3f (110,50,380);
        glVertex3f (80,50,380);
        
        glVertex3f (80,50,380);
        glVertex3f (80,20,380);
        
        glVertex3f (80,20,380);
        glVertex3f (50,20,380);
        
        glVertex3f (50,20,380);
        glVertex3f (50,50,380);
        
        glVertex3f (50,50,380);
        glVertex3f (20,50,380);
        
        glVertex3f (20,50,380);
        glVertex3f (20,80,380);
        
        glVertex3f (20,80,380);
        glVertex3f (20,80,270);
        
        glVertex3f (50,80,380);
        glVertex3f (50,80,270);
        
        glVertex3f (50,110,380);
        glVertex3f (50,110,270);
        
        glVertex3f (80,110,380);
        glVertex3f (80,110,270);
        
        glVertex3f (80,80,380);
        glVertex3f (80,80,270);
        
        glVertex3f (110,80,380);
        glVertex3f (110,80,270);
        
        glVertex3f (110,50,380);
        glVertex3f (110,50,270);
        
        glVertex3f (80,50,380);
        glVertex3f (80,50,270);
        
        glVertex3f (80,20,380);
        glVertex3f (80,20,270);
        
        glVertex3f (50,20,380);
        glVertex3f (50,20,270);
        
        glVertex3f (50,50,270);
        glVertex3f (50,50,380);
        
        glVertex3f (20,50,270);
        glVertex3f (20,50,380);
        
        glVertex3f (20,80,380);
        glVertex3f (80,80,380);
        
        glVertex3f (80,80,380);
        glVertex3f (80,50,380);
        
        glVertex3f (80,50,380);
        glVertex3f (20,50,380);
        
        glVertex3f (20,50,380);
        glVertex3f (20,80,380);
        
        glVertex3f (20,80,440);
        glVertex3f (80,80,440);
        
        glVertex3f (80,80,440);
        glVertex3f (80,50,440);
        
        glVertex3f (80,50,440);
        glVertex3f (20,50,440);
        
        glVertex3f (20,50,440);
        glVertex3f (20,80,440);
        
        glVertex3f (20,80,440);
        glVertex3f (20,80,380);
        
        glVertex3f (80,80,440);
        glVertex3f (80,80,380);
        
        glVertex3f (80,50,440);
        glVertex3f (80,50,380);
        
        glVertex3f (20,50,440);
        glVertex3f (20,50,380);
        
        //second obstacle
        glVertex3f (200,150,0);
        glVertex3f (300,150,0);
        
        glVertex3f (300,150,0);
        glVertex3f (250,110,0);
        
        glVertex3f (250,110,0);
        glVertex3f (200,110,0);
        
        glVertex3f (200,110,0);
        glVertex3f (200,150,0);
        
        glVertex3f (200,150,70);
        glVertex3f (300,150,70);
        
        glVertex3f (300,150,70);
        glVertex3f (250,110,70);
        
        glVertex3f (250,110,70);
        glVertex3f (200,110,70);
        
        glVertex3f (200,110,70);
        glVertex3f (200,150,70);
        
        glVertex3f (200,150,0);
        glVertex3f (200,150,70);
        
        glVertex3f (300,150,0);
        glVertex3f (300,150,70);
        
        glVertex3f (250,110,0);
        glVertex3f (250,110,70);
        
        glVertex3f (200,110,0);
        glVertex3f (200,110,70);
        
        glVertex3f (245,132,70);
        glVertex3f (261,145,70);
        
        glVertex3f (261,145,70);
        glVertex3f (277,132,70);
        
        glVertex3f (277,132,70);
        glVertex3f (261,119,70);
        
        glVertex3f (261,119,70);
        glVertex3f (245,132,70);
        
        glVertex3f (245,132,130);
        glVertex3f (261,145,130);
        
        glVertex3f (261,145,130);
        glVertex3f (277,132,130);
        
        glVertex3f (277,132,130);
        glVertex3f (261,119,130);
        
        glVertex3f (261,119,130);
        glVertex3f (245,132,130);
        
        glVertex3f (245,132,70);
        glVertex3f (245,132,130);
        
        glVertex3f (261,145,70);
        glVertex3f (261,145,130);
        
        glVertex3f (277,132,70);
        glVertex3f (277,132,130);
        
        glVertex3f (261,119,70);
        glVertex3f (261,119,130);
        
        //third obstacle
        glVertex3f (330,95,0);
        glVertex3f (380,95,0);
        
        glVertex3f (380,95,0);
        glVertex3f (380,45,0);
        
        glVertex3f (380,45,0);
        glVertex3f (330,45,0);
        
        glVertex3f (330,45,0);
        glVertex3f (330,95,0);
        
        glVertex3f (330,95,340);
        glVertex3f (380,95,340);
        
        glVertex3f (380,95,340);
        glVertex3f (380,45,340);
        
        glVertex3f (380,45,340);
        glVertex3f (330,45,340);
        
        glVertex3f (330,45,340);
        glVertex3f (330,95,340);
        
        glVertex3f (330,95,0);
        glVertex3f (330,95,340);
        
        glVertex3f (380,95,0);
        glVertex3f (380,95,340);
        
        glVertex3f (380,45,0);
        glVertex3f (380,45,340);
        
        glVertex3f (330,45,0);
        glVertex3f (330,45,340);
        
        //fourth obstacle
        glVertex3f (230,220,0);
        glVertex3f (280,220,0);
        
        glVertex3f (280,220,0);
        glVertex3f (280,170,0);
        
        glVertex3f (280,170,0);
        glVertex3f (230,170,0);
        
        glVertex3f (230,170,0);
        glVertex3f (230,220,0);
        
        glVertex3f (230,220,262);
        glVertex3f (280,220,262);
        
        glVertex3f (280,220,262);
        glVertex3f (280,170,262);
        
        glVertex3f (280,170,262);
        glVertex3f (230,170,262);
        
        glVertex3f (230,170,262);
        glVertex3f (230,220,262);
        
        glVertex3f (230,220,0);
        glVertex3f (230,220,262);
        
        glVertex3f (280,220,0);
        glVertex3f (280,220,262);
        
        glVertex3f (280,170,0);
        glVertex3f (280,170,262);
        
        glVertex3f (230,170,0);
        glVertex3f (230,170,262);
        
        glVertex3f (235,215,262);
        glVertex3f (275,215,262);
        
        glVertex3f (275,215,262);
        glVertex3f (275,175,262);
        
        glVertex3f (275,175,262);
        glVertex3f (235,175,262);
        
        glVertex3f (235,175,262);
        glVertex3f (235,215,262);
        
        glVertex3f (235,215,269);
        glVertex3f (275,215,269);
        
        glVertex3f (275,215,269);
        glVertex3f (275,175,269);
        
        glVertex3f (275,175,269);
        glVertex3f (235,175,269);
        
        glVertex3f (235,175,269);
        glVertex3f (235,215,269);
        
        glVertex3f (235,215,262);
        glVertex3f (235,215,269);
        
        glVertex3f (275,215,262);
        glVertex3f (275,215,269);
        
        glVertex3f (275,175,262);
        glVertex3f (275,175,269);
        
        glVertex3f (235,175,262);
        glVertex3f (235,175,269);
        
        glVertex3f (240,210,269);
        glVertex3f (270,210,269);
        
        glVertex3f (270,210,269);
        glVertex3f (270,180,269);
        
        glVertex3f (270,180,269);
        glVertex3f (240,180,269);
        
        glVertex3f (240,180,269);
        glVertex3f (240,210,269);
        
        glVertex3f (240,210,276);
        glVertex3f (270,210,276);
        
        glVertex3f (270,210,276);
        glVertex3f (270,180,276);
        
        glVertex3f (270,180,276);
        glVertex3f (240,180,276);
        
        glVertex3f (240,180,276);
        glVertex3f (240,210,276);
        
        glVertex3f (240,210,269);
        glVertex3f (240,210,276);
        
        glVertex3f (270,210,269);
        glVertex3f (270,210,276);
        
        glVertex3f (270,180,269);
        glVertex3f (270,180,276);
        
        glVertex3f (240,180,269);
        glVertex3f (240,180,276);
        
        glVertex3f (245,205,276);
        glVertex3f (265,205,276);
        
        glVertex3f (265,205,276);
        glVertex3f (265,185,276);
        
        glVertex3f (265,185,276);
        glVertex3f (245,185,276);
        
        glVertex3f (245,185,276);
        glVertex3f (245,205,276);
        
        glVertex3f (245,205,283);
        glVertex3f (265,205,283);
        
        glVertex3f (265,205,283);
        glVertex3f (265,185,283);
        
        glVertex3f (265,185,283);
        glVertex3f (245,185,283);
        
        glVertex3f (245,185,283);
        glVertex3f (245,205,283);
        
        glVertex3f (245,205,276);
        glVertex3f (245,205,283);
        
        glVertex3f (265,205,276);
        glVertex3f (265,205,283);
        
        glVertex3f (265,185,276);
        glVertex3f (265,185,283);
        
        glVertex3f (245,185,276);
        glVertex3f (245,185,283);
        
        glVertex3f (250,200,283);
        glVertex3f (260,200,283);
        
        glVertex3f (260,200,283);
        glVertex3f (260,190,283);
        
        glVertex3f (260,190,283);
        glVertex3f (250,190,283);
        
        glVertex3f (250,190,283);
        glVertex3f (250,200,283);
        
        glVertex3f (250,200,290);
        glVertex3f (260,200,290);
        
        glVertex3f (260,200,290);
        glVertex3f (260,190,290);
        
        glVertex3f (260,190,290);
        glVertex3f (250,190,290);
        
        glVertex3f (250,190,290);
        glVertex3f (250,200,290);
        
        glVertex3f (250,200,283);
        glVertex3f (250,200,290);
        
        glVertex3f (260,200,283);
        glVertex3f (260,200,290);
        
        glVertex3f (260,190,283);
        glVertex3f (260,190,290);
        
        glVertex3f (250,190,283);
        glVertex3f (250,190,290);
        
        glVertex3f (253,197,290);
        glVertex3f (257,197,290);
        
        glVertex3f (257,197,290);
        glVertex3f (257,193,290);
        
        glVertex3f (257,193,290);
        glVertex3f (253,193,290);
        
        glVertex3f (253,193,290);
        glVertex3f (253,197,290);
        
        glVertex3f (253,197,305);
        glVertex3f (257,197,305);
        
        glVertex3f (257,197,305);
        glVertex3f (257,193,305);
        
        glVertex3f (257,193,305);
        glVertex3f (253,193,305);
        
        glVertex3f (253,193,305);
        glVertex3f (253,197,305);
        
        glVertex3f (253,197,290);
        glVertex3f (253,197,305);
        
        glVertex3f (257,197,290);
        glVertex3f (257,197,305);
        
        glVertex3f (257,193,290);
        glVertex3f (257,193,305);
        
        glVertex3f (253,193,290);
        glVertex3f (253,193,305);
        
        glEnd();

    }
    else if (m == 4) {
        glBegin (GL_QUADS);
        
        glColor3f  ( 0.9, 0.9,  0.9);
        glVertex3f (10.0,  35.0, 0.0);
        glVertex3f ( 50.0,  35.0, 0.0);
        glVertex3f ( 50.0, 10.0, 0.0);
        glVertex3f (10.0, 10.0, 0.0);
        
        glVertex3f (10.0,  35.0, 0.0);
        glVertex3f ( 10.0,  10.0, 0.0);
        glVertex3f ( 10.0, 10.0, 85.0);
        glVertex3f (10.0, 35.0, 85.0);
        
        glVertex3f (10.0, 35.0,  0.0);
        glVertex3f ( 50.0, 35.0,  0.0);
        glVertex3f ( 50.0, 35.0, 85.0);
        glVertex3f (10.0, 35.0, 85.0);
        
        glVertex3f (50.0, 35.0,  0.0);
        glVertex3f ( 50.0, 10.0,  0.0);
        glVertex3f ( 50.0, 10.0, 85.0);
        glVertex3f (50.0, 35.0, 85.0);
        
        glVertex3f (10.0,  10.0, 0.0);
        glVertex3f ( 50.0,  10.0, 0.0);
        glVertex3f ( 50.0, 10.0, 85.0);
        glVertex3f (10.0, 10.0, 85.0);
        
        glVertex3f (10.0,  35.0, 20.0);
        glVertex3f ( 50.0,  35.0, 20.0);
        glVertex3f ( 50.0, 10.0, 85.0);
        glVertex3f (10.0, 10.0, 85.0);
        
        glVertex3f (132.0,  223.0, 0.0);
        glVertex3f ( 212.0,  223.0, 0.0);
        glVertex3f ( 212.0, 223.0, 90.0);
        glVertex3f (132.0, 223.0, 90.0);
        
        glVertex3f (212.0,  223.0, 0.0);
        glVertex3f ( 212.0,  143.0, 0.0);
        glVertex3f ( 212.0, 143.0, 90.0);
        glVertex3f (212.0, 223.0, 90.0);
        
        glVertex3f (132.0,  223.0, 0.0);
        glVertex3f ( 212.0,  143.0, 0.0);
        glVertex3f ( 212.0, 143.0, 90.0);
        glVertex3f (132.0, 223.0, 90.0);
        
        glVertex3f (20.0,  250.0, 0.0);
        glVertex3f ( 100.0, 170.0, 0.0);
        glVertex3f ( 100.0, 170.0, 50.0);
        glVertex3f (20.0,  250.0, 50.0);
        
        glVertex3f ( 20.0,  170.0, 0.0);
        glVertex3f ( 100.0, 170.0, 0.0);
        glVertex3f ( 100.0, 170.0, 50.0);
        glVertex3f ( 20.0,  170.0, 50.0);
        
        glVertex3f (20.0,  250.0, 0.0);
        glVertex3f ( 20.0,  170.0, 0.0);
        glVertex3f ( 20.0,  170.0, 50.0);
        glVertex3f (20.0,  250.0, 50.0);
        
        glVertex3f (35.0,  130.0, 0.0);
        glVertex3f ( 195.0,  130.0, 0.0);
        glVertex3f ( 195.0, 50.0, 0.0);
        glVertex3f (35.0, 50.0, 0.0);
        
        glVertex3f (35.0,  130.0, 40.0);
        glVertex3f ( 195.0,  130.0, 40.0);
        glVertex3f ( 195.0, 50.0, 40.0);
        glVertex3f (35.0, 50.0, 40.0);
        
        glVertex3f (35.0,  130.0, 0.0);
        glVertex3f ( 195.0,  130.0, 0.0);
        glVertex3f ( 195.0,  130.0, 40.0);
        glVertex3f (35.0,  130.0, 40.0);
        
        glVertex3f ( 195.0,  130.0, 0.0);
        glVertex3f ( 195.0, 50.0, 0.0);
        glVertex3f ( 195.0, 50.0, 40.0);
        glVertex3f ( 195.0,  130.0, 40.0);
        
        glVertex3f ( 195.0, 50.0, 0.0);
        glVertex3f (35.0, 50.0, 0.0);
        glVertex3f (35.0, 50.0, 40.0);
        glVertex3f ( 195.0, 50.0, 40.0);
        
        glVertex3f (35.0, 50.0, 0.0);
        glVertex3f (35.0,  130.0, 0.0);
        glVertex3f (35.0,  130.0, 40.0);
        glVertex3f (35.0, 50.0, 40.0);
        
        glVertex3f (76.0,  260.0, 38.0);
        glVertex3f (126.0,  260.0, 38.0);
        glVertex3f (126.0,  210.0, 38.0);
        glVertex3f (76.0,  210.0, 38.0);
        
        glVertex3f (76.0,  260.0, 0.0);
        glVertex3f (126.0,  260.0, 0.0);
        glVertex3f (126.0,  210.0, 0.0);
        glVertex3f (76.0,  210.0, 0.0);
        
        glVertex3f (76.0,  260.0, 0.0);
        glVertex3f (126.0,  260.0, 0.0);
        glVertex3f (126.0,  260.0, 38.0);
        glVertex3f (76.0,  260.0, 38.0);
        
        glVertex3f (126.0,  260.0, 0.0);
        glVertex3f (126.0,  210.0, 0.0);
        glVertex3f (126.0,  210.0, 38.0);
        glVertex3f (126.0,  260.0, 38.0);
        
        glVertex3f (126.0,  210.0, 0.0);
        glVertex3f (76.0,  210.0, 0.0);
        glVertex3f (76.0,  210.0, 38.0);
        glVertex3f (126.0,  210.0, 38.0);
        
        glVertex3f (76.0,  210.0, 0.0);
        glVertex3f (76.0,  260.0, 0.0);
        glVertex3f (76.0,  260.0, 38.0);
        glVertex3f (76.0,  210.0, 38.0);
        
        glVertex3f (180.0,  15.0, 0.0);
        glVertex3f ( 222.0,  57.0, 0.0);
        glVertex3f ( 222.0,  57.0, 50.0);
        glVertex3f (180.0,  15.0, 50.0);
        
        glVertex3f ( 222.0,  57.0, 0.0);
        glVertex3f ( 222.0, 15.0, 0.0);
        glVertex3f ( 222.0, 15.0, 50.0);
        glVertex3f ( 222.0,  57.0, 50.0);
        
        glVertex3f ( 222.0, 15.0, 0.0);
        glVertex3f (180.0,  15.0, 0.0);
        glVertex3f (180.0,  15.0, 50.0);
        glVertex3f ( 222.0, 15.0, 50.0);
        
        glVertex3f (250.0,  263.0, 0.0);
        glVertex3f (350.0,  263.0, 0.0);
        glVertex3f (350.0,  13.0, 0.0);
        glVertex3f (250.0,  13.0, 0.0);
        
        glVertex3f (250.0,  263.0, 75.0);
        glVertex3f (350.0,  263.0, 75.0);
        glVertex3f (350.0,  13.0, 75.0);
        glVertex3f (250.0,  13.0, 75.0);
        
        glVertex3f (250.0,  263.0, 0.0);
        glVertex3f (350.0,  263.0, 0.0);
        glVertex3f (350.0,  263.0, 75.0);
        glVertex3f (250.0,  263.0, 75.0);
        
        glVertex3f (350.0,  263.0, 0.0);
        glVertex3f (350.0,  13.0, 0.0);
        glVertex3f (350.0,  13.0, 75.0);
        glVertex3f (350.0,  263.0, 75.0);
        
        glVertex3f (350.0,  13.0, 0.0);
        glVertex3f (250.0,  13.0, 0.0);
        glVertex3f (250.0,  13.0, 75.0);
        glVertex3f (350.0,  13.0, 75.0);
        
        glVertex3f (250.0,  13.0, 0.0);
        glVertex3f (250.0,  263.0, 0.0);
        glVertex3f (250.0,  263.0, 75.0);
        glVertex3f (250.0,  13.0, 75.0);
        
        glVertex3f (65.0,  115.0, 40.0);
        glVertex3f (165.0,  115.0, 40.0);
        glVertex3f (165.0,  65.0, 40.0);
        glVertex3f (65.0,  65.0, 40.0);
        
        glVertex3f (65.0,  115.0, 63.0);
        glVertex3f (165.0,  115.0, 63.0);
        glVertex3f (165.0,  65.0, 63.0);
        glVertex3f (65.0,  65.0, 63.0);
        
        glVertex3f (65.0,  115.0, 40.0);
        glVertex3f (165.0,  115.0, 40.0);
        glVertex3f (165.0,  115.0, 63.0);
        glVertex3f (65.0,  115.0, 63.0);
        
        glVertex3f (165.0,  115.0, 40.0);
        glVertex3f (165.0,  65.0, 40.0);
        glVertex3f (165.0,  65.0, 63.0);
        glVertex3f (165.0,  115.0, 63.0);
        
        glVertex3f (165.0,  65.0, 40.0);
        glVertex3f (65.0,  65.0, 40.0);
        glVertex3f (65.0,  65.0, 63.0);
        glVertex3f (165.0,  65.0, 63.0);
        
        glVertex3f (65.0,  65.0, 40.0);
        glVertex3f (65.0,  115.0, 40.0);
        glVertex3f (65.0,  115.0, 63.0);
        glVertex3f (65.0,  65.0, 63.0);
        
        glVertex3f (102.0,  115.0, 63.0);
        glVertex3f (165.0,  115.0, 63.0);
        glVertex3f (165.0,  83.0, 63.0);
        glVertex3f (102.0,  83.0, 63.0);
        
        glVertex3f (102.0,  115.0, 82.0);
        glVertex3f (165.0,  115.0, 82.0);
        glVertex3f (165.0,  83.0, 82.0);
        glVertex3f (102.0,  83.0, 82.0);
        
        glVertex3f (102.0,  115.0, 63.0);
        glVertex3f (165.0,  115.0, 63.0);
        glVertex3f (165.0,  115.0, 82.0);
        glVertex3f (102.0,  115.0, 82.0);
        
        glVertex3f (165.0,  115.0, 63.0);
        glVertex3f (165.0,  83.0, 63.0);
        glVertex3f (165.0,  83.0, 82.0);
        glVertex3f (165.0,  115.0, 82.0);
        
        glVertex3f (165.0,  83.0, 63.0);
        glVertex3f (102.0,  83.0, 63.0);
        glVertex3f (102.0,  83.0, 82.0);
        glVertex3f (165.0,  83.0, 82.0);
        
        glVertex3f (102.0,  83.0, 63.0);
        glVertex3f (102.0,  115.0, 63.0);
        glVertex3f (102.0,  115.0, 82.0);
        glVertex3f (102.0,  83.0, 82.0);
        
        glColor3f  ( 0.6, 0.6,  0.6);
        glVertex3f (-40.0,  -10.0, 0.0);
        glVertex3f (-40.0,  300.0, 0.0);
        glVertex3f (400.0,  300.0, 0.0);
        glVertex3f (400.0,  -10.0, 0.0);
        
        glEnd();
        
        glBegin(GL_TRIANGLES);
        
        glColor3f  ( 0.9, 0.9,  0.9);
        glVertex3f (132.0,  223.0, 0.0);
        glVertex3f ( 212.0,  223.0, 0.0);
        glVertex3f ( 212.0, 143.0, 0.0);
        
        glVertex3f (132.0,  223.0, 90.0);
        glVertex3f ( 212.0,  223.0, 90.0);
        glVertex3f ( 212.0, 143.0, 90.0);
        
        glVertex3f (20.0,  250.0, 50.0);
        glVertex3f ( 20.0,  170.0, 50.0);
        glVertex3f ( 100.0, 170.0, 50.0);
        
        glVertex3f (20.0,  250.0, 0.0);
        glVertex3f ( 20.0,  170.0, 0.0);
        glVertex3f ( 100.0, 170.0, 0.0);
        
        glVertex3f (180.0,  15.0, 0.0);
        glVertex3f ( 222.0,  57.0, 0.0);
        glVertex3f ( 222.0, 15.0, 0.0);
        
        glVertex3f (180.0,  15.0, 50.0);
        glVertex3f ( 222.0,  57.0, 50.0);
        glVertex3f ( 222.0, 15.0, 50.0);
        
        
        glEnd();
        
        glLineWidth(1.3);
        
        glBegin(GL_LINES);
        glColor3f  ( 0.0, 0.0,  0.0);
        glVertex3f (10.0,  35.0, 0.0);
        glVertex3f ( 50.0,  35.0, 0.0);
        
        glVertex3f ( 50.0,  35.0, 0.0);
        glVertex3f ( 50.0, 10.0, 0.0);
        
        glVertex3f ( 50.0, 10.0, 0.0);
        glVertex3f (10.0, 10.0, 0.0);
        
        glVertex3f (10.0, 10.0, 0.0);
        glVertex3f (10.0,  35.0, 0.0);
        
        glVertex3f (10.0,  35.0, 85.0);
        glVertex3f ( 50.0,  35.0, 85.0);
        
        glVertex3f ( 50.0,  35.0, 85.0);
        glVertex3f ( 50.0, 10.0, 85.0);
        
        glVertex3f ( 50.0, 10.0, 85.0);
        glVertex3f (10.0, 10.0, 85.0);
        
        glVertex3f (10.0, 10.0, 85.0);
        glVertex3f (10.0,  35.0, 85.0);
        
        glVertex3f (10.0,  35.0, 0.0);
        glVertex3f (10.0,  35.0, 85.0);
        
        glVertex3f ( 50.0,  35.0, 0.0);
        glVertex3f ( 50.0,  35.0, 85.0);
        
        glVertex3f ( 50.0, 10.0, 0.0);
        glVertex3f ( 50.0, 10.0, 85.0);
        
        glVertex3f (10.0, 10.0, 0.0);
        glVertex3f (10.0, 10.0, 85.0);
        
        glVertex3f (132.0,  223.0, 0.0);
        glVertex3f ( 212.0,  223.0, 0.0);
        
        glVertex3f (212.0,  223.0, 0.0);
        glVertex3f ( 212.0,  143.0, 0.0);
        
        glVertex3f (132.0,  223.0, 0.0);
        glVertex3f ( 212.0,  143.0, 0.0);
        
        glVertex3f (132.0,  223.0, 90.0);
        glVertex3f ( 212.0,  223.0, 90.0);
        
        glVertex3f (212.0,  223.0, 90.0);
        glVertex3f ( 212.0,  143.0, 90.0);
        
        glVertex3f (132.0,  223.0, 90.0);
        glVertex3f ( 212.0,  143.0, 90.0);
        
        glVertex3f (132.0,  223.0, 0.0);
        glVertex3f (132.0,  223.0, 90.0);
        
        glVertex3f (212.0,  223.0, 0.0);
        glVertex3f (212.0,  223.0, 90.0);
        
        glVertex3f ( 212.0,  143.0, 0.0);
        glVertex3f ( 212.0,  143.0, 90.0);
        
        glVertex3f (20.0,  250.0, 0.0);
        glVertex3f ( 20.0,  170.0, 0.0);
        
        glVertex3f ( 20.0,  170.0, 0.0);
        glVertex3f ( 100.0, 170.0, 0.0);
        
        glVertex3f ( 100.0, 170.0, 0.0);
        glVertex3f (20.0,  250.0, 0.0);
        
        glVertex3f (20.0,  250.0, 50.0);
        glVertex3f ( 20.0,  170.0, 50.0);
        
        glVertex3f ( 20.0,  170.0, 50.0);
        glVertex3f ( 100.0, 170.0, 50.0);
        
        glVertex3f ( 100.0, 170.0, 50.0);
        glVertex3f (20.0,  250.0, 50.0);
        
        glVertex3f (20.0,  250.0, 0.0);
        glVertex3f (20.0,  250.0, 50.0);
        
        glVertex3f ( 20.0,  170.0, 0.0);
        glVertex3f ( 20.0,  170.0, 50.0);
        
        glVertex3f ( 100.0, 170.0, 0.0);
        glVertex3f ( 100.0, 170.0, 50.0);
        
        glVertex3f (76.0,  260.0, 0.0);
        glVertex3f (126.0,  260.0, 0.0);
        
        glVertex3f (126.0,  260.0, 0.0);
        glVertex3f (126.0,  210.0, 0.0);
        
        glVertex3f (126.0,  210.0, 0.0);
        glVertex3f (76.0,  210.0, 0.0);
        
        glVertex3f (76.0,  210.0, 0.0);
        glVertex3f (76.0,  260.0, 0.0);
        
        glVertex3f (76.0,  260.0, 38.0);
        glVertex3f (126.0,  260.0, 38.0);
        
        glVertex3f (126.0,  260.0, 38.0);
        glVertex3f (126.0,  210.0, 38.0);
        
        glVertex3f (126.0,  210.0, 38.0);
        glVertex3f (76.0,  210.0, 38.0);
        
        glVertex3f (76.0,  210.0, 38.0);
        glVertex3f (76.0,  260.0, 38.0);
        
        glVertex3f (76.0,  260.0, 0.0);
        glVertex3f (76.0,  260.0, 38.0);
        
        glVertex3f (76.0,  210.0, 0.0);
        glVertex3f (76.0,  210.0, 38.0);
        
        glVertex3f (126.0,  210.0, 0.0);
        glVertex3f (126.0,  210.0, 38.0);
        
        glVertex3f (126.0,  260.0, 0.0);
        glVertex3f (126.0,  260.0, 38.0);
        
        glVertex3f (35.0,  130.0, 0.0);
        glVertex3f ( 195.0,  130.0, 0.0);
        
        glVertex3f ( 195.0,  130.0, 0.0);
        glVertex3f ( 195.0, 50.0, 0.0);
        
        glVertex3f ( 195.0, 50.0, 0.0);
        glVertex3f (35.0, 50.0, 0.0);
        
        glVertex3f (35.0, 50.0, 0.0);
        glVertex3f (35.0,  130.0, 0.0);
        
        glVertex3f (35.0,  130.0, 40.0);
        glVertex3f ( 195.0,  130.0, 40.0);
        
        glVertex3f ( 195.0,  130.0, 40.0);
        glVertex3f ( 195.0, 50.0, 40.0);
        
        glVertex3f ( 195.0, 50.0, 40.0);
        glVertex3f (35.0, 50.0, 40.0);
        
        glVertex3f (35.0, 50.0, 40.0);
        glVertex3f (35.0,  130.0, 40.0);
        
        glVertex3f (35.0, 50.0, 0.0);
        glVertex3f (35.0, 50.0, 40.0);
        
        glVertex3f (35.0,  130.0, 0.0);
        glVertex3f (35.0,  130.0, 40.0);
        
        glVertex3f ( 195.0, 50.0, 0.0);
        glVertex3f ( 195.0, 50.0, 40.0);
        
        glVertex3f ( 195.0,  130.0, 0.0);
        glVertex3f ( 195.0,  130.0, 40.0);
        
        glVertex3f (180.0,  15.0, 50.0);
        glVertex3f ( 222.0,  57.0, 50.0);
        
        glVertex3f ( 222.0,  57.0, 50.0);
        glVertex3f ( 222.0, 15.0, 50.0);
        
        glVertex3f ( 222.0, 15.0, 50.0);
        glVertex3f (180.0,  15.0, 50.0);
        
        glVertex3f (180.0,  15.0, 0.0);
        glVertex3f ( 222.0,  57.0, 0.0);
        
        glVertex3f ( 222.0,  57.0, 0.0);
        glVertex3f ( 222.0, 15.0, 0.0);
        
        glVertex3f ( 222.0, 15.0, 0.0);
        glVertex3f (180.0,  15.0, 0.0);
        
        glVertex3f ( 222.0, 15.0, 0.0);
        glVertex3f ( 222.0, 15.0, 50.0);
        
        glVertex3f (180.0,  15.0, 0.0);
        glVertex3f (180.0,  15.0, 50.0);
        
        glVertex3f ( 222.0,  57.0, 0.0);
        glVertex3f ( 222.0,  57.0, 50.0);
        
        glVertex3f (250.0,  263.0, 75.0);
        glVertex3f (350.0,  263.0, 75.0);
        
        glVertex3f (350.0,  263.0, 75.0);
        glVertex3f (350.0,  13.0, 75.0);
        
        glVertex3f (350.0,  13.0, 75.0);
        glVertex3f (250.0,  13.0, 75.0);
        
        glVertex3f (250.0,  13.0, 75.0);
        glVertex3f (250.0,  263.0, 75.0);
        
        glVertex3f (250.0,  263.0, 0.0);
        glVertex3f (350.0,  263.0, 0.0);
        
        glVertex3f (350.0,  263.0, 0.0);
        glVertex3f (350.0,  13.0, 0.0);
        
        glVertex3f (350.0,  13.0, 0.0);
        glVertex3f (250.0,  13.0, 0.0);
        
        glVertex3f (250.0,  13.0, 0.0);
        glVertex3f (250.0,  263.0, 0.0);
        
        glVertex3f (250.0,  263.0, 0.0);
        glVertex3f (250.0,  263.0, 75.0);
        
        glVertex3f (250.0,  13.0, 0.0);
        glVertex3f (250.0,  13.0, 75.0);
        
        glVertex3f (350.0,  13.0, 0.0);
        glVertex3f (350.0,  13.0, 75.0);
        
        glVertex3f (350.0,  263.0, 0.0);
        glVertex3f (350.0,  263.0, 75.0);
        
        glVertex3f (65.0,  115.0, 63.0);
        glVertex3f (165.0,  115.0, 63.0);
        
        glVertex3f (165.0,  115.0, 63.0);
        glVertex3f (165.0,  65.0, 63.0);
        
        glVertex3f (165.0,  65.0, 63.0);
        glVertex3f (65.0,  65.0, 63.0);
        
        glVertex3f (65.0,  65.0, 63.0);
        glVertex3f (65.0,  115.0, 63.0);
        
        glVertex3f (65.0,  115.0, 40.0);
        glVertex3f (165.0,  115.0, 40.0);
        
        glVertex3f (165.0,  115.0, 40.0);
        glVertex3f (165.0,  65.0, 40.0);
        
        glVertex3f (165.0,  65.0, 40.0);
        glVertex3f (65.0,  65.0, 40.0);
        
        glVertex3f (65.0,  65.0, 40.0);
        glVertex3f (65.0,  115.0, 40.0);
        
        glVertex3f (65.0,  115.0, 40.0);
        glVertex3f (65.0,  115.0, 63.0);
        
        glVertex3f (165.0,  115.0, 40.0);
        glVertex3f (165.0,  115.0, 63.0);
        
        glVertex3f (165.0,  65.0, 40.0);
        glVertex3f (165.0,  65.0, 63.0);
        
        glVertex3f (65.0,  65.0, 40.0);
        glVertex3f (65.0,  65.0, 63.0);
        
        glVertex3f (102.0,  115.0, 82.0);
        glVertex3f (165.0,  115.0, 82.0);
        
        glVertex3f (165.0,  115.0, 82.0);
        glVertex3f (165.0,  83.0, 82.0);
        
        glVertex3f (165.0,  83.0, 82.0);
        glVertex3f (102.0,  83.0, 82.0);
        
        glVertex3f (102.0,  83.0, 82.0);
        glVertex3f (102.0,  115.0, 82.0);
        
        glVertex3f (102.0,  115.0, 63.0);
        glVertex3f (165.0,  115.0, 63.0);
        
        glVertex3f (165.0,  115.0, 63.0);
        glVertex3f (165.0,  83.0, 63.0);
        
        glVertex3f (165.0,  83.0, 63.0);
        glVertex3f (102.0,  83.0, 63.0);
        
        glVertex3f (102.0,  83.0, 63.0);
        glVertex3f (102.0,  115.0, 63.0);
        
        glVertex3f (102.0,  115.0, 63.0);
        glVertex3f (102.0,  115.0, 82.0);
        
        glVertex3f (165.0,  115.0, 63.0);
        glVertex3f (165.0,  115.0, 82.0);
        
        glVertex3f (165.0,  83.0, 63.0);
        glVertex3f (165.0,  83.0, 82.0);
        
        glVertex3f (102.0,  83.0, 63.0);
        glVertex3f (102.0,  83.0, 82.0);
        
        glEnd();
    }
    glLineWidth(5.0);
    glColor3f  (1.0, 0.0,  0.0);
    double x1, y1, z1, x2, y2, z2;
    while (myfile >> x1 >> y1 >> z1 >> x2 >> y2 >> z2)
    {
        glBegin(GL_LINES);
        glVertex3f (x1, y1, z1);
        glVertex3f (x2, y2, z2);
        glEnd();
    }
    myfile.close();
    
}

void redraw (void)
{    
    glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable (GL_DEPTH_TEST);
    
    glLoadIdentity ();
    
    glTranslatef (0, 0, -3);
    glRotatef (tippangle, 1,0,0);  // Up and down arrow keys 'tip' view.
    glRotatef (viewangle, 0,1,0);  // Right/left arrow keys 'turn' view.
    
    glDisable (GL_LIGHTING);
    
    glPushMatrix ();
    glTranslatef (d[0], d[1], d[2]);    // Move box down X axis.
    glScalef (0.005, 0.005, 0.005);
    glRotatef (zAngle, 0,0,1);
    glRotatef (yAngle, 0,1,0);
    glRotatef (xAngle, 1,0,0);
    Draw_Box ();
    glPopMatrix ();
    
    glutSwapBuffers();
}