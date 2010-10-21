/**
 * sorting.c
 *
 * Sorting routines
 *
 * Created by: James Paton      10/21/10
 **/

#include "Utils/sorting.h"
#include "DataTypes/genetic.h"

/****
 * QUICKSORT
 *
 * Based on Wikipedia psuedocode
 **/

#ifndef DEBUG
inline 
#endif 
void swap( Individual * population, float * fitnesses, size_t i0, size_t i1) {
    Individual tempi = population[i0];
    float tempf = fitnesses[i0];
    population[i0] = population[i1];
    population[i1] = tempi;
    fitnesses[i0] = fitnesses[i1];
    fitnesses[i1] = tempf;
}

void quicksort( Individual * population, float * fitnesses, size_t size ) {
    __quicksort( population, fitnesses, 0, size - 1 );
}

static void __quicksort( Individual * population, float * fitnesses, size_t left, size_t right ) {
    size_t leftIdx = left;
    size_t rightIdx = right;
    size_t pivot;

    if (right - left + 1 > 1) {
        pivot = (left + right) / 2;
        while (leftIdx <= pivot && rightIdx >= pivot) {
            while (fitnesses[leftIdx] > fitnesses[pivot] && leftIdx++ <= pivot); 
            while (fitnesses[rightIdx] < fitnesses[pivot] && rightIdx-- >= pivot);
            swap( population, fitnesses, leftIdx++, rightIdx-- );
            if (leftIdx - 1 == pivot)
                pivot = ++rightIdx;
            else if (rightIdx + 1 == pivot)
                pivot = --leftIdx;
        }
        __quicksort( population, fitnesses, left, pivot - 1);
        __quicksort( population, fitnesses, pivot + 1, right);
    }
}

/**
 * END QUICKSORT
 **/
