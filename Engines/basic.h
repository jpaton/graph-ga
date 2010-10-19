/**
	basic.h
**/

#ifndef __BASIC_H
#define __BASIC_H

#include <float.h>
#include <stdbool.h>

#include "DataTypes/graph.h"
#include "DataTypes/genetic.h"

/*** ENGINE PARAMETERS ***/

/* temporary until we have a more sophisticated algorithm */
/* K = number of partititions in final solution */
#define K 2

// maximum number of generations
#define MAX_GENERATIONS 100

// size of each generation
#define GENERATION_SIZE 1000

// proportion of each generation to select
// #define SELECTION_SIZE 0.1f

// proportion of resulting generation that should be mutated
#define MUTATION_SIZE 0.05f

// number of times to mutate each individual
#define NUM_MUTATIONS 1

// number of times to crossover each parent pair
#define NUM_CROSSOVERS 1

Individual find_solution( Graph * g, 
						 int max_generations, 
						 int generation_size  );

#endif
