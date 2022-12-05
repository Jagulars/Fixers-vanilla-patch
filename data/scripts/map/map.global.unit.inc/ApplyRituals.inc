section.begin
   Name = ApplyRituals
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\APPLYRITUALS';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;var myPlName : String = GetCurrentPlayerName();
      [*] = ;var myIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(myIndex)+']',_log_trace);
      [*] = ;if (not _misc_IsMapLocked()) and (gIntRegister_MapTurnIteration = 0) and (myIndex = _gv_GetCurrentPlayer()) then
      [*] = ;begin
      [*] = ;   var plProvHandle : Integer = _map_GetProvincesPlayer();
      [*] = ;
      [*] = ;   var provCount : Integer = GetPlayerGameObjectsCountByHandle(plProvHandle);
      [*] = ;   var ind : Integer = 0;
      [*] = ;
      [*] = ;   if (gIntRegister_CurQueryHandle = 0) and (gIntRegister_CurProvinceIndex < provCount) then
      [*] = ;   begin
      [*] = ;      ind := -1;
      [*] = ;      for i := gIntRegister_CurProvinceIndex to provCount-1 do
      [*] = ;      begin
      [*] = ;         var provHandle : Integer = GetGameObjectHandleByIndex(i, plProvHandle);
      [*] = ;         var pProvHandle : Integer = GetGameObjectIntValueIndByHandle(provHandle, gc_map_GOStack_Province_iParserHandle);
      [*] = ;         var provPlayer : String = ParserGetValueByKeyByHandle(pProvHandle, 'Player');
      [*] = ;         var pCastedRituals : Integer = ParserSelectByHandleByKey(pProvHandle, 'CastedRituals');
      [*] = ;         var castedCount : Integer = ParserGetCountByHandle(pCastedRituals);
      [*] = ;
      [*] = ;         if SameText(provPlayer, myPlName) and (castedCount > 0) then
      [*] = ;         begin
      [*] = ;            ind := i;
      [*] = ;            gIntRegister_CurrentEventID := 0;
      [*] = ;            gIntRegister_CurProvinceIndex := i;
      [*] = ;            GameObjectExecuteStateByHandle(provHandle, 'ApplyCastedRituals');
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if ind = -1 then
      [*] = ;   begin
      [*] = ;      // switch to next iteration state
      [*] = ;      gIntRegister_MapTurnIteration := gIntRegister_MapTurnIteration + 1;
      [*] = ;      gIntRegister_MapCurHeroIndex := -1;
      [*] = ;      gIntRegister_CurProvinceIndex := -1;
      [*] = ;      gIntRegister_CurrentEncounterID := 0;
      [*] = ;      gIntRegister_CurrentEventID := 0;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

