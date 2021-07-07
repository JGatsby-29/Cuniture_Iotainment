// adafruit 이름, 키
#define IO_USERNAME "JGatsby"
#define IO_KEY "aio_ekfk14xJ9hhrk76ls6mAe4wk0ugG"

// wifi
#define WIFI_SSID "yyh"
#define WIFI_PASS "1q2w3e4r"

#include "AdafruitIO_WiFi.h"

#if defined(USE_AIRLIFT) || defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE) ||         \
    defined(ADAFRUIT_PYPORTAL)

#if !defined(SPIWIFI_SS)
#define SPIWIFI SPI
#define SPIWIFI_SS 10
#define NINA_ACK 9
#define NINA_RESETN 6
#define NINA_GPIO0 -1
#endif
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS, SPIWIFI_SS,
                   NINA_ACK, NINA_RESETN, NINA_GPIO0, &SPIWIFI);
#else
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
#endif
