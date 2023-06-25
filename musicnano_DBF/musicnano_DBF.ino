#include <SPI.h>
#include <SD.h>
const int chipSelect = 10;
int steptime = 27;
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 4); // RX, TX
SoftwareSerial mySerial2(3, 5); // RX, TX
SoftwareSerial mySerial1(8, 7); // RX, TX
SoftwareSerial mySerial3(A0, 9); // RX, TX
#define M_B0 31
#define M_C1 33
#define M_CS1 35
#define M_D1 37
#define M_DS1 39
#define M_E1 41
#define M_F1 44
#define M_FS1 46
#define M_G1 49
#define M_GS1 52
#define M_A1 55
#define M_AS1 58
#define M_B1 62
#define M_C2 65
#define M_CS2 69
#define M_D2 73
#define M_DS2 78
#define M_E2 82
#define M_F2 87
#define M_FS2 93
#define M_G2 98
#define M_GS2 104
#define M_A2 110
#define M_AS2 117
#define M_B2 123
#define M_C3 131
#define M_CS3 139
#define M_D3 147
#define M_DS3 156
#define M_E3 165
#define M_F3 175
#define M_FS3 185
#define M_G3 196
#define M_GS3 208
#define M_A3 220
#define M_AS3 233
#define M_B3 247
#define M_C4 262
#define M_CS4 277
#define M_D4 294
#define M_DS4 311
#define M_E4 330
#define M_F4 349
#define M_FS4 370
#define M_G4 392
#define M_GS4 415
#define M_A4 440
#define M_AS4 466
#define M_B4 494
#define M_C5 523
#define M_CS5 554
#define M_D5 587
#define M_DS5 622
#define M_E5 659
#define M_F5 698
#define M_FS5 740
#define M_G5 784
#define M_GS5 831
#define M_A5 880
#define M_AS5 932
#define M_B5 988
#define M_C6 1047
#define M_CS6 1109
#define M_D6 1175
#define M_DS6 1245
#define M_E6 1319
#define M_F6 1397
#define M_FS6 1480
#define M_G6 1568
#define M_GS6 1661
#define M_A6 1760
#define M_AS6 1865
#define M_B6 1976
#define M_C7 2093
#define M_CS7 2217
#define M_D7 2349
#define M_DS7 2489
#define M_E7 2637
#define M_F7 2794
#define M_FS7 2960
#define M_G7 3136
#define M_GS7 3322
#define M_A7 3520
#define M_AS7 3729
#define M_B7 3951
#define M_C8 4186
#define M_CS8 4435
#define M_D8 4699
#define M_DS8 4978


long timer = 0;
long timer2 = 0;
int readbu = 0;
int readbu2 = 0;
String shuzistr = "";
String shuzistr2 = "";
int readxx, gozt;
float goxx, goyy, gozz;
int readxx2, gozt2;
float goxx2, goyy2, gozz2;
long lasttime = 0;
long lasttime2 = 0;
String sendx = "";
long hh = 0;
long hh2=0;
long lastbegin = 0;
long lastbegin2 = 0;
int newmu = 0;
bool xxfh = 0;
bool xxfh2=0;
String openwjm = "";
String openwjm2 = "";
int openwjs = 0;
int openwjsx = 0;
int pn1 = 0;
int pn2 = 0;
int pn3 = 0;
int zhuangtai = 0;
int bfsx = 0;
int readf1 = 0;
int readf2 = 0;
String gozts; 

void setup() {
  mySerial1.begin(38400);
  mySerial2.begin(38400);
  mySerial3.begin(38400);
  mySerial.begin(38400);
  pinMode(6, OUTPUT);

  pinMode(10, OUTPUT);
  Serial.begin(9600);
  SD.begin(10);
  // tone(6, M_C3,300);
  delay(500);
  openwjs = 99;
}

