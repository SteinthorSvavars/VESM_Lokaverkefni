#include <LiquidCrystal.h>
#include <Wire.h>
#define SLAVE_ADDR 9
int send = 0;
int x = 0;
int y = 0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int Speed=0;void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(9,INPUT); 
  pinMode(10,INPUT);  
  pinMode(7,INPUT); 
  pinMode(8,INPUT); 
  lcd.begin(16, 2);
}
void keys(){
  if (digitalRead(8)==HIGH && digitalRead(7)==HIGH){
  Serial.print("Nothing");
    x = 0;
  }
  else if (digitalRead(8)==HIGH){
  		Serial.print("Left");
    x = 1;
  }
  else if (digitalRead(7)==HIGH){
  		Serial.print("Rigth");
    x = 2;
  }
  else {
    Serial.print("Nothing");
    x = 0;
  }
  
  if (digitalRead(10)==HIGH && digitalRead(9)==HIGH){
  Serial.print("Nothing");
    y = 0;
  }
  else if (digitalRead(10)==HIGH){
  		Serial.print("Forwards");
    y = 1;
  }
  else if (digitalRead(9)==HIGH){
  		Serial.print("Backwards");
    y = 2;
  }
  else {
    Serial.print("Nothing");
    y = 0;
  }
  y =  y*10;
  send = y+x;
}
void Write(){
  lcd.clear();
  Wire.requestFrom(SLAVE_ADDR,1);
  int Cm = Wire.read();
  lcd.print("Distance to wall");
  lcd.setCursor(0, 1);
  lcd.print(Cm);
  lcd.print(" CM");
  delay(50);
  
}
int b = 0;
void loop() {
  keys();
  Write();
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(send);
  Wire.endTransmission();
}
