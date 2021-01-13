#include <ESP8266WiFi.h>

// Define pins
#define BTN_PIN D0
#define LED_PIN D1

// Wifi connection informations
const char* ssid = "SSID";
const char* password = "PASSWORD";

// Create server object
WiFiServer server(80);

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
	byte mac[WL_MAC_ADDR_LENGTH];
	WiFi.macAddress(mac);

	// Print IP address
	Serial.print("IP address : ");
	Serial.println(WiFi.localIP());

	// Start web server
	server.begin();

	// Init pin configuration
	pinMode(BTN_PIN, INPUT);
	pinMode(LED_PIN, OUTPUT);

	// Disable led
	digitalWrite(LED_PIN, LOW);
}

void loop() {
	// Init connection with client
	WiFiClient client = server.available();
	if(!client) {
		return;
	}

	while(!client.available()) {
		delay(1);
	}

	// Read client request
	String req = client.readStringUntil('\r');

	// Flush output
	client.flush();

	String text = ""; // Return text
	if(req.indexOf("/place_node") != -1) {
		// Add button state to output
		int state = digitalRead(BTN_PIN);
		text += (state == LOW) ? "1" : "0";

	} else if(req.indexOf("/led_on") != -1) {
		// Enable led
		digitalWrite(LED_PIN, HIGH);

	} else if(req.indexOf("/led_off") != -1) {
		// Disable led
		digitalWrite(LED_PIN, LOW);
	}

	// Flush output
	client.flush();

	// Generate HTML output
	String htmlPage = "HTTP/1.1 200 OK\r\n";
	htmlPage += "Content-Type: text/html\r\n";
	htmlPage += "\r\n";
	htmlPage += text + "\r\n";

	// Send html output to client
	client.println(htmlPage);
	delay(1);
}
