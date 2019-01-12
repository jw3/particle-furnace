#include <fsm.hpp>
#include <events.hpp>
#include <stdint.h>

using B=Behavior::OptBehavior;

B Initializing::operator()(const TempRead& temp, uint32_t tick) {
   return become<Idle>();
}

B Idle::operator()(const TempRead& temp, uint32_t tick) {
   if(temp.value() <= cfg().low())
      return become<TempLow>();
   return SameBehavior;
}

B TempLow::operator()(const TempRead& temp, uint32_t tick) {
   if(temp.value() <= cfg().low())
      return become<Blowing>(cfg().high());
   return SameBehavior;
}

B TempHigh::operator()(const TempRead& temp, uint32_t tick) {
   if(temp.value() <= cfg().low())
      return become<Idle>();
   return SameBehavior;
}

B Blowing::operator()(const TempRead& temp, uint32_t tick) {
   if(tempOff && tempOff.value() >= temp.value())
      return become<Idle>();
   if(tick > tickOff)
      return become<Idle>();
   return SameBehavior;
}

