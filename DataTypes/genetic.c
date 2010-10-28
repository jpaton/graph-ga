/**
 * genetic.c
 *
 * This file should contain implementations of fitness, crossover, mutate, and
 * other functions which essentially define our genetic algorithm.
 *
 * Created by: James Paton		10/18/10
 **/

#include "genetic.h"

#ifdef DEBUG
    extern inline Chromosome * make_Chromosomes( size_t );
    extern inline Individual make_Individual( size_t );
#endif

inline Chromosome * make_Chromosomes( size_t num ) {
    return (Chromosome *)malloc(num * sizeof(Chromosome));
}
 
inline Individual make_Individual( size_t size ) {
    Individual value; 
    value.size = size;
    value.chromosomes = make_Chromosomes( size );
    return value;
}
 
void mutate( Individual * individual, int k ) {
    Chromosome temp; // for swapping
    Chromosome partitions[k]; // for shuffling partitions

    /* generate partition-relative indices of elements to be swapped */
    int first = rand() % ( individual->size / k );
    int second = rand() % ( individual->size / k );

    /* select partitions using Fisher-Yates inside-out */
	partitions[0] = 0;
	for (int i = 1; i < k; i++) {
		int j = rand() % (i + 1);
		partitions[i] = partitions[j];
		partitions[j] = i;
	}
    int first_partition = partitions[0];
    int second_partition = partitions[1];

    /* convert partition relative indices to real indices */
    int first_index;
    int second_index;
    int i;
    for( i = first_index = 0; first > 0; first-- ) 
        while (individual->chromosomes[i++] != first_partition);
    first_index = i;
    for( i = second_index = 0; second > 0; second-- ) 
        while (individual->chromosomes[i++] != second_partition);
    second_index = i;

    /**
     * test for sanity and abort if we find none;
     * this is a temporary fix until we can fix crossover
     **/
    if (first_index >= individual->size || second_index >= individual->size)
        return;

    /* swap chromosomes */
    temp = individual->chromosomes[first_index];
    individual->chromosomes[first_index] = individual->chromosomes[second_index];
    individual->chromosomes[second_index] = temp;
}
 
float fitness( Individual * individual, Graph * g, size_t k, float k_penalty ) {
	float fitness = 0.0;
    size_t counts[k];
	Edge * e;

    // initialize counts
    for (int i = 0; i < k; i++) 
        counts[i] = 0;
	
	// iterate over each edge in g 
	for (int i = 0; i < g->num_edges; i++) {
		e = &g->edges[i]; /* store for readability */
		if (individual->chromosomes[e->v0] != individual->chromosomes[e->v1]) 
			/* they are not in the same parition */
			fitness -= e->weight;
	}

    // find the sizes of each parition
    for (int i = 0; i < individual->size; i++) 
        counts[(int)individual->chromosomes[i]]++;

    // find count difference penalty
    size_t min, max;
    max = 0;
    min = SIZE_MAX;
    for (int i = 0; i < k; i++) {
        if (counts[i] < min) min = counts[i];
        if (counts[i] > max) max = counts[i];
    }

    fitness -= (float)(max - min) * k_penalty;
	
	return fitness;
}

void crossover( Individual * p0, Individual * p1, Individual * o0, Individual * o1 ) {
	int n = rand() % p0->size + 1; // choose cutoff for crossover
	
	/* assign chromosomes */
	for (int i = 0; i < n; i++) {
		o0->chromosomes[i] = p0->chromosomes[i];
		o1->chromosomes[i] = p1->chromosomes[i];
	}	
	for (int i = n; i < p0->size; i++) {
		o0->chromosomes[i] = p1->chromosomes[i];
		o1->chromosomes[i] = p0->chromosomes[i];
	}
	
}

Individual random_individual( Graph * g, int k ) {
	Individual individual = make_Individual( g->num_vertices );
	
	/* create a list of vertices */
	int vertices[g->num_vertices];
	/* initialize them and shuffle using Fisher-Yates inside-out version */
	vertices[0] = 0;
	for (int i = 1; i < g->num_vertices; i++) {
		int j = rand() % (i + 1);
		vertices[i] = vertices[j];
		vertices[j] = i;
	}
	
	/* deal out vertices to partitions */
	for (int i = 0; i < g->num_vertices; i++) {
		individual.chromosomes[vertices[i]] = i % k;
	}
	
	return individual;
}

Individual copy( Individual * target ) {
	Individual individual;
	
	individual.size = target->size;
	individual.chromosomes = (Chromosome *)malloc(individual.size * sizeof(Chromosome));
	
	for (int i = 0; i < individual.size; i++)
		individual.chromosomes[i] = target->chromosomes[i];
	
	return individual;
}

void swap( Individual * population, float * fitnesses, size_t i0, size_t i1) {
    Individual tempi;
    float tempf;

    // swap individuals
    tempi = population[i0];
    population[i0] = population[i1];
    population[i1] = tempi;

    // swap fitnesses
    tempf = fitnesses[i0];
    fitnesses[i0] = fitnesses[i1];
    fitnesses[i1] = tempf;
}

