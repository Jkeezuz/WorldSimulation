#pragma once
#include "Animals.h"
class Turtle :
	public Animals
{
public:
	std::shared_ptr<Organism> ReturnNew() override;
	Turtle(std::string name, char symbol, World* world);
	bool Action() override;
	bool DidIReflect(Organism* Attacker) override;
	//bool DidReflect(std::shared_ptr<Organism>& EnemyName);
	~Turtle();
};

