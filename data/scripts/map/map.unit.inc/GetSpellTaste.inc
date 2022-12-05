section.begin
   Name = GetSpellTaste
   Description : struct.begin
      [*] = ;IntRegister0 - spell ID
      [*] = ;OUT: spell taste
   struct.end
   UsedFileName = 
   Code : struct.begin
      [*] = ;var spellID : Integer = IntRegister0;
      [*] = ;var initMachine : Integer = GetMapInitMachineHandle;
      [*] = ;
      [*] = ;var myHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myClass1 : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iClassInd1);
      [*] = ;var myLevel : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iLevel);
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myHandle);
      [*] = ;var plKarma : Integer = _map_GetPlayerKarma(myPlHandle);
      [*] = ;
      [*] = ;IntRegister0 := spellID;
      [*] = ;StateMachineExecuteState(initMachine, 'GetSpellParserByID', 0);
      [*] = ;var pSpell : Integer = IntRegister1;
      [*] = ;
      [*] = ;var durationMod : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'DurationMod');
      [*] = ;var powerMod : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'PowerMod');
      [*] = ;var area : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Area');
      [*] = ;var target : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Target');
      [*] = ;var radius : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Radius');
      [*] = ;var spKarma : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Karma');
      [*] = ;
      [*] = ;var taste : Integer = 3;
      [*] = ;
      [*] = ;IntRegister0 := gc_ability_spell_duration;
      [*] = ;ExecuteState('CheckAbility');
      [*] = ;taste := taste + (IntRegister1 * durationMod) div 100;
      [*] = ;
      [*] = ;var pSpellEffects : Integer = ParserSelectByHandleByKey(pSpell, 'Effects');
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;for i := ParserGetCountByHandle(pSpellEffects)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pSpellEffect : Integer = ParserSelectByHandleByIndex(pSpellEffects, i);
      [*] = ;   var abilID : Integer = ParserGetIntValueByKeyByHandle(pSpellEffect, 'AbilityID');
      [*] = ;
      [*] = ;   if abilID = 1 then
      [*] = ;   begin
      [*] = ;      var bonus : Integer = ParserGetIntValueByKeyByHandle(pSpellEffect, 'Power');
      [*] = ;
      [*] = ;      IntRegister0 := gc_ability_spell_power;
      [*] = ;      ExecuteState('CheckAbility');
      [*] = ;      var abil905 : Integer = IntRegister1;
      [*] = ;
      [*] = ;      IntRegister0 := gc_ability_resistance_overrule;
      [*] = ;      ExecuteState('CheckAbility');
      [*] = ;      var abil908 : Integer = IntRegister1;
      [*] = ;
      [*] = ;      bonus := bonus + (abil905 * powerMod) div 100 + abil908 div 2;
      [*] = ;
      [*] = ;      if (area = 2) and (target = 0) then
      [*] = ;      bonus := bonus * 8;
      [*] = ;      if (area = 1) and (target = 3) then
      [*] = ;      bonus := bonus * (1 + radius * 3);
      [*] = ;
      [*] = ;      var pUnitTypes : Integer = ParserSelectByHandleByKey(pSpell, 'UnitTypes');
      [*] = ;      var count : Integer = ParserGetCountByHandle(pUnitTypes);
      [*] = ;      var maxCount : Integer = gPrototypeData.unitTypes.number-1;
      [*] = ;      bonus := (bonus * (maxCount - count)) div maxCount;
      [*] = ;
      [*] = ;      taste := taste + bonus div 2;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if abilID > 1000 then
      [*] = ;   begin
      [*] = ;      var unitID : Integer = abilID - 1000;
      [*] = ;      var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;
      [*] = ;      IntRegister0 := unitID;
      [*] = ;      StateMachineExecuteState(initMachine, 'GetUnitPowerByID', 0);
      [*] = ;      var bonus : Integer = IntRegister1;
      [*] = ;
      [*] = ;      IntRegister0 := gc_ability_summoning_power;
      [*] = ;      ExecuteState('CheckAbility');
      [*] = ;      var level : Integer = 2 * IntRegister1;
      [*] = ;
      [*] = ;      var unitType : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'UnitType');
      [*] = ;      if unitType = 2 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := gc_ability_necro_summoning_power;
      [*] = ;         ExecuteState('CheckAbility');
      [*] = ;         var abil909 : Integer = IntRegister1;
      [*] = ;         level := level + abil909;
      [*] = ;
      [*] = ;         var unitRank : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Rank');
      [*] = ;         if unitRank < abil909 then
      [*] = ;         bonus := bonus * 3;
      [*] = ;      end;
      [*] = ;
      [*] = ;      bonus := bonus + ((bonus * level) div 10);
      [*] = ;      taste := taste + bonus div 10;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (myClass1 = 4) and (spellID = 4) and (myLevel < 10) then
      [*] = ;taste := taste + (15 - myLevel) * 3;
      [*] = ;if (myClass1 = 1) and (spellID = 17) then
      [*] = ;taste := taste + 20;
      [*] = ;
      [*] = ;if gGame.improvedai or (gProfile.improvedai and (gGame.gameType <> gc_GameTypeLanShard)) then
      [*] = ;begin
      [*] = ;   spKarma := Min(Max(spKarma, -1), 1);
      [*] = ;   taste := taste + Max(0, taste) * spKarma * plKarma div 100;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister1 := taste;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

