#ifndef FISH_H
#define FISH_H

int fishHasFinished();
void fishStop();
void startFishing();
void startFishingStep();
void onEndFishing(void (*callback)(void));

#endif
