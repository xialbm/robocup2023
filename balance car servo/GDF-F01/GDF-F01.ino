
#include <Servo.h>

Servo myservo1; 
Servo myservo2; 
void setup() {
 myservo1.attach(8);  
 myservo2.attach(9);  
 myservo1.write(0);  
 myservo2.write(160);  

}

void loop() {
  if(analogRead(A0)>400)
  {
   myservo1.write(90);  
 myservo2.write(70);  
  }
}