void loop() {

  if (openwjs == 0) {
    openwjm = "";
    openwjm2 = "";
  }
  else if (openwjs == 99) {
    openwjm = "MUSIC01.txt";
    openwjm2 = "MUSIC02.txt";
  }
  else if (openwjs == 1) {
    openwjm = "MUSIC11.txt";
    openwjm2 = "MUSIC12.txt";
  }
  else if (openwjs == 2) {
    openwjm = "MUSIC21.txt";
    openwjm2 = "MUSIC22.txt";
  }
  else if (openwjs == 3) {
    openwjm = "MUSIC31.txt";
    openwjm2 = "MUSIC32.txt";
  }
  else if (openwjs == 4) {
    openwjm = "MUSIC41.txt";
    openwjm2 = "MUSIC42.txt";
  }
  else {
    openwjm = "";
  }

  /*{
    openwjsx++;
    if (openwjsx >= 8)openwjsx = 0;
    if (openwjsx == 1) {
     openwjm = "KLDYZY.txt";
    }  else if (openwjsx == 2) {
     openwjm = "RA3.txt";
    } else if (openwjsx == 3) {
     openwjm = "gthljxq.txt";
    } else if (openwjsx == 4) {
      openwjm = "CAIR2.txt";
    } else if (openwjsx == 5) {
      openwjm = "FLHB.txt";
    } else if (openwjsx == 6) {
      openwjm = "bad apple.txt";
    } else if (openwjsx == 7) {
      openwjm = "HRTG.txt";
    } else {
      openwjm = "CAIR.txt";
    }
    }*/



  if (openwjm != ""){  Serial.println(openwjm);sendair();}
  noTone(6);

  delay(100);
  jieshou();

}


void musicauto(int soun, long dela)
{
  // Serial.print(soun);Serial.print("  "); Serial.println(dela);
  if (soun == 0) noTone(6);
  else if (soun == 11) tone(6, M_C1, dela);
  else if (soun == -11) tone(6, M_CS1, dela);
  else if (soun == 12) tone(6, M_D1, dela);
  else if (soun == -12) tone(6, M_DS1, dela);
  else if (soun == 13) tone(6, M_E1, dela);
  else if (soun == 14) tone(6, M_F1, dela);
  else if (soun == -14) tone(6, M_FS1, dela);
  else if (soun == 15) tone(6, M_G1, dela);
  else if (soun == -15) tone(6, M_GS1, dela);
  else if (soun == 16) tone(6, M_A1, dela);
  else if (soun == -16) tone(6, M_AS1, dela);
  else if (soun == 17) tone(6, M_B1, dela);
  else if (soun == 21) tone(6, M_C2, dela);
  else if (soun == -21) tone(6, M_CS2, dela);
  else if (soun == 22) tone(6, M_D2, dela);
  else if (soun == -22) tone(6, M_DS2, dela);
  else if (soun == 23) tone(6, M_E2, dela);
  else if (soun == 24) tone(6, M_F2, dela);
  else if (soun == -24) tone(6, M_FS2, dela);
  else if (soun == 25) tone(6, M_G2, dela);
  else if (soun == -25) tone(6, M_GS2, dela);
  else if (soun == 26) tone(6, M_A2, dela);
  else if (soun == 26) tone(6, M_AS2, dela);
  else if (soun == 27) tone(6, M_B2, dela);
  else if (soun == 31) tone(6, M_C3, dela);
  else if (soun == -31) tone(6, M_CS3, dela);
  else if (soun == 32) tone(6, M_D3, dela);
  else if (soun == -32) tone(6, M_DS3, dela);
  else if (soun == 33) tone(6, M_E3, dela);
  else if (soun == 34) tone(6, M_F3, dela);
  else if (soun == -34) tone(6, M_FS3, dela);
  else if (soun == 35) tone(6, M_G3, dela);
  else if (soun == -35) tone(6, M_GS3, dela);
  else if (soun == 36) tone(6, M_A3, dela);
  else if (soun == -36) tone(6, M_AS3, dela);
  else if (soun == 37) tone(6, M_B3, dela);
  else if (soun == 41) tone(6, M_C4, dela);
  else if (soun == -41) tone(6, M_CS4, dela);
  else if (soun == 42) tone(6, M_D4, dela);
  else if (soun == -42) tone(6, M_DS4, dela);
  else if (soun == 43) tone(6, M_E4, dela);
  else if (soun == 44) tone(6, M_F4, dela);
  else if (soun == -44) tone(6, M_FS4, dela);
  else if (soun == 45) tone(6, M_G4, dela);
  else if (soun == -45) tone(6, M_GS4, dela);
  else if (soun == 46) tone(6, M_A4, dela);
  else if (soun == -46) tone(6, M_AS4, dela);
  else if (soun == 47) tone(6, M_B4, dela);
  else if (soun == 51) tone(6, M_C5, dela);
  else if (soun == -51) tone(6, M_CS5, dela);
  else if (soun == 52) tone(6, M_D5, dela);
  else if (soun == -52) tone(6, M_DS5, dela);
  else if (soun == 53) tone(6, M_E5, dela);
  else if (soun == 54) tone(6, M_F5, dela);
  else if (soun == -54) tone(6, M_FS5, dela);
  else if (soun == 55) tone(6, M_G5, dela);
  else if (soun == -55) tone(6, M_GS5, dela);
  else if (soun == 56) tone(6, M_A5, dela);
  else if (soun == -56) tone(6, M_AS5, dela);
  else if (soun == 57) tone(6, M_B5, dela);

}




