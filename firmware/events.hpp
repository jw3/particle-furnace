#pragma once

#ifndef DEVICE_DISCONNECTED_F
#define DEVICE_DISCONNECTED_F -196.6
#endif

struct TempRead
{
   TempRead(uint8_t val) : val(val) {};
   uint8_t value() const { return val; }
   bool valid() const { return val != DEVICE_DISCONNECTED_F; }
private:
   uint8_t val;
};
