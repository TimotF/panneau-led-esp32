#ifndef WAVE_ANIMATION_H
#define WAVE_ANIMATION_H

#include "Animation.h"

// Vague lumineuse fluide qui traverse les deux noms
class WaveAnimation : public Animation
{
private:
  float waveOffset = 0;

public:
  WaveAnimation() : Animation("Vague douce") {}

  void reset() override
  {
    waveOffset = 0;
  }

  void update(CRGB *leds, uint32_t frameCount) override
  {
    waveOffset += 0.06f;

    for (int i = 0; i < NUM_LEDS; i++)
    {
      // Onde sinusoïdale avec propagation
      float pos = (float)i / NUM_LEDS;
      float wave = sin(waveOffset + pos * 4.0f * PI);

      // Applique easing pour adoucir les pics
      float normalized = (wave + 1.0f) / 2.0f;
      float eased = easeInOutSine(normalized);

      uint8_t brightness = 80 + (uint8_t)(eased * 175);
      uint8_t hue = getHue(i);

      // Légère variation de teinte avec la vague (reste dans jaune-vert)
      int8_t hueShift = (int8_t)(wave * 8);
      hue = constrain(hue + hueShift, HUE_YELLOW - 10, HUE_GREEN + 10);

      leds[i] = CHSV(hue, SAT_DEFAULT, brightness);
    }
  }
};

#endif
