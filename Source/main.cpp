// ------------------------main.cpp-------------------

#define GLUT_DISABLE_ATEXIT_HACK 
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "Entity.h"
#include "glEntity.h"
#include "DataFile.h"

using namespace std;

int main (int argc, char **argv) {

   	glEntity tata;

    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize (800, 600);
    glutInitWindowPosition (700, 300);
    glutCreateWindow ("Universe");
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
                  GLUT_ACTION_CONTINUE_EXECUTION);

    tata.initEntity();

    glutDisplayFunc (tata.displayEntity);
    glutIdleFunc (tata.displayEntity);
    glutReshapeFunc (tata.reshapeEntity);

    cout << "in the OpenGL loop";
    //Lighting stuff:      option 2
    glShadeModel(GL_SMOOTH);	//GL_FLAT would look much worse
    glEnable(GL_DEPTH_TEST);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tata.MatSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, tata.MatShininess);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glutPassiveMotionFunc(tata.mouseMovement); //check for Mouse movement with button up
    glutMotionFunc(tata.mouseMovement_Rclick); //check for Mouse movement with button down
    std::cout << "before glutKeyboardFunc ";
    glutKeyboardFunc(tata.keyDown);
    std::cout << "after glutKeyboardFunc ";
    glutMainLoop ();

   exit(0);
}


