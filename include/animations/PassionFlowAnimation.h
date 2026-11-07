#ifndef PASSION_FLOW_ANIMATION_H
#define PASSION_FLOW_ANIMATION_H

#include "Animation.h"

// Dégradé fluide blanc-rouge qui se déplace
class PassionFlowAnimation : public Animation
{
private:
  float offset = 0;

  // Rouge en HSV FastLED = 0 (ou 255)
  static const uint8_t HUE_RED = 0;

public:
  PassionFlowAnimation() : Animation("Passion flow") {}

  void reset() override
  {
    offset = 0;
  }

  void update(CRGB *leds, uint32_t frameCount) override
  {
    offset += 0.25f;

    for (int i = 0; i < NUM_LEDS; i++)
    {
      // Position normalisée avec offset
      float pos = fmod((float)i + offset, (float)NUM_LEDS) / (float)NUM_LEDS;

      // Interpolation douce entre blanc et rouge
      float blend = (sin(pos * 2.0f * PI) + 1.0f) / 2.0f;
      blend = easeInOutSine(blend);

      // Quand blend = 0 : blanc (sat faible), quand blend = 1 : rouge vif
      uint8_t hue = HUE_RED;
      uint8_t sat = (uint8_t)(blend * 255); // 0 = blanc, 255 = rouge pur

      // Légère variation de luminosité
      float brightVar = (sin(pos * 4.0f * PI + offset * 0.05f) + 1.0f) / 2.0f;
      uint8_t brightness = 180 + (uint8_t)(brightVar * 75);

      leds[i] = CHSV(hue, sat, brightness);
    }
  }
};

#endif
