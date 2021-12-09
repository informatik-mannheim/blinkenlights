/**
 * Hardware access functions.
 *
 * (c) 2021 Thomas Smits
 */

#include <FastLED.h>

#ifndef hardware_h
#define hardware_h

/* Number of LEDs attached to DATA_PIN */
#define NUM_LEDS 16

/* LEDs data structure */
CRGB leds[NUM_LEDS];

/**
 * Initialize the hardware.
 */
void setup_hardware();

/**
 * Get the devices ID by reading the setting
 * of the DIP switch connected to the ports
 * defined by the constants.
 *
 * @return the id of the device as set by the
 */
uint get_id();

#endif
