/***************************************************************************
 * Sketch Name: IoT Sensors- Flame Sensor
 * Description: This sketch illustrates how to read flame sensor data
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

int FLAME_SENSOR_PIN = A0;
float flameSensorValue = 0.0;
 
void readSensorData()
{
  //Read Mositure Sensor Value
  flameSensorValue = analogRead(FLAME_SENSOR_PIN);
 
  //Display Readings
  Serial.print("[INFO] Flame Sensor Reading: ");
  Serial.println(flameSensorValue);
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
  
  delay(1000);
}
