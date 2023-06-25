#include <Wire.h>
#include <SoftwareSerial.h>
SoftwareSerial Serialn(2, 3); // RX, TX
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
const int MPU_addr = 0x68; // MPU-6050的i2c地址
float agx,agy,agz;
float xxx=0;
int agxn=45;
int agzn=45;
int sz1=0;
int znzx=0;

void setup() {
  Serial.begin(9600);
  Serialn.begin(38400);
  Wire.begin(); 
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); 
  Wire.write(0); //启动mpu6050
  Wire.endTransmission(true);                         //初始化MPU6050
  delay(500);  Serial.println(200+znzx);
  
}

void loop() {
esp32MPU();
agx=abs(agx);
agx=agx/2;
agxn=(agxn*4+agx)/5;
agz=agz+90;
agz=agz/2;
agzn=(agzn*4+agz)/5;
Serial.print("Gyx = "); Serial.print(agxn);
Serial.print(" | Gyy = "); Serial.print(agy);
Serial.print(" | GyZ = "); Serial.println(agzn);
//Serial.println();
if(agzn<0) agzn=0;
if(agzn>99) agzn=99;
if(agxn<0) agxn=0;
if(agxn>99) agxn=99;
znzx=znzget();
if(znzx>180)znzx=znzx-360;
znzx=10-znzx/9;
if(znzx<0)znzx=0;
if(znzx>20)znzx=20;
Serialn.write(agzn);
delay(90);
Serialn.write(100+agxn);
delay(90);
Serialn.write(200+znzx);
delay(90);
// Serial.print(agzn);
// Serial.print("a");
// Serial.println(agxn);
 if(sz1==0&&analogRead(A0)<700)
 {
   sz1=1;
   Serialn.write(223);
  delay(90);
 }
 else if(sz1==1&&analogRead(A0)>850)
 {
   sz1=0;
   Serialn.write(224);
  delay(90);
 }

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


int znzget()
{
  int highpr = 99;
  int lowpr = 99;
  Wire.requestFrom(59, 2);
  while (Wire.available())
  {
    highpr = Wire.read();
    lowpr = Wire.read();
  }
  if (highpr == 11 && lowpr == 02) return 999;
  else if (highpr < 2)return highpr * 255 + lowpr;
  else return highpr;
}