#ifndef ORGANISM_H
#define ORGANISM_H
#include <vector>
#include <memory>
class World;
class Organism
{
protected:
	int strength, initiative, xPos, yPos, age;
	std::string type;
	World* world;
	int color;
	std::string name;
	char symbol;
	
public:
	bool AmIPlant;
	bool isimmortal;
	Organism();
	bool IsDead;
	virtual void WriteSpecial();
	virtual std::shared_ptr<Organism> ReturnNew() = 0;
	virtual bool Action() = 0;
	virtual int Collision(Organism* EnemyName) = 0;
	virtual World* GetWorld();
	virtual void DrawMe();
	virtual std::string GetName() const;
	virtual std::string  GetType() const;
	virtual int GetAge() const;
	virtual int GetInitiative() const;
	virtual int GetXPOS() const;
	virtual int GetYPOS() const;
	virtual int GetStrength() const;
	virtual void SetStrength(int s);
	virtual void SetXPOS(int x);
	virtual void SetYPOS(int y);
	virtual char GetSymbol();
	virtual void IncrementAge();
};
#endif
