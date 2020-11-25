#include <Particle.h>
#include <OneWire.h>
#include <spark-dallas-temperature.h>
#include <Adafruit_SSD1306.h>

SYSTEM_MODE(MANUAL)

auto w1 = OneWire(D4);
auto sensor = DallasTemperature(&w1);

void updateDisplay(float f, Adafruit_SSD1306& display) {
   display.clearDisplay();
   display.setTextColor(WHITE);
   display.setTextSize(1);
   display.setCursor(0, 10);
   display.printf("Temp: %f F", f);
   display.display();
}

Adafruit_SSD1306 tft(128, 32);
void setup() {
   updateDisplay(0.0, tft);
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
         updateDisplay(val, tft);
         last = millis();
      }
   }
}
