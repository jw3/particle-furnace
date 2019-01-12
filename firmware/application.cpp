#include <Particle.h>
#include <OneWire.h>
#include <spark-dallas-temperature.h>

#include <db.hpp>
#include <fsm.hpp>
#include <config.hpp>
#include <events.hpp>

using TempBuffer = Buffer<TempRead>;
using TempBufferPtr = std::unique_ptr<TempBuffer>;

OneWire w1(D4);
DallasTemperature sensor(&w1);

TempBufferPtr buffer = std::make_unique<TempBuffer>(100);
ConfigPtr config = std::make_unique<Config>();
Config& cfgRef = *config;

Behavior::OptBehavior current = Initializing(cfgRef);

bool ready(system_tick_t now, ConfigRef cfg) {
   return now - cfg.lastTick() > cfg.interval();
}

void setup() {
   sensor.begin();
}

void loop() {
   if(ready(millis(), cfgRef)) {
      sensor.requestTemperatures();
      const auto val = sensor.getTempFByIndex(0);
      const system_tick_t t = millis();
      if(val != DEVICE_DISCONNECTED_F) {
         auto Fn = *current; // cant be inlined below in gcc-5
         if(auto next = Fn(static_cast<uint8_t>(val), t))
            current = next;
      }
      buffer->add(Time.now(), val);
      cfgRef.lastTick(t);
   }
}
