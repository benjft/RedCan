#include <memory>

#include <WifiAp.hpp>


using namespace std;
using namespace benjft;

shared_ptr<WifiAp> wifiAp;

extern "C" void app_main(void)
{
    wifiAp = make_shared<WifiAp>();
    esp_restart();
}
