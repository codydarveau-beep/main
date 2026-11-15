"""Chapter2 executable dialogue definitions; physical staging is audited separately."""
def make_chapter2(say,choice,gate,end,close,join,guild):
 return [[
  say('start','Judia','That marker said something else yesterday.','weather'),
  say('weather','Nera','Weather can take paint off wood. It cannot rewrite the receipt in my pocket.','ask'),
  choice('ask','Who remembers the person?','Let us compare the records.','daughter','daughter'),
  say('daughter','Judia','His daughter does. Today. That is why I would prefer we hurry. She is safe with her family; this is not a race against a clock.','vanguard'),
  say('vanguard','Judia','You keep the search road open. I will follow the tracks.','pathfinder',1),
  say('pathfinder','Judia','Two sets of eyes. Let us see which one the liar forgot.','keeper',2),
  say('keeper','Judia','Stay with the family while we work. Tell them what we know, not what we hope.','directions',4),
  say('directions','Nera','A young man in southern Payon remembers his grandfather. Monster Scholar Vuicokk, on the northern road, studies the cave\'s dead. Ask him about Undead Monsters.','rubbing'),
  say('rubbing','Judia','Hear both accounts. Then compare the old burial register at the cave entrance. A name is easier to steal when only one copy remains.','investigate'),
  gate('investigate',7,'evidence'),
  say('evidence','Nera','The family remembers Henrik. The altered receipt says Henrich. The old record agrees with the family. Same dates. Same house. Different name.','distinction'),
  say('distinction','Judia','The dead here already have enough trouble resting. This change was made by someone living.','alberta'),
  say('alberta','Nera','The paper carries an Alberta warehouse seal. I will bring these accounts to the family. Meet Maya at the warehouse; she knows the shipping ledgers.','finish'),
  end('finish',7)
 ],[
  say('start','Maya','Relief supplies do not generally need armed guards facing inward.','veyr'),
  say('veyr','Veyr','The guards protect the records from theft. Their contents are irreplaceable.','ask'),
  choice('ask','People are irreplaceable too.','Who authorized these shipments?','people','people'),
  say('people','Veyr','Of course. Records are how we find people when the world loses them.','driver'),
  say('driver','Maya','Then your invoices should help us find the missing driver.','permission'),
  say('permission','Veyr','You may examine them. I would rather have suspicious helpers than incurious ones.','instructions'),
  say('instructions','Maya','The open dispatch ledger is beside the warehouse entrance. Compare its destination and date with the blue-cord receipt. We keep our copy; no one needs to steal the book.','ledger'),
  gate('ledger',1,'route'),
  say('route','Maya','Alberta to Geffen. Ink, medicine, and a second list of names that never appears on the freight manifest.','help'),
  say('help','Veyr','Then I shall have the duplicate sent to the Geffen relief office. Ask for the clerk who keeps the older files. They deserve care too.','thanks'),
  say('thanks','Player','Thank you. We will compare both copies.','inn'),
  say('inn','Maya','And before we collect another bill, come to the inn. We should decide who is paying which share.','finish'),
  end('finish',1)
 ],[
  say('start','Maya','If we keep sharing expenses, I require a name for the ledger.','heroic'),
  say('heroic','Roan','Something heroic.','short'),
  say('short','Judia','Something short enough to shout while running.','recognize'),
  say('recognize','Yuufa','Something the missing might recognize when we come looking.','name_choice'),
  choice('name_choice','Let us give it a name.','I need to think.','guild','later'),
  say('later','Maya','The ledger can wait. The bill has shown considerably less patience.','close'),
  close('close'),guild('guild','named'),
  say('named','Maya','{GUILD}. Good. Now it exists in two ledgers and one exceptionally untidy heart.','principle'),
  choice('principle','We make room for people who need us.','We finish what we begin.','staying','staying'),
  say('staying','Judia','Then I am staying. Someone should make sure you notice the tracks.','maya'),
  say('maya','Maya','And someone should make sure your heroic organization survives its first grocery bill. May we travel with you?','consent'),
  choice('consent','Welcome to the guild, both of you.','Let me settle a few things first.','joined','later'),
  join('joined',(1<<8)|(1<<12),'welcome'),
  say('welcome','Yuufa','A guild with a promise, a name, and an accountant. We may be dangerously close to respectable.','next'),
  say('next','Maya','Geffen is next. Its relief office has the older records. We follow the shipment, not every rumour in the kingdom.','finish'),
  end('finish',1)
 ]]
