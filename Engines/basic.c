/**
	basic.c
	
	Implementation of basic GA engine
	
	Created by: James Paton		10/18/10
**/

#include "basic.h"

Individual * find_solution( Graph * g ) {
	Individual * population; // array of individuals
	Individual best; // best individual so far
	float * fitness = (float *)malloc(sizeof(float)); // fitness[i] = fitness of population[i]
	bool * decision = (bool *)malloc(sizeof(bool)); // decision[i] iff we will keep population[i]
	
	/* create initial generation */
	population = (Individual *)malloc(GENERATION_SIZE * sizeof(Individual));
	for (int i = 0; i < GENERATION_SIZE; i++) 
		population[i] = random_individual( g, K );

	for (int generation = 0; generation < GENERATION_SIZE; generation++) {
		
		/* find the best and worst fitness; also, save the best individual */
		float min_fitness = FLT_MAX;
		float max_fitness = FLT_MIN;
		for (int i = 0; i < GENERATION_SIZE; i++) {
			fitness[i] = fitness(population[i], g);
			if (fitness[i] < min_fitness)
				min_fitness = fitness[i];
			else if (fitness[i] > max_fitness) {
				max_fitness = fitness[i];
				best = population[i]; // save a copy
			}
		}
	}
	
	return individuals;
}
