// A simple web server that always just says "Hello World"

#include "etherShield.h"
#include "ETHER_28J60.h"

static uint8_t mac[6] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24};   // this just needs to be unique for your network, 
                                                                // so unless you have more than one of these boards
                                                                // connected, you should be fine with this value.
                                                           
static uint8_t ip[4] = {192, 168, 1, 15};                       // the IP address for your board. Check your home hub
                                                                // to find an IP address not in use and pick that
                                                                // this or 10.0.0.15 are likely formats for an address
                                                                // that will work.

static uint16_t port = 80;                                      // Use port 80 - the standard for HTTP

ETHER_28J60 ethernet;

void setup()
{ 
  ethernet.setup(mac, ip, port);
}

void loop()
{
  if (ethernet.serviceRequest())
  {
    ethernet.print("<H1>Hello World</H1>");
    ethernet.respond();
  }
  delay(100);
}

