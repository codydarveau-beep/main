#include <stdio.h>
#include <assert.h>
#include "frontend_state56.h"
static void settle(Frontend56*f){while(f->fade)frontend_tick56(f,180);}
int main(void){Frontend56 f;frontend_init56(&f);unsigned code[]={1024,1024,2048,2048,4096,8192,4096,8192,4,2};for(unsigned i=0;i<10;i++)frontend_input56(&f,code[i]);settle(&f);assert(f.unlocked&&f.page==F56_HOME);frontend_input56(&f,2048);assert(f.row==1);frontend_input56(&f,2048);assert(f.row==0);frontend_input56(&f,1024);assert(f.row==1);frontend_input56(&f,2);settle(&f);assert(f.page==F56_SETTINGS);f.page=F56_HOME;f.row=0;frontend_input56(&f,2);settle(&f);assert(f.page==F56_CHARACTERS&&f.unlocked);frontend_input56(&f,4);settle(&f);assert(f.page==F56_HOME);f.unlocked=0;frontend_input56(&f,2048);assert(f.row==1);frontend_input56(&f,2048);assert(f.row==0);puts("PASS title: two options before/after Konami, Start enters characters, Settings remains, no third developer option; unlocked state retained for header/session.");}
