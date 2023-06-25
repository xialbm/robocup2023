#include <Wire.h>
#include <AccelStepper.h>
#include <Adafruit_PWMServoDriver.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2); // RX, TX
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define STEPPER1_DIR_PIN 4
#define STEPPER1_STEP_PIN 5
#define M_G0 98
#define M_GS0 104
#define M_A0 111
#define M_AS0 117
#define M_B0 124
#define M_C1 131
#define M_CS1 139
#define M_D1 147
#define M_DS1 156
#define M_E1 165
#define M_F1 175
#define M_FS1 186
#define M_G1 197
#define M_GS1 208
#define M_A1 221
#define M_AS1 234
#define M_B1 248
#define M_C2 263
#define M_CS2 278
#define M_D2 295
#define M_DS2 313
#define M_E2 331
#define M_F2 351
#define M_FS2 372
#define M_G2 394
#define M_GS2 417
#define M_A2 442
#define M_AS2 469
#define M_B2 497
#define M_C3 525//262     //131 //4248     8548
#define M_CS3 551//277//139 
#define M_D3 588//294//147 
#define M_DS3 622//311//156 
#define M_E3 660//330//165 
#define M_F3 700//349//175 
#define M_FS3 740//371//185 
#define M_G3 786//393//196  
#define M_GS3 833//0//208
#define M_A3 880//416//220
#define M_AS3 932//440//233
#define M_B3 988//467//247 
#define M_C4 1049//494//262
#define M_CS4 1110//524//277
#define M_D4 1177//555//294
#define M_DS4 1244//588//311
#define M_E4 1322//622//330
#define M_F4 1403//660//349
#define M_FS4 1483//699//370
#define M_G4 1563//741//392
#define M_GS4 1643//781//415
#define M_A4 1723//831//440
#define M_AS4 1803//881//466
#define M_B4 1997
#define M_C5 2105
#define M_CS5 2246
#define M_D5 2376
#define M_DS5 2518
#define M_E5 2656



AccelStepper stepper1(AccelStepper::DRIVER, STEPPER1_STEP_PIN, STEPPER1_DIR_PIN);


long s;
int sound=0;
long soundt=0;

void setup() {

  Serial.begin(9600);
  mySerial.begin(38400);
  Wire.begin();
  stepper1.setCurrentPosition (0);
  stepper1.setMaxSpeed(10000.0);

}


void loop(){ 

//jieshou();
jieshou2();
if(millis()<soundt) musi2(sound);
  

}
void musi2(int m){
stepper1.runSpeed();
}



void musicauto(int soun,long dela)
{
  
 if(soun==0) {soundt=0;sound=0;}
 else if(soun==11) sound=M_C1;
 else if(soun==-11) sound=M_CS1;
 else if(soun==12) sound=M_D1;
 else if(soun==-12) sound=M_DS1;
 else if(soun==13) sound=M_E1;
 else if(soun==14) sound=M_F1;
 else if(soun==-14) sound=M_FS1;
 else if(soun==15) sound=M_G1;
 else if(soun==-15) sound=M_GS1;
 else if(soun==16) sound=M_A1;
 else if(soun==-16) sound=M_AS1;
 else if(soun==17) sound=M_B1;
 else if(soun==21) sound=M_C2;
 else if(soun==-21) sound=M_CS2;
 else if(soun==22) sound=M_D2;
 else if(soun==-22) sound=M_DS2;
 else if(soun==23) sound=M_E2;
 else if(soun==24) sound=M_F2;
 else if(soun==-24) sound=M_FS2;
 else if(soun==25) sound=M_G2;
 else if(soun==-25) sound=M_GS2;
 else if(soun==26) sound=M_A2;
 else if(soun==-26) sound=M_AS2;
 else if(soun==27) sound=M_B2;
 else if(soun==31) sound=M_C3;
 else if(soun==-31) sound=M_CS3;
 else if(soun==32) sound=M_D3;
 else if(soun==-32) sound=M_DS3;
 else if(soun==33) sound=M_E3;
 else if(soun==34) sound=M_F3;
 else if(soun==-34) sound=M_FS3;
 else if(soun==35) sound=M_G3;
 else if(soun==-35) sound=M_GS3;
 else if(soun==36) sound=M_A3;
 else if(soun==-36) sound=M_AS3;
 else if(soun==37) sound=M_B3;
 else if(soun==41) sound=M_C4;
 else if(soun==-41) sound=M_CS4;
 else if(soun==42) sound=M_D4;
 else if(soun==-42) sound=M_DS4;
 else if(soun==43) sound=M_E4;
 else if(soun==44) sound=M_F4;
 else if(soun==-44) sound=M_FS4;
 else if(soun==45) sound=M_G4;
 else if(soun==-45) sound=M_GS4;
 else if(soun==46) sound=M_A4;
 else if(soun==-46) sound=M_AS4;
 else if(soun==47) sound=M_B4;
 else if(soun==51) sound=M_C5;
 else if(soun==-51) sound=M_CS5;
 else if(soun==52) sound=M_D5;
 else if(soun==-52) sound=M_DS5;
 else if(soun==53) sound=M_E5;

 stepper1.setSpeed(sound);

 if(soun!=0) soundt=millis()+dela;
 //Serial.print(soundt);Serial.print("  "); Serial.println(dela);
 
}


void jieshou2()
{
  if (mySerial.available() > 0)
  {
    String getly = "";
    int wp1, wpjy, zj1, zj2;
    String lswp = "";
    delay(4);
    while (mySerial.available() > 0)
    {
      getly += char(mySerial.read());
    }
    if (getly.length() > 0)
    {
       zj1=getly.indexOf("A");
       zj2=getly.indexOf("B");
       if(zj1>-1&&zj2>-1)  {lswp=getly.substring(zj1+1,zj2);wp1=zhuanhuan(lswp);}
       zj1=zj2;
       zj2=getly.indexOf("\r\n");
       if(zj1>-1&&zj2>-1)  {lswp=getly.substring(zj1+1,zj2);wpjy=zhuanhuan(lswp);}
    }
   Serial.print (getly);Serial.print ("  ");Serial.print(wp1);Serial.print ("    ");Serial.println (wpjy);
    musicauto(wp1,wpjy);
  }
}



int zhuanhuan( String lswp1)
{   
  
  char *lswpx="";
    char p[10];
    int i;
    for( i=0;i<lswp1.length();i++)
       { p[i] = lswp1[i];}
    p[i] = '\0';
    lswpx=(char*)p;
    return(atof(lswpx)); 
    
}
