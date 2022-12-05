section.begin
   Name = map.BeforeEndTurn
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\MAP\MAP.BEFOREENDTURN';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;if gGame.gameType <> gc_GameTypeLanShard then
      [*] = ;begin
      [*] = ;   if (gProfile.autosave > 0) and (gGame.currentturn mod gProfile.autosave = 0) then
      [*] = ;   begin
      [*] = ;      StringRegister0 := 'map';
      [*] = ;      BoolRegister0 := True;
      [*] = ;      IntRegister0 := 0;
      [*] = ;      ExecuteState('SaveMap');
      [*] = ;   end;
      [*] = ;
      [*] = ;   SetPlayerIntValueIndByHandle(GetPlayerHandleInterfaceIO(), gc_map_PLStack_MapUnit_iSelectedUID, gIntRegister_MapSelectedUID);
      [*] = ;   SetPlayerBoolValueIndByHandle(GetPlayerHandleInterfaceIO(), gc_map_PLStack_MapUnit_bTurnFinished, true);
      [*] = ;
      [*] = ;   ExecuteState('map.CheckNextPlayer');
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   var p : Integer;
      [*] = ;
      [*] = ;   SetPlayerIntValueIndByHandle(GetPlayerHandleInterfaceIO(), gc_map_PLStack_MapUnit_iSelectedUID, gIntRegister_MapSelectedUID);
      [*] = ;   SetPlayerBoolValueIndByHandle(GetPlayerHandleInterfaceIO(), gc_map_PLStack_MapUnit_bTurnFinished, true);
      [*] = ;
      [*] = ;   _gv_SetMapLock($10001,_log_name);
      [*] = ;
      [*] = ;   if GetLanMode() > 1 then // host
      [*] = ;   begin
      [*] = ;      p := ParserSelectByHandleByKey(ParserSelectStateMachineByHandle(GetMapInitMachineHandle()), 'SyncInfo');
      [*] = ;      p := ParserAddChildByIndex(ParserSelectByHandleByKey(p, 'Players'), '*');
      [*] = ;
      [*] = ;      IntRegister0 := p;
      [*] = ;      IntRegister1 := 1;
      [*] = ;      PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO(), 'SaveInfoToParser');
      [*] = ;
      [*] = ;      if (gProfile.autosave > 0) and (gGame.currentturn mod gProfile.autosave = 0) and (gStringRegister_LanMapSaveName = '') then
      [*] = ;         gStringRegister_LanMapSaveName := 'map'
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      p := _misc_ParserGetOrCreateByKey('map_bet_EndTurn',true);
      [*] = ;
      [*] = ;      IntRegister0 := p;
      [*] = ;      IntRegister1 := 1;
      [*] = ;      PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO(), 'SaveInfoToParser');
      [*] = ;
      [*] = ;      _lan_LanSendParserToServer(gc_LAN_SHARD_ENDTURN, p);
      [*] = ;   end;
      [*] = ;
      [*] = ;   _lan_stimer_Start(gc_lt_map_end_turn,false);
      [*] = ;   ExecuteState('map.LanCheckEndTurn');
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

