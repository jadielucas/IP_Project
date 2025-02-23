#ifndef MQTT_H
#define MQTT_H

#include "inc/mic.h"           // Header for microphone data structures
#include "lwip/apps/mqtt.h"    // LWIP MQTT client library

/**
 * @brief MQTT connection callback function.
 *
 * This function is called when the MQTT client establishes or loses a connection
 * with the broker. It handles connection events and updates the client status.
 *
 * @param client Pointer to the MQTT client instance.
 * @param arg User-defined argument (can be NULL if not used).
 * @param status Connection status (e.g., connected, disconnected, or error states).
 */
void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status);

/**
 * @brief Initializes and starts the MQTT client.
 *
 * This function sets up the MQTT client, establishes a connection to the broker,
 * and prepares it for publishing and subscribing to topics.
 */
void start_mqtt_client(void);

/**
 * @brief Publishes the microphone dB value to the MQTT broker.
 *
 * This function takes the decibel value from the micdata structure and sends it
 * to a predefined MQTT topic, enabling remote monitoring or data logging.
 *
 * @param micdata Pointer to the micdata_t structure containing the current dB value.
 */
void publish_db_to_mqtt(micdata_t *micdata);

#endif
