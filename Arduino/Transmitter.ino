#include <Wire.h>
#include <TinyGPS++.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(PB0, PA4); // CE, CSN
TinyGPSPlus gpsData; 

const byte address[6] = "00001";

void setup() {
  Serial1.begin(9600); 
  radio.begin();
  radio.openWritingPipe(address); 
  radio.setPALevel(RF24_PA_LOW); 
  radio.stopListening();
}
void loop() {
  while (Serial1.available() > 0) {
    if (gpsData.encode(Serial1.read())) {
      
      if (gpsData.location.isValid()) {
        String gpsString = String(gpsData.location.lat(), 6) + 
										       ", " + 
										       String(gpsData.location.lng(), 6);
        radio.write(gpsString.c_str(), gpsString.length());

        delay(1000);
      }
    }
  }
}
