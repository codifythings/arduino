/***************************************************************************
 * Sketch Name: Temperature Monitoring System
 * Description: This sketch illustrates how to publish temperature data to
                Carriots IoT platform
 * Created On:  June 29, 2016
 * Author:      Adeel Javed
 * Website:     http://codifythings.com
 **************************************************************************/

/***************************************************************************
 * External Libraries
 **************************************************************************/

#include <Process.h>
#include <YunClient.h>
#include <dht11.h>

/***************************************************************************
 * Internet Connectivity Setup - Variables & Functions
 **************************************************************************/

// Yun client already connected to the internet
YunClient client;

void printConnectionInformation() 
{  
  // Initialize a new process
  Process wifiCheck;

  // Run Command
  wifiCheck.runShellCommand("/usr/bin/pretty-wifi-info.lua");

  // Print Connection Information  
  while (wifiCheck.available() > 0) 
  {
    char c = wifiCheck.read();
    Serial.print(c);
  }

  Serial.println("-----------------------------------------------");
  Serial.println("");
}

/*****************************************************************************
 * Sensor Setup - Variables & Functions
 ****************************************************************************/

dht11 DHT11;

#define DHT11PIN 3 
 
float tempC = 0.0;

void readSensorData()
{
  int chk = DHT11.read(DHT11PIN);

  Serial.print("[INFO] DHT11 Read: ");
  
  switch (chk)
  {
    case DHTLIB_OK: 
      Serial.println("OK"); 
  
      tempC = (float)DHT11.temperature;
      
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
 * Data Publish - Variables & Functions
 **************************************************************************/
 
#define APIKEY "6d8b4a2581ac5179ef9645b43b4642c9be9da14fecbc722fce82eaf230a81b52" // TO BE REPLACED with your Carriots APIKEY
#define DEVICE "temperatureDevice1@codifythings.codifythings" // TO BE REPLACED with your Device's ID developer

// Set up net client info
const unsigned long postingInterval = 10000;  //delay between updates to Carriots
unsigned long lastRequest = 0;      // when you last made a request
String dataString = ""; 
 
void transmitSensorData() 
{
  // Form the string for the APIKEY header parameter
  String apiString = "carriots.apikey: ";
  apiString += APIKEY;

  // Convert the readings to a String to send it
  dataString = "{\"protocol\":\"v1\",\"checksum\":\"\",\"device\":\"";
  dataString += DEVICE;
  dataString += "\",\"at\":\"now\",\"data\":{\"temperature\":";
  dataString += tempC;
  dataString += "}}";
  Serial.println("[INFO] Data String:" + dataString);

  // Send the HTTP POST request  
  Serial.println("[INFO] HTTP GET Started");
  
  Process carriots;
  carriots.begin("curl");
  carriots.addParameter("-k");
  carriots.addParameter("--request");
  carriots.addParameter("POST");
  carriots.addParameter("--data");
  carriots.addParameter(dataString);
  carriots.addParameter("--header");
  carriots.addParameter(apiString);
  carriots.addParameter("https://api.carriots.com/streams/");
  carriots.run();
  
  Serial.println("[INFO] HTTP GET Completed");

  // If there's incoming data from the net connection, print it on Serial
  while (carriots.available() > 0) 
  {
    char c = carriots.read();
    Serial.write(c);
  }
}

/***************************************************************************
 * Standard Arduino Functions - setup(), loop()
 **************************************************************************/

void setup() 
{
  // Initialize serial port
  Serial.begin(9600);
  
  // Do nothing until serial monitor is opened
  while (!Serial);     

  // Contact the Linux processor
  Bridge.begin();  
  
  // Print connection information
  printConnectionInformation(); 
  
  lastRequest = millis();
}

void loop() 
{  
  // Get a timestamp to calculate reading and sending intervals
  long now = millis();

  // If the sending interval has passed since last connection, 
  // then connect again and send data
  if (now - lastRequest >= postingInterval) 
  {
    // Read sensor data
    readSensorData();

    // Transmit sensor data
    transmitSensorData();  
  
    lastRequest = now;
  }  
  
  // Delay
  delay(1000);    
}
