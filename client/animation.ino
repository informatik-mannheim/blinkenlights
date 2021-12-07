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
 * @param server IP address of the server
 * @param port port of the server
 * @return animation* animation structure. Must be freed by the caller.
 */
animation* read_animation(const char* server, const int port) {

    WiFiClient client;

    if (!client.connect(server, port)) {
        tracenl("Connection to host failed");
        return 0;
    }

    // Allocate memory
    animation *result = (animation*) malloc(sizeof(animation));

    // Read data from server
    result->start_time = client.readStringUntil('\n').toInt();;
    result->cycle_pause = client.readStringUntil('\n').toInt();;
    result->repeat = client.readStringUntil('\n').toInt();

    uint num_elements = client.readStringUntil('\n').toInt();

    result->num_elements = num_elements;
    result->elements = (animation_element*) calloc(num_elements, sizeof(animation_element));

    for (int i = 0; i < num_elements; i++) {
        ulong duration = client.readStringUntil('\n').toInt();
        ulong command = client.readStringUntil('\n').toInt();
        result->elements[i].duration = duration;
        result->elements[i].command = command;
    }

    client.stop();

    tracenl("Read animation...");
    trace("Start: ");
    tracenl(result->start_time);

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
 * @param animation animation to be played
 */
void play_animation(animation *animation) {

    ulong time_sum = animation->start_time;

    for (int i = 0; i < animation->num_elements; i++) {

        trace("Playing animation-step: ");
        tracenl(i);

        ulong time = get_time();
        animation_element e = animation->elements[i];

        if (e.command < animations->num_animations) {
            // Call the animation function
            animations->callback[e.command]();
        }

        while (time_sum + e.duration > get_time()) {
            // busy wait
            delay(5);
        }

        time_sum += e.duration;
    }
}

/**
 * Initialize the animation.
 */
void setup_animation() {
    pinMode(LED_BUILTIN, OUTPUT);
}

/**
 * Function called from the main loop function.
 */
void loop_animation() {

    static animation *ani = NULL;

    if (!ani) {
        ani = read_animation(ANIMATION_SERVER, ANIMATION_PORT);
    }

    ulong current_time = get_time();

    if (ani && time_compare(ani->start_time, current_time)) {
        tracenl("Animation start");
        play_animation(ani);

        if (ani->repeat > 0) {
            ani->start_time += ani->cycle_pause;
            ani->repeat--;
            trace("Repeat: ");
            tracenl(ani->repeat);
        }
    }

    if (ani && (ani->start_time < current_time)) {
        free_animation(ani);
        ani = NULL;
    }
}
