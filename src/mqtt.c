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
    IP4_ADDR(&broker_ip, 18,157,172,212);

    struct mqtt_connect_client_info_t client_info = {
        .client_id = "pico_client",
        .client_user = NULL,
        .client_pass = NULL,
        .keep_alive = 60,
    };
    mqtt_client_connect(global_mqtt_client, &broker_ip, MQTT_PORT, mqtt_connection_cb, NULL, &client_info);
}

void publish_db_to_mqtt(micdata_t *micdata)
{
    if (global_mqtt_client && mqtt_client_is_connected(global_mqtt_client))
    {
        char payload[32];
        snprintf(payload, sizeof(payload), "%.2f", micdata->dB);
        const char *topic = "sensor/sound/pico";

        err_t err = mqtt_publish(global_mqtt_client, topic, payload, strlen(payload), 1, 0, NULL, NULL);
        if (err == ERR_OK)
        {
            printf("Dados enviados: %s\n", payload);
            ssd1306_clear_area(&disp, 0, 30, 78, 32);
        }
        else
        {
            printf("Erro ao publicar dados: %d\n", err);
            ssd1306_draw_string(&disp, 0, 30, 1, "Publish ERROR");
        }
    }
    else
    {
        printf("MQTT nÃƒo conectado\n");
        ssd1306_draw_string(&disp, 0, 30, 1, "MQTT ERROR");
        ssd1306_draw_string(&disp, 0, 45, 1, "Press RESET");
    }
}