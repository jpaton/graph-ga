/**
 * sorting.h
 *
 * Header file for sorting routines in sorting.c
 *
 * Created by: James Paton       10/21/10
 **/

#ifndef __SORTING_H
#define __SORTING_H

#include <stddef.h>
#include "DataTypes/genetic.h"

inline void swap( Individual * population, float * fitnesses, size_t i0, size_t i1) {
    Individual tempi = population[i0];
    float tempf = fitnesses[i0];
    population[i0] = population[i1];
    population[i1] = tempi;
    fitnesses[i0] = fitnesses[i1];
    fitnesses[i1] = tempf;
}

void quicksort( Individual * population, float * fitnesses, size_t size ); 
static void __quicksort( Individual * population, float * fitnesses, size_t left, size_t right ); 

#endif
