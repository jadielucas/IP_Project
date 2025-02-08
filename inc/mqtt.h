#ifndef MQTT_H
#define MQTT_H

#include "lwip/apps/mqtt.h"

extern mqtt_client_t *global_mqtt_client;

void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status);
void start_mqtt_client(void);

#endif