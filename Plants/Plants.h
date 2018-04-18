#ifndef PLANTS_H
#define PLANTS_H
#ifndef ORGA_INC
#define ORGA_INC
#include "Organism.h"
#endif
#include <memory>
class Plants : public Organism
{
protected:
	
public:
	void Spread();
	bool Action() override;
	virtual int Collision(Organism* EnemyName) override;
	Plants();
	~Plants();
};
#endif // !PLANTS



