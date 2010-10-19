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
	
	Graph g = random_graph( 100, 0.3, 15.0 );
	
	// fprint_graph( &g, stdout );
	
	Individual best = find_solution( &g );
	
	printInd( &best );
	
	printf( "Fitness: %f\n", fitness(&best, &g) );
	
	return 0;
}
