#pragma once

#include <cassert>
#include <experimental/optional>

#include <fsm.hpp>
#include "config.hpp"
#include "events.hpp"

struct S : public State
{
   S(TempRead temp, system_tick_t tick) : temp(temp), tick(tick) {}
   TempRead temp;
   system_tick_t tick;
};

using StateRef = S&;
using B = Behavior<Cfg, S>;
using OptB = std::shared_ptr<B>;

/*
 *
 */
struct Initializing : public B
{
   explicit Initializing(CfgRef c) { cfg(c); }
   OptB operator()(S&) override;
};

/*
 *
 */
struct Idle : public B
{
   OptB operator()(S&) override;
};


/*
 *
 */
struct TempLow : public B
{
   OptB operator()(S&) override;
   void enter() override;
};


/*
 *
 */
struct TempHigh : public B
{
   OptB operator()(S&) override;
   void enter() override;
};


/*
 *
 */
struct Blowing : public B
{
   using OptTemp = std::experimental::optional<uint8_t>;
   using OptTick = std::experimental::optional<system_tick_t>;

   explicit Blowing(uint8_t temp) : tempOff(temp) {};
   explicit Blowing(system_tick_t time) : tickOff(time) {};

   OptB operator()(S&) override;

private:
   OptTemp tempOff;
   OptTick tickOff;
};

