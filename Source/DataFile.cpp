//----------------DataFile.cpp--------
//01/08/2012 replace Entity by glEntit7


#include <fstream>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <cstdlib>
#include "Entity.h"
#include "glEntity.h"
#include "DataFile.h"
#include<dirent.h>

#include <errno.h>


using namespace std;

//glEntity* obj2;
int dataFile::file_size;
char dataFile::menuKeyChoice;
std::vector<std::string> dataFile::storeDataText;

//int* nb_glEntity;
std::vector<std::string> results;// holds search results
int input;

char storeName[10][24];
unsigned int* indexMembers = new unsigned int[6];

//int* nb_row;
//
//double** storeData= new double*[10];
char storeText[10][10];

//double** storeData= new double*[*nb_row];
//char *lineText = new char[10];
//char *storeText = new lineText[*nb_row];

//DIR* dir_point;
//dirent* entry;


std::vector<int> Entity::structureEntity;             //MEMBER0: flag 0 if direct value; flag 1 if structure
std::vector<unsigned int>  Entity::typeEntity;          //MEMBER1: the type of the entity
std::vector<unsigned int>  Entity::nbChildren;          //MEMBER2: number of dependants
std::vector<unsigned int> Entity::masterEntity;        //MEMBER3: address of the Entity from which this Entity depends
std::vector<int> Entity::layerEntity;
std::vector<double> Entity::valueEntity;
std::vector<string> Entity::textEntity;

std::vector<string> vector_swap_dataTextEntity;


void dataFile::menuFile()

{
     char menuChoice, menuChoiceSave;
     
//     nb_glEntity = new int;
//     obj2 = new glEntity[*nb_glEntity];

     std::cout << "******************************\n";
     std::cout << "*      Entity Project        *\n";
     std::cout << "******************************\n";
     std::cout << "\n";
     std::cout << "Main Menu\n";
     std::cout << "\n";
     std::cout << "1- Load default file\n";
     std::cout << "2- Enter Data\n";
     std::cout << "3- Load an exiting file\n";
     std::cout << "4- Enter Energy Values\n";
     std::cout << "5- Enter Entities by layer\n";
     std::cout << "6- Load an Entity with layers\n";
     std::cout << "7- List all stored Entities\n";
     std::cout << "8- Display Entities in Main console\n";
     std::cout << "9- Merge 2 Entities\n";
     std::cout << "d- delete Entity\n";
     std::cout << "q- Quit program\n";
     std::cout << "\n";
     std::cout << "Your choice?\n";
     std::cin >> menuChoice;


	switch (menuChoice)
	{


           case '3':
           case '6':
                dataFile::listFile();
           case 't':
           case '1':
                dataFile::loadFile(menuChoice);
                break;                 
                                
           case '2':
           case '4':
           case '5':        
                dataFile::enterData(menuChoice);
                std::cout << "Do you want to save your Data? (y/n) "  << std::endl;
                std::cin >> menuChoiceSave;
                if (menuChoiceSave=='y')
                dataFile::saveFileEntity(file_size);
                break;
           case '7':
                dataFile::listFile();
//                dataFile::loadFile(menuChoice);
                break;
           case '8':
                dataFile::listFile();
                dataFile::loadFile(menuChoice);
                dataFile::displayEntity();
                break;
           case '9':
        	   	std::cout << "Select the First Entity" << std::endl;
                dataFile::listFile();
                dataFile::loadFile('8');
                dataFile::displayEntity();
        	   	std::cout << "What element is parent of the Second Entity?" << std::endl;
        	   	std::cin >> input;
        	   	std::cout << "Select the Second Entity" << std::endl;
                dataFile::listFile();
                dataFile::loadFile(menuChoice);
                dataFile::displayEntity();
                dataFile::saveFileEntity(file_size);
                break;
           case 'd':
        	   std::cout << "Select the Entity" << std::endl;
               dataFile::listFile();
               dataFile::loadFile('8');
               dataFile::displayEntity();
               std::cout << "What element do you want to delete?" << std::endl;
               std::cin >> input;
               dataFile::deleteEntity(input,'0');
               dataFile::displayEntity();
        	   	break;
           case 's':
               	dataFile::saveFileEntity(file_size);
        	   	break;
           case 'q':	//ESC
        	   	dataFile::menuKeyChoice=menuChoice;
                exit(0);
	            break;
           default:
                break;
    }
}

