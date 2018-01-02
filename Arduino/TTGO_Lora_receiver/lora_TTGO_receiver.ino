
#include <SPI.h>
#include <LoRa.h>
#include <SSD1306.h> // alias for `#include "SSD1306Wire.h"`



// GPIO5  -- SX1278's SCK
// GPIO19 -- SX1278's MISO
// GPIO27 -- SX1278's MOSI
// GPIO18 -- SX1278's CS
// GPIO14 -- SX1278's RESET
// GPIO26 -- SX1278's IRQ(Interrupt Request)

SSD1306 display(0x3c, 4, 15);

#define SS 18
#define RST 14
#define DI0 26
#define BAND 429E6 //915E6

// #define BAND 434500000.00
// #define BAND 434500000.00

//#define spreadingFactor 9
// #define SignalBandwidth 62.5E3
//#define SignalBandwidth 31.25E3
//#define preambleLength 8
//#define codingRateDenominator 8

int lora_msg_reception_counter = 0;

void setup() {
  //-----------------------
  // Setup OLED Display
  pinMode(16,OUTPUT);
  digitalWrite(16, LOW); // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(16, HIGH);
  //-----------------------
  
  Serial.begin(115200);
  while (!Serial); //if just the the basic function, must connect to a computer
  delay(1000);
  
  //Serial.println("LoRa Receiver"); 

// Initialising the UI will init the display too.
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(5,5,"LoRa Receiver");
  display.display();

  SPI.begin(5,19,27,18);
  LoRa.setPins(SS,RST,DI0);

  //LoRa.setSignalBandwidth(SignalBandwidth);

  //LoRa.setCodingRate4(codingRateDenominator);

  //LoRa.setPreambleLength(preambleLength);
  
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();

  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(3, 5, "Waiting for packet ");
  display.drawString(50, 30, String(lora_msg_reception_counter));
  display.display();
  
  if (packetSize) {
    lora_msg_reception_counter++;
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }
    
    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
