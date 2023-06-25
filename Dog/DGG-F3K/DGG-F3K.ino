//0123下    4567上
#include "PCA9685.h"
PCA9685 pwmController1(0x41);
PCA9685 pwmController2(0x60);
int a = 100, b = 310, c = 500;
#define IN1M 27
#define IN2M 33
#define PWMA 26
#define PWMB 32
int xxa, xxb;
int steptime = 2;
int stepc = 0;
int zhuangtai=0;
int zhuandong=0;
long timer=0;


void setup() {
  pinMode(IN1M, OUTPUT);                         
  pinMode(IN2M, OUTPUT);
  pinMode(PWMA, OUTPUT);                        
  pinMode(PWMB, OUTPUT);  
  digitalWrite(IN1M, 0);
  digitalWrite(IN2M, 0);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  ledcAttachPin(PWMA, 1);
  ledcAttachPin(PWMB, 2);
  ledcSetup(1, 500, 8);
  ledcSetup(2, 500, 8);
  pinMode(34, INPUT);
  pinMode(35, INPUT);
  Wire.begin();
  pwmController1.resetDevices();
  pwmController2.resetDevices();
  pwmController1.init();
  pwmController2.init();
  pwmController1.setPWMFrequency(50);
  pwmController2.setPWMFrequency(50);
  Serial.begin(9600);
  Serial2.begin(38400);
  yundong(2, 135);
  yundong(6, 125);
  yundong(1, 140);
  yundong(5, 100);                    
  yundong(3, 100);
  yundong(7, 130);
  yundong(0, 80);
  yundong(4, 110);

sport(0,0);
while(1)
{
  jieshou();
  if(zhuangtai==1){zhuangtai=2;zigbeesend(1);digitalWrite(2,1);}
  if(zhuangtai>=10)break;
}
while(1)
{
  jieshou();
  if(zhuangtai>=20)break;
  ledjs();
}
while(1)
{
  jieshou();
  if(zhuangtai>=40)break;
}

for (int i=0;i<28000;i++)
{
zhuandong=znzget();
if(zhuandong>180)zhuandong=zhuandong-360;
zhuandong=zhuandong*3;
if(zhuandong>150)zhuandong=150;
if(zhuandong<-150)zhuandong=-150;
if(zhuandong<5&&zhuandong>-5)zhuandong=0;
sport(80-zhuandong,80+zhuandong);
}
 for (int i=0;i<20000;i++)
{
zhuandong=(znzget()-180+720)%360;
if(zhuandong>180)zhuandong=zhuandong-360;
zhuandong=zhuandong*2;
if(zhuandong>150)zhuandong=150;
if(zhuandong<-150)zhuandong=-150;
if(zhuandong<5&&zhuandong>-5)zhuandong=0;
sport(-zhuandong,+zhuandong);
}
sport(0,0);
zigbeesend(50);
while(1)
{
  jieshou();
  if(zhuangtai>=60)break;
}
  yundong(2, 400);
  yundong(6, 315);
  yundong(1, 400);
  yundong(5, 315);
  yundong(3, 250);
  yundong(7, 150);
  yundong(0, 250);
  yundong(4, 150);
  delay(1500);
while(1)
{
  jieshou();
  if(zhuangtai>=70)break;
  shoutao();
}

  yundong(2, 135);
  yundong(6, 125);
  yundong(1, 140);
  yundong(5, 100);                    
  yundong(3, 100);
  yundong(7, 130);
  yundong(0, 80);
  yundong(4, 110);
  delay(1500);
 for (int i=0;i<20000;i++)
{
zhuandong=(znzget()+720)%360;
if(zhuandong>180)zhuandong=zhuandong-360;
zhuandong=zhuandong*2;
if(zhuandong>150)zhuandong=150;
if(zhuandong<-150)zhuandong=-150;
if(zhuandong<5&&zhuandong>-5)zhuandong=0;
sport(-zhuandong,+zhuandong);
}
  timer=millis();
  while(1)
  {
  stepc = stepc + 1;                                            
  if (stepc > 200) stepc = 0;
  gougou(1, stepc);
  gougou(2, (stepc + 100) % 200);                  
  gougou(3, (stepc + 100) % 200);
  gougou(4, (stepc + 0) % 200);
  delay(steptime);
  if(millis()-timer>8000){break;}
  }
  yundong(2, 400);
  yundong(6, 315);
  yundong(1, 400);
  yundong(5, 315);                    
  yundong(3, 250);
  yundong(7, 150);
  yundong(0, 250);
  yundong(4, 150);


  
}
void loop() {
  


}


