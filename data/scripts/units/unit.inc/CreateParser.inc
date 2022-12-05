section.begin
   Name = CreateParser
   UsedFileName = 
   Code : struct.begin
      [*] = ;var myHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var pMyParser : Integer = ParserCreateGameObject(myHandle);
      [*] = ;
      [*] = ;var unitID : Integer = GetIntValueByIndex(gc_stack_unit_iUnitID);
      [*] = ;ParserSetIntValueByKeyByHandle(pMyParser, 'UnitID', unitID);
      [*] = ;
      [*] = ;ParserAddChildByIndex(pMyParser, 'Upgrades');
      [*] = ;ParserAddChildByIndex(pMyParser, 'Medals');
      [*] = ;ParserAddChildByIndex(pMyParser, 'Spells');
      [*] = ;ParserAddChildByIndex(pMyParser, 'KnownSpells');
      [*] = ;ParserAddChildByIndex(pMyParser, 'Skills');
      [*] = ;ParserAddChildByIndex(pMyParser, 'Effects');
      [*] = ;ParserAddChildByIndex(pMyParser, 'Neighbours');
      [*] = ;ParserSetIntValueByKeyByHandle(pMyParser, 'BattleX', 0);
      [*] = ;ParserSetIntValueByKeyByHandle(pMyParser, 'BattleY', 0);
      [*] = ;
      [*] = ;var pMyActions : Integer = ParserAddChildByIndex(pMyParser, 'Actions');
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;for i := 0 to 6 do
      [*] = ;begin
      [*] = ;   var pAction : Integer = ParserAddChildByIndex(pMyActions, '*');
      [*] = ;   ParserSetIntValueByKeyByHandle(pAction, 'Value', 0);
      [*] = ;end;
      [*] = ;
      [*] = ;ParserAddChildByIndex(pMyParser, 'KnownAbilities');
      [*] = ;var pMyAbilities : Integer = ParserAddChildByIndex(pMyParser, 'Abilities');
      [*] = ;
      [*] = ;for i := 0 to 200 do
      [*] = ;begin
      [*] = ;   var pMyAbility : Integer = ParserAddChildByIndex(pMyAbilities, '*');
      [*] = ;   ParserSetIntValueByKeyByHandle(pMyAbility, 'AbilityID', i);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMyAbility, 'Value', 0);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMyAbility, 'Hero', 0);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMyAbility, 'Squad', 0);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMyAbility, 'Inventory', 0);
      [*] = ;end;
      [*] = ;
      [*] = ;var pMyHeroAbilities : Integer = ParserAddChildByIndex(pMyParser, 'HeroAbilities');
      [*] = ;
      [*] = ;for i := 0 to 99 do
      [*] = ;begin
      [*] = ;   var pMyHeroAbility : Integer = ParserAddChildByIndex(pMyHeroAbilities, '*');
      [*] = ;   ParserSetIntValueByKeyByHandle(pMyHeroAbility, 'AbilityID', 900 + i);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMyHeroAbility, 'Value', 0);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMyHeroAbility, 'Hero', 0);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMyHeroAbility, 'Squad', 0);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMyHeroAbility, 'Inventory', 0);
      [*] = ;end;
      [*] = ;
      [*] = ;var pMySpellAbilities : Integer = ParserAddChildByIndex(pMyParser, 'SpellAbilities');
      [*] = ;
      [*] = ;for i := 0 to gPrototypeData.spells.number-1 do
      [*] = ;begin
      [*] = ;   var pMySpellAbility : Integer = ParserAddChildByIndex(pMySpellAbilities, '*');
      [*] = ;   ParserSetIntValueByKeyByHandle(pMySpellAbility, 'AbilityID', 2000 + i);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMySpellAbility, 'Value', 0);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMySpellAbility, 'Hero', 0);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMySpellAbility, 'Squad', 0);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMySpellAbility, 'Inventory', 0);
      [*] = ;end;
      [*] = ;
      [*] = ;var pMyAttackList : Integer = ParserAddChildByIndex(pMyParser, 'AttackList');
      [*] = ;var pMyAttackAnimList : Integer = ParserAddChildByIndex(pMyParser, 'AttackAnimList');
      [*] = ;var pRoundTargets : Integer = ParserAddChildByIndex(pMyParser, 'RoundTargets');
      [*] = ;var pChangedParams : Integer = ParserAddChildByIndex(pMyParser, 'ChangedParams');
      [*] = ;
      [*] = ;ParserSetIntValueByKeyByHandle(pMyParser, 'BerserkUID', 0);
      [*] = ;
      [*] = ;var pLanUnitSyncs : Integer = ParserAddChildByIndex(pMyParser, 'LanUnitSyncs');
      [*] = ;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

