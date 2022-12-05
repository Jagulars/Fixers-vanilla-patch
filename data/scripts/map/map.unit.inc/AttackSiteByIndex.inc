section.begin
   Name = AttackSiteByIndex
   Description : struct.begin
      [*] = ;IntRegister0 - site index
   struct.end
   Code : struct.begin
      [*] = ;var siteInd : Integer = IntRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'MAP\MAP.UNIT.INC\ATTACKSITEBYINDEX';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(siteInd)+']',_log_trace);
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;
      [*] = ;var plDiff : Integer = gGame.arrplayerdifficulty[GetPlayerIndexByHandle(myPlHandle)].basediff;
      [*] = ;var pDifficulty : Integer = ParserSelectByHandleByIndex(gPrototypeData.difficulty.handle, plDiff);
      [*] = ;var heroAdvice : Boolean = ParserGetBoolValueByKeyByHandle(pDifficulty, 'HeroAdvice');
      [*] = ;
      [*] = ;var pProvince : Integer = _misc_GetProvinceParserByUID(GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iCurrentUID));
      [*] = ;var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;var provPlHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;
      [*] = ;var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, siteInd);
      [*] = ;var pSiteGuard : Integer = ParserSelectByHandleByKey(pProvSite, 'Guard');
      [*] = ;var pSiteUnits : Integer = ParserSelectByHandleByKey(pSiteGuard, 'Units');
      [*] = ;var guardCount : Integer = ParserGetCountByHandle(pSiteUnits);
      [*] = ;
      [*] = ;var siteID : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'SiteID');
      [*] = ;var pSite : Integer = ParserSelectByHandleByIndex(gPrototypeData.sites.handle, siteID);
      [*] = ;
      [*] = ;if myPlHandle = GetPlayerHandleInterfaceIO() then
      [*] = ;begin
      [*] = ;   if guardCount > 0 then
      [*] = ;   begin
      [*] = ;      _hero_GetName(myGOHandle, gStringRegister_MyHeroName);
      [*] = ;      gStringRegister_SiteName := GetLocaleTableListItemByID('site', IntToStr(siteID));
      [*] = ;      PlayerExecuteStateByHandle(provPlHandle, 'GetName');
      [*] = ;      gStringRegister_EnemyPlayerName := StringRegister0;
      [*] = ;
      [*] = ;      IntRegister0 := pSiteUnits;
      [*] = ;      MapExecuteState('map.GetArmyUnitsCount');
      [*] = ;      gIntRegister_GuardEnemyCount := IntRegister1;
      [*] = ;
      [*] = ;      IntRegister0 := pSiteUnits;
      [*] = ;      MapExecuteState('map.GetArmyUnitsList');
      [*] = ;      gStringRegister_GuardEnemyList := StringRegister0;
      [*] = ;
      [*] = ;      gIntRegister_BattleAttackArmy := pMyParser;
      [*] = ;      gIntRegister_BattleAttackHeroHandle := myGOHandle;
      [*] = ;      gIntRegister_BattleAttackPlayer := myPlHandle;
      [*] = ;
      [*] = ;      gIntRegister_BattleDefendArmy := pSiteGuard;
      [*] = ;      gIntRegister_BattleDefendHeroHandle := 0;
      [*] = ;      gIntRegister_BattleDefendPlayer := 0;
      [*] = ;
      [*] = ;      if heroAdvice then
      [*] = ;      begin
      [*] = ;         IntRegister0 := pProvince;
      [*] = ;         IntRegister1 := siteInd;
      [*] = ;         BoolRegister0 := false;
      [*] = ;         BoolRegister1 := false;
      [*] = ;         ExecuteState('AdvCompareArmiesStrength');
      [*] = ;
      [*] = ;         gIntRegister_VirtualBattleResult := IntRegister2;
      [*] = ;         gBoolRegister_ShowAdvice := true;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   IntRegister0 := siteID;
      [*] = ;   MapExecuteState('GetSiteParserByID');
      [*] = ;   var pSite : Integer = IntRegister1;
      [*] = ;
      [*] = ;   var encounter : Integer = ParserGetIntValueByKeyByHandle(pSite, 'Encounter');
      [*] = ;   var dialog : Integer = ParserGetIntValueByKeyByHandle(pSite, 'Dialog');
      [*] = ;
      [*] = ;   var siteGuarded : Integer = ParserGetIntValueByKeyByHandle(pSite, 'Guarded');
      [*] = ;
      [*] = ;   var questData : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'QuestData');
      [*] = ;   if questData > 0 then
      [*] = ;   begin
      [*] = ;      gStringRegister_SpellName := GetLocaleTableListItemByID('spell', IntToStr(questData - gPrototypeData.items.number));
      [*] = ;   end;
      [*] = ;
      [*] = ;   var queryID : Integer = 0;
      [*] = ;   if ((dialog = 0) or (siteGuarded = 0) or (guardCount = 0)) and (encounter > 0) then
      [*] = ;      queryID := encounter
      [*] = ;   else
      [*] = ;      queryID := dialog;
      [*] = ;
      [*] = ;   if (queryID > gc_query_EncounterMinIndex) and (queryID <= gc_query_EncounterMaxIndex) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := queryID;
      [*] = ;      ExecuteState('ProceedEncounter');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var resultHandle : Integer = 0;
      [*] = ;      if gIntRegister_CurQueryHandle <> 0 then
      [*] = ;         resultHandle := _query_GetExecutedHandle();
      [*] = ;
      [*] = ;      if (resultHandle <> 0) and (QueryMachineIsResultHandle(resultHandle)) then
      [*] = ;         QueryMachineResultSetNextQuery(resultHandle, IntToStr(queryID))
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         StringRegister0 := IntToStr(queryID);
      [*] = ;         GUIExecuteState('map.RequestQueryWindow');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if ParserGetCountByHandle(pSiteUnits) > 0 then
      [*] = ;   begin
      [*] = ;      gBoolRegister_QuickBattle := true;
      [*] = ;      IntRegister0 := pSiteGuard;
      [*] = ;      IntRegister1 := 0;
      [*] = ;      ExecuteState('StartBattleWithArmy');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      IntRegister0 := pProvince;
      [*] = ;      IntRegister1 := siteInd;
      [*] = ;      ExecuteState('ExploreSite');
      [*] = ;
      [*] = ;      _gv_SetMapLock($10000,_log_name);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

