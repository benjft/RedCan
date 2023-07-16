#ifndef WIFI_AP_HPP_
#define WIFI_AP_HPP_

#include <esp_wifi.h>
#include <memory>
#include "Errors.hpp"

namespace benjft {
    class WifiAp {
        private:
        wifi_init_config_t *wifi_config;
        bool is_initialized;
        
        error_t initializeWifi(void);


        WifiAp(void);

        public:
        WifiAp(WifiAp const&) = delete;
        void operator=(WifiAp const&) = delete;
    };
};
#endif WIFI_AP_HPP_