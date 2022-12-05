section.begin
   Name = DoDestroy
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\DODESTROY';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;UnregisterGUIAllShortcuts();
      [*] = ;
      [*] = ;_gui_ft_UnRegisterAll();
      [*] = ;
      [*] = ;_gui_ClearLayers();
      [*] = ;
      [*] = ;SetCameraElasticTargetObject(0);
      [*] = ;GUIClearElements();
      [*] = ;SetGUIMiniMapVisible(False);
      [*] = ;SetGUIBaseControlVisible(false);
      [*] = ;
      [*] = ;//if gIntRegister_CurGameMode = 2 then
      [*] = ;//ExecuteState('DoDebugDrawHexGrid');
      [*] = ;
      [*] = ;gIntRegister_GUIScrollSliderHandle := 0;
      [*] = ;
      [*] = ;ResetBlendToLightPattern;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

