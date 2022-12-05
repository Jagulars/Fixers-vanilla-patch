section.begin
   Name = ExploreNextSite
   Description : struct.begin
      [*] = ;OUT: StringRegister0 - next query ID
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.PROVINCE.INC\EXPLORENEXTSITE';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var myHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var curPlHandle : Integer = _gv_GetCurrentPlayerHandle();
      [*] = ;var curGOHandle : Integer = GetGameObjectHandleByIndex(gIntRegister_MapCurHeroIndex, curPlHandle);
      [*] = ;var pGOParser : Integer = ParserSelectGameObject(curGOHandle);
      [*] = ;
      [*] = ;IntRegister0 := GetGameObjectUniqueIdByHandle(myHandle);
      [*] = ;MapExecuteState('GetProvinceParserByUID');
      [*] = ;var pCurHexCell : Integer = IntRegister1;
      [*] = ;var provExplored : Integer = ParserGetIntValueByKeyByHandle(pCurHexCell, 'Explored');
      [*] = ;var oldExplored : Integer = provExplored;
      [*] = ;var provExp1 : Integer = provExplored;
      [*] = ;var pProvSites : Integer = ParserSelectByHandleByKey(pCurHexCell, 'Sites');
      [*] = ;
      [*] = ;provExplored := provExplored + gIntRegister_MapExploreValue;
      [*] = ;var provExp2 : Integer = provExplored;
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;var minSiteExplore : Integer = 100;
      [*] = ;var FoundSiteInd : Integer = -1;
      [*] = ;
      [*] = ;for i := ParserGetCountByHandle(pProvSites)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, i);
      [*] = ;   var siteExplore : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'Explore');
      [*] = ;   var siteID : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'SiteID');
      [*] = ;
      [*] = ;   if (siteID > 0) and ((siteExplore > provExp1) and (siteExplore <= provExp2)) then
      [*] = ;   begin
      [*] = ;      if siteExplore < minSiteExplore then
      [*] = ;      begin
      [*] = ;         minSiteExplore := siteExplore;
      [*] = ;         FoundSiteInd := i;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var event : Boolean = QueryMachineIsExecutedEvent();
      [*] = ;var queryID : String = '';
      [*] = ;
      [*] = ;// if hero found site
      [*] = ;if (curPlHandle = GetPlayerHandleInterfaceIO()) then
      [*] = ;begin
      [*] = ;   _hero_GetName(curGOHandle, gStringRegister_MyHeroName);
      [*] = ;   IntRegister0 := pCurHexCell;
      [*] = ;   MapExecuteState('map.GetProvinceName');
      [*] = ;   gStringRegister_ProvinceName := StringRegister0;
      [*] = ;
      [*] = ;   if (FoundSiteInd > -1) then
      [*] = ;   begin
      [*] = ;      var pFoundedSite : Integer = ParserSelectByHandleByIndex(pProvSites, FoundSiteInd);
      [*] = ;      var siteID : Integer = ParserGetIntValueByKeyByHandle(pFoundedSite, 'SiteID');
      [*] = ;      var siteExplore : Integer = ParserGetIntValueByKeyByHandle(pFoundedSite, 'Explore');
      [*] = ;      var pSiteUnits : Integer = ParserSelectByHandleByKey(pFoundedSite, 'Guard');
      [*] = ;      pSiteUnits := ParserSelectByHandleByKey(pSiteUnits, 'Units');
      [*] = ;      gIntRegister_EncounterEnemyArmy := pSiteUnits; // !!!
      [*] = ;
      [*] = ;      IntRegister0 := siteID;
      [*] = ;      MapExecuteState('GetSiteParserByID');
      [*] = ;      var pSite : Integer = IntRegister1;
      [*] = ;
      [*] = ;      var guarded : Integer = ParserGetIntValueByKeyByHandle(pSite, 'Guarded');
      [*] = ;      var dialog : Integer = ParserGetIntValueByKeyByHandle(pSite, 'Dialog');
      [*] = ;      var encounter : Integer = ParserGetIntValueByKeyByHandle(pSite, 'Encounter');
      [*] = ;      var canEnter : Boolean = ParserGetBoolValueByKeyByHandle(pSite, 'CanEnter');
      [*] = ;
      [*] = ;      gStringRegister_SiteName := GetLocaleTableListItemByID('site', IntToStr(siteID));
      [*] = ;
      [*] = ;      IntRegister0 := pSiteUnits;
      [*] = ;      MapExecuteState( 'map.GetArmyUnitsCount');
      [*] = ;      gIntRegister_GuardEnemyCount := IntRegister1;
      [*] = ;
      [*] = ;      IntRegister0 := pSiteUnits;
      [*] = ;      MapExecuteState( 'map.GetArmyUnitsList');
      [*] = ;      gStringRegister_GuardEnemyList := StringRegister0;
      [*] = ;
      [*] = ;      gIntRegister_FoundSiteIndex := FoundSiteInd;
      [*] = ;      SetGameObjectIntValueIndByHandle(curGOHandle, gc_map_GOStack_MapUnit_iSiteIndex, FoundSiteInd);
      [*] = ;      _gui_ProgressCalculations(_log_name+' Site ' + IntToStr(siteID) + ' found');
      [*] = ;
      [*] = ;      ParserSetIntValueByKeyByHandle(pCurHexCell, 'Explored', siteExplore);
      [*] = ;      gIntRegister_MapExploreValue := gIntRegister_MapExploreValue - (siteExplore - provExp1);
      [*] = ;
      [*] = ;      IntRegister0 := pCurHexCell;
      [*] = ;      IntRegister1 := FoundSiteInd;
      [*] = ;      GameObjectExecuteStateByHandle(curGOHandle, 'ExploreSite');
      [*] = ;
      [*] = ;      // check ability 21 - show special dialog
      [*] = ;      var spDialog : Integer = 0;
      [*] = ;      var pSiteAbilities : Integer = ParserSelectByHandleByKey(pSite, 'Abilities');
      [*] = ;      for i := ParserGetCountByHandle(pSiteAbilities)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pSiteAbility : Integer = ParserSelectByHandleByIndex(pSiteAbilities, i);
      [*] = ;         var abilID : Integer = ParserGetIntValueByKeyByHandle(pSiteAbility, 'AbilityID');
      [*] = ;         if abilID = 21 then
      [*] = ;         begin
      [*] = ;            spDialog := ParserGetIntValueByKeyByHandle(pSiteAbility, 'Param1');
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if siteID < gPrototypeData.resources.number then
      [*] = ;      begin
      [*] = ;         if pSiteUnits = 0 then
      [*] = ;            spDialog := ParserGetIntValueByKeyByHandle(pSite, 'Dialog2');
      [*] = ;      end;
      [*] = ;
      [*] = ;      if spDialog > 0 then
      [*] = ;         queryID := IntToStr(spDialog)
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (guarded > 0) or canEnter then
      [*] = ;            queryID := IntToStr(gc_gui_query_heroExploreFoundSite)
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if encounter > 0 then
      [*] = ;               queryID := IntToStr(encounter)
      [*] = ;            else
      [*] = ;               queryID := IntToStr(dialog);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if provExplored >= 100 then
      [*] = ;      begin
      [*] = ;         // achievements
      [*] = ;         _achievement_Trigger(gc_achiev_whole_province_explored,'');
      [*] = ;         //
      [*] = ;         gIntRegister_MapExploreValue := 0;
      [*] = ;         ExecuteState('FinishExploration');
      [*] = ;         queryID := IntToStr(gc_gui_query_heroExploreFinished);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         ParserSetIntValueByKeyByHandle(pCurHexCell, 'Explored', provExplored);
      [*] = ;
      [*] = ;         if not event then
      [*] = ;         begin
      [*] = ;            gIntRegister_ExploreValue := gIntRegister_MapExploreValue;
      [*] = ;            queryID := IntToStr(gc_gui_query_heroExploreNothingFound);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            queryID := '';
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      gIntRegister_MapExploreValue := 0;
      [*] = ;      _gv_SetMapLock($10000,_log_name);
      [*] = ;      gIntRegister_FoundSiteIndex := -1;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if (FoundSiteInd > -1) then
      [*] = ;   begin
      [*] = ;      var pFoundedSite : Integer = ParserSelectByHandleByIndex(pProvSites, FoundSiteInd);
      [*] = ;      var siteID : Integer = ParserGetIntValueByKeyByHandle(pFoundedSite, 'SiteID');
      [*] = ;      var siteExplore : Integer = ParserGetIntValueByKeyByHandle(pFoundedSite, 'Explore');
      [*] = ;      var pSiteUnits : Integer = ParserSelectByHandleByKey(pFoundedSite, 'Guard');
      [*] = ;      pSiteUnits := ParserSelectByHandleByKey(pSiteUnits, 'Units');
      [*] = ;
      [*] = ;      IntRegister0 := siteID;
      [*] = ;      MapExecuteState('GetSiteParserByID');
      [*] = ;      var pSite : Integer = IntRegister1;
      [*] = ;
      [*] = ;      var guarded : Integer = ParserGetIntValueByKeyByHandle(pSite, 'Guarded');
      [*] = ;      var dialog : Integer = ParserGetIntValueByKeyByHandle(pSite, 'Dialog');
      [*] = ;      var encounter : Integer = ParserGetIntValueByKeyByHandle(pSite, 'Encounter');
      [*] = ;
      [*] = ;      SetGameObjectIntValueIndByHandle(curGOHandle, gc_map_GOStack_MapUnit_iSiteIndex, FoundSiteInd);
      [*] = ;      _gui_ProgressCalculations(_log_name+' Site ' + IntToStr(siteID) + ' found');
      [*] = ;
      [*] = ;      ParserSetIntValueByKeyByHandle(pCurHexCell, 'Explored', siteExplore);
      [*] = ;      gIntRegister_MapExploreValue := gIntRegister_MapExploreValue - (siteExplore - provExp1);
      [*] = ;
      [*] = ;      IntRegister0 := pCurHexCell;
      [*] = ;      IntRegister1 := FoundSiteInd;
      [*] = ;      GameObjectExecuteStateByHandle(curGOHandle, 'ExploreSite');
      [*] = ;
      [*] = ;      if ParserGetCountByHandle(pSiteUnits) > 0 then
      [*] = ;      begin
      [*] = ;         var pHeroUnits : Integer = ParserSelectByHandleByKey(pGOParser, 'Units');
      [*] = ;         var notInBattle : Integer = GetGameObjectIntValueIndByHandle(curGOHandle, gc_map_GOStack_MapUnit_iNotInBattle);
      [*] = ;
      [*] = ;         IntRegister0 := pCurHexCell;
      [*] = ;         IntRegister1 := FoundSiteInd;
      [*] = ;         BoolRegister0 := true;
      [*] = ;         BoolRegister1 := true;
      [*] = ;         GameObjectExecuteStateByHandle(curGOHandle, 'AdvCompareArmiesStrength');
      [*] = ;         var power : Integer = IntRegister2;
      [*] = ;         var heroDeath : Boolean = BoolRegister2;
      [*] = ;
      [*] = ;         if power > 110 - notInBattle then
      [*] = ;         begin
      [*] = ;            GameObjectExecuteStateByHandle(curGOHandle, 'AttackSite');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            ExecuteState('ExploreNextSite');
      [*] = ;         end;
      [*] = ;
      [*] = ;         IntRegister0 := FoundSiteInd;
      [*] = ;         ExecuteState('CheckSiteDestroy');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      // non-guarded site
      [*] = ;      begin
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if provExplored >= 100 then
      [*] = ;      begin
      [*] = ;         gIntRegister_MapExploreValue := 0;
      [*] = ;         ExecuteState('FinishExploration');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         ParserSetIntValueByKeyByHandle(pCurHexCell, 'Explored', provExplored);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var newExplored : Integer = ParserGetIntValueByKeyByHandle(pCurHexCell, 'Explored');
      [*] = ;var plExplore : Integer = GetPlayerIntValueIndByHandle(curPlHandle, gc_map_PLStack_MapUnit_iExplore);
      [*] = ;plExplore := plExplore + newExplored - oldExplored;
      [*] = ;SetPlayerIntValueIndByHandle(curPlHandle, gc_map_PLStack_MapUnit_iExplore, plExplore);
      [*] = ;
      [*] = ;if (curPlHandle = GetPlayerHandleInterfaceIO()) and (not event) and (queryID <> '') then //not event was needed to resolve #65549
      [*] = ;begin
      [*] = ;   StringRegister0 := queryID;
      [*] = ;   GUIExecuteState('map.RequestQueryWindow');
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;
      [*] = ;StringRegister0 := queryID;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

