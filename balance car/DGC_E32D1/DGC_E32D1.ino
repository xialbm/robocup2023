#include <KalmanFilter.h>
#include <Wire.h>
#include <Esp.h>
#include "esp_system.h"
#include "esp_task_wdt.h"
KalmanFilter kalmanfilter;


int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
//TB6612FNG驱动模块的控制信号
#define IN1M 27
#define IN2M 33
#define PWMA 26
#define PWMB 32


#define PinA_left 34  //中断0
#define PinA_right 35 //中断1
//先p再i
const int MPU_addr = 0x68; // MPU-6050的i2c地址

int pulseleft = 0;
int pulseright = 0;

double angleoutput = 0, pwm1 = 0, pwm2 = 0;
float speeds_filterold;
float positions;
int turnmax = 2;
int turncount = 0; 
double speedoutput = 0;    
float turnoutput = 0;                                 
float turnout = 0;

long ttime=0;
int zhuangtai=90;
double setp0 = 0; 
int zz1=0;
int dj0=0;

//PID调试
float K1 =1; // 对加速度计取值的权重
float angle0 =1.09; //机械平衡角


double kp =40, kd = 1.1;                   //平衡PID，ki不需要
double kp_speed = -2.2, ki_speed = -0.04;    //速度PID，kd不需要      
double kp_turn = 20, kd_turn = 0.2;          //旋转PID设定， ki不需要
//转向PID参数

//卡尔曼滤波参数
float Q_angle = 0.001, Q_gyro = 0.005; //角度数据置信度,角速度数据置信度
float R_angle = 0.5 , C_0 = 1;
float timeChange = 5; //滤波法采样时间间隔毫秒
float dt = timeChange * 0.001; //注意：dt的取值为滤波器采样时间


volatile long count_left = 0;
volatile long count_right = 0;
int speedcc = 0;


int lz = 0;
int lpluse = 0;
int rz = 0;
int rpluse = 0;
int front = 0;
int back = 0;
int turnx = 0;



long timerx=0;
int showonce=0;








// ===    初始设置     ===
void setup() {
                      



  //初始化电机驱动模块
    esp_task_wdt_deinit();
  pinMode(IN1M, OUTPUT);                         
  pinMode(IN2M, OUTPUT);
  pinMode(PWMA, OUTPUT);                        
  pinMode(PWMB, OUTPUT);  
  digitalWrite(IN1M, 0);
  digitalWrite(IN2M, 0);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);

  pinMode(PinA_left, INPUT);  //测速码盘输入
  pinMode(PinA_right, INPUT);
  pinMode(13, OUTPUT);
  ledcAttachPin(PWMA, 1);
  ledcAttachPin(PWMB, 2);
  ledcSetup(1, 500, 8);
  ledcSetup(2, 500, 8);
 
  Wire.begin();
  Serial2.begin(38400);
  Serial.begin(9600);
  delay(100);
  Serial.println("x1x");

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); 
  Wire.write(0); //启动mpu6050
  Wire.endTransmission(true);                         //初始化MPU6050
  delay(500);


  attachInterrupt(PinA_left, Code_left, CHANGE);
  attachInterrupt(PinA_right, Code_right, CHANGE);
  sport (0, 0);
  ttime=millis();
  Serial.println(ttime-millis());
  timerx=millis();
digitalWrite(13,0);
delay(1000);
            
}

void loop() {

 // kongzhi();
//if (millis()-timerx>4){timerx=millis();onTimergo();}//////////调试
front=30;
 jieshou();

if(zhuangtai<10)
{
  ttime=millis();
 if(zhuangtai==1){zhuangtai=2;zigbeesend(1);digitalWrite(2,1);}
   count_left=0; count_right=0;positions=0;speeds_filterold=0;
   if (millis()-timerx>4){timerx=millis();mpugo();}
}
else if(zhuangtai<90)
 {
   ttime=millis();
   count_left=0; count_right=0;positions=0;speeds_filterold=0;
    if (millis()-timerx>4){timerx=millis();mpugo();}

    
 }
 else
 {
    if(millis()-ttime<4000)
    {front=50;}
     else if(millis()-ttime<6000)
     {sportkk (-90, 0);}
     else if(millis()-ttime<8000)
     {sportkk (-90, 0);digitalWrite(13,1);}
     else if(millis()-ttime<12000)
    { sportkk (-90, 50);}
     else
     {sportkk (-90, 0);}
    if (millis()-timerx>4){timerx=millis();onTimergo();}
 }

// if(millis()-ttime<5000){
// sport (45, 45); }
// else if(millis()-ttime<5500){
// sport (20, 20); }
// else if(millis()-ttime<8000){
// sport (0, 0); if (millis()-timerx>4){timerx=millis();mpugo();}
// } 
// else if(millis()-ttime<8200){
// sport (0, 0);count_left=0; count_right=0;positions=0;if (millis()-timerx>4){timerx=millis();mpugo();}}
// else if(millis()-ttime<8500){
// sportkk(0,5);if (millis()-timerx>4){timerx=millis();onTimergo();}}
// else if(millis()-ttime<18500){
// sportkk(0,30); if (millis()-timerx>4){timerx=millis();onTimergo();}}
// else {sportkk(90,0); if (millis()-timerx>4){timerx=millis();onTimergo();}}
// }


}









