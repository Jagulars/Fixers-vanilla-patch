section.begin
   Name = GetBattleTrophies
   UsedFileName =
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.UNIT.INC\GETBATTLETROPHIES';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;
      [*] = ;ExecuteState('GetHeroHandle');
      [*] = ;var myHeroHandle : Integer = IntRegister0;
      [*] = ;var myHeroParser : Integer = ParserSelectGameObject(myHeroHandle);
      [*] = ;var myHeroUID : Integer = GetGameObjectIntValueIndByHandle(myHeroHandle, gc_stack_unit_iHeroUID);
      [*] = ;var myMapHeroHandle : Integer = GetGameObjectHandleByUniqueId(myHeroUID);
      [*] = ;var myMapPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myMapHeroHandle);
      [*] = ;
      [*] = ;if myHeroHandle = 0 then
      [*] = ;exit;
      [*] = ;
      [*] = ;PlayerExecuteStateByHandle(myMapPlHandle, 'GetCastleParser');
      [*] = ;var pMyCastle : Integer = IntRegister0;
      [*] = ;var castleUID : Integer = ParserGetIntValueByKeyByHandle(pMyCastle, 'DummyUID');
      [*] = ;var castleHandle : Integer = GetGameObjectHandleByUniqueId(castleUID);
      [*] = ;
      [*] = ;ExecuteState('GetEnemyPlHandle');
      [*] = ;var enPlHandle : Integer = IntRegister0;
      [*] = ;PlayerExecuteStateByHandle(enPlHandle, 'GetHeroHandle');
      [*] = ;var enHeroHandle : Integer = IntRegister0;
      [*] = ;var enHeroParser : Integer = ParserSelectGameObject(enHeroHandle);
      [*] = ;var enHeroUID : Integer = GetGameObjectIntValueIndByHandle(enHeroHandle, gc_stack_unit_iHeroUID);
      [*] = ;var enMapHeroHandle : Integer = GetGameObjectHandleByUniqueId(enHeroUID);
      [*] = ;var enMapHeroParser : Integer = ParserSelectGameObject(enMapHeroHandle);
      [*] = ;
      [*] = ;var enHP : Integer = GetGameObjectIntValueIndByHandle(enHeroHandle, gc_stack_unit_iCurLife);
      [*] = ;var trGold : Integer = 0;
      [*] = ;var trGem : Integer = 0;
      [*] = ;
      [*] = ;var initMachine : Integer = GetMapInitMachineHandle;
      [*] = ;var pDifficulties : Integer = gPrototypeData.difficulty.handle;
      [*] = ;
      [*] = ;function GetRandomLoot(pDoll, looter : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   Result := -1;
      [*] = ;
      [*] = ;   for i := 0 to looter-1 do
      [*] = ;   begin
      [*] = ;      if RandomExt > 0.5 then
      [*] = ;      begin
      [*] = ;         var ind : Integer = Floor(RandomExt * gc_HeroInventoryCount);
      [*] = ;         var pItem : Integer = ParserSelectByHandleByIndex(pDoll, ind);
      [*] = ;
      [*] = ;         var itemID : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemID');
      [*] = ;         if itemID > 0 then
      [*] = ;         begin
      [*] = ;            Result := ind;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (enHeroHandle <> 0) and (enHP = 0) then
      [*] = ;begin
      [*] = ;   var enLevel : Integer = GetGameObjectIntValueIndByHandle(enHeroHandle, gc_stack_unit_iLevel);
      [*] = ;   var enClass1 : Integer = ParserGetIntValueByKeyByHandle(enHeroParser, 'HeroClass1');
      [*] = ;   var enClass2 : Integer = ParserGetIntValueByKeyByHandle(enHeroParser, 'HeroClass2');
      [*] = ;
      [*] = ;   trGold := trGold + Floor(enLevel * (10 - (enClass1 + enClass2) / 2));
      [*] = ;   trGem  := trGem + Floor(enLevel * (enClass1 + enClass2) / 2);
      [*] = ;   _log_Map('BattleGold after enemy hero: '+IntToStr(trGold)+', BattleGem after enemy hero: '+IntToStr(trGem));
      [*] = ;end;
      [*] = ;
      [*] = ;var i, j, k : Integer;
      [*] = ;
      [*] = ;for i := GetPlayerGameObjectsCountByHandle(enPlHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var enGOHandle : Integer = GetGameObjectHandleByIndex(i, enPlHandle);
      [*] = ;   var enUnitID : Integer  = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iUnitID);
      [*] = ;   var enLevel : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iLevel);
      [*] = ;
      [*] = ;   var kUID : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iKillerUID);
      [*] = ;   var kGOHandle : Integer = GetGameObjectHandleByUniqueId(kUID);
      [*] = ;   var mul : Integer = 1;
      [*] = ;
      [*] = ;   if _unit_CheckAbility(kGOHandle, gc_ability_looter) > 0 then
      [*] = ;      mul := 2;
      [*] = ;
      [*] = ;   var pUnit : Integer = _unit_GetUnitParserByID(enUnitID);
      [*] = ;
      [*] = ;   var goldPrice : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'GoldPrice');
      [*] = ;   var gemPrice : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'GemPrice');
      [*] = ;
      [*] = ;   trGold := trGold + mul * Floor(goldPrice * (1 + enLevel / 10));
      [*] = ;   trGem  := trGem + mul * Floor(gemPrice * (1 + enLevel / 10));
      [*] = ;end;
      [*] = ;_log_Map('BattleGold after enemy units: '+IntToStr(trGold)+', BattleGem after enemy units: '+IntToStr(trGem));
      [*] = ;
      [*] = ;IntRegister0 := 992;
      [*] = ;GameObjectExecuteStateByHandle(myMapHeroHandle, 'CheckAbility');
      [*] = ;var looter : Integer = IntRegister1;
      [*] = ;
      [*] = ;trGold := trGold + Floor(trGold * looter / 10);
      [*] = ;trGem := trGem + Floor(trGem * looter / 10);
      [*] = ;_log_Map('BattleGold after hero skill: '+IntToStr(trGold)+', BattleGem after hero skill: '+IntToStr(trGem));
      [*] = ;
      [*] = ;IntRegister0 := 41;
      [*] = ;GameObjectExecuteStateByHandle(castleHandle, 'CheckInnerBuildAbility');
      [*] = ;var value : Integer = IntRegister1;
      [*] = ;
      [*] = ;trGold := trGold + Floor(trGold * value / 100);
      [*] = ;trGem := trGem + Floor(trGem * value / 100);
      [*] = ;_log_Map('BattleGold after buildings: '+IntToStr(trGold)+', BattleGem after buildings: '+IntToStr(trGem));
      [*] = ;
      [*] = ;// check for marauder units abilities
      [*] = ;for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;   if GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife) > 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := 56;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'CheckAbility');
      [*] = ;      var value : Integer = IntRegister1;
      [*] = ;
      [*] = ;      trGold := trGold - Floor(trGold * value / 100);
      [*] = ;      trGem := trGem - Floor(trGem * value / 100);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;_log_Map('BattleGold after marauder: '+IntToStr(trGold)+', BattleGem after marauder: '+IntToStr(trGem));
      [*] = ;
      [*] = ;if SameText(cMode, 'cmPlayer') then
      [*] = ;begin
      [*] = ;   var diff : Integer = gGame.arrplayerdifficulty[GetPlayerIndexByHandle(myMapPlHandle)].basediff;
      [*] = ;   var pDifficulty : Integer = ParserSelectByHandleByIndex(pDifficulties, diff);
      [*] = ;   var loot : Integer = ParserGetIntValueByKeyByHandle(pDifficulty, 'LootMod');
      [*] = ;
      [*] = ;   trGold := (trGold * loot) div 100;
      [*] = ;   _log_Map('BattleGold after difficulty: '+IntToStr(trGold)+', BattleGem after difficulty: '+IntToStr(trGem));
      [*] = ;end;
      [*] = ;
      [*] = ;trGold := trGold div 5;
      [*] = ;trGem := trGem div 5;
      [*] = ;_log_Map('BattleGold after division: '+IntToStr(trGold)+', BattleGem after division: '+IntToStr(trGem));
      [*] = ;
      [*] = ;// world rule
      [*] = ;if (_worldrule_GetWorldRuleAbilityExistByID(4)) then
      [*] = ;begin
      [*] = ;   var param2 : Integer = _worldrule_GetWorldRuleAbilityParam2(4);
      [*] = ;   trGold := (trGold*param2) div 100;
      [*] = ;   trGem := (trGem*param2) div 100;
      [*] = ;
      [*] = ;   trGold := trGold+15+round(RandomExt()*15);
      [*] = ;end;
      [*] = ;_log_Map('BattleGold after worldrule: '+IntToStr(trGold)+', BattleGem after worldrule: '+IntToStr(trGem));
      [*] = ;
      [*] = ;ParserSetIntValueByKeyByHandle(myHeroParser, 'BattleGold', trGold);
      [*] = ;ParserSetIntValueByKeyByHandle(myHeroParser, 'BattleGem', trGem);
      [*] = ;
      [*] = ;var pBattleLootItems : Integer = ParserAddChildByIndex(myHeroParser, 'BattleLootItems');
      [*] = ;if pBattleLootItems = 0 then
      [*] = ;pBattleLootItems := ParserAddChildByIndex(myHeroParser, 'BattleLootItems')
      [*] = ;else
      [*] = ;ParserClearByHandle(pBattleLootItems);
      [*] = ;
      [*] = ;if enHeroHandle <> 0 then
      [*] = ;begin
      [*] = ;   var pEnemyDoll : Integer = ParserSelectByHandleByKey(enMapHeroParser, 'Doll');
      [*] = ;
      [*] = ;   var itemInd : Integer = GetRandomLoot(pEnemyDoll, looter);
      [*] = ;   if itemInd > -1 then
      [*] = ;   begin
      [*] = ;      var pItem : Integer = ParserSelectByHandleByIndex(pEnemyDoll, itemInd);
      [*] = ;      var itemID : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemID');
      [*] = ;      var itemDur : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Durability');
      [*] = ;
      [*] = ;      var pNewLoot : Integer = ParserAddChildByIndex(pBattleLootItems, '*');
      [*] = ;
      [*] = ;      ParserSetIntValueByKeyByHandle(pNewLoot, 'ItemID', itemID);
      [*] = ;      ParserSetIntValueByKeyByHandle(pNewLoot, 'Durability', itemDur);
      [*] = ;      _log_Map('Battle Loot Item: '+IntToStr(itemID));
      [*] = ;   end;
      [*] = ;
      [*] = ;   var itemInd1 : Integer = GetRandomLoot(pEnemyDoll, looter);
      [*] = ;   if (itemInd1 > -1) and (itemInd1 <> itemInd) then
      [*] = ;   begin
      [*] = ;      var pItem : Integer = ParserSelectByHandleByIndex(pEnemyDoll, itemInd1);
      [*] = ;      var itemID : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemID');
      [*] = ;      var itemDur : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Durability');
      [*] = ;
      [*] = ;      var pNewLoot : Integer = ParserAddChildByIndex(pBattleLootItems, '*');
      [*] = ;
      [*] = ;      ParserSetIntValueByKeyByHandle(pNewLoot, 'ItemID', itemID);
      [*] = ;      ParserSetIntValueByKeyByHandle(pNewLoot, 'Durability', itemDur);
      [*] = ;      _log_Map('Battle Loot Item: '+IntToStr(itemID));
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   var lootPoss : Integer = looter;
      [*] = ;   var lootCount : Integer = 0;
      [*] = ;   var parser : Integer = 0;
      [*] = ;
      [*] = ;   if gIntRegister_BattleGuardIndex > 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := gIntRegister_BattleGuardIndex;
      [*] = ;      StateMachineExecuteState(initMachine, 'GetGuardParserByID', 0);
      [*] = ;      parser := IntRegister1;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if gIntRegister_BattleDefenderIndex > 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := gIntRegister_BattleDefenderIndex;
      [*] = ;      StateMachineExecuteState(initMachine, 'GetDefenderParserByID', 0);
      [*] = ;      parser := IntRegister1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if parser > 0 then
      [*] = ;   begin
      [*] = ;      lootPoss := lootPoss + ParserGetIntValueByKeyByHandle(parser, 'LootPoss');
      [*] = ;      lootCount := ParserGetIntValueByKeyByHandle(parser, 'MaxLoot');
      [*] = ;
      [*] = ;      // world rule
      [*] = ;      if (_worldrule_GetWorldRuleAbilityExistByID(4)) then
      [*] = ;      begin
      [*] = ;         var param1 : Integer = _worldrule_GetWorldRuleAbilityParam1(4);
      [*] = ;         lootPoss := (lootPoss*param1) div 100;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if _rand_Random(100) < lootPoss then // gain loot
      [*] = ;      begin
      [*] = ;         var lootItems : Integer = 1;
      [*] = ;         while (lootItems < lootCount) and (_rand_Random(100) + looter > 50) do
      [*] = ;            lootItems := lootItems + 1;
      [*] = ;
      [*] = ;         // TODO: check if array needed
      [*] = ;         for i := 0 to lootItems-1 do
      [*] = ;         begin
      [*] = ;            ArrayClear;
      [*] = ;            for j := GetPlayerGameObjectsCountByHandle(enPlHandle)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var goHandle : Integer = GetGameObjectHandleByIndex(j, enPlHandle);
      [*] = ;               var unitID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iUnitID);
      [*] = ;
      [*] = ;               var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;
      [*] = ;               ArrayPushValue(i);
      [*] = ;            end;
      [*] = ;
      [*] = ;            if ArrayGetCount > 0 then
      [*] = ;            begin
      [*] = ;               var ind : Integer = Floor(RandomExt * ArrayGetCount);
      [*] = ;               var goHandle : Integer = GetGameObjectHandleByIndex(ind, enPlHandle);
      [*] = ;               var unitID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iUnitID);
      [*] = ;
      [*] = ;               var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;               var pUnitLootLevels : Integer = ParserSelectByHandleByKey(pUnit, 'UnitLoots');
      [*] = ;
      [*] = ;               var level : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iLevel);
      [*] = ;
      [*] = ;               var sum : Integer = 0;
      [*] = ;               for j := 0 to level do
      [*] = ;               begin
      [*] = ;                  var pUnitLootLevel : Integer = ParserSelectByHandleByIndex(pUnitLootLevels, j);
      [*] = ;                  var pUnitLoots : Integer = ParserSelectByHandleByKey(pUnitLootLevel, 'Items');
      [*] = ;
      [*] = ;                  for k := ParserGetCountByHandle(pUnitLoots)-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     var pUnitLoot : Integer = ParserSelectByHandleByIndex(pUnitLoots, k);
      [*] = ;                     var poss : Integer = ParserGetIntValueByKeyByHandle(pUnitLoot, 'Possibility');
      [*] = ;
      [*] = ;                     if poss > 0 then
      [*] = ;                     sum := sum + 2 * poss + j;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               var rand : Float = RandomExt * sum;
      [*] = ;               var curSum : Integer = 0;
      [*] = ;
      [*] = ;               for [MAIN]j := 0 to level do
      [*] = ;               begin
      [*] = ;                  var pUnitLootLevel : Integer = ParserSelectByHandleByIndex(pUnitLootLevels, j);
      [*] = ;                  var pUnitLoots : Integer = ParserSelectByHandleByKey(pUnitLootLevel, 'Items');
      [*] = ;
      [*] = ;                  for k := ParserGetCountByHandle(pUnitLoots)-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     var pUnitLoot : Integer = ParserSelectByHandleByIndex(pUnitLoots, k);
      [*] = ;                     var itemID : Integer = ParserGetIntValueByKeyByHandle(pUnitLoot, 'ItemID');
      [*] = ;                     var poss : Integer = ParserGetIntValueByKeyByHandle(pUnitLoot, 'Possibility');
      [*] = ;
      [*] = ;                     if poss > 0 then
      [*] = ;                     curSum := curSum + 2 * poss + j;
      [*] = ;
      [*] = ;                     if curSum >= rand then
      [*] = ;                     begin
      [*] = ;                        var pNewLoot : Integer = ParserAddChildByIndex(pBattleLootItems, '*');
      [*] = ;                        ParserSetIntValueByKeyByHandle(pNewLoot, 'ItemID', itemID);
      [*] = ;
      [*] = ;                        IntRegister0 := itemID;
      [*] = ;                        StateMachineExecuteState(initMachine, 'GetItemParserByID', 0);
      [*] = ;                        var pItem : Integer = IntRegister1;
      [*] = ;                        var itemDur : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Durability');
      [*] = ;                        var itemBr : Boolean = ParserGetBoolValueByKeyByHandle(pItem, 'Breakable');
      [*] = ;                        var itemRarity : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Rarity');
      [*] = ;                        var dur : Integer = 0;
      [*] = ;
      [*] = ;                        if not itemBr then
      [*] = ;                        dur := -1
      [*] = ;                        else
      [*] = ;                        dur := 1 + _rand_Random(itemDur);
      [*] = ;
      [*] = ;                        ParserSetIntValueByKeyByHandle(pNewLoot, 'Durability', dur);
      [*] = ;
      [*] = ;                        IntRegister0 := itemID;
      [*] = ;                        PlayerExecuteStateByHandle(myMapPlHandle, 'CheckItemRarity');
      [*] = ;                        _log_Map('Battle Loot Item: '+IntToStr(itemID));
      [*] = ;
      [*] = ;                        break(MAIN);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[BattleGold: '+IntToStr(trGold)+', BattleGem: '+IntToStr(trGem)+']',$1000000 or _log_trace);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

