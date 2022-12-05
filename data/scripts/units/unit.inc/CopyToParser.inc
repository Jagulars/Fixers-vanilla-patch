section.begin
   Name = CopyToParser
   UsedFileName = 
   Code : struct.begin
      [*] = ;var myHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myHandle);
      [*] = ;
      [*] = ;var aMode : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_battle_PLStack_iAttackMode);
      [*] = ;var pArmyUnits : Integer;
      [*] = ;
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
      [*] = ;var mapHeroUID : Integer = GetGameObjectIntValueIndByHandle(heroHandle, gc_stack_unit_iHeroUID);
      [*] = ;var mapHeroHandle : Integer = GetGameObjectHandleByUniqueId(mapHeroUID);
      [*] = ;
      [*] = ;var myCustomName : String = GetGameObjectCustomNameByHandle(myHandle);
      [*] = ;var isHero : Boolean = GetGameObjectBoolValueIndByHandle(myHandle, gc_stack_unit_bIsHero);
      [*] = ;//var pUnitParser : Integer = GetGameObjectIntValueIndByHandle(myHandle, gc_stack_unit_iParserHandle);
      [*] = ;var armyInd : Integer = GetGameObjectIntValueIndByHandle(myHandle, gc_stack_unit_iArmyIndex);
      [*] = ;var pUnitParser : Integer = ParserSelectByHandleByIndex(pArmyUnits, armyInd);
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myHandle);
      [*] = ;
      [*] = ;_log_map('Execute CopyToParser for ' + myCustomName);
      [*] = ;
      [*] = ;//if (not isHero) and (not GetGameObjectPlayableObjectByHandle(myHandle)) then
      [*] = ;//ParserClearByHandle(pUnitParser)
      [*] = ;//else
      [*] = ;begin
      [*] = ;   var unitID : Integer = GetGameObjectIntValueIndByHandle(myHandle, gc_stack_unit_iUnitID);
      [*] = ;   var curLife : Integer = GetGameObjectIntValueIndByHandle(myHandle, gc_stack_unit_iCurLife);
      [*] = ;   var curMoral : Integer = GetGameObjectIntValueIndByHandle(myHandle, gc_stack_unit_iCurMoral);
      [*] = ;   var exp : Integer = GetGameObjectIntValueIndByHandle(myHandle, gc_stack_unit_iExperience);
      [*] = ;   var level : Integer = GetGameObjectIntValueIndByHandle(myHandle, gc_stack_unit_iLevel);
      [*] = ;
      [*] = ;   // modify unit life
      [*] = ;   var lifeMod : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_battle_PLStack_iLifeMod);
      [*] = ;
      [*] = ;   IntRegister0 := gc_battle_unit_iMaxLife;
      [*] = ;   ExecuteState('GetProperty');
      [*] = ;   var maxLife : Integer = IntRegister1;
      [*] = ;   var fMaxLife : Float = FloatRegister0;
      [*] = ;   
      [*] = ;   var bonus : Integer = 0;
      [*] = ;
      [*] = ;   if (heroHandle <> 0) and (not isHero) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := myHandle;
      [*] = ;      IntRegister1 := 0;
      [*] = ;      IntRegister2 := mapHeroHandle;
      [*] = ;      IntRegister3 := 1;
      [*] = ;      MapExecuteState('CalcUnitHeroBonus');
      [*] = ;      bonus := IntRegister4;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //Heroes[j]->pSquad[i]->iLife=Squad[j][i].iLife*100/LifeMod[j]-Heroes[j]->CheckUnitBonus(1)*(100-(Squad[j][i].GetLife()-Squad[j][i].iLife)*100/Squad[j][i].GetLife())/100;
      [*] = ;   var fCurLife : Float = curLife * 100 / lifeMod - bonus * (100 - (maxLife - curLife) * 100 / maxLife) / 100;
      [*] = ;   var newLife : Integer = Floor(fCurLife);
      [*] = ;   if (curLife > 0) and (newLife <= 0) then
      [*] = ;   begin
      [*] = ;      newLife := 1;
      [*] = ;      fCurLife := 1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   IntRegister0 := pUnitParser;
      [*] = ;   IntRegister1 := pArmyUnits;
      [*] = ;   IntRegister2 := gc_battle_unit_iMaxMoral;
      [*] = ;   StateMachineExecuteState(initMachine, 'GetUnitPropertyByParser', 0);
      [*] = ;   var maxMoral : Integer = IntRegister3;
      [*] = ;
      [*] = ;   if _unit_CheckAbility(myHandle, gc_ability_fearless) = 0 then
      [*] = ;   begin
      [*] = ;      curMoral := curMoral - GetPlayerIntValueIndByHandle(myPlHandle, gc_battle_PLStack_iMoralBonus);
      [*] = ;
      [*] = ;      if curMoral - maxMoral > 10 then
      [*] = ;      curMoral := maxMoral + 10;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var f : Float = (maxLife * 100 / lifeMod);
      [*] = ;   maxLife := Round(fmaxLife * 100 / lifeMod);
      [*] = ;
      [*] = ;   if newLife > maxLife then
      [*] = ;   newLife := maxLife;
      [*] = ;   if fCurLife > maxLife then
      [*] = ;   fCurLife := maxLife;
      [*] = ;
      [*] = ;   var oldMoral : Integer = ParserGetIntValueByKeyByHandle(pUnitParser, 'CurMoral');
      [*] = ;   ParserSetIntValueByKeyByHandle(pUnitParser, 'UnitID', unitID);
      [*] = ;   ParserSetIntValueByKeyByHandle(pUnitParser, 'CurLife', newLife);
      [*] = ;   ParserSetFloatValueByKeyByHandle(pUnitParser, 'FCurLife', fCurLife);
      [*] = ;   ParserSetFloatValueByKeyByHandle(pUnitParser, 'LifeRatio', newLife / maxLife);
      [*] = ;   ParserSetIntValueByKeyByHandle(pUnitParser, 'CurMoral', curMoral);
      [*] = ;   ParserSetIntValueByKeyByHandle(pUnitParser, 'OldMoral', oldMoral);
      [*] = ;   ParserSetIntValueByKeyByHandle(pUnitParser, 'MoralMod', 2 * (curMoral - maxMoral));
      [*] = ;   ParserSetIntValueByKeyByHandle(pUnitParser, 'Exp', exp);
      [*] = ;   ParserSetIntValueByKeyByHandle(pUnitParser, 'Level', level);
      [*] = ;
      [*] = ;   if isHero and (not gBoolRegister_BattleSimulate) then
      [*] = ;   begin
      [*] = ;      // increase item durability for the battle to account for item maintenance skill.
      [*] = ;      var itemMaintenace : Integer = _unit_CheckAbility(myHandle, gc_ability_item_maintenance);
      [*] = ;      if (itemMaintenace > 0) and (itemMaintenace < 100) then
      [*] = ;      begin
      [*] = ;         var pDoll : Integer = ParserSelectByHandleByKey(ParserSelectGameObject(mapHeroHandle), 'Doll');
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
      [*] = ;               durability := Floor(itemDur / (100 / (100-itemMaintenace)));
      [*] = ;               ParserSetIntValueByKeyByHandle(pDollSlot, 'Durability', durability);
      [*] = ;               //_log_map('Item Maintenance adjustment: Item ID '+IntToStr(itemID)+', Durability set as '+IntToStr(durability));
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   // start position
      [*] = ;   var battleX : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iBattleX);
      [*] = ;   var battleY : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iBattleY);
      [*] = ;
      [*] = ;   if battleX >= 6 then
      [*] = ;   battleX := 7 - battleX;
      [*] = ;
      [*] = ;   ParserSetIntValueByKeyByHandle(pUnitParser, 'BattleX', battleX);
      [*] = ;   ParserSetIntValueByKeyByHandle(pUnitParser, 'BattleY', battleY);
      [*] = ;
      [*] = ;   // upgrades
      [*] = ;   var pMyUpgrades : Integer = ParserSelectByHandleByKey(pMyParser, 'Upgrades');
      [*] = ;   var pUnitUpgrades : Integer = ParserSelectByHandleByKey(pUnitParser, 'Upgrades');
      [*] = ;   ParserCopyFromByHandle(pMyUpgrades);
      [*] = ;
      [*] = ;   // medals
      [*] = ;   var pMyMedals : Integer = ParserSelectByHandleByKey(pMyParser, 'Medals');
      [*] = ;   var pUnitMedals : Integer = ParserSelectByHandleByKey(pUnitParser, 'Medals');
      [*] = ;   ParserCopyFromByHandle(pMyMedals);
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

