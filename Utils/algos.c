/**
 * algos.c
 *
 * Contains any algorithms for graph partitioning other than genetic ones
 *
 * Created by: James Paton      10/28/10
 **/

#include "DataTypes/graph.h"
#include "DataTypes/genetic.h"
#include "algos.h"

/**
 * kernighanlin
 *
 * Based on Wikipedia pseudocode
 **/
Individual * kernighanlin( Graph * g, int k ) {
    // initial individual
    Individual individual = random_individual( g, k );

    do {
        /* code */
    } while (g_max <= 0);
}
