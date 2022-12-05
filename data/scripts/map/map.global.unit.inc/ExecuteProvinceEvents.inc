section.begin
   Name = ExecuteProvinceEvents
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\EXECUTEPROVINCEEVENTS';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlName : String = GetCurrentPlayerName;
      [*] = ;var myIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;
      [*] = ;if (not _misc_IsMapLocked()) and (gIntRegister_MapTurnIteration = 9) and (myIndex = _gv_GetCurrentPlayer()) then
      [*] = ;begin
      [*] = ;   var pMyPlayer : Integer = ParserSelectPlayer(myPlHandle);
      [*] = ;   var pEventItems : Integer = ParserSelectByHandleByKey(pMyPlayer, 'EventItems');
      [*] = ;   if (ParserGetCountByHandle(pEventItems)>0) then
      [*] = ;      ParserClearByHandle(pEventItems);
      [*] = ;
      [*] = ;   var plProvHandle : Integer = _map_GetProvincesPlayer();
      [*] = ;
      [*] = ;   var provCount : Integer = GetPlayerGameObjectsCountByHandle(plProvHandle);
      [*] = ;   var ind : Integer = -1;
      [*] = ;
      [*] = ;   if (gGame.currentTurn > 3) and (not gTutorial.map) and (gIntRegister_CurProvinceIndex < provCount) then
      [*] = ;   begin
      [*] = ;      for i := gIntRegister_CurProvinceIndex+1 to provCount-1 do
      [*] = ;      begin
      [*] = ;         var provHandle : Integer = GetGameObjectHandleByIndex(i, plProvHandle);
      [*] = ;         var pProvince : Integer = GetGameObjectIntValueIndByHandle(provHandle, gc_map_GOStack_Province_iParserHandle);
      [*] = ;         var provPlayer : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;         if SameText(provPlayer, myPlName) then
      [*] = ;         begin
      [*] = ;            var chance : Float = RandomExt;
      [*] = ;            if SameText(cMode, 'cmPlayer') then _log_Map('Event Roll: '+FloatToStr(chance));
      [*] = ;            if (chance < gc_map_ProvinceEventFreq / 100) then
      [*] = ;            begin
      [*] = ;               if SameText(cMode, 'cmPlayer') then
      [*] = ;               begin
      [*] = ;                  ind := i;
      [*] = ;                  gIntRegister_CurProvinceIndex := i;
      [*] = ;                  
      [*] = ;                  GameObjectExecuteStateByHandle(provHandle, 'IsUnderSiege');
      [*] = ;                  var bSiege : Boolean = BoolRegister0;
      [*] = ;                  var bCastle : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;                  _log_Map('bSiege '+BoolToStr(bSiege));
      [*] = ;                  _log_Map('bCastle '+BoolToStr(bCastle));
      [*] = ;                  if (not bSiege) and (not bCastle) then
      [*] = ;                     GameObjectExecuteStateByHandle(provHandle, 'CreateEvent');
      [*] = ;               
      [*] = ;                  break;
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  GameObjectExecuteStateByHandle(provHandle, 'CreateAIEvent');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if ind = -1 then
      [*] = ;   begin
      [*] = ;      // switch to next iteration state
      [*] = ;      if _plr_IsInGame(myPlHandle) then
      [*] = ;      begin
      [*] = ;         gIntRegister_MapTurnIteration := gIntRegister_MapTurnIteration + 1;
      [*] = ;         gIntRegister_CurProvinceIndex := -1;
      [*] = ;         gIntRegister_CurrentEventID := 0;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         MapExecuteState('map.CheckNextPlayer');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

