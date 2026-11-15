/* MIT. Original solo service dependencies, with persisted character variables. */
#ifndef MYRO_NPC_SOLO_SERVICES180_H
#define MYRO_NPC_SOLO_SERVICES180_H
static NpcState55*npc_character_state180(NpcGame55*g){NpcVariables55*v=&g->vm[0].variables;return(v->shared?v->shared:v->domain)+N55_VAR_CHARACTER;}
static void npc_carry_sync180(NpcGame55*g){int64_t rank=npc_state_number55(npc_character_state180(g),npc_variable_key55("gympassmemory",0),0);g->player.game->carryTraining180=rank<0?0:rank>10?10:(unsigned)rank;}
static int npc_merge_items180(Combat*g){OwnedItems52*b=malloc(sizeof(*b));if(!b)return 0;*b=g->owned52;if(!owned_valid52(b,item_rule52)){free(b);return 0;}for(unsigned i=0;i<b->count[0];i++){OwnedItem52*a=b->items+i;const OwnedRule52*r=item_rule52(a->sourceID);if(!r||owned_gear52(r)||a->equipped||r->stackLimit<=1)continue;for(unsigned j=i+1;j<b->count[0]&&a->quantity<r->stackLimit;j++){OwnedItem52*c=b->items+j;if(c->sourceID!=a->sourceID||c->equipped||c->identified!=a->identified||c->bound!=a->bound||c->flags!=a->flags||c->refine!=a->refine||memcmp(c->cards,a->cards,sizeof(a->cards)))continue;unsigned n=r->stackLimit-a->quantity;if(n>c->quantity)n=c->quantity;a->quantity+=n;c->quantity-=n;}}inventory_compact52(b);int ok=owned_valid52(b,item_rule52);if(ok)g->owned52=*b;free(b);return ok;}
static int npc_solo_service_command180(NpcGame55*g,NpcRuntime55*r,NpcMachine55*m,const char*name,const NpcValue55*args,unsigned count,NpcValue55*out){
 *out=npc_vm_number55(0);
 if(!strcmp(name,"mergeitem")){if(count||!r->attached)return N55_ERROR;return npc_merge_items180(g->player.game)?N55_READY:N55_ERROR;}
 /* The source NPC explicitly provides its classic dialogue workflow when this returns false. */
 if(!strcmp(name,"openrefineryui")){if(count||!r->attached)return N55_ERROR;return N55_READY;}
 /* Alora uses a single string conversion to extract a headgear colour.
    A literal mismatch after that conversion still returns one assignment,
    following scanf semantics. No source-controlled format reaches libc. */
 if(!strcmp(name,"sscanf")){NpcValue55 text,format;if(count!=3||!npc_vm_value55(m,args[0],&text)||text.kind!=N55_STRING_KIND||!npc_vm_value55(m,args[1],&format)||format.kind!=N55_STRING_KIND||strncmp(format.text,"%s",2)||strchr(format.text+2,'%')||args[2].kind!=N55_REFERENCE_KIND||!m->api.write)return N55_ERROR;const char*start=text.text;while(*start==' '||*start=='\t'||*start=='\n'||*start=='\r')start++;unsigned n=0;while(start[n]&&start[n]!=' '&&start[n]!='\t'&&start[n]!='\r'&&start[n]!='\n')n++;if(!n)return N55_READY;if(n>=128)return N55_ERROR;char token[128];memcpy(token,start,n);token[n]=0;NpcValue55 value=npc_vm_string55(token);if(!m->api.write(m->api.context,args+2,&value))return N55_ERROR;*out=npc_vm_number55(1);return N55_READY;}
 return-1;
}
#endif
