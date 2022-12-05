section.begin
   Name = CheckCampQuest
   Description : struct.begin
      [*] = ;IntRegister0 - province parser
      [*] = ;IntRegister1 - site index
   struct.end
   Code : struct.begin
      [*] = ;var provInd : Integer = IntRegister0;
      [*] = ;var siteInd : Integer = IntRegister1;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(myPlHandle);
      [*] = ;
      [*] = ;var pProvince : Integer = ParserSelectByHandleByIndex(gStratHexCells.handle, provInd);
      [*] = ;var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, siteInd);
      [*] = ;var siteID : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'SiteID');
      [*] = ;var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;
      [*] = ;var pMachineParser : Integer = ParserSelectStateMachineByHandle(GetMapInitMachineHandle());
      [*] = ;var pQueries : Integer = ParserSelectByHandleByKey(pMachineParser, 'Queries');
      [*] = ;if pQueries = 0 then  pQueries := ParserAddChildByIndex(pMachineParser, 'Queries');
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;if (gGame.gameType = gc_GameTypeCampaign) and SameText(cMode, 'cmPlayer') then
      [*] = ;begin
      [*] = ;   for i := 0 to gc_MaxCampaignQuest-1 do
      [*] = ;   begin
      [*] = ;      var questID : Integer = gCampaign.arrQuests[i].questIndex;
      [*] = ;      var pQuest : Integer = ParserSelectByHandleByIndex(gPrototypeData.quests.handle, questID);
      [*] = ;      var pQuestObjectives : Integer = ParserSelectByHandleByKey(pQuest, 'Objectives');
      [*] = ;      var pQuestObjective : Integer = ParserSelectByHandleByIndex(pQuestObjectives, 0);
      [*] = ;      var qTarget : Integer = ParserGetIntValueByKeyByHandle(pQuestObjective, 'Target');
      [*] = ;      var qPoss : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'Possibility');
      [*] = ;
      [*] = ;      if (questID > 0) and ((gCampaign.arrQuests[i].status = 0) or (gCampaign.arrQuests[i].status = 1)) then
      [*] = ;      begin
      [*] = ;         var checkFail : Boolean = true;
      [*] = ;         if (gCampaign.arrQuests[i].provIndex > 0) or (provInd = 0) then
      [*] = ;         begin
      [*] = ;            if (gCampaign.arrQuests[i].provIndex = provInd) and (gCampaign.arrQuests[i].siteIndex = siteInd) then
      [*] = ;            begin
      [*] = ;               gCampaign.arrQuests[i].status := 2;
      [*] = ;               var encSuccess : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'EncSuccess');
      [*] = ;               if encSuccess > 0 then
      [*] = ;               begin
      [*] = ;                  var pQuery : Integer = ParserAddChildByIndex(pQueries, '*');
      [*] = ;                  ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', encSuccess);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pQuery, 'DummyUID', dummyUID);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pQuery, 'QuestIndex', questID);
      [*] = ;                  checkFail := false;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if (gCampaign.arrQuests[i].provIndex = 0) and checkFail then
      [*] = ;         begin
      [*] = ;            if qTarget = siteID then
      [*] = ;            begin
      [*] = ;               if _rand_Random(100) < qPoss then
      [*] = ;               begin
      [*] = ;                  gCampaign.arrQuests[i].status := 2;
      [*] = ;                  var encSuccess : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'EncSuccess');
      [*] = ;                  if encSuccess > 0 then
      [*] = ;                  begin
      [*] = ;                     var pQuery : Integer = ParserAddChildByIndex(pQueries, '*');
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', encSuccess);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'DummyUID', dummyUID);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'QuestIndex', questID);
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  var encNotFound : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'EncNotFound');
      [*] = ;                  if encNotFound > 0 then
      [*] = ;                  begin
      [*] = ;                     var pQuery : Integer = ParserAddChildByIndex(pQueries, '*');
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'QueryID', encNotFound);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'DummyUID', dummyUID);
      [*] = ;                     ParserSetIntValueByKeyByHandle(pQuery, 'QuestIndex', questID);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

