section.begin
   Name = bat.AfterBattle
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\BAT\BAT.AFTERBATTLE';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;if _misc_IsLanBattle then
      [*] = ;begin
      [*] = ;   gIntRegsiter_LanReadyPlayersCount := gIntRegsiter_LanReadyPlayersCount + 1;
      [*] = ;   if _log then _log_map(_log_name+' gIntRegsiter_LanReadyPlayersCount: '+IntToStr(gIntRegsiter_LanReadyPlayersCount));
      [*] = ;   if (gIntRegsiter_LanReadyPlayersCount < 2) then  // ensure hero death state has been transferred, bat.AfterBattle is called once more when it's transferred
      [*] = ;      exit;
      [*] = ;end;
      [*] = ;gIntRegsiter_LanReadyPlayersCount := 0;
      [*] = ;
      [*] = ;const bpHandle = 0;//player (battle)
      [*] = ;const mpHandle = 1;//player (map)
      [*] = ;const mpMode = 2;//(0-none, 1-PC, 2-Human)
      [*] = ;const bhHandle = 3;//hero battle
      [*] = ;const mhHandle = 4;//hero map
      [*] = ;const mhAlive = 5;//hero alive
      [*] = ;const bArmy = 6;//army parser
      [*] = ;
      [*] = ;var avar : array [0..$10] of Integer;//attacker
      [*] = ;var dvar : array [0..$10] of Integer;//defender
      [*] = ;var wvar : array [0..$10] of Integer;//winner
      [*] = ;var lvar : array [0..$10] of Integer;//loser
      [*] = ;var status : Integer;
      [*] = ;
      [*] = ;procedure PrintDebugInfo(attackPlHandle, defendPlHandle : Integer);
      [*] = ;begin
      [*] = ;   var i,goHandle : Integer;
      [*] = ;
      [*] = ;   logI(_log_name+' Armies list start');
      [*] = ;   LogI('Attack player:');
      [*] = ;   for i := 0 to GetPlayerGameObjectsCountByHandle(attackPlHandle)-1 do
      [*] = ;   begin
      [*] = ;      goHandle := GetGameObjectHandleByIndex(i, attackPlHandle);
      [*] = ;      LogI('  UnitID = ' + IntToStr(GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iUnitID)) + ', life = ' + IntToStr(GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife)));
      [*] = ;   end;
      [*] = ;
      [*] = ;   LogI('Defend player:');
      [*] = ;   for i := 0 to GetPlayerGameObjectsCountByHandle(defendPlHandle)-1 do
      [*] = ;   begin
      [*] = ;      goHandle := GetGameObjectHandleByIndex(i, defendPlHandle);
      [*] = ;      LogI('  UnitID = ' + IntToStr(GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iUnitID)) + ', life = ' + IntToStr(GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife)));
      [*] = ;   end;
      [*] = ;   _log_map('Armies list end');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CheckQuestEncounters(heroHandle : Integer; isWin : Boolean;pQueries : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   // quest encounters
      [*] = ;   var heroUID : Integer = GetGameObjectUniqueIdByHandle(heroHandle);
      [*] = ;
      [*] = ;   if (heroUID<>0) then
      [*] = ;   begin
      [*] = ;      var plHandle : Integer = GetGameObjectPlayerHandleByHandle(heroHandle);
      [*] = ;      var cMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;      if SameText(cMode, 'cmPlayer') then
      [*] = ;      begin
      [*] = ;         var pHeroParser : Integer = ParserSelectGameObject(heroHandle);
      [*] = ;         var pHeroQuests : Integer = ParserSelectByHandleByKey(pHeroParser, 'Quests');
      [*] = ;         for i := 0 to ParserGetCountByHandle(pHeroQuests)-1 do
      [*] = ;         begin
      [*] = ;            var pHeroQuest : Integer = ParserSelectByHandleByIndex(pHeroQuests, i);
      [*] = ;            var questID : Integer = ParserGetIntValueByKeyByHandle(pHeroQuest, 'Index');
      [*] = ;            var questComplete : Boolean = ParserGetBoolValueByKeyByHandle(pHeroQuest, 'Complete');
      [*] = ;            var pQuest : Integer = ParserSelectByHandleByIndex(gPrototypeData.quests.handle, questID);
      [*] = ;            var pQuestObjectives : Integer = ParserSelectByHandleByKey(pQuest, 'Objectives');
      [*] = ;            var qType : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'Type');
      [*] = ;
      [*] = ;            if (isWin and (qType = 2)) or (qType = 3) or (qType = 8) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := i;
      [*] = ;               GameObjectExecuteStateByHandle(heroHandle, 'CheckQuestDone');
      [*] = ;
      [*] = ;               var qComplete : Boolean = ParserGetBoolValueByKeyByHandle(pHeroQuest, 'Complete');
      [*] = ;               var qFound : Integer = ParserGetIntValueByKeyByHandle(pHeroQuest, 'Found');
      [*] = ;               if (not qComplete) and (qFound <> 0) then
      [*] = ;               begin
      [*] = ;                  var encFound : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'EncFound');
      [*] = ;                  var encNotFound : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'EncNotFound');
      [*] = ;
      [*] = ;                  if (qFound = 1) and (encFound > 0) then
      [*] = ;                  begin
      [*] = ;                     var pQuery : Integer = ParserAddChildByIndex(pQueries, '*');
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', encFound);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'HeroUID', heroUID);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'QuestIndex', i);
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if (qFound = -1) and (encNotFound > 0) then
      [*] = ;                  begin
      [*] = ;                     var pQuery : Integer = ParserAddChildByIndex(pQueries, '*');
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', encNotFound);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'HeroUID', heroUID);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'QuestIndex', i);
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  ParserSetIntValueByKeyByHandle(pHeroQuest, 'Found', 0);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CheckSiteQuest(goHandle, siteInd, pProvince,pQueries : Integer);
      [*] = ;begin
      [*] = ;   var i, j : Integer;
      [*] = ;   var heroUID : Integer = GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;
      [*] = ;   var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;   var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, siteInd);
      [*] = ;   var siteID : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'SiteID');
      [*] = ;
      [*] = ;   var pHeroParser : Integer = ParserSelectGameObject(gIntRegister_BattleAttackHeroHandle);
      [*] = ;   var pHeroQuests : Integer = ParserSelectByHandleByKey(pHeroParser, 'Quests');
      [*] = ;   for i := 0 to ParserGetCountByHandle(pHeroQuests)-1 do
      [*] = ;   begin
      [*] = ;      var pHeroQuest : Integer = ParserSelectByHandleByIndex(pHeroQuests, i);
      [*] = ;      var pHeroArProgress : Integer = ParserSelectByHandleByKey(pHeroQuest, 'ArProgress');
      [*] = ;      var questID : Integer = ParserGetIntValueByKeyByHandle(pHeroQuest, 'Index');
      [*] = ;      var questComplete : Boolean = ParserGetBoolValueByKeyByHandle(pHeroQuest, 'Complete');
      [*] = ;      var pQuest : Integer = ParserSelectByHandleByIndex(gPrototypeData.quests.handle, questID);
      [*] = ;      var pQuestObjectives : Integer = ParserSelectByHandleByKey(pQuest, 'Objectives');
      [*] = ;      var qType : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'Type');
      [*] = ;      var encFound : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'EncFound');
      [*] = ;      var encNotFound : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'EncNotFound');
      [*] = ;
      [*] = ;      if (qType = 1) and (not questComplete) then
      [*] = ;      begin
      [*] = ;         for j := ParserGetCountByHandle(pQuestObjectives)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pQuestObjective : Integer = ParserSelectByHandleByIndex(pQuestObjectives, j);
      [*] = ;            var ind : Integer = ParserGetIntValueByKeyByHandle(pQuestObjective, 'Index');
      [*] = ;            var param : Integer = ParserGetIntValueByKeyByHandle(pQuestObjective, 'Param');
      [*] = ;
      [*] = ;            if ind = siteID then
      [*] = ;            begin
      [*] = ;               if param > _rand_Random(100) then
      [*] = ;               begin
      [*] = ;                  var pHeroProgress : Integer = ParserSelectByHandleByIndex(pHeroArProgress, j);
      [*] = ;                  var progress : Integer = ParserGetIntValueByKeyByHandle(pHeroProgress, 'Progress');
      [*] = ;                  progress := progress + 1;
      [*] = ;                  ParserSetIntValueByKeyByHandle(pHeroProgress, 'Progress', progress);
      [*] = ;
      [*] = ;                  if encFound > 0 then
      [*] = ;                  begin
      [*] = ;                     var pQuery : Integer = ParserAddChildByIndex(pQueries, '*');
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', encFound);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'HeroUID', heroUID);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'QuestIndex', i);
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  IntRegister0 := i;
      [*] = ;                  GameObjectExecuteStateByHandle(goHandle, 'CheckQuestDone');
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if encNotFound > 0 then
      [*] = ;                  begin
      [*] = ;                     var pQuery : Integer = ParserAddChildByIndex(pQueries, '*');
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', encNotFound);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'HeroUID', heroUID);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'QuestIndex', i);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ConflictRetreat(heroHandle : Integer);
      [*] = ;begin
      [*] = ;   BoolRegister0 := false;
      [*] = ;   GameObjectExecuteStateByHandle(heroHandle, 'RetreatGuard');
      [*] = ;   _misc_RemoveConflictHero(GetGameObjectUniqueIdByHandle(heroHandle));
      [*] = ;end;
      [*] = ;
      [*] = ;procedure RemoveWaterfields();
      [*] = ;begin
      [*] = ;   const cPatternPlName = 'battle.pattern';
      [*] = ;   var i,plHandle : Integer;
      [*] = ;
      [*] = ;   plHandle := GetPlayerHandleByName(cPatternPlName);
      [*] = ;   for i := WaterFieldGetCount()-1 downto 0 do
      [*] = ;   begin
      [*] = ;      if SameText(WaterFieldGetNameByIndex(i), 'battle') then
      [*] = ;         WaterFieldDelete(i);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function ProcessSiteBattle(site_index,pProvince,pQueries : Integer) : Integer;
      [*] = ;begin
      [*] = ;   if (status = 0) and (site_index <> -1) then
      [*] = ;   begin
      [*] = ;      // destroying site if needed
      [*] = ;      var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;      var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, site_index);
      [*] = ;      var siteID : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'SiteID');
      [*] = ;      var pSiteGuard : Integer = ParserSelectByHandleByKey(pProvSite, 'Guard');
      [*] = ;      var pGuard : Integer = ParserSelectByHandleByIndex(gPrototypeData.guards.handle, ParserGetIntValueByKeyByHandle(pSiteGuard, 'GuardID'));
      [*] = ;      var guardPower : Integer = ParserGetIntValueByKeyByHandle(pGuard, 'Power');
      [*] = ;      var guardType : Integer = ParserGetIntValueByKeyByHandle(pSiteGuard, 'GuardType');
      [*] = ;      var siteRes : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'Resource');
      [*] = ;      var plHandle : Integer = wvar[mpHandle];
      [*] = ;      var provInd : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Index');
      [*] = ;      
      [*] = ;      if (wvar[mhHandle] <> 0) and gBoolRegister_BattleEnemyFullPower {and SameText(GetPlayerControlModeByHandle(wvar[mpHandle]), 'cmPC')} then
      [*] = ;      begin
      [*] = ;         var heroAIPower : Integer = GetGameObjectIntValueIndByHandle(wvar[mhHandle], gc_map_GOStack_MapUnit_iAIPower);
      [*] = ;         if guardPower > heroAIPower then
      [*] = ;            SetGameObjectIntValueIndByHandle(wvar[mhHandle], gc_map_GOStack_MapUnit_iAIPower, guardPower);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if siteRes > 0 then
      [*] = ;         ParserSetBoolValueByKeyByHandle(pProvince,'ResourceGuarded', false);
      [*] = ;
      [*] = ;      ParserClearByHandle(pSiteGuard);
      [*] = ;
      [*] = ;      if (guardType = 23) or (guardType = 41) or (guardType = 46) then
      [*] = ;         SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iDragonHunt, GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iDragonHunt) + 1);
      [*] = ;
      [*] = ;      IntRegister0 := provInd;
      [*] = ;      IntRegister1 := site_index;
      [*] = ;      PlayerExecuteStateByHandle(plHandle, 'CheckCampQuest');
      [*] = ;
      [*] = ;      if (wvar[mhAlive] > 0) and ((wvar[mpMode] = 2) or (gBoolRegister_IsDefenderAutoBattle)) then
      [*] = ;      begin
      [*] = ;         var queryID : Integer;
      [*] = ;
      [*] = ;         CheckSiteQuest(wvar[mhHandle],site_index,pProvince,pQueries);
      [*] = ;
      [*] = ;         // check altar quests
      [*] = ;         queryID := 0;
      [*] = ;         if (gGame.GameType = gc_GameTypeCampaign) and (siteID = 26) then
      [*] = ;         begin
      [*] = ;            if (gIntRegister_CampDefendPlayer = 7) and (gCampaign.arrDialogs[573] > 0) then
      [*] = ;            begin
      [*] = ;               if gCampaign.arrDialogs[30] > 0 then
      [*] = ;                  queryID := gc_gui_query_heroAltarAmphoraAndKey
      [*] = ;               else
      [*] = ;                  queryID := gc_gui_query_heroAltarAmphora;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if gCampaign.arrDialogs[30] > 0 then
      [*] = ;                  queryID := gc_gui_query_heroAltarKey;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if queryID > 0 then
      [*] = ;         begin
      [*] = ;            var pQuery : Integer = ParserAddChildByIndex(pQueries, '*');
      [*] = ;            ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', queryID);
      [*] = ;            ParserSetIntValueByKeyByHandle(pQuery, 'HeroUID', GetGameObjectUniqueIdByHandle(wvar[mhHandle]));
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // scenario
      [*] = ;      if (gScenario.enabled) and (wvar[mhHandle] <> 0) and (wvar[mpHandle] <> 0) then
      [*] = ;      begin
      [*] = ;         _scenario_AddTriggerSiteCapture(gScenario.evaluate, provInd, site_index, siteID, wvar[mpHandle], wvar[mhHandle]);
      [*] = ;         _scenario_EvaluateTriggers(gScenario.evaluate);
      [*] = ;      end;
      [*] = ;      var dummyHandle : Integer = GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID'));
      [*] = ;      if dummyHandle <> 0 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := gc_province_uf_sites_updated;
      [*] = ;         StringRegister0 := _log_name;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'MergeUpdateFlags');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   Result := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;function PickupLoot() : Boolean;
      [*] = ;begin
      [*] = ;   Result := false;
      [*] = ;   if (wvar[bhHandle] <> 0) and (wvar[mhHandle] <> 0) then
      [*] = ;   begin
      [*] = ;      var pWinParser : Integer = ParserSelectGameObject(wvar[bhHandle]);
      [*] = ;      var pMapWinParser : Integer = ParserSelectGameObject(wvar[mhHandle]);
      [*] = ;      var i, plGold, plGem, battleGold, battleGem, siteGold, siteGem, pBattleLootItems, pSiteLootItems, pSiteItem, pNewItem : Integer;
      [*] = ;
      [*] = ;      battleGold := ParserGetIntValueByKeyByHandle(pWinParser, 'BattleGold');
      [*] = ;      battleGem := ParserGetIntValueByKeyByHandle(pWinParser, 'BattleGem');
      [*] = ;      siteGold := ParserGetIntValueByKeyByHandle(pMapWinParser, 'SiteGold');
      [*] = ;      siteGem := ParserGetIntValueByKeyByHandle(pMapWinParser, 'SiteGem');
      [*] = ;      plGold := battleGold + siteGold + GetPlayerIntValueIndByHandle(wvar[mpHandle],gc_map_PLStack_MapUnit_iGold);
      [*] = ;      plGem := battleGem + siteGem + GetPlayerIntValueIndByHandle(wvar[mpHandle],gc_map_PLStack_MapUnit_iGem);
      [*] = ;      SetPlayerIntValueIndByHandle(wvar[mpHandle],gc_map_PLStack_MapUnit_iGold, plGold);
      [*] = ;      SetPlayerIntValueIndByHandle(wvar[mpHandle],gc_map_PLStack_MapUnit_iGem, plGem);
      [*] = ;
      [*] = ;      plGold := GetPlayerIntValueIndByHandle(wvar[mpHandle], gc_map_PLStack_MapUnit_iGoldGain);
      [*] = ;      SetPlayerIntValueIndByHandle(wvar[mpHandle], gc_map_PLStack_MapUnit_iGoldGain, plGold + battleGold + siteGold);
      [*] = ;
      [*] = ;      plGem := GetPlayerIntValueIndByHandle(wvar[mpHandle], gc_map_PLStack_MapUnit_iGemGain);
      [*] = ;      SetPlayerIntValueIndByHandle(wvar[mpHandle], gc_map_PLStack_MapUnit_iGemGain, plGem + battleGem + siteGem);
      [*] = ;
      [*] = ;      if _stats_IsEligible(wvar[mpHandle]) then 
      [*] = ;      begin
      [*] = ;         _stats_SimpleUpdate('Gold', 'BattleGold', battleGold);
      [*] = ;         _stats_SimpleUpdate('Gold', 'SiteGold', siteGold);
      [*] = ;
      [*] = ;         _stats_SimpleUpdate('Gem', 'BattleGem', battleGem);
      [*] = ;         _stats_SimpleUpdate('Gem', 'SiteGem', siteGem);
      [*] = ;      end;
      [*] = ;
      [*] = ;      // add loot to hero doll
      [*] = ;      pBattleLootItems := ParserSelectByHandleByKey(pWinParser, 'BattleLootItems');
      [*] = ;      pSiteLootItems := ParserSelectByHandleByKey(pMapWinParser, 'SiteLootItems');
      [*] = ;
      [*] = ;      for i := 0 to ParserGetCountByHandle(pSiteLootItems)-1 do
      [*] = ;      begin
      [*] = ;         pSiteItem := ParserSelectByHandleByIndex(pSiteLootItems, i);
      [*] = ;         pNewItem := ParserAddChildByIndex(pBattleLootItems, '*');
      [*] = ;         ParserCopyFromByHandle(pSiteItem);
      [*] = ;      end;
      [*] = ;
      [*] = ;      IntRegister0 := pBattleLootItems;
      [*] = ;      GameObjectExecuteStateByHandle(wvar[mhHandle], 'TakeLootByParser');
      [*] = ;      Result := BoolRegister0;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function ProcessHeroesBattle() : Integer;
      [*] = ;begin
      [*] = ;   if _log then _log_map('ProcessHeroesBattle, status: '+IntToStr(status));
      [*] = ;   case status of
      [*] = ;      0 : begin
      [*] = ;         if _log then _log_map('ProcessHeroesBattle, avar[mhAlive]: '+BoolToStr(avar[mhAlive] > 0));
      [*] = ;         if avar[mhAlive] > 0 then
      [*] = ;            GameObjectExecuteStateByHandle(avar[mhHandle], 'ReturnBeforeAttack')
      [*] = ;         else
      [*] = ;            ConflictRetreat(avar[mhHandle]);
      [*] = ;         ConflictRetreat(dvar[mhHandle]);
      [*] = ;      end;
      [*] = ;      1 : begin
      [*] = ;         if _log then _log_map('ProcessHeroesBattle, dvar[mhAlive]: '+BoolToStr(dvar[mhAlive] > 0));
      [*] = ;         if dvar[mhAlive] > 0 then
      [*] = ;            GameObjectExecuteStateByHandle(dvar[mhHandle], 'ReturnBeforeAttack')
      [*] = ;         else
      [*] = ;            ConflictRetreat(dvar[mhHandle]);
      [*] = ;         ConflictRetreat(avar[mhHandle]);
      [*] = ;      end;
      [*] = ;      2 : begin
      [*] = ;         if _log then _log_map('ProcessHeroesBattle, draw');
      [*] = ;         ConflictRetreat(avar[mhHandle]);
      [*] = ;         ConflictRetreat(dvar[mhHandle]);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   Result := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;function FreeDeadUnits(pArmyParser : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := false;
      [*] = ;   
      [*] = ;   var i, pArmyUnits, pArmyUnit, armyCount : Integer;
      [*] = ;
      [*] = ;   pArmyUnits := ParserSelectByHandleByKey(pArmyParser, 'Units');
      [*] = ;   armyCount := ParserGetCountByHandle(pArmyUnits); 
      [*] = ;   if armyCount > 0 then
      [*] = ;   begin
      [*] = ;      for i := ParserGetCountByHandle(pArmyUnits)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         pArmyUnit := ParserSelectByHandleByIndex(pArmyUnits, i);
      [*] = ;
      [*] = ;         if (ParserGetIntValueByKeyByHandle(pArmyUnit, 'CurLife') = 0) then
      [*] = ;         begin
      [*] = ;            Result := true;
      [*] = ;            
      [*] = ;            if not ParserGetBoolValueByKeyByHandle(pArmyUnit, 'IsHero') then
      [*] = ;               ParserFreeByHandle(pArmyUnit);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var s : array [0..$10] of String;
      [*] = ;var i,j,new_battle_mode,p : Integer;
      [*] = ;
      [*] = ;var pProvince : Integer = gIntRegister_MapBattleProvince;
      [*] = ;var pQueries : Integer = ParserSelectByHandleByKey(ParserSelectCurrentStateMachine(), 'Queries');
      [*] = ;var new_army,new_hero : Integer;
      [*] = ;var capture,garrison,no_space : Boolean;
      [*] = ;
      [*] = ;TimeLog('AfterBattle execute');
      [*] = ;
      [*] = ;if pQueries = 0 then
      [*] = ;   pQueries := ParserAddChildByIndex(ParserSelectCurrentStateMachine(), 'Queries');
      [*] = ;
      [*] = ;RemoveWaterfields();
      [*] = ;
      [*] = ;ExecuteState('bat.GetAfterBattleHandles');
      [*] = ;status := IntRegister0;
      [*] = ;s[0] := StringRegister0;
      [*] = ;s[1] := StringRegister1;
      [*] = ;s[2] := StringRegister2;
      [*] = ;s[3] := StringRegister3;
      [*] = ;
      [*] = ;for i := 0 to 4-1 do
      [*] = ;begin
      [*] = ;   for j := 0 to 7-1 do
      [*] = ;   begin
      [*] = ;      case i of
      [*] = ;         0 : wvar[j] := _sa_GetAsInt(s[i],j);
      [*] = ;         1 : lvar[j] := _sa_GetAsInt(s[i],j);
      [*] = ;         2 : avar[j] := _sa_GetAsInt(s[i],j);
      [*] = ;         3 : dvar[j] := _sa_GetAsInt(s[i],j);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;if (gGame.gameType = gc_GameTypeHotseat) and (avar[mpHandle] <> 0) then
      [*] = ;begin
      [*] = ;   if avar[mpMode] = 2 then
      [*] = ;      gIntRegister_MapMyPlayerIndex := GetPlayerIndexByHandle(avar[mpHandle]);
      [*] = ;end;
      [*] = ;
      [*] = ;if _log then PrintDebugInfo(avar[bpHandle],dvar[bpHandle]);
      [*] = ;if _log then _Log_ValuesM('Status|AMode|DMode',status,avar[mpMode],dvar[mpMode],0,0,0);
      [*] = ;if _log then _log_valuesM('APlayer|DPlayer|AMHero|DMHero|CUID1|CUID2',avar[mpHandle],dvar[mpHandle],avar[mhHandle],dvar[mhHandle],gIntRegister_ConflictHeroUID1,gIntRegister_ConflictHeroUID2);
      [*] = ;
      [*] = ;new_army := 0;
      [*] = ;new_hero := 0;
      [*] = ;garrison := false;
      [*] = ;capture := false;
      [*] = ;
      [*] = ;if wvar[mpHandle] <> 0 then
      [*] = ;begin
      [*] = ;   no_space := PickupLoot();
      [*] = ;   if (wvar[mpMode] = 1) and (not gBoolRegister_IsDefenderAutoBattle) then
      [*] = ;      PlayerExecuteStateByHandle(wvar[bpHandle],'AICheckNecromancy');
      [*] = ;end
      [*] = ;else
      [*] = ;   no_space := false;
      [*] = ;
      [*] = ;SetGameObjectIntValueIndByHandle(avar[mhHandle], gc_map_GOStack_MapUnit_iNotInBattle, 0);
      [*] = ;SetGameObjectIntValueIndByHandle(dvar[mhHandle], gc_map_GOStack_MapUnit_iNotInBattle, 0);
      [*] = ;
      [*] = ;if (wvar[mpHandle] <> 0) and (wvar[mhHandle] <> 0) then
      [*] = ;   SetPlayerIntValueIndByHandle(wvar[mpHandle],gc_map_PLStack_MapUnit_iWinCount,GetPlayerIntValueIndByHandle(wvar[mpHandle], gc_map_PLStack_MapUnit_iWinCount) + 1);
      [*] = ;
      [*] = ;if (lvar[mpHandle] <> 0) and (lvar[mhHandle] <> 0) then
      [*] = ;   SetPlayerIntValueIndByHandle(lvar[mpHandle],gc_map_PLStack_MapUnit_iLoseCount,GetPlayerIntValueIndByHandle(lvar[mpHandle], gc_map_PLStack_MapUnit_iLoseCount) + 1);
      [*] = ;
      [*] = ;if _log then _log_map('dvar[bArmy] '+IntToStr(dvar[bArmy]));
      [*] = ;if _log then _log_map('gBoolRegister_BattleEnemyFullPower '+BoolToStr(gBoolRegister_BattleEnemyFullPower));
      [*] = ;
      [*] = ;if (gIntRegister_BattleSiteID > 0) then
      [*] = ;begin
      [*] = ;   if _log then _Log_valuesM('SiteID|SiteIdx',gIntRegister_BattleSiteID,gIntRegister_BattleSiteIndex,0,0,0,0);
      [*] = ;   Assert((gIntRegister_BattleSiteIndex <> -1),'Site idx is -1 while BattleSiteID is '+IntToStr(gIntRegister_BattleSiteID));
      [*] = ;   ParserSetBoolValueByKeyByHandle(dvar[bArmy],'NeedRestore', true);
      [*] = ;   new_battle_mode := ProcessSiteBattle(gIntRegister_BattleSiteIndex,pProvince,pQueries);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if ((gIntRegister_ConflictHeroUID1 > 0) and (gIntRegister_ConflictHeroUID2 > 0)) then
      [*] = ;   begin
      [*] = ;      if _log then _log_map('ProcessHeroesBattle, ConfUID1: '+IntToStr(gIntRegister_ConflictHeroUID1)+', ConfUID2: '+IntToStr(gIntRegister_ConflictHeroUID2));
      [*] = ;      new_battle_mode := ProcessHeroesBattle();
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      case status of
      [*] = ;         0 : begin // attacker wins
      [*] = ;            var new_prov_type : Integer = 0;
      [*] = ;
      [*] = ;            if _log then _log_map('attacker wins');
      [*] = ;            var pProvGuard : Integer = ParserSelectByHandleByKey(pProvince, 'Guard');
      [*] = ;            if dvar[bArmy] = pProvGuard then
      [*] = ;            begin
      [*] = ;               if _log then _log_map('guard beaten');
      [*] = ;               var pGuard : Integer = ParserSelectByHandleByIndex(gPrototypeData.guards.handle, ParserGetIntValueByKeyByHandle(pProvGuard, 'GuardID'));
      [*] = ;               var guardPower : Integer = ParserGetIntValueByKeyByHandle(pGuard, 'Power');
      [*] = ;               if _log then _log_map('guard power '+IntToStr(guardPower));
      [*] = ;      
      [*] = ;               if (wvar[mhHandle] <> 0) and gBoolRegister_BattleEnemyFullPower {and SameText(GetPlayerControlModeByHandle(wvar[mpHandle]), 'cmPC')} then
      [*] = ;               begin
      [*] = ;                  var heroAIPower : Integer = GetGameObjectIntValueIndByHandle(wvar[mhHandle], gc_map_GOStack_MapUnit_iAIPower);
      [*] = ;                  if guardPower > heroAIPower then
      [*] = ;                     SetGameObjectIntValueIndByHandle(wvar[mhHandle], gc_map_GOStack_MapUnit_iAIPower, guardPower);
      [*] = ;               end;
      [*] = ;               
      [*] = ;               ParserClearByHandle(ParserSelectByHandleByKey(pProvGuard, 'Units'));
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if dvar[bArmy] = ParserSelectByHandleByKey(pProvince, 'Defender') then
      [*] = ;            begin
      [*] = ;               if _log then _log_map('defender beaten');
      [*] = ;               var pProvDefender : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;
      [*] = ;               ParserClearByHandle(ParserSelectByHandleByKey(pProvDefender, 'Units'));
      [*] = ;               ParserSetIntValueByKeyByHandle(pProvDefender, 'DefenderID', 0);
      [*] = ;               ParserSetIntValueByKeyByHandle(pProvDefender, 'Initiative', 0);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if dvar[bArmy] = ParserSelectByHandleByKey(pProvince, 'Garrison') then
      [*] = ;            begin
      [*] = ;               if _log then _log_map('garrison beaten');
      [*] = ;               ParserClearByHandle(ParserSelectByHandleByKey(ParserSelectByHandleByKey(pProvince, 'Garrison'), 'Units'));
      [*] = ;            end;
      [*] = ;
      [*] = ;            if avar[mpHandle] <> 0 then
      [*] = ;            begin
      [*] = ;               if (avar[mhAlive] > 0) then
      [*] = ;               begin
      [*] = ;                  var aHeroAction : Integer = GetGameObjectIntValueIndByHandle(avar[mhHandle], gc_map_GOStack_MapUnit_iActionType);
      [*] = ;                  case aHeroAction of
      [*] = ;                     gc_UnitTaskMove : begin
      [*] = ;                        IntRegister0 := pProvince;
      [*] = ;                        IntRegister1 := aHeroAction;
      [*] = ;                        IntRegister2 := -1;
      [*] = ;                        GameObjectExecuteStateByHandle(avar[mhHandle], 'GetProvEnemyArmy');
      [*] = ;                        new_army := IntRegister3;
      [*] = ;                        new_hero := IntRegister4;
      [*] = ;                        garrison := BoolRegister0;
      [*] = ;                        if _log then _log_valuesM('P_IDX|ACTION|E_ARMY|E_HERO|'+ParserGetValueByKeyByHandle(pProvince,'Player'),ParserGetIntValueByKeyByHandle(pProvince,'Index'),aHeroAction,new_army,new_hero,lvar[mhHandle],0);
      [*] = ;
      [*] = ;                        capture := true;
      [*] = ;                     end;
      [*] = ;                     gc_UnitTaskSiege : capture := true;
      [*] = ;                     else Assert(false,'Unknown action: '+IntToStr(aHeroAction));
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else // rebel or event attack
      [*] = ;            begin
      [*] = ;               var dummyHandle : Integer = GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID'));
      [*] = ;
      [*] = ;               IntRegister0 := avar[bArmy];
      [*] = ;               IntRegister1 := 0;
      [*] = ;               GameObjectExecuteStateByHandle(dummyHandle, 'GetOwnerArmy');
      [*] = ;               new_army := IntRegister2;
      [*] = ;               new_hero := IntRegister3;
      [*] = ;               garrison := BoolRegister0;
      [*] = ;
      [*] = ;               if (new_army = 0) or (garrison) then // conquer the province if no more defenders, or check siege
      [*] = ;               begin
      [*] = ;                  if gIntRegister_CurrentEventID > 0 then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := gIntRegister_CurrentEventID;
      [*] = ;                     ExecuteState('GetEventParserByID');
      [*] = ;                     j := IntRegister1;
      [*] = ;                     i := ParserGetIntValueByKeyByHandle( j, 'ProvType');
      [*] = ;
      [*] = ;                     if (i > 0) or (gIntRegister_CurrentEventID = gc_gui_query_provStartRebel) then // only certain event-attacks can cause siege.
      [*] = ;                     begin
      [*] = ;                        capture := true;
      [*] = ;                        new_prov_type := i;
      [*] = ;                        
      [*] = ;                        if garrison and (gIntRegister_CurrentEventID <> gc_gui_query_provStartRebel) then
      [*] = ;                        begin
      [*] = ;                           var p : Integer = ParserSelectByHandleByKey(ParserSelectByHandleByKey(pProvince,'Rebel'),'Guard');
      [*] = ;
      [*] = ;                           ParserSetIntValueByKeyByHandle(p,'RebelEvent',gIntRegister_CurrentEventID);
      [*] = ;                           ParserSetIntValueByKeyByHandle(p,'NewProvType',i);
      [*] = ;                           ParserSetIntValueByKeyByHandle(p,'EventWin',ParserGetIntValueByKeyByHandle(j,'EventWin'));
      [*] = ;                           ParserSetIntValueByKeyByHandle(p,'EventDraw',ParserGetIntValueByKeyByHandle(j,'EventDraw'));
      [*] = ;                           ParserSetIntValueByKeyByHandle(p,'EventLose',ParserGetIntValueByKeyByHandle(j,'EventLose'));
      [*] = ;                        end;
      [*] = ;                     end
      [*] = ;                     else // otherwise no province conquest from this event
      [*] = ;                     begin
      [*] = ;                        // event continues after this battle - no siege
      [*] = ;                        ParserClearByHandle(ParserSelectByHandleByKey(pProvince, 'Rebel'));
      [*] = ;                        new_army := 0;
      [*] = ;                        new_hero := 0;
      [*] = ;                     end;
      [*] = ;                  end
      [*] = ;                  else // normal rebellion victorious, conquer province
      [*] = ;                     capture := true;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if capture then
      [*] = ;            begin
      [*] = ;               var provPlHandle : Integer = GetPlayerHandleByName(ParserGetValueByKeyByHandle(pProvince, 'Player'));
      [*] = ;
      [*] = ;               if (new_army = 0) and (provPlHandle <> avar[mpHandle]) then
      [*] = ;               begin
      [*] = ;                  var dummyHandle : Integer = GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID'));
      [*] = ;
      [*] = ;                  if (avar[bhHandle] <> 0) then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := avar[mpHandle];
      [*] = ;                     BoolRegister0 := false;
      [*] = ;                     GameObjectExecuteStateByHandle(dummyHandle, 'CaptureProvince');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := new_prov_type;
      [*] = ;                     GameObjectExecuteStateByHandle(dummyHandle, 'GuardCaptureProvince');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         1 : begin // defender wins
      [*] = ;            if _log then _log_map('defender wins');
      [*] = ;            var pProvRebel : Integer = ParserSelectByHandleByKey(pProvince, 'Rebel');
      [*] = ;
      [*] = ;            if avar[mpHandle] = 0 then
      [*] = ;            begin
      [*] = ;               // rebel
      [*] = ;               var pGuardUnits : Integer = ParserSelectByHandleByKey(ParserSelectByHandleByKey(pProvRebel, 'Guard'), 'Units');
      [*] = ;               ParserClearByHandle(pGuardUnits);
      [*] = ;               pGuardUnits := ParserSelectByHandleByKey(ParserSelectByHandleByKey(pProvince, 'Guard'), 'Units');
      [*] = ;               ParserClearByHandle(pGuardUnits);
      [*] = ;            end;
      [*] = ;
      [*] = ;            if (avar[mpHandle] <> 0) and (avar[mhHandle] <> 0) then
      [*] = ;            begin
      [*] = ;               var provPlHandle : Integer = GetPlayerHandleByName(ParserGetValueByKeyByHandle(pProvince, 'Player'));
      [*] = ;               var pProvDefender : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;               var dummyHandle : Integer = GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID'));
      [*] = ;               var pDefUnits : Integer = ParserSelectByHandleByKey(pProvDefender, 'Units');
      [*] = ;
      [*] = ;               if (dvar[bArmy] = pProvDefender) and (avar[mpHandle] = provPlHandle) then // was not able to defeat defender
      [*] = ;               begin
      [*] = ;                  var pGarrUnits : Integer = ParserSelectByHandleByKey(ParserSelectByHandleByKey(pProvince, 'Garrison'), 'Units');
      [*] = ;
      [*] = ;                  if ParserGetCountByHandle(pGarrUnits) > 0 then
      [*] = ;                  begin
      [*] = ;                     var pRebelUnits : Integer = ParserSelectByHandleByKey(ParserSelectByHandleByKey(pProvRebel, 'Guard'), 'Units');
      [*] = ;
      [*] = ;                     ParserClearByHandle(pRebelUnits);
      [*] = ;                     ParserSelectByHandle(pRebelUnits);
      [*] = ;                     ParserCopyFromByHandle(pDefUnits);
      [*] = ;                     GameObjectExecuteStateByHandle(dummyHandle, 'DismissDefender');
      [*] = ;                     GameObjectExecuteStateByHandle(dummyHandle, 'Rebel');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     var pGuardUnits : Integer = ParserSelectByHandleByKey(ParserSelectByHandleByKey(pProvince, 'Guard'), 'Units');
      [*] = ;
      [*] = ;                     ParserClearByHandle(pGuardUnits);
      [*] = ;                     ParserSelectByHandle(pGuardUnits);
      [*] = ;                     ParserCopyFromByHandle(pDefUnits);
      [*] = ;
      [*] = ;                     GameObjectExecuteStateByHandle(dummyHandle, 'DismissDefender');
      [*] = ;
      [*] = ;                     IntRegister0 := 21;
      [*] = ;                     GameObjectExecuteStateByHandle(dummyHandle, 'GuardCaptureProvince');
      [*] = ;
      [*] = ;                     _map_RefreshProvinceHUD(GetGameObjectUniqueIdByHandle(dummyHandle));
      [*] = ;
      [*] = ;                     IntRegister0 := 0;
      [*] = ;                     GameObjectExecuteStateByHandle(dummyHandle, 'SetupPlayerFlag');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               {else
      [*] = ;               begin
      [*] = ;                  if (provPlHandle <> dvar[mpHandle]) and (dvar[mhHandle] <> 0) then // enemy tried to cancel siege
      [*] = ;                  begin
      [*] = ;                     i := GetGameObjectIntValueIndByHandle(dvar[mhHandle],gc_map_GOStack_MapUnit_iActionType);
      [*] = ;                     Assert((i = gc_UnitTaskSiege),'Wrong siege hero task: '+IntToStr(i));
      [*] = ;
      [*] = ;                     IntRegister0 := pProvince;
      [*] = ;                     IntRegister1 := i;
      [*] = ;                     IntRegister2 := -1;
      [*] = ;                     GameObjectExecuteStateByHandle(dvar[mhHandle], 'GetProvEnemyArmy');
      [*] = ;                     new_army := IntRegister3;
      [*] = ;                     new_hero := IntRegister4;
      [*] = ;                     garrison := BoolRegister0;
      [*] = ;                     if _log then _log_valuesM('P_IDX|ACTION|E_ARMY|E_HERO|'+ParserGetValueByKeyByHandle(pProvince,'Player'),ParserGetIntValueByKeyByHandle(pProvince,'Index'),i,new_army,new_hero,lvar[mhHandle],0);
      [*] = ;
      [*] = ;                     if (new_army = 0) and (provPlHandle <> dvar[mpHandle]) then
      [*] = ;                     begin
      [*] = ;                        Assert((dvar[bhHandle] <> 0),'Siege by NULL hero');
      [*] = ;                        IntRegister0 := dvar[mpHandle];
      [*] = ;                        BoolRegister0 := false;
      [*] = ;                        GameObjectExecuteStateByHandle(dummyHandle, 'CaptureProvince');
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;}
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         2 : begin // draw
      [*] = ;            if _log then _log_map('draw');
      [*] = ;            if dvar[bArmy] = ParserSelectByHandleByKey(pProvince, 'Guard') then
      [*] = ;            begin
      [*] = ;               if _log then _log_map('guard draw');
      [*] = ;               ParserClearByHandle(ParserSelectByHandleByKey(ParserSelectByHandleByKey(pProvince, 'Guard'), 'Units'));
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if dvar[bArmy] = ParserSelectByHandleByKey(pProvince, 'Defender') then
      [*] = ;               begin
      [*] = ;                  if _log then _log_map('defender draw');
      [*] = ;                  var pProvDefender : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;
      [*] = ;                  ParserClearByHandle(ParserSelectByHandleByKey(pProvDefender, 'Units'));
      [*] = ;                  ParserSetIntValueByKeyByHandle(pProvDefender, 'DefenderID', 0);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pProvDefender, 'Initiative', 0);
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if _log then _log_map('garrison draw');
      [*] = ;                  if dvar[bArmy] = ParserSelectByHandleByKey(pProvince, 'Garrison') then
      [*] = ;                     ParserClearByHandle(ParserSelectByHandleByKey(ParserSelectByHandleByKey(pProvince, 'Garrison'), 'Units'));
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if avar[mpHandle] = 0 then
      [*] = ;            begin
      [*] = ;               // rebel
      [*] = ;               var pProvRebel : Integer = ParserSelectByHandleByKey(pProvince, 'Rebel');
      [*] = ;               var pGuardUnits : Integer = ParserSelectByHandleByKey(ParserSelectByHandleByKey(pProvRebel, 'Guard'), 'Units');
      [*] = ;               ParserClearByHandle(pGuardUnits);
      [*] = ;               pGuardUnits := ParserSelectByHandleByKey(ParserSelectByHandleByKey(pProvince, 'Guard'), 'Units');
      [*] = ;               ParserClearByHandle(pGuardUnits);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      new_battle_mode := 0;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;ParserClearByHandle(ParserSelectByHandleByKey(pProvince, 'EncounterGuard'));
      [*] = ;
      [*] = ;CheckQuestEncounters(wvar[mhHandle], true, pQueries);
      [*] = ;CheckQuestEncounters(lvar[mhHandle], false, pQueries);
      [*] = ;
      [*] = ;//if FreeDeadUnits(gIntRegister_BattleAttackArmy) and (avar[bhHandle] <> 0) and (avar[mpHandle] <> 0) then
      [*] = ;//   SetPlayerBoolValueIndByHandle(avar[mpHandle], gc_map_PLStack_MapUnit_bNoLoss, false);
      [*] = ;
      [*] = ;//if FreeDeadUnits(gIntRegister_BattleDefendArmy) and (dvar[bhHandle] <> 0) and (dvar[mpHandle] <> 0) then
      [*] = ;//   SetPlayerBoolValueIndByHandle(dvar[mpHandle], gc_map_PLStack_MapUnit_bNoLoss, false);
      [*] = ;
      [*] = ;if new_army <> 0 then
      [*] = ;begin
      [*] = ;   if new_hero <> 0 then
      [*] = ;   begin
      [*] = ;      var provPlHandle : Integer = GetPlayerHandleByName(ParserGetValueByKeyByHandle(pProvince, 'Player'));
      [*] = ;      var new_player : Integer = GetGameObjectPlayerHandleByHandle(new_hero);
      [*] = ;
      [*] = ;      if new_player = provPlHandle then
      [*] = ;         new_battle_mode := 1
      [*] = ;      else
      [*] = ;         new_battle_mode := 4;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      Assert((status=0),'Wrong battle status: '+IntToStr(status));
      [*] = ;
      [*] = ;      if (ParserGetIntValueByKeyByHandle(new_army, 'DefenderID') > 0) or (not garrison) then
      [*] = ;         new_battle_mode := 2
      [*] = ;      else
      [*] = ;         new_battle_mode := 3; // siege
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if _log then _Log_map(_log_name+' NewBattle = '+ IntToStr(new_battle_mode));
      [*] = ;gBoolRegister_BattleEnemyFullPower := false;
      [*] = ;
      [*] = ;if new_battle_mode = 0 then
      [*] = ;begin
      [*] = ;// after battle encounters
      [*] = ;   if ((wvar[mpHandle] <> 0) and (lvar[mpHandle] = 0)) or ((lvar[mpHandle] <> 0) and (wvar[mpHandle] = 0)) then
      [*] = ;   begin
      [*] = ;      if status = 2 then
      [*] = ;         i := 2
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if wvar[mpHandle] <> 0 then
      [*] = ;            i := 0
      [*] = ;         else
      [*] = ;            i := 1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if _log then _Log_map('gIntRegister_CurrentEncounterID '+IntToStr(gIntRegister_CurrentEncounterID));
      [*] = ;      if gIntRegister_CurrentEncounterID > 0 then
      [*] = ;      begin
      [*] = ;         var pEncounter : Integer = ParserSelectByHandleByIndex(gPrototypeData.encounters.handle, gIntRegister_CurrentEncounterID - gc_query_EncounterMinIndex);
      [*] = ;         if _log then _Log_map('pEncounter '+IntToStr(pEncounter));
      [*] = ;
      [*] = ;         case i of
      [*] = ;            0  : gIntRegister_AfterBattleEncounterID := ParserGetIntValueByKeyByHandle(pEncounter, 'EncWin');
      [*] = ;            2  : gIntRegister_AfterBattleEncounterID := ParserGetIntValueByKeyByHandle(pEncounter, 'EncDraw');
      [*] = ;            1 : gIntRegister_AfterBattleEncounterID := ParserGetIntValueByKeyByHandle(pEncounter, 'EncLose');
      [*] = ;         end;
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvince, 'EncWin', 0);
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvince, 'EncDraw', 0);
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvince, 'EncLose', 0);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if _log then _Log_map('gIntRegister_CurrentEventID '+IntToStr(gIntRegister_CurrentEventID));
      [*] = ;         if gIntRegister_CurrentEventID > 0 then // check after battle event
      [*] = ;         begin
      [*] = ;            var pEvent : Integer = ParserSelectByHandleByIndex(gPrototypeData.events.handle, gIntRegister_CurrentEventID - gc_query_EventMinIndex);
      [*] = ;            if _log then _Log_map('pEvent '+IntToStr(pEvent));
      [*] = ;
      [*] = ;            case i of
      [*] = ;               0  : gIntRegister_AfterBattleEventID := ParserGetIntValueByKeyByHandle(pEvent, 'EventWin');
      [*] = ;               2  : gIntRegister_AfterBattleEventID := ParserGetIntValueByKeyByHandle(pEvent, 'EventDraw');
      [*] = ;               1 : gIntRegister_AfterBattleEventID := ParserGetIntValueByKeyByHandle(pEvent, 'EventLose');
      [*] = ;            end;
      [*] = ;            ParserSetIntValueByKeyByHandle(pProvince, 'EventWin', 0);
      [*] = ;            ParserSetIntValueByKeyByHandle(pProvince, 'EventDraw', 0);
      [*] = ;            ParserSetIntValueByKeyByHandle(pProvince, 'EventLose', 0);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if gIntRegister_BattleSiteID > 0 then // site
      [*] = ;            begin
      [*] = ;               if status = 0 then
      [*] = ;               begin
      [*] = ;                  var pSite,pSiteAbilities,id : Integer;
      [*] = ;
      [*] = ;                  pSite := ParserSelectByHandleByIndex(gPrototypeData.sites.handle, gIntRegister_BattleSiteID);
      [*] = ;                  pSiteAbilities := ParserSelectByHandleByKey(pSite, 'Abilities');
      [*] = ;
      [*] = ;                  for i := ParserGetCountByHandle(pSiteAbilities)-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     id := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pSiteAbilities, i), 'AbilityID');
      [*] = ;                     if id = 17 then
      [*] = ;                     begin
      [*] = ;                        gIntRegister_AfterBattleEncounterID := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pSiteAbilities, i), 'Param1');
      [*] = ;                        break;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  gIntRegister_AfterBattleEncounterID := 0;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               case i of
      [*] = ;                  0  : gIntRegister_AfterBattleEventID := ParserGetIntValueByKeyByHandle(pProvince, 'EventWin');
      [*] = ;                  2  : gIntRegister_AfterBattleEventID := ParserGetIntValueByKeyByHandle(pProvince, 'EventDraw');
      [*] = ;                  1 : gIntRegister_AfterBattleEventID := ParserGetIntValueByKeyByHandle(pProvince, 'EventLose');
      [*] = ;               end;
      [*] = ;
      [*] = ;               ParserSetIntValueByKeyByHandle(pProvince, 'EventWin', 0);
      [*] = ;               ParserSetIntValueByKeyByHandle(pProvince, 'EventDraw', 0);
      [*] = ;               ParserSetIntValueByKeyByHandle(pProvince, 'EventLose', 0);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if _log then _Log_map('gIntRegister_AfterBattleEncounterID '+IntToStr(gIntRegister_AfterBattleEncounterID));
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if ((new_battle_mode = 0) or (new_battle_mode = 3)) and (not gBoolRegister_BattleIsSiege) then
      [*] = ;begin
      [*] = ;   // decrease unrest and population after rebel
      [*] = ;   if (avar[mpHandle] = 0) and ((gIntRegister_CurrentEventID = 0) or (gIntRegister_CurrentEventID = gc_gui_query_provStartRebel)) then
      [*] = ;   begin
      [*] = ;      var dummyHandle : Integer = GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID'));
      [*] = ;      IntRegister0 := GetPlayerIndexByHandle(GetPlayerHandleByName(ParserGetValueByKeyByHandle(pProvince, 'Player')));
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle, 'AfterRebel');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// we have to reverse attack/defend sides if after attack of the hero who is doing the siege defeated
      [*] = ;{if (new_battle_mode = 3) and (status = 1) and (dvar[mpHandle] <> 0) and (dvar[mhHandle] <> 0) then
      [*] = ;begin
      [*] = ;   i := GetGameObjectIntValueIndByHandle(dvar[mhHandle], gc_map_GOStack_MapUnit_iActionType);
      [*] = ;   if i = gc_UnitTaskSiege then
      [*] = ;   begin
      [*] = ;      gIntRegister_BattleAttackPlayer := dvar[mpHandle];
      [*] = ;      gIntRegister_BattleDefendPlayer := avar[mpHandle];
      [*] = ;
      [*] = ;      gIntRegister_BattleAttackHeroHandle := dvar[mhHandle];
      [*] = ;      gIntRegister_BattleDefendHeroHandle := avar[mhHandle];
      [*] = ;
      [*] = ;      gIntRegister_BattleAttackArmy := dvar[bArmy];
      [*] = ;      gIntRegister_BattleDefendArmy := avar[bArmy]; 
      [*] = ;   end;
      [*] = ;end;}
      [*] = ;
      [*] = ;// set playable = false
      [*] = ;for j := 0 to 1 do
      [*] = ;begin
      [*] = ;   if j = 0 then p := avar[bpHandle]
      [*] = ;   else p := dvar[bpHandle];
      [*] = ;
      [*] = ;   for i := GetPlayerGameObjectsCountByHandle(p)-1 downto 0 do
      [*] = ;      SetGameObjectPlayableObjectByHandle(GetGameObjectHandleByIndex(i,p),false);
      [*] = ;end;
      [*] = ;
      [*] = ;gIntRegister_NewBattle :=  new_battle_mode;
      [*] = ;
      [*] = ;if (not no_space) and ((gIntRegister_CurQueryHandle = 0) or (QueryMachineIsExecutedEvent() = true)) then
      [*] = ;   ExecuteState('bat.CheckNewBattle');
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(gIntRegister_NewBattle)+']',$1000000 or _log_trace);
   struct.end
section.end

