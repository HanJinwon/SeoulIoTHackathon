#include <Adafruit_NeoPixel.h>

#define PIN 8
Adafruit_NeoPixel strip = Adafruit_NeoPixel(14, PIN, NEO_GRB + NEO_KHZ800);

//  VARIABLES
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat
int fadePin = 5;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin


// these variables are volatile because they are used during the interrupt service routine!
volatile int BPM;                   // used to hold the pulse rate
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // holds the time between beats, the Inter-Beat Interval
volatile boolean Pulse = false;     // true when pulse wave is high, false when it's low
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.


void setup(){
  pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  pinMode(fadePin,OUTPUT);          // pin that will fade to your heartbeat!
  Serial.begin(9600);              // we agree to talk fast!
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS 
   // UN-COMMENT THE NEXT LINE IF YOU ARE POWERING The Pulse Sensor AT LOW VOLTAGE, 
   // AND APPLY THAT VOLTAGE TO THE A-REF PIN
   //analogReference(EXTERNAL);
   strip.begin();                   // Using LED strip object
}



void loop(){
  sendDataToProcessing('S', Signal);     // send Processing the raw Pulse Sensor data
  if (QS == true){                       // Quantified Self flag is true when arduino finds a heartbeat
        fadeRate = 255;                  // Set 'fadeRate' Variable to 255 to fade LED with pulse
        sendDataToProcessing('B',BPM);   // send heart rate with a 'B' prefix
        sendDataToProcessing('Q',IBI);   // send time between beats with a 'Q' prefix
        QS = false;                      // reset the Quantified Self flag for next time    
     }
  
  ledFadeToBeat();
  
  delay(20);                             //  take a break
}

void ledFadeToBeat(){
    fadeRate -= 15;                         //  set LED fade value
    fadeRate = constrain(fadeRate,0,255);   //  keep LED fade value from going into negative numbers!
    analogWrite(fadePin,fadeRate);          //  fade LED
  }

void sendDataToProcessing(char symbol, int data ){
    if(symbol == 'B'){
    //Serial.print(symbol);                // symbol prefix tells Processing what type of data is coming
    Serial.println(data);

    // Case of LED color by Heartbeat level
    if(data < 70) {
      for(int i=0; i<13; i++) { 
      strip.setPixelColor(i, strip.Color(211, 53, 255)); //r  
      strip.show();
      }
    }                 // the data to send culminating in a carriage return  
    else if(data > 70 && data < 80) {
      for(int i=0; i<13; i++) { 
      strip.setPixelColor(i, strip.Color(0, 150, 255)); //r  
      strip.show();
      }
    }
    else if(data > 80 && data < 90){
      for(int i=0; i<13; i++) { 
      strip.setPixelColor(i, strip.Color(0, 255, 0)); //r  
      strip.show();
      }
    }
    else if(data > 90 && data < 100){
      for(int i=0; i<13; i++) { 
      strip.setPixelColor(i, strip.Color(255, 255, 0)); //r  
      strip.show();
      }
    }
    else if(data > 100){
      for(int i=0; i<13; i++) { 
      strip.setPixelColor(i, strip.Color(255, 0, 0)); //r  
      strip.show();
      }
    }
  }
}