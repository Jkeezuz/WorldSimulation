#pragma once
#include "Plants.h"
class Dandelion :
	public Plants
{
public:
	std::shared_ptr<Organism> ReturnNew() override;
	bool Action() override;
	Dandelion(std::string name, char symbol, World* world);
	~Dandelion();
};

