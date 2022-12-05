section.begin
   Name = bat.AddUnitsExperience
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\BAT\BAT.ADDUNITSEXPERIENCE';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;ExecuteState('bat.GetWinPlayerHandle');
      [*] = ;var winPlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;procedure CheckQuests(battleHeroHandle,enemyArmyParser : Integer);
      [*] = ;begin
      [*] = ;   GameObjectExecuteStateByHandle(battleHeroHandle, 'GetMapHandles');
      [*] = ;   if IntRegister0 <> 0 then
      [*] = ;   begin
      [*] = ;      var i,j,k,pHeroParser,pHeroQuests,pArmyUnits,pArmyUnit: Integer;
      [*] = ;      var cMode : String;
      [*] = ;      var human_player : Boolean;
      [*] = ;
      [*] = ;      cMode := GetPlayerControlModeByHandle( IntRegister1 );
      [*] = ;      pHeroParser := ParserSelectGameObject( IntRegister0 );
      [*] = ;      pHeroQuests := ParserSelectByHandleByKey(pHeroParser, 'Quests');
      [*] = ;      human_player := SameText(cMode, 'cmPlayer');
      [*] = ;
      [*] = ;      pArmyUnits := ParserSelectByHandleByKey(enemyArmyParser, 'Units');
      [*] = ;
      [*] = ;      if _log then _Log_valuesM(cMode+'|HeroParser|EnemyArmyNo',ParserGetCountByHandle(pHeroQuests),pHeroParser,ParserGetCountByHandle(pArmyUnits),0,0,0);
      [*] = ;      for i := ParserGetCountByHandle(pArmyUnits)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pArmyUnit : Integer = ParserSelectByHandleByIndex(pArmyUnits, i);
      [*] = ;
      [*] = ;         if ParserGetIntValueByKeyByHandle(pArmyUnit, 'CurLife') = 0 then
      [*] = ;         begin
      [*] = ;            var isHero : Boolean = ParserGetBoolValueByKeyByHandle(pArmyUnit, 'IsHero');
      [*] = ;            var unitID : Integer = ParserGetIntValueByKeyByHandle(pArmyUnit, 'UnitID');
      [*] = ;
      [*] = ;            // Check for kill units quests
      [*] = ;            for j := ParserGetCountByHandle(pHeroQuests)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var pHeroQuest : Integer = ParserSelectByHandleByIndex(pHeroQuests, j);
      [*] = ;               var questComplete : Boolean = ParserGetBoolValueByKeyByHandle(pHeroQuest, 'Complete');
      [*] = ;
      [*] = ;               if not questComplete then
      [*] = ;               begin
      [*] = ;                  var pHeroArProgress : Integer = ParserSelectByHandleByKey(pHeroQuest, 'ArProgress');
      [*] = ;                  var questID : Integer = ParserGetIntValueByKeyByHandle(pHeroQuest, 'Index');
      [*] = ;                  var pQuest : Integer = ParserSelectByHandleByIndex(gPrototypeData.quests.handle, questID);
      [*] = ;                  var pQuestObjectives : Integer = ParserSelectByHandleByKey(pQuest, 'Objectives');
      [*] = ;                  var qType : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'Type');
      [*] = ;
      [*] = ;                  case qType of
      [*] = ;                     2, 3 : begin
      [*] = ;                        if _log then _Log_map(' Quest for unit found: '+IntToStr(unitID));
      [*] = ;                        for k := ParserGetCountByHandle(pQuestObjectives)-1 downto 0 do
      [*] = ;                        begin
      [*] = ;                           var pQuestObjective : Integer = ParserSelectByHandleByIndex(pQuestObjectives, k);
      [*] = ;                           var param : Integer = ParserGetIntValueByKeyByHandle(pQuestObjective, 'Param');
      [*] = ;
      [*] = ;                           if ParserGetIntValueByKeyByHandle(pQuestObjective, 'Index') = unitID then
      [*] = ;                           begin
      [*] = ;                              if (qType = 3) or (param = 0) or (_rand_Random(100) < param) then
      [*] = ;                              begin
      [*] = ;                                 var pHeroProgress : Integer = ParserSelectByHandleByIndex(pHeroArProgress, k);
      [*] = ;                                 var progress : Integer = ParserGetIntValueByKeyByHandle(pHeroProgress, 'Progress');
      [*] = ;                                 progress := progress + 1;
      [*] = ;                                 if _log then _Log_map('  New progress value: '+IntToStr(progress));
      [*] = ;                                 ParserSetIntValueByKeyByHandle(pHeroProgress, 'Progress', progress);
      [*] = ;                                 ParserSetIntValueByKeyByHandle(pHeroQuest, 'Found', 1);
      [*] = ;                              end
      [*] = ;                              else
      [*] = ;                              begin
      [*] = ;                                 if ParserGetIntValueByKeyByHandle(pHeroQuest, 'Found') <> 1 then
      [*] = ;                                     ParserSetIntValueByKeyByHandle(pHeroQuest, 'Found', -1);
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                     8 : begin
      [*] = ;                        var pProvince : Integer = ParserSelectByHandleByIndex(gStratHexCells.handle, ParserGetIntValueByKeyByHandle(pHeroQuest, 'ProvIndex'));
      [*] = ;                        var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;                        var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, ParserGetIntValueByKeyByHandle(pHeroQuest, 'SiteIndex'));
      [*] = ;
      [*] = ;                        if ParserGetIntValueByKeyByHandle(pProvSite, 'Level') = unitID then
      [*] = ;                        begin
      [*] = ;                           var pHeroProgress : Integer = ParserSelectByHandleByIndex(pHeroArProgress, 0);
      [*] = ;                           var progress : Integer = ParserGetIntValueByKeyByHandle(pHeroProgress, 'Progress');
      [*] = ;                           progress := progress + 1;
      [*] = ;                           ParserSetIntValueByKeyByHandle(pHeroProgress, 'Progress', progress);
      [*] = ;                           ParserSetIntValueByKeyByHandle(pHeroQuest, 'Found', 1);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if human_player and (gGame.gameType = gc_GameTypeCampaign) and (gCampaign.arrDialogs[687] > 0) then
      [*] = ;            begin
      [*] = ;               case unitID of
      [*] = ;                  21 : gCampaign.arrItems[3] := gCampaign.arrItems[3] + 1;
      [*] = ;                  37, 38 : gCampaign.arrItems[3] := gCampaign.arrItems[3] + 3;
      [*] = ;                  56 : gCampaign.arrItems[3] := gCampaign.arrItems[3] + 7;
      [*] = ;                  65 : gCampaign.arrItems[3] := gCampaign.arrItems[3] + 15;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ProcessPlayer(plHandle, heroHandle : Integer);
      [*] = ;begin
      [*] = ;   // add win player units experience
      [*] = ;   if winPlHandle <> 0 then
      [*] = ;   begin
      [*] = ;      BoolRegister0 := false;
      [*] = ;      PlayerExecuteStateByHandle(plHandle, 'IsAlive');
      [*] = ;      if BoolRegister0 then
      [*] = ;      begin
      [*] = ;         GameObjectExecuteStateByHandle(heroHandle, 'GetMapHandles');
      [*] = ;         var mapPlHandle : Integer = IntRegister1;
      [*] = ;         //var mapPlIndex : Integer = GetPlayerIndexByHandle( mapPlHandle );
      [*] = ;
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'AddUnitsExperience');
      [*] = ;         if (gBoolRegister_IsDefenderBattle and (not gBoolRegister_IsDefenderAutoBattle)) or (not SameText(GetPlayerControlModeByHandle(mapPlHandle), 'cmPlayer')) then
      [*] = ;            PlayerExecuteStateByHandle(plHandle, 'MakeUpgrades');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   PlayerExecuteStateByHandle(plHandle, 'AfterBattle');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CloseDeadIndex(plHandle, index : Integer);
      [*] = ;begin
      [*] = ;   var i, curInd : Integer;
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(index, plHandle);
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iArmyIndex, -1);
      [*] = ;   
      [*] = ;   for i := index+1 to GetPlayerGameObjectsCountByHandle(plHandle)-1 do
      [*] = ;   begin
      [*] = ;      goHandle := GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;      curInd := GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iArmyIndex);
      [*] = ;      SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iArmyIndex, curInd-1);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure FreeDeadUnits(plHandle, heroHandle, pArmyParser : Integer);
      [*] = ;begin
      [*] = ;   var i,pArmyUnits,pArmyUnit : Integer;
      [*] = ;   var mapPlHandle : Integer = 0;
      [*] = ;
      [*] = ;   pArmyUnits := ParserSelectByHandleByKey(pArmyParser, 'Units');
      [*] = ;   if heroHandle <> 0 then
      [*] = ;   begin
      [*] = ;      GameObjectExecuteStateByHandle(heroHandle, 'GetMapHandles');
      [*] = ;      //mapHeroHandle := IntRegister0;
      [*] = ;      mapPlHandle := IntRegister1;
      [*] = ;      if not GetPlayerBoolValueIndByHandle(mapPlHandle, gc_map_PLStack_MapUnit_bNoLoss) then
      [*] = ;         mapPlHandle := 0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pArmyUnits)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      pArmyUnit := ParserSelectByHandleByIndex(pArmyUnits, i);
      [*] = ;
      [*] = ;      if (ParserGetIntValueByKeyByHandle(pArmyUnit, 'CurLife') = 0) then
      [*] = ;      begin
      [*] = ;         if not ParserGetBoolValueByKeyByHandle(pArmyUnit,'IsHero') then
      [*] = ;         begin
      [*] = ;            ParserFreeByHandle(pArmyUnit);
      [*] = ;            CloseDeadIndex(plHandle, i);
      [*] = ;         end;
      [*] = ;
      [*] = ;         if mapPlHandle <> 0 then
      [*] = ;            SetPlayerBoolValueIndByHandle(mapPlHandle, gc_map_PLStack_MapUnit_bNoLoss, false);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var aPlHandle : Integer = GetPlayerHandleByName(gc_battle_attackPlayerName);
      [*] = ;var dPlHandle : Integer = GetPlayerHandleByName(gc_battle_defendPlayerName);
      [*] = ;var aHeroHandle, dHeroHandle : Integer;
      [*] = ;
      [*] = ;PlayerExecuteStateByHandle(aPlHandle, 'GetHeroHandle');
      [*] = ;aHeroHandle := IntRegister0;
      [*] = ;
      [*] = ;PlayerExecuteStateByHandle(dPlHandle, 'GetHeroHandle');
      [*] = ;dHeroHandle := IntRegister0;
      [*] = ;
      [*] = ;ProcessPlayer(aPlHandle,aHeroHandle);
      [*] = ;ProcessPlayer(dPlHandle,dHeroHandle);
      [*] = ;
      [*] = ;if dHeroHandle <> 0 then
      [*] = ;   CheckQuests(dHeroHandle,gIntRegister_BattleAttackArmy);
      [*] = ;if aHeroHandle <> 0 then
      [*] = ;   CheckQuests(aHeroHandle,gIntRegister_BattleDefendArmy);
      [*] = ;
      [*] = ;if _log and (gIntRegister_GVLogging <> gc_gvlog_log_none) then
      [*] = ;begin
      [*] = ;   ParserSaveToFileByHandle(gIntRegister_BattleAttackArmy,'.\log\after_battle_attack.dat');
      [*] = ;   ParserSaveToFileByHandle(gIntRegister_BattleDefendArmy,'.\log\after_battle_defend.dat');
      [*] = ;end;
      [*] = ;
      [*] = ;FreeDeadUnits(aPlHandle, aHeroHandle, gIntRegister_BattleAttackArmy);
      [*] = ;FreeDeadUnits(dPlHandle, dHeroHandle, gIntRegister_BattleDefendArmy);
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

