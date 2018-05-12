#include <XBee.h>
#define trig1 2 
#define echo1 3 
#define trig2 4 
#define echo2 5 
int cm1; //distance at cm1
int cm;
float temp1; //   
int cm2; //distance at cm1
int cm3; //distance at cm1
int cm4; //distance at cm1
float temp2; //   
//const int aRead = A0; 
//int value; 
int ledLeft=10;
int ledRight=12;
int ledAlarm=7;
long xbeeDistance=0;
long currentDistance=0;
long lastDistance=0;
long delta=0;
XBee xbee = XBee();

Rx16Response rx16 = Rx16Response();

void setup()
{
    pinMode(trig1, OUTPUT);  
    pinMode(echo1, INPUT);
    pinMode(trig2, OUTPUT);  
    pinMode(echo2, INPUT);   
    pinMode(ledAlarm,OUTPUT);
    pinMode(ledLeft,OUTPUT);
    pinMode(ledRight,OUTPUT);
    xbee.begin(9600);
    Serial.begin(9600);
}

void loop()
{
    xbee.readPacket(100);
    //read API package
    if (xbee.getResponse().isAvailable())
    {
        if (xbee.getResponse().getApiId() == RX_16_RESPONSE)
        {
            xbee.getResponse().getRx16Response(rx16);
            xbeeDistance=rx16.getRssi();
            //get RSSI value 
            Serial.print("wireless distance is ");//print the RSSI value for debugging 
            Serial.println(xbeeDistance);//the RSSI value is inverse proportinal to the distance
        }      
    }   
    if (xbeeDistance>100) //if the suitcase is 5 meters far from the Xbee sender the light will go on
        {
          digitalWrite(ledAlarm, HIGH);
          }
       
  //trig1ger the distance mesurement 
  digitalWrite(trig1, LOW); // send low to trig1
  delayMicroseconds(2);    //wait more than 10us aka 2 ms
  digitalWrite(trig1,HIGH); //send high to trig1 
  delayMicroseconds(10);    //wait 10 ms
  digitalWrite(trig1, LOW); //send low and end trig1ger
  temp1 = float(pulseIn(echo1, HIGH)); //save the time of echo1
  //transfer  time to distance
  cm1 = (temp1 * 17 )/1000; 
  
  //second Ultrasonic
  digitalWrite(trig2, LOW); // send low to trig1
  delayMicroseconds(2);    //wait more than 10us aka 2 ms
  digitalWrite(trig2,HIGH); //send high to trig1 
  delayMicroseconds(10);    //wait 10 ms
  digitalWrite(trig2, LOW); //send low and end trig1ger
  temp2 = float(pulseIn(echo2, HIGH)); //save the time of echo1
  //transfer  time to distance
  cm2 = (temp2 * 17 )/1000; 
//using two ultrasonic chips to get the more accurate value
if (cm1>cm2)
{
  cm3=cm2;}
  else
  {cm3=cm1;}
cm4=cm1-cm2;
if (abs(cm4)<10)
{
  cm=cm1;
  }
  else
  {cm=cm3;}
  
  Serial.print("The distance is");
  Serial.println(cm);
      
      
       if (cm > 30 && xbeeDistance>50)
     // if (cm>30)
   {
    digitalWrite(ledLeft, HIGH);
    digitalWrite(ledRight, HIGH);
    //delay(1000);
    }
    else
    {
      digitalWrite(ledLeft, LOW);
      digitalWrite(ledRight,LOW);
      //delay(1000);
      }  
}
