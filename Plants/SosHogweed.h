#ifndef SOS_HOGWEED_H
#define SOS_HOGWEED_H
#include "Plants.h"
class Organism;
class SosHogweed : public Plants
{
public:
	bool Action() override;
	int Collision(Organism* attacker) override;
	SosHogweed(std::string name, char symbol, World* world);
	std::shared_ptr<Organism> ReturnNew();
	~SosHogweed();
};


#endif // !SOS_HOGWEED_H