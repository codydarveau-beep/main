/* Exact production declarations used by the host draw recorder. */
typedef struct {int slot,kind;unsigned frame;float x,y,depth,groundY;unsigned sourceFade50c;int water54;float waterline54,scale60;} DrawActor;
static int facing(float fx,float fy,float co,float si){float sx=co*fx+si*fy,sy=si*fx-co*fy;return ((int)floorf(atan2f(-sx,sy)*4/3.14159265f+.5f)+8)%8;}
