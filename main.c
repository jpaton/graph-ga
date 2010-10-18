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

extern FILE * stdout;

void printInd( Individual * i0 ) {
	for (int i = 0; i < i0->size; i++)
		printf("%d ", i0->chromosomes[i]);
	printf("\n");
}

int main( void ) {
	srand( RAND_SEED );
	
	Graph g = random_graph( 10, 0.3, 15.0 );
	
	fprint_graph( &g, stdout );
	
	for (int i = 0; i < 10; i++) {
		Individual ind = random_individual( &g, 5 );
		printInd(&ind);
		printf("Fitness: %f\n\n", fitness(&ind, &g));
	}
	
	return 0;
}
