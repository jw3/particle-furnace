#include <Particle.h>
#include <OneWire.h>
#include <spark-dallas-temperature.h>

#include <db.hpp>
#include <fsm.hpp>
#include <states.hpp>
#include <config.hpp>
#include <events.hpp>


auto w1 = OneWire(D4);
auto sensor = DallasTemperature(&w1);

auto buffer = Buffer<TempRead>(100);
auto config = Cfg(*sensor);

// states
struct IdleX {};
struct HeatingToTemp {};
struct HeatingUntil {};

// events
struct TempReading {
   TempReading(uint8_t temp, system_tick_t tick) : temp(temp), tick(tick) {}
   const uint8_t temp;
   const system_tick_t tick;
};
struct CancelAndShutoff {};
struct RunForSomeDuration {};
struct RunUntilSomeTemp {};

using state = std::variant<IdleX, HeatingToTemp, HeatingUntil>;

struct FSM : fsm<FSM, state>
{
   template<typename State, typename Event>
   auto on_event(State&, const Event&) { return std::nullopt; }

   template<typename State>
   auto on_event(State&, const TempReading& r) {
       return r.temp > 200 ?    std::make_optional(IdleX()) : std::nullopt;
   }

   auto on_event(IdleX&, const RunForSomeDuration&) { return HeatingToTemp(); }
   auto on_event(IdleX&, const RunUntilSomeTemp&) { return HeatingUntil(); }

   auto on_event(HeatingToTemp&, const CancelAndShutoff&) { return IdleX(); }
};


bool ready(system_tick_t now, CfgRef cfg) {
   return now - cfg.lastTick() > cfg.interval();
}

void setup() {
   sensor.begin();
}

FSM s;

void loop() {
   if(ready(millis(), *config)) {
      sensor.requestTemperatures();
      const auto val = sensor.getTempFByIndex(0);
      const system_tick_t t = millis();
      if(val != DEVICE_DISCONNECTED_F) {
         s.handle(TempReading(static_cast<uint8_t>(val), t));
      }
      buffer.add(Time.now(), val);
      config.lastTick(t);
   }
}
