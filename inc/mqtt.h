#ifndef MQTT_H
#define MQTT_H

#include <stdio.h>
#include <string.h>
#include "lwip/apps/mqtt.h"
#include "lwip/ip_addr.h"
#include "libs/ssd1306.h"
#include "inc/mic.h"
#include "inc/display.h"

extern mqtt_client_t *global_mqtt_client;

void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status);
void start_mqtt_client(void);
void publish_db_to_mqtt(micdata_t *micdata);

#endif