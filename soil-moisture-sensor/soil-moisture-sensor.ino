/***************************************************************************
 * Sketch Name: IoT Sensors- Soil Moisture Sensor
 * Description: This sketch illustrates how to read soil moisture data
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

int MOISTURE_SENSOR_PIN = A0;
float moistureSensorValue = 0.0;
 
void readSensorData()
{
  //Read Mositure Sensor Value
  moistureSensorValue = analogRead(MOISTURE_SENSOR_PIN);
 
  //Display Readings
  Serial.print("[INFO] Moisture Sensor Reading: ");
  Serial.println(moistureSensorValue);
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
