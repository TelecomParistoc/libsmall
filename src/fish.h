#ifndef FISH_H
#define FISH_H

#ifdef __cplusplus
extern "C" {
#endif

int fishHasFinished();
void fishStop();
void delayStart();
void turn2();
void releaseFish();
void startFishing();
void startFishingStep();
void onEndFishing(void (*callback)(void));
void onJump(void (*callback)(int));

#ifdef __cplusplus
}
#endif

#endif
