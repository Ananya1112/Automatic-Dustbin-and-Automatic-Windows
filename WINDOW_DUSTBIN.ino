#include <Servo.h>
 Servo servo1;
 Servo servo2;     
 int sensor_pin = A0;
 int output_value ;
 int trig1 = 2;
 int echo1 = 3;
 long duration, dist, average;
 long aver[3];
 int  trig2 = 12;
 int echo2 =  13;
 int Buzzer = 8; // Connect buzzer pin to 8
 int duration2, distance;

 
 void measure() 
 {
   digitalWrite(trig1, LOW);
   delayMicroseconds(5);
   digitalWrite(trig1, HIGH);
   delayMicroseconds(15);
   digitalWrite(trig1, LOW);
   pinMode(echo1, INPUT);
   duration = pulseIn(echo1, HIGH);
   dist = (duration/2) / 29.1; //obtain distance
 }

 void measure2() 
 {
   digitalWrite(trig2, LOW);
   delayMicroseconds(5);
   digitalWrite(trig2, HIGH);
   delayMicroseconds(15);
   digitalWrite(trig2, LOW);
   pinMode(echo2, INPUT);
   duration2 = pulseIn(echo1, HIGH);
   dist = (duration2/2) / 29.1; //obtain distance
 }
 

void setup() 
{
  Serial.begin(9600);
  servo1.attach(9);
  servo2.attach(10); 
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT); 
  pinMode(echo2, INPUT);
  pinMode(Buzzer, OUTPUT);
  Serial.println("Reading From the Sensor ...");
  delay(1000);  
  servo2.detach();
} 

void loop(){

 for (int i=0;i<=2;i++) //average distance
  { 
  measure();
  aver[i]=dist;
  delay(10); //delay between measurements
  }
  dist=(aver[0]+aver[1]+aver[2])/3;
  if ( dist<50) {
  servo2.attach(10);//Change distance as per your need
  delay(1);
  servo2.write(0);
  delay(3000);
  servo2.write(150);
  delay(1000);
  servo2.detach();
  Serial.write(dist); 
  }

   measure2();
   if (distance >= 200 || distance <= 0) 
   {
     digitalWrite(Buzzer,LOW);
   }
  else
  {
     Serial.println("object detected \n");
     Serial.print("distance= ");              
     Serial.print(distance);        //prints the distance if it is between the range 0 to 200
     tone(Buzzer,400); 
  }// play tone of 400Hz for 500 ms
 
  
  output_value= analogRead(sensor_pin);
  output_value = map(output_value,550,0,0,100);
  Serial.print(output_value);
  Serial.println("%");
  

  if( output_value > -30)
  {
    servo1.write(180);
  }
  else
  {
    servo1.write(0);
  }
}
