#include <Arduino.h>
#include <Wire.h>

#define MPU6050_address		0x68	// 104
#define MPU6050_PWR1		0x6B	// 107
#define MPU6050_data_start	0x3B	// 59

void setup() {
	Serial.begin(19200);	// serial 통신 시작 (data rate : 19200)

	Wire.begin();
	Wire.beginTransmission(MPU6050_address);
	Wire.write(MPU6050_PWR1);
	Wire.write(0);
	Wire.endTransmission();
}

void loop() {
	int temp=0, accel_x=0, accel_y=0, accel_z=0, gyro_x=0, gyro_y=0, gyro_z=0;
	int read_bytes = 2;

	Wire.beginTransmission(MPU6050_address);
	Wire.write(MPU6050_data_start);
	Wire.endTransmission(false);
	Wire.requestFrom(MPU6050_address, read_bytes);
	if(Wire.available() == read_bytes){
		accel_x = Wire.read()<<8 | Wire.read();
	}

	Serial.print("x:");
	Serial.println(accel_x);

	Wire.beginTransmission(MPU6050_address);
	Wire.endTransmission(true);    //연결종료	

	delay(500);
}
