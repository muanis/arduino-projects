#include <EtherCard.h>

static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x32,0x31 };
byte Ethernet::buffer[700];
static uint32_t timer;

static byte hisip[] = { 192,168,16,103 };

int sensorPin = A1;
int sensorPin2 = A2;
int sensorPin3 = A3;
int sensorPin4 = A4;
int sensorPin5 = A5;
int sensorValue = 0;
float tempC= 0.0;


void setup () {
  Serial.begin(57600);
  Serial.println(F("\n[simple_sensor]"));

  Serial.print("MAC: ");
  for (byte i = 0; i < 6; ++i) {
    Serial.print(mymac[i], HEX);
    if (i < 5)
      Serial.print(':');
  }
  Serial.println();
  
  // Ethernet Shield v.1.0 by SeeedStudio on top of Duemilanove
//  if (ether.begin(sizeof Ethernet::buffer, mymac, 10) == 0) 
//    Serial.println(F("Failed to access Ethernet controller"));
//
//  Serial.println(F("[Setting up DHCP]"));
//  if (!ether.dhcpSetup())
//    Serial.println(F("DHCP failed"));
//  
//  ether.printIp("My IP: ", ether.myip);
//  ether.printIp("Netmask: ", ether.netmask);
//  ether.printIp("GW IP: ", ether.gwip);
//  ether.printIp("DNS IP: ", ether.dnsip);
//  
//  ether.copyIp(ether.hisip, hisip);
//  ether.printIp("DST IP: ", ether.hisip);
//  ether.hisport = 8888;
  
//  sendToServer();
}

  static byte session;
  Stash stash;

static void sendToServer (int temp) {
  
  
  Serial.print("Sending temperature to server ... ");
  Serial.print(temp);
//  byte sd = stash.create();
//  stash.print("t1=");
//  stash.print(temp);
//  stash.save();
//  int stash_size = stash.size();

  // Compose the http POST request, taking the headers below and appending
  // previously created stash in the sd holder.
//  Stash::prepare(PSTR("POST /register-temp HTTP/1.0" "\r\n"
//    "Content-Length: $D" "\r\n"
//    "Content-Type: application/x-www-form-urlencoded" "\r\n"
//    "\r\n"
//    "$H"),
//  stash_size, sd);



  // send the packet - this also releases all stash buffers once done
  // Save the session ID so we can watch for it in the main loop.
//  session = ether.tcpSend();
  Serial.println(" sent");
}

void loop () {
//  ether.packetLoop(ether.packetReceive());

  if (millis() > timer) {
    timer = millis() + 2000;
    sensorValue = analogRead(sensorPin);  
    tempC = (((float)sensorValue * (5000.0/1024.0)) - 500)/10.0;
    Serial.print("1: ");
    Serial.print(tempC);  
    delay(3);

    sensorValue = analogRead(sensorPin2);  
    tempC = (((float)sensorValue * (5000.0/1024.0)) - 500)/10.0;
    Serial.print("   2: ");
    Serial.print(tempC);  
    delay(3);
  
    sensorValue = analogRead(sensorPin3);  
    tempC = (((float)sensorValue * (5000.0/1024.0)) - 500)/10.0;
    Serial.print("   3: ");
    Serial.print(tempC);  
    delay(3);
  
    sensorValue = analogRead(sensorPin4);  
    tempC = (((float)sensorValue * (5000.0/1024.0)) - 500)/10.0;
    Serial.print("   4: ");
    Serial.print(tempC);  
    delay(3);
  
    sensorValue = analogRead(sensorPin5);  
    tempC = (((float)sensorValue * (5000.0/1024.0)) - 500)/10.0;
    Serial.print("   5: ");
    Serial.println(tempC);  
  
    //sendToServer(sensorValue);
    
  }
    
  
//  const char* reply = ether.tcpReply(session);
//  if (reply != 0) {
//    Serial.println("Got a response!");
//    Serial.println(reply);
//  }  
}

static void my_callback (byte status, word off, word len) {
  Serial.println(">>>");
  Ethernet::buffer[off+300] = 0;
  Serial.print((const char*) Ethernet::buffer + off);
  Serial.println("...");
}


