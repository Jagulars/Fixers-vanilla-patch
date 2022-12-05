section.begin
   Name = ExecuteUnionPeace
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\EXECUTEUNIONPEACE';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var proposePlInd : Integer = IntRegister0;
      [*] = ;var answerPlInd : Integer = IntRegister1;
      [*] = ;
      [*] = ;var proposePlHandle : Integer = GetPlayerHandleByIndex(proposePlInd);
      [*] = ;var answerPlHandle : Integer = GetPlayerHandleByIndex(answerPlInd);
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[MyIndex: '+IntToStr(myPlIndex)+', ProposePlayer: '+IntToStr(proposePlInd)+', AnswerPlayer: '+IntToStr(answerPlInd)+']',_log_trace);
      [*] = ;
      [*] = ;procedure MakePeace(plInd1, plInd2 : Integer);
      [*] = ;begin
      [*] = ;   if (gArrDiplomacy[plInd1][plInd2].message.treaty = gc_TreatyPeace) and (gArrDiplomacy[plInd1][plInd2].message.deal > 0) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := plInd1;
      [*] = ;      PlayerExecuteStateByHandle(GetPlayerHandleByIndex(plInd2), 'AcceptDeal');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (gArrDiplomacy[plInd2][plInd1].message.treaty = gc_TreatyPeace) and (gArrDiplomacy[plInd2][plInd1].message.deal > 0) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := plInd2;
      [*] = ;      PlayerExecuteStateByHandle(GetPlayerHandleByIndex(plInd1), 'AcceptDeal');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      gArrDiplomacy[plInd1][plInd2].treaty := gc_TreatyPeace;
      [*] = ;      gArrDiplomacy[plInd2][plInd1].treaty := gc_TreatyPeace;
      [*] = ;      gArrDiplomacy[plInd1][plInd2].arrTalk[gc_TreatyPeace][0] := 1;
      [*] = ;      gArrDiplomacy[plInd2][plInd1].arrTalk[gc_TreatyPeace][0] := 1;
      [*] = ;      gArrDiplomacy[plInd1][plInd2].arrTalk[gc_TreatyPeace][1] := gGame.currentTurn;
      [*] = ;      gArrDiplomacy[plInd2][plInd1].arrTalk[gc_TreatyPeace][1] := gGame.currentTurn;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;      
      [*] = ;var ally1 : Integer = -1; // proposer ally
      [*] = ;var ally2 : Integer = -1; // answer ally
      [*] = ;var i : Integer;
      [*] = ;for i := 0 to gGame.map.players-1 do
      [*] = ;begin
      [*] = ;   if _plr_IsInGame(GetPlayerHandleByIndex(i)) then
      [*] = ;   begin
      [*] = ;      if (gArrDiplomacy[proposePlInd][i].treaty = gc_TreatyUnion) and (gArrDiplomacy[answerPlInd][i].treaty = gc_TreatyWar) then 
      [*] = ;         ally1 := i
      [*] = ;      else
      [*] = ;      if (gArrDiplomacy[answerPlInd][i].treaty = gc_TreatyUnion) and (gArrDiplomacy[proposePlInd][i].treaty = gc_TreatyWar) then 
      [*] = ;         ally2 := i;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// send peace signed announcement to all players who know at least two of the belligerents.
      [*] = ;for i := 0 to gGame.map.players-1 do
      [*] = ;begin
      [*] = ;   var plHnd : Integer = GetPlayerHandleByIndex(i);
      [*] = ;         
      [*] = ;   if ((gGame.gameType = gc_GameTypeHotseat) and _plr_IsInGame(plHnd) and SameText(GetPlayerControlModeByHandle(plHnd), 'cmPlayer')) or (i = gIntRegister_MapMyPlayerIndex) then
      [*] = ;   begin
      [*] = ;      var playersList : String = gc_gui_BreakLine;
      [*] = ;      var player1, player2 : Integer = -1;
      [*] = ;      var knownPlayers : Integer = 0;
      [*] = ;      if (i = proposePlInd) or (gArrDiplomacy[i][proposePlInd].treaty > 0) then
      [*] = ;      begin
      [*] = ;         player1 := proposePlInd;
      [*] = ;         knownPlayers := knownPlayers + 1;
      [*] = ;         PlayerExecuteStateByHandle(proposePlHandle, 'GetName');
      [*] = ;         playersList := playersList + gc_gui_BreakLine + StringRegister0;
      [*] = ;      end;
      [*] = ;      if (i = answerPlInd) or (gArrDiplomacy[i][answerPlInd].treaty > 0) then
      [*] = ;      begin
      [*] = ;         if player1 = -1 then player1 := answerPlInd
      [*] = ;         else player2 := answerPlInd;
      [*] = ;         knownPlayers := knownPlayers + 1;
      [*] = ;         PlayerExecuteStateByHandle(answerPlHandle, 'GetName');
      [*] = ;         playersList := playersList + gc_gui_BreakLine + StringRegister0;
      [*] = ;      end;
      [*] = ;      if (i = ally1) or (gArrDiplomacy[i][ally1].treaty > 0) then
      [*] = ;      begin
      [*] = ;         if player1 = -1 then player1 := ally1
      [*] = ;         else player2 := ally1;
      [*] = ;         knownPlayers := knownPlayers + 1;
      [*] = ;         PlayerExecuteStateByHandle(GetPlayerHandleByIndex(ally1), 'GetName');
      [*] = ;         playersList := playersList + gc_gui_BreakLine + StringRegister0;
      [*] = ;      end;
      [*] = ;      if (i = ally2) or (gArrDiplomacy[i][ally2].treaty > 0) then
      [*] = ;      begin
      [*] = ;         player2 := ally2;
      [*] = ;         knownPlayers := knownPlayers + 1;
      [*] = ;         PlayerExecuteStateByHandle(GetPlayerHandleByIndex(ally2), 'GetName');
      [*] = ;         playersList := playersList + gc_gui_BreakLine + StringRegister0;
      [*] = ;      end;
      [*] = ;      
      [*] = ;      if (knownPlayers > 2) or ((knownPlayers = 2) and (gArrDiplomacy[player1][player2].treaty = gc_TreatyWar)) then
      [*] = ;      begin
      [*] = ;         var pQuery : Integer = ParserAddChildByIndex(ParserSelectByHandleByKey(ParserSelectPlayer(plHnd), 'Queries'), '*');
      [*] = ;         ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', gc_gui_query_diplPeaceSigned);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pQuery, 'Diplomacy', true);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pQuery, 'Informative', true);
      [*] = ;         ParserSetValueByKeyByHandle(pQuery, 'gStringRegister_PlayersList', playersList);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;MakePeace(proposePlInd, answerPlInd);
      [*] = ;if (ally1 >= 0) then
      [*] = ;   MakePeace(answerPlInd, ally1);
      [*] = ;if (ally2 >= 0) then
      [*] = ;   MakePeace(proposePlInd, ally2);
      [*] = ;if (ally1 >= 0) and (ally2 >= 0) then 
      [*] = ;   MakePeace(ally1, ally2);
      [*] = ;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

