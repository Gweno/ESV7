//----------- DataFile.h-----------

#ifndef DATAFILE_H
#define DATAFILE_H

#include <string>
#include <string.h>
#include "Entity.h"

class dataFile : public Entity {
      public:
             dataFile();//Declare constructor w/o parameters
             dataFile(int);
             ~dataFile();//Declare Destructor
             static void saveFile(unsigned int nbEntity);
             static void saveFileEntity(unsigned int nbEntity);
             static void saveFileFromGL(const char* FileName);
             static void menuFile();
             static void loadFile(char menuChoice);
             static void enterData(unsigned int menuChoice);             
             static void enterDataMultiLevel();
             static void enterLayer();
             static void mergeEntity();
             static void listFile();
             static void searchFile(std::string curr_directory, std::string extension);
             static void displayEntity();
             static void toEntity (Entity objEntity);
             static void dataFiletoGlEntity();

//             static void toGlEntity (glEntity objEntity);
             static void insertEntity(int input);
             static void loadDefault();
             static void resetDataFile();
             static void deleteEntity(int reference, unsigned int option_delete);
             static void firstLine(char* FileNameIn); // to be improved with pointers
             static void assignIndex();
//             static void storeDataFromFile(char* FileNameIn);
             static void storeDataFromFile();
             static void data_to_Entity();


      public:

             static int file_size;         // parameter for the size of the Dynamic Array            
             static char menuKeyChoice;
         	static std::vector<std::string> storeDataText;

      };

#endif
