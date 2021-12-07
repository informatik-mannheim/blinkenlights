/**
 * Handling of animations for blinkenlights.
 *
 * (c) 2021 Thomas Smits
 */

#include "types.h"

#ifndef animation_h
#define animation_h

/**
 * A single step in the animation.
 */
typedef struct {
    /** Duration of the command in milliseconds */
    uint duration;

    /**
     * Animation command to be executed. The command is an integer value
     * triggering one specific animation type. It is an index into the
     * function pointer array provided by the animations.h header file.
     */
    uint command;
} animation_element;

/**
 * One animation.
 */
typedef struct {
    /** Start time (in milliseconds) for the animation */
    ulong start_time;

    /** Pause (in millisceonds) betwen two cylces of this animation */
    ulong cycle_pause;

    /** Number of repetitions */
    ulong repeat;

    /** Number of elements */
    uint num_elements;

    /** Array of the single steps (elements) of the animation */
    animation_element *elements;
} animation;

/**
 * Free the animation allocated by the read_animation function.
 *
 * @param ani animation to be freed
 */
void free_animation(animation *ani);

/**
 * Fetch the next animation from the server.
 *
 * @param server IP address of the server
 * @param port port of the server
 * @return animation* animation structure. Must be freed by the caller.
 */
animation* read_animation(const char* server, const int port);

/**
 * Plays the animation.
 *
 * @param animation animation to be played
 */
void play_animation(animation *animation);

/**
 * Initialize the animation.
 */
void setup_animation();

/**
 * Function called from the main loop function.
 */
void loop_animation();

#endif
