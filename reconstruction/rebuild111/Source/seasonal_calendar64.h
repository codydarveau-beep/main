/* Offline calendar using the Xbox date. Inclusive30-day lead-in through event end.
 * Lunar tables retain exact documented coverage; no guessed future festival dates. */
#ifndef MYRO_SEASONAL_CALENDAR64_H
#define MYRO_SEASONAL_CALENDAR64_H
#include <stdint.h>
#include "npc_clock55.h"
#include "seasonal_dates64.h"
enum{SEASON_HALLOWEEN64,SEASON_CHRISTMAS64,SEASON_EASTER64,SEASON_VALENTINE64,SEASON_WHITE64,SEASON_LUNAR64,SEASON_PATRICK64,SEASON_DUMPLING64,SEASON_CHILDREN64,SEASON_FITRI64,SEASON_MEMORIAL64,SEASON_COUNT64};
static int64_t seasonal_day64(int y,unsigned m,unsigned d){y-=m<=2;int era=(y>=0?y:y-399)/400;unsigned yo=(unsigned)(y-era*400),doYear=(153*(m+(m>2?-3:9))+2)/5+d-1,doEra=yo*365+yo/4-yo/100+doYear;return(int64_t)era*146097+doEra-719468;}
static int seasonal_window64(int64_t day,int64_t first,int64_t last){return day>=first-30&&day<=last;}
static unsigned seasonal_mask64(uint64_t utc){struct tm date;if(!npc_clock_parts55(utc,&date))return 0;int year=date.tm_year+1900;int64_t day=(int64_t)(utc/86400);unsigned mask=0;
 for(int y=year-1;y<=year+1;y++){
  static const unsigned fixed[][3]={{SEASON_HALLOWEEN64,10,31},{SEASON_CHRISTMAS64,12,25},{SEASON_VALENTINE64,2,14},{SEASON_WHITE64,3,14},{SEASON_PATRICK64,3,17},{SEASON_CHILDREN64,11,14}};
  for(unsigned i=0;i<sizeof(fixed)/sizeof(*fixed);i++){int64_t start=seasonal_day64(y,fixed[i][1],fixed[i][2]);if(seasonal_window64(day,start,start+(fixed[i][0]==SEASON_CHILDREN64?6:0)))mask|=1u<<fixed[i][0];}
  int a=y%19,b=y/100,c=y%100,d=b/4,e=b%4,f=(b+8)/25,g=(b-f+1)/3,h=(19*a+b-d-g+15)%30,i=c/4,k=c%4,l=(32+2*e+2*i-h-k)%7,m=(a+11*h+22*l)/451,n=h+l-7*m+114;int64_t easter=seasonal_day64(y,(unsigned)(n/31),(unsigned)(n%31+1));if(seasonal_window64(day,easter,easter))mask|=1u<<SEASON_EASTER64;
  int64_t may31=seasonal_day64(y,5,31);int weekday=(int)((may31+4)%7);if(weekday<0)weekday+=7;int64_t memorial=may31-(weekday+6)%7;if(seasonal_window64(day,memorial,memorial))mask|=1u<<SEASON_MEMORIAL64;
 }
 for(unsigned i=0;i<sizeof(seasonalDates64)/sizeof(*seasonalDates64);i++)if(seasonal_window64(day,seasonalDates64[i].start,seasonalDates64[i].end))mask|=1u<<seasonalDates64[i].event;
 return mask;
}
#endif
