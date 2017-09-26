#pragma once
#include "stdafx.h"
#include <random>
#include <math.h>
using namespace std;

random_device randomDevice;
mt19937 seedGenerator(randomDevice());
uniform_int_distribution<int> seedDistr(1, 30000);
int seed = seedDistr(seedGenerator);
//int seed = 20016;
default_random_engine generator(seed);

int genRandomNumUniform(int min, int max)
{
	uniform_int_distribution<int> distr(min, max);
	return distr(generator);
}

int genRandomNumNormal(int mean, int stdDev, int min, int max)
{
	normal_distribution<float> distr(mean, stdDev);
	float number;
	do
	{
		number = distr(generator);
	} while (number < min || number > max);
	return (int)(floor(number));
}
