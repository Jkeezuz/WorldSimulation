#pragma once
#include "Plants.h"
class Weed :
	public Plants
{
public:
	std::shared_ptr<Organism> ReturnNew() override;
	Weed(std::string name, char symbol, World* world);
	~Weed();
};

