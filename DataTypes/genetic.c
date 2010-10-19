/**
 * genetic.c
 *
 * This file should contain implementations of fitness, crossover, mutate, and
 * other functions which essentially define our genetic algorithm.
 *
 * Created by: James Paton		10/18/10
 **/

#include "genetic.h"

// FIXME: there should be a way to do this without externing everything!
extern inline Chromosome * make_Chromosomes( size_t );
extern inline Individual make_Individual( size_t );

float fitness( Individual * individual, Graph * g ) {
	float fitness = 0.0;
	Edge * e;
	
	/* iterate over each edge in g */
	for (int i = 0; i < g->num_edges; i++) {
		e = &g->edges[i]; /* store for readability */
		if (individual->chromosomes[e->v0] != individual->chromosomes[e->v1]) 
			/* they are not in the same parition */
			fitness -= e->weight;
	}
	
	return fitness;
}

void crossover( Individual * p0, Individual * p1, Individual * o0, Individual * o1 ) {
	int n = rand() % p0->size + 1; // choose cutoff for crossover
	
	/* allocate memory for chromosomes */
	Chromosome * offspring0 = (Chromosome *)malloc(p0->size * sizeof(Chromosome));
	Chromosome * offspring1 = (Chromosome *)malloc(p0->size * sizeof(Chromosome));
	
	/* assign chromosomes */
	for (int i = 0; i < n; i++) {
		offspring0[i] = p0->chromosomes[i];
		offspring1[i] = p1->chromosomes[i];
	}	
	for (int i = n; i < p0->size; i++) {
		offspring0[i] = p1->chromosomes[i];
		offspring1[i] = p0->chromosomes[i];
	}
	
	o0->chromosomes = offspring0;
	o1->chromosomes = offspring1;
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
