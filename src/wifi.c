#include "inc/wifi.h"

int wifi_init()
{
    if (cyw43_arch_init())
    {
        printf("Erro ao inicializar o Wi-Fi\n");
        return 1;
    }
    cyw43_arch_enable_sta_mode();
    printf("Conectando ao Wi-Fi...\n");
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 5000))
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