#ifndef PINCERSACTION_H
#define PINCERSACTION_H

#ifdef __cplusplus
extern "C" {
#endif

int pincersHasFinished();
void pincersStop();
void faceShell();
void setGetTimeCallback(double (*callback)(void));

#ifdef __cplusplus
}
#endif

#endif
