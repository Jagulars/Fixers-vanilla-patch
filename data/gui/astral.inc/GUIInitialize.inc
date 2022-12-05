section.begin
   Name = GUIInitialize
   Code : struct.begin
      [*] = ;var _log_name : String = 'ASTRAL.INC\GUIINITIALIZE';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var temp_str : String;
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
      [*] = ;SetGUIHintWaitDelay(0.1);
      [*] = ;
      [*] = ;_gui_ClearLayers();
      [*] = ;_gui_RootWindowInit();
      [*] = ;
      [*] = ;_gui_createLayer(cInterfaceLayer);
      [*] = ;_gui_createLayer(cTooltipLayer);
      [*] = ;_gui_createLayer(cTutorialLayer);
      [*] = ;_gui_createLayer(cTopmostLayer);
      [*] = ;_gui_createLayer(cChatLayer);
      [*] = ;
      [*] = ;gIntConsoleStateMachineHandle := StateMachineLibraryGetOrAdd('.\data\gui\cc.astral.aix');
      [*] = ;
      [*] = ;_gui_PreloadGUITextures(_gui_GetLayerI());
      [*] = ;
      [*] = ;//_gui_ReloadFontsConfig();
      [*] = ;//_gui_ReloadInterfaceDataConfig();
      [*] = ;//_misc_BuildOuterBuildingsExtraData();
      [*] = ;
      [*] = ;_cmd_ReloadCommands();
      [*] = ;_cmd_RegisterStateForDummy('astral_top_commands','VVK.AstralTopCommands','',cRootWindowTop,cRootWindowAttrHighest);
      [*] = ;temp_str := 'Global|Astral';
      [*] = ;_misc_PostConsoleCommand('allowdebugkeys '+IntToStr(gc_GameModeAstral),true);
      [*] = ;if _gui_GetWindow(gc_gui_allow_debug_keys_element) <> 0 then
      [*] = ;begin
      [*] = ;   _sa_Add(temp_str,'DebugAstral');
      [*] = ;   _cmd_RegisterStateForDummy('debug_commands','VVK.DebugCommands','',cRootWindowTop,0);
      [*] = ;   if (GetUserBoolValue('GUIDebug')) then
      [*] = ;      _cmd_RegisterStateForDummy('debug_commands_guixyz','DebugXYZ','',cRootWindowTop,0);
      [*] = ;   RemoveGUIElement(_gui_GetWindow(gc_gui_allow_debug_keys_element));
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
      [*] = ;_cmd_RegisterShortcuts(temp_str);
      [*] = ;
      [*] = ;SetFloatValueByName('StartBattleTime', 0);
      [*] = ;SetIntValueByName('MouseDirectionX', 0);
      [*] = ;SetIntValueByName('MouseDirectionY', 0);
      [*] = ;
      [*] = ;GUIExecuteState('CreateHUD');
      [*] = ;GUIExecuteState('GUICreateMouseControls');
      [*] = ;GUIExecuteState('CreateControlPanel');
      [*] = ;_cmd_RegisterStateForDummy('astral_mainpanel_commands','VVK.AstralCommands','',cRootWindowNormal,0);
      [*] = ;
      [*] = ;GUIExecuteState('DoInitSound');
      [*] = ;
      [*] = ;_gv_SetAstralLock($10000,_log_name);
      [*] = ;gBoolRegister_ShardBattleStarted := false;
      [*] = ;gIntRegister_GUITutorialChooseDifficultyMode := 0;
      [*] = ;gIntRegister_CurQueryHandle := 0;
      [*] = ;gBoolRegister_GUIForceMouseMove := False;
      [*] = ;gBoolRegister_GUIUpdateInterfacePanel := False;
      [*] = ;
      [*] = ;_gui_ft_UnRegisterAll();
      [*] = ;_gui_ft_Register(cInnerBuildingTooltipWindowName,'VVK.FTooltipInnerBuilding');
      [*] = ;_gui_ft_Register(cItemTooltipWindowName,'VVK.FTooltipItem');
      [*] = ;_gui_ft_Register(cSpellTooltipWindowName,'VVK.FTooltipSpell');
      [*] = ;_gui_ft_Register(cDefenderTooltipWindowName,'VVK.FTooltipDefender');
      [*] = ;_gui_ft_Register(cOuterBuildTooltipWindowName,'VVK.FTooltipOuterBuild');
      [*] = ;gArr_gui_float_tooltips_check_time := 0;
      [*] = ;
      [*] = ;if StateMachineGetBoolValueByName(GetMapInitMachineHandle(), 'LoadAstral') = true then
      [*] = ;   MapExecuteState('astral.BackToCampaign');
      [*] = ;
      [*] = ;GUIExecuteState('CreateShowTutorialButton');
      [*] = ;
      [*] = ;_inet_InitAstralChat(true);
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

