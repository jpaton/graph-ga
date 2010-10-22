/**
	basic.c
	
	Implementation of basic GA engine
	
	Created by: James Paton		10/18/10
**/

#include "basic.h"
#include "params.h"
#include "Utils/sorting.h"

Individual find_solution( 
						 Graph * g, 
						 int max_generations, 
						 int generation_size,
                         size_t k,
                         float k_penalty
                         ) {
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
			fitnesses[i] = fitness(&population[i], g, k, k_penalty);
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
		
        /* do in place sorting of individuals */
        quicksort( population, fitnesses, generation_size );

        /* choose cutoff point for parents */
        int lastindex = SELECTION_SIZE * generation_size;
		
		/* create new individuals through crossover */
		int couples = lastindex / 2; // couples * 2 = the first parent of a couple
		couples = couples == 0 ? 1 : couples; // prevent 0 couples
		for (int i = lastindex; i < generation_size - 1; i += 2) 
            /* first, free up the offspring's chromosomes */
			crossover( &population[(i % couples) * 2],
					   &population[(i % couples) * 2 + 1],
					   &population[i],
					   &population[i + 1]); 
		
		/* mutate some random individuals */
		int num_mutants = MUTATION_SIZE * generation_size;
		if (num_mutants == 0) num_mutants = 1;
		for (int i = 0; i < rand() % (num_mutants + 1); i++) 
		 	mutate( &population[rand() % generation_size], K); 
		
	}
	
	/** free up memory **/
	for (int i = 0; i < generation_size; i++) 
		free(population[i].chromosomes);
	free(population); // let my people go
	free(fitnesses);
	free(decision);
	
	return best;
}
