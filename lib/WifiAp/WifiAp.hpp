#ifndef WIFI_AP_HPP_
#define WIFI_AP_HPP_

#include <esp_wifi.h>

namespace benjft {
    class WifiAp {
        private:
        static wifi_init_config_t wifi_config;
        static bool is_initialized;
        
        void initializeWifi(void);

        public:
        WifiAp(void);
    };
}
#endif WIFI_AP_HPP_