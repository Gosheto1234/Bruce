#include "ble_main.h"

// Bruce’s existing BLE modules
#include "ble_common.h"
#include "ble_spam.h"

// Select mode: 0 = advertiser/spam, 1 = scanner/display
static constexpr int BLE_MODE = 0;

namespace BLEModule {

void bleInit() {
    // Initialize display and M5 hardware if not done elsewhere
    M5.begin();
    M5.Lcd.setRotation(3);

    // Run Bruce’s BLE self‐test (registers callbacks, etc.)
    ble_test();
}

void blePoll() {
    if (BLE_MODE == 0) {
        // Advertising/spam mode
        aj_adv(/* ble_choice */ 0);
    } else {
        // Scanning/display mode
        ble_scan();
        disPlayBLESend();
    }
    // Short delay to avoid BLE stack congestion
    delay(50);
}

} // namespace BLEModule
