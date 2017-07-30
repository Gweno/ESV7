//-----------Entity.h-------------
#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <string.h>

class Entity {
  public:
//   default constructor; initialize the entity         
    Entity();

//  Destructor; to free memory space if Entity is not needed anymore      
    ~Entity();

public:
    static std::vector<int> structureEntity;             //MEMBER0: flag 0 if direct value; flag 1 if structure
    static std::vector<unsigned int>  typeEntity;          //MEMBER1: the type of the entity
    static std::vector<unsigned int>  nbChildren;          //MEMBER2: number of dependants
    static std::vector<unsigned int> masterEntity;        //MEMBER3: address of the Entity from which this Entity depends
	static std::vector<int> layerEntity;                  //MEMBER4: Layer or level of this Entity
	static std::vector<double> valueEntity;               //MEMBER5: The basic value of Entity is of type 'double' for now
	static std::vector<std::string> textEntity;
// public method
//	void deleteEntity(int reference, unsigned int option_delete);

    static void newEntity();
    static void deleteEntity(unsigned int iterator);

// private methods

//private:
	unsigned int getValueEntity(unsigned int iterEntity);
	void setValueEntity();
	static unsigned int getValueEntity_Relative(int reference);

};

#endif
