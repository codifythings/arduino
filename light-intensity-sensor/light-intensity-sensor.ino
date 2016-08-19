/***************************************************************************
 * Sketch Name: IoT Sensors- Light Intensity Sensor
 * Description: This sketch illustrates how to read light intensity data
                from sensor
 * Created On:  January 15, 2016
 * Author:      Adeel Javed
 * Website:     http://codifythings.com
 **************************************************************************/

/***************************************************************************
 * External Libraries
 **************************************************************************/
 
#include <SPI.h>

/*****************************************************************************
 * Sensor Setup - Variables & Functions
 ****************************************************************************/

int lightValue;
 
void readSensorData()
{
  //Read Light Sensor Value  
  lightValue = analogRead(A0);   
  
  Serial.print("[INFO] Light Sensor Reading: "); 
  Serial.println(lightValue);      
} 

/***************************************************************************
 * Standard Arduino Functions - setup(), loop()
 **************************************************************************/

void setup() 
{
  // Initialize serial port
  Serial.begin(9600);
}
 
void loop() 
{    
  readSensorData();
  
  delay(5000);
}
