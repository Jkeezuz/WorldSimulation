#include "Dandelion.h"
#include <string>
//Returns new object of this type
std::shared_ptr<Organism> Dandelion::ReturnNew() {
	static int counter = 0;
	std::string s1 = this->GetName();
	std::string s2 = s1 + "JR." + std::to_string(counter++);
	std::shared_ptr<Organism> orgnew(new Dandelion(s2, '*', this->world));
	return orgnew;
}
//
//Sets the attributes to default values
Dandelion::Dandelion(std::string name, char symbol, World* world)
{
	this->age = 0;
	this->strength = 0;
	this->symbol = symbol;
	this->name = name;
	this->world = world;
	this->color = 226;
	this->type = "DANDELION";
}
//
//Dandelions tries to spread 3 times in a turn
bool Dandelion::Action() {
	for(int i = 0; i < 3; i++)
	if (rand() % 10 == 1) 
		Spread();
	return 0;
}
//
Dandelion::~Dandelion()
{
}
