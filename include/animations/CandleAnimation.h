#ifndef CANDLE_ANIMATION_H
#define CANDLE_ANIMATION_H

#include "Animation.h"

// Flamme de bougie : effet chaleureux avec touches orangées/rouges
class CandleAnimation : public Animation
{
private:
  float flickerPhase[NUM_LEDS];
  float flickerSpeed[NUM_LEDS];

public:
  CandleAnimation() : Animation("Flamme de bougie") {}

  void reset() override
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      flickerPhase[i] = random8() / 255.0f * 2 * PI;
      flickerSpeed[i] = 0.05f + (random8() / 255.0f) * 0.1f;
    }
  }

  void update(CRGB *leds, uint32_t frameCount) override
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      flickerPhase[i] += flickerSpeed[i];

      // Plusieurs couches de bruit pour un effet organique
      float flicker1 = sin(flickerPhase[i]);
      float flicker2 = sin(flickerPhase[i] * 2.3f + i);
      float flicker3 = sin(flickerPhase[i] * 0.7f + i * 0.5f);

      float combined = (flicker1 * 0.5f + flicker2 * 0.3f + flicker3 * 0.2f + 1.0f) / 2.0f;

      // Base de couleur selon la zone
      uint8_t baseHue = getHue(i);

      // Variation de teinte vers le chaud (orange/rouge) lors des pics
      // Le jaune (42) va vers orange (30) puis rouge (15)
      // Le vert (85) va vers jaune-vert (70)
      int8_t hueShift;
      if (isName1(i))
      {
        hueShift = -(int8_t)(combined * 25); // Jaune -> orange
      }
      else
      {
        hueShift = -(int8_t)(combined * 20); // Vert -> jaune-vert
      }

      uint8_t hue = (uint8_t)max(0, (int)baseHue + hueShift);

      // Luminosité avec vacillement
      uint8_t brightness = 120 + (uint8_t)(combined * 135);

      // Légère désaturation lors des pics (plus "blanc chaud")
      uint8_t sat = SAT_DEFAULT - (uint8_t)(combined * 40);

      leds[i] = CHSV(hue, sat, brightness);
    }
  }
};

#endif
