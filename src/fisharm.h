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

/* calls a callback when an ax-12 finishes a move */
void onMagnetOn(void (*callback)(void));
void onMagnetOff(void (*callback)(void));
void onArmUp(void (*callback)(void));
void onArmMid(void (*callback)(void));
void onArmDown(void (*callback)(void));

/* puts both Ax-12 in default mode with a speed limit defined in fisharm.c */
void initFishAx12();

/* functions to move the Ax-12 */
void magnetOn() {
void magnetOff() {
void armUp() {
void armMid() {
void armDown() {

#ifdef __cplusplus
}
#endif

#endif
