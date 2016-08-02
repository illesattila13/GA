#include "Individual.h"
#include <random>
#include <chrono>

using namespace std;

Individual::Individual(vector<int> chromosome_)
{
	chromosome = chromosome_;
}

Individual::Individual(int chromosomeLength)
{
	chromosome.resize(chromosomeLength);
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_real_distribution<double> distribution(0.0, 1.0);
	for (auto &gene : chromosome)
	{
		if (0.5 < distribution(generator))
		{
			gene = 0;
		}
		else
		{
			gene = 1;
		}
	}
}

vector<int>& Individual::getChromosome()
{
	return chromosome;
}

int Individual::getChromosomeLength()
{
	return chromosome.size();
}

void Individual::setGene(int offset, int gene)
{
	chromosome[offset] = gene;
}

int Individual::getGene(int offset)
{
	return chromosome[offset];
}

void Individual::setFitness(double fitness_)
{
	fitness = fitness_;
}

double Individual::getFitness()
{
	return fitness;
}

string Individual::toString()
{
	string out;
	for (auto &gene : chromosome)
	{
		out += to_string(gene);
	}
	return out;
}

bool Individual::operator<(const Individual&   rhs) const 
{
	if (fitness < rhs.fitness) return true;
	else return false;
}

bool Individual::operator>(const Individual & rhs) const 
{
	return fitness > rhs.fitness;
}
