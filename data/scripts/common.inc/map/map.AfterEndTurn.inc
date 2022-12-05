section.begin
   Name = map.AfterEndTurn
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\MAP\MAP.AFTERENDTURN';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerHandleByIndex(gIntRegister_MapMyPlayerIndex);
      [*] = ;
      [*] = ;if gGame.gameType = gc_GameTypeLanShard then
      [*] = ;   _lan_timer_Reset(gc_lt_conflicts,true,'COMMON.INC\MAP\MAP.AFTERENDTURN');
      [*] = ;
      [*] = ;if (gGame.gameType <> gc_GameTypeLanShard) or _plr_IsInGame(myPlHandle) then
      [*] = ;begin
      [*] = ;   // setup update player info for lan shard game
      [*] = ;   var i, j, up : Integer;
      [*] = ;   var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;   for i := ParserGetCountByHandle(pProvinces)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, i);
      [*] = ;      var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;
      [*] = ;      if _misc_IsProvinceNeutral(pProvince) then
      [*] = ;      begin
      [*] = ;         var lastPlayer : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'LastPlayer');
      [*] = ;         if lastPlayer >= 0 then
      [*] = ;            provPlName := GetPlayerNameByIndex(lastPlayer);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (provPlName <> '') then
      [*] = ;         up := GetPlayerIndexByHandle(GetPlayerHandleByName(provPlName))
      [*] = ;      else
      [*] = ;         up := -1;
      [*] = ;      ParserSetIntValueByKeyByHandle(pProvince, 'UpdatePlayer', up);
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;   begin
      [*] = ;      var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;      var goCount : Integer = GetPlayerGameObjectsCountByHandle(plHandle);
      [*] = ;      for j := 0 to goCount-1 do
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;         if not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bBuried) then
      [*] = ;         begin
      [*] = ;            var pProvince : Integer = _misc_GetProvinceParserByUID(GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID));
      [*] = ;
      [*] = ;            if GetPlayerHandleByName(ParserGetValueByKeyByHandle(pProvince, 'Player')) = 0 then
      [*] = ;               ParserSetIntValueByKeyByHandle(pProvince, 'UpdatePlayer', i);
      [*] = ;
      [*] = ;            pProvince := _misc_GetProvinceParserByUID(GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iReachUID));
      [*] = ;            ParserSetIntValueByKeyByHandle(pProvince, 'UpdatePlayer', i);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   ExecuteState('map.ProcessAIPlayers');
      [*] = ;end;
      [*] = ;
      [*] = ;//var profManager : Integer = EditorProfManagerGetProfilerHandleByName('WholeTurn');
      [*] = ;//EditorProfilerEnd(profManager);
      [*] = ;//EditorProfManagerStop;
      [*] = ;//EditorProfManagerShowReport;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

