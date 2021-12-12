/**
 * Handling of animations for blinkenlights.
 *
 * (c) 2021 Thomas Smits
 */

#include <WiFi.h>
#include "animation.h"
#include "trace.h"
#include "animations.h"

#define LED_BUILTIN 2

/**
 * Fetch the next animation from the server.
 *
 * @param id the id of this client
 * @param server IP address of the server
 * @param port port of the server
 * @return animation* animation structure. Must be freed by the caller.
 */
animation* read_animation(const uint id, const char* server, const int port) {

    WiFiClient client;

    if (!client.connect(server, port)) {
        tracenl("Connection to host failed");
        return 0;
    }

    // Send our id to the server
    char id_string[3] = {'0', '0', '\0' };

    if (id < 10) {
      itoa(id, id_string + 1, 10);
    }
    else {
      itoa(id, id_string, 10);
    }
    
    client.println(id_string);
     
    // Allocate memory
    animation *result = (animation*) malloc(sizeof(animation));

    // Read data from server
    result->start_time  = client.readStringUntil('\n').toInt();;
    result->cycle_pause = client.readStringUntil('\n').toInt();;
    result->repeat      = client.readStringUntil('\n').toInt();

    uint num_elements = client.readStringUntil('\n').toInt();

    result->num_elements = num_elements;
    result->elements = (animation_element*) calloc(num_elements, sizeof(animation_element));

    for (int i = 0; i < num_elements; i++) {
        ulong duration = client.readStringUntil('\n').toInt();
        ulong command = client.readStringUntil('\n').toInt();
        uint command_param = client.readStringUntil('\n').toInt();
        result->elements[i].duration = duration;
        result->elements[i].command = command;
        result->elements[i].command_param = command_param;
    }

    client.stop();

    trace("Read animation...");
    tracenl(get_time());
    trace("  Start      : ");
    tracenl(result->start_time);
    trace("  Cycle-Pause: ");
    tracenl(result->cycle_pause);
    trace("  Repeat     : ");
    tracenl(result->repeat);
    trace("  Steps      : ");
    tracenl(result->num_elements);
    

    return result;
}

/**
 * Free the animation allocated by the read_animation function.
 *
 * @param ani animation to be freed
 */
void free_animation(animation *ani) {
    free(ani->elements);
    free(ani);

    tracenl("Freed animation...");
}

/**
 * Plays the animation.
 *
 * @param id the id of this client
 * @param animation animation to be played
 */
void play_animation(const uint id, animation *animation) {

    ulong start_millis = millis();
    
    ulong time_sum = animation->start_time;

    for (int i = 0; i < animation->num_elements; i++) {

        trace("Playing animation-step: ");
        tracenl(i);

        ulong time = get_time();
        animation_element e = animation->elements[i];

        if (e.command < animations->num_callbacks) {
            // Call the animation function
            animations->callbacks[e.command](id, e.command_param);
        }

        while (time_sum + e.duration > get_time()) {
            // busy wait with 5 milliseconds steps
            delay(5);
        }

        time_sum += e.duration;
    }

    ulong duration = millis() - start_millis;

    animation->actual_duration = duration;
    
    trace("Duration of animation: ");
    tracenl(animation->actual_duration);
}

/**
 * Initialize the animation.
 */
void setup_animation() {
    // configure builtin LED
    pinMode(LED_BUILTIN, OUTPUT);
}

/**
 * Function called from the main loop function.
 *
 * @param id the id of this client
 */
void loop_animation(const uint id) {

    static animation *ani = NULL;
    
    ulong current_time = get_time();

    if (!ani) {
        ani = read_animation(id, ANIMATION_SERVER, ANIMATION_PORT);
    }

    if (ani && time_compare(ani->start_time, current_time)) {
        tracenl("Animation start");
        play_animation(id, ani);

        if (ani->repeat > 0) {
            ani->start_time += ani->cycle_pause + ani->actual_duration;
            ani->repeat--;
            trace("Repeat: ");
            tracenl(ani->repeat);
        }
    }
    else if (ani) {
        trace("Time till animation starts: ");
        tracenl((int) (ani->start_time - current_time));
    }

    if (ani && (ani->start_time < current_time)) {
        free_animation(ani);
        ani = NULL;
    }
}
