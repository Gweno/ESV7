//------------- glEntity.cpp-----------

#define GLUT_DISABLE_ATEXIT_HACK 
//#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
//#include <QtOpenGL>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include <string>

#include "Entity.h"
#include "glEntity.h"

#include "DataFile.h"

using namespace std;

//Init Static member from glEntity

int glEntity::array_size;
char glEntity::keyChoice;
bool text_input_on=false;
bool cameraMoveEnable=false;
bool entityMoveEnable=false;
bool displayMenu=false;
bool mouse=false;
bool mouse_button_down=false;
bool mouseMove = false;
bool keyboard=false;
std::string input_text;

//int maxCol = 10;
char storeNameGl[10][24];

std::vector<double> glEntity::Xpos;
std::vector<double> glEntity::Ypos;
std::vector<double> glEntity::Zpos;
std::vector<float> glEntity::fRed;
std::vector<float> glEntity::fGreen;
std::vector<float> glEntity::fBlue;
std::vector<float> glEntity::fAlpha;
std::vector<int> glEntity::structureEntity;             //MEMBER0: flag 0 if direct value; flag 1 if structure
std::vector<unsigned int>  glEntity::typeEntity;          //MEMBER1: the type of the entity
std::vector<unsigned int>  glEntity::nbChildren;          //MEMBER2: number of dependants
std::vector<unsigned int> glEntity::masterEntity;        //MEMBER3: address of the Entity from which this Entity depends
std::vector<int> glEntity::layerEntity;                  //MEMBER4: Layer or level of this Entity
std::vector<double> glEntity::valueEntity;               //MEMBER5: The basic value of Entity is of type 'double' for now
std::vector<std::string> glEntity::textEntity;



//std::vector<string> vector_swap_glTextEntity;


/*
TVector* ColEntity::ArrayVel;                     //holds velocity of Entities
TVector* ColEntity::ArrayPos;                     //position of Entities
TVector* ColEntity::OldPos; 
*/

// init for  lighting
bool LightEnabled = true;

GLfloat glEntity::MatSpec[] = {1.0,1.0,1.0,1.0};
GLfloat glEntity::MatShininess[] = {128.0};
GLfloat glEntity::LightPos[] = {-1.0,1.0,0.0,0.0};

// init for camera
float xpos_m = 0, ypos_m = 0, zpos_m = 0, xrot_m = 0, yrot_m = 0, angle=0.0;
float xpos_k = 0, ypos_k = 0, zpos_k = 0, xrot_k = 0, yrot_k = 0;

//float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle=0.0;
float xpos2 = 0, ypos2 = 0, zpos2 = 0, xrot2 = 0, yrot2 = 0, angle2=0.0;


float lastx, lasty;
float lastx2, lasty2;

float red=1, green=0, blue=0;

// init for iterator for Moving Entity
unsigned int glEntity::iterEntity=0;

const unsigned char tmp[10] = "Entity";

//init the char array for text display:
char gMouseXLoc[20];
char gMouseYLoc[20];
char ePrintAll[20][100];
float x_text=1;
float y_text=1;
float z_text=1;

//Entity newToto;

GLfloat matrix[16];

//Init all method from glEntity including constructors, destructors, static and non-static methodes

// Constructors

glEntity::glEntity(){
	newGlEntity();
	glCoordinateToGlEntity(0);
}

// Destructor

glEntity::~glEntity(){}

// --------init functions--------

void glEntity::drawAxes(GLdouble length)
{
	  // Draw a red x-axis, a green y-axis, and a blue z-axis.  Each of the
	  // axes are ten units long.
	  glBegin(GL_LINES);
	    glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(length, 0, 0);
	    glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, length, 0);
	    glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, length);
	  glEnd();

	  glFlush();
	}

void glEntity::entityVertex_Lines()
{

	glBegin(GL_LINE_STRIP);
	glColor3f(1, 0, 0);
	for (int i = 0; i < int(Xpos.size()); i++)
	    {
		glVertex3d(Xpos.at(i), Ypos.at(i),Zpos.at(i));
	    }
	glVertex3d(Xpos.at(0), Ypos.at(0),Zpos.at(0));
	glEnd();
	glFlush();
	}

