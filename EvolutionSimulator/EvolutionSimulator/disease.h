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
};

Disease::Disease()
{
	lethality = 50;
	duration = 5;
	spreadChance = 15;
}
