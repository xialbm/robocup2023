#include <Wire.h>


int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
const int MPU_addr = 0x68; // MPU-6050的i2c地址
float agx,agy,agz;


void setup() {
  Serial.begin(9600);
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); 
  Wire.write(0); //启动mpu6050
  Wire.endTransmission(true);                         //初始化MPU6050
  delay(500);
}

void loop() {
  esp32MPU();
Serial.print("Gyx = "); Serial.print(agx);
Serial.print(" | Gyy = "); Serial.print(agy);
Serial.print(" | GyZ = "); Serial.println(agz);
}


void esp32MPU()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  agx = atan2(AcY , AcZ) * 57.3;
  agy = atan2(AcX , AcZ) * 57.3;
  agz = atan2(AcX , AcY) * 57.3;
  //  Serial.print("AcX = "); Serial.print(AcX);
  //  Serial.print(" | AcY = "); Serial.print(AcY);
  //  Serial.print(" | AcZ = "); Serial.print(AcZ);
  //  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53); //equation for temperature in degrees C from datasheet
  //  Serial.print(" | GyX = "); Serial.print(GyX);
  //  Serial.print(" | GyY = "); Serial.print(GyY);
  //  Serial.print(" | GyZ = "); Serial.println(GyZ);
}
