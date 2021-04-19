#include <Arduino.h>
#include "Adafruit_NeoPixel.h"

//Pinos led
#define pinLED 23 //Pino SIG da cascata de led
#define ledCount 24
Adafruit_NeoPixel strip(ledCount, pinLED, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);

  strip.setBrightness(100);
  strip.begin();
  strip.show();
}

//Variaveis dos sinais recebidos
int inSerial[3] = {0, 0, 0};
int indexBass = 0;
int tempBass = 0;
boolean sentidoBass = 0;

int tempBeat = 0;

int red = 0;
int blue = 0;
int green = 0;

void loop() {
  if(Serial.available()){

    if(Serial.read() == 0xff){
      for(int i=0; i<3; i++){
        inSerial[i] = Serial.read();
    
      }
    }

    //Beat
    if(inSerial[0] == 1){
      red = random(0, 255);
      green = random(0, 255);
      blue = random(0, 255);

      tempBeat = millis();
      for(int i = 9; i <= 14; i++){
        strip.setPixelColor(i, red, green, blue);
      }   
    }
    if(millis() - tempBass > 25){
      tempBeat = millis();
      for(int i = 9; i <= 14; i++){
        strip.setPixelColor(i, 0, 0, 0);
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
        strip.setPixelColor(indexBass, 255, 0, indexBass*30);
        strip.setPixelColor(23 - indexBass, 200, indexBass*30, 0);
        //strip.show();
        if(indexBass <= 8)
          indexBass++;
      }else{
        strip.setPixelColor(indexBass-1, 0, 0, 0);
        strip.setPixelColor(23 - indexBass+1, 0, 0, 0);
        //strip.show();
        if(indexBass > 0)
          indexBass--;
      }
    }
    if(indexBass > 8){
      sentidoBass = 0;
    }

    strip.show();
    delay(5);
  }
}