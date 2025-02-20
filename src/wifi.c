#include <stdio.h>
#include "inc/wifi.h"
#include "libs/lwipopts.h"
#include "inc/display.h"

static uint8_t reconnection_attempts = 0;

/**
 * @brief Initializes the Wi-Fi connection.
 *
 * This function initializes the Wi-Fi module and attempts to connect to a Wi-Fi network.
 * If initialization or connection fails, it prints an error message and returns 1.
 * If the connection is successful, it prints a confirmation message.
 *
 * @return int Returns 0 on success, 1 on failure.
 */

int wifi_init()
{
    if (cyw43_arch_init())
    {
        printf("Erro ao inicializar o Wi-Fi\n");
        return 1;
    }
    cyw43_arch_enable_sta_mode();
    printf("Conectando ao Wi-Fi...\n");
    
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 8000))
    {
        printf("Falha ao conectar ao Wi-Fi\n");
        ssd1306_clear_area(&disp, 5, 28, 128, 50);
        return 1;
    }
    else
    {
        printf("Wi-Fi conectado!\n");
        ssd1306_clear_area(&disp, 5, 28, 128, 50);
    }
    return 0;
}

bool is_wifi_connected()
{
    int status = cyw43_wifi_link_status(&cyw43_state, CYW43_ITF_STA);

    if (status == CYW43_LINK_JOIN || status == CYW43_LINK_UP)
    {
        ssd1306_clear_area(&disp, 0, 0, 128, 16);
        
        reconnection_attempts = 0;

        return true;
    }
    else
    {
        return false;
    }
}

void check_wifi_connection()
{

    while (reconnection_attempts < 6 && !is_wifi_connected())
    {
        ssd1306_clear(&disp);
        ssd1306_draw_string(&disp, 0, 0, 1, "Wi-Fi: Reconnecting..");
        ssd1306_show(&disp);

        if (!is_wifi_connected())
        {
            
            printf("Wi-Fi desconectado. Tentando reconectar...\n");
            if (cyw43_arch_wifi_connect_async(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK) == 0)
            {
                printf("Reconectando...\n");

                reconnection_attempts++;

                sleep_ms(10000);
            }
            else
            {
                printf("Erro ao iniciar reconexão\n");
            }
        }
    }
}