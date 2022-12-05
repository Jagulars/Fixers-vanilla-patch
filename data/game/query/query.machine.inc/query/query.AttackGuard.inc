section.begin
   Name = query.AttackGuard
   Code : struct.begin
      [*] = ;var _log_name : String = 'QUERY\QUERY.ATTACKGUARD';
      [*] = ;var _log_trace : Integer = $80001;
      [*] = ;
      [*] = ;if gGame.quickgame and (not gBoolRegister_IsDefenderAutoBattle) then
      [*] = ;begin
      [*] = ;   ExecuteState('query.AttackGuardAuto');
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;var goHandle : Integer = GetGameObjectHandleByIndex(gIntRegister_MapCurHeroIndex, _gv_GetCurrentPlayerHandle());
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[P:'+GetPlayerNameByHandle(GetGameObjectPlayerHandleByHandle(goHandle))+']',_log_trace);
      [*] = ;
      [*] = ;//var siteInd : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iSiteIndex);
      [*] = ;
      [*] = ;if gIntRegister_CurGameMode = gc_GameModeStrategy then
      [*] = ;begin
      [*] = ;   IntRegister0 := _misc_GetProvinceParserByUID(GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID));
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'CheckAttackMode');
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   IntRegister0 := gIntRegister_BattleDefendArmy;
      [*] = ;   IntRegister1 := gIntRegister_BattleDefendHeroHandle;
      [*] = ;   GameObjectExecuteStateByHandle(goHandle,'StartBattleWithArmy');
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

