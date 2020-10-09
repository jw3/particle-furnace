#pragma once

#include <memory>
#include <pinmap_hal.h>

class DallasTemperature;

struct Cfg : public Config
{
   explicit Cfg(DallasTemperature& s) : dt(s) {};
   Cfg(const Cfg&) = delete;
   Cfg(const Cfg&&) = delete;

   uint8_t high() const { return s.high; }
   void high(uint8_t high) { s.high = high; }

   uint8_t low() const { return s.low; }
   void low(uint8_t low) { s.low = low; }

   system_tick_t lastTick() const { return s.lastTick; }
   void lastTick(system_tick_t t) { s.lastTick = t; }

   system_tick_t interval() const { return s.interval; }
   void interval(system_tick_t t) { s.interval = t; }

   pin_t blowerPin() const { return s.blowerPin; }
   void blowerPin(pin_t p) { s.blowerPin = p; }

   DallasTemperature& sensor() const { return dt; }

private:
   struct Settings
   {
      uint8_t low = 0;
      uint8_t high = 0;
      system_tick_t lastTick = 0;
      system_tick_t interval = 5 * 1000;

      pin_t blowerPin = D0;

   };
   Settings s;
   DallasTemperature& dt;
};
using CfgRef = Cfg&;