void gougou(int tui, int bu) {

  if (bu < 8) {
    if (tui == 1) {    yundong(2, 340);    yundong(6, 230);  }
    if (tui == 2) {    yundong(1, 340);    yundong(5, 230);   }
    if (tui == 3) {    yundong(3, 160);    yundong(7, 210);  }
    if (tui == 4) {    yundong(0, 160);    yundong(4, 210);  }
  } else if (bu < 24) {
    if (tui == 1) {    yundong(2, 340);   yundong(6, 315);  }
    if (tui == 2) {    yundong(1, 340);   yundong(5, 315);  }
    if (tui == 3) {    yundong(3, 160);   yundong(7, 150); }
    if (tui == 4) {    yundong(0, 160);   yundong(4, 150); }
  } else if (bu < 32) {
    if (tui == 1) {     yundong(2, 440);      yundong(6, 315);   }
    if (tui == 2) {     yundong(1, 440);      yundong(5, 315);
    }
    if (tui == 3) {     yundong(3, 210);     yundong(7, 150);   }
    if (tui == 4) {     yundong(0, 210);     yundong(4, 150);  }
  } else {
    if (tui == 1) {    yundong(2, 440 - (bu - 32) * 12 / 30);    yundong(6, 315 - (bu - 32) * 17 / 30);  }
    if (tui == 2) {    yundong(1, 440 - (bu - 32) * 12 / 30);    yundong(5, 315 - (bu - 32) * 17 / 30);  }
    if (tui == 3) {
      yundong(3, 210 + (bu - 100) * 10 / 30);
      yundong(7, 150 + (bu - 100) * 12 / 30);
    }
    if (tui == 4) {
      yundong(0, 210 + (bu - 100) * 10 / 30);
      yundong(4, 150 + (bu - 100) * 12 / 30);
    }
  }
}

void yundong(int djbianhao, int zhi) {
  if (djbianhao == 0 || djbianhao == 1 || djbianhao == 2 || djbianhao == 3) {
    if (djbianhao == 0) {
      pwmController1.setChannelPWM(0, zhi);

    } else if (djbianhao == 1) {
      pwmController1.setChannelPWM(1, zhi - 50);

    } else if (djbianhao == 2) {
      pwmController1.setChannelPWM(2, zhi);                                                

    } else if (djbianhao == 3) {
      pwmController1.setChannelPWM(3, zhi);
    }
  } else if (djbianhao == 4 || djbianhao == 5 || djbianhao == 6 || djbianhao == 7) {
    if (djbianhao == 4) {
      pwmController2.setChannelPWM(4, zhi - 30);
    } else if (djbianhao == 5) {
      pwmController2.setChannelPWM(5, zhi - 20);
    } else if (djbianhao == 6) {
      pwmController2.setChannelPWM(6, zhi);
    } else if (djbianhao == 7) {
      pwmController2.setChannelPWM(7, zhi);
    }
  }
}
void sport(int a,int b){
  if (a >= 0) {
    digitalWrite(IN1M,LOW);
    ledcWrite(1, a);
  } else {
    digitalWrite(IN1M,HIGH);
    ledcWrite(1, -a);
  }
  //电机的正负输出判断        右电机判断
  if (b >= 0) {
    digitalWrite(IN2M,HIGH);
    ledcWrite(2, b);
  } else {
    digitalWrite(IN2M,LOW);
    ledcWrite(2, -b);
  }
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

void ledjs()
{

}

void shoutao()
{

}