#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>



SoftwareSerial SSSerial4(8, 9); // RX, TX
SoftwareSerial SSSerial5(10, 11); // RX, TX
LiquidCrystal_I2C lcd(0x27,16,2);

int showx=0;
int zj1,zj2,zj3,zj4,zj5;
int anniu1=1000;
long timer=0;
int get1,get2,get3,get4,get5;

void setup() {
  lcd.init();                    
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Prepare...");
  Serial1.begin(38400);delay(50);//大轮
  Serial2.begin(38400);delay(50);//平衡
  Serial3.begin(38400);delay(50);//狗
  SSSerial4.begin(38400);delay(50);
  SSSerial5.begin(38400);delay(50);
  Serial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print("wait...   ");
  timer=millis();
  while(1)
  {
    get1=jieshou1();
    get2=jieshou2();
    get3=jieshou3();
    if(get1>0){get1=0;lcd.setCursor(0, 1);lcd.print("*1*");}
    if(get2>0){get2=0;lcd.setCursor(3, 1);lcd.print("*2*");}
    if(get3>0){get3=0;lcd.setCursor(6, 1);lcd.print("*3*");}
    anniu1=(anniu1*29+analogRead(A0))/30;
    if(millis()-timer>2000){timer=millis();zigbeesend1(1);zigbeesend2(1);zigbeesend3(1);zigbeesend4(1);zigbeesend5(1);}
    if(anniu1<200){lcd.clear();delay(200);showx=1;break;}
  }

  zigbeesend2(10);
  zigbeesend4(10);
  zigbeesend3(10);
  lcd.setCursor(0, 0);lcd.print("A");//亮警灯
  delay(9000);
  zigbeesend1(20);
  zigbeesend4(20);
  lcd.setCursor(0, 0);lcd.print("B");//大轮开始走
  timer=millis();
  while(1)
  {
    get1=jieshou1();
    if(get1>=30){break;}
      if(millis()-timer>30000){lcd.setCursor(0, 1);lcd.print("T");break;}
  }
   zigbeesend1(40);
  delay(4500);
 
  zigbeesend3(40);
  lcd.setCursor(0, 0);lcd.print("C");//狗开始走
  timer=millis();
  while(1)
  {
    get3=jieshou3();
    if(get3>=50){break;}
      if(millis()-timer>15000){lcd.setCursor(0, 1);lcd.print("T");break;}
  }
  delay(500);
  zigbeesend3(60);
  lcd.setCursor(0, 0);lcd.print("D");//狗跟手套做动作
  delay(19000);

  zigbeesend3(70);
  delay(20000);
  zigbeesend1(70);
  lcd.setCursor(0, 0);lcd.print("E");//大轮开始倾斜
   timer=millis();
  while(1)
  {
    get1=jieshou1();
    if(get1>=80){break;}
      if(millis()-timer>8000){lcd.setCursor(0, 1);lcd.print("T");break;}
  }
  zigbeesend1(90);

  zigbeesend2(90);
  lcd.setCursor(0, 0);lcd.print("F");//放下小车
  delay(16000);
    zigbeesend1(100);
    zigbeesend3(100);
    lcd.setCursor(0, 0);lcd.print("G");//结束

}

void loop() {
    get1=jieshou1();
    get2=jieshou2();
    get3=jieshou3();
    if(get1>0){zigbeesend1(get1-1);get1=0;}
    if(get2>0){zigbeesend2(get2-1);get2=0;}
    if(get3>0){zigbeesend3(get3-1);get3=0;}

}





int jieshou1()
{ 
  zj1=0;
  if(Serial1.available()> 0)
  {
    if(Serial1.read()!=201) 
    {
    }
    else
    {
      delay(20); 
      zj1=Serial1.read();
    }
  }
  if(showx==1&&zj1>0){lcd.setCursor(0, 2);lcd.print("U1:   ");lcd.setCursor(3, 2);lcd.print(zj1);}
  return zj1;
}

int jieshou2()
{ 
  zj2=0;
  if(Serial2.available()> 0)
  {
    if(Serial2.read()!=201) 
    {
    }
    else
    {
      delay(20); 
      zj2=Serial2.read();
    }
  }
  if(showx==1&&zj2>0){lcd.setCursor(7, 2);lcd.print("U2:   ");lcd.setCursor(10, 2);lcd.print(zj2);}
  return zj2;
}

int jieshou3()
{ 
  zj3=0;
  if(Serial3.available()> 0)
  {
    if(Serial3.read()!=201) 
    {
    }
    else
    {
      delay(20); 
      zj3=Serial3.read();
    }
  }
  if(showx==1&&zj3>0){lcd.setCursor(14, 2);lcd.print("U3:   ");lcd.setCursor(17, 2);lcd.print(zj3);}
  return zj3;
}





void zigbeesend1(int zbsj)
{
  Serial1.write(201);
  Serial1.write(zbsj);
  if(showx==1){lcd.setCursor(2, 0);lcd.print("S1:   ");lcd.setCursor(5, 0);lcd.print(zbsj);}
}

void zigbeesend2(int zbsj)
{
  Serial2.write(201);
  Serial2.write(zbsj);
  if(showx==1){lcd.setCursor(8, 0);lcd.print("S2:   ");lcd.setCursor(11, 0);lcd.print(zbsj);}
}

void zigbeesend3(int zbsj)
{
  Serial3.write(201);
  Serial3.write(zbsj);
  if(showx==1){lcd.setCursor(14, 0);lcd.print("S3:   ");lcd.setCursor(17, 0);lcd.print(zbsj);}
}

void zigbeesend4(int zbsj)
{
  SSSerial4.write(201);
  SSSerial4.write(zbsj);
  if(showx==1){lcd.setCursor(2, 1);lcd.print("S4:   ");lcd.setCursor(5, 1);lcd.print(zbsj);}
}

void zigbeesend5(int zbsj)
{
  SSSerial5.write(201);
  SSSerial5.write(zbsj);
  if(showx==1){lcd.setCursor(8, 1);lcd.print("S5:   ");lcd.setCursor(11, 1);lcd.print(zbsj);}
}
