section.begin
   Name = bat.GetStrengthDisparity
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\BAT\BAT.GETSTRENGTHDISPARITY';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;SetActiveTrackNodeList(0);
      [*] = ;_gv_SetMapLock($10000,_log_name);
      [*] = ;
      [*] = ;var attackPlHandle, defendPlHandle : Integer;
      [*] = ;if (not gBoolRegister_BattleSimulate) or gBoolRegister_RealAIBattle then
      [*] = ;begin
      [*] = ;   attackPlHandle := GetPlayerHandleByName(gc_battle_attackPlayerName);
      [*] = ;   defendPlHandle := GetPlayerHandleByName(gc_battle_defendPlayerName);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   attackPlHandle := GetPlayerHandleByName(gc_battle_virtAttackPlayerName);
      [*] = ;   defendPlHandle := GetPlayerHandleByName(gc_battle_virtDefendPlayerName);
      [*] = ;end;
      [*] = ;
      [*] = ;var bAIPlayer : Boolean = not SameText(GetPlayerControlModeByHandle(gIntRegister_BattleAttackPlayer), 'cmPlayer');
      [*] = ;var bAccurateCheck : Boolean = (not bAIPlayer or gGame.improvedai or (gProfile.improvedai and (gGame.gameType <> gc_GameTypeLanShard))); // by default use accurate estimation only when human player is given hint on potential battle results
      [*] = ;
      [*] = ;if _log then _Log_Map('Accurate Check : '+BoolToStr(bAccurateCheck));
      [*] = ;
      [*] = ;var strength : Integer = 100;
      [*] = ;
      [*] = ;strength := strength + _army_CalcRemainingPower(attackPlHandle);
      [*] = ;strength := strength - _army_CalcRemainingPower(defendPlHandle);
      [*] = ;
      [*] = ;if _log then _Log_Map(_log_name+'[Strength Disparity = ' + IntToStr(strength)+']');
      [*] = ;
      [*] = ;IntRegister0 := strength;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

