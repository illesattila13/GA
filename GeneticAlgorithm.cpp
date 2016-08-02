#include "GeneticAlgorithm.h"
#include <random>
#include <chrono>

using namespace std;

GEneticAlgorithm::GEneticAlgorithm(int populationSize_, double mutationRate_, double crossoverRate_, int elitismCount_):
	populationSize(populationSize_),
	mutationRate(mutationRate_),
	crossoverRate(crossoverRate_),
	elitismCount(elitismCount_)
{
}

Population GEneticAlgorithm::initPopulation(int chromosomeLength)
{
	Population population(populationSize, chromosomeLength);
	return population;
}

double GEneticAlgorithm::calcFitness(Individual& individual)
{
	int correctGenes = 0;
	for (auto &gene : individual.getChromosome())
	{
		if (gene == 1) correctGenes++;
	}
	double fitness = (double)correctGenes / individual.getChromosomeLength();
	individual.setFitness(fitness);
	return fitness;
}

void GEneticAlgorithm::evalPopulation(Population& population)
{
	double popuFitness = 0.0;
	for (auto &ind : population.getIndividuals())
	{
		popuFitness += calcFitness(ind);
	}
	population.setPopulationsFitness(popuFitness);
}

bool GEneticAlgorithm::isTerminationConditionMet(Population population)
{
	for (auto &ind : population.getIndividuals())
	{
		if (ind.getFitness() == 1)
		{
			return true;
		}
	}
	return false;
}

Individual GEneticAlgorithm::selectParent(Population& population)
{
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution(0.0, 1.0);
	double rouletteWheelPos = population.getPopulationFitness() * distribution(generator);
	double spinWheel = 0;
	for (auto ind : population.getIndividuals())
	{
		spinWheel += ind.getFitness();
		if (spinWheel >= rouletteWheelPos) return ind;
	}
	return population.getIndividual(population.size() - 1);
}

Population GEneticAlgorithm::crossoverPopulation(Population population)
{
	Population newPopulation(population.size());

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_real_distribution<double> distribution(0.0, 1.0);

	for (int pindex = 0; pindex < population.size(); ++pindex)
	{
		Individual parent1 = population.getFittest(pindex);

		if (crossoverRate > distribution(generator) && pindex >= elitismCount)
		{
			Individual offspring(parent1.getChromosomeLength());

			Individual parent2 = selectParent(population);

			for (int gindex = 0; gindex < parent1.getChromosomeLength(); ++gindex)
			{
				if (0.5 > distribution(generator))
				{
					offspring.setGene(gindex, parent1.getGene(gindex));
				}
				else
				{
					offspring.setGene(gindex, parent2.getGene(gindex));
				}
			}
			newPopulation.setIndividual(pindex, offspring);
		}
		else
		{
			newPopulation.setIndividual(pindex, parent1);
		}
	}
	return newPopulation;
}

Population GEneticAlgorithm::mutatePopulation(Population population)
{
	Population newPopulation(populationSize);

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_real_distribution<double> distribution(0.0, 1.0);

	for (int pindex = 0; pindex < population.size(); ++pindex)
	{
		Individual individual = population.getFittest(pindex);

		for (int gindex = 0; gindex < individual.getChromosomeLength(); ++gindex)
		{
			if (pindex > elitismCount)
			{
				if (mutationRate > distribution(generator))
				{
					int newGene = 1;
					if (individual.getGene(gindex) == 1)
					{
						newGene = 0;
					}
					individual.setGene(gindex, newGene);
				}
			}
		}

		newPopulation.setIndividual(pindex, individual);
	}
	return newPopulation;
}
