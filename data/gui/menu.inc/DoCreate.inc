section.begin
   Name = DoCreate
   Description[*] = ;
   UsedFileName =
   Code : struct.begin
      [*] = ;if not gBoolRegister_GUIStartup then exit;
      [*] = ;
      [*] = ;gBoolRegister_GUIStartup := false;
      [*] = ;
      [*] = ;var _log_name : String = 'MENU.INC\DOCREATE';
      [*] = ;_log_gui(_log_name);
      [*] = ;
      [*] = ;var old_game_type : Integer = gGame.gameType;
      [*] = ;
      [*] = ;GUIExecuteState('DoUpdateCamera');
      [*] = ;
      [*] = ;SetCameraElasticTargetObject(0);
      [*] = ;SetCameraElasticMoveTurnOff();
      [*] = ;SetCameraElasticRotationTurnOff();
      [*] = ;SetCameraControlMode('ccmRTS');
      [*] = ;SetCameraInfoSmoothingChange(true);
      [*] = ;SetCameraBounded(false);
      [*] = ;SetCameraDynamicFocalLength(true);
      [*] = ;SetCameraControlMouseWheelRotate(false);
      [*] = ;SetCameraControlMouseWheelDistance(false);
      [*] = ;SetGUIBaseControlVisible(true);
      [*] = ;SetMiniMapFrustumVisible(false);
      [*] = ;
      [*] = ;// FixFogMode
      [*] = ;if (SameText(GetProjectOptionAsString('HDRType'), 'htNone')) and (GetFogEnable) then
      [*] = ;   SetFogEnable(False);
      [*] = ;
      [*] = ;//_gui_UpdateSettingsLowest(gProfile.settingslowest);
      [*] = ;
      [*] = ;//_gui_ReloadFontsConfig();
      [*] = ;//_gui_ReloadInterfaceDataConfig();
      [*] = ;
      [*] = ;GUIExecuteState('DoInitialize');
      [*] = ;
      [*] = ;gIntRegister_CurGameMode := gc_GameModeMenu;
      [*] = ;
      [*] = ;LanTerminateGame();
      [*] = ;
      [*] = ;_lan_timer_Reset(gc_lt_loading,true,'MENU.INC\DOCREATE');
      [*] = ;
      [*] = ;case old_game_type of
      [*] = ;   gc_GameTypeHotseat : begin
      [*] = ;      GUIExecuteState('ShowMultiplayer');
      [*] = ;      _cmd_Post('menuaction','hotseatshard','');
      [*] = ;   end;
      [*] = ;   gc_GameTypeHotseatBattle : _cmd_Post('menuaction','hotseatbattle','');
      [*] = ;   gc_GameTypeLanShard :  _cmd_Post('menuaction','lanshard','');
      [*] = ;   gc_GameTypeLanBattle :  _cmd_Post('menuaction','lanbattle','');
      [*] = ;   else begin
      [*] = ;      _gui_DelayExecuteStateOneInstance('ShowHeader', 2.0); // delay so the fade in does not get skipped because of processing lag.
      [*] = ;      _gui_DelayExecuteStateOneInstance('ShowMenu', 3.5);
      [*] = ;      if (gIntRegister_GUIRouteOnGUIRestart<>0) then
      [*] = ;      begin
      [*] = ;         case gIntRegister_GUIRouteOnGUIRestart of
      [*] = ;            1 : begin
      [*] = ;               GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;               gIntRegister_GUIRouteOnGUIRestart := 0;
      [*] = ;               GUIExecuteState('ShowSettings');
      [*] = ;               _gui_FadeElement(GetGUIElementIndexByNameParent('Settings', _gui_GetLayerI()), 0, true, false, false);
      [*] = ;            end;
      [*] = ;            2 : begin
      [*] = ;               GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;               gIntRegister_GUIRouteOnGUIRestart := 0;
      [*] = ;               GUIExecuteState('ShowSettings');
      [*] = ;               _gui_FadeElement(_gui_GetWindow('Settings'), 0, true, false, false);
      [*] = ;
      [*] = ;               const cSwitchResolutionApprove = 401;
      [*] = ;               const cSwitchResolutionCancel = 402;
      [*] = ;               _gui_ShowQuestionDialog('menu|98', 'EventSettings', cSwitchResolutionApprove, 'EventSettings', cSwitchResolutionCancel, true, false);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;GUIExecuteState('ShowVersion');
      [*] = ;
      [*] = ;if (old_game_type <> gc_GameTypeHotseat) and (old_game_type <> gc_GameTypeHotseatBattle) and (old_game_type <> gc_GameTypeLanShard) and (old_game_type <> gc_GameTypeLanBattle) then
      [*] = ;   _gui_DelayExecuteStateOneInstance('InitAstralChat', 3.5);
      [*] = ;   //_inet_InitAstralChat(false);
      [*] = ;
      [*] = ;_log_gui(_log_name+' END');
   struct.end
section.end

