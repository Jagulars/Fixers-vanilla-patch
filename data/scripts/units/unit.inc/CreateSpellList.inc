section.begin
   Name = CreateSpellList
   UsedFileName = 
   Code : struct.begin
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;
      [*] = ;var isHero : Boolean = GetGameObjectMyBoolValueInd(gc_stack_unit_bIsHero);
      [*] = ;
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;var pMySpells : Integer = ParserSelectByHandleByKey(pMyParser, 'Spells');
      [*] = ;ParserClearByHandle(pMySpells);
      [*] = ;var pKnownSpells : Integer = ParserSelectByHandleByKey(pMyParser, 'KnownSpells');
      [*] = ;ParserClearByHandle(pKnownSpells);
      [*] = ;      
      [*] = ;var i, j, k : Integer;
      [*] = ;
      [*] = ;procedure AddKnownSpell(spellID : Integer);
      [*] = ;begin
      [*] = ;   var count : Integer = ParserGetCountByHandle(pKnownSpells);
      [*] = ;   if count > 0 then
      [*] = ;   begin
      [*] = ;      for k := 0 to count do
      [*] = ;      begin
      [*] = ;         if ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pKnownSpells, k), 'SpellID') = spellID then
      [*] = ;            exit
      [*] = ;         else
      [*] = ;         if k = count-1 then
      [*] = ;            ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pKnownSpells, '*'), 'SpellID', spellID);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pKnownSpells, '*'), 'SpellID', spellID);
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;if isHero then
      [*] = ;begin
      [*] = ;   var uid : Integer = GetGameObjectIntValueIndByHandle(myGOHandle, gc_stack_unit_iHeroUID);
      [*] = ;   var mapHeroHandle : Integer = GetGameObjectHandleByUniqueId(uid);
      [*] = ;   var pMapHeroParser : Integer = ParserSelectGameObject(mapHeroHandle);
      [*] = ;
      [*] = ;   //var pUnitParser : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iParserHandle);
      [*] = ;   var pUnitSpells : Integer = ParserSelectByHandleByKey(pMapHeroParser, 'Spells');
      [*] = ;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pUnitSpells)-1 do
      [*] = ;   begin
      [*] = ;      var pUnitSpell : Integer = ParserSelectByHandleByIndex(pUnitSpells, i);
      [*] = ;      var spellID : Integer = ParserGetIntValueByKeyByHandle(pUnitSpell, 'SpellID');
      [*] = ;      var slotLevel : Integer = ParserGetIntValueByKeyByHandle(pUnitSpell, 'SlotLevel');
      [*] = ;      var slotIndex : Integer = ParserGetIntValueByKeyByHandle(pUnitSpell, 'SlotIndex');
      [*] = ;
      [*] = ;      var pMySpell : Integer = ParserAddChildByIndex(pMySpells, '*');
      [*] = ;      ParserSetIntValueByKeyByHandle(pMySpell, 'SpellID', spellID);
      [*] = ;      ParserSetIntValueByKeyByHandle(pMySpell, 'SlotLevel', slotLevel);
      [*] = ;      ParserSetIntValueByKeyByHandle(pMySpell, 'SlotIndex', slotIndex);
      [*] = ;      ParserSetIntValueByKeyByHandle(pMySpell, 'Ammo', 0);
      [*] = ;      ParserSetBoolValueByKeyByHandle(pMySpell, 'Used', false);
      [*] = ;      AddKnownSpell(spellID);
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   var pMyUpgrades : Integer = ParserSelectByHandleByKey(pMyParser, 'Upgrades');
      [*] = ;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pMyUpgrades)-1 do
      [*] = ;   begin
      [*] = ;      var pMyUpgrade : Integer = ParserSelectByHandleByIndex(pMyUpgrades, i);
      [*] = ;      var upgradeID : Integer = ParserGetIntValueByKeyByHandle(pMyUpgrade, 'UpgradeID');
      [*] = ;
      [*] = ;      var pUpgrade : Integer = _unit_GetUpgradeParserByID(upgradeID);
      [*] = ;
      [*] = ;      var pUpgUpgrades : Integer = ParserSelectByHandleByKey(pUpgrade, 'Upgrades');
      [*] = ;      for j := 0 to ParserGetCountByHandle(pUpgUpgrades)-1 do
      [*] = ;      begin
      [*] = ;         var pUpgUpgrade : Integer = ParserSelectByHandleByIndex(pUpgUpgrades, j);
      [*] = ;         var abilID : Integer = ParserGetIntValueByKeyByHandle(pUpgUpgrade, 'AbilityID');
      [*] = ;
      [*] = ;         if abilID > 2000 then
      [*] = ;         begin
      [*] = ;            var quantity : Integer = ParserGetIntValueByKeyByHandle(pUpgUpgrade, 'Quantity');
      [*] = ;            var spellID : Integer = abilID - 2000;
      [*] = ;
      [*] = ;            var pMySpell : Integer = ParserAddChildByIndex(pMySpells, '*');
      [*] = ;            ParserSetIntValueByKeyByHandle(pMySpell, 'SpellID', spellID);
      [*] = ;            ParserSetIntValueByKeyByHandle(pMySpell, 'Ammo', quantity);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pMySpell, 'Used', false);
      [*] = ;            AddKnownSpell(spellID);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

