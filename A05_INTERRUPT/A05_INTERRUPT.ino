#include <Arduino.h>

const uint8_t PIN_MOTOR_1	= 3;

void ISR_function() {
	Serial.println("interrupted...");
}

void setup() {
	Serial.begin(19200);	// serial 통신 시작 (data rate : 19200)
	
	attachInterrupt(INT1, ISR_function, RISING);	// interrupt service routine 등록
}

void loop() {
	pinMode(PIN_MOTOR_1, OUTPUT);
	digitalWrite(PIN_MOTOR_1, HIGH);	// software interrupt 발생
	delay(2);
	digitalWrite(PIN_MOTOR_1, LOW);
	delay(1000);
}