void dataFile::saveFile(unsigned int nbEntity)

{

    char *FileName = new char[20];
    char *FileNameOut = new char[24];    
    char *ExtensionCSV = new char[4];
    strcpy(ExtensionCSV,".csv");
    cout << "\nEnter the name of the file you want to create: ";
    cin >> FileName;
    FileNameOut = strcat(FileName, ExtensionCSV);
    ofstream fileEntity(FileNameOut, ios::out);    
    fileEntity << "Entity number,Xpos,Ypos,Zpos,Xmov,Ymov,Zmov,Xacc,Yacc,Zacc\n";
}

void dataFile::saveFileFromGL(const char* FileName)

{

    char *FileNameOut = new char[24];
    char *ExtensionCSV = new char[4];
    strcpy(ExtensionCSV,".csv");
    strcpy(FileNameOut,FileName);
    strcat(FileNameOut,ExtensionCSV);
    ofstream fileEntity(FileNameOut, ios::out);
    fileEntity << "Entity number,typeEntity,nbChildren,masterEntity,layerEntity,valueEntity,textEntity\n";
        for (unsigned int i=0; i<glEntity::valueEntity.size();i++){
        	            fileEntity << i << "," << glEntity::typeEntity.at(i) << "," << glEntity::nbChildren.at(i) << "," << glEntity::masterEntity.at(i) << ","
        	            << glEntity::layerEntity.at(i) << "," << glEntity::valueEntity.at(i) << "," << glEntity::textEntity.at(i) << "," <<"\n";
        }
}

void dataFile::saveFileEntity(unsigned int nbEntity)

{

    char *FileName = new char[20];
    char *FileNameOut = new char[75];
    char *ExtensionCSV = new char[4];
    char *Path = new char[50];
    FileNameOut[0]=0;				// to clear the array of Char
    strcpy(ExtensionCSV,".csv");
//    Path = "/home/gweno/Entity/";
    strcpy(Path,"/home/gweno/Entity/");
    cout << "\nEnter the name of the file you want to create: " << std::endl;
    cin >> FileName;

    strcat(FileNameOut, Path);
    strcat(FileNameOut,FileName);
    strcat(FileNameOut, ExtensionCSV);
    ofstream fileEntity(FileNameOut, ios::out);

    std:: cout << FileNameOut << std::endl;
    fileEntity << "Entity number,typeEntity,textEntity\n";
        for (unsigned int i=0; i<valueEntity.size();i++){

        	            fileEntity << i << "," << valueEntity.at(i) << "," << textEntity.at(i) <<"\n";
//        	            fileEntity << i << "," << valueEntity.at(i) <<"\n";
        }


//    for (unsigned int i=0; i<valueEntity.size();i++){
//
//    	            fileEntity << i << "," << typeEntity.at(i) << "," << nbChildren.at(i) << "," << masterEntity.at(i) << ","
//    	            << layerEntity.at(i) << "," << valueEntity.at(i) << "," << textEntity.at(i) << "," <<"\n";
//    }
}


//void dataFile::saveFileGlEntity(unsigned int nbEntity){
//
//    fileEntity << "Entity number,Xpos,Ypos,Zpos\n";
//    for (unsigned int i=0; i<valueEntity.size();i++){
//
//    }
//}

void dataFile::firstLine(char* FileNameIn){			 // to be improved with pointers
    char *bufferString1 = new char[20];
//    char *ExtensionCSV = new char[4];
    char *bufferChar;
//    int nb_column,nb_line;

    ifstream fileEntity;
    fileEntity.open(FileNameIn, ios::in);			//file should be open already

    int j=0;
//    int maxCol = 10;


    fileEntity.clear();                   // absolutly needed otherwise the file is flagged at eof, and good=0
    fileEntity.seekg(0, ios::beg);        // set cursor at 0 from start of file

//    char storeName[maxCol][24];

//  definition of 1D array and declaration des tableaux 1D elements de notre 1er tableau

    j=0;
//    while ((fileEntity.good()) && (!fileEntity.eof()))     // loop while extraction from file is possible
//          {
          fileEntity.getline(bufferString1, 100, '\n');           // store character strings between each ',' (comma) in bufferString (size max=100)
          bufferChar= strtok (bufferString1,",");
          while (bufferChar!=NULL){
         	  	  	  	  	  		strcpy(storeName[j],bufferChar);
        	  	  	  	  	  		bufferChar= strtok (NULL,",");
        	  	  	  	  	  		std::cout<<"1stline"<<storeName[j]<<std::endl;
        	  	  	  	  	  		j++;
          	  	  	  	  	  	  }

    fileEntity.close();           // close file

//          }
}

