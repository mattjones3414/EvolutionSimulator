#pragma once
#include "stdafx.h"
#include "seed.h"
#include <math.h>
#include <iostream>

enum attributesList {
	speciesID, totalSpecies, population, maxPopulation, minSpawnPerIndPerGen,
	maxSpawnPerIndPerGen, avgSpawnPerIndPerGen
}; // TODO find a more organized location for this

class Creature
{
private:
	// Change EvolutionSimulator.cpp => numCreatureAttributes whenever this changes
	int speciesID;
	static int totalSpecies;
	int population;
	int maxPopulation;
	int minSpawnPerIndPerGen;
	int maxSpawnPerIndPerGen;
	int avgSpawnPerIndPerGen;

public:
	Creature::Creature();
	void setPopulation(int, int);
	void configurePropagation();
	void reproduce();
	//void getAllAttributes(int*);
	int getAttribute(attributesList);
};

int Creature::totalSpecies = 0; // TODO does this need to be here?

Creature::Creature()
{
	totalSpecies++;
	speciesID = totalSpecies;

}

void Creature::setPopulation(int remainingPopulation, int remainingSpecies)
{
	if (remainingSpecies == 1)
	{
		population = remainingPopulation;
	}
	else
	{
		int possiblePopulation = ceil((remainingPopulation - remainingSpecies) / 3);
		uniform_int_distribution<int> popDistr(1, possiblePopulation);
		population = popDistr(generator);
		int i = 1;
	}
}

void Creature::configurePropagation()
{
	maxPopulation = genRandomNumUniform(population * 500, population * 50000);

	minSpawnPerIndPerGen = 1; // TODO make these random/dynamic/more easily changeable
	maxSpawnPerIndPerGen = 5;
	avgSpawnPerIndPerGen = genRandomNumUniform(minSpawnPerIndPerGen, maxSpawnPerIndPerGen);
}

// Calculate number of spawn successes, then spawn per individual success based on a
//		normal distribution
// TODO make spawn success chance (currently 50%) and standard deviation (currently 1) procedural
void Creature::reproduce()
{
	if (population < maxPopulation)
	{
		int spawnSuccesses = 0;
		for (int i = 0; i < population; i++)
		{
			spawnSuccesses += genRandomNumUniform(0, 1);
		}
		int newPopulation = 0;
		for (int i = 0; i < spawnSuccesses; i++)
		{
			newPopulation += genRandomNumNormal(avgSpawnPerIndPerGen, 1, minSpawnPerIndPerGen, maxSpawnPerIndPerGen);
		}
		std::cout << "Species " << speciesID << ", with an average spawn number of " <<
			avgSpawnPerIndPerGen << " and " << spawnSuccesses << " successful births, produced " <<
			newPopulation << " new spawn.\n";
		population += newPopulation;
		if (population > maxPopulation) { population = maxPopulation; }
	}
	else
	{
		std::cout << "Species " << speciesID << " has saturated its population with " <<
			population << " individuals. Its population did not grow.\n";
	}
}

/*void Creature::getAllAttributes(int* attributeList)
{
	// Must be dereferenced (*)
	// i.e. int* attributes = getAllAttributes;
	//		maxPopulation = *(attributes+2);
	//		OR
	//		speciesID = attributes[0];
	attributeList[0] = Creature::speciesID;
	attributeList[1] = Creature::totalSpecies;
	attributeList[2] = Creature::population;
	attributeList[3] = Creature::maxPopulation;
	attributeList[4] = Creature::minSpawnPerIndPerGen;
	attributeList[5] = Creature::maxSpawnPerIndPerGen;
	attributeList[6] = Creature::avgSpawnPerIndPerGen;
}*/

int Creature::getAttribute(attributesList attribute)
{
	int attributeValues[] = { Creature::speciesID, Creature::totalSpecies, Creature::population,
		Creature::maxPopulation, Creature::minSpawnPerIndPerGen, Creature::maxSpawnPerIndPerGen,
		Creature::avgSpawnPerIndPerGen };
	return attributeValues[attribute];
}