//////////////////////////脉冲中断计算/////////////////////////////////////

void Code_left()  {
  count_left ++;  //左测速码盘计数
}

void Code_right() {
  count_right ++; //右测速码盘计数
}

//////////////////////////脉冲中断计算/////////////////////////////////////













//////////////////////脉冲计算///////////////////////
void countpluse()
{

  lz = count_left;
  rz = count_right;

  count_left = 0;
  count_right = 0;

  lpluse = lz;
  rpluse = rz;

  if ((pwm1 < 0) && (pwm2 < 0))                     //小车运动方向判断 后退时（PWM即电机电压为负） 脉冲数为负数
  {
    rpluse = rpluse;
    lpluse = lpluse;
  }
  else if ((pwm1 > 0) && (pwm2 > 0))                 //小车运动方向判断 前进时（PWM即电机电压为正） 脉冲数为负数
  {
    rpluse = -rpluse;
    lpluse = -lpluse;
  }
  else if ((pwm1 < 0) && (pwm2 > 0))                 //小车运动方向判断 前进时（PWM即电机电压为正） 脉冲数为负数
  {
    rpluse = -rpluse;
    lpluse = lpluse;
  }
  else if ((pwm1 > 0) && (pwm2 < 0))               //小车运动方向判断 左旋转 右脉冲数为负数 左脉冲数为正数
  {
    rpluse = rpluse;
    lpluse = -lpluse;
  }



  //每5ms进入中断时，脉冲数叠加
  pulseright += rpluse;
  pulseleft += lpluse;

}
////////////////////脉冲计算///////////////////////








void  onTimergo()
{

  countpluse();                                     //脉冲叠加子函数
  esp32MPU();
  kalmanfilter.Angletest(AcX, AcY, AcZ, GyX, GyY, GyZ, dt, Q_angle, Q_gyro, R_angle, C_0, K1);                                   //获取angle角度和卡曼滤波
  angleoutput = kp * (kalmanfilter.angle - angle0) + kd * kalmanfilter.Gyro_x;                                  //角度环 PD控制 P角度 D瞬时加速度

  speedcc++;                  //计数器
  if (speedcc >= 8)                                //40ms进入速度环计算
  {
    speedoutput = speedpiout(kp_speed, ki_speed, front, back, setp0);
    speedcc = 0;
  }
  turncount++;
  if (turncount >= 2)                                //10ms进入转动环计算
  {
    turnoutput = turnspin(turnx, kp_turn, kd_turn, kalmanfilter.Gyro_z);                              //旋转子函数
    turncount = 0;
  }
 
  pwma();           //小车总PWM输出

}












//速度PI
double speedpiout(double kps, double kis,  int f, int b, double p0)
{
  float speeds = (pulseleft + pulseright) * 1.0;                                                               //车速 脉冲值
  pulseleft = pulseright = 0;                                                                   //一阶互补滤波
  float speeds_filter = speeds_filterold*0.7 + speeds * 0.3;
  speeds_filterold = speeds_filter;
  positions =positions+ speeds_filter+f+b;                                                                       
  positions = constrain(positions, -4550, 4550); //抗积分饱和
  double output = kis * (p0 - positions) + kps * (p0 - speeds_filter);                      //速度环控制 PI


  return output;
}
//转动PI

float turnspin(int turnflag, double kpturn, double kdturn, float Gyroz)
{

  float turnspeed = 0;
float turnout_put = 0;

  if (turnflag != 0 &&(kalmanfilter.angle - angle0)<  2&&(kalmanfilter.angle - angle0) > -2)
  {

    turnspeed = ( 2* pulseleft);                       //小车当前车速 脉冲表示
    if (turnspeed < 0)                                 //小车当前速度绝对值
    {
      turnspeed = -turnspeed;
    }
    if(turnspeed==0)turnspeed=1;
    turnspeed = 55 / turnspeed;                        //根据小车速度设定值
    if (turnspeed <0.5)turnspeed = 0.5;
    if (turnspeed > 3)turnspeed = 3;
  }
  else
  {
    turnspeed = 0;
  }
 
  if (turnflag == 1 )//根据方向参数叠加
  {
    turnout += turnspeed;
  }
  else if (turnflag == -1)//根据方向参数叠加
  {
    turnout -= turnspeed;
  }
  else turnout = 0;
     
  if (turnout > turnmax) turnout = turnmax;//幅值最大值设置
  if (turnout < -turnmax) turnout = -turnmax;//幅值最小值设置

  turnout_put =turnout * kpturn- Gyroz * kdturn;//旋转PD算法控制 融合速度和Z轴旋转定位。
  return turnout_put;
}



