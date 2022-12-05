section.begin
   Name = CompletePlayerTurn
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\COMPLETEPLAYERTURN';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;var myPlName : String = GetCurrentPlayerName();
      [*] = ;var myIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;
      [*] = ;if (not _misc_IsMapLocked()) and (gIntRegister_MapTurnIteration = 14) and (myIndex = _gv_GetCurrentPlayer()) then
      [*] = ;begin
      [*] = ;   var inGame : Boolean;
      [*] = ;
      [*] = ;   ExecuteState('IsInGame');
      [*] = ;   inGame := BoolRegister0;
      [*] = ;
      [*] = ;   if SameText(cMode, 'cmPC') then
      [*] = ;   begin
      [*] = ;      var index : Integer = -1;
      [*] = ;      var i,cp_idx : Integer;
      [*] = ;
      [*] = ;      if inGame then
      [*] = ;      begin
      [*] = ;         ExecuteState('MakeTurn');
      [*] = ;         ExecuteState('AfterEndTurn');
      [*] = ;      end;
      [*] = ;
      [*] = ;      cp_idx := _gv_GetCurrentPlayer();
      [*] = ;      for i := cp_idx+1 to gGame.map.players-1 do
      [*] = ;      begin
      [*] = ;         var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;         var cMode1 : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;
      [*] = ;         if _plr_IsInGame(plHandle) and SameText(cMode1, 'cmPC') then
      [*] = ;         begin
      [*] = ;            index := i;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if index > -1 then
      [*] = ;      begin
      [*] = ;         _gv_SetCurrentPlayer(index,_log_name);
      [*] = ;         gIntRegister_MapTurnIteration := 0;
      [*] = ;         gIntRegister_MapCurHeroIndex := -1;
      [*] = ;         BoolRegister0 := false;
      [*] = ;         GUIExecuteState('map.ShowWhosTurn');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         // switch to next iteration state
      [*] = ;         gIntRegister_MapTurnIteration := gIntRegister_MapTurnIteration + 1;
      [*] = ;         _gv_SetCurrentPlayer(0,_log_name);
      [*] = ;         gIntRegister_MapCurHeroIndex := -1;
      [*] = ;         MapExecuteState('map.StartHumanTurn');
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      gIntRegister_MapTurnIteration := gIntRegister_MapTurnIteration + 1;
      [*] = ;      _gv_SetCurrentPlayer(-1,_log_name);
      [*] = ;      gIntRegister_MapCurHeroIndex := -1;
      [*] = ;      _gv_SetMapLock($10000,_log_name);
      [*] = ;
      [*] = ;      if inGame then
      [*] = ;      begin
      [*] = ;         ExecuteState('AfterEndTurn');
      [*] = ;      
      [*] = ;         if (gIntRegister_DebugAutopassTurns > 0) and (gGame.currentTurn mod gIntRegister_DebugAutopassTurns <> 0) then
      [*] = ;         begin
      [*] = ;            _cmd_Post('mapnextturn','','');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end
