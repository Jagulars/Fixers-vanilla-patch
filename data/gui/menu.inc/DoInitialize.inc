section.begin
   Name = DoInitialize
   Code : struct.begin
      [*] = ;var _log_name : String = 'MENU.INC\DOINITIALIZE';
      [*] = ;_log_gui(_log_name);
      [*] = ;
      [*] = ;var temp_str : String;
      [*] = ;
      [*] = ;GUIMiniMapPrimitivesClear();
      [*] = ;GUIClearElements();
      [*] = ;
      [*] = ;_gui_ClearLayers();
      [*] = ;_gui_RootWindowInit();
      [*] = ;_gui_createLayer(cInterfaceLayer);
      [*] = ;_gui_createLayer(cDragDropLayer);
      [*] = ;_gui_createLayer(cTooltipLayer);
      [*] = ;_gui_createLayer(cTutorialLayer);
      [*] = ;_gui_createLayer(cTopmostLayer);
      [*] = ;_gui_createLayer(cChatLayer);
      [*] = ;
      [*] = ;_gui_PreloadGUITextures(_gui_GetLayerI());
      [*] = ;//_misc_BuildOuterBuildingsExtraData();
      [*] = ;
      [*] = ;gIntConsoleStateMachineHandle := StateMachineLibraryGetOrAdd('.\data\gui\cc.menu.aix');
      [*] = ;
      [*] = ;GUIExecuteState('DoInitSound');
      [*] = ;
      [*] = ;SetIntValueByName('MouseDirectionX', 0);
      [*] = ;SetIntValueByName('MouseDirectionY', 0);
      [*] = ;
      [*] = ;gIntRegister_CurDemoMode := 0;
      [*] = ;gBoolRegister_GUIShowFinishCampaign := False;
      [*] = ;gIntRegister_InetRecruitRankMode := 1;
      [*] = ;gIntRegister_InetLibraryRankMode := 1;
      [*] = ;gIntRegister_InetShopRankMode := 1;
      [*] = ;gIntRegister_InetShopSortMode := 0;
      [*] = ;gBoolRegister_InetStartBattle := False;
      [*] = ;gIntRegister_InetPickedUnitSlot := 0;
      [*] = ;gIntRegister_InetPickedSpellSlot := -1;
      [*] = ;gIntRegister_InetPickedItemSlot := -1;
      [*] = ;gIntRegister_InetShopPickedSpellID := 0;
      [*] = ;gIntRegister_InetShopPickedUnitID := 0;
      [*] = ;gIntRegister_InetShopPickedItemID := 0;
      [*] = ;gBoolRegister_InetUnitLevelUpMode := False;
      [*] = ;gIntRegister_InetUnitLevelUpSlot := 0;
      [*] = ;//gIntRegister_CurHeroUIDInfo := 0;
      [*] = ;gIntRegister_CurQueryHandle := 0;
      [*] = ;gBoolRegister_GUIForceMouseMove := False;
      [*] = ;gArr_gui_float_tooltips_check_time := 0;
      [*] = ;
      [*] = ;gGame.gametype := gc_GameTypeNone;
      [*] = ;
      [*] = ;gIntRegister_DemoQueryIntro := GetUserIntValue('DemoQueryIntro');
      [*] = ;gIntRegister_DemoQueryCampaign := GetUserIntValue('DemoQueryCampaign');
      [*] = ;gIntRegister_DemoQueryMap := GetUserIntValue('DemoQueryMap');
      [*] = ;gIntRegister_DemoQueryBattle := 0;
      [*] = ;
      [*] = ;_cmd_ReloadCommands();
      [*] = ;_cmd_RegisterStateForDummy('menu_commands','VVK.MenuCommands','',cRootWindowNormal,0);
      [*] = ;temp_str := 'Global|Menu';
      [*] = ;_misc_PostConsoleCommand('allowdebugkeys '+IntToStr(gc_GameModeMenu),true);
      [*] = ;if _gui_GetWindow(gc_gui_allow_debug_keys_element) <> 0 then
      [*] = ;begin
      [*] = ;   _sa_Add(temp_str,'DebugMenu');
      [*] = ;   _cmd_RegisterStateForDummy('debug_commands','VVK.DebugCommands','',cRootWindowTop,0);
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
      [*] = ;_gui_ft_UnRegisterAll();
      [*] = ;_gui_ft_Register(cItemTooltipWindowName,'VVK.FTooltipItem');
      [*] = ;_gui_ft_Register(cSpellTooltipWindowName,'VVK.FTooltipSpell');
      [*] = ;
      [*] = ;_log_gui(_log_name+' END');
   struct.end
section.end

