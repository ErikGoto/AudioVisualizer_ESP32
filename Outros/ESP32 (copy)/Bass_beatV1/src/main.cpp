#include <Arduino.h>
#include "Adafruit_NeoPixel.h"

#define pinBot 4

//Pinos led
#define pinLED 23 //Pino SIG da cascata de led
#define ledCount 24
Adafruit_NeoPixel strip(ledCount, pinLED, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(pinBot, INPUT_PULLUP);

  Serial.begin(9600);

  strip.setBrightness(100);
  strip.begin();
  strip.show();
}

int temp = 0;
int temp2 = 0;
int inSerial[3] = {0, 0, 0};

int indexBass = 0;
int tempBass = 0;
boolean sentidoBass = 0;

int red = 0;
int blue = 0;
int green = 0;

int matrixLed[5] = {0, 0, 0, 0, 0};
int countBeat = 0;
void loop() {
  if(Serial.available()){

    if(Serial.read() == 0xff){
      for(int i=0; i<3; i++){
        inSerial[i] = Serial.read();
    
      }
    }

    //Beat
    if(inSerial[0] == 1){
      matrixLed[0] = 1;
    }
    if((millis() - temp) > 50){
      temp = millis();

      if(matrixLed[countBeat] == 1){
        strip.setPixelColor(10-countBeat, red, green, blue);
        matrixLed[countBeat] = 0;
        matrixLed[countBeat+1] = 1;

        strip.show();
      }

      if(matrixLed[countBeat] == 0){
        strip.setPixelColor(10-countBeat, 0, 0, 0);
      }
      countBeat++;

      if(countBeat > 6){
        countBeat = 0;
        red = random(0, 255);
        green = random(0, 255);
        blue = random(0, 255);
      }
    }




    //Bass
    if(inSerial[1] == 1){
      tempBass = millis();
      sentidoBass = 1;
    }

    if(millis() - tempBass > 15){
      tempBass = millis();
      if(sentidoBass == 1){
        strip.setPixelColor(indexBass, 200, 0, 150);
        strip.show();
        if(indexBass < 5)
          indexBass++;
      }else{
        strip.setPixelColor(indexBass, 0, 0, 0);
        strip.show();
        if(indexBass > 0)
          indexBass--;
      }
    }
    if(indexBass > 4){
      sentidoBass = 0;
    }
    


    //strip.show();

    delay(5);
  }
}