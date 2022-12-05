section.begin
   Name = map.LanCheckEndTurn
   Code : struct.begin
      [*] = ;if (gGame.gameType = gc_GameTypeLanShard) and (_lan_stimer_Status(gc_lt_map_end_turn) = gc_lan_timer_status_released) then
      [*] = ;begin
      [*] = ;   var _log_name : String = 'COMMON.INC\MAP\MAP.LANCHECKENDTURN';
      [*] = ;   var _log_trace : Integer = $20001;
      [*] = ;   _gv_traceState(_log_name,_log_trace);
      [*] = ;   _lan_stimer_Reset(gc_lt_map_end_turn,false);
      [*] = ;   //if finished then
      [*] = ;   //if _lan_stimer_Status(gc_lt_map_end_turn) then
      [*] = ;   if (GetLanMode() >= 2) then
      [*] = ;   begin
      [*] = ;      var pMachineParser : Integer = ParserSelectStateMachineByHandle(GetMapInitMachineHandle());
      [*] = ;      var pSyncInfo : Integer = ParserSelectByHandleByKey(pMachineParser, 'SyncInfo');
      [*] = ;      var randKey0, randKey1, p : Integer;
      [*] = ;
      [*] = ;      _gv_SetMapLock($10000,_log_name);
      [*] = ;      //GetMapGeneratorRandomKey(randKey0, randKey1);
      [*] = ;      GetRandomExtKey64(randKey0, randKey1);
      [*] = ;      ParserSetIntValueByKeyByHandle(pSyncInfo, 'RandKey0', randKey0);
      [*] = ;      ParserSetIntValueByKeyByHandle(pSyncInfo, 'RandKey1', randKey1);
      [*] = ;      ParserSetIntValueByKeyByHandle(pSyncInfo, 'SaveMapKey', gIntRegister_LanMapUID);
      [*] = ;      ParserSetValueByKeyByHandle(pSyncInfo, 'SaveMapName', gStringRegister_LanMapSaveName);
      [*] = ;
      [*] = ;      _inet_LanSendParserExt(gc_LAN_SHARD_CALCTURN, pSyncInfo);
      [*] = ;
      [*] = ;      p := ParserSelectByHandleByKey(pSyncInfo, 'Players');
      [*] = ;      ParserClearByHandle(p);
      [*] = ;      p := ParserSelectByHandleByKey(pSyncInfo, 'Game');
      [*] = ;      ParserClearByHandle(p);
      [*] = ;   end;
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;end;
   struct.end
section.end