void dataFile::assignIndex()
{
for(int j=0;j<10;j++){
	std::cout << "assignIndex " << j << std::endl;
if(strcmp(storeName[j],"typeEntity")==0) indexMembers[0]=j;
else if(strcmp(storeName[j],"nbChildren")==0) indexMembers[1]=j;
else if(strcmp(storeName[j],"masterEntity")==0) indexMembers[2]=j;
else if(strcmp(storeName[j],"layerEntity")==0) indexMembers[3]=j;
else if(strcmp(storeName[j],"valueEntity")==0) indexMembers[4]=j;
else if(strcmp(storeName[j],"textEntity")==0) indexMembers[5]=j;
std::cout << "storeName[" << j << "]: " << storeName[j] << std::endl;

}
}



void dataFile::data_to_Entity(){

//
//for (int i=0;i<dataFile::file_size; i++){
//    std::cout << "Control 1 " << i << std::endl;
//    std::cout << "Nb Lines " << dataFile::file_size << std::endl;
//    			dataFile::typeEntity.push_back(storeData[i][1]);
//                dataFile::nbChildren.push_back(storeData[i][2]);
//                dataFile::masterEntity.push_back(storeData[i][3]);
//                dataFile::layerEntity.push_back(storeData[i][4]);
//                dataFile::valueEntity.push_back(storeData[i][5]);
//                dataFile::textEntity.push_back(storeText[i]);
//                std::cout << "control A" << std::endl;
//                std::cout << "valueEntity" << dataFile::valueEntity.at(0)<< std::endl;
//                std::cout << "typeEntity" << dataFile::typeEntity.at(0)<< std::endl;
//                std::cout << "textEntity" << dataFile::textEntity.at(0)<< std::endl;
//    }
}

void dataFile::loadFile(char menuChoice)

