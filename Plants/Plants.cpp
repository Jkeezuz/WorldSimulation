
#include "Plants.h"
#include <Windows.h>
#include "World.h"
#include "Organism.h"
#include "Info.h"
#include <random>
//Creates new objects of this type and places it in vector queue and on the surface
void Plants::Spread() {
	bool success = 0;
	if (this->GetAge() > 20) {
		std::shared_ptr<Organism> newanim;
		newanim = std::move(this->ReturnNew());
		std::string name = newanim->GetName();
		success = world->AddOrganism(newanim);
		newanim->SetXPOS(this->GetXPOS());
		newanim->SetYPOS(this->GetYPOS());
		if (success == 1) {
			
			success = world->PutBabyIntoWorld(&*newanim);
			if(success == 1) world->informator->AnnounceBirth(&*newanim);
		}
		return;
	}
}
//
//Has 2% chance to spread on neighbouring field
bool Plants::Action() {
	if (rand() % 50 == 1) Spread();
	return 0;
}
//
//Dies on contanct with enemy
int Plants::Collision(Organism* EnemyName) { 
	world->informator->AnnounceEat(EnemyName, this);
	//world->DestroyOrganism(this);
	this->IsDead = 1;
	return 0;
};
//
Plants::Plants()
{
	this->initiative = 0;
	this->AmIPlant = 1;
}

Plants::~Plants()
{
}