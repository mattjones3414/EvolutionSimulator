// EvolutionSimulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include "creature.h"
#include "disease.h"
using namespace std;


int generation;
int worldPopulation;
std::vector<Creature> creatures;
const int numCreatureAttributes = 7; // Note: Check creature.h for number of attributes
// TODO figure out a way to make this adjust automatically, or at least be less tedious
int maxSpecies;
std::vector<Disease> diseases;

void initializeWorld()
{
	generation = 1;
	worldPopulation = 200; // TODO adjust numbers so that simulation doesn't end so quickly
	maxSpecies = 100;
}

void initializeCreatures()
{
	int numSpecies = ((seed % (maxSpecies-2)) + 2);
	creatures.resize(numSpecies);

	int remainingPopulation = worldPopulation;
	int remainingSpecies = numSpecies;
	for (int i = 0; remainingSpecies > 0; i++)
	{
		creatures[i].setPopulation(remainingPopulation, remainingSpecies);
		creatures[i].configurePropagation();

		remainingPopulation = remainingPopulation - creatures[i].getAttribute(population);
		remainingSpecies--;
	}
}

void startSimulation()
{
	initializeWorld();
	initializeCreatures();
}

void reportNumSpecies()
{
	cout << "The seed is " << seed << ".\nThe number of species is " <<
		creatures[0].getAttribute(totalSpecies) << ".\n";
}

void reportLargestPopulation()
{
	int population1 = creatures[0].getAttribute(population);
	int largestSpeciesID = 0;
	for (int i = 1; i < creatures[0].getAttribute(totalSpecies); i++)
	{
		int population2 = creatures[i].getAttribute(population);
		if (population2 > population1)
		{
			population1 = population2;
			largestSpeciesID = i;
		}
	}
	cout << "The largest population is " << population1 << ", belonging to Species "
		<< creatures[largestSpeciesID].getAttribute(speciesID) << ".\n";
}

bool continueSimulation()
{
	cout << "Would you like to continue?\nPlease enter 'y' to continue or 'n' to quit. ";
	char continueChoice;
	cin >> continueChoice;
	bool validInput = false;
	while (!validInput)
	{
		if (continueChoice == 'n') { return false; }
		else if (continueChoice == 'y')
		{
			cout << "Please wait...\n";
			return true;
		}
		else
		{
			cout << "Please enter 'y' or 'n'. ";
			cin >> continueChoice;
		}
	}
}

int getWorldPopulation()
{
	int worldPopulation = 0;
	for (int i = 1; i < creatures[0].getAttribute(totalSpecies); i++)
	{
		worldPopulation += creatures[i].getAttribute(population);
	}
	return worldPopulation;
}

void advanceGeneration()
{
	for (int i = 0; i < creatures[0].getAttribute(totalSpecies); i++)
	{
		creatures[i].reproduce();
	}
	generation++;
	cout << "Generation " << generation << ". The world population is " << getWorldPopulation()
		<< ".\n";
}

int main()
{
	
	startSimulation();

	reportNumSpecies();
	reportLargestPopulation();

	while (continueSimulation())
	{
		advanceGeneration();
	}
	

    return 0;
}
