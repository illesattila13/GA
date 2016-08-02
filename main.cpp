#include "GeneticAlgorithm.h"
#include "Population.h"
#include <iostream>

using namespace std;

int main()
{
	//int populationSize_, double mutationRate_, double crossoverRate_, int elitismCount_)
	GEneticAlgorithm ga(
		100,	//int populationSize_
		0.005,	//double mutationRate_
		0.95,	//double crossoverRate_
		2		//int elitismCount_
	);

	Population population = ga.initPopulation(79);
	ga.evalPopulation(population);

	int gen = 1;

	while (ga.isTerminationConditionMet(population) == false)
	{
		cout << population.getFittest(0).toString() << endl;

		population = ga.crossoverPopulation(population);

		population = ga.mutatePopulation(population);

		ga.evalPopulation(population);

		gen++;
	}
	cout << "Find soulution in " << gen << " generations" << endl;
	cout << population.getFittest(0).toString() << endl;
}