section.begin
   Name = battle.DoProgressGUI
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\BATTLE\BATTLE.DOPROGRESSGUI';
      [*] = ;
      [*] = ;var _log : Boolean = false;
      [*] = ;var gf : Integer;
      [*] = ;var lan_battle : Boolean = _misc_IsLanBattle();
      [*] = ;
      [*] = ;if _log and GetUserBoolValue('GUIDebug') then
      [*] = ;begin
      [*] = ;   var iTag : Integer = GetIntValueByName('Tag');
      [*] = ;   case iTag of
      [*] = ;      661: gIntRegister_dbgX := gIntRegister_dbgX-1;
      [*] = ;      662: gIntRegister_dbgX := gIntRegister_dbgX+1;
      [*] = ;      663: gIntRegister_dbgY := gIntRegister_dbgY-1;
      [*] = ;      664: gIntRegister_dbgY := gIntRegister_dbgY+1;
      [*] = ;      671: gIntRegister_dbgX := gIntRegister_dbgX-10;
      [*] = ;      672: gIntRegister_dbgX := gIntRegister_dbgX+10;
      [*] = ;      673: gIntRegister_dbgY := gIntRegister_dbgY-10;
      [*] = ;      674: gIntRegister_dbgY := gIntRegister_dbgY+10;
      [*] = ;      681: gIntRegister_dbgZ := gIntRegister_dbgZ-1;
      [*] = ;      682: gIntRegister_dbgZ := gIntRegister_dbgZ+1;
      [*] = ;   end;
      [*] = ;   if (gFloatRegister_gDbgFloat0PrevValue <> gIntRegister_dbgX) or (gFloatRegister_gDbgFloat1PrevValue <> gIntRegister_dbgY) or (gFloatRegister_gDbgFloat2PrevValue <> gIntRegister_dbgZ) then
      [*] = ;   begin
      [*] = ;      //ExecuteState('ShowBattleSettings');
      [*] = ;      //SetIntValueByName('ElementHandle', GetGUIElementUnderMouse);
      [*] = ;      //ExecuteState('OnMouseEnter');
      [*] = ;   end;
      [*] = ;
      [*] = ;   gFloatRegister_gDbgFloat0PrevValue := gIntRegister_dbgX;
      [*] = ;   gFloatRegister_gDbgFloat1PrevValue := gIntRegister_dbgY;
      [*] = ;   gFloatRegister_gDbgFloat2PrevValue := gIntRegister_dbgZ;
      [*] = ;   procedure CreateTestBoomPFX;
      [*] = ;   begin
      [*] = ;      var plName : String = 'projectiles';
      [*] = ;      var plHandle : Integer = GetPlayerHandleByName(plName);
      [*] = ;      if (plHandle=0) then
      [*] = ;      plHandle := CreatePlayer(plName, 'misc', 'cmNone');
      [*] = ;      var goHnd : Integer = CreatePlayerGameObjectHandleByHandle(plHandle, 'misc', 'weapon.empty', -62, 2, 55);
      [*] = ;      GameObjectDelayExecuteStateByHandle(goHnd, 'Destroy', 0.5);
      [*] = ;      GameObjectPFXSrcLibCreateByHandle(goHnd, 'spellboomperlin1', 'spellboomperlin1');
      [*] = ;      GameObjectPFXSrcLibCreateByHandle(goHnd, 'spellboomperlin2', 'spellboomperlin2');
      [*] = ;      GameObjectPFXSrcLibCreateByHandle(goHnd, 'spellboomperlin3', 'spellboomperlin3');
      [*] = ;   end;
      [*] = ;   CreateTestBoomPFX();
      [*] = ;end;
      [*] = ;
      [*] = ;if (gIntRegister_GUICurCastleMode=0) then
      [*] = ;   GUIExecuteState('UpdateCameraRestrict');
      [*] = ;
      [*] = ;//if (not GetProgressingPauseMode()) and (_gui_GetWindow('Settings')=0) then // there is no point in doing this every update frame for every unit when it can be done only when consumption of stats happens
      [*] = ;//   GUIExecuteState('battle.UnitHUDControl');
      [*] = ;
      [*] = ;if (gBoolRegister_GUIUpdateInterfacePanel) then
      [*] = ;begin
      [*] = ;   GUIExecuteState('battle.CreateControlPanelWindow');
      [*] = ;   gBoolRegister_GUIUpdateInterfacePanel := False;
      [*] = ;end;
      [*] = ;
      [*] = ;if (_cmd_CheckNF('battleunfreeze','','') = 1) then
      [*] = ;begin
      [*] = ;   ErrorLogI('Seems that battle is frozen. Unfreezing.');
      [*] = ;   _cmd_Post('battleunfreeze','','');
      [*] = ;end;
      [*] = ;
      [*] = ;if (gBoolRegister_GUIBattleExitBattleMode) and (gIntRegister_GUINoSpaceForItemHeroUID = 0) then
      [*] = ;begin
      [*] = ;   if _log then _Log_gui('gBoolRegister_GUIBattleExitBattleMode = True');
      [*] = ;   SetBoolValueByName('FadeFromBattleMode', true);
      [*] = ;   IntRegister0 := gc_gui_ModeMap;
      [*] = ;   FloatRegister0 := gc_gui_FadeTime1_25;
      [*] = ;   StringRegister0 := '';
      [*] = ;   GUIExecuteState('VVK.SwitchGameMode');
      [*] = ;   gBoolRegister_GUIBattleExitBattleMode := False;
      [*] = ;end;
      [*] = ;
      [*] = ;if GetBoolValueByName('FadeFromBattleMode') then
      [*] = ;   exit;
      [*] = ;
      [*] = ;if (gBoolRegister_GUIUpdateBattlePlacementMode) then
      [*] = ;begin
      [*] = ;   gBoolRegister_GUIUpdateBattlePlacementMode := false;
      [*] = ;   if (gBoolRegister_BattlePlaceMode) then
      [*] = ;      GUIExecuteState('battle.SetPlacementMode')
      [*] = ;   else
      [*] = ;      GUIExecuteState('battle.ExitPlacementMode');
      [*] = ;end;
      [*] = ;
      [*] = ;if (gBoolRegister_GUIBattleSelectNextUnit) then
      [*] = ;begin
      [*] = ;   gBoolRegister_GUIBattleSelectNextUnit := False;
      [*] = ;   gBoolRegister_GUIBattleResetHexGrid := true;
      [*] = ;   GUIExecuteState('battle.SelectNextUnit');
      [*] = ;end;
      [*] = ;
      [*] = ;if (gBoolRegister_GUIBattleResetHexGrid) then
      [*] = ;begin
      [*] = ;   if (GetGUIElementUnderMouse()=0) then
      [*] = ;      GUIExecuteState('battle.CreateTooltip');
      [*] = ;   gBoolRegister_GUIBattleResetHexGrid := false;
      [*] = ;   gBoolRegister_GUIBattleUpdateHexGrid := false;
      [*] = ;   gIntRegister_GUIBattleTooltipLastEndHexCell := 0;
      [*] = ;   GUIExecuteState('battle.ResetHexGrid');
      [*] = ;   GUIExecuteState('battle.UpdateCursor');
      [*] = ;end;
      [*] = ;
      [*] = ;if (gBoolRegister_GUIBattleUpdateHexGrid) then
      [*] = ;begin
      [*] = ;   if (GetGUIElementUnderMouse()=0) then
      [*] = ;      GUIExecuteState('battle.CreateTooltip');
      [*] = ;   gBoolRegister_GUIBattleUpdateHexGrid := false;
      [*] = ;   gIntRegister_GUIBattleTooltipLastEndHexCell := 0;
      [*] = ;   GUIExecuteState('battle.UpdateHexGrid');
      [*] = ;   GUIExecuteState('battle.UpdateCursor');
      [*] = ;end;
      [*] = ;
      [*] = ;if (gBoolRegister_NeedSeasonChangeObjects) then
      [*] = ;begin
      [*] = ;   MapExecuteState('CreateSeasons');
      [*] = ;   gBoolRegister_NeedSeasonChangeObjects := False; // Need to set after execute CreateSeasons
      [*] = ;end;
      [*] = ;
      [*] = ;if lan_battle then
      [*] = ;   GUIExecuteState('lan.OnProgressClientEndTurn');
      [*] = ;
      [*] = ;if gBoolRegister_GUIEndTurn and (_gv_GetBattleLock() = 0) then
      [*] = ;begin
      [*] = ;   if lan_battle then
      [*] = ;   begin
      [*] = ;      if (LanMyInfoID() = gIntRegsiter_LanBatServerID) then
      [*] = ;      begin
      [*] = ;         gBoolRegister_GUIEndTurn := false;
      [*] = ;         ExecuteState('lan.OnProgressEndTurn')
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      gBoolRegister_GUIEndTurn := false;
      [*] = ;      IntRegister0 := -1;
      [*] = ;      MapExecuteState('bat.EndTurn');
      [*] = ;      gIntRegister_StartTrackNode := 0;
      [*] = ;      gIntRegister_SelectedUID := 0;
      [*] = ;      GUIExecuteState('battle.DoDrawHexGrid');
      [*] = ;   end
      [*] = ;end;
      [*] = ;
      [*] = ;if (gIntRegister_QuerySpellUsage>0) then
      [*] = ;begin
      [*] = ;   gIntRegister_QuerySpellUsage := -1*gIntRegister_QuerySpellUsage;
      [*] = ;
      [*] = ;   StringRegister0 := IntToStr(gc_gui_query_battleRestrictSpellUsage);
      [*] = ;   GUIExecuteState('map.RequestQueryWindow');
      [*] = ;end;
      [*] = ;
      [*] = ;// chatnet : Crash after _cmd_Post('generallanconsolereceive','',IntToStr(idFrom)+#128+msg);
      [*] = ;gf :=  _misc_GetGameFlags();
      [*] = ;if ((gf and (gc_GameTypeFlagInternet or gc_GameTypeFlagSingle)) = gc_GameTypeFlagInternet) then
      [*] = ;begin
      [*] = ;   // this is VERY weird part of code - why on the Earth they do not call 'Nothing' on client machines???
      [*] = ;   // I think because in case either player loses when loss is checked in Nothing, on the master's machine, it will send the parser about loss to the client.
      [*] = ;   if (gGame.gameType = gc_GameTypeLanShard) and (GetLanMode() = 1) then // but then again this only checks on client machines
      [*] = ;   begin
      [*] = ;      PlayerExecuteStateByHandle(GetPlayerHandleByName(gc_battle_attackPlayerName), 'Nothing');
      [*] = ;      PlayerExecuteStateByHandle(GetPlayerHandleByName(gc_battle_defendPlayerName), 'Nothing');
      [*] = ;   end;
      [*] = ;
      [*] = ;   if lan_battle then
      [*] = ;      GUIExecuteState('lan.DoProgressGUI');
      [*] = ;end;
   struct.end
section.end

