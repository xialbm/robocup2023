int anniu1=0;
int anniujiasu=0;
unsigned long time1 = 0;
int anniujishux=0;

int setx=1;

void setup() {
  Serial.begin(9600);
  Serial2.begin(38400);
}

void loop() {
  anniu();
  anniujishux=anniujishux+1;
  if(anniu1>0)
  {
      if(setx==1)
      {
        if(anniu1==2)zigbeesend(1);
        else if(anniu1==3)zigbeesend(2);
        else if(anniu1==4)zigbeesend(3);
        else if(anniu1==5)zigbeesend(4);
      }
      else if(setx==2)
      {
        if(anniu1==2)zigbeesend(5);
        else if(anniu1==3)zigbeesend(6);
        else if(anniu1==4)zigbeesend(7);
        else if(anniu1==5)zigbeesend(8);
      }
      else if(setx==3)
      {
        if(anniu1==2)zigbeesend(9);
        else if(anniu1==3)zigbeesend(10);
        else if(anniu1==4)zigbeesend(11);
        else if(anniu1==5)zigbeesend(12);
      }
      else if(setx==4)
      {
        if(anniu1==2)zigbeesend(13);
        else if(anniu1==3)zigbeesend(14);
        else if(anniu1==4)zigbeesend(15);
        else if(anniu1==5)zigbeesend(16);
      }
    anniujishux=0;
    anniu1=0;
  }
  if(anniujishux>5000){anniujishux=0;Serial2.write(100);}
  jieshou();
}


void anniu() {
  int s1, s2, s3;
  s1 = 500;
  s2 = analogRead(A1);
  s3 = analogRead(A0);
  // Serial.print(s1);
  // Serial.print("  ");
  // Serial.print(s2);
  // Serial.print("  ");
  // Serial.println(s3);
  if (s1 < 200 || s2 < 200 || s2 > 800 || s3 < 200 || s3 > 800) {
    time1 = millis();
    while (1) {
  s1 = 500;
  s2 = analogRead(A1);
  s3 = analogRead(A0);

      if (s2 < 300 && anniu1 != 1) anniu1 = 2;
      if (s2 > 700 && anniu1 != 1) anniu1 = 3;
      if (s3 < 300 && anniu1 != 1) anniu1 = 4;
      if (s3 > 700 && anniu1 != 1) anniu1 = 5;
      if (s1 < 220) anniu1 = 1;

      if (millis() > time1 + 500 - anniujiasu * 10) {
        anniujiasu = anniujiasu + 5;
        if (anniujiasu > 20) anniujiasu = 20;
        break;
      }
      if (s1 > 300 && s2 > 200 && s2 < 800 && s3 > 200 && s3 < 800) {
        anniujiasu = 0;
        break;
      }
    }
  } else anniujiasu = 0;
  delay(10);
}



void jieshou()
{ 
  if(Serial2.available()> 0)
  {
    Serial.write(Serial2.read());
  }
}

void zigbeesend(int zbsj)
{
  Serial.println(" ");
  Serial.print("send ");
  Serial.println(zbsj);
  Serial2.write(zbsj);
}