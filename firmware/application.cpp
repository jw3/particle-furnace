#include <Particle.h>
#include <OneWire.h>
#include <spark-dallas-temperature.h>

long previous = 0;
long interval = 5 * 1000;

OneWire w1(D4);
DallasTemperature sensor(&w1);

void setup() {
   sensor.begin();
}

void loop() {
   if(millis() - previous > interval) {
      sensor.requestTemperatures();
      String s(sensor.getTempFByIndex(0));
      previous = millis();
   }
}
