/* MIT. Terrain range intersected with the actual affine camera footprint. */
#ifndef MYRO_TERRAIN_VIEW180_H
#define MYRO_TERRAIN_VIEW180_H
typedef struct{int x0,y0,x1,y1;}TerrainView180;
static TerrainView180 terrain_view180(const float*m,unsigned width,unsigned height,int cx,int cy,unsigned cells,float low,float high){
 TerrainView180 out={0,0,(int)width-1,(int)height-1};
 if(cells){int radius=(int)(cells+1)/2;out=(TerrainView180){cx-radius,cy-radius,cx+radius,cy+radius};}
 float det=m[0]*m[5]-m[1]*m[4];
 if(isfinite(det)&&fabsf(det)>.00001f){float xmin=1e30f,xmax=-1e30f,ymin=1e30f,ymax=-1e30f;
  for(int k=0;k<8;k++){float z=k&4?high:low,sx=(k&1?644.f:-4.f)-m[3]-m[2]*z,sy=(k&2?484.f:-4.f)-m[7]-m[6]*z;
   float x=(sx*m[5]-sy*m[1])/det,y=(sy*m[0]-sx*m[4])/det;
   if(x<xmin)xmin=x;if(x>xmax)xmax=x;if(y<ymin)ymin=y;if(y>ymax)ymax=y;
  }
  int x0=(int)floorf(xmin/16)-1,x1=(int)floorf(xmax/16)+1,y0=(int)floorf(ymin/16)-1,y1=(int)floorf(ymax/16)+1;
  if(x0>out.x0)out.x0=x0;if(x1<out.x1)out.x1=x1;if(y0>out.y0)out.y0=y0;if(y1<out.y1)out.y1=y1;
 }
 if(out.x0<0)out.x0=0;if(out.y0<0)out.y0=0;if(out.x1>=(int)width)out.x1=(int)width-1;if(out.y1>=(int)height)out.y1=(int)height-1;return out;
}
#endif
