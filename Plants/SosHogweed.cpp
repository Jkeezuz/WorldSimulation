#include "SosHogweed.h"
#include "World.h"
#include "Info.h"
#include "Organism.h"
//Destroys every animal on the neighbouring fields
bool SosHogweed::Action() {
	Organism* Enemy;
	int startx = this->xPos - 1;
	int starty = this->yPos - 1;
	for (int i = startx; i < startx + 3; i++) {
		for (int j = starty; j < starty + 3; j++) {
			if ((i != this->xPos || j != this->yPos) && i >= 0 && j >=0 && i < world->GetSizeX() && j < world->GetSizeY()) {
				Enemy = world->CheckForCollision(i, j);
				if (Enemy != NULL && Enemy->GetType() != this->GetType() && Enemy->isimmortal == 0 && Enemy->AmIPlant == 0)
					world->DestroyOrganism(Enemy);
			}
		}
	}
	return Plants::Action();
}
//
//Kills the attacker on collision and dies
int SosHogweed::Collision(Organism* attacker) {
	world->informator->AnnounceEat(attacker, this);
	attacker->IsDead = 1;
	return 1;
}
//Returns new object of this type
std::shared_ptr<Organism> SosHogweed::ReturnNew() {
	static int counter = 0;
	std::string s1 = this->GetName();
	std::string s2 = s1 + "JR." + std::to_string(counter++);
	std::shared_ptr<Organism> orgnew(new SosHogweed(s2, 'X', this->world));
	return orgnew;
}
//Sets attributes to default values
SosHogweed::SosHogweed(std::string name, char symbol, World* world)
{
	this->age = 0;
	this->strength = 10;
	this->symbol = symbol;
	this->name = name;
	this->world = world;
	this->color = 240;
	this->type = "SOSHOGWEED";
}


SosHogweed::~SosHogweed()
{
}
