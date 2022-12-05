section.begin
   Name = DiplomacyWrongMessages
   Code : struct.begin
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlName : String = GetCurrentPlayerName;
      [*] = ;var myIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var pMyParser : Integer = ParserSelectPlayer(myPlHandle);
      [*] = ;var pQueries : Integer = ParserSelectByHandleByKey(pMyParser, 'Queries');
      [*] = ;
      [*] = ;var myCMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;//var myProfile : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iProfile);
      [*] = ;//var myLord : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iLordIndex);
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;
      [*] = ;//Log('Execute diplomacy for ' + myPlName);
      [*] = ;
      [*] = ;if (not _misc_IsMapLocked) and (gIntRegister_MapTurnIteration = 2) and (myIndex = _gv_GetCurrentPlayer()) then
      [*] = ;begin
      [*] = ;   //Проверка почты союзников (для игрока-человека) // check if proposal cannot be fulfilled
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;   if i <> myIndex then
      [*] = ;   begin
      [*] = ;      var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;      if _plr_IsInGame(plHandle)then
      [*] = ;      begin
      [*] = ;         if _diplomacy_IsMessageValid(i, myIndex, gArrDiplomacy[i][myIndex].message) then
      [*] = ;         begin
      [*] = ;            var cMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;            if SameText(myCMode, 'cmPC') or SameText(cMode, 'cmPC') then // always display offers when it's human to human.
      [*] = ;            begin
      [*] = ;               IntRegister0 := myIndex;
      [*] = ;               PlayerExecuteStateByHandle(plHandle, 'CheckMessage'); // do I meet requirements?
      [*] = ;               if (not BoolRegister0) then
      [*] = ;               begin
      [*] = ;                  if _diplomacy_IsProposal(gArrDiplomacy[i][myIndex].message) then
      [*] = ;                     gArrDiplomacy[myIndex][i].answer := -2 // use a refusal as an answer when requirements cannot be fulfilled so it is impossible to figure out the resources of the other player by testing with different proposals.
      [*] = ;                  else
      [*] = ;                     gArrDiplomacy[myIndex][i].answer := 0;
      [*] = ;                  {var pQuery : Integer = ParserAddChildByIndex(pQueries, '*');
      [*] = ;                  ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', gc_gui_query_diplCancelMessage);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex', i);
      [*] = ;                  ParserSetBoolValueByKeyByHandle(pQuery, 'Diplomacy', true);}
      [*] = ;
      [*] = ;                  IntRegister0 := i;
      [*] = ;                  ExecuteState('CancelDeal');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else // cold removal
      [*] = ;         begin
      [*] = ;            _diplomacy_Escrow(i, myIndex, false);
      [*] = ;            _diplomacy_ClearMessage(gArrDiplomacy[i][myIndex].message);
      [*] = ;
      [*] = ;            if SameText(myCMode, 'cmPlayer') then // from AI to player - can't fulfill requirements - don't notice me - delete AI message query
      [*] = ;            begin
      [*] = ;               for j := ParserGetCountByHandle(pQueries)-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  var pQuery : Integer = ParserSelectByHandleByIndex(pQueries, j);
      [*] = ;                  var query : String = ParserGetValueByKeyByHandle(pQuery, 'QueryID');
      [*] = ;                  var plIndex : Integer = _pars_ParserGetIntValueExt(pQuery, 'PlayerIndex');
      [*] = ;                  var diplomacy : Boolean = ParserGetBoolValueByKeyByHandle(pQuery, 'Diplomacy');
      [*] = ;                  var informative : Boolean = ParserGetBoolValueByKeyByHandle(pQuery, 'Informative');
      [*] = ;
      [*] = ;                  if diplomacy and (not informative) and (plIndex = i) then
      [*] = ;                     ParserFreeByHandle(pQuery);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // switch to next iteration state
      [*] = ;   gIntRegister_MapTurnIteration := gIntRegister_MapTurnIteration + 1;
      [*] = ;   gIntRegister_CurEventTimerIndex := -1;
      [*] = ;   gIntRegister_CurrentEventID := 0;
      [*] = ;   gIntRegister_CurrentEncounterID := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

