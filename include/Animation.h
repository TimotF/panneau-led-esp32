#ifndef ANIMATION_H
#define ANIMATION_H

#include <FastLED.h>
#include "config.h"

// Classe de base abstraite pour toutes les animations
class Animation
{
public:
  const char *name;

  Animation(const char *animName) : name(animName) {}
  virtual ~Animation() {}

  // Appelé à chaque frame, doit remplir le buffer sans appeler FastLED.show()
  virtual void update(CRGB *leds, uint32_t frameCount) = 0;

  // Reset de l'état interne (appelé au début de l'animation)
  virtual void reset() {}

protected:
  // Helpers communs
  inline uint8_t getHue(int ledIndex)
  {
    return (ledIndex < NUM_LED_NAME1) ? HUE_YELLOW : HUE_GREEN;
  }

  inline bool isName1(int ledIndex)
  {
    return ledIndex < NUM_LED_NAME1;
  }

  // Easing functions pour des mouvements fluides
  inline float easeInOutSine(float t)
  {
    return -(cos(PI * t) - 1.0f) / 2.0f;
  }

  inline float easeInOutCubic(float t)
  {
    return t < 0.5f ? 4.0f * t * t * t : 1.0f - pow(-2.0f * t + 2.0f, 3) / 2.0f;
  }
};

#endif
