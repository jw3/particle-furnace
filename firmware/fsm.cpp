#include <fsm.hpp>
#include <events.hpp>

#include <stdint.h>
#include <spark_wiring_ticks.h>


Behavior::OptBehavior Idle::operator()(const TempRead& temp, uint32_t tick) {
   if(temp.value() <= cfg.low())
      return Blowing(cfg.high(), cfg);
   return std::move(*this);
}

Behavior::OptBehavior Blowing::operator()(const TempRead& temp, uint32_t tick) {
   if(tempOff && tempOff.value() >= temp.value())
      return Idle(cfg);
   if(millis() > tickOff)
      return Idle(cfg);
   return SameBehavior;
}
