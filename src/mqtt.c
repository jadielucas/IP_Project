#include <stdio.h>
#include "lwip/ip_addr.h"
#include "lwip/apps/mqtt.h"
#include "inc/mqtt.h"

mqtt_client_t *global_mqtt_client = NULL;

void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
    if (status == MQTT_CONNECT_ACCEPTED)
    {
        printf("Conexão MQTT bem-sucedida!\n");
    }
    else
    {
        printf("Falha na conexão MQTT: %d\n", status);
    }
}

void start_mqtt_client(void)
{
    global_mqtt_client = mqtt_client_new();
    if (!global_mqtt_client)
    {
        printf("Falha ao criar cliente MQTT\n");
        return;
    }
    ip_addr_t broker_ip;
    IP4_ADDR(&broker_ip, 52, 28, 26, 70);

    struct mqtt_connect_client_info_t client_info = {
        .client_id = "pico_client",
        .client_user = NULL,
        .client_pass = NULL,
        .keep_alive = 60,
    };
    mqtt_client_connect(global_mqtt_client, &broker_ip, MQTT_PORT, mqtt_connection_cb, NULL, &client_info);
}