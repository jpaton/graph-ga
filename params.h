/**
 * params.h
 *
 * Contains parameters for graph partitioning problem
 *
 * Created by: James Paton      10/22/10
 **/

// K = number of partititions in final solution 
#define K 2

// maximum number of generations
#define MAX_GENERATIONS 100

// size of each generation
#define GENERATION_SIZE 1000

// proportion of each generation to select
#define SELECTION_SIZE 0.1f

// proportion of resulting generation that should be mutated
#define MUTATION_SIZE 0.1f

// number of times to mutate each individual
#define NUM_MUTATIONS 1

// number of times to crossover each parent pair
#define NUM_CROSSOVERS 1

// number of vertices in graph
#define NUM_VERTICES 500    

// propability of each edge
#define PROB_EDGE 0.1f

// maximum edge weight
#define MAX_EDGE_WEIGHT 15.0f
