#include "Weed.h"
#include <string>
//Returns new object of this type
std::shared_ptr<Organism> Weed::ReturnNew() {
	static int counter = 0;
	std::string s1 = this->GetName();
	std::string s2 = s1 + "JR." + std::to_string(counter++);
	std::shared_ptr<Organism> orgnew(new Weed(s2, '|', this->world));
	return orgnew;
}
//
//Sets the attributes to the default values
Weed::Weed(std::string name, char symbol, World* world)
{
	this->age = 0;
	this->strength = 0;
	this->symbol = symbol;
	this->name = name;
	this->world = world;
	this->color = 39;
	this->type = "WEED";
}


Weed::~Weed()
{
}
