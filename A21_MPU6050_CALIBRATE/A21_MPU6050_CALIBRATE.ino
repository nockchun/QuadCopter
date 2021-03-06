#include <Arduino.h>
#include "i2cUtil.h"
#include "mpu6050.h"

#define PIN_MOTOR_1       6
#define PIN_MOTOR_2       10
#define PIN_MOTOR_3       5
#define PIN_MOTOR_4       9

float rad2degree = 57.3;
float delta      = 20;
unsigned long t  = 0;

vector_t accelAngel, gyroAngel, gyroBase;

void setup() {
	Serial.begin(115200);  // serial 통신 시작 (data rate : 19200)

	mpu6050Reset();
	setAccelRange(MPU6050_RANGE_4G);
	setGyroScale(MPU6050_SCALE_250DPS);
	mpu6050SetSleepMode(false);
	mpu6050PrintStatus();

	gyroBase = mpu6050Gyro();
	pinMode(PIN_MOTOR_1, OUTPUT);
	pinMode(PIN_MOTOR_2, OUTPUT);
	pinMode(PIN_MOTOR_3, OUTPUT);
	pinMode(PIN_MOTOR_4, OUTPUT);	
}

void loop() {
	t = millis();
	// printTemperature();
	// printAccelerometer();
	printGyroscope();
	// setMotorPower(20);

	// Serial.println(((float)(millis()-t)/delta)*100);
	while((millis()-t) < delta){ // Making sure the cycle time is equal to delta
	}
}

void printTemperature() {
	float temp = readTemperature();
	Serial.print("Temperature RAW[");
	Serial.print(readRawTemperature());
	Serial.print("] ºC[");
	Serial.print(readTemperature());
	Serial.println("]");
}

void printAccelerometer() {
	vector_t rawAccelValue = mpu6050RawAccel();
	vector_t accelValue    = mpu6050Accel();

	accelAngel.x = atan2(accelValue.y, accelValue.z) * rad2degree;
	accelAngel.y = atan2(accelValue.x, accelValue.z) * rad2degree;
	accelAngel.z = atan2(accelValue.z, sqrt(accelValue.x*accelValue.x + accelValue.y*accelValue.y)) * rad2degree;

	Serial.print("Accelerometer VALUE[x:");
	Serial.print(accelValue.x);
	Serial.print(", y:");
	Serial.print(accelValue.y);
	Serial.print(", z:");
	Serial.print(accelValue.z);
	Serial.print("] AXIS ANGLE[x:");
	Serial.print(accelAngel.x);
	Serial.print(", y:");
	Serial.print(accelAngel.y);
	Serial.print(", z:");
	Serial.print(accelAngel.z);
	Serial.println("]");
}

void printGyroscope() {
	vector_t gyroDiffBase;
	vector_t rawGyroValue = mpu6050RawGyro();
	vector_t gyroValue    = mpu6050Gyro();

	gyroDiffBase.x = (gyroValue.x - gyroBase.x) / 1000;
	gyroDiffBase.y = (gyroValue.y - gyroBase.y) / 1000;
	gyroDiffBase.z = (gyroValue.z - gyroBase.z) / 1000;

	gyroAngel.x = gyroAngel.x + (gyroDiffBase.x) * delta;
	gyroAngel.y = gyroAngel.y + (gyroDiffBase.y) * delta;
	gyroAngel.z = gyroAngel.z + (gyroDiffBase.z) * delta;

	Serial.print("Gyro VALUE[x:");
	Serial.print(gyroDiffBase.x);
	Serial.print(", y:");
	Serial.print(gyroDiffBase.y);
	Serial.print(", z:");
	Serial.print(gyroDiffBase.z);
	Serial.print("] ANGLE[x:");
	Serial.print(gyroAngel.x);
	Serial.print(", y:");
	Serial.print(gyroAngel.y);
	Serial.print(", z:");
	Serial.print(gyroAngel.z);
	Serial.println("]");
}

void setMotorPower(int power) {
    analogWrite(PIN_MOTOR_1, power);
    analogWrite(PIN_MOTOR_4, power);
    analogWrite(PIN_MOTOR_3, power);
    analogWrite(PIN_MOTOR_2, power);
}