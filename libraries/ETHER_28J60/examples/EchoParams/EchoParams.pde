#include "etherShield.h"
#include "ETHER_28J60.h"

int ledPin = 5;

static uint8_t mac[6] = {0x54,0x55,0x58,0x10,0x00,0x24}; 
static uint8_t ip[4] = {192,168,1,15};
static uint16_t port = 80; 

ETHER_28J60 ethernet;

void setup()
{ 
  ethernet.setup(mac, ip, port);
}

void loop()
{
  char* param;
  if (param = ethernet.serviceRequest())
  {
    ethernet.print("<H1>Arduino</H1>");
    ethernet.print("<H2>");
    ethernet.print(param);
    ethernet.print("</H2>");
    ethernet.respond();
  }
}

