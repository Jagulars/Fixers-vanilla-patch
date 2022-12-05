section.begin
   Name = DiplomacyFirstMeet
   Code : struct.begin
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;//Log('Execute diplomacy for ' + myPlName);
      [*] = ;
      [*] = ;if (not _misc_IsMapLocked) and (gIntRegister_MapTurnIteration = 3) and (myIndex = _gv_GetCurrentPlayer()) then
      [*] = ;begin
      [*] = ;   var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;   var i, j : Integer;
      [*] = ;   var pMyParser : Integer = ParserSelectPlayer(myPlHandle);
      [*] = ;   var pQueries : Integer = ParserSelectByHandleByKey(pMyParser, 'Queries');
      [*] = ;   var myPlName : String = GetCurrentPlayerName;
      [*] = ;   var myCMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;   var myLord : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iLordIndex);
      [*] = ;   
      [*] = ;   //Проверка почты союзников (для игрока-человека)
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;   if (i <> myIndex) and (gArrDiplomacy[i][myIndex].treaty = 0) then
      [*] = ;   begin
      [*] = ;      var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;      var plName : String = GetPlayerNameByHandle(plHandle);
      [*] = ;      var cMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;      if _plr_IsInGame(plHandle) then
      [*] = ;      begin
      [*] = ;         var meet : Boolean = false;
      [*] = ;         if not gGame.fog then
      [*] = ;            meet := true
      [*] = ;         else
      [*] = ;         for j := ParserGetCountByHandle(pProvinces)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, j);
      [*] = ;            var pProvFog : Integer = ParserSelectByHandleByKey(pProvince, 'Fog');
      [*] = ;            var plFog : Integer = ParserGetIntValueByIndexByHandle(pProvFog, i);
      [*] = ;            var myFog : Integer = ParserGetIntValueByIndexByHandle(pProvFog, myIndex);
      [*] = ;
      [*] = ;            var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;            if (SameText(provPlName, myPlName) and (plFog < 2)) or (SameText(provPlName, plName) and (myFog < 2)) then
      [*] = ;            begin
      [*] = ;               meet := true;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if meet then
      [*] = ;         begin
      [*] = ;            var plProfile : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;            var plLord : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iLordIndex);
      [*] = ;
      [*] = ;            if (not gGame.diplomacy) or (myLord > 0) or (plLord > 0) then // always war when no diplomacy allowed or one of the players is a local lord.
      [*] = ;            begin
      [*] = ;               if SameText(cMode, 'cmPC') then
      [*] = ;               begin
      [*] = ;                  gArrDiplomacy[myIndex][i].treaty := gc_TreatyWar;
      [*] = ;                  gArrDiplomacy[i][myIndex].treaty := gc_TreatyWar;
      [*] = ;
      [*] = ;                  if (gIntRegister_DiplomacyActivePlayerID=-1) then
      [*] = ;                     gIntRegister_DiplomacyActivePlayerID := i;
      [*] = ;
      [*] = ;                  if SameText(myCMode, 'cmPlayer') and gGame.diplomacy then
      [*] = ;                  begin
      [*] = ;                     var pQuery : Integer = ParserAddChildByIndex(pQueries, '*');
      [*] 
      [*] = ;                     if plProfile > 0 then
      [*] = ;                        ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', gc_gui_query_diplMeetOverlord)
      [*] = ;                     else
      [*] = ;                        ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', gc_gui_query_diplMeetLocalLord);
      [*] = ;
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex', i);
      [*] = ;                     ParserSetBoolValueByKeyByHandle(pQuery, 'Diplomacy', true);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (not gTutorial.map) then
      [*] = ;               begin
      [*] = ;                  var myProfile : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iProfile);
      [*] = ;                  if myProfile > 0 then
      [*] = ;                  begin
      [*] = ;                     var pProfile : Integer = ParserSelectByHandleByIndex(gPrototypeData.players.handle, myProfile);
      [*] = ;                     _diplomacy_ShuffleRandom(myIndex, i, ParserGetIntValueByKeyByHandle(pProfile, 'Random'));
      [*] = ;                  end;
      [*] = ;         
      [*] = ;                  gArrDiplomacy[myIndex][i].treaty := gc_TreatyPeace;
      [*] = ;                  gArrDiplomacy[myIndex][i].meet := gGame.currentTurn;
      [*] = ;                  gArrDiplomacy[i][myIndex].treaty := gc_TreatyPeace;
      [*] = ;                  gArrDiplomacy[i][myIndex].meet := gGame.currentTurn;
      [*] = ;
      [*] = ;                  if (gIntRegister_DiplomacyActivePlayerID=-1) then
      [*] = ;                     gIntRegister_DiplomacyActivePlayerID := i;
      [*] = ;
      [*] = ;                  var ind1 : Integer = -1;
      [*] = ;                  var ind2 : Integer = -1;
      [*] = ;                  if gGame.diplomacy and ((SameText(myCMode, 'cmPlayer') and SameText(cMode, 'cmPC')) or
      [*] = ;                  (SameText(myCMode, 'cmPC') and SameText(cMode, 'cmPlayer'))) then
      [*] = ;                  begin
      [*] = ;                     if SameText(myCMode, 'cmPlayer') then
      [*] = ;                     begin
      [*] = ;                        IntRegister0 := myIndex;
      [*] = ;                        PlayerExecuteStateByHandle(plHandle, 'SendGreetings');
      [*] = ;                        ind1 := i;
      [*] = ;                        ind2 := myIndex;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        IntRegister0 := i;
      [*] = ;                        ExecuteState('SendGreetings');
      [*] = ;                        ind1 := myIndex;
      [*] = ;                        ind2 := i;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if ind2 >= 0 then
      [*] = ;                  begin
      [*] = ;                     var plHandle : Integer = GetPlayerHandleByIndex(ind2);
      [*] = ;                     var pPlParser : Integer = ParserSelectPlayer(plHandle);
      [*] = ;                     var pPlQueries : Integer = ParserSelectByHandleByKey(pPlParser, 'Queries');
      [*] = ;
      [*] = ;                     var pPlQuery : Integer = ParserAddChildByIndex(pPlQueries, '*');
      [*] = ;                     var text : String = gArrDiplomacy[ind1][ind2].message.text;
      [*] = ;
      [*] = ;                     ParserSetValueByKeyByHandle(pPlQuery, 'QueryID', text);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pPlQuery, 'PlayerIndex', ind1);
      [*] = ;                  end;
      [*] = ;               end;
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

