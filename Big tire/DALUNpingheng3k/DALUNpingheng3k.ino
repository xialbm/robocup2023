#include <Adafruit_PWMServoDriver.h>
#include <FastIMU.h>
#include <Wire.h>
#include <SCServo.h>
#include <DFRobot_HuskyLens.h>

DFRobot_HuskyLens huskylens;
SCSCL sc;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define IMU_ADDRESS 0x68    //Change to the address of the IMU
MPU6050 IMU;    // Currently supported IMUS: MPU9255 MPU9250 MPU6886 MPU6500 MPU6050 ICM20689 ICM20690 BMI055 BMX055 BMI160 LSM6DS3 LSM6DSL
calData calib = { 0 };  //Calibration data
AccelData accelData;    //Sensor data

int djspeed=0;
int compassyes = 1;
//指南针变量
int zhinz = 0;
//程序用变量
int zhuangtai=0;
float tlyx=0;
float tlyy=0;
float tlyz=0;
float zerox=-2.5;
float zeroy=-9.9;

float pingheng1=100;
float pingheng3=100;
float pingheng1o=100;
float pingheng3o=100;
int pgo1=0;
int pgo3=0;
int zhuandong=0;
int speedx=0;
int hux=0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial1.begin(115200);
  Serial2.begin(38400);
  IMU.init(calib, IMU_ADDRESS);
  pwm.begin();
  pwm.setPWMFreq(100);
  Serial3.begin(115200);
  sc.pSerial = &Serial3;
  djspeed=400;
  huskylens.beginI2CUntilSuccess();
  stopdj();
pwm.setPWM(3, 0, 225);
 pwm.setPWM(12, 0, 420);
  pwm.setPWM(13, 0, 820);
  dj1(200);dj2(200);dj3(200);dj4(200);
sc.RegWriteAction();



while(1)
{
  jieshou();
  if(zhuangtai==1){zhuangtai=2;zigbeesend(1);digitalWrite(13,1);}
  if(zhuangtai>=20)break;
}
while(1)
{
  jieshou();
  pinghenggo();
  huskylens.request();
      if ((huskylens.readBlockCenterParameterDirect().ID == 1)) {
        hux = huskylens.readBlockParameter(1).xCenter;
        if((hux>105&&hux<205))
        {
            break;
        }
      
      }
      if(zhuangtai>=40)break;
      Serial.println(zhuangtai);
}
Serial.println("xxxx");
zigbeesend(30);
  stopdj();
  dj1(200);dj2(200);dj3(200);dj4(200);
sc.RegWriteAction();
while(1)
{
  jieshou();
  if(zhuangtai>=70)break;
}
  pullup(); 
  delay(3500);
  for(int i=225;i<=425;i++){pwm.setPWM(3, 0,i);delay(12);}
  delay(500);
  zigbeesend(80);
while(1)
{
  jieshou();
  if(zhuangtai>=90)break;
}

   pwm.setPWM(12, 0, 820);
   pwm.setPWM(13, 0, 420);
while(1)
{
  jieshou();
  if(zhuangtai>=100)break;
}

while(1){}
}




void loop() {


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

void zigbeesend(int zbsj)
{
  Serial2.write(201);
  Serial2.write(zbsj);
}

void dj1(int dj1jd)
{
  
  if(dj1jd>900) dj1jd=900;
  if(dj1jd<20) dj1jd=20;
  sc.RegWritePos(1, dj1jd, 0,djspeed);
  
}
void dj2(int dj2jd)
{
  dj2jd=960-dj2jd;
  if(dj2jd>950) dj2jd=950;
  if(dj2jd<20) dj2jd=20;
   sc.RegWritePos(2, dj2jd, 0, djspeed);
   
}

void dj3(int dj3jd)
{
  dj3jd=960-dj3jd;
  if(dj3jd>900) dj3jd=900;
  if(dj3jd<20) dj3jd=20;
   sc.RegWritePos(3, dj3jd, 0, djspeed);
   
}

void dj4(int dj4jd)
{
  dj4jd=dj4jd+20;
  if(dj4jd>970) dj4jd=970;
  if(dj4jd<40) dj4jd=40;
   sc.RegWritePos(4, dj4jd, 0, djspeed);
  
}

void mpuget()
{
  IMU.update();
  IMU.getAccel(&accelData);
  tlyx=100*accelData.accelX;
  tlyy=100*accelData.accelY;
  tlyz=100*accelData.accelZ;
}
 

void pullup()
{
 djspeed=250;
  dj1(50);
  dj2(50);
  dj3(820);
  dj4(820);
sc.RegWriteAction();

 djspeed=1200;
}


void pinghenggo()
{
speedx=140;
mpuget();
//Serial.print (pingheng1);Serial.print ("  ");Serial.print (pingheng3);Serial.print ("  ");Serial.print (tlyx);Serial.print ("  ");Serial.print (tlyy);Serial.print ("  ");Serial.println (tlyz);
tlyy=tlyy-zeroy;
tlyx=tlyx-zerox;
pingheng1o=pingheng1;
pingheng3o=pingheng3;
if(tlyy>1) {pingheng1=pingheng1+tlyy/10;pingheng3=pingheng3-tlyy/10;}
if(tlyy<-1){pingheng1=pingheng1+tlyy/10;pingheng3=pingheng3-tlyy/10;}
if(tlyx>1) {pingheng1=pingheng1+tlyx/6;pingheng3=pingheng3+tlyx/6;}
if(tlyx<-1) {pingheng1=pingheng1+tlyx/6;pingheng3=pingheng3+tlyx/6;}
if(pingheng1<50) pingheng1=50;
if(pingheng1>550) pingheng1=550;
if(pingheng3<50) pingheng3=50;
if(pingheng3>550) pingheng3=550;
if(pingheng1o>pingheng1){pgo1=-40;}
else if(pingheng1o<pingheng1){pgo1=40;}
else {pgo1=0;}
if(pingheng3o>pingheng3){pgo3=-40;}
else if(pingheng3o<pingheng3){pgo3=40;}
else {pgo3=0;}
dj1(pingheng1);
dj3(pingheng3);
sc.RegWriteAction();
zhuandong=znzget();
if(zhuandong>180)zhuandong=zhuandong-360;
zhuandong=zhuandong*8;
if(zhuandong>150)zhuandong=150;
if(zhuandong<-150)zhuandong=-150;
if(zhuandong<20&&zhuandong>-20)zhuandong=0;
if(pingheng1>250||pingheng3>250)speedx=130;
sportkk1(speedx+pgo1-zhuandong,speedx+zhuandong, speedx+pgo3-zhuandong, speedx+zhuandong);

}