/***************************************************************************
 * Sketch Name: IBM Bluemix IoTF - MQT Data Publish
 * Description: This sketch illustrates how Arduino can publish events to
                IBM Bluemix IoTF
 * Created On:  December 15, 2015
 * Author:      Adeel Javed
 * Website:     http://codifythings.com
 **************************************************************************/

/***************************************************************************
 * External Libraries
 **************************************************************************/
 
#include <SPI.h>
#include <WiFi.h>
#include <dht11.h>
#include <PubSubClient.h>

/***************************************************************************
 * Internet Connectivity Setup - Variables & Functions
 **************************************************************************/
 
char ssid[] = "HOME-9252";        // Network SSID (name) 
char pass[] = "E37DCD7F7DCDF7AC"; // Network Password (use for WPA, 
                                  // or use as key for WEP)

int keyIndex = 0;                 // Network Key Index Number 
                                  // (needed only for WEP)
 
int status = WL_IDLE_STATUS;

WiFiClient client;

void connectToInternet()
{
  status = WiFi.status();
  
  // Check for the presence of the shield
  if (status == WL_NO_SHIELD) 
  {
    Serial.println("[ERROR] WiFi Shield Not Present");
    // Do nothing
    while (true);
  }

  // Attempt to connect to WPA/WPA2 Wifi network
  while ( status != WL_CONNECTED) 
  {
    Serial.print("[INFO] Attempting Connection - WPA SSID: ");
    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);
  }

  // Connection successful
  Serial.print("[INFO] Connection Successful");
  Serial.print("");  
  printConnectionInformation();
  Serial.println("-----------------------------------------------");
  Serial.println("");  
}

void printConnectionInformation() 
{
  // Print Network SSID
  Serial.print("[INFO] SSID: ");
  Serial.println(WiFi.SSID());

  // Print Router's MAC address
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("[INFO] BSSID: ");
  Serial.print(bssid[5], HEX);
  Serial.print(":");
  Serial.print(bssid[4], HEX);
  Serial.print(":");
  Serial.print(bssid[3], HEX);
  Serial.print(":");
  Serial.print(bssid[2], HEX);
  Serial.print(":");
  Serial.print(bssid[1], HEX);
  Serial.print(":");
  Serial.println(bssid[0], HEX);

  // Print received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("[INFO] Signal Strength (RSSI): ");
  Serial.println(rssi);

  // Print encryption type
  byte encryption = WiFi.encryptionType();
  Serial.print("[INFO] Encryption Type: ");
  Serial.println(encryption, HEX);

  // Print WiFi Shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("[INFO] IP Address: ");
  Serial.println(ip);

  // Print MAC address
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("[INFO] MAC Address: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);
}

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
 * Data Publish - Variables & Functions
 **************************************************************************/

// IP address of the IBM MQTT server
char server[] = "3znyoi.messaging.internetofthings.ibmcloud.com";
int port = 1883;
char topic[] = "iot-2/evt/status/fmt/json";
String clientName = "d:3znyoi:WeatherDT:WeatherD";
char token[] = "*QYGI_FpT6!&NrKzOF";

PubSubClient pubSubClient(server, port, 0, client);

void publishData()
{   
  // Connect MQTT Broker
  Serial.println("[INFO] Connecting to MQTT Broker");
  
  char clientStr[60]; 
  clientName.toCharArray(clientStr,60);
  
  if (pubSubClient.connect(clientStr, "use-token-auth", token)) 
  {
    Serial.println("[INFO] Connection to MQTT Broker Successfull");
  }
  else
  {
    Serial.println("[INFO] Connection to MQTT Broker Failed");
  }
  
  // Publish to MQTT Topic
  if (pubSubClient.connected()) 
  { 
    //Read sensor data
    readSensorData();
      
    Serial.println("[INFO] Publishing to IBM IoTF");
    String data = "{\"d\": {\"humidity\": \"" + String(humidity) + "\", \"tempC\": \"" + String(tempC) + "\"}}";

    char jsonStr[50];
    data.toCharArray(jsonStr,50);

    Serial.print("[INFO] JSON Data: ");    
    Serial.println(jsonStr);    
    
    char topicStr[33];  
    String topicName = topic;
    topicName.toCharArray(topicStr,33);
    
    if (pubSubClient.publish(topicStr,jsonStr))
    {
      Serial.println("[INFO] Data Published Successfully");
    }  
    else
    {
      Serial.println("[INFO] Failed to Publish Data");
    }
    
    Serial.println("[INFO] Disconnecting Server");
    pubSubClient.disconnect();
  }

  Serial.println("[INFO] Publish to MQTT Broker Complete");
  Serial.println("-----------------------------------------------");
  
  pubSubClient.loop();
}

/***************************************************************************
 * Standard Arduino Functions - setup(), loop()
 **************************************************************************/

void setup() 
{
  // Initialize serial port
  Serial.begin(9600);

  // Connect Arduino to internet
  connectToInternet();
}
 
void loop() 
{    
  //readSensorData();
  publishData();    
  
  delay(5000);
}
