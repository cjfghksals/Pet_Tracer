//수신부
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <string.h>

RF24 radio(PB0, PA4); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening();
}

void loop() {
  if(radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
    Serial1.println(text);

  }
}
