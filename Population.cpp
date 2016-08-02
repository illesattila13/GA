#include "Population.h"
#include<algorithm>
#include <functional>
#include <random>
#include <chrono>
#include <iostream>

using namespace std;

Population::Population(int populationSize)
{
	for (int i = 0; i < populationSize; ++i)
	{
		population.emplace(population.begin());
	}
}

Population::Population(int populationSize, int chromosomeLength)
{
	for (int i = 0; i < populationSize; ++i)
	{
		population.emplace(population.begin(), chromosomeLength);
	}
}

vector<Individual>& Population::getIndividuals()
{
	return population;
}

Individual Population::getFittest(int offset)
{
	sort(population.begin(), population.end(), greater<Individual>());
	return population[offset];
}

void Population::setPopulationsFitness(double fitness)
{
	populationFitness = fitness;
}

double Population::getPopulationFitness()
{
	return populationFitness;
}

int Population::size()
{
	return population.size();
}

Individual& Population::getIndividual(int offset)
{
	return population[offset];
}

Individual & Population::setIndividual(int offset, Individual& individual)
{
	return population[offset] = individual;
}

void Population::shuffle()
{
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	//uniform_int_distribution<int> distribution(0.0, 1.0);
	for (int i = population.size() - 1; i > 0; --i)
	{
		uniform_int_distribution<int> distribution(0, i + 1);
		int index = distribution(generator);
		swap(population[i], population[index]);
	}
}

void Population::print()
{
	for (auto &ind : population)
	{
		cout << ind.toString() << endl;
	}
}


