#include <SevSeg.h>

SevSeg sevseg;
int analogPin = 0;     // potentiometer wiper (middle terminal) connected to analog pin 3
// outside leads to ground and +5V
int val = 0;           // variable to store the value read
int nextPushed = 0;    // is the next button pushed

byte digitPins[] = {
  2, 3, 4, 5};         // LSB to MSB
byte segmentPins[] = {
  6,7,8,9,10,11,12,13}; // Segment a to g
byte nextPin = 0; 

unsigned int adc;


//Create global variables
unsigned long timer;
int CentSec=0;

void setup()
{
  //I am using a common anode display, with the digit pins connected
  //from 2-5 and the segment pins connected from 6-13
  sevseg.Begin(0,2,3,4,5,6,7,8,9,10,11,12,13);
  //Set the desired brightness (0 to 100);
  sevseg.Brightness(90);
  Serial.begin(9600);          //  setup serial
  timer = millis();
}

void loop()
{
  //Produce an output on the display
  sevseg.PrintOutput();

  val = analogRead(analogPin);    // read the input pin
  nextPushed = digitalRead(nextPin);
  //Serial.println(val);
  //Serial.println(humidity(val));
  Serial.println(nextPushed);



  //Check if 10ms has elapsed
  unsigned long mils=millis();
  if (mils-timer>=100) {
    timer=mils;
    //Update the number to be displayed, with a decimal
    //place in the correct position.
    sevseg.NewNum(humidity(val),(byte) 2);
  }

}

int humidity(int readVal) {
  return (
  1024 - readVal) / 10;
  //return ((1024 - readVal) * 100) / 1024; 
}



