#ifndef CONFIG_H
#define CONFIG_H

// === HARDWARE ===
#define DATA_PIN 2
#define NUM_LED_NAME1 18  // LED de la première zone
#define NUM_LED_NAME2 17  // LED de la seconde zone
#define NUM_LEDS (NUM_LED_NAME1 + NUM_LED_NAME2)

// === COULEURS DU MARIAGE ===
#define HUE_YELLOW 42     // Jaune doré
#define HUE_GREEN 85      // Vert tendre
#define SAT_DEFAULT 255   // Saturation par défaut
#define SAT_PASTEL 180    // Saturation pastel

// === TIMING ===
#define ANIMATION_DURATION_MS 25000   // Durée par animation
#define TRANSITION_DURATION_MS 1500   // Durée du fondu enchaîné
#define FRAME_DELAY_MS 16             // ~60 FPS

// === LUMINOSITÉ ===
#define BRIGHTNESS_MIN 40
#define BRIGHTNESS_MAX 255
#define BRIGHTNESS_BASE 150

#endif
