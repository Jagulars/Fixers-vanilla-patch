section.begin
   Name = ExecuteHeroOrders
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\EXECUTEHEROORDERS';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;var myPlName : String = GetCurrentPlayerName();
      [*] = ;var myIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;var goCount : Integer = GetPlayerGameObjectsCountByHandle(myPlHandle);
      [*] = ;var i : Integer;
      [*] = ;var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+myPlName+']',_log_trace);
      [*] = ;
      [*] = ;if (not _misc_IsMapLocked()) and (gIntRegister_MapTurnIteration = 1) and (myIndex = _gv_GetCurrentPlayer()) then
      [*] = ;begin
      [*] = ;   if _log then _Log_map('Execute hero events for ['+ IntToStr(myIndex)+'] ' + myPlName);
      [*] = ;   if gIntRegister_MapCurHeroIndex >= 0 then
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(gIntRegister_MapCurHeroIndex, myPlHandle);
      [*] = ;      var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;      var pGOQuests : Integer = ParserSelectByHandleByKey(pGOParser, 'Quests');
      [*] = ;      var siteInd : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iSiteIndex);
      [*] = ;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'ClearSiteLoot');
      [*] = ;
      [*] = ;      if (gIntRegister_FoundSiteIndex >= 0) or (siteInd >= 0) then
      [*] = ;      begin
      [*] = ;         if gIntRegister_FoundSiteIndex >= 0 then
      [*] = ;         siteInd := gIntRegister_FoundSiteIndex;
      [*] = ;
      [*] = ;         var provUID : Integer; 
      [*] = ;         if GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead) then
      [*] = ;            provUID := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iBeforeTargetUID) // in case the hero was delivered to castle
      [*] = ;         else
      [*] = ;            provUID := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;
      [*] = ;         var dummyHandle : Integer = GetGameObjectHandleByUniqueId(provUID);
      [*] = ;
      [*] = ;         IntRegister0 := siteInd;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'CheckSiteDestroy');
      [*] = ;      end;
      [*] = ;
      [*] = ;      var task : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iActionType);
      [*] = ;      if task = 4  then
      [*] = ;      GameObjectExecuteStateByHandle(goHandle, 'CancelOrders');
      [*] = ;
      [*] = ;      MapExecuteState('map.ResetEncRegisters');
      [*] = ;   end;
      [*] = ;
      [*] = ;   gIntRegister_MapCurHeroIndex := gIntRegister_MapCurHeroIndex + 1;
      [*] = ;   gIntRegister_FoundSiteIndex := -1;
      [*] = ;
      [*] = ;   if (gIntRegister_MapCurHeroIndex < goCount) then
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(gIntRegister_MapCurHeroIndex, myPlHandle);
      [*] = ;      var isDead : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;
      [*] = ;      if not isDead then
      [*] = ;      begin
      [*] = ;         var oldHeroIndex : Integer = gIntRegister_MapCurHeroIndex;
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'CheckCancelOrders');
      [*] = ;
      [*] = ;         var task : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iTask);
      [*] = ;         //var aiTask : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iAITask);
      [*] = ;         //SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iActionType, task);
      [*] = ;
      [*] = ;         if myIndex = gIntRegister_MapMyPlayerIndex then
      [*] = ;         begin
      [*] = ;            gIntRegister_GUIDrawPathUID := GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;            gBoolRegister_GUIUpdateMapDrawPath := True;
      [*] = ;            //GUIExecuteState('DoProgressGUI');
      [*] = ;         end;
      [*] = ;
      [*] = ;         var currentUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;         var targetUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iTargetUID);
      [*] = ;         var dummyHandle : Integer = GetGameObjectHandleByUniqueId(currentUID);
      [*] = ;
      [*] = ;         // skip a turn when blizzard is casted
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'CheckFreeze');
      [*] = ;         if BoolRegister0 then
      [*] = ;         begin
      [*] = ;            if myPlHandle = GetPlayerHandleInterfaceIO() then // display message
      [*] = ;            begin
      [*] = ;               //var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;               _hero_GetName(goHandle, gStringRegister_MyHeroName);
      [*] = ;               IntRegister0 := _misc_GetProvinceParserByUID(currentUID);
      [*] = ;               MapExecuteState('map.GetProvinceName');
      [*] = ;               gStringRegister_ProvinceName := StringRegister0;
      [*] = ;
      [*] = ;               StringRegister0 := IntToStr(gc_gui_query_heroBlizzard);
      [*] = ;               GUIExecuteState('map.RequestQueryWindow');
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            MapExecuteState('map.ResetEncRegisters');
      [*] = ;
      [*] = ;            var pTargetProvince : Integer = _misc_GetProvinceParserByUID(targetUID);
      [*] = ;
      [*] = ;            case task of
      [*] = ;               gc_UnitTaskMove : begin
      [*] = ;                  if (targetUID <> 0) and (currentUID <> targetUID) then
      [*] = ;                  begin
      [*] = ;                     if myPlHandle = GetPlayerHandleInterfaceIO() then
      [*] = ;                     begin
      [*] = ;                        var pTargetProvGuard : Integer = ParserSelectByHandleByKey(pTargetProvince, 'Guard');
      [*] = ;                        gIntRegister_EncounterEnemyArmy := ParserSelectByHandleByKey(pTargetProvGuard, 'Units');
      [*] = ;
      [*] = ;                        if GetGameObjectTrackPointCountByHandle(goHandle) > 0 then
      [*] = ;                        begin
      [*] = ;                           if GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iReachPoint) > 0 then
      [*] = ;                           begin
      [*] = ;                              _gv_SetMapLock($10001,_log_name);
      [*] = ;                              CadencerProgress();
      [*] = ;                              BoolRegister0 := true;
      [*] = ;                              GameObjectExecuteStateByHandle(goHandle, 'Move');
      [*] = ;                           end;
      [*] = ;                        end
      [*] = ;                        else
      [*] = ;                           GameObjectExecuteStateByHandle(goHandle, 'CancelOrders');
      [*] = ;
      [*] = ;                        if not GetGameObjectVisibleByHandle(goHandle) then
      [*] = ;                        begin
      [*] = ;                           SetGameObjectVisibleByHandle(goHandle, True);
      [*] = ;                           SetGameObjectPositionByHandle(goHandle, GetGameObjectPositionXByHandle(goHandle), GetGameObjectPositionYByHandle(goHandle), GetGameObjectPositionZByHandle(goHandle)+0.05);
      [*] = ;                           GameObjectDoRayCastTerrainByHandle(goHandle);
      [*] = ;                        end;
      [*] = ;
      [*] = ;                        SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iUpdate, 1);
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        _gv_SetMapLock($10001,_log_name);
      [*] = ;                        GameObjectExecuteStateByHandle(goHandle, 'Select');
      [*] = ;                        BoolRegister0 := false;
      [*] = ;                        GameObjectExecuteStateByHandle(goHandle, 'Move');
      [*] = ;                     end;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                     SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iTask, gc_UnitTaskRest);
      [*] = ;               end;
      [*] = ;               gc_UnitTaskExplore : GameObjectExecuteStateByHandle(goHandle, 'ExploreProvince');
      [*] = ;               gc_UnitTaskRobber : GameObjectExecuteStateByHandle(goHandle, 'RobProvince');
      [*] = ;               gc_UnitTaskAttackSite : begin
      [*] = ;                  var site_idx : Integer = GetGameObjectIntValueIndByHandle(goHandle,gc_map_GOStack_MapUnit_iSiteIndex);
      [*] = ;                  var pSite : Integer;
      [*] = ;
      [*] = ;                  _gv_SetMapLock($10001,_log_name);
      [*] = ;                  pSite := ParserSelectByHandleByIndex(ParserSelectByHandleByKey(pTargetProvince, 'Sites'),site_idx);
      [*] = ;
      [*] = ;                  gIntRegister_EncounterEnemyArmy := ParserSelectByHandleByKey(ParserSelectByHandleByKey(pSite,'Guard'),'Units'); // !!!
      [*] = ;
      [*] = ;                  IntRegister0 := site_idx;
      [*] = ;                  GameObjectExecuteStateByHandle(goHandle,'AttackSiteByIndex');
      [*] = ;               end;
      [*] = ;               gc_UnitTaskSiege : begin
      [*] = ;                  if SameText(cMode, 'cmPlayer') then
      [*] = ;                  begin
      [*] = ;                     GameObjectExecuteStateByHandle(dummyHandle, 'GetWallPercent');
      [*] = ;                     if IntRegister0 > 50 then
      [*] = ;                        GameObjectExecuteStateByHandle(goHandle, 'ContinueSiege');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               gc_UnitTaskAttackOwnDefender : begin
      [*] = ;                  if myIndex = gIntRegister_MapMyPlayerIndex then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := _misc_GetProvinceParserByUID(GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID));
      [*] = ;                     MapExecuteState('map.GetProvinceName');
      [*] = ;                     gStringRegister_ProvinceName := StringRegister0;
      [*] = ;
      [*] = ;                     _hero_GetName(goHandle, gStringRegister_MyHeroName);
      [*] = ;
      [*] = ;                     StringRegister0 := IntToStr(gc_gui_query_heroAttackOwnDefender);
      [*] = ;                     GUIExecuteState('map.RequestQueryWindow');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     // AI doesn't attack own defenders
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if oldHeroIndex = gIntRegister_MapCurHeroIndex then
      [*] = ;            SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iMoveBonus, 0);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (gIntRegister_MapCurHeroIndex >= goCount) then
      [*] = ;   begin
      [*] = ;      var index : Integer = -1;
      [*] = ;
      [*] = ;      if (myPlHandle=GetPlayerHandleInterfaceIO()) then
      [*] = ;      begin
      [*] = ;         gIntRegister_GUIDrawPathUID := gIntRegister_MapSelectedUID;
      [*] = ;         gBoolRegister_GUIUpdateMapDrawPath := True;
      [*] = ;         _map_RefreshProvincesHUDs();
      [*] = ;      end;
      [*] = ;
      [*] = ;      // switch to next iteration state
      [*] = ;      gIntRegister_MapTurnIteration := gIntRegister_MapTurnIteration + 1;
      [*] = ;      gIntRegister_MapCurHeroIndex := -1;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

