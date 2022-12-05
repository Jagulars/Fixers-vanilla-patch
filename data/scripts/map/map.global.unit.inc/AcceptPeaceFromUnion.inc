section.begin
   Name = AcceptPeaceFromUnion
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\ACCEPTPEACEFROMUNION';
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
      [*] = ;   ParserSetIntValueByKeyByHandle(pMessageParser, 'Deal', 2); 
      [*] = ;            
      [*] = ;   var pSendTreasury : Integer = ParserAddChildByIndex(pMessageParser, 'Treasury');
      [*] = ;   var pTreasury : Integer = ParserSelectByHandleByKey(ParserSelectPlayer(myPlHandle), 'Treasury');
      [*] = ;   ParserCopyToByHandle(pSendTreasury); // update treasury along with the message, as items can be switched around at any time.
      [*] = ;   
      [*] = ;   _lan_LanSendParser(gc_LAN_SHARD_DIPLOMACYMESSAGE, pMessageParser);
      [*] = ;end;
      [*] = ;
      [*] = ;// send peace offer directly to enemies in this union war if none exists.
      [*] = ;var i, enPlayerInd : Integer;
      [*] = ;if gArrDiplomacy[myPlIndex][answerPlInd].treaty = gc_TreatyWar then
      [*] = ;   enPlayerInd := answerPlInd
      [*] = ;else
      [*] = ;   enPlayerInd := proposePlInd;
      [*] = ;
      [*] = ;var bUpdateDiplWindow : Boolean = false;
      [*] = ;for i := 0 to gGame.map.players-1 do
      [*] = ;if ((gArrDiplomacy[i][enPlayerInd].treaty = gc_TreatyUnion) or (i = enPlayerInd)) and (gArrDiplomacy[i][myPlIndex].message.treaty <> gc_TreatyPeace) and (gArrDiplomacy[myPlIndex][i].message.treaty <> gc_TreatyPeace) and _plr_IsInGame(GetPlayerHandleByIndex(i)) then 
      [*] = ;begin
      [*] = ;   gArrDiplomacy[myPlIndex][i].message.treaty := gc_TreatyPeace;
      [*] = ;   gArrDiplomacy[myPlIndex][i].message.mType := gc_MessageTreaty;
      [*] = ;   gArrDiplomacy[myPlIndex][i].answer := 0;
      [*] = ;   _diplomacy_AssignMessage(gArrDiplomacy[myPlIndex][i].queryWindowMessage, gArrDiplomacy[myPlIndex][i].message);
      [*] = ;   
      [*] = ;   if (myPlIndex = gIntRegister_MapMyPlayerIndex) then
      [*] = ;   begin
      [*] = ;      if (gIntRegister_DiplomacyWindowMode > 0) and (gIntRegister_DiplomacyActivePlayerID = i) then
      [*] = ;         bUpdateDiplWindow := true;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (i = gIntRegister_MapMyPlayerIndex) then
      [*] = ;   begin
      [*] = ;       _diplomacy_UpdateDisplayPriority(i, 1);
      [*] = ;       gArrDiplomacy[myPlIndex][i].displayPriority := (gArrDiplomacy[myPlIndex][i].displayPriority and $ffff00) + 1;
      [*] = ;       if (gIntRegister_DiplomacyActivePlayerID = myPlIndex) and (gIntRegister_DiplomacyWindowMode > 0) then
      [*] = ;         bUpdateDiplWindow := true;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;if bUpdateDiplWindow then
      [*] = ;   GUIExecuteState('map.CreateDiplomacyWindow');
      [*] = ;   
      [*] = ;IntRegister0 := proposePlInd;
      [*] = ;IntRegister1 := answerPlInd;
      [*] = ;BoolRegister0 := false;
      [*] = ;ExecuteState('CheckUnionPeaceOffer');
      [*] = ;var queryAnotherPlayer : Boolean = BoolRegister2;
      [*] = ;var unionRejection : Boolean = BoolRegister3;
      [*] = ;var allyPlIndex : Integer = IntRegister0;
      [*] = ;var enPlIndex : Integer = IntRegister1;
      [*] = ;
      [*] = ;if (allyPlIndex >= 0) and (enPlIndex >= 0) then
      [*] = ;begin
      [*] = ;   _misc_PlMakeDiplomacyText(allyPlIndex, myPlIndex, 28, 0); // ally refuse peace
      [*] = ;   var queryID : String = gArrDiplomacy[allyPlIndex][myPlIndex].message.text;
      [*] = ;   if queryID <> '' then
      [*] = ;   begin
      [*] = ;      var pQuery : Integer = ParserAddChildByIndex(ParserSelectByHandleByKey(ParserSelectPlayer(myPlHandle), 'Queries'), '*');
      [*] = ;         
      [*] = ;      ParserSetValueByKeyByHandle(pQuery, 'QueryID', queryID);
      [*] = ;      ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex', allyPlIndex);
      [*] = ;      ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex1', enPlIndex);
      [*] = ;      ParserSetBoolValueByKeyByHandle(pQuery, 'Diplomacy', true);
      [*] = ;      ParserSetBoolValueByKeyByHandle(pQuery, 'Informative', true);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;   
      [*] = ;   
      [*] = ;if queryAnotherPlayer then
      [*] = ;begin
      [*] = ;   if (myPlIndex = gIntRegister_MapMyPlayerIndex) then
      [*] = ;   begin
      [*] = ;      StringRegister0 := IntToStr(gc_gui_query_diplUnionPeaceAlliesNotif);
      [*] = ;      GUIExecuteState('map.RequestQueryWindow');
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;if (gGame.gameType <> gc_GameTypeLanShard) or SameText(GetPlayerControlModeByHandle(myPlHandle), 'cmPC') then
      [*] = ;begin
      [*] = ;   if unionRejection then
      [*] = ;   begin
      [*] = ;      IntRegister0 := proposePlInd;
      [*] = ;      IntRegister1 := answerPlInd;
      [*] = ;      ExecuteState('DeleteUnionPeaceOffers');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      IntRegister0 := proposePlInd;
      [*] = ;      IntRegister1 := answerPlInd;
      [*] = ;      ExecuteState('ExecuteUnionPeace');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

