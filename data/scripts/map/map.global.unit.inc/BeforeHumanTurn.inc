section.begin
   Name = BeforeHumanTurn
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\BEFOREHUMANTURN';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;const cPressState = 'map.StartHumanTurn';
      [*] = ;
      [*] = ;var i, j, plHnd, goHandle : Integer;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;gIntRegister_MapMyPlayerIndex := myPlIndex;
      [*] = ;
      [*] = ;// delete buried heroes
      [*] = ;for i := 0 to gGame.map.players-1 do
      [*] = ;begin
      [*] = ;   plHnd := GetPlayerHandleByIndex(i);
      [*] = ;   for j := 0 to GetPlayerGameObjectsCountByHandle(plHnd)-1 do
      [*] = ;   begin
      [*] = ;      goHandle := GetGameObjectHandleByIndex(j, plHnd);
      [*] = ;      if GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bBuried) then
      [*] = ;      begin
      [*] = ;         if gc_RecycleHeroes then
      [*] = ;            _obj_Recycle(goHandle)
      [*] = ;         else
      [*] = ;            GameObjectDestroyByHandle(goHandle);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+ IntToStr(myPlIndex)+']',_log_trace);
      [*] = ;_misc_AntiFreezeFinish();
      [*] = ;TimeLog('_misc_AntiFreezeFinish');
      [*] = ;
      [*] = ;if (gIntRegister_PlayBell > 0) then 
      [*] = ;   _gui_PlaySound('interface','end_turn');
      [*] = ;gIntRegister_PlayBell := 0;
      [*] = ;
      [*] = ;_gv_SetCurrentPlayer(myPlIndex,_log_name);
      [*] = ;_gv_SetIOHandle(myPlHandle,_log_name);
      [*] = ;SetBoolValueByIndex(gc_map_PLStack_MapUnit_bTurnFinished, false);
      [*] = ;
      [*] = ;IntRegister0 := myPlHandle;
      [*] = ;GUIExecuteState('map.SetPlayerCamera');
      [*] = ;
      [*] = ;if gGame.fog then
      [*] = ;   MapExecuteState('map.DoFogOfWar')
      [*] = ;else
      [*] = ;   MapExecuteState('map.CalcFogMap');
      [*] = ;
      [*] = ;if gGame.gameType = gc_GameTypeHotseat then // switch visuals in Stronghold
      [*] = ;begin
      [*] = ;   IntRegister0 := _obj_GetCheckSceneryFlags(gProfile.objectflags, gProfile.shardscenery, $ff, gProfile.provincescenery, gProfile.battlescenery);
      [*] = ;   GUIExecuteState('CheckScenery');
      [*] = ;end;
      [*] = ;
      [*] = ;gBoolRegister_GUIUpdateMapHexGrid := True;
      [*] = ;
      [*] = ;_map_RefreshProvincesHUDs();
      [*] = ;
      [*] = ;gIntRegister_MapSelectedUID := GetIntValueByIndex(gc_map_PLStack_MapUnit_iSelectedUID);
      [*] = ;goHandle := GetGameObjectHandleByUniqueId(gIntRegister_MapSelectedUID);
      [*] = ;var tmpPlHandle : Integer = GetGameObjectPlayerHandleByHandle(goHandle);
      [*] = ;if tmpPlHandle <> myPlHandle then
      [*] = ;begin
      [*] = ;   // checking needed for switch player cheat
      [*] = ;   gIntRegister_MapSelectedUID := 0;
      [*] = ;   SetIntValueByIndex(gc_map_PLStack_MapUnit_iSelectedUID, 0);
      [*] = ;end;
      [*] = ;
      [*] = ;if (gIntRegister_MapSelectedUID = 0) or GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead) then
      [*] = ;   ExecuteState('SelectNextHero');
      [*] = ;
      [*] = ;IntRegister0 := myPlHandle;
      [*] = ;GUIExecuteState('map.UpdatePlayerHUDs');
      [*] = ;
      [*] = ;MapExecuteState('map.FogHideObjects');
      [*] = ;
      [*] = ;if (gGame.gameType = gc_GameTypeLanShard) and (GetLanMode() >= 2) then
      [*] = ;begin
      [*] = ;   var pMachineParser : Integer = ParserSelectStateMachineByHandle(GetMapInitMachineHandle);
      [*] = ;   var pSyncInfo : Integer = ParserSelectByHandleByKey(pMachineParser, 'SyncInfo');
      [*] = ;   var pLanGame : Integer = ParserAddChildByIndex(pSyncInfo, 'Game');
      [*] = ;   StateMachineGlobalVariablesSaveToParser(pLanGame, 'gGame', false, false);
      [*] = ;
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;   begin
      [*] = ;      var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;      var cMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;
      [*] = ;      if SameText(cMode, 'cmPlayer') and _plr_IsInGame(plHandle) then
      [*] = ;         SetPlayerBoolValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_bTurnFinished, false);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if gGame.gameType = gc_GameTypeHotseat then
      [*] = ;begin
      [*] = ;   _gv_SetMapLock($10001,_log_name);
      [*] = ;   
      [*] = ;   gIntRegister_DiplomacyActivePlayerID := -1;
      [*] = ;   
      [*] = ;   _gui_ShowQuestionDialog('gui|761', cPressState, myPlIndex, cPressState, myPlIndex, True, True);
      [*] = ;end
      [*] = ;else
      [*] = ;   ExecuteState('StartHumanTurn');
      [*] = ;
      [*] = ;// TODO: debug code
      [*] = ;//IntRegister0 := 0;
      [*] = ;//MapExecuteState('map.LanCreatePlayersParser');
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

