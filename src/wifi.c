#include "inc/wifi.h"

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