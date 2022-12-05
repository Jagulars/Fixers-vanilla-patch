section.begin
   Name = bat.ProceedHeroesDeath
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\BAT\BAT.PROCEEDHEROESDEATH';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;gBoolRegister_IsDefenderAutoBattle := false;
      [*] = ;if not _misc_IsLanBattle() then
      [*] = ;begin
      [*] = ;   IntRegister0 := gIntRegister_BattleAttackHeroHandle;
      [*] = ;   MapExecuteState('bat.ProceedHeroDeath');
      [*] = ;
      [*] = ;   if gIntRegister_CurQueryHandle = 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := gIntRegister_BattleDefendHeroHandle;
      [*] = ;      MapExecuteState('bat.ProceedHeroDeath');
      [*] = ;
      [*] = ;      if gIntRegister_CurQueryHandle = 0 then
      [*] = ;         MapExecuteState('bat.AfterBattle');
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   var heroHandle : Integer = 0;
      [*] = ;
      [*] = ;   if (GetPlayerIndexByHandle(gIntRegister_BattleAttackPlayer) = gIntRegister_MapMyPlayerIndex) and (gIntRegister_BattleAttackHeroHandle <> 0) then
      [*] = ;      heroHandle := gIntRegister_BattleAttackHeroHandle
      [*] = ;   else
      [*] = ;      if (GetPlayerIndexByHandle(gIntRegister_BattleDefendPlayer) = gIntRegister_MapMyPlayerIndex) and (gIntRegister_BattleDefendHeroHandle <> 0) then
      [*] = ;         heroHandle := gIntRegister_BattleDefendHeroHandle;
      [*] = ;
      [*] = ;   _lan_timer_Arm(gc_lt_conflicts,0,false);
      [*] = ;
      [*] = ;   IntRegister0 := heroHandle;
      [*] = ;   MapExecuteState('bat.ProceedHeroDeath');
      [*] = ;
      [*] = ;   if gIntRegister_CurQueryHandle = 0 then
      [*] = ;   begin
      [*] = ;      _lan_LanSendParserToEnemy(gc_LAN_SHARD_PROCEEDHERODEATH, _pars_ParserEmpty);
      [*] = ;      MapExecuteState('bat.AfterBattle');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

