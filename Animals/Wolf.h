#pragma once
#include "Animals.h"
class Wolf : 
	public Animals
{
public:
	std::shared_ptr<Organism> ReturnNew() override;
	Wolf(std::string name, char symbol, World* world);
	~Wolf();
};

