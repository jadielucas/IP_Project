#include <stdio.h>
#include <string.h>
#include "lwip/ip_addr.h"
#include "inc/mqtt.h"
#include "inc/wifi.h"
#include "inc/display.h"

#define MQTT_TOPIC "sensor/sound/pico" // MQTT topic to publish the sound level data

// Structure to store the MQTT client information
static struct mqtt_connect_client_info_t client_info = {
    .client_id = "pico_client", // Client ID
    .client_user = NULL,        // User name
    .client_pass = NULL,        // Password
    .keep_alive = 60,           // Keep alive time
};

// MQTT Client
static mqtt_client_t *global_mqtt_client = NULL;

// Broker IP address
static ip_addr_t broker_ip;

/**
 * @brief Callback function for MQTT connection events.
 * 
 * @param client MQTT client instance.
 * @param arg User-defined argument (unused in this case).
 * @param status Connection status.
 *
 * This function is called when an MQTT connection attempt is completed.
 * It prints whether the connection was successful or failed.
 * 
 * It also tries to reconnect if the connection failed.
 * 
 */

// Callback function for MQTT connection events
void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{

    // Check if the connection was successful
    if (status == MQTT_CONNECT_ACCEPTED)
    {
        printf("Conexão MQTT bem-sucedida!\n"); // Debug message

        ssd1306_draw_string(&disp, 0, 30, 1, "MQTT: Connected"); // Display "MQTT: Connected" on the display
    }
    else
    {
        printf("Falha na conexão MQTT: %d\n", status); // Debug message
        mqtt_client_connect(global_mqtt_client, &broker_ip, MQTT_PORT, mqtt_connection_cb, NULL, &client_info); // Try to reconnect
    }
}

/**
 * @brief Initializes and starts the MQTT client.
 *
 * This function creates a new MQTT client, assigns a broker IP,
 * and attempts to establish a connection.
 * 
 */

void start_mqtt_client(void)
{
    IP4_ADDR(&broker_ip, 5, 196, 78, 28); // Broker IP address

    global_mqtt_client = mqtt_client_new(); // Create a new MQTT client

    // Check if the client was created successfully
    if (!global_mqtt_client)
    {
        printf("Falha ao criar cliente MQTT\n"); // Debug message
        return;
    }

    mqtt_client_connect(global_mqtt_client, &broker_ip, MQTT_PORT, mqtt_connection_cb, NULL, &client_info); // Connect to the broker

    sleep_ms(5000); // Wait 5 seconds for the connection to be established
}

/**
 * @brief Publishes sound level data to an MQTT topic.
 *
 * @param micdata Pointer to a micdata_t structure containing the sound level data.
 *
 * This function checks if the MQTT client/Wi-Fi is connected, checks if dB value is greater than the
 * treshold, formats the sound level data to a string, and publishes it to the "sensor/sound/pico" topic.
 * 
 * It also displays the connection status on the OLED display.
 * If the data is published successfully, it displays a debug message.
 * If there is an error, it displays an error message.
 * If the MQTT client is not connected, it tries to reconnect.
 *
 */

void publish_db_to_mqtt(micdata_t *micdata)
{
    static char payload[6]; // Payload buffer

    // Check if the MQTT client is created/connected, and check if Wi-Fi is connected
    if (global_mqtt_client && mqtt_client_is_connected(global_mqtt_client) && is_wifi_connected())
    {

        ssd1306_clear_area(&disp, 0, 30, 128, 32);               // Clear the "MQTT: Connected" area (if it was previously displayed)
        ssd1306_draw_string(&disp, 0, 30, 1, "MQTT: Connected"); // Display "MQTT: Connected" on the display

        // Check if the dB value is greater than the threshold
        if (micdata->dB > DB_THRESHOLD)
        {
            snprintf(payload, sizeof(payload), "%.2f", micdata->dB); // Format the dB value as a string

            err_t err = mqtt_publish(global_mqtt_client, MQTT_TOPIC, payload, strlen(payload), 0, 0, NULL, NULL); // Publish the dB value to the MQTT topic

            // Check if the data was published successfully
            if (err == ERR_OK)
            {
                ssd1306_clear_area(&disp, 0, 50, 128, 32); // Clear the "Publish ERROR" area

                printf("Dados enviados: %s\n", payload); // Debug message
            }
            else
            {
                ssd1306_draw_string(&disp, 0, 50, 1, "Publish ERROR"); // Display "Publish ERROR" on the display

                printf("Erro ao publicar dados: %d\n", err); // Debug message
            }
        }
    }
    else
    {
        printf("MQTT nÃo conectado\n"); // Debug message

        ssd1306_clear_area(&disp, 0, 30, 128, 32);                  // Clear the "MQTT: Connected" area
        ssd1306_draw_string(&disp, 0, 30, 1, "Local Running");      // Display "Local Running" on the display
        ssd1306_draw_string(&disp, 0, 45, 1, "No MQTT Connection"); // Display "No MQTT Connection" on the display

        mqtt_client_connect(global_mqtt_client, &broker_ip, MQTT_PORT, mqtt_connection_cb, NULL, &client_info); // Try to reconnect
    }
}