
#include <SoftwareSerial.h>

#define rxPin 17
#define txPin 16

SoftwareSerial lcd = SoftwareSerial(rxPin,txPin);
int oldI,i=1500,j=0,k;

void setup() {
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(2,INPUT);
  pinMode(4,INPUT);
  pinMode(txPin,OUTPUT);
  lcd.begin(9600);
  delay(1000);
  i=1560;
  
//  digitalWrite(txPin,HIGH);
//  delay(1000);
//  pinMode(rxPin,INPUT);
}

void loop() {
  if(digitalRead(2)==0) {
    if(i<2500) {
      i+=20;
    } else {
      beep();
    }
  }
  if(digitalRead(4)==0) {
    if(i>400) {
      i-=20;
    } else {
      beep();
    }
  }
  
  if(i!=oldI) {
    lcdCmd(0x01);
    lcd.print(i,DEC);
    oldI = i;
  }
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  delayMicroseconds(i);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  delay(20);
}

void lcdCmd( int command ) {
  lcd.write(0xFE);
  lcd.write(command);
  delay(10);
}


void beep() {
  int i;
  for(i=0;i<600;i++) {
    digitalWrite(14,HIGH);
    delayMicroseconds(150);
    digitalWrite(14,LOW);
    delayMicroseconds(150);
  }
}

