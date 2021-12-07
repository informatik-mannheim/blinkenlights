/**
 * Collection of different animations.
 * 
 * (c) 2021 Thomas Smits
 */

#ifndef animations_h
#define animations_h

#include "config.h"
#include "types.h"

/** Function pointer for the animation  */
typedef void (*animation_function)();

/** Animations stored */
typedef struct {
    /** Number of animations */
    uint num_animations;

    /* functions to be called */
    animation_function *callback;
} animation_functions;

/** 
 *  Pointer to all available animations. Will be initialized
 *  by the setup_animations function.
 */
animation_functions *animations;

/**
 * Initialize the animations available.
 */
void setup_animations();

#endif