{
    unsigned int FileNum;
    char *FileName = new char[20];
    char *FileNameIn = new char[24];
    char *bufferString = new char[20];
    char *ExtensionCSV = new char[4];
    char *bufferChar;
    int nb_column, nb_line;
//    int maxCol = 10;

//    istream bufferStream(0);
    strcpy(ExtensionCSV,".csv");
//  number of columns corresponds to the number of members of Class to be stored
//    nb_column=10;

	switch (menuChoice)
	{
           case '1':
//                FileNameIn= "/home/gweno/workspace/ESV5-Linux/default.csv";
                strcpy(FileNameIn,"/home/gweno/Documents/Project/Cpp/ESV7/default.csv");
                nb_column=7;
                break;           
           case 't':
//                FileNameIn= "/home/gweno/workspace/ESV5-Linux/test01.csv";
                strcpy(FileNameIn,"/home/gweno/Documents/Project/Cpp/ESV7/test01.csv");
                nb_column=7;
                break;
           case '2':
//                FileNameIn= "/home/gweno/workspace/ESV5-Linux/joe.csv";
                strcpy(FileNameIn,"/home/gweno/Documents/Project/Cpp/ESV7/joe.csv");
//                firstLine(FileNameIn);
//                assignIndex();
                nb_column=7;
                break;
           case '3':
                std::cout << "\nEnter the name of the existing file you want to load: ";
                std::cin >> FileName;
                FileNameIn = strcat(FileName, ExtensionCSV);
                nb_column=10;
                break;
            case '6':
                 std::cout << "\nEnter the name of the existing file you want to load: ";
                 std::cin >> FileNum;
//                 FileNameIn = strcat(FileName, ExtensionCSV); // inadequate when using listFile()
                 strcpy(FileNameIn,results[FileNum].c_str()); // Working with Linux
                 nb_column=6;
                 break;
            case '7':
            case '8':
                 std::cout << "\nSelect the File number you want to load: ";
                 std::cin >> FileNum;
//                 std::copy(results[FileNum].begin(),results[FileNum].end(),FileNameIn);  //was working with Windows OS
                 std::cout << "control 8 FileNameIn: " << results[FileNum] << std::endl;
                 strcpy(FileNameIn,results[FileNum].c_str()); // Working with Linux
                 std::cout << "control 8 FileNameIn: " << FileNameIn << std::endl;
                 nb_column=6;
                 break;
            case '9':
                 cout << "\nSelect the File number you want to load: ";
                 cin >> FileNum;
//                 std::copy(results[FileNum].begin(),results[FileNum].end(),FileNameIn);  //was working with Windows OS
                 strcpy(FileNameIn,results[FileNum].c_str()); // Working with Linux
                 nb_column=6;

                 break;

           default:
                break;
    }                                  

    ifstream fileEntity;
    std::cout << "control 81 FileNameIn: " << FileNameIn << std::endl;
    std::cout << "control 82 strcmp: " << strcmp(FileNameIn,"/home/gweno/workspace/ESV5-Linux/default.csv") << std::endl;

    fileEntity.open(FileNameIn, ios::in);

                 std::cout << "control 7" << std::endl;
    int i=0, j=0;
//    unsigned int nextComma;

    while (fileEntity.good())     // loop while extraction from file is possible
        {
         fileEntity.ignore(100,'\n');
         std::cout << "control loop" << std::endl;
         i++;    
         }
    std::cout << "control fileEntity.good()" << fileEntity.good() << std::endl;
    fileEntity.clear();                   // absolutly needed otherwise the file is flagged at eof, and good=0   
    fileEntity.seekg(0, ios::beg);        // set cursor at 0 from start of file
    
    nb_line=i-2;                                 // substract 2 lines 1 for the header, 1 for the eof
//    nb_line=i;                                      //24/10/2012 comment above + add this line

                 std::cout << "control 8" << std::endl;
                 std::cout << "nb_line " <<nb_line<< std::endl;

//                 obj = new glEntity[nb_line];                   // Very important, need to instantiate obj!!
                 std::cout << "control 9" << std::endl;
                 dataFile::file_size=nb_line;
                 std::cout << "control 10" << std::endl;

//  declaration of the array of DOUBLE one dimension, with pointer of pointer
    double** storeData= new double*[nb_line];
    char storeText[nb_line][10];
//    char storeName[maxCol][24];


//  definition of 1D array and declaration des tableaux 1D elements de notre 1er tableau
    for (int i=0;i<nb_line;i++)
    {
        storeData[i]=new double[nb_column];
    }
    
    if (fileEntity.good()){                         // test if extraction from file is possible
//        fileEntity.ignore(80,'\n');
        fileEntity.ignore(100,'\n');
    } 
//////////////
//
//    i=0;
//    j=0;
//
//    std::cout << "control6 fileEntity.good()" << fileEntity.good() << std::endl;
//
//    while ((fileEntity.good()) && (!fileEntity.eof()))     // loop while extraction from file is possible
//          {
//          fileEntity.getline(bufferString, 100, '\n');           // store character strings between each ',' (comma) in bufferString (size max=100)
//          bufferChar= strtok (bufferString,",");
//          std::cout<< "control 11 SDFF" <<std::endl;
//          std::cout << "i, j" << i << "," << j << std::endl;
//          while (bufferChar!=NULL){
//        	  	  	  	  	  	  if (j!=indexMembers[5]){
////	        	  	  	  	  	  		  storeData[i][indexMembers[j]] = atof(bufferChar);
//        	  	  	  	  	  		  storeData[i][j] = atof(bufferChar);
//        	  	  	  	  	  		  bufferChar= strtok (NULL,",");
//        	  	  	  	  	  		  std::cout << "i, j" << i << "," << j << std::endl;
////	        	  	  	  	  	  		  std::cout << "storeData[i][indexMembers[j]]" << storeData[i][indexMembers[j]] << std::endl;
//                                   }
//        	  	  	  	  	  	  else{
//        	  	  	  	  	  		  strcpy(storeText[i],bufferChar);
//        	  	  	  	  	  		  bufferChar= strtok (NULL,",");
//        	  	  	  	  	  		  std::cout << "i, j" << i << "," << j << std::endl;
//        	  	  	  	  	  		  std::cout << "storeText[i]" << storeText[i] << std::endl;
//
//        	  	  	  	  	  	  }
//
//        	  	  	  	  	  	  j++;
//          }
//
//
//          i++;
//          j=0;
//          }
//
//
//////////////
    i=0;
    j=0;
    while ((fileEntity.good()) && (!fileEntity.eof()))     // loop while extraction from file is possible
          {
          fileEntity.getline(bufferString, 100, '\n');           // store character strings between each ',' (comma) in bufferString (size max=100)
          bufferChar= strtok (bufferString,",");
          std::cout<< "control 11" <<std::endl;

          while (bufferChar!=NULL){
        	  	  	  	  	  	  if (j<6){
        	  	  	  	  	  		  storeData[i][j] = atof(bufferChar);
        	  	  	  	  	  		  bufferChar= strtok (NULL,",");
                                   }
        	  	  	  	  	  	  else{
        	  	  	  	  	  		  strcpy(storeText[i],bufferChar);
        	  	  	  	  	  		  bufferChar= strtok (NULL,",");
        	  	  	  	  	  	  }

        	  	  	  	  	  	  j++;
          }


          i++;
          j=0;
          }

  
    fileEntity.close();           // close file
  
//  load data into entity array
    switch(menuChoice)  {
    case 't':
    case '1':
    case '2':
    case '3':
//        for (int i=0;i<nb_line; i++){
////            obj[i].Xpos=storeData[i][1];
////            obj[i].Ypos=storeData[i][2];
////            obj[i].Zpos=storeData[i][3];
////            obj[i].Xmov=storeData[i][4];
////            obj[i].Ymov=storeData[i][5];
////            obj[i].Zmov=storeData[i][6];
////            obj[i].Xacc=storeData[i][7];
////            obj[i].Yacc=storeData[i][8];
////            obj[i].Zacc=storeData[i][9];
//            }
//            break;
        	dataFile::resetDataFile();
    case '6'   :
    case '7'   :
    case '8'   :
        for (int i=0;i<nb_line; i++){
            std::cout << "Control 1 " << i << std::endl;
            std::cout << "Nb Lines " << nb_line << std::endl;
            			dataFile::typeEntity.push_back(storeData[i][1]);
                        dataFile::nbChildren.push_back(storeData[i][2]);
                        dataFile::masterEntity.push_back(storeData[i][3]);
                        dataFile::layerEntity.push_back(storeData[i][4]);
                        dataFile::valueEntity.push_back(storeData[i][5]);
//                        dataFile::textEntity.push_back(storeText[i]);
                        dataFile::storeDataText.push_back(storeText[i]);
                        std::cout << "control A" << std::endl;
                        std::cout << "valueEntity" << dataFile::valueEntity.at(0)<< std::endl;
                        std::cout << "typeEntity" << dataFile::typeEntity.at(0)<< std::endl;
            }
            break;
    case '9'   :
        dataFile::nbChildren.at(input)++;
//        unsigned int size;
        dataFile::file_size=dataFile::masterEntity.size();

        for (int i=0;i<nb_line; i++){
            std::cout << "Control 2";
                        dataFile::typeEntity.push_back(storeData[i][1]);
                        dataFile::nbChildren.push_back(storeData[i][2]);
                        dataFile::masterEntity.push_back(storeData[i][3]+dataFile::file_size);
                        dataFile::layerEntity.push_back(storeData[i][4]+dataFile::layerEntity.at(input));
                        dataFile::valueEntity.push_back(storeData[i][5]);

            }
        dataFile::masterEntity.at(dataFile::file_size)=input;
        dataFile::file_size=dataFile::masterEntity.size()-1;
            break;
     default:
            break;

    }

std::cout << "control B" << std::endl;

//      Destroy the array ...


for (int i=0;i<nb_line;i++)
{

//    for (int j=0;j<nb_column;j++)
//    {
    	delete [] storeData[i];
//    }
    }
delete [] storeData;

//delete [] FileName;
//delete [] FileNameIn;
//delete [] bufferString;
//delete [] ExtensionCSV;


std::cout << "control C" << std::endl;

}