//运动合成
void pwma()
{

  pwm1 = -angleoutput - speedoutput - turnoutput; //Left电机PWM输出值
  pwm2 = -angleoutput - speedoutput + turnoutput;//Right电机PWM输出值

  //幅度值限制
  if (pwm1 > 255) pwm1 = 255;
  if (pwm1 < -255) pwm1 = -255;
  if (pwm2 > 255) pwm2 = 255;
  if (pwm2 < -255) pwm2 = -255;
  sport(pwm1,pwm2);

  //角度过大，停止电机
  if ((kalmanfilter.angle - angle0) > 40 || (kalmanfilter.angle - angle0)< -40)
  {
    sport(0,0);
    while(1)
      {
          count_left=0; count_right=0;positions=0;speeds_filterold=0;
          if (millis()-timerx>4){timerx=millis();mpugo();}
          if((kalmanfilter.angle - angle0)<1 && (kalmanfilter.angle - angle0)>-1) break;
      }
    positions = 0;
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
  //  Serial.print("AcX = "); Serial.print(AcX);
  //  Serial.print(" | AcY = "); Serial.print(AcY);
  //  Serial.print(" | AcZ = "); Serial.print(AcZ);
  //  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53); //equation for temperature in degrees C from datasheet
  //  Serial.print(" | GyX = "); Serial.print(GyX);
  //  Serial.print(" | GyY = "); Serial.print(GyY);
  //  Serial.print(" | GyZ = "); Serial.println(GyZ);
}



////////////////////////bluetooth//////////////////////
void kongzhi()
{
  while (Serial2.available())                                    //等待蓝牙数据
  
  {
    

 switch (Serial2.read())                                      //读取蓝牙数据
    {
      case 1: kp = kp+0.5;   break;                        
      case 2: kp = kp-0.5;   break;                        
      case 3: kd = kd+0.05;   break;                        
      case 4: kd = kd-0.05;    break;                         
      case 5: kp_speed=kp_speed+0.05;ki_speed=kp_speed/200.0;   break;                       
      case 6: kp_speed=kp_speed-0.05;ki_speed=kp_speed/200.0;   break;                      
      case 7: ki_speed=ki_speed+0.005;  break;                   
      case 8: ki_speed=ki_speed-0.005;  break;                  
      case 9: kp_turn = kp_turn+0.5; break;  
      case 10: kp_turn = kp_turn-0.5; break;       
      case 11: kd_turn = kd_turn+0.5; break;   
      case 12: kd_turn = kd_turn-0.5; break;   
      case 13: front = 50; turnx = 0;  break;                         //前进
      case 14: back = -50; turnx = 0;  break;                        //后退
      case 15: front = 0; back = 0; turnx=1;break; 
      case 16: front = 0; back = 0; turnx=-1;break; 
      default: front = 0; back = 0; turnx = 0;  turnoutput = 0; break;
    }
Serial2.print("kp:");Serial2.print(kp);Serial2.print(" kd:");Serial2.print(kd);
Serial2.print(" kps:");Serial2.print(kp_speed);Serial2.print(" kis:");Serial2.print(ki_speed);
Serial2.print(" kpt:");Serial2.print(kp_turn);Serial2.print(" kdt:");Serial2.print(kd_turn);
Serial2.print(" ang:");Serial2.println(kalmanfilter.angle);Serial2.println(" ");

  }
}


////////////////////////////////////////turn//////////////////////////////////


void mpugo()
{
  esp32MPU();
  kalmanfilter.Angletest(AcX, AcY, AcZ, GyX, GyY, GyZ, dt, Q_angle, Q_gyro, R_angle, C_0, K1); 
}








void sportkk (int a, int b){
    a = (a-znzget() + 720) % 360;
    if(a>180) a=a-360;
    if(a > 3){
      turnx = 1;
      front = 0;
    }else if(a< -3){
      turnx = -1;
      front = 0;
    }else{
      turnx = 0;
      front = b;
    }
}

void sportkk2(int a, int b){

      turnx = 0;
      front = b;
    
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
      Serial.println(zj1);
      if(zhuangtai<zj1) zhuangtai=zj1;
      
    }
  }
}

void zigbeesend(int zbsj)
{
  Serial2.write(201);
  Serial2.write(zbsj);

}
int calculatePWM(int degree)//小舵机
{ 
  const float deadZone = 6.4;
  const float max = 32;
  if (degree < 0)
    degree = 0;
  if (degree > 180)
    degree = 180;
  return (int)(((max - deadZone) / 180) * degree + deadZone);
}


