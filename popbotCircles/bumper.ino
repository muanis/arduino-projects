
void setup() {
  pinMode(3,OUTPUT);  // Motor A1
  pinMode(5,OUTPUT);  // Motor A2
  pinMode(6,OUTPUT);  // Motor B2
  pinMode(9,OUTPUT);  // Motor B1
  
  pinMode(15,INPUT);  // Left switch
  pinMode(17,INPUT);  // Right switch
}

void loop() {
  forward(150);
  if(digitalRead(15)==0) {
    backward(150);delay(500);
    spinRight(200);delay(400);
  }
  if(digitalRead(17)==0) {
    backward(150);delay(400);
    spinLeft(200);delay(400);
  }
}

/*** functions ***/

void forward(int speed) {
  analogWrite(3,speed);
  digitalWrite(5,LOW);
  analogWrite(6,speed);
  digitalWrite(9,LOW);
}

void backward(int speed) {
  analogWrite(5,speed);
  digitalWrite(3,LOW);
  analogWrite(9,speed);
  digitalWrite(6,LOW);
}

void spinLeft(int speed) {
  analogWrite(5,speed);
  digitalWrite(3,LOW);
  analogWrite(6,speed);
  digitalWrite(9,LOW);
}

void spinRight(int speed) {
  analogWrite(3,speed);
  digitalWrite(5,LOW);
  analogWrite(9,speed);
  digitalWrite(6,LOW);
}

