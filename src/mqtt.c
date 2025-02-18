#include "inc/mqtt.h"
#include "inc/wifi.h"

struct mqtt_connect_client_info_t client_info = {
    .client_id = "pico_client",
    .client_user = NULL,
    .client_pass = NULL,
    .keep_alive = 60,
};

mqtt_client_t *global_mqtt_client = NULL;
ip_addr_t broker_ip;

/**
 * @brief Callback function for MQTT connection events.
 *
 * This function is called when an MQTT connection attempt is completed.
 * It prints whether the connection was successful or failed.
 *
 * @param client MQTT client instance.
 * @param arg User-defined argument (unused in this case).
 * @param status Connection status.
 */

void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
    if (status == MQTT_CONNECT_ACCEPTED)
    {
        printf("Conexão MQTT bem-sucedida!\n");
    }
    else
    {
        mqtt_client_connect(global_mqtt_client, &broker_ip, MQTT_PORT, mqtt_connection_cb, NULL, &client_info);
        printf("Falha na conexão MQTT: %d\n", status);
    }
}

/**
 * @brief Initializes and starts the MQTT client.
 *
 * This function creates a new MQTT client, assigns a broker IP,
 * and attempts to establish a connection.
 */

void start_mqtt_client(void)
{
    IP4_ADDR(&broker_ip, 18, 195, 118, 49);

    global_mqtt_client = mqtt_client_new();
    if (!global_mqtt_client)
    {
        printf("Falha ao criar cliente MQTT\n");
        return;
    }

    mqtt_client_connect(global_mqtt_client, &broker_ip, MQTT_PORT, mqtt_connection_cb, NULL, &client_info);
}

/**
 * @brief Publishes sound level data to an MQTT topic.
 *
 * This function checks if the MQTT client is connected, formats the sound level data,
 * and publishes it to the "sensor/sound/pico" topic if dB value - last db value is greater/equal 2.
 *
 * @param micdata Pointer to a micdata_t structure containing the sound level data.
 */

void publish_db_to_mqtt(micdata_t *micdata)
{
    static float last_db;
    static char payload[10];

    if (global_mqtt_client && mqtt_client_is_connected(global_mqtt_client) && is_wifi_connected())
    {
        if (fabs(micdata->dB - last_db) >= 2.0)
        {
            snprintf(payload, sizeof(payload), "%.2f", micdata->dB);

            err_t err = mqtt_publish(global_mqtt_client, MQTT_TOPIC, payload, strlen(payload), 0, 0, NULL, NULL);
            if (err == ERR_OK)
            {
                ssd1306_clear_area(&disp, 0, 30, 128, 32);
                ssd1306_draw_string(&disp, 0, 30, 1, "MQTT: Connected");
                printf("Dados enviados: %s\n", payload);
                last_db = micdata->dB;
            }
            else
            {
                ssd1306_clear_area(&disp, 0, 30, 90, 32);
                ssd1306_draw_string(&disp, 0, 30, 1, "Publish ERROR");

                printf("Erro ao publicar dados: %d\n", err);
            }
        }
    }
    else
    {
        printf("MQTT nÃo conectado\n");

        ssd1306_clear_area(&disp, 0, 30, 128, 32);
        ssd1306_draw_string(&disp, 0, 30, 1, "Local Running");
        ssd1306_draw_string(&disp, 0, 45, 1, "No MQTT Connection");

        mqtt_client_connect(global_mqtt_client, &broker_ip, MQTT_PORT, mqtt_connection_cb, NULL, &client_info);
    }
}
