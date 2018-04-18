#include "Sheep.h"
#include "Animals.h"
#include <string>
//Returns new object of this type
std::shared_ptr<Organism> Sheep::ReturnNew() {
	static int counter = 0;
	std::string s1 = this->GetName();
	std::string s2 = s1 + "JR." + std::to_string(counter++);
	std::shared_ptr<Organism> orgnew(new Sheep(s2, 'S', this->world));
	return orgnew;
}
//
//Sets the attributes to default values
Sheep::Sheep(std::string name, char symbol, World* world)
{
	//this->counter = 0;
	this->strength = 4;
	this->initiative = 4;
	this->age = 0;
	this->color = 7;
	this->world = world;
	this->name = name;
	this->symbol = symbol;
	this->type = "SHEEP";
}
//
Sheep::~Sheep()
{
}
