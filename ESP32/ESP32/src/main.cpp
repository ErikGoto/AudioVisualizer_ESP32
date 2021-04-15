#include <Arduino.h>
#include "Adafruit_NeoPixel.h"

#define pinLed 4
#define pinLed2 18

//Pinos led
#define pinLED 23 //Pino SIG da cascata de led
#define ledCount 10
Adafruit_NeoPixel strip(ledCount, pinLED, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinLed2, OUTPUT);

  Serial.begin(9600);

  strip.setBrightness(50);
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
void loop() {
  if(Serial.available()){
    
    if(Serial.read() == 0xff){
      for(int i=0; i<3; i++){
        inSerial[i] = Serial.read();
    
      }
    }

    if(inSerial[0] == 1){
      temp = millis();   
      red = 0;
      green = random(0, 255);
      blue = random(0, 100);
      for(int i = 5; i < 10; i++){
        strip.setPixelColor(i, red, green, blue);
      }
    }

    if((millis() - temp) > 200){
      temp = millis();

      for(int i = 5; i < 10; i++){
        strip.setPixelColor(i, 0, 0, 0);
      }
    }


    if(inSerial[1] == 1){
      tempBass = millis();
      sentidoBass = 1;
    }

    if(millis() - tempBass > 15){
      tempBass = millis();
      if(sentidoBass == 1){
        strip.setPixelColor(indexBass, 200, 0, 150);
        if(indexBass < 5)
          indexBass++;
      }else{
        strip.setPixelColor(indexBass, 0, 0, 0);
        if(indexBass > 0)
          indexBass--;
      }
    }
    if(indexBass > 4){
      sentidoBass = 0;
    }



    strip.show();

    Serial.println('a');
    delay(5);
  }
}