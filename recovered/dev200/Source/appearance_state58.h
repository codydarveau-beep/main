/* Persistent appearance; zero remains the original style/colour for old saves. */
#ifndef MYRO_APPEARANCE_STATE58_H
#define MYRO_APPEARANCE_STATE58_H
typedef struct{unsigned hair,colour,cloth;}Appearance58;
static int appearance_valid58(Appearance58 a){return a.hair<42&&a.colour<9&&a.cloth<5;}
static int appearance_equal58(Appearance58 a,Appearance58 b){return a.hair==b.hair&&a.colour==b.colour&&a.cloth==b.cloth;}
#endif
