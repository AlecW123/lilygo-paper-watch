#pragma once

#include "Arduino.h"
#include "ESP32Time.h"
#include "GxDEPG0150BN/GxDEPG0150BN.h" // 1.54 b/w 200x200
#include "GxEPD.h"

#include "lib/ui.h"
#include "resources/fonts/FreeSerifBold12pt7b.h"
#include "resources/fonts/Outfit_60011pt7b.h"
#include "resources/fonts/Outfit_80036pt7b.h"
#include "resources/icons.h"

void drawHomeUI(GxEPD_Class *display, ESP32Time *rtc, int batteryStatus);
void disableWifiDisplay(GxEPD_Class *display);
void enableWifiDisplay(GxEPD_Class *display);
void displayWeather(GxEPD_Class *display, String weatherCondition, String weatherTemp);
void displayBatteryStatus(GxEPD_Class *display, int batteryStatus);
void displayFocusTime(GxEPD_Class *display, int focusTime);
void displayTime(GxEPD_Class *display, ESP32Time *rtc);
void displayBatteryStatus(GxEPD_Class *display, int batteryStatus);