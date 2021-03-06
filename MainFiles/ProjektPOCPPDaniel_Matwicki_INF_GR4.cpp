#include <windows.h>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include "World.h"
#include "Animals.h"
#include "Plants.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Antelope.h"
#include "Fox.h"
#include "Turtle.h"
#include "Info.h"
#include "Weed.h"
#include "Dandelion.h"
#include "Guarana.h"
#include "DeadlyNightshade.h"
#include "Human.h"
#include "SosHogweed.h"
#define DEBUG
#define OrgType std::shared_ptr<Organism>

struct comparestruct {
	bool operator()(std::shared_ptr<Organism>& O1, std::shared_ptr<Organism>& O2) const {
		if ((*O1).GetInitiative() == (*O2).GetInitiative()) return (*O1).GetAge() > (*O2).GetAge();
		else return (*O1).GetInitiative() > (*O2).GetInitiative();
	}
}compareme;

//DODAC NIESPRAWDZANIE MIEJSC, NA KTORE I TAK JUZ NIE MOZNA WEJSC!!
//DODAC NIESPRAWDZANIE MIEJSC, NA KTORE I TAK JUZ NIE MOZNA ZASADZIC DZIECIORA!!
int main()
{
	srand(time(NULL));
	SetConsoleTitle(TEXT("Daniel Matwicki 171580"));
	int height = 0;
	int width = 0;
	std::string name;
#ifndef DEBUG
	std::cout << "Type the height of the world: " << std::endl;
	std::cin >> height;
	std::cout << "Type the width of the world: " << std::endl;
	std::cin >> width;
	std::cout << "Type the name of the world: " << std::endl;
	std::cin >> name;
	World world(name, height, width);
#endif
#ifdef DEBUG
	World world("DebugWorld", 20, 20);
	Info* info = new Info(world.GetSizeX() + 3, 0);
	world.AddInformator(info);
#endif
	{//ZROBIC Z TEGO METHODE WORLDA XD
	OrgType wolf(new Wolf("Marek", 'W', &world));
	world.AddOrganism(wolf);
	OrgType antelope(new Antelope("Marcin", 'A', &world));
	world.AddOrganism(antelope);
	OrgType sheep(new Sheep("Ola", 'S', &world));
	world.AddOrganism(sheep);
	OrgType wolf2(new Wolf("Tyx", 'w', &world));
	world.AddOrganism(wolf2);
	OrgType antelope2(new Antelope("AntekXD", 'a', &world));
	world.AddOrganism(antelope2);
	OrgType sheep2(new Sheep("Shon", 's', &world));
	world.AddOrganism(sheep2);
	OrgType wolf3(new Wolf("Tyx2", '3', &world));
	world.AddOrganism(wolf3);
	OrgType antelope3(new Antelope("AntekXD2", '0', &world));
	world.AddOrganism(antelope3);
	OrgType sheep3(new Sheep("Shon2", '=', &world));
	world.AddOrganism(sheep3);
	OrgType fox(new Fox("Foxi", 'F', &world));
	world.AddOrganism(fox);
	OrgType turtle(new Turtle("Turtl", 'T', &world));
	world.AddOrganism(turtle);
	OrgType weed(new Weed("Weederino", '|', &world));
	world.AddOrganism(weed);
	OrgType dandelion(new Dandelion("Dandi", '*', &world));
	world.AddOrganism(dandelion);
	OrgType guarana(new Guarana("Guarana1", 'G', &world));
	world.AddOrganism(guarana);
	OrgType dn(new DeadlyNightshade("DN1", 'D', &world));
	world.AddOrganism(dn);
	OrgType human(new Human("HumanidusXD", 'H', &world));
	world.AddOrganism(human);
	OrgType sh(new SosHogweed("SosHogweed", 'X', &world));
	world.AddOrganism(sh);
    }
	std::sort(world.GetOrganismsBegin(), world.GetOrganismsEnd(), compareme);
	world.PopulateWorld();
	
	char c = NULL;
	do{
		if ((c == -32 || c == 121) && world.GetHuman() != NULL)
			world.informator->AskForHumanInput(world.GetHuman(), c);
		else if (world.GetHuman() == NULL) _getch();
		world.MakeTurn();
		
	}while(c = _getch());

	//etc(stdin);
	//clrscr();
	//world.DrawWorld();
	//system("cls");
	//world.DrawWorld();
	//delete &world;
    return 0;
}

