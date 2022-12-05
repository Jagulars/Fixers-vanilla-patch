section.begin
   Name = CheckFailQuests
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\CHECKFAILQUESTS';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;var myPlName : String = GetCurrentPlayerName();
      [*] = ;var myIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;
      [*] = ;var goCount : Integer = GetPlayerGameObjectsCountByHandle(myPlHandle);
      [*] = ;var i : Integer;
      [*] = ;var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;var pQuests : Integer = gPrototypeData.quests.handle;
      [*] = ;
      [*] = ;//Log('Execute hero events for ' + myPlName);
      [*] = ;
      [*] = ;if (not _misc_IsMapLocked()) and (gIntRegister_MapTurnIteration = 13) and (myIndex = _gv_GetCurrentPlayer()) then
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(gIntRegister_MapCurHeroIndex, myPlHandle);
      [*] = ;   var isDead : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;
      [*] = ;   var qFound : Boolean = false;
      [*] = ;
      [*] = ;   if not isDead then
      [*] = ;   begin
      [*] = ;      var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;      var pGOQuests : Integer = ParserSelectByHandleByKey(pGOParser, 'Quests');
      [*] = ;
      [*] = ;      for i := 0 to ParserGetCountByHandle(pGOQuests)-1 do
      [*] = ;      begin
      [*] = ;         var pGOQuest : Integer = ParserSelectByHandleByIndex(pGOQuests, i);
      [*] = ;         var questID : Integer = ParserGetIntValueByKeyByHandle(pGOQuest, 'Index');
      [*] = ;         var siteIndex : Integer = ParserGetIntValueByKeyByHandle(pGOQuest, 'SiteIndex');
      [*] = ;         var provIndex : Integer = ParserGetIntValueByKeyByHandle(pGOQuest, 'ProvIndex');
      [*] = ;
      [*] = ;         var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, provIndex);
      [*] = ;         var provPlayer : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;
      [*] = ;         if questID > 0 then
      [*] = ;         begin
      [*] = ;            if siteIndex >= 0 then
      [*] = ;            begin
      [*] = ;               var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;               var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, siteIndex);
      [*] = ;               var siteID : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'SiteID');
      [*] = ;
      [*] = ;               if siteID = 0 then
      [*] = ;                  qFound := true;
      [*] = ;            end
      [*] = ;            else
      [*] = ;               if provPlayer <> '' then
      [*] = ;                  qFound := true;
      [*] = ;
      [*] = ;            if qFound then
      [*] = ;            begin
      [*] = ;               gIntRegister_EncounterQuestID := questID;
      [*] = ;
      [*] = ;               var pQuest : Integer = ParserSelectByHandleByIndex(pQuests, questID);
      [*] = ;               var encounterID : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'EncFailGiver');
      [*] = ;
      [*] = ;               if encounterID > 0 then
      [*] = ;               begin
      [*] = ;                  _hero_GetName(goHandle, gStringRegister_MyHeroName);
      [*] = ;                  IntRegister0 := pProvince;
      [*] = ;                  MapExecuteState('map.GetProvinceName');
      [*] = ;                  gStringRegister_ProvinceName := StringRegister0;
      [*] = ;
      [*] = ;                  IntRegister0 := encounterID;
      [*] = ;                  GameObjectExecuteStateByHandle(goHandle, 'ProceedEncounter');
      [*] = ;               end;
      [*] = ;               IntRegister0 := i;
      [*] = ;               GameObjectExecuteStateByHandle(goHandle, 'AbandonQuest');
      [*] = ;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if not qFound then
      [*] = ;   begin
      [*] = ;      var ind : Integer = -1;
      [*] = ;      for i := gIntRegister_MapCurHeroIndex+1 to goCount-1 do
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;         var isDead : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;         var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;         var pGOQuests : Integer = ParserSelectByHandleByKey(pGOParser, 'Quests');
      [*] = ;         var questCount : Integer = ParserGetCountByHandle(pGOQuests);
      [*] = ;
      [*] = ;         if (not isDead) and (questCount > 0) then
      [*] = ;         begin
      [*] = ;            ind := i;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if ind >= 0 then
      [*] = ;         gIntRegister_MapCurHeroIndex := ind
      [*] = ;      else
      [*] = ;         gIntRegister_MapTurnIteration := gIntRegister_MapTurnIteration + 1;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

