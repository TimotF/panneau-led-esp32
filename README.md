# Panneau LED — ESP32

Six animations FastLED pour un panneau lumineux de mariage, à adapter à votre réalisation.

## Télécharger et ouvrir le programme

1. Sur GitHub, choisissez **Code → Download ZIP**, puis décompressez l’archive.
2. Installez Visual Studio Code et son extension officielle **PlatformIO IDE**.
3. Ouvrez le dossier contenant `platformio.ini`. Ne déplacez pas les fichiers : les dossiers `src/` et `include/` sont déjà organisés.
4. Utilisez **PlatformIO: Build** pour compiler. Branchez l’ESP32 avec un câble USB de données, puis utilisez **PlatformIO: Upload** pour téléverser.

La configuration cible une ESP32 DOIT DevKit V1, avec Arduino, la plateforme Espressif32 8.0.0 et FastLED 3.10.9. La compilation de cette version a été vérifiée ; aucun nouveau test sur carte physique n’a été réalisé pendant sa préparation.

## Montage et réglages

Le programme utilise un ruban **5 V de type WS2812, ordre GRB**, piloté par **GPIO2 (D2)**. Il gère une chaîne de **35 LED**, réparties en deux zones de **18 et 17 LED**. Reliez directement GPIO2 à DIN et partagez la masse entre la carte, le ruban et l’alimentation. Cette liaison de données en 3,3 V a fonctionné sur notre montage ; vérifiez les caractéristiques d’entrée si vous utilisez un autre ruban.

Alimentez le ruban par une branche adaptée du bloc 5 V et la carte par USB. Le courant du ruban ne doit pas traverser la carte. Le schéma et les instructions de fabrication du coffret seront disponibles sur la fiche Atomm du projet (publication en préparation).

Une alimentation **USB 5 V / 2 A au total** convient à notre montage avec les animations fournies, ce que nous avons confirmé par des mesures. Ces effets n’allument jamais simultanément tous les canaux de couleur de toutes les LED à 100 %. Si vous ajoutez des LED ou modifiez les animations, mesurez à nouveau la consommation et adaptez l’alimentation et le câblage.

Dans `include/config.h`, adaptez la broche, les nombres de LED, les teintes et la durée des effets. Dans `src/main.cpp`, le tableau `enabled` active les animations : conservez au moins une valeur `true`. La luminosité globale est réglée par `FastLED.setBrightness(255)` dans ce même fichier ; `BRIGHTNESS_BASE` n’est pas utilisé.

## Animations

Respiration alternée, vague douce, dégradé jaune-vert, battement de cœur, flamme de bougie et dégradé blanc-rouge. Chaque effet possède son fichier dans `include/animations/`.

Les animations ont été créées avec l’aide de ChatGPT. Vous pouvez lui fournir les sources, le modèle de carte, la référence du ruban, la broche et les nombres de LED pour demander d’autres effets. Recompilez et essayez chaque modification avant de fermer le coffret.

Ce dépôt contient uniquement le programme. Les fichiers de découpe et les médias du projet restent sur Atomm. FastLED est une dépendance externe, récupérée par PlatformIO ; elle conserve sa propre licence.

## Licence

Les sources sont partagées sous [CC BY-NC-SA 4.0](https://creativecommons.org/licenses/by-nc-sa/4.0/), comme le projet Atomm : attribution à Ker-Tilane Créations / TimotF, usage non commercial et partage des adaptations sous la même licence. Les dépendances externes conservent leur propre licence.
