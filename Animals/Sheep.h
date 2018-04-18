#pragma once
#include "Animals.h"
class Sheep :
	public Animals
{
public:
	std::shared_ptr<Organism> ReturnNew() override;
	Sheep(std::string name, char symbol, World* world);
	~Sheep();
};