void sendair()
{
  pn1 = 0; pn2 = 0; pn3 = 0;
  File dataFile = SD.open(openwjm);   //打开文件
  File dataFile2 ;
  if (openwjm2 != "") dataFile2 = SD.open(openwjm2);
  timer = millis();
  openwjs = 0;
  lasttime = 0;
  lastbegin = 0;
  lasttime2 = 0;
  lastbegin2 = 0;
  readf1 = 0;
  readf2 = 0;
  hh = 0;
  hh2=0;
  gozt = -100;
  steptime = 27;
  Serial.println("begin");
  if (dataFile)
  { readbu = 0; shuzistr = "";
    while (1)
    {
      jieshou();
      if (dataFile.available()&&readf1==0)
      {
        readxx = dataFile.read();
        if (readxx == 35 || readxx == 42) {
          while (1) {
            readxx = dataFile.read();
            Serial.write(readxx);
            if (readxx == 13)break;
          } Serial.println("-A");
          readbu = 0;
        }
        if (readbu == 0 && readxx == 71)readbu = 1;
        if (readbu == 1 && readxx == 88) {
          gozt = zhuanhuan2(shuzistr);
          shuzistr = "";
          readbu = 2;
        }
        if (readbu == 2 && readxx == 89) {
          if (shuzistr.indexOf('-') >= 0) xxfh = 1;
          else xxfh = 0;
          goxx = zhuanhuan2(shuzistr);
          shuzistr = "";
          readbu = 3;
        }
        if (readbu == 3 && readxx == 90) {
          goyy = zhuanhuan2(shuzistr);
          shuzistr = "";
          readbu = 4;
        }
        if (readbu > 0 && readxx > 44 && readxx < 58) shuzistr = shuzistr + (char)(readxx);
        if (readxx == 13) {
          gozz = zhuanhuan2(shuzistr);
          shuzistr = "";
          hh = hh + 1;
        }
        else if (readxx == 10) {
          if (gozt != -100)readf1=1;
          if (gozt == 99)newmu = 99;
          shuzistr = "";  readbu = 0;
        }
        if (gozt == 88) {
          pn1 = goxx;
          pn2 = goyy;
          pn3 = gozz;
          newmu = 0;
        }
        if (gozt == 77) {
          if (goxx > 0)steptime = goxx;
          newmu = 0;
        }
      }


      if (dataFile2.available()&&readf2==0)
      {
        readxx2 = dataFile2.read();
        if (readxx2 == 35 || readxx2 == 42) {
          while (1) {
            readxx2 = dataFile2.read();
            Serial.write(readxx2);
            if (readxx2 == 13)break;
          } Serial.println("-B");
          readbu = 0;
        }
        if (readbu2 == 0 && readxx2 == 71)readbu2 = 1;
        if (readbu2 == 1 && readxx2 == 88) {
          gozt2 = zhuanhuan2(shuzistr2);
          shuzistr2 = "";
          readbu2 = 2;
        }
        if (readbu2 == 2 && readxx2 == 89) {
          if (shuzistr2.indexOf('-') >= 0) xxfh2 = 1;
          else xxfh2 = 0;
          goxx2 = zhuanhuan2(shuzistr2);
          shuzistr2 = "";
          readbu2 = 3;
        }
        if (readbu2 == 3 && readxx2 == 90) {
          goyy2 = zhuanhuan2(shuzistr2);
          shuzistr2 = "";
          readbu2 = 4;
        }
        if (readbu2 > 0 && readxx2 > 44 && readxx2 < 58) shuzistr2 = shuzistr2 + (char)(readxx2);
        if (readxx2 == 13) {
          gozz2 = zhuanhuan2(shuzistr2);
          shuzistr2 = "";
          hh2 = hh2 + 1;
        }
        else if (readxx2 == 10) {
          if (gozt2 != -100)readf2=1;
          if (gozt2 == 99)newmu = 99;
          shuzistr2 = "";  readbu2 = 0;
        }
        if (gozt2 == 88) {
          pn1 = goxx2;
          pn2 = goyy2;
          pn3 = gozz2;
          newmu = 0;
        }
        if (gozt2 == 77) {
          if (goxx2 > 0)steptime = goxx2;
          newmu = 0;
        }
      }


      if (openwjs > 0) {
        newmu = 0;
        goxx = 0;
        break;
      }


      if(readf1==1)
      {
        if (goxx == 0 && hh > 1 && xxfh == 0)
        { goxx = lasttime / steptime;
          gozz = lasttime / steptime + gozz;
        }
        else if (xxfh == 1)
        {
          gozz = lastbegin / steptime - goxx + gozz;
          goxx = lastbegin / steptime - goxx;
        }
        lastbegin = goxx * steptime;
        lasttime = gozz * steptime;
        readf1 = 2;
       
      }
      
      if(readf2==1)
      {
        if (goxx2 == 0 && hh2 > 1 && xxfh2 == 0)
        { goxx2 = lasttime2 / steptime;
          gozz2 = lasttime2 / steptime + gozz2;
        }
        else if (xxfh2 == 1)
        {
          gozz2 = lastbegin2 / steptime - goxx2 + gozz2;
          goxx2 = lastbegin2 / steptime - goxx2;
        }
        lastbegin2 = goxx2 * steptime;
        lasttime2 = gozz2 * steptime;
        readf2 = 2;
       
      }




      

      if (readf1==2&&timer > 0 && (millis() - timer) >= (goxx * steptime))
      {
       Serial.print(gozt); Serial.print("  "); Serial.print(goxx); Serial.print("  "); Serial.print(goyy); Serial.print("  "); Serial.print(gozz); Serial.print("  ");Serial.print("read "); Serial.println(readf1);
       gozts=String(gozt);
        if (String(gozt).indexOf("1")>=0) {
          if (gozz > 0)
          {
            noTone(6); delay(1);
            musicauto(goyy + pn1, (gozz - goxx)*steptime);
          }
        }
        if (String(gozt).indexOf("2")>=0) {
          if (gozz > 0)
          {
            sendx = "A" + String(int(goyy + pn2)) + "B" + int((gozz - goxx) * steptime);
            mySerial1.println(sendx);
            //Serial.println(sendx);
          }
        }
        if (String(gozt).indexOf("3")>=0) {
          if (gozz > 0)
          {
            sendx = "A" + String(int(goyy + pn3)) + "B" + int((gozz - goxx) * steptime);
            mySerial2.println(sendx);
          }
        }
        if (String(gozt).indexOf("4")>=0) {
          if (gozz > 0)
          {
            sendx = "A" + String(int(goyy + pn3)) + "B" + int((gozz - goxx) * steptime);
            mySerial3.println(sendx);
          }
        }
        if (newmu == 99) break;
        newmu = 0;
        readf1=0;
        gozt = -100;
      }



      if (readf2==2&&timer > 0 && (millis() - timer) >= (goxx2 * steptime))
      {
       Serial.print(gozt2); Serial.print("  "); Serial.print(goxx2); Serial.print("  "); Serial.print(goyy2); Serial.print("  "); Serial.print(gozz2); Serial.print("  ");Serial.print("read2 "); Serial.println(readf2);
        if (String(gozt2).indexOf("1")>=0) {
          if (gozz2 > 0)
          {
            noTone(6); delay(1);
            musicauto(goyy2 + pn1, (gozz2 - goxx2)*steptime);
          }
        }
        if(String(gozt2).indexOf("2")>=0) {
          if (gozz2 > 0)
          {
            sendx = "A" + String(int(goyy2 + pn2)) + "B" + int((gozz2 - goxx2) * steptime);
            mySerial1.println(sendx);
            //Serial.println(sendx);
          }
        }
        if(String(gozt2).indexOf("3")>=0)  {
          if (gozz2 > 0)
          {
            sendx = "A" + String(int(goyy2 + pn3)) + "B" + int((gozz2 - goxx2) * steptime);
            mySerial2.println(sendx);
          }
        }
       if(String(gozt2).indexOf("4")>=0)  {
          if (gozz2 > 0)
          {
            sendx = "A" + String(int(goyy2 + pn3)) + "B" + int((gozz2 - goxx2) * steptime);
            mySerial3.println(sendx);
          }
        }
        if (newmu == 99) break;
        newmu = 0;
        readf2=0;
        gozt2 = -100;
      }

    }
  }
  while (timer > 0 && millis() - timer < goxx * steptime) {}
  dataFile.close();
  sendx = "A" + String(int(0)) + "B" + int(10);
  mySerial1.println(sendx);
  mySerial2.println(sendx);
  Serial.println("end");
}

