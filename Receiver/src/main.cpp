#include <SPI.h>
#include <LoRa.h>


#define ss D8
#define rst D0
#define dio0 D3

void onReceive(int packetSize) {
  // received a packet
  Serial.print("Received packet '");
 
  // read packet
  for (int i = 0; i < packetSize; i++) {
    Serial.print((char)LoRa.read());
  }
 
  // print RSSI of packet
  Serial.print("' with RSSI ");
  Serial.println(LoRa.packetRssi());
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
 
  Serial.println("LoRa Receiver Callback");
 
  LoRa.setPins(ss, rst, dio0);
 
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
 
  // register the receive callback
  LoRa.onReceive(onReceive);
 
  // put the radio into receive mode
  LoRa.receive();
}
 
void loop() {
  // do nothing
  Serial.println("LoRa Receiver Callback");
  delay(3000);
}
 

