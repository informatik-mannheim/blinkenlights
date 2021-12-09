/*
 * Network functions.
 *
 * (c) 2021 Thomas Smits
 */
#include "WiFi.h"
#include "config.h"
#include "trace.h"
#include "network.h"

/**
 * Initialize the network connection.
 */
void setup_network() {
    // Connect to the Wireless network
    WiFi.mode(WIFI_STA);
    WiFi.begin(WLAN_SSID, WLAN_PASSWORD);

    int status;

    while ((status = WiFi.status()) != WL_CONNECTED) {
        delay(500);
        trace("Connecting to WiFi... Status = ");
        tracenl(status);
    }

    tracenl("Connected to the WiFi network");
    trace("IP = ");
    tracenl(WiFi.localIP());
}

/**
 * Get the current timestamp in milliseconds from the
 * server.
 */
ulong get_server_time() {

    WiFiClient client;

    if (!client.connect(TIME_SERVER, TIME_PORT)) {
        Serial.println("Connection to host failed");
        return 0;
    }

    String line = client.readStringUntil('\r');
    ulong timestamp = line.toInt();

    client.stop();

    return timestamp;
}
