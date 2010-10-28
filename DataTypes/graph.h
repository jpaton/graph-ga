/**
	graph.h
	
	Defines datatypes for representing graphs
	
	Created by: James Paton		10/18/10
**/

#ifndef __GRAPH_H
#define __GRAPH_H

#include <stdint.h>
#include <stdio.h>

typedef float Vertex;

typedef struct edge {
	/* the two ends of the edge, both vertex ids */
	int v0;
	int v1;
	float weight; // the edge weight
} Edge;

typedef struct graph {
	Vertex * vertices;
	Edge * edges;
	size_t num_vertices;
	size_t num_edges;
} Graph;

/**
	random_graph
	
	Create and return a random graph with n vertices where every possible edge has
	probability p of occurring and edge weight are assigned random weights up to
	max_weight.
**/
Graph random_graph( int n, float p, float max_weight );

/**
	fprint_graph
	
	Print a representation of graph g to stream
**/
void fprint_graph( Graph * g, FILE * stream );

#endif
