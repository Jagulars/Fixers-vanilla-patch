section.begin
   Name = Encounter.ApplyEffects
   Description : struct.begin
      [*] = ;OUT: StringRegister0 - current query ID
      [*] = ;OUT: BoolRegister0 - is opened another window
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'ENCOUNTER\ENCOUNTER.APPLYEFFECTS';
      [*] = ;var _log_trace : Integer = $80001;
      [*] = ;
      [*] = ;var pEnemyUnits : Integer = gIntRegister_EncounterEnemyArmy;
      [*] = ;// get parser event handle
      [*] = ;var queryHandle : Integer = _query_GetExecutedHandle;
      [*] = ;var queryID : String = QueryMachineQueryGetID(queryHandle);
      [*] = ;
      [*] = ;var i, j, k : Integer;
      [*] = ;
      [*] = ;var pItems : Integer = gPrototypeData.items.handle;
      [*] = ;var pUnits : Integer = gPrototypeData.units.handle;
      [*] = ;var pQuests : Integer = gPrototypeData.quests.handle;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+queryID+']',_log_trace);
      [*] = ;IntRegister0 := StrToInt(queryID);
      [*] = ;MapExecuteState('GetEncounterParserByID');
      [*] = ;var pEncounter : Integer = IntRegister1;
      [*] = ;
      [*] = ;var pChooseItems : Integer = _misc_ParserGetOrCreateByKey('ChooseItems',true);
      [*] = ;
      [*] = ;// get hero handle
      [*] = ;var plHandle : Integer = _gv_GetCurrentPlayerHandle();
      [*] = ;var goHandle : Integer = GetGameObjectHandleByIndex(gIntRegister_MapCurHeroIndex, plHandle);
      [*] = ;if goHandle = 0 then
      [*] = ;begin
      [*] = ;   goHandle := gIntRegister_MapActiveHeroHandle;
      [*] = ;   plHandle := GetGameObjectPlayerHandleByHandle(goHandle);
      [*] = ;end;
      [*] = ;var bInterfacePlayer : Boolean = (GetPlayerHandleInterfaceIO = plHandle);
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;
      [*] = ;var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;var pGOQuests : Integer = ParserSelectByHandleByKey(pGOParser, 'Quests');
      [*] = ;var pGOUnits : Integer = ParserSelectByHandleByKey(pGOParser, 'Units');
      [*] = ;var pGODoll : Integer = ParserSelectByHandleByKey(pGOParser, 'Doll');
      [*] = ;var pGOLeftLootItems : Integer = ParserSelectByHandleByKey(pGOParser, 'LeftLootItems');
      [*] = ;var pGOSiteLootItems : Integer = ParserSelectByHandleByKey(pGOParser, 'SiteLootItems');
      [*] = ;
      [*] = ;var heroQuestCount : Integer = ParserGetCountByHandle(pGOQuests);
      [*] = ;
      [*] = ;var pPlParser : Integer = ParserSelectPlayer(plHandle);
      [*] = ;var pEncRecruitUnits : Integer = ParserSelectByHandleByKey(pPlParser, 'EncRecruitUnits');
      [*] = ;ParserClearByHandle(pEncRecruitUnits);
      [*] = ;
      [*] = ;// get province parser
      [*] = ;var provUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;var dummyHandle : Integer = GetGameObjectHandleByUniqueId(provUID);
      [*] = ;var pProvince : Integer = _misc_GetProvinceParserByUID(provUID);
      [*] = ;var prRace : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceRace');
      [*] = ;var prIndex : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Index');
      [*] = ;
      [*] = ;// get site parser
      [*] = ;var siteInd : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iSiteIndex);
      [*] = ;var pProvSite : Integer = ParserSelectByHandleByIndex(ParserSelectByHandleByKey(pProvince, 'Sites'), siteInd);
      [*] = ;var siteID : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'SiteID');
      [*] = ;var siteQuest : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'Quest');
      [*] = ;var siteRandQuest : Boolean = ParserGetBoolValueByKeyByHandle(pProvSite, 'RandomQuest');
      [*] = ;var province_flags : Integer = 0;
      [*] = ;
      [*] = ;PlayerExecuteStateByHandle(plHandle, 'GetCastleParser');
      [*] = ;var pCastle : Integer = IntRegister0;
      [*] = ;var cDummyUID : Integer = ParserGetIntValueByKeyByHandle(pCastle, 'DummyUID');
      [*] = ;var cDummyHandle : Integer = GetGameObjectHandleByUniqueId(cDummyUID);
      [*] = ;
      [*] = ;var curQuestID : Integer = gIntRegister_EncounterQuestID;
      [*] = ;
      [*] = ;function CalcEffect(pEncounter, index, mult, goDipl : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;
      [*] = ;   var pEffects : Integer = ParserSelectByHandleByKey(pEncounter, 'Effects');
      [*] = ;   var i : Integer;
      [*] = ;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pEffects)-1 do
      [*] = ;   begin
      [*] = ;      var pEffect : Integer = ParserSelectByHandleByIndex(pEffects, i);
      [*] = ;      var ind : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Index');
      [*] = ;      var power : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Power');
      [*] = ;      var param1 : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Param1');
      [*] = ;      var param2 : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Param2');
      [*] = ;
      [*] = ;      if ind = index then
      [*] = ;      begin
      [*] = ;         case param2 of
      [*] = ;            0 :
      [*] = ;            begin
      [*] = ;               Result := Result + power + _rand_Random(param1);
      [*] = ;            end;
      [*] = ;            1 :
      [*] = ;            begin
      [*] = ;               Result := Result + mult * (power + _rand_Random(param1));
      [*] = ;            end;
      [*] = ;            2 :
      [*] = ;            begin
      [*] = ;               Result := Result + gIntRegister_EncounterParam1;
      [*] = ;            end;
      [*] = ;            3 :
      [*] = ;            begin
      [*] = ;               Result := Result + gIntRegister_EncounterParam2;
      [*] = ;            end;
      [*] = ;            4 :
      [*] = ;            begin
      [*] = ;               var value : Integer = power + _rand_Random(param1);
      [*] = ;               value := value + (value * goDipl) div 100;
      [*] = ;               Result := Result + value;
      [*] = ;            end;
      [*] = ;            5 :
      [*] = ;            begin
      [*] = ;               var mult1, mult2 : Integer;
      [*] = ;               case power of
      [*] = ;                  1 : mult1 := mult;
      [*] = ;                  2 : mult1 := gIntRegister_EncounterParam1;
      [*] = ;                  3 : mult1 := gIntRegister_EncounterParam2;
      [*] = ;                  4 : mult1 := 1 + goDipl div 100;
      [*] = ;               end;
      [*] = ;               case param1 of
      [*] = ;                  1 : mult2 := mult;
      [*] = ;                  2 : mult2 := gIntRegister_EncounterParam1;
      [*] = ;                  3 : mult2 := gIntRegister_EncounterParam2;
      [*] = ;                  4 : mult2 := 1 + goDipl div 100;
      [*] = ;               end;
      [*] = ;               Result := Result + mult1 * mult2;
      [*] = ;            end;
      [*] = ;            6 :
      [*] = ;            begin
      [*] = ;               Result := Result - gIntRegister_EncounterParam1;
      [*] = ;            end;
      [*] = ;            7 :
      [*] = ;            begin
      [*] = ;               Result := Result - gIntRegister_EncounterParam2;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure GetRandomItem(var itemID : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var sum : Integer = 0;
      [*] = ;   itemID := 0;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pChooseItems)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      sum := sum + ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pChooseItems, i), 'Freq');
      [*] = ;   end;
      [*] = ;
      [*] = ;   if sum > 0 then
      [*] = ;   begin
      [*] = ;      var randSum : Integer = _rand_Random(sum);
      [*] = ;
      [*] = ;      for i := ParserGetCountByHandle(pChooseItems)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pChooseItem : Integer = ParserSelectByHandleByIndex(pChooseItems, i);
      [*] = ;         randSum := randSum - ParserGetIntValueByKeyByHandle(pChooseItem, 'Freq');
      [*] = ;
      [*] = ;         if randSum <= 0 then
      [*] = ;         begin
      [*] = ;            itemID := ParserGetIntValueByKeyByHandle(pChooseItem, 'ItemID');
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function CheckQuest(heroHandle, questID : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   Result := false;
      [*] = ;   var pGOParser : Integer = ParserSelectGameObject(heroHandle);
      [*] = ;   var pGOQuests : Integer = ParserSelectByHandleByKey(pGOParser, 'Quests');
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pGOQuests)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pGOQuest : Integer = ParserSelectByHandleByIndex(pGOQuests, i);
      [*] = ;      var qInd : Integer = ParserGetIntValueByKeyByHandle(pGOQuest, 'Index');
      [*] = ;      var qProvInd : Integer = ParserGetIntValueByKeyByHandle(pGOQuest, 'ProvIndex');
      [*] = ;
      [*] = ;      if (qInd = questID) and (qProvInd = prIndex) then
      [*] = ;      begin
      [*] = ;         Result := true;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CheckItem(goHandle, itemID : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;   var pGODoll : Integer = ParserSelectByHandleByKey(pGOParser, 'Doll');
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pGODoll)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pGODollSlot : Integer = ParserSelectByHandleByIndex(pGODoll, i);
      [*] = ;      var id : Integer = ParserGetIntValueByKeyByHandle(pGODollSlot, 'ItemID');
      [*] = ;
      [*] = ;      if id = itemID then
      [*] = ;      begin
      [*] = ;         ParserSetIntValueByKeyByHandle(pGODollSlot, 'ItemID', 0);
      [*] = ;         ParserSetIntValueByKeyByHandle(pGODollSlot, 'Durability', 0);
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetHeroQuest(goHandle, questID : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;   var pGOQuests : Integer = ParserSelectByHandleByKey(pGOParser, 'Quests');
      [*] = ;   var i : Integer;
      [*] = ;   Result := 0;
      [*] = ;
      [*] = ;   var pQuest : Integer = ParserSelectByHandleByIndex(pQuests, questID);
      [*] = ;   var qType : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'Type');
      [*] = ;
      [*] = ;   if qType >= 7 then
      [*] = ;   begin
      [*] = ;      for i := 0 to ParserGetCountByHandle(pGOQuests)-1 do
      [*] = ;      begin
      [*] = ;         var pGOQuest : Integer = ParserSelectByHandleByIndex(pGOQuests, i);
      [*] = ;         var qIndex : Integer = ParserGetIntValueByKeyByHandle(pGOQuest, 'Index');
      [*] = ;         var qProvInd : Integer = ParserGetIntValueByKeyByHandle(pGOQuest, 'ProvIndex');
      [*] = ;         var qSiteInd : Integer = ParserGetIntValueByKeyByHandle(pGOQuest, 'SiteIndex');
      [*] = ;
      [*] = ;         if (qIndex = questID) and (qProvInd = prIndex) and (qSiteInd = siteInd) then
      [*] = ;         begin
      [*] = ;            Result := pGOQuest;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      for i := 0 to ParserGetCountByHandle(pGOQuests)-1 do
      [*] = ;      begin
      [*] = ;         var pGOQuest : Integer = ParserSelectByHandleByIndex(pGOQuests, i);
      [*] = ;         var qIndex : Integer = ParserGetIntValueByKeyByHandle(pGOQuest, 'Index');
      [*] = ;
      [*] = ;         if qIndex = questID then
      [*] = ;         begin
      [*] = ;            Result := pGOQuest;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var openHeroWindow : Boolean = false;
      [*] = ;
      [*] = ;if ParserGetCountByHandle(pGOLeftLootItems) > 0 then
      [*] = ;begin
      [*] = ;   ErrorLogI(_log_name+' LeftLootItems is '+IntToStr(ParserGetCountByHandle(pGOLeftLootItems)));
      [*] = ;   ParserClearByHandle(pGOLeftLootItems);
      [*] = ;end;
      [*] = ;
      [*] = ;if pEncounter = 0 then
      [*] = ;begin
      [*] = ;   StringRegister0 := '';
      [*] = ;   BoolRegister0 := openHeroWindow;
      [*] = ;   _gv_traceState(_log_name+'[Encounter=NULL]',$1000000 or _log_trace);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;var plGem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;
      [*] = ;IntRegister0 := gc_ability_diplomacy;
      [*] = ;GameObjectExecuteStateByHandle(goHandle, 'CheckAbility');
      [*] = ;var goDipl : Integer = IntRegister1;
      [*] = ;
      [*] = ;gIntRegister_EncounterDifficulty := 1;
      [*] = ;var qNum : Integer = 0;
      [*] = ;var attackLevel : Integer = 0;
      [*] = ;gBoolRegister_EncounterDiffFlag := false;
      [*] = ;gIntRegister_EncounterGuardLevel := 0;
      [*] = ;
      [*] = ;var pEffects : Integer = ParserSelectByHandleByKey(pEncounter, 'Effects');
      [*] = ;var guardTypeID : Integer = ParserGetIntValueByKeyByHandle(pEncounter, 'GuardType');
      [*] = ;
      [*] = ;var plKarma : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iKarma);
      [*] = ;plKarma := plKarma + ParserGetIntValueByKeyByHandle(pEncounter, 'Karma');
      [*] = ;SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iKarma, plKarma);
      [*] = ;
      [*] = ;_hero_GetName(goHandle, gStringRegister_MyHeroName);
      [*] = ;IntRegister0 := pProvince;
      [*] = ;MapExecuteState('map.GetProvinceName');
      [*] = ;gStringRegister_ProvinceName := StringRegister0;
      [*] = ;
      [*] = ;gIntRegister_TreasureGoldReward := 0;
      [*] = ;gIntRegister_TreasureGemReward := 0;
      [*] = ;
      [*] = ;var newQueryID : String = queryID;
      [*] = ;// calculate difficulty of encounter
      [*] = ;for i := 0 to ParserGetCountByHandle(pEffects)-1 do
      [*] = ;begin
      [*] = ;   var pEffect : Integer = ParserSelectByHandleByIndex(pEffects, i);
      [*] = ;   var index : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Index');
      [*] = ;   var power : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Power');
      [*] = ;   var param1 : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Param1');
      [*] = ;   var param2 : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Param2');
      [*] = ;
      [*] = ;   //3 ��������� ���������� ��������� �����������
      [*] = ;   //
      [*] = ;   //    Power:
      [*] = ;   //    1. ������� ���������
      [*] = ;   //    2. ������� �����
      [*] = ;   //    3. ������� ������ (7)
      [*] = ;   //    4. ������ Param1
      [*] = ;   if index = 3 then
      [*] = ;   begin
      [*] = ;      case power of
      [*] = ;         1 : begin
      [*] = ;            gIntRegister_EncounterDifficulty := ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceLevel');
      [*] = ;            gBoolRegister_EncounterDiffFlag := true;
      [*] = ;         end;
      [*] = ;         2 : begin
      [*] = ;            gIntRegister_EncounterDifficulty := ParserGetIntValueByKeyByHandle(pProvSite, 'Level');
      [*] = ;            gBoolRegister_EncounterDiffFlag := true;
      [*] = ;         end;
      [*] = ;         3 : begin
      [*] = ;            var questData : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'QuestData');
      [*] = ;            var pExtItem : Integer = ParserSelectByHandleByIndex(gPrototypeData.extItems.handle, questData);
      [*] = ;            var shopLevel : Integer = ParserGetIntValueByKeyByHandle(pExtItem, 'ShopLevel');
      [*] = ;
      [*] = ;            gIntRegister_EncounterDifficulty := shopLevel;
      [*] = ;            gBoolRegister_EncounterDiffFlag := true;
      [*] = ;         end;
      [*] = ;         4 : begin
      [*] = ;            gIntRegister_EncounterDifficulty := param1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var difficulty : Integer = gIntRegister_EncounterDifficulty;
      [*] = ;
      [*] = ;var pFirstEffect : Integer = ParserSelectByHandleByIndex(pEffects, 0);
      [*] = ;var firstInd : Integer = ParserGetIntValueByKeyByHandle(pFirstEffect, 'Index');
      [*] = ;
      [*] = ;var mult : Integer = 0;
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pEffects)-1 do
      [*] = ;begin
      [*] = ;   var pEffect : Integer = ParserSelectByHandleByIndex(pEffects, i);
      [*] = ;   var index : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Index');
      [*] = ;   var power : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Power');
      [*] = ;   var param1 : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Param1');
      [*] = ;   var param2 : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Param2');
      [*] = ;
      [*] = ;   if (newQueryID <> '') and (newQueryID <> queryID) then
      [*] = ;      break;
      [*] = ;
      [*] = ;   case index of
      [*] = ;      //2 ��������� �������� 1 ��� �������� � ��������� �����������.
      [*] = ;      2 : gIntRegister_EncounterParam1 := CalcEffect(pEncounter, 2, difficulty, goDipl);
      [*] = ;      //5 ��������� �������� 2 ��� �������� � ��������� �����������.
      [*] = ;      5 : gIntRegister_EncounterParam2 := CalcEffect(pEncounter, 5, difficulty, goDipl);
      [*] = ;      //7 ����� + Power+Random(Param1)
      [*] = ;      7 : begin
      [*] = ;         var karma : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iKarma);
      [*] = ;         karma := karma + CalcEffect(pEncounter, 7, difficulty, goDipl);
      [*] = ;         SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iKarma, karma);
      [*] = ;      end;
      [*] = ;      //8 �������� ���������� ������� Power
      [*] = ;      {8 :
      [*] = ;      begin
      [*] = ;         newQueryID := IntToStr(power);
      [*] = ;      end;}
      [*] = ;      //9 (effect is deleted) � ��������� ���������� ����� ���� Power. ���� Param1>0 - ���� �������.
      [*] = ;      //10 ���������� ���� ����������� � �������� Power
      [*] = ;      10 : begin
      [*] = ;         gIntRegister_EncounterResult := power;
      [*] = ;      end;
      [*] = ;      //11 ������� ����������� Power (���� Param1>0 - ������� ����������� Param1, ���� Random(100)>Param2)
      [*] = ;      {11 :
      [*] = ;      begin
      [*] = ;         var queryID : Integer = 0;
      [*] = ;         if (param1 > 0) and (_rand_Random(100) > param2) then
      [*] = ;         queryID := param1
      [*] = ;         else
      [*] = ;         queryID := power;
      [*] = ;
      [*] = ;         newQueryID := IntToStr(queryID);
      [*] = ;      end;}
      [*] = ;      //12 �������� Param1 �������� ��������� Power
      [*] = ;      12 : begin
      [*] = ;         var pAvOuterBuildings : Integer = ParserSelectByHandleByKey(pCastle, 'AvOuterBuildings');
      [*] = ;         var pAvOuterBuilding : Integer = ParserSelectByHandleByIndex(pAvOuterBuildings, power);
      [*] = ;         var count : Integer = ParserGetIntValueByKeyByHandle(pAvOuterBuilding, 'Count');
      [*] = ;         if count >= 0 then
      [*] = ;            count := count + param1;
      [*] = ;         ParserSetIntValueByKeyByHandle(pAvOuterBuilding, 'Count', count);
      [*] = ;
      [*] = ;         //var itemID : Integer = gPrototypeData.items.number + gPrototypeData.spells.number + gPrototypeData.defenders.number + power;
      [*] = ;         // !!! why this was not commented out???
      [*] = ;         {IntRegister0 := power;
      [*] = ;         IntRegister1 := 12;
      [*] = ;         MapExecuteState('GetExtItemIDByType');
      [*] = ;         var itemID : Integer = IntRegister2;}
      [*] = ;      end;
      [*] = ;      //13 �������� Param1 ������� ���������� Power
      [*] = ;      13 : begin
      [*] = ;         //var itemID : Integer = gPrototypeData.items.number + power;
      [*] = ;         IntRegister0 := power;
      [*] = ;         IntRegister1 := 10;
      [*] = ;         MapExecuteState('GetExtItemIDByType');
      [*] = ;         var itemID : Integer = IntRegister2;
      [*] = ;
      [*] = ;         IntRegister0 := itemID;
      [*] = ;         MapExecuteState('GetItemParserByID');
      [*] = ;         var pItem : Integer = IntRegister1;
      [*] = ;         var itemDur : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Durability');
      [*] = ;
      [*] = ;         for j := 0 to param1-1 do
      [*] = ;         begin
      [*] = ;            IntRegister0 := itemID;
      [*] = ;            IntRegister1 := itemDur;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'TakeLootItem');
      [*] = ;            if not BoolRegister0 then
      [*] = ;            begin
      [*] = ;               var pGOLeftLootItem : Integer = ParserAddChildByIndex(pGOLeftLootItems, '*');
      [*] = ;               ParserSetIntValueByKeyByHandle(pGOLeftLootItem, 'ItemID', itemID);
      [*] = ;               ParserSetIntValueByKeyByHandle(pGOLeftLootItem, 'Durability', itemDur);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //14 �������� ��������� ������� ������ Power, c ��������� �� ���� Param1
      [*] = ;      14 : begin
      [*] = ;         var itemID : Integer;
      [*] = ;
      [*] = ;         for j := ParserGetCountByHandle(pItems)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pItem : Integer = ParserSelectByHandleByIndex(pItems, j);
      [*] = ;            var shopLevel : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ShopLevel');
      [*] = ;            var rarity : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Rarity');
      [*] = ;
      [*] = ;            if (shopLevel = power) and (rarity >= param1) then
      [*] = ;            begin
      [*] = ;               var pChooseItem : Integer = ParserAddChildByIndex(pChooseItems, '*');
      [*] = ;               ParserSetIntValueByKeyByHandle(pChooseItem, 'ItemID', ParserGetIntValueByKeyByHandle(pItem, 'ItemID'));
      [*] = ;               ParserSetIntValueByKeyByHandle(pChooseItem, 'Freq', 7 - rarity);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         GetRandomItem(itemID);
      [*] = ;
      [*] = ;         IntRegister0 := itemID;
      [*] = ;         MapExecuteState('GetItemParserByID');
      [*] = ;         var pItem : Integer = IntRegister1;
      [*] = ;         var itemDur : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Durability');
      [*] = ;
      [*] = ;         IntRegister0 := itemID;
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'CheckItemRarity');
      [*] = ;
      [*] = ;         // Loot items parser for visualization in ToolQueryWindow
      [*] = ;         var pGOSiteLootItem : Integer = ParserAddChildByIndex(pGOSiteLootItems, '*');
      [*] = ;         ParserSetIntValueByKeyByHandle(pGOSiteLootItem, 'ItemID', itemID);
      [*] = ;         ParserSetIntValueByKeyByHandle(pGOSiteLootItem, 'Durability', itemDur);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pGOSiteLootItem, 'Picked', false);
      [*] = ;
      [*] = ;         IntRegister0 := itemID;
      [*] = ;         IntRegister1 := itemDur;
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'TakeLootItem');
      [*] = ;         if not BoolRegister0 then
      [*] = ;         begin
      [*] = ;            var pGOLeftLootItem : Integer = ParserAddChildByIndex(pGOLeftLootItems, '*');
      [*] = ;            ParserSetIntValueByKeyByHandle(pGOLeftLootItem, 'ItemID', itemID);
      [*] = ;            ParserSetIntValueByKeyByHandle(pGOLeftLootItem, 'Durability', itemDur);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //15 ���� ������� � �������� Power �� �����������, ������� � ���������� � Param2 �����������
      [*] = ;      15 : begin
      [*] = ;         var cond : Boolean = true;
      [*] = ;         case power of
      [*] = ;            //    1 - ���� ������ �����>���� NPC
      [*] = ;            1 :
      [*] = ;            begin
      [*] = ;               // my hero
      [*] = ;               IntRegister0 := 27;
      [*] = ;               GameObjectExecuteStateByHandle(goHandle, 'GetSkillLevel');
      [*] = ;               var skill27 : Integer = IntRegister1;
      [*] = ;
      [*] = ;               IntRegister0 := gc_map_hero_iHealthProperty;
      [*] = ;               GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;               var health : Integer = IntRegister1;
      [*] = ;
      [*] = ;               IntRegister0 := gc_map_hero_iMagicProperty;
      [*] = ;               GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;               var magic : Integer = IntRegister1;
      [*] = ;
      [*] = ;               var power1 : Integer = health + magic + skill27 * 3;
      [*] = ;
      [*] = ;               for j := ParserGetCountByHandle(pGOUnits)-1 downto 1 do
      [*] = ;               begin
      [*] = ;                  var pGOUnit : Integer = ParserSelectByHandleByIndex(pGOUnits, j);
      [*] = ;                  var unitID : Integer = ParserGetIntValueByKeyByHandle(pGOUnit, 'UnitID');
      [*] = ;
      [*] = ;                  var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;                  var rank : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Rank');
      [*] = ;                  power1 := power1 + rank;
      [*] = ;               end;
      [*] = ;
      [*] = ;               // enemy hero
      [*] = ;               var power2 : Integer = 0;
      [*] = ;               var ind : Integer = 0;
      [*] = ;               var pEnemyUnit0 : Integer = ParserSelectByHandleByIndex(pEnemyUnits, 0);
      [*] = ;               var class1 : Integer = ParserGetIntValueByKeyByHandle(pEnemyUnit0, 'HeroClass1');
      [*] = ;
      [*] = ;               if class1 > 0 then
      [*] = ;               begin
      [*] = ;                  var enHeroUID : Integer = ParserGetIntValueByKeyByHandle(pEnemyUnit0, 'HeroUID');
      [*] = ;                  var enHeroHandle : Integer = GetGameObjectHandleByUniqueId(enHeroUID);
      [*] = ;
      [*] = ;                  IntRegister0 := 27;
      [*] = ;                  GameObjectExecuteStateByHandle(enHeroHandle, 'GetSkillLevel');
      [*] = ;                  var skill27 : Integer = IntRegister1;
      [*] = ;
      [*] = ;                  IntRegister0 := gc_map_hero_iHealthProperty;
      [*] = ;                  GameObjectExecuteStateByHandle(enHeroHandle, 'GetProperty');
      [*] = ;                  var health : Integer = IntRegister1;
      [*] = ;
      [*] = ;                  IntRegister0 := gc_map_hero_iMagicProperty;
      [*] = ;                  GameObjectExecuteStateByHandle(enHeroHandle, 'GetProperty');
      [*] = ;                  var magic : Integer = IntRegister1;
      [*] = ;
      [*] = ;                  power2 := 2 * health + 2 * magic;
      [*] = ;                  ind := 1;
      [*] = ;               end;
      [*] = ;
      [*] = ;               for j := ParserGetCountByHandle(pEnemyUnits)-1 downto ind do
      [*] = ;               begin
      [*] = ;                  var pEnemyUnit : Integer = ParserSelectByHandleByIndex(pEnemyUnits, j);
      [*] = ;                  var unitID : Integer = ParserGetIntValueByKeyByHandle(pEnemyUnit, 'UnitID');
      [*] = ;
      [*] = ;                  var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;                  var rank : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Rank');
      [*] = ;                  power2 := power2 + rank;
      [*] = ;               end;
      [*] = ;
      [*] = ;               cond := (power1 > power2 * 3 / 2);
      [*] = ;            end;
      [*] = ;            //    2 - ���������� �����>=Param1
      [*] = ;            2 :
      [*] = ;            begin
      [*] = ;               IntRegister0 := 27;
      [*] = ;               GameObjectExecuteStateByHandle(goHandle, 'GetSkillLevel');
      [*] = ;               var skill : Integer = IntRegister1;
      [*] = ;
      [*] = ;               cond := (skill >= param1);
      [*] = ;            end;
      [*] = ;            //    3 - ����� ������>=Param1
      [*] = ;            3 :
      [*] = ;            begin
      [*] = ;               var karma : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iKarma);
      [*] = ;               cond := (karma >= param1);
      [*] = ;            end;
      [*] = ;            //    4 - ����� ������<=Param1
      [*] = ;            4 :
      [*] = ;            begin
      [*] = ;               var karma : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iKarma);
      [*] = ;               cond := (karma <= param1);
      [*] = ;            end;
      [*] = ;            //    5 - Random(100)<Param1
      [*] = ;            5 :
      [*] = ;            begin
      [*] = ;               if _rand_Random(100) < param1 then
      [*] = ;               cond := true
      [*] = ;               else
      [*] = ;               cond := false;
      [*] = ;            end;
      [*] = ;            //    6 - ���� ��������� � ���������>=Param1
      [*] = ;            6 :
      [*] = ;            begin
      [*] = ;               IntRegister0 := GetPlayerIndexByHandle(plHandle);
      [*] = ;               GameObjectExecuteStateByHandle(dummyHandle, 'GetPlayerAttitude');
      [*] = ;               var attitude : Integer = IntRegister0;
      [*] = ;               cond := (attitude >= param1);
      [*] = ;            end;
      [*] = ;            //    7 - �������� ��������� ������:
      [*] = ;            //        Param1=
      [*] = ;            7 :
      [*] = ;            begin
      [*] = ;               cond := true;
      [*] = ;               case param1 of
      [*] = ;                  // ���� ����� ������ ���� ��� �� �������
      [*] = ;                  // 0 - ���� ������,
      [*] = ;                  0 :
      [*] = ;                  begin
      [*] = ;                     cond := not CheckQuest(goHandle, gGame.arrRaceQuest[prRace]);
      [*] = ;
      [*] = ;                     if not cond then
      [*] = ;                     gIntRegister_EncounterQuestID := gGame.arrRaceQuest[prRace];
      [*] = ;                  end;
      [*] = ;                  // 1 - ������ ������
      [*] = ;                  1 :
      [*] = ;                  begin
      [*] = ;                     for j := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;                     if cond then
      [*] = ;                     begin
      [*] = ;                        var heroHandle : Integer = GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;                        if (heroHandle <> goHandle) and (not GetGameObjectBoolValueIndByHandle(heroHandle, gc_map_GOStack_MapUnit_bBuried)) then
      [*] = ;                        cond := not CheckQuest(heroHandle, gGame.arrRaceQuest[prRace]);
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     if not cond then
      [*] = ;                     gIntRegister_EncounterQuestID := gGame.arrRaceQuest[prRace];
      [*] = ;                  end;
      [*] = ;                  // 2 - � ������ ���������
      [*] = ;                  2 :
      [*] = ;                  begin
      [*] = ;                     for [MAIN]j := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;                     begin
      [*] = ;                        var heroHandle : Integer = GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;                        if (not GetGameObjectBoolValueIndByHandle(heroHandle, gc_map_GOStack_MapUnit_bBuried)) then
      [*] = ;                        begin
      [*] = ;                           var pGOParser : Integer = ParserSelectGameObject(heroHandle);
      [*] = ;                           var pGOQuests : Integer = ParserSelectByHandleByKey(pGOParser, 'Quests');
      [*] = ;
      [*] = ;                           for k := ParserGetCountByHandle(pGOQuests)-1 downto 0 do
      [*] = ;                           begin
      [*] = ;                              var pGOQuest : Integer = ParserSelectByHandleByIndex(pGOQuests, k);
      [*] = ;                              var qInd : Integer = ParserGetIntValueByKeyByHandle(pGOQuest, 'Index');
      [*] = ;                              var qProvInd : Integer = ParserGetIntValueByKeyByHandle(pGOQuest, 'ProvIndex');
      [*] = ;
      [*] = ;                              if (qInd = gGame.arrRaceQuest[prRace]) and (qProvInd <> prIndex) then
      [*] = ;                              begin
      [*] = ;                                 cond := false;
      [*] = ;                                 break(MAIN);
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     if not cond then
      [*] = ;                     gIntRegister_EncounterQuestID := gGame.arrRaceQuest[prRace];
      [*] = ;                  end;
      [*] = ;                  // ���� ������� �����
      [*] = ;                  // 4 - �������� ���� ������
      [*] = ;                  4 :
      [*] = ;                  begin
      [*] = ;                     if curQuestID > 0 then
      [*] = ;                     begin
      [*] = ;                        for j := 0 to ParserGetCountByHandle(pGOQuests)-1 do
      [*] = ;                        begin
      [*] = ;                           var pGOQuest : Integer = ParserSelectByHandleByIndex(pGOQuests, j);
      [*] = ;                           var qInd : Integer = ParserGetIntValueByKeyByHandle(pGOQuest, 'Index');
      [*] = ;                           var qProvInd : Integer = ParserGetIntValueByKeyByHandle(pGOQuest, 'ProvIndex');
      [*] = ;                           var qSiteInd : Integer = ParserGetIntValueByKeyByHandle(pGOQuest, 'SiteIndex');
      [*] = ;
      [*] = ;                           if (qInd = curQuestID) and (qProvInd = prIndex) and (qSiteInd = siteInd) then
      [*] = ;                           begin
      [*] = ;                              IntRegister0 := j;
      [*] = ;                              GameObjectExecuteStateByHandle(goHandle, 'CheckQuestDone');
      [*] = ;                              //if IntRegister1 > 0 then
      [*] = ;                              //newQueryID := IntToStr(IntRegister1);
      [*] = ;
      [*] = ;                              cond := ParserGetBoolValueByKeyByHandle(pGOQuest, 'Complete');
      [*] = ;                              break;
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  // ���� ����� ������� ����� ��� �� �������
      [*] = ;                  // 5 - ���� ������
      [*] = ;                  5 :
      [*] = ;                  begin
      [*] = ;                     if siteQuest < 0 then
      [*] = ;                     begin
      [*] = ;                        for j := 0 to ParserGetCountByHandle(pGOQuests)-1 do
      [*] = ;                        begin
      [*] = ;                           var pGOQuest : Integer = ParserSelectByHandleByIndex(pGOQuests, j);
      [*] = ;                           var qInd : Integer = ParserGetIntValueByKeyByHandle(pGOQuest, 'Index');
      [*] = ;
      [*] = ;                           if qInd = -siteQuest then
      [*] = ;                           begin
      [*] = ;                              cond := false;
      [*] = ;                              gIntRegister_EncounterQuestID := gGame.arrRaceQuest[prRace];
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  // 6 - ����� ������
      [*] = ;                  6 :
      [*] = ;                  begin
      [*] = ;                     if (siteQuest <= 0) and (not siteRandQuest) then
      [*] = ;                     begin
      [*] = ;                        cond := false;
      [*] = ;                        gIntRegister_EncounterQuestID := gGame.arrRaceQuest[prRace];
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            // 8 - ���� �� �������� ���� (Param1=0 � ���� �����, 1 - � ������ �����)
      [*] = ;            8 :
      [*] = ;            begin
      [*] = ;               var unionRace : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iUnion);
      [*] = ;
      [*] = ;               case param1 of
      [*] = ;                  0 : cond := (unionRace <> prRace);
      [*] = ;                  1 : cond := (unionRace = 0) or (unionRace = prRace);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            //    9 (EFFECT IS DELETED) - ���� ��������� ������(8) �� �������� �����!=Param1 (�� ���������)
      [*] = ;            //    10 - ���� Random(100-����������*10)<Param1
      [*] = ;            10 :
      [*] = ;            begin
      [*] = ;               IntRegister0 := 27;
      [*] = ;               GameObjectExecuteStateByHandle(goHandle, 'GetSkillLevel');
      [*] = ;               var skill : Integer = IntRegister1;
      [*] = ;
      [*] = ;               cond := (_rand_Random(100 - skill * 10) < param1);
      [*] = ;            end;
      [*] = ;            //    11 - ���� � ��������� ��� ��������� Param1
      [*] = ;            11 :
      [*] = ;            begin
      [*] = ;               IntRegister0 := param1;
      [*] = ;               GameObjectExecuteStateByHandle(dummyHandle, 'CheckOuterBuilding');
      [*] = ;               var isBuilt : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;               cond := (not isBuilt);
      [*] = ;            end;
      [*] = ;            //    12 - ���� � ��������� ���� ����� ��� ���������
      [*] = ;            12 :
      [*] = ;            begin
      [*] = ;               GameObjectExecuteStateByHandle(dummyHandle, 'GetFreeOuterBuildSlot');
      [*] = ;               var slot : Integer = IntRegister0;
      [*] = ;
      [*] = ;               cond := (slot >= 0);
      [*] = ;            end;
      [*] = ;            //    13 - ���� ������� �������� Param1!=0
      [*] = ;            13 :
      [*] = ;            begin
      [*] = ;               cond := ((gGame.gameType = 2) and (gCampaign.arrDialogs[param1] <> 0));
      [*] = ;            end;
      [*] = ;            //    14 - �������� ������� �������
      [*] = ;            14 :
      [*] = ;            begin
      [*] = ;               var pPlParser : Integer = ParserSelectPlayer(plHandle);
      [*] = ;               var pEventTimers : Integer = ParserSelectByHandleByKey(pPlParser, 'EventTimers');
      [*] = ;
      [*] = ;               for j := ParserGetCountByHandle(pEventTimers)-1 downto 0 do
      [*] = ;               begin
      [*] = ;                  var pEvenTimer : Integer = ParserSelectByHandleByIndex(pEventTimers, j);
      [*] = ;                  var eventID : Integer = ParserGetIntValueByKeyByHandle(pEvenTimer, 'EventID');
      [*] = ;                  var timer : Integer = ParserGetIntValueByKeyByHandle(pEvenTimer, 'Timer');
      [*] = ;
      [*] = ;                  cond := (timer > 0);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if not cond then
      [*] = ;            newQueryID := IntToStr(param2);
      [*] = ;      end;
      [*] = ;      //16 ������ ����� �� Power+Random(Param1)% ����� (�� ����� �����).
      [*] = ;      16 :
      [*] = ;      begin
      [*] = ;         var pGOUnit : Integer = ParserSelectByHandleByIndex(pGOUnits, 0);
      [*] = ;         var curLife : Integer = ParserGetIntValueByKeyByHandle(pGOUnit, 'CurLife');
      [*] = ;
      [*] = ;         if curLife > 1 then
      [*] = ;         begin
      [*] = ;            var effect : Integer = CalcEffect(pEncounter, 16, difficulty, goDipl);
      [*] = ;
      [*] = ;            IntRegister0 := pGOUnit;
      [*] = ;            IntRegister1 := pGOUnits;
      [*] = ;            IntRegister2 := gc_battle_unit_iMaxLife;
      [*] = ;            MapExecuteState('GetUnitPropertyByParser');
      [*] = ;            var maxLife : Integer = IntRegister3;
      [*] = ;
      [*] = ;            var hit : Integer = (maxLife * effect) div 100;
      [*] = ;            curLife := curLife - hit;
      [*] = ;            if curLife < 1 then
      [*] = ;               curLife := 1;
      [*] = ;
      [*] = ;            ParserSetIntValueByKeyByHandle(pGOUnit, 'CurLife', curLife);
      [*] = ;            ParserSetFloatValueByKeyByHandle(pGOUnit, 'FCurLife', curLife);
      [*] = ;            ParserSetFloatValueByKeyByHandle(pGOUnit, 'LifeRatio', curLife / maxLife);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //17 �������� ���������� ������ Power=0 - ��������, 1 - ��������, 2 - �����
      [*] = ;      17 : begin
      [*] = ;         case power of
      [*] = ;            1 :
      [*] = ;            begin
      [*] = ;               gIntRegister_EncounterQuestID := gGame.arrRaceQuest[prRace];
      [*] = ;            end;
      [*] = ;            2 :
      [*] = ;            begin
      [*] = ;               if siteRandQuest then
      [*] = ;               begin
      [*] = ;                  var count : Integer = 0;
      [*] = ;                  _rand_ClearRoll;
      [*] = ;
      [*] = ;                  var pQuests : Integer = gPrototypeData.quests.handle;
      [*] = ;                  for j := ParserGetCountByHandle(pQuests)-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     var pQuest : Integer = ParserSelectByHandleByIndex(pQuests, j);
      [*] = ;                     var pQuestObjectives : Integer = ParserSelectByHandleByKey(pQuest, 'Objectives');
      [*] = ;                     var pQuestObjective : Integer = ParserSelectByHandleByIndex(pQuestObjectives, 0);
      [*] = ;                     var objIndex : Integer = ParserGetIntValueByKeyByHandle(pQuestObjective, 'Index');
      [*] = ;                     var giver : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'Giver');
      [*] = ;
      [*] = ;                     if (giver = siteID) and (gIntRegister_EncounterDifficulty = objIndex) then
      [*] = ;                     begin
      [*] = ;                        gArrRollerN[count] := j;
      [*] = ;                        gArrRollerP[count] := ParserGetIntValueByKeyByHandle(pQuest, 'Possibility');
      [*] = ;                        count := count + 1;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if count > 0 then
      [*] = ;                  begin
      [*] = ;                     var questID : Integer = _rand_Roll(false);
      [*] = ;
      [*] = ;                     gIntRegister_EncounterQuestID := questID;
      [*] = ;
      [*] = ;                     province_flags := province_flags or gc_province_uf_sites_updated;
      [*] = ;
      [*] = ;                     ParserSetIntValueByKeyByHandle(pProvSite, 'Quest', questID);
      [*] = ;                     ParserSetBoolValueByKeyByHandle(pProvSite, 'RandomQuest', false);
      [*] = ;
      [*] = ;                     var pQuest : Integer = ParserSelectByHandleByIndex(pQuests, questID);
      [*] = ;                     var pQuestObjectives : Integer = ParserSelectByHandleByKey(pQuest, 'Objectives');
      [*] = ;                     var pQuestObjective : Integer = ParserSelectByHandleByIndex(pQuestObjectives, 0);
      [*] = ;                     var questTarget : Integer = ParserGetIntValueByKeyByHandle(pQuestObjective, 'Target');
      [*] = ;                     var questQuantity : Integer = ParserGetIntValueByKeyByHandle(pQuestObjective, 'Quantity');
      [*] = ;                     var questParam : Integer = ParserGetIntValueByKeyByHandle(pQuestObjective, 'Param');
      [*] = ;                     var questType : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'Type');
      [*] = ;
      [*] = ;                     if questType = 8 then
      [*] = ;                     begin
      [*] = ;                        var unitCount : Integer = questQuantity + _rand_Random(questParam);
      [*] = ;
      [*] = ;                        IntRegister0 := questTarget; // unit rank
      [*] = ;                        GameObjectExecuteStateByHandle(dummyHandle, 'GetQuestUnit');
      [*] = ;                        var unitID : Integer = IntRegister1;
      [*] = ;
      [*] = ;                        if unitID > 0 then
      [*] = ;                        begin
      [*] = ;                           ParserSetIntValueByKeyByHandle(pProvSite, 'Level', unitID);
      [*] = ;                           ParserSetIntValueByKeyByHandle(pProvSite, 'QuestData', unitCount);
      [*] = ;                        end
      [*] = ;                        else
      [*] = ;                        begin
      [*] = ;                           count := 0;
      [*] = ;                           _rand_ClearRoll;
      [*] = ;
      [*] = ;                           for i := ParserGetCountByHandle(pUnits)-1 downto 0 do
      [*] = ;                           begin
      [*] = ;                              if _map_IsQuestUnitEnabled(ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pUnits, i), 'UnitID')) then
      [*] = ;                              begin
      [*] = ;                                 var pUnit : Integer = ParserSelectByHandleByIndex(pUnits, i);
      [*] = ;                                 var rank : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Rank');
      [*] = ;
      [*] = ;                                 if rank = questTarget then
      [*] = ;                                 begin
      [*] = ;                                    gArrRollerN[count] := i;
      [*] = ;                                    gArrRollerP[count] := 10;
      [*] = ;                                    count := count + 1;
      [*] = ;                                 end;
      [*] = ;                              end;
      [*] = ;                           end;
      [*] = ;
      [*] = ;                           if count > 0 then
      [*] = ;                           begin
      [*] = ;                              unitID := _rand_Roll(false);
      [*] = ;
      [*] = ;                              ParserSetIntValueByKeyByHandle(pProvSite, 'Level', unitID);
      [*] = ;                              ParserSetIntValueByKeyByHandle(pProvSite, 'QuestData', unitCount);
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;
      [*] = ;                        gStringRegister_UnitName := GetLocaleTableListItemByID('unit', IntToStr(unitID));
      [*] = ;                        gIntRegister_UnitCount := unitCount;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  gIntRegister_EncounterQuestID := Round(Abs(siteQuest));
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var pQuest : Integer = ParserSelectByHandleByIndex(pQuests, gIntRegister_EncounterQuestID);
      [*] = ;
      [*] = ;         //    ���� Param1
      [*] = ;         //    0 - ��������� ������
      [*] = ;         //    1 - ��������
      [*] = ;         //    2 - ����������
      [*] = ;         case param1 of
      [*] = ;            0 : newQueryID := ParserGetValueByKeyByHandle(pQuest, 'EncInit');
      [*] = ;            1 : newQueryID := ParserGetValueByKeyByHandle(pQuest, 'EncWait');
      [*] = ;            2 : newQueryID := ParserGetValueByKeyByHandle(pQuest, 'EncSuccess');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //18 ��������� ��������� �������� ������ Power=0 - ������, 1 - ����������, 2 - �����
      [*] = ;      18 : begin
      [*] = ;         case power of
      [*] = ;            // 0 - ������
      [*] = ;            0 :
      [*] = ;            begin
      [*] = ;               if heroQuestCount >= gc_HeroQuestLimit then
      [*] = ;                  newQueryID := IntToStr(gc_gui_query_heroQuestLimit)
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  var questID : Integer = gIntRegister_EncounterQuestID;
      [*] = ;                  var pQuest : Integer = ParserSelectByHandleByIndex(pQuests, questID);
      [*] = ;                  var pQuestObjectives : Integer = ParserSelectByHandleByKey(pQuest, 'Objectives');
      [*] = ;                  var qGiver : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'Giver');
      [*] = ;
      [*] = ;                  var pGOQuest : Integer = ParserAddChildByIndex(pGOQuests, '*');
      [*] = ;                  ParserSetIntValueByKeyByHandle(pGOQuest, 'Index', questID);
      [*] = ;                  ParserSetBoolValueByKeyByHandle(pGOQuest, 'Complete', false);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pGOQuest, 'ProvIndex', prIndex);
      [*] = ;
      [*] = ;                  if qGiver > 0 then
      [*] = ;                     ParserSetIntValueByKeyByHandle(pGOQuest, 'SiteIndex', siteInd)
      [*] = ;                  else
      [*] = ;                     ParserSetIntValueByKeyByHandle(pGOQuest, 'SiteIndex', -1);
      [*] = ;
      [*] = ;                  ParserSetIntValueByKeyByHandle(pGOQuest, 'Time', 0);
      [*] = ;                  var pArProgress : Integer = ParserAddChildByIndex(pGOQuest, 'ArProgress');
      [*] = ;                  for j := ParserGetCountByHandle(pQuestObjectives)-1 downto 0 do
      [*] = ;                  begin
      [*] = ;                     ParserSetIntValueByKeyByHandle(ParserAddChildByIndex(pArProgress, '*'), 'Progress', 0);
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  if qGiver > 0 then
      [*] = ;                  begin
      [*] = ;                     ParserSetIntValueByKeyByHandle(pProvSite, 'Quest', -1*ParserGetIntValueByKeyByHandle(pProvSite, 'Quest'));
      [*] = ;                     province_flags := province_flags or gc_province_uf_sites_updated;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  IntRegister0 := heroQuestCount;
      [*] = ;                  GameObjectExecuteStateByHandle(goHandle, 'CheckQuestDone');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            // 1 - ����������
      [*] = ;            1 :
      [*] = ;            begin
      [*] = ;               var pQuest : Integer = ParserSelectByHandleByIndex(pQuests, curQuestID);
      [*] = ;               var qType : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'Type');
      [*] = ;               var qExp : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'Exp');
      [*] = ;
      [*] = ;               var pGOQuest : Integer = GetHeroQuest(goHandle, curQuestID);
      [*] = ;
      [*] = ;               if pGOQuest <> 0 then
      [*] = ;               begin
      [*] = ;                  if qType = 7 then
      [*] = ;                  begin
      [*] = ;                     var questData : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'QuestData');
      [*] = ;                     CheckItem(goHandle, questData);
      [*] = ;
      [*] = ;                     var pItem : Integer = ParserSelectByHandleByIndex(pItems, questData);
      [*] = ;                     var shopLevel : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ShopLevel');
      [*] = ;                     var expAdd : Integer = qExp * shopLevel;
      [*] = ;                     var heroExp : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iExp);
      [*] = ;                     heroExp := heroExp + expAdd;
      [*] = ;                     SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iExp, heroExp);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     if qType = 9 then
      [*] = ;                     begin
      [*] = ;                        var pQuestObjectives : Integer = ParserSelectByHandleByKey(pQuest, 'Objectives');
      [*] = ;                        var pQuestObjective : Integer = ParserSelectByHandleByIndex(pQuestObjectives, 0);
      [*] = ;                        var param : Integer = ParserGetIntValueByKeyByHandle(pQuestObjective, 'Param');
      [*] = ;
      [*] = ;                        CheckItem(goHandle, param);
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     if qType = 8 then
      [*] = ;                     begin
      [*] = ;                        ParserSetIntValueByKeyByHandle(pProvSite, 'Level', 0);
      [*] = ;                        province_flags := province_flags or gc_province_uf_sites_updated;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     var heroExp : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iExp);
      [*] = ;                     heroExp := heroExp + qExp;
      [*] = ;                     SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iExp, heroExp);
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  var qGiver : Integer = ParserGetIntValueByKeyByHandle(pQuest, 'Giver');
      [*] = ;                  if qGiver > 0 then
      [*] = ;                  begin
      [*] = ;                     province_flags := province_flags or gc_province_uf_sites_updated;
      [*] = ;                     ParserSetIntValueByKeyByHandle(pProvSite, 'Quest', 0);
      [*] = ;                     var pSite : Integer = ParserSelectByHandleByIndex(gPrototypeData.sites.handle, siteID);
      [*] = ;                     var pSiteAbilities : Integer = ParserSelectByHandleByKey(pSite, 'Abilities');
      [*] = ;                     for j := ParserGetCountByHandle(pSiteAbilities)-1 downto 0 do
      [*] = ;                     begin
      [*] = ;                        var pSiteAbility : Integer = ParserSelectByHandleByIndex(pSiteAbilities, j);
      [*] = ;                        var abilID : Integer = ParserGetIntValueByKeyByHandle(pSiteAbility, 'AbilityID');
      [*] = ;
      [*] = ;                        if abilID = 18 then
      [*] = ;                           ParserSetBoolValueByKeyByHandle(pProvSite, 'RandomQuest', true);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  ParserSetBoolValueByKeyByHandle(pGOQuest, 'Complete', true);
      [*] = ;                  var questDone : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iQuestDone);
      [*] = ;                  SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iQuestDone, questDone+1);
      [*] = ;
      [*] = ;                  ParserFreeByHandle(pGOQuest);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            // 2 - �����
      [*] = ;            2 :
      [*] = ;            begin
      [*] = ;               var pGOQuest : Integer = GetHeroQuest(goHandle, curQuestID);
      [*] = ;               if pGOQuest <> 0 then
      [*] = ;                  qNum := ParserGetIntValueByKeyByHandle(pGOQuest, 'ProvIndex');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //19 ��������� ���� � ������ ������� ���������
      [*] = ;      19 : begin
      [*] = ;         var prRace : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceRace');
      [*] = ;         var a_id : Integer;
      [*] = ;
      [*] = ;         SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iUnion, prRace);
      [*] = ;         // achievement
      [*] = ;         case prRace of
      [*] = ;            2 : a_id := gc_achiev_alliance_with_elves;
      [*] = ;            3 : a_id := gc_achiev_alliance_with_dwarves;
      [*] = ;            4 : a_id := gc_achiev_alliance_with_goblins;
      [*] = ;            5 : a_id := gc_achiev_alliance_with_orcs;
      [*] = ;            6 : a_id := gc_achiev_alliance_with_halflings;
      [*] = ;            7 : a_id := gc_achiev_alliance_with_centaurs;
      [*] = ;            8 : a_id := gc_achiev_alliance_with_lizardmen;
      [*] = ;            else a_id := 0;
      [*] = ;         end;
      [*] = ;         if a_id <> 0 then
      [*] = ;            _achievement_Trigger(a_id,'');
      [*] = ;         //
      [*] = ;      end;
      [*] = ;      //20 �������� ��������� ������� � ��������� �� Power
      [*] = ;      20 : begin
      [*] = ;         IntRegister0 := plHandle;
      [*] = ;         IntRegister1 := power;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'ChangeAttitude');
      [*] = ;      end;
      [*] = ;      //21 �������� ������� Power
      [*] = ;      21 : begin
      [*] = ;         IntRegister0 := power;
      [*] = ;         MapExecuteState('GetItemParserByID');
      [*] = ;         var pItem : Integer = IntRegister1;
      [*] = ;         var itemID : Integer = ParserGetIntValueByKeyByHandle(pItem, 'ItemID');
      [*] = ;         var itemDur : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Durability');
      [*] = ;
      [*] = ;         // Loot items parser for visualization in ToolQueryWindow
      [*] = ;         var pGOSiteLootItem : Integer = ParserAddChildByIndex(pGOSiteLootItems, '*');
      [*] = ;         ParserSetIntValueByKeyByHandle(pGOSiteLootItem, 'ItemID', itemID);
      [*] = ;         ParserSetIntValueByKeyByHandle(pGOSiteLootItem, 'Durability', itemDur);
      [*] = ;         ParserSetBoolValueByKeyByHandle(pGOSiteLootItem, 'Picked', false);
      [*] = ;
      [*] = ;         IntRegister0 := itemID;
      [*] = ;         IntRegister1 := itemDur;
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'TakeLootItem');
      [*] = ;         if not BoolRegister0 then
      [*] = ;         begin
      [*] = ;            var pGOLeftLootItem : Integer = ParserAddChildByIndex(pGOLeftLootItems, '*');
      [*] = ;            ParserSetIntValueByKeyByHandle(pGOLeftLootItem, 'ItemID', itemID);
      [*] = ;            ParserSetIntValueByKeyByHandle(pGOLeftLootItem, 'Durability', itemDur);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //22 �������� Param1 ��������� �� ������� Power
      [*] = ;      22 : begin
      [*] = ;         var pMyDefenders : Integer = ParserSelectByHandleByKey(pCastle, 'Defenders');
      [*] = ;         var pMyDefender : Integer = ParserSelectByHandleByIndex(pMyDefenders, power);
      [*] = ;         var count : Integer = ParserGetIntValueByKeyByHandle(pMyDefender, 'Count');
      [*] = ;         if count >= 0 then
      [*] = ;         count := count + param1;
      [*] = ;         ParserSetIntValueByKeyByHandle(pMyDefender, 'Count', count);
      [*] = ;
      [*] = ;         //var itemID : Integer = gPrototypeData.items.number + gPrototypeData.spells.number + power;
      [*] = ;         IntRegister0 := power;
      [*] = ;         IntRegister1 := 11;
      [*] = ;         MapExecuteState('GetExtItemIDByType');
      [*] = ;         var itemID : Integer = IntRegister2;
      [*] = ;      end;
      [*] = ;      //23 �������� ����� � ��� �����
      [*] = ;      23 : begin
      [*] = ;         for j := ParserGetCountByHandle(pGOUnits)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pGOUnit : Integer = ParserSelectByHandleByIndex(pGOUnits, j);
      [*] = ;            var curLife : Integer = ParserGetIntValueByKeyByHandle(pGOUnit, 'CurLife');
      [*] = ;            if curLife > 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := pGOUnit;
      [*] = ;               IntRegister1 := pGOUnits;
      [*] = ;               IntRegister2 := gc_battle_unit_iMaxLife;
      [*] = ;               MapExecuteState('GetUnitPropertyByParser');
      [*] = ;               var maxLife : Integer = IntRegister3;
      [*] = ;
      [*] = ;               ParserSetIntValueByKeyByHandle(pGOUnit, 'CurLife', maxLife);
      [*] = ;               ParserSetFloatValueByKeyByHandle(pGOUnit, 'FCurLife', maxLife);
      [*] = ;               ParserSetFloatValueByKeyByHandle(pGOUnit, 'LifeRatio', curLife / maxLife);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //24 ����� � ������� �����
      [*] = ;      24 : begin
      [*] = ;         if bInterfacePlayer then
      [*] = ;         begin
      [*] = ;         LogI('SiteID = ' + IntToStr(siteID));
      [*] = ;
      [*] = ;         var pShop : Integer = 0;
      [*] = ;         if power = 0 then
      [*] = ;            pShop := ParserSelectByHandleByKey(pProvSite, 'Shop')
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            pShop := ParserAddChildByIndex(pProvSite, 'Shop');
      [*] = ;            var pShopItems : Integer = ParserAddChildByIndex(pShop, 'Items');
      [*] = ;
      [*] = ;            // setup price modifiers
      [*] = ;            var pPriceModifiers : Integer = ParserAddChildByIndex(pShop, 'PriceModifiers');
      [*] = ;            for i := 0 to gGame.map.players-1 do
      [*] = ;            begin
      [*] = ;               var pPriceModifier : Integer = ParserAddChildByIndex(pPriceModifiers, '*');
      [*] = ;               ParserSetIntValueByKeyByHandle(pPriceModifier, 'PlayerIndex', i);
      [*] = ;               ParserSetIntValueByKeyByHandle(pPriceModifier, 'PriceModifier', 300);
      [*] = ;            end;
      [*] = ;
      [*] = ;            var stuff : Integer = 8 + _rand_Random(5);
      [*] = ;            _rand_ClearRoll();
      [*] = ;            var randCount : Integer = 0;
      [*] = ;
      [*] = ;            for j := 0 to ParserGetCountByHandle(pItems)-1 do
      [*] = ;            begin
      [*] = ;               var pItem : Integer = ParserSelectByHandleByIndex(pItems, j);
      [*] = ;               var rarity : Integer = ParserGetIntValueByKeyByHandle(pItem, 'Rarity');
      [*] = ;
      [*] = ;               if rarity > 1 then
      [*] = ;               begin
      [*] = ;                  gArrRollerN[randCount] := j;
      [*] = ;                  gArrRollerP[randCount] := 8 - rarity;
      [*] = ;                  randCount := randCount + 1;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            // fill shop items
      [*] = ;            if randCount > 0 then
      [*] = ;            begin
      [*] = ;               if stuff > randCount then
      [*] = ;                  stuff := randCount;
      [*] = ;
      [*] = ;               for i := 0 to stuff-1 do
      [*] = ;               begin
      [*] = ;                  var pShopItem : Integer = ParserAddChildByIndex(pShopItems, '*');
      [*] = ;                  var itemID : Integer = _rand_Roll(true);
      [*] = ;
      [*] = ;                  var count : Integer = 1 + _rand_Random(3);
      [*] = ;
      [*] = ;                  ParserSetIntValueByKeyByHandle(pShopItem, 'ItemID', itemID);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pShopItem, 'Count', count);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         _gv_SetMapLock(100,_log_name+' [1172]');
      [*] = ;
      [*] = ;         gIntRegister_MapCurrentShop := pShop;
      [*] = ;         gIntRegister_GUIActiveHeroUID1 := GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;         gIntRegister_GUIShopSortMode := 0;
      [*] = ;         gIntRegister_GUICurHeroMode := gc_HeroPanelInventory;
      [*] = ;         GUIExecuteState('map.CreateHeroWindow');
      [*] = ;
      [*] = ;         //GameObjectExecuteStateByHandle(goHandle, 'CancelOrders');
      [*] = ;         //IntRegister0 := goHandle;
      [*] = ;         //GUIExecuteState('map.HeroHUDControlTask');
      [*] = ;
      [*] = ;         openHeroWindow := true;
      [*] = ;      end;
      [*] = ;      end;
      [*] = ;      //25 ���� ����� Power + Random(Param1) �����, ���� Param2>0, �� � ���� ��� ������
      [*] = ;      25 : begin
      [*] = ;         var expAdd : Integer = power + _rand_Random(param1);
      [*] = ;         var heroExp : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iExp);
      [*] = ;         SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iExp, heroExp + expAdd);
      [*] = ;
      [*] = ;         if param2 > 0 then
      [*] = ;         begin
      [*] = ;            for j := ParserGetCountByHandle(pGOUnits)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var pGOUnit : Integer = ParserSelectByHandleByIndex(pGOUnits, j);
      [*] = ;               var exp : Integer = ParserGetIntValueByKeyByHandle(pGOUnit, 'Exp');
      [*] = ;               exp := exp + expAdd;
      [*] = ;               ParserSetIntValueByKeyByHandle(pGOUnit, 'Exp', exp);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if bInterfacePlayer then
      [*] = ;            gBoolRegister_CheckLevelUp := true;
      [*] = ;      end;
      [*] = ;      //26 �������� ������ ��� ������ ����� �� Power+Random(Power1). ���� Param2>0 �������� �������� � ���� ������, � ������ ����������, ����<0 - ��������, �� ��������� �� �����������.
      [*] = ;      26 : begin
      [*] = ;         IntRegister1 := power + _rand_Random(param1);
      [*] = ;         IntRegister0 := pGOUnits;
      [*] = ;         IntRegister2 := param2;
      [*] = ;         MapExecuteState('map.ChangeArmyMoral');
      [*] = ;      end;
      [*] = ;      //27 ���������� ������� ���������� ������ � Power (1-4)
      [*] = ;      27 : begin
      [*] = ;         gIntRegister_EncounterGuardLevel := power-1;
      [*] = ;      end;
      [*] = ;      //28 ���������� ������� ���� (���� POwer>0 - �������� ��� ������ Power)
      [*] = ;      28 : begin
      [*] = ;         province_flags := province_flags or gc_province_uf_sites_updated;
      [*] = ;         if power > 0 then
      [*] = ;         begin
      [*] = ;            ParserSetIntValueByKeyByHandle(pProvSite, 'SiteID', power);
      [*] = ;            if ParserGetCountByHandle(ParserSelectByHandleByKey(ParserSelectByHandleByIndex(gPrototypeData.sites.handle, power), 'Guards')) = 0 then
      [*] = ;               ParserClearByHandle(ParserSelectByHandleByKey(pProvSite, 'Guard'));
      [*] = ;         end
      [*] = ;         else
      [*] = ;            ParserClearByHandle(pProvSite);
      [*] = ;      end;
      [*] = ;      //29 �������� � ������ ����� ����� Power. ���� Param1>0 - ������� ���� �����. ���� Param2>0 - �� �������� � ������������ Param2
      [*] = ;      29 : begin
      [*] = ;         if bInterfacePlayer then
      [*] = ;         begin
      [*] = ;            if (param1 < 2) then // assign recruit units
      [*] = ;            begin
      [*] = ;               var count : Integer = ParserGetCountByHandle(pEncRecruitUnits);
      [*] = ;               
      [*] = ;               function AlreadyRecruitable(unitID : Integer) : Boolean;
      [*] = ;               begin
      [*] = ;                  Result := False;
      [*] = ;                  
      [*] = ;                  var i, pUnitForHire : Integer;
      [*] = ;                  for i := 0 to count-1 do
      [*] = ;                  begin
      [*] = ;                     pUnitForHire := ParserSelectByHandleByIndex(pEncRecruitUnits, i);
      [*] = ;                     if ParserGetIntValueByKeyByHandle(pUnitForHire, 'UnitID') = unitID then
      [*] = ;                     begin
      [*] = ;                        Result := True;
      [*] = ;                        break;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               
      [*] = ;               if not _map_IsUnitEnabled(power) then
      [*] = ;                  power := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(gPrototypeData.units.handle, power), 'ReplacementID');
      [*] = ;               
      [*] = ;               if (power > 0) and (count<=11) and ((param2 = 0) or (param2 >= (RandomExt*100))) and (not AlreadyRecruitable(power)) then
      [*] = ;               begin
      [*] = ;                  var pUnitForHire : Integer = ParserAddChildByIndex(pEncRecruitUnits, '*');
      [*] = ;                  ParserSetIntValueByKeyByHandle(pUnitForHire, 'UnitID', power);
      [*] = ;                  if (param1 = 1) then
      [*] = ;                     ParserSetBoolValueByKeyByHandle(pUnitForHire, 'Mercenary', true);
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if (param1 = 2) then // finally open recruitment window
      [*] = ;            begin
      [*] = ;               _gv_SetMapLock(100,_log_name+' [1248]');
      [*] = ;
      [*] = ;               gIntRegister_GUIActiveHeroUID1 := GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;               gIntRegister_GUICurHeroMode := gc_HeroPanelUnitsOnly;
      [*] = ;               GUIExecuteState('map.CreateHeroWindow');
      [*] = ;
      [*] = ;               openHeroWindow := true;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //30 (effect is unneeded) ���������� � DialogParam=3 �������� ������� ��������� (Power ������ ���� 1)
      [*] = ;      30 : begin
      [*] = ;      end;
      [*] = ;      //31 ������������ � ������ ����� ����� ���� Power ������ Param1+Random(Param2).
      [*] = ;      31 : begin
      [*] = ;         var unitID : Integer = power;
      [*] = ;         var level : Integer = param1 + _rand_Random(param2);
      [*] = ;
      [*] = ;         // achievement
      [*] = ;         if (unitID = 19) or (unitID = 20) then
      [*] = ;            _achievement_Trigger(gc_achiev_undead_50,'');
      [*] = ;         //
      [*] = ;         IntRegister0 := unitID;
      [*] = ;         IntRegister1 := level;
      [*] = ;         MapExecuteState('GetUnitExpByLevel');
      [*] = ;         var unitExp : Integer = IntRegister2;
      [*] = ;
      [*] = ;         var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;         var rank : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Rank');
      [*] = ;
      [*] = ;         IntRegister0 := rank;
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'GetFreeUnitSlot');
      [*] = ;         var slotRank : Integer = IntRegister1;
      [*] = ;         var slotInd : Integer = IntRegister2;
      [*] = ;
      [*] = ;         if (slotRank > -1) and (slotInd > -1) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := unitID;
      [*] = ;            IntRegister1 := unitExp;
      [*] = ;            IntRegister2 := slotRank;
      [*] = ;            IntRegister3 := slotInd;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'AddUnitToArmy');
      [*] = ;         end
      [*] = ;         else if bInterfacePlayer then
      [*] = ;         begin
      [*] = ;            var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;            var pGOUnits : Integer =  ParserSelectByHandleByKey(pGOParser, 'Units');
      [*] = ;            var goUID : Integer = GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;
      [*] = ;            IntRegister0 := pGOUnits;
      [*] = ;            IntRegister1 := unitID;
      [*] = ;            IntRegister2 := unitExp;
      [*] = ;            IntRegister3 := 0;
      [*] = ;            MapExecuteState('AddUnitToParser');
      [*] = ;            var pGOUnit : Integer = IntRegister4;
      [*] = ;            ParserSetIntValueByKeyByHandle(pGOUnit, 'SlotRank', 5);
      [*] = ;            ParserSetIntValueByKeyByHandle(pGOUnit, 'SlotIndex', 0);
      [*] = ;
      [*] = ;            _gv_SetMapLock(100,_log_name+' [56]');
      [*] = ;
      [*] = ;            // show unit window
      [*] = ;            gIntRegister_GUIActiveHeroUID1 := goUID;
      [*] = ;            gIntRegister_GUIActiveHeroUID2 := 0;
      [*] = ;            gIntRegister_GUICurHeroMode := gc_HeroPanelExtraUnit;
      [*] = ;            GUIExecuteState('map.CreateHeroWindow');
      [*] = ;
      [*] = ;            openHeroWindow := true;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //32 � ������� ��������� ���������� ��������� Power
      [*] = ;      32 : begin
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetFreeOuterBuildSlot');
      [*] = ;         var slotInd : Integer = IntRegister0;
      [*] = ;
      [*] = ;         if slotInd > -1 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := power;
      [*] = ;            IntRegister1 := slotInd;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'AddOuterBuilding');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //33 �������� ��������� �������� ����� � ��� ������ �� Power, ��� ����������� ����� ������ �������������. Param1=0 - ���������� ��������, 1 - � %, Param2=1 - ��������� ������ �� �����.
      [*] = ;      33 : begin
      [*] = ;         IntRegister0 := pGOUnits;
      [*] = ;         IntRegister1 := power;
      [*] = ;         IntRegister2 := param1;
      [*] = ;         IntRegister3 := param2;
      [*] = ;         MapExecuteState('map.ChangeArmyLife');
      [*] = ;      end;
      [*] = ;      //34 ��������� ����� ���� ����� �� Power
      [*] = ;      34 : begin
      [*] = ;         SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iMoveBonus, power);
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'UpdatePath');
      [*] = ;
      [*] = ;         if GetPlayerIndexByHandle(plHandle) = gIntRegister_MapMyPlayerIndex then
      [*] = ;            gBoolRegister_GUIUpdateMapDrawPath := true;
      [*] = ;      end;
      [*] = ;      //35 ��������� ����� � ������� ��������� (��� � ��������, ���� ������� ��������)
      [*] = ;      35 : begin
      [*] = ;         GameObjectExecuteStateByHandle(cDummyHandle, 'IsUnderSiege');
      [*] = ;         if not BoolRegister0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := pCastle;
      [*] = ;            BoolRegister0 := true;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'JumpToProvince');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var teleport : Boolean = false;
      [*] = ;            for j := 0 to 5 do
      [*] = ;            begin
      [*] = ;               IntRegister0 := pCastle;
      [*] = ;               IntRegister1 := j;
      [*] = ;               MapExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;               var pNProvince : Integer = IntRegister2;
      [*] = ;               var nDummyUID : Integer = ParserGetIntValueByKeyByHandle(pNProvince, 'DummyUID');
      [*] = ;               var nDummyHandle : Integer = GetGameObjectHandleByUniqueId(nDummyUID);
      [*] = ;
      [*] = ;               var provPlName : String = ParserGetValueByKeyByHandle(pNProvince, 'Player');
      [*] = ;               var provPlHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;
      [*] = ;               GameObjectExecuteStateByHandle(nDummyHandle, 'IsPlayable');
      [*] = ;               var playable : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;               GameObjectExecuteStateByHandle(nDummyHandle, 'IsUnderSiege');
      [*] = ;               if playable and (provPlHandle = plHandle) and (not BoolRegister0) then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := pNProvince;
      [*] = ;                  BoolRegister0 := true;
      [*] = ;                  GameObjectExecuteStateByHandle(goHandle, 'JumpToProvince');
      [*] = ;
      [*] = ;                  teleport := true;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if not teleport then
      [*] = ;               newQueryID := IntToStr(gc_gui_query_playerAstralGatesUnluck);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      //36 ��� ���� ������ � ������ �����, ���� ����������� �� ����� ���� Power, ���������� ��� � �������� � Power. �� ��������� �� ������������ ������.
      [*] = ;      36 : begin
      [*] = ;         var i : Integer;
      [*] = ;         IntRegister0 := pGOUnits;
      [*] = ;         ExecuteState('map.GetArmyHeroHandle');
      [*] = ;         var heroHandle : Integer = IntRegister1;
      [*] = ;
      [*] = ;         for i := ParserGetCountByHandle(pGOUnits)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pGOUnit : Integer = ParserSelectByHandleByIndex(pGOUnits, i);
      [*] = ;            var unitID : Integer = ParserGetIntValueByKeyByHandle(pGOUnit, 'UnitID');
      [*] = ;            var curLife : Integer = ParserGetIntValueByKeyByHandle(pGOUnit, 'CurLife');
      [*] = ;            var moralMod : Integer = ParserGetIntValueByKeyByHandle(pGOUnit, 'MoralMod');
      [*] = ;
      [*] = ;            var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;
      [*] = ;            IntRegister0 := 0;
      [*] = ;            IntRegister1 := pGOUnit;
      [*] = ;            IntRegister2 := heroHandle;
      [*] = ;            IntRegister3 := 19;
      [*] = ;            ExecuteState('CheckUnitAbility');
      [*] = ;            var abilValue : Integer = IntRegister4;
      [*] = ;
      [*] = ;            if (curLife > 0) and (abilValue = 0) and (moralMod<power) then
      [*] = ;            begin
      [*] = ;               moralMod := power;
      [*] = ;               ParserSetIntValueByKeyByHandle(pGOUnit, 'MoralMod', moralMod);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if newQueryID = queryID then
      [*] = ;begin
      [*] = ;   //1 �������� Power+Random(Param1) ������.
      [*] = ;   //
      [*] = ;   //    ���� Param2=
      [*] = ;   //    1, �������� ���������� �� ��������� �����������,
      [*] = ;   //    2 - ����� ����� �� ����������� ��������� 1
      [*] = ;   //    3 - ����� ����� �� ����������� ��������� 2
      [*] = ;   //    4 - �������� � Power % �� ����������
      [*] = ;   //    5 - ����������� �������� ������ �� power � param1
      [*] = ;   //    6 - ������� ����� �� ����������� ��������� 1
      [*] = ;   //    7 - ������� ����� �� ����������� ��������� 2
      [*] = ;   //    (1 - ���������, 2 - ��������1, 3 - �������� 2, 4 - ����������)
      [*] = ;   var gold : Integer = CalcEffect(pEncounter, 1, difficulty, goDipl);
      [*] = ;   gIntRegister_TreasureGoldReward := gold;
      [*] = ;   plGold := plGold + gold;
      [*] = ;   SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold, plGold);
      [*] = ;
      [*] = ;   plGold := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGoldGain);
      [*] = ;   SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGoldGain, plGold + gold);
      [*] = ;
      [*] = ;   if (gold<>0) and bInterfacePlayer then
      [*] = ;      _gui_PlaySound('interface', 'money_spent');
      [*] = ;
      [*] = ;   //6 �������� Power+Random(Param1) ����������. ���� Param2=1, �������� ���������� �� ������� ���������
      [*] = ;   var gem : Integer = CalcEffect(pEncounter, 6, difficulty, goDipl);
      [*] = ;   gIntRegister_TreasureGemReward := gem;
      [*] = ;   plGem := plGem + gem;
      [*] = ;   SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem, plGem);
      [*] = ;
      [*] = ;   plGem := GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGemGain);
      [*] = ;   SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGemGain, plGem + gem);
      [*] = ;
      [*] = ;   // dialog params
      [*] = ;   var dlgParam1 : Integer = ParserGetIntValueByKeyByHandle(pEncounter, 'DlgParam1');
      [*] = ;   var dlgParam2 : Integer = ParserGetIntValueByKeyByHandle(pEncounter, 'DlgParam2');
      [*] = ;
      [*] = ;   case firstInd of
      [*] = ;      1 : mult := Round(Abs(gold));
      [*] = ;      2 : mult := Round(Abs(gIntRegister_EncounterParam1));
      [*] = ;      5 : mult := Round(Abs(gIntRegister_EncounterParam2));
      [*] = ;      6 : mult := Round(Abs(gem));
      [*] = ;   end;
      [*] = ;
      [*] = ;   case dlgParam1 of
      [*] = ;      2 : begin
      [*] = ;         if ((dlgParam2 <> 1) and (dlgParam2 <> 3)) then
      [*] = ;         begin
      [*] = ;            // HACK - could be collision between original and our Eador dialog system! If encounter text has two of these parameters it's incorrect
      [*] = ;            gIntRegister_GoldCost := mult;
      [*] = ;            gIntRegister_GemCost := mult;
      [*] = ;            gIntRegister_GoldReward := mult;
      [*] = ;            gIntRegister_GemReward := mult;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      4 : begin
      [*] = ;         var siteInd : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iSiteIndex);
      [*] = ;         //var pProvSite : Integer = ParserSelectByHandleByIndex(ParserSelectByHandleByKey(pProvince, 'Sites'), siteInd);
      [*] = ;         // TODO: get site quest data - spell name, used in encounter 7363
      [*] = ;      end;
      [*] = ;      5 : begin
      [*] = ;         var siteInd : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iSiteIndex);
      [*] = ;         //var pProvSite : Integer = ParserSelectByHandleByIndex(ParserSelectByHandleByKey(pProvince, 'Sites'), siteInd);
      [*] = ;         // TODO: get site quest data - unit name, units count, used in encounter 7444
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pEffects)-1 do
      [*] = ;   begin
      [*] = ;      var pEffect : Integer = ParserSelectByHandleByIndex(pEffects, i);
      [*] = ;      var index : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Index');
      [*] = ;      var power : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Power');
      [*] = ;      var param1 : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Param1');
      [*] = ;      var param2 : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'Param2');
      [*] = ;
      [*] = ;      case index of
      [*] = ;         //8 �������� ���������� ������� Power
      [*] = ;         8 : begin
      [*] = ;            newQueryID := IntToStr(power);
      [*] = ;         end;
      [*] = ;         //11 ������� ����������� Power (���� Param1>0 - ������� ����������� Param1, ���� Random(100)>Param2)
      [*] = ;         11 : begin
      [*] = ;            var queryID : Integer = 0;
      [*] = ;            if (param1 > 0) and (_rand_Random(100) > param2) then
      [*] = ;               queryID := param1
      [*] = ;            else
      [*] = ;               queryID := power;
      [*] = ;
      [*] = ;            newQueryID := IntToStr(queryID);
      [*] = ;
      [*] = ;            //if openHeroWindow and (queryID > 0) then // in case there's a query waiting after closing the hero window. Otherwise it will trigger on top of the hero window.
      [*] = ;            //   _gv_SetMapLock(1,_log_name+' [Index 11]');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;//ParserFreeByHandle(pChooseItems);
      [*] = ;
      [*] = ;if province_flags <> 0 then
      [*] = ;begin
      [*] = ;   var provHandle : Integer = GetGameObjectHandleByUniqueId(provUID);
      [*] = ;   if provHandle <> 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := province_flags;
      [*] = ;      StringRegister0 := _log_name;
      [*] = ;      GameObjectExecuteStateByHandle(provHandle, 'MergeUpdateFlags');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;gBoolRegister_GUIUpdateInterfacePanel := True;
      [*] = ;
      [*] = ;if (newQueryID = '') or (newQueryID = '0') then
      [*] = ;   newQueryID := queryID;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+newQueryID+']',$1000000 or _log_trace);
      [*] = ;StringRegister0 := newQueryID;
      [*] = ;BoolRegister0 := openHeroWindow;
   struct.end
section.end

