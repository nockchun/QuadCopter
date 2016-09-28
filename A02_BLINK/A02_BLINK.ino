#include <Arduino.h>

const uint8_t PIN_LED		= 13;

void setup() {
	Serial.begin(19200);	// serial 통신 시작 (data rate : 19200)
	while(!Serial) {		// serial 통신을 위한 접속 대기
		delay(100);
	}
}

void loop() {
	pinMode(TXLED, OUTPUT);

	digitalWrite(PIN_LED, HIGH);
	delay(1000);
	digitalWrite(PIN_LED, LOW);
	delay(100);
}
