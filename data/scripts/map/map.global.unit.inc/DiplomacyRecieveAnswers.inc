section.begin
   Name = DiplomacyRecieveAnswers
   Code : struct.begin
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;//var myPlName : String = GetCurrentPlayerName;
      [*] = ;var myIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;
      [*] = ;//var myProfile : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iProfile);
      [*] = ;//var myLord : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iLordIndex);
      [*] = ;
      [*] = ;//var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;
      [*] = ;//Log('Execute diplomacy for ' + myPlName);
      [*] = ;
      [*] = ;if (not _misc_IsMapLocked) and (gIntRegister_MapTurnIteration = 5) and (myIndex = _gv_GetCurrentPlayer()) then
      [*] = ;begin
      [*] = ;   //Проверка почты союзников (для игрока-человека) Check mail (for human player)
      [*] = ;   var myCMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;   if SameText(myCMode, 'cmPlayer') then
      [*] = ;   begin
      [*] = ;      var i : Integer;
      [*] = ;      var pMyParser : Integer = ParserSelectPlayer(myPlHandle);
      [*] = ;      var pQueries : Integer = ParserSelectByHandleByKey(pMyParser, 'Queries');
      [*] = ;      
      [*] = ;      for i := 0 to gGame.map.players-1 do
      [*] = ;      if i <> myIndex then
      [*] = ;      begin
      [*] = ;         var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;         if _plr_IsInGame(plHandle) then
      [*] = ;         begin
      [*] = ;            //Получение ответа на сообщение
      [*] = ;            // for Human - answer from PC
      [*] = ;            if (gArrDiplomacy[i][myIndex].answer <> 0) and ((gGame.gameType <> gc_GameTypeLanShard) or SameText(GetPlayerControlModeByHandle(plHandle), 'cmPC') or ((gArrDiplomacy[i][myIndex].displayPriority and $ff00) > 0)) then 
      [*] = ;            begin
      [*] = ;               IntRegister0 := myIndex;
      [*] = ;               PlayerExecuteStateByHandle(plHandle, 'SendAnswer');
      [*] = ;
      [*] = ;               var queryID : String = gArrDiplomacy[i][myIndex].message.text;
      [*] = ;               if queryID <> '' then
      [*] = ;               begin
      [*] = ;                  var pQuery : Integer = ParserAddChildByIndex(pQueries, '*');
      [*] = ;                  ParserSetBoolValueByKeyByHandle(pQuery, 'Priority', true);
      [*] = ;                  ParserSetValueByKeyByHandle(pQuery, 'QueryID', queryID);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex', i);
      [*] = ;                  ParserSetBoolValueByKeyByHandle(pQuery, 'Diplomacy', true);
      [*] = ;                  ParserSetBoolValueByKeyByHandle(pQuery, 'Informative', true);
      [*] = ;
      [*] = ;                  StringRegister0 := IntToStr(gc_gui_query_diplCancelMessage);
      [*] = ;                  IntRegister0 := i;
      [*] = ;                  ExecuteState('DeleteDiplQuery');
      [*] = ;               end;
      [*] = ;               gArrDiplomacy[i][myIndex].answer := 0;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // switch to next iteration state
      [*] = ;   gIntRegister_MapTurnIteration := gIntRegister_MapTurnIteration + 1;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

