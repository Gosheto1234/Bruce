#pragma once

#include <Arduino.h>

namespace BLEModule {

/** 
 * @brief  Initialize the BLE subsystem.  
 *         Call this in your global setup() once.  
 */
void bleInit();

/** 
 * @brief  Poll or run BLE logic.  
 *         Call this in your global loop() repeatedly.  
 */
void blePoll();

} // namespace BLEModule

