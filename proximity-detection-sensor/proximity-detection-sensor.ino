/***************************************************************************
 * Sketch Name: IoT Sensors- Proximity Detection Sensor
 * Description: This sketch illustrates how to detect proximity from sensor
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

int calibrationTime = 30;        
#define TRIGPIN 2        // Pin to send trigger pulse
#define ECHOPIN 3        // Pin to receive echo pulse 

void calibrateSensor()
{
  //Give sensor some time to calibrate
  Serial.println("[INFO] Calibrating Sensor ");
  
  for(int i = 0; i < calibrationTime; i++)
  {
    Serial.print(".");
    delay(1000);
  }
  
  Serial.println("");
  Serial.println("[INFO] Calibration Complete");
  Serial.println("[INFO] Sensor Active");
  
  delay(50);
}

void readSensorData()
{
  // Generating a burst to check for objects
  digitalWrite(TRIGPIN, LOW); 
  delayMicroseconds(10); 
  digitalWrite(TRIGPIN, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TRIGPIN, LOW);
  
  // Distance Calculation
  float distance = pulseIn(ECHOPIN, HIGH); 
  
  Serial.println("[INFO] Object Distance: " + String(distance));
}

/***************************************************************************
 * Standard Arduino Functions - setup(), loop()
 **************************************************************************/

void setup() 
{ 
  // Initialize serial port  
  Serial.begin(9600); 
  
  // Set pin mode
  pinMode(ECHOPIN, INPUT); 
  pinMode(TRIGPIN, OUTPUT);

  // Calibrate sensor  
  calibrateSensor();       
}

void loop() 
{ 
  // Read sensor data
  readSensorData();

  // Delay
  delay(5000); 
}
