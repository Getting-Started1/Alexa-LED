/*
 * If you encounter any issues:
 * - check the readme.md at https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md
 * - ensure all dependent libraries are installed
 *   - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#arduinoide
 *   - see https://github.com/sinricpro/esp8266-esp32-sdk/blob/master/README.md#dependencies
 * - open serial monitor and check whats happening
 * - check full user documentation at https://sinricpro.github.io/esp8266-esp32-sdk
 * - visit https://github.com/sinricpro/esp8266-esp32-sdk/issues and check for existing issues or open a new one
 */

// Uncomment the following line to enable serial debug output
//#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
       #define DEBUG_ESP_PORT Serial
       #define NODEBUG_WEBSOCKETS
       #define NDEBUG
#endif 

#include <Arduino.h>
#ifdef ESP8266 
       #include <ESP8266WiFi.h>
#endif 
#ifdef ESP32   
       #include <WiFi.h>
#endif

#include "SinricPro.h"
#include "SinricProSwitch.h"

#define WIFI_SSID         "Kinuthia"    
#define WIFI_PASS         "m@!n!90!"
#define APP_KEY           "4bfaf63c-dbd5-4603-bfce-a1e4b991462b"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "d2170a7d-a600-4698-ae86-8e8be160a9ea-a3423086-cee5-4dc8-a245-48cb630471ea"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define SWITCH_ID         "648ff6e1743f9120703a6857"    // Should look like "5dc1564130xxxxxxxxxxxxxx"
#define BAUD_RATE         9600                // Change baudrate to your need

#ifdef ESP8266
#define RELAY_PIN         D5                  // Pin where the relay is connected (D5 = GPIO 14 on ESP8266)
#endif

#ifdef ESP32
#define RELAY_PIN         2                  // Pin where the relay is connected (GPIO 16 on ESP32)
#endif

bool onPowerState(const String &deviceId, bool &state) {
  digitalWrite(RELAY_PIN, state);             // set pin state
  return true;                                // request handled properly
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);                 // set relay-pin to output mode
  WiFi.begin(WIFI_SSID, WIFI_PASS);           // start wifi

  SinricProSwitch& mySwitch = SinricPro[SWITCH_ID];   // create new switch device
  mySwitch.onPowerState(onPowerState);                // apply onPowerState callback
  SinricPro.begin(APP_KEY, APP_SECRET);               // start SinricPro
}

void loop() {
  SinricPro.handle();                         // handle SinricPro commands
}
