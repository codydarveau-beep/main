#ifndef MYRO_CONTROLLER_TOKENS64_H
#define MYRO_CONTROLLER_TOKENS64_H
/* Explicit controller references, preserving articles and ordinary prose. */
static int ui_button_token64(const char*begin,const char*s,unsigned*length){
 static const struct{const char*name;unsigned icon;}names[]={
 {"LEFT/RIGHT",11},{"UP/DOWN",10},{"Right stick",13},{"Left stick",12},{"right stick",13},{"left stick",12},{"R stick",13},{"L stick",12},{"D-pad",10},{"D-PAD",10},
 {"Up/down",10},{"Left/right",11},{"L3",12},{"R3",13},{"LEFT",11},{"RIGHT",11},{"UP",10},{"DOWN",10},{"START",8},{"SELECT",9},{"Start",8},{"Select",9},{"LB",4},{"RB",5},{"LT",6},{"RT",7},{"A",0},{"B",1},{"X",2},{"Y",3}};
 for(unsigned i=0;i<sizeof(names)/sizeof(*names);i++){
  unsigned n=(unsigned)strlen(names[i].name);unsigned matched=0;while(matched<n){unsigned a=(unsigned char)s[matched],b=(unsigned char)names[i].name[matched];if(a>='a'&&a<='z')a-=32;if(b>='a'&&b<='z')b-=32;if(a!=b)break;matched++;}if(matched!=n)continue;
  const char*p=s+n;if((*p>='A'&&*p<='Z')||(*p>='a'&&*p<='z')||(*p>='0'&&*p<='9')||*p=='_')continue;
  while(*p==' ')p++;int explicit64=*p==':'||*p=='/'||!strcmp(names[i].name,"L3")||!strcmp(names[i].name,"R3")||((names[i].icon>=4&&names[i].icon<=7)||names[i].icon>=12||strchr(names[i].name,'/')||strstr(names[i].name,"pad")||strstr(names[i].name,"PAD"))||!strncmp(p,"to ",3)||!strncmp(p,"again",5)||!strncmp(p,"button",6);
  if(!explicit64){static const char*verbs[]={"PRESS ","HOLD ","TAP ","Press ","press ","Hold ","hold ","Tap ","tap ","Release ","release ","with ","using "};
   for(unsigned k=0;k<sizeof(verbs)/sizeof(*verbs);k++){size_t v=strlen(verbs[k]);if((size_t)(s-begin)>=v&&!strncmp(s-v,verbs[k],v)){explicit64=1;break;}}
   /* End of a slash-separated controller group, including A/B and LB / RB. */
   const char*q=s;while(q>begin&&q[-1]==' ')q--;if(q>begin&&q[-1]=='/'&&(!*p||*p==')'||*p==','||*p=='.'))explicit64=1;
  }
  if(explicit64){*length=n;return(int)names[i].icon;}
 }
 return-1;
}
#endif
