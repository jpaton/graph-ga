/**
	basic.c
	
	Implementation of basic GA engine
	
	Created by: James Paton		10/18/10
**/

#include "basic.h"

extern inline void mutate( Individual *, int );

Individual find_solution( 
						 Graph * g, 
						 int max_generations, 
						 int generation_size ) {
	Individual * population; // array of individuals
	Individual best; // best individual so far
	float best_fitness = -FLT_MAX; // fitness of best individual so far
	float * fitnesses = (float *)malloc(generation_size * sizeof(float)); // fitnesses[i] = fitness of population[i]
	bool * decision = (bool *)malloc(generation_size * sizeof(bool)); // decision[i] iff we will keep population[i]
	
	/* create initial generation */
	population = (Individual *)malloc(generation_size * sizeof(Individual));
	for (int i = 0; i < generation_size; i++) 
		population[i] = random_individual( g, K );
	
	for (int generation = 0; generation < max_generations; generation++) {
		
		/* find the best and worst fitness; also, save the best individual */
		float min_fitness = FLT_MAX;
		float max_fitness = -FLT_MAX;
		for (int i = 0; i < generation_size; i++) {
			fitnesses[i] = fitness(&population[i], g);
			if (fitnesses[i] < min_fitness)
				min_fitness = fitnesses[i];
			if (fitnesses[i] > max_fitness) {
				max_fitness = fitnesses[i];
				if (max_fitness > best_fitness) {
					best = copy(&population[i]); // save a copy
					best_fitness = max_fitness;
				}
			}
		}
		
		/* make decisions on whether to keep each individual */
		float spread = max_fitness - min_fitness;
		for (int i = 0; i < generation_size; i++) {
			float roll = (float)rand() / RAND_MAX;
			/* threshold is the square of the fitness normalized to [0, 1] */
			float threshold = (fitnesses[i] - min_fitness) / spread;
			threshold *= threshold;
			decision[i] = roll <= threshold;
		}
		
		/* scrunch the array to make room for the new members */
		int lastindex = 1; // points just past the index of the last kept individual
		int i, j; // indices
		i = 0; // indices start at 0 and 1
		while ( i < generation_size ) {
			while ( decision[i++] && i < generation_size );
			lastindex = j = i;
			while ( !decision[j++] && j < generation_size);
			if ( j >= generation_size ) break;
			Individual temp = population[i];
			population[i] = population[j];
			population[j] = temp;
		}
		
		/* create new individuals through crossover */
		int couples = lastindex / 2; // couples * 2 = the first parent of a couple
		couples = couples == 0 ? 1 : couples; // prevent 0 couples
		for (int i = lastindex; i < generation_size - 1; i += 2) {
			crossover( &population[(i % couples) * 2],
					   &population[(i % couples) * 2 + 1],
					   &population[i],
					   &population[i + 1]); 
		}
		
		/* mutate some random individuals */
		int num_mutants = MUTATION_SIZE * generation_size;
		if (num_mutants == 0) num_mutants = 1;
		for (int i = 0; i < rand() % (num_mutants + 1); i++) {
		 	mutate( &population[rand() % generation_size], K); 
		}
		
	}
	
	return best;
}
