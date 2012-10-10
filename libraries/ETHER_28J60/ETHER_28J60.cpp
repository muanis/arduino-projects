/*
ETHER_28J60.cpp - Ethernet library
Copyright (c) 2010 Simon Monk.  All right reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "etherShield.h"
#include "ETHER_28J60.h"
//#include "WProgram.h" // Arduino 0.23
#include "Arduino.h" // Arduino 1.0 -- 2011 12 15 # Ben Schueler

/******************************************************************************
 * Definitions
 ******************************************************************************/
#define BUFFER_SIZE 500
#define STR_BUFFER_SIZE 32
static uint8_t buf[BUFFER_SIZE+1];
static char strbuf[STR_BUFFER_SIZE+1];
EtherShield es=EtherShield();
uint16_t plen;


/******************************************************************************
 * Constructors
 ******************************************************************************/

/******************************************************************************
 * User API
 ******************************************************************************/

void ETHER_28J60::setup(uint8_t macAddress[], uint8_t ipAddress[], uint16_t port)
{
	_port = port;
    es.ES_enc28j60Init(macAddress);
    es.ES_enc28j60clkout(2); // change clkout from 6.25MHz to 12.5MHz
    delay(10);
	es.ES_enc28j60PhyWrite(PHLCON,0x880);
	delay(500);
	es.ES_enc28j60PhyWrite(PHLCON,0x990);
	delay(500);
	es.ES_enc28j60PhyWrite(PHLCON,0x880);
	delay(500);
	es.ES_enc28j60PhyWrite(PHLCON,0x990);
	delay(500);
    es.ES_enc28j60PhyWrite(PHLCON,0x476);
	delay(100);
    es.ES_init_ip_arp_udp_tcp(macAddress, ipAddress, _port);
}


char* ETHER_28J60::serviceRequest()
{
	uint16_t dat_p;
	int8_t cmd;
	plen = es.ES_enc28j60PacketReceive(BUFFER_SIZE, buf);

	/*plen will ne unequal to zero if there is a valid packet (without crc error) */
	if(plen!=0)
	{
		// arp is broadcast if unknown but a host may also verify the mac address by sending it to a unicast address.
	    if (es.ES_eth_type_is_arp_and_my_ip(buf, plen))
		{
	      es.ES_make_arp_answer_from_request(buf);
	      return 0;
	    }
	    // check if ip packets are for us:
	    if (es.ES_eth_type_is_ip_and_my_ip(buf, plen) == 0)
	 	{
	      return 0;
	    }
	    if (buf[IP_PROTO_P]==IP_PROTO_ICMP_V && buf[ICMP_TYPE_P]==ICMP_TYPE_ECHOREQUEST_V)
		{
	      es.ES_make_echo_reply_from_request(buf, plen);
	      return 0;
	    }
	    // tcp port www start, compare only the lower byte
	    if (buf[IP_PROTO_P]==IP_PROTO_TCP_V&&buf[TCP_DST_PORT_H_P]==0&&buf[TCP_DST_PORT_L_P] == _port)
		{
	    	if (buf[TCP_FLAGS_P] & TCP_FLAGS_SYN_V)
			{
	         	es.ES_make_tcp_synack_from_syn(buf); // make_tcp_synack_from_syn does already send the syn,ack
	         	return 0;     
	      	}
	      	if (buf[TCP_FLAGS_P] & TCP_FLAGS_ACK_V)
			{
	        	es.ES_init_len_info(buf); // init some data structures
	        	dat_p=es.ES_get_tcp_data_pointer();
	        	if (dat_p==0)
				{ // we can possibly have no data, just ack:
	          		if (buf[TCP_FLAGS_P] & TCP_FLAGS_FIN_V)
					{
	            		es.ES_make_tcp_ack_from_any(buf);
	          		}
	          		return 0;
	        	}
	        	if (strncmp("GET ",(char *)&(buf[dat_p]),4)!=0)
				{
	          		// head, post and other methods for possible status codes see:
	            	// http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html
	            	plen=es.ES_fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n<h1>200 OK</h1>"));
					plen=es.ES_fill_tcp_data_p(buf,plen,PSTR("<h1>A</h1>"));		        	
					respond();
	        	}
	 			if (strncmp("/",(char *)&(buf[dat_p+4]),1)==0) // was "/ " and 2
				{
					// Copy the request action before we overwrite it with the response
					int i = 0;
					while (buf[dat_p+5+i] != ' ' && i < STR_BUFFER_SIZE)
					{
						strbuf[i] = buf[dat_p+5+i];
						i++;
					}
					strbuf[i] = '\0';
					plen=es.ES_fill_tcp_data_p(buf,0,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n"));		        	
					return (char*)strbuf;
	         	}	     
	      }
		}
	}
}


void ETHER_28J60::print(char* text)
{
	int j = 0;
  	while (text[j]) 
	{
    	buf[TCP_CHECKSUM_L_P+3+plen]=text[j++];
    	plen++;
  	}
}

void ETHER_28J60::print(int number)
{
  char tempString[9]; 
  itoa(number, tempString, 10);
  print(tempString);
}

void ETHER_28J60::respond()
{
	es.ES_make_tcp_ack_from_any(buf); // send ack for http get
	es.ES_make_tcp_ack_with_data(buf,plen); // send data
}
