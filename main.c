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
#include <getopt.h>

#include "DataTypes/genetic.h"
#include "DataTypes/graph.h"
#include "Engines/basic.h"
#include "params.h"

extern FILE * stdout;

#ifdef SERIAL
#define ALGO_TYPE "serial"
#else
#define ALGO_TYPE "openmp.block"
#define NUM_THREADS 12
#endif

void printInd( Individual * i0 ) {
	for (int i = 0; i < i0->size; i++)
		printf("%d ", i0->chromosomes[i]);
	printf("\n");
}

void process_options( int argc, char *argv[] ) {
    int opt;
    int option_index = 0;

    static struct option options [] = {
        { "generation_size", required_argument, NULL, true },
        { 0, 0, 0, 0 }
    };

    while (true) {
        opt = getopt_long( argc, argv, "", options, &option_index );
        if (opt == -1) break;
    }
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
             num_threads, \
             \n");

    #ifndef SERIAL
    for (int num_threads = 1; num_threads <= NUM_THREADS; num_threads++) {
        omp_set_num_threads( num_threads );
    #else
        int num_threads = 1;
    #endif
		srand( RAND_SEED );
		
        #ifdef SERIAL
        clock_t start = clock();
		Individual best = find_solution( &g, MAX_GENERATIONS, GENERATION_SIZE, K, K_PENALTY, 1 );
        clock_t end = clock();
        #else
        double start = omp_get_wtime();
		Individual best = find_solution( &g, MAX_GENERATIONS, GENERATION_SIZE, K, K_PENALTY, num_threads );
        double end = omp_get_wtime();
        #endif
		
		printf( "%d,", MAX_GENERATIONS );
        printf( "%f,", fitness(&best, &g, K, K_PENALTY) );
        #ifdef SERIAL
        printf( "%f,", (double)(end - start) / CLOCKS_PER_SEC );
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
        #ifdef SERIAL
        printf( "%d,", 1 );
        #else
        printf( "%d,", num_threads);
        #endif
        printf( "\n" );
    #ifndef SERIAL
	}
    #endif
	
	return 0;
}
