unsigned rank=party_skill_rank193(m,440);

assert(
 party_caster_cost194(m,440,rank)==
 party_skill_cost200(440,rank)-
 party_skill_cost200(440,rank)*
 7*party_skill_rank193(m,437)/100
);