// enterData is to enter Data with user manual entries...

void dataFile::enterData(unsigned int menuChoice){

   //~ int nbEntity, countEntity;
   int nbEntity;
   double eNergy_Entity;

   //~ countEntity=0;
   
	switch (menuChoice)
	{
           case '2':
           cout << "How many entities in the universe?" << endl;
           cin >> nbEntity;
//           obj = new glEntity[nbEntity];
           dataFile::file_size=nbEntity;
           for (int i=0; i<nbEntity ; i++) {     
               cout << "Enter parameter for Entity #" << i << ":" << endl;
               cout << "Xpos= " ;
               cout << endl;
                    }       
                break;           

           case '4':
               std::cout << "How many entities in the universe?" << std::endl;
               std::cin >> nbEntity;
               dataFile::file_size=nbEntity;
               for (int i=0; i<nbEntity ; i++) {
                   std::cout << "Energy?" << std::endl;
                   cin >> eNergy_Entity;
               }           
           break;              
             
             case '5':
            	 std::cout << "Control enterData 5" << std::endl;
                dataFile::enterLayer();
                    break;     
                  


           default:
                break;
    }   
}                     
                                                          
void dataFile::enterLayer() {
//~ int currentLayer;
unsigned int iterEntity, iterChildrenEnd, iterChildrenStart;
iterEntity=0;
//~ currentLayer=0;
iterChildrenStart=0;
iterChildrenEnd=0;

unsigned int input,input2;
char *input_char = new char[10];

while (iterEntity<layerEntity.size() and iterEntity<=iterChildrenEnd) {
      std::cout<<"Vector's size: " << layerEntity.size() << std::endl;
      std::cout<<"Parent is Entity #" << masterEntity.at(iterEntity)<< std::endl;
      typeEntity.push_back(1);
      std::cout << "Value Entity #" << iterEntity << " ?" << std::endl;
      std::cin>>input;
      valueEntity.push_back(input);
      std::cout << " Input: " << input << std::endl;

      std::cout << "Text Entity #" << iterEntity << " ?" << std::endl;
      std::cin>>input_char;
      textEntity.push_back(input_char);

      std::cout << " textEntity.at(iterEntity) " << textEntity.at(iterEntity) << std::endl;
      std::cout << " textEntity.at(0) " << textEntity.at(0) << std::endl;
      std::cout << "Nb Children of Entity #" << iterEntity << " ?" << std::endl;
      std::cin>>input2;
      nbChildren.push_back(input2);

      if (nbChildren.at(iterEntity)>0){
         iterChildrenStart=iterChildrenEnd+1;
         iterChildrenEnd=iterChildrenStart+nbChildren.at(iterEntity)-1;
         for (unsigned int i=iterChildrenStart; i<=iterChildrenEnd; i++){
        	 masterEntity.push_back(iterEntity);
        	 layerEntity.push_back(layerEntity.at(iterEntity)+1);
        	 std::cout << i <<std::endl ;
             }
         }
         std::cout<<"Layer is " << layerEntity.at(iterEntity) << std::endl;
         std::cout<<"First Child: " << iterChildrenStart << std::endl;
         std::cout<<"Last Child: " << iterChildrenEnd << std::endl<< std::endl ;
         iterEntity++;
      }

        displayEntity();
}




