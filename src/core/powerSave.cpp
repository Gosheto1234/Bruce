#include "powerSave.h"
#include "display.h"
#include "settings.h"


#define SCREEN_OFF_DELAY 5000
#define FADE_OUT_STEPS 10
#define FADE_OUT_DELAY 30  

void checkPowerSaveTime() {
    if (bruceConfig.dimmerSet == 0) return;
    unsigned long elapsed = millis() - previousMillis;

    if (elapsed >= (bruceConfig.dimmerSet * 1000) && !dimmer && !isSleeping) {
        dimmer = true;
        setBrightness(5, false);
    } else if (elapsed >= ((bruceConfig.dimmerSet * 1000) + SCREEN_OFF_DELAY) && !isScreenOff &&
               !isSleeping) {
        isScreenOff = true;

        // Smooth fade-out effect
        for (int brightness = 100; brightness >= 0; brightness -= (100 / FADE_OUT_STEPS)) {
            setBrightness(brightness, false);
            delay(FADE_OUT_DELAY);
        }

        turnOffDisplay();  // After fading out, turn off the display
    }
}


void sleepModeOn() {
    isSleeping = true;
    setCpuFrequencyMhz(80);

    // Smooth fade-out effect before going to sleep
    for (int brightness = 100; brightness >= 0; brightness -= (100 / FADE_OUT_STEPS)) {
        setBrightness(brightness, false);  // Gradually reduce brightness
        delay(FADE_OUT_DELAY);  // Wait before the next reduction
    }

    turnOffDisplay();
    disableCore0WDT();
    disableCore1WDT();
    disableLoopWDT();
    delay(200);
}

void sleepModeOff() {
    isSleeping = false;
    setCpuFrequencyMhz(240);
    getBrightness();
    enableCore0WDT();
    enableCore1WDT();
    enableLoopWDT();
    feedLoopWDT();
    delay(200);
}
