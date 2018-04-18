#ifndef GUARANA_H
#define GUARANA_H
#include "Plants.h"
class Guarana : public Plants
{
public:
	std::shared_ptr<Organism> ReturnNew() override;
	Guarana(std::string name, char symbol, World* world);
	int Collision(Organism* attacker) override;
	~Guarana();
};
#endif