void glEntity::UpdateEntity(){

		Xpos.at(iterEntity)=double(xpos2);
		Ypos.at(iterEntity)=double(ypos2);
		Zpos.at(iterEntity)=double(zpos2);

}

// pass object ob from class entity as paramameter to the function
void glEntity::drawEntity(){

//double XposCumul;


for (int i = 0; i < int(Xpos.size()); i++)
    {

	glPushMatrix();
    glTranslatef (Xpos.at(i), Ypos.at(i),Zpos.at(i));
    glEnable (GL_BLEND);
    glEnable(GL_COLOR_MATERIAL);
//    glColor4f(red, green, blue, 1.0f);
    glColor4f(fRed.at(i), fGreen.at(i), fBlue.at(i), fAlpha.at(i));
    glutSolidSphere (0.3,20,20);

    glRasterPos2i(-2, -2);
    glColor4f(0, 1, 0, 1.0f);


    sprintf(ePrintAll[0], "index:%i",i);
    sprintf(ePrintAll[1], "x:%2.3f",Xpos.at(i));
    sprintf(ePrintAll[2], "y:%2.3f",Ypos.at(i));
    sprintf(ePrintAll[3], "z:%2.3f",Zpos.at(i));
    drawString(GLUT_BITMAP_HELVETICA_18, ePrintAll[0], x_text, y_text, z_text);
    drawString(GLUT_BITMAP_HELVETICA_18, ePrintAll[1], x_text, y_text-0.5, z_text);
    drawString(GLUT_BITMAP_HELVETICA_18, ePrintAll[2],x_text, y_text-1, z_text);
    drawString(GLUT_BITMAP_HELVETICA_18, ePrintAll[3],x_text, y_text-1.5, z_text);

	if (textEntity.size()>0) {
		sprintf (ePrintAll[4], "text:%s",textEntity.at(i).c_str());
	    drawString(GLUT_BITMAP_HELVETICA_18, ePrintAll[4], x_text, y_text-2.0, z_text);
	}



    glPopMatrix();
}

}


