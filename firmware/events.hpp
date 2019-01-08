#pragma once

#include <event.hpp>
#include <stdint.h>

struct TempRead : public eventpp::Event<TempRead>
{
   explicit TempRead(uint8_t val) : val(val) {};
   uint8_t value() { return val; }
private:
   uint8_t val;
};
struct TempReadFail : public eventpp::Event<TempReadFail> {};
