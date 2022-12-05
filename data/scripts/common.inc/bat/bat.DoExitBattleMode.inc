section.begin
   Name = bat.DoExitBattleMode
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\BAT\BAT.DOEXITBATTLEMODE';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;if _log then _Log_lan('Exit battle mode. In battle: '+ BoolToStr(gBoolRegister_InBattle)+', game mode: '+ IntToStr(gIntRegister_CurGameMode));
      [*] = ;if gBoolRegister_InBattle or (gIntRegister_CurGameMode <> gc_GameModeTactics) then
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleByIndex(gIntRegister_MapMyPlayerIndex);
      [*] = ;
      [*] = ;   _gv_SetIOHandle(plHandle,_log_name);
      [*] = ;   SetActiveTrackNodeList(0);
      [*] = ;
      [*] = ;   if gIntRegister_CurGameMode = gc_GameModeTactics then
      [*] = ;      gBoolRegister_GUIBattleExitBattleMode := true
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if gStringRegister_AfterBattleQuery <> '' then
      [*] = ;      begin
      [*] = ;         StringRegister0 := gStringRegister_AfterBattleQuery;
      [*] = ;         GUIExecuteState('map.RequestQueryWindow');
      [*] = ;         gStringRegister_AfterBattleQuery := '';
      [*] = ;      end;
      [*] = ;
      [*] = ;      _gv_SetMapLock($10000,_log_name);
      [*] = ;      gBoolRegister_MapProceedBattle := false;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if gIntRegister_BattleAttackHeroHandle <> 0 then
      [*] = ;   begin
      [*] = ;      GameObjectExecuteStateByHandle(gIntRegister_BattleAttackHeroHandle, 'ClearSiteLoot');
      [*] = ;   end;
      [*] = ;
      [*] = ;   gBoolRegister_ResetBattleData := true;
      [*] = ;   gBoolRegister_InBattle := false;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

