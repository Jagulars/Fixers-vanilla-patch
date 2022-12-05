section.begin
   Name = AttackTargetProvince
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.UNIT.INC\ATTACKTARGETPROVINCE';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;var pMyParser : Integer =  ParserSelectGameObject(myGOHandle);
      [*] = ;var pMyUnits : Integer = ParserSelectByHandleByKey(pMyParser, 'Units');
      [*] = ;
      [*] = ;var unionRace : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iUnion);
      [*] = ;var plDiff : Integer = gGame.arrplayerdifficulty[myPlIndex].basediff;
      [*] = ;var pDifficulty : Integer = ParserSelectByHandleByIndex(gPrototypeData.difficulty.handle, plDiff);
      [*] = ;var heroAdvice : Boolean = ParserGetBoolValueByKeyByHandle(pDifficulty, 'HeroAdvice');
      [*] = ;
      [*] = ;var tarUID : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iTargetUID);
      [*] = ;var dummyHandle : Integer = GetGameObjectHandleByUniqueId(tarUID);
      [*] = ;
      [*] = ;var pProvince : Integer = _misc_GetProvinceParserByUID(tarUID);
      [*] = ;var pProvGuard : Integer = ParserSelectByHandleByKey(pProvince, 'Guard');
      [*] = ;var provRace : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceRace');
      [*] = ;var provType : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceType');
      [*] = ;var pProvDefender : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(tarUID)+']',_log_trace);
      [*] = ;
      [*] = ;IntRegister0 := myPlIndex;
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'GetPlayerIndex');
      [*] = ;var provPlIndex : Integer = IntRegister1;
      [*] = ;var provPlHandle : Integer = GetPlayerHandleByIndex(provPlIndex);
      [*] = ;var provCMode : String = GetPlayerControlModeByHandle(provPlHandle);
      [*] = ;
      [*] = ;var isCastle : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;var pProvGarrison : Integer = ParserSelectByHandleByKey(pProvince, 'Garrison');
      [*] = ;
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'IsGarrison');
      [*] = ;var isGarrison : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'IsUnderSiege');
      [*] = ;var isSiege : Boolean = BoolRegister0;
      [*] = ;var siegePlHandle : Integer = IntRegister0;
      [*] = ;var siegePlIndex : Integer = GetPlayerIndexByHandle(siegePlHandle);
      [*] = ;
      [*] = ;gIntRegister_MapBattleProvince := pProvince;
      [*] = ;
      [*] = ;IntRegister0 := pProvince;
      [*] = ;MapExecuteState('map.GetProvinceName');
      [*] = ;gStringRegister_ProvinceName := StringRegister0;
      [*] = ;
      [*] = ;gBoolRegister_QueryBribeGuard := false;
      [*] = ;
      [*] = ;if SameText(cMode, 'cmPlayer') then
      [*] = ;begin
      [*] = ;   _hero_GetName(myGOHandle, gStringRegister_MyHeroName);
      [*] = ;
      [*] = ;   if provPlHandle <> 0 then
      [*] = ;      PlayerExecuteStateByHandle(provPlHandle, 'GetName')
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var idx : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'LastPlayer');
      [*] = ;      if idx >= 0 then
      [*] = ;         idx := GetPlayerHandleByIndex(idx);
      [*] = ;      if idx > 0 then
      [*] = ;         PlayerExecuteStateByHandle(idx, 'GetName')
      [*] = ;      else
      [*] = ;         StringRegister0 := GetLocaleTableListItemByID('gui', '323');
      [*] = ;   end;
      [*] = ;   gStringRegister_EnemyPlayerName := StringRegister0;
      [*] = ;
      [*] = ;   IntRegister0 := 12;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'CheckRitualEffect');
      [*] = ;   if BoolRegister0 then
      [*] = ;   begin
      [*] = ;      StringRegister0 := IntToStr(gc_gui_query_heroProvinceMagicBarrier);
      [*] = ;      BoolRegister0 := true;
      [*] = ;      PlayerExecuteStateByHandle(myPlHandle, 'CheckRequestQuery');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      IntRegister0 := pProvince;
      [*] = ;      IntRegister1 := GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iActionType);
      [*] = ;      IntRegister2 := GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iSiteIndex);
      [*] = ;      ExecuteState('GetProvEnemyArmy');
      [*] = ;      var pGuard : Integer = IntRegister3;
      [*] = ;      var enGOHandle : Integer = IntRegister4;
      [*] = ;      var defCount : Integer = IntRegister5;
      [*] = ;
      [*] = ;      gIntRegister_BattleAttackArmy := pMyParser;
      [*] = ;      gIntRegister_BattleAttackHeroHandle := myGOHandle;
      [*] = ;      gIntRegister_BattleAttackPlayer := myPlHandle;
      [*] = ;
      [*] = ;      gIntRegister_BattleDefendArmy := pGuard;
      [*] = ;      gIntRegister_BattleDefendHeroHandle := enGOHandle;
      [*] = ;      gIntRegister_BattleDefendPlayer := GetGameObjectPlayerHandleByHandle(enGOHandle);
      [*] = ;
      [*] = ;      var batResult : Integer = 100;
      [*] = ;      if (not gBoolRegister_ShowPlayerHint) and (pGuard <> 0) and ((heroAdvice and (pGuard <> pProvGarrison)) or (pGuard = pProvDefender)) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := pProvince;
      [*] = ;         IntRegister1 := -1;
      [*] = ;         BoolRegister0 := false;
      [*] = ;         BoolRegister1 := false;
      [*] = ;         ExecuteState('AdvCompareArmiesStrength');
      [*] = ;         batResult := IntRegister2;
      [*] = ;
      [*] = ;         gIntRegister_VirtualBattleResult := batResult;
      [*] = ;
      [*] = ;         if heroAdvice then
      [*] = ;            gBoolRegister_ShowAdvice := true;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var pGuardUnits : Integer = ParserSelectByHandleByKey(pGuard, 'Units');
      [*] = ;      IntRegister0 := pGuardUnits;
      [*] = ;      MapExecuteState('map.GetArmyUnitsCount');
      [*] = ;      var enArmyCount : Integer = IntRegister1;
      [*] = ;
      [*] = ;      IntRegister0 := pGuardUnits;
      [*] = ;      MapExecuteState('map.GetArmyUnitsList');
      [*] = ;      var enArmyList : String = StringRegister0;
      [*] = ;
      [*] = ;      if enGOHandle <> 0 then
      [*] = ;      begin
      [*] = ;         gIntRegister_EnemyHeroArmyCount := enArmyCount;
      [*] = ;         gStringRegister_EnemyHeroArmyList := enArmyList;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if pGuard = pProvGuard then
      [*] = ;         begin
      [*] = ;            gIntRegister_GuardEnemyCount := enArmyCount;
      [*] = ;            gStringRegister_GuardEnemyList := enArmyList;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            gIntRegister_DefenderEnemyCount := enArmyCount;
      [*] = ;            gStringRegister_DefenderEnemyList := enArmyList;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if ParserGetCountByHandle(pGuardUnits) = 0 then
      [*] = ;      begin
      [*] = ;         BoolRegister0 := true;
      [*] = ;         StringRegister0 := IntToStr(gc_gui_query_heroAttackProvNoGuard);
      [*] = ;         PlayerExecuteStateByHandle(myPlHandle, 'CheckRequestQuery');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (pGuard = pProvGarrison) then
      [*] = ;         begin
      [*] = ;            BoolRegister0 := true;
      [*] = ;            StringRegister0 := IntToStr(gc_gui_query_heroStartSiege);
      [*] = ;            PlayerExecuteStateByHandle(myPlHandle, 'CheckRequestQuery');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if enGOHandle <> 0 then
      [*] = ;            begin
      [*] = ;               if isSiege then
      [*] = ;               begin
      [*] = ;                  PlayerExecuteStateByHandle(siegePlHandle, 'GetName');
      [*] = ;                  gStringRegister_EnemyPlayerName := StringRegister0;
      [*] = ;
      [*] = ;                  if enGOHandle <> 0 then
      [*] = ;                     _hero_GetName(enGOHandle, gStringRegister_EnemyHeroName);
      [*] = ;
      [*] = ;                  BoolRegister0 := true;
      [*] = ;                  StringRegister0 := IntToStr(gc_gui_query_heroAttackSiegePlayer);
      [*] = ;                  PlayerExecuteStateByHandle(myPlHandle, 'CheckRequestQuery');
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  _hero_GetName(enGOHandle, gStringRegister_EnemyHeroName);
      [*] = ;
      [*] = ;                  if _misc_IsProvinceNeutral(pProvince) then
      [*] = ;                  begin
      [*] = ;                     var enPlHandle : Integer = GetGameObjectPlayerHandleByHandle(enGOHandle);
      [*] = ;                     PlayerExecuteStateByHandle(enPlHandle, 'GetName');
      [*] = ;                     gStringRegister_EnemyPlayerName := StringRegister0;
      [*] = ;
      [*] = ;                     StringRegister0 := IntToStr(gc_gui_query_heroAttackPassableProvince);
      [*] = ;                     BoolRegister0 := true;
      [*] = ;                     PlayerExecuteStateByHandle(myPlHandle, 'CheckRequestQuery');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     StringRegister0 := IntToStr(gc_gui_query_heroAttackProvEnemyHero);
      [*] = ;                     BoolRegister0 := true;
      [*] = ;                     PlayerExecuteStateByHandle(myPlHandle, 'CheckRequestQuery');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if pGuard = pProvGuard then
      [*] = ;            begin
      [*] = ;               if isSiege then
      [*] = ;               begin
      [*] = ;                  BoolRegister0 := true;
      [*] = ;                  StringRegister0 := IntToStr(gc_gui_query_heroAttackSiegeRebel);
      [*] = ;                  PlayerExecuteStateByHandle(myPlHandle, 'CheckRequestQuery');
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  var pProvinceType : Integer = ParserSelectByHandleByIndex(gPrototypeData.provinceTypes.handle, provType);
      [*] = ;                  var typeRace : Integer = ParserGetIntValueByKeyByHandle(pProvinceType, 'RaceID');
      [*] = ;
      [*] = ;                  if (provRace > 0) and (provRace = unionRace) and (typeRace = unionRace) then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := ParserGetIntValueByKeyByHandle(pGuard, 'Encounter');
      [*] = ;                     ExecuteState('ProceedEncounter');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     StringRegister0 := ParserGetValueByKeyByHandle(pGuard, 'Dialog');
      [*] = ;                     BoolRegister0 := true;
      [*] = ;                     PlayerExecuteStateByHandle(myPlHandle, 'CheckRequestQuery');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if pGuard = pProvDefender then
      [*] = ;            begin
      [*] = ;               var defID : Integer = ParserGetIntValueByKeyByHandle(pProvDefender, 'DefenderID');
      [*] = ;               var pDefender : Integer = ParserSelectByHandleByIndex(gPrototypeData.defenders.handle, defID);
      [*] = ;
      [*] = ;               IntRegister0 := defID;
      [*] = ;               IntRegister1 := 11;
      [*] = ;               MapExecuteState('CheckDefenderAbility');
      [*] = ;               var value : Integer = IntRegister2;
      [*] = ;
      [*] = ;               var queryID : String = '';
      [*] = ;               if (not isCastle) and (value = 0) and (batResult > 180 + _rand_Random(10)) then
      [*] = ;               queryID := IntToStr(gc_gui_query_heroEnemyDefRetreat)
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  IntRegister0 := defID;
      [*] = ;                  IntRegister1 := 12;
      [*] = ;                  MapExecuteState('CheckDefenderAbility');
      [*] = ;                  var value12 : Integer = IntRegister2;
      [*] = ;
      [*] = ;                  IntRegister0 := 27;
      [*] = ;                  ExecuteState('CheckAbility');
      [*] = ;                  var value27 : Integer = IntRegister1;
      [*] = ;
      [*] = ;                  if (defCount <= 1) and (not isGarrison) and (value12 = 0) and (batResult > 160 + _rand_Random(10) - value27 * 2) then
      [*] = ;                  begin
      [*] = ;                     var dGoldCost : Integer = ParserGetIntValueByKeyByHandle(pDefender, 'GoldCost');
      [*] = ;                     var dGemCost : Integer = ParserGetIntValueByKeyByHandle(pDefender, 'GemCost');
      [*] = ;
      [*] = ;                     var brGold : Integer = dGoldCost * 4 + dGemCost * 10;
      [*] = ;                     if brGold <=0 then
      [*] = ;                     begin
      [*] = ;                        IntRegister0 := ParserSelectByHandleByKey(pProvDefender, 'Units');
      [*] = ;                        MapExecuteState('GetDefArmyPayment');
      [*] = ;                        brGold := IntRegister1 * 25 + IntRegister2 * 50;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     brGold := (brGold * (10 - value27)) div 10;
      [*] = ;
      [*] = ;                     gBoolRegister_QueryBribeGuard := true;
      [*] = ;                     gIntRegister_GoldCost := brGold;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  queryID := IntToStr(gc_gui_query_heroAttackProvDefender);
      [*] = ;               end;
      [*] = ;
      [*] = ;               if queryID <> '' then
      [*] = ;               begin
      [*] = ;                  StringRegister0 := queryID;
      [*] = ;                  BoolRegister0 := true;
      [*] = ;                  PlayerExecuteStateByHandle(myPlHandle, 'CheckRequestQuery');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   IntRegister0 := 12;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'CheckRitualEffect');
      [*] = ;   if BoolRegister0 then
      [*] = ;   begin
      [*] = ;      BoolRegister0 := false;
      [*] = ;      ExecuteState('RetreatGuard');
      [*] = ;      _gv_SetMapLock($10000,_log_name);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      ExecuteState('SetupEnemyRegisters');
      [*] = ;
      [*] = ;      IntRegister0 := pProvince;
      [*] = ;      IntRegister1 := GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iActionType);
      [*] = ;      IntRegister2 := GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iSiteIndex);
      [*] = ;      ExecuteState('GetProvEnemyArmy');
      [*] = ;      var pGuard : Integer = IntRegister3;
      [*] = ;
      [*] = ;      {if SameText(provCMode, 'cmPlayer') then
      [*] = ;      begin
      [*] = ;         StringRegister0 := IntToStr(gc_gui_query_heroEnemyAttackProvince);
      [*] = ;         BoolRegister0 := true;
      [*] = ;         PlayerExecuteStateByHandle(provPlHandle, 'CheckRequestQuery');
      [*] = ;      end
      [*] = ;      else}
      [*] = ;      begin
      [*] = ;         if isSiege then
      [*] = ;         begin
      [*] = ;            var cMode : String = GetPlayerControlModeByHandle(siegePlHandle);
      [*] = ;
      [*] = ;            if SameText(cMode, 'cmPlayer') then
      [*] = ;            begin
      [*] = ;               StringRegister0 := IntToStr(gc_gui_query_heroEnemyAttackSiegeHero);
      [*] = ;               BoolRegister0 := true;
      [*] = ;               PlayerExecuteStateByHandle(siegePlHandle, 'CheckRequestQuery');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               IntRegister0 := pMyUnits;
      [*] = ;               IntRegister1 := myGOHandle;
      [*] = ;               GameObjectExecuteStateByHandle(dummyHandle, 'EnemyAttack');
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if SameText(provCMode, 'cmPlayer') then
      [*] = ;            begin
      [*] = ;               StringRegister0 := IntToStr(gc_gui_query_heroEnemyAttackProvince);
      [*] = ;               BoolRegister0 := true;
      [*] = ;               PlayerExecuteStateByHandle(provPlHandle, 'CheckRequestQuery');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if pGuard <> pProvGarrison then
      [*] = ;               begin
      [*] = ;                  // check for union
      [*] = ;                  var defID : Integer = 0;
      [*] = ;
      [*] = ;                  if provPlHandle = 0 then
      [*] = ;                  begin
      [*] = ;                     var union : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iUnion);
      [*] = ;                     IntRegister0 := 27;
      [*] = ;                     ExecuteState('GetSkillLevel');
      [*] = ;                     var skill27 : Integer = IntRegister1;
      [*] = ;
      [*] = ;                     if (union = provRace) or ((provRace = 1) and (3 + 3 * skill27 > _rand_Random(100))) then
      [*] = ;                     begin
      [*] = ;                        case provType of
      [*] = ;                           1 : defID := 30;
      [*] = ;                           2 : defID := 29;
      [*] = ;                           4 : defID := 43;
      [*] = ;                           6 : defID := 42;
      [*] = ;                           8 : defID := 45;
      [*] = ;                           9 : defID := 37;
      [*] = ;                           10 : defID := 38;
      [*] = ;                           11 : defID := 31;
      [*] = ;                           16 : begin
      [*] = ;                              var karma : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iKarma);
      [*] = ;                              var profile : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;                              if profile > 0 then
      [*] = ;                              begin
      [*] = ;                                 var pProfile : Integer = ParserSelectByHandleByIndex(gPrototypeData.players.handle, profile);
      [*] = ;                                 karma := ParserGetIntValueByKeyByHandle(pProfile, 'Karma');
      [*] = ;                              end;
      [*] = ;
      [*] = ;                              if karma > 0 then
      [*] = ;                              defID := 34;
      [*] = ;                           end;
      [*] = ;                           17 : defID := 35;
      [*] = ;                           18 : defID := 41;
      [*] = ;                           20 : defID := 55;
      [*] = ;                           24 : defID := 68;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if defID > 0 then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := myPlHandle;
      [*] = ;                     IntRegister1 := defID;
      [*] = ;                     GameObjectExecuteStateByHandle(dummyHandle, 'DiplCaptureProvince');
      [*] = ;                     _gv_SetMapLock($10000,_log_name);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := pGuard;
      [*] = ;                     IntRegister1 := 0;
      [*] = ;                     ExecuteState('StartBattleWithArmy');
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  _gv_SetMapLock($10000,_log_name);
      [*] = ;                  ExecuteState('StartSiege');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

