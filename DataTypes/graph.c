/**
	graph.c
	
	Some utility functions for graphs
	
	Created by: James Paton		10/18/10
**/

#include "graph.h"

#include <stdlib.h>

void fprint_graph( Graph * g, FILE * stream ) {
	fprintf( stream, "%d nodes\n", g->num_vertices );
	fprintf( stream, "%d edges\n", g->num_edges );
	
	fprintf( stream, "Vertices:\n" );
	for (int i = 0; i < g->num_vertices; i++) 
		fprintf( stream, "\t%d: %f\n", i, g->vertices[i] );
	
	fprintf( stream, "Edges:\n" );
	for (int i = 0; i < g->num_edges; i++)
		fprintf( stream, "\t%d %d: %f\n", g->edges[i].v0, g->edges[i].v1, g->edges[i].weight );
	
	fprintf( stream, "\n" );
}

Graph random_graph( int n, float p, float max_weight ) {
	/* create graph of size n */
	Graph g;
	g.num_vertices = n;
	g.num_edges = 0;
	g.vertices = (Vertex *)malloc(n * sizeof(Vertex));
	Edge * edges = (Edge *)malloc(n * n * sizeof(Edge)); // we will free excess later
	
	/* create edges with probability p */
	int k = 0; // the next edge index to use
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			float roll = (float)rand() / RAND_MAX;
			if (roll <= p) {
				edges[k].v0 = i;
				edges[k].v1 = j;
				edges[k].weight = (float)rand() / RAND_MAX * max_weight;
				g.num_edges++;
				k++;
			}
		}
	
	/* copy over edges and free excess space */
	g.edges = (Edge *)malloc(k * sizeof(Edge));
	for (int i = 0; i < k; i++) 
		g.edges[i] = edges[i];
	free(edges);
	
	return g;
}
