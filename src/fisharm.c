#include <robotdriver/motioncontroller.h>
#include <robotdriver/speedcontroller.h>
#include <robotdriver/headingcontroller.h>
#include <robotdriver/motordriver.h>
#include <robotdriver/toolboxdriver.h>
#include <stdlib.h>
#include "fisharm.h"

static void (*captureCallback)(void) = NULL;
static void (*releaseCallback)(void) = NULL;

int hasFish() {
    return getSensor(2);
}

void fishSensorManager() {
    if(hasFish()) {
        if(captureCallback != NULL)
            captureCallback();
    } else {
        if(releaseCallback != NULL)
            releaseCallback();
    }
}
void onFishCapture(void (*callback)(void)) {
    enableSensorCallback(2);
    captureCallback = callback;
}

void onFishRelease(void (*callback)(void)) {
    enableSensorCallback(2);
    releaseCallback = callback;
}
