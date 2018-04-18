#include "Fox.h"
#include "World.h"
#include "Animals.h"
#include "World.h"
#include "Info.h"
//Returns new object of this type
std::shared_ptr<Organism> Fox::ReturnNew() {
	static int counter = 0;
	std::string s1 = this->GetName();
	std::string s2 = s1 + "JR." + std::to_string(counter++);
	std::shared_ptr<Organism> orgnew(new Fox(s2, 'F', this->world));
	return orgnew;
}
//
//Checks if fox should escape the enemy
int Fox::ShouldEscape(Organism* EnemyName) {
	if (EnemyName != NULL && EnemyName->GetType() != this->GetType()) {
		if (EnemyName->GetStrength() > GetStrength()) {
			return 1;
		}
		else if (EnemyName->GetStrength() < GetStrength()) {
			return 0;
		}
		else {
			return 2;
		}
	}
	return 0;
}
//
//Moves the fox, checks for colliision, if fox should escape the fight - moves it, destroys enemy in case fox wins
bool Fox::Action() {
	int x = xPos;
	int y = yPos;
	bool blocked[8] = {0};
	int should;
	this->Move();
	world->informator->AnnounceMove(this);
	Organism* EnemyName = world->CheckForCollision(this->xPos, this->yPos);
	if (EnemyName != NULL) {
		should = ShouldEscape(EnemyName);
		while(should == 1) {
			xPos = x;
			yPos = y;
			this->Move();
			EnemyName = world->CheckForCollision(this->xPos, this->yPos);
			if (EnemyName == NULL) return 0;
			should = ShouldEscape(EnemyName);
		}
		int res = EnemyName->Collision(this);
		if (res == 2) {
			xPos = x;
			yPos = y;
			return 0;
		}
		else if (res == 3) return 0;
		else if (res == 4) {
			world->DestroyOrganism(EnemyName);
			return 1;
		}
		else if (res == 0) {
			world->DestroyOrganism(EnemyName);
			return 0;
		}
		
		else return 1;
	}
	return 0;
}
//
//Sets attributes to defalut values
Fox::Fox(std::string name, char symbol, World* world)
{
	//this->counter = 0;
	this->strength = 3;
	this->initiative = 7;
	this->age = 0;
	this->color = 78;
	this->world = world;
	this->name = name;
	this->symbol = symbol;
	this->type = "FOX";
}
//
Fox::~Fox()
{
}
