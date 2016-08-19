/***************************************************************************
 * Sketch Name: IoT Sensors- Location Detection Sensor (GPS)
 * Description: This sketch illustrates how to detect location from a GPS
 * Created On:  January 15, 2016
 * Author:      Adeel Javed
 * Website:     http://codifythings.com
 **************************************************************************/

/***************************************************************************
 * External Libraries
 **************************************************************************/
 
#include <SPI.h>
#include <TinyGPS.h>
#include <SoftwareSerial.h>

/*****************************************************************************
 * Sensor Setup - Variables & Functions
 ****************************************************************************/

TinyGPS gps;
SoftwareSerial ss(2, 3); // GPS TX = Arduino D2, GPS RX = Arduino D3

static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

void getGPSCoordinates()
{
  float latitude;
  float longitude;
  unsigned long age = 0;
   
  gps.f_get_position(&latitude, &longitude, &age);
  
  // Transmit sensor data  
  if(latitude != TinyGPS::GPS_INVALID_F_ANGLE && 
                               longitude != TinyGPS::GPS_INVALID_F_ANGLE)
  {
    Serial.print("[INFO] Latitude: " + String(latitude));
    Serial.println(", Longitude: " + String(longitude));    
  }
  else
  {
    Serial.println("[INFO] Searching for Satellite");
  }
  
  smartdelay(10000);
}

/***************************************************************************
 * Standard Arduino Functions - setup(), loop()
 **************************************************************************/

void setup()
{  
  // Initialize serial port  
  Serial.begin(115200);
  
  // Initialize serial port for GPS data
  ss.begin(9600);

}

void loop()
{
  // Get GPS Coordinates
  getGPSCoordinates();
}
