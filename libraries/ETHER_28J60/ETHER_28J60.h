/*
  ETHER_28J60.h - Ethernet library
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

#ifndef ETHER_28J60_h
#define ETHER_28J60_h

#include <inttypes.h>

class ETHER_28J60
{
  public:
    void setup(uint8_t macAddress[], uint8_t ipAddress[], uint16_t port);
	char* serviceRequest();		// returns a char* containing the requestString
								//        or NULL if no request to service
	void print(char* text); 	// append the text to the response
	void print(int value);  	// append the number to the response
	void respond(); 			// write the final response
  private:
	uint16_t _port;

};

#endif

