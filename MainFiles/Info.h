#ifndef INFO_H
#define INFO_H
#include <string>
#include <memory>
#include <vector>
class Organism;
class World;
class Info
{
private:
	int xLinePos, yLinePos;
	void gotoxy(int x, int y);
	void WriteOnConsole(std::string);
public:
	Info(int x, int y);
	void UseUlt(Organism* human);
	void AnnounceCooldown(Organism* human);
	void AskForHumanInput(Organism* human, char c);
	void AnnounceBirth(Organism* newborn);
	void AnnounceDeath(Organism* dead);
	void AnnounceFight(Organism* attacker, Organism* defender);
	void AnnounceMove(Organism*);
	void AnnounceEscape(Organism*, Organism*);
	void AnnounceEat(Organism* eater, Organism* plant);
	void ResetYLINE();
	~Info();
};

#endif