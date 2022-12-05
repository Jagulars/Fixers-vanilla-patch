section.begin
   Name = map.EventQueryWindow
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\MAP\MAP.EVENTQUERYWINDOW';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;procedure CloseQueryWindow();
      [*] = ;begin
      [*] = ;   SetValueByName('queryID', '');
      [*] = ;   QueryMachineCustomQueriesClear();
      [*] = ;   GUIExecuteState('ToolQueryWindow');
      [*] = ;end;
      [*] = ;
      [*] = ;function IsNetworkQuery(query_id : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var myPlHandle : Integer = GetPlayerHandleByIndex(gIntRegister_MapMyPlayerIndex);
      [*] = ;
      [*] = ;   if (gGame.gameType = gc_GameTypeLanShard) and gBoolRegister_MapResolveConflicts and (GetLanMode() = 1) and
      [*] = ;      ((not gBoolRegister_MapProceedBattle) or (gIntRegister_NewBattle >= 0)) and _plr_IsInGame(myPlHandle) and
      [*] = ;      (query_id <> gc_gui_query_lan_playerWin) then
      [*] = ;      Result := true
      [*] = ;   else
      [*] = ;      Result := false;
      [*] = ;end;
      [*] = ;
      [*] = ;var sPress  : String  = GetValueByName('Press');
      [*] = ;var sKey : String  = GetValueByName('Key');
      [*] = ;var elmName : String = GetGUIElementNameByIndex(GetIntValueByName('ElementHandle'));
      [*] = ;
      [*] = ;if (sKey='LButton') and (sPress='c') and (elmName <> 'innerbuild_reward_icon') then
      [*] = ;begin
      [*] = ;   var iTag,curUID,dummyHandle,pProvince : Integer;
      [*] = ;   var curQueryID : String = GetValueByName('queryID');
      [*] = ;   var plHandle : Integer = _gv_GetCurrentPlayerHandle();
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(gIntRegister_MapCurHeroIndex, plHandle);
      [*] = ;
      [*] = ;   if goHandle = 0 then
      [*] = ;   begin
      [*] = ;      goHandle := gIntRegister_MapActiveHeroHandle;
      [*] = ;      plHandle := GetGameObjectPlayerHandleByHandle(goHandle);
      [*] = ;   end;
      [*] = ;
      [*] = ;   curUID := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;   dummyHandle := GetGameObjectHandleByUniqueId(curUID);
      [*] = ;   pProvince := _misc_GetProvinceParserByUID(curUID);
      [*] = ;
      [*] = ;   if (GetValueByName('Status')='button') and (sPress='c') then
      [*] = ;      iTag := GetIntValueByName('Tag')
      [*] = ;   else
      [*] = ;      iTag := 0;
      [*] = ;
      [*] = ;   _gv_traceState(_log_name+'[Q:'+curQueryID+',PROV:'+IntToStr(curUID)+',PL:'+GetPlayerNameByHandle(plHandle)+',TAG:'+IntToStr(iTag)+']',_log_trace);
      [*] = ;
      [*] = ;   if elmName = 'btn_hero_window' then
      [*] = ;   begin
      [*] = ;      gIntRegister_GUICurHeroMode := gc_HeroPanelBothPanels;
      [*] = ;      gIntRegister_GUIActiveHeroUID1 := GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;      GUIExecuteState('map.CreateHeroWindow');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   case iTag of
      [*] = ;      0 : iTag := 0;
      [*] = ;      1 :  CloseQueryWindow();
      [*] = ;      else begin
      [*] = ;         if IsNetworkQuery(StrToInt(curQueryID)) then
      [*] = ;         begin
      [*] = ;            var pQuery : Integer = _misc_ParserGetOrCreateByKey('meqw_Query',true);
      [*] = ;
      [*] = ;            ParserSetValueByKeyByHandle(pQuery, 'QueryID', curQueryID);
      [*] = ;            ParserSetValueByKeyByHandle(pQuery, 'Result', QueryMachineResultGetID(iTag));
      [*] = ;            ParserSetIntValueByKeyByHandle(pQuery, 'LanID', LanMyInfoID());
      [*] = ;
      [*] = ;            _gv_SetMapTurnFinished(false,_log_name);
      [*] = ;            _lan_LanSendParserToServer(gc_LAN_SHARD_CHOOSERESULT, pQuery);
      [*] = ;            CloseQueryWindow();
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var resultHandle : Integer = iTag;
      [*] = ;            var queryHandle : Integer = QueryMachineResultGetQuery(resultHandle);
      [*] = ;
      [*] = ;            var oldQueryHandle : Integer = gIntRegister_CurQueryHandle;
      [*] = ;            var oldQueryID : String = curQueryID;
      [*] = ;            QueryMachineResultDoSelectExecute(resultHandle);
      [*] = ;            var newQueryHandle : Integer = gIntRegister_CurQueryHandle;
      [*] = ;            var newQueryID : String = GetValueByName('queryID');
      [*] = ;
      [*] = ;            var resultNextQuery : String = QueryMachineResultGetNextQuery(resultHandle);
      [*] = ;            var nextQuery : Integer = StrToInt(resultNextQuery);
      [*] = ;            if (resultNextQuery<>'') then
      [*] = ;            begin
      [*] = ;               // proceed province events if needed
      [*] = ;               if ((nextQuery > gc_query_EventMinIndex) and (nextQuery <= gc_query_EventMaxIndex)) or ((nextQuery > gc_query_ScenarioEventMinIndex) and (nextQuery <= gc_query_ScenarioCampEventMaxIndex)) then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := nextQuery;
      [*] = ;                  GameObjectExecuteStateByHandle(_map_GetCurrentProvinceHandle(), 'ProceedEvent');
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  // proceed hero events if needed
      [*] = ;                  if (nextQuery > gc_query_EncounterMinIndex) and (nextQuery <= gc_query_EncounterMaxIndex) then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := nextQuery;
      [*] = ;                     GameObjectExecuteStateByHandle(goHandle, 'ProceedEncounter');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     queryHandle := QueryMachineCustomQueryCreate(resultNextQuery);
      [*] = ;                     gIntRegister_CurQueryHandle := queryHandle;
      [*] = ;
      [*] = ;                     QueryMachineQueryDoCreateExecute(queryHandle);
      [*] = ;                     SetValueByName('queryID', resultNextQuery);
      [*] = ;                     GUIExecuteState('ToolQueryWindow');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (queryHandle<>0) and (not SameText(resultNextQuery, QueryMachineQueryGetID(queryHandle))) then
      [*] = ;               begin
      [*] = ;                  if _log then _Log_gui('QueryMachineQueriesRemove : ' + QueryMachineQueryGetID(queryHandle));
      [*] = ;                  QueryMachineQueriesRemove(QueryMachineGetCustomQueriesHandle, queryHandle);
      [*] = ;
      [*] = ;                  // check encounter result
      [*] = ;                  if gIntRegister_EncounterResult = -3 then
      [*] = ;                  begin
      [*] = ;                     if gIntRegister_CurGameMode = gc_GameModeStrategy then
      [*] = ;                        _gv_SetMapLock(-1,_log_name+'[gIntRegister_EncounterResult -3]')
      [*] = ;                     else
      [*] = ;                        _gv_SetBattleLock(-1,_log_name+'[gIntRegister_EncounterResult -3]');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (oldQueryID=newQueryID) then
      [*] = ;                  CloseQueryWindow();
      [*] = ;
      [*] = ;               var guardAttack : Boolean = false;
      [*] = ;               var curQuery : Integer = StrToInt(curQueryID);
      [*] = ;               if (curQuery > gc_query_EventMinIndex) and (curQuery <= gc_query_EventMaxIndex) then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := curQuery;
      [*] = ;                  MapExecuteState('GetEventParserByID');
      [*] = ;                  var guardType : Integer = ParserGetIntValueByKeyByHandle( IntRegister1, 'Attacker');
      [*] = ;
      [*] = ;                  if guardType > 0 then
      [*] = ;                  begin
      [*] = ;                     _gv_SetMapLock($10001,_log_name+'[Event Guard Attack]');
      [*] = ;                     guardAttack := true;
      [*] = ;
      [*] = ;                     IntRegister0 := guardType;
      [*] = ;                     GameObjectExecuteStateByHandle(_map_GetCurrentProvinceHandle(), 'GuardAttack');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if (curQuery > gc_query_EncounterMinIndex) and (curQuery <= gc_query_EncounterMaxIndex) then
      [*] = ;               begin
      [*] = ;                  var pEncounter : Integer = ParserSelectByHandleByIndex(gPrototypeData.encounters.handle, curQuery -  gc_query_EncounterMinIndex);
      [*] = ;                  var guardTypeID : Integer = ParserGetIntValueByKeyByHandle(pEncounter, 'GuardType');
      [*] = ;
      [*] = ;                  if guardTypeID > 0 then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := guardTypeID;
      [*] = ;                     GameObjectExecuteStateByHandle(goHandle, 'SetupEncGuard');
      [*] = ;
      [*] = ;                     IntRegister0 := pProvince;
      [*] = ;                     GameObjectExecuteStateByHandle(goHandle, 'CheckAttackMode');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if not guardAttack then
      [*] = ;               begin
      [*] = ;                  Assert(((newQueryHandle<>oldQueryHandle) or (oldQueryID=newQueryID)),'newQueryHandle==oldQueryHandle and oldQueryID!=newQueryID');
      [*] = ;                  if (newQueryHandle=oldQueryHandle) then
      [*] = ;                  begin
      [*] = ;                     if gIntRegister_CurGameMode = gc_GameModeStrategy then
      [*] = ;                        _gv_SetMapLock(-1,_log_name+'[newQueryHandle=oldQueryHandle]')
      [*] = ;                     else
      [*] = ;                        _gv_SetBattleLock(-1,_log_name+'[newQueryHandle=oldQueryHandle]');
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if (curQuery > gc_query_EncounterMinIndex) and (curQuery <= gc_query_EncounterMaxIndex) then
      [*] = ;                  begin
      [*] = ;                     {GameObjectExecuteStateByHandle(goHandle, 'CancelOrders');
      [*] = ;
      [*] = ;                     if plHandle = GetPlayerHandleInterfaceIO then
      [*] = ;                     begin
      [*] = ;                        IntRegister0 := goHandle;
      [*] = ;                        ExecuteState('map.GUIUpdateHeroHUD');
      [*] = ;                     end;}
      [*] = ;
      [*] = ;                     var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;                     var pGOLeftLootItems : Integer = ParserSelectByHandleByKey(pGOParser, 'LeftLootItems');
      [*] = ;                     if (ParserGetCountByHandle(pGOLeftLootItems)>0) then
      [*] = ;                     begin
      [*] = ;                        _gv_SetMapLock(1,_log_name+'[LootItems]');
      [*] = ;
      [*] = ;                        IntRegister0 := pGOLeftLootItems;
      [*] = ;                        gIntRegister_GUINoSpaceForItemHeroUID := GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;                        GUIExecuteState('map.CreateNoSpaceForItemWindow');
      [*] = ;                        ParserClearByHandle(pGOLeftLootItems);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               
      [*] = ;                  // pass commands that cannot be passed before the modal query window is removed.
      [*] = ;                  var iQueryID : Integer = StrToInt(oldQueryID);
      [*] = ;                  if iQueryID > 0 then
      [*] = ;                  case iQueryID of
      [*] = ;                     gc_gui_query_heroMakeSabotage : _cmd_Post('battlenextturn','','');
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  // levelup window if levelup happened from exploring, but a site discovery got in way
      [*] = ;                  if gBoolRegister_CheckLevelUp and (not gBoolRegister_MapProceedBattle) and (oldQueryID = newQueryID) and (not gBoolRegister_GUIBattleResultWindow) and (gIntRegister_EncounterResult <> -1) and (_gui_GetWindow('site_loot_window') = 0) then
      [*] = ;                  begin
      [*] = ;                     var isDead : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;                     if not isDead then
      [*] = ;                     begin
      [*] = ;                        GameObjectExecuteStateByHandle(goHandle, 'IsLevelUp');
      [*] = ;                        if BoolRegister0 then
      [*] = ;                        begin
      [*] = ;                           _gui_PlaySound('interface', 'level_up_heroe');
      [*] = ;                           _gv_SetMapLock(1,_log_name+'[LevelUp]');
      [*] = ;
      [*] = ;                           IntRegister0 := goHandle;
      [*] = ;                           GUIExecuteState('CheckHeroUpgrade');
      [*] = ;                        end
      [*] = ;                        else
      [*] = ;                        begin
      [*] = ;                           gIntRegister_BattleCurGOIndex := 0;
      [*] = ;                           GUIExecuteState('battle.CreateUnitUpgradeWindow');
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                     gBoolRegister_CheckLevelUp := false;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if _log then _Log_gui('Encounter result: '+ IntToStr(gIntRegister_EncounterResult)+', QueryID: '+ oldQueryID);
      [*] = ;            // check encounter result
      [*] = ;            if gIntRegister_EncounterResult > -3 then
      [*] = ;            begin
      [*] = ;               var curQueryID : String = GetValueByName('QueryID');
      [*] = ;               if curQueryID = '' then
      [*] = ;               begin
      [*] = ;                  case gIntRegister_EncounterResult of
      [*] = ;                     0 : begin // retreat guard
      [*] = ;                        BoolRegister0 := false;
      [*] = ;                        GameObjectExecuteStateByHandle(goHandle, 'RetreatGuard');
      [*] = ;                        gIntRegister_EncounterResult := -3;
      [*] = ;                     end;
      [*] = ;                     -1 : begin // attack guard
      [*] = ;                        if plHandle = GetPlayerHandleInterfaceIO() then
      [*] = ;                        begin
      [*] = ;                           GameObjectExecuteStateByHandle(goHandle, 'SetupEnemyArmy');
      [*] = ;                           IntRegister0 := pProvince;
      [*] = ;                           GameObjectExecuteStateByHandle(goHandle, 'CheckAttackMode');
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                     -2 : begin // diplomatic province capture
      [*] = ;                        IntRegister0 := plHandle;
      [*] = ;                        BoolRegister0 := true;
      [*] = ;                        GameObjectExecuteStateByHandle(dummyHandle, 'CaptureProvince');
      [*] = ;                        SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iTask, gc_UnitTaskRest);
      [*] = ;                        SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iActionType, 0);
      [*] = ;                        IntRegister0 := goHandle;
      [*] = ;                        GUIExecuteState('map.GUIUpdateHeroHUD');
      [*] = ;                     end
      [*] = ;                     else begin
      [*] = ;                        if gIntRegister_EncounterResult > 0 then
      [*] = ;                        begin
      [*] = ;                           IntRegister0 := plHandle;
      [*] = ;                           IntRegister1 := gIntRegister_EncounterResult;
      [*] = ;                           GameObjectExecuteStateByHandle(dummyHandle, 'DiplCaptureProvince');
      [*] = ;
      [*] = ;                           SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iTask, gc_UnitTaskRest);
      [*] = ;                           SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iActionType, 0);
      [*] = ;                           IntRegister0 := goHandle;
      [*] = ;                           GUIExecuteState('map.GUIUpdateHeroHUD');
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;end;
   struct.end
section.end

