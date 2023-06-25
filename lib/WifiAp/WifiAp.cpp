#include "WifiAp.hpp"
#include <esp_wifi.h>
#include <iostream>

using namespace benjft;

wifi_init_config_t 
WifiAp::wifi_config = WIFI_INIT_CONFIG_DEFAULT();

bool WifiAp::is_initialized = false;

void benjft::WifiAp::initializeWifi(void) {
    esp_err_t err = esp_wifi_init(&wifi_config);
    if (err == ESP_OK) {
        std::cout << "esp_wifi initialized" << std::endl;
        is_initialized = true;
    } else if (err == ESP_ERR_NO_MEM) {
        std::cerr << "Failed to initialize esp_wifi due to lack of memory" << std::endl;
    } else {
        std::cerr << "Unknown error occurred when initializing eps_wifi : " << err << std::endl; 
    }
};

WifiAp::WifiAp(void)
{
    if (!is_initialized) {
        this->initializeWifi();
    }
};
