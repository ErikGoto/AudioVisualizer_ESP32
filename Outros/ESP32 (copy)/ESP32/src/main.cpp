#include <Arduino.h>
#include "Adafruit_NeoPixel.h"

#define pinLed 22
#define pinLed2 18
#define pinBot 4

//Pinos led
#define pinLED 23 //Pino SIG da cascata de led
#define ledCount 10
Adafruit_NeoPixel strip(ledCount, pinLED, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinLed2, OUTPUT);

  pinMode(pinBot, INPUT_PULLUP);

  Serial.begin(9600);

  strip.setBrightness(5);
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
int countBeat = 0;

void loop() {
  if(Serial.available()){
    strip.setBrightness(100);

    if(Serial.read() == 0xff){
      for(int i=0; i<3; i++){
        inSerial[i] = Serial.read();
    
      }
    }


    if(inSerial[0] == 1){
      red = random(0, 1000);
      green = random(0, 255);
      blue = random(0, 200);
    }

    //[Beat] Acende a fita completa
    if((millis() - temp) > 80){
      temp = millis();
      
      strip.setPixelColor(10-countBeat, red, green, blue);
      countBeat++;
      if(countBeat > 10){
        countBeat = 0;
      }
    }

    //[Beat] Um led percorrendo a fita
    /*if((millis() - temp) > 60){
      temp = millis();
    
      strip.setPixelColor(10-countBeat, red, green, blue);
      strip.setPixelColor(11-countBeat, 0, 0, 0);
      countBeat++;
      if(countBeat > 10){
        countBeat = 0;
      }
    }*/


    //Bass
    if(inSerial[1] == 1){
      tempBass = millis();
      sentidoBass = 1;
    }

    if(millis() - tempBass > 20){
      tempBass = millis();
      if(sentidoBass == 1){
        strip.setPixelColor(indexBass, 255, 0, 50);
        countBeat = 0;
        strip.show();
        if(indexBass < 9)
          indexBass++;
      }else{
        strip.setPixelColor(indexBass, 0, 0, 0);
        strip.show();
        if(indexBass > 0)
          indexBass--;
      }
    }
    if(indexBass > 8){
      sentidoBass = 0;
    }

    delay(5);
  }
}