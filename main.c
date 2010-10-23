/**
	main.c
	
	Main source file of C implementation of graph partitioning GA
	
	Created by: James Paton		10/18/10
**/

// TODO: convert everything to use drand48_r for thread safety before using OpenMP

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "DataTypes/genetic.h"
#include "DataTypes/graph.h"
#include "Engines/basic.h"
#include "params.h"

extern FILE * stdout;

#ifdef SERIAL
#define ALGO_TYPE "serial"
#else
#define ALGO_TYPE "openmp"
#define NUM_THREADS 8
#endif

void printInd( Individual * i0 ) {
	for (int i = 0; i < i0->size; i++)
		printf("%d ", i0->chromosomes[i]);
	printf("\n");
}

int main( void ) {
	srand( RAND_SEED );
	
	Graph g = random_graph( NUM_VERTICES, PROB_EDGE, MAX_EDGE_WEIGHT );

    // print column headings
    printf( "num_generations, \
             best_fitness, \
             processor_time, \
             num_vertices, \
             prob_edge, \
             max_edge_weight, \
             k, \
             k_penalty, \
             generation_size, \
             selection_size, \
             mutation_size, \
             num_crossovers, \
             algo_type, \
             \n");

    #ifndef SERIAL
    omp_set_num_threads( NUM_THREADS );
    #endif
	
	for (int max_generations = 1; max_generations <= MAX_GENERATIONS; max_generations++) {
		srand( RAND_SEED );
		
        #ifdef SERIAL
        clock_t start = clock();
		Individual best = find_solution( &g, max_generations, GENERATION_SIZE, K, K_PENALTY );
        clock_t end = clock();
        #else
        double start = omp_get_wtime();
		Individual best = find_solution( &g, max_generations, GENERATION_SIZE, K, K_PENALTY );
        double end = omp_get_wtime();
        #endif
		
		printf( "%d,", max_generations );
        printf( "%f,", fitness(&best, &g, K, K_PENALTY) );
        #ifdef SERIAL
        printf( "%g,", (double)(end - start) / CLOCKS_PER_SEC );
        #else
        printf( "%f,", end - start );
        #endif
        printf( "%d,", NUM_VERTICES );
        printf( "%f,", PROB_EDGE );
        printf( "%f,", MAX_EDGE_WEIGHT );
        printf( "%d,", K );
        printf( "%f,", K_PENALTY );
        printf( "%d,", GENERATION_SIZE );
        printf( "%f,", SELECTION_SIZE );
        printf( "%f,", MUTATION_SIZE );
        printf( "%d,", NUM_CROSSOVERS );
        printf( "%s,", ALGO_TYPE  );
        printf( "\n" );
	}
	
	return 0;
}
