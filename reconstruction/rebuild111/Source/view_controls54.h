/* MIT. Preserve closest view; retain45%of the old outward camera-distance span.
 * Zoom is inverse distance, so interpolate1/zoom rather than zoom itself. */
#ifndef MYRO_VIEW_CONTROLS54_H
#define MYRO_VIEW_CONTROLS54_H
#include "water_mode190.h"
#define VIEW_ZOOM_IN54 6.0f
#define VIEW_OLD_ZOOM_OUT54 .85f
#define VIEW_OUTWARD_FRACTION54 .45f
/* Near distance is30%of the former closest distance (70%closer).
 * Far distance is the midpoint of the former near/far distances. */
static unsigned cameraNear65=48,cameraFar65=16,cameraStart65=36,cameraCurrent163=36,cameraRevision65;
static float camera_zoom65(unsigned value){return .85f+(value?value-1:0)*(6.f-.85f)/99.f;}
static float view_zoom_min54(void){return camera_zoom65(cameraFar65);}
static float view_zoom_clamp54(float z){float low=view_zoom_min54(),high=camera_zoom65(cameraNear65);return z<low?low:z>high?high:z;}
/* Five percent farther from the previous starting view; zoom is inverse distance. */
static float camera_start_zoom180(void){return view_zoom_clamp54(camera_zoom65(cameraStart65)/1.05f);}
static unsigned camera_value65(unsigned row){return row==1?cameraFar65:row==2?cameraNear65:cameraCurrent163;}
static int camera_step65(unsigned row,int value,int delta){int lo=row==2?(int)cameraFar65:row==3?(int)cameraFar65:1,hi=row==1?(int)cameraNear65:row==3?(int)cameraNear65:100;int n=value+delta;return n<lo?lo:n>hi?hi:n;}
static void camera_set65(unsigned row,unsigned value){unsigned n=(unsigned)camera_step65(row,(int)value,0);if(row==1)cameraFar65=n;else if(row==2)cameraNear65=n;else cameraStart65=cameraCurrent163=n;if(cameraStart65<cameraFar65)cameraStart65=cameraFar65;if(cameraStart65>cameraNear65)cameraStart65=cameraNear65;if(cameraCurrent163<cameraFar65)cameraCurrent163=cameraFar65;if(cameraCurrent163>cameraNear65)cameraCurrent163=cameraNear65;cameraRevision65++;}
#endif
