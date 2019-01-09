#include <fsm.hpp>
#include <events.hpp>

#include <stdint.h>
#include <spark_wiring_ticks.h>


Behavior::OptBehavior Idle::operator()(const TempRead& temp, uint32_t tick) {
   if(temp.value() <= low)
      return Blowing(high);
   return std::move(*this);
}

Behavior::OptBehavior Blowing::operator()(const TempRead& temp, uint32_t tick) {
   if(tempOff && tempOff.value() >= temp.value())
      return Idle(0, 0);
   if(millis() > tickOff)
      return Idle(0, 0);
   return SameBehavior;
}
