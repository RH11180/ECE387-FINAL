#include <XBee.h> //Xbee library

XBee xbee = XBee();

uint8_t payload[] = { '3', '8', '7'};//send a payload to teh xbee receiver
//The content of the payload is not important becasue we only need to read the signal strength 

Tx16Request tx = Tx16Request(0x1387, payload, sizeof(payload));//the MY address of the receiver is 1387

void setup()
{
  
    xbee.begin(9600);
    xbee.setSerial(Serial);
}

void loop()
{
 
      
    xbee.send( tx ); //send the payload. 
    delay(50);
}
