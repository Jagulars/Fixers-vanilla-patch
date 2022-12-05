section.begin
   Name = map.CloseShopWindow
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\MAP\MAP.CLOSESHOPWINDOW';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;if _gui_GetWindow('map_shoppanel') <> 0 then
      [*] = ;begin
      [*] = ;   _gv_SetMapLock(-1,_log_name);
      [*] = ;   _gui_RootWindowRemoveWithFade(_gui_GetWindow('map_shoppanel'),0);
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

