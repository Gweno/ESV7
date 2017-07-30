//------------glEntity.h--------------
#ifndef GLENTITY_H
#define GLENTITY_H

#include <GL/freeglut.h>
#include "Entity.h"
#include "DataFile.h"



class glEntity : public Entity {
      public:
             glEntity();//Declare constructor w/o parameters
             ~glEntity();//Declare Destructor

             static void initEntity();
             static void drawEntity();
             static void UpdateEntity();
             static void displayEntity(void);
             static void reshapeEntity(int w, int h);

             static void keyDown(unsigned char key, int x, int y);
             static void mouseMovement(int x, int y);
             static void mouseMovement_Rclick(int x, int y);
             static void camera (void);
             static void entityMovement(int x, int y);
             static void loadEntity();
             static void resetIterEntity();
             static void drawString (void * font, char *s, float x, float y, float z);
             static void mouseMotionForGlut(int x, int y);
             static void console();
             static void drawAxes(GLdouble length);
             static void entityVertex_Lines();
             static void fixEntity();
             static void newGlEntity();
             static void copyEntity();
             static void deleteGlEntity();
             static void coordinate_glEntity();
             static void dataToGl(dataFile);
             static void glCoordinateToGlEntity_All();
             static void glCoordinateToGlEntity(unsigned int iterEntity);
             static void process_move(int x, int y);

      public:

             static int array_size;         // parameter for the size of the Dynamic Array
             static char keyChoice;
             static GLfloat MatSpec[];
             static GLfloat MatShininess[];
             static GLfloat LightPos[];
             static unsigned int iterEntity;

            static std::vector<int> structureEntity;             //MEMBER0: flag 0 if direct value; flag 1 if structure
            static std::vector<unsigned int>  typeEntity;          //MEMBER1: the type of the entity
            static std::vector<unsigned int>  nbChildren;          //MEMBER2: number of dependants
            static std::vector<unsigned int> masterEntity;        //MEMBER3: address of the Entity from which this Entity depends
         	static std::vector<int> layerEntity;                  //MEMBER4: Layer or level of this Entity
         	static std::vector<double> valueEntity;               //MEMBER5: The basic value of Entity is of type 'double' for now
         	static std::vector<std::string> textEntity;



// 02/08/2012
// public members
//               public:

                 static std::vector<double> Xpos;
                 static std::vector<double> Ypos;
                 static std::vector<double> Zpos;
                 static std::vector<double> Xmov;
                 static std::vector<double> Ymov;
                 static std::vector<double> Zmov;
                 static std::vector<double> Xacc;
                 static std::vector<double> Yacc;
                 static std::vector<double> Zacc;
                 static std::vector<float> fRed;
                 static std::vector<float> fGreen;
                 static std::vector<float> fBlue;
                 static std::vector<float> fAlpha;
//                 static std::vector<std::string> text_Entity;
//                 static std::vector<std::vector<unsigned int> > parent;
//                 static std::vector<std::vector<unsigned int> > child;
//                 static std::vector<std::vector<unsigned int> > sibling;



      };

#endif
