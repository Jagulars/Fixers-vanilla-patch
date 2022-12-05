section.begin
   Name = DeleteUnionPeaceOffers
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\DELETEUNIONPEACEOFFERS';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var proposePlInd : Integer = IntRegister0;
      [*] = ;var answerPlInd : Integer = IntRegister1;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[MyIndex: '+IntToStr(myPlIndex)+', ProposePlayer: '+IntToStr(proposePlInd)+', AnswerPlayer: '+IntToStr(answerPlInd)+']',_log_trace);
      [*] = ;   
      [*] = ;procedure DeleteMessages(plIndex, plIndex2 : Integer);
      [*] = ;begin
      [*] = ;   _diplomacy_Escrow(plIndex, plIndex2, false);
      [*] = ;   _diplomacy_Escrow(plIndex2, plIndex, false);
      [*] = ;   _diplomacy_ClearMessage(gArrDiplomacy[plIndex][plIndex2].message);
      [*] = ;   _diplomacy_ClearMessage(gArrDiplomacy[plIndex2][plIndex].message);
      [*] = ;end;
      [*] = ;   
      [*] = ;DeleteMessages(proposePlInd, answerPlInd);
      [*] = ;      
      [*] = ;var i : Integer;
      [*] = ;var ally1, ally2 : Integer = -1;
      [*] = ;for i := 0 to gGame.map.players-1 do
      [*] = ;if (i <> proposePlInd) and (i <> answerPlInd) then
      [*] = ;begin
      [*] = ;   if (gArrDiplomacy[answerPlInd][i].treaty = gc_TreatyUnion) then
      [*] = ;   begin
      [*] = ;      ally1 := i;
      [*] = ;      DeleteMessages(proposePlInd, i);
      [*] = ;      if (i <> myPlIndex) then
      [*] = ;         DeleteMessages(myPlIndex, i);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (gArrDiplomacy[proposePlInd][i].treaty = gc_TreatyUnion) then
      [*] = ;   begin
      [*] = ;      ally2 := i;
      [*] = ;      DeleteMessages(answerPlInd, i);
      [*] = ;      if (i <> myPlIndex) then
      [*] = ;         DeleteMessages(myPlIndex, i);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (ally1 >= 0) and (ally2 >= 0) then
      [*] = ;   DeleteMessages(ally1, ally2);
      [*] = ;
      [*] = ;// send a breakdown of the situation to all involved human players
      [*] = ;for i := 0 to gGame.map.players-1 do
      [*] = ;begin
      [*] = ;   var plHnd : Integer = GetPlayerHandleByIndex(i);
      [*] = ;   if (i = proposePlInd) or (i = answerPlInd) or (i = ally1) or (i = ally2) and (((gGame.gameType = gc_GameTypeHotseat) or (i = gIntRegister_MapMyPlayerIndex)) and _plr_IsInGame(plHnd) and SameText(GetPlayerControlModeByHandle(plHnd), 'cmPlayer')) then
      [*] = ;   begin
      [*] = ;      var pQuery : Integer = ParserAddChildByIndex(ParserSelectByHandleByKey(ParserSelectPlayer(plHnd), 'Queries'), '*');
      [*] = ;      ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', gc_gui_query_diplWarContinues);
      [*] = ;      ParserSetBoolValueByKeyByHandle(pQuery, 'Diplomacy', true);
      [*] = ;      ParserSetBoolValueByKeyByHandle(pQuery, 'Informative', true);
      [*] = ;      ParserSetValueByKeyByHandle(pQuery, 'gStringRegister_PlayersList', gStringRegister_PlayersList); // from CheckUnionPeaceOffer
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

