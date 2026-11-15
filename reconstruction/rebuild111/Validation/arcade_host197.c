/* HOST ONLY: execute the exact recovered native source via Unicorn.
 * This adapter is not compiled into the Xbox executable. */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unicorn/unicorn.h>
#include <unicorn/x86.h>
#include "arcade_host_symbols197.h"
static uc_engine*cpu197;
static void close197(void){if(cpu197)uc_close(cpu197);cpu197=NULL;}
static uint32_t u32(const unsigned char*p){return p[0]|(uint32_t)p[1]<<8|(uint32_t)p[2]<<16|(uint32_t)p[3]<<24;}
static uint16_t u16(const unsigned char*p){return p[0]|(uint16_t)p[1]<<8;}
static void init197(void){assert(uc_open(UC_ARCH_X86,UC_MODE_32,&cpu197)==UC_ERR_OK);FILE*f=fopen(ARCADE_HOST_ELF197,"rb");assert(f);assert(!fseek(f,0,SEEK_END));long n=ftell(f);rewind(f);unsigned char*p=malloc((size_t)n);assert(p&&fread(p,1,n,f)==(size_t)n);fclose(f);
 unsigned off=u32(p+28),size=u16(p+42),count=u16(p+44);for(unsigned i=0;i<count;i++){unsigned char*s=p+off+i*size;if(u32(s)!=1)continue;unsigned va=u32(s+8),bytes=u32(s+20);for(unsigned at=va&~4095u;at<((va+bytes+4095)&~4095u);at+=4096){uc_err e=uc_mem_map(cpu197,at,4096,UC_PROT_ALL);assert(e==UC_ERR_OK||e==UC_ERR_MAP);}assert(uc_mem_write(cpu197,va,p+u32(s+4),u32(s+16))==UC_ERR_OK);}free(p);assert(uc_mem_map(cpu197,0x2000000,0x20000,UC_PROT_ALL)==UC_ERR_OK);assert(uc_mem_map(cpu197,0x1000000,4096,UC_PROT_ALL)==UC_ERR_OK);unsigned cr4=0x200;assert(uc_reg_write(cpu197,UC_X86_REG_CR4,&cr4)==UC_ERR_OK);atexit(close197);}
void arcade_host197(unsigned operation,void*state,unsigned argument,float dt){if(!cpu197)init197();unsigned function=operation==0?HOST_ARCADE197_RESET:operation==1?HOST_ARCADE197_INPUT:HOST_ARCADE197_TICK;unsigned sp=0x2010000,args[3]={0x1000000,argument,0};if(!operation){args[1]=*(unsigned*)state;args[2]=argument;}else if(operation==2)memcpy(args+2,&dt,4);assert(uc_mem_write(cpu197,HOST_ARCADE197_STATE,state,1804)==UC_ERR_OK);assert(uc_mem_write(cpu197,sp,args,sizeof args)==UC_ERR_OK);assert(uc_reg_write(cpu197,UC_X86_REG_ESP,&sp)==UC_ERR_OK);assert(uc_emu_start(cpu197,function,0x1000000,0,1000000)==UC_ERR_OK);unsigned pc;assert(uc_reg_read(cpu197,UC_X86_REG_EIP,&pc)==UC_ERR_OK&&pc==0x1000000);assert(uc_mem_read(cpu197,HOST_ARCADE197_STATE,state,1804)==UC_ERR_OK);}
