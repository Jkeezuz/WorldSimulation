#include "Info.h"
#include <iostream>
#include "Organism.h"
#include <Windows.h>
#include <conio.h>
#include "Human.h"
//Writes on console when human uses his ability
void Info::UseUlt(Organism* human) {
	std::string s1 = "Human " + human->GetName() + " unleashes his ultimate power: Immortality!";
	WriteOnConsole(s1);
}
//
//Writes out the remaining cooldown on ability and if the ability is active writes "ult active"
void Info::AnnounceCooldown(Organism* human) {
	std::string s1 = "Remaining cooldown: " + std::to_string(((Human*)human)->GetCooldown());
	if (((Human*)human)->GetCooldown() >= 5) {
		std::string s2 = " ULT ACTIVE";
		s1 = s1 + s2;
	}
	WriteOnConsole(s1);
}
//
//Gets input for human action
void Info::AskForHumanInput(Organism* human, char c) {
	if (c != 'y') {
		c = _getch();
		((Human*)human)->SetDirection(c);
	}
	else if (c == 'y') {
		if(((Human*)human)->GetCooldown() == 0) UseUlt(human);
		((Human*)human)->ImmortalitySpecial();
	}
}
//
//Informs on console who ate who
void Info::AnnounceEat(Organism* eater, Organism* plant) {
	std::string s1 = eater->GetName();
	std::string s2 = plant->GetName();
	std::string s3 = s1 + " has eaten " + s2 + "(" + plant->GetType() + ")";
	WriteOnConsole(s3);
}
//
//Informs on console who escaped who 
void Info::AnnounceEscape(Organism* Escapee, Organism* attacker) {
	std::string s1 = Escapee->GetName();
	std::string s2 = attacker->GetName();
	std::string s3 = s1 + " has escaped " + s2 + " to: X: " + std::to_string(Escapee->GetXPOS()) + " Y: " + std::to_string(Escapee->GetYPOS());
	WriteOnConsole(s3);
}
void Info::gotoxy(int x, int y) {
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}
//Writes given message on console
void Info::WriteOnConsole(std::string string) {
	gotoxy(xLinePos, yLinePos);
	std::cout << string << std::endl;
	yLinePos++;
}
//
//Informs on console who was born where
void Info::AnnounceBirth(Organism* babyname) {
	std::string s1 = babyname->GetName();
	std::string s2 = s1 + " has been born on X: " + std::to_string(babyname->GetXPOS()) + " Y: " + std::to_string(babyname->GetYPOS());
	WriteOnConsole(s2);
}
//
//Informs on console who died
void Info::AnnounceDeath(Organism* dead) {
	std::string s1 = dead->GetName();
	std::string s2 = s1 + " has died on: X: " + std::to_string(dead->GetXPOS()) + "Y: " + std::to_string(dead->GetYPOS());
	WriteOnConsole(s2);
}
//
//Informs on console who fought who and where
void Info::AnnounceFight(Organism* attacker, Organism* defender) {
	std::string s1 = attacker->GetName();
	std::string s2 = defender->GetName();
	std::string s3 = s1 + " attacked " + s2 + " on: X: " + std::to_string(defender->GetXPOS()) + "Y: " + std::to_string(defender->GetYPOS());
	WriteOnConsole(s3);
}
//
//Informs on console movement of given organism with additional info on attribues and type
void Info::AnnounceMove(Organism* mover) {
	std::string s1 = mover->GetName();
	std::string s2 = s1 + " has moved to: X: " + std::to_string(mover->GetXPOS()) + " Y: " + std::to_string(mover->GetYPOS()) + " AGE: " + std::to_string(mover->GetAge()) +
		" STRENGTH: " + std::to_string(mover->GetStrength()) + " INITIATIVE: " + std::to_string(mover->GetInitiative()) + " (" + mover->GetType() + ")";
	WriteOnConsole(s2);
}
//
//Resets the Y line so new info will be written from the top of the console
void Info::ResetYLINE() {
	yLinePos = 0;
}
Info::Info(int x, int y)
{
	xLinePos = x;
	yLinePos = y;
}


Info::~Info()
{
}
