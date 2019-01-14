#include "states.hpp"
#include <events.hpp>
#include <stdint.h>

#include <spark_wiring.h>


OptB Initializing::operator()(S& state) {
   return become<Idle>();
}

OptB Idle::operator()(S& state) {
   if(state.temp.value() <= cfg().low())
      return become<TempLow>();
   return remain();
}

OptB TempLow::operator()(S& state) {
   if(state.temp.value() <= cfg().low())
      return become<Blowing>(cfg().high());
   return remain();
}

void TempLow::enter() {
   digitalWrite(cfg().blowerPin(), 1);
}

OptB TempHigh::operator()(S& state) {
   return become<Idle>();
}

void TempHigh::enter() {
   digitalWrite(cfg().blowerPin(), 0);
}

OptB Blowing::operator()(S& state) {
   if(tempOff && tempOff.value() >= state.temp.value())
      return become<TempHigh>();
   if(tickOff && state.tick > tickOff.value())
      return become<TempHigh>();
   return remain();
}

