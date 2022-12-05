section.begin
   Name = MakeTurn
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\MAKETURN';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;ExecuteState('IsInGame');
      [*] = ;if (not BoolRegister0) or (not gBoolRegister_MapAIEnabled) then
      [*] = ;begin
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var myPlName : String = GetPlayerNameByHandle(myPlHandle);
      [*] = ;var pMyParser : Integer = ParserSelectPlayer(myPlHandle);
      [*] = ;var goCount : Integer = GetPlayerGameObjectsCountByHandle(myPlHandle);
      [*] = ;
      [*] = ;var plKarma : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iKarma);
      [*] = ;var plCMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;var plProfile : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;var plDiff : Integer = gGame.arrplayerdifficulty[GetPlayerIndexByHandle(myPlHandle)].basediff;
      [*] = ;
      [*] = ;ExecuteState('GetCastleParser');
      [*] = ;var pCastle : Integer = IntRegister0;
      [*] = ;var pPlDefenders : Integer = ParserSelectByHandleByKey(pCastle, 'Defenders');
      [*] = ;var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pCastle, 'DummyUID');
      [*] = ;var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;var pDefenders : Integer = gPrototypeData.defenders.handle;
      [*] = ;var i, j : Integer;
      [*] = ;
      [*] = ;if (plCMode = 'cmPC') and (plProfile = 0) then
      [*] = ;   SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iKarma, 0);
      [*] = ;
      [*] = ;var curTurn : Integer = gGame.currentTurn;
      [*] = ;
      [*] = ;procedure DoAlchemy();
      [*] = ;begin
      [*] = ;   IntRegister0 := 103;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'CheckInnerBuilding');
      [*] = ;   if BoolRegister0 then
      [*] = ;   begin
      [*] = ;      var goldGain, gemGain, goldLost, gemlost : Integer = 0;
      [*] = ;      var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;      var plGem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;
      [*] = ;      if (plGold < 100) and (plGem > 2000) then
      [*] = ;      begin
      [*] = ;         plGold := plGold + 200;
      [*] = ;         plGem := plGem - 200;
      [*] = ;
      [*] = ;         var gold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldGain);
      [*] = ;         SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldGain, gold + 200);
      [*] = ;      end;
      [*] = ;      if (plGold > 10000) and (plGem < 50) then
      [*] = ;      begin
      [*] = ;         plGold := plGold - 1000;
      [*] = ;         plGem := plGem + 40;
      [*] = ;
      [*] = ;         var gem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGemGain);
      [*] = ;         SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGemGain, gem + 40);
      [*] = ;      end;
      [*] = ;
      [*] = ;      SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold, plGold);
      [*] = ;      SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem, plGem);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if not gTutorial.map then
      [*] = ;begin
      [*] = ;   // adding defender agreements
      [*] = ;   if (gGame.gameType = gc_GameTypeCampaign) and (curTurn mod 11 = 10) then
      [*] = ;   begin
      [*] = ;      var power : Integer = 1 + curTurn div 100;
      [*] = ;      if power > 1 + gCampaign.currentTurn div 10 then
      [*] = ;         power := 1 + gCampaign.currentTurn div 10;
      [*] = ;
      [*] = ;      if power > 3 then
      [*] = ;         power := 3;
      [*] = ;
      [*] = ;      var karma : Integer = 0;
      [*] = ;      if Abs(plKarma) >= 50 then
      [*] = ;      begin
      [*] = ;         if plKarma > 0 then
      [*] = ;            karma := 1
      [*] = ;         else
      [*] = ;            karma := -1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      for i := ParserGetCountByHandle(pPlDefenders)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pPlDefender : Integer = ParserSelectByHandleByIndex(pPlDefenders, i);
      [*] = ;         var defID : Integer = ParserGetIntValueByKeyByHandle(pPlDefender, 'DefenderID');
      [*] = ;         var count : Integer = ParserGetIntValueByKeyByHandle(pPlDefender, 'Count');
      [*] = ;
      [*] = ;         var pDefender : Integer = ParserSelectByHandleByIndex(pDefenders, defID);
      [*] = ;         var defPower : Integer = ParserGetIntValueByKeyByHandle(pDefender, 'Power');
      [*] = ;         var defKarma : Integer = ParserGetIntValueByKeyByHandle(pDefender, 'Karma');
      [*] = ;
      [*] = ;         if (count = 0) and (defPower = power) and ((karma = 0) or (defKarma = 0) or (karma * defKarma > 0)) then
      [*] = ;            ParserSetIntValueByKeyByHandle(pPlDefender, 'Count', 1);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i := 0 to gGame.map.players-1 do
      [*] = ;      gArrDiplomacy[myPlIndex][i].canKill := -10;
      [*] = ;
      [*] = ;   SetBoolValueByIndex(gc_map_PLStack_MapUnit_bExpandHalted, true);
      [*] = ;   DoAlchemy();
      [*] = ;
      [*] = ;   var goldLimit : Integer = 50 + curTurn;
      [*] = ;   var gemLimit : Integer = 20 + curTurn div 5;
      [*] = ;
      [*] = ;   SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldLimit, goldLimit);
      [*] = ;   SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGemLimit, gemLimit);
      [*] = ;
      [*] = ;   // refresh camper provinces list
      [*] = ;   var pCampProvinces : Integer = ParserSelectByHandleByKey(pMyParser, 'CampProvinces');
      [*] = ;
      [*] = ;   for i := 0 to goCount-1 do
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;      var dead : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;      var campUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCampUID);
      [*] = ;      var campTurn : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCampTurn);
      [*] = ;
      [*] = ;      if (not dead) and (campUID <> 0) and (campTurn > 0) then
      [*] = ;      begin
      [*] = ;         var pCampProvince : Integer = ParserAddChildByIndex(pCampProvinces, '*');
      [*] = ;         ParserSetIntValueByKeyByHandle(pCampProvince, 'UID', campUID);
      [*] = ;
      [*] = ;         SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCampUID, 0);
      [*] = ;         SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCampTurn, 0);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pCampProvinces)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pCampProvince : Integer = ParserSelectByHandleByIndex(pCampProvinces, i);
      [*] = ;      var uid : Integer = ParserGetIntValueByKeyByHandle(pCampProvince, 'UID');
      [*] = ;
      [*] = ;      if uid > 0 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := uid;
      [*] = ;         MapExecuteState('GetProvinceParserByUID');
      [*] = ;         var pProvince : Integer = IntRegister1;
      [*] = ;
      [*] = ;         var bCamp : Boolean = false;
      [*] = ;         var provPlayer : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;         if (provPlayer <> '') and (not SameText(myPlName, provPlayer)) then
      [*] = ;         begin
      [*] = ;            var plHandle : Integer = GetPlayerHandleByName(provPlayer);
      [*] = ;
      [*] = ;            for j := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var goHandle : Integer = GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;               var dead : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;               var curUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;
      [*] = ;               if (not dead) and (curUID = uid) then
      [*] = ;               begin
      [*] = ;                  bCamp := true;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if not bCamp then
      [*] = ;               ParserFreeByHandle(pCampProvince);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // adding defender agreements for camp players
      [*] = ;   if plProfile > 0 then
      [*] = ;   begin
      [*] = ;      if (plProfile = 13) and (curTurn = 50 - plDiff * 5) then
      [*] = ;      begin
      [*] = ;         var pProvSite : Integer = ParserSelectByHandleByIndex(ParserSelectByHandleByKey(pCastle, 'Sites'), 0);
      [*] = ;         if (dummyHandle <> 0) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := gc_province_uf_sites_updated;
      [*] = ;            StringRegister0 := _log_name;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'MergeUpdateFlags');
      [*] = ;         end;
      [*] = ;         ParserFreeByHandle(ParserSelectByHandleByKey(pProvSite, 'Guard'));
      [*] = ;      end;
      [*] = ;
      [*] = ;      var aiUnionCounter : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iAIUnionCounter);
      [*] = ;      var union : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iUnion);
      [*] = ;      var aiUnion : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iAIUnionRace);
      [*] = ;
      [*] = ;      if aiUnionCounter > 0 then
      [*] = ;      begin
      [*] = ;         aiUnionCounter := aiUnionCounter - 1;
      [*] = ;         SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iAIUnionCounter, aiUnionCounter);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (aiUnionCounter = 0) and (union = 0) and (aiUnion > 0) then
      [*] = ;         SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iUnion, aiUnion);
      [*] = ;
      [*] = ;      if plDiff > 0 then
      [*] = ;      begin
      [*] = ;         var defID : Integer = 0;
      [*] = ;         case plProfile of
      [*] = ;            1, 16 :
      [*] = ;            begin
      [*] = ;               if (curTurn+1) mod (150 - plDiff * 10) = 0 then
      [*] = ;                  defID := 58;
      [*] = ;            end;
      [*] = ;            2, 15 :
      [*] = ;            begin
      [*] = ;               if (curTurn+1) mod (150 - plDiff * 10) = 0 then
      [*] = ;                  defID := 50;
      [*] = ;            end;
      [*] = ;            3 :
      [*] = ;            begin
      [*] = ;               if (curTurn+1) mod (150 - plDiff * 10) = 0 then
      [*] = ;                  defID := 48;
      [*] = ;            end;
      [*] = ;            4 :
      [*] = ;            begin
      [*] = ;               if (curTurn+1) mod (150 - plDiff * 10) = 0 then
      [*] = ;                  defID := 59;
      [*] = ;            end;
      [*] = ;            5, 12 :
      [*] = ;            begin
      [*] = ;               if (curTurn+1) mod (150 - plDiff * 10) = 0 then
      [*] = ;                  defID := 46;
      [*] = ;            end;
      [*] = ;            6 :
      [*] = ;            begin
      [*] = ;               if (curTurn+1) mod (150 - plDiff * 10) = 0 then
      [*] = ;                  defID := 47;
      [*] = ;            end;
      [*] = ;            7 :
      [*] = ;            begin
      [*] = ;               if (curTurn+1) mod (150 - plDiff * 10) = 0 then
      [*] = ;                  defID := 57;
      [*] = ;            end;
      [*] = ;            8, 10 :
      [*] = ;            begin
      [*] = ;               if (curTurn+1) mod (120 - plDiff * 10) = 0 then
      [*] = ;                  defID := 56;
      [*] = ;            end;
      [*] = ;            11 :
      [*] = ;            begin
      [*] = ;               if (curTurn+1) mod (150 - plDiff * 10) = 0 then
      [*] = ;                  defID := 53;
      [*] = ;            end;
      [*] = ;            13 :
      [*] = ;            begin
      [*] = ;               if (curTurn+1) mod (120 - plDiff * 10) = 0 then
      [*] = ;                  defID := 55;
      [*] = ;            end;
      [*] = ;            9, 14 :
      [*] = ;            begin
      [*] = ;               if (curTurn+1) mod (150 - plDiff * 10) = 0 then
      [*] = ;                  defID := 60;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var pPlDefender : Integer = ParserSelectByHandleByIndex(pPlDefenders, defID);
      [*] = ;         var count : Integer = ParserGetIntValueByKeyByHandle(pPlDefender, 'Count');
      [*] = ;         ParserSetIntValueByKeyByHandle(pPlDefender, 'Count', count+1);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle,  gc_map_PLStack_MapUnit_iGold);
      [*] = ;   var plGem : Integer = GetPlayerIntValueIndByHandle(myPlHandle,  gc_map_PLStack_MapUnit_iGem);
      [*] = ;
      [*] = ;   if plGold < 0 then
      [*] = ;   begin
      [*] = ;      plGold := -1;
      [*] = ;      SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold, plGold);
      [*] = ;   end;
      [*] = ;   if plGem < 0 then
      [*] = ;   begin
      [*] = ;      plGem := -1;
      [*] = ;      SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem, plGem);
      [*] = ;   end;
      [*] = ;
      [*] = ;   ExecuteState('AIRecruitHero');
      [*] = ;   var canSpend : Boolean = BoolRegister0;
      [*] = ;   SetPlayerBoolValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_bCanSpend, canSpend);
      [*] = ;
      [*] = ;   if canSpend and (curTurn <= 10) then
      [*] = ;   begin
      [*] = ;      ExecuteState('ChooseInnerBuild');
      [*] = ;   end;
      [*] = ;
      [*] = ;   goCount := GetPlayerGameObjectsCountByHandle(myPlHandle);
      [*] = ;   ExecuteState('RitualHealUnits');
      [*] = ;
      [*] = ;   // heroes actions
      [*] = ;   for i := 0 to goCount-1 do
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;
      [*] = ;      GameObjectExecuteStateByHandle(goHandle,'IsActionsPossible');
      [*] = ;      if IntRegister0 > 0 then
      [*] = ;      begin
      [*] = ;         var notInBattle : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iNotInBattle);
      [*] = ;
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'HireUnits');
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'LearnSpells');
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'EquipItems');
      [*] = ;         notInBattle := notInBattle + 1;
      [*] = ;         SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iNotInBattle, notInBattle);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   ExecuteState('HeroTaskMaster');
      [*] = ;   ExecuteState('FillGarrison');
      [*] = ;
      [*] = ;   if (plDiff = 0) and (curTurn mod 2 = 0) then
      [*] = ;      canSpend := false;
      [*] = ;
      [*] = ;   if (plDiff = 1) and (curTurn mod 3 = 0) then
      [*] = ;      canSpend := false;
      [*] = ;
      [*] = ;   if canSpend then
      [*] = ;   begin
      [*] = ;      ExecuteState('AIPlaceDefender');
      [*] = ;
      [*] = ;      if (curTurn > 10) then
      [*] = ;      begin
      [*] = ;         ExecuteState('ChooseInnerBuild');
      [*] = ;      end;
      [*] = ;
      [*] = ;      if _rand_Random(100) > 60 then
      [*] = ;         ExecuteState('AIOuterBuild');
      [*] = ;   end;
      [*] = ;
      [*] = ;   ExecuteState('CastRitualAI');
      [*] = ;   if (plProfile > 0) and gGame.diplomacy then
      [*] = ;      ExecuteState('MakeDiplomacy');
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