int zhuanhuan2( String lswp1)
{
  char *lswpx = "";
  char p[10];
  int i;
  for ( i = 0; i < lswp1.length(); i++)
  {
    p[i] = lswp1[i] ;
  }
  p[i] = '\0';
  lswpx = (char*)p;
  return (atof(lswpx));
}



void jieshou2()
{
  if (Serial.available() > 0)
  {
    String getly = "";
    int wpjy, zj1, zj2;
    String lswp = "";
    openwjs = 0;
    delay(4);
    while (Serial.available() > 0)
    {
      getly += char(Serial.read());
    }
    if (getly.length() > 0)
    {
      zj1 = getly.indexOf("A");
      zj2 = getly.indexOf("B");
      if (zj1 > -1 && zj2 > -1)  {
        lswp = getly.substring(zj1 + 1, zj2);
        openwjs = zhuanhuan2(lswp);
      }
      zj1 = zj2;
      zj2 = getly.indexOf("\r\n");
      if (zj1 > -1 && zj2 > -1)  {
        lswp = getly.substring(zj1 + 1, zj2);
        wpjy = zhuanhuan2(lswp);
      }
    }
    Serial.print (getly); Serial.print ("  "); Serial.println(openwjs);
  }
}



void jieshou()
{
  if (mySerial.available() > 0)
  {
    int zj1;
    if (mySerial.read() != 201)
    {
    }
    else
    {
      delay(20);
      zj1 = mySerial.read();
      Serial.println(zj1);
      if (zhuangtai < zj1)
      {
        zhuangtai = zj1;
        if (zhuangtai >= 1 && bfsx < 1) {
          bfsx = 1;
          openwjs = 1;
        }
        if (zhuangtai >= 10 && bfsx < 2) {
          bfsx = 2;
          openwjs = 2;
        }
        if (zhuangtai >= 20 && bfsx < 3) {
          bfsx = 3;
          openwjs = 3;
        }
        if (zhuangtai >= 30 && bfsx < 4) {
          bfsx = 4;
          openwjs = 4;
        }
        if (zhuangtai >= 40 && bfsx < 5) {
          bfsx = 5;
          openwjs = 5;
        }
      }

    }
  }
}



void zigbeesend(int zbsj)
{
  mySerial.write(201);
  mySerial.write(zbsj);

}
