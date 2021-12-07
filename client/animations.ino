/**
 * Collection of different animations.
 *
 * (c) 2021 Thomas Smits
 */

#include "config.h"
#include "animations.h"

#define NUM_ANIMATION_FUNCTIONS 2

/**
 * Initialize the animations available.
 */
void setup_animations() {
    animation_functions *functions = (animation_functions*) malloc(sizeof(animation_functions));

    functions->num_callbacks = NUM_ANIMATION_FUNCTIONS;

    functions->callbacks = (animation_function*) calloc(functions->num_callbacks, sizeof(animation_function));

    int i = 0;

    functions->callbacks[i++] = led_on;
    functions->callbacks[i++] = led_off;

    // add your functions here

    animations = functions;
}

/* ####################################### */
/* Animation functions go here */
/* ####################################### */

void led_on() {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
}

void led_off() {
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
}
