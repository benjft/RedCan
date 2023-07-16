#include <esp_wifi.h>

#include "Errors.hpp"
#include "WifiAp.hpp"

using namespace benjft;

benjft::error_t WifiAp::initializeWifi(void) {
    esp_err_t err = esp_wifi_init(wifi_config);
    if (err == ESP_OK) {
        is_initialized = true;
    } else if (err == ESP_ERR_NO_MEM) {
        return MAKE_ERROR2("Failed to initialize esp_wifi due to lack of memory", err);
    } else {
        return MAKE_ERROR2("Unknown error occurred when initializing eps_wifi : " + std::to_string(err), err); 
    }
    return nullptr;
};

WifiAp::WifiAp(void)
{
    is_initialized = false;
    wifi_init_config_t conf = WIFI_INIT_CONFIG_DEFAULT();
    wifi_config = new wifi_init_config_t(conf);
};
