//----------Entity.cpp----------

#include <iostream>
#include <vector>
#include "Entity.h"
#include <string>
#include <string.h>

using namespace std;

// 02/08/2012

//vector<int> structureEntity;
std::vector<double> valueEntity;
std::vector<int> structureEntity;
std::vector<unsigned int>  typeEntity;
std::vector<unsigned int>  nbChildren;
std::vector<unsigned int> masterEntity;
std::vector<int> layerEntity;
std::vector<std::string> textEntity;


Entity::Entity(){

//    std::vector<int> structureEntity;             //MEMBER0: flag 0 if direct value; flag 1 if structure
//	std::vector<double> valueEntity;               //MEMBER5: The basic value of Entity is of type 'double' for now

    std::vector<int> structureEntity;             //MEMBER0: flag 0 if direct value; flag 1 if structure
    std::vector<unsigned int>  typeEntity;          //MEMBER1: the type of the entity
    std::vector<unsigned int>  nbChildren;          //MEMBER2: number of dependants
    std::vector<unsigned int> masterEntity;        //MEMBER3: address of the Entity from which this Entity depends
	std::vector<int> layerEntity;                  //MEMBER4: Layer or level of this Entity
	std::vector<double> valueEntity;               //MEMBER5: The basic value of Entity is of type 'double' for now
	std::vector<std::string> textEntity;


}

Entity::~Entity(){}

unsigned int Entity::getValueEntity(unsigned int iterEntity){
	return valueEntity.at(iterEntity);
}

//void Entity::deleteEntity(int reference, unsigned int option_delete){
//	switch (option_delete)
//	{
//           case '0':
//        	    dataFile::structureEntity.erase(dataFile::structureEntity.begin()+reference);
//        	    dataFile::typeEntity.erase(dataFile::typeEntity.begin()+reference);
//        	    dataFile::nbChildren.erase(dataFile::nbChildren.begin()+reference);
//        	    dataFile::masterEntity.erase(dataFile::masterEntity.begin()+reference);
//        	    dataFile::layerEntity.erase(dataFile::layerEntity.begin()+reference);
//        	    dataFile::valueEntity.erase(dataFile::valueEntity.begin()+reference);
//        	    dataFile::textEntity.erase(dataFile::textEntity.begin()+reference);
//
//        	   break;
//           default:
//               break;
//	}
//}


void::Entity::newEntity(){

	Entity::structureEntity.push_back(0);
	Entity::typeEntity.push_back(0);
	Entity::nbChildren.push_back(0);
	Entity::masterEntity.push_back(0);
	Entity::layerEntity.push_back(0);
	Entity::valueEntity.push_back(0);
	Entity::textEntity.push_back(0);

}

void::Entity::deleteEntity(unsigned int iterator){
	if (valueEntity.size()>1){
	structureEntity.erase(structureEntity.begin() + iterator);
	typeEntity.erase(typeEntity.begin() + iterator);
	nbChildren.erase(nbChildren.begin() + iterator);
	masterEntity.erase(masterEntity.begin() + iterator);
	layerEntity.erase(layerEntity.begin() + iterator);
	valueEntity.erase(valueEntity.begin() + iterator);
//	textEntity.erase(textEntity.begin() + iterator);
	}
}

