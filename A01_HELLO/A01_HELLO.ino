#include <Arduino.h>

void setup() {
	Serial.begin(115200);	// init serial communication (data rate : 19200)
}

void loop() {
	Serial.println("Hello World.");
	Serial.println(Serial.available());
	Serial.println(Serial);

	Serial.print(78, BIN);
	Serial.println(78, OCT);
	Serial.println(78, DEC);
	Serial.println(78, HEX);
	Serial.println(4.20, 0);
	Serial.println(4.14, 1);
	char text[40];
	sprintf(text, "%d,%d,%s", 100, 200, String(30.5f);
	Serial.println(text);
	Serial.println("----------------------------------------------");

	delay(1000);
}
