#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

#define MIRF_PAYLOAD 32

byte rxData[MIRF_PAYLOAD+1];
byte txData[MIRF_PAYLOAD+1];

void setup(){
  memset(rxData, 0, sizeof(rxData));
  memset(txData, 0, sizeof(txData));
  Serial.begin(9600);
  Mirf.cePin = 9;
  Mirf.csnPin = 10;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte*)"serv1");
  Mirf.payload = MIRF_PAYLOAD;   
  Mirf.channel = 10;
  Mirf.config();
}

void loop(){
  memset(rxData, 0, sizeof(rxData));
  if(!Mirf.isSending() && Mirf.dataReady()){
    Mirf.getData(rxData);
    Serial.println((const char*)rxData);
    Mirf.setTADDR((byte*)"clie1");
    for (unsigned i = 0; i != MIRF_PAYLOAD; ++i) {
      txData[i] = rxData[i] + 1;
    }
    Mirf.send(txData);
  }
}
