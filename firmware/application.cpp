#include <Particle.h>
#include <OneWire.h>
#include <spark-dallas-temperature.h>

#include <db.hpp>
#include <fsm.hpp>
#include <states.hpp>
#include <config.hpp>
#include <events.hpp>

using TempBuffer = Buffer<TempRead>;
using TempBufferPtr = std::unique_ptr<TempBuffer>;

OneWire w1(D4);
DallasTemperature sensor(&w1);

TempBufferPtr buffer = std::make_unique<TempBuffer>(100);
auto config = std::make_unique<Cfg>();
CfgRef cfgRef = *config;

OptB current = std::make_shared<Initializing>(cfgRef);

bool ready(system_tick_t now, CfgRef cfg) {
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
         S state{static_cast<uint8_t>(val), t};
         current = (*current)(state);
      }
      buffer->add(Time.now(), val);
      cfgRef.lastTick(t);
   }
}
