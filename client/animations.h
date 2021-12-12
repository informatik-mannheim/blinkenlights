/**
 * Collection of different animations.
 *
 * (c) 2021 Thomas Smits
 */

#ifndef animations_h
#define animations_h

#include "config.h"
#include "types.h"
#include "hardware.h"

/** Function pointer for the animation  */
typedef void (*animation_function)(uint, uint);

/** Animations stored */
typedef struct {
    /** Number of callback functions for animations */
    uint num_callbacks;

    /* functions to be called */
    animation_function *callbacks;
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
