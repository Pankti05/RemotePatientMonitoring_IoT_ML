#include "UbidotsESPMQTT.h"
#include <SoftwareSerial.h>

SoftwareSerial myserial(2,3);

#Defaults
#define TOKEN "BBFF-3xOjJPz8KVc4u6LUB2USla8UnioVbW" // Your Ubidots TOKEN
#define WIFINAME "BGM" //Your SSID
#define WIFIPASS "Mechanical" // Your Wifi Pass

Ubidots client(TOKEN);

/****************************************
 * Auxiliar Functions
 ****************************************/
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

/****************************************
 * Setup Functions
 ****************************************/

void setup() {
  // put your setup code here, to run once:
  //client.ubidotsSetBroker("business.api.ubidots.com"); // Sets the broker properly for the business account
  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  Serial.begin(115200);
  Serial.print("Its ESP8266 here");
  myserial.begin(115200);
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  }

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
      client.reconnect();
      }
  String astring=myserial.readString();
  //Serial.print(astring);
 // int valueint= astring.toInt();
  //int valuefloat= astring.toFloat();

  /*
  Serial.println("--------------STRING----------------");
  Serial.println(astring);
  Serial.println("-------------INT-----------------");
  Serial.println(valueint);
  Serial.println("-------------FLOAT-----------------");
  Serial.println(valuefloat);
  Serial.write("--------------STRING----------------");
  //Serial.write(astring);
  Serial.write("-------------INT-----------------");
  Serial.write(valueint);
  Serial.write("-------------FLOAT-----------------");
  Serial.write(valuefloat);
  */
  int value1= Integer.parseInt(astring);
  
  //float value1 = analogRead(0);
  
  //float value1 = random(1000);
  //float value2 = analogRead(2)
  
  client.add("ecg", value1);
  //client.add("status", value2);
  client.ubidotsPublish("ECG_GRAPH");
  client.loop();
}