dataFile::dataFile(int file_size){                     //init the constructor with the array size in parameter
                      
					dataFile::structureEntity.push_back(0);
					dataFile::layerEntity.push_back(0);

                       }


dataFile::~dataFile(){
						results.clear();
                        dataFile::typeEntity.clear();
                        dataFile::nbChildren.clear();
                        dataFile::masterEntity.clear();
                        dataFile::layerEntity.clear();
                        dataFile::valueEntity.clear();
                        dataFile::structureEntity.clear();             //MEMBER0: flag 0 if direct value; flag 1 if structure
//                        dataFile::textEntity.clear();
                        dataFile::storeDataText.clear();
//                        delete storeText;
//                        delete storeData[0];
//                        delete storeName[0];
//                	    delete indexMembers;
                        std::cout << "size destructor dataFile storeDataText:" << storeDataText.size() << std::endl;

						}


void dataFile::listFile(){


//    DIR *dir;
//    struct dirent *ent;
//    dir = opendir (".");
//    if (dir != NULL) {

//      /* print all the files and directories within directory */
//      while ((ent = readdir (dir)) != NULL) {
//          std::string fname = ent->d_name;
//          if (fname!="." and fname!=".."){
////          std::cout <<fname.substr(fname.length()-3,3)<< std::endl;
//              if (fname.substr(fname.length()-3,3)=="csv" ){
//          std::cout <<fname<< std::endl;
//          }
//          }
//      }
//      closedir (dir);
//    } else {
//      /* could not open directory */
//      perror ("");
////      return EXIT_FAILURE;

//    }
    std::string extension = "csv";

    // setup search parameters
//    std::string curr_directory = get_current_dir_name();
//    std::string curr_directory=".";
    std::string curr_directory="/home/gweno/workspace/ESV5-Linux";

    std::cout << curr_directory << std::endl;


    dataFile::searchFile(curr_directory, extension);

    std::cout << "Control 1 List file"<< std::endl;

    // output results
    if (results.size()){
    std::cout << results.size() << " files were found:" << std::endl;
    for (unsigned int i = 0; i < results.size(); ++i) // used unsigned to appease compiler warnings
    std::cout << "- \t" << i << " : " << results[i] << std::endl;
    }
    else{
    std::cout << "No files ending in '" << extension << "' were found." << std::endl;
    }
}




