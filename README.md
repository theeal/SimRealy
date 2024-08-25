Based of code by (c) Copyright 2022 Aaron Kimball.

Modifyed for RelaySimulation by Martin Normann and Åke Bermhult

# SimRealy
This Library Simulates Relay:s with Turnactive/Turninactive timers. 

Default Turn Active/Inactive is defined in SimRelay.h
Can be changed with  setRelayONInterval(int),setRelayOFFInterval(int)

SRelay Relay1(0,0,handlerFn)

Creates an SRelay with Name Relay1   Id Nr 0 ,InvertedInput 0, Callback to handlerFn

  SRelay(uint8_t id,bool ref, SRelayHandler_t handlerFn);
  ----------------------
Or with individual turnon/turnoff times 

SRelay Relay1(0,0,10,100,handlerFn)
Creates an SRelay with Name Relay1   Id Nr 1 ,InvertedInput 0, turnontime 10 mS turnofftime 100 mS Callback to handlerFn

SRelay(uint8_t id,bool ref,int turnon,int turnoff, SRelayHandler_t handlerFn)

----Status is Independent of InvertedInput.  
SRelay_active = 1;
SRelay_inactive = 0;
