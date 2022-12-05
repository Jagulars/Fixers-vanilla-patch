section.begin
   Name = map.EndTurn
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\MAP\MAP.ENDTURN';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var i, j, k : Integer;
      [*] = ;var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;
      [*] = ;var myIndex : Integer = gIntRegister_MapMyPlayerIndex;
      [*] = ;var myPlHandle : Integer = GetPlayerHandleByIndex(myIndex);
      [*] = ;
      [*] = ;if not _plr_IsInGame(myPlHandle) then
      [*] = ;   exit;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[Turn: '+IntToStr(gGame.currentTurn)+']',_log_trace);
      [*] = ;// network game autosave and forced save
      [*] = ;if (gGame.gameType = gc_GameTypeLanShard) and (gIntRegister_LanMapUID <> 0) and (gStringRegister_LanMapSaveName <> '') then
      [*] = ;begin
      [*] = ;   StringRegister0 := gStringRegister_LanMapSaveName;
      [*] = ;   if gStringRegister_LanMapSaveName = 'map' then
      [*] = ;      BoolRegister0 := True // autosave
      [*] = ;   else
      [*] = ;      BoolRegister0 := False;
      [*] = ;   IntRegister0 := gIntRegister_LanMapUID;
      [*] = ;   ExecuteState('SaveMap');
      [*] = ;   gStringRegister_LanMapSaveName := '';
      [*] = ;end;
      [*] = ;
      [*] = ;// executing hero movements, province events, healing armies and other stuff
      [*] = ;gGame.currentTurn := gGame.currentTurn + 1;
      [*] = ;
      [*] = ;if gGame.gameType = gc_GameTypeLanShard then
      [*] = ;begin
      [*] = ;   _lan_timer_Reset(gc_lt_map_end_turn,true,'COMMON.INC\MAP\MAP.ENDTURN');
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;// Process agreements that have already been sealed/should have been sealed in the diplomacy window.
      [*] = ;var proposePlInd, answerPlInd : Integer;
      [*] = ;var myCMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;var pQueries : Integer = ParserSelectByHandleByKey(ParserSelectPlayer(myPlHandle), 'Queries');
      [*] = ;
      [*] = ;for proposePlInd := 0 to gGame.map.players-1 do
      [*] = ;begin
      [*] = ;   var proposePlHandle : Integer = GetPlayerHandleByIndex(proposePlInd);
      [*] = ;      
      [*] = ;   if _plr_IsInGame(proposePlHandle) then
      [*] = ;   begin
      [*] = ;      var proposeCM : String = GetPlayerControlModeByHandle(proposePlHandle);
      [*] = ;      
      [*] = ;      for answerPlInd := 0 to gGame.map.players-1 do
      [*] = ;      if (proposePlInd <> answerPlInd) and (gArrDiplomacy[proposePlInd][answerPlInd].message.mType > 0) then
      [*] = ;      begin
      [*] = ;         var answerPlHandle : Integer = GetPlayerHandleByIndex(answerPlInd);
      [*] = ;         var mDeal : Integer = gArrDiplomacy[proposePlInd][answerPlInd].message.deal;
      [*] = ;         var bProposal : Boolean = _diplomacy_IsProposal(gArrDiplomacy[proposePlInd][answerPlInd].message);
      [*] = ;      
      [*] = ;         if bProposal and _plr_IsInGame(answerPlHandle) then // exclude messages that don't need to be answered. They will be processed just before the start of the next turn like AI messages.
      [*] = ;         begin
      [*] = ;            var mTreaty : Integer = gArrDiplomacy[proposePlInd][answerPlInd].message.treaty;
      [*] = ;               
      [*] = ;            var bUnionPeaceOffer : Boolean = false;
      [*] = ;            if mTreaty = gc_TreatyPeace then
      [*] = ;            begin
      [*] = ;               IntRegister0 := proposePlInd;
      [*] = ;               IntRegister1 := answerPlInd;
      [*] = ;               BoolRegister0 := false;
      [*] = ;               PlayerExecuteStateByHandle(proposePlHandle, 'CheckUnionPeaceOffer');
      [*] = ;               bUnionPeaceOffer := BoolRegister1;
      [*] = ;               //var queryAnotherPlayer : Boolean = BoolRegister2;
      [*] = ;               //var unionRejection : Boolean = BoolRegister3;
      [*] = ;            end;
      [*] = ;            
      [*] = ;            if bUnionPeaceOffer then
      [*] = ;            begin
      [*] = ;               if not BoolRegister2 then // everyone involved has answered
      [*] = ;               begin
      [*] = ;                  if BoolRegister3 then // impossible to execute, someone rejected
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := proposePlInd;
      [*] = ;                     IntRegister1 := answerPlInd;
      [*] = ;                     PlayerExecuteStateByHandle(proposePlHandle, 'DeleteUnionPeaceOffers');
      [*] = ;                  end
      [*] = ;                  else 
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := proposePlInd;
      [*] = ;                     IntRegister1 := answerPlInd;
      [*] = ;                     PlayerExecuteStateByHandle(proposePlHandle, 'ExecuteUnionPeace');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if (mDeal > 0) then // proposal accepted
      [*] = ;            begin
      [*] = ;               IntRegister0 := answerPlInd;
      [*] = ;               PlayerExecuteStateByHandle(proposePlHandle, 'CheckMessage');
      [*] = ;               if BoolRegister0 and _diplomacy_IsMessageValid(proposePlInd, answerPlInd, gArrDiplomacy[proposePlInd][answerPlInd].message) then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := proposePlInd;
      [*] = ;                  PlayerExecuteStateByHandle(answerPlHandle, 'AcceptDeal');
      [*] = ;                  
      [*] = ;                  if (mTreaty = gc_TreatyWar) or (mTreaty = gc_TreatyUnion) then // check if war should be declared because of an alliance
      [*] = ;                  begin
      [*] = ;                     PlayerExecuteStateByHandle(answerPlHandle, 'CheckUnionWars');
      [*] = ;                     PlayerExecuteStateByHandle(proposePlHandle, 'CheckUnionWars');
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else // deal cancelled because requirements are no longer met for some reason
      [*] = ;               begin
      [*] = ;                  if ((proposePlInd = myIndex) or (answerPlInd = myIndex)) and SameText(myCMode, 'cmPlayer') then
      [*] = ;                  begin
      [*] = ;                     var otherPlayerIndex : Integer = answerPlInd;
      [*] = ;                     if (otherPlayerIndex = myIndex) then
      [*] = ;                        otherPlayerIndex := proposePlInd;
      [*] = ;                     
      [*] = ;                     var pQuery : Integer = ParserAddChildByIndex(pQueries, '*');
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', gc_gui_query_diplCancelDeal);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex', otherPlayerIndex);
      [*] = ;                     ParserSetBoolValueByKeyByHandle(pQuery, 'Diplomacy', true);
      [*] = ;                     ParserSetBoolValueByKeyByHandle(pQuery, 'Informative', true);
      [*] = ;                  
      [*] = ;                     gArrDiplomacy[proposePlInd][answerPlInd].answer := 0;
      [*] = ;                     gArrDiplomacy[proposePlInd][answerPlInd].displayPriority := gArrDiplomacy[proposePlInd][answerPlInd].displayPriority and $ff0000;
      [*] = ;                     gArrDiplomacy[answerPlInd][proposePlInd].answer := 0;
      [*] = ;                     gArrDiplomacy[answerPlInd][proposePlInd].displayPriority := gArrDiplomacy[answerPlInd][proposePlInd].displayPriority and $ff0000;
      [*] = ;                  end;
      [*] = ;                  IntRegister0 := proposePlInd;
      [*] = ;                  PlayerExecuteStateByHandle(answerPlHandle, 'CancelDeal');
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if (mDeal < 0) or SameText(proposeCM, 'cmPC') then // rejected or withdrawn 
      [*] = ;            begin
      [*] = ;               if (mDeal = 0) then
      [*] = ;                  gArrDiplomacy[proposePlInd][answerPlInd].message.deal := -3; // AI always withdraw offer if not answered during the same turn as arrived 
      [*] = ;               
      [*] = ;               // send a message if offer withdrawn and the offer has been viewed
      [*] = ;               if (answerPlInd = myIndex) and SameText(myCMode, 'cmPlayer') and (gArrDiplomacy[answerPlInd][proposePlInd].answer = 0) and (gArrDiplomacy[proposePlInd][answerPlInd].message.deal = -3) 
      [*] = ;                 and ((gArrDiplomacy[proposePlInd][answerPlInd].displayPriority and $ff) = 0) then
      [*] = ;               begin
      [*] = ;                  var pQuery : Integer = ParserAddChildByIndex(pQueries, '*');
      [*] = ;                  ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', gc_gui_query_diplOfferWithdrawn);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex', proposePlInd);
      [*] = ;                  ParserSetBoolValueByKeyByHandle(pQuery, 'Diplomacy', true);
      [*] = ;                  ParserSetBoolValueByKeyByHandle(pQuery, 'Informative', true);
      [*] = ;               end;
      [*] = ;               IntRegister0 := proposePlInd;
      [*] = ;               PlayerExecuteStateByHandle(answerPlHandle, 'CancelDeal');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if (mDeal = -3) then // clear withdrawn messages
      [*] = ;               _diplomacy_ClearMessage(gArrDiplomacy[proposePlInd][answerPlInd].message);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if not bProposal then
      [*] = ;         begin
      [*] = ;            if (mDeal = -3) then // clear withdrawn non-proposal messages
      [*] = ;               _diplomacy_ClearMessage(gArrDiplomacy[proposePlInd][answerPlInd].message)
      [*] = ;            else
      [*] = ;            if myIndex = proposePlInd then // we must seal the "deal" of non-proposals so that the proposing player can no longer touch it in case he loads his new turn faster than the answer player sends his confirmation.
      [*] = ;               gArrDiplomacy[proposePlInd][answerPlInd].message.deal := 1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// decreasing ritual timers
      [*] = ;for i := 0 to ParserGetCountByHandle(pProvinces)-1 do
      [*] = ;begin
      [*] = ;   var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, i);
      [*] = ;   var pProvRituals : Integer = ParserSelectByHandleByKey(pProvince, 'Rituals');
      [*] = ;
      [*] = ;   for j := ParserGetCountByHandle(pProvRituals)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pProvRitual : Integer = ParserSelectByHandleByIndex(pProvRituals, j);
      [*] = ;      var time : Integer = ParserGetIntValueByKeyByHandle(pProvRitual, 'Time');
      [*] = ;
      [*] = ;      if time = 0 then
      [*] = ;      begin
      [*] = ;         ParserFreeByHandle(pProvRitual);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         time := time - 1;
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvRitual, 'Time', time);
      [*] = ;
      [*] = ;         if time = 0 then
      [*] = ;         begin
      [*] = ;            var dummyHandle : Integer = GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID'));
      [*] = ;
      [*] = ;            var ritualID : Integer = ParserGetIntValueByKeyByHandle(pProvRitual, 'RitualID');
      [*] = ;            IntRegister0 := ritualID;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'DestroyRitualFX');
      [*] = ;         end;
      [*] = ;         
      [*] = ;         time := ParserGetIntValueByKeyByHandle(pProvRitual, 'Length')+1;
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvRitual, 'Length',time);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// processing rituals in neutral provinces
      [*] = ;for i := 0 to ParserGetCountByHandle(pProvinces)-1 do
      [*] = ;begin
      [*] = ;   var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, i);
      [*] = ;   var dummyHandle : Integer = GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID'));
      [*] = ;
      [*] = ;   if SameText(ParserGetValueByKeyByHandle(pProvince, 'Player'), '') then
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle, 'ApplyCastedRituals');
      [*] = ;end;
      [*] = ;
      [*] = ;// repairing walls
      [*] = ;for i := 0 to ParserGetCountByHandle(pProvinces)-1 do
      [*] = ;begin
      [*] = ;   var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, i);
      [*] = ;   var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;   var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'GetWallRepairValue');
      [*] = ;   var repair : Integer = IntRegister0;
      [*] = ;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'GetMaxFortValue');
      [*] = ;   var maxFort : Integer = IntRegister0;
      [*] = ;
      [*] = ;   if maxFort > 0 then
      [*] = ;   begin
      [*] = ;      var fort : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Fort');
      [*] = ;
      [*] = ;      if fort < maxFort then
      [*] = ;         fort := fort + (maxFort * repair) div 100;
      [*] = ;      if fort > maxFort then
      [*] = ;         fort := maxFort;
      [*] = ;
      [*] = ;      ParserSetIntValueByKeyByHandle(pProvince, 'Fort', fort);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// changing attitudes
      [*] = ;for i := 0 to ParserGetCountByHandle(pProvinces)-1 do
      [*] = ;begin
      [*] = ;   var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, i);
      [*] = ;   var pProvAttitudes : Integer = ParserSelectByHandleByKey(pProvince, 'Attitudes');
      [*] = ;
      [*] = ;   for j := ParserGetCountByHandle(pProvAttitudes)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pProvAttitude : Integer = ParserSelectByHandleByIndex(pProvAttitudes, j);
      [*] = ;      var attitude : Integer = ParserGetIntValueByKeyByHandle(pProvAttitude, 'Attitude');
      [*] = ;
      [*] = ;      if attitude <> 0 then
      [*] = ;      begin
      [*] = ;         var timer : Integer = ParserGetIntValueByKeyByHandle(pProvAttitude, 'Timer');
      [*] = ;         timer := timer - 1;
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvAttitude, 'Timer', timer);
      [*] = ;
      [*] = ;         if timer = 0 then
      [*] = ;         begin
      [*] = ;            if attitude > 0 then
      [*] = ;               attitude := attitude - 1
      [*] = ;            else
      [*] = ;               attitude := attitude + 1;
      [*] = ;
      [*] = ;            ParserSetIntValueByKeyByHandle(pProvAttitude, 'Attitude', attitude);
      [*] = ;            ParserSetIntValueByKeyByHandle(pProvAttitude, 'Timer', gc_AttitudeTime);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// restore province and site guards
      [*] = ;for i := 0 to ParserGetCountByHandle(pProvinces)-1 do
      [*] = ;begin
      [*] = ;   var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, i);
      [*] = ;   var provPlayer : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;   var provHandle : Integer = GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID'));
      [*] = ;   var prov_flags : Integer = 0;
      [*] = ;
      [*] = ;   if SameText(provPlayer, '') then
      [*] = ;   begin
      [*] = ;      var pProvGuard : Integer = ParserSelectByHandleByKey(pProvince, 'Guard');
      [*] = ;      var pGuardUnits : Integer = ParserSelectByHandleByKey(pProvGuard, 'Units');
      [*] = ;
      [*] = ;      IntRegister0 := pGuardUnits;
      [*] = ;      IntRegister1 := 0;
      [*] = ;      IntRegister2 := 0;
      [*] = ;      IntRegister3 := 0;
      [*] = ;      BoolRegister0 := true;
      [*] = ;      BoolRegister1 := false;
      [*] = ;      ExecuteState('map.RestoreUnits');
      [*] = ;   end;
      [*] = ;
      [*] = ;   var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;   for j := ParserGetCountByHandle(pProvSites)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, j);
      [*] = ;      var pSiteGuard : Integer = ParserSelectByHandleByKey(pProvSite, 'Guard');
      [*] = ;      var pSiteUnits : Integer = ParserSelectByHandleByKey(pSiteGuard, 'Units');
      [*] = ;      var restore : Boolean = ParserGetBoolValueByKeyByHandle(pSiteGuard, 'NeedRestore');
      [*] = ;
      [*] = ;      if restore then
      [*] = ;      begin
      [*] = ;         IntRegister0 := pSiteUnits;
      [*] = ;         IntRegister1 := 0;
      [*] = ;         IntRegister2 := 0;
      [*] = ;         IntRegister3 := 0;
      [*] = ;         BoolRegister0 := true;
      [*] = ;         BoolRegister1 := false;
      [*] = ;         ExecuteState('map.RestoreUnits');
      [*] = ;         if not BoolRegister2 then
      [*] = ;            ParserSetBoolValueByKeyByHandle(pSiteGuard, 'NeedRestore', false);
      [*] = ;         prov_flags := prov_flags or gc_province_uf_sites_updated;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (provHandle <> 0) and (prov_flags <> 0) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := prov_flags;
      [*] = ;      StringRegister0 := _log_name;
      [*] = ;      GameObjectExecuteStateByHandle(provHandle, 'MergeUpdateFlags');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;for i := 0 to gGame.map.players-1 do
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;   if _plr_IsInGame(plHandle) then
      [*] = ;   begin
      [*] = ;      PlayerExecuteStateByHandle(plHandle, 'GetCastleParser');
      [*] = ;      var pPlProvince : Integer = IntRegister0;
      [*] = ;      var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pPlProvince, 'DummyUID');
      [*] = ;      var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;      // adding mercenaries
      [*] = ;      IntRegister0 := 24;
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle, 'CheckInnerBuildAbility');
      [*] = ;      var fast : Integer = IntRegister1;
      [*] = ;
      [*] = ;      var pProvMercenary : Integer = ParserSelectByHandleByKey(pPlProvince, 'Mercenary');
      [*] = ;      var mercUnitID : Integer = ParserGetIntValueByKeyByHandle(pProvMercenary, 'UnitID');
      [*] = ;      var timer : Integer = ParserGetIntValueByKeyByHandle(pProvMercenary, 'Timer');
      [*] = ;      timer := timer + 1;
      [*] = ;      ParserSetIntValueByKeyByHandle(pProvMercenary, 'Timer', timer);
      [*] = ;      if _log then Log('Mercenary timer: '+IntToStr(timer)+', unitID: '+IntToStr(mercUnitID)+', plIndex: '+IntToStr(i));
      [*] = ;
      [*] = ;      if ((mercUnitID = 0) and (fast > 0) and (timer > gc_MercenaryTime / 2)) or (timer >= gc_MercenaryTime) then
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'AddMercenary');
      [*] = ;
      [*] = ;      // changing attitudes
      [*] = ;      if ((gGame.currentTurn mod 10) = 0) then
      [*] = ;      begin
      [*] = ;         for j := 0 to gGame.map.players-1 do
      [*] = ;         if j <> i then
      [*] = ;         begin
      [*] = ;            var plHandle1 : Integer = GetPlayerHandleByIndex(j);
      [*] = ;            if _plr_IsInGame(plHandle1) then
      [*] = ;            begin
      [*] = ;               if gArrDiplomacy[i][j].treaty = 1 then
      [*] = ;                  gArrDiplomacy[i][j].attitude := gArrDiplomacy[i][j].attitude - 1;
      [*] = ;               if gArrDiplomacy[i][j].treaty = 3 then
      [*] = ;                  gArrDiplomacy[i][j].attitude := gArrDiplomacy[i][j].attitude + 1;
      [*] = ;               if gArrDiplomacy[i][j].trade.trade then
      [*] = ;                  gArrDiplomacy[i][j].attitude := gArrDiplomacy[i][j].attitude + 1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // decreasing ritual cooldowns
      [*] = ;      var pPlRituals : Integer = ParserSelectByHandleByKey(pPlProvince, 'AvailableRituals');
      [*] = ;      for j := ParserGetCountByHandle(pPlRituals)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pPlRitual : Integer = ParserSelectByHandleByIndex(pPlRituals, j);
      [*] = ;         var cooldown : Integer = ParserGetIntValueByKeyByHandle(pPlRitual, 'Cooldown');
      [*] = ;
      [*] = ;         if cooldown > 0 then
      [*] = ;            ParserSetIntValueByKeyByHandle(pPlRitual, 'Cooldown', cooldown - 1);
      [*] = ;      end;
      [*] = ;
      [*] = ;      // process sieges
      [*] = ;      for j := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;         var isDead : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;         var task : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iTask);
      [*] = ;
      [*] = ;         if (not isDead) and (task = gc_UnitTaskSiege) then
      [*] = ;         begin
      [*] = ;            var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;            var pGOUnits : Integer = ParserSelectByHandleByKey(pGOParser, 'Units');
      [*] = ;
      [*] = ;            var curUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;            var pProvince : Integer = _misc_GetProvinceParserByUID(curUID);
      [*] = ;
      [*] = ;            IntRegister0 := pGOUnits;
      [*] = ;            IntRegister1 := goHandle;
      [*] = ;            IntRegister2 := pProvince;
      [*] = ;            ExecuteState('map.ContinueSiegeByParser');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      for j := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;         if not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead) then
      [*] = ;         begin
      [*] = ;            var task : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iTask);
      [*] = ;            if _log then _Log_map(_log_name+' assign hero task as action type: ID ='+IntToStr(task)+', Player.'+IntToStr(i));
      [*] = ;            SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iActionType, task);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SetPlayerBoolValueIndByHandle(GetPlayerHandleInterfaceIO(), gc_map_PLStack_MapUnit_bTurnFinished, false);
      [*] = ;
      [*] = ;_gv_SetCurrentPlayer(-1,_log_name);
      [*] = ;gIntRegister_CurProvinceIndex := -1;
      [*] = ;_gv_SetMapLock($10000,_log_name);
      [*] = ;_gv_SetMapTurnFinished(true,_log_name+'[1]');
      [*] = ;gIntRegister_CurrentEventID := 0;
      [*] = ;
      [*] = ;gBoolRegister_CheckLevelUp := false; // this would cause a lot of problems if it remains true outside "exploration-levelup-delay-coz-site-query" combo it's meant for.
      [*] = ;
      [*] = ;BoolRegister0 := false;
      [*] = ;GUIExecuteState('map.ShowWhosTurn');
      [*] = ;
      [*] = ;ExecuteState('map.MoveHeroes');
      [*] = ;gBoolRegister_MapResolveConflicts := true;
      [*] = ;
      [*] = ;if gGame.gameType = gc_GameTypeLanShard then
      [*] = ;begin
      [*] = ;   if GetLanMode() >= 2 then
      [*] = ;      gIntRegister_ConflictPlayerIndex := gIntRegister_MapMyPlayerIndex
      [*] = ;   else
      [*] = ;      gIntRegister_ConflictPlayerIndex := -1;
      [*] = ;end
      [*] = ;else
      [*] = ;   gIntRegister_ConflictPlayerIndex := 0;
      [*] = ;
      [*] = ;var randkey0, randKey1 : Integer;
      [*] = ;GetRandomExtKey64(randKey0, randKey1);
      [*] = ;_Log_map(_log_name+' randKey0 = ' + IntToStr(randKey0) + ' randKey1 = ' + IntToStr(randKey1));
      [*] = ;
      [*] = ;_gv_SetMapTurnFinished(false,_log_name+'[2]');
      [*] = ;BoolRegister0 := false;
      [*] = ;ExecuteState('bat.ResetData');
      [*] = ;
      [*] = ;if (gGame.gameType <> gc_GameTypeLanShard) or (GetLanMode() >= 2) then
      [*] = ;   ExecuteState('map.FindConflicts')
      [*] = ;else
      [*] = ;   _gv_SetMapLock($10001,_log_name);
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

