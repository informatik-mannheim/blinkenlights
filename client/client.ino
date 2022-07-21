/**
 * Blinkenlights client.
 *
 * (c) 2021 Thomas Smits
 */

#include <WiFi.h>

#undef DEBUG_OUTPUT

#include "trace.h"
#include "config.h"
#include "time.h"
#include "animation.h"
#include "animations.h"
#include "hardware.h"

/** Throttle the loop to an invocation every X milliseconds */
#define INTERVAL 10

#define ANIMATION_INTERVAL (1000 / INTERVAL)

uint id = 0; // the id of this client

// the setup function runs once when you press reset or power the board
void setup() {

    setup_trace();     
    setup_animation();
    //setup_network();
    setup_animations();
    setup_hardware();
    //setup_time();
    
    // read our own id from the DIP switch
    id = get_id();
    trace("Client startet. ID=");
    tracenl(id);
}

ulong loop_count = 0;   // wraparound intended

void loop() {
    //loop_animation(id);
    
    loop_count++; // wraparound intended

    delay(INTERVAL);
/*
// Test run of all animation commands         
     for (int i = 0; i < animations->num_callbacks; i++) {                                       
       animations->callbacks[i](id, 0);            
       delay(2000);                                
     } 
    // Test run of all animation commands
    */
      animations->callbacks[5](id, 0);
      animations->callbacks[5](id, 1);
      //animations->callbacks[4](id, 0);
      

}
