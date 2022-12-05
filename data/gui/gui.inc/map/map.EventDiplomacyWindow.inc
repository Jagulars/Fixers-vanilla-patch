section.begin
   Name = map.EventDiplomacyWindow
   Code : struct.begin
      [*] = ;procedure SortItemsArray(var trade : TTrade);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to gc_MaxTradeItemCount-1 do
      [*] = ;   begin
      [*] = ;      if (trade.arrItems[i][0]=0) and (i<gc_MaxTradeItemCount-1) then
      [*] = ;      begin
      [*] = ;         trade.arrItems[i][0] := trade.arrItems[i+1][0];
      [*] = ;         trade.arrItems[i][1] := trade.arrItems[i+1][1];
      [*] = ;         trade.arrItems[i+1][0] := 0;
      [*] = ;         trade.arrItems[i+1][1] := 0;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetInputBox(sideName, partName : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := GetGUIElementIndexByNameParent('diplomacy.dip_background.'+sideName+'.frame_'+partName+'.inputbox_'+partName+'.text', _gui_GetLayerI());
      [*] = ;end;
      [*] = ;
      [*] = ;function GetInputBoxIntValue(sideName, partName : String) : Integer;
      [*] = ;begin
      [*] = ;   var elmHnd : Integer = GetGUIElementIndexByNameParent('diplomacy.dip_background.'+sideName+'.frame_'+partName+'.inputbox_'+partName+'.text', _gui_GetLayerI());
      [*] = ;   Result := StrToInt(GetGUIElementText(elmHnd));
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetInputBoxIntValue(sideName, partName : String; value : Integer);
      [*] = ;begin
      [*] = ;   SetGUIElementText(GetInputBox(sideName, partName), IntToStr(value));
      [*] = ;end;
      [*] = ;
      [*] = ;var sPress  : String = GetValueByName('Press');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;//var elementHandle : String = GetValueByName('ElementHandle');
      [*] = ;//var sTag : String = GetValueByName('Tag'); // IntToStr(Key)
      [*] = ;//var sStatus : String = GetValueByName('Status'); // 'shortcut', 'key', 'button'
      [*] = ;var sKey : String = GetValueByName('Key'); // 'shortcut', 'key', 'button'
      [*] = ;
      [*] = ;const cDeclareWarBtnTag = 1;
      [*] = ;const cOfferPeaceBtnTag = 2;
      [*] = ;const cOfferUnionBtnTag = 3;
      [*] = ;const cCancelUnionBtnTag = 4;
      [*] = ;const cCancelTradeBtnTag = 5;
      [*] = ;const cOfferTradeBtnTag = 6;
      [*] = ;const cOfferExchangeBtnTag = 7;
      [*] = ;const cSendMessageBtnTag = 8;
      [*] = ;const cClearMessageBtnTag = 9;
      [*] = ;const cOfferResTag = 10;
      [*] = ;const cEditMessageBtnTag = 90;
      [*] = ;const cDemandResTag = 20;
      [*] = ;const cCancelTreatyTag = 31;
      [*] = ;const cOfferGoldIncTag = 32;
      [*] = ;const cOfferGemIncTag = 33;
      [*] = ;const cDemandGoldIncTag = 34;
      [*] = ;const cDemandGemIncTag = 35;
      [*] = ;const cOfferGoldTag = 36;
      [*] = ;const cOfferGemTag = 37;
      [*] = ;const cDemandGoldTag = 38;
      [*] = ;const cDemandGemTag = 39;
      [*] = ;const cShowMyMessage = 40;
      [*] = ;const cShowTheirMessage = 41;
      [*] = ;const cHideMessage = 42;
      [*] = ;const cAcceptDeal = 43;
      [*] = ;const cDeclineDeal = 44;
      [*] = ;const cAcceptBtnTag = 100;
      [*] = ;const cCancelBtnTag = 101;
      [*] = ;const cCloseBtnTag = 102;
      [*] = ;const cLogEvent1BtnTag = 200;
      [*] = ;const cInputMinus = 301;
      [*] = ;const cInputPlus = 302;
      [*] = ;const cInputBoxOfferGold = 410;
      [*] = ;const cInputBoxOfferGem = 420;
      [*] = ;const cInputBoxDemandGold = 415;
      [*] = ;const cInputBoxDemandGem = 425;
      [*] = ;const cBtnInputBoxOfferGoldCancel = 411;
      [*] = ;const cBtnInputBoxOfferGemCancel = 421;
      [*] = ;const cBtnInputBoxDemandGoldCancel = 416;
      [*] = ;const cBtnInputBoxDemandGemCancel = 426;
      [*] = ;const cInputBoxOfferGoldInc = 430;
      [*] = ;const cInputBoxOfferGemInc = 440;
      [*] = ;const cInputBoxDemandGoldInc = 435;
      [*] = ;const cInputBoxDemandGemInc = 445;
      [*] = ;const cBtnInputBoxOfferGoldIncCancel = 431;
      [*] = ;const cBtnInputBoxOfferGemIncCancel = 441;
      [*] = ;const cBtnInputBoxDemandGoldIncCancel = 436;
      [*] = ;const cBtnInputBoxDemandGemIncCancel = 446;
      [*] = ;const cPlayerTag = 1000;
      [*] = ;const cOfferItemTag = 2000;
      [*] = ;const cDemandItemTag = 3000;
      [*] = ;const cCancelOfferItemTag = 4000;
      [*] = ;const cCancelDemandItemTag = 5000;
      [*] = ;const cOfferProvinceTag = 6000;
      [*] = ;const cDemandProvinceTag = 7000;
      [*] = ;const cEndTag = 8000;
      [*] = ;
      [*] = ;const cTradeMode = 2;
      [*] = ;const cExchangeMode = 3;
      [*] = ;const cCancelTradeMode = 4;
      [*] = ;
      [*] = ;{const cSpaceChar  = 32; // space
      [*] = ;const cQuoteChar  = 34; // "
      [*] = ;const cEscChar    = 27; // Escape
      [*] = ;const cReturnChar = 13; // Enter or Return}
      [*] = ;
      [*] = ;var pItems : Integer = gPrototypeData.items.handle;
      [*] = ;var maxItemsCount : Integer = ParserGetCountByHandle(pItems)-1;
      [*] = ;var ChangeTreaty : Integer = -1;
      [*] = ;//log (sPress);
      [*] = ;//log(sKey);
      [*] = ;
      [*] = ;if (sKey<>'shortcut') then
      [*] = ;if (sPress='u') or (tag=gc_gui_hotkey_btnEscape) or (tag=gc_gui_hotkey_btnEnter) then //'c' - означает что нам нужно событие отжатия мышки
      [*] = ;begin
      [*] = ;   //log (IntToStr(tag));
      [*] = ;
      [*] = ;   var myPlHandle : Integer = GetPlayerHandleInterfaceIO;
      [*] = ;   var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;   var plIndex : Integer = gIntRegister_DiplomacyActivePlayerID;
      [*] = ;
      [*] = ;   procedure SendLanProposal(answerPlIndex : Integer);
      [*] = ;   begin
      [*] = ;      var pMessageParser : Integer = _misc_ParserGetOrCreateByKey('lan_diplomacy_message', true);
      [*] = ;      
      [*] = ;      IntRegister0 := 2;
      [*] = ;      IntRegister1 := pMessageParser;
      [*] = ;      IntRegister2 := myPlIndex;
      [*] = ;      IntRegister3 := answerPlIndex;
      [*] = ;      GUIExecuteState('VVK.DiplomacyHelper');
      [*] = ;      
      [*] = ;      ParserSetIntValueByKeyByHandle(pMessageParser, 'ProposePlayer', myPlIndex);
      [*] = ;      ParserSetIntValueByKeyByHandle(pMessageParser, 'AnswerPlayer', answerPlIndex);
      [*] = ;      ParserSetIntValueByKeyByHandle(pMessageParser, 'MessagePlayer', myPlIndex);
      [*] = ;      ParserSetIntValueByKeyByHandle(pMessageParser, 'Deal', 0); // proposal
      [*] = ;            
      [*] = ;      var pSendTreasury : Integer = ParserAddChildByIndex(pMessageParser, 'Treasury');
      [*] = ;      ParserSelectByHandleByKey(ParserSelectPlayer(myPlHandle), 'Treasury');
      [*] = ;      ParserCopyToByHandle(pSendTreasury); // update treasury along with the message, as items can be switched around at any time.
      [*] = ;
      [*] = ;      _lan_LanSendParser(gc_LAN_SHARD_DIPLOMACYMESSAGE, pMessageParser);
      [*] = ;   end;
      [*] = ;
      [*] = ;   procedure LanWithdrawal(answerPlIndex : Integer);
      [*] = ;   begin
      [*] = ;      var pMessageParser : Integer = _misc_ParserGetOrCreateByKey('lan_diplomacy_message', true);
      [*] = ;      ParserSetIntValueByKeyByHandle(pMessageParser, 'ProposePlayer', myPlIndex);
      [*] = ;      ParserSetIntValueByKeyByHandle(pMessageParser, 'AnswerPlayer', answerPlIndex);
      [*] = ;      ParserSetIntValueByKeyByHandle(pMessageParser, 'MessagePlayer', myPlIndex);
      [*] = ;      ParserSetIntValueByKeyByHandle(pMessageParser, 'Deal', -3);
      [*] = ;            
      [*] = ;      var pSendTreasury : Integer = ParserAddChildByIndex(pMessageParser, 'Treasury');
      [*] = ;      ParserSelectByHandleByKey(ParserSelectPlayer(myPlHandle), 'Treasury');
      [*] = ;      ParserCopyToByHandle(pSendTreasury); // update treasury along with the message, as items can be switched around at any time.
      [*] = ;
      [*] = ;      _lan_LanSendParser(gc_LAN_SHARD_DIPLOMACYMESSAGE, pMessageParser);
      [*] = ;   end;
      [*] = ;
      [*] = ;   procedure WithdrawProposal();
      [*] = ;   begin
      [*] = ;      if (gArrDiplomacy[myPlIndex][plIndex].message.mType > 0) then
      [*] = ;      begin
      [*] = ;         _diplomacy_Escrow(myPlIndex, plIndex, false);
      [*] = ;         if (gGame.gameType = gc_GameTypeLanShard) and _diplomacy_IsProposal(gArrDiplomacy[myPlIndex][plIndex].message) then
      [*] = ;            LanWithdrawal(plIndex);
      [*] = ;         
      [*] = ;         gArrDiplomacy[plIndex][myPlIndex].answer := 0;
      [*] = ;         gArrDiplomacy[myPlIndex][plIndex].message.deal := -3;
      [*] = ;         
      [*] = ;         // withdraw peace offer to the ally of the enemy as well
      [*] = ;         if gArrDiplomacy[myPlIndex][plIndex].message.treaty = gc_TreatyPeace then
      [*] = ;         begin
      [*] = ;            {IntRegister0 := myPlIndex;
      [*] = ;            IntRegister1 := plIndex;
      [*] = ;            BoolRegister0 := false;
      [*] = ;            ExecuteState('CheckUnionPeaceOffer');
      [*] = ;            var bUnionPeaceOffer : Boolean = BoolRegister1;
      [*] = ;            var queryAnotherPlayer : Boolean = BoolRegister2;
      [*] = ;            var unionRejection : Boolean = BoolRegister3;
      [*] = ;            var allyPlIndex : Integer = IntRegister0;
      [*] = ;            var enPlIndex : Integer = IntRegister1;}
      [*] = ;            var i : Integer;
      [*] = ;            for i := 0 to gGame.map.players-1 do
      [*] = ;            if (i <> myPlIndex) and (i <> plIndex) and (gArrDiplomacy[plIndex][i].treaty = gc_TreatyUnion) and (gArrDiplomacy[myPlIndex][i].message.treaty = gc_TreatyPeace) and (gArrDiplomacy[myPlIndex][i].message.deal = 0) then
      [*] = ;            begin
      [*] = ;               //bUnionPeaceOffer := true;
      [*] = ;            
      [*] = ;               _diplomacy_Escrow(myPlIndex, i, false);
      [*] = ;               if (gGame.gameType = gc_GameTypeLanShard) then
      [*] = ;                  LanWithdrawal(i);
      [*] = ;               
      [*] = ;               gArrDiplomacy[i][myPlIndex].answer := 0;
      [*] = ;               gArrDiplomacy[myPlIndex][i].message.deal := -3;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (tag>gc_gui_treasuryitemslots_btnBaseTag) and (tag<=maxItemsCount) then
      [*] = ;   begin
      [*] = ;      var itemID : Integer = tag-gc_gui_treasuryitemslots_btnBaseTag;
      [*] = ;      log('Diplomacy pressed itemID = ' + IntToStr(itemID));
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      case tag of
      [*] = ;         cInputBoxOfferGold, cInputBoxOfferGem, cInputBoxDemandGold, cInputBoxDemandGem, cInputBoxOfferGoldInc, cInputBoxOfferGemInc, cInputBoxDemandGold, cInputBoxDemandGem, cInputBoxDemandGoldInc, cInputBoxDemandGemInc:
      [*] = ;         begin
      [*] = ;         end;
      [*] = ;         cBtnInputBoxOfferGoldCancel:
      [*] = ;         begin
      [*] = ;            gDiplMessage.tradeGive.gold := 0;
      [*] = ;            SetInputBoxIntValue('offers', 'offergold', 0);
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cBtnInputBoxOfferGemCancel:
      [*] = ;         begin
      [*] = ;            gDiplMessage.tradeGive.gem := 0;
      [*] = ;            SetInputBoxIntValue('offers', 'offergem', 0);
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cBtnInputBoxDemandGoldCancel:
      [*] = ;         begin
      [*] = ;            gDiplMessage.tradeTake.gold := 0;
      [*] = ;            SetInputBoxIntValue('demand', 'demandgold', 0);
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cBtnInputBoxDemandGemCancel:
      [*] = ;         begin
      [*] = ;            gDiplMessage.tradeTake.gem := 0;
      [*] = ;            SetInputBoxIntValue('demand', 'demandgem', 0);
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         {cBtnInputBoxOfferGoldIncCancel:
      [*] = ;         begin
      [*] = ;            var inputHnd : Integer = GetGUIElementIndexByNameParent('diplomacy.dip_background.inputbox_GiveGoldinc.input', _gui_GetLayerI());
      [*] = ;            var value : Integer = StrToInt(GetGUIElementText(inputHnd));
      [*] = ;            gDiplMessage.tradeGive.gold := value;
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cBtnInputBoxOfferGemIncCancel:
      [*] = ;         begin
      [*] = ;            var inputHnd : Integer = GetGUIElementIndexByNameParent('diplomacy.dip_background.inputbox_GiveGeminc.input', _gui_GetLayerI());
      [*] = ;            var value : Integer = StrToInt(GetGUIElementText(inputHnd));
      [*] = ;            gDiplMessage.tradeGive.gem := value;
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cBtnInputBoxDemandGoldIncCancel:
      [*] = ;         begin
      [*] = ;            var inputHnd : Integer = GetGUIElementIndexByNameParent('diplomacy.dip_background.inputbox_Takegoldinc.input', _gui_GetLayerI());
      [*] = ;            var value : Integer = StrToInt(GetGUIElementText(inputHnd));
      [*] = ;            gDiplMessage.tradeTake.gold := value;
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cBtnInputBoxDemandGemIncCancel:
      [*] = ;         begin
      [*] = ;            var inputHnd : Integer = GetGUIElementIndexByNameParent('diplomacy.dip_background.inputbox_Takegeminc.input', _gui_GetLayerI());
      [*] = ;            var value : Integer = StrToInt(GetGUIElementText(inputHnd));
      [*] = ;            gDiplMessage.tradeTake.gem := value;
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;}
      [*] = ;         {cInputBoxOfferGold,cInputBoxOfferGem:
      [*] = ;         begin
      [*] = ;            var inputHnd : Integer = GetGUIElementIndexByNameParent('diplomacy.dip_background.inputbox_GiveGold.input', _gui_GetLayerI());
      [*] = ;            SetGUIElementFocusedHandle(inputHnd);
      [*] = ;            log(GetValueByName('Key'));
      [*] = ;            log(sStatus);
      [*] = ;
      [*] = ;            var keyTag : Integer = 0;
      [*] = ;            case sStatus of
      [*] = ;               'shortcut' : begin
      [*] = ;                  case GetValueByName('Key') of
      [*] = ;                     'escape' : keyTag := 1;
      [*] = ;                     'return' : if (sPress='u') then keyTag := GetGUIElementTag(inputParentHnd);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               'key' : begin
      [*] = ;                  case StrToInt(sTag) of
      [*] = ;                     cEscChar : keyTag := 1;
      [*] = ;                     cReturnChar : if (sPress='u') then keyTag := GetGUIElementTag(inputParentHnd);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               else
      [*] = ;               keyTag := 1;
      [*] = ;            end;
      [*] = ;            case (keyTag) of
      [*] = ;               1 : begin
      [*] = ;                  // Cancel
      [*] = ;                  SetGUIElementText(inputHnd, '');
      [*] = ;                  SetGUIElementTextFormatted(inputHnd, True);
      [*] = ;                  SetGUIEventStateOnKeyDown('');
      [*] = ;               end;
      [*] = ;               10 :
      [*] = ;               begin
      [*] = ;                  // Cheats
      [*] = ;                  var value : String = GetGUIElementText(inputHnd);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;}
      [*] = ;         cDeclareWarBtnTag:
      [*] = ;         begin
      [*] = ;            var timerPeace1 : Integer = gArrDiplomacy[myPlIndex][plIndex].arrTalk[2][1];
      [*] = ;            var timerPeace2 : Integer = gArrDiplomacy[plIndex][myPlIndex].arrTalk[2][1];
      [*] = ;            var timerGift : Integer = gArrDiplomacy[plIndex][myPlIndex].arrTalk[7][1];
      [*] = ;            var bAnswerGift : Boolean = (gArrDiplomacy[plIndex][myPlIndex].arrTalk[7][0]=1);
      [*] = ;            var bAnswerPeace1 : Boolean = (gArrDiplomacy[myPlIndex][plIndex].arrTalk[7][0]=1);
      [*] = ;            var bAnswerPeace2 : Boolean = (gArrDiplomacy[plIndex][myPlIndex].arrTalk[7][0]=1);
      [*] = ;            var durationPeace1 : Integer = gc_DipAgreementTimer-(gGame.currentTurn-timerPeace1);
      [*] = ;            var durationPeace2 : Integer = gc_DipAgreementTimer-(gGame.currentTurn-timerPeace2);
      [*] = ;            var durationGift : Integer = gc_DipAgreementTimer-(gGame.currentTurn-timerGift);
      [*] = ;            if ((timerPeace1>0) and (durationPeace1>0) and (durationPeace1<=gc_DipAgreementTimer))
      [*] = ;            or ((timerPeace2>0) and (durationPeace2>0) and (durationPeace2<=gc_DipAgreementTimer)) then
      [*] = ;            begin
      [*] = ;               gIntRegister_DiplomacyTurnLeft := Max(durationPeace1, durationPeace2);
      [*] = ;               StringRegister0 := IntToStr(gc_gui_query_diplRestrictWarFromPeace);
      [*] = ;               GUIExecuteState('map.RequestQueryWindow');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if (bAnswerGift) and (timerGift>0) and (durationGift>0) and (durationGift<=gc_DipAgreementTimer) then
      [*] = ;            begin
      [*] = ;               gIntRegister_DiplomacyTurnLeft := durationGift;
      [*] = ;               StringRegister0 := IntToStr(gc_gui_query_diplRestrictWarFromGift);
      [*] = ;               GUIExecuteState('map.RequestQueryWindow');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               _diplomacy_ClearMessage(gDiplMessage);
      [*] = ;               gDiplMessage.treaty := cDeclareWarBtnTag;
      [*] = ;               gDiplMessage.mType := gc_MessageTreaty;
      [*] = ;               gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;               ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;
      [*] = ;               if gProfile.mestutor and (gTutorial.war = 0) then
      [*] = ;               begin
      [*] = ;                  gTutorial.war := 1;
      [*] = ;                  IntRegister0 := 107;
      [*] = ;                  ExecuteState('ShowTutorial');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         cOfferPeaceBtnTag:
      [*] = ;         begin
      [*] = ;            gDiplMessage.treaty := cOfferPeaceBtnTag;
      [*] = ;            //gDiplMessage.mType := 1;
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;
      [*] = ;            if gProfile.mestutor and (gTutorial.peace = 0) then
      [*] = ;            begin
      [*] = ;               gTutorial.peace := 1;
      [*] = ;               IntRegister0 := 109;
      [*] = ;               ExecuteState('ShowTutorial');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         cOfferUnionBtnTag:
      [*] = ;         begin
      [*] = ;            var bUnionExist : Boolean = False;
      [*] = ;            var ind : Integer;
      [*] = ;            for ind:=0 to gGame.map.players-1 do
      [*] = ;            begin
      [*] = ;               var plHandle : Integer = GetPlayerHandleByIndex(ind);
      [*] = ;               var plProfileID : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;               if (plProfileID>0) and (_plr_IsInGame(plHandle)) then
      [*] = ;               begin
      [*] = ;                  bUnionExist := (gArrDiplomacy[myPlIndex][ind].treaty = gc_TreatyUnion);
      [*] = ;                  if (bUnionExist) then
      [*] = ;                     break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if (bUnionExist) then
      [*] = ;            begin
      [*] = ;               StringRegister0 := IntToStr(gc_gui_query_diplRestrictSecondUnion);
      [*] = ;               GUIExecuteState('map.RequestQueryWindow');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               gDiplMessage.treaty := cOfferUnionBtnTag;
      [*] = ;               //gDiplMessage.mType := 1;
      [*] = ;               gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;               ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;
      [*] = ;               if gProfile.mestutor and (gTutorial.union = 0) then
      [*] = ;               begin
      [*] = ;                  gTutorial.union := 1;
      [*] = ;                  IntRegister0 := 108;
      [*] = ;                  ExecuteState('ShowTutorial');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         cCancelUnionBtnTag:
      [*] = ;         begin
      [*] = ;            var timer : Integer = Max(gArrDiplomacy[myPlIndex][plIndex].arrTalk[3][1], gArrDiplomacy[plIndex][myPlIndex].arrTalk[3][1]);
      [*] = ;            var duration : Integer = gc_DipAgreementTimer-(gGame.currentTurn-timer);
      [*] = ;            if (timer>0) and (duration>0) and (duration<=gc_DipAgreementTimer) then
      [*] = ;            begin
      [*] = ;               gIntRegister_DiplomacyTurnLeft := duration;
      [*] = ;               StringRegister0 := IntToStr(gc_gui_query_diplRestrictCancelUnion);
      [*] = ;               GUIExecuteState('map.RequestQueryWindow');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               _diplomacy_ClearMessage(gDiplMessage);
      [*] = ;               gDiplMessage.treaty := cCancelUnionBtnTag;
      [*] = ;               //gDiplMessage.mType := 1;
      [*] = ;               gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;               ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         cCancelTradeBtnTag:
      [*] = ;         begin
      [*] = ;            var timer : Integer = Max(gArrDiplomacy[myPlIndex][plIndex].arrTalk[5][1], gArrDiplomacy[plIndex][myPlIndex].arrTalk[5][1]);
      [*] = ;            if (gArrDiplomacy[myPlIndex][plIndex].arrTalk[5][0] = 0) and (gArrDiplomacy[plIndex][myPlIndex].arrTalk[5][0] = 0) then
      [*] = ;            timer := 0;
      [*] = ;
      [*] = ;            var duration : Integer = gc_DipAgreementTimer-(gGame.currentTurn-timer);
      [*] = ;            if (timer>0) and (duration>0) and (duration<=gc_DipAgreementTimer) then
      [*] = ;            begin
      [*] = ;               gIntRegister_DiplomacyTurnLeft := duration;
      [*] = ;               StringRegister0 := IntToStr(gc_gui_query_diplRestrictCancelTrade);
      [*] = ;               GUIExecuteState('map.RequestQueryWindow');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               _diplomacy_ClearMessage(gDiplMessage);
      [*] = ;               gDiplMessage.mType := cCancelTradeMode;
      [*] = ;               gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;               ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         cOfferTradeBtnTag:
      [*] = ;         begin
      [*] = ;            var timer : Integer = Max(gArrDiplomacy[myPlIndex][plIndex].arrTalk[5][1], gArrDiplomacy[plIndex][myPlIndex].arrTalk[5][1]);
      [*] = ;            var bAnswer : Boolean = Max((gArrDiplomacy[myPlIndex][plIndex].arrTalk[5][0]), (gArrDiplomacy[plIndex][myPlIndex].arrTalk[5][0]))=1;
      [*] = ;            var duration : Integer = gc_DipAgreementTimer-(gGame.currentTurn-timer);
      [*] = ;            if (bAnswer) and (timer>0) and (duration>0) and (duration<=gc_DipAgreementTimer) then
      [*] = ;            begin
      [*] = ;               gIntRegister_DiplomacyTurnLeft := duration;
      [*] = ;               StringRegister0 := IntToStr(gc_gui_query_diplRestrictCancelTrade);
      [*] = ;               GUIExecuteState('map.RequestQueryWindow');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if gIntRegister_DiplomacyWindowMode < 3 then // when viewing a proposal, use it as a basis for editing. Otherwise use current trade agreement.
      [*] = ;               begin
      [*] = ;                  _diplomacy_AssignTrade(gDiplMessage.tradeGive, gArrDiplomacy[myPlIndex][plIndex].trade);
      [*] = ;                  _diplomacy_AssignTrade(gDiplMessage.tradeTake, gArrDiplomacy[plIndex][myPlIndex].trade);
      [*] = ;                  //_diplomacy_AssignMessage(gDiplMessage, gArrDiplomacy[sender][plIndex].message);
      [*] = ;                  
      [*] = ;                  //gDiplMessage.tradeGive.gold := gArrDiplomacy[myPlIndex][plIndex].trade.gold;
      [*] = ;                  //gDiplMessage.tradeGive.gem := gArrDiplomacy[myPlIndex][plIndex].trade.gem;
      [*] = ;                  //gDiplMessage.tradeTake.gold := gArrDiplomacy[plIndex][myPlIndex].trade.gold;
      [*] = ;                  //gDiplMessage.tradeTake.gem := gArrDiplomacy[plIndex][myPlIndex].trade.gem;
      [*] = ;               end;
      [*] = ;               gDiplMessage.mType := cTradeMode;
      [*] = ;               gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;               ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;            end;
      [*] = ;
      [*] = ;            if gProfile.mestutor and (gTutorial.dipTrade = 0) then
      [*] = ;            begin
      [*] = ;               gTutorial.dipTrade := 1;
      [*] = ;               IntRegister0 := 105;
      [*] = ;               ExecuteState('ShowTutorial');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         cOfferExchangeBtnTag:
      [*] = ;         begin
      [*] = ;            if gIntRegister_DiplomacyWindowMode < 3 then // when viewing a proposal, use it as a basis for editing. Otherwise zero.
      [*] = ;            begin
      [*] = ;               gDiplMessage.tradeGive.gold := 0;
      [*] = ;               gDiplMessage.tradeGive.gem := 0;
      [*] = ;               gDiplMessage.tradeTake.gold := 0;
      [*] = ;               gDiplMessage.tradeTake.gem := 0;
      [*] = ;            end;
      [*] = ;
      [*] = ;            gDiplMessage.mType := cExchangeMode;
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;
      [*] = ;            if gProfile.mestutor and (gTutorial.exchange = 0) then
      [*] = ;            begin
      [*] = ;               gTutorial.exchange := 1;
      [*] = ;               IntRegister0 := 103;
      [*] = ;               ExecuteState('ShowTutorial');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         cSendMessageBtnTag, gc_gui_hotkey_btnEnter:
      [*] = ;         begin
      [*] = ;            var elmBtnHandle : Integer = GetGUIElementIndexByNameParent('diplomacy.dip_background.btn_send_message', _gui_GetLayerI());
      [*] = ;               
      [*] = ;            if GetGUIElementVisible(elmBtnHandle) and GetGUIElementEnabled(elmBtnHandle) then
      [*] = ;            begin
      [*] = ;               _diplomacy_Escrow(myPlIndex, plIndex, false); // release escrow of previous message
      [*] = ;               
      [*] = ;               var queryID : String = '';
      [*] = ;               
      [*] = ;               if (gDiplMessage.mType = 0) and (gDiplMessage.treaty > 0) then
      [*] = ;                  gDiplMessage.mType := gc_MessageTreaty;
      [*] = ;
      [*] = ;               if (gDiplMessage.mType > 0) then
      [*] = ;               begin
      [*] = ;                  gDiplMessage.deal := 0;
      [*] = ;                  _diplomacy_AssignMessage(gArrDiplomacy[myPlIndex][plIndex].message, gDiplMessage);
      [*] = ;                  _diplomacy_ClearMessage(gArrDiplomacy[myPlIndex][plIndex].queryWindowMessage);
      [*] = ;                  _diplomacy_AssignMessage(gArrDiplomacy[myPlIndex][plIndex].queryWindowMessage, gDiplMessage);
      [*] = ;
      [*] = ;                  _diplomacy_Escrow(myPlIndex, plIndex, true);
      [*] = ;                  if (gGame.gameType = gc_GameTypeLanShard) and _diplomacy_IsProposal(gDiplMessage) then // messages that don't need an answer will be delivered to the other player at LanSync at the end of turn.
      [*] = ;                     SendLanProposal(plIndex);
      [*] = ;
      [*] = ;                  gArrDiplomacy[plIndex][myPlIndex].answer := 0;
      [*] = ;               
      [*] = ;                  // check if peace offer should be sent to ally of the enemy
      [*] = ;                  if gDiplMessage.treaty = gc_TreatyPeace then
      [*] = ;                  begin
      [*] = ;                     var i : Integer;
      [*] = ;                     for i := 0 to gGame.map.players-1 do
      [*] = ;                     if (gArrDiplomacy[i][plIndex].treaty = gc_TreatyUnion) and ((gArrDiplomacy[myPlIndex][i].message.treaty <> gc_TreatyPeace) or (gArrDiplomacy[myPlIndex][i].message.deal < 0))
      [*] = ;                      and (gArrDiplomacy[i][myPlIndex].message.treaty <> gc_TreatyPeace) and _plr_IsInGame(GetPlayerHandleByIndex(i)) then 
      [*] = ;                     begin
      [*] = ;                        gArrDiplomacy[myPlIndex][i].message.deal := 0;
      [*] = ;                        gArrDiplomacy[myPlIndex][i].message.treaty := gc_TreatyPeace;
      [*] = ;                        gArrDiplomacy[myPlIndex][i].message.mType := gc_MessageTreaty;
      [*] = ;                        gArrDiplomacy[i][myPlIndex].answer := 0;
      [*] = ;                        _diplomacy_AssignMessage(gArrDiplomacy[myPlIndex][i].queryWindowMessage, gArrDiplomacy[myPlIndex][i].message);
      [*] = ;
      [*] = ;                        if (gGame.gameType = gc_GameTypeLanShard) then
      [*] = ;                           SendLanProposal(i);
      [*] = ;                     end;
      [*] = ;                        
      [*] = ;                     IntRegister0 := myPlIndex;
      [*] = ;                     IntRegister1 := plIndex;
      [*] = ;                     BoolRegister0 := false;
      [*] = ;                     PlayerExecuteStateByHandle(myPlHandle, 'CheckUnionPeaceOffer');
      [*] = ;                     var isUnionOffer : Boolean = BoolRegister1;
      [*] = ;                     var queryAnotherPlayer : Boolean = BoolRegister2;
      [*] = ;                     if isUnionOffer and queryAnotherPlayer then
      [*] = ;                        queryID := IntToStr(gc_gui_query_diplUnionPeaceAlliesNotif);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               _diplomacy_ClearMessage(gDiplMessage);
      [*] = ;               gIntRegister_DiplomacyWindowMode := 1;
      [*] = ;               ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;               
      [*] = ;               if queryID <> '' then
      [*] = ;               begin
      [*] = ;                  StringRegister0 := queryID;
      [*] = ;                  GUIExecuteState('map.RequestQueryWindow');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         cClearMessageBtnTag:
      [*] = ;         begin
      [*] = ;            // withdraw sent message only if currently viewing it unmodified. Otherwise just clear the view.
      [*] = ;            if (gIntRegister_DiplomacyWindowMode = 3) then
      [*] = ;               WithdrawProposal();
      [*] = ;            
      [*] = ;            _diplomacy_ClearMessage(gDiplMessage);
      [*] = ;            gIntRegister_DiplomacyWindowMode := 1;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         //cEditMessageBtnTag:
      [*] = ;         //begin
      [*] = ;         //   _diplomacy_AssignMessage(gDiplMessage, gArrDiplomacy[myPlIndex][plIndex].message);
      [*] = ;         //   //_diplomacy_ClearMessage(gArrDiplomacy[sender][plIndex].message);
      [*] = ;         //   ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         //end;
      [*] = ;         cOfferResTag..cOfferResTag+gc_MaxTradeResCount:
      [*] = ;         begin
      [*] = ;            gDiplMessage.tradeGive.arrResources[tag - cOfferResTag] := not gDiplMessage.tradeGive.arrResources[tag - cOfferResTag];
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cDemandResTag..cDemandResTag+gc_MaxTradeResCount:
      [*] = ;         begin
      [*] = ;            gDiplMessage.tradeTake.arrResources[tag - cDemandResTag] := not gDiplMessage.tradeTake.arrResources[tag - cDemandResTag];
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cCancelTreatyTag:
      [*] = ;         begin
      [*] = ;            case gDiplMessage.treaty of
      [*] = ;               gc_TreatyWar : 
      [*] = ;               begin
      [*] = ;                  _diplomacy_ClearMessage(gDiplMessage);
      [*] = ;                  if (gArrDiplomacy[myPlIndex][plIndex].message.treaty = gc_TreatyWar) then // Cancel war declaration if already sent. This does not require server transfer since it is not a proposal and would simply be delivered to the other player after general diplomacy sync at the end of turn.
      [*] = ;                     _diplomacy_ClearMessage(gArrDiplomacy[myPlIndex][plIndex].message);
      [*] = ;                  
      [*] = ;                  gIntRegister_DiplomacyWindowMode := 1;
      [*] = ;               end;
      [*] = ;               gc_TreatyPeace :
      [*] = ;               begin
      [*] = ;                  _diplomacy_ClearMessage(gDiplMessage); // when at war, the peace offer is a requisite for any message so if it is deleted, the whole message must be cleared.
      [*] = ;               
      [*] = ;                  if (gIntRegister_DiplomacyWindowMode = 3) then // withdraw the already sent message
      [*] = ;                     WithdrawProposal();
      [*] = ;                  
      [*] = ;                  gIntRegister_DiplomacyWindowMode := 1;
      [*] = ;               end;
      [*] = ;               gc_TreatyUnion :
      [*] = ;               begin
      [*] = ;                  if (gDiplMessage.mType = gc_MessageTreaty) then // the message does not contain anything else than the union proposal. Clear the whole proposal.
      [*] = ;                  begin
      [*] = ;                     _diplomacy_ClearMessage(gDiplMessage);
      [*] = ;                     
      [*] = ;                     if (gIntRegister_DiplomacyWindowMode = 3) then // withdraw the already sent message
      [*] = ;                        WithdrawProposal();
      [*] = ;                     
      [*] = ;                     gIntRegister_DiplomacyWindowMode := 1;
      [*] = ;                  end
      [*] = ;                  else // just remove the union proposal and resume editing.
      [*] = ;                  begin
      [*] = ;                     gDiplMessage.treaty := 0;
      [*] = ;                     gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               gc_TreatyCancelUnion :
      [*] = ;               begin
      [*] = ;                  _diplomacy_ClearMessage(gDiplMessage);
      [*] = ;                  
      [*] = ;                  if (gArrDiplomacy[myPlIndex][plIndex].message.treaty = gc_TreatyCancelUnion) then //This does not require server transfer since it is not a proposal and would simply be delivered to the other player after general diplomacy sync at the end of turn.
      [*] = ;                     _diplomacy_ClearMessage(gArrDiplomacy[myPlIndex][plIndex].message);
      [*] = ;                  
      [*] = ;                  gIntRegister_DiplomacyWindowMode := 1;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cOfferGoldIncTag:
      [*] = ;         begin
      [*] = ;            var goldInc : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldInc);
      [*] = ;            if goldInc < 15 then
      [*] = ;               gDiplMessage.tradeGive.gold := goldInc
      [*] = ;            else
      [*] = ;               gDiplMessage.tradeGive.gold := 15;
      [*] = ;
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cOfferGemIncTag:
      [*] = ;         begin
      [*] = ;            var gemInc : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGemInc);
      [*] = ;            if gemInc < 3 then
      [*] = ;               gDiplMessage.tradeGive.gem := gemInc
      [*] = ;            else
      [*] = ;               gDiplMessage.tradeGive.gem := 3;
      [*] = ;
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cDemandGoldIncTag:
      [*] = ;         begin
      [*] = ;            gDiplMessage.tradeTake.gold := 15;
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cDemandGemIncTag:
      [*] = ;         begin
      [*] = ;            gDiplMessage.tradeTake.gem := 3;
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cOfferGoldTag:
      [*] = ;         begin
      [*] = ;            var gold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;            if gold < 150 then
      [*] = ;               gDiplMessage.tradeGive.gold := gold
      [*] = ;            else
      [*] = ;               gDiplMessage.tradeGive.gold := 150;
      [*] = ;
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cOfferGemTag:
      [*] = ;         begin
      [*] = ;            var gem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;            if gem < 30 then
      [*] = ;               gDiplMessage.tradeGive.gem := gem
      [*] = ;            else
      [*] = ;               gDiplMessage.tradeGive.gem := 30;
      [*] = ;
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cDemandGoldTag:
      [*] = ;         begin
      [*] = ;            gDiplMessage.tradeTake.gold := 150;
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cDemandGemTag:
      [*] = ;         begin
      [*] = ;            gDiplMessage.tradeTake.gem := 30;
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cShowMyMessage:
      [*] = ;         begin
      [*] = ;            _diplomacy_ClearMessage(gDiplMessage);
      [*] = ;            _diplomacy_AssignMessage(gDiplMessage, gArrDiplomacy[myPlIndex][plIndex].message); 
      [*] = ;            
      [*] = ;            gIntRegister_DiplomacyWindowMode := 3;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cShowTheirMessage:
      [*] = ;         begin
      [*] = ;            _diplomacy_ClearMessage(gDiplMessage);
      [*] = ;            _diplomacy_AssignMessage(gDiplMessage, gArrDiplomacy[plIndex][myPlIndex].message);
      [*] = ;            _diplomacy_AssignTrade(gDiplMessage.tradeTake, gArrDiplomacy[plIndex][myPlIndex].message.tradeGive);
      [*] = ;            _diplomacy_AssignTrade(gDiplMessage.tradeGive, gArrDiplomacy[plIndex][myPlIndex].message.tradeTake);
      [*] = ;            
      [*] = ;            gIntRegister_DiplomacyWindowMode := 4;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cHideMessage:
      [*] = ;         begin
      [*] = ;            _diplomacy_ClearMessage(gDiplMessage);
      [*] = ;            gIntRegister_DiplomacyWindowMode := 1;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cAcceptDeal:
      [*] = ;         begin
      [*] = ;            IntRegister0 := plIndex;
      [*] = ;            PlayerExecuteStateByHandle(myPlHandle, 'HumanAcceptDeal');
      [*] = ;         end;
      [*] = ;         cDeclineDeal:
      [*] = ;         begin
      [*] = ;            IntRegister0 := plIndex;
      [*] = ;            PlayerExecuteStateByHandle(myPlHandle, 'HumanCancelDeal');
      [*] = ;         end;
      [*] = ;         cPlayerTag..cOfferItemTag-1:
      [*] = ;         begin
      [*] = ;            if gIntRegister_DiplomacyActivePlayerID <> tag - cPlayerTag then
      [*] = ;            begin
      [*] = ;               _diplomacy_ClearMessage(gDiplMessage);
      [*] = ;               gIntRegister_DiplomacyActivePlayerID := tag - cPlayerTag;
      [*] = ;               plIndex := gIntRegister_DiplomacyActivePlayerID;
      [*] = ;               var plHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;            
      [*] = ;               // if they have accepted my proposal since last check
      [*] = ;               if ((gArrDiplomacy[plIndex][myPlIndex].displayPriority and $ff00) > 0) and (gArrDiplomacy[myPlIndex][plIndex].message.mType > 0) 
      [*] = ;                 and (gArrDiplomacy[myPlIndex][plIndex].message.deal > 0) and (gArrDiplomacy[plIndex][myPlIndex].answer = 2) then
      [*] = ;               begin
      [*] = ;                  _diplomacy_AssignMessage(gDiplMessage, gArrDiplomacy[myPlIndex][plIndex].message);
      [*] = ;                  _diplomacy_AssignTrade(gDiplMessage.tradeGive, gArrDiplomacy[myPlIndex][plIndex].message.tradeGive);
      [*] = ;                  _diplomacy_AssignTrade(gDiplMessage.tradeTake, gArrDiplomacy[myPlIndex][plIndex].message.tradeTake);
      [*] = ;                  gIntRegister_DiplomacyWindowMode := 3;
      [*] = ;               end
      [*] = ;               else // if they offer a proposal since last check
      [*] = ;               if ((gArrDiplomacy[plIndex][myPlIndex].displayPriority and $ff) > 0) and (gArrDiplomacy[plIndex][myPlIndex].message.mType > 0) 
      [*] = ;                 and (gArrDiplomacy[plIndex][myPlIndex].message.deal = 0) and (gArrDiplomacy[myPlIndex][plIndex].answer = 0) then
      [*] = ;               begin
      [*] = ;                  _diplomacy_AssignMessage(gDiplMessage, gArrDiplomacy[plIndex][myPlIndex].message);
      [*] = ;                  _diplomacy_AssignTrade(gDiplMessage.tradeTake, gArrDiplomacy[plIndex][myPlIndex].message.tradeGive);
      [*] = ;                  _diplomacy_AssignTrade(gDiplMessage.tradeGive, gArrDiplomacy[plIndex][myPlIndex].message.tradeTake);
      [*] = ;                  gIntRegister_DiplomacyWindowMode := 4;
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  gIntRegister_DiplomacyWindowMode := 1;
      [*] = ;               
      [*] = ;               ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         cOfferItemTag..cDemandItemTag-1:
      [*] = ;         begin
      [*] = ;            var i : Integer;
      [*] = ;            var slot : Integer = -1;
      [*] = ;
      [*] = ;            for i := 0 to gc_MaxTradeItemCount-1 do
      [*] = ;            if (gDiplMessage.tradeGive.arrItems[i][0] = 0) then
      [*] = ;            begin
      [*] = ;               slot:=i;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if (slot >= 0) then
      [*] = ;            begin
      [*] = ;               var index : Integer = tag - cOfferItemTag;
      [*] = ;               var pMyPlParser : Integer = ParserSelectPlayer(GetPlayerHandleInterfaceIO);
      [*] = ;               var pMyTreasury : Integer = ParserSelectByHandleByKey(pMyPlParser, 'Treasury');
      [*] = ;               var pTreasuryItem : Integer = ParserSelectByHandleByIndex(pMyTreasury, index);
      [*] = ;               
      [*] = ;               gDiplMessage.tradeGive.arrItems[slot][0] := ParserGetIntValueByKeyByHandle(pTreasuryItem, 'ItemID');
      [*] = ;               gDiplMessage.tradeGive.arrItems[slot][1] := ParserGetIntValueByKeyByHandle(pTreasuryItem, 'Durability');
      [*] = ;            end;
      [*] = ;
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cDemandItemTag..cCancelOfferItemTag-1:
      [*] = ;         begin
      [*] = ;            var i : Integer;
      [*] = ;            var slot : Integer = -1;
      [*] = ;
      [*] = ;            for i := 0 to gc_MaxTradeItemCount-1 do
      [*] = ;            if (gDiplMessage.tradeTake.arrItems[i][0] = 0) then
      [*] = ;            begin
      [*] = ;               slot := i;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if (slot>=0) then
      [*] = ;            begin
      [*] = ;               var index : Integer = tag - cDemandItemTag;
      [*] = ;               var plHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;               var pPlParser : Integer = ParserSelectPlayer(plHandle);
      [*] = ;               var pPlTreasury : Integer = ParserSelectByHandleByKey(pPlParser, 'Treasury');
      [*] = ;               var pTreasuryItem : Integer = ParserSelectByHandleByIndex(pPlTreasury, index);
      [*] = ;               
      [*] = ;               gDiplMessage.tradeTake.arrItems[slot][0] := ParserGetIntValueByKeyByHandle(pTreasuryItem, 'ItemID');
      [*] = ;               gDiplMessage.tradeTake.arrItems[slot][1] := ParserGetIntValueByKeyByHandle(pTreasuryItem, 'Durability');
      [*] = ;            end;
      [*] = ;
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cCancelOfferItemTag..cCancelDemandItemTag-1:
      [*] = ;         begin
      [*] = ;            var i : Integer;
      [*] = ;            var index : Integer = tag - cCancelOfferItemTag;
      [*] = ;            var pMyPlParser : Integer = ParserSelectPlayer(GetPlayerHandleInterfaceIO);
      [*] = ;            var pMyTreasury : Integer = ParserSelectByHandleByKey(pMyPlParser, 'Treasury');
      [*] = ;            var pTreasuryItem : Integer = ParserSelectByHandleByIndex(pMyTreasury, index);
      [*] = ;            var itemID : Integer = ParserGetIntValueByKeyByHandle(pTreasuryItem, 'ItemID');
      [*] = ;            var itemDur : Integer = ParserGetIntValueByKeyByHandle(pTreasuryItem, 'Durability');
      [*] = ;
      [*] = ;            for i := 0 to gc_MaxTradeItemCount-1 do
      [*] = ;            if (gDiplMessage.tradeGive.arrItems[i][0] = itemID) and (gDiplMessage.tradeGive.arrItems[i][1] = itemDur) then
      [*] = ;            begin
      [*] = ;               gDiplMessage.tradeGive.arrItems[i][0] := 0;
      [*] = ;               gDiplMessage.tradeGive.arrItems[i][1] := 0;
      [*] = ;               SortItemsArray(gDiplMessage.tradeGive);
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cCancelDemandItemTag..cOfferProvinceTag-1:
      [*] = ;         begin
      [*] = ;            var i : Integer;
      [*] = ;            var index : Integer = tag - cCancelDemandItemTag;
      [*] = ;            var plHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;            var pPlParser : Integer = ParserSelectPlayer(plHandle);
      [*] = ;            var pPlTreasury : Integer = ParserSelectByHandleByKey(pPlParser, 'Treasury');
      [*] = ;            var pTreasuryItem : Integer = ParserSelectByHandleByIndex(pPlTreasury, index);
      [*] = ;            var itemID : Integer = ParserGetIntValueByKeyByHandle(pTreasuryItem, 'ItemID');
      [*] = ;            var itemDur : Integer = ParserGetIntValueByKeyByHandle(pTreasuryItem, 'Durability');
      [*] = ;
      [*] = ;            for i := 0 to gc_MaxTradeItemCount-1 do
      [*] = ;            if (gDiplMessage.tradeTake.arrItems[i][0] = itemID) and (gDiplMessage.tradeTake.arrItems[i][1] = itemDur) then
      [*] = ;            begin
      [*] = ;               gDiplMessage.tradeTake.arrItems[i][0] := 0;
      [*] = ;               gDiplMessage.tradeTake.arrItems[i][1] := 0;
      [*] = ;               SortItemsArray(gDiplMessage.tradeTake);
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cOfferProvinceTag..cDemandProvinceTag-1 : begin
      [*] = ;            var provInd : Integer = tag-cOfferProvinceTag;
      [*] = ;            log('OfferProvince ind='+IntToStr(provInd));
      [*] = ;            var place : Integer = -1;
      [*] = ;            var pickedPlace : Integer = -1;
      [*] = ;            var i : Integer;
      [*] = ;
      [*] = ;            for i:=0 to gc_MaxTradeProvCount-1 do
      [*] = ;            begin
      [*] = ;               if (gDiplMessage.tradeGive.arrProvinces[i]=provInd) then
      [*] = ;               begin
      [*] = ;                  pickedPlace := i;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if (pickedPlace>-1) then
      [*] = ;            gDiplMessage.tradeGive.arrProvinces[pickedPlace] := -1
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               for i:=0 to gc_MaxTradeProvCount-1 do
      [*] = ;               begin
      [*] = ;                  if (gDiplMessage.tradeGive.arrProvinces[i]=-1) then
      [*] = ;                  begin
      [*] = ;                     place := i;
      [*] = ;                     break;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               if (place>-1) then
      [*] = ;               gDiplMessage.tradeGive.arrProvinces[place] := provInd;
      [*] = ;            end;
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cDemandProvinceTag..cEndTag-1 : begin
      [*] = ;            var provInd : Integer = tag-cDemandProvinceTag;
      [*] = ;            log('DemandProvince ind='+IntToStr(provInd));
      [*] = ;            var place : Integer = -1;
      [*] = ;            var pickedPlace : Integer = -1;
      [*] = ;            var i : Integer;
      [*] = ;
      [*] = ;            for i:=0 to gc_MaxTradeProvCount-1 do
      [*] = ;            begin
      [*] = ;               if (gDiplMessage.tradeTake.arrProvinces[i]=provInd) then
      [*] = ;               begin
      [*] = ;                  pickedPlace := i;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if (pickedPlace>-1) then
      [*] = ;            gDiplMessage.tradeTake.arrProvinces[pickedPlace] := -1
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               for i:=0 to gc_MaxTradeProvCount-1 do
      [*] = ;               begin
      [*] = ;                  if (gDiplMessage.tradeTake.arrProvinces[i]=-1) then
      [*] = ;                  begin
      [*] = ;                     place := i;
      [*] = ;                     break;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               if (place>-1) then
      [*] = ;               gDiplMessage.tradeTake.arrProvinces[place] := provInd;
      [*] = ;            end;
      [*] = ;            gIntRegister_DiplomacyWindowMode := 2;
      [*] = ;            ExecuteState('map.CreateDiplomacyWindow');
      [*] = ;         end;
      [*] = ;         cCloseBtnTag, gc_gui_hotkey_btnEscape :
      [*] = ;         begin
      [*] = ;            //if ((gDiplMessage.treaty=0) and (gDiplMessage.mType=0)) or (gIntRegister_DiplomacyWindowMode > 2) then
      [*] = ;            //begin
      [*] = ;               ExecuteState('map.CloseDiplomacyWindow');
      [*] = ;            //end
      [*] = ;            //else if gIntRegister_DiplomacyWindowMode = 2 then
      [*] = ;            //begin
      [*] = ;            //   gIntRegister_DiplomacyActivePlayerIDTemporary := -1;
      [*] = ;            //   StringRegister0 := IntToStr(gc_gui_query_diplUndeliveredMessage);
      [*] = ;            //   GUIExecuteState('map.RequestQueryWindow');
      [*] = ;            //end;
      [*] = ;         end;
      [*] = ;         cLogEvent1BtnTag : Log('Diplomacy Event1Btn Pressed');
      [*] = ;         cInputMinus :
      [*] = ;         begin
      [*] = ;            log('inputMinus');
      [*] = ;         end;
      [*] = ;         cInputPlus :
      [*] = ;         begin
      [*] = ;            log('inputPlus');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

