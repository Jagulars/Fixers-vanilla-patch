section.begin
   Name = MakeStratHexGrid
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\MAKESTRATHEXGRID';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;gBoolRegister_GeneratorFinished := False;
      [*] = ;
      [*] = ;SetObjectBasedVisibilityCulling(false);
      [*] = ;SetTerrainVisible(true);
      [*] = ;SetTerrainBordersVisible(false);
      [*] = ;
      [*] = ;if (gMapEditor.enabled) then
      [*] = ;begin
      [*] = ;   //_editor_LoadMapDataFromFile('gMapEditor');
      [*] = ;   SetRandomExtKey64(gMapEditor.randkey0, gMapEditor.randkey1);
      [*] = ;end;
      [*] = ;
      [*] = ;ExecuteState('map.InitGrid');
      [*] = ;ExecuteState('SetupGridVertices');
      [*] = ;ExecuteState('MakeTerrain');
      [*] = ;ExecuteState('InitRegisters');
      [*] = ;
      [*] = ;if (gGame.gameType <> gc_GameTypeHotseatBattle) and (gGame.gameType <> gc_GameTypeLanBattle) then
      [*] = ;begin
      [*] = ;   if (not ((gMapEditor.enabled) and (gBoolRegister_EditorFastGeneration))) then
      [*] = ;      ExecuteState('CreateTown');
      [*] = ;   
      [*] = ;   if gGame.gameType = gc_GameTypeCampaign then
      [*] = ;      ExecuteState('map.ApplyBonuses');
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister0 := _obj_GetCheckSceneryFlags($ff, $ff, $ff, $ff, gProfile.battlescenery);
      [*] = ;GUIExecuteState('CheckScenery');
      [*] = ;
      [*] = ;gBoolRegister_GeneratorFinished := True;
      [*] = ;
      [*] = ;ExecuteState('DrawStratHexGrid');
      [*] = ;ExecuteState('bat.InitGrid');
      [*] = ;
      [*] = ;if (not ((gMapEditor.enabled) and (gBoolRegister_EditorFastGeneration))) then
      [*] = ;   ExecuteState('CreateCameras');
      [*] = ;
      [*] = ;_log_battle_Clear();
      [*] = ;
      [*] = ;SetActiveTrackNodeList(0);
      [*] = ;
      [*] = ;if (gGame.gameType = gc_GameTypeHotseatBattle) or (gGame.gameType = gc_GameTypeLanBattle) then
      [*] = ;begin
      [*] = ;   ExecuteState('CreateInetGame');
      [*] = ;   //ExecuteState('CreateInetBattle');
      [*] = ;   //ExecuteState('CreateInetBattleAfterGen');
      [*] = ;   //GUIExecuteState('map.SwitchToBattle');
      [*] = ;end
      [*] = ;else
      [*] = ;if {(gc_demoVersion=1) and} (gIntRegister_CurDemoMode>0) then
      [*] = ;begin
      [*] = ;   if (gIntRegister_CurDemoMode=1) or (gIntRegister_CurDemoMode=2) then
      [*] = ;      ExecuteState('CreateDemoGame');
      [*] = ;
      [*] = ;   if (gIntRegister_CurDemoMode=2) then
      [*] = ;   begin
      [*] = ;      ExecuteState('CreateDemoBattle');
      [*] = ;      ExecuteState('CreateDemoBattleAfterGen');
      [*] = ;      GUIExecuteState('map.SwitchToBattle');
      [*] = ;   end;
      [*] = ;
      [*] = ;   _misc_ParserGetOrCreateByKey('DemoGame',true);
      [*] = ;   //gIntRegister_CurDemoMode := 3; // Ready for finish game
      [*] = ;end;
      [*] = ;if (gMapEditor.enabled) then
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to gMapEditor.map.players-1 do
      [*] = ;   begin
      [*] = ;      if (gMapEditor.players[i].castleprovind>-1) then
      [*] = ;      begin
      [*] = ;         var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;         _editor_AssignPlayerHeroesToCurrentMap(plHandle, gMapEditor.players[i]);
      [*] = ;      end;
      [*] = ;      gGUIEditor.selhero := 0;
      [*] = ;      gIntRegister_MapSelectedUID := 0;
      [*] = ;   end;
      [*] = ;   if (gMapEditor.run) then // turn off editor interface to play premade map
      [*] = ;   begin
      [*] = ;      gMapEditor.enabled := False;
      [*] = ;      gScenario.enabled := true;
      [*] = ;      if gGame.fog then
      [*] = ;         ExecuteState('map.DoFogOfWar');
      [*] = ;   end;
      [*] = ;   if (gScenario.enabled) then
      [*] = ;      _scenario_InitTriggers(gScenario);
      [*] = ;
      [*] = ;   if (gBoolRegister_EditorFastGeneration) then
      [*] = ;   begin
      [*] = ;      GUIExecuteState('DoDestroy');
      [*] = ;      GUIExecuteState('DoCreate');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;gBoolRegister_GUIStartup := true;
      [*] = ;IntRegister0 := 0;
      [*] = ;GUIExecuteState('vvk.map.UpdateProvinceHUD');
      [*] = ;
      [*] = ;
      [*] = ;//if gProfile.simplegraphics then
      [*] = ;//   _actor_CheckSimplifiedGraphics();
      [*] = ;//if (gProfile.settingslowest) then
      [*] = ;//   _gui_RecalcSettingsLowest(gProfile.settingslowest);
      [*] = ;gBoolRegister_GUIProgressOnceOnGUIDoCreate := True;
      [*] = ;
      [*] = ;TimeLog('Generating map finished');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

