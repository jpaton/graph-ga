/**
	basic.c
	
	Implementation of basic GA engine
	
	Created by: James Paton		10/18/10
**/

#include "basic.h"

extern inline void mutate( Individual *, int );

Individual find_solution( Graph * g ) {
	Individual * population; // array of individuals
	Individual best; // best individual so far
	float * fitnesses = (float *)malloc(sizeof(float)); // fitnesses[i] = fitness of population[i]
	bool * decision = (bool *)malloc(sizeof(bool)); // decision[i] iff we will keep population[i]
	
	/* create initial generation */
	population = (Individual *)malloc(GENERATION_SIZE * sizeof(Individual));
	for (int i = 0; i < GENERATION_SIZE; i++) 
		population[i] = random_individual( g, K );

	for (int generation = 0; generation < GENERATION_SIZE; generation++) {
		
		/* find the best and worst fitness; also, save the best individual */
		float min_fitness = FLT_MAX;
		float max_fitness = -10000; // TODO: use a proper constant (not FLT_MIN)
		for (int i = 0; i < GENERATION_SIZE; i++) {
			fitnesses[i] = fitness(&population[i], g);
			if (fitnesses[i] < min_fitness)
				min_fitness = fitnesses[i];
			if (fitnesses[i] > max_fitness) {
				max_fitness = fitnesses[i];
				// TODO: we need to manually copy the chromosomes!!!
				best = population[i]; // save a copy
			}
			puts("1");
		}
		
		/* make decisions on whether to keep each individual */
		float spread = max_fitness - min_fitness;
		for (int i = 0; i < GENERATION_SIZE; i++) {
			float roll = (float)rand() / RAND_MAX;
			/* threshold is the square of the fitness normalized to [0, 1] */
			float threshold = (fitnesses[i] - min_fitness) * spread;
			threshold *= threshold;
			decision[i] = roll <= threshold;
			puts("2");
		}
		
		/* scrunch the array to make room for the new members */
		// TODO: this should really be two while loops where j does not get reset;
		// this will be more efficient
		int lastindex = 0; // points just past the index of the last kept individual
		for (int i = 0; i < GENERATION_SIZE; lastindex = ++i) {
			if (decision[i]) continue;
			for (int j = i; j < GENERATION_SIZE; j++) {
				if (decision[j]) {
		 			Individual temp = population[i];
					population[i] = population[j];
					population[j] = temp; 
				}
			}
			puts("3");
		}
		
		/* create new individuals through crossover */
		int couples = lastindex / 2; // couples * 2 = the first parent of a couple
		couples = couples == 0 ? 1 : couples; // prevent 0 couples
		for (int i = lastindex; i < GENERATION_SIZE - 1; i += 2) {
			crossover( &population[(i % couples) * 2],
					   &population[(i % couples) * 2 + 1],
					   &population[i],
					   &population[i + 1]); 
			puts("4");
		}
		
		/* mutate some random individuals */
		int num_mutants = MUTATION_SIZE * GENERATION_SIZE;
		if (num_mutants == 0) num_mutants = 1;
		for (int i = 0; i < rand() % (num_mutants + 1); i++) {
		 	mutate( &population[rand() % GENERATION_SIZE], K); 
			puts("5");
		}
		
	}
	
	return best;
}
