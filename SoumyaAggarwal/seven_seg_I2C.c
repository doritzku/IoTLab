#include <Wire.h>
#include "RTClib.h"
#include <TM1637Display.h> 

RTC_DS3231 rtc; 

// Create an instance of the TM1637 display
TM1637Display display(22, 21); // CLK, DIO pins for TM1637

void setup() {
  Wire.begin(21, 22);
  Serial.begin(9600); // Start serial

  // Initialize the RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1); // Stop execution if RTC is not found
  }

  
  rtc.adjust(DateTime(2025, 2, 12, 9, 30, 0));

  // Initialize the TM1637 display
  display.setBrightness(0x0f); 
}

void loop() {
  // Get the current time and date
  DateTime now = rtc.now();
  
  // Extract hours and minutes
  uint8_t hour = now.hour();
  uint8_t minute = now.minute();

  // Print the time and date to the Serial Monitor
  Serial.print("Time: ");
  Serial.print(hour);
  Serial.print(':');
  Serial.print(minute);
  Serial.print(" Date: ");
  Serial.print(now.day());
  Serial.print('/');
  Serial.print(now.month());
  Serial.print('/');
  Serial.println(now.year());

  // Format time as HHMM for the display
  int displayTime = now.hour() * 100 + now.minute(); // Combine hour and minute
  // Display the time on the TM1637
  display.showNumberDec(displayTime, false, 5, 0); // Display HHMM

  delay(1000); // Wait for a second before repeating
}