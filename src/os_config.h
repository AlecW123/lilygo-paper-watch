#pragma once

// OS Configuration
#define DEVICE_NAME            "z88kat Watch"
#define PREFS_KEY              "lilygo-prefs"

#define PIN_KEY                35
#define PWR_EN                 5
#define BACKLIGHT              33
#define BAT_ADC                34
#define PIN_MOTOR              4

#define SPI_SCK                14
#define SPI_DIN                13
#define EPD_CS                 15
#define EPD_DC                 2
#define SRAM_CS                -1
#define EPD_RESET              17
#define EPD_BUSY               16

// Time Configuration
#define NTP_SERVER1            "pool.ntp.org"
#define NTP_SERVER2            "time.nist.gov"
#define GMT_OFFSET_SEC         (3600 * 1)
#define DAY_LIGHT_OFFSET_SEC   0

// Software Functions Configuration
#define UPDATE_WAKEUP_TIMER_US 60 * 1000000

#define ENABLE_MOTOR           1

// Allow the setting of your WiFi credentials
// If these values are not set the WiFi will be disabled giving longer battery life
#define WIFI_SSID              "PLUSNET-MJC36Q"
#define WIFI_PASSWD            "4arNEymNk4hUrg"

// Set your API Key according to https://openweathermap.org/api
// Add the weather API key
#define WEATHER_API_KEY       ""

// Set your address according to https://openweathermap.org/find eg: London,UK
// And the geo-location will be calculated automatically to set the weather for your location
#define WEATHER_LOCATION   ""