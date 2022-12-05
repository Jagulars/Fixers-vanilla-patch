section.begin
   Name = CheckFearVictory
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\GLOBAL.INC\CHECKFEARVICTORY';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;var aMod : Integer = GetIntValueByIndex(gc_battle_PLStack_iAttackMode);
      [*] = ;
      [*] = ;var autoBattle : Boolean = GetPlayerBoolValueIndByHandle(GetPlayerHandleInterfaceIO, gc_battle_PLStack_bAutoBattle);
      [*] = ;var scared : Boolean = false;
      [*] = ;
      [*] = ;if (not GetBoolValueByIndex(gc_battle_PLStack_bInPanic)) and (not _misc_IsLanBattle) then // workaround: never give option to chase/let flee in lan battles. Would cause turn not passing correctly.
      [*] = ;begin
      [*] = ;   ExecuteState('IsArmyScared');
      [*] = ;   scared := BoolRegister0;
      [*] = ;end;
      [*] = ;
      [*] = ;if _log then _Log_Map(+_log_name+' Scared: '+BoolToStr(scared));
      [*] = ;
      [*] = ;if scared then
      [*] = ;begin
      [*] = ;   SetBoolValueByIndex(gc_battle_PLStack_bInPanic, true);
      [*] = ;
      [*] = ;   if gBoolRegister_IsHumanPlayer and (not autoBattle) and (not gBoolRegister_QuickBattle) then
      [*] = ;   begin
      [*] = ;      if ((aMod = 0) and (GetPlayerIndexByHandle(gIntRegister_BattleAttackPlayer) = gIntRegister_MapMyPlayerIndex)) or
      [*] = ;      ((aMod = 1) and (GetPlayerIndexByHandle(gIntRegister_BattleDefendPlayer) = gIntRegister_MapMyPlayerIndex)) then
      [*] = ;      begin
      [*] = ;         StringRegister0 := IntToStr(gc_gui_query_battleFearVictory);
      [*] = ;         GUIExecuteState('map.RequestQueryWindow');
      [*] = ;      end
      [*] = ;      else
      [*] = ;         MapExecuteState('bat.DoFinishBattle');
      [*] = ;   end
      [*] = ;   else
      [*] = ;      MapExecuteState('bat.DoFinishBattle');
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   BoolRegister0 := true;
      [*] = ;   ExecuteState('BeforeTurn');
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+' Scared: '+BoolToStr(scared),$1000000 or _log_trace);
      [*] = ;
      [*] = ;BoolRegister0 := scared;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