// recursive search algorithm
void dataFile::searchFile(std::string curr_directory, std::string extension){
	std::cout << "Control 1 searchfile, curr_directory: "<< curr_directory << " , extension:" << extension << std::endl;
DIR* dir_point = opendir(curr_directory.c_str());
	dir_point = opendir(curr_directory.c_str());
std::cout << "Control 2 searchfile " << dir_point << std::endl;
std::cout << "Control Error " << strerror(errno) << std::endl;
dirent* entry = readdir(dir_point);
entry = readdir(dir_point);
std::cout << "Control 3 searchfile, entry: " << entry->d_name << std::endl;

while (entry){ // if !entry then end of directory
if (entry->d_type == DT_DIR){ // if entry is a directory
	std::cout << "Control 4 searchfile"<< std::endl;
	std::string fname = entry->d_name;
	std::cout << "Control 5 searchfile "<< fname << std::endl;
if (fname != "." && fname != "..")
		{std::cout << "Control 6 searchfile"<< std::endl;
	if (opendir(fname.c_str())!=NULL){
	dataFile::searchFile(entry->d_name, extension); // search through it
	std::cout << "Control 7 searchfile"<< std::endl;}
		}
}
else if (entry->d_type == DT_REG){ // if entry is a regular file
	std::cout << "Control 8 searchfile"<< std::endl;
std::string fname = entry->d_name; // filename
// if filename's last characters are extension
	std::cout << "Control 9 searchfile "<< fname<< std::endl;
if (fname.find(extension, (fname.length() - extension.length())) != std::string::npos)
	{std::cout << "Control 10 searchfile "<< fname << std::endl;
	std::string fname_fullpath;
	fname_fullpath=curr_directory;
	fname_fullpath=fname_fullpath+'/'+fname;
std::cout << "Control 101 fnamefullpath"<< fname_fullpath << std::endl;

//std::string string_name_fullpath(fname_fullpath);
//results.push_back(string_name_fullpath); // add filename to results vector
	results.push_back(fname_fullpath); // add filename to results vector
	std::cout << "Control 11 searchfile"<< std::endl;
	std::cout << "Control 111 fnamefullpath"<< fname_fullpath << std::endl;

//	delete [] fname_fullpath;
//	delete [] slash;
	}
}
std::cout << "Control 112 searchfile " << std::endl;
entry = readdir(dir_point);
std::cout << "Control 12 searchfile " << dir_point << std::endl;
}

return;
}

