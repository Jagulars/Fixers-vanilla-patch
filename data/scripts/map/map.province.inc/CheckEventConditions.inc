section.begin
   Name = CheckEventConditions
   Description : struct.begin
      [*] = ;IntRegister0 - event ID
      [*] = ;OUT: BoolRegister0 - can it occur in province
   struct.end
   Code : struct.begin
      [*] = ;var eventID : Integer = IntRegister0;
      [*] = ;
      [*] = ;var dummyHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var dummyUID : Integer = GetGameObjectUniqueIdByHandle(dummyHandle);
      [*] = ;var pProvince : Integer = GetIntValueByIndex(gc_map_GOStack_Province_iParserHandle);
      [*] = ;
      [*] = ;var plName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;var plHandle : Integer = GetPlayerHandleByName(plName);
      [*] = ;var pPlParser : Integer = ParserSelectPlayer(plHandle);
      [*] = ;var pTreasury : Integer = ParserSelectByHandleByKey(pPlParser, 'Treasury');
      [*] = ;
      [*] = ;var i, j, k : Integer;
      [*] = ;
      [*] = ;IntRegister0 := eventID;
      [*] = ;MapExecuteState('GetEventParserByID');
      [*] = ;var pEvent : Integer = IntRegister1;
      [*] = ;
      [*] = ;var cond : Boolean;
      [*] = ;
      [*] = ;var isHero : Boolean = false;
      [*] = ;for i := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;   if not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead) then
      [*] = ;   begin
      [*] = ;      var uid : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;
      [*] = ;      if uid = dummyUID then
      [*] = ;      begin
      [*] = ;         isHero := true;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var pProvDefender : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;var defenderID : Integer = ParserGetIntValueByKeyByHandle(pProvDefender, 'DefenderID');
      [*] = ;
      [*] = ;var pProvSites : Integer = ParserSelectByHandleByKey(pProvince, 'Sites');
      [*] = ;
      [*] = ;var makeEvent : Boolean = true;
      [*] = ;
      [*] = ;var pConditions : Integer = ParserSelectByHandleByKey(pEvent, 'ConditionList');
      [*] = ;
      [*] = ;IntRegister0 := ParserGetIntValueByKeyByHandle(pProvince, 'TerrainType');
      [*] = ;MapExecuteState('GetTerrainParserByID');
      [*] = ;if ParserGetBoolValueByKeyByHandle(IntRegister1,'NoEvents') then
      [*] = ;begin
      [*] = ;   cond := false;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pConditions)-1 do
      [*] = ;   begin
      [*] = ;      var pCondition : Integer = ParserSelectByHandleByIndex(pConditions, i);
      [*] = ;      var power : Integer = ParserGetIntValueByKeyByHandle(pCondition, 'Power');
      [*] = ;      var param1 : Integer = ParserGetIntValueByKeyByHandle(pCondition, 'Param1');
      [*] = ;
      [*] = ;      case power of
      [*] = ;         // 100 - force event in noevents province with terrain type param1
      [*] = ;         100 : begin
      [*] = ;            if ParserGetIntValueByKeyByHandle(pProvince, 'TerrainType') = param1 then
      [*] = ;               cond := true;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if cond then
      [*] = ;         break;
      [*] = ;   end;
      [*] = ;   if not cond then
      [*] = ;   begin
      [*] = ;      BoolRegister0 := false;
      [*] = ;      SwitchTo('Nothing');
      [*] = ;      exit;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;   cond := true;
      [*] = ;
      [*] = ;for i := 0 to ParserGetCountByHandle(pConditions)-1 do
      [*] = ;begin
      [*] = ;   var pCondition : Integer = ParserSelectByHandleByIndex(pConditions, i);
      [*] = ;   var power : Integer = ParserGetIntValueByKeyByHandle(pCondition, 'Power');
      [*] = ;   var param1 : Integer = ParserGetIntValueByKeyByHandle(pCondition, 'Param1');
      [*] = ;   var param2 : Integer = ParserGetIntValueByKeyByHandle(pCondition, 'Param2');
      [*] = ;
      [*] = ;   case power of
      [*] = ;      //1 - если уровень провинции >=Param1
      [*] = ;      1 :
      [*] = ;      begin
      [*] = ;         var ProvinceLevel : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceLevel');
      [*] = ;         cond := (ProvinceLevel >= param1);
      [*] = ;         //Log('Condition: 1 - если уровень провинции >= ' + IntToStr(Param1) + ' (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //2 - если территория=Param1
      [*] = ;      2 :
      [*] = ;      begin
      [*] = ;         var TerrainType : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'TerrainType');
      [*] = ;         cond := (TerrainType = param1);
      [*] = ;         //Log('Condition: 2 - если территория = ' + IntToStr(Param1) + ' (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //3 - если у игрока золота >=Param1
      [*] = ;      3 :
      [*] = ;      begin
      [*] = ;         var gold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;         cond := (gold >= Param1);
      [*] = ;         //Log('Condition: 3 - если у игрока золота >= ' + IntToStr(Param1) + ' (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //4 - если есть свободное место для скрытого сайта
      [*] = ;      4 :
      [*] = ;      begin
      [*] = ;         IntRegister0 := 1;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetNewSiteExplore');
      [*] = ;         cond := (IntRegister1 > 0);
      [*] = ;         //Log('Condition: 4 - если есть свободное место для скрытого сайта (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //5 - если настроение жителей <=Param1
      [*] = ;      5 :
      [*] = ;      begin
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetMood');
      [*] = ;         var mood : Integer = IntRegister0;
      [*] = ;
      [*] = ;         cond := (mood <= param1);
      [*] = ;         //Log('Condition: 5 - если настроение жителей <= ' + IntToStr(Param1) + ' (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //6 - если настроение жителей >=Param1
      [*] = ;      6 :
      [*] = ;      begin
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetMood');
      [*] = ;         var mood : Integer = IntRegister0;
      [*] = ;
      [*] = ;         cond := (mood >= param1);
      [*] = ;         //Log('Condition: 6 - если настроение жителей >= ' + IntToStr(Param1) + ' (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //7 - если уровень провинции <=Param1
      [*] = ;      7 :
      [*] = ;      begin
      [*] = ;         var ProvinceLevel : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceLevel');
      [*] = ;         cond := (ProvinceLevel <= param1);
      [*] = ;         //Log('Condition: 7 - если уровень провинции <= ' + IntToStr(Param1) + ' (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //8 - если в сокровищнице есть Param1 или больше свободных мест
      [*] = ;      8 :
      [*] = ;      begin
      [*] = ;         var count : Integer = 0;
      [*] = ;
      [*] = ;         for j := 0 to gc_TreasurySize-1 do
      [*] = ;         begin
      [*] = ;            var pTreasuryItem : Integer = ParserSelectByHandleByIndex(pTreasury, j);
      [*] = ;            var itemID : Integer = ParserGetIntValueByKeyByHandle(pTreasuryItem, 'ItemID');
      [*] = ;            if itemID = 0 then
      [*] = ;            count := count + 1;
      [*] = ;         end;
      [*] = ;
      [*] = ;         cond := (count >= param1);
      [*] = ;         //Log('Condition: 8 - если в сокровищнице есть ' + IntToStr(Param1) + ' или больше свободных мест (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //9 - если карма игрока <=Param1
      [*] = ;      9 :
      [*] = ;      begin
      [*] = ;         var karma : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iKarma);
      [*] = ;         cond := (karma <= Param1);
      [*] = ;         //Log('Condition: 9 - если карма игрока <= ' + IntToStr(Param1) + ' (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //10 - если карма игрока >=Param1
      [*] = ;      10 :
      [*] = ;      begin
      [*] = ;         var karma : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iKarma);
      [*] = ;         cond := (karma >= Param1);
      [*] = ;         //Log('Condition: 10 - если карма игрока >= ' + IntToStr(Param1) + ' (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //11 - только не в родовой провинции
      [*] = ;      11 :
      [*] = ;      begin
      [*] = ;         var castle : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;         cond := (not castle);
      [*] = ;         //Log('Condition: 11 - только не в родовой провинции (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //12 - только в прибрежной провинции
      [*] = ;      12 :
      [*] = ;      begin
      [*] = ;         var coast : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Coast');
      [*] = ;         cond := (coast > 0);
      [*] = ;         //Log('Condition: 12 - только в прибрежной провинции (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //13 - только в провинции, населённой расой Param1
      [*] = ;      13 :
      [*] = ;      begin
      [*] = ;         var provinceRace : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'ProvinceRace');
      [*] = ;         cond := (provinceRace = param1);
      [*] = ;         //Log('Condition: 13 - только в провинции, населённой расой  ' + IntToStr(Param1) + ' (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //14 - в провинции есть герой (или стражник, если Param1>0)
      [*] = ;      14 :
      [*] = ;      begin
      [*] = ;         cond := isHero;
      [*] = ;
      [*] = ;         if param1 > 0 then
      [*] = ;         cond := cond or (defenderID > 0);
      [*] = ;         //Log('Condition: 14 - в провинции есть герой (или стражник, если Param1>0) (Param1 = ' + IntToStr(param1) + ') (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //15 - только в родовой провинции
      [*] = ;      15 :
      [*] = ;      begin
      [*] = ;         var castle : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;         cond := (castle = true);
      [*] = ;         //Log('Condition: 15 - только в родовой провинции (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //16 - если в провинции нет ресурса
      [*] = ;      16 :
      [*] = ;      begin
      [*] = ;         var resID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Resource');
      [*] = ;         cond := (resID = 0);
      [*] = ;         //Log('Condition: 16 - если в провинции нет ресурса (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //17 - если в провинции есть место для сайта Param1 -1 открытого Param1 1 скрытого
      [*] = ;      17 :
      [*] = ;      begin
      [*] = ;         if ParserGetCountByHandle(pProvSites) >= gc_MaxProvinceSite then
      [*] = ;            cond := false
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            IntRegister0 := param1;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'GetNewSiteExplore');
      [*] = ;            cond := (IntRegister1 > 0);
      [*] = ;         end;
      [*] = ;         //Log('Condition: 17 - если в провинции есть место для сайта Param1 -1 открытого Param1 1 скрытого (Param1 = ' + IntToStr(param1) + ') (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //18 - если в провинции нет охранника (Param1=0) иначе если есть охранник Param1
      [*] = ;      18 :
      [*] = ;      begin
      [*] = ;         if ((param1 = 0) and (defenderID = 0)) or ((param1 <> 0) and (defenderID = param1)) then
      [*] = ;            cond := true
      [*] = ;         else
      [*] = ;            cond := false;
      [*] = ;         //Log('Condition: 18 - если в провинции нет охранника (Param1=0) иначе если есть охранник Param1 (Param1 = ' + IntToStr(param1) + ') (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //19 - если в провинции есть постройка Param1
      [*] = ;      19 :
      [*] = ;      begin
      [*] = ;         IntRegister0 := Param1;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'CheckOuterBuilding');
      [*] = ;         cond := BoolRegister0;
      [*] = ;         //Log('Condition: 19 - если в провинции есть постройка ' + IntToStr(Param1) + ' (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //20 - если в провинции есть место для постройки (родовая провинция этим условием запрещена)
      [*] = ;      20 :
      [*] = ;      begin
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetFreeOuterBuildSlot');
      [*] = ;         cond := (IntRegister0 >= 0);
      [*] = ;         //Log('Condition: 20 - если в провинции есть место для постройки (родовая провинция этим условием запрещена) (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //21 - если в провинции НЕТ постройки Param1
      [*] = ;      21 :
      [*] = ;      begin
      [*] = ;         IntRegister0 := Param1;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'CheckOuterBuilding');
      [*] = ;         cond := (not BoolRegister0);
      [*] = ;         //Log('Condition: 21 - если в провинции НЕТ постройки ' + IntToStr(Param1) + ' (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //22 - если коррупция >= Param1 %
      [*] = ;      22 :
      [*] = ;      begin
      [*] = ;         BoolRegister0 := false;
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'GetCorruption');
      [*] = ;         cond := (IntRegister0 >= param1);
      [*] = ;         //Log('Condition: 22 - если коррупция >= ' + IntToStr(Param1) + ' % (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //23 - если у игрока кристаллов >=Param1
      [*] = ;      23 :
      [*] = ;      begin
      [*] = ;         var gem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;         cond := (gem >= Param1);
      [*] = ;         //Log('Condition: 23 - если у игрока кристаллов >= ' + IntToStr(Param1) + ' (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //24 - если у игрока Есть доступ к ресурсу Param1
      [*] = ;      24 :
      [*] = ;      begin
      [*] = ;         IntRegister0 := Param1;
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'GetResCount');
      [*] = ;         var resCount : Integer = IntRegister1;
      [*] = ;
      [*] = ;         cond := (resCount > 0);
      [*] = ;         //Log('Condition: 24 - если у игрока есть доступ к ресурсу ' + IntToStr(Param1) + ' (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //25 - если у игрока Нет доступа к ресурсу Param1
      [*] = ;      25 :
      [*] = ;      begin
      [*] = ;         IntRegister0 := Param1;
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'GetResCount');
      [*] = ;         var resCount : Integer = IntRegister1;
      [*] = ;
      [*] = ;         cond := (resCount = 0);
      [*] = ;         //Log('Condition: 25 - если у игрока нет доступа к ресурсу ' + IntToStr(Param1) + ' (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //26 - !только в режиме кампании! если значение флага Param1 из кампании истинно и текущий ход больше либо равен Param2 (если possibility=0 - обязательное событие в родовой провинции)
      [*] = ;      26 :
      [*] = ;      begin
      [*] = ;         //TODO gec заглушки на false
      [*] = ;         cond := false;
      [*] = ;      end;
      [*] = ;      //27 - если в провинции НЕТ героя
      [*] = ;      27 :
      [*] = ;      begin
      [*] = ;         cond := (not isHero);
      [*] = ;         //Log('Condition: 27 - если в провинции НЕТ героя (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //28 - если в провинции нет сайта Param1
      [*] = ;      28 :
      [*] = ;      begin
      [*] = ;         cond := true;
      [*] = ;
      [*] = ;         for j := ParserGetCountByHandle(pProvSites)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, j);
      [*] = ;            var siteID : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'SiteID');
      [*] = ;
      [*] = ;            if siteID = Param1 then
      [*] = ;            begin
      [*] = ;               cond := false;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         //Log('Condition: 28 - если в провинции нет сайта ' + IntToStr(Param1) + ' (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;      //29 - если в сокровищнице есть предмет Param1
      [*] = ;      29 :
      [*] = ;      begin
      [*] = ;         cond := false;
      [*] = ;
      [*] = ;         for j := 0 to gc_TreasurySize-1 do
      [*] = ;         begin
      [*] = ;            var pTreasuryItem : Integer = ParserSelectByHandleByIndex(pTreasury, j);
      [*] = ;            var itemID : Integer = ParserGetIntValueByKeyByHandle(pTreasuryItem, 'ItemID');
      [*] = ;            if itemID = param1 then
      [*] = ;            begin
      [*] = ;               cond := true;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         //Log('Condition: 29 - если в сокровищнице есть предмет ' + IntToStr(Param1) + ' (' + BoolToStr(cond) + ')');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if not cond then
      [*] = ;   begin
      [*] = ;      makeEvent := false;
      [*] = ;      break;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;BoolRegister0 := makeEvent;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