void glEntity::fixEntity(void){
	/// testing fixed object
		glPushMatrix();

if (mouse){
    glRotatef(-yrot_m,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
    glRotatef(-xrot_m,1.0,0.0,0.0);  //rotate our camera on the x-axis (left and right)
    glTranslated(-xpos_m,-ypos_m,-zpos_m); //translate the screen to the position of our camera
}

if (keyboard){
	glRotatef(-yrot_k,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
	glRotatef(-xrot_k,1.0,0.0,0.0);  //rotate our camera on the x-axis (left and right)
    glTranslated(xpos_k,ypos_k,zpos_k); //translate the screen to the position of our camera
}

	    glTranslated(-5.0, 3.0, 1.0); //translate the screen to the position
	    glEnable (GL_BLEND);
	    glEnable(GL_COLOR_MATERIAL);
	    glColor4f(1.0, 1.0, 1.0f, 1.0f);
	    glutSolidCube (0.3);
	    sprintf(ePrintAll[6], "Mouse xrot:%2.3f yrot:%2.3f",xrot_m,yrot_m);
	    sprintf(ePrintAll[7], "Mouse xpos:%2.3f ypos:%2.3f ypos:%2.3f",xpos_m,ypos_m,zpos_m);
	    sprintf(ePrintAll[8], "KeyBoard xrot:%2.3f yrot:%2.3f",xrot_k,yrot_k);
	    sprintf(ePrintAll[9], "KeyBoard xpos:%2.3f ypos:%2.3f ypos:%2.3f",xpos_k,ypos_k,zpos_k);

	    drawString(GLUT_BITMAP_HELVETICA_12, ePrintAll[6],x_text, y_text-0.25, z_text);
	    drawString(GLUT_BITMAP_HELVETICA_12, ePrintAll[7],x_text, y_text-0.5, z_text);
	    drawString(GLUT_BITMAP_HELVETICA_12, ePrintAll[8],x_text, y_text-0.75, z_text);
	    drawString(GLUT_BITMAP_HELVETICA_12, ePrintAll[9],x_text, y_text-1, z_text);

	    sprintf(ePrintAll[10], "cameraMoveEnable :%d",cameraMoveEnable);
	    sprintf(ePrintAll[11], "mouse :%d",mouse);
	    sprintf(ePrintAll[12], "keyboard :%d",keyboard);
	    sprintf(ePrintAll[13], "displayMenu :%d",displayMenu);
	    sprintf(ePrintAll[14], "text_input_on :%d",text_input_on);
	    sprintf(ePrintAll[15], "entityMoveEnable :%d",entityMoveEnable);

	    drawString(GLUT_BITMAP_HELVETICA_12, ePrintAll[10],x_text, y_text-1.5, z_text);
	    drawString(GLUT_BITMAP_HELVETICA_12, ePrintAll[11],x_text, y_text-1.75, z_text);
	    drawString(GLUT_BITMAP_HELVETICA_12, ePrintAll[12],x_text, y_text-2.0, z_text);
	    drawString(GLUT_BITMAP_HELVETICA_12, ePrintAll[13],x_text, y_text-2.25, z_text);
	    drawString(GLUT_BITMAP_HELVETICA_12, ePrintAll[14],x_text, y_text-2.5, z_text);
	    drawString(GLUT_BITMAP_HELVETICA_12, ePrintAll[15],x_text, y_text-3.0, z_text);

	    sprintf(ePrintAll[16], "Input Text :");
	    drawString(GLUT_BITMAP_HELVETICA_18, ePrintAll[16],x_text, y_text-4, z_text);
	    drawString(GLUT_BITMAP_HELVETICA_18, ePrintAll[5],x_text, y_text-4.5, z_text);

	    sprintf(ePrintAll[17], "Entity selected : %i",glEntity::iterEntity);
	    drawString(GLUT_BITMAP_HELVETICA_18, ePrintAll[17],x_text, y_text-5, z_text);



	    glPopMatrix();
}


void glEntity::console(void) {
	glPushMatrix();


//    glTranslatef (-matrix[2]+xpos, -matrix[8]+ypos, -matrix[12]+zpos);
//    glEnable (GL_BLEND);
//    glEnable(GL_COLOR_MATERIAL);
//    glColor4f(red, green, blue, 1.0f);
//    glutSolidSphere (1.0,20,20);
    drawString(GLUT_BITMAP_HELVETICA_18, ePrintAll[2],0,0,0);


    glGetFloatv (GL_MODELVIEW_MATRIX, matrix);

	glPopMatrix();

}


void glEntity::displayEntity(void){
    glClearDepth (1);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
    glTranslatef (0,0,-10);
    camera();
    drawAxes(10);
    loadEntity();
    UpdateEntity();
    drawEntity();
    entityVertex_Lines();
    fixEntity();
    glutSwapBuffers();
}

void glEntity::reshapeEntity(int w, int h){
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode (GL_MODELVIEW);
}


void glEntity::initEntity(){
    glEnable(GL_DEPTH_TEST);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
}


void glEntity::camera (void) {
	//~ if (mouse) {
		glRotatef(xrot_m,1.0,0.0,0.0);  //rotate our camera on the x-axis (left and right)
		glRotatef(yrot_m,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
		glTranslated(xpos_m,ypos_m,zpos_m); //translate the screen to the position of our camera
	//~ }
	//~ if (keyboard){
		glRotatef(xrot_k,1.0,0.0,0.0);  //rotate our camera on the x-axis (left and right)
		glRotatef(yrot_k,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
		glTranslated(-xpos_k,-ypos_k,-zpos_k); //translate the screen to the position of our camera
	//~ }
		glFlush();
	}

void glEntity::mouseMovement(int x, int y) {
	mouse_button_down = false;
	mouseMove = true;
	process_move(x,y);
	}
	
void glEntity::mouseMovement_Rclick(int x, int y){
	mouse_button_down = true;
	mouseMove = true;
	process_move(x,y);
	}

void glEntity::process_move(int x, int y){
	unsigned char key;
	float xrotrad, yrotrad;
	
	std::cout << "process_move x y"  << x << "," << y << std::endl;
	std::cout << "process_move cameraMoveEnable"  << cameraMoveEnable << std::endl;
	std::cout << "process_move  keyboard"  << keyboard << std::endl;
	
	if ((cameraMoveEnable) and mouseMove and !(mouse_button_down)){
		mouse = true;
		keyboard = false;
		float diffx=x-lastx; //check the difference between the current x and the last x position
		float diffy=y-lasty; //check the difference between the current y and the last y position
		lastx=x; //set lastx to the current x position
		lasty=y; //set lasty to the current y position
		xrot_m += (float) diffy; //set the xrot to xrot with the addition of the difference in the y position
		yrot_m += (float) diffx;    //set the xrot to yrot with the addition of the difference in the x position
		if (xrot_m >360) xrot_m -= 360;
		if (xrot_m < -360) xrot_m += 360;
		if (yrot_m >360) yrot_m -= 360;
		if (yrot_m < -360) yrot_m += 360;
		std::cout<<"move" << std::endl;
	}

	if ((cameraMoveEnable) and mouseMove and mouse_button_down){
		mouse = true;
		keyboard = false;
		float diffx=x-lastx; //check the difference between the current x and the last x position
		float diffy=y-lasty; //check the difference between the current y and the last y position
		lastx=x; //set lastx to the current x position
		lasty=y; //set lasty to the current y position
		if(diffx<0) xpos_m += ((float) diffx-250)/500;
		if(diffx>0) xpos_m += (250-(float) diffx)/500;
		if(diffy<0) ypos_m += (250-(float) diffy)/500;
		if(diffy>0) ypos_m += ((float) diffy-250)/500;
		std::cout<<"button_down" << std::endl;
	}
	
		if ((entityMoveEnable) and mouseMove and !(mouse_button_down)){
		float diffx=x-lastx; //check the difference between the current x and the last x position
		float diffy=y-lasty; //check the difference between the current y and the last y position
		lastx=x; //set lastx to the current x position
		lasty=y; //set lasty to the current y position
		if(diffx<0) xpos2 += ((float) diffx-250)/500;
		if(diffx>0) xpos2 += (250-(float) diffx)/500;
		if(diffy<0) ypos2 += (250-(float) diffy)/500;
		if(diffy>0) ypos2 += ((float) diffy-250)/500;
	}

	if (cameraMoveEnable and keyboard){
		mouse = false;
		keyboard = true;
		key = glEntity::keyChoice;
		std::cout << "key: " << key << std::endl;
		std::cout << "xrot_m(0): " << xrot_m << std::endl;
		std::cout << "yrot_m(0): " << yrot_m << std::endl;
		
		
			switch(key)
			{
			case 'q':
				xrot_m += 1;
				if (xrot_m >360) xrot_m -= 360;
			break;

			case 'z':
				xrot_m -= 1;
				if (xrot_m < -360) xrot_m += 360;
			break;

			case 'e':
				yrot_m += 1;
				if (yrot_m >360) yrot_m -= 360;
			break;

			case 'r':
				yrot_m -= 1;
				if (yrot_m < -360) yrot_m += 360;
			break;


			case 'w':
				yrotrad = (yrot_m / 180 * 3.141592654f);
				xrotrad = (xrot_m / 180 * 3.141592654f);
				xpos_m += float(sin(yrotrad)) ;
				zpos_m -= float(cos(yrotrad)) ;
				ypos_m -= float(sin(xrotrad)) ;
			break;

			case 's':
				yrotrad = (yrot_m / 180 * 3.141592654f);
				xrotrad = (xrot_m / 180 * 3.141592654f);
				xpos_m -= float(sin(yrotrad));
				zpos_m += float(cos(yrotrad)) ;
				ypos_m += float(sin(xrotrad));
				break;

			case 'd':
				yrotrad = (yrot_m / 180 * 3.141592654f);
				xpos_m += float(cos(yrotrad)) * 0.2;
				zpos_m += float(sin(yrotrad)) * 0.2;
				break;

			case'a':
				yrotrad = (yrot_m / 180 * 3.141592654f);
				xpos_m -= float(cos(yrotrad)) * 0.2;
				zpos_m -= float(sin(yrotrad)) * 0.2;
				break;

			case 'l':
				LightEnabled = !LightEnabled;
				if (LightEnabled) glEnable(GL_LIGHTING);
					else glDisable(GL_LIGHTING);
			break;
		}
		std::cout << "xrot_m(1): " << xrot_m << std::endl;
		std::cout << "yrot_m(1): " << yrot_m << std::endl;

	}

}

void glEntity::keyDown(unsigned char key, int x, int y)
//Note: because there is an Idle-func, we don't have to call Display here
{
    //~ float xrotrad, yrotrad;
	glEntity::keyChoice=key;
	std::cout << "cameraMoveEnable"  << cameraMoveEnable << std::endl;
	
	if (!text_input_on){

		switch(key)
		{
		case 'c':
			displayMenu=false; //change switch position;
			cameraMoveEnable=!cameraMoveEnable;  //force switch;
			entityMoveEnable=false;
			text_input_on=false;
		break;

		case 'y':
			displayMenu=false; //change switch position;
			cameraMoveEnable=false; //force switch;
			entityMoveEnable=!entityMoveEnable;	//force switch;
			text_input_on=false;
		break;

		case 'm':
			displayMenu=!displayMenu; //change switch position;
			cameraMoveEnable=false; //force switch;
			entityMoveEnable=false;	//force switch;
			text_input_on=false;
		break;

		case 27:	//ESC to exit program
			exit(0);
		break;


		default:
		break;
		}
		if (cameraMoveEnable) {
			
			mouse = false;
			keyboard = true;
			std::cout << "key2 x y"  << x << "," << y << std::endl;				
			mouseMove = false;
			mouse_button_down = false;
			process_move(x,y);
		}
				
		if (entityMoveEnable) {
			switch (key){
				case',':
					xpos2 -= 1;
				break;

				case'.':
					xpos2 += 1;
				break;

				case'k':
					ypos2 -= 1;
				break;

				case'o':
					ypos2 += 1;
				break;

				case'/':
					zpos2 -= 1;
				break;

				case';':
					zpos2 += 1;
				break;

				case'-':
					if (glEntity::iterEntity!=0) glEntity::iterEntity-=1;
						xpos2=Xpos.at(glEntity::iterEntity);
						ypos2=Ypos.at(glEntity::iterEntity);
						zpos2=Zpos.at(glEntity::iterEntity);
						for (unsigned int i = 0; i < (unsigned int)(Xpos.size()); i++)
							{
							if(i!=glEntity::iterEntity){
								glEntity::fRed.at(i)=1.0;
					//			glEntity::fGreen.at(i)=0.0;
								glEntity::fBlue.at(i)=0.0;
								glEntity::fAlpha.at(i)=0.0;
							}
							}
						glEntity::fRed.at(glEntity::iterEntity)=0.0;
			//			glEntity::fGreen.at(glEntity::iterEntity)=0.0;
						glEntity::fBlue.at(glEntity::iterEntity)=1.0;
						glEntity::fAlpha.at(glEntity::iterEntity)=1.0;
						break;

				case'=':
						if (glEntity::iterEntity<Xpos.size()-1) glEntity::iterEntity+=1;
						xpos2=Xpos.at(glEntity::iterEntity);
						ypos2=Ypos.at(glEntity::iterEntity);
						zpos2=Zpos.at(glEntity::iterEntity);
						for (unsigned int i = 0; i < (unsigned int)(Xpos.size()); i++)
							{
							if(i!=glEntity::iterEntity){
						glEntity::fRed.at(i)=1.0;
			//			glEntity::fGreen.at(i)=0.0;
						glEntity::fBlue.at(i)=0.0;
						glEntity::fAlpha.at(i)=0.0;
							}
							}
						glEntity::fRed.at(glEntity::iterEntity)=0.0;
			//			glEntity::fGreen.at(glEntity::iterEntity)=0.0;
						glEntity::fBlue.at(glEntity::iterEntity)=1.0;
						glEntity::fAlpha.at(glEntity::iterEntity)=1.0;
						break;
			}
		}

		if (displayMenu){

			switch (key)
			{
				case'r':
			//      Return to main menu
				glutLeaveMainLoop();
				break;

				case 'n':									//new
					glEntity::newGlEntity();
					glEntity::iterEntity=0;
					glCoordinateToGlEntity(iterEntity);
			//    	glEntity::iterEntity=Xpos.size()-1;
					text_input_on = true;
					break;

				case 'v':									//copy
					glEntity::copyEntity();
					glCoordinateToGlEntity(iterEntity);
					if ( glEntity::Xpos.size()!=0 ) {
							glEntity::iterEntity=Xpos.size()-1;
						}
					else {
								glEntity::iterEntity=0;
						};
					text_input_on = true;
				break;

				case 'b':								//delete
					glEntity::deleteGlEntity();
					glEntity::deleteEntity(iterEntity);
					glEntity::iterEntity=0;
				break;

			}
		}

	}	// end of 'when text_input_on is off'

	else {			// when text_input is on

		if (key!=char(13)){
			input_text.push_back(key);
//	    	sprintf (ePrintAll[0], "test");
	    	sprintf (ePrintAll[5], "%s",input_text.c_str());
		}
		else{
			text_input_on = false;
//	    	glEntity::copyEntity();
	    	glEntity::textEntity.pop_back();
	    	glEntity::textEntity.push_back(input_text);
	    	std::cout << input_text << std::endl;
			input_text="";
		}

	}	// end of 'when text_input is on' (else)
}

// Test to move Entity 1 with the mouse
void glEntity::entityMovement(int x, int y) {
	if (entityMoveEnable) {
    float diffx=x-lastx; //check the difference between the current x and the last x position
    float diffy=y-lasty; //check the difference between the current y and the last y position
    lastx=x; //set lastx to the current x position
    lasty=y; //set lasty to the current y position
    if(diffx<0) xpos2 += ((float) diffx-250)/500;
    if(diffx>0) xpos2 += (250-(float) diffx)/500;
    if(diffy<0) ypos2 += (250-(float) diffy)/500;
    if(diffy>0) ypos2 += ((float) diffy-250)/500;
//    double xloc = x;
//    sprintf(gMouseXLoc, "%2.15f", xloc);

//    glTranslated(-xpos,-ypos,-zpos); //translate the screen to the position of our camera
	}
}


void::glEntity::coordinate_glEntity(){

	glEntity::Xpos.clear();
	glEntity::Ypos.clear();
	glEntity::Zpos.clear();
	glEntity::fRed.clear();
	glEntity::fGreen.clear();
	glEntity::fBlue.clear();
	glEntity::fAlpha.clear();

		    	for (int i=0;i<int(valueEntity.size());i++){
		    		glEntity::Xpos.push_back(valueEntity.at(i)*1.0);
		    		glEntity::Ypos.push_back(layerEntity.at(i)*1.0);
		    		glEntity::Zpos.push_back(masterEntity.at(i)*1.0);
					glEntity::fRed.push_back(1.0);
					glEntity::fGreen.push_back(0.0);
					glEntity::fBlue.push_back(0.0);
					glEntity::fAlpha.push_back(1.0);
			}
}


void::glEntity::glCoordinateToGlEntity_All(){
	valueEntity=glEntity::Xpos;
    for (unsigned int i=0; i<glEntity::valueEntity.size();i++){
    	layerEntity.at(i)=int(glEntity::Ypos.at(i));
    	masterEntity.at(i)=int(glEntity::Zpos.at(i));
    	typeEntity.at(i)=0;
    	nbChildren.at(i)=0;
    	masterEntity.at(i)=0;

    }

}

void::glEntity::glCoordinateToGlEntity(unsigned int iterEntity){
	valueEntity.push_back(glEntity::Xpos.at(iterEntity));
	layerEntity.push_back(int(glEntity::Ypos.at(iterEntity)));
	masterEntity.push_back(int(glEntity::Zpos.at(iterEntity)));
	typeEntity.push_back(iterEntity);
	nbChildren.push_back(iterEntity);
	masterEntity.push_back(iterEntity);

}


void glEntity::loadEntity() {
	if ( (!text_input_on) && displayMenu) {

//	if ( (!text_input_on) && displayMenu && (glEntity::keyChoice=='t') ){
		if (glEntity::keyChoice=='t'){
		dataFile dataGlEntity(0);
		glEntity::resetIterEntity();
		dataGlEntity.loadFile('t');
		dataToGl(dataGlEntity);
		coordinate_glEntity();
		glEntity::keyChoice='\0';
	}
//	if( (!text_input_on)  && displayMenu && glEntity::keyChoice=='1'){
		if(glEntity::keyChoice=='1'){
		dataFile dataGlEntity(0);
		dataGlEntity.loadFile('1');
		glEntity::resetIterEntity();
		dataToGl(dataGlEntity);
		coordinate_glEntity();
		glEntity::keyChoice='\0';
	}
//	if( (!text_input_on)  && displayMenu && glEntity::keyChoice=='2'){
	if(glEntity::keyChoice=='2'){
		glEntity::resetIterEntity();
		dataFile dataGlEntity(0);
		dataGlEntity.loadFile('2');
		dataToGl(dataGlEntity);
		coordinate_glEntity();
		glEntity::keyChoice='\0';
	}

//	if ( (!text_input_on) && displayMenu && (glEntity::keyChoice=='s') ){
	if(glEntity::keyChoice=='s'){
		dataFile dataGlEntity(0);
	    glCoordinateToGlEntity_All();
//		dataGlEntity.saveFileFromGL("test01.csv");
	    dataGlEntity.saveFileFromGL("test01");
		glEntity::keyChoice='\0';
	}

}
}

void::glEntity::resetIterEntity(){
	glEntity::iterEntity=0;
}

/* test */


void::glEntity::drawString (void * font, char *s, float x, float y, float z){
     unsigned int i;
//     glTranslatef (X, Y, Z);
     glRasterPos3f(x, y, z);

     for (i = 0; i < strlen (s); i++)
          glutBitmapCharacter (font, s[i]);
}

void::glEntity::mouseMotionForGlut(int x, int y){
     double xloc = x;
     double yloc = y;
     sprintf(gMouseXLoc, "x:%2.3f", xloc);
     sprintf(gMouseYLoc, "y:%2.3f", yloc);
}


void::glEntity::newGlEntity(){
	glEntity::Xpos.push_back(0);
	glEntity::Ypos.push_back(0);
	glEntity::Zpos.push_back(0);
	glEntity::fRed.push_back(1.0);
	glEntity::fGreen.push_back(0.0);
	glEntity::fBlue.push_back(0.0);
	glEntity::fAlpha.push_back(1.0);
	glEntity::textEntity.push_back("Enter Text");

}
void::glEntity::copyEntity(){
	glEntity::Xpos.push_back(glEntity::Xpos.at(iterEntity));
	glEntity::Ypos.push_back(glEntity::Ypos.at(iterEntity));
	glEntity::Zpos.push_back(glEntity::Zpos.at(iterEntity));
	glEntity::fRed.push_back(1.0);
	glEntity::fGreen.push_back(0.0);
	glEntity::fBlue.push_back(0.0);
	glEntity::fAlpha.push_back(1.0);
	glEntity::textEntity.push_back("Enter Text");
}

void::glEntity::deleteGlEntity(){
	unsigned int iterator =glEntity::iterEntity;
	if (glEntity::Xpos.size()>1){

	glEntity::Xpos.erase(glEntity::Xpos.begin() + iterator);
	glEntity::Ypos.erase(glEntity::Ypos.begin() + iterator);
	glEntity::Zpos.erase(glEntity::Zpos.begin() + iterator);
	glEntity::fRed.erase(glEntity::fRed.begin() + iterator);
	glEntity::fGreen.erase(glEntity::fGreen.begin() + iterator);
	glEntity::fBlue.erase(glEntity::fBlue.begin() + iterator);
	glEntity::fAlpha.erase(glEntity::fAlpha.begin() + iterator);

	glEntity::textEntity.erase(glEntity::textEntity.begin() + iterator);
	}

}

void glEntity::dataToGl (dataFile objData){
		structureEntity=objData.structureEntity;
		typeEntity=objData.typeEntity;
		nbChildren=objData.nbChildren;
		masterEntity=objData.masterEntity;
		layerEntity=objData.layerEntity;
		valueEntity=objData.valueEntity;
		textEntity=objData.storeDataText;
}
