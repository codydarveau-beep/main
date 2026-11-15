/* MIT. Ask the linked NXDK allocator to return unused pages, never live data.
 * The SDK's dlmalloc exports are verified in the pinned libpdclib library. */
#include <limits.h>
static unsigned heapTrimAt183,heapReturned183,heapTrimCalls183;
#if !defined(MYRO_HOST) || defined(MYRO_HEAP_HOST183)
extern int dlmalloc_trim(size_t);
extern size_t dlmalloc_footprint(void);
static unsigned heap_footprint183(void){return(unsigned)dlmalloc_footprint();}
static void heap_trim183(void){size_t before=dlmalloc_footprint();dlmalloc_trim(65536);size_t after=dlmalloc_footprint();if(before>after){size_t delta=before-after;heapReturned183=delta>UINT_MAX-heapReturned183?UINT_MAX:heapReturned183+(unsigned)delta;}heapTrimCalls183++;}
static void heap_frame183(unsigned now){if((unsigned)(now-heapTrimAt183)<5000)return;heapTrimAt183=now;MM_STATISTICS m={0};m.Length=sizeof(m);MmQueryStatistics(&m);if(m.AvailablePages<2048)heap_trim183();}
#else
static unsigned heap_footprint183(void){return 0;}
static void heap_trim183(void){}
static void heap_frame183(unsigned now){(void)now;}
#endif
