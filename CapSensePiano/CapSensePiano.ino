/*
  Capacitive-Touch Arduino Keyboard Piano
  
  Plays piano tones through a buzzer when the user taps touch-sensitive piano "keys"
  
  Created  18 May 2013
  Modified 23 May 2013
  by Tyler Crumpton and Nicholas Jones
  
  This code is released to the public domain. For information about the circuit,
  visit the Instructable tutorial at http://www.instructables.com/id/Capacitive-Touch-Arduino-Keyboard-Piano/
*/

#include <CapacitiveSensor.h>
#include "pitches.h"

#define COMMON_PIN      2    // The common 'send' pin for all keys
#define BUZZER_PIN      A4   // The output pin for the piezo buzzer
#define NUM_OF_SAMPLES  4   // Higher number whens more delay but more consistent readings
#define CAP_THRESHOLD   150  // Capactive reading that triggers a note (adjust to fit your needs)
#define NUM_OF_KEYS     2    // Number of keys that are on the keyboard

//int inPin = 4;

// This macro creates a capacitance "key" sensor object for each key on the piano keyboard:
#define CS(Y) CapacitiveSensor(2, Y)

// Each key corresponds to a note, which are defined here. Uncomment the scale that you want to use:
int notes[]={NOTE_C4,NOTE_D4}; // C-Major scale
//int notes[]={NOTE_A4,NOTE_B4,NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5,NOTE_G5,NOTE_A5}; // A-Minor scale
//int notes[]={NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_FS4,NOTE_G4,NOTE_AS4,NOTE_C5,NOTE_DS5}; // C Blues scale

// Defines the pins that the keys are connected to:
CapacitiveSensor keys[] = {CS(3), CS(4)};

// Define la cantidad de teclas que hay.
int keysCant = 2;

void setup() { 
  Serial.begin(9600);    // configura el puerto serie a 9600bps
  // Turn off autocalibrate on all channels:
  for(int i=0; i<2; ++i) {
    keys[i].set_CS_AutocaL_Millis(0xFFFFFFFF);
    
  }
  // Set the buzzer as an output:
  pinMode(BUZZER_PIN, OUTPUT); 
  //pinMode(inPin, INPUT); // pin4 como salida
  //analogWrite(inPin, LOW);
}

void loop() {    
  String currentKeys = "";
  // Loop through each key:
  for (int i = 0; i < keysCant; ++i) {
    // If the capacitance reading is greater than the threshold, play a note:
    if(keys[i].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD) {
     //analogWrite(inPin, HIGH);
     currentKeys = currentKeys + i;
     if(i == (keysCant - 1)){
      Serial.println(currentKeys);
      // envía valor analógico
     }
    tone(BUZZER_PIN, notes[i], 10);
    // Plays the note corresponding to the key pressed
        
    }
  }
}
