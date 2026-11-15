/* MIT. One open original script trader, reusing the established shop window. */
#ifndef MYRO_CORE_TRADER_STATE180_H
#define MYRO_CORE_TRADER_STATE180_H
static CoreNpc53 coreTrader180;static unsigned(*coreTraderStock180)[2];static unsigned coreTraderRows180;
static void core_trader_clear180(void){free(coreTraderStock180);coreTraderStock180=NULL;coreTraderRows180=0;memset(&coreTrader180,0,sizeof(coreTrader180));}
static const CoreNpc53*core_descriptor180(int id){return id==(int)CORE_NPC_COUNT53?&coreTrader180:coreNpcs53+id;}
static const unsigned*core_stock180(unsigned index){unsigned base=sizeof(coreStock53)/sizeof(*coreStock53);static const unsigned empty[2]={0};if(index<base)return coreStock53[index];index-=base;return index<coreTraderRows180?coreTraderStock180[index]:empty;}
#endif
