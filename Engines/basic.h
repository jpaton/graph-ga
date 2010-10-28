/**
	basic.h
**/

#ifndef __BASIC_H
#define __BASIC_H

#include <float.h>
#include <stdbool.h>
#include <omp.h>

#include "DataTypes/graph.h"
#include "DataTypes/genetic.h"

Individual find_solution( Model * g, 
						 int max_generations, 
						 int generation_size,
                         size_t k,
                         float k_penalty,
                         int num_blocks);

#endif
