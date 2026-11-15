/* MIT. Rebase NV2A triangle arrays to keep draw indices below the hardware limit.
 * Geometry is unchanged; only attribute base addresses and local indices move.
 * Real-Xbox high-vertex tests note a separate 0xFFFF DRAW_ARRAYS limit:
 * https://github.com/abaire/nxdk_pgraph_tests/blob/main/src/tests/high_vertex_count_tests.cpp
 */
#ifndef MYRO_GPU_VERTEX_WINDOW54_H
#define MYRO_GPU_VERTEX_WINDOW54_H
static unsigned gpuRangeFirst54,gpuRangeCount54;static uintptr_t gpuRangeBase54;
#define GPU_VERTEX_WINDOW54 65520u /* multiple of both three and the 252-vertex packet */
static void gpu_triangle_range54(const void*mesh,unsigned total,unsigned first,unsigned count){
 if(first>total||count>total-first||count%3)fail("GPU triangle range invalid");
 while(count){unsigned window=count>GPU_VERTEX_WINDOW54?GPU_VERTEX_WINDOW54:count;
  uintptr_t base=(uintptr_t)mesh+(uintptr_t)first*20u;gpuRangeFirst54=first;gpuRangeCount54=window;gpuRangeBase54=base;uint32_t*p=pb_begin();
  p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_OFFSET,(uint32_t)base&0x03ffffffu);
  p=pb_push1(p,NV097_SET_VERTEX_DATA_ARRAY_OFFSET+9*4,(uint32_t)(base+12u)&0x03ffffffu);
  p=pb_push1(p,NV097_BREAK_VERTEX_BUFFER_CACHE,0);p=pb_push1(p,NV097_SET_BEGIN_END,5);
  for(unsigned at=0;at<window;){unsigned n=window-at;if(n>252)n=252;p=pb_push1(p,NV097_DRAW_ARRAYS,((n-1u)<<24)|at);at+=n;}
  p=pb_push1(p,NV097_SET_BEGIN_END,0);pb_end(p);first+=window;count-=window;
 }
}
#endif
