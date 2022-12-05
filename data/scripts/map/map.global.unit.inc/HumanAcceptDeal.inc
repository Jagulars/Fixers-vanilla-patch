section.begin
   Name = HumanAcceptDeal
   Description[*] = ;IntRegister0 - sender player index
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\HUMANACCEPTDEAL';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var plIndex : Integer = IntRegister0;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;   
      [*] = ;var mType : Integer = gArrDiplomacy[plIndex][myPlIndex].message.mType;
      [*] = ;var mTreaty : Integer = gArrDiplomacy[plIndex][myPlIndex].message.treaty;
      [*] = ;var bProposal : Boolean = _diplomacy_IsProposal(gArrDiplomacy[plIndex][myPlIndex].message);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[MyIndex: '+IntToStr(myPlIndex)+', plIndex: '+IntToStr(plIndex)+']',_log_trace);
      [*] = ;
      [*] = ;if (gGame.gameType = gc_GameTypeLanShard) and (myPlIndex = gIntRegister_MapMyPlayerIndex) then
      [*] = ;begin
      [*] = ;   var pMessageParser : Integer = _misc_ParserGetOrCreateByKey('lan_diplomacy_message', true);
      [*] = ;   
      [*] =     IntRegister0 := 2; // pack message
      [*] = ;   IntRegister1 := pMessageParser;
      [*] = ;   IntRegister2 := plIndex;
      [*] = ;   IntRegister3 := myPlIndex;
      [*] = ;   GUIExecuteState('VVK.DiplomacyHelper'); // send the whole message in case the other player deletes it during the network delay.
      [*] = ;   
      [*] = ;   ParserSetIntValueByKeyByHandle(pMessageParser, 'ProposePlayer', plIndex);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMessageParser, 'AnswerPlayer', myPlIndex);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMessageParser, 'MessagePlayer', myPlIndex);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMessageParser, 'Deal', 1); 
      [*] = ;            
      [*] = ;   var pSendTreasury : Integer = ParserAddChildByIndex(pMessageParser, 'Treasury');
      [*] = ;   var pTreasury : Integer = ParserSelectByHandleByKey(ParserSelectPlayer(myPlHandle), 'Treasury');
      [*] = ;   ParserCopyToByHandle(pSendTreasury); // update treasury along with the message, as items can be switched around at any time.
      [*] = ;   
      [*] = ;   _lan_LanSendParser(gc_LAN_SHARD_DIPLOMACYMESSAGE, pMessageParser);
      [*] = ;end;
      [*] = ;   
      [*] = ;// release the escrow of my offer because only one sealed deal between two players per turn
      [*] = ;_diplomacy_Escrow(myPlIndex, plIndex, false);
      [*] = ;
      [*] = ;_diplomacy_ClearMessage(gArrDiplomacy[myPlIndex][plIndex].message); // only one deal can be formed between two players per turn, so my offer is deleted if I accept the other player's offer.
      [*] = ;gArrDiplomacy[plIndex][myPlIndex].message.deal := 1;
      [*] = ;if ((mType > 0) or (mTreaty > 0)) and bProposal then
      [*] = ;   gArrDiplomacy[myPlIndex][plIndex].answer := 2;
      [*] = ;   
      [*] = ;// in case of delayed processing, store an escrow that can't be used until the deal is resolved.
      [*] = ;_diplomacy_Escrow(plIndex, myPlIndex, true);
      [*] = ;
      [*] = ;// check union peace offer
      [*] = ;var isUnionOffer, bUpdateDiplWindow : Boolean = false;
      [*] = ;if (mTreaty = gc_TreatyPeace) then
      [*] = ;begin
      [*] = ;   // send peace offer directly to enemies in this union war if none exists.
      [*] = ;   var i : Integer;
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;   if (gArrDiplomacy[i][plIndex].treaty = gc_TreatyUnion) and (gArrDiplomacy[i][myPlIndex].message.treaty <> gc_TreatyPeace) and (gArrDiplomacy[myPlIndex][i].message.treaty <> gc_TreatyPeace) and _plr_IsInGame(GetPlayerHandleByIndex(i)) then 
      [*] = ;   begin
      [*] = ;      gArrDiplomacy[myPlIndex][i].message.treaty := gc_TreatyPeace;
      [*] = ;      gArrDiplomacy[myPlIndex][i].message.mType := gc_MessageTreaty;
      [*] = ;      _diplomacy_AssignMessage(gArrDiplomacy[myPlIndex][i].queryWindowMessage, gArrDiplomacy[myPlIndex][i].message);
      [*] = ;   
      [*] = ;      if (myPlIndex = gIntRegister_MapMyPlayerIndex) then
      [*] = ;      begin
      [*] = ;         if (gIntRegister_DiplomacyWindowMode > 0) and (gIntRegister_DiplomacyActivePlayerID = i) then
      [*] = ;            bUpdateDiplWindow := true;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (i = gIntRegister_MapMyPlayerIndex) then
      [*] = ;      begin
      [*] = ;          _diplomacy_UpdateDisplayPriority(i, 1);
      [*] = ;          gArrDiplomacy[myPlIndex][i].displayPriority := (gArrDiplomacy[myPlIndex][i].displayPriority and $ffff00) + 1;
      [*] = ;          if (gIntRegister_DiplomacyActivePlayerID = myPlIndex) then
      [*] = ;            bUpdateDiplWindow := true;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;      
      [*] = ;   IntRegister0 := plIndex;
      [*] = ;   IntRegister1 := myPlIndex;
      [*] = ;   BoolRegister0 := false;
      [*] = ;   ExecuteState('CheckUnionPeaceOffer');
      [*] = ;   isUnionOffer := BoolRegister1;
      [*] = ;   var queryAnotherPlayer : Boolean = BoolRegister2;
      [*] = ;   var unionRejection : Boolean = BoolRegister3;
      [*] = ;   var allyPlIndex : Integer = IntRegister0;
      [*] = ;   var enPlIndex : Integer = IntRegister1;
      [*] = ;      
      [*] = ;   if (allyPlIndex >= 0) and (enPlIndex >= 0) and ((gGame.gameType <> gc_GameTypeLanShard) or (myPlIndex = gIntRegister_MapMyPlayerIndex)) then
      [*] = ;   begin
      [*] = ;      _misc_PlMakeDiplomacyText(allyPlIndex, myPlIndex, 28, 0); // ally refuse peace
      [*] = ;      var queryID : String = gArrDiplomacy[allyPlIndex][myPlIndex].message.text;
      [*] = ;      if queryID <> '' then
      [*] = ;      begin
      [*] = ;         var pQuery : Integer = ParserAddChildByIndex(ParserSelectByHandleByKey(ParserSelectPlayer(myPlHandle), 'Queries'), '*');
      [*] = ;         
      [*] = ;         ParserSetValueByKeyByHandle(pQuery, 'QueryID', queryID);
      [*] = ;         ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex', allyPlIndex);
      [*] = ;         ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex1', enPlIndex);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pQuery, 'Diplomacy', true);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pQuery, 'Informative', true);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   if queryAnotherPlayer then
      [*] = ;   begin
      [*] = ;      if (myPlIndex = gIntRegister_MapMyPlayerIndex) then
      [*] = ;      begin
      [*] = ;         StringRegister0 := IntToStr(gc_gui_query_diplUnionPeaceAlliesNotif);
      [*] = ;         GUIExecuteState('map.RequestQueryWindow');
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if unionRejection then
      [*] = ;   begin
      [*] = ;      IntRegister0 := plIndex;
      [*] = ;      IntRegister1 := myPlIndex;
      [*] = ;      ExecuteState('DeleteUnionPeaceOffers');
      [*] = ;   end
      [*] = ;   else 
      [*] = ;   if isUnionOffer and (gGame.gameType <> gc_GameTypeLanShard) then // on lan games the deals will be processed right after the end of turn
      [*] = ;   begin
      [*] = ;      IntRegister0 := plIndex;
      [*] = ;      IntRegister1 := myPlIndex;
      [*] = ;      ExecuteState('ExecuteUnionPeace');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;   
      [*] = ;   
      [*] = ;var plHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;if (not isUnionOffer) and ((gGame.gameType <> gc_GameTypeLanShard) or (not bProposal) or SameText(GetPlayerControlModeByHandle(plHandle), 'cmPC')) then
      [*] = ;begin
      [*] = ;   // Beleth (your ally) demands the shard for himself once other masters are banished
      [*] = ;   if (mType = gc_MessageDemandSurrender) and (gGame.gameType = gc_GameTypeCampaign) and (GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile) = 3) and (gCampaign.arrDialogs[103] > 0) then 
      [*] = ;      gCampaign.arrItems[4] := gCampaign.arrItems[4] + 1; // shards for Beleth
      [*] = ;
      [*] = ;   IntRegister0 := plIndex;
      [*] = ;   ExecuteState('AcceptDeal');
      [*] = ;
      [*] = ;   if (mTreaty = gc_TreatyWar) or (mTreaty = gc_TreatyUnion) then
      [*] = ;      ExecuteState('CheckUnionWars');
      [*] = ;end;
      [*] = ;
      [*] = ;// update diplomacy window
      [*] = ;if myPlIndex = gIntRegister_MapMyPlayerIndex then // I accepted
      [*] = ;begin
      [*] = ;   if (gIntRegister_DiplomacyWindowMode > 0) and (gIntRegister_DiplomacyActivePlayerID = plIndex) then
      [*] = ;   begin
      [*] = ;       gArrDiplomacy[plIndex][myPlIndex].displayPriority := gArrDiplomacy[plIndex][myPlIndex].displayPriority and $ffff00;
      [*] = ;      _diplomacy_ClearMessage(gDiplMessage);
      [*] = ;      gIntRegister_DiplomacyWindowMode := 1;
      [*] = ;      GUIExecuteState('map.CreateDiplomacyWindow');
      [*] = ;      bUpdateDiplWindow := false;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;if plIndex = gIntRegister_MapMyPlayerIndex then // my message was accepted
      [*] = ;begin
      [*] = ;   if bProposal then
      [*] = ;   begin
      [*] = ;      _diplomacy_UpdateDisplayPriority(plIndex, $100);
      [*] = ;      gArrDiplomacy[myPlIndex][plIndex].displayPriority := gArrDiplomacy[myPlIndex][plIndex].displayPriority or $100;
      [*] = ;   end;
      [*] = ;                  
      [*] = ;   if (gIntRegister_DiplomacyWindowMode > 0) then
      [*] = ;   begin
      [*] = ;      if (gIntRegister_DiplomacyActivePlayerID = myPlIndex) then
      [*] = ;      begin
      [*] = ;         _diplomacy_ClearMessage(gDiplMessage);
      [*] = ;         _diplomacy_AssignMessage(gDiplMessage, gArrDiplomacy[plIndex][myPlIndex].message);
      [*] = ;         _diplomacy_AssignTrade(gDiplMessage.tradeGive, gArrDiplomacy[plIndex][myPlIndex].message.tradeGive);
      [*] = ;         _diplomacy_AssignTrade(gDiplMessage.tradeTake, gArrDiplomacy[plIndex][myPlIndex].message.tradeTake);
      [*] = ;         gIntRegister_DiplomacyWindowMode := 3;
      [*] = ;         GUIExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         bUpdateDiplWindow := false;
      [*] = ;      end
      [*] = ;      else // apply blink to icon immediately on arrival of the acceptance
      [*] = ;      begin
      [*] = ;         var elmPortrait : Integer = GetGUIElementIndexByNameParent('dip_background.round_portrait_'+IntToStr(myPlIndex)+'_border', _gui_GetWindow('diplomacy'));
      [*] = ;         _gui_CreateBlinkElement('btnDiplomacyPlayer_'+IntToStr(myPlIndex), elmPortrait, 'gamepanel01.btn.round.73x73.highlight', false, 0, 0, 0, 0);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;if bUpdateDiplWindow then
      [*] = ;   GUIExecuteState('map.CreateDiplomacyWindow');
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

