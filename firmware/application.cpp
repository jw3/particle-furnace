#include <Particle.h>
#include <OneWire.h>
#include <spark-dallas-temperature.h>

#include <db.hpp>
#include <fsm.hpp>
#include <events.hpp>

using TempBuffer = Buffer<TempRead>;

system_tick_t previous = 0;
system_tick_t interval = 5 * 1000;

OneWire w1(D4);
DallasTemperature sensor(&w1);

auto tb = std::make_shared<TempBuffer>(100);

Behavior::OptBehavior current = Idle(0, 0);

void setup() {
   sensor.begin();
}

void loop() {
   if(millis() - previous > interval) {
      sensor.requestTemperatures();
      const auto val = sensor.getTempFByIndex(0);
      const system_tick_t t = millis();
      if(val != DEVICE_DISCONNECTED_F) {
         auto Fn = *current; // cant be inlined below in gcc-5
         if(auto next = Fn(static_cast<uint8_t>(val), t))
            current = next;
      }
      previous = t;
   }
}
