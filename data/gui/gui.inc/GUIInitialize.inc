section.begin
   Name = GUIInitialize
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\GUIINITIALIZE';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var temp_str : String;
      [*] = ;var create_lan_chat : Boolean = IsLanGame();
      [*] = ;
      [*] = ;GUIMiniMapPrimitivesClear();
      [*] = ;GUIClearElements();
      [*] = ;
      [*] = ;SetGUIMiniMapVAlign('valBottom');
      [*] = ;SetGUIMiniMapHAlign('halLeft');
      [*] = ;SetGUIMiniMapPosition(30, -30, 0);
      [*] = ;SetGUIMiniMapWidth(128);
      [*] = ;SetGUIMiniMapHeight(128);
      [*] = ;SetMiniMapFrustumVisible(false);
      [*] = ;
      [*] = ;SetGUIHintWaitDelay(0.1); //0.15
      [*] = ;
      [*] = ;if (gFloatRegister_DoDebugHintAlpha>0) then // debug
      [*] = ;   SetGUIHintWaitDelay(0);
      [*] = ;
      [*] = ;if gIntRegister_CameraMode = 0 then
      [*] = ;   SetCameraControlMouseWheelRotate(false)
      [*] = ;else
      [*] = ;   SetCameraControlMouseWheelRotate(true);
      [*] = ;
      [*] = ;_gui_ClearLayers();
      [*] = ;_gui_RootWindowInit();
      [*] = ;
      [*] = ;_gui_createLayer(cInterfaceLayer);
      [*] = ;_gui_createLayer(cDragDropLayer);
      [*] = ;_gui_createLayer(cTooltipLayer);
      [*] = ;_gui_createLayer(cTutorialLayer);
      [*] = ;_gui_createLayer(cTopmostLayer);
      [*] = ;if create_lan_chat then
      [*] = ;   _gui_createLayer(cLanChatLayer);
      [*] = ;_gui_createLayer(cChatLayer);
      [*] = ;_gui_PreloadGUITextures(_gui_GetLayerI());
      [*] = ;//_gui_ReloadFontsConfig();
      [*] = ;//_gui_ReloadInterfaceDataConfig();
      [*] = ;_cmd_ReloadCommands();
      [*] = ;_fx_FlyTextInit();
      [*] = ;
      [*] = ;if gIntRegister_CurGameMode = gc_GameModeStrategy then
      [*] = ;   temp_str := 'Global|Map'
      [*] = ;else
      [*] = ;   temp_str := 'Global|Battle';
      [*] = ;
      [*] = ;_misc_PostConsoleCommand('allowdebugkeys '+IntToStr(gIntRegister_CurGameMode),true);
      [*] = ;if _gui_GetWindow(gc_gui_allow_debug_keys_element) <> 0 then
      [*] = ;begin
      [*] = ;   _sa_Add(temp_str,'Debug');
      [*] = ;   if gIntRegister_CurGameMode = gc_GameModeStrategy then
      [*] = ;      _sa_Add(temp_str,'DebugMap')
      [*] = ;   else
      [*] = ;      _sa_Add(temp_str,'DebugBattle');
      [*] = ;   _cmd_RegisterStateForDummy('debug_commands','VVK.DebugCommands','',cRootWindowTop,0);
      [*] = ;   if (GetUserBoolValue('GUIDebug')) then
      [*] = ;      _cmd_RegisterStateForDummy('debug_commands_guixyz','DebugXYZ','',cRootWindowTop,0);
      [*] = ;   RemoveGUIElement(_gui_GetWindow(gc_gui_allow_debug_keys_element));
      [*] = ;   
      [*] = ;   gIntRegister_GVLogging := gc_gvlog_log_all;
      [*] = ;   gIntRegister_LogLanParsers := gc_gvlog_log_all_lan;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   gIntRegister_LogLanParsers := gc_gvlog_log_none;
      [*] = ;   if gc_TestVersion then
      [*] = ;      gIntRegister_GVLogging := gc_gvlog_log_all
      [*] = ;   else
      [*] = ;      gIntRegister_GVLogging := gc_gvlog_log_none;
      [*] = ;end;
      [*] = ;
      [*] = ;_misc_PostConsoleCommand('alloweditor '+IntToStr(gIntRegister_CurGameMode)+' 1',true);
      [*] = ;if _gui_GetWindow(gc_gui_allow_debug_keys_element) <> 0 then
      [*] = ;begin
      [*] = ;   if (gMapEditor.enabled) and (gIntRegister_CurGameMode=gc_GameModeStrategy) then
      [*] = ;   begin
      [*] = ;      _sa_Add(temp_str,'MapEditor');
      [*] = ;      _cmd_RegisterStateForDummy('editor_commands','ExecuteEditorCommands','',cRootWindowAttrHighest,0);
      [*] = ;   end;
      [*] = ;   RemoveGUIElement(_gui_GetWindow(gc_gui_allow_debug_keys_element));
      [*] = ;end;
      [*] = ;
      [*] = ;if create_lan_chat then
      [*] = ;begin
      [*] = ;   if gIntRegister_CurGameMode = gc_GameModeStrategy then
      [*] = ;      _sa_Add(temp_str,'LanMap')
      [*] = ;   else
      [*] = ;      _sa_Add(temp_str,'LanBattle');
      [*] = ;end;
      [*] = ;
      [*] = ;_cmd_RegisterStateForDummy('camera_commands','VVK.CameraCommands','',cRootWindowActive,0);
      [*] = ;if gTutorial.map then
      [*] = ;   _cmd_RegisterStateForDummy('tutorial_commands','VVK.TutorialCommands','',cRootWindowTop,cRootWindowAttrHighest);
      [*] = ;
      [*] = ;if gIntRegister_CurGameMode = gc_GameModeStrategy then
      [*] = ;   _cmd_RegisterStateForDummy('map_top_commands','VVK.map.TopCommands','',cRootWindowTop,cRootWindowAttrHighest)
      [*] = ;else
      [*] = ;   _cmd_RegisterStateForDummy('battle_top_commands','VVK.battle.TopCommands','',cRootWindowTop,cRootWindowAttrHighest);
      [*] = ;_cmd_RegisterShortcuts(temp_str);
      [*] = ;
      [*] = ;if gTutorial.map then
      [*] = ;   _cmd_RegisterStateForDummy('tutorial_top_commands','VVK.TopTutorialCommands','',cRootWindowTop,cRootWindowAttrHighest);
      [*] = ;
      [*] = ;if create_lan_chat then
      [*] = ;   _gui_RootWindowAddExt(_gui_GetWindow('lan_chat_command_interceptor'),cRootWindowTop,cRootWindowAttrHighest,0,'');
      [*] = ;_gui_RootWindowAddExt(_gui_GetWindow('chat_command_interceptor'),cRootWindowTop,cRootWindowAttrHighest,0,'');
      [*] = ;
      [*] = ;SetIntValueByName('DragElement', 0);
      [*] = ;SetIntValueByName('CurProvHUDParser', 0);
      [*] = ;SetIntValueByName('ProvHUDLastUnderMouse', 0);
      [*] = ;SetIntValueByName('ProvHUDHandle', 0);
      [*] = ;SetIntValueByName('MBTN', 0);
      [*] = ;SetIntValueByName('MouseDirectionX', 0);
      [*] = ;SetIntValueByName('MouseDirectionY', 0);
      [*] = ;SetBoolValueByName('KeyPressedCtrl', False);
      [*] = ;SetBoolValueByName('KeyPressedAlt', False);
      [*] = ;SetBoolValueByName('SndLevelUpPlayed', False);
      [*] = ;gBoolRegister_ShowExtendedHint := False;
      [*] = ;gBoolRegister_ShowBattleExtendedHint := False;
      [*] = ;gBoolRegister_ShowProvinceExtendedHint := False;
      [*] = ;gStrRegister_GUIBuildWindowState := '0|1|0';
      [*] = ;gStrRegister_GUIBuildHistory := '';
      [*] = ;
      [*] = ;if (gIntRegister_CurGameMode <> gc_GameModeStrategy) and (gIntRegister_CurGameMode <> gc_GameModeTactics) then
      [*] = ;begin
      [*] = ;   ErrorLogI(_log_name+' gIntRegister_CurGameMode = ' + IntToStr(gIntRegister_CurGameMode));
      [*] = ;   gIntRegister_CurGameMode := gc_GameModeStrategy;
      [*] = ;end;
      [*] = ;
      [*] = ;//gIntRegister_MapPickedInnerBuildID := 0;
      [*] = ;
      [*] = ;GUIExecuteState('DoInitSound');
      [*] = ;
      [*] = ;gIntRegister_GUIScrollSliderHandle := 0;
      [*] = ;gIntRegister_GUIActiveHeroUID1 := 0;
      [*] = ;gIntRegister_GUIActiveHeroUID2 := 0;
      [*] = ;gIntRegister_GUICurHeroMode := gc_HeroPanelNotValid;
      [*] = ;gBoolRegister_GUIExchangeSecond := False;
      [*] = ;gIntRegister_CampaignHeroesPanel := 0;
      [*] = ;gBoolRegister_GUIForceMouseMove := False;
      [*] = ;gBoolRegister_GUIProvRadialPlaceInCenter := False;
      [*] = ;gIntRegister_CurQueryHandle := 0;
      [*] = ;gIntRegister_MapDismissHeroUID := 0;
      [*] = ;
      [*] = ;
      [*] = ;case gIntRegister_CurGameMode of
      [*] = ;   gc_GameModeStrategy: GUIExecuteState('map.GUIInitialize');
      [*] = ;   gc_GameModeTactics: GUIExecuteState('battle.GUIInitialize');
      [*] = ;end;
      [*] = ;
      [*] = ;_inet_InitAstralChat(true);
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

