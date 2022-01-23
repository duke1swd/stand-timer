/*
 * Code to manage the stand-timer
 *
 * Built with Homie framework for remote control and OTA upgrades
 */

#include <Homie.h>

#define FIRMWARE_NAME     "stand-timer"
#define FIRMWARE_VERSION  "0.0.1"

/*
 * IO Pins
 */
const int PIN_SCL = D1;
const int PIN_SDA = D2;
const int PIN_LED = 2;

/*
 * Misc globals
 */


/****
 *
 * Message Handlers
 *
 * NOTE: the message handlers are called asynchronously from the TCP/IP upcal.
 * We assume this means they may be called from an interrupt at any time.
 *
 ****/

/*
 * This code called once to set up, but only after completely connected.
 */
void setupHandler() {
}

void setup() {
  void loopHandler();
  Serial.begin(115200);
  Serial.println("Stand Timer");
  Serial.println(FIRMWARE_VERSION);
  Serial << endl << endl;

  Homie_setFirmware(FIRMWARE_NAME, FIRMWARE_VERSION);
  Homie.setSetupFunction(setupHandler).setLoopFunction(loopHandler);

  Homie.setup();
}


/*
 * This code is called once per loop(), but only
 * when connected to WiFi and MQTT broker
 */
void loopHandler() {
}

/*
 * This code runs repeatedly, whether connected to not.
 */
void loop() {

  Homie.loop();
}
