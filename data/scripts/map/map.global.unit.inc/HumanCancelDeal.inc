section.begin
   Name = HumanCancelDeal
   Description[*] = ;IntRegister0 - sender player index
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\HUMANCANCELDEAL';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var plIndex : Integer = IntRegister0;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[MyIndex: '+IntToStr(myPlIndex)+', plIndex: '+IntToStr(plIndex)+']',_log_trace);
      [*] = ;
      [*] = ;if (gGame.gameType = gc_GameTypeLanShard) and (myPlIndex = gIntRegister_MapMyPlayerIndex) then
      [*] = ;begin
      [*] = ;   var pMessageParser : Integer = _misc_ParserGetOrCreateByKey('lan_diplomacy_message', true);
      [*] = ;   
      [*] = ;   ParserSetIntValueByKeyByHandle(pMessageParser, 'ProposePlayer', plIndex);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMessageParser, 'AnswerPlayer', myPlIndex);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMessageParser, 'MessagePlayer', myPlIndex);
      [*] = ;   ParserSetIntValueByKeyByHandle(pMessageParser, 'Deal', -1); 
      [*] = ;            
      [*] = ;   var pSendTreasury : Integer = ParserAddChildByIndex(pMessageParser, 'Treasury');
      [*] = ;   var pTreasury : Integer = ParserSelectByHandleByKey(ParserSelectPlayer(myPlHandle), 'Treasury');
      [*] = ;   ParserCopyToByHandle(pSendTreasury); // update treasury along with the message, as items can be switched around at any time.
      [*] = ;   
      [*] = ;   _lan_LanSendParser(gc_LAN_SHARD_DIPLOMACYMESSAGE, pMessageParser);
      [*] = ;end;
      [*] = ;
      [*] = ;var mType : Integer = gArrDiplomacy[plIndex][myPlIndex].message.mType;
      [*] = ;var mTreaty : Integer = gArrDiplomacy[plIndex][myPlIndex].message.treaty;
      [*] = ;var bProposal : Boolean = _diplomacy_IsProposal(gArrDiplomacy[plIndex][myPlIndex].message);
      [*] = ;
      [*] = ;if (gArrDiplomacy[plIndex][myPlIndex].message.deal < 1) then // ensure that already sealed deal cannot be cancelled because of internet lag
      [*] = ;   gArrDiplomacy[plIndex][myPlIndex].message.deal := -1;
      [*] = ;
      [*] = ;if ((mType > 0) or (mTreaty > 0)) and bProposal then
      [*] = ;   gArrDiplomacy[myPlIndex][plIndex].answer := -2;
      [*] = ;
      [*] = ;case mTreaty of
      [*] = ;   0 : begin
      [*] = ;      if ((mType = gc_MessageTrade) or (mType = gc_MessageExchange)) and (_rand_Random(10) < 5) then // 50% chance to reduce attitude when refusing business offer
      [*] = ;         gArrDiplomacy[plIndex][myPlIndex].attitude := gArrDiplomacy[plIndex][myPlIndex].attitude - 1;
      [*] = ;   end;
      [*] = ;   gc_TreatyPeace, gc_TreatyUnion : gArrDiplomacy[plIndex][myPlIndex].attitude := gArrDiplomacy[plIndex][myPlIndex].attitude - 2;
      [*] = ;end;
      [*] = ;
      [*] = ;// check union peace offer
      [*] = ;var isUnionOffer : Boolean = false;
      [*] = ;if (mTreaty = gc_TreatyPeace) then
      [*] = ;begin
      [*] = ;   // send pseudo-peace offer (instant withdrawal) directly to enemies in this union war if none exists. So that CheckUnionPeaceOffer does not interpret a pending situation between players.
      [*] = ;   var i : Integer;
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;   if (gArrDiplomacy[i][plIndex].treaty = gc_TreatyUnion) and ((gArrDiplomacy[i][myPlIndex].message.treaty <> gc_TreatyPeace) or (gArrDiplomacy[i][myPlIndex].message.deal < 0)) 
      [*] = ;     and (gArrDiplomacy[myPlIndex][i].message.treaty <> gc_TreatyPeace) and _plr_IsInGame(GetPlayerHandleByIndex(i)) then 
      [*] = ;   begin
      [*] = ;      gArrDiplomacy[myPlIndex][i].message.deal := -3;
      [*] = ;      gArrDiplomacy[myPlIndex][i].message.treaty := gc_TreatyPeace;
      [*] = ;      gArrDiplomacy[myPlIndex][i].message.mType := gc_MessageTreaty;
      [*] = ;   end;
      [*] = ;      
      [*] = ;   IntRegister0 := plIndex;
      [*] = ;   IntRegister1 := myPlIndex;
      [*] = ;   BoolRegister0 := true;
      [*] = ;   ExecuteState('CheckUnionPeaceOffer');
      [*] = ;   isUnionOffer := BoolRegister1;
      [*] = ;   var queryAnotherPlayer : Boolean = BoolRegister2;
      [*] = ;   //var unionRejection : Boolean = BoolRegister3;
      [*] = ;   var allyPlIndex : Integer = IntRegister0;
      [*] = ;   var enPlIndex : Integer = IntRegister1;
      [*] = ;      
      [*] = ;   if (allyPlIndex >= 0) and (enPlIndex >= 0) and ((gGame.gameType <> gc_GameTypeLanShard) or (allyPlIndex = gIntRegister_MapMyPlayerIndex)) and SameText(GetPlayerControlModeByHandle(GetPlayerHandleByIndex(allyPlIndex)), 'cmPlayer') then
      [*] = ;   begin
      [*] = ;      _misc_PlMakeDiplomacyText(myPlIndex, allyPlIndex, 28, 0); // send ally refuse peace message
      [*] = ;      var queryID : String = gArrDiplomacy[myPlIndex][allyPlIndex].message.text;
      [*] = ;      if queryID <> '' then
      [*] = ;      begin
      [*] = ;         var pQuery : Integer = ParserAddChildByIndex(ParserSelectByHandleByKey(ParserSelectPlayer(GetPlayerHandleByIndex(allyPlIndex)), 'Queries'), '*');
      [*] = ;         
      [*] = ;         ParserSetBoolValueByKeyByHandle(pQuery, 'Priority', true);
      [*] = ;         ParserSetValueByKeyByHandle(pQuery, 'QueryID', queryID);
      [*] = ;         ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex', myPlIndex);
      [*] = ;         ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex1', enPlIndex);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pQuery, 'Diplomacy', true);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pQuery, 'Informative', true);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   if isUnionOffer and (not queryAnotherPlayer) and ((gGame.gameType <> gc_GameTypeLanShard) or SameText(GetPlayerControlModeByHandle(myPlHandle), 'cmPC')) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := plIndex;
      [*] = ;      IntRegister1 := myPlIndex;
      [*] = ;      ExecuteState('DeleteUnionPeaceOffers');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var plHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;if (not isUnionOffer) and ((gGame.gameType <> gc_GameTypeLanShard) or (not bProposal) or SameText(GetPlayerControlModeByHandle(plHandle), 'cmPC')) then
      [*] = ;begin
      [*] = ;   // Beleth (your ally) demands the shard for himself once other masters are banished, refusal cancels the alliance
      [*] = ;   if (gGame.gameType = gc_GameTypeCampaign) and (mType = gc_MessageDemandSurrender) and (GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile) = 3) and (gCampaign.arrDialogs[103] > 0) then 
      [*] = ;   begin
      [*] = ;      gCampaign.arrCampPlayers[3].treaty := 0;
      [*] = ;      gCampaign.arrDialogs[103] := 0;
      [*] = ;      gCampaign.arrDialogs[104] := 1;
      [*] = ;      gArrDiplomacy[plIndex][myPlIndex].attitude := gArrDiplomacy[plIndex][myPlIndex].attitude - 400;
      [*] = ;   end;
      [*] = ;
      [*] = ;   IntRegister0 := plIndex;
      [*] = ;   ExecuteState('CancelDeal');
      [*] = ;end
      [*] = ;else // ensure AI players don't keep bombarding peace offers
      [*] = ;begin
      [*] = ;   IntRegister0 := plIndex;
      [*] = ;   IntRegister1 := 0;
      [*] = ;   ExecuteState('MessageEntry');
      [*] = ;end;
      [*] = ;
      [*] = ;// update diplomacy window
      [*] = ;if myPlIndex = gIntRegister_MapMyPlayerIndex then // I refused
      [*] = ;begin
      [*] = ;   if (gIntRegister_DiplomacyWindowMode > 0) and (gIntRegister_DiplomacyActivePlayerID = plIndex) then
      [*] = ;   begin
      [*] = ;       gArrDiplomacy[plIndex][myPlIndex].displayPriority := gArrDiplomacy[plIndex][myPlIndex].displayPriority and $ffff00;
      [*] = ;      _diplomacy_ClearMessage(gDiplMessage);
      [*] = ;      gIntRegister_DiplomacyWindowMode := 1;
      [*] = ;      GUIExecuteState('map.CreateDiplomacyWindow');
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;if plIndex = gIntRegister_MapMyPlayerIndex then //my proposal refused
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
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

