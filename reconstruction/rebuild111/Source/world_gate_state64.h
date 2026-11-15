#ifndef MYRO_WORLD_GATE_STATE64_H
#define MYRO_WORLD_GATE_STATE64_H
/* Shared by travel, map markers and both portal renderers. */
static int (*worldGateAvailable64)(unsigned);
static int(*worldStoryGateOpen199)(unsigned);
static int world_gate_open199(unsigned gate){return !worldStoryGateOpen199||worldStoryGateOpen199(gate); }
static int(*worldCareerGateAvailable194)(unsigned);
static int world_gate_enabled64(unsigned gate){if(gate>=CAREER_GATE_START194&&(!worldCareerGateAvailable194||!worldCareerGateAvailable194(gate)))return 0;return !worldGateAvailable64||worldGateAvailable64(gate);}
#endif
