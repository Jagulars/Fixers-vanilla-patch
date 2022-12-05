section.begin
   Name = RefusePeaceFromUnion
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\REFUSEPEACEFROMUNION';
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
      [*] = ;if (gGame.gameType = gc_GameTypeLanShard) and (myPlIndex = gIntRegister_MapMyPlayerIndex) then
      [*] = ;begin
      [*] = ;   var pMessageParser : Integer = _misc_ParserGetOrCreateByKey('lan_diplomacy_message', true);
      [*] = ;   
      [*] = ;   ParserSetIntValueByKeyByHandle(pMessageParser, 'ProposePlayer', proposePlInd);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMessageParser, 'AnswerPlayer', answerPlInd);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMessageParser, 'MessagePlayer', myPlIndex);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMessageParser, 'Deal', -2); 
      [*] = ;            
      [*] = ;   var pSendTreasury : Integer = ParserAddChildByIndex(pMessageParser, 'Treasury');
      [*] = ;   var pTreasury : Integer = ParserSelectByHandleByKey(ParserSelectPlayer(myPlHandle), 'Treasury');
      [*] = ;   ParserCopyToByHandle(pSendTreasury); // update treasury along with the message, as items can be switched around at any time.
      [*] = ;   
      [*] = ;   _lan_LanSendParser(gc_LAN_SHARD_DIPLOMACYMESSAGE, pMessageParser);
      [*] = ;end;
      [*] = ;
      [*] = ;var i, enPlIndex, allyPlIndex : Integer;
      [*] = ;if gArrDiplomacy[myPlIndex][answerPlInd].treaty = gc_TreatyWar then
      [*] = ;begin
      [*] = ;   enPlIndex := answerPlInd;
      [*] = ;   allyPlIndex := proposePlInd;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   enPlIndex := proposePlInd;
      [*] = ;   allyPlIndex := answerPlInd;
      [*] = ;end;
      [*] = ;
      [*] = ;// ensure AI players don't keep bombarding peace offers
      [*] = ;gArrDiplomacy[enPlIndex][myPlIndex].arrTalk[gc_TreatyPeace][1] := gGame.currentTurn;
      [*] = ;
      [*] = ;// refuse peace offers
      [*] = ;for i := 0 to gGame.map.players-1 do
      [*] = ;if ((gArrDiplomacy[i][enPlIndex].treaty = gc_TreatyUnion) or (i = enPlIndex)) and _plr_IsInGame(GetPlayerHandleByIndex(i)) then 
      [*] = ;begin
      [*] = ;   // send pseudo-peace offer (instant withdrawal) directly to enemies in this union war if none exists. So that CheckUnionPeaceOffer does not interpret a pending situation between players.
      [*] = ;   if ((gArrDiplomacy[i][myPlIndex].message.treaty <> gc_TreatyPeace) or (gArrDiplomacy[i][myPlIndex].message.deal < 0)) and (gArrDiplomacy[myPlIndex][i].message.treaty <> gc_TreatyPeace) then 
      [*] = ;   begin
      [*] = ;      gArrDiplomacy[myPlIndex][i].message.deal := -3;
      [*] = ;      gArrDiplomacy[myPlIndex][i].message.treaty := gc_TreatyPeace;
      [*] = ;      gArrDiplomacy[myPlIndex][i].message.mType := gc_MessageTreaty;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;      
      [*] = ; // send ally refuse peace message if the ally has already agreed to peace
      [*] = ;if ((allyPlIndex = proposePlInd) or (gArrDiplomacy[allyPlIndex][enPlIndex].message.treaty = gc_TreatyPeace) or (gArrDiplomacy[enPlIndex][allyPlIndex].message.deal > 0)) 
      [*] = ;  and ((gGame.gameType <> gc_GameTypeLanShard) or (allyPlIndex = gIntRegister_MapMyPlayerIndex)) and SameText(GetPlayerControlModeByHandle(GetPlayerHandleByIndex(allyPlIndex)), 'cmPlayer') then
      [*] = ;begin
      [*] = ;   _misc_PlMakeDiplomacyText(myPlIndex, allyPlIndex, 28, 0);
      [*] = ;   var queryID : String = gArrDiplomacy[myPlIndex][allyPlIndex].message.text;
      [*] = ;   if queryID <> '' then
      [*] = ;   begin
      [*] = ;      var pQuery : Integer = ParserAddChildByIndex(ParserSelectByHandleByKey(ParserSelectPlayer(GetPlayerHandleByIndex(allyPlIndex)), 'Queries'), '*');
      [*] = ;         
      [*] = ;      ParserSetBoolValueByKeyByHandle(pQuery, 'Priority', true);
      [*] = ;      ParserSetValueByKeyByHandle(pQuery, 'QueryID', queryID);
      [*] = ;      ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex', myPlIndex);
      [*] = ;      ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex1', enPlIndex);
      [*] = ;      ParserSetBoolValueByKeyByHandle(pQuery, 'Diplomacy', true);
      [*] = ;      ParserSetBoolValueByKeyByHandle(pQuery, 'Informative', true);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister0 := proposePlInd;
      [*] = ;IntRegister1 := answerPlInd;
      [*] = ;BoolRegister0 := true;
      [*] = ;ExecuteState('CheckUnionPeaceOffer');
      [*] = ;var queryAnotherPlayer : Boolean = BoolRegister2;
      [*] = ;
      [*] = ;if (not queryAnotherPlayer) and ((gGame.gameType <> gc_GameTypeLanShard) or SameText(GetPlayerControlModeByHandle(myPlHandle), 'cmPC')) then
      [*] = ;begin
      [*] = ;   IntRegister0 := proposePlInd;
      [*] = ;   IntRegister1 := answerPlInd;
      [*] = ;   ExecuteState('DeleteUnionPeaceOffers');
      [*] = ;end;
      [*] = ;
      [*] = ;      
      [*] = ;{// update diplomacy window
      [*] = ;if myPlIndex = gIntRegister_MapMyPlayerIndex then // I refused
      [*] = ;begin
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;   if ((gArrDiplomacy[i][enPlIndex].treaty = gc_TreatyUnion) or (i = enPlIndex)) and _plr_IsInGame(GetPlayerHandleByIndex(i)) then 
      [*] = ;   begin
      [*] = ;      if (gIntRegister_DiplomacyWindowMode > 0) and (gIntRegister_DiplomacyActivePlayerID = i) then
      [*] = ;      begin
      [*] = ;       gArrDiplomacy[plIndex][myPlIndex].displayPriority := gArrDiplomacy[plIndex][myPlIndex].displayPriority and $ff00;
      [*] = ;      _diplomacy_ClearMessage(gDiplMessage);
      [*] = ;      gIntRegister_DiplomacyWindowMode := 1;
      [*] = ;      GUIExecuteState('map.CreateDiplomacyWindow');
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;if proposePlInd = gIntRegister_MapMyPlayerIndex then //my proposal refused
      [*] = ;begin
      [*] = ;   _diplomacy_UpdateDisplayPriority(gIntRegister_MapMyPlayerIndex, $100);
      [*] = ;   gArrDiplomacy[myPlIndex][gIntRegister_MapMyPlayerIndex].displayPriority := gArrDiplomacy[myPlIndex][gIntRegister_MapMyPlayerIndex].displayPriority or $100;
      [*] = ;                  
      [*] = ;   if (gIntRegister_DiplomacyWindowMode > 0) then
      [*] = ;   begin     
      [*] = ;      if (gIntRegister_DiplomacyActivePlayerID = myPlIndex) then
      [*] = ;      begin
      [*] = ;         if gIntRegister_DiplomacyWindowMode = 3 then
      [*] = ;            gIntRegister_DiplomacyWindowMode := 1;
      [*] = ;         GUIExecuteState('map.CreateDiplomacyWindow');
      [*] = ;      end
      [*] = ;      else // apply blink to icon immediately on arrival of the refusal
      [*] = ;      begin
      [*] = ;         var elmPortrait : Integer = GetGUIElementIndexByNameParent('dip_background.round_portrait_'+IntToStr(myPlIndex)+'_border', _gui_GetWindow('diplomacy'));
      [*] = ;         _gui_CreateBlinkElement('btnDiplomacyPlayer_'+IntToStr(myPlIndex), elmPortrait, 'gamepanel01.btn.round.73x73.highlight', false, 0, 0, 0, 0);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;}
      [*] = ;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

