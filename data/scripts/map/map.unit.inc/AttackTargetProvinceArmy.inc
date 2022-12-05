section.begin
   Name = AttackTargetProvinceArmy
   Description : struct.begin
      [*] = ;IntRegister0 - enemy army
      [*] = ;IntRegister1 - enemy hero
   struct.end
   Code : struct.begin
      [*] = ;var pEnemyArmy : Integer = IntRegister0;
      [*] = ;var enHeroHandle : Integer = IntRegister1;
      [*] = ;
      [*] = ;var _log_name : String = 'MAP\MAP.UNIT.INC\ATTACKTARGETPROVINCEARMY';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;var pMyParser : Integer =  ParserSelectGameObject(myGOHandle);
      [*] = ;
      [*] = ;var unionRace : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iUnion);
      [*] = ;var plDiff : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iDifficulty);
      [*] = ;var pDifficulty : Integer = ParserSelectByHandleByIndex(gPrototypeData.difficulty.handle, plDiff);
      [*] = ;var heroAdvice : Boolean = ParserGetBoolValueByKeyByHandle(pDifficulty, 'HeroAdvice');
      [*] = ;
      [*] = ;var tarUID : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iTargetUID);
      [*] = ;var dummyHandle : Integer = GetGameObjectHandleByUniqueId(tarUID);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[PE:'+IntToStr(GetPlayerIndexByHandle(GetGameObjectPlayerHandleByHandle(enHeroHandle)))+',P:'+IntToStr(myPlIndex)+','+cMode+']',_log_trace);
      [*] = ;
      [*] = ;var pProvince : Integer = _misc_GetProvinceParserByUID(tarUID);
      [*] = ;var pProvGuard : Integer = ParserSelectByHandleByKey(pProvince, 'Guard');
      [*] = ;var provRace : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceRace');
      [*] = ;var provType : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceType');
      [*] = ;var pProvDefender : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
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
      [*] = ;
      [*] = ;IntRegister0 := pProvince;
      [*] = ;MapExecuteState('map.GetProvinceName');
      [*] = ;gStringRegister_ProvinceName := StringRegister0;
      [*] = ;
      [*] = ;gBoolRegister_QueryBribeGuard := false;
      [*] = ;
      [*] = ;IntRegister0 := pEnemyArmy;
      [*] = ;IntRegister1 := enHeroHandle;
      [*] = ;ExecuteState('SetupBattleRegisters');
      [*] = ;{if SameText(cMode, 'cmPlayer') then
      [*] = ;begin
      [*] = ;   SetPlayerHandleInterfaceIO(myPlHandle);
      [*] = ;   gIntRegister_MapMyPlayerIndex := myPlIndex;
      [*] = ;end;}
      [*] = ;
      [*] = ;//gIntRegister_BattleDefendArmy := pEnemyArmy;
      [*] = ;//gIntRegister_BattleDefendHeroHandle := enHeroHandle;
      [*] = ;
      [*] = ;{if enHeroHandle <> 0 then
      [*] = ;   gIntRegister_BattleDefendPlayer := GetGameObjectPlayerHandleByHandle(enHeroHandle)
      [*] = ;else
      [*] = ;   if (pEnemyArmy = pProvDefender) or (pEnemyArmy = pProvGarrison) then
      [*] = ;      gIntRegister_BattleDefendPlayer := provPlHandle
      [*] = ;   else
      [*] = ;      gIntRegister_BattleDefendPlayer := 0;}
      [*] = ;
      [*] = ;if SameText(cMode, 'cmPlayer') then
      [*] = ;begin
      [*] = ;   _hero_GetName(myGOHandle, gStringRegister_MyHeroName);
      [*] = ;
      [*] = ;   PlayerExecuteStateByHandle(provPlHandle, 'GetName');
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
      [*] = ;      var batResult : Integer = 100;
      [*] = ;      var pGuardUnits : Integer = ParserSelectByHandleByKey(gIntRegister_BattleDefendArmy, 'Units');
      [*] = ;
      [*] = ;      {gIntRegister_BattleAttackArmy := pMyParser;
      [*] = ;      gIntRegister_BattleAttackHeroHandle := myGOHandle;
      [*] = ;      gIntRegister_BattleAttackPlayer := myPlHandle;}
      [*] = ;
      [*] = ;      //if (not gBoolRegister_ShowPlayerHint) and (gIntRegister_BattleDefendArmy <> 0) and ((heroAdvice and (pEnemyArmy <> pProvGarrison)) or (pEnemyArmy = pProvDefender)) then
      [*] = ;      if (not gBoolRegister_ShowPlayerHint) and (gIntRegister_BattleDefendArmy <> 0) and heroAdvice then
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
      [*] = ;      IntRegister0 := pGuardUnits;
      [*] = ;      MapExecuteState('map.GetArmyUnitsCount');
      [*] = ;      var enArmyCount : Integer = IntRegister1;
      [*] = ;
      [*] = ;      IntRegister0 := pGuardUnits;
      [*] = ;      MapExecuteState('map.GetArmyUnitsList');
      [*] = ;      var enArmyList : String = StringRegister0;
      [*] = ;
      [*] = ;      if gIntRegister_BattleDefendHeroHandle <> 0 then
      [*] = ;      begin
      [*] = ;         gIntRegister_EnemyHeroArmyCount := enArmyCount;
      [*] = ;         gStringRegister_EnemyHeroArmyList := enArmyList;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if gIntRegister_BattleDefendArmy = pProvGuard then
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
      [*] = ;         StringRegister0 := IntToStr(gc_gui_query_heroAttackProvNoGuard);
      [*] = ;         BoolRegister0 := true;
      [*] = ;         PlayerExecuteStateByHandle(myPlHandle, 'CheckRequestQuery');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (gIntRegister_BattleDefendArmy = pProvGarrison) then
      [*] = ;         begin
      [*] = ;            StringRegister0 := IntToStr(gc_gui_query_heroStartSiege);
      [*] = ;            BoolRegister0 := true;
      [*] = ;            PlayerExecuteStateByHandle(myPlHandle, 'CheckRequestQuery');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if gIntRegister_BattleDefendHeroHandle <> 0 then
      [*] = ;            begin
      [*] = ;               if isSiege then
      [*] = ;               begin
      [*] = ;                  PlayerExecuteStateByHandle(siegePlHandle, 'GetName');
      [*] = ;                  gStringRegister_EnemyPlayerName := StringRegister0;
      [*] = ;
      [*] = ;                  if enHeroHandle <> 0 then
      [*] = ;                     _hero_GetName(gIntRegister_BattleDefendHeroHandle, gStringRegister_EnemyHeroName);
      [*] = ;
      [*] = ;                  StringRegister0 := IntToStr(gc_gui_query_heroAttackSiegePlayer);
      [*] = ;                  BoolRegister0 := true;
      [*] = ;                  PlayerExecuteStateByHandle(myPlHandle,'CheckRequestQuery');
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  _hero_GetName(gIntRegister_BattleDefendHeroHandle, gStringRegister_EnemyHeroName);
      [*] = ;
      [*] = ;                  if _misc_IsProvinceNeutral(pProvince) then
      [*] = ;                  begin
      [*] = ;                     var enPlHandle : Integer = GetGameObjectPlayerHandleByHandle(enHeroHandle);
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
      [*] = ;            if gIntRegister_BattleDefendArmy = pProvGuard then
      [*] = ;            begin
      [*] = ;               if isSiege then
      [*] = ;               begin
      [*] = ;                  StringRegister0 := IntToStr(gc_gui_query_heroAttackSiegeRebel);
      [*] = ;                  BoolRegister0 := true;
      [*] = ;                  PlayerExecuteStateByHandle(myPlHandle, 'CheckRequestQuery');
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  var pProvinceType : Integer = ParserSelectByHandleByIndex(gPrototypeData.provinceTypes.handle, provType);
      [*] = ;                  var typeRace : Integer = ParserGetIntValueByKeyByHandle(pProvinceType, 'RaceID');
      [*] = ;
      [*] = ;                  if (provRace > 0) and (provRace = unionRace) and (typeRace = unionRace) then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := ParserGetIntValueByKeyByHandle(pEnemyArmy, 'Encounter');
      [*] = ;                     ExecuteState('ProceedEncounter');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     StringRegister0 := ParserGetValueByKeyByHandle(pEnemyArmy, 'Dialog');
      [*] = ;                     GUIExecuteState('map.RequestQueryWindow');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if gIntRegister_BattleDefendArmy = pProvDefender then
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
      [*] = ;                  queryID := IntToStr(gc_gui_query_heroEnemyDefRetreat)
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
      [*] = ;                  if {(defCount <= 1) and} (not isGarrison) and (value12 = 0) and (batResult > 160 + _rand_Random(10) - value27 * 2) then
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
      [*] = ;      if gIntRegister_BattleDefendArmy <> pProvGarrison then
      [*] = ;      begin
      [*] = ;         IntRegister0 := pProvince;
      [*] = ;         ExecuteState('CheckAttackMode');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if SameText(provCMode, 'cmPlayer') then
      [*] = ;         begin
      [*] = ;            StringRegister0 := IntToStr(gc_gui_query_playerEnemyStartSiege);
      [*] = ;            BoolRegister0 := true;
      [*] = ;            PlayerExecuteStateByHandle(provPlHandle, 'CheckRequestQuery');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            ExecuteState('StartSiege');
      [*] = ;
      [*] = ;            if gBoolRegister_MapProceedBattle then
      [*] = ;               MapExecuteState('bat.ExitBattleMode');
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

