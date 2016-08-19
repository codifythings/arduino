/***************************************************************************
 * Sketch Name: IoT Sensors- DHT11 (Temperature & Humidity) Sensor
 * Description: This sketch illustrates how to read temperature and 
                humidity data from sensor
 * Created On:  January 15, 2016
 * Author:      Adeel Javed
 * Website:     http://codifythings.com
 **************************************************************************/

/***************************************************************************
 * External Libraries
 **************************************************************************/
 
#include <SPI.h>
#include <dht11.h>

/*****************************************************************************
 * Sensor Setup - Variables & Functions
 ****************************************************************************/

dht11 DHT11;

#define DHT11PIN 3 
 
float humidity = 0.0;
float tempC = 0.0;

void readSensorData()
{
  int chk = DHT11.read(DHT11PIN);

  Serial.print("[INFO] DHT11 Read: ");
  
  switch (chk)
  {
    case DHTLIB_OK: 
      Serial.println("OK"); 
  
      humidity = (float)DHT11.humidity;
      tempC = (float)DHT11.temperature;
      
      Serial.print("[INFO] Humidity (%): ");
      Serial.print(humidity, 2);
      Serial.print(" Temperature (*C): ");
      Serial.println(tempC, 2);      
      break;
    case DHTLIB_ERROR_CHECKSUM: 
      Serial.println("Checksum Error"); 
      break;
    case DHTLIB_ERROR_TIMEOUT: 
      Serial.println("Time Out Error"); 
      break;
    default: 
      Serial.println("Unknown Error"); 
      break;
  }
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
