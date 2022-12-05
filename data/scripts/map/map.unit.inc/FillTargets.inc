section.begin
   Name = FillTargets
   Description : struct.begin
      [*] = ;OUT: BoolRegister0 - if target changes
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.UNIT.INC\FILLTARGETS';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var improvedAI : Boolean = (gGame.improvedai or ((gGame.gameType <> gc_GameTypeLanShard) and gProfile.improvedai));
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var myCustomName : String = GetGameObjectCustomNameByHandle(myGOHandle);
      [*] = ;
      [*] = ;var pStratHexCells : Integer = gStratHexCells.handle;
      [*] = ;var mapSizeX : Integer = gGame.map.x;
      [*] = ;var mapSizeY : Integer = gGame.map.y;
      [*] = ;
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;var plGem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;var plDiff : Integer = gGame.arrplayerdifficulty[GetPlayerIndexByHandle(myPlHandle)].basediff;
      [*] = ;var plProfile : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;var pProfile : Integer = ParserSelectByHandleByIndex(gPrototypeData.players.handle, plProfile);
      [*] = ;
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;var pMyEnemyTargets : Integer = ParserSelectByHandleByKey(pMyParser, 'EnemyTargets');
      [*] = ;var pMyEnemyPassTargets : Integer = ParserSelectByHandleByKey(pMyParser, 'EnemyPassTargets');
      [*] = ;var pMyNeutralTargets : Integer = ParserSelectByHandleByKey(pMyParser, 'NeutralTargets');
      [*] = ;var pMyPassableTargets : Integer = ParserSelectByHandleByKey(pMyParser, 'PassableTargets');
      [*] = ;var pMySiteTargets : Integer = ParserSelectByHandleByKey(pMyParser, 'SiteTargets');
      [*] = ;var pMySiegeTargets : Integer = ParserSelectByHandleByKey(pMyParser, 'SiegeTargets');
      [*] = ;var pMyRuinSiegeTargets : Integer = ParserSelectByHandleByKey(pMyParser, 'RuinSiegeTargets');
      [*] = ;
      [*] = ;var heroLevel : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iLevel);
      [*] = ;var maxTargets : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iMaxTargets);
      [*] = ;var curUID : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;var dummyHandle : Integer = GetGameObjectHandleByUniqueId(curUID);
      [*] = ;var notInBattle : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iNotInBattle);
      [*] = ;
      [*] = ;IntRegister0 := curUID;
      [*] = ;MapExecuteState('GetProvinceParserByUID');
      [*] = ;var pCurProvince : Integer = IntRegister1;
      [*] = ;var myX : Integer = ParserGetIntValueByKeyByHandle(pCurProvince, 'X');
      [*] = ;var myY : Integer = ParserGetIntValueByKeyByHandle(pCurProvince, 'Y');
      [*] = ;
      [*] = ;var isCastle : Boolean = ParserGetBoolValueByKeyByHandle(pCurProvince, 'Castle');
      [*] = ;var curProvExplored : Integer = ParserGetIntValueByKeyByHandle(pCurProvince, 'Explored');
      [*] = ;var provPlName : String = ParserGetValueByKeyByHandle(pCurProvince, 'Player');
      [*] = ;var provPlHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;var coast : Integer = ParserGetIntValueByKeyByHandle(pCurProvince, 'Coast');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;IntRegister0 := 4;
      [*] = ;IntRegister1 := 1;
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'CheckOuterBuildAbilityByParam1');
      [*] = ;var isGarrison : Boolean = isCastle or (IntRegister2 > 0);
      [*] = ;
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'GetPort');
      [*] = ;var port : Integer = IntRegister0;
      [*] = ;
      [*] = ;//ExecuteState('UpdateTrackNodes');
      [*] = ;//IntRegister0 := pCurProvince;
      [*] = ;//MapExecuteState('map.CalcMoveMap');
      [*] = ;ExecuteState('Select');
      [*] = ;
      [*] = ;PlayerExecuteStateByHandle(myPlHandle, 'GetCastleParser');
      [*] = ;var pCastle : Integer = IntRegister0;
      [*] = ;var castleUID : Integer = ParserGetIntValueByKeyByHandle(pCastle, 'DummyUID');
      [*] = ;var castleDist : Integer = ParserGetIntValueByKeyByHandle(pCastle, 'MoveMap');
      [*] = ;
      [*] = ;SetGameObjectIntValueIndByHandle(myGOHandle, gc_map_GOStack_MapUnit_iExploreTarget, 0);
      [*] = ;
      [*] = ;ParserClearByHandle(pMyEnemyTargets);
      [*] = ;ParserClearByHandle(pMyEnemyPassTargets);
      [*] = ;ParserClearByHandle(pMyNeutralTargets);
      [*] = ;ParserClearByHandle(pMyPassableTargets);
      [*] = ;ParserClearByHandle(pMySiteTargets);
      [*] = ;ParserClearByHandle(pMySiegeTargets);
      [*] = ;ParserClearByHandle(pMyRuinSiegeTargets);
      [*] = ;
      [*] = ;var i, j, k : Integer;
      [*] = ;var bChange : Boolean = false;
      [*] = ;
      [*] = ;// building shipyard if needed
      [*] = ;if (not isCastle) and (myPlHandle = provPlHandle) and (castleDist < 0) and (coast > 0) and (port = 0) then
      [*] = ;begin
      [*] = ;   var pProvOuterBuildings : Integer = ParserSelectByHandleByKey(pCurProvince, 'OuterBuildings');
      [*] = ;   var pChOuterBuilding : Integer = ParserSelectByHandleByIndex(pProvOuterBuildings, 0);
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pProvOuterBuildings)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pProvOuterBuilding : Integer = ParserSelectByHandleByIndex(pProvOuterBuildings, i);
      [*] = ;      var buildID : Integer = ParserGetIntValueByKeyByHandle(pProvOuterBuilding, 'OuterBuildID');
      [*] = ;
      [*] = ;      if buildID = 0 then
      [*] = ;      begin
      [*] = ;         pChOuterBuilding := pProvOuterBuilding;
      [*] = ;         break;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var id : Integer = ParserGetIntValueByKeyByHandle(pChOuterBuilding, 'OuterBuildID');
      [*] = ;
      [*] = ;         IntRegister0 := id;
      [*] = ;         MapExecuteState('GetOuterBuildParserByID');
      [*] = ;         var chGoldCost : Integer = ParserGetIntValueByKeyByHandle( IntRegister1, 'GoldCost');
      [*] = ;         var chGemCost : Integer = ParserGetIntValueByKeyByHandle( IntRegister1, 'GemCost');
      [*] = ;
      [*] = ;         IntRegister0 := buildID;
      [*] = ;         MapExecuteState('GetOuterBuildParserByID');
      [*] = ;         var curGoldCost : Integer = ParserGetIntValueByKeyByHandle( IntRegister1, 'GoldCost');
      [*] = ;         var curGemCost : Integer = ParserGetIntValueByKeyByHandle( IntRegister1, 'GemCost');
      [*] = ;
      [*] = ;         if curGoldCost * curGemCost * 5 / 2 < chGoldCost * chGemCost * 5 / 2 then
      [*] = ;            pChOuterBuilding := pProvOuterBuilding;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if pChOuterBuilding <> 0 then
      [*] = ;   begin
      [*] = ;      ParserSetIntValueByKeyByHandle(pChOuterBuilding, 'OuterBuildID', 10);
      [*] = ;      var outerBuild : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iCanOuterBuild);
      [*] = ;      SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iCanOuterBuild, outerBuild-1);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// cancel old orders
      [*] = ;var task : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iTask);
      [*] = ;if task <> gc_UnitTaskExplore then
      [*] = ;   SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iAITask, 0);
      [*] = ;// TODO: hack, to do it right
      [*] = ;if task <> gc_UnitTaskSiege then
      [*] = ;   SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iTask, gc_UnitTaskRest);
      [*] = ;
      [*] = ;// recruit units and build fort
      [*] = ;var pMyUnits : Integer = ParserSelectByHandleByKey(pMyParser, 'Units');
      [*] = ;var armyCount : Integer = ParserGetCountByHandle(pMyUnits)-1;
      [*] = ;if armyCount < 0 then
      [*] = ;   armyCount := 0;
      [*] = ;
      [*] = ;var myHeroPower : Integer = GetIntValueByIndex(gc_map_GOStack_MapUnit_iAIPower);
      [*] = ;var maxProvPowerDiff : Integer = 1 + myHeroPower div 2 + notInBattle div 5;
      [*] = ;var maxSitePowerDiff : Integer = 1 + myHeroPower div 2 + notInBattle div 5;
      [*] = ;var maxProvsConsider : Integer = 15;
      [*] = ;var maxSitesConsider : Integer = 20;
      [*] = ;
      [*] = ;ExecuteState('IsBestHero');
      [*] = ;var isBest : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var slotCount : Integer = 0;
      [*] = ;//check hero unit slots from rank 1 to 4:
      [*] = ;for i := 1 to 4 do
      [*] = ;begin
      [*] = ;   IntRegister0 := i;
      [*] = ;   ExecuteState('GetUnitSlots');
      [*] = ;   slotCount := slotCount + IntRegister1;
      [*] = ;end;
      [*] = ;
      [*] = ;if (armyCount < slotCount * 0.6) and isBest then
      [*] = ;   SetPlayerBoolValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_bExpandHalted, false);
      [*] = ;
      [*] = ;if (armyCount < slotCount * 0.6) and (not isGarrison) then
      [*] = ;begin
      [*] = ;   var pTrgProvince : Integer = 0;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pStratHexCells)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pProvince : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      var uid : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;      var tmpDummyHandle : Integer = GetGameObjectHandleByUniqueId(uid);
      [*] = ;
      [*] = ;      var tmpIsCastle : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;      var plName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;      var plHandle : Integer = GetPlayerHandleByName(plName);
      [*] = ;      //check if the building has garrison slots (ability 4 is garrison, param 1 is rank):
      [*] = ;      IntRegister0 := 4;
      [*] = ;      IntRegister1 := 1;
      [*] = ;      GameObjectExecuteStateByHandle(tmpDummyHandle, 'CheckOuterBuildAbilityByParam1');
      [*] = ;      var isGarrison : Boolean = tmpIsCastle or (IntRegister2 > 0);
      [*] = ;
      [*] = ;      GameObjectExecuteStateByHandle(tmpDummyHandle, 'IsUnderSiege');
      [*] = ;      var siege : Boolean = BoolRegister0;
      [*] = ;      //check if the province can provide troops and has shorter distance than previous province under iteration.
      [*] = ;      if (plHandle = myPlHandle) and isGarrison and (not siege) then
      [*] = ;      begin
      [*] = ;         var trgDist : Integer = ParserGetIntValueByKeyByHandle(pTrgProvince, 'MoveMap');
      [*] = ;         var dist : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'MoveMap');
      [*] = ;
      [*] = ;         if (pTrgProvince = 0) or ((dist >= 0) and (dist < trgDist)) then
      [*] = ;            pTrgProvince := pProvince;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var trgDist : Integer = ParserGetIntValueByKeyByHandle(pTrgProvince, 'MoveMap');
      [*] = ;   if (pTrgProvince = 0) or (trgDist > 3) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := pCurProvince;
      [*] = ;      PlayerExecuteStateByHandle(myPlHandle, 'TryBuildGarrison');
      [*] = ;      if BoolRegister0 then
      [*] = ;      begin
      [*] = ;         ExecuteState('HireUnits');
      [*] = ;         bChange := true;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// fill targets for siege help
      [*] = ;for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;   var isDead : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;   var trgGOPower : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iTargetPower);
      [*] = ;
      [*] = ;   var tmpUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;   IntRegister0 := tmpUID;
      [*] = ;   MapExecuteState('GetProvinceParserByUID');
      [*] = ;   var pProvince : Integer = IntRegister1;
      [*] = ;   var dist : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'MoveMap');
      [*] = ;   var plName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;   var plHandle : Integer = GetPlayerHandleByName(plName);
      [*] = ;
      [*] = ;   if (goHandle <> myGOHandle) and (not isDead) and (plHandle <> myPlHandle) and (plHandle <> 0) and (trgGOPower < 100) and (dist >= 0) then
      [*] = ;   begin
      [*] = ;      var pProvGarrison : Integer = ParserSelectByHandleByKey(pProvince, 'Garrison');
      [*] = ;      var pGarrisonUnits : Integer = ParserSelectByHandleByKey(pProvince, 'Units');
      [*] = ;
      [*] = ;      var tmpIsCastle : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;      var tmpDist : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'MoveMap');
      [*] = ;
      [*] = ;      IntRegister0 := pMyUnits;
      [*] = ;      IntRegister1 := myGOHandle;
      [*] = ;      IntRegister2 := myPlHandle;
      [*] = ;      IntRegister3 := pGarrisonUnits;
      [*] = ;      IntRegister4 := 0;
      [*] = ;      IntRegister5 := plHandle;
      [*] = ;      MapExecuteState('map.CompareArmiesStrength');
      [*] = ;      var tmpPower : Integer = IntRegister6;
      [*] = ;
      [*] = ;      // add siege target
      [*] = ;      var pNewTarget : Integer = 0;
      [*] = ;
      [*] = ;      if ParserGetCountByHandle(pMySiegeTargets) < maxTargets then
      [*] = ;         pNewTarget := ParserAddChildByIndex(pMySiegeTargets, '*')
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         for j := 0 to maxTargets-1 do
      [*] = ;         begin
      [*] = ;            var pMySiegeTarget : Integer = ParserSelectByHandleByIndex(pMySiegeTargets, j);
      [*] = ;
      [*] = ;            var trgDummyUID : Integer = ParserGetIntValueByKeyByHandle(pMySiegeTarget, 'DummyUID');
      [*] = ;            var trgDist : Integer = ParserGetIntValueByKeyByHandle(pMySiegeTarget, 'Distance');
      [*] = ;            var trgPower : Integer = ParserGetIntValueByKeyByHandle(pMySiegeTarget, 'Power');
      [*] = ;
      [*] = ;            if pNewTarget = 0 then
      [*] = ;            begin
      [*] = ;               if (tmpIsCastle and (trgDummyUID <> castleUID)) or (trgDist > tmpDist) or ((trgDist = tmpDist) and (trgPower < tmpPower)) then
      [*] = ;               pNewTarget := pMySiegeTarget;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var selDist : Integer = ParserGetIntValueByKeyByHandle(pNewTarget, 'Distance');
      [*] = ;               var selPower : Integer = ParserGetIntValueByKeyByHandle(pNewTarget, 'Power');
      [*] = ;
      [*] = ;               if (trgDummyUID <> castleUID) and ((trgDist > selDist) or ((trgDist = selDist) and (trgPower < selPower))) then
      [*] = ;               pNewTarget := pMySiegeTarget;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if pNewTarget <> 0 then
      [*] = ;      begin
      [*] = ;         _gui_ProgressCalculations(_log_name+' Siege target for ' + myCustomName + ' (DummyUID = ' + IntToStr(tmpUID) + ', power = ' + IntToStr(tmpPower) + ')');
      [*] = ;         ParserSetIntValueByKeyByHandle(pNewTarget, 'DummyUID', tmpUID);
      [*] = ;         ParserSetIntValueByKeyByHandle(pNewTarget, 'Distance', tmpDist);
      [*] = ;         ParserSetIntValueByKeyByHandle(pNewTarget, 'Power', tmpPower);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pNewTarget, 'HeroDeath', false);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// fill targets for interfere siege
      [*] = ;for i := ParserGetCountByHandle(pStratHexCells)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pProvince : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   if ParserGetIntValueByKeyByHandle(pProvince, 'MoveMap') >= 0 then
      [*] = ;   begin
      [*] = ;      var tmpUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;      var dHandle : Integer = GetGameObjectHandleByUniqueId(tmpUID);
      [*] = ;
      [*] = ;      var plName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;      var plHandle : Integer = GetPlayerHandleByName(plName);
      [*] = ;
      [*] = ;      GameObjectExecuteStateByHandle(dHandle, 'IsUnderSiege');
      [*] = ;      var isSiege : Boolean = BoolRegister0;
      [*] = ;      var siegePlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;      if (plHandle = myPlHandle) and isSiege then
      [*] = ;      begin
      [*] = ;         var tmpIsCastle : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;         var tmpDist : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'MoveMap');
      [*] = ;         var tmpPower : Integer = 1000;
      [*] = ;
      [*] = ;         if siegePlHandle = 0 then
      [*] = ;         begin
      [*] = ;            var pProvGuard : Integer = ParserSelectByHandleByKey(pProvince, 'Guard');
      [*] = ;            var pGuardUnits : Integer = ParserSelectByHandleByKey(pProvince, 'Units');
      [*] = ;
      [*] = ;            IntRegister0 := pMyUnits;
      [*] = ;            IntRegister1 := myGOHandle;
      [*] = ;            IntRegister2 := myPlHandle;
      [*] = ;            IntRegister3 := pGuardUnits;
      [*] = ;            IntRegister4 := 0;
      [*] = ;            IntRegister5 := 0;
      [*] = ;            MapExecuteState('map.CompareArmiesStrength');
      [*] = ;            tmpPower := IntRegister6;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            for j := GetPlayerGameObjectsCountByHandle(siegePlHandle)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var goHandle : Integer = GetGameObjectHandleByIndex(j, siegePlHandle);
      [*] = ;               var isDead : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;               var trgUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;
      [*] = ;               if (trgUID = tmpUID) and (not isDead) then
      [*] = ;               begin
      [*] = ;                  var pEnemyParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;                  var pEnemyUnits : Integer = ParserSelectByHandleByKey(pEnemyParser, 'Units');
      [*] = ;
      [*] = ;                  IntRegister0 := pMyUnits;
      [*] = ;                  IntRegister1 := myGOHandle;
      [*] = ;                  IntRegister2 := myPlHandle;
      [*] = ;                  IntRegister3 := pEnemyUnits;
      [*] = ;                  IntRegister4 := goHandle;
      [*] = ;                  IntRegister5 := siegePlHandle;
      [*] = ;                  MapExecuteState('map.CompareArmiesStrength');
      [*] = ;                  if IntRegister6 < tmpPower then
      [*] = ;                  tmpPower := IntRegister6;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         // add interfere siege target
      [*] = ;         var pNewTarget : Integer = 0;
      [*] = ;
      [*] = ;         if ParserGetCountByHandle(pMyRuinSiegeTargets) < maxTargets then
      [*] = ;            pNewTarget := ParserAddChildByIndex(pMyRuinSiegeTargets, '*')
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            for j := 0 to maxTargets-1 do
      [*] = ;            begin
      [*] = ;               var pMySiegeTarget : Integer = ParserSelectByHandleByIndex(pMySiegeTargets, j);
      [*] = ;
      [*] = ;               var trgDummyUID : Integer = ParserGetIntValueByKeyByHandle(pMySiegeTarget, 'DummyUID');
      [*] = ;               var trgDist : Integer = ParserGetIntValueByKeyByHandle(pMySiegeTarget, 'Distance');
      [*] = ;               var trgPower : Integer = ParserGetIntValueByKeyByHandle(pMySiegeTarget, 'Power');
      [*] = ;
      [*] = ;               if pNewTarget = 0 then
      [*] = ;               begin
      [*] = ;                  if tmpIsCastle or (trgPower < tmpPower) or ((trgPower = tmpPower) and (trgDist > tmpDist)) then
      [*] = ;                  pNewTarget := pMySiegeTarget;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  var selDist : Integer = ParserGetIntValueByKeyByHandle(pNewTarget, 'Distance');
      [*] = ;                  var selPower : Integer = ParserGetIntValueByKeyByHandle(pNewTarget, 'Power');
      [*] = ;
      [*] = ;                  if (trgDummyUID <> castleUID) and ((trgPower < selPower) or ((trgPower = selPower) and (trgDist > selDist))) then
      [*] = ;                     pNewTarget := pMySiegeTarget;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if pNewTarget <> 0 then
      [*] = ;         begin
      [*] = ;            _gui_ProgressCalculations(_log_name+' Ruin siege target for ' + myCustomName + ' (DummyUID = ' + IntToStr(tmpUID) + ', power = ' + IntToStr(tmpPower) + ')');
      [*] = ;            ParserSetIntValueByKeyByHandle(pNewTarget, 'DummyUID', tmpUID);
      [*] = ;            ParserSetIntValueByKeyByHandle(pNewTarget, 'Distance', tmpDist);
      [*] = ;            ParserSetIntValueByKeyByHandle(pNewTarget, 'Power', tmpPower);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pNewTarget, 'HeroDeath', false);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;// search for province to attack
      [*] = ;var provInfo : array [0..100] of array [0..2] of Integer;
      [*] = ;var powers_num:Integer=0;
      [*] = ;var plHandle, pProvince : Integer;
      [*] = ;var power, newProv, newUnion, newDist : Integer;
      [*] = ;var pGuardUnits : Integer;
      [*] = ;var provGuard : Integer;
      [*] = ;var dummyUIDN : Integer;
      [*] = ;var dummyHandleN : Integer;
      [*] = ;var provPlayable : Boolean;
      [*] = ;var canPass : Boolean;
      [*] = ;var nc, nTmpProv, nTmpPower, nTmpUnion, nTmpDist, provIdx, passPlIndex, sector, ring, rowIndex, x, y, latestPassableRing, moveMap : Integer;
      [*] = ;ring := 1;
      [*] = ;sector := 0;
      [*] = ;rowIndex := 0;
      [*] = ;latestPassableRing := 0;
      [*] = ;
      [*] = ;if not improvedAI then
      [*] = ;for i := ParserGetCountByHandle(pStratHexCells)-1 downto 0 do
      [*] = ;begin
      [*] = ;   pProvince := ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   var moveMap : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'MoveMap');
      [*] = ;   if moveMap > 0 then
      [*] = ;   begin
      [*] = ;      var passPlIndex : Integer;
      [*] = ;
      [*] = ;      dummyUIDN := ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;      if dummyUIDN > 0 then
      [*] = ;      begin
      [*] = ;         dummyHandleN := GetGameObjectHandleByUniqueId(dummyUIDN);
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandleN, 'IsPlayable');
      [*] = ;         provPlayable := BoolRegister0;
      [*] = ;
      [*] = ;         if provPlayable then
      [*] = ;         begin
      [*] = ;            IntRegister0 := pProvince;
      [*] = ;            PlayerExecuteStateByHandle(myPlHandle, 'CanPassProvince');
      [*] = ;            canPass := BoolRegister0;
      [*] = ;            passPlIndex := IntRegister1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (dummyUIDN > 0) and provPlayable and (not canPass) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := pProvince;
      [*] = ;         ExecuteState('CompareArmiesStrength');
      [*] = ;         var power : Integer = IntRegister1;
      [*] = ;         newProv := pProvince;
      [*] = ;         _gui_ProgressCalculations(_log_name+' Province [' + IntToStr(dummyUIDN) + '] approximate power: ' + IntToStr(power));
      [*] = ;
      [*] = ;         newUnion := 0;
      [*] = ;         var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;         var provPlHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;         var provPlIndex : Integer = GetPlayerIndexByHandle(provPlHandle);
      [*] = ;
      [*] = ;         if provPlIndex >= 0 then
      [*] = ;         begin
      [*] = ;            var isCastle : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'IsCastle');
      [*] = ;
      [*] = ;            var kill : Integer = 0;
      [*] = ;            if isCastle then
      [*] = ;            begin
      [*] = ;               if power > 100 then
      [*] = ;                  kill := 1000
      [*] = ;               else
      [*] = ;                  kill := power div 2;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if power > 100 then
      [*] = ;                  kill := Min(10, (power - 100) div 10 + 1);
      [*] = ;            end;
      [*] = ;
      [*] = ;            gArrDiplomacy[myPlIndex][provPlIndex].canKill := gArrDiplomacy[myPlIndex][provPlIndex].canKill + kill;
      [*] = ;            if gArrDiplomacy[myPlIndex][provPlIndex].canKill < 0 then
      [*] = ;               gArrDiplomacy[myPlIndex][provPlIndex].canKill := 0;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if power >= 100 then
      [*] = ;               SetPlayerBoolValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_bExpandHalted, false);
      [*] = ;
      [*] = ;            var plUnion : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iUnion);
      [*] = ;            var provRaceID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceRace');
      [*] = ;            var pProvRace : Integer = ParserSelectByHandleByIndex(gPrototypeData.races.handle, provRaceID);
      [*] = ;
      [*] = ;            if (provRaceID > 0) and (plUnion = provRaceID) then
      [*] = ;            begin
      [*] = ;               power := 1000;
      [*] = ;               newUnion := 1;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if gGame.currentTurn >= 15 - plDiff then
      [*] = ;               begin
      [*] = ;                  if (provRaceID > 1) and (plProfile > 0) then
      [*] = ;                  begin
      [*] = ;                     var aiUnion : Integer = 0;
      [*] = ;                     var aiCounter : Integer = 0;
      [*] = ;
      [*] = ;                     case plProfile of
      [*] = ;                        4 :
      [*] = ;                        if provRaceID = 6 then
      [*] = ;                        begin
      [*] = ;                           aiUnion := 6;
      [*] = ;                           aiCounter := 0;
      [*] = ;                        end;
      [*] = ;                        5 :
      [*] = ;                        if provRaceID = 2 then
      [*] = ;                        begin
      [*] = ;                           aiUnion := 2;
      [*] = ;                           aiCounter := 0;
      [*] = ;                        end;
      [*] = ;                        6 :
      [*] = ;                        if provRaceID = 3 then
      [*] = ;                        begin
      [*] = ;                           aiUnion := 3;
      [*] = ;                           aiCounter := 0;
      [*] = ;                        end;
      [*] = ;                        10 :
      [*] = ;                        if provRaceID = 7 then
      [*] = ;                        begin
      [*] = ;                           aiUnion := 7;
      [*] = ;                           aiCounter := 0;
      [*] = ;                        end;
      [*] = ;                        11 :
      [*] = ;                        if provRaceID = 5 then
      [*] = ;                        begin
      [*] = ;                           aiUnion := 5;
      [*] = ;                           aiCounter := 0;
      [*] = ;                        end;
      [*] = ;                        16 :
      [*] = ;                        if provRaceID = 4 then
      [*] = ;                        begin
      [*] = ;                           aiUnion := 4;
      [*] = ;                           aiCounter := 0;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     if aiUnion > 0 then
      [*] = ;                     begin
      [*] = ;                        if aiCounter > 0 then
      [*] = ;                        begin
      [*] = ;                           SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iAIUnionRace, aiUnion);
      [*] = ;                           SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iAIUnionCounter, aiCounter);
      [*] = ;                        end
      [*] = ;                        else//if counter reaches zero, gain union
      [*] = ;                           SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iUnion, aiUnion);
      [*] = ;                     end;
      [*] = ;						//if not predefined union target (once only)
      [*] = ;                     if GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iAIUnionRace) = 0 then
      [*] = ;                     begin
      [*] = ;                        var prRaceKarma : Integer = ParserGetIntValueByKeyByHandle(pProvRace, 'Karma');
      [*] = ;                        var plKarma : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'Karma');
      [*] = ;
      [*] = ;                        if plKarma * prRaceKarma >= 0 then
      [*] = ;                        begin
      [*] = ;                           var counter : Integer = Floor((1 + RandomExt) * (10 - plDiff));
      [*] = ;
      [*] = ;                           SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iAIUnionRace, provRaceID);
      [*] = ;                           SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iAIUnionCounter, counter);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     if (provRaceID > 0) and (provRaceID = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iAIUnionRace)) then
      [*] = ;                     begin//if counter is zero for the target union, the player is not afraid of the province, else, do not attack.
      [*] = ;                        if GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iAIUnionCounter) = 0 then
      [*] = ;                           power := 2000
      [*] = ;                        else
      [*] = ;                           power := -200;
      [*] = ;
      [*] = ;                        newUnion := 1;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if ((provPlIndex = -1) or (gArrDiplomacy[myPlIndex][provPlIndex].treaty = 1)) and
      [*] = ;         ((passPlIndex = -1) or ((gArrDiplomacy[myPlIndex][passPlIndex].treaty = 1) and (moveMap = 1))) then
      [*] = ;         begin
      [*] = ;            if powers_num < 100 then
      [*] = ;            begin
      [*] = ;               for nc := 0 to powers_num-1 do
      [*] = ;               begin
      [*] = ;                  if provInfo[nc,1] < power then
      [*] = ;                  begin
      [*] = ;                     nTmpProv := provInfo[nc,0];
      [*] = ;                     nTmpPower := provInfo[nc,1];
      [*] = ;                     nTmpUnion := provInfo[nc,2];
      [*] = ;                     provInfo[nc,0] := newProv;
      [*] = ;                     provInfo[nc,1] := power;
      [*] = ;                     provInfo[nc,2] := newUnion;
      [*] = ;                     newProv := nTmpProv;
      [*] = ;                     power := nTmpPower;
      [*] = ;                     newUnion := nTmpUnion;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               provInfo[powers_num,0] := newProv;
      [*] = ;               provInfo[powers_num,1] := power;
      [*] = ;               provInfo[powers_num,2] := newUnion;
      [*] = ;               powers_num := powers_num+1;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               ErrorLogI('Too many target provinces (100)');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;repeat
      [*] = ;   pProvince := 0;
      [*] = ;   _map_GetHexOutward(myX, myY, sector, ring, rowIndex, x, y);
      [*] = ;   if (x >= 0) and (x < mapSizeX) and (y >= 0) and (y < mapSizeY) then
      [*] = ;      pProvince := _map_GetStratHex(x, y);
      [*] = ;      
      [*] = ;   if rowIndex = ring-1 then
      [*] = ;   begin
      [*] = ;      rowIndex := 0;
      [*] = ;      if sector = 5 then
      [*] = ;      begin
      [*] = ;         sector := 0;
      [*] = ;         ring := ring + 1;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         sector := sector + 1;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      rowIndex := rowIndex + 1;
      [*] = ;   
      [*] = ;   moveMap := ParserGetIntValueByKeyByHandle(pProvince, 'MoveMap');
      [*] = ;   if (pProvince <> 0) and (moveMap > 0) then
      [*] = ;   begin
      [*] = ;      latestPassableRing := ring;
      [*] = ;      var pProvGuard : Integer = ParserSelectByHandleByKey(pProvince, 'Guard');
      [*] = ;      var pGuard : Integer = ParserSelectByHandleByIndex(gPrototypeData.guards.handle, ParserGetIntValueByKeyByHandle(pProvGuard, 'GuardID'));
      [*] = ;      var guardPower : Integer = ParserGetIntValueByKeyByHandle(pGuard, 'Power');
      [*] = ;      
      [*] = ;      if (guardPower = 0) or (guardPower - myHeroPower <= maxProvPowerDiff) then
      [*] = ;      begin
      [*] = ;         passPlIndex := 0;
      [*] = ;
      [*] = ;         dummyUIDN := ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;         if dummyUIDN > 0 then
      [*] = ;         begin
      [*] = ;            dummyHandleN := GetGameObjectHandleByUniqueId(dummyUIDN);
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandleN, 'IsPlayable');
      [*] = ;            provPlayable := BoolRegister0;
      [*] = ;
      [*] = ;            if provPlayable then
      [*] = ;            begin
      [*] = ;               IntRegister0 := pProvince;
      [*] = ;               PlayerExecuteStateByHandle(myPlHandle, 'CanPassProvince');
      [*] = ;               canPass := BoolRegister0;
      [*] = ;               passPlIndex := IntRegister1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (dummyUIDN > 0) and provPlayable and (not canPass) then
      [*] = ;         begin
      [*] = ;            var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;            var provPlHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;            var provPlIndex : Integer = GetPlayerIndexByHandle(provPlHandle);
      [*] = ;
      [*] = ;            IntRegister0 := pProvince;
      [*] = ;            IntRegister1 := 1;
      [*] = ;            IntRegister2 := -1;
      [*] = ;            ExecuteState('GetProvEnemyArmy');
      [*] = ;            var pEnemyArmy : Integer = IntRegister3;
      [*] = ;            var enHeroHandle : Integer = IntRegister4;
      [*] = ;            var pEnemyUnits : Integer = ParserSelectByHandleByKey(pEnemyArmy, 'Units');
      [*] = ;
      [*] = ;            var enPlHandle : Integer = provPlHandle;
      [*] = ;            if enHeroHandle <> 0 then
      [*] = ;            enPlHandle := GetGameObjectPlayerHandleByHandle(enHeroHandle);
      [*] = ;
      [*] = ;            IntRegister0 := pMyUnits;
      [*] = ;            IntRegister1 := myGOHandle;
      [*] = ;            IntRegister2 := myPlHandle;
      [*] = ;            IntRegister3 := pEnemyUnits;
      [*] = ;            IntRegister4 := enHeroHandle;
      [*] = ;            IntRegister5 := enPlHandle;
      [*] = ;            MapExecuteState('map.CompareArmiesStrength');
      [*] = ;            var power : Integer = IntRegister6;
      [*] = ;
      [*] = ;           // IntRegister1 := power;
      [*] = ;           // IntRegister0 := pProvince;
      [*] = ;           // ExecuteState('CompareArmiesStrength');
      [*] = ;           // var power : Integer = IntRegister1;
      [*] = ;            newProv := pProvince;
      [*] = ;            _gui_ProgressCalculations(_log_name+' Province [' + IntToStr(dummyUIDN) + '] approximate power: ' + IntToStr(power) +' guard power: '+IntToStr(guardPower));
      [*] = ;
      [*] = ;            newUnion := 0;
      [*] = ;
      [*] = ;            if provPlIndex >= 0 then
      [*] = ;            begin
      [*] = ;               var isCastle : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'IsCastle');
      [*] = ;
      [*] = ;               var kill : Integer = 0;
      [*] = ;               if isCastle then
      [*] = ;               begin
      [*] = ;                  if power > 100 then
      [*] = ;                     kill := 1000
      [*] = ;                  else
      [*] = ;                     kill := power div 2;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if power > 100 then
      [*] = ;                     kill := Min(10, (power - 100) div 10 + 1);
      [*] = ;               end;
      [*] = ;
      [*] = ;               gArrDiplomacy[myPlIndex][provPlIndex].canKill := gArrDiplomacy[myPlIndex][provPlIndex].canKill + kill;
      [*] = ;               if gArrDiplomacy[myPlIndex][provPlIndex].canKill < 0 then
      [*] = ;                  gArrDiplomacy[myPlIndex][provPlIndex].canKill := 0;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if power >= 100 then
      [*] = ;                  SetPlayerBoolValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_bExpandHalted, false);
      [*] = ;
      [*] = ;               var plUnion : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iUnion);
      [*] = ;               var provRaceID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceRace');
      [*] = ;               var pProvRace : Integer = ParserSelectByHandleByIndex(gPrototypeData.races.handle, provRaceID);
      [*] = ;
      [*] = ;               if (provRaceID > 0) and (plUnion = provRaceID) then
      [*] = ;               begin
      [*] = ;                  power := 1000;
      [*] = ;                  newUnion := 1;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if gGame.currentTurn >= 15 - plDiff then
      [*] = ;                  begin
      [*] = ;                     if (provRaceID > 1) and (plProfile > 0) then
      [*] = ;                     begin
      [*] = ;                        var aiUnion : Integer = 0;
      [*] = ;                        var aiCounter : Integer = 0;
      [*] = ;   
      [*] = ;                        case plProfile of
      [*] = ;                           4 :
      [*] = ;                           if provRaceID = 6 then
      [*] = ;                           begin
      [*] = ;                              aiUnion := 6;
      [*] = ;                              aiCounter := 0;
      [*] = ;                           end;
      [*] = ;                           5 :
      [*] = ;                           if provRaceID = 2 then
      [*] = ;                           begin
      [*] = ;                              aiUnion := 2;
      [*] = ;                              aiCounter := 0;
      [*] = ;                           end;
      [*] = ;                           6 :
      [*] = ;                           if provRaceID = 3 then
      [*] = ;                           begin
      [*] = ;                              aiUnion := 3;
      [*] = ;                              aiCounter := 0;
      [*] = ;                           end;
      [*] = ;                           10 :
      [*] = ;                           if provRaceID = 7 then
      [*] = ;                           begin
      [*] = ;                              aiUnion := 7;
      [*] = ;                              aiCounter := 0;
      [*] = ;                           end;
      [*] = ;                           11 :
      [*] = ;                           if provRaceID = 5 then
      [*] = ;                           begin
      [*] = ;                              aiUnion := 5;
      [*] = ;                              aiCounter := 0;
      [*] = ;                           end;
      [*] = ;                           16 :
      [*] = ;                           if provRaceID = 4 then
      [*] = ;                           begin
      [*] = ;                              aiUnion := 4;
      [*] = ;                              aiCounter := 0;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;
      [*] = ;                        if aiUnion > 0 then
      [*] = ;                        begin
      [*] = ;                           if aiCounter > 0 then
      [*] = ;                           begin
      [*] = ;                              SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iAIUnionRace, aiUnion);
      [*] = ;                              SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iAIUnionCounter, aiCounter);
      [*] = ;                           end
      [*] = ;                           else
      [*] = ;                              SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iUnion, aiUnion);
      [*] = ;                        end;
      [*] = ;
      [*] = ;                       if GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iAIUnionRace) = 0 then
      [*] = ;                        begin
      [*] = ;                           var prRaceKarma : Integer = ParserGetIntValueByKeyByHandle(pProvRace, 'Karma');
      [*] = ;                           var plKarma : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'Karma');
      [*] = ;
      [*] = ;                           if plKarma * prRaceKarma >= 0 then
      [*] = ;                           begin
      [*] = ;                              var counter : Integer = Floor((1 + RandomExt) * (10 - plDiff));
      [*] = ;
      [*] = ;                              SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iAIUnionRace, provRaceID);
      [*] = ;                              SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iAIUnionCounter, counter);
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;
      [*] = ;                        if (provRaceID > 0) and (provRaceID = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iAIUnionRace)) then
      [*] = ;                        begin
      [*] = ;                           if GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iAIUnionCounter) = 0 then
      [*] = ;                              power := 2000
      [*] = ;                           else
      [*] = ;                              power := -200;
      [*] = ;
      [*] = ;                           newUnion := 1;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if ((provPlIndex = -1) or (gArrDiplomacy[myPlIndex][provPlIndex].treaty = 1)) and
      [*] = ;            ((passPlIndex = -1) or ((gArrDiplomacy[myPlIndex][passPlIndex].treaty = 1) and (moveMap = 1))) then
      [*] = ;            begin
      [*] = ;               if powers_num < maxProvsConsider then
      [*] = ;               begin
      [*] = ;                  for nc := 0 to powers_num-1 do
      [*] = ;                  begin
      [*] = ;                     if provInfo[nc,1] < power then
      [*] = ;                     begin
      [*] = ;                        nTmpProv := provInfo[nc,0];
      [*] = ;                        nTmpPower := provInfo[nc,1];
      [*] = ;                        nTmpUnion := provInfo[nc,2];
      [*] = ;                        provInfo[nc,0] := newProv;
      [*] = ;                        provInfo[nc,1] := power;
      [*] = ;                        provInfo[nc,2] := newUnion;
      [*] = ;                        newProv := nTmpProv;
      [*] = ;                        power := nTmpPower;
      [*] = ;                        newUnion := nTmpUnion;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  provInfo[powers_num,0] := newProv;
      [*] = ;                  provInfo[powers_num,1] := power;
      [*] = ;                  provInfo[powers_num,2] := newUnion;
      [*] = ;                  powers_num := powers_num+1;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  ErrorLogI('Too many target provinces');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;until (powers_num = maxProvsConsider) or (ring > latestPassableRing + 3);
      [*] = ;   _log_map('prov powers_num '+IntToStr(powers_num));
      [*] = ;
      [*] = ;var res_batl, pMyTarget, simulations_count, p : Integer;
      [*] = ;res_batl := plDiff;
      [*] = ;_gui_ProgressCalculations(_log_name+'[1] Diff:' + IntToStr(res_batl));
      [*] = ;if res_batl < 0 then
      [*] = ;begin
      [*] = ;   ErrorLogI('Player difficulty is < 0 ('+IntToStr(res_batl)+')');
      [*] = ;   res_batl := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;if (not improvedAI) and (RandomExt<0.8) then
      [*] = ;   res_batl := 0; // hot optimization 0 means 2 battles
      [*] = ;
      [*] = ;simulations_count := Min(powers_num-1, res_batl+1);
      [*] = ;for i := 0 to simulations_count do
      [*] = ;begin
      [*] = ;   var pProvince : Integer = provInfo[i, 0];
      [*] = ;   var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;   IntRegister0 := pProvince;
      [*] = ;   IntRegister1 := provInfo[i, 1];
      [*] = ;   BoolRegister0 := (provInfo[i, 2] > 0);
      [*] = ;   ExecuteState('TryAttackProvince');
      [*] = ;   if ParserGetCountByHandle(pMyPassableTargets)>0 then
      [*] = ;   begin
      [*] = ;      pMyTarget := ParserSelectByHandleByIndex(pMyPassableTargets, ParserGetCountByHandle(pMyPassableTargets)-1);
      [*] = ;      res_batl := ParserGetIntValueByKeyByHandle(pMyTarget, 'Power');
      [*] = ;   end;
      [*] = ;   if ParserGetCountByHandle(pMyNeutralTargets)>0 then
      [*] = ;   begin
      [*] = ;      pMyTarget := ParserSelectByHandleByIndex(pMyNeutralTargets, ParserGetCountByHandle(pMyNeutralTargets)-1);
      [*] = ;      p := ParserGetIntValueByKeyByHandle(pMyTarget, 'Power');
      [*] = ;      if res_batl<p then
      [*] = ;         res_batl := p;
      [*] = ;   end;
      [*] = ;   if ParserGetCountByHandle(pMyEnemyPassTargets)>0 then
      [*] = ;   begin
      [*] = ;      pMyTarget := ParserSelectByHandleByIndex(pMyEnemyPassTargets, ParserGetCountByHandle(pMyEnemyPassTargets)-1);
      [*] = ;      p := ParserGetIntValueByKeyByHandle(pMyTarget, 'Power');
      [*] = ;      if res_batl<p then
      [*] = ;         res_batl := p;
      [*] = ;   end;
      [*] = ;   if ParserGetCountByHandle(pMyEnemyTargets)>0 then
      [*] = ;   begin
      [*] = ;      pMyTarget := ParserSelectByHandleByIndex(pMyEnemyTargets, ParserGetCountByHandle(pMyEnemyTargets)-1);
      [*] = ;      p := ParserGetIntValueByKeyByHandle(pMyTarget, 'Power');
      [*] = ;      if res_batl<p then
      [*] = ;         res_batl := p;
      [*] = ;   end;
      [*] = ;   _gui_ProgressCalculations(_log_name+' Province [' + IntToStr(dummyUID) + '] precise power: ' + IntToStr(res_batl));
      [*] = ;   if res_batl>100 then
      [*] = ;      break;
      [*] = ;end;
      [*] = ;
      [*] = ;_gui_ProgressCalculations(_log_name+' [Hire units task]');
      [*] = ;// search for province to hire units
      [*] = ;SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iGarrisonUID, 0);
      [*] = ;
      [*] = ;if slotCount > armyCount then
      [*] = ;begin
      [*] = ;   if plGold > 50 + gGame.currentTurn then
      [*] = ;   begin
      [*] = ;      var pTrgProvince : Integer = 0;
      [*] = ;
      [*] = ;      for i := ParserGetCountByHandle(pStratHexCells)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pProvince : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;         var dist : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'MoveMap');
      [*] = ;         if dist >= 0 then
      [*] = ;         begin
      [*] = ;            var isCastle1 : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;            var dummyUID1 : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;            var dummyHandle1 : Integer = GetGameObjectHandleByUniqueId(dummyUID1);
      [*] = ;            var plName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;            var plHandle : Integer = GetPlayerHandleByName(plName);
      [*] = ;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle1, 'IsUnderSiege');
      [*] = ;            var isSiege1 : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;            IntRegister0 := 4;
      [*] = ;            IntRegister1 := 1;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle1, 'CheckOuterBuildAbilityByParam1');
      [*] = ;            var isGarrison1 : Boolean = isCastle1 or (IntRegister2 > 0);
      [*] = ;
      [*] = ;            if (plHandle = myPlHandle) and isGarrison1 and (not isSiege1) then
      [*] = ;            begin
      [*] = ;               var trgDist : Integer = ParserGetIntValueByKeyByHandle(pTrgProvince, 'MoveMap');
      [*] = ;               if (pTrgProvince = 0) or (dist < trgDist) then
      [*] = ;               pTrgProvince := pProvince;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if pTrgProvince <> 0 then
      [*] = ;      begin
      [*] = ;         var trgUID : Integer = ParserGetIntValueByKeyByHandle(pTrgProvince, 'DummyUID');
      [*] = ;
      [*] = ;         if armyCount < 0.6 * slotCount then
      [*] = ;         begin
      [*] = ;            var dist : Integer = ParserGetIntValueByKeyByHandle(pTrgProvince, 'MoveMap');
      [*] = ;            if dist > 3 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := pCurProvince;
      [*] = ;               PlayerExecuteStateByHandle(myPlHandle, 'TryBuildGarrison');
      [*] = ;               if BoolRegister0 then
      [*] = ;               begin
      [*] = ;                  ExecuteState('HireUnits');
      [*] = ;                  bChange := true;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if trgUID <> curUID then
      [*] = ;                  begin
      [*] = ;                     SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iTask, gc_UnitTaskMove);
      [*] = ;                     SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iTargetUID, trgUID);
      [*] = ;                     SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iAITask, 1);
      [*] = ;
      [*] = ;                     _gv_traceState(_log_name+'[moving to garrison in '+IntToStr(trgUID)+']',$1000000 or _log_trace);
      [*] = ;                     BoolRegister0 := bChange;
      [*] = ;                     exit;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if trgUID <> curUID then
      [*] = ;               begin
      [*] = ;                  SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iTask, gc_UnitTaskMove);
      [*] = ;                  SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iTargetUID, trgUID);
      [*] = ;                  SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iAITask, 1);
      [*] = ;
      [*] = ;                  _gv_traceState(_log_name+'[moving to garrison in '+IntToStr(trgUID)+']',$1000000 or _log_trace);
      [*] = ;                  BoolRegister0 := bChange;
      [*] = ;                  exit;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iGarrisonUID, trgUID);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      SetPlayerBoolValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_bCanSpend, false);
      [*] = ;end;
      [*] = ;
      [*] = ;_gui_ProgressCalculations(_log_name+' [Learn spells task]');
      [*] = ;// search for province to learn spells
      [*] = ;var pAvSpells : Integer = ParserSelectByHandleByKey(pCastle, 'Spells');
      [*] = ;if ParserGetCountByHandle(pAvSpells) > 0 then
      [*] = ;begin
      [*] = ;   var pMySpells : Integer = ParserSelectByHandleByKey(pMyParser, 'Spells');
      [*] = ;   var spellCount : Integer = ParserGetCountByHandle(pMySpells);
      [*] = ;
      [*] = ;   var spellSlotCount : Integer = 0;
      [*] = ;
      [*] = ;   for i := 1 to 4 do
      [*] = ;   begin
      [*] = ;      IntRegister0 := i;
      [*] = ;      ExecuteState('GetSpellSlots');
      [*] = ;      spellSlotCount := spellSlotCount + IntRegister1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if spellCount < spellSlotCount * 0.7 then
      [*] = ;   begin
      [*] = ;      var pTrgProvince : Integer = 0;
      [*] = ;
      [*] = ;      for i := ParserGetCountByHandle(pStratHexCells)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pProvince : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;         var dist : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'MoveMap');
      [*] = ;         if dist >= 0 then
      [*] = ;         begin
      [*] = ;            var isCastle1 : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;            var dummyUID1 : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;            var dummyHandle1 : Integer = GetGameObjectHandleByUniqueId(dummyUID1);
      [*] = ;            var plName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;            var plHandle : Integer = GetPlayerHandleByName(plName);
      [*] = ;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle1, 'IsUnderSiege');
      [*] = ;            var isSiege1 : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;            if (plHandle = myPlHandle) and (not isSiege1) then
      [*] = ;            begin
      [*] = ;               var lib : Boolean = false;
      [*] = ;
      [*] = ;               if isCastle1 then
      [*] = ;               lib := true
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  var pProvOuterBuildings : Integer = ParserSelectByHandleByKey(pProvince, 'OuterBuildings');
      [*] = ;                  for j := ParserGetCountByHandle(pProvOuterBuildings)-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     var pProvOuterBuilding : Integer = ParserSelectByHandleByIndex(pProvOuterBuildings, j);
      [*] = ;                     var buildID : Integer = ParserGetIntValueByKeyByHandle(pProvOuterBuilding, 'OuterBuildID');
      [*] = ;
      [*] = ;                     if buildID > 0 then
      [*] = ;                     begin
      [*] = ;                        IntRegister0 := buildID;
      [*] = ;                        MapExecuteState('GetOuterBuildParserByID');
      [*] = ;                        var pOuterBuild : Integer = IntRegister1;
      [*] = ;
      [*] = ;                        if ParserGetBoolValueByKeyByHandle(pOuterBuild, 'Library') then
      [*] = ;                        begin
      [*] = ;                           lib := true;
      [*] = ;                           break;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               var trgDist : Integer = ParserGetIntValueByKeyByHandle(pTrgProvince, 'MoveMap');
      [*] = ;               if lib and ((pTrgProvince = 0) or (dist < trgDist)) then
      [*] = ;                  pTrgProvince := pProvince;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if pTrgProvince <> 0 then
      [*] = ;      begin
      [*] = ;         var trgUID : Integer = ParserGetIntValueByKeyByHandle(pTrgProvince, 'DummyUID');
      [*] = ;
      [*] = ;         var dist : Integer = ParserGetIntValueByKeyByHandle(pTrgProvince, 'MoveMap');
      [*] = ;         if dist > 3 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := pCurProvince;
      [*] = ;            PlayerExecuteStateByHandle(myPlHandle, 'TryBuildLibrary');
      [*] = ;            if BoolRegister0 then
      [*] = ;            begin
      [*] = ;               ExecuteState('LearnSpells');
      [*] = ;               bChange := true;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if trgUID <> curUID then
      [*] = ;               begin
      [*] = ;                  SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iTask, gc_UnitTaskMove);
      [*] = ;                  SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iTargetUID, trgUID);
      [*] = ;                  SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iAITask, 2);
      [*] = ;
      [*] = ;                  _gv_traceState(_log_name+'[moving to library in '+IntToStr(trgUID)+']',$1000000 or _log_trace);
      [*] = ;                  BoolRegister0 := bChange;
      [*] = ;                  exit;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if trgUID <> curUID then
      [*] = ;            begin
      [*] = ;               SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iTask, gc_UnitTaskMove);
      [*] = ;               SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iTargetUID, trgUID);
      [*] = ;               SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iAITask, 2);
      [*] = ;
      [*] = ;               _gv_traceState(_log_name+'[moving to library in '+IntToStr(trgUID)+']',$1000000 or _log_trace);
      [*] = ;               BoolRegister0 := bChange;
      [*] = ;               exit;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gui_ProgressCalculations(_log_name+' [Shop items task]');
      [*] = ;// search for province to exchange items
      [*] = ;var pCastleShop : Integer = ParserSelectByHandleByKey(pCastle, 'Shop');
      [*] = ;var pCastleShopItems : Integer = ParserSelectByHandleByKey(pCastleShop, 'Items');
      [*] = ;
      [*] = ;if ParserGetCountByHandle(pCastleShopItems) > 0 then
      [*] = ;begin
      [*] = ;   var pMyDollSlots : Integer = ParserSelectByHandleByKey(pMyParser, 'Doll');
      [*] = ;   var itemCount : Integer = 0;
      [*] = ;
      [*] = ;   for i := gc_HeroDollSlotsCount to gc_HeroInventoryCount-1 do
      [*] = ;   begin
      [*] = ;      var pMyDollSlot : Integer = ParserSelectByHandleByIndex(pMyDollSlots, i);
      [*] = ;      var itemID : Integer = ParserGetIntValueByKeyByHandle(pMyDollSlot, 'ItemID');
      [*] = ;
      [*] = ;      if itemID > 0 then
      [*] = ;      itemCount := itemCount + 1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   IntRegister0 := 1;
      [*] = ;   ExecuteState('GetSlotIndexByItemSlot');
      [*] = ;   var slotInd1 : Integer = IntRegister1;
      [*] = ;   var pMyDollSlot1 : Integer = ParserSelectByHandleByIndex(pMyDollSlots, slotInd1);
      [*] = ;   var itemID1 : Integer = ParserGetIntValueByKeyByHandle(pMyDollSlot1, 'ItemID');
      [*] = ;   var itemDur1 : Integer = ParserGetIntValueByKeyByHandle(pMyDollSlot1, 'Durability');
      [*] = ;
      [*] = ;   IntRegister0 := itemID1;
      [*] = ;   MapExecuteState('GetItemParserByID');
      [*] = ;   var pItem1 : Integer = IntRegister1;
      [*] = ;   var maxDur1 : Integer = ParserGetIntValueByKeyByHandle(pItem1, 'Durability');
      [*] = ;
      [*] = ;   IntRegister0 := 12;
      [*] = ;   ExecuteState('GetSlotIndexByItemSlot');
      [*] = ;   var slotInd12 : Integer = IntRegister1;
      [*] = ;   var pMyDollSlot12 : Integer = ParserSelectByHandleByIndex(pMyDollSlots, slotInd12);
      [*] = ;   var itemID12 : Integer = ParserGetIntValueByKeyByHandle(pMyDollSlot12, 'ItemID');
      [*] = ;   var itemDur12 : Integer = ParserGetIntValueByKeyByHandle(pMyDollSlot12, 'Durability');
      [*] = ;
      [*] = ;   IntRegister0 := itemID12;
      [*] = ;   MapExecuteState('GetItemParserByID');
      [*] = ;   var pItem12 : Integer = IntRegister1;
      [*] = ;   var maxDur12 : Integer = ParserGetIntValueByKeyByHandle(pItem12, 'Durability');
      [*] = ;
      [*] = ;   if (itemCount > 7) or ((itemID1 > 0) and (itemDur1 < maxDur1 / 5)) or ((itemID12 > 0) and (itemDur12 < maxDur12 / 5)) then
      [*] = ;   begin
      [*] = ;      var pTrgProvince : Integer = 0;
      [*] = ;
      [*] = ;      for i := ParserGetCountByHandle(pStratHexCells)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pProvince : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;         var dist : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'MoveMap');
      [*] = ;         if dist >= 0 then
      [*] = ;         begin
      [*] = ;            var isCastle1 : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;            var dummyUID1 : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;            var dummyHandle1 : Integer = GetGameObjectHandleByUniqueId(dummyUID1);
      [*] = ;            var plName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;            var plHandle : Integer = GetPlayerHandleByName(plName);
      [*] = ;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle1, 'IsUnderSiege');
      [*] = ;            var isSiege1 : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;            if (plHandle = myPlHandle) and (not isSiege1) then
      [*] = ;            begin
      [*] = ;               var shop : Boolean = false;
      [*] = ;
      [*] = ;               if isCastle1 then
      [*] = ;               shop := true
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  var pProvOuterBuildings : Integer = ParserSelectByHandleByKey(pProvince, 'OuterBuildings');
      [*] = ;                  for j := ParserGetCountByHandle(pProvOuterBuildings)-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     var pProvOuterBuilding : Integer = ParserSelectByHandleByIndex(pProvOuterBuildings, j);
      [*] = ;                     var buildID : Integer = ParserGetIntValueByKeyByHandle(pProvOuterBuilding, 'OuterBuildID');
      [*] = ;
      [*] = ;                     if buildID > 0 then
      [*] = ;                     begin
      [*] = ;                        IntRegister0 := buildID;
      [*] = ;                        MapExecuteState('GetOuterBuildParserByID');
      [*] = ;                        var pOuterBuild : Integer = IntRegister1;
      [*] = ;
      [*] = ;                        if ParserGetBoolValueByKeyByHandle(pOuterBuild, 'Shop') then
      [*] = ;                        begin
      [*] = ;                           shop := true;
      [*] = ;                           break;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               var trgDist : Integer = ParserGetIntValueByKeyByHandle(pTrgProvince, 'MoveMap');
      [*] = ;               if shop and ((pTrgProvince = 0) or (dist < trgDist)) then
      [*] = ;                  pTrgProvince := pProvince;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if pTrgProvince <> 0 then
      [*] = ;      begin
      [*] = ;         var trgUID : Integer = ParserGetIntValueByKeyByHandle(pTrgProvince, 'DummyUID');
      [*] = ;
      [*] = ;         var dist : Integer = ParserGetIntValueByKeyByHandle(pTrgProvince, 'MoveMap');
      [*] = ;         if dist > 3 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := pCurProvince;
      [*] = ;            PlayerExecuteStateByHandle(myPlHandle, 'TryBuildShop');
      [*] = ;            if BoolRegister0 then
      [*] = ;            begin
      [*] = ;               ExecuteState('EquipItems');
      [*] = ;               bChange := true;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if trgUID <> curUID then
      [*] = ;               begin
      [*] = ;                  SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iTask, gc_UnitTaskMove);
      [*] = ;                  SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iTargetUID, trgUID);
      [*] = ;                  SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iAITask, 3);
      [*] = ;
      [*] = ;                  _gv_traceState(_log_name+'[moving to shop in '+IntToStr(trgUID)+']',$1000000 or _log_trace);
      [*] = ;                  BoolRegister0 := bChange;
      [*] = ;                  exit;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if trgUID <> curUID then
      [*] = ;            begin
      [*] = ;               SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iTask, gc_UnitTaskMove);
      [*] = ;               SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iTargetUID, trgUID);
      [*] = ;               SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iAITask, 3);
      [*] = ;
      [*] = ;               _gv_traceState(_log_name+'[moving to shop in '+IntToStr(trgUID)+']',$1000000 or _log_trace);
      [*] = ;               BoolRegister0 := bChange;
      [*] = ;               exit;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// search for sites
      [*] = ;_gui_ProgressCalculations(_log_name+' [Sites exploration task]');
      [*] = ;var dummyUID1 : Integer;
      [*] = ;var dummyHandle1 : Integer;
      [*] = ;var provExplored : Integer;
      [*] = ;var plName : String;
      [*] = ;var isCastle1 : Boolean;
      [*] = ;var dist,mid,mpower : Integer;
      [*] = ;var siteInfo : array [0..100] of array [0..3] of Integer;
      [*] = ;powers_num:=0;
      [*] = ;ring := 0;
      [*] = ;sector := 0;
      [*] = ;rowIndex := 0;
      [*] = ;latestPassableRing := 0;
      [*] = ;if not improvedAI then
      [*] = ;for i := ParserGetCountByHandle(pStratHexCells)-1 downto 0 do
      [*] = ;begin
      [*] = ;   pProvince := ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   dist := ParserGetIntValueByKeyByHandle(pProvince, 'MoveMap');
      [*] = ;   newDist := dist;
      [*] = ;   if dist >= 0 then
      [*] = ;   begin
      [*] = ;      dummyUID1 := ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;      newProv:=dummyUID1;
      [*] = ;      dummyHandle1 := GetGameObjectHandleByUniqueId(dummyUID1);
      [*] = ;      provExplored := ParserGetIntValueByKeyByHandle(pProvince, 'Explored');
      [*] = ;      plName := ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;      plHandle := GetPlayerHandleByName(plName);
      [*] = ;      isCastle1 := ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle1, 'IsUnderSiege');
      [*] = ;      var isSiege1 : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;      if (plHandle = myPlHandle) and (not isSiege1) then
      [*] = ;      begin
      [*] = ;         var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;         for j := ParserGetCountByHandle(pProvSites)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, j);
      [*] = ;            var siteID : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'SiteID');
      [*] = ;            var siteExplore : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'Explore');
      [*] = ;            var pSiteGuard : Integer = ParserSelectByHandleByKey(pProvSite, 'Guard');
      [*] = ;            var pGuardUnits : Integer = ParserSelectByHandleByKey(pSiteGuard, 'Units');
      [*] = ;            var isGuarded : Boolean = (ParserGetCountByHandle(pGuardUnits) > 0);
      [*] = ;            if (siteID > 0) and (siteID <> 41) and (siteExplore <= provExplored) and isGuarded and
      [*] = ;            ((not isCastle1) or (j > 0) or (plProfile = 0)) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := pMyUnits;
      [*] = ;               IntRegister1 := myGOHandle;
      [*] = ;               IntRegister2 := myPlHandle;
      [*] = ;               IntRegister3 := pGuardUnits;
      [*] = ;               IntRegister4 := 0;
      [*] = ;               IntRegister5 := 0;
      [*] = ;               MapExecuteState('map.CompareArmiesStrength');
      [*] = ;               power := IntRegister6;
      [*] = ;               newUnion:=j;
      [*] = ;               if powers_num < 100 then
      [*] = ;               begin
      [*] = ;                  for nc := 0 to powers_num-1 do
      [*] = ;                  begin
      [*] = ;                     if siteInfo[nc,1] < power then
      [*] = ;                     begin
      [*] = ;                           nTmpProv := siteInfo[nc,0];
      [*] = ;                           nTmpPower := siteInfo[nc,1];
      [*] = ;                           nTmpUnion := siteInfo[nc,2];
      [*] = ;                           nTmpDist := siteInfo[nc,3];
      [*] = ;                           siteInfo[nc,0] := newProv;
      [*] = ;                           siteInfo[nc,1] := power;
      [*] = ;                           siteInfo[nc,2] := newUnion;
      [*] = ;                           siteInfo[nc,3] := newDist;
      [*] = ;                           newProv := nTmpProv;
      [*] = ;                           power := nTmpPower;
      [*] = ;                           newUnion := nTmpUnion;
      [*] = ;                           newDist := nTmpDist;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  siteInfo[powers_num,0] := newProv;
      [*] = ;                  siteInfo[powers_num,1] := power;
      [*] = ;                  siteInfo[powers_num,2] := newUnion;
      [*] = ;                  siteInfo[powers_num,3] := newDist;
      [*] = ;                  powers_num := powers_num+1;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  ErrorLogI('Too many battles with sites (100)');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            // add site target
      [*] = ;            var pNewTarget : Integer = 0;
      [*] = ;            // check for arena
      [*] = ;            var trgCount : Integer = ParserGetCountByHandle(pMySiteTargets);
      [*] = ;
      [*] = ;            if (siteID = 41) and (siteExplore <= provExplored) and (heroLevel < 10) and (plDiff > 1) and (trgCount = 0) then
      [*] = ;            begin
      [*] = ;               var pNewTarget : Integer = ParserAddChildByIndex(pMySiteTargets, '*');
      [*] = ;
      [*] = ;               ParserSetIntValueByKeyByHandle(pNewTarget, 'DummyUID', dummyUID1);
      [*] = ;               ParserSetIntValueByKeyByHandle(pNewTarget, 'Distance', dist);
      [*] = ;               ParserSetIntValueByKeyByHandle(pNewTarget, 'Power', 110 - notInBattle);
      [*] = ;               ParserSetIntValueByKeyByHandle(pNewTarget, 'SiteIndex', j);
      [*] = ;               ParserSetBoolValueByKeyByHandle(pNewTarget, 'HeroDeath', false);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;repeat
      [*] = ;   pProvince := 0;
      [*] = ;   if ring = 0 then
      [*] = ;   begin
      [*] = ;      pProvince := pCurProvince;
      [*] = ;      ring := 1;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      _map_GetHexOutward(myX, myY, sector, ring, rowIndex, x, y);
      [*] = ;      if (x >= 0) and (x < mapSizeX) and (y >= 0) and (y < mapSizeY) then
      [*] = ;         pProvince := _map_GetStratHex(x, y);
      [*] = ;      
      [*] = ;      if rowIndex = ring-1 then
      [*] = ;      begin
      [*] = ;         rowIndex := 0;
      [*] = ;         if sector = 5 then
      [*] = ;         begin
      [*] = ;            sector := 0;
      [*] = ;            ring := ring + 1;
      [*] = ;         end
      [*] = ;         else
      [*] = ;            sector := sector + 1;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         rowIndex := rowIndex + 1;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   dist := ParserGetIntValueByKeyByHandle(pProvince, 'MoveMap');
      [*] = ;   newDist := dist;
      [*] = ;   if (pProvince <> 0) and (dist >= 0) then
      [*] = ;   begin
      [*] = ;      latestPassableRing := ring;
      [*] = ;      plName := ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;      plHandle := GetPlayerHandleByName(plName);
      [*] = ;
      [*] = ;      if (plHandle = myPlHandle)  then
      [*] = ;      begin
      [*] = ;         dummyUID1 := ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;         dummyHandle1 := GetGameObjectHandleByUniqueId(dummyUID1);
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle1, 'IsUnderSiege');
      [*] = ;         if (not BoolRegister0) then
      [*] = ;         begin
      [*] = ;            newProv:=dummyUID1;
      [*] = ;            isCastle1 := ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;            provExplored := ParserGetIntValueByKeyByHandle(pProvince, 'Explored');
      [*] = ;            var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;            for j := ParserGetCountByHandle(pProvSites)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, j);
      [*] = ;               var siteID : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'SiteID');
      [*] = ;               var siteExplore : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'Explore');
      [*] = ;               var pSiteGuard : Integer = ParserSelectByHandleByKey(pProvSite, 'Guard');
      [*] = ;               var pGuard : Integer = ParserSelectByHandleByIndex(gPrototypeData.guards.handle, ParserGetIntValueByKeyByHandle(pSiteGuard, 'GuardID'));
      [*] = ;               var guardPower : Integer = ParserGetIntValueByKeyByHandle(pGuard, 'Power');
      [*] = ;               var pGuardUnits : Integer = ParserSelectByHandleByKey(pSiteGuard, 'Units');
      [*] = ;               var isGuarded : Boolean = (ParserGetCountByHandle(pGuardUnits) > 0);
      [*] = ;               if (siteID > 0) and (siteID <> 41) and (siteExplore <= provExplored) and isGuarded and
      [*] = ;               ((not isCastle1) or (j > 0) or (plProfile = 0)) and (Round(Abs(myHeroPower - guardPower)) <= maxSitePowerDiff) then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := pMyUnits;
      [*] = ;                  IntRegister1 := myGOHandle;
      [*] = ;                  IntRegister2 := myPlHandle;
      [*] = ;                  IntRegister3 := pGuardUnits;
      [*] = ;                  IntRegister4 := 0;
      [*] = ;                  IntRegister5 := 0;
      [*] = ;                  MapExecuteState('map.CompareArmiesStrength');
      [*] = ;                  power := IntRegister6;
      [*] = ;                  newUnion:=j;
      [*] = ;                  if powers_num < maxSitesConsider then
      [*] = ;                  begin
      [*] = ;                     for nc := 0 to powers_num-1 do
      [*] = ;                     begin
      [*] = ;                        if siteInfo[nc,1] < power then
      [*] = ;                        begin
      [*] = ;                           nTmpProv := siteInfo[nc,0];
      [*] = ;                           nTmpPower := siteInfo[nc,1];
      [*] = ;                           nTmpUnion := siteInfo[nc,2];
      [*] = ;                           nTmpDist := siteInfo[nc,3];
      [*] = ;                           siteInfo[nc,0] := newProv;
      [*] = ;                           siteInfo[nc,1] := power;
      [*] = ;                           siteInfo[nc,2] := newUnion;
      [*] = ;                           siteInfo[nc,3] := newDist;
      [*] = ;                           newProv := nTmpProv;
      [*] = ;                           power := nTmpPower;
      [*] = ;                           newUnion := nTmpUnion;
      [*] = ;                           newDist := nTmpDist;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                     siteInfo[powers_num,0] := newProv;
      [*] = ;                     siteInfo[powers_num,1] := power;
      [*] = ;                     siteInfo[powers_num,2] := newUnion;
      [*] = ;                     siteInfo[powers_num,3] := newDist;
      [*] = ;                     powers_num := powers_num+1;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     ErrorLogI('Too many battles with sites');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               // add site target
      [*] = ;               var pNewTarget : Integer = 0;
      [*] = ;               // check for arena
      [*] = ;               var trgCount : Integer = ParserGetCountByHandle(pMySiteTargets);
      [*] = ;
      [*] = ;               if (siteID = 41) and (siteExplore <= provExplored) and (heroLevel < 10) and (plDiff > 1) and (trgCount = 0) then
      [*] = ;               begin
      [*] = ;                  var pNewTarget : Integer = ParserAddChildByIndex(pMySiteTargets, '*');
      [*] = ;
      [*] = ;                  ParserSetIntValueByKeyByHandle(pNewTarget, 'DummyUID', dummyUID1);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pNewTarget, 'Distance', dist);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pNewTarget, 'Power', 110 - notInBattle);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pNewTarget, 'SiteIndex', j);
      [*] = ;                  ParserSetBoolValueByKeyByHandle(pNewTarget, 'HeroDeath', false);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;until (powers_num = maxSitesConsider) or (ring > latestPassableRing + 3);
      [*] = ;   _log_Map('site powers_num '+IntToStr(powers_num));
      [*] = ;
      [*] = ;res_batl := plDiff;
      [*] = ;_gui_ProgressCalculations(_log_name+'[2] Diff:' + IntToStr(res_batl));
      [*] = ;if res_batl < 0 then
      [*] = ;begin
      [*] = ;   ErrorLogI(_log_name+' Player difficulty is < 0 ('+IntToStr(res_batl)+')');
      [*] = ;   res_batl := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;if (not improvedAI) and (RandomExt<0.8) then
      [*] = ;   res_batl := -1; // hot optimization -1 means 1 battles
      [*] = ;
      [*] = ;simulations_count := Min(powers_num-1, res_batl+1);
      [*] = ;for i := 0 to simulations_count do
      [*] = ;begin
      [*] = ;   var pNewTarget : Integer = 0;
      [*] = ;
      [*] = ;   if ParserGetCountByHandle(pMySiteTargets) < maxTargets then
      [*] = ;      pNewTarget := ParserAddChildByIndex(pMySiteTargets, '*')
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      for k := 0 to maxTargets-1 do
      [*] = ;      begin
      [*] = ;         var pMySiteTarget : Integer = ParserSelectByHandleByIndex(pMySiteTargets, k);
      [*] = ;
      [*] = ;         var trgDist : Integer = ParserGetIntValueByKeyByHandle(pMySiteTarget, 'Distance');
      [*] = ;         var trgPower : Integer = ParserGetIntValueByKeyByHandle(pMySiteTarget, 'Power');
      [*] = ;
      [*] = ;         if pNewTarget = 0 then
      [*] = ;         begin
      [*] = ;            if (trgPower < siteInfo[i,1]) or ((trgPower = siteInfo[i,1]) and (trgDist > siteInfo[i,3])) then
      [*] = ;               pNewTarget := pMySiteTarget;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var selDist : Integer = ParserGetIntValueByKeyByHandle(pNewTarget, 'Distance');
      [*] = ;            var selPower : Integer = ParserGetIntValueByKeyByHandle(pNewTarget, 'Power');
      [*] = ;
      [*] = ;            if (trgPower < selPower) or ((trgPower = selPower) and (trgDist > selDist)) then
      [*] = ;               pNewTarget := pMySiteTarget;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if pNewTarget <> 0 then
      [*] = ;   begin
      [*] = ;      _gui_ProgressCalculations(_log_name+'[3] site target for ' + myCustomName + ' (DummyUID = ' + IntToStr(siteInfo[i,0]) + ', power = ' + IntToStr(siteInfo[i,1]) + ', ind = ' + IntToStr(siteInfo[i,2]) + ')');
      [*] = ;
      [*] = ;      ParserSetIntValueByKeyByHandle(pNewTarget, 'DummyUID', siteInfo[i,0]);
      [*] = ;      ParserSetIntValueByKeyByHandle(pNewTarget, 'Distance', siteInfo[i,3]);
      [*] = ;      ParserSetIntValueByKeyByHandle(pNewTarget, 'Power', siteInfo[i,1]);
      [*] = ;      ParserSetIntValueByKeyByHandle(pNewTarget, 'SiteIndex', siteInfo[i,2]);
      [*] = ;      ParserSetBoolValueByKeyByHandle(pNewTarget, 'HeroDeath', false);
      [*] = ;    end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gui_ProgressCalculations(_log_name+' [Explore provinces task]');
      [*] = ;// search for province to explore
      [*] = ;if curProvExplored < 100 then
      [*] = ;   SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iExploreTarget, curUID)
      [*] = ;else
      [*] = ;begin
      [*] = ;   var expUID : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iExploreTarget);
      [*] = ;   MapExecuteState('GetProvinceParserByUID');
      [*] = ;   var pExpProvince : Integer = IntRegister1;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pStratHexCells)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pProvince : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      var dist : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'MoveMap');
      [*] = ;      if dist >= 0 then
      [*] = ;      begin
      [*] = ;         var dummyUID1 : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;         var dummyHandle1 : Integer = GetGameObjectHandleByUniqueId(dummyUID1);
      [*] = ;         var plName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;         var plHandle : Integer = GetPlayerHandleByName(plName);
      [*] = ;         var explored : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Explored');
      [*] = ;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle1, 'IsUnderSiege');
      [*] = ;         var isSiege1 : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;         if (plHandle = myPlHandle) and (not isSiege1) and (explored < 100) then
      [*] = ;         begin
      [*] = ;            var expDist : Integer = ParserGetIntValueByKeyByHandle(pExpProvince, 'MoveMap');
      [*] = ;            if (expUID = 0) or (dist < expDist) then
      [*] = ;            begin
      [*] = ;               pExpProvince := pProvince;
      [*] = ;               expUID := dummyUID1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   SetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iExploreTarget, expUID);
      [*] = ;end;
      [*] = ;_log_map('AIHeroName: '+myCustomName);
      [*] = ;_log_map('AIHeroPower: '+IntToStr(myHeroPower));
      [*] = ;_log_map('AIHeroUID: '+IntToStr(GetGameObjectUniqueIdByHandle(myGOHandle)));
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+BoolToStr(bChange)+']',$1000000 or _log_trace);
      [*] = ;
      [*] = ;BoolRegister0 := bChange;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

