section.begin
   Name = map.CheckQueryExecute
   Code : struct.begin
      [*] = ;var pMachineParser : Integer = ParserSelectStateMachineByHandle(GetMapInitMachineHandle);
      [*] = ;var pQueries : Integer = ParserSelectByHandleByKey(pMachineParser, 'Queries');
      [*] = ;
      [*] = ;var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;gIntRegister_CurrentEncounterID := 0;
      [*] = ;gIntRegister_CurrentEventID := 0;
      [*] = ;
      [*] = ;if ParserGetCountByHandle(pQueries) > 0 then
      [*] = ;begin
      [*] = ;   var pQuery : Integer = ParserSelectByHandleByIndex(pQueries, 0);
      [*] = ;   
      [*] = ;   var queryID : Integer = ParserGetIntValueByKeyByHandle(pQuery, 'QueryID');
      [*] = ;   var heroUID : Integer = ParserGetIntValueByKeyByHandle(pQuery, 'HeroUID');
      [*] = ;   var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pQuery, 'DummyUID');
      [*] = ;   var isQuest : Boolean = ParserIsValueExistsByKeyByHandle(pQuery, 'QuestIndex');
      [*] = ;   var questInd : Integer = ParserGetIntValueByKeyByHandle(pQuery, 'QuestIndex');
      [*] = ;   
      [*] = ;   var isEncounter : Boolean = (queryID > gc_query_EncounterMinIndex) and (queryID <= gc_query_EncounterMaxIndex);
      [*] = ;   ParserFreeByHandle(pQuery);
      [*] = ;   
      [*] = ;   if queryID > 0 then
      [*] = ;   begin
      [*] = ;      if heroUID > 0 then
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByUniqueId(heroUID);
      [*] = ;         if goHandle <> 0 then
      [*] = ;         begin
      [*] = ;            var plHandle  : Integer = GetGameObjectPlayerHandleByHandle(goHandle);
      [*] = ;            var raceTag : Integer = GetPlayerRaceTagByHandle(plHandle);
      [*] = ;            if raceTag = gc_map_PlayerRaceTag then
      [*] = ;            begin
      [*] = ;               var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;               var pGOQuests : Integer = ParserSelectByHandleByKey(pGOParser, 'Quests');
      [*] = ;               
      [*] = ;               gIntRegister_MapActiveHeroHandle := goHandle;
      [*] = ;               
      [*] = ;               if isQuest then
      [*] = ;               begin
      [*] = ;                  var pGOQuest : Integer = ParserSelectByHandleByIndex(pGOQuests, questInd);
      [*] = ;                  var questInd : Integer = ParserGetIntValueByKeyByHandle(pGOQuest, 'Index');
      [*] = ;                  var provInd : Integer = ParserGetIntValueByKeyByHandle(pGOQuest, 'ProvIndex');
      [*] = ;                  var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, provInd);
      [*] = ;                  
      [*] = ;                  IntRegister0 := pProvince;
      [*] = ;                  MapExecuteState('map.GetProvinceName');
      [*] = ;                  gStringRegister_ProvinceName := StringRegister0;
      [*] = ;                  
      [*] = ;                  _hero_GetName(goHandle, gStringRegister_MyHeroName);
      [*] = ;                  
      [*] = ;                  gIntRegister_EncounterQuestID := questInd;
      [*] = ;               end;
      [*] = ;               
      [*] = ;               if isEncounter then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := queryID;
      [*] = ;                  GameObjectExecuteStateByHandle(goHandle, 'ProceedEncounter');
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  StringRegister0 := IntToStr(queryID);
      [*] = ;                  GUIExecuteState('map.RequestQueryWindow');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if dummyUID > 0 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := dummyUID;
      [*] = ;         ExecuteState('GetProvinceParserByUID');
      [*] = ;         var pProvince : Integer = IntRegister1;
      [*] = ;         
      [*] = ;         var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;         gIntRegister_CurProvinceIndex := GetGameObjectIndexByHandle(dummyHandle);
      [*] = ;         IntRegister0 := queryID;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'ProceedEvent');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

