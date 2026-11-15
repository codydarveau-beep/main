/* Source test used actual prepared companions and the actual combat tick. */

campaign_battle_tick200(&g,.05f,0);

assert(m->pendingSkill);
assert(party_caster_spell194(m->pendingSkill));
assert(m->castUntil>=g.time);
assert(m->sp==sp); /* Not paid at cast initiation. */

assert(party_hurt200(&g,m,1));
assert(!m->pendingSkill);
assert(m->sp==sp); /* Interrupted before completion: no SP debit. */
