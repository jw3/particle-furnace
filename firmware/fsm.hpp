#pragma once

#include <experimental/optional>

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
   Idle(uint8_t low, uint8_t high) : low(low), high(high) {};

   OptBehavior operator()(const TempRead& temp, system_tick_t tick) override;

private:
   uint8_t low, high;
};

struct Blowing : public Behavior
{
   using OptTemp = std::experimental::optional<uint8_t>;
   using OptTick = std::experimental::optional<system_tick_t>;

   Blowing(uint8_t temp) : tempOff(temp) {};
   Blowing(system_tick_t time) : tickOff(time) {};

   OptBehavior operator()(const TempRead& temp, system_tick_t tick) override;

private:
   OptTemp tempOff;
   OptTick tickOff;
};

