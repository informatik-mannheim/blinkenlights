/**
 * Hardware access functions.
 *
 * (c) 2021 Thomas Smits
 */

#include "types.h"

/* Pins for DIP switch */
#define DIP0_PIN 25
#define DIP1_PIN 33
#define DIP2_PIN 32
#define DIP3_PIN 35

/* Pin the neopixel stripe is attached to */
#define DATA_PIN 4

/**
 * Initialize the hardware.
 */
void setup_hardware() {
    // set the DIP switch pins to input and activate internal
    // pulldown resistor
    pinMode(DIP0_PIN, INPUT_PULLDOWN);
    pinMode(DIP1_PIN, INPUT_PULLDOWN);
    pinMode(DIP2_PIN, INPUT_PULLDOWN);
    pinMode(DIP3_PIN, INPUT_PULLDOWN);

    // Initialize FastLED lib
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

/**
 * Get the devices ID by reading the setting
 * of the DIP switch connected to the ports
 * defined by the constants.
 *
 * @return the id of the device as set by the
 */
uint get_id() {

    int p0 = digitalRead(DIP0_PIN);
    int p1 = digitalRead(DIP1_PIN);
    int p2 = digitalRead(DIP2_PIN);
    int p3 = digitalRead(DIP3_PIN);

    uint id = (uint) (p0 + (p1 * 2) + (p2 * 4) + (p3 * 8));

    trace("get_id: ");
    trace(p0);
    trace("-");
    trace(p1);
    trace("-");
    trace(p2);
    trace("-");
    trace(p3);
    trace("=");
    tracenl(id);

    return id;
}
