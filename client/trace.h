/*
 * Debugging and tracing functions.
 * 
 * (c) 2021 Thomas Smits
 */

#ifndef trace_h
#define trace_h

// Trace macro for debugging output
#ifdef DEBUG_OUTPUT
#define trace(a) { Serial.print(a); }
#define tracenl(a) { Serial.print(a); Serial.print("\n"); }
#define setup_trace() { Serial.begin(9600); }
#else
#define trace(a)
#define tracenl(a)
#define setup_trace()
#endif

#endif
