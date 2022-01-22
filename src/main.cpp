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
const int PIN_DHT = D5;

/*
 * Misc globals
 */
volatile long time_base;
long now;
long last_light_time;
long published_light_time;
int light;
const long light_period = 3;	// sample every 30 seconds XXX actually, for debugging do this more often
float temp;
float humidity;
long last_temp_time;
long published_temp_time;
const long temp_period = 30;	// sample every 30 seconds

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
#define DHTTYPE DHT22   // DHT 22  (AM2302) type of temp/humidity sensor we are using
DHT dht(PIN_DHT, DHTTYPE);

HomieNode timerNode("lux", "lux", "sensor");

/****
 *
 * Message Handlers
 *
 * NOTE: the message handlers are called asynchronously from the TCP/IP upcal.
 * We assume this means they may be called from an interrupt at any time.
 *
 ****/

// Broadcast handler.  Useful for time base.
bool broadcastHandler(const String& level, const String& value) {
  // Only broadcast we know about it IOTtime.
  if (level == "IOTtime") {
	long t = value.toInt();

	if (t < 0) return false;

	time_base = t - millis()/1000;
	return true;
  }
  return false;
}

/*
 * This code called once to set up, but only after completely connected.
 */
void setupHandler() {
  published_light_time = 0;
  published_temp_time = 0;
  luxNode.setProperty("unit").send("lux");
  tempNode.setProperty("unit").send("F");
}

void setup() {
  void loopHandler();
  Serial.begin(115200);
  Serial.println("Stand Timer");
  Serial.println(FIRMWARE_VERSION);
  Serial << endl << endl;

  Homie_setFirmware(FIRMWARE_NAME, FIRMWARE_VERSION);
  Homie.setSetupFunction(setupHandler).setLoopFunction(loopHandler);

  luxNode.advertise("lux").
	setName("Light Intensity").
	setDatatype("integer");

  Homie.setBroadcastHandler(broadcastHandler);

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

  long t;

  t = millis()/1000;
  noInterrupts();
  now = time_base + t;
  interrupts();

  Homie.loop();
}
