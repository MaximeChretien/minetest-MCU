#include <WiFi.h>
#include <WebServer.h>

// Define pins
#define BTN_PIN 0
#define LED_PIN 2
bool ledStatus = LOW, oldLedStatus = LOW;

// Wifi connection informations
const char* ssid = "SSID";
const char* password = "PASSWD";

// Create server object
WebServer server(80);

void setup() {
	// Init Serial line to get IP address
	Serial.begin(115200);
	delay(10);

	// Init Wifi connection and print some text
	Serial.println();
	Serial.print("Connecting");

	WiFi.begin(ssid, password);

	while(WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println();

	Serial.println("Wifi connection OK");

	// Get MAC address
	byte mac[6];
	WiFi.macAddress(mac);

	// Print IP address
	Serial.print("IP address : ");
	Serial.println(WiFi.localIP());

	// Start web server
	server.on("/led_on", led_on);
	server.on("/led_off", led_off);
	server.on("/place_node", place_node);
	server.begin();

	// Init pin configuration
	pinMode(BTN_PIN, INPUT);
	pinMode(LED_PIN, OUTPUT);

	// Disable led
	digitalWrite(LED_PIN, LOW);
}

void loop() {
	server.handleClient();

	if(oldLedStatus != ledStatus) {
		digitalWrite(LED_PIN, ledStatus);
		oldLedStatus = ledStatus;
	}
}

void led_on() {
	ledStatus = HIGH;
	server.send(200, "text/html", "");
}

void led_off() {
	ledStatus = LOW;
	server.send(200, "text/html", "");
}

void place_node() {
	server.send(200, "text/plain", (digitalRead(BTN_PIN) == LOW) ? "1" : "0");
}
