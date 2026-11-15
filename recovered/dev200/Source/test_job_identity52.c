/* Actual masks used by skill and audio ownership; exercise the 32-bit boundary. */
#include <assert.h>
#include <stdio.h>
#include "job_identity52.h"
int main(void){
 for(unsigned j=0;j<J52_COUNT;j++){assert(job_valid52(j));ClassMask52 bit=job_bit52(j);assert(bit&&job_mask_has52(bit,j));for(unsigned k=0;k<J52_COUNT;k++)assert(job_mask_has52(bit,k)==(j==k));
  if(j>=21){assert(job_parent52(j)<21);assert(job_mask_inherits52(job_bit52(job_parent52(j)),j));assert(job_transcendent52(j));}}
 assert(job_bit52(31)==UINT64_C(0x80000000));assert(job_bit52(32)==UINT64_C(0x100000000));assert(job_bit52(39)==UINT64_C(0x8000000000));assert(!job_bit52(64)&&!job_bit52(~0u));assert(!job_mask_has52(~UINT64_C(0),J52_COUNT));
 assert(job_source52(8)==4010&&job_source52(J52_HIGH_PRIEST)==4009&&job_source52(J52_CREATOR)==4019);assert(job_parent52(J52_HIGH_NOVICE)==0);assert(!job_transcendent52(0)&&job_transcendent52(8));
 puts("PASS40 stable/planned job identities, exact source IDs, parent inheritance and safe64-bit masks through bit39; invalid shifts rejected.");
}
