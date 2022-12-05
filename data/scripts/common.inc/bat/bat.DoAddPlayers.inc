section.begin
   Name = bat.DoAddPlayers
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\BAT\BAT.DOADDPLAYERS';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var attackPlName : String;
      [*] = ;var defendPlName : String;
      [*] = ;
      [*] = ;if gBoolRegister_BattleSimulate then
      [*] = ;begin
      [*] = ;   attackPlName := gc_battle_virtAttackPlayerName;
      [*] = ;   defendPlName := gc_battle_virtDefendPlayerName;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   attackPlName := gc_battle_attackPlayerName;
      [*] = ;   defendPlName := gc_battle_defendPlayerName;
      [*] = ;end;
      [*] = ;
      [*] = ;const cPlayerRace = 'units';
      [*] = ;
      [*] = ;const cTowerOffset : Float = 2;
      [*] = ;const cMageTowerOffset : Float = 2;
      [*] = ;
      [*] = ;var attackPlHandle : Integer = GetPlayerHandleByName(attackPlName);
      [*] = ;var defendPlHandle : Integer = GetPlayerHandleByName(defendPlName);
      [*] = ;
      [*] = ;var pProvince : Integer = gIntRegister_MapBattleProvince;
      [*] = ;var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;procedure ClearHuds(plHandle : Integer);
      [*] = ;begin
      [*] = ;   var hudCollection : Integer = _gui_GetLayerExt(cHUDTacticsUnitLayer,-1);
      [*] = ;   var i : Integer;
      [*] = ;
      [*] = ;   if hudCollection <> 0 then
      [*] = ;   begin
      [*] = ;      for i := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;         var hudHandle : Integer = GetGUIGroupHUDCollectionItemByGameObject(hudCollection, goHandle);
      [*] = ;         if (hudHandle<>0) then
      [*] = ;            GUIGroupHUDCollectionDeleteGameObject(hudCollection, goHandle);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure InitPlayer(var batPlHandle : Integer; const mapPlHandle, enMapPlHandle, heroHandle, aMode : Integer);
      [*] = ;begin
      [*] = ;   var mapCMode : String = GetPlayerControlModeByHandle(mapPlHandle);
      [*] = ;   var enMapCMode : String = GetPlayerControlModeByHandle(enMapPlHandle);
      [*] = ;
      [*] = ;   var cMode : String;
      [*] = ;   if (mapPlHandle <> 0) and (not gBoolRegister_BattleSimulate) and gBoolRegister_IsHumanPlayer then
      [*] = ;   begin
      [*] = ;      if SameText(mapCMode, 'cmPlayer') and SameText(enMapCMode, 'cmPlayer') and (mapPlHandle <> enMapPlHandle) then
      [*] = ;         cMode := 'cmPlayer'
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (heroHandle <> 0) or (gBoolRegister_BattleIsSiege and (aMode = 0)) then
      [*] = ;            cMode := GetPlayerControlModeByHandle(mapPlHandle)
      [*] = ;         else
      [*] = ;            cMode := 'cmPC';
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      cMode := 'cmPC';
      [*] = ;
      [*] = ;   var plName : String;
      [*] = ;   if aMode = 1 then
      [*] = ;      plName := attackPlName
      [*] = ;   else
      [*] = ;      plName := defendPlName;
      [*] = ;
      [*] = ;   if batPlHandle = 0 then
      [*] = ;      batPlHandle := CreatePlayer(plName, cPlayerRace, cMode)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if not gBoolRegister_BattleSimulate then
      [*] = ;         ClearHuds(batPlHandle);
      [*] = ;
      [*] = ;      ClearPlayerGameObjectsByHandle(batPlHandle);
      [*] = ;      SetPlayerControlModeByHandle(batPlHandle, cMode);
      [*] = ;   end;
      [*] = ;
      [*] = ;   PlayerExecuteStateByHandle(batPlHandle, 'Initial');
      [*] = ;   SetPlayerIntValueIndByHandle(batPlHandle, gc_battle_PLStack_iAttackMode, aMode);
      [*] = ;   SetPlayerIntValueIndByHandle(batPlHandle, gc_battle_PLStack_iCastMode, 2);
      [*] = ;   SetPlayerIntValueIndByHandle(batPlHandle, gc_battle_PLStack_iGemSpent, 0);
      [*] = ;   SetPlayerBoolValueIndByHandle(batPlHandle, gc_battle_PLStack_bUnitPlacement, true);
      [*] = ;   SetPlayerBoolValueIndByHandle(batPlHandle, gc_battle_PLStack_bCheckSabotage, true);
      [*] = ;   SetPlayerIntValueIndByHandle(batPlHandle, gc_battle_PLStack_iIdleMode, gc_battle_idle_normal);
      [*] = ;
      [*] = ;   _misc_AntiFreeze();
      [*] = ;end;
      [*] = ;
      [*] = ;procedure AddTowers(plHandle : Integer);
      [*] = ;begin
      [*] = ;   var i, j : Integer;
      [*] = ;   var attack : Integer = 0;
      [*] = ;
      [*] = ;   IntRegister0 := 30;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'CheckInnerBuildAbility');
      [*] = ;   attack := attack + IntRegister1;
      [*] = ;
      [*] = ;   IntRegister0 := 12;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'CheckOuterBuildAbility');
      [*] = ;   attack := attack + IntRegister2;
      [*] = ;
      [*] = ;   var pPlParser : Integer = ParserSelectPlayer(plHandle);
      [*] = ;   var pPlTowers : Integer = ParserSelectByHandleByKey(pPlParser, 'Towers');
      [*] = ;
      [*] = ;   IntRegister0 := pPlTowers;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'GetTowersData');
      [*] = ;   var towerCount : Integer = IntRegister1;
      [*] = ;   var mTowerCount : Integer = IntRegister2;
      [*] = ;
      [*] = ;   var tInd : Integer = 0;
      [*] = ;   if not gBoolRegister_BattleSimulate then
      [*] = ;   begin
      [*] = ;      for i := 0 to gc_battle_GridSize-1 do
      [*] = ;      begin
      [*] = ;         var ind : Integer = i * gc_battle_GridSize + gc_battle_GridSize - 3;
      [*] = ;         var pHexCell : Integer = ParserSelectByHandleByIndex(gHexCells.handle , ind);
      [*] = ;         var tower : Boolean = ParserGetBoolValueByKeyByHandle(pHexCell, 'Tower');
      [*] = ;
      [*] = ;         if tower then
      [*] = ;         begin
      [*] = ;            var x : Float = ParserGetFloatValueByKeyByHandle(pHexCell, 'CenterX');
      [*] = ;            var z : Float = ParserGetFloatValueByKeyByHandle(pHexCell, 'CenterY');
      [*] = ;            var y : Float = RayCastHeight(x, z) + cTowerOffset;
      [*] = ;
      [*] = ;            var pPlTower : Integer = ParserSelectByHandleByIndex(pPlTowers, tInd);
      [*] = ;            ParserSetFloatValueByKeyByHandle(pPlTower, 'X', x);
      [*] = ;            ParserSetFloatValueByKeyByHandle(pPlTower, 'Y', y);
      [*] = ;            ParserSetFloatValueByKeyByHandle(pPlTower, 'Z', z);
      [*] = ;
      [*] = ;            tInd := tInd + 1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if tInd < towerCount then
      [*] = ;      begin
      [*] = ;         for i := towerCount-1 downto tInd do
      [*] = ;         begin
      [*] = ;            var pPlTower : Integer = ParserSelectByHandleByIndex(pPlTowers, i);
      [*] = ;            ParserFreeByHandle(pPlTower);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      tInd := towerCount;
      [*] = ;
      [*] = ;   for i := 0 to mTowerCount-1 do
      [*] = ;   begin
      [*] = ;      IntRegister0 := i;
      [*] = ;      ExecuteState('bat.GetMageTowerPosition');
      [*] = ;      var x : Float = FloatRegister0;
      [*] = ;      var y : Float = FloatRegister1 + cMageTowerOffset;
      [*] = ;      var z : Float = FloatRegister2;
      [*] = ;
      [*] = ;      var pPlTower : Integer = ParserSelectByHandleByIndex(pPlTowers, tInd);
      [*] = ;      ParserSetFloatValueByKeyByHandle(pPlTower, 'X', x);
      [*] = ;      ParserSetFloatValueByKeyByHandle(pPlTower, 'Y', y);
      [*] = ;      ParserSetFloatValueByKeyByHandle(pPlTower, 'Z', z);
      [*] = ;
      [*] = ;      tInd := tInd + 1;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure PrepareUnit(pUnits, ind : Integer; isAttack, isHero : Boolean);
      [*] = ;begin
      [*] = ;   var pUnit : Integer = ParserSelectByHandleByIndex(pUnits, ind);
      [*] = ;
      [*] = ;   var unitID : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'UnitID');
      [*] = ;   var posX : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'BattleX');
      [*] = ;   var posY : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'BattleY');
      [*] = ;
      [*] = ;   if not isAttack then
      [*] = ;      posX := gc_battle_GridSize - 1 - posX;
      [*] = ;
      [*] = ;   var plHandle : Integer;
      [*] = ;   if isAttack then
      [*] = ;      plHandle := attackPlHandle
      [*] = ;   else
      [*] = ;      plHandle := defendPlHandle;
      [*] = ;
      [*] = ;   IntRegister0 := unitID;
      [*] = ;   IntRegister1 := posX;
      [*] = ;   IntRegister2 := posY;
      [*] = ;   PlayerExecuteStateByHandle(plHandle, 'AddUnit');
      [*] = ;   var goHandle : Integer = IntRegister3;
      [*] = ;
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iParserHandle, pUnit);
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iArmyIndex, ind);
      [*] = ;
      [*] = ;   SetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bIsHero, isHero);
      [*] = ;   if isHero then
      [*] = ;   begin
      [*] = ;      var heroHandle : Integer;
      [*] = ;      if isAttack then
      [*] = ;         heroHandle := gIntRegister_BattleAttackHeroHandle
      [*] = ;      else
      [*] = ;         heroHandle := gIntRegister_BattleDefendHeroHandle;
      [*] = ;
      [*] = ;      var heroUID : Integer = GetGameObjectUniqueIdByHandle(heroHandle);
      [*] = ;      SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iHeroUID, heroUID);
      [*] = ;
      [*] = ;      if (not gBoolRegister_BattleSimulate) then
      [*] = ;      begin
      [*] = ;         var class1 : Integer = GetGameObjectIntValueIndByHandle(heroHandle, gc_map_GOStack_MapUnit_iClassInd1);
      [*] = ;         var class2 : Integer = GetGameObjectIntValueIndByHandle(heroHandle, gc_map_GOStack_MapUnit_iClassInd2);
      [*] = ;         if (class1=3) and (class2<>2) then
      [*] = ;         begin
      [*] = ;            var goChildHnd : Integer = GetGameObjectGOHandleChildByBaseName(goHandle, 'units', 'commander_crossbow');
      [*] = ;            SetGameObjectVisibleByHandle(goChildHnd, False);
      [*] = ;            goChildHnd := GetGameObjectGOHandleChildByBaseName(goHandle, 'units', 'commander_arrow');
      [*] = ;            SetGameObjectVisibleByHandle(goChildHnd, False);
      [*] = ;         end;
      [*] = ;         if (class1=1) and (class2<>2) then
      [*] = ;         begin
      [*] = ;            var goChildHnd : Integer = GetGameObjectGOHandleChildByBaseName(goHandle, 'units', 'warrior_arbalet');
      [*] = ;            SetGameObjectVisibleByHandle(goChildHnd, False);
      [*] = ;            goChildHnd := GetGameObjectGOHandleChildByBaseName(goHandle, 'units', 'warrior_arrow');
      [*] = ;            SetGameObjectVisibleByHandle(goChildHnd, False);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'CopyFromParser');
      [*] = ;
      [*] = ;   _misc_AntiFreeze();
      [*] = ;end;
      [*] = ;
      [*] = ;function IsArmyAtFullPower(pArmy : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := true;
      [*] = ;   var pArmyUnits : Integer = ParserSelectByHandleByKey(pArmy, 'Units');
      [*] = ;   
      [*] = ;   var i : Integer;
      [*] = ;   var pOrigArmy, origArmyCount : Integer = 0;
      [*] = ;   if (gIntRegister_BattleSiteIndex >= 0) and (gIntRegister_BattleSiteID > 0) then
      [*] = ;   begin
      [*] = ;      var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;      var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, gIntRegister_BattleSiteIndex);
      [*] = ;      var pSiteGuard : Integer = ParserSelectByHandleByKey(pProvSite, 'Guard');
      [*] = ;      pOrigArmy := ParserSelectByHandleByIndex(gPrototypeData.guards.handle, ParserGetIntValueByKeyByHandle(pSiteGuard, 'GuardID'));
      [*] = ;      origArmyCount := ParserGetIntValueByKeyByHandle(pOrigArmy, 'Quantity');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (pArmy = ParserSelectByHandleByKey(pProvince, 'Guard')) then
      [*] = ;   begin
      [*] = ;      var pProvGuard : Integer = ParserSelectByHandleByKey(pProvince, 'Guard');
      [*] = ;      pOrigArmy := ParserSelectByHandleByIndex(gPrototypeData.guards.handle, ParserGetIntValueByKeyByHandle(pProvGuard, 'GuardID'));
      [*] = ;      origArmyCount := ParserGetIntValueByKeyByHandle(pOrigArmy, 'Quantity');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (pArmy = ParserSelectByHandleByKey(pProvince, 'Defender')) then
      [*] = ;   begin
      [*] = ;      var pProvDefender : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;      pOrigArmy := ParserSelectByHandleByIndex(gPrototypeData.defenders.handle, ParserGetIntValueByKeyByHandle(pProvDefender, 'DefenderID'));
      [*] = ;      var pDefUnits : Integer = ParserSelectByHandleByKey(pOrigArmy, 'Units');
      [*] = ;      
      [*] = ;      for i := 0 to ParserGetCountByHandle(pDefUnits)-1 do 
      [*] = ;         origArmyCount := origArmyCount + ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pDefUnits, i), 'Count');
      [*] = ;   end;
      [*] = ;   
      [*] = ;   var armyCount : Integer = ParserGetCountByHandle(pArmyUnits);
      [*] = ;//Log('origArmyCount '+IntToStr(origArmyCount));
      [*] = ;//Log('armyCount '+IntToStr(armyCount));
      [*] = ;   if (origArmyCount = 0) or (armyCount = 0) or (armyCount < origArmyCount) then
      [*] = ;   begin
      [*] = ;      Result := false;
      [*] = ;      exit;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   var initMachine : Integer = GetMapInitMachineHandle;
      [*] = ;   var pUnitParser : Integer;
      [*] = ;   if Result then
      [*] = ;   for i := 0 to armyCount-1 do
      [*] = ;   begin
      [*] = ;      pUnitParser := ParserSelectByHandleByIndex(pArmyUnits, i);
      [*] = ;      
      [*] = ;      IntRegister0 := pUnitParser;
      [*] = ;      IntRegister1 := 0;
      [*] = ;      IntRegister2 := gc_battle_unit_iMaxLife;
      [*] = ;      StateMachineExecuteState(initMachine, 'GetUnitPropertyByParser', 0);
      [*] = ;      
      [*] = ;      if (IntRegister3 = 0) or (ParserGetIntValueByKeyByHandle(pUnitParser, 'CurLife') < IntRegister3) then
      [*] = ;      begin
      [*] = ;         Result := false;
      [*] = ;         exit;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;
      [*] = ;// init players
      [*] = ;var mapAttackPlHandle : Integer = gIntRegister_BattleAttackPlayer;
      [*] = ;var mapDefendPlHandle : Integer = gIntRegister_BattleDefendPlayer;
      [*] = ;
      [*] = ;LogI('gIntRegister_BattleAttackPlayer: '+IntToStr(gIntRegister_BattleAttackPlayer));
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;InitPlayer(attackPlHandle, mapAttackPlHandle, mapDefendPlHandle, gIntRegister_BattleAttackHeroHandle, 1);
      [*] = ;InitPlayer(defendPlHandle, mapDefendPlHandle, mapAttackPlHandle, gIntRegister_BattleDefendHeroHandle, 0);
      [*] = ;
      [*] = ;// init towers
      [*] = ;//if gBoolRegister_BattleSimulate then
      [*] = ;ExecuteState('bat.CheckSiege');
      [*] = ;
      [*] = ;if gBoolRegister_BattleIsSiege then
      [*] = ;begin
      [*] = ;   if gIntRegister_BattleDefendPlayer <> 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := 19;
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle, 'CheckInnerBuildAbility');
      [*] = ;      var moralBonus : Integer = IntRegister1;
      [*] = ;
      [*] = ;      IntRegister0 := 10;
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle, 'CheckOuterBuildAbility');
      [*] = ;      moralBonus := moralBonus + IntRegister1;
      [*] = ;
      [*] = ;      SetPlayerIntValueIndByHandle(defendPlHandle, gc_battle_PLStack_iMoralBonus, moralBonus);
      [*] = ;   end;
      [*] = ;
      [*] = ;   AddTowers(defendPlHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;// calculate life modificators
      [*] = ;var aLifeMod : Integer = 100;
      [*] = ;var aDiff : Integer = 0;//GetPlayerIntValueIndByHandle(gIntRegister_BattleAttackPlayer, gc_map_PLStack_MapUnit_iDifficulty);
      [*] = ;if (gIntRegister_BattleAttackPlayer<>0) then
      [*] = ;   aDiff := gGame.arrplayerdifficulty[GetPlayerIndexByHandle(gIntRegister_BattleAttackPlayer)].basediff;
      [*] = ;
      [*] = ;var dLifeMod : Integer = 100;
      [*] = ;var dDiff : Integer = 0;//GetPlayerIntValueIndByHandle(gIntRegister_BattleDefendPlayer, gc_map_PLStack_MapUnit_iDifficulty);
      [*] = ;if (gIntRegister_BattleDefendPlayer<>0) then
      [*] = ;   dDiff := gGame.arrplayerdifficulty[GetPlayerIndexByHandle(gIntRegister_BattleDefendPlayer)].basediff;
      [*] = ;
      [*] = ;var aCMode : String = GetPlayerControlModeByHandle(attackPlHandle);
      [*] = ;var dCMode : String = GetPlayerControlModeByHandle(defendPlHandle);
      [*] = ;
      [*] = ;if _log then _Log_map('Attacker: '+aCMode+', Defender: '+dCMode);
      [*] = ;LogI('Difficulty Attacker: '+IntToStr(aDiff));
      [*] = ;LogI('Difficulty Defender: '+IntToStr(aDiff));
      [*] = ;
      [*] = ;if SameText(aCMode, 'cmPC') and SameText(dCMode, 'cmPC') and (not SameText(GetPlayerControlModeByHandle(mapAttackPlHandle), 'cmPlayer')) then
      [*] = ;begin
      [*] = ;   if aDiff < dDiff then
      [*] = ;      aLifeMod := (10 + aDiff - dDiff) * 10;
      [*] = ;
      [*] = ;   if dDiff < aDiff then
      [*] = ;      dLifeMod := (10 + dDiff - aDiff) * 10;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if SameText(aCMode, 'cmPlayer') and (gIntRegister_BattleAttackHeroHandle <> 0) then
      [*] = ;   begin
      [*] = ;      if (gIntRegister_BattleDefendPlayer=0) then
      [*] = ;         dLifeMod := gGame.arrplayerdifficulty[GetPlayerIndexByHandle(gIntRegister_BattleAttackPlayer)].neutralhp
      [*] = ;      else
      [*] = ;      if (gIntRegister_BattleDefendHeroHandle=0) then
      [*] = ;         dLifeMod := gGame.arrplayerdifficulty[GetPlayerIndexByHandle(gIntRegister_BattleAttackPlayer)].defenderhp;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if SameText(dCMode, 'cmPlayer') and (gIntRegister_BattleDefendHeroHandle <> 0) then
      [*] = ;   begin
      [*] = ;      if (gIntRegister_BattleAttackPlayer=0) then
      [*] = ;         aLifeMod := gGame.arrplayerdifficulty[GetPlayerIndexByHandle(gIntRegister_BattleDefendPlayer)].neutralhp
      [*] = ;      else
      [*] = ;      if (gIntRegister_BattleAttackHeroHandle=0) then
      [*] = ;         aLifeMod := gGame.arrplayerdifficulty[GetPlayerIndexByHandle(gIntRegister_BattleDefendPlayer)].defenderhp
      [*] = ;   end;
      [*] = ;end;
      [*] = ;LogI('LifeMod Attacker: '+IntToStr(aLifeMod));
      [*] = ;LogI('LifeMod Defender: '+IntToStr(dLifeMod));
      [*] = ;
      [*] = ;if aLifeMod <= 0 then
      [*] = ;begin
      [*] = ;   LogI(' Warning: attack life modifier <= 0');
      [*] = ;   aLifeMod := 1;
      [*] = ;end;
      [*] = ;if dLifeMod <= 0 then
      [*] = ;begin
      [*] = ;   LogI(' Warning: defend life modifier <= 0');
      [*] = ;   dLifeMod := 1;
      [*] = ;end;
      [*] = ;
      [*] = ;SetPlayerIntValueIndByHandle(attackPlHandle, gc_battle_PLStack_iLifeMod, aLifeMod);
      [*] = ;SetPlayerIntValueIndByHandle(defendPlHandle, gc_battle_PLStack_iLifeMod, dLifeMod);
      [*] = ;
      [*] = ;// prepare units
      [*] = ;var i : Integer;
      [*] = ;for i := 0 to ParserGetCountByHandle(gHexCells.handle)-1 do
      [*] = ;   ParserSetIntValueByKeyByHandle(ParserSelectByHandleByIndex(gHexCells.handle, i), 'UID', 0);
      [*] = ;
      [*] = ;var attackParser : Integer = gIntRegister_BattleAttackArmy;
      [*] = ;var defendParser : Integer = gIntRegister_BattleDefendArmy;
      [*] = ;
      [*] = ;var pAttackUnits : Integer = ParserSelectByHandleByKey(attackParser, 'Units');
      [*] = ;var pDefendUnits : Integer = ParserSelectByHandleByKey(defendParser, 'Units');
      [*] = ;
      [*] = ;SetActiveTrackNodeList(1);
      [*] = ;
      [*] = ;if _log then _Log_map('Attack units['+IntToStr(ParserGetCountByHandle(pAttackUnits))+']:');
      [*] = ;for i := 0 to ParserGetCountByHandle(pAttackUnits)-1 do
      [*] = ;begin
      [*] = ;   var pUnit : Integer = ParserSelectByHandleByIndex(pAttackUnits, i);
      [*] = ;   var isHero : Boolean = ParserGetBoolValueByKeyByHandle(pUnit, 'IsHero');
      [*] = ;   var curLife : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'CurLife');
      [*] = ;
      [*] = ;   if curLife > 0 then
      [*] = ;      PrepareUnit(pAttackUnits, i, true, isHero);
      [*] = ;end;
      [*] = ;
      [*] = ;if _log then _Log_map('Defend units['+IntToStr(ParserGetCountByHandle(pDefendUnits))+']:');
      [*] = ;for i := 0 to ParserGetCountByHandle(pDefendUnits)-1 do
      [*] = ;begin
      [*] = ;   var pUnit : Integer = ParserSelectByHandleByIndex(pDefendUnits, i);
      [*] = ;   var isHero : Boolean = ParserGetBoolValueByKeyByHandle(pUnit, 'IsHero');
      [*] = ;   var curLife : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'CurLife');
      [*] = ;
      [*] = ;   if curLife > 0 then
      [*] = ;      PrepareUnit(pDefendUnits, i, false, isHero);
      [*] = ;end;
      [*] = ;
      [*] = ;AddPlayerEnemyPlayerByHandle(defendPlHandle, attackPlHandle);
      [*] = ;AddPlayerEnemyPlayerByHandle(attackPlHandle, defendPlHandle);
      [*] = ;
      [*] = ;if gBoolRegister_BattleSimulate then
      [*] = ;   gBoolRegister_IsHumanPlayer := false
      [*] = ;else
      [*] = ;   gIntRegister_NewBattle := 0;
      [*] = ;
      [*] = ;gBoolRegister_QuickBattle := (not gBoolRegister_IsHumanPlayer);
      [*] = ;
      [*] = ;gBoolRegister_BattleEndBattle := false;
      [*] = ;gIntRegister_BattleCurrentTurn := 0;
      [*] = ;gFloatRegister_BattleFlyTextTime := 0;
      [*] = ;
      [*] = ;var plHandle : Integer = attackPlHandle;
      [*] = ;if gBoolRegister_IsHumanPlayer then
      [*] = ;begin
      [*] = ;   if gGame.gameType = gc_GameTypeLanBattle then
      [*] = ;   begin
      [*] = ;      if (GetLanMode() >= 2) then // master
      [*] = ;         plHandle := attackPlHandle
      [*] = ;      else
      [*] = ;         plHandle := defendPlHandle;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if gGame.gameType = gc_GameTypeHotseat then
      [*] = ;   begin
      [*] = ;      if (not SameText(aCMode, 'cmPlayer')) then
      [*] = ;         plHandle := defendPlHandle;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (GetPlayerIndexByHandle(mapDefendPlHandle) = gIntRegister_MapMyPlayerIndex) and
      [*] = ;      ((GetPlayerIndexByHandle(mapAttackPlHandle) <> gIntRegister_MapMyPlayerIndex) or (gIntRegister_BattleAttackHeroHandle = 0)) then
      [*] = ;         plHandle := defendPlHandle;
      [*] = ;   end;
      [*] = ;   gBoolRegister_BattlePlaceMode := true;
      [*] = ;
      [*] = ;   _gv_SetIOHandle(plHandle,_log_name);
      [*] = ;
      [*] = ;   _log_battle_Clear();
      [*] = ;end
      [*] = ;else
      [*] = ;   gBoolRegister_BattlePlaceMode := false;
      [*] = ;
      [*] = ;if _log and (gIntRegister_GVLogging <> gc_gvlog_log_none) then
      [*] = ;begin
      [*] = ;   ParserSaveToFileByHandle(gIntRegister_BattleAttackArmy,'.\log\before_battle_attack.dat');
      [*] = ;   ParserSaveToFileByHandle(gIntRegister_BattleDefendArmy,'.\log\before_battle_defend.dat');
      [*] = ;end;
      [*] = ;
      [*] = ;var pPlParser : Integer = ParserSelectPlayer(defendPlHandle);
      [*] = ;var pPlTowers : Integer = ParserSelectByHandleByKey(pPlParser, 'Towers');
      [*] = ;
      [*] = ;if (not gBoolRegister_IsHumanPlayer) and (not gBoolRegister_BattleSimulate) then
      [*] = ;begin
      [*] = ;   //gBoolRegister_BattleSimulate := true; why the hell should it be marked simulated when not gBoolRegister_IsHumanPlayer??
      [*] = ;   gBoolRegister_RealAIBattle := true;
      [*] = ;end
      [*] = ;else
      [*] = ;   gBoolRegister_RealAIBattle := false;
      [*] = ;
      [*] = ;_Log_Map('gIntRegister_BattleSiteID '+IntToStr(gIntRegister_BattleSiteID));
      [*] = ;_Log_Map('gBoolRegister_RealAIBattle '+BoolToStr(gBoolRegister_RealAIBattle));
      [*] = ;if gBoolRegister_RealAIBattle and IsArmyAtFullPower(gIntRegister_BattleDefendArmy) then
      [*] = ;   gBoolRegister_BattleEnemyFullPower := true
      [*] = ;else
      [*] = ;   gBoolRegister_BattleEnemyFullPower := false;
      [*] = ;_Log_Map('gBoolRegister_BattleEnemyFullPower '+BoolToStr(gBoolRegister_BattleEnemyFullPower));
      [*] = ;
      [*] = ;if not gBoolRegister_BattleSimulate then
      [*] = ;begin
      [*] = ;   // unit placement
      [*] = ;   if acMode = 'cmPC' then
      [*] = ;      PlayerExecuteStateByHandle(attackPlHandle, 'UnitPlacement');
      [*] = ;   if dcMode = 'cmPC' then
      [*] = ;      PlayerExecuteStateByHandle(defendPlHandle, 'UnitPlacement');
      [*] = ;
      [*] = ;   if gIntRegister_BattleAttackHeroHandle <> 0 then
      [*] = ;      GameObjectExecuteStateByHandle(gIntRegister_BattleAttackHeroHandle, 'ClearSiteLoot');
      [*] = ;
      [*] = ;   if gIntRegister_BattleDefendHeroHandle <> 0 then
      [*] = ;      GameObjectExecuteStateByHandle(gIntRegister_BattleDefendHeroHandle, 'ClearSiteLoot');
      [*] = ;
      [*] = ;   if gBoolRegister_IsHumanPlayer then
      [*] = ;   begin
      [*] = ;      gBoolRegister_GUIUpdateInterfacePanel := true;
      [*] = ;
      [*] = ;      //if not (gBoolRegister_ArenaBattle and gBoolRegister_ArenaWatcher) then
      [*] = ;      gBoolRegister_GUIUpdateBattlePlacementMode := true;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      ExecuteState('bat.CheckSabotage');
      [*] = ;
      [*] = ;   if gBoolRegister_ArenaBattle and gBoolRegister_ArenaWatcher then
      [*] = ;   begin
      [*] = ;      SetPlayerBoolValueIndByHandle(attackPlHandle, gc_battle_PLStack_bAutoBattle, true);
      [*] = ;      SetPlayerBoolValueIndByHandle(defendPlHandle, gc_battle_PLStack_bAutoBattle, true);
      [*] = ;      //gBoolRegister_BattlePlaceMode := false;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;var attInit : Integer = 0;
      [*] = ;if gIntRegister_BattleAttackHeroHandle <> 0 then
      [*] = ;begin
      [*] = ;   IntRegister0 := gc_map_hero_iInitiative;
      [*] = ;   GameObjectExecuteStateByHandle(gIntRegister_BattleAttackHeroHandle, 'GetProperty');
      [*] = ;   attInit := IntRegister1;
      [*] = ;end
      [*] = ;else
      [*] = ;   attInit := ParserGetIntValueByKeyByHandle(gIntRegister_BattleAttackArmy, 'Initiative');
      [*] = ;
      [*] = ;var defInit : Integer = 0;
      [*] = ;if gIntRegister_BattleDefendHeroHandle <> 0 then
      [*] = ;begin
      [*] = ;   IntRegister0 := gc_map_hero_iInitiative;
      [*] = ;   GameObjectExecuteStateByHandle(gIntRegister_BattleDefendHeroHandle, 'GetProperty');
      [*] = ;   defInit := IntRegister1;
      [*] = ;end
      [*] = ;else
      [*] = ;   defInit := ParserGetIntValueByKeyByHandle(gIntRegister_BattleDefendArmy, 'Initiative');
      [*] = ;
      [*] = ;if defInit > attInit then
      [*] = ;begin
      [*] = ;   plHandle := defendPlHandle;
      [*] = ;   gIntRegister_BattleCurPlIndex := GetPlayerIndexByHandle(defendPlHandle);
      [*] = ;
      [*] = ;   if (not _misc_IsLanBattle) and SameText(dCMode, 'cmPlayer') then
      [*] = ;   for i := GetPlayerGameObjectsCountByHandle(attackPlHandle)-1 downto 0 do
      [*] = ;      SetGameObjectVisibleByHandle(GetGameObjectHandleByIndex(i, attackPlHandle), false);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   plHandle := attackPlHandle;
      [*] = ;   gIntRegister_BattleCurPlIndex := GetPlayerIndexByHandle(attackPlHandle);
      [*] = ;
      [*] = ;   if (not _misc_IsLanBattle) and SameText(aCMode, 'cmPlayer') then
      [*] = ;   for i := GetPlayerGameObjectsCountByHandle(defendPlHandle)-1 downto 0 do
      [*] = ;      SetGameObjectVisibleByHandle(GetGameObjectHandleByIndex(i, defendPlHandle), false);
      [*] = ;end;
      [*] = ;
      [*] = ;//if _log then _Log_gui('Before turn [498]');
      [*] = ;BoolRegister0 := false;
      [*] = ;PlayerExecuteStateByHandle(plHandle, 'BeforeTurn');
      [*] = ;//if _log then _Log_gui('After turn [501]');
      [*] = ;
      [*] = ;gStringRegister_AfterBattleQuery := '';
      [*] = ;
      [*] = ;var bothHuman : Boolean = SameText(aCMode, 'cmPlayer') and SameText(dCMode, 'cmPlayer');
      [*] = ;if ((gGame.gameType = gc_GameTypeHotseatBattle) or ((gGame.gameType = gc_GameTypeHotseat) and bothHuman)) and (not gBoolRegister_BattleSimulate) then
      [*] = ;   _gv_SetIOHandle(GetPlayerHandleByIndex(gIntRegister_BattleCurPlIndex),_log_name);
      [*] = ;
      [*] = ;if not gBoolRegister_BattleSimulate then
      [*] = ;   gIntRegister_NewBattle := -1;
      [*] = ;
      [*] = ;if not gBoolRegister_BattlePlaceMode then
      [*] = ;begin
      [*] = ;   BoolRegister0 := true;
      [*] = ;   PlayerExecuteStateByHandle(plHandle, 'MakeTurn');
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if gBoolRegister_IsHumanPlayer and (gTutorial.broken = 0) and (not bothHuman) then
      [*] = ;   begin
      [*] = ;      var heroHandle : Integer = 0;
      [*] = ;      if (GetPlayerIndexByHandle(gIntRegister_BattleAttackPlayer) = gIntRegister_MapMyPlayerIndex) and (gIntRegister_BattleAttackHeroHandle <> 0) then
      [*] = ;         heroHandle := gIntRegister_BattleAttackHeroHandle;
      [*] = ;
      [*] = ;      if (GetPlayerIndexByHandle(gIntRegister_BattleDefendPlayer) = gIntRegister_MapMyPlayerIndex) and (gIntRegister_BattleDefendHeroHandle <> 0) then
      [*] = ;         heroHandle := gIntRegister_BattleDefendHeroHandle;
      [*] = ;
      [*] = ;      if heroHandle <> 0 then
      [*] = ;      begin
      [*] = ;         GameObjectExecuteStateByHandle(heroHandle, 'IsWeaponBroken');
      [*] = ;         if BoolRegister0 then
      [*] = ;         begin
      [*] = ;            gBoolRegister_BrokenWeapon := true;
      [*] = ;            gBoolRegister_BtnSwitchWeaponBlink := true;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_log_map('gBoolRegister_IsHumanPlayer: '+BoolToStr(gBoolRegister_IsHumanPlayer));
      [*] = ;_log_map('gBoolRegister_IsDefenderBattle: '+BoolToStr(gBoolRegister_IsDefenderBattle));
      [*] = ;_log_map('gBoolRegister_IsDefenderAutoBattle: '+BoolToStr(gBoolRegister_IsDefenderAutoBattle));
      [*] = ;_log_map('gBoolRegister_IsAutoBattle: '+BoolToStr(gBoolRegister_IsAutoBattle));
      [*] = ;_log_map('gBoolRegister_QuickBattle: '+BoolToStr(gBoolRegister_QuickBattle));
      [*] = ;_log_map('gBoolRegister_BattleSimulate: '+BoolToStr(gBoolRegister_BattleSimulate));
      [*] = ;_log_map('gBoolRegister_RealAIBattle: '+BoolToStr(gBoolRegister_RealAIBattle));
      [*] = ;_log_map('gBoolRegister_ArenaBattle: '+BoolToStr(gBoolRegister_ArenaBattle));
      [*] = ;_log_map('gBoolRegister_ArenaWatcher: '+BoolToStr(gBoolRegister_ArenaWatcher));
      [*] = ;
      [*] = ;if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;   GUIExecuteState('battle.UnitHUDControl');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

