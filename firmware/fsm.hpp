#pragma once

#include <experimental/optional>
#include "config.hpp"

class TempRead;

using std::experimental::nullopt;
using std::experimental::make_optional;
constexpr auto SameBehavior = std::experimental::nullopt;


struct Behavior
{
   using OptBehavior = std::experimental::optional<Behavior>;

   virtual OptBehavior operator()(const TempRead&, system_tick_t) {
      return SameBehavior;
   };
};

struct Idle : public Behavior
{
   Idle(ConfigRef cfg) : cfg(cfg) {};

   OptBehavior operator()(const TempRead& temp, system_tick_t tick) override;

private:
   ConfigRef cfg;
};

struct Blowing : public Behavior
{
   using OptTemp = std::experimental::optional<uint8_t>;
   using OptTick = std::experimental::optional<system_tick_t>;

   Blowing(uint8_t temp, ConfigRef cfg) : tempOff(temp), cfg(cfg) {};
   Blowing(system_tick_t time, ConfigRef cfg) : tickOff(time), cfg(cfg) {};

   OptBehavior operator()(const TempRead& temp, system_tick_t tick) override;

private:
   OptTemp tempOff;
   OptTick tickOff;
   ConfigRef cfg;
};

