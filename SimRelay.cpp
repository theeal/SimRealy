/*
  Copyright (c) 2024, Martin Normann and Åke Bermhult
  Based of code by (c) Copyright 2022 Aaron Kimball
  Modifyed for RelaySimulation by Åke Bermhult and Martin Normann
*/
#include "SimRelay.h"

/** A handler that does nothing; for states when a given Relay is unmapped. */
void emptySRelayHandler(uint8_t Id, uint8_t RState) {
}

// ------ default Constructor
SRelay::SRelay(uint8_t id,bool ref, SRelayHandler_t handlerFn):
    _id(id), _ref(ref), _RState(SRelay_inactive), _priorPoll(SRelay_inactive), _readStartTime(0),
    _RelayONInterval(RelayON_MILLIS),
    _RelayOFFInterval(RelayOFF_MILLIS),
    _handlerFn(handlerFn) {

  if (NULL == _handlerFn) {
    _handlerFn = emptySRelayHandler;
  }
}

// Overlay Constructor
SRelay::SRelay(uint8_t id,bool ref,int turnon,int turnoff, SRelayHandler_t handlerFn):
    _id(id), _ref(ref), _RState(SRelay_inactive), _priorPoll(SRelay_inactive), _readStartTime(0),
    _RelayONInterval(turnon),
    _RelayOFFInterval(turnoff),
    _handlerFn(handlerFn) {

  if (NULL == _handlerFn) {
    _handlerFn = emptySRelayHandler;
  }
}

//-----
bool SRelay::update(bool latestPoll) {
  latestPoll = (latestPoll != _ref); // Collapse input into a 1/0 universe dependent of _ref.
	
  if (latestPoll != _priorPoll) {
    // Input has changed since we last polled. Reset debounce timer.
    _readStartTime = millis();
  }

  // Save reading for next interrogation of update().
  _priorPoll = latestPoll;

  // Decide which debounce interval to use, depending on whether we're monitoring
  // for a next state change of "active" (0 to 1) or "inactive" (1 to 0).
  unsigned int debounceInterval = _RelayONInterval;
  if (_RState == SRelay_active) {
    debounceInterval = _RelayOFFInterval;
  }

  if ((millis() - _readStartTime) > debounceInterval) {
    // The reading has remained consistent for the debounce interval.
    // It's a legitimate state.

    if (latestPoll != _RState) {
      _RState = latestPoll; // Lock this in as the new state.
      (*_handlerFn)(_id, _RState); // Invoke callback handler.
      return true;
    }
  }

  return false; // No state change.
}
