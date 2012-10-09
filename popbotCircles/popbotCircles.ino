
//void setup() {
//  pinMode(3,OUTPUT);  // Motor A1
//  pinMode(5,OUTPUT);  // Motor A2
//  pinMode(6,OUTPUT);  // Motor B2
//  pinMode(9,OUTPUT);  // Motor B1
//  pinMode(2,INPUT);   // Switch Left
//  pinMode(4,INPUT);   // Switch Right
//}

void forward(int lSpeed, int rSpeed) {
  analogWrite(3,lSpeed);
  digitalWrite(5,LOW);
  analogWrite(6,rSpeed);
  digitalWrite(9,LOW);
}

void motorStop() {
  digitalWrite(3,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(9,LOW);
}

void backward() {
  digitalWrite(3,LOW);
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(9,HIGH);
}  

//void loop() {
//  forward(50,100);
//  if(digitalRead(4)==0) {
//    motorStop();
//    while(1);
//  }
////  delay(1000);
////  Backward();
////  delay(1000);
//}
