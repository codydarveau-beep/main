/* MIT. Equal integer blue cells, equal one-pixel gaps, no unticked end margins. */
#ifndef MYRO_CAST_LAYOUT43_H
#define MYRO_CAST_LAYOUT43_H
static void cast_layout41(float total,int*margin,int*used,int*step,int*segments){int n=isfinite(total)&&total>0?(int)ceilf(fminf(12,total*2)):1;if(n<1)n=1;if(n>12)n=12;int cell=(46-(n-1)+n/2)/n;if(cell<1)cell=1;*step=cell+1;*used=n**step-1;*margin=0;*segments=n;}
static int cast_quarter_gap(float total,int pixel){int margin,used,step,n;cast_layout41(total,&margin,&used,&step,&n);return pixel>=0&&pixel<used&&pixel%step==step-1;}
#endif
