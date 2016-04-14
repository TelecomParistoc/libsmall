#ifndef FISH_H
#define FISH_H

#ifdef __cplusplus
extern "C" {
#endif

int fishHasFinished();
void fishStop();
void startFishing();
void startFishingStep();
void onEndFishing(void (*callback)(void));

#ifdef __cplusplus
}
#endif

#endif
