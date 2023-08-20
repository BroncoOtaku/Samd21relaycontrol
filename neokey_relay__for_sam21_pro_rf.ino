#include "Adafruit_NeoKey_1x4.h"
#include "seesaw_neopixel.h"

Adafruit_NeoKey_1x4 neokey;
// Pins used to control the relays
const int RELAY_PIN  =  2; 
const int RELAY_PINa  = 3;   
const int RELAY_PINb  = 4;   
const int RELAY_PINc  = 5;   

// Keep track to know if relay was on or off the last time a button was pressed  
int lastrelay;
int lastrelaya;
int lastrelayb;
int lastrelayc;
int currentrelay;
int currentrelaya;
int currentrelayb;
int currentrelayc;
int relayState = LOW;
int relayStatea = LOW;
int relayStateb = LOW;
int relayStatec = LOW;

void setup() {
  Serial.begin(115200);
 
  //  Set the board's pins to outputs
  pinMode(RELAY_PIN, OUTPUT);        
  pinMode(RELAY_PINa, OUTPUT);        
  pinMode(RELAY_PINb, OUTPUT);        
  pinMode(RELAY_PINc, OUTPUT);       
 
  // Set the Neokey buttons to inputs
 currentrelay = digitalRead(NEOKEY_1X4_BUTTONA);
 currentrelaya = digitalRead(NEOKEY_1X4_BUTTONB);
 currentrelayb = digitalRead(NEOKEY_1X4_BUTTONC);
 currentrelayc = digitalRead(NEOKEY_1X4_BUTTOND);
 
  //Turn on the Neokey
  if (! neokey.begin(0x30)) {
    Serial.println("Could not start NeoKey, check wiring?");
    while(1) delay(10);
  }
  Serial.println("NeoKey started!");

// Make the neopixels work
  for (uint16_t i=0; i<neokey.pixels.numPixels(); i++) {
    neokey.pixels.setPixelColor(i, Wheel(map(i, 0, neokey.pixels.numPixels(), 0, 255)));
    neokey.pixels.show();
    delay(500);
  }
  for (uint16_t i=0; i<neokey.pixels.numPixels(); i++) {
    neokey.pixels.setPixelColor(i, 0x000000);
    neokey.pixels.show();
    delay(500);
  }
}

uint8_t j=0;  // this variable tracks the colors of the LEDs cycle.

void loop() {
  uint8_t buttons = neokey.read();
   lastrelay    = currentrelay;      // save the last state
     currentrelay = digitalRead(NEOKEY_1X4_BUTTONA); // read new state
     
      lastrelaya    = currentrelaya;      // save the last state
     currentrelaya = digitalRead(NEOKEY_1X4_BUTTONB); // read new state
     
      lastrelayb    = currentrelayb;      // save the last state
     currentrelayb = digitalRead(NEOKEY_1X4_BUTTONC); // read new state
     
      lastrelayc    = currentrelayc;      // save the last state
     currentrelayc = digitalRead(NEOKEY_1X4_BUTTOND); // read new state

  
  for (int i=0; i< neokey.pixels.numPixels(); i++) {
    neokey.pixels.setPixelColor(i, Wheel(((i * 256 / neokey.pixels.numPixels()) + j) & 255));
  }  
  // If put press a button. A relay turns on or off.
  if (buttons & (1<<0)) {
    Serial.println("Button A");
    (lastrelay == HIGH && currentrelay == LOW);
    relayState = !relayState;
    digitalWrite (RELAY_PIN, relayState) ;
    delay(500);
   
  } else {
  
    neokey.pixels.setPixelColor(400, 0);  
  
 
        
  }

  if (buttons & (1<<1)) {
    Serial.println("Button B");
    (lastrelaya == HIGH && currentrelaya == LOW);
    relayStatea = !relayStatea;
    digitalWrite (RELAY_PINa, relayStatea) ;
    delay(500);
    
  } else {
    neokey.pixels.setPixelColor(100, 0);
     
  }
  
  if (buttons & (1<<2)) {
    Serial.println("Button C");
     (lastrelayb == HIGH && currentrelayb == LOW);
    relayStateb = !relayStateb;
    digitalWrite (RELAY_PINb, relayStateb);
    delay(500);
   
  } else {
    neokey.pixels.setPixelColor(150, 0);
  }

  if (buttons & (1<<3)) {
    Serial.println("Button D");
     (lastrelayc == HIGH && currentrelayc == LOW);
    relayStatec = !relayStatec;
    digitalWrite (RELAY_PINc, relayStatec);
    delay(500);
    
  } else {
    neokey.pixels.setPixelColor(200, 0);
    
  }  

  neokey.pixels.show();
  
  delay(50);    // don't print too fast
  j++;          // make colors cycle
}



/******************************************/

// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return seesaw_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return seesaw_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return seesaw_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  return 0;
}
