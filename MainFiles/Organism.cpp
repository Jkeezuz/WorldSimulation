#include "Organism.h"
#include <Windows.h>
//Creates basic organism
Organism::Organism() {
	IsDead = 0;
	isimmortal = 0;
}
//Increments the age of organism
void Organism::IncrementAge() {
	this->age++;
}
//Return world inside which the organism is placed
World* Organism::GetWorld() {
	return world;
}

//Draws the symbol of the organism in console
void Organism::DrawMe() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), this->color);
	putchar(symbol);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
};
//Getters return attributes of the organism
int Organism::GetStrength() const {
	return strength;
}//
std::string Organism::GetName() const {
	return this->name;
}//
char Organism::GetSymbol() {
	return this->symbol;
}//
int Organism::GetAge() const {
	return age;
}//
int Organism::GetInitiative() const {
	return initiative;
}//
std::string Organism::GetType() const {
	return type;
}//
int Organism::GetXPOS() const {
	return xPos;
}//
int Organism::GetYPOS() const {
	return yPos;
}//
//--------/
//Setters set given attribute to a given value
void Organism::SetStrength(int s) {
	this->strength = s;
}//
void Organism::SetXPOS(int x) {
	this->xPos = x;
}//
void Organism::SetYPOS(int y) {
	this->yPos = y;
}//
//-------/
void Organism::WriteSpecial() {
	return;
}