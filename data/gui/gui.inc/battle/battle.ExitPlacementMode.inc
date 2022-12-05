section.begin
   Name = battle.ExitPlacementMode
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\BATTLE\BATTLE.EXITPLACEMENTMODE';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;if (gIntRegister_BattleCurPlIndex <> GetPlayerIndexByHandle(GetPlayerHandleInterfaceIO)) or _misc_IsLanBattle() then
      [*] = ;begin
      [*] = ;   gIntRegister_SelectedUID := 0;
      [*] = ;   GUIExecuteState('battle.ResetHexGrid');
      [*] = ;end;
      [*] = ;
      [*] = ;if gBoolRegister_BrokenWeapon then
      [*] = ;begin
      [*] = ;   gBoolRegister_BrokenWeapon := false;
      [*] = ;   if gBoolRegister_BtnSwitchWeaponBlink then
      [*] = ;      _gui_RemoveBlinkElement('btnSwitchWeapon', gBoolRegister_BtnSwitchWeaponBlink);
      [*] = ;end;
      [*] = ;
      [*] = ;gBoolRegister_BattlePlaceMode := False;
      [*] = ;
      [*] = ;MapExecuteState('bat.ShowUnits');
      [*] = ;
      [*] = ;GUIExecuteState('battle.CreateControlPanelWindow');
      [*] = ;RemoveGUIElement(_gui_GetWindow('blinker_top.blink_battle_start'));
      [*] = ;
      [*] = ;GUIExecuteState('DoHideScreenMessage');
      [*] = ;
      [*] = ;GUIExecuteState('lan.ExitPlacementMode');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

