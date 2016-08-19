/***************************************************************************
 * Sketch Name: IoT Sensors- Capacitive Touch Sensor
 * Description: This sketch illustrates how to read capacitive touch sensor
                data
 * Created On:  February 01, 2016
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

int CAPACITIVE_SENSOR_PIN = 3;
int capacitiveSensorValue = 0;
 
void readSensorData()
{
  //Read Sensor Value
  capacitiveSensorValue = digitalRead(CAPACITIVE_SENSOR_PIN);
 
  //Display Readings
  Serial.print("[INFO] Capacitive Touch Sensor Reading: ");
  Serial.println(capacitiveSensorValue);
}

/***************************************************************************
 * Standard Arduino Functions - setup(), loop()
 **************************************************************************/

void setup() 
{
  pinMode(CAPACITIVE_SENSOR_PIN, INPUT);
  
  // Initialize serial port
  Serial.begin(9600);
}
 
void loop() 
{    
  readSensorData();
  
  delay(1000);
}
