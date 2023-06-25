#include <Adafruit_PWMServoDriver.h>
#include <FastIMU.h>
#include <Wire.h>


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define IMU_ADDRESS 0x68    //Change to the address of the IMU
MPU6050 IMU;    // Currently supported IMUS: MPU9255 MPU9250 MPU6886 MPU6500 MPU6050 ICM20689 ICM20690 BMI055 BMX055 BMI160 LSM6DS3 LSM6DSL
calData calib = { 0 };  //Calibration data
AccelData accelData;    //Sensor data


int compassyes = 1;
//指南针变量
int zhinz = 0;
//程序用变量
int zhuangtai=0;
float tlyx=0;
float tlyy=0;
float tlyz=0;
float zerox=1.2;
float zeroy=-10.7;

int pingheng1=0;
int pingheng3=0;
int pingheng1o=0;
int pingheng3o=0;
int pgo1=0;
int pgo3=0;



void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial1.begin(115200);
  Serial2.begin(38400);
  IMU.init(calib, IMU_ADDRESS);
  pwm.begin();
  pwm.setPWMFreq(100);
  pinMode(22,OUTPUT);
  delay(300);
  stopdj();

  dj1(100);dj2(100);dj3(100);dj4(100);


  

}




void loop() {
mpuget();
tlyy=tlyy-zeroy;
tlyx=tlyx-zerox;
pingheng1o=pingheng1;
pingheng3o=pingheng3;
if(tlyy>4) {pingheng1=pingheng1+4;pingheng3=pingheng3-4;}
if(tlyy<-4){pingheng1=pingheng1-4;pingheng3=pingheng3+4;}
if(tlyx>4) {pingheng1=pingheng1-5;pingheng3=pingheng3-5;}
if(tlyx<-4) {pingheng1=pingheng1+5;pingheng3=pingheng3+5;}
if(pingheng1<0) pingheng1=0;
if(pingheng1>450) pingheng1=450;
if(pingheng3<0) pingheng3=0;
if(pingheng3>450) pingheng3=450;
if(pingheng1o>pingheng1){pgo1=-40;}
else if(pingheng1o<pingheng1){pgo1=40;}
else {pgo1=0;}
if(pingheng3o>pingheng3){pgo3=-40;}
else if(pingheng3o<pingheng3){pgo3=40;}
else {pgo3=0;}
dj1(pingheng1);
dj3(pingheng3);
Serial.print (tlyx);Serial.print ("  ");Serial.print (tlyy);Serial.print ("  ");Serial.println (tlyz);
sportkk1(60+pgo1, 60, 60+pgo3, 60);
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





void stopdj()
{
  sportkk1(0, 0, 0, 0);
}


void turn(int turndg)
{
  int dgturn;
   dgturn=(znzget()-turndg+1440)%360;
   if(dgturn>180)dgturn=dgturn-360;
   dgturn=dgturn*8;
   if(dgturn<40&&dgturn>-40)dgturn=0;
   if(dgturn>255)dgturn=255;
   if(dgturn<-255)dgturn=-255;
   sportkk1(dgturn, -dgturn, dgturn, -dgturn);   
}

void foward(int speedt,int turndg)
{
  int dgturn;
   dgturn=(znzget()-turndg+1440)%360;
   if(dgturn>180)dgturn=dgturn-360;
   dgturn=dgturn*8;
   if(dgturn>100)dgturn=100;
   if(dgturn<-100)dgturn=-100;
   sportkk1(speedt+dgturn, speedt-dgturn, speedt+dgturn, speedt-dgturn);   
}


void sportkk1(int speedkz1, int speedkz2, int speedkz3, int speedkz4)
{
  int sdjk2, sdjk3, sdjk4, sdjk5, sdjk6, sdjk7, sdjk8, sdjk9;
  if (speedkz1 < 0) {
    sdjk2 = -speedkz1;
    sdjk3 = 0;
  }  else if (speedkz1 > 0) {
    sdjk2 = speedkz1;
    sdjk3 = 1;
  }  else {
    sdjk2 = 0;
    sdjk3 = 0;
  }

  if (speedkz2 < 0) {
    sdjk4 = -speedkz2;
    sdjk5 = 1;
  }  else if (speedkz2 > 0) {
    sdjk4 = speedkz2;
    sdjk5 = 0;
  }  else {
    sdjk4 = 0;
    sdjk5 = 0;
  }
  if (speedkz3 < 0) {
    sdjk6 = -speedkz3;
    sdjk7 = 0;
  }  else if (speedkz3 > 0) {
    sdjk6 = speedkz3;
    sdjk7 = 1;
  }  else {
    sdjk6 = 0;
    sdjk7 = 0;
  }
  if (speedkz4 < 0) {
    sdjk8 = -speedkz4;
    sdjk9 = 1;
  }  else if (speedkz4 > 0) {
    sdjk8 = speedkz4;
    sdjk9 = 0;
  }  else {
    sdjk8 = 0;
    sdjk9 = 0;
  }
  analogWrite(4, sdjk2); digitalWrite(45, sdjk3); analogWrite(5, sdjk4); digitalWrite(44, sdjk5); analogWrite(6, sdjk6); digitalWrite(43, sdjk7); analogWrite(7, sdjk8); digitalWrite(42, sdjk9);
}



void jieshou()
{ 
  if(Serial2.available()> 0)
  {
    int zj1;
    if(Serial2.read()!=201) 
    {
    }
    else
    {
      delay(20); 
      zj1=Serial2.read();
      //Serial.println(zj1);
      if(zhuangtai<zj1) zhuangtai=zj1;
    }
  }
}


void dj1(int dj1jd)
{
  dj1jd=dj1jd+230;
  if(dj1jd>930) dj1jd=930;
  if(dj1jd<230) dj1jd=230;
  pwm.setPWM(1, 0, dj1jd);
}
void dj2(int dj2jd)
{
  dj2jd=dj2jd +220;
  if(dj2jd>920) dj2jd=920;
  if(dj2jd<220) dj2jd=220;
  pwm.setPWM(2, 0, dj2jd);
}

void dj3(int dj3jd)
{
  dj3jd=dj3jd +240;
  if(dj3jd>940) dj3jd=940;
  if(dj3jd<240) dj3jd=240;
  pwm.setPWM(3, 0, dj3jd);
}

void dj4(int dj4jd)
{
  dj4jd=dj4jd +220;
  if(dj4jd>920) dj4jd=920;
  if(dj4jd<220) dj4jd=220;
  pwm.setPWM(4, 0, dj4jd);
}

void mpuget()
{
  IMU.update();
  IMU.getAccel(&accelData);
  tlyx=100*accelData.accelX;
  tlyy=100*accelData.accelY;
  tlyz=100*accelData.accelZ;
}
 