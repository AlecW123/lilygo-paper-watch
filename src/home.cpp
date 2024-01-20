#include "home.h"

const char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

const char *days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

void drawHomeUI(GxEPD_Class *display, ESP32Time *rtc, int batteryStatus) {
  display->fillScreen(GxEPD_WHITE);
  display->setTextColor(GxEPD_BLACK);
  display->setTextWrap(false);

  // Time
  display->setFont(&Outfit_80036pt7b);
  String hoursFiller = rtc->getHour(true) < 10 ? "0" : "";
  String minutesFiller = rtc->getMinute() < 10 ? "0" : "";
  String timeStr = hoursFiller + String(rtc->getHour(true)) + ":" + minutesFiller + String(rtc->getMinute());
  printCenterString(display, timeStr.c_str(), 100, 118);

  // Display the Date
  display->setFont(&Outfit_60011pt7b);
  printCenterString(display, String(String(days[rtc->getDayofWeek()]) + ", " + String(months[rtc->getMonth()]) + " " + String(rtc->getDay())).c_str(),
                    100, 158);

  // Battery
  printRightString(display, String(String(batteryStatus) + "%").c_str(), 166, 22);

  const unsigned char *icon_battery_small_array[6] = {epd_bitmap_icon_battery_0_small,  epd_bitmap_icon_battery_20_small,
                                                      epd_bitmap_icon_battery_40_small, epd_bitmap_icon_battery_60_small,
                                                      epd_bitmap_icon_battery_80_small, epd_bitmap_icon_battery_100_small};
  display->drawBitmap(170, 2, icon_battery_small_array[batteryStatus / 20], 28, 28, GxEPD_BLACK);

  // Status icons
  // Wifi
  // display->drawBitmap(2, 2, icon_wifi_small, 28, 28, GxEPD_BLACK);
  // BLE Tooth
  // display->drawBitmap(30, 2, icon_no_ble_small, 28, 28, GxEPD_BLACK);
}

/**
 * Show the Wifi is disabled icon (indicates that the wifi connection failed)
 */
void disableWifiDisplay(GxEPD_Class *display) { display->drawBitmap(2, 24, icon_no_ble_small, 28, 28, GxEPD_BLACK); }

/**
 * Add the wifi - is active - icon to the display
 */
void enableWifiDisplay(GxEPD_Class *display) { display->drawBitmap(2, 24, icon_wifi_small, 28, 28, GxEPD_BLACK); }

/**
 * Display the weather condition and temp
 */
void displayWeather(GxEPD_Class *display, String weatherCondition, String weatherTemp) {

  // Check if the weather condition is empty
  if (weatherCondition.length() == 0 || weatherCondition == "Unknown") {
    return;
  }
  // Check if the weather temp is empty
  if (weatherTemp.length() == 0) {
    return;
  }

  // Concatenate the weather condition and temperature + C
  String weatherText = weatherCondition + " " + weatherTemp + "°C";

  // Weather condition (bottom of the screen)
  // N x,y
  display->setFont(&Outfit_60011pt7b);
  printLeftString(display, weatherText.c_str(), 4, 190);
}

/**
 * Display the battery status
 */
void displayBatteryStatus(GxEPD_Class *display, int batteryStatus) {
  // Battery
  printRightString(display, String(String(batteryStatus) + "%").c_str(), 166, 22);
}

/**
 * If the focus time is running display it, once we get to 0 we stop and leave it at 0
 */
void displayFocusTime(GxEPD_Class *display, int focusTime) {

  if (focusTime > 0) {
    // Focus Time
    display->setFont(&Outfit_60011pt7b);
    String hoursFiller = focusTime < 10 ? "0" : "";
    String timeStr = hoursFiller + String(focusTime) + ":00";
    printLeftString(display, timeStr.c_str(), 4, 22);
  } else {
    String a = "--:--";
    printLeftString(display, a.c_str(), 4, 22);
  }
}

/**
 * Display the time
 */
void displayTime(GxEPD_Class *display, ESP32Time *rtc) {
  // Time
  display->setFont(&Outfit_80036pt7b);
  String hoursFiller = rtc->getHour(true) < 10 ? "0" : "";
  String minutesFiller = rtc->getMinute() < 10 ? "0" : "";
  String timeStr = hoursFiller + String(rtc->getHour(true)) + ":" + minutesFiller + String(rtc->getMinute());
  printCenterString(display, timeStr.c_str(), 100, 118);
}