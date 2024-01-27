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

#define WIFI_SSID         "ELVIS"    
#define WIFI_PASS         "Gmunene@123"
#define APP_KEY           "4bfaf63c-dbd5-4603-bfce-a1e4b991462b"      // Should look like "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "d2170a7d-a600-4698-ae86-8e8be160a9ea-a3423086-cee5-4dc8-a245-48cb630471ea"   // Should look like "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
#define SWITCH_ID         "64d1e56a708e0f2583b86ebb"    // Should look like "5dc1564130xxxxxxxxxxxxxx"
#define SWITCH_ID_2       "64d1e44a708e0f2583b86e43"    // Switch ID for the second relay
#define SWITCH_ID_3       "64d1e532a1c7182622ab83f7" 
#define BAUD_RATE         9600                // Change baudrate to your need

#ifdef ESP8266
#define RELAY_PIN         D5                  // Pin where the first relay is connected (D5 = GPIO 14 on ESP8266)
#define RELAY_PIN_2       D6                  // Pin where the second relay is connected (D6 = GPIO 12 on ESP8266)
#define RELAY_PIN_3       D7                  // Pin where the third relay is connected (D7 = GPIO 13 on ESP8266)
#endif

#ifdef ESP32
#define RELAY_PIN         16                  // Pin where the first relay is connected (GPIO 16 on ESP32)
#define RELAY_PIN_2       19                // Pin where the second relay is connected (GPIO 17 on ESP32)
#define RELAY_PIN_3       33                  // Pin where the third relay is connected (GPIO 18 on ESP32)
#endif

bool onPowerState(const String &deviceId, bool &state) {
  digitalWrite(RELAY_PIN, state);             // set pin state for the first relay
  digitalWrite(RELAY_PIN_2, state);           // set pin state for the second relay
  digitalWrite(RELAY_PIN_3, state);           // set pin state for the third relay
  return true;                                // request handled properly
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);                  // set first relay-pin to output mode
  pinMode(RELAY_PIN_2, OUTPUT);                // set second relay-pin to output mode
  pinMode(RELAY_PIN_3, OUTPUT);                // set third relay-pin to output mode

  WiFi.begin(WIFI_SSID, WIFI_PASS);            // start wifi

  SinricProSwitch& mySwitch = SinricPro[SWITCH_ID];     // create new switch device for the first relay
  mySwitch.onPowerState(onPowerState);                  // apply onPowerState callback

  SinricProSwitch& mySwitch2 = SinricPro[SWITCH_ID_2];   // create new switch device for the second relay
  mySwitch2.onPowerState(onPowerState);                 // apply onPowerState callback

  SinricProSwitch& mySwitch3 = SinricPro[SWITCH_ID_3];   // create new switch device for the third relay
  mySwitch3.onPowerState(onPowerState);                 // apply onPowerState callback

  SinricPro.begin(APP_KEY, APP_SECRET);                 // start SinricPro
}

void loop() {
  SinricPro.handle();                          // handle SinricPro commands
}
