/*
 * Time management functions.
 *
 * (c) 2021 Thomas Smits
 */

#include "WiFi.h"
#include "time.h"
#include "trace.h"
#include "config.h"
#include "network.h"

#define MILLIS_PER_DAY (24L*60*60*1000)
#define MILLIS_PER_HOUR (60L*60*1000)
#define MILLIS_PER_MINUTE (60L*1000)
#define MILLIS_PER_SECOND (1000L)

/**
  Convert hour, minute and second to timestamp.

  @param hour hour
  @param minute minute
  @param second second
  @param msec milliseconds
  @param (out) timestamp in milliseconds
*/
void time_to_millis(ushort hour, ushort minute, ushort second, ushort msec, ulong* timestamp) {
  *timestamp = hour * MILLIS_PER_HOUR
      + minute * MILLIS_PER_MINUTE
      + second * MILLIS_PER_SECOND;
}

/**
  Convert timestamp to hour, minute, second.

  @param timestamp timestamp in milliseconds
  @param (out) hour hour
  @param (out) minute minute
  @param (out) second second
  @param (out) milliseconds
*/
void millis_to_time(ulong timestamp, ushort* hour, ushort* minute, ushort* second, ushort* msec) {

    // handle wraparound of day
    while (timestamp > MILLIS_PER_DAY) {
        timestamp -= MILLIS_PER_DAY;
    }

    *hour = timestamp / MILLIS_PER_HOUR;

    // remove hour part from timestamp
    timestamp -= *hour * MILLIS_PER_HOUR;

    *minute = timestamp / MILLIS_PER_MINUTE;

    // remove minute part from timestamp
    timestamp -= *minute * MILLIS_PER_MINUTE;

    *second = timestamp / MILLIS_PER_SECOND;

    *msec = timestamp % MILLIS_PER_SECOND;
}

/**
  Manage time wrap around on hour and minute.
  If minute is > 60, hour is incremented.
  If hour is > 24, it is set to hour =- 24.

  @param hour (in, out) hour
  @param minute (int, out) minute
*/
void time_wrap(ushort* hour, ushort* minute) {
    while (*minute >= 60) {
        *minute -= 60;
        *hour++;
    }

    while (*hour >= 24) {
        *hour -= 24;
    }
}

/**
 * Get the current timestamp (synchronized with the server clock)
 *
 * @return ulong the current timestamp
 */
ulong get_time() {

    static ulong start_millis = millis();    // internal clock at first call
    static ulong timestamp = 0;              // current timestamp
    static ulong last_server_time_fetch = 0; // last time we asked the server

    if (timestamp >= last_server_time_fetch + SERVER_TIME_FETCH_INTERVAL || timestamp == 0) {
        // We should get a fresh time from the server
        ulong old_ts = timestamp;

        // sync time with server
        timestamp = get_server_time();

        // calculate internal clock skew
        long skew = timestamp - (old_ts + millis() - start_millis);

        trace("Time synched from server: ");
        trace(timestamp);
        trace(" (");
        trace(skew);
        tracenl( ")");

        start_millis = millis();
        last_server_time_fetch = timestamp;
    }
    else {
        // calculate next timestamp based on internal clock
        ulong m = millis();
        timestamp += m - start_millis;
        start_millis = m;
    }

    return timestamp;
}

#define EPSILON 100

/**
 * Check, if the val1 lies within a epsilon environment around val2.
 *
 * @param val1 first value
 * @param val2 second value
 * @return true if the value is in the interval
 * @return false if the value is not in the interval
 */
bool time_compare(ulong val1, ulong val2) {
    return ((val2 - 2*EPSILON < val1) && (val1 < val2 + 2*EPSILON));
}


/**
 * Set up the time management.
 */
void setup_time() {
    // call get_time once to retrieve the server time
    get_time();
}
