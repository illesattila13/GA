#pragma once
#include <vector> // for the chromosome
#include <string>

using namespace std;

/**
An "Individual" represent a single candidate solution for the problem. The information is in it's "chromosome", in this class 
this is a int array. The lenght of the chromosome has to be set in the template parameter. Each Individual has a "fitness" property,
which represent the goodnes of the solution for the actual problem. 
*/
class Individual
{
	vector<int> chromosome;	///< the information
	double fitness;				///< the goodnes of the solution

public:
	/**
		Init the Individual whit a specific chromosome.
		@param chromosome_ 
			the chromosome to give to the Individual
	*/
	Individual(vector<int> chromosome_);

	/**
	Init the chromosome with random values.
	@param chromosomeLenght
		the length of the chromosome
	*/
	Individual(int chromosomeLength=0);

	/**
	Returns a reference to the chromosome.
	@return
		reference to the chromosome
	*/
	vector<int>& getChromosome();

	/**
	@return
		the length of the chromosome
	*/
	int getChromosomeLength();

	/**
	Set a gene at the offset.
	@param offset
		the position in the chromosome
	@param gene
		the gene to set
	*/
	void setGene(int offset, int gene);

	/**
	Get a gene at the offset.
	@param offset
	the position in the chromosome
	@return 
	the gene in the offset position
	*/
	int getGene(int offset);

	/**
	Set the fitness of the Individual.
	@param fitness_ 
		the fitness to store
	*/
	void setFitness(double fitness_);

	/**
	Returns the fitness of the Individual.
	@return
		the fitness of hte Individual
	*/
	double getFitness();

	/**
	String representation of the chromosome.
	@return
		the String representing the chromosome
	*/
	string toString();

	/**
	Individual lhs is less than rhs if lhs's fitness < rhs's fitness. 
	@param rhs
		the rhs operand
	@return 
		true if lhs<rhs
	*/
	bool operator<(const Individual&  rhs) const;

	bool operator>(const Individual& rhs) const;
};