#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include <FastLED.h>
#include "config.h"
#include "Animation.h"

class AnimationManager
{
private:
  Animation **animations;
  bool *enabled;
  int count;
  int currentIndex;
  int nextIndex;

  uint32_t frameCounter;
  unsigned long lastFrameTime;
  unsigned long animationStartTime;

  // Buffers pour le crossfade
  CRGB bufferCurrent[NUM_LEDS];
  CRGB bufferNext[NUM_LEDS];

  bool inTransition;
  float transitionProgress;

  int findNextEnabled(int from)
  {
    int next = (from + 1) % count;
    int attempts = 0;

    while (!enabled[next] && attempts < count)
    {
      next = (next + 1) % count;
      attempts++;
    }

    return (attempts < count) ? next : from;
  }

  // Blend entre deux couleurs
  CRGB blendColors(CRGB a, CRGB b, float t)
  {
    return CRGB(
        a.r + (b.r - a.r) * t,
        a.g + (b.g - a.g) * t,
        a.b + (b.b - a.b) * t);
  }

public:
  AnimationManager(Animation **anims, bool *enabledFlags, int animCount)
      : animations(anims), enabled(enabledFlags), count(animCount),
        currentIndex(0), nextIndex(0), frameCounter(0),
        lastFrameTime(0), animationStartTime(0),
        inTransition(false), transitionProgress(0) {}

  void begin()
  {
    // Trouve la première animation activée
    if (!enabled[0])
    {
      currentIndex = findNextEnabled(0);
    }
    animations[currentIndex]->reset();
    animationStartTime = millis();

    Serial.println("💒 Animations mariage initialisées");
    Serial.println("================================");
    listAnimations();
    Serial.print("\n▶ ");
    Serial.println(animations[currentIndex]->name);
  }

  void listAnimations()
  {
    for (int i = 0; i < count; i++)
    {
      Serial.print(enabled[i] ? "✓ " : "✗ ");
      Serial.println(animations[i]->name);
    }
  }

  void update(CRGB *leds)
  {
    unsigned long now = millis();

    // Limite le framerate
    if (now - lastFrameTime < FRAME_DELAY_MS)
    {
      return;
    }
    lastFrameTime = now;
    frameCounter++;

    // Vérifie si on doit démarrer une transition
    if (!inTransition && (now - animationStartTime > ANIMATION_DURATION_MS))
    {
      nextIndex = findNextEnabled(currentIndex);

      if (nextIndex != currentIndex)
      {
        inTransition = true;
        transitionProgress = 0;
        animations[nextIndex]->reset();

        Serial.print("→ Transition vers : ");
        Serial.println(animations[nextIndex]->name);
      }
      else
      {
        // Une seule animation active, on la relance
        animationStartTime = now;
      }
    }

    if (inTransition)
    {
      // Calcul de la progression du fondu
      transitionProgress += (float)FRAME_DELAY_MS / TRANSITION_DURATION_MS;

      if (transitionProgress >= 1.0f)
      {
        // Fin de transition
        inTransition = false;
        currentIndex = nextIndex;
        animationStartTime = now;

        Serial.print("▶ ");
        Serial.println(animations[currentIndex]->name);
      }
      else
      {
        // Crossfade : génère les deux animations et blend
        animations[currentIndex]->update(bufferCurrent, frameCounter);
        animations[nextIndex]->update(bufferNext, frameCounter);

        // Easing sur la transition
        float easedProgress = (1.0f - cos(transitionProgress * PI)) / 2.0f;

        for (int i = 0; i < NUM_LEDS; i++)
        {
          leds[i] = blendColors(bufferCurrent[i], bufferNext[i], easedProgress);
        }
        return;
      }
    }

    // Animation normale
    animations[currentIndex]->update(leds, frameCounter);
  }

  const char *getCurrentName()
  {
    return animations[currentIndex]->name;
  }

  void skipToNext()
  {
    if (!inTransition)
    {
      animationStartTime = 0; // Force le changement
    }
  }
};

#endif
