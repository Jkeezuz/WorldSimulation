#include "Guarana.h"
#include <string>
#include "World.h"
#include "Info.h"
//Returns new object of this type
std::shared_ptr<Organism> Guarana::ReturnNew() {
	static int counter = 0;
	std::string s1 = this->GetName();
	std::string s2 = s1 + "JR." + std::to_string(counter++);
	std::shared_ptr<Organism> orgnew(new Guarana(s2, 'G', this->world));
	return orgnew;
}
//
//Guarana buffs attacker, gives it +3 strength on collision
int Guarana::Collision(Organism* attacker) {
	attacker->SetStrength(attacker->GetStrength() + 3);
	world->informator->AnnounceEat(attacker, this);
	//world->DestroyOrganism(this);
	this->IsDead = 1;
	return 0;
}
//
//Sets the attributes to default values
Guarana::Guarana(std::string name, char symbol, World* world)
{
	this->age = 0;
	this->strength = 0;
	this->symbol = symbol;
	this->name = name;
	this->world = world;
	this->color = 192;
	this->type = "GUARANA";
}
//
Guarana::~Guarana()
{
}
