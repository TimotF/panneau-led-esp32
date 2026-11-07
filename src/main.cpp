#include <Arduino.h>
#include <FastLED.h>

#include "config.h"
#include "AnimationManager.h"

// === ANIMATIONS ===
#include "animations/BreathingAnimation.h"
#include "animations/WaveAnimation.h"
#include "animations/GradientFlowAnimation.h"
#include "animations/HeartbeatAnimation.h"
#include "animations/CandleAnimation.h"
#include "animations/PassionFlowAnimation.h"

// === BUFFER LED ===
CRGB leds[NUM_LEDS];

// === INSTANCES D'ANIMATIONS ===
BreathingAnimation breathingAnim;
WaveAnimation waveAnim;
GradientFlowAnimation gradientAnim;
HeartbeatAnimation heartbeatAnim;
CandleAnimation candleAnim;
PassionFlowAnimation passionFlowAnim;

// === CONFIGURATION DES ANIMATIONS ===
// Réglez ces valeurs pour activer ou désactiver les animations
Animation *animations[] = {
    &breathingAnim,        // Respiration naturelle alternée
    &waveAnim,             // Vague douce
    &gradientAnim,         // Dégradé fluide jaune-vert
    &heartbeatAnim,        // Battement de cœur
    &candleAnim,           // Flamme de bougie
    &passionFlowAnim       // Dégradé blanc-rouge
};

bool enabled[] = {
    true,   // Respiration naturelle alternée
    true,   // Vague douce
    true,   // Dégradé fluide jaune-vert
    true,   // Battement de cœur
    true,   // Flamme de bougie
    true    // Passion flow (blanc-rouge)
};

const int ANIM_COUNT = sizeof(animations) / sizeof(animations[0]);

// === MANAGER ===
AnimationManager manager(animations, enabled, ANIM_COUNT);

// === SETUP ===
void setup()
{
  Serial.begin(115200);
  delay(500);

  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  FastLED.clear();
  FastLED.show();

  manager.begin();
}

// === LOOP ===
void loop()
{
  manager.update(leds);
  FastLED.show();
}
