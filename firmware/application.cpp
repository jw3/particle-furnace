#include <Particle.h>
#include <OneWire.h>
#include <spark-dallas-temperature.h>

auto w1 = OneWire(D4);
auto sensor = DallasTemperature(&w1);

void setup() {
   sensor.begin();
}

uint32_t interval = 5000;
system_tick_t last;

void loop() {
   if(millis() - last > interval) {
      sensor.requestTemperatures();
      const auto val = sensor.getTempFByIndex(0);
      const system_tick_t t = millis();
      if(val != DEVICE_DISCONNECTED_F) {
         // valid
         last = millis();
      }
   }
}
