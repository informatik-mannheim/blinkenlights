/**
 * Collection of different animations.
 *
 * (c) 2021 Thomas Smits
 */

#include "config.h"
#include "animations.h"

/**
 * Initialize the animations available.
 */
void setup_animations() {
    animation_functions *functions = (animation_functions*) malloc(sizeof(animation_functions));

    functions->num_animations = 2;

    functions->callback = (animation_function*) calloc(functions->num_animations, sizeof(animation_function));

    int i = 0;

    functions->callback[i++] = led_on;
    functions->callback[i++] = led_off;

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
