/* Retained doors and room predicates; source geometry alias independently recovered. */
#ifndef MYRO_GUILD_LAYOUT194_H
#define MYRO_GUILD_LAYOUT194_H
#define GUILD_MAP194 494u
#define GUILD_PROPS_MAX194 48u

typedef struct{
 unsigned model;
 float x,y,angle,scale;
 unsigned solid;
}GuildProp194;

typedef struct{
 float x,y;
 unsigned map;
 float toX,toY;
 unsigned any;
 const char*label;
}GuildDoor194;

static const GuildDoor194 guildDoors194[]={
 {192,1324,132,188,1116,0,"return to Alberta"},
 {268,1408,GUILD_MAP194,192,848,2,"enter the common room"},
 {192,864,GUILD_MAP194,244,1408,0,"return to the entrance room"},
 {300,720,GUILD_MAP194,784,800,12,"visit the library / workshop"},
 {784,832,GUILD_MAP194,276,720,0,"return to the common room"},
 {300,800,GUILD_MAP194,1340,1376,32,"visit the arcade annex"},
 {1340,1392,GUILD_MAP194,276,800,0,"return to the common room"},
 {192,620,GUILD_MAP194,192,588,16,"enter the great hall"}
};

static int guild_room_ready194(unsigned built,float x,float y){
 if(x>=96&&x<288&&y>=1312&&y<1504)
  return 1;

 if(x>=64&&x<320&&y>=272&&y<880)
  return (built&2)&&(y>=608||(built&16));

 if(x>=720&&x<848&&y>=272&&y<848)
  return (built&12)!=0;

 if(x>=1280&&x<1408&&y>=112&&y<1440)
  return (built&32)!=0;

 return 0;
}

#endif
