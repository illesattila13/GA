#pragma once

#include "Population.h"
#include "Individual.h"

/**
* The GeneticAlgorithm class is our main abstraction for managing the
* operations of the genetic algorithm. This class is meant to be
* problem-specific, meaning that (for instance) the "calcFitness" method may
* need to change from problem to problem.
*
* This class concerns itself mostly with population-level operations, but also
* problem-specific operations such as calculating fitness, testing for
* termination criteria, and managing mutation and crossover operations (which
* generally need to be problem-specific as well).
*
* Generally, GeneticAlgorithm might be better suited as an abstract class or an
* interface, rather than a concrete class as below. A GeneticAlgorithm
* interface would require implementation of methods such as
* "isTerminationConditionMet", "calcFitness", "mutatePopulation", etc, and a
* concrete class would be defined to solve a particular problem domain. For
* instance, the concrete class "TravelingSalesmanGeneticAlgorithm" would
* implement the "GeneticAlgorithm" interface. This is not the approach we've
* chosen, however, so that we can keep each chapter's examples as simple and
* concrete as possible.
*
* @author bkanber (Apress: Genetic Algorithms in Java Basics)
*
*/

class GEneticAlgorithm
{
	int populationSize;

	/**
	* Mutation rate is the fractional probability than an individual gene will
	* mutate randomly in a given generation. The range is 0.0-1.0, but is
	* generally small (on the order of 0.1 or less).
	*/
	double mutationRate;

	/**
	* Crossover rate is the fractional probability that two individuals will
	* "mate" with each other, sharing genetic information, and creating
	* offspring with traits of each of the parents. Like mutation rate the
	* range is 0.0-1.0 but small.
	*/
	double crossoverRate;

	/**
	* Elitism is the concept that the strongest members of the population
	* should be preserved from generation to generation. If an individual is
	* one of the elite, it will not be mutated or crossover.
	*/
	int elitismCount;
public:
	GEneticAlgorithm(int populationSize_, double mutationRate_, double crossoverRate_, int elitismCount_);

	/**
	* Initialize population
	*
	* @param chromosomeLength
	*            The length of the individuals chromosome
	* @return population The initial population generated
	*/
	Population initPopulation(int chromosomeLength);

	/**
	* Calculate fitness for an individual.
	*
	* In this case, the fitness score is very simple: it's the number of ones
	* in the chromosome. Don't forget that this method, and this whole
	* GeneticAlgorithm class, is meant to solve the problem in the "AllOnesGA"
	* class and example. For different problems, you'll need to create a
	* different version of this method to appropriately calculate the fitness
	* of an individual.
	*
	* @param individual
	*            the individual to evaluate
	* @return double The fitness value for individual
	*/
	double calcFitness(Individual& individual);

	/**
	* Evaluate the whole population
	*
	* Essentially, loop over the individuals in the population, calculate the
	* fitness for each, and then calculate the entire population's fitness. The
	* population's fitness may or may not be important, but what is important
	* here is making sure that each individual gets evaluated.
	*
	* @param population
	*            the population to evaluate
	*/
	void evalPopulation(Population& population);

	/**
	* Check if population has met termination condition
	*
	* For this simple problem, we know what a perfect solution looks like, so
	* we can simply stop evolving once we've reached a fitness of one.
	*
	* @param population
	* @return boolean True if termination condition met, otherwise, false
	*/
	bool isTerminationConditionMet(Population population);

	/**
	* Select parent for crossover
	*
	* @param population
	*            The population to select parent from
	* @return The individual selected as a parent
	*/
	Individual selectParent(Population& population);

	/**
	* Apply crossover to population
	*
	* Crossover, more colloquially considered "mating", takes the population
	* and blends individuals to create new offspring. It is hoped that when two
	* individuals crossover that their offspring will have the strongest
	* qualities of each of the parents. Of course, it's possible that an
	* offspring will end up with the weakest qualities of each parent.
	*
	* This method considers both the GeneticAlgorithm instance's crossoverRate
	* and the elitismCount.
	*
	* The type of crossover we perform depends on the problem domain. We don't
	* want to create invalid solutions with crossover, so this method will need
	* to be changed for different types of problems.
	*
	* This particular crossover method selects random genes from each parent.
	*
	* @param population
	*            The population to apply crossover to
	* @return The new population
	*/
	Population crossoverPopulation(Population population);

	/**
	* Apply mutation to population
	*
	* Mutation affects individuals rather than the population. We look at each
	* individual in the population, and if they're lucky enough (or unlucky, as
	* it were), apply some randomness to their chromosome. Like crossover, the
	* type of mutation applied depends on the specific problem we're solving.
	* In this case, we simply randomly flip 0s to 1s and vice versa.
	*
	* This method will consider the GeneticAlgorithm instance's mutationRate
	* and elitismCount
	*
	* @param population
	*            The population to apply mutation to
	* @return The mutated population
	*/
	Population mutatePopulation(Population population);
};