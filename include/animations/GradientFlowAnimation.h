#ifndef GRADIENT_FLOW_ANIMATION_H
#define GRADIENT_FLOW_ANIMATION_H

#include "Animation.h"

// Dégradé fluide jaune-vert qui se déplace lentement
class GradientFlowAnimation : public Animation
{
private:
  float offset = 0;

public:
  GradientFlowAnimation() : Animation("Dégradé fluide") {}

  void reset() override
  {
    offset = 0;
  }

  void update(CRGB *leds, uint32_t frameCount) override
  {
    offset += 0.3f;

    for (int i = 0; i < NUM_LEDS; i++)
    {
      // Position normalisée avec offset
      float pos = fmod((float)i + offset, (float)NUM_LEDS) / (float)NUM_LEDS;

      // Interpolation douce entre jaune et vert
      // Utilise une fonction sinusoïdale pour le mélange
      float blend = (sin(pos * 2.0f * PI) + 1.0f) / 2.0f;
      blend = easeInOutSine(blend);

      // Interpole la teinte entre jaune et vert
      uint8_t hue = HUE_YELLOW + (uint8_t)(blend * (HUE_GREEN - HUE_YELLOW));

      // Légère variation de luminosité pour donner du relief
      float brightVar = (sin(pos * 4.0f * PI + offset * 0.05f) + 1.0f) / 2.0f;
      uint8_t brightness = 160 + (uint8_t)(brightVar * 95);

      leds[i] = CHSV(hue, SAT_DEFAULT, brightness);
    }
  }
};

#endif
