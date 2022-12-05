section.begin
   Name = vvk.map.HeroAstralTransfer
   Description : struct.begin
      [*] = ;displays hero selection window
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\MAP\VVK.MAP.HEROASTRALTRANSFER';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;if _plr_GetNonBuriedHeroCount(GetPlayerHandleInterfaceIO()) = 0 then
      [*] = ;begin
      [*] = ;   if (gBoolRegister_MapWin) then
      [*] = ;   begin
      [*] = ;      if gCampaign.defender then
      [*] = ;      begin
      [*] = ;         BoolRegister0 := true;
      [*] = ;         IntRegister0 := 0;
      [*] = ;         GUIExecuteState('map.CreateStatistics');
      [*] = ;      end
      [*] = ;      else
      [*] = ;         GUIExecuteState('map.CreateShardCapture');
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if gIntRegister_MapSelectedUID = 0 then
      [*] = ;      gIntRegister_MapSelectedUID := GetGameObjectUniqueIdByHandle(GetGameObjectHandleByIndex(0,GetPlayerHandleInterfaceIO()));
      [*] = ;   gIntRegister_GUIActiveHeroUID2 := 0;
      [*] = ;   BoolRegister0 := false;
      [*] = ;   GUIExecuteState('map.CloseHeroWindow');
      [*] = ;   gIntRegister_GUICurHeroMode := gc_HeroPanelBothPanels;
      [*] = ;   gIntRegister_GUIActiveHeroUID1 := gIntRegister_MapSelectedUID;
      [*] = ;   gIntRegister_CampaignHeroesPanel := 1;
      [*] = ;   GUIExecuteState('map.CreateHeroWindow');
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end
