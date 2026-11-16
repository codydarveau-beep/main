#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "controller_tokens64.h"
static void check(const char*s,const char*at,int expected){unsigned n=0;assert(ui_button_token64(s,at,&n)==expected);if(expected>=0)assert(n>0);}
int main(void){const char*prose[]={"a knife","A knife","with a knife","using a potion","with a button","using a button","a button","a toad"};for(unsigned i=0;i<sizeof(prose)/sizeof(*prose);i++){const char*s=prose[i],*p=strrchr(s,'a');if(i==1)p=s;if(i>=2&&i<=5)p=strchr(s,' ')+1;if(i<2)p=s;check(s,p,-1);}const char*buttons[]={"Press A","press a","Hold X","tap b","A: choose","B: cancel","A to continue","the A button","X/Y"};int expected[]={0,0,2,1,0,1,0,0,2};for(unsigned i=0;i<sizeof(buttons)/sizeof(*buttons);i++){const char*s=buttons[i],*p=s;if(i<4||i==7)p=strrchr(s,' ')+1;if(i==7)p=strstr(s,"A button");check(s,p,expected[i]);}puts("PASS actual controller parser: ordinary articles remain text; explicit button references and groups remain icons.");}
