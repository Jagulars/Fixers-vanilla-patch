section.begin
   Name = AcceptDeal
   Description[*] = ;IntRegister0 - sender player index
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\ACCEPTDEAL';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var plIndex : Integer = IntRegister0;
      [*] = ;var plHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;var plName : String = GetPlayerNameByIndex(plIndex);
      [*] = ;var pPlParser : Integer = ParserSelectPlayer(plHandle);
      [*] = ;var pPlTreasury : Integer = ParserSelectByHandleByKey(pPlParser, 'Treasury');
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var myPlName : String = GetPlayerNameByHandle(myPlHandle);
      [*] = ;var pMyParser : Integer = ParserSelectPlayer(myPlHandle);
      [*] = ;var pMyTreasury : Integer = ParserSelectByHandleByKey(pMyParser, 'Treasury');
      [*] = ;
      [*] = ;var bUpdateMyStats : Boolean = _stats_IsEligible(myPlHandle);
      [*] = ;var bUpdatePlStats : Boolean = _stats_IsEligible(plHandle);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[MyIndex: '+IntToStr(myPlIndex)+', ProposePlayer: '+IntToStr(plIndex)+']',_log_trace);
      [*] = ;
      [*] = ;IntRegister0 := plIndex;
      [*] = ;IntRegister1 := 1;
      [*] = ;ExecuteState('MessageEntry');
      [*] = ;
      [*] = ;var mTreaty : Integer = gArrDiplomacy[plIndex][myPlIndex].message.treaty;
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;
      [*] = ;if mTreaty > 0 then
      [*] = ;begin
      [*] = ;   // Send treaty announcement to other players who know the players in question. War announcement is made from DeclareWar
      [*] = ;   if mTreaty > 1 then
      [*] = ;   begin
      [*] = ;      procedure SendAnnouncement(plHnd : Integer);
      [*] = ;      begin
      [*] = ;         if mTreaty = gc_TreatyPeace then
      [*] = ;         begin
      [*] = ;            // Check that not a union war. Otherwise the announcement will be sent from ExecuteUnionPeace.
      [*] = ;            var isUnionPeaceOffer : Boolean = false;
      [*] = ;            var i : Integer;
      [*] = ;            for i := 0 to gGame.map.players-1 do
      [*] = ;            if (gArrDiplomacy[i][plIndex].treaty = gc_TreatyUnion) or (gArrDiplomacy[i][myPlIndex].treaty = gc_TreatyUnion) then 
      [*] = ;            begin
      [*] = ;               isUnionPeaceOffer := true;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;            if not isUnionPeaceOffer then
      [*] = ;            begin
      [*] = ;               var pQuery : Integer = ParserAddChildByIndex(ParserSelectByHandleByKey(ParserSelectPlayer(plHnd), 'Queries'), '*');
      [*] = ;               ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', gc_gui_query_diplPeaceSigned);
      [*] = ;                        
      [*] = ;               PlayerExecuteStateByHandle(plHandle, 'GetName');
      [*] = ;               var playersList : String = gc_gui_BreakLine + gc_gui_BreakLine + StringRegister0;
      [*] = ;               PlayerExecuteStateByHandle(myPlHandle, 'GetName');
      [*] = ;               playersList := playersList + gc_gui_BreakLine + StringRegister0;
      [*] = ;                        
      [*] = ;               ParserSetValueByKeyByHandle(pQuery, 'gStringRegister_PlayersList', playersList);
      [*] = ;               ParserSetBoolValueByKeyByHandle(pQuery, 'Diplomacy', true);
      [*] = ;               ParserSetBoolValueByKeyByHandle(pQuery, 'Informative', true);
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if (mTreaty = gc_TreatyUnion) or (mTreaty = gc_TreatyCancelUnion) then
      [*] = ;         begin
      [*] = ;            var pQuery : Integer = ParserAddChildByIndex(ParserSelectByHandleByKey(ParserSelectPlayer(plHnd), 'Queries'), '*');
      [*] = ;            if (mTreaty = gc_TreatyUnion) then
      [*] = ;               ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', gc_gui_query_diplNewUnion)
      [*] = ;            else
      [*] = ;               ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', gc_gui_query_diplUnionBroken);
      [*] = ;            ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex', plIndex);
      [*] = ;            ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex1', myPlIndex);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pQuery, 'Diplomacy', true);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pQuery, 'Informative', true);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;         
      [*] = ;      if (gGame.gameType = gc_GameTypeHotseat) then
      [*] = ;      begin
      [*] = ;         var plHnd : Integer;
      [*] = ;         for i := 0 to gGame.map.players-1 do
      [*] = ;         if (i <> myPlIndex) and (i <> plIndex) then
      [*] = ;         begin
      [*] = ;            plHnd := GetPlayerHandleByIndex(i);
      [*] = ;            if _plr_IsInGame(plHnd) and SameText(GetPlayerControlModeByHandle(plHnd), 'cmPlayer') and (gArrDiplomacy[i][plIndex].treaty > 0) and (gArrDiplomacy[i][myPlIndex].treaty > 0) then
      [*] = ;               SendAnnouncement(plHnd);
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (gIntRegister_MapMyPlayerIndex <> plIndex) and (gIntRegister_MapMyPlayerIndex <> myPlIndex) and (gArrDiplomacy[gIntRegister_MapMyPlayerIndex][plIndex].treaty > 0) and (gArrDiplomacy[gIntRegister_MapMyPlayerIndex][myPlIndex].treaty > 0) then
      [*] = ;         SendAnnouncement(GetPlayerHandleByIndex(gIntRegister_MapMyPlayerIndex));
      [*] = ;   end;
      [*] = ;
      [*] = ;   if mTreaty = gc_TreatyCancelUnion then
      [*] = ;   begin
      [*] = ;      gArrDiplomacy[plIndex][myPlIndex].message.treaty := gc_TreatyPeace;
      [*] = ;      mTreaty := gc_TreatyPeace;
      [*] = ;   end;
      [*] = ;   gArrDiplomacy[myPlIndex][plIndex].treaty := mTreaty;
      [*] = ;   gArrDiplomacy[plIndex][myPlIndex].treaty := mTreaty;
      [*] = ;   gArrDiplomacy[myPlIndex][plIndex].arrTalk[mTreaty][0] := 1;
      [*] = ;   gArrDiplomacy[myPlIndex][plIndex].arrTalk[mTreaty][1] := gGame.currentTurn;
      [*] = ;
      [*] = ;   if mTreaty = gc_TreatyWar then
      [*] = ;   begin
      [*] = ;      IntRegister0 := plIndex;
      [*] = ;      ExecuteState('DeclareWar');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// release escrow that was stored to be used in this deal
      [*] = ;_diplomacy_Escrow(plIndex, myPlIndex, false);
      [*] = ;
      [*] = ;var mType : Integer = gArrDiplomacy[plIndex][myPlIndex].message.mType;
      [*] = ;case mType of
      [*] = ;   gc_MessageTrade : begin
      [*] = ;      _diplomacy_AssignTrade(gArrDiplomacy[myPlIndex][plIndex].trade, gArrDiplomacy[plIndex][myPlIndex].message.tradeTake);
      [*] = ;      gArrDiplomacy[myPlIndex][plIndex].trade.trade := true;
      [*] = ;
      [*] = ;      _diplomacy_AssignTrade(gArrDiplomacy[plIndex][myPlIndex].trade, gArrDiplomacy[plIndex][myPlIndex].message.tradeGive);
      [*] = ;      gArrDiplomacy[plIndex][myPlIndex].trade.trade := true;
      [*] = ;      gArrDiplomacy[plIndex][myPlIndex].arrTalk[5][0] := 1;
      [*] = ;   end;
      [*] = ;   gc_MessageExchange : begin
      [*] = ;      var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;      var plGem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;      var takeGold : Integer = gArrDiplomacy[plIndex][myPlIndex].message.tradeTake.gold;
      [*] = ;      var giveGold : Integer = gArrDiplomacy[plIndex][myPlIndex].message.tradeGive.gold;
      [*] = ;      var takeGem : Integer = gArrDiplomacy[plIndex][myPlIndex].message.tradeTake.gem;
      [*] = ;      var giveGem : Integer = gArrDiplomacy[plIndex][myPlIndex].message.tradeGive.gem;
      [*] = ;         
      [*] = ;      plGold := plGold + takeGold;
      [*] = ;      plGold := plGold - giveGold;
      [*] = ;      plGem := plGem + takeGem;
      [*] = ;      plGem := plGem - giveGem;
      [*] = ;      SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold, plGold);
      [*] = ;      SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem, plGem);
      [*] = ;
      [*] = ;      var myGold : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGold);
      [*] = ;      var myGem : Integer = GetIntValueByIndex(gc_map_PLStack_MapUnit_iGem);
      [*] = ;      myGold := myGold - takeGold;
      [*] = ;      myGold := myGold + giveGold;
      [*] = ;      myGem := myGem - takeGem;
      [*] = ;      myGem := myGem + giveGem;
      [*] = ;      SetIntValueByIndex(gc_map_PLStack_MapUnit_iGold, myGold);
      [*] = ;      SetIntValueByIndex(gc_map_PLStack_MapUnit_iGem, myGem);
      [*] = ;
      [*] = ;      plGold := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGoldGain);
      [*] = ;      SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGoldGain, plGold + takeGold);
      [*] = ;
      [*] = ;      plGem := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGemGain);
      [*] = ;      SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGemGain, plGem + takeGem);
      [*] = ;
      [*] = ;      myGold := GetIntValueByIndex(gc_map_PLStack_MapUnit_iGoldGain);
      [*] = ;      SetIntValueByIndex(gc_map_PLStack_MapUnit_iGoldGain, myGold + giveGold);
      [*] = ;
      [*] = ;      myGem := GetIntValueByIndex(gc_map_PLStack_MapUnit_iGemGain);
      [*] = ;      SetIntValueByIndex(gc_map_PLStack_MapUnit_iGemGain, myGem + giveGem);
      [*] = ;
      [*] = ;      if bUpdatePlStats then
      [*] = ;      begin
      [*] = ;         _stats_SimpleUpdate('Diplomacy', 'ExchangeGainGold', takeGold);
      [*] = ;         _stats_SimpleUpdate('Diplomacy', 'ExchangeGainGem', takeGem);
      [*] = ;         _stats_SimpleUpdate('Diplomacy', 'ExchangeGiveGold', giveGold);
      [*] = ;         _stats_SimpleUpdate('Diplomacy', 'ExchangeGiveGem', giveGem);
      [*] = ;      end;
      [*] = ;      
      [*] = ;      if bUpdateMyStats then
      [*] = ;      begin
      [*] = ;         _stats_SimpleUpdate('Diplomacy', 'ExchangeGainGold', giveGold);
      [*] = ;         _stats_SimpleUpdate('Diplomacy', 'ExchangeGainGem', giveGem);
      [*] = ;         _stats_SimpleUpdate('Diplomacy', 'ExchangeGiveGold', takeGold);
      [*] = ;         _stats_SimpleUpdate('Diplomacy', 'ExchangeGiveGem', takeGem);
      [*] = ;      end;
      [*] = ;
      [*] = ;      for i := 0 to gc_MaxTradeProvCount-1 do
      [*] = ;      begin
      [*] = ;         var provInd : Integer = gArrDiplomacy[plIndex][myPlIndex].message.tradeGive.arrProvinces[i];
      [*] = ;         if provInd >= 0 then
      [*] = ;         begin
      [*] = ;            var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, provInd);
      [*] = ;            var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;            var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;            IntRegister0 := myPlHandle;
      [*] = ;            BoolRegister0 := true;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'CaptureProvince');
      [*] = ;
      [*] = ;            if bUpdateMyStats then _stats_SimpleUpdate('Diplomacy', 'ExchangeProvincesGained', 1);
      [*] = ;            if bUpdatePlStats then _stats_SimpleUpdate('Diplomacy', 'ExchangeProvincesGiven', 1);
      [*] = ;         end;
      [*] = ;
      [*] = ;         provInd := gArrDiplomacy[plIndex][myPlIndex].message.tradeTake.arrProvinces[i];
      [*] = ;         if provInd >= 0 then
      [*] = ;         begin
      [*] = ;            var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, provInd);
      [*] = ;            var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;            var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;            IntRegister0 := plHandle;
      [*] = ;            BoolRegister0 := true;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'CaptureProvince');
      [*] = ;
      [*] = ;            if bUpdateMyStats then _stats_SimpleUpdate('Diplomacy', 'ExchangeProvincesGiven', 1);
      [*] = ;            if bUpdatePlStats then _stats_SimpleUpdate('Diplomacy', 'ExchangeProvincesGained', 1);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      for i := 0 to gc_MaxTradeItemCount-1 do
      [*] = ;      begin
      [*] = ;         var itemID : Integer = gArrDiplomacy[plIndex][myPlIndex].message.tradeGive.arrItems[i][0];
      [*] = ;         var itemDur : Integer = gArrDiplomacy[plIndex][myPlIndex].message.tradeGive.arrItems[i][1];
      [*] = ;
      [*] = ;         if itemID > 0 then
      [*] = ;         begin
      [*] = ;            var pItem : Integer = ParserSelectByHandleByIndex(gPrototypeData.items.handle, itemID);
      [*] = ;                  
      [*] = ;            IntRegister0 := itemID;
      [*] = ;            IntRegister1 := itemDur;
      [*] = ;            PlayerExecuteStateByHandle(plHandle, 'FindTreasuryItem');
      [*] = ;            var ind : Integer = IntRegister2;
      [*] = ;
      [*] = ;            if ind >= 0 then
      [*] = ;            begin
      [*] = ;               var pTreasuryItem : Integer = ParserSelectByHandleByIndex(pPlTreasury, ind);
      [*] = ;               var itemID : Integer = ParserGetIntValueByKeyByHandle(pTreasuryItem, 'ItemID');
      [*] = ;               var itemDur : Integer = ParserGetIntValueByKeyByHandle(pTreasuryItem, 'Durability');
      [*] = ;
      [*] = ;               IntRegister0 := itemID;
      [*] = ;               IntRegister1 := itemDur;
      [*] = ;               ExecuteState('AddTreasuryItem');
      [*] = ;               if BoolRegister0 then
      [*] = ;               begin
      [*] = ;                  ParserSetIntValueByKeyByHandle(pTreasuryItem, 'ItemID', 0);
      [*] = ;                  
      [*] = ;                  ParserSetIntValueByKeyByHandle(pTreasuryItem, 'Durability', 0);
      [*] = ;                  {if bUpdateMyStats then
      [*] = ;                  begin
      [*] = ;                     _stats_SubCategoryUpdate('Diplomacy', 'ExchangeItems', 'ItemsGainedLevel_'+IntToStr(ParserGetIntValueByKeyByHandle(pItem, 'ShopLevel')), 1);
      [*] = ;                     _stats_SubCategoryUpdate('Diplomacy', 'ExchangeItems', 'ItemsGainedRarity_'+IntToStr(ParserGetIntValueByKeyByHandle(pItem, 'Rarity')), 1);
      [*] = ;                  end;
      [*] = ;                  if bUpdatePlStats then 
      [*] = ;                  begin
      [*] = ;                     _stats_SubCategoryUpdate('Diplomacy', 'ExchangeItems', 'ItemsGivenLevel_'+IntToStr(ParserGetIntValueByKeyByHandle(pItem, 'ShopLevel')), 1);
      [*] = ;                     _stats_SubCategoryUpdate('Diplomacy', 'ExchangeItems', 'ItemsGivenRarity_'+IntToStr(ParserGetIntValueByKeyByHandle(pItem, 'Rarity')), 1);
      [*] = ;                  end;}
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         itemID := gArrDiplomacy[plIndex][myPlIndex].message.tradeTake.arrItems[i][0];
      [*] = ;         itemDur := gArrDiplomacy[plIndex][myPlIndex].message.tradeTake.arrItems[i][1];
      [*] = ;         if itemID > 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := itemID;
      [*] = ;            IntRegister1 := itemDur;
      [*] = ;            ExecuteState('FindTreasuryItem');
      [*] = ;            var ind : Integer = IntRegister2;
      [*] = ;
      [*] = ;            if ind >= 0 then
      [*] = ;            begin
      [*] = ;               var pTreasuryItem : Integer = ParserSelectByHandleByIndex(pMyTreasury, ind);
      [*] = ;               var itemID : Integer = ParserGetIntValueByKeyByHandle(pTreasuryItem, 'ItemID');
      [*] = ;               var itemDur : Integer = ParserGetIntValueByKeyByHandle(pTreasuryItem, 'Durability');
      [*] = ;
      [*] = ;               IntRegister0 := itemID;
      [*] = ;               IntRegister1 := itemDur;
      [*] = ;               PlayerExecuteStateByHandle(plHandle, 'AddTreasuryItem');
      [*] = ;               if BoolRegister0 then
      [*] = ;               begin
      [*] = ;                  ParserSetIntValueByKeyByHandle(pTreasuryItem, 'ItemID', 0);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pTreasuryItem, 'Durability', 0);
      [*] = ;                  
      [*] = ;                  {if bUpdateMyStats then
      [*] = ;                  begin
      [*] = ;                     _stats_SubCategoryUpdate('Diplomacy', 'ExchangeItems', 'ItemsGivenLevel_'+IntToStr(ParserGetIntValueByKeyByHandle(pItem, 'ShopLevel')), 1);
      [*] = ;                     _stats_SubCategoryUpdate('Diplomacy', 'ExchangeItems', 'ItemsGivenRarity_'+IntToStr(ParserGetIntValueByKeyByHandle(pItem, 'Rarity')), 1);
      [*] = ;                  end;
      [*] = ;                  if bUpdatePlStats then 
      [*] = ;                  begin
      [*] = ;                     _stats_SubCategoryUpdate('Diplomacy', 'ExchangeItems', 'ItemsGainedLevel_'+IntToStr(ParserGetIntValueByKeyByHandle(pItem, 'ShopLevel')), 1);
      [*] = ;                     _stats_SubCategoryUpdate('Diplomacy', 'ExchangeItems', 'ItemsGainedRarity_'+IntToStr(ParserGetIntValueByKeyByHandle(pItem, 'Rarity')), 1);
      [*] = ;                  end;}
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   gc_MessageCancelTrade : begin
      [*] = ;      _diplomacy_ClearTrade(gArrDiplomacy[plIndex][myPlIndex].trade);
      [*] = ;      _diplomacy_ClearTrade(gArrDiplomacy[myPlIndex][plIndex].trade);
      [*] = ;   end;
      [*] = ;   gc_MessageThrowDice : begin
      [*] = ;      StringRegister0 := '11187';
      [*] = ;      GUIExecuteState('map.RequestQueryWindow');
      [*] = ;   end;
      [*] = ;   gc_MessageDemandSurrender : begin
      [*] = ;      // defeat
      [*] = ;      gArrDiplomacy[plIndex][myPlIndex].attitude := gArrDiplomacy[plIndex][myPlIndex].attitude + 10;
      [*] = ;      ExecuteState('PlayerLose');
      [*] = ;   end;
      [*] = ;   gc_MessageSurrender : begin
      [*] = ;      // win
      [*] = ;      ExecuteState('PlayerWin');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if gArrDiplomacy[myPlIndex][plIndex].treaty > 1 then
      [*] = ;begin
      [*] = ;   IntRegister0 := plIndex;
      [*] = ;   ExecuteState('ReturnHeroes');
      [*] = ;
      [*] = ;   IntRegister0 := myPlIndex;
      [*] = ;   PlayerExecuteStateByHandle(plHandle, 'ReturnHeroes');
      [*] = ;end;
      [*] = ;
      [*] = ;if _diplomacy_IsProposal(gArrDiplomacy[plIndex][myPlIndex].message) then
      [*] = ;begin
      [*] = ;   _diplomacy_AssignMessage(gArrDiplomacy[plIndex][myPlIndex].queryWindowMessage, gArrDiplomacy[plIndex][myPlIndex].message);
      [*] = ;
      [*] = ;   if (gGame.improvedai or (gProfile.improvedai and (gGame.gameType <> gc_GameTypeLanShard))) then
      [*] = ;   begin
      [*] = ;      if SameText(GetPlayerControlModeByHandle(plHandle), 'cmPC') then
      [*] = ;      begin
      [*] = ;         var plProfile : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;         if plProfile > 0 then
      [*] = ;         begin
      [*] = ;            var profRandom : Integer = ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(gPrototypeData.players.handle, plProfile), 'Random');
      [*] = ;            _diplomacy_SwitchRandom(plIndex, myPlIndex, profRandom);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   
      [*] = ;      if SameText(GetPlayerControlModeByHandle(myPlHandle), 'cmPC') then
      [*] = ;      begin
      [*] = ;         var myProfile : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;         if myProfile > 0 then
      [*] = ;         begin
      [*] = ;            var profRandom : Integer = ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(gPrototypeData.players.handle, myProfile), 'Random');
      [*] = ;            _diplomacy_SwitchRandom(myPlIndex, plIndex, profRandom);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_diplomacy_ClearMessage(gArrDiplomacy[plIndex][myPlIndex].message);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

