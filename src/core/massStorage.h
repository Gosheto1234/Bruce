#ifdef ARDUINO_USB_MODE

#ifndef __MASS_STORAGE_H__
#define __MASS_STORAGE_H__

#include <USBMSC.h>
#include <globals.h>

class MassStorage {
public:
    static bool shouldStop;

    /////////////////////////////////////////////////////////////////////////////////////
    // Constructor
    /////////////////////////////////////////////////////////////////////////////////////
    MassStorage();
    ~MassStorage();

    /////////////////////////////////////////////////////////////////////////////////////
    // Life Cycle
    /////////////////////////////////////////////////////////////////////////////////////
    void setup();
    void loop();

    /////////////////////////////////////////////////////////////////////////////////////
    // Operations
    /////////////////////////////////////////////////////////////////////////////////////
    static void setShouldStop(bool value) { shouldStop = value; }

    /////////////////////////////////////////////////////////////////////////////////////
    // Display functions
    /////////////////////////////////////////////////////////////////////////////////////
    static void displayMessage(String message);

private:
    USBMSC msc;

    /////////////////////////////////////////////////////////////////////////////////////
    // Setup
    /////////////////////////////////////////////////////////////////////////////////////
    void beginUsb(void);
    void setupUsbCallback(void);
    void setupUsbEvent(void);
};

int32_t usbWriteCallback(uint32_t lba, uint32_t offset, uint8_t *buffer, uint32_t bufsize);
int32_t usbReadCallback(uint32_t lba, uint32_t offset, void *buffer, uint32_t bufsize);
bool usbStartStopCallback(uint8_t power_condition, bool start, bool load_eject);

void drawUSBStickIcon(bool plugged);

#endif // MASS_STORAGE_H
#endif // ARDUINO_USB_MODE
