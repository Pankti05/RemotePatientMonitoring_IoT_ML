#include <SoftwareSerial.h>
#define RX 2
#define TX 3
String AP = "BGM";       // CHANGE ME
String PASS = "Mechanical"; // CHANGE ME
String API = "CUW7NAP5OZZHFL1G";   // CHANGE ME
String HOST = "api.thingspeak.com";
String PORT = "80";
String field = "field1";
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
int valSensor = 1;
SoftwareSerial esp82661(RX,TX); 
 
  
void setup() {
  Serial.begin(9600);
  pinMode(10,INPUT);
  pinMode(11,INPUT);
  esp82661.begin(115200);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
}
void loop() {
 valSensor = getSensorData();
 String getData = "GET /update?api_key="+ API +"&"+ field +"="+String(valSensor);
sendCommand("AT+CIPMUX=1",5,"OK");
 sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
 sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
 esp82661.println(getData);delay(1500);countTrueCommand++;
 sendCommand("AT+CIPCLOSE=0",5,"OK");
}
int getSensorData(){
  //return random(1000); // Replace with 
  if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
    Serial.println('!');
    return -1;
}
else {
  Serial.println("------------------------");
  Serial.println(analogRead(A0));
  Serial.println("------------------------");
  return analogRead(A0);
  delay(2);
}
}
void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp82661.println(command);//at+cipsend
    if(esp82661.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }
