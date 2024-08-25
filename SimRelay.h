// Copyright (c) 2024, theeal and AkeBermhult
// Based of code by (c) Copyright 2022 Aaron Kimball
// Modifyed for RelaySimulation by Martin Normann and Åke Bermhult

#ifndef _SRelay_H_
#define _SRelay_H_

#include<Arduino.h>

/* Default delay for a Turn on / Turn off time in mS." */
constexpr unsigned int RelayON_MILLIS = 5;
constexpr unsigned int RelayOFF_MILLIS = 5;

// SRelay::getState() returns 1 if a input is registered as active, 0 if inactive.
constexpr uint8_t SRelay_active = 1;
constexpr uint8_t SRelay_inactive = 0;

// A function called whenever a button has definitively changed state.
typedef void (*SRelayHandler_t)(uint8_t id, uint8_t RState);

class SRelay {
public:
	// Creates an SRelay with Id Nr, InvertedInput and Callback handlerFn (using default turnon/turnoff times)

  SRelay(uint8_t id,bool ref, SRelayHandler_t handlerFn);

    // Creates an SRelay with Id Nr, InvertedInput ,turnontime, turnofftime and Callback handlerFn
  SRelay(uint8_t id,bool ref,int turnon,int turnoff, SRelayHandler_t handlerFn);

  /**
   * Called to tell the Relay about the latest polled state and register
   * as a Active/Inactive if appropriate.
   *
   * Returns true if the state has decisively changed, false otherwise.
   */
  bool update(bool latestPoll);

  /** Returns 1 if relay active, 0 if inactive. */
  uint8_t getState() const { return _RState; };

  void setHandler(SRelayHandler_t handlerFn) { _handlerFn = handlerFn; };
  SRelayHandler_t getHandler() const { return _handlerFn; };
  unsigned int getRelayONInterval() const { return _RelayONInterval; };
  unsigned int getRelayOFFInterval() const { return _RelayOFFInterval; };
  void setRelayONInterval(unsigned int debounce) { _RelayONInterval = debounce; };
  void setRelayOFFInterval(unsigned int debounce) { _RelayOFFInterval = debounce; };

private:
  uint8_t _id;
  bool _ref;
  uint8_t _RState;
  uint8_t _priorPoll;
  uint32_t _readStartTime;
  unsigned int _RelayONInterval;
  unsigned int _RelayOFFInterval;
  SRelayHandler_t _handlerFn;
};

#ifdef __cplusplus
extern "C" {
#endif // C++
  void emptySRelayHandler(uint8_t Id, uint8_t RState);
#ifdef __cplusplus
};
#endif // C++

#endif /* _SRelay_H_ */
