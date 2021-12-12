/*
 * Time management functions.
 * 
 * (c) 2021 Thomas Smits
 */

#include "types.h"

#ifndef time_h
#define time_h

/**
  Convert hour, minute and second to timestamp.

  @param hour hour
  @param minute minute
  @param second second
  @param msec milliseconds
  @param (out) timestamp in milliseconds
*/
void time_to_millis(ushort hour, ushort minute, ushort second, ushort msec, ulong* timestamp);

/**
  Convert timestamp to hour, minute, second.

  @param timestamp timestamp in milliseconds
  @param (out) hour hour
  @param (out) minute minute
  @param (out) second second
  @param (out) milliseconds
*/
void millis_to_time(ulong timestamp, ushort* hour, ushort* minute, ushort* second, ushort* msec);

/**
  Manage time wrap around on hour and minute.
  If minute is > 60, hour is incremented.
  If hour is > 24, it is set to hour =- 24.

  @param hour (in, out) hour
  @param minute (int, out) minute
*/
void time_wrap(ushort* hour, ushort* minute);

/**
 * Check, if the val1 lies within a epsilon environment around val2.
 *
 * @param val1 first value
 * @param val2 second value
 * @return true if the value is in the interval
 * @return false if the value is not in the interval
 */
bool time_compare(ulong val1, ulong val2);

/**
 * Get the current timestamp (synchronized with the server clock)
 *
 * @return ulong the current timestamp
 */
ulong get_time();

/**
 * Set up the time management.
 */
void setup_time();

#endif
