#pragma once
#include <vector>
#include"Individual.h"

using namespace std;

/**
A collection of individuals.
Grup level operations like finding the strongest individual, statistic on the population, selecting for mutation and crossover.
*/
class Population
{
	vector<Individual> population;
	double populationFitness;

public:
	/**
	Init the population with blank Individuals.
	@param populationSize
		the size of the population.
	*/
	Population(int populationSize);

	/**
	Init the population with Individuals.
	@param populationSize
		the size of the population.
	@param chromosomeLength
		the length of the chromosome of the Inividuals
	*/
	Population(int populationSize, int chromosomeLength);

	/**
	@return 
		Individuals
	*/
	vector<Individual>& getIndividuals();

	/**
	Find an Individual in the population in the order of fitness. 
	@param offset
		The offset of the individual to return. The individuals are soreted by fitness. \n
		[0]					: strongest
		[population.size-1]	: weakest
	@return
		Individual at the offset.
	*/
	Individual getFittest(int offset);

	/**
	Set populations fittnes
	@param fitness
		the fitness to set
	*/
	void setPopulationsFitness(double fitness);

	/**
	Returns the fitness of the population
	@return
		the fitness of the populaion
	*/
	double getPopulationFitness();

	/**
	@return 
		the size of the population
	*/
	int size();


	/**
	Get the Individual at the offset.
	@param offset
		the offset
	@return
		the Individual at the offset
	*/
	Individual& getIndividual(int offset);

	/**
	Set the Individual at the offset.
	@param offset
		the offset
	@param individual
		individual
	@return
		the Individual at the offset
	*/
	Individual& setIndividual(int offset, Individual& individual);

	/**
	Shuffles the population in place.
	*/
	void shuffle();

	/**
	Prints out the population.
	*/
	void print();
};
