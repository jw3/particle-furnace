#pragma once

#include <events.hpp>
#include <stdint.h>

struct TempRead
{
   TempRead(uint8_t val) : val(val) {};
   uint8_t value() const { return val; }
private:
   uint8_t val;
};
struct TempReadFail {};
