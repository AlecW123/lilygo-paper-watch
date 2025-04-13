#include "home.h"
#include "rolex_crown_bitmap.h" // Include the Rolex crown bitmap

const char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

const char *days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

void drawHomeUI(GxEPD_Class *display, ESP32Time *rtc, int batteryStatus) {
  // Clear the screen
  display->fillRect(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_WHITE);
  display->setTextColor(GxEPD_BLACK);
  display->setTextWrap(false);

  // Define the square clock face
  int centerX = GxEPD_WIDTH / 2;  // Center of the screen
  int centerY = GxEPD_WIDTH / 2;             // Adjust Y position for the clock
  int sideLength = 150;          // Side length of the square clock face
  int halfSide = sideLength / 2;

  // Draw the square clock face
 // display->drawRect(centerX - halfSide, centerY - halfSide, sideLength, sideLength, GxEPD_BLACK);

  // Draw numbers 1 to 12 around the edges of the square
  const int numberOffset = 10; // Offset for numbers from the edges
  display->setFont(&Outfit_60011pt7b); // Set font for numbers
  for (int i = 1; i <= 12; i++) {
    float angle = radians((i - 3) * 30); // Calculate angle for each number
    int numberX = centerX + cos(angle) * (halfSide + numberOffset);
    int numberY = centerY + sin(angle) * (halfSide + numberOffset);
    display->setCursor(numberX - 5, numberY + 5); // Adjust position for centering
    display->print(i);
  }
// Add "ROLEX" text above the center point
display->setFont(&Outfit_60011pt7b); // Set font for "ROLEX"
display->setCursor(centerX - 30, centerY - 40); // Adjust position for "ROLEX"
display->print("ROLEX");

// Draw the Rolex crown logo above the "ROLEX" text
// Assuming you have a bitmap for the crown logo named `rolex_crown_bitmap`
// and its dimensions are 20x20 pixels
display->drawBitmap(centerX - 10, centerY - 60, rolex_crown_bitmap, 20, 20, GxEPD_BLACK);

  // Get the current time
  int hours = rtc->getHour(true); // 24-hour format
  int minutes = rtc->getMinute();

  // Convert hours to 12-hour format
  hours = hours % 12;

  // Calculate angles for the hands
  float hourAngle = (hours + minutes / 60.0) * 30; // Each hour is 30 degrees
  float minuteAngle = minutes * 6; // Each minute is 6 degrees

  // Convert angles to radians
  float hourRad = radians(hourAngle - 90); // Offset by -90 degrees to start at 12 o'clock
  float minuteRad = radians(minuteAngle - 90);

  // Calculate hand positions
  int hourX = centerX + cos(hourRad) * (halfSide * 0.5); // Hour hand is shorter
  int hourY = centerY + sin(hourRad) * (halfSide * 0.5);

  int minuteX = centerX + cos(minuteRad) * (halfSide * 0.8); // Minute hand is longer
  int minuteY = centerY + sin(minuteRad) * (halfSide * 0.8);

  // Draw the hands
  display->drawLine(centerX, centerY, hourX, hourY, GxEPD_BLACK);   // Hour hand
  display->drawLine(centerX, centerY, minuteX, minuteY, GxEPD_BLACK); // Minute hand

  // Draw the center point
  display->fillCircle(centerX, centerY, 2, GxEPD_BLACK);
  const unsigned char *icon_battery_small_array[6] = {epd_bitmap_icon_battery_0_small,  epd_bitmap_icon_battery_20_small,
    epd_bitmap_icon_battery_40_small, epd_bitmap_icon_battery_60_small,
    epd_bitmap_icon_battery_80_small, epd_bitmap_icon_battery_100_small};
  // Display the battery status
  //printRightString(display, String(String(batteryStatus) + "%").c_str(), 166, 22); // thjis displays the battery %% in the top right corner
  display->drawBitmap(170, 2, icon_battery_small_array[batteryStatus / 20], 28, 28, GxEPD_BLACK);
}

/**
 * Show the Wifi is disabled icon (indicates that the wifi connection failed)
 */
void disableWifiDisplay(GxEPD_Class *display) { display->drawBitmap(GxEPD_WIDTH / 2, GxEPD_WIDTH / 2, icon_no_ble_small, 28, 28, GxEPD_BLACK); }

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
  String weatherText = weatherCondition + " " + weatherTemp + "C";

  // Weather condition (bottom of the screen)
  // N x,y
  display->setFont(&Outfit_60011pt7b);
  //printLeftString(display, weatherText.c_str(), 4, 190);
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
  display->updateWindow(0, 60, 200, 60, true);
}

/**
 * Display the battery status and refresh the display
 */
void displayBatteryStatus(GxEPD_Class *display, int batteryStatus) {
  // Battery
  printRightString(display, String(String(batteryStatus) + "%").c_str(), 166, 22);
  // display->updateWindow(166, 0, 34, 34, true);
}