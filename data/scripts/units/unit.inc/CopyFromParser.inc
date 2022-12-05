section.begin
   Name = CopyFromParser
   UsedFileName = 
   Code : struct.begin
      [*] = ;var myHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myHandle);
      [*] = ;
      [*] = ;var aMode : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_battle_PLStack_iAttackMode);
      [*] = ;var pArmyUnits : Integer;
      [*] = ;var armyHeroHandle : Integer;
      [*] = ;
      [*] = ;_log_map('Execute CopyFromParser for ' + GetGameObjectCustomNameByHandle(myHandle));
      [*] = ;if aMode = 1 then
      [*] = ;pArmyUnits := gIntRegister_BattleAttackArmy
      [*] = ;else
      [*] = ;pArmyUnits := gIntRegister_BattleDefendArmy;
      [*] = ;pArmyUnits := ParserSelectByHandleByKey(pArmyUnits, 'Units');
      [*] = ;
      [*] = ;var initMachine : Integer = GetMapInitMachineHandle;
      [*] = ;
      [*] = ;PlayerExecuteStateByHandle(myPlHandle, 'GetHeroHandle');
      [*] = ;var heroHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;var isHero : Boolean = GetGameObjectBoolValueIndByHandle(myHandle, gc_stack_unit_bIsHero);
      [*] = ;
      [*] = ;var heroUID : Integer = GetGameObjectIntValueIndByHandle(heroHandle, gc_stack_unit_iHeroUID);
      [*] = ;var mapHeroHandle : Integer = GetGameObjectHandleByUniqueId(heroUID);
      [*] = ;var pMapHeroParser : Integer = ParserSelectGameObject(mapHeroHandle);
      [*] = ;
      [*] = ;var pUnitParser : Integer = GetGameObjectIntValueIndByHandle(myHandle, gc_stack_unit_iParserHandle);
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myHandle);
      [*] = ;
      [*] = ;var unitID : Integer = ParserGetIntValueByKeyByHandle(pUnitParser, 'UnitID');
      [*] = ;ParserSetIntValueByKeyByHandle(pMyParser, 'UnitID', unitID);
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;
      [*] = ;if isHero then
      [*] = ;begin
      [*] = ;   var heroClass1 : Integer = ParserGetIntValueByKeyByHandle(pUnitParser, 'HeroClass1');
      [*] = ;   var heroClass2 : Integer = ParserGetIntValueByKeyByHandle(pUnitParser, 'HeroClass2');
      [*] = ;
      [*] = ;   ParserSetIntValueByKeyByHandle(pMyParser, 'HeroClass1', heroClass1);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMyParser, 'HeroClass2', heroClass2);
      [*] = ;end;
      [*] = ;
      [*] = ;// upgrades
      [*] = ;var pUnitUpgrades : Integer = ParserSelectByHandleByKey(pUnitParser, 'Upgrades');
      [*] = ;var pMyUpgrades : Integer = ParserSelectByHandleByKey(pMyParser, 'Upgrades');
      [*] = ;ParserCopyFromByHandle(pUnitUpgrades);
      [*] = ;
      [*] = ;// medals
      [*] = ;var pUnitMedals : Integer = ParserSelectByHandleByKey(pUnitParser, 'Medals');
      [*] = ;var pMyMedals : Integer = ParserSelectByHandleByKey(pMyParser, 'Medals');
      [*] = ;ParserCopyFromByHandle(pUnitMedals);
      [*] = ;
      [*] = ;var curLife : Integer = ParserGetIntValueByKeyByHandle(pUnitParser, 'CurLife');
      [*] = ;var fCurLife : Float = ParserGetFloatValueByKeyByHandle(pUnitParser, 'FCurLife');
      [*] = ;var curMoral : Integer = ParserGetIntValueByKeyByHandle(pUnitParser, 'CurMoral');
      [*] = ;
      [*] = ;SetGameObjectMyIntValueInd(gc_stack_unit_iCurLife, curLife);
      [*] = ;ExecuteState('CalcAbilities');
      [*] = ;
      [*] = ;var level : Integer = 0;
      [*] = ;var exp : Integer = 0;
      [*] = ;
      [*] = ;if isHero then
      [*] = ;begin
      [*] = ;   level := GetGameObjectIntValueIndByHandle(mapHeroHandle, gc_map_GOStack_MapUnit_iLevel);
      [*] = ;   exp := GetGameObjectIntValueIndByHandle(mapHeroHandle, gc_map_GOStack_MapUnit_iExp);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   level := ParserGetIntValueByKeyByHandle(pUnitParser, 'Level');
      [*] = ;   exp := ParserGetIntValueByKeyByHandle(pUnitParser, 'Exp');
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister0 := pUnitParser;
      [*] = ;IntRegister1 := pArmyUnits;
      [*] = ;IntRegister2 := gc_battle_unit_iMaxMoral;
      [*] = ;StateMachineExecuteState(initMachine, 'GetUnitPropertyByParser', 0);
      [*] = ;var maxMoral : Integer = IntRegister3;
      [*] = ;curMoral := maxMoral;
      [*] = ;
      [*] = ;if _unit_CheckAbility(myHandle, gc_ability_fearless) = 0 then
      [*] = ;begin
      [*] = ;   var moralMod : Integer = ParserGetIntValueByKeyByHandle(pUnitParser, 'MoralMod');
      [*] = ;   curMoral := curmoral + moralMod div 2;
      [*] = ;
      [*] = ;   curMoral := curMoral + GetPlayerIntValueIndByHandle(myPlHandle, gc_battle_PLStack_iMoralBonus);
      [*] = ;end;
      [*] = ;
      [*] = ;if curMoral < 1 then
      [*] = ;curMoral := 1;
      [*] = ;
      [*] = ;SetGameObjectIntValueIndByHandle(myHandle, gc_stack_unit_iCurMoral, curMoral);
      [*] = ;SetGameObjectIntValueIndByHandle(myHandle, gc_stack_unit_iExperience, exp);
      [*] = ;SetGameObjectIntValueIndByHandle(myHandle, gc_stack_unit_iLevel, level);
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iMaxStamina;
      [*] = ;ExecuteState('GetProperty');
      [*] = ;var maxStamina : Integer = IntRegister1;
      [*] = ;SetGameObjectIntValueIndByHandle(myHandle, gc_stack_unit_iCurStamina, maxStamina);
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iMaxAmmo;
      [*] = ;ExecuteState('GetProperty');
      [*] = ;var maxAmmo : Integer = IntRegister1;
      [*] = ;SetGameObjectIntValueIndByHandle(myHandle, gc_stack_unit_iCurAmmo, maxAmmo);
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iSpeed;
      [*] = ;ExecuteState('GetProperty');
      [*] = ;var speed : Integer = IntRegister1;
      [*] = ;SetGameObjectIntValueIndByHandle(myHandle, gc_stack_unit_iMovePoints, speed);
      [*] = ;
      [*] = ;if isHero then
      [*] = ;begin
      [*] = ;   // skills
      [*] = ;   var pUnitSkills : Integer = ParserSelectByHandleByKey(pMapHeroParser, 'Skills');
      [*] = ;   var pMySkills : Integer = ParserSelectByHandleByKey(pMyParser, 'Skills');
      [*] = ;   ParserCopyFromByHandle(pUnitSkills);
      [*] = ;   
      [*] = ;   if (not gBoolRegister_BattleSimulate) then
      [*] = ;   begin
      [*] = ;      // reduce item durability from the battle to account for item maintenance skill.
      [*] = ;      var itemMaintenace : Integer = _unit_CheckAbility(myHandle, gc_ability_item_maintenance);
      [*] = ;      if (itemMaintenace > 0) and (itemMaintenace < 100) then
      [*] = ;      begin
      [*] = ;         var pDoll : Integer = ParserSelectByHandleByKey(pMapHeroParser, 'Doll');
      [*] = ;         var i, pDollSlot, itemID, pItem, itemDur, itemSlot, durability : Integer;
      [*] = ;         var breakable : Boolean;
      [*] = ;         
      [*] = ;         for i := 0 to gc_HeroInventoryCount-1 do
      [*] = ;         begin
      [*] = ;            pDollSlot := ParserSelectByHandleByIndex(pDoll, i);
      [*] = ;            itemID := ParserGetIntValueByKeyByHandle(pDollSlot, 'ItemID');
      [*] = ;            pItem := ParserSelectByHandleByIndex(gPrototypeData.items.handle, itemID);
      [*] = ;            
      [*] = ;            itemDur := ParserGetIntValueByKeyByHandle(pDollSlot, 'Durability');
      [*] = ;            itemSlot := ParserGetIntValueByKeyByHandle(pDollSlot, 'ItemSlot');
      [*] = ;            breakable := ParserGetBoolValueByKeyByHandle(pItem, 'Breakable');
      [*] = ;
      [*] = ;            if (itemID > 0) and (itemDur > 0) and breakable and (itemSlot <> 13) then
      [*] = ;            begin
      [*] = ;               durability := _misc_RoundUp(itemDur * (100 / (100-itemMaintenace)));
      [*] = ;               ParserSetIntValueByKeyByHandle(pDollSlot, 'Durability', durability);
      [*] = ;               //_log_map('Item Maintenance adjustment: Item ID '+IntToStr(itemID)+', Durability set as '+IntToStr(durability));
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;ExecuteState('CreateSpellList');
      [*] = ;
      [*] = ;//create a list of known activateable abilities that consume a turn when used
      [*] = ;var pKnownAbilities : Integer = ParserSelectByHandleByKey(pMyParser, 'KnownAbilities');
      [*] = ;ParserClearByHandle(pKnownAbilities);
      [*] = ;var pAbilities : Integer = gPrototypeData.abilities.handle;
      [*] = ;for i := 0 to gPrototypeData.abilities.number-1 do
      [*] = ;begin
      [*] = ;   var pAbility : Integer = ParserSelectByHandleByIndex(pAbilities, i);
      [*] = ;   if ParserGetBoolValueByKeyByHandle(pAbility, 'Activate') and ParserGetBoolValueByKeyByHandle(pAbility, 'ConsumeTurn') then
      [*] = ;   begin
      [*] = ;      var abilID : Integer = ParserGetIntValueByKeyByHandle(pAbility, 'AbilityID');
      [*] = ;      if _unit_CheckAbility(myHandle, abilID) > 0 then
	  [*] = ;         ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pKnownAbilities, '*'), 'AbilityID', abilID);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;
      [*] = ;IntRegister0 := pUnitParser;
      [*] = ;IntRegister1 := 0;
      [*] = ;IntRegister2 := gc_battle_unit_iMaxLife;
      [*] = ;StateMachineExecuteState(initMachine, 'GetUnitPropertyByParser', 0);
      [*] = ;var maxLife : Integer = IntRegister3;
      [*] = ;
      [*] = ;var bonus : Integer = 0;
      [*] = ;
      [*] = ;if (heroHandle <> 0) and (not isHero) then
      [*] = ;begin
      [*] = ;   IntRegister0 := myHandle;
      [*] = ;   IntRegister1 := 0;
      [*] = ;   IntRegister2 := mapHeroHandle;
      [*] = ;   IntRegister3 := 1;
      [*] = ;   MapExecuteState('CalcUnitHeroBonus');
      [*] = ;   bonus := IntRegister4;
      [*] = ;end;
      [*] = ;
      [*] = ;// modify unit life
      [*] = ;var lifeMod : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_battle_PLStack_iLifeMod);
      [*] = ;curLife := Floor((fCurLife * lifeMod / 100 + bonus * (100 - (maxLife - fCurLife) * 100 / maxLife) / 100));
      [*] = ;
      [*] = ;if (fCurLife > 0) and (curLife = 0) then
      [*] = ;curLife := 1;
      [*] = ;
      [*] = ;SetGameObjectMyIntValueInd(gc_stack_unit_iCurLife, curLife);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

