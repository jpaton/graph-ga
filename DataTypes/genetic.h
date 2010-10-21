/**
 * genetic.h
 *
 * Contains data types for our genetic algorithm for graph partitioning
 *
 * Created by: James Paton		10/18/10
 **/
 
 #ifndef __GENETIC_H
 #define __GENETIC_H
 
 #include <stddef.h>
 #include <stdint.h>
 #include <stdlib.h>
 
 #include "graph.h"
 
 typedef uint8_t Chromosome; // individual.chromosomes[i] = the partition number of element i
 
 /* make an array of chromosomes */
 inline Chromosome * make_Chromosomes( size_t num );
 	 
 typedef struct individual {
 	 Chromosome * chromosomes; // array of chromosomes
 	 size_t size; // number of chromosomes
 } Individual;
 
 /* make an individual; also allocate chromosomes */
 inline Individual make_Individual( size_t size ); 
 
 /*
 	fitness
 	
 	Evaluates the fitness of an individual for a given graph and returns it as 
 	a float
 */
 float fitness( Individual *, Graph * );
 
 /*
 	crossover
 	
 	Performs random crossover of two individuals and returns a size 2 array of
 	the two offspring.  
 */
 void crossover( Individual *, Individual *, Individual *, Individual *);
 
 /*
 	mutate
 	
 	Mutates first individual and stores result in second.  The integer parameter is the
 	number of partitions.  This will do just a single mutation.
 */
 inline void mutate( Individual * i, int k ); 
 
 /*
 	random_individual
 	
 	Create a random individual for graph g with k equal sized partitions
 */
 Individual random_individual( Graph * g, int k );
 
 Individual copy( Individual * target );
 #endif
