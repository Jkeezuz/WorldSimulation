#pragma once
#include "Plants.h"
class DeadlyNightshade :
	public Plants
{
public:
	std::shared_ptr<Organism> ReturnNew() override;
	DeadlyNightshade(std::string name, char symbol, World* world);
	int Collision(Organism* attacker) override;
	~DeadlyNightshade();
};

