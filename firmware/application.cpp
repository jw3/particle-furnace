#include <Particle.h>
#include <OneWire.h>
#include <spark-dallas-temperature.h>

#include <db.hpp>
#include <pl.hpp>
#include <bus.hpp>
#include <events.hpp>

using EventBus = eventpp::Bus<TempRead, TempReadFail>;
using TempBuffer = Buffer<TempRead>;

system_tick_t previous = 0;
system_tick_t interval = 5 * 1000;

OneWire w1(D4);
DallasTemperature sensor(&w1);

EventBus eb;
auto tb = std::make_shared<TempBuffer>(100);
ParticleListener pl;

void setup() {
   eb.add<TempRead>(tb);
   sensor.begin();
}

void loop() {
   if(millis() - previous > interval) {
      sensor.requestTemperatures();
      const auto val = sensor.getTempFByIndex(0);
      if(val != DEVICE_DISCONNECTED_F)
         eb.publish<TempRead>(static_cast<uint8_t>(val));
      else eb.publish<TempReadFail>();

      previous = millis();
   }
}
