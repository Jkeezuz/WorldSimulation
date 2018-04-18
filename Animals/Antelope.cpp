#include "Antelope.h"
#include "World.h"
#include "Organism.h"
#include "Info.h"
#include "Animals.h"
#include <string>

enum dir {
	UP = 1,
	R,
	DWN,
	L,
};
//Checks if Antelope escaped enemy
bool Antelope::DidIEscape(Organism* Attacker) {
	Organism* Enemy;
	int x = xPos;
	int y = yPos;
	bool blocked[8] = { 0 };
	bool DidIEscapeAttacker;
	int iterator = 0;
	if (rand() % 2 == 1) {
		do {
			this->xPos = x;
			this->yPos = y;
			this->Animals::Move();
			Enemy = world->CheckForCollision(xPos, yPos);
			iterator++;
		} while (Enemy != NULL && iterator < 1000); // ZMIENIC TO TAK JAK W INNYCH ZEBY NIE BYLO OD 1000 TYLKO COS SPRYTNIEJ
		if (iterator < 1000) {
			world->informator->AnnounceEscape(this, Attacker);
		}
	}
	else return 0;
	if (Enemy == NULL) return 1;
	else return 0;
}
//
//Moves the antelope
void Antelope::Move() {
	int NoMove = 1;
	while (NoMove) {
		NoMove = 0;
		int direction = rand() % 4 + 1;
		switch (direction) {
		case UP:
			if (yPos > 1) yPos-=2;
			else NoMove = 1;
			break;
		case R:
			if (xPos < world->GetSizeX() - 2) xPos+=2;
			else NoMove = 1;
			break;
		case DWN:
			if (yPos < world->GetSizeY() - 2) yPos+=2;
			else NoMove = 1;
			break;
		case L:
			if (xPos > 1) xPos -= 2;
			else NoMove = 1;
			break;
		}
	}
}
//
//Calls an action of Antelope. Antelope has 50% chance of escaping the fight
bool Antelope::Action() {
	int x = xPos;
	int y = yPos;
	this->Move();
	world->informator->AnnounceMove(this);
	Organism* EnemyName = world->CheckForCollision(this->xPos, this->yPos);
	if (EnemyName != NULL) {
		if (EnemyName->GetStrength() != 0 && DidIEscape(EnemyName)) return 0;
		int res = EnemyName->Collision(this);
		if (res == 2) {
			xPos = x;
			yPos = y;
			return 0;
		}
		else if (res == 3) return 0;
		else if (res == 0) {
			world->DestroyOrganism(EnemyName);
			return 0;
		}
		else if (res == 4) {
			world->DestroyOrganism(EnemyName);
			return 1;
		}
		else return 1;

	}return 0;
}
//
//Sets the attributes to default values
Antelope::Antelope(std::string name, char symbol, World* world)
{
	//this->counter = 0;
	this->strength = 4;
	this->color = 30;
	this->initiative = 4;
	this->age = 0;
	this->world = world;
	this->name = name;
	this->symbol = symbol;
	this->type = "ANTELOPE";
}
//
//Returns new object of this type
std::shared_ptr<Organism> Antelope::ReturnNew() {
	static int counter = 0;
	std::string s1 = this->GetName();
	std::string s2 = s1 + "JR." + std::to_string(counter++);
	std::shared_ptr<Organism> orgnew(new Antelope(s2, 'A', this->world));
	return orgnew;
}
//
Antelope::~Antelope()
{
}
