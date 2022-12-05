section.begin
   Name = bat.CheckSabotage
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\BAT\BAT.CHECKSABOTAGE';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;
      [*] = ;var bProceedTurn : Boolean = True;
      [*] = ;
      [*] = ;var IOPlHandle : Integer = GetPlayerHandleInterfaceIO();
      [*] = ;var aPlHandle : Integer = GetPlayerHandleByName(gc_battle_attackPlayerName);
      [*] = ;var dPlHandle : Integer = GetPlayerHandleByName(gc_battle_defendPlayerName);
      [*] = ;
      [*] = ;var bCheckAtt : Boolean = GetPlayerBoolValueIndByHandle(aPlHandle, gc_battle_PLStack_bCheckSabotage);
      [*] = ;var bCheckDef : Boolean = GetPlayerBoolValueIndByHandle(dPlHandle, gc_battle_PLStack_bCheckSabotage);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[Check Attacker: '+BoolToStr(bCheckAtt)+', Check Defender: '+BoolToStr(bCheckDef)+']',_log_trace);
      [*] = ;
      [*] = ;if GetPlayerBoolValueIndByHandle(IOPlHandle, gc_battle_PLStack_bCheckSabotage) then
      [*] = ;begin
      [*] = ;   // both players get a chance for sabotage in battle mode
      [*] = ;   if (gGame.gameType = gc_GameTypeHotseatBattle) or (gGame.gameType = gc_GameTypeLanBattle) then
      [*] = ;   begin
      [*] = ;      PlayerExecuteStateByHandle(IOPlHandle, 'CheckSabotage');
      [*] = ;      bProceedTurn := BoolRegister0;
      [*] = ;   end
      [*] = ;   else // only attacking hero can sabotage
      [*] = ;   if (gIntRegister_BattleAttackHeroHandle <> 0) then
      [*] = ;   begin
      [*] = ;      var needCheck : Boolean = false;
      [*] = ;      PlayerExecuteStateByHandle(aPlHandle, 'CheckHumanTurn');
      [*] = ;      needCheck := needCheck or BoolRegister0;
      [*] = ;      PlayerExecuteStateByHandle(dPlHandle, 'CheckHumanTurn');
      [*] = ;      needCheck := needCheck or BoolRegister0;
      [*] = ;
      [*] = ;      if ((not gBoolRegister_IsHumanPlayer) or needCheck) and ((not _misc_BattleBothHuman) or (aPlHandle = IOPlHandle)) then
      [*] = ;      begin
      [*] = ;         PlayerExecuteStateByHandle(aPlHandle, 'CheckSabotage');
      [*] = ;         bProceedTurn := BoolRegister0;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if bProceedTurn and ((not GetPlayerBoolValueIndByHandle(aPlHandle, gc_battle_PLStack_bCheckSabotage)) and (not GetPlayerBoolValueIndByHandle(dPlHandle, gc_battle_PLStack_bCheckSabotage))) then
      [*] = ;begin
      [*] = ;   var pExitPlacement : Integer = _misc_ParserGetOrCreateByKey('battle_placement', false);
      [*] = ;   var pSabotages : Integer = ParserSelectByHandleByKey(pExitPlacement, 'Sabotage');
      [*] = ;   
      [*] = ;   var i, pSabotage : Integer;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pSabotages)-1 do
      [*] = ;   begin
      [*] = ;      pSabotage := ParserSelectByHandleByIndex(pSabotages, i);
      [*] = ;      IntRegister0 := ParserGetIntValueByKeyByHandle(pSabotage, 'SabotageIndex');
      [*] = ;      PlayerExecuteStateByHandle(GetPlayerHandleByIndex(ParserGetIntValueByKeyByHandle(pSabotage, 'PlayerIndex')), 'MakeSabotage');
      [*] = ;   end;
      [*] = ;
      [*] = ;   ParserClearByHandle(pSabotages);
      [*] = ;end;
      [*] = ;
      [*] = ;BoolRegister0 := bProceedTurn;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[Proceed Turn: '+BoolToStr(bProceedTurn)+']',$1000000 or _log_trace);
   struct.end
section.end

