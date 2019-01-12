#pragma once

#include <cassert>
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

   template<class T, class... A>
   OptBehavior become(A&& ... args) {
      T t(std::forward<A>(args)...);
      t.cfg(*config);
      return std::move(t);
   }

protected:
   Behavior() = default;
   ConfigRef cfg() {
      assert(config);
      return *config;
   }
   void cfg(ConfigRef c) {}

private:
   Config* config = nullptr;
};

/*
 *
 */
struct Initializing : public Behavior
{
   explicit Initializing(ConfigRef c) { cfg(c); }
   OptBehavior operator()(const TempRead&, system_tick_t) override;
};

/*
 *
 */
struct Idle : public Behavior
{
   OptBehavior operator()(const TempRead&, system_tick_t) override;
};


/*
 *
 */
struct TempLow : public Behavior
{
   OptBehavior operator()(const TempRead&, system_tick_t) override;
};


/*
 *
 */
struct TempHigh : public Behavior
{
   OptBehavior operator()(const TempRead&, system_tick_t) override;
};


/*
 *
 */
struct Blowing : public Behavior
{
   using OptTemp = std::experimental::optional<uint8_t>;
   using OptTick = std::experimental::optional<system_tick_t>;

   explicit Blowing(uint8_t temp) : tempOff(temp) {};
   explicit Blowing(system_tick_t time) : tickOff(time) {};

   OptBehavior operator()(const TempRead& temp, system_tick_t tick) override;

private:
   OptTemp tempOff;
   OptTick tickOff;
};

