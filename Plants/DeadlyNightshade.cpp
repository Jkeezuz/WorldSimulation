#include "DeadlyNightshade.h"
#include <string>
#include "World.h"
#include "Info.h"
//Returns new object of this type
std::shared_ptr<Organism> DeadlyNightshade::ReturnNew() {
	static int counter = 0;
	std::string s1 = this->GetName();
	std::string s2 = s1 + "JR." + std::to_string(counter++);
	std::shared_ptr<Organism> orgnew(new DeadlyNightshade(s2, 'D', this->world));
	return orgnew;
}
//
//Deadly nightshade destroys enemy organism on collsion
int DeadlyNightshade::Collision(Organism* attacker) {
	world->informator->AnnounceEat(attacker, this);
	
	attacker->IsDead = 1;
	return 4;
}
//Sets attributes to default values
DeadlyNightshade::DeadlyNightshade(std::string name, char symbol, World* world)
{
	this->age = 0;
	this->strength = 99;
	this->symbol = symbol;
	this->name = name;
	this->world = world;
	this->color = 240;
	this->type = "DEADLYNIGHTSHADE";
}
//
DeadlyNightshade::~DeadlyNightshade()
{
}
