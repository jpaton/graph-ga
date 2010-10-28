/**
	basic.c
	
	Implementation of basic GA engine
	
	Created by: James Paton		10/18/10
**/

#include "basic.h"
#include "params.h"
#include "Utils/sorting.h"

int min( int a, int b ) {
    return a < b ? a : b;
}

Individual find_solution( 
						 Model * g, 
						 int max_generations, 
						 int generation_size,
                         size_t k,
                         float k_penalty,
                         int num_threads
                         ) {
	Individual * population; // array of individuals
	Individual best; // best individual so far
	float best_fitness = -FLT_MAX; // fitness of best individual so far
	float * fitnesses = (float *)malloc(generation_size * sizeof(float)); // fitnesses[i] = fitness of population[i]
	bool * decision = (bool *)malloc(generation_size * sizeof(bool)); // decision[i] iff we will keep population[i]
    int num_blocks = ( num_threads + generation_size - 1 ) / num_threads;
	
	/* create initial generation */
	population = (Individual *)malloc(generation_size * sizeof(Individual));
	for (int i = 0; i < generation_size; i++) 
		population[i] = random_individual( g, K );
	
	for (int generation = 0; generation < max_generations; generation++) {
		
		/* find the best and worst fitness; also, save the best individual */
		float max_fitness = -FLT_MAX;
        #ifndef SERIAL
        int num_per_block = generation_size / num_blocks;
        int i, j;
        #pragma omp parallel for shared(max_fitness, best, k, k_penalty, g) private(i, j)
        for (j = 0; j < num_blocks; j++) {
            for (i = j * num_per_block; i < min((j + 1) * num_per_block, generation_size); i++) {
        #else
		for (int i = 0; i < generation_size; i++) {
        #endif
			fitnesses[i] = fitness(&population[i], g, k, k_penalty);
            #ifndef SERIAL
            #pragma omp critical 
            {
            #endif
                if (fitnesses[i] > max_fitness) {
                        max_fitness = fitnesses[i];
                    if (max_fitness > best_fitness) {
                        best = copy(&population[i]); // save a copy
                        best_fitness = max_fitness;
                    }
                }
            #ifndef SERIAL
            }
            #endif
		}
        #ifndef SERIAL
        }
        #endif
		
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
