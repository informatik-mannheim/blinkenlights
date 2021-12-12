/**
 * Configuration for blinkenlights.
 *
 * (c) 2021 Thomas Smits
 */

#ifndef config_h
#define config_h

/** Get passwords */
#include "config_secret.h"

/** Server providing timestamps */
#define TIME_SERVER "192.168.0.200"
#define TIME_PORT 2000

/** Server providing animations */
#define ANIMATION_SERVER "192.168.0.200"
#define ANIMATION_PORT 2001

/* Fetch server time every 100 seconds */
#define SERVER_TIME_FETCH_INTERVAL 100000

#endif
