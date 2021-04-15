/**
 * This sketch shows how to use the FFT class to analyze a stream
 * of sound. Change the number of bands to get more spectral bands
 * (at the expense of more coarse-grained time resolution of the spectrum).
 */
import processing.sound.*;
import processing.serial.*;

// Declare the sound source and FFT analyzer variables
AudioIn in;
FFT fft;
BeatDetector beatDetector;

Serial myPort;  // Create object from Serial class

// Define how many FFT bands to use (this needs to be a power of two)
int bands = 32;

// Define a smoothing factor which determines how much the spectrums of consecutive
// points in time should be combined to create a smoother visualisation of the spectrum.
// A smoothing factor of 1.0 means no smoothing (only the data from the newest analysis
// is rendered), decrease the factor down towards 0.0 to have the visualisation update
// more slowly, which is easier on the eye.
float smoothingFactor = 0.1;

// Create a vector to store the smoothed spectrum data in
float[] sum = new float[bands];

// Variables for drawing the spectrum:
// Declare a scaling factor for adjusting the height of the rectangles
int scale = 3;
// Declare a drawing variable for calculating the width of the 
float barWidth;

public void setup() {
  size(640, 360);
  background(255);

  // Calculate the width of the rects depending on how many bands we have
  barWidth = width/float(bands);

  // Load and play a soundfile and loop it.
  in = new AudioIn(this, 0);
  in.start();

  // Create the FFT analyzer and connect the playing soundfile to it.
  fft = new FFT(this, bands);
  fft.input(in);
  beatDetector = new BeatDetector(this);
  beatDetector.input(in);

  beatDetector.sensitivity(60);

  myPort = new Serial(this, "/dev/ttyUSB0", 9600);
}

int red = 0;
int green = 0;
int blue = 0;

int msg = 0;
int beat = 0;
public void draw() {
  // Set background color, noStroke and fill color
  background(200, 200, 200);
  fill(red, green, blue);
  noStroke();

  // Perform the analysis
  fft.analyze();

  for (int i = 0; i < bands-20; i++) {
    // Smooth the FFT spectrum data by smoothing factor
    sum[i] += (fft.spectrum[i] - sum[i]) * smoothingFactor;

    // Draw the rectangles, adjust their height using the scale factor
    rect(i*barWidth, height, barWidth, -sum[i]*height*scale);
  }

  //Escreve os valores das barras
  fill(0, 0, 0);
  text(fft.spectrum[0], 0, 20);
  text(fft.spectrum[1], 40, 20);

  // If a beat is currently detected, light up the indicator
  if (beatDetector.isBeat()) {
    fill(255, 0, 0);
    red = int(random(0, 255));
    green = int(random(0, 255));
    blue = int(random(0, 255));
    
  } else {
    fill(0);
  }

  stroke(255);
  strokeWeight(1);
  rect(560, 80, 15, 15, 5);

  fill(255);
  textAlign(LEFT, TOP);
  text("BEAT DETECTED", 520, 100);
  
  //Baixo
  if(fft.spectrum[0] > 0.4){
    msg = 1;
  }else{
    msg = 0;
  }
  
  //Beat
  if(beatDetector.isBeat()){
    beat = 1;
  }else{
    beat = 0;
  }
  
  if(myPort.available()> 0){
    println(myPort.readString());
  }
  
  myPort.write(0xff);
  myPort.write(beat);
  myPort.write(msg);
  myPort.write(10);
  delay(10);
}
