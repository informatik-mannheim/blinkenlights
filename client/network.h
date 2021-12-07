/*
 * Network functions.
 * 
 * (c) 2021 Thomas Smits
 */
#ifndef network_h
#define network_h

/**
 * Setup network functionality.
 */
void setup_network();

/**
 * Get the current timestamp in milliseconds from the
 * server.
 */
ulong get_server_time();

#endif
