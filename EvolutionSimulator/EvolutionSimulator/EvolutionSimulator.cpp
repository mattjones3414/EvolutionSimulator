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

		int attributes[numCreatureAttributes];
		creatures[i].getAttributes(attributes);
		remainingPopulation = remainingPopulation - attributes[2];
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
	cout << "The seed is " << seed << ".\n";
	int attributes[numCreatureAttributes];
	creatures[0].getAttributes(attributes);
	cout << "The number of species is " << attributes[1] << ".\n";
}

void reportLargestPopulation()
{
	int attributes1[numCreatureAttributes];
	creatures[0].getAttributes(attributes1);
	int attributes2[numCreatureAttributes];
	for (int i = 1; i < attributes1[1]; i++)
	{
		creatures[i].getAttributes(attributes2);
		if (attributes2[2] > attributes1[2])
		{
			creatures[i].getAttributes(attributes1);
		}
	}
	cout << "The largest population is " << attributes1[2] <<
		", belonging to Species " << attributes1[0] << ".\n";
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
	int attributes[numCreatureAttributes];
	creatures[0].getAttributes(attributes);
	int population = attributes[2];
	for (int i = 1; i < attributes[1]; i++)
	{
		creatures[i].getAttributes(attributes);
		population += attributes[2];
	}
	return population;
}

void advanceGeneration()
{
	int attributes[numCreatureAttributes];
	creatures[0].getAttributes(attributes);
	int start_s = clock();
	for (int i = 0; i < attributes[1]; i++)
	{
		creatures[i].reproduce();
	}
	int stop_s = clock();
	cout << "Loop time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << endl;

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
