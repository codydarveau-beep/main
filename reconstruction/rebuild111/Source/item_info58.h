/* Original item descriptions plus catalog facts; inspection never changes inventory. */
#ifndef MYRO_ITEM_INFO58_H
#define MYRO_ITEM_INFO58_H
static int item_info_build58(int id,int identified,char*out,size_t bytes){if(!out||!bytes||id<0||id>=ITEM_COUNT)return 0;const ItemDef*d=itemDefs+id;const OwnedRule52*r=item_rule52(d->id);if(!identified&&r&&owned_gear52(r)){snprintf(out,bytes,"Unidentified equipment\n\nIdentify this item to reveal its name and properties.");return 1;}const char*type=r&&r->kind==OWNED_CARD52?"Card":r&&owned_gear52(r)?"Equipment":"Item";snprintf(out,bytes,"%s\n%s\n\n%s\n\nWeight: %u.%u",d->name,type,d->description&&strcmp(d->description,d->name)?d->description:"No original description was supplied for this item.",r?r->weight/10:0,r?r->weight%10:0);return 1;}
#endif
