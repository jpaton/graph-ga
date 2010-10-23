/**
 * rng.c
 *
 * Reentrant random number generator source file.
 *
 * Created by: James Paton      10/23/10
 **/

#include "rng.h"

// a buffer for the Xi_i or whatever it is that drand48_r uses
static struct drand48_data buffer;

/**
 * rng_initialize
 *
 * Initialized the rng using seed as the seed 
 **/
void rng_initialize( long int seedval ) {
    srand48_r( seedval, &buffer );
}


/**
 * rng_random
 *
 * Returns the result of drand48_r.  Make sure to call rng_initialize first.
 **/
inline double rng_random( void ) {
    double x;

    drand48_r( &buffer, &x );

    return x;
}
