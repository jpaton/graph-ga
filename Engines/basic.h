/**
	basic.h
**/

#ifndef __BASIC_H
#define __BASIC_H

#include <float.h>
#include <stdbool.h>

#include "DataTypes/graph.h"
#include "DataTypes/genetic.h"

Individual find_solution( Graph * g, 
						 int max_generations, 
						 int generation_size,
                         size_t k,
                         float k_penalty);

#endif
