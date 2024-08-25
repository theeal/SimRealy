// Copyright (c) 2024, Martin Normann and Åke Bermhult
//
// This file is open source under the terms of the BSD 3-Clause license.
//
// Based of code by (c) Copyright 2022 Aaron Kimball
// Modifyed for RelaySimulation by Martin Norrman and Åke Bermhult
//
// This Example uses Inverted Input defined i SRelay constructor.
// Example usage for the SRelay library: in this example the PIN must be LOW 
// for a full second to trigger the Relay. and HIGH for 4 seconds to turn off the Relay 
// 
#include<Arduino.h>
#include<SimRelay.h>

// Connect a button to some GPIO pin and ground; digital pin 6 in this example.
static constexpr int PIN = 6;
static constexpr int LEDPIN = 13;
//--------
// Callbackfunction, SRelayhandler is only called when a Relay with this handler has changed its state 
// 
static void SRelayhandler(uint8_t Id, uint8_t RState) {
  switch(Id){
    case 0:  // Action when SRelay with Id 0 changes state.
      if (RState == SRelay_active) {
	    digitalWrite(LEDPIN,1);
      break; 
      }
    digitalWrite(LEDPIN,0);
    break;
    case 1:
    // Do someshing when SRelay with Id 1 changes state.
    break;
  
} // end Switch(Id)
} // end SRelayhandler
//--------------
// Create an SRelay with (Id,Invert-Input,Callbackfunction)
// or with turn on/off times (Id,Invert-Input,turnon,turnoff,Callbackfunction)
// Constructor Id = 0-255 , InvertInput = 0-1, Callbackfunction = FunctionName or NULL 
// If Callbackfunction is not used SRelay status must be read with getState() function
//
static SRelay mySRelay(0,1,1000,4000, SRelayhandler);
//static SRelay mySRelay(0,1, SRelayhandler);
// static SRelay mySRelay(0,1, NULL);
void setup() {
  pinMode(PIN, INPUT_PULLUP);
  pinMode(LEDPIN, OUTPUT);
  
  //  Change to 1s to trigger the SRelay ON; a short press won't .
  // This means it will take a second to trigger SRelayhandler(..., SRelay_active).
  // It will then take 4S to trigger SRelayhandler(..., SRelay_inactive).
 // mySRelay.setRelayONInterval(1000);
 // mySRelay.setRelayOFFInterval(4000);
  
}

static void pollSRelays() {
  mySRelay.update(digitalRead(PIN));
}

void loop() {
  pollSRelays();
  delay(20);
}
