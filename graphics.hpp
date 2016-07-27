
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


//---+----3----+----2----+----1----+---<>---+----1----+----2----+----3----+----4

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

//---+----3----+----2----+----1----+---<>---+----1----+----2----+----3----+----4

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

//---+----3----+----2----+----1----+---<>---+----1----+----2----+----3----+----4

void Draw_Box (void)
{
    glBegin (GL_QUADS);
    
    glColor3f  ( 1.0, 1.0,  1.0);
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
    
    glEnd();
    
    glBegin(GL_TRIANGLES);
    
    glColor3f  ( 1.0, 1.0,  1.0);
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
    
    glLineWidth(1.0);
    
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
    
    glLineWidth(5.0);
    glColor3f  (1.0, 0.0,  0.0);
    
    ifstream myfile("path.txt");
    double x1, y1, z1, x2, y2, z2;
    while (myfile >> x1 >> y1 >> z1 >> x2 >> y2 >> z2)
    {
        //cout << x1 << " " << y1 << " " << z1 << " " << x2 << " "<< y2 " " << z2 << endl;
        glBegin(GL_LINES);
        glVertex3f (x1, y1, z1);
        glVertex3f (x2, y2, z2);
        glEnd();
    }
    myfile.close();
    
    
    /*glBegin(GL_LINES);
    glColor3f  (1.0, 0.0,  0.0);
    glVertex3f (0.0, 0.0, 0.0);
    glVertex3f (10.0, 0.0, 0.0);
    
    glVertex3f (10.0, 0.0, 0.0);
    glVertex3f (10.0, 10.0, 0.0);
    
    glVertex3f (10.0, 10.0, 0.0);
    glVertex3f (10.0, 35.0, 0.0);
    
    glVertex3f (10.0, 35.0, 0.0);
    glVertex3f (10.0, 50.0, 0.0);
    
    glVertex3f (10.0, 50.0, 0.0);
    glVertex3f (35.0, 50.0, 0.0);
    
    glVertex3f (35.0, 50.0, 0.0);
    glVertex3f (35.0, 130.0, 0.0);
    
    glVertex3f (35.0, 130.0, 0.0);
    glVertex3f (100.0, 130.0, 0.0);
    
    glVertex3f (100.0, 130.0, 0.0);
    glVertex3f (126.0, 130.0, 0.0);
    
    glVertex3f (126.0, 130.0, 0.0);
    glVertex3f (126.0, 170.0, 0.0);
    
    glVertex3f (126.0, 170.0, 0.0);
    glVertex3f (126.0, 210.0, 0.0);
    
    glVertex3f (126.0, 210.0, 0.0);
    glVertex3f (126.0, 223.0, 0.0);
    
    glVertex3f (126.0, 223.0, 0.0);
    glVertex3f (126.0, 240.0, 0.0);
    
    glVertex3f (126.0, 240.0, 0.0);
    glVertex3f (165.0, 240.0, 0.0);
    
    glEnd();*/
    
    
}

//---+----3----+----2----+----1----+---<>---+----1----+----2----+----3----+----4

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