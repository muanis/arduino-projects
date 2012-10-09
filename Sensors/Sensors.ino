
#include <SoftwareSerial.h>

#define rxPin 17
#define txPin 16

SoftwareSerial lcd = SoftwareSerial(rxPin,txPin);

int leftSensor;
int rightSensor;

void setup() {
  digitalWrite(txPin,HIGH);
  pinMode(txPin,OUTPUT);
  lcd.begin(9600);
  delay(1000);
}

void lcdCmd( int command ) {
  lcd.write(0xFE);
  lcd.write(command);
  delay(10);
}

void loop() {
  leftSensor = analogRead(7);
  rightSensor = analogRead(6);
  lcdCmd(0x80);
  lcd.print("L Sensor=       ");
  lcdCmd(0x8a);
  lcd.print(leftSensor,DEC);
  
  lcdCmd(0xC0);
  lcd.print("R Sensor=       ");
  lcdCmd(0xCA);
  lcd.print(rightSensor,DEC);
  
  delay(200);
}
