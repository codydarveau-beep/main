/* MIT. Real native terrain interpolation and movement across the Izlude south ramp. */
#define main world43_baseline_main
#include "test_world43.c"
#undef main
int main(void){assert(world_activate(3));unsigned steps=0;for(int direction=-1;direction<=1;direction+=2)for(int column=126;column<=129;column++){
 float x=(column+.5f)*8,y=(direction>0?57.5f:65.5f)*8;
 for(int i=0;i<64;i++){float next=y+direction;assert(allowed(x,next));if(!world_can_move(NULL,x,y,x,next)){fprintf(stderr,"ramp blocked x%.1f y%.1f next%.1f h%.3f->%.3f\n",x,y,next,height_at(x,y),height_at(x,next));abort();}y=next;steps++;}
 }
 /* Four previously absent transition cells: bottom edge must meet the bridge. */
 for(unsigned x=126;x<=129;x++){float z=height_at((x+.25f)*8,61*8.f+.001f);assert(fabsf(z+17.6f)<.06f);}
 /* These original bridge cells and all other map spans retain their source values. */
 assert(surfaceCount45==1238);assert(fabsf(height_at(127.5f*8,59.5f*8)+17.6f)<.04f);
 WorldBlob invalid[7];memcpy(invalid,worldBlobs[0],sizeof(invalid));invalid[3].offset=WORLD_FILE_BYTES;assert(!world_sections_ready44(invalid,WORLD_FILE_BYTES));assert(!world_destination_ready44(WORLD_MAP_COUNT));
 world_release();assert(!allocated&&!bytesNow);printf("PASS44 Izlude bridge: %u real one-unit steps in both directions/four approach columns, source contact heights, invalid destination metadata rejection.\n",steps);}
