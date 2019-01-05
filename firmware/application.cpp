#include <Particle.h>
#include <OneWire.h>
#include <spark-dallas-temperature.h>

#include <pl.hpp>
#include <bus.hpp>
#include <events.hpp>

using EventBus = eventpp::Bus<TempRead>;

long previous = 0;
long interval = 5 * 1000;

OneWire w1(D4);
DallasTemperature sensor(&w1);

EventBus eb;
ParticleListener pl;

void setup() {
   sensor.begin();
}

void loop() {
   if(millis() - previous > interval) {
      sensor.requestTemperatures();
      sensor.getTempFByIndex(0);
      previous = millis();

      eb.publish<TempRead>();
   }
}
