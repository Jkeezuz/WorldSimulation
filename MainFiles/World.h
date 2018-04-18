#ifndef WORLD_H
#define WORLD_H
#include "Organism.h"
#include <string>
#include <vector>
#include <memory>
class Info;
class World
{
private:
	std::string name;
	std::vector<std::vector<std::shared_ptr<Organism>>> surface;
	//<std::shared_ptr
	int turncounter;
	int sizeX;
	int sizeY;
	std::vector<std::shared_ptr<Organism>> organisms;
public:
	Info * informator;
	Organism* CheckForCollision(int x, int y);
	World(std::string name, int height, int width);
	void AddInformator(Info* informator);
	~World();
	virtual bool AddOrganism(std::shared_ptr<Organism>& organism);
	virtual bool AddOrganismMove(std::shared_ptr<Organism>& organism);
	bool PutBabyIntoWorld(Organism* baby);
	int GetSizeX();
	int GetSizeY();
	Organism* GetHuman();
	void ShowAllOrganisms();
	void EndTurn();
	void MakeTurn();
	void PopulateWorld();
	void DestroyOrganism(Organism* organism);
	std::vector<std::shared_ptr<Organism> >::iterator GetOrganismsBegin();
	std::vector<std::shared_ptr<Organism> >::iterator GetOrganismsEnd();
};

#endif