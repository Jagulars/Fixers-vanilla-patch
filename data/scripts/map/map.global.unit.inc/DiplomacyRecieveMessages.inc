section.begin
   Name = DiplomacyRecieveMessages
   Code : struct.begin
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;
      [*] = ;//Log('Execute diplomacy for ' + IntToStr(myPlIndex));
      [*] = ;
      [*] = ;if (not _misc_IsMapLocked) and (gIntRegister_MapTurnIteration = 4) and (myPlIndex = _gv_GetCurrentPlayer()) then
      [*] = ;begin
      [*] = ;   var pMyParser : Integer = ParserSelectPlayer(myPlHandle);
      [*] = ;   var pMyQueries : Integer = ParserSelectByHandleByKey(pMyParser, 'Queries');
      [*] = ;
      [*] = ;   var myCMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;   //var myProfile : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iProfile);
      [*] = ;   //var myLord : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iLordIndex);
      [*] = ;
      [*] = ;   var i, j : Integer;
      [*] = ;
      [*] = ;   //Получение сообщения
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;   if i <> myPlIndex then
      [*] = ;   begin
      [*] = ;      var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;      if _plr_IsInGame(plHandle) then
      [*] = ;      begin
      [*] = ;         //var plName : String = GetPlayerNameByHandle(plHandle);
      [*] = ;         var cMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;         
      [*] = ;         // lan shard human to human proposals are processed right at the end of turn
      [*] = ;         if (gArrDiplomacy[i][myPlIndex].message.mType > 0) and ((gArrDiplomacy[i][myPlIndex].message.deal = 0) or (gArrDiplomacy[i][myPlIndex].message.deal = 1)) // deal can 1 (=accepted) at this point if it's non-proposal
      [*] = ;         and ((gGame.gameType <> gc_GameTypeLanShard) or SameText(myCMode, 'cmPC') or (not _diplomacy_IsProposal(gArrDiplomacy[i][myPlIndex].message))) then
      [*] = ;         begin
      [*] = ;            if SameText(myCMode, 'cmPlayer') then
      [*] = ;            begin
      [*] = ;               if SameText(cMode, 'cmPlayer') then // query messages from AI to player are sent directly in MakeDiplomacy
      [*] = ;               begin
      [*] = ;                  IntRegister0 := myPlIndex;
      [*] = ;                  PlayerExecuteStateByHandle(plHandle, 'MakeHumanDiplomacyText');
      [*] = ;
      [*] = ;                  var queryID : String = gArrDiplomacy[i][myPlIndex].message.text;
      [*] = ;                  if queryID <> '' then
      [*] = ;                  begin
      [*] = ;                     var pMyQuery : Integer = ParserAddChildByIndex(pMyQueries, '*');
      [*] = ;                     ParserSetValueByKeyByHandle(pMyQuery, 'QueryID', queryID);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pMyQuery, 'PlayerIndex', i);
      [*] = ;                     ParserSetBoolValueByKeyByHandle(pMyQuery, 'Diplomacy', true);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else // AI reply to message
      [*] = ;            begin
      [*] = ;               if gArrDiplomacy[myPlIndex][i].answer = 0 then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := i;
      [*] = ;                  ExecuteState('GetDiploAnswerAI');
      [*] = ;                  gArrDiplomacy[myPlIndex][i].answer := IntRegister1;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   //Check if allies want peace with our enemy.
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;   if i <> myPlIndex then
      [*] = ;   begin
      [*] = ;      if (gArrDiplomacy[myPlIndex][i].treaty = gc_TreatyUnion) and _plr_IsInGame(GetPlayerHandleByIndex(i)) then
      [*] = ;      begin
      [*] = ;         var enemyPlInd : Integer;
      [*] = ;         for j := 0 to gGame.map.players-1 do
      [*] = ;         if (j <> myPlIndex) and (j <> i) and _plr_IsInGame(GetPlayerHandleByIndex(j)) then
      [*] = ;         begin
      [*] = ;            enemyPlInd := -1;
      [*] = ;            if (gArrDiplomacy[i][j].message.treaty = gc_TreatyPeace) or (gArrDiplomacy[j][i].message.treaty = gc_TreatyPeace) then
      [*] = ;               enemyPlInd := j;
      [*] = ;         
      [*] = ;            if (enemyPlInd >= 0) and (gArrDiplomacy[enemyPlInd][myPlIndex].message.treaty <> gc_TreatyPeace) and (gArrDiplomacy[myPlIndex][enemyPlInd].message.treaty <> gc_TreatyPeace) then // don't display tangential peace offer if there's already a direct peace offer
      [*] = ;            begin
      [*] = ;               if SameText(myCMode, 'cmPlayer') then
      [*] = ;               begin
      [*] = ;                  var pQuery : Integer = ParserAddChildByIndex(pMyQueries, '*');
      [*] = ;                  ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', gc_gui_query_diplAskPeaceFromUnion);
      [*] = ;                  if (gArrDiplomacy[i][enemyPlInd].message.treaty = gc_TreatyPeace) then
      [*] = ;                  begin
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex', i);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex1', enemyPlInd);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex', enemyPlInd);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex1', i);
      [*] = ;                  end;
      [*] = ;                  ParserSetBoolValueByKeyByHandle(pQuery, 'Diplomacy', true);
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  // use pseudo offer from the enemy player to get willingness of AI to form peace. Any real offers should no longer exist at this point.
      [*] = ;                  gArrDiplomacy[enemyPlInd][myPlIndex].message.mType := gc_MessageTreaty;
      [*] = ;                  gArrDiplomacy[enemyPlInd][myPlIndex].message.treaty := gc_TreatyPeace;
      [*] = ;                           
      [*] = ;                  IntRegister0 := enemyPlInd;
      [*] = ;                  ExecuteState('GetDiploAnswerAI');
      [*] = ;                  var bAgree : Boolean = (gArrDiplomacy[enemyPlInd][myPlIndex].message.deal > 0);
      [*] = ;                  _diplomacy_ClearMessage(gArrDiplomacy[enemyPlInd][myPlIndex].message);
      [*] = ;                  _diplomacy_ClearMessage(gArrDiplomacy[enemyPlInd][myPlIndex].queryWindowMessage);
      [*] = ;                           
      [*] = ;                  // send the actual message. The message to a potential ally of the enemy is already sent in GetDiploAnswerAI
      [*] = ;                  gArrDiplomacy[myPlIndex][enemyPlInd].message.mType := gc_MessageTreaty;
      [*] = ;                  gArrDiplomacy[myPlIndex][enemyPlInd].message.treaty := gc_TreatyPeace;
      [*] = ;                  if not bAgree then 
      [*] = ;                  begin
      [*] = ;                     gArrDiplomacy[myPlIndex][enemyPlInd].message.deal := -3;
      [*] = ;                     gArrDiplomacy[myPlIndex][enemyPlInd].arrTalk[gc_TreatyPeace][0] := 0;
      [*] = ;                     gArrDiplomacy[myPlIndex][enemyPlInd].arrTalk[gc_TreatyPeace][1] := gGame.currentTurn;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               
      [*] = ;               // process only one gc_gui_query_diplAskPeaceFromUnion per union war
      [*] = ;               break;
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

