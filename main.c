/**
	main.c
	
	Main source file of C implementation of graph partitioning GA
	
	Created by: James Paton		10/18/10
**/

// TODO: convert everything to use drand48_r for thread safety before using OpenMP

#include <stdio.h>
#include <stdlib.h>

#include "DataTypes/genetic.h"
#include "DataTypes/graph.h"
#include "Engines/basic.h"

extern FILE * stdout;

void printInd( Individual * i0 ) {
	for (int i = 0; i < i0->size; i++)
		printf("%d ", i0->chromosomes[i]);
	printf("\n");
}

int main( void ) {
	srand( RAND_SEED );
	
	Graph g = random_graph( 500, 0.1, 15.0 );
	
	for (int max_generations = 1; max_generations <= MAX_GENERATIONS; max_generations++) {
		srand( RAND_SEED );
		
		Individual best = find_solution( &g, max_generations, GENERATION_SIZE );
		
		printf( "%d, %f\n", max_generations, fitness(&best, &g) );
	}
	
	return 0;
}
