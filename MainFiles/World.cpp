#include "World.h"
#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include "Animals.h"
#include "Organism.h"
#include "Plants.h"
#include <Windows.h>
#include "Info.h"
//A struct allowing to compare given objects and sort them in the queue
struct comparestruct {
	bool operator()(std::shared_ptr<Organism>& O1, std::shared_ptr<Organism>& O2) const {
		if ((*O1).GetInitiative() == (*O2).GetInitiative()) return (*O1).GetAge() > (*O2).GetAge();
		else return (*O1).GetInitiative() > (*O2).GetInitiative();
	}
}compare;
//
//A method allowing us to access human for special interactions
Organism* World::GetHuman() {
	for (int i = 0; i < organisms.size(); i++) {
		if ((*organisms[i]).GetType() == "HUMAN")return &(*organisms[i]);
	}return NULL;
}
//Gotoxy allowing us to move cursor on console
void gotoxy(int x, int y) {
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}
//
//Add new informator(comentator) to the world
void World::AddInformator(Info* informator) {
	this->informator = std::move(informator);
}
//
//World constructor setting necessary attributes
World::World(std::string name, int height, int width)
{
	this->turncounter = 0;
	this->sizeX = width;
	this->sizeY = height;
	this->name = name;
	surface.resize(height);
	for (int i = 0; i < height; i++) {
		surface[i].resize(width);
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			surface[i][j] = NULL;
		}
	}
}
//
//
World::~World()
{

}
//
//Getters
std::vector<std::shared_ptr<Organism> >::iterator World::GetOrganismsBegin() {
	return organisms.begin();
}
std::vector<std::shared_ptr<Organism> >::iterator World::GetOrganismsEnd() {
	return organisms.end();
}
int World::GetSizeX() {
	return sizeX;
}
int World::GetSizeY() {
	return sizeY;
}
//-------//
//Delete given organism from the queue and surface and call its destructor
void World::DestroyOrganism(Organism* organism) {
	std::vector<std::shared_ptr<Organism>>::iterator it = organisms.begin();
	for (int i = 0; i < organisms.size(); i++) {
		if ((*organisms[i]).GetName() == organism->GetName()) {
			organisms[i].use_count();
			organisms[i].unique();
			surface[organism->GetYPOS()][organism->GetXPOS()].reset();
			surface[organism->GetYPOS()][organism->GetXPOS()] = NULL;
			organisms[i].use_count();
			organisms[i].unique();
			std::advance(it, i);
			organisms.erase(it);
			
			return;
		}
	}
}
//
//Add given organism to the queue vector
bool World::AddOrganism(std::shared_ptr<Organism>& organism) {
	if (organisms.size() < ((sizeX*sizeY) - 1)) {
		organisms.push_back(organism);
		return 1;
	}return 0;
};
//
//-..- with move
bool World::AddOrganismMove(std::shared_ptr<Organism>& organism) {
	if (organisms.size() < ((sizeX*sizeY) - 1)) {
		organisms.push_back(std::move(organism));
		return 1;
	}return 0;
};
//
//Shows all organism in the queue vector for debug needs
void World::ShowAllOrganisms() {
	for (int i = 0; i < organisms.size(); i++) {
		std::cout << (*organisms[i]).GetType() << " " << (*organisms[i]).GetName() << '\n';
		std::cout << "Initiative: " << (*organisms[i]).GetInitiative() << '\n';
		std::cout << "X: " << (*organisms[i]).GetXPOS() << '\n';
		std::cout << "Y: " << (*organisms[i]).GetYPOS() << '\n';
		std::cout << '\n';
	}
}
//
//End the turn for every organism, call its action, destroy if it dies and sort queue vector at the end
void World::EndTurn() {
	int j = 0;
	int x;
	int y;
	std::string name;
	turncounter++;
	while ((j < organisms.size()) && (organisms[j] != NULL)) {
		name = (*organisms[j]).GetName();
		x = (*organisms[j]).GetXPOS();
		y = (*organisms[j]).GetYPOS();
		bool DidIDie = (*organisms[j]).Action();
		if (j >= organisms.size()) {
			for (j = organisms.size() - 1; j >= 0; j++) {
				if ((*organisms[j]).GetName() == name) break;
			}
		}
		(*organisms[j]).WriteSpecial();
		surface[y][x].reset();
		surface[y][x] = NULL;
		if (!DidIDie) {
			surface[(*organisms[j]).GetYPOS()][(*organisms[j]).GetXPOS()] = organisms[j];
			organisms[j]->IncrementAge();
		}
		else {
			DestroyOrganism(&(*organisms[j]));
		}
		j++;
	}
	std::sort(this->GetOrganismsBegin(), this->GetOrganismsEnd(), compare);
};
//
//Clears the screen, calls EndTurn and draws new board
void World::MakeTurn() {
	informator->ResetYLINE();
	system("cls");
	EndTurn();
	gotoxy(0, 0);
	for (int i = -1; i <= sizeY; i++) {
		for (int j = -1; j <= sizeX; j++) {
			if (i == -1 || j == -1 || i == sizeY || j == sizeX) {
				putc('#', stdout);
			}
			else {
				if (surface[i][j] != NULL) {
					surface[i][j]->DrawMe();
				}
				else {
					putchar(' ');
				}
			}
		}
		putchar('\n');
	}
	
	gotoxy(sizeX/4, 0);
	std::cout << name << " turn counter: " << turncounter;
};
//Puts new organism into world, sets its position and puts it onto surface. If its not possible - destroys it
bool World::PutBabyIntoWorld(Organism* baby) {//ZMIENIC TUTAJ KONIECZNIE SPRAWDZANIE CZY JEST MOZLIWE WSADZENIE DZIECIORA!!!!!!!
	int x, y;
	int xrem = baby->GetXPOS();
	int yrem = baby->GetYPOS();
	int i;
	int iterator = -1;
	for (i = organisms.size() - 1; i >= 0; i++) {
		if (organisms[i]->GetName() == baby->GetName()) break;
	}
	if (organisms[i]->GetName() != baby->GetName()) {
		DestroyOrganism(baby);
		return 0;
	}
	do { 
		do {
			x = baby->GetXPOS() + (rand() % 3) - 1;
			y = baby->GetYPOS() + (rand() % 3) - 1;
		} while (x < 0 || y < 0 || x >= sizeX || y >= sizeY || (xrem == x && yrem == y));
		iterator++;
	} while (surface[y][x] != NULL && iterator < 1000);
	if (iterator < 1000) {//W TYM IFIE SIE NAJPRAWDOPODOBNIEJ WYSYPUJE
		baby->SetXPOS(x);
		baby->SetYPOS(y);
		surface[y][x] = organisms[i];
		return 1;
	}
	else {
		DestroyOrganism(baby);
		return 0;
	}
	
}
//
//Puts all organisms from vector queue to the surface and sets its positions
void World::PopulateWorld() {
	int x, y, it = -1;
	for (int i = 0; i < organisms.size(); i++) {
		it++;
		do {
			x = rand() % sizeX;
			y = rand() % sizeY;
			(*organisms[i]).SetXPOS(x);
			(*organisms[i]).SetYPOS(y);
		} while (surface[y][x] != NULL);
		surface[y][x] = organisms[i];
	}

}
//
//Checks of given position is free or taken
Organism* World::CheckForCollision(int x, int y) {
	return &*(surface[y][x]);
}
//end
