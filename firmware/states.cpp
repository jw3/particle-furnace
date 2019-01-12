#include "states.hpp"
#include <events.hpp>
#include <stdint.h>

#include <spark_wiring.h>


BX Initializing::operator()(const TempRead& temp, uint32_t tick) {
   return become<Idle>();
}

BX Idle::operator()(const TempRead& temp, uint32_t tick) {
   if(temp.value() <= cfg().low())
      return become<TempLow>();
   return SameBehavior;
}

BX TempLow::operator()(const TempRead& temp, uint32_t tick) {
   if(temp.value() <= cfg().low())
      return become<Blowing>(cfg().high());
   return SameBehavior;
}

void TempLow::enter() {
   digitalWrite(cfg().blowerPin(), 1);
}

void TempHigh::enter() {
   digitalWrite(cfg().blowerPin(), 0);
}

BX Blowing::operator()(const TempRead& temp, uint32_t tick) {
   if(tempOff && tempOff.value() >= temp.value())
      return become<TempHigh>();
   if(tickOff && tick > tickOff.value())
      return become<TempHigh>();
   return SameBehavior;
}

