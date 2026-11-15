/* MIT. Recovery counters are elapsed milliseconds, independent of simulation time. */
#ifndef MYRO_RECOVERY_STATE50_H
#define MYRO_RECOVERY_STATE50_H
typedef struct {
 unsigned hp,sp,skillHP,skillSP,sittingHP,sittingSP;
 float fractionalMS;
} Recovery50;
#endif
