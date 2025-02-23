#include <stdio.h>
#include "inc/wifi.h"
#include "inc/display.h"

#define WIFI_SSID "Galaxy"
#define WIFI_PASSWORD "12345678"

static uint8_t reconnection_attempts = 0;

/**
 * @brief Initializes the Wi-Fi connection.
 *
 * This function initializes the Wi-Fi module and attempts to connect to a Wi-Fi network.
 * 
 * If initialization or connection fails, it prints an error message and returns 1.
 * If the connection is successful, it prints a confirmation message.
 * It also clears "SilentPico" logo from the display.
 *
 * @return int Returns 0 on success, 1 on failure.
 */

int wifi_init()
{
    // Initialize the Wi-Fi module
    if (cyw43_arch_init())
    {
        printf("Erro ao inicializar o Wi-Fi\n"); // Debug message
        return 1;
    }
    
    cyw43_arch_enable_sta_mode();       // Enable the station mode
    printf("Conectando ao Wi-Fi...\n"); // Debug message
    
    // Connect to the Wi-Fi network
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 8000))
    {
        printf("Falha ao conectar ao Wi-Fi\n");     // Debug message
        return 1;
    }
    else
    {
        ssd1306_clear(&disp);         // Clear "SilentPico" logo from the display            
        printf("Wi-Fi conectado!\n"); // Debug message
    }
    return 0;
}

/**
 * @brief Checks if the Wi-Fi connection is active.
 *
 * This function checks if the Wi-Fi connection is active by calling the cyw43_wifi_link_status function.
 * 
 * If the connection is active, it clears the display and returns true.
 * If the connection is not active, it returns false.
 * It also resets the reconnection attempts counter.
 *
 * @return bool Returns true if the Wi-Fi connection is active, false otherwise.
 */

bool is_wifi_connected()
{
    int status = cyw43_wifi_link_status(&cyw43_state, CYW43_ITF_STA); // Get the Wi-Fi connection status

    // Check if the connection is active
    if (status == CYW43_LINK_JOIN || status == CYW43_LINK_UP)
    {
        ssd1306_clear_area(&disp, 0, 0, 128, 16); // Clear "Wi-Fi: Reconnecting.." message
        
        reconnection_attempts = 0; // Reset the reconnection attempts counter

        return true; // Return true if the connection is active
    }
    else
    {
        return false; // Return false if the connection is not active
    }
}

/**
 * @brief Checks the Wi-Fi connection status and attempts to reconnect if necessary.
 *
 * This function checks the Wi-Fi connection status by calling the is_wifi_connected function.
 * 
 * If the connection is not active, it attempts to reconnect to the Wi-Fi network.
 * If the reconnection fails after 6 attempts, it prints an error message and returns.
 */

void check_wifi_connection()
{
    // Loop to try Wi-Fi reconnection for 1 minute
    while (reconnection_attempts < 7 && !is_wifi_connected())
    {
        ssd1306_clear(&disp); // Clear the display
        ssd1306_draw_string(&disp, 0, 0, 1, "Wi-Fi: Reconnecting.."); // Display "Wi-Fi: Reconnecting.." message
        ssd1306_show(&disp);  // Update the display

        // If Wi-Fi is not connected, try to reconnect
        if (!is_wifi_connected())
        {
            
            printf("Wi-Fi desconectado. Tentando reconectar...\n"); // Debug message

            //Try reconnecting to the Wi-Fi network
            if (cyw43_arch_wifi_connect_async(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK) == 0)
            {
                printf("Reconectando...\n"); // Debug message

                reconnection_attempts++;    // Increment the reconnection attempts counter

                sleep_ms(10000);           // Wait 10 seconds before the next reconnection attempt
            }
            else
            {
                printf("Erro ao iniciar reconexão\n"); // Debug message
            }
        }
    }
}