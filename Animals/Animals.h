#ifndef ANIMALS_H
#define ANIMALS_H
#include <memory>
#ifndef ORGA_INC
#define ORGA_INC
#include "Organism.h"
#endif
class Animals : public Organism
{
protected:
	
public:
	Animals();
	Animals(World& world);
	virtual bool Action() override;
	virtual void Move();
	virtual int Collision(Organism* EnemyName) override;
	virtual void MakeLove(Organism* LoverName);
	virtual bool DidIReflect(Organism* EnemyName);
	virtual bool DidIEscape(Organism* EnemyName);
	~Animals();
};
#endif // ! ANIMALS



