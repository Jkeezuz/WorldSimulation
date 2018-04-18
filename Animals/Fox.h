#pragma once
#include "Animals.h"
class Fox :
	public Animals
{
public:
	Fox(std::string name, char symbol, World* world);
	bool Action() override;
	std::shared_ptr<Organism> ReturnNew() override;
	int ShouldEscape(Organism* EnemyName);
	~Fox();
};

