#include <Wire.h>
#define SLAVE_ADDR 9

int cm = 0;
int speed = 0;
int x = 0;
int y = 0;
void setup()
{Serial.begin(9600);
   Wire.begin(SLAVE_ADDR);
 Wire.onReceive(receiveEvent);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
 Wire.onRequest(returnCm);
}

void returnCm(){
  cm = 0.01723 * readUltrasonicDistance(7, 8);
  Serial.print("Request");
  Wire.write(cm);
}
int rd = 0;
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}
void receiveEvent(int howMany){
  rd = Wire.read();
  y = rd/10;
  x = rd%10;
  Serial.print(x);
    Serial.print(",");
    Serial.println(y);
}
void car (){
  if (y == 0){
    speed = 0;
  }
  else if (y == 1){
    forward();
  }
  else if (y == 2){
    backwards();
  }
    if (x == 0){
    forward();
  }
  else if (x == 1){
    left();
  }
  else if (x == 2){
    right();
  }
}

 void forward(){
    digitalWrite(10,LOW);
    digitalWrite(9,HIGH);
   	digitalWrite(6,HIGH);
   	digitalWrite(5,LOW);    
   speed = 150;
  }
void backwards(){
   	digitalWrite(10,HIGH);
 	digitalWrite(9,LOW);
  	digitalWrite(6,LOW);
  	digitalWrite(5,HIGH);
  speed = 150;
 }
void left(){
  	digitalWrite(10,HIGH);
  	digitalWrite(9,LOW);
    digitalWrite(6,HIGH);
   	digitalWrite(5,LOW);
  speed = 150;
 }
void right(){
  	digitalWrite(10,LOW);
    digitalWrite(9,HIGH);
    digitalWrite(6,LOW);
  	digitalWrite(5,HIGH);
  speed = 150;
 }
void loop(){
  car();
  analogWrite(4,speed);
}
