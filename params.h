/**
 * params.h
 *
 * Contains parameters for graph partitioning problem
 *
 * Created by: James Paton      10/22/10
 **/

// K = number of partititions in final solution 
#define K 2

// K_PENALTY = penalty muliplier for uneven partitions
#define K_PENALTY 100.0f

// maximum number of generations
#define MAX_GENERATIONS 1000

// size of each generation
#define GENERATION_SIZE 100

// proportion of each generation to select
#define SELECTION_SIZE 0.1f

// proportion of resulting generation that should be mutated
#define MUTATION_SIZE 0.05f

// number of times to mutate each individual
#define NUM_MUTATIONS 0.1

// number of times to crossover each parent pair
#define NUM_CROSSOVERS 2

// number of vertices in graph
#define NUM_VERTICES 500    

// propability of each edge
#define PROB_EDGE 0.1f

// maximum edge weight
#define MAX_EDGE_WEIGHT 15.0f
