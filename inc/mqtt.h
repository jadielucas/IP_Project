#ifndef MQTT_H
#define MQTT_H

#include "inc/mic.h"
#include "lwip/apps/mqtt.h"

#define MQTT_TOPIC "sensor/sound/pico"

void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status);
void start_mqtt_client(void);
void publish_db_to_mqtt(micdata_t *micdata);

#endif