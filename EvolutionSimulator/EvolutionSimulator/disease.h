#pragma once
#include "stdafx.h"
#include "seed.h"

class Disease
{
private:
	int diseaseID, lethality, duration, spreadChance;

public:
	Disease::Disease();
	Disease(int a, int b, int c) : lethality(a), duration(b), spreadChance(c) {};
	void getAllAttributes(int*);
};

Disease::Disease()
{
	lethality = 50;
	duration = 5;
	spreadChance = 15;
}

void Disease::getAllAttributes(int* attributesList)
{
	// Must be dereferenced (*)
	// i.e. int* attributes = getAllAttributes;
	//		lethality = attributes[1];
	//		OR
	//		lethality = *(attributes+1)
	attributesList[0] = Disease::diseaseID;
	attributesList[1] = Disease::lethality;
	attributesList[2] = Disease::diseaseID;
	attributesList[3] = Disease::spreadChance;
}
