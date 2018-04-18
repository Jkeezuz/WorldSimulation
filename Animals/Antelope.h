#pragma once
#include "Animals.h"
class Antelope : public Animals
{

public:
	Antelope(std::string name, char symbol, World* world);
	std::shared_ptr<Organism> ReturnNew() override;
	bool DidIEscape(Organism* Attacker) override;
	bool Action() override;
	void Move() override;
	~Antelope();
};

