#include "Wolf.h"
#include "Animals.h"
#include <string>
//Returns new object of this type
std::shared_ptr<Organism> Wolf::ReturnNew() {
	static int counter = 0;
	std::string s1 = this->GetName();
	std::string s2 = s1 + "JR." + std::to_string(counter++);
	std::shared_ptr<Organism> orgnew(new Wolf(s2, 'W', this->world));
	return orgnew;
}
//Sets the attributes to the default values
Wolf::Wolf(std::string name, char symbol, World* world)
{
	//this->counter = 0;
	this->strength = 9;
	this->initiative = 5;
	this->age = 0;
	this->color = 12;
	this->world = world;
	this->name = name;
	this->symbol = symbol;
	this->type = "WOLF";
}
Wolf::~Wolf()
{
}