// displayEntityLayer is used to display Entities using tags

void dataFile::displayEntity(){

	dataFile::file_size=dataFile::masterEntity.size();
    std::cout << "Displaying Entity" << std::endl;
        for (int i=0; i<file_size;i++){
        std::cout << "&" << i;
        std::cout << ":" << dataFile::valueEntity.at(i);
        std::cout << "#" << dataFile::textEntity.at(i);
        std::cout << "<" << dataFile::masterEntity.at(i);
        std::cout << ">" << dataFile::nbChildren.at(i) << std::endl;
    }
}

void dataFile::toEntity (Entity objEntity){

//	if (!objEntity.structureEntity.empty()) objEntity.structureEntity.clear();
//	if (!objEntity.typeEntity.empty()) objEntity.typeEntity.clear();
//	if (!objEntity.nbChildren.empty()) objEntity.nbChildren.clear();
//	if (!objEntity.masterEntity.empty()) objEntity.masterEntity.clear();
//	if (!objEntity.layerEntity.empty()) objEntity.layerEntity.clear();
//	if (!objEntity.valueEntity.empty()) objEntity.valueEntity.clear();
//	if (!objEntity.textEntity.empty()) objEntity.textEntity.clear();

//	if (objEntity.textEntity.size()>0) objEntity.textEntity.clear();
//	if (objEntity.textEntity.size()>0) objEntity.textEntity.swap(vector_swap_dataTextEntity);

	objEntity.structureEntity=dataFile::structureEntity;
	objEntity.typeEntity=dataFile::typeEntity;
	objEntity.nbChildren=dataFile::nbChildren;
	objEntity.masterEntity=dataFile::masterEntity;
	objEntity.layerEntity=dataFile::layerEntity;
	objEntity.valueEntity=dataFile::valueEntity;
//	objEntity.textEntity=dataFile::textEntity;
	objEntity.textEntity=dataFile::storeDataText;

}
void dataFile::dataFiletoGlEntity (){

	glEntity::structureEntity=dataFile::structureEntity;
	glEntity::typeEntity=dataFile::typeEntity;
	glEntity::nbChildren=dataFile::nbChildren;
	glEntity::masterEntity=dataFile::masterEntity;
	glEntity::layerEntity=dataFile::layerEntity;
	glEntity::valueEntity=dataFile::valueEntity;
//	glEntity::textEntity=dataFile::textEntity;
	glEntity::textEntity=dataFile::storeDataText;

}


void dataFile::insertEntity(int input){

}

void dataFile::loadDefault(){
	dataFile::loadFile('1');
	}

void dataFile::resetDataFile(){
                        dataFile::typeEntity.clear();
                        dataFile::nbChildren.clear();
                        dataFile::masterEntity.clear();
                        dataFile::layerEntity.clear();
                        dataFile::valueEntity.clear();
                        dataFile::structureEntity.clear();             //MEMBER0: flag 0 if direct value; flag 1 if structure
                       }


void dataFile::deleteEntity(int reference, unsigned int option_delete){
    std::cout << "Control deleteEntity" << std::endl;
    std::cout << "reference: " << reference << std::endl;
    std::cout << "option_delete: " << option_delete << std::endl;
    std::cout << "dataFile::structureEntity.size(): " << dataFile::structureEntity.size() << std::endl;
//    std::cout << "dataFile::structureEntity.begin(): " << dataFile::structureEntity.begin() << std::endl;

	switch (option_delete)
	{
           case '0':
//        	    dataFile::structureEntity.erase(dataFile::structureEntity.begin()+reference);
        	    dataFile::typeEntity.erase(dataFile::typeEntity.begin()+reference);
        	    dataFile::nbChildren.erase(dataFile::nbChildren.begin()+reference);
        	    dataFile::masterEntity.erase(dataFile::masterEntity.begin()+reference);
        	    dataFile::layerEntity.erase(dataFile::layerEntity.begin()+reference);
        	    dataFile::valueEntity.erase(dataFile::valueEntity.begin()+reference);
        	    dataFile::textEntity.erase(dataFile::textEntity.begin()+reference);

        	   break;
           default:
               break;
	}
}

