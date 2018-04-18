#pragma once
#include "Animals.h"
class Human :
	public Animals
	
{
private:
	char directions;
	int UltCooldown;
public:
	Human(std::string name, char symbol, World* world);
	bool Action() override;
	bool IsUltActive();
	void RandomMove();
	void WriteSpecial() override;
	int EscapeFight(int x, int y, Organism* enemy);
	std::shared_ptr<Organism> ReturnNew() override;
	void ImmortalitySpecial();
	bool DidIEscape(Organism* attacker);
	void Move() override;
	void DrawMe() override;
	void SetDirection(char x);
	char GetDirection();
	int GetCooldown();
	~Human();
};

