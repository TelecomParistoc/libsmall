#ifndef FISHARM_H
#define FISHARM_H

#ifdef __cplusplus
extern "C" {
#endif

/* returns 1 if a fish has been captured, 0 otherwise */
int hasFish();

/* calls a callback when a fish is captured (stucked to the arm) */
void onFishCapture(void (*callback)(void));

/* calls a callback when a fish is released (falls from the arm)*/
void onFishRelease(void (*callback)(void));

#ifdef __cplusplus
}
#endif

#endif
