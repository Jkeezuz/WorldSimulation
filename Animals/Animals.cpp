
#include "Animals.h"
#include "World.h"
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "Info.h"
//all directions
enum dir {
	UP = 1,
	R,
	DWN,
	L,
};
//
//Creates new organism, adds it to vector queue and to the surface
void Animals::MakeLove(Organism* LoverName) {
	std::shared_ptr<Organism> newanim;
	newanim = std::move(this->ReturnNew());
	std::string name = newanim->GetName();
	world->informator->AnnounceBirth(&*newanim);
	world->AddOrganism(newanim);
	newanim->SetXPOS(this->GetXPOS());
	newanim->SetYPOS(this->GetYPOS());
	world->PutBabyIntoWorld(&*newanim);
	return;
}
//
//Moves animal
void Animals::Move() {
	int NoMove = 1;
	while (NoMove) {
		NoMove = 0;
		int direction = rand() % 4 + 1;
		switch (direction) {
		case UP:
			if (yPos > 0) yPos--;
			else NoMove = 1;
			break;
		case R:
			if (xPos < world->GetSizeX() - 1) xPos++;
			else NoMove = 1;
			break;
		case DWN:
			if (yPos < world->GetSizeY() - 1) yPos++;
			else NoMove = 1;
			break;
		case L:
			if (xPos > 0) xPos--;
			else NoMove = 1;
			break;
		}
	}
	
	
}
//

//Checks if animal reflected the attack
bool Animals::DidIReflect(Organism* EnemyName) {
	return 0;
}
//
//Checks if animal escaped
bool Animals::DidIEscape(Organism* EnemyName) {
	return 0;
}
//
//Checks what happens on a collision with a given organism
int Animals::Collision(Organism*  Attacker) {
	if (Attacker->GetType() == this->GetType()) {
		if (Attacker->GetAge() > 40 && this->GetAge() > 40)
			MakeLove(Attacker);
		return 2;
	}
	if (DidIReflect(Attacker)) return 2;
	if (DidIEscape(Attacker)) return 3;
	world->informator->AnnounceFight(Attacker, this);
	if (Attacker->GetStrength() > GetStrength()) {
		world->informator->AnnounceDeath(this);
		//world->DestroyOrganism(this);
		this->IsDead = 0;
		return 0;
	}
	else if (Attacker->GetStrength() < GetStrength()) {
		world->informator->AnnounceDeath(Attacker);
		//world->DestroyOrganism(Attacker);
		Attacker->IsDead = 1;
		return 1;
	}
	else {
		if (Attacker->GetAge() > GetAge()) {
			world->informator->AnnounceDeath(this);
			//world->DestroyOrganism(this);
			this->IsDead = 0;
			return 0;
		}
		else {
			world->informator->AnnounceDeath(Attacker);
			//world->DestroyOrganism(Attacker);
			Attacker->IsDead = 1;
			return 1;
		}
	}
	return 0;
};
//
//Calls a set of behaviours for a animals, calls Move, checks for collision and depending on the Collision return value might destroy enemy
bool Animals::Action() {
	int x = xPos;
	int y = yPos;
	this->Move();
	world->informator->AnnounceMove(this);
	Organism* EnemyName = world->CheckForCollision(this->xPos, this->yPos);
	if (EnemyName != NULL) {
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
		
	}return 0;
};
//
Animals::Animals() {
	AmIPlant = 0;
}
//Sets all the attributes to default values
Animals::Animals(World& world)
{
	this->age = 0;
	this->world = &world;
	this->type = "ANIMAL";
	this->xPos = -1;
	this->yPos = -1;
}
Animals::~Animals()
{
}
