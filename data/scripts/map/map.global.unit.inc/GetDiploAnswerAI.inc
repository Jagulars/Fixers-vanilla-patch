section.begin
   Name = GetDiploAnswerAI
   Description : struct.begin
      [*] = ;IntRegister0 - writer player index
      [*] = ;OUT: IntRegister1 - answer
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\GETDIPLOANSWERAI';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = 
      [*] = ;var plIndex : Integer = IntRegister0;
      [*] = ;var plHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var myPlName : String = GetPlayerNameByHandle(myPlHandle);
	  [*] = ;var bImprovedAI : Boolean = gGame.improvedai or (gProfile.improvedai and (gGame.gameType <> gc_GameTypeLanShard));
      [*] = ;
      [*] = ;var gold : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGold);
      [*] = ;var gem : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGem);
      [*] = ;var goldInc : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGoldInc);
      [*] = ;var gemInc : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGemInc);
      [*] = ;var profile : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iProfile);
      [*] = ;
      [*] = ;function GetTradeProfit(cMessage : TDiplMessage) : Integer;
      [*] = ;begin
      [*] = ;   var gold : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGold);
      [*] = ;   var gem : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGem);
      [*] = ;   var goldInc : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGoldInc);
      [*] = ;   var gemInc : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGemInc);
      [*] = ;         
      [*] = ;   ExecuteState('GetGoldAndGemTaste');
      [*] = ;   var goldTaste : Float = FloatRegister0;
      [*] = ;   var gemTaste : Float = FloatRegister1;
      [*] = ;   
      [*] = ;   var i, j : Integer;
      [*] = ;   Result := 0;
      [*] = ;
      [*] = ;   case cMessage.mType of
      [*] = ;      gc_MessageTrade : begin
      [*] = ;         Result := Result + Round(cMessage.tradeGive.gold * goldTaste * 2);
      [*] = ;         Result := Result + Round(cMessage.tradeGive.gem * gemTaste * 5);
      [*] = ;         Result := Result - Round(cMessage.tradeTake.gold * goldTaste * 2);
      [*] = ;         Result := Result - Round(cMessage.tradeTake.gem * gemTaste * 5);
      [*] = ;
      [*] = ;         if goldInc < cMessage.tradeTake.gold * 2 then
      [*] = ;         Result := Result - 100;
      [*] = ;         if goldInc < cMessage.tradeTake.gold then
      [*] = ;         Result := Result - 10000;
      [*] = ;         if gemInc < cMessage.tradeTake.gem * 2 then
      [*] = ;         Result := Result - 100;
      [*] = ;         if gemInc < cMessage.tradeTake.gem then
      [*] = ;         Result := Result - 10000;
      [*] = ;
      [*] = ;         for i := 0 to gc_MaxTradeResCount-1 do
      [*] = ;         if cMessage.tradeGive.arrResources[i] then
      [*] = ;         begin
      [*] = ;            IntRegister0 := i+1;
      [*] = ;            ExecuteState('GetResCount');
      [*] = ;            if IntRegister1 <= 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := i+1;
      [*] = ;               MapExecuteState('map.GetResPriceValue');
      [*] = ;               Result := Result + IntRegister1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         for i := 0 to gc_MaxTradeResCount-1 do
      [*] = ;         if cMessage.tradeTake.arrResources[i] then
      [*] = ;         begin
      [*] = ;            IntRegister0 := i+1;
      [*] = ;            MapExecuteState('map.GetResPriceValue');
      [*] = ;            Result := Result - IntRegister1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      gc_MessageExchange : begin
      [*] = ;         Result := Result + Round(cMessage.tradeGive.gold * goldTaste / 2);
      [*] = ;         Result := Result + Round(cMessage.tradeGive.gem * gemTaste * 1.25);
      [*] = ;         Result := Result - Round(cMessage.tradeTake.gold * goldTaste / 2);
      [*] = ;         Result := Result - Round(cMessage.tradeTake.gem * gemTaste * 1.25);
      [*] = ;
      [*] = ;         if gold < cMessage.tradeTake.gold * 2 then
      [*] = ;         Result := Result - 100;
      [*] = ;         if gold < cMessage.tradeTake.gold then
      [*] = ;         Result := Result - 10000;
      [*] = ;         if gem < cMessage.tradeTake.gem * 2 then
      [*] = ;         Result := Result - 100;
      [*] = ;         if gem < cMessage.tradeTake.gem then
      [*] = ;         Result := Result - 10000;
      [*] = ;
      [*] = ;         var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;
      [*] = ;         for i := 0 to gc_MaxTradeProvCount-1 do
      [*] = ;         if cMessage.tradeGive.arrProvinces[i] >= 0 then
      [*] = ;         begin
      [*] = ;            var provInd : Integer = cMessage.tradeGive.arrProvinces[i];
      [*] = ;            var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, provInd);
      [*] = ;            var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;            var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;            IntRegister0 := 3;
      [*] = ;            IntRegister1 := -1;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'GetGoldAndGemIncomeExt');
      [*] = ;            Result := Result + 2 * IntRegister0;
      [*] = ;            Result := Result + 5 * IntRegister1;
      [*] = ;
      [*] = ;            IntRegister0 := 1;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'GetResource');
      [*] = ;            var res : Integer = IntRegister1;
      [*] = ;
      [*] = ;            if res > 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := res;
      [*] = ;               ExecuteState('GetResCount');
      [*] = ;               if IntRegister1 <= 0 then
      [*] = ;               Result := Result + 50
      [*] = ;               else
      [*] = ;               Result := Result + 15;
      [*] = ;            end;
      [*] = ;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'IsGarrison');
      [*] = ;            if BoolRegister0 then
      [*] = ;            Result := Result + 20;
      [*] = ;
      [*] = ;            var pProvDefender : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;            var defID : Integer = ParserGetIntValueByKeyByHandle(pProvDefender, 'DefenderID');
      [*] = ;            if defID > 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := defID;
      [*] = ;               MapExecuteState('GetDefenderPowerByID');
      [*] = ;               Result := Result + IntRegister1 div 100;
      [*] = ;            end;
      [*] = ;
      [*] = ;            for j := 0 to 5 do
      [*] = ;            begin
      [*] = ;               IntRegister0 := pProvince;
      [*] = ;               IntRegister1 := j;
      [*] = ;               MapExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;               var pNProvince : Integer = IntRegister2;
      [*] = ;               var provPlName : String = ParserGetValueByKeyByHandle(pNProvince, 'Player');
      [*] = ;
      [*] = ;               if SameText(provPlName, myPlName) then
      [*] = ;               begin
      [*] = ;                  var isCastle : Boolean = ParserGetBoolValueByKeyByHandle(pNProvince, 'Castle');
      [*] = ;                  if isCastle then
      [*] = ;                  Result := Result + 30
      [*] = ;                  else
      [*] = ;                  Result := Result + 7;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         for i := 0 to gc_MaxTradeProvCount-1 do
      [*] = ;         if cMessage.tradeTake.arrProvinces[i] >= 0 then
      [*] = ;         begin
      [*] = ;            var provInd : Integer = cMessage.tradeTake.arrProvinces[i];
      [*] = ;            var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, provInd);
      [*] = ;            var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;            var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;            Result := Result - gGame.currentTurn * 3;
      [*] = ;            IntRegister0 := 3;
      [*] = ;            IntRegister1 := -1;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'GetGoldAndGemIncomeExt');
      [*] = ;            Result := Result - 20 * IntRegister0;
      [*] = ;            Result := Result - 40 * IntRegister1;
      [*] = ;
      [*] = ;            IntRegister0 := 1;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'GetResource');
      [*] = ;            if IntRegister1 > 0 then
      [*] = ;            Result := Result - 500;
      [*] = ;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'IsGarrison');
      [*] = ;            if BoolRegister0 then
      [*] = ;            Result := Result - 500;
      [*] = ;
      [*] = ;            var pProvDefender : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;            var defID : Integer = ParserGetIntValueByKeyByHandle(pProvDefender, 'DefenderID');
      [*] = ;            if defID > 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := defID;
      [*] = ;               MapExecuteState('GetDefenderPowerByID');
      [*] = ;               Result := Result - IntRegister1 div 20;
      [*] = ;            end;
      [*] = ;
      [*] = ;            for j := 0 to 5 do
      [*] = ;            begin
      [*] = ;               IntRegister0 := pProvince;
      [*] = ;               IntRegister1 := j;
      [*] = ;               MapExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;               var pNProvince : Integer = IntRegister2;
      [*] = ;               var provPlName : String = ParserGetValueByKeyByHandle(pNProvince, 'Player');
      [*] = ;
      [*] = ;               if SameText(provPlName, myPlName) then
      [*] = ;               begin
      [*] = ;                  var isCastle : Boolean = ParserGetBoolValueByKeyByHandle(pNProvince, 'Castle');
      [*] = ;                  if isCastle then
      [*] = ;                  Result := Result - 500
      [*] = ;                  else
      [*] = ;                  Result := Result - 200;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         for i := 0 to gc_MaxTradeItemCount-1 do
      [*] = ;         if cMessage.TradeGive.arrItems[i][0] > 0 then
      [*] = ;         begin
      [*] = ;            var itemID : Integer = cMessage.TradeGive.arrItems[i][0];
      [*] = ;            var pItem : Integer = ParserSelectByHandleByIndex(gPrototypeData.items.handle, itemID);
      [*] = ;            var goldCost : Integer = ParserGetIntValueByKeyByHandle(pItem, 'GoldCost');
      [*] = ;            var gemCost : Integer = ParserGetIntValueByKeyByHandle(pItem, 'GemCost');
      [*] = ;
      [*] = ;            IntRegister0 := itemID;
      [*] = ;            ExecuteState('CanSellItem');
      [*] = ;            if BoolRegister0 then
      [*] = ;            Result := Result + (goldCost + 2 * gemCost) div 4
      [*] = ;            else
      [*] = ;            Result := Result + goldCost + 2 * gemCost;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function CheckUnionPeaceOffer(bRefused : Boolean) : Boolean;
      [*] = ;begin
      [*] = ;   IntRegister0 := plIndex;
      [*] = ;   IntRegister1 := myPlIndex;
      [*] = ;   BoolRegister0 := bRefused;
      [*] = ;   ExecuteState('CheckUnionPeaceOffer');
      [*] = ;   Result := BoolRegister1;
      [*] = ;   var queryAnotherPlayer : Boolean = BoolRegister2;
      [*] = ;   var unionRejection : Boolean= BoolRegister3;
      [*] = ;   var allyPlIndex : Integer = IntRegister0;
      [*] = ;   var enPlIndex : Integer = IntRegister1;
      [*] = ;      
      [*] = ;   var i : Integer;
      [*] = ;   if Result and bRefused then
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;   if (i <> myPlIndex) and (i <> plIndex) then
      [*] = ;   begin
      [*] = ;      var tmpPlHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;         
      [*] = ;      if _plr_IsInGame(tmpPlHandle) and (gArrDiplomacy[i][plIndex].treaty = gc_TreatyUnion) and (gArrDiplomacy[i][myPlIndex].treaty = gc_TreatyWar) 
      [*] = ;         and (gArrDiplomacy[i][myPlIndex].message.treaty <> gc_TreatyPeace) and (gArrDiplomacy[myPlIndex][i].message.treaty <> gc_TreatyPeace) then
      [*] = ;      begin
      [*] = ;         gArrDiplomacy[myPlIndex][i].message.treaty := gc_TreatyPeace;
      [*] = ;         gArrDiplomacy[myPlIndex][i].message.mType := gc_MessageTreaty;
      [*] = ;         gArrDiplomacy[myPlIndex][i].message.deal := -3;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;      
      [*] = ;   if bRefused and (allyPlIndex >= 0) and (enPlIndex >= 0) and ((gGame.gameType <> gc_GameTypeLanShard) or (allyPlIndex = gIntRegister_MapMyPlayerIndex)) then
      [*] = ;   begin
      [*] = ;      var allyPlHandle : Integer = GetPlayerHandleByIndex(allyPlIndex);
      [*] = ;      
      [*] = ;      if SameText(GetPlayerControlModeByHandle(allyPlHandle), 'cmPlayer') then
      [*] = ;      begin
      [*] = ;         _misc_PlMakeDiplomacyText(myPlIndex, allyPlIndex, 28, 0); // ally refuse peace
      [*] = ;         var queryID : String = gArrDiplomacy[myPlIndex][allyPlIndex].message.text;
      [*] = ;         if queryID <> '' then
      [*] = ;         begin
      [*] = ;            var pQuery : Integer = ParserAddChildByIndex(ParserSelectByHandleByKey(ParserSelectPlayer(allyPlHandle), 'Queries'), '*');
      [*] = ;         
      [*] = ;            ParserSetBoolValueByKeyByHandle(pQuery, 'Priority', true);
      [*] = ;            ParserSetValueByKeyByHandle(pQuery, 'QueryID', queryID);
      [*] = ;            ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex', myPlIndex);
      [*] = ;            ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex1', enPlIndex);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pQuery, 'Diplomacy', true);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pQuery, 'Informative', true);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   _diplomacy_AssignMessage(gArrDiplomacy[plIndex][myPlIndex].queryWindowMessage, gArrDiplomacy[plIndex][myPlIndex].message);
      [*] = ;   
      [*] = ;   if Result and (not queryAnotherPlayer) then
      [*] = ;   begin
      [*] = ;      if unionRejection then
      [*] = ;      begin
      [*] = ;         IntRegister0 := plIndex;
      [*] = ;         IntRegister1 := myPlIndex;
      [*] = ;         ExecuteState('DeleteUnionPeaceOffers');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         IntRegister0 := plIndex;
      [*] = ;         IntRegister1 := myPlIndex;
      [*] = ;         ExecuteState('ExecuteUnionPeace');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetPositiveResponse(power, attitude : Integer) : Integer;
      [*] = ;begin
      [*] = ;   if power < 0 then
      [*] = ;   begin
      [*] = ;      Result := 1;
      [*] = ;      gArrDiplomacy[myPlIndex][plIndex].attitude := gArrDiplomacy[myPlIndex][plIndex].attitude - 1;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if power < 100 then
      [*] = ;         Result := 2
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         Result := 3;
      [*] = ;         var value : Integer = Min(3, (power - 80) div 20);
      [*] = ;         gArrDiplomacy[myPlIndex][plIndex].attitude := gArrDiplomacy[myPlIndex][plIndex].attitude + value;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   if bImprovedAI then // response text should depend on attitude and not just benefit
      [*] = ;   begin
      [*] = ;      if (power + attitude > 80) then
      [*] = ;         Result := 3
      [*] = ;      else
      [*] = ;      if (power + attitude > 20) then
      [*] = ;         Result := 2
      [*] = ;      else
      [*] = ;         Result := 1;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetNegativeResponse(power, attitude : Integer) : Integer;
      [*] = ;begin
      [*] = ;   if power < -50 then
      [*] = ;   begin
      [*] = ;      Result := -3;
      [*] = ;      gArrDiplomacy[myPlIndex][plIndex].attitude := gArrDiplomacy[myPlIndex][plIndex].attitude - 1;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if ((power < 50) and (gArrDiplomacy[plIndex][myPlIndex].message.treaty <> gc_TreatyPeace)) or ((power < 0) and (gArrDiplomacy[plIndex][myPlIndex].message.treaty = gc_TreatyPeace)) then
      [*] = ;         Result := -2
      [*] = ;      else
      [*] = ;         Result := -1;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   if bImprovedAI then // response text should depend on attitude and not just benefit
      [*] = ;   begin
      [*] = ;      if (power + attitude < -40) then
      [*] = ;         Result := -3
      [*] = ;      else
      [*] = ;      if (power + attitude < 20) then
      [*] = ;         Result := -2
      [*] = ;      else
      [*] = ;         Result := -1;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var pProfiles : Integer = gPrototypeData.players.handle;
      [*] = ;
      [*] = ;var myPlProfile : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iProfile);
      [*] = ;var pProfile : Integer = ParserSelectByHandleByIndex(pProfiles, myPlProfile);
      [*] = ;var profDiplTimer : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'DiplomacyTimer');
      [*] = ;var profAggro : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'Aggro');
      [*] = ;var profGreed : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'Greed');
      [*] = ;var profSensitivity : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'Sensitivity');
      [*] = ;var profRandom : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'Random');
      [*] = ;
      [*] = ;if (not bImprovedAI) then
      [*] = ;begin
      [*] = ;   profGreed := 0;
      [*] = ;   profRandom := 0;
      [*] = ;   profSensitivity := 100;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[MyIndex: '+IntToStr(myPlIndex)+', ProposePlayer: '+IntToStr(plIndex)+', Profile: '+IntToStr(myPlProfile)+']',_log_trace);
      [*] = ;
      [*] = ;IntRegister0 := plIndex;
      [*] = ;ExecuteState('GetAttitude');
      [*] = ;var attitude : Integer = IntRegister1;
      [*] = ;
      [*] = ;var curTurn : Integer = gGame.currentTurn;
      [*] = ;
      [*] = ;var mType : Integer = gArrDiplomacy[myPlIndex][plIndex].message.mType;
      [*] = ;var mTreaty : Integer = gArrDiplomacy[myPlIndex][plIndex].message.treaty;
      [*] = ;var i : Integer;
      [*] = ;var res : Integer = 0;
      [*] = ;var power : Integer = 0;
      [*] = ;
      [*] = ;if mType > 0 then
      [*] = ;begin
      [*] = ;   if (mTreaty = gc_TreatyWar) or ((mType = gc_TreatyCancelUnion) and gArrDiplomacy[myPlIndex][plIndex].message.tradeGive.trade) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := plIndex;
      [*] = ;      ExecuteState('CancelDeal');
      [*] = ;      IntRegister1 := 0;
      [*] = ;      _gv_traceState(_log_name+'[Accept: '+BoolToStr(false)+', Result: '+IntToStr(IntRegister1)+']',$1000000 or _log_trace);
      [*] = ;      exit;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;MapExecuteState('map.GetActivePlayers');
      [*] = ;if IntRegister0 = 2 then
      [*] = ;begin
      [*] = ;   IntRegister0 := plIndex;
      [*] = ;   ExecuteState('CancelDeal');
      [*] = ;   IntRegister1 := 19;
      [*] = ;    _gv_traceState(_log_name+'[Accept: '+BoolToStr(false)+', Result: '+IntToStr(IntRegister1)+']',$1000000 or _log_trace);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;var bWarJustStarted : Boolean = false;
      [*] = ;if (gArrDiplomacy[myPlIndex][plIndex].treaty = gc_TreatyWar) and ((curTurn - gArrDiplomacy[myPlIndex][plIndex].arrTalk[gc_TreatyWar][1] < profDiplTimer) or
      [*] = ;(curTurn - gArrDiplomacy[plIndex][myPlIndex].arrTalk[gc_TreatyWar][1] < profDiplTimer)) then
      [*] = ;begin
      [*] = ;   bWarJustStarted := true;
      [*] = ;end;
      [*] = ;
      [*] = ;mType := gArrDiplomacy[plIndex][myPlIndex].message.mType;
      [*] = ;mTreaty := gArrDiplomacy[plIndex][myPlIndex].message.treaty;
      [*] = ;_log_Map('Message Type: '+IntToStr(mType)+', Message Treaty: '+IntToStr(mTreaty));
      [*] = ;
      [*] = ;var randomFactor : Integer = 0;
      [*] = ;if profRandom > 0 then
      [*] = ;begin
      [*] = ;   randomFactor := gArrDiplomacy[myPlIndex][plIndex].random;
      [*] = ;end;
      [*] = ;
      [*] = ;if (not bWarJustStarted) and ((mType = gc_MessageTrade) or (mType = gc_MessageExchange)) then
      [*] = ;begin
      [*] = ;   var profit : Integer = GetTradeProfit(gArrDiplomacy[plIndex][myPlIndex].message);
      [*] = ;   _log_Map('Offer Profit '+IntToStr(profit)); 
      [*] = ;   power := power + profit;
      [*] = ;   if mTreaty = 0 then
      [*] = ;   begin
      [*] = ;      if _diplomacy_IsTradeFree(gArrDiplomacy[plIndex][myPlIndex].message.tradeTake) then // gift
      [*] = ;      begin
      [*] = ;         var giftExpectation : Integer = curTurn + 20 + profGreed; // gifts have to better later in the game
      [*] = ;         _log_Map('Gift Expectation '+IntToStr(giftExpectation)); 
      [*] = ;         power := power - giftExpectation;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if _diplomacy_IsTradeFree(gArrDiplomacy[plIndex][myPlIndex].message.tradeGive) then // demand
      [*] = ;      begin
      [*] = ;         IntRegister0 := plIndex;
      [*] = ;         ExecuteState('GetPoliticalPower');
      [*] = ;         var demandPower : Integer = 6 * IntRegister1;
      [*] = ;         
      [*] = ;         demandPower := demandPower - profAggro div 5 - profGreed;
      [*] = ;
      [*] = ;         if gArrDiplomacy[myPlIndex][plIndex].canKill > 0 then
      [*] = ;            demandPower := demandPower - 5 * gArrDiplomacy[myPlIndex][plIndex].canKill;
      [*] = ;
      [*] = ;         _log_Map('Demand Power '+IntToStr(demandPower)+', CanKill: '+IntToStr(gArrDiplomacy[myPlIndex][plIndex].canKill)); 
      [*] = ;         power := power + demandPower;
      [*] = ;         gArrDiplomacy[myPlIndex][plIndex].attitude := gArrDiplomacy[myPlIndex][plIndex].attitude - 2;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (power - profGreed >= 0) or (profGreed > 0) then
      [*] = ;      power := power - profGreed;
      [*] = ;end;
      [*] = ;
      [*] = ;if (not bWarJustStarted) and ((mTreaty = gc_TreatyPeace) or (mTreaty = gc_TreatyUnion)) then
      [*] = ;begin
      [*] = ;   power := power div 2; // halve the weight of the possible goods offered when treaty offer is included
      [*] = ;   IntRegister0 := plIndex;
      [*] = ;   ExecuteState('GetPoliticalPower');
      [*] = ;   power := power + IntRegister1 * 2;
      [*] = ;end;
      [*] = ;
      [*] = ;power := power + randomFactor;
      [*] = ;
      [*] = ;_log_Map('Power '+IntToStr(power)+', Attitude '+IntToStr(attitude)+', Random factor '+IntToStr(randomFactor)); 
      [*] = ;
      [*] = ;case mTreaty of
      [*] = ;   gc_TreatyPeace : begin
      [*] = ;      power := power - gArrDiplomacy[myPlIndex][plIndex].canKill;
      [*] = ;      power := power - profAggro div 3;
      [*] = ;
      [*] = ;      var bTraitor : Boolean = false;
      [*] = ;
      [*] = ;      if (profSensitivity > 0) then
      [*] = ;      begin
      [*] = ;         if gArrDiplomacy[myPlIndex][plIndex].arrTraitor[0] > 0 then // attacks without declaration of war
      [*] = ;         begin
      [*] = ;            power := power - 500 * profSensitivity div 100;
      [*] = ;            bTraitor := true;
      [*] = ;         end;
      [*] = ;         if gArrDiplomacy[myPlIndex][plIndex].arrTraitor[1] > 0 then // attack on ally
      [*] = ;         begin
      [*] = ;            power := power - 1000 * profSensitivity div 100;
      [*] = ;            bTraitor := true;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var combAtt : Integer = attitude; // need this to preserve "attitude" in case of merging of allies
      [*] = ;      var peacePower1 : Integer = power + attitude;
      [*] = ;      _log_Map('Peace Treaty Power '+IntToStr(peacePower1)+', CanKill: '+IntToStr(gArrDiplomacy[myPlIndex][plIndex].canKill)); 
      [*] = ;      
      [*] = ;      // check if I want peace with the ally of the player who's proposing peace
      [*] = ;      for i := 0 to gGame.map.players-1 do
      [*] = ;      if (i <> myPlIndex) and (i <> plIndex) then
      [*] = ;      begin
      [*] = ;         var tmpPlHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;         
      [*] = ;         if _plr_IsInGame(tmpPlHandle) and (gArrDiplomacy[i][plIndex].treaty = gc_TreatyUnion) and (gArrDiplomacy[i][myPlIndex].treaty = gc_TreatyWar) then
      [*] = ;         begin
      [*] = ;            var bWarJustStarted2 : Boolean = (curTurn - gArrDiplomacy[myPlIndex][i].arrTalk[gc_TreatyWar][1] < profDiplTimer) or (curTurn - gArrDiplomacy[i][myPlIndex].arrTalk[gc_TreatyWar][1] < profDiplTimer);
      [*] = ;            var peacePower2 : Integer = 0;
      [*] = ;               
      [*] = ;            IntRegister0 := i;
      [*] = ;            ExecuteState('GetAttitude');
      [*] = ;            var attitude2 : Integer = IntRegister1;
      [*] = ;               
      [*] = ;            if bImprovedAI and (not bWarJustStarted2) then
      [*] = ;            begin
      [*] = ;               var randomFactor2 : Integer = 0;
      [*] = ;               if profRandom > 0 then
      [*] = ;                  randomFactor2 := gArrDiplomacy[myPlIndex][i].random;
      [*] = ;               
      [*] = ;               IntRegister0 := i;
      [*] = ;               ExecuteState('GetPoliticalPower');
      [*] = ;               var polPower : Integer = IntRegister1;
      [*] = ;                  
      [*] = ;               peacePower2 := polPower + attitude2 + randomFactor2 - profAggro div 3 - gArrDiplomacy[myPlIndex][i].canKill;
      [*] = ;                  
      [*] = ;               if (profSensitivity > 0) then
      [*] = ;               begin
      [*] = ;                  if gArrDiplomacy[myPlIndex][i].arrTraitor[0] > 0 then // attacks without declaration of war
      [*] = ;                     peacePower2 := peacePower2 - 500 * profSensitivity div 100;
      [*] = ;                     
      [*] = ;                  if gArrDiplomacy[myPlIndex][i].arrTraitor[1] > 0 then // attack on ally
      [*] = ;                     peacePower2 := peacePower2 - 1000 * profSensitivity div 100;
      [*] = ;               end;
      [*] = ;                  
      [*] = ;               _log_Map('GetDiploAnswerAI EnemyAllyIndex('+IntToStr(i)+') Peace Power: '+IntToStr(peacePower2));
      [*] = ;               power := (peacePower1 - attitude + peacePower2 - attitude2) div 2; // merge peace preferences, exclude attitudes from power
      [*] = ;               combAtt := (attitude + attitude2) div 2;
      [*] = ;            end;
      [*] = ;            
      [*] = ;            // send a message to the enemy ally if they have not sent me individually
      [*] = ;            if ((gArrDiplomacy[i][myPlIndex].message.treaty <> gc_TreatyPeace) or (gArrDiplomacy[i][myPlIndex].message.deal < 0)) and (gArrDiplomacy[myPlIndex][i].message.treaty <> gc_TreatyPeace) then
      [*] = ;            begin
      [*] = ;               if bWarJustStarted2 then
      [*] = ;               begin
      [*] = ;                  _log_Map('GetDiploAnswerAI not ready for peace to ally: ' +IntToStr(i));
      [*] = ;                  gArrDiplomacy[myPlIndex][i].message.treaty := gc_TreatyPeace;
      [*] = ;                  gArrDiplomacy[myPlIndex][i].message.mType := gc_MessageTreaty;
      [*] = ;                  gArrDiplomacy[myPlIndex][i].message.deal := -3;
      [*] = ;                
      [*] = ;                  //IntRegister0 := plIndex;
      [*] = ;                  //ExecuteState('CancelDeal');
      [*] = ;                  //IntRegister1 := 1000+i;
      [*] = ;                  //exit;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  var bAgreePeace : Boolean;
      [*] = ;               
      [*] = ;                  if bImprovedAI then
      [*] = ;                     bAgreePeace := ((peacePower1 + peacePower2) div 2 > 0) or (peacePower2 > 0)
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     var war : Integer = profAggro div 2 + 40 - attitude2;
      [*] = ;                     bAgreePeace := (war <= 10) or (_rand_Random(war) <= 10);
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if not bAgreePeace then
      [*] = ;                  begin
      [*] = ;                     _log_Map('GetDiploAnswerAI refuse peace to ally: ' +IntToStr(i));
      [*] = ;                     gArrDiplomacy[myPlIndex][i].message.treaty := gc_TreatyPeace;
      [*] = ;                     gArrDiplomacy[myPlIndex][i].message.mType := gc_MessageTreaty;
      [*] = ;                     gArrDiplomacy[myPlIndex][i].message.deal := -3;
      [*] = ;                     gArrDiplomacy[myPlIndex][i].arrTalk[gc_TreatyPeace][1] := curTurn;
      [*] = ;                     gArrDiplomacy[i][myPlIndex].arrTalk[gc_TreatyPeace][1] := curTurn;
      [*] = ;                  
      [*] = ;                     //IntRegister0 := plIndex;
      [*] = ;                     //ExecuteState('CancelDeal');
      [*] = ;                     //IntRegister1 := 1000+i;
      [*] = ;                     //exit;
      [*] = ;                  end
      [*] = ;                  else // send peace offer to ally of the proposer when I agree to peace
      [*] = ;                  begin
      [*] = ;                     _log_Map('GetDiploAnswerAI offer peace to ally: ' +IntToStr(i));
      [*] = ;                     gArrDiplomacy[myPlIndex][i].message.treaty := gc_TreatyPeace;
      [*] = ;                     gArrDiplomacy[myPlIndex][i].message.mType := gc_MessageTreaty;
      [*] = ;                  
      [*] = ;                     if ((gGame.gameType <> gc_GameTypeLanShard) or (i = gIntRegister_MapMyPlayerIndex)) and SameText(GetPlayerControlModeByHandle(tmpPlHandle), 'cmPlayer') then
      [*] = ;                        _diplomacy_AssignMessage(gArrDiplomacy[myPlIndex][i].queryWindowMessage, gArrDiplomacy[myPlIndex][i].message);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      
      [*] = ;      if bWarJustStarted then
      [*] = ;      begin
      [*] = ;         gArrDiplomacy[plIndex][myPlIndex].message.deal := -1;
      [*] = ;         if (not CheckUnionPeaceOffer(true)) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := plIndex;
      [*] = ;            ExecuteState('CancelDeal');
      [*] = ;         end;
      [*] = ;         IntRegister1 := 23;
      [*] = ;         _gv_traceState(_log_name+'[Accept: '+BoolToStr(false)+', Result: '+IntToStr(IntRegister1)+']',$1000000 or _log_trace);
      [*] = ;         exit;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (peacePower1 > 0) or (power + combAtt > 0) then // send acceptance reply if want peace with this enemy or if want peace with its ally so much.
      [*] = ;      begin
      [*] = ;         res := GetPositiveResponse(power, attitude);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if bTraitor then
      [*] = ;         begin
      [*] = ;            gArrDiplomacy[plIndex][myPlIndex].message.deal := -1;
      [*] = ;            if (mTreaty <> gc_TreatyPeace) or (not CheckUnionPeaceOffer(true)) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := plIndex;
      [*] = ;               ExecuteState('CancelDeal');
      [*] = ;            end;
      [*] = ;            IntRegister1 := 17;
      [*] = ;            _gv_traceState(_log_name+'[Accept: '+BoolToStr(false)+', Result: '+IntToStr(IntRegister1)+']',$1000000 or _log_trace);
      [*] = ;            exit;
      [*] = ;         end;
      [*] = ;         res := GetNegativeResponse(power, attitude);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   gc_TreatyUnion : begin
      [*] = ;      var bTraitor : Boolean = false;
      [*] = ;
      [*] = ;      if (profSensitivity > 0) then
      [*] = ;      begin
      [*] = ;         if gArrDiplomacy[myPlIndex][plIndex].arrTraitor[0] > 0 then // attacks without declaration of war
      [*] = ;         begin
      [*] = ;            power := power - 1300 * profSensitivity div 100;
      [*] = ;            bTraitor := true;
      [*] = ;         end;
      [*] = ;         if gArrDiplomacy[myPlIndex][plIndex].arrTraitor[1] > 0 then // attack on ally
      [*] = ;         begin
      [*] = ;            power := power - 2500 * profSensitivity div 100;
      [*] = ;            bTraitor := true;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      ExecuteState('GetUnionCount');
      [*] = ;      var myUnion : Integer = IntRegister0;
      [*] = ;      PlayerExecuteStateByHandle(plHandle, 'GetUnionCount');
      [*] = ;      var plUnion : Integer = IntRegister0;
      [*] = ;
      [*] = ;      _log_Map('Union Treaty Power '+IntToStr(power)); 
      [*] = ;      if (power + attitude div 2 > 100) and (attitude >= 30) and (myUnion = 0) and (plUnion = 0) then
      [*] = ;      begin
      [*] = ;         res := GetPositiveResponse(power, attitude);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if bTraitor then
      [*] = ;         begin
      [*] = ;            IntRegister0 := plIndex;
      [*] = ;            ExecuteState('CancelDeal');
      [*] = ;            IntRegister1 := 16;
      [*] = ;            _gv_traceState(_log_name+'[Accept: '+BoolToStr(false)+', Result: '+IntToStr(IntRegister1)+']',$1000000 or _log_trace);
      [*] = ;            exit;
      [*] = ;         end;
      [*] = ;         res := GetNegativeResponse(power, attitude);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   0 : begin
      [*] = ;      _log_Map('No Treaty Offer Power '+IntToStr(power)); 
      [*] = ;      if power + attitude div 10 > 5 then
      [*] = ;      begin
      [*] = ;         res := GetPositiveResponse(power, attitude);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         res := GetNegativeResponse(power, attitude);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var bProposal : Boolean = _diplomacy_IsProposal(gArrDiplomacy[plIndex][myPlIndex].message);
      [*] = ;if not bProposal then
      [*] = ;   res := 0;
      [*] = ;
      [*] = ;if (mTreaty = gc_TreatyCancelUnion) and (gGame.gameType = gc_GameTypeCampaign) and (profile = 3) and (plIndex = 0) and (gCampaign.arrDialogs[103] > 0) then // Beleth angry if you cancel alliance
      [*] = ;begin
      [*] = ;   gArrDiplomacy[myPlIndex][plIndex].attitude := gArrDiplomacy[myPlIndex][plIndex].attitude - 400;
      [*] = ;   gCampaign.arrCampPlayers[3].treaty := 0;
      [*] = ;   gCampaign.arrDialogs[103] := 0;
      [*] = ;   gCampaign.arrDialogs[104] := 2;
      [*] = ;   res := 32;
      [*] = ;end;
      [*] = ;
      [*] = ;// check response to a gift
      [*] = ;if (mType = gc_MessageTrade) or (mType = gc_MessageExchange) then
      [*] = ;begin
      [*] = ;   if res > 0 then
      [*] = ;   begin
      [*] = ;      if _diplomacy_IsTradeFree(gArrDiplomacy[plIndex][myPlIndex].message.tradeTake) then
      [*] = ;      begin
      [*] = ;         var min : Integer = Min(2, 1 + power div 30);
      [*] = ;         gArrDiplomacy[myPlIndex][plIndex].attitude := gArrDiplomacy[myPlIndex][plIndex].attitude + min;
      [*] = ;         if mTreaty = 0 then
      [*] = ;         begin
      [*] = ;            gArrDiplomacy[plIndex][myPlIndex].arrTalk[7][1] := curTurn;
      [*] = ;            gArrDiplomacy[plIndex][myPlIndex].arrTalk[7][0] := 1;
      [*] = ;
      [*] = ;            IntRegister0 := plIndex;
      [*] = ;            ExecuteState('AcceptDeal');
      [*] = ;            IntRegister1 := 25;
      [*] = ;            _gv_traceState(_log_name+'[Accept: '+BoolToStr(true)+', Result: '+IntToStr(IntRegister1)+']',$1000000 or _log_trace);
      [*] = ;            exit;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if _diplomacy_IsTradeFree(gArrDiplomacy[plIndex][myPlIndex].message.tradeTake) and (mTreaty = 0) then
      [*] = ;      begin
      [*] = ;         gArrDiplomacy[myPlIndex][plIndex].attitude := gArrDiplomacy[myPlIndex][plIndex].attitude - 1;
      [*] = ;         IntRegister0 := plIndex;
      [*] = ;         ExecuteState('CancelDeal');
      [*] = ;         IntRegister1 := 24;
      [*] = ;         _gv_traceState(_log_name+'[Accept: '+BoolToStr(false)+', Result: '+IntToStr(IntRegister1)+']',$1000000 or _log_trace);
      [*] = ;         exit;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if mTreaty = gc_TreatyWar then
      [*] = ;begin
      [*] = ;   gArrDiplomacy[myPlIndex][plIndex].attitude := gArrDiplomacy[myPlIndex][plIndex].attitude - 5;
      [*] = ;   res := 27;
      [*] = ;end;
      [*] = ;
      [*] = ;if mTreaty = gc_TreatyCancelUnion then
      [*] = ;   gArrDiplomacy[myPlIndex][plIndex].attitude := gArrDiplomacy[myPlIndex][plIndex].attitude - 2;
      [*] = ;
      [*] = ;if mType = gc_MessageCancelTrade then
      [*] = ;   gArrDiplomacy[myPlIndex][plIndex].attitude := gArrDiplomacy[myPlIndex][plIndex].attitude - 1;
      [*] = ;
      [*] = ;if res >= 0 then
      [*] = ;   gArrDiplomacy[plIndex][myPlIndex].message.deal := 1
      [*] = ;else
      [*] = ;   gArrDiplomacy[plIndex][myPlIndex].message.deal := -1;
      [*] = ;   
      [*] = ;// release the escrow of my offer because only one sealed deal between two players per turn (should not be any message here though)
      [*] = ;_diplomacy_Escrow(myPlIndex, plIndex, false);
      [*] = ;
      [*] = ;// in case of delayed processing, store an escrow that can't be used until deal is resolved.
      [*] = ;_diplomacy_Escrow(plIndex, myPlIndex, true);
      [*] = ;
      [*] = ;if (mTreaty <> gc_TreatyPeace) or (not CheckUnionPeaceOffer(res < 0)) then
      [*] = ;begin
      [*] = ;   if res >= 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := plIndex;
      [*] = ;      ExecuteState('AcceptDeal');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      IntRegister0 := plIndex;
      [*] = ;      ExecuteState('CancelDeal');
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if res < 0 then  // ensure AI players don't keep bombarding peace offers
      [*] = ;   begin
      [*] = ;      IntRegister0 := plIndex;
      [*] = ;      IntRegister1 := 0;
      [*] = ;      ExecuteState('MessageEntry');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister1 := res;
      [*] = ;_gv_traceState(_log_name+'[Accept: '+BoolToStr(res > 0)+', Result: '+IntToStr(IntRegister1)+']',$1000000 or _log_trace);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

