#include <Arduino.h>
#include <Wire.h>

#define MPU6050_address		0x68
#define MPU6050_data_start	0x3B

int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

void setup(){
	Wire.begin();				//init Wire library
	Wire.beginTransmission(MPU6050_address);	//MPU로 데이터 전송 시작
	Wire.write(0x6B);			// PWR_MGMT_1 register
	Wire.write(0);				// MPU-6050 시작 모드로
	Wire.endTransmission(true); 
	Serial.begin(115200);		// serial 통신 시작 (data rate : 19200)
}

void loop(){
	Wire.beginTransmission(MPU6050_address);	//데이터 전송시작
	Wire.write(MPU6050_data_start);				// register 0x3B (ACCEL_XOUT_H), 큐에 데이터 기록
	Wire.endTransmission(false);				//연결유지

	//데이터 한 바이트 씩 읽어서 반환
	Wire.requestFrom(MPU6050_address,14,true);  //MPU에 데이터 요청
	if (Wire.available() == 14) {
		AcX=Wire.read()<<8 | Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
		AcY=Wire.read()<<8 | Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
		AcZ=Wire.read()<<8 | Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
		Tmp=Wire.read()<<8 | Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
		GyX=Wire.read()<<8 | Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
		GyY=Wire.read()<<8 | Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
		GyZ=Wire.read()<<8 | Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
	}

	//시리얼 모니터에 출력
	Serial.print("ACCEL[x:");	Serial.print(AcX);
	Serial.print(", y:");		Serial.print(AcY);
	Serial.print(", z:");		Serial.print(AcZ);
	Serial.print("] TEMP[");	Serial.print(Tmp / 340.00 + 36.53);
	Serial.print("] GYRO[x:");	Serial.print(GyX);
	Serial.print(", y:");		Serial.print(GyY);
	Serial.print(", z:");		Serial.print(GyZ);
	Serial.println("]");

	delay(500);
}
