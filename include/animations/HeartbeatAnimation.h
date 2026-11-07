#ifndef HEARTBEAT_ANIMATION_H
#define HEARTBEAT_ANIMATION_H

#include "Animation.h"

// Battement de cœur subtil et romantique
class HeartbeatAnimation : public Animation
{
private:
  float time = 0;
  static constexpr float BEAT_PERIOD = 1.8f;  // Période d'un battement complet

  // Simule la courbe ECG simplifiée
  float heartCurve(float t)
  {
    // Normalise t dans [0, 1]
    float phase = fmod(t / BEAT_PERIOD, 1.0f);

    // Premier pic (systole) - rapide et fort
    if (phase < 0.1f)
    {
      float p = phase / 0.1f;
      return easeInOutCubic(sin(p * PI));
    }
    // Petit creux
    else if (phase < 0.15f)
    {
      return 0.2f;
    }
    // Deuxième pic (plus petit)
    else if (phase < 0.25f)
    {
      float p = (phase - 0.15f) / 0.1f;
      return 0.3f + 0.4f * easeInOutSine(sin(p * PI));
    }
    // Repos (diastole) - long et doux
    else
    {
      float p = (phase - 0.25f) / 0.75f;
      return 0.2f + 0.1f * sin(p * PI * 0.5f);
    }
  }

public:
  HeartbeatAnimation() : Animation("Battement de cœur") {}

  void reset() override
  {
    time = 0;
  }

  void update(CRGB *leds, uint32_t frameCount) override
  {
    time += 0.016f; // Environ 60 FPS

    float beat = heartCurve(time);

    // Luminosité basée sur le battement
    uint8_t brightness = 80 + (uint8_t)(beat * 175);

    // Légère expansion/contraction du "centre" lumineux
    float center = NUM_LEDS / 2.0f;
    float expansion = beat * 0.3f;

    for (int i = 0; i < NUM_LEDS; i++)
    {
      uint8_t hue = getHue(i);

      // Distance normalisée du centre
      float dist = abs(i - center) / center;

      // Les LEDs proches du centre sont légèrement plus lumineuses pendant le pic
      float localBright = brightness * (1.0f - dist * expansion * 0.3f);
      localBright = constrain(localBright, BRIGHTNESS_MIN, BRIGHTNESS_MAX);

      leds[i] = CHSV(hue, SAT_DEFAULT, (uint8_t)localBright);
    }
  }
};

#endif
