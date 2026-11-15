#ifndef MYRO_WORLD_GATE_STATE64_H
#define MYRO_WORLD_GATE_STATE64_H
/* Shared by travel, map markers and both portal renderers. */
static int (*worldGateAvailable64)(unsigned);
static int world_gate_enabled64(unsigned gate){return !worldGateAvailable64||worldGateAvailable64(gate);}
#endif
