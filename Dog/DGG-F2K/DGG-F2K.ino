//0123下    4567上
#include "PCA9685.h"
PCA9685 pwmController1(0x41);
PCA9685 pwmController2(0x60);
int a = 100, b = 310, c = 500;

int xxa,xxb;
int steptime=2;
int stepc=0;
void setup() {
  pinMode(34,INPUT);
  pinMode(35,INPUT);
  Wire.begin();
  pwmController1.resetDevices();
  pwmController2.resetDevices();
  pwmController1.init();
  pwmController2.init();
  pwmController1.setPWMFrequency(50);
  pwmController2.setPWMFrequency(50);
 Serial.begin(9600);
 xxa=analogRead(34)/10;
 xxb=analogRead(35)/10;

 yundong(2,400);
yundong(6,315);
yundong(1,400);
yundong(5,315);

yundong(3,250);
yundong(7,150);
yundong(0,250);
yundong(4,150);

 delay(2000);
}
void loop() {


stepc=stepc+1;
if(stepc>200)stepc=0;
gougou(1,stepc);
gougou(2,(stepc+100)%200);
gougou(3,(stepc+100)%200);
gougou(4,(stepc+0)%200);
delay(steptime);


}




void gougou(int tui,int bu)
{

    if(bu<8)
    {
      if(tui==1){yundong(2,300);yundong(6,230);}
      if(tui==2){yundong(1,300);yundong(5,230);}
      if(tui==3){yundong(3,150);yundong(7,210);}
      if(tui==4){yundong(0,150);yundong(4,210);}
    }
    else if(bu<24)
    {
      if(tui==1){yundong(2,300);yundong(6,315);}
      if(tui==2){yundong(1,300);yundong(5,315);}
      if(tui==3){yundong(3,150);yundong(7,150);}
      if(tui==4){yundong(0,150);yundong(4,150);}
    }
    else if(bu<32)
    {
      if(tui==1){yundong(2,400);yundong(6,315);}
      if(tui==2){yundong(1,400);yundong(5,315);}
      if(tui==3){yundong(3,200);yundong(7,150);}
      if(tui==4){yundong(0,200);yundong(4,150);}
    }
    else 
    {
      if(tui==1){yundong(2,400-(bu-100)*12/30);yundong(6,315-(bu-100)*17/30);}
      if(tui==2){yundong(1,400-(bu-100)*12/30);yundong(5,315-(bu-100)*17/30);}
      if(tui==3){yundong(3,200+(bu-100)*10/30);yundong(7,150+(bu-100)*12/30);}
      if(tui==4){yundong(0,200+(bu-100)*10/30);yundong(4,150+(bu-100)*12/30);}
    }
  
}



void yundong(int djbianhao, int zhi) {
  if (djbianhao == 0 || djbianhao == 1 || djbianhao == 2 || djbianhao == 3) {
    if (djbianhao == 0) {
      pwmController1.setChannelPWM(0, zhi);

    } else if (djbianhao == 1) {
      pwmController1.setChannelPWM(1, zhi-50);

    } else if (djbianhao == 2) {
      pwmController1.setChannelPWM(2, zhi);

    } else if (djbianhao == 3) {
      pwmController1.setChannelPWM(3, zhi);
    }
  } else if (djbianhao == 4 || djbianhao == 5 || djbianhao == 6 || djbianhao == 7) {
    if (djbianhao == 4) {
      pwmController2.setChannelPWM(4,  zhi-30);

    } else if (djbianhao == 5) {
      pwmController2.setChannelPWM(5,  zhi-20);

    } else if (djbianhao == 6) {
      pwmController2.setChannelPWM(6,   zhi);

    } else if (djbianhao == 7) {
      pwmController2.setChannelPWM(7,  zhi);
    }
  }
}