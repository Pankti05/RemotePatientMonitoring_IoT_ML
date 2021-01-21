#include <SoftwareSerial.h>
#define RX 3
#define TX 2
void setup() {
  // initialize the serial communication:
  Serial.begin(115200);
  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO -

}

void loop() {

 
  if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
    Serial.println('!');
  }
  else{
    // send the value of analog input 0:
      //String thisString = String(analogRead(A0));
      //Serial.write(thisString);
      Serial.println(analogRead(A0));
  }
  //Serial.println();
  //Serial.write("He Au=rduino here");
  //Wait for a bit to keep serial data from saturating
  delay(2);
}
