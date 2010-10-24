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

void quicksort( Individual * population, float * fitnesses, size_t size ); 
static void __quicksort( Individual * population, float * fitnesses, size_t left, size_t right ); 

#endif
