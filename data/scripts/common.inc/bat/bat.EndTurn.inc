section.begin
   Name = bat.EndTurn
   Code : struct.begin
      [*] = ;var lanPlIndex : Integer = IntRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'COMMON.INC\BAT\BAT.ENDTURN';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var plIndex : Integer = gIntRegister_BattleCurPlIndex;
      [*] = ;var curPlHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(gIntRegister_BattleCurrentTurn)+']',_log_trace);
      [*] = ;if not gBoolRegister_BattleEndBattle then
      [*] = ;begin
      [*] = ;   var plHandle : Integer;
      [*] = ;   var autoBattle : Boolean = GetPlayerBoolValueIndByHandle(GetPlayerHandleInterfaceIO(), gc_battle_PLStack_bAutoBattle);
      [*] = ;
      [*] = ;   PlayerExecuteStateByHandle(curPlHandle, 'AfterTurn');
      [*] = ;
      [*] = ;   if (_gv_GetBattleLock() > 0) and (not gBoolRegister_BattleSimulate) and (not gBoolRegister_RealAIBattle) then
      [*] = ;   begin
      [*] = ;      gBoolRegister_BattleSwitchPlayer := true;
      [*] = ;      _gv_traceState(_log_name+'[Locked]',$1000000 or _log_trace);
      [*] = ;      exit;
      [*] = ;   end;
      [*] = ;
      [*] = ;   gIntRegister_BattleCurrentTurn := gIntRegister_BattleCurrentTurn + 1;
      [*] = ;
      [*] = ;   if _misc_IsLanBattle() then
      [*] = ;      plHandle := GetPlayerHandleByIndex(lanPlIndex)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      PlayerExecuteStateByHandle(curPlHandle, 'GetEnemyPlHandle');
      [*] = ;      plHandle := IntRegister0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if _log then _Log_map('['+ IntToStr(gIntRegister_BattleCurrentTurn)+'] AMode: '+GetPlayerControlModeByHandle(curPlHandle)+', DMode: '+GetPlayerControlModeByHandle(plHandle)+', Lan: '+BoolToStr(_misc_IsLanBattle()));
      [*] = ;
      [*] = ;   //gIntRegister_BattleCurPlIndex := GetPlayerIndexByHandle(plHandle);
      [*] = ;
      [*] = ;   gIntRegister_SelectedUID := 0;
      [*] = ;   gIntRegister_StartTrackNode := 0;
      [*] = ;   gIntRegister_EndTrackNode := 0;
      [*] = ;   gIntRegister_EndHexCell := 0;
      [*] = ;   gIntRegister_EndHexUID := 0;
      [*] = ;   gFloatRegister_UnitMoveSpeedBoost := 1;
      [*] = ;
      [*] = ;   gIntRegister_CurSpell := -1;
      [*] = ;   gIntRegister_CurSpellIndex := -1;
      [*] = ;   gIntRegister_SacrificeUID := 0;
      [*] = ;   gIntRegister_TeleportUID := 0;
      [*] = ;
      [*] = ;   gBoolRegister_BattleSwitchPlayer := false;
      [*] = ;   BoolRegister0 := true;
      [*] = ;   PlayerExecuteStateByHandle(plHandle, 'CheckFearVictory');
      [*] = ;
      [*] = ;   if gBoolRegister_IsHumanPlayer then
      [*] = ;   begin
      [*] = ;      gBoolRegister_GUIUpdateInterfacePanel := true;
      [*] = ;
      [*] = ;      if (plHandle = GetPlayerHandleInterfaceIO()) and (not gBoolRegister_BattlePlaceMode) and (not gBoolRegister_QuickBattle) and (not gBoolRegister_IsAutoBattle) and (not autoBattle) then
      [*] = ;         gBoolRegister_GUIBattleSelectNextUnit := true;
      [*] = ;
      [*] = ;      if GetPlayerBoolValueIndByHandle(GetPlayerHandleInterfaceIO(), gc_battle_PLStack_bAutoBattle) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := 1;
      [*] = ;         GUIExecuteState('DoShowScreenMessage');
      [*] = ;      end
      [*] = ;      else
      [*] = ;         GUIExecuteState('DoHideScreenMessage');
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if _log then _Log_map(_log_name+' BattleSwitchPlayer := False');
      [*] = ;   gBoolRegister_BattleSwitchPlayer := False;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

