/* MIT. Two-layer rolling hotbar, no allocation; 0.10-second half-turn. */
#ifndef MYRO_HOTBAR_MOTION_H
#define MYRO_HOTBAR_MOTION_H
static float hotbarPhase,hotbarTarget;static unsigned hotbarObserved;static int hotbarStarted;
static void hotbar_motion(unsigned bar,float dt){const float pi=3.14159265f,tau=6.28318531f;if(!hotbarStarted){hotbarPhase=hotbarTarget=bar*pi;hotbarObserved=bar;hotbarStarted=1;}if(bar!=hotbarObserved){float base=floorf(hotbarPhase/tau)*tau+bar*pi,goal=base;for(int k=-1;k<=1;k++){float c=base+k*tau;if(fabsf(c-hotbarPhase)<fabsf(goal-hotbarPhase)-.0001f||(fabsf(fabsf(c-hotbarPhase)-fabsf(goal-hotbarPhase))<.0001f&&c>goal))goal=c;}hotbarTarget=goal;hotbarObserved=bar;}float step=dt*pi/.10f,d=hotbarTarget-hotbarPhase;if(fabsf(d)<=step)hotbarPhase=hotbarTarget;else hotbarPhase+=d>0?step:-step;if(fabsf(hotbarPhase)>12.5663706f&&hotbarPhase==hotbarTarget){hotbarPhase=fmodf(hotbarPhase,tau);if(hotbarPhase<0)hotbarPhase+=tau;hotbarTarget=hotbarPhase;}}
static float hotbar_front(unsigned bar){return (1+cosf(hotbarPhase-bar*3.14159265f))*.5f;}
static float hotbar_y(unsigned bar){float a=hotbarPhase-bar*3.14159265f;return 431+26*(1-hotbar_front(bar))+sinf(a)*2;}
#endif
