#ifndef BREATHING_ANIMATION_H
#define BREATHING_ANIMATION_H

#include "Animation.h"

// Respiration profonde alternée avec contraste marqué
class BreathingAnimation : public Animation
{
private:
  float phase1 = 0;
  float phase2 = PI; // Déphasé de 180°

public:
  BreathingAnimation() : Animation("Respiration alternée") {}

  void reset() override
  {
    phase1 = 0;
    phase2 = PI;
  }

  void update(CRGB *leds, uint32_t frameCount) override
  {
    // Vitesse lente pour un effet relaxant
    phase1 += 0.025f;
    phase2 += 0.025f;

    // Utilise easing pour un mouvement plus naturel
    float raw1 = (sin(phase1) + 1.0f) / 2.0f;
    float raw2 = (sin(phase2) + 1.0f) / 2.0f;

    float breath1 = easeInOutCubic(raw1);
    float breath2 = easeInOutCubic(raw2);

    // Contraste fort : de très sombre à très lumineux
    uint8_t bright1 = BRIGHTNESS_MIN + (uint8_t)(breath1 * (BRIGHTNESS_MAX - BRIGHTNESS_MIN));
    uint8_t bright2 = BRIGHTNESS_MIN + (uint8_t)(breath2 * (BRIGHTNESS_MAX - BRIGHTNESS_MIN));

    for (int i = 0; i < NUM_LEDS; i++)
    {
      if (isName1(i))
      {
        leds[i] = CHSV(HUE_YELLOW, SAT_DEFAULT, bright1);
      }
      else
      {
        leds[i] = CHSV(HUE_GREEN, SAT_DEFAULT, bright2);
      }
    }
  }
};

#endif
