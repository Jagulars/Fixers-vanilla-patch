section.begin
   Name = CheckHumanPlayer
   Description : struct.begin
      [*] = ;IntRegister0 - province parser
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\CHECKHUMANPLAYER';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;
      [*] = ;procedure CheckHumanPlayer(plHandle, enPlHandle, pArmy, pProvDefender : Integer);
      [*] = ;begin
      [*] = ;   if SameText(GetPlayerControlModeByHandle(plHandle), 'cmPlayer') then
      [*] = ;   begin
      [*] = ;      if (pArmy <> pProvDefender) then
      [*] = ;      begin
      [*] = ;         //if (gProfile.autocombat <> 0) and (enPlHandle = 0) then
      [*] = ;         //   gBoolRegister_IsAutoBattle := true
      [*] = ;         //else
      [*] = ;            gBoolRegister_IsHumanPlayer := true;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         gBoolRegister_IsDefenderBattle := true;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var pProvince : Integer = IntRegister0;
      [*] = ;var pProvDefender : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID'))+']',_log_trace);
      [*] = ;
      [*] = ;gBoolRegister_IsHumanPlayer := false;
      [*] = ;gBoolRegister_IsDefenderBattle := false;
      [*] = ;gBoolRegister_IsAutoBattle := false;
      [*] = ;
      [*] = ;if not gBoolRegister_IsDefenderAutoBattle then
      [*] = ;begin
      [*] = ;   CheckHumanPlayer(gIntRegister_BattleAttackPlayer, gIntRegister_BattleDefendPlayer, gIntRegister_BattleAttackArmy,pProvDefender);
      [*] = ;   CheckHumanPlayer(gIntRegister_BattleDefendPlayer, gIntRegister_BattleAttackPlayer, gIntRegister_BattleDefendArmy,pProvDefender);
      [*] = ;end
      [*] = ;else
      [*] = ;   gBoolRegister_IsDefenderBattle := true;
      [*] = ;
      [*] = ;if gBoolRegister_IsHumanPlayer then
      [*] = ;   gBoolRegister_IsDefenderBattle := false;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+BoolToStr(gBoolRegister_IsHumanPlayer)+']',$1000000 or _log_trace);
   struct.end
section.end

