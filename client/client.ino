/**
 * Blinkenlights client.
 * 
 * (c) 2021 Thomas Smits
 */

#include <WiFi.h>

#define DEBUG_OUTPUT

#include "trace.h"
#include "config.h"
#include "time.h"
#include "animation.h"
#include "animations.h"

/** Throttle the loop to an invocation every X milliseconds */
#define INTERVAL 10

// the setup function runs once when you press reset or power the board
void setup() {
    setup_trace();
    setup_animation();
    setup_network();
    setup_animations();
}

ulong loop_count = 0;   // wraparound intended

void loop() {
    loop_animation();

    loop_count++; // wraparound intended

    delay(INTERVAL);
}
