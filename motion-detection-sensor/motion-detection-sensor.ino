/***************************************************************************
 * Sketch Name: IoT Sensors- Motion Detection Sensor
 * Description: This sketch illustrates how to detect motion from sensor
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
long unsigned int lowIn;         
long unsigned int pause = 5000;  
boolean lockLow = true;
boolean takeLowTime;  
int pirPin = 3;

void calibrateSensor()
{
  pinMode(pirPin, INPUT);
  digitalWrite(pirPin, LOW);

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
  if(digitalRead(pirPin) == HIGH)
  {
    if(lockLow)
    {     
      lockLow = false;            
      Serial.print("[INFO] Activty Detected @ ");
      Serial.print(millis()/1000);
      Serial.print(" secs"); 
      Serial.println("");        
       
      delay(50);
    }         
     
    takeLowTime = true;
  }
  
  if(digitalRead(pirPin) == LOW)
  {       
    if(takeLowTime)
    {
      lowIn = millis();
      takeLowTime = false;
    }
      
    if(!lockLow && millis() - lowIn > pause)
    {  
      lockLow = true;                        

      Serial.print("[INFO] Activty Ended @ ");      //output
      Serial.print((millis() - pause)/1000);
      Serial.print(" secs"); 
      Serial.println("");
        
      delay(50);
    }
  }   
}

/***************************************************************************
 * Standard Arduino Functions - setup(), loop()
 **************************************************************************/

void setup() 
{
  // Initialize serial port
  Serial.begin(9600);
  
  // Calibrate motion sensor  
  calibrateSensor();  
}
 
void loop() 
{    
  readSensorData();
}
