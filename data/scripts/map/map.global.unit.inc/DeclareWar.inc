section.begin
   Name = DeclareWar
   Description[*] = ;IntRegister0 - player index
   Code : struct.begin
      [*] = ;var plIndex : Integer = IntRegister0;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;
      [*] = ;procedure SendAnnouncement(plHnd : Integer);
      [*] = ;begin
      [*] = ;   var pQuery : Integer = ParserAddChildByIndex(ParserSelectByHandleByKey(ParserSelectPlayer(plHnd), 'Queries'), '*');
      [*] = ;   ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', gc_gui_query_diplNewWar);
      [*] = ;   ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex', plIndex);
      [*] = ;   ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex1', myPlIndex);
      [*] = ;   ParserSetBoolValueByKeyByHandle(pQuery, 'Diplomacy', true);
      [*] = ;   ParserSetBoolValueByKeyByHandle(pQuery, 'Informative', true);
      [*] = ;end;
      [*] = ;         
      [*] = ;// Send announcement to other players who know the players in question.
      [*] = ;if (gGame.gameType = gc_GameTypeHotseat) then
      [*] = ;begin
      [*] = ;   var i, plHnd : Integer;
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;   if (i <> myPlIndex) and (i <> plIndex) then
      [*] = ;   begin
      [*] = ;      plHnd := GetPlayerHandleByIndex(i);
      [*] = ;      if _plr_IsInGame(plHnd) and SameText(GetPlayerControlModeByHandle(plHnd), 'cmPlayer') and (gArrDiplomacy[i][plIndex].treaty > 0) and (gArrDiplomacy[i][myPlIndex].treaty > 0) then
      [*] = ;         SendAnnouncement(plHnd);
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;if (gIntRegister_MapMyPlayerIndex <> plIndex) and (gIntRegister_MapMyPlayerIndex <> myPlIndex) and (gArrDiplomacy[gIntRegister_MapMyPlayerIndex][plIndex].treaty > 0) and (gArrDiplomacy[gIntRegister_MapMyPlayerIndex][myPlIndex].treaty > 0) then
      [*] = ;   SendAnnouncement(GetPlayerHandleByIndex(gIntRegister_MapMyPlayerIndex));
      [*] = ;      
      [*] = ;
      [*] = ;gArrDiplomacy[myPlIndex][plIndex].treaty := gc_TreatyWar;
      [*] = ;_diplomacy_ClearTrade(gArrDiplomacy[myPlIndex][plIndex].trade);
      [*] = ;
      [*] = ;gArrDiplomacy[myPlIndex][plIndex].arrTalk[gc_TreatyWar][1] := gGame.currentTurn;
      [*] = ;
      [*] = ;gArrDiplomacy[plIndex][myPlIndex].treaty := gc_TreatyWar;
      [*] = ;_diplomacy_ClearTrade(gArrDiplomacy[plIndex][myPlIndex].trade);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

