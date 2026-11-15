/* Only implemented solo actions pass this gate. */
#ifndef MYRO_EXPANDED_MECHANICS60_H
#define MYRO_EXPANDED_MECHANICS60_H
static int expanded_mechanics60(unsigned id){return (id>=SK60_NJ_TOBIDOUGU&&id<=SK60_SG_KNOWLEDGE&&id!=SK60_TK_POWER&&id!=SK60_SG_FRIEND)||(id>=SK60_SL_KAIZEL&&id<=SK60_SL_SKA)||id==SK60_TK_RUN||id==SK60_TK_HIGHJUMP;}
#endif
