#include "Turtle.h"
#include "World.h"
#include "Animals.h"
#include <random>
//Returns new object of this type
std::shared_ptr<Organism> Turtle::ReturnNew() {
	static int counter = 0;
	std::string s1 = this->GetName();
	std::string s2 = s1 + "JR." + std::to_string(counter++);
	std::shared_ptr<Organism> orgnew(new Turtle(s2, 'T', this->world));
	return orgnew;
}
//
//Checks if turtle reflected, it does if enemy strength is lesser than 5
bool Turtle::DidIReflect(Organism* Attacker) {
	if (Attacker->GetStrength() < 5) return 1;
	else return 0;
}
//
//Moves the turtle, checks for collision, destroys enemy if he kills it
bool Turtle::Action() {
	if ((rand() % 4 + 1) != 4) return 0;
	int x = xPos;
	int y = yPos;
	this->Move();
	Organism* EnemyName = world->CheckForCollision(this->xPos, this->yPos);
	if (EnemyName != NULL) {
		int res = EnemyName->Collision(this);
		if (res == 2) {
			xPos = x;
			yPos = y;
			return 0;
		}
		else if (res == 0) {
			world->DestroyOrganism(EnemyName);
			return 0;
		}
		else if (res == 3) return 0;
		else if (res == 4) {
			world->DestroyOrganism(EnemyName);
			return 1;
		}
		else return 1;
	}return 0;
}
//Sets the attributes to default values
Turtle::Turtle(std::string name, char symbol, World* world)
{
	//this->counter = 0;
	this->strength = 2;
	this->initiative = 1;
	this->age = 0;
	this->color = 10;
	this->world = world;
	this->name = name;
	this->symbol = symbol;
	this->type = "TURTLE";
}


Turtle::~Turtle()
{
}
