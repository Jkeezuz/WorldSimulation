#include "Human.h"
#include "World.h"
#include "Info.h"
#include <Windows.h>
//codes for arrow keys
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
//Calls Animals implementation of move to move the human randomly to neighbouring field
void Human::RandomMove() {
	Animals::Move();
}
//
//Writes out human's ability cooldown
void Human::WriteSpecial() {
	world->informator->AnnounceCooldown(this);
}
//
//the same as for animal but takes care of keeping up the ability cooldown
bool Human::Action() {
	int x = xPos;
	int y = yPos;
	this->Move();
	if (xPos == x && yPos == y) {
		if (UltCooldown != 0) {
			UltCooldown--;
			if (UltCooldown < 5) {
				isimmortal = 0;
			}
		}
		return 0;
	}
	Organism* EnemyName = world->CheckForCollision(this->xPos, this->yPos);
	if (EnemyName != NULL) {
		if (IsUltActive()) {
			return EscapeFight(this->GetXPOS(),this->GetYPOS(), &*EnemyName);
		}
		if (UltCooldown != 0) {
			UltCooldown--;
			if (UltCooldown < 5) {
				isimmortal = 0;
			}
		}
		int res = EnemyName->Collision(this);
		if (res == 2) {
			xPos = x;
			yPos = y;
			return 0;
		}
		else if (res == 3) return 0;
		else if (res == 4) {
			world->DestroyOrganism(EnemyName);
			return 1;
		}
		else if (res == 0) {
			world->DestroyOrganism(EnemyName);
			return 0;
		}
		else return 1;
		
	}
	if (UltCooldown != 0) {
		UltCooldown--;
		if (UltCooldown < 5) {
			isimmortal = 0;
		}
	}
	return 0;
}
//
//Checks if ability is active
bool Human::IsUltActive() {
	if (UltCooldown >= 5) return 1;
	else return 0;
}
//
//Draws human symbol on console
void Human::DrawMe() {
	//world->informator->AnnounceCooldown(this);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), this->color);
	putchar(symbol);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}
//
//Return new object of this type
std::shared_ptr<Organism> Human::ReturnNew() {
	static int counter = 0;
	std::string s1 = this->GetName();
	std::string s2 = s1 + "JR." + std::to_string(counter++);
	std::shared_ptr<Organism> orgnew(new Human(s2, 'H', this->world));
	return orgnew;
}
//
//Checks if human escaped enemy(he only does if ability is active)
bool Human::DidIEscape(Organism* attacker) {
	if (IsUltActive()) {
		EscapeFight(this->GetXPOS(), this->GetYPOS(), attacker);
		return 1;
	}else return 0;
}
//
//Makes the human escape the fight to random neighbouring field
int Human::EscapeFight(int x, int y, Organism* enemy) {
	Organism* EnemyName;
	do {
		this->xPos = x;
		this->yPos = y;
		this->RandomMove();
		EnemyName = world->CheckForCollision(this->xPos, this->yPos);
	} while (EnemyName != NULL);
	world->informator->AnnounceEscape(this, enemy);
	if (UltCooldown != 0) {
		UltCooldown--;
		if (UltCooldown < 5) {
			isimmortal = 0;
		}
	}
	return 0;
}
//
//Turns on human's special ability if cooldown = 0
void Human::ImmortalitySpecial() {
	if (UltCooldown == 0) {
		UltCooldown = 10;
		isimmortal = 1;
	}
	
}
//
//Moves the human according to pressed key
void Human::Move() {
	int NoMove = 0;
	switch (this->directions) {
	case UP:
		if (yPos > 0) yPos--;
		else NoMove = 1;
		break;
	case RIGHT:
		if (xPos < world->GetSizeX() - 1) xPos++;
		else NoMove = 1;
		break;
	case DOWN:
		if (yPos < world->GetSizeY() - 1) yPos++;
		else NoMove = 1;
		break;
	case LEFT:
		if (xPos > 0) xPos--;
		else NoMove = 1;
		break;	
	}
	this->directions = 0;
	world->informator->AnnounceMove(this);
}
//
//Sets the attributes to default values
Human::Human(std::string name, char symbol, World* world)
{
	//this->counter = 0;
	this->UltCooldown = 0;
	this->strength = 5;
	this->initiative = 4;
	this->age = 0;
	this->color = 253;
	this->world = world;
	this->name = name;
	this->symbol = symbol;
	this->type = "HUMAN";
}
void Human::SetDirection(char x) {
	this->directions = x;
}
char Human::GetDirection() {
	return this->directions;
}
int Human::GetCooldown() {
	return this->UltCooldown;
}
Human::~Human()
{
}
