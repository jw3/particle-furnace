#pragma once

#include <Particle.h>
#include <events.hpp>

struct ParticleListener
{
   void receive(const TempRead&) {
      Particle.publish("temp", PRIVATE);
   }
};
