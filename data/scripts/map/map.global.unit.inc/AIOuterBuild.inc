section.begin
   Name = AIOuterBuild
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\AIOUTERBUILD';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var myPlName : String = GetCurrentPlayerName;
      [*] = ;
      [*] = ;var pMyPlParser : Integer = ParserSelectPlayer(myPlHandle);
      [*] = ;
      [*] = ;var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;
      [*] = ;ExecuteState('GetCastleParser');
      [*] = ;var pCastle : Integer = IntRegister0;
      [*] = ;var cUID : Integer = ParserGetIntValueByKeyByHandle(pCastle, 'DummyUID');
      [*] = ;var cDummyHandle : Integer = GetGameObjectHandleByUniqueId(cUID);
      [*] = ;
      [*] = ;var pOuterBuildings : Integer = gPrototypeData.outerBuildings.handle;
      [*] = ;
      [*] = ;var i, j, k, l : Integer;
      [*] = ;
      [*] = ;procedure DestroyCheapOuterBuilding(pProvince : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var pProvOuterBuildings : Integer = ParserSelectByHandleByKey(pProvince, 'OuterBuildings');
      [*] = ;
      [*] = ;   var price : Integer = 10000;
      [*] = ;   var killID : Integer = -1;
      [*] = ;
      [*] = ;   for i := 0 to 2 do
      [*] = ;   begin
      [*] = ;      var pProvOuterBuilding : Integer = ParserSelectByHandleByIndex(pProvOuterBuildings, i);
      [*] = ;      var buildID : Integer = ParserGetIntValueByKeyByHandle(pProvOuterBuilding, 'OuterBuildID');
      [*] = ;
      [*] = ;      IntRegister0 := buildID;
      [*] = ;      MapExecuteState('GetOuterBuildParserByID');
      [*] = ;      var pOuterBuilding : Integer = IntRegister1;
      [*] = ;
      [*] = ;      var goldPrice : Integer = ParserGetIntValueByKeyByHandle(pOuterBuilding, 'GoldPrice');
      [*] = ;      var gemPrice : Integer = ParserGetIntValueByKeyByHandle(pOuterBuilding, 'GemPrice');
      [*] = ;
      [*] = ;      if goldPrice + 3 * gemPrice < price then
      [*] = ;      begin
      [*] = ;         price := goldPrice + 3 * gemPrice;
      [*] = ;         killID := buildID;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   IntRegister0 := pProvince;
      [*] = ;   IntRegister1 := killID;
      [*] = ;   ExecuteState('DestroyOuterBuild');
      [*] = ;end;
      [*] = ;
      [*] = ;// build shipyard for hero on island
      [*] = ;for i := GetPlayerGameObjectsCountByHandle(myPlHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;   var isDead : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;   var curUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;   var dummyHandle : Integer = GetGameObjectHandleByUniqueId(curUID);
      [*] = ;
      [*] = ;   IntRegister0 := curUID;
      [*] = ;   MapExecuteState('GetProvinceParserByUID');
      [*] = ;   var pProvince : Integer = IntRegister1;
      [*] = ;
      [*] = ;   var coast : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Coast');
      [*] = ;   var isCastle : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;   var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;   var provPlHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'GetPort');
      [*] = ;   var port : Integer = IntRegister0;
      [*] = ;
      [*] = ;   if (not isDead) and (coast > 0) and (port = 0) and (not isCastle) and (provPlHandle = myPlHandle) then
      [*] = ;   begin
      [*] = ;      var island : Boolean = true;
      [*] = ;      for j := 0 to 5 do
      [*] = ;      begin
      [*] = ;         IntRegister0 := pProvince;
      [*] = ;         IntRegister1 := j;
      [*] = ;         MapExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;         var pNProvince : Integer = IntRegister2;
      [*] = ;
      [*] = ;         var nProvPlName : String = ParserGetValueByKeyByHandle(pNProvince, 'Player');
      [*] = ;         var nProvPlHandle : Integer = GetPlayerHandleByName(nProvPlName);
      [*] = ;
      [*] = ;         if nProvPlHandle = myPlHandle then
      [*] = ;         begin
      [*] = ;            island := false;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if island then
      [*] = ;      begin
      [*] = ;         IntRegister0 := 52;
      [*] = ;         GameObjectExecuteStateByHandle(cDummyHandle, 'CheckInnerBuilding');
      [*] = ;         var isBuilt : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;         // build shipbuilder's guild
      [*] = ;         if not isBuilt then
      [*] = ;         begin
      [*] = ;            var pProvInnerBuildings : Integer = ParserSelectByHandleByKey(pCastle, 'InnerBuildings');
      [*] = ;            var pProvInnerBuilding : Integer = ParserAddChildByIndex(pProvInnerBuildings, '*');
      [*] = ;            ParserSetIntValueByKeyByHandle(pProvInnerBuilding, 'BuildingID', 52);
      [*] = ;            ParserSetIntValueByKeyByHandle(pProvInnerBuilding, 'Group', 0);
      [*] = ;         end;
      [*] = ;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetFreeOuterBuildSlot');
      [*] = ;         var slotInd : Integer = IntRegister0;
      [*] = ;
      [*] = ;         // destroy most cheap outer building
      [*] = ;         if slotInd < 0 then
      [*] = ;         DestroyCheapOuterBuilding(pProvince);
      [*] = ;
      [*] = ;         // build shipyard
      [*] = ;         IntRegister0 := pProvince;
      [*] = ;         IntRegister1 := 10;
      [*] = ;         ExecuteState('BuyOuterBuild');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var island : Boolean = true;
      [*] = ;var freeProv : Integer = -1;
      [*] = ;var occProv : Integer = -1;
      [*] = ;
      [*] = ;// build shipyard for islands
      [*] = ;for i := ParserGetCountByHandle(pProvinces)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, i);
      [*] = ;   var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;   var provPlHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;
      [*] = ;   var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;   var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHandle, 'GetPort');
      [*] = ;   var port : Integer = IntRegister0;
      [*] = ;
      [*] = ;   if (provPlHandle = myPlHandle) and (port = 0) then
      [*] = ;   begin
      [*] = ;      for [MAIN]j := 0 to 5 do
      [*] = ;      begin
      [*] = ;         IntRegister0 := pProvince;
      [*] = ;         IntRegister1 := j;
      [*] = ;         MapExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;         var pNProvince : Integer = IntRegister2;
      [*] = ;
      [*] = ;         var terType : Integer = ParserGetIntValueByKeyByHandle(pNProvince, 'TerrainType');
      [*] = ;         var nProvPlName : String = ParserGetValueByKeyByHandle(pNProvince, 'Player');
      [*] = ;         var nProvPlHandle : Integer = GetPlayerHandleByName(nProvPlName);
      [*] = ;
      [*] = ;         if (pNProvince <> 0) and (terType <> gc_WaterTerrainType) and (terType <> gc_MountainTerrainType) and (nProvPlHandle <> myPlHandle) then
      [*] = ;         island := false;
      [*] = ;
      [*] = ;         if (pNProvince <> 0) and (terType = gc_WaterTerrainType) and (freeProv = -1) then
      [*] = ;         begin
      [*] = ;            for k := 0 to 5 do
      [*] = ;            begin
      [*] = ;               IntRegister0 := pNProvince;
      [*] = ;               IntRegister1 := k;
      [*] = ;               MapExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;               var pNNProvince : Integer = IntRegister2;
      [*] = ;
      [*] = ;               if pNNProvince <> 0 then
      [*] = ;               begin
      [*] = ;                  var nnProvPlName : String = ParserGetValueByKeyByHandle(pNNProvince, 'Player');
      [*] = ;                  var nnProvPlHandle : Integer = GetPlayerHandleByName(nnProvPlName);
      [*] = ;                  var nnPlIndex : Integer = GetPlayerIndexByHandle(nnProvPlHandle);
      [*] = ;
      [*] = ;                  var canKill : Integer = 0;
      [*] = ;                  if nnPlIndex >= 0 then
      [*] = ;                  canKill := gArrDiplomacy[myPlIndex][nnPlIndex].canKill;
      [*] = ;
      [*] = ;                  if (nnProvPlHandle <> 0) and (nnProvPlHandle <> myPlHandle) and (canKill < 0) then
      [*] = ;                  begin
      [*] = ;                     occProv := i;
      [*] = ;                     break(MAIN);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if occProv = i then
      [*] = ;      begin
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetFreeOuterBuildSlot');
      [*] = ;         var slotInd : Integer = IntRegister0;
      [*] = ;
      [*] = ;         if slotInd >= 0 then
      [*] = ;         begin
      [*] = ;            freeProv := occProv;
      [*] = ;            occProv := -1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if island then
      [*] = ;begin
      [*] = ;   IntRegister0 := 52;
      [*] = ;   GameObjectExecuteStateByHandle(cDummyHandle, 'CheckInnerBuilding');
      [*] = ;   var isBuilt : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;   // build shipbuilder's guild
      [*] = ;   if not isBuilt then
      [*] = ;   begin
      [*] = ;      var pProvInnerBuildings : Integer = ParserSelectByHandleByKey(pCastle, 'InnerBuildings');
      [*] = ;      var pProvInnerBuilding : Integer = ParserAddChildByIndex(pProvInnerBuildings, '*');
      [*] = ;      ParserSetIntValueByKeyByHandle(pProvInnerBuilding, 'BuildingID', 52);
      [*] = ;      ParserSetIntValueByKeyByHandle(pProvInnerBuilding, 'Group', 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var water : Integer = 0;
      [*] = ;   var maxWater : Integer = 0;
      [*] = ;   var pick : Integer = -1;
      [*] = ;   var build : Integer;
      [*] = ;   var buildPick : Integer;
      [*] = ;
      [*] = ;   if occProv > 0 then
      [*] = ;   begin
      [*] = ;      buildPick := 2;
      [*] = ;      pick := occProv;
      [*] = ;      occProv := 0;
      [*] = ;   end;
      [*] = ;   if freeProv > 0 then
      [*] = ;   begin
      [*] = ;      buildPick := 3;
      [*] = ;      pick := freeProv;
      [*] = ;      freeProv := 0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if pick < 0 then
      [*] = ;   begin
      [*] = ;      for i := ParserGetCountByHandle(pProvinces)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, i);
      [*] = ;
      [*] = ;         var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;         var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;         var coast : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Coast');
      [*] = ;         var isCastle : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;         var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;         var provPlHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'GetPort');
      [*] = ;         var port : Integer = IntRegister0;
      [*] = ;
      [*] = ;         if (provPlHandle = myPlHandle) and (coast > 0) and (port = 0) and (not isCastle) then
      [*] = ;         begin
      [*] = ;            water := 0;
      [*] = ;
      [*] = ;            for [MAIN]j := 0 to 5 do
      [*] = ;            begin
      [*] = ;               IntRegister0 := pProvince;
      [*] = ;               IntRegister1 := j;
      [*] = ;               MapExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;               var pNProvince : Integer = IntRegister2;
      [*] = ;
      [*] = ;               var terType : Integer = ParserGetIntValueByKeyByHandle(pNProvince, 'TerrainType');
      [*] = ;
      [*] = ;               if (pNProvince <> 0) and (terType = gc_WaterTerrainType) then
      [*] = ;               water := water + 1;
      [*] = ;            end;
      [*] = ;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'GetFreeOuterBuildSlot');
      [*] = ;            var slotInd : Integer = IntRegister0;
      [*] = ;
      [*] = ;            if (pick < 0) or (water > maxWater) or ((water = maxWater) and (slotInd < buildPick)) then
      [*] = ;            begin
      [*] = ;               buildPick := i;
      [*] = ;               maxWater := water;
      [*] = ;               buildPick := slotInd;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if pick >= 0 then
      [*] = ;   begin
      [*] = ;      if buildPick = 3 then
      [*] = ;      buildPick := -1;
      [*] = ;
      [*] = ;      var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, pick);
      [*] = ;
      [*] = ;      if buildPick = -1 then
      [*] = ;      DestroyCheapOuterBuilding(pProvince);
      [*] = ;
      [*] = ;      // build shipyard
      [*] = ;      IntRegister0 := pProvince;
      [*] = ;      IntRegister1 := 10;
      [*] = ;      ExecuteState('BuyOuterBuild');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// build shipyard if coast neighbour founded
      [*] = ;var plCanOuterBuild : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iCanOuterBuild);
      [*] = ;
      [*] = ;IntRegister0 := 52;
      [*] = ;GameObjectExecuteStateByHandle(cDummyHandle, 'CheckInnerBuilding');
      [*] = ;var isBuilt : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;if isBuilt and (plCanOuterBuild > 0) then
      [*] = ;begin
      [*] = ;   if freeProv >= 0 then
      [*] = ;   begin
      [*] = ;      var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, freeProv);
      [*] = ;
      [*] = ;      IntRegister0 := pProvince;
      [*] = ;      IntRegister1 := 10;
      [*] = ;      ExecuteState('BuyOuterBuild');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if occProv >= 0 then
      [*] = ;      begin
      [*] = ;         var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, freeProv);
      [*] = ;         DestroyCheapOuterBuilding(pProvince);
      [*] = ;
      [*] = ;         IntRegister0 := pProvince;
      [*] = ;         IntRegister1 := 10;
      [*] = ;         ExecuteState('BuyOuterBuild');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// choose building from whole build list
      [*] = ;plCanOuterBuild := GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iCanOuterBuild);
      [*] = ;
      [*] = ;for k := 0 to plCanOuterBuild-1 do
      [*] = ;begin
      [*] = ;   var trgBuildID : Integer = -1;
      [*] = ;   var pTrgProvince : Integer = 0;
      [*] = ;   var taste : Integer = 0;
      [*] = ;
      [*] = ;   var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;   var plGem : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;   var plGoldLimit : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldLimit);
      [*] = ;   var plGemLimit : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGemLimit);
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pProvinces)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pProvince : Integer = ParserSelectByHandleByIndex(pProvinces, i);
      [*] = ;      var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;      var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;      var isCastle : Boolean = ParserGetBoolValueByKeyByHandle(pProvince, 'Castle');
      [*] = ;      var provPlName : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;      var provPlHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;
      [*] = ;      if (provPlHandle = myPlHandle) and (not isCastle) then
      [*] = ;      begin
      [*] = ;         for j := ParserGetCountByHandle(pOuterBuildings)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pOuterBuilding : Integer = ParserSelectByHandleByIndex(pOuterBuildings, j);
      [*] = ;            var buildID : Integer = ParserGetIntValueByKeyByHandle(pOuterBuilding, 'BuildingID');
      [*] = ;
      [*] = ;            IntRegister0 := buildID;
      [*] = ;            GameObjectExecuteStateByHandle(dummyHandle, 'IsBuildingAvailable');
      [*] = ;            var isAvailable : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;            IntRegister0 := buildID;
      [*] = ;            ExecuteState('GetOuterBuildPrice');
      [*] = ;            var goldCost : Integer = IntRegister1;
      [*] = ;            var gemCost : Integer = IntRegister2;
      [*] = ;
      [*] = ;            if isAvailable and ((plGold>=plGoldLimit+goldCost) or (goldCost=0)) and ((gemCost=0) or (plGem>=plGemLimit+gemCost)) then
      [*] = ;            begin
      [*] = ;               var goldAdd : Integer = ParserGetIntValueByKeyByHandle(pOuterBuilding, 'GoldAdd');
      [*] = ;               var gemAdd : Integer = ParserGetIntValueByKeyByHandle(pOuterBuilding, 'GemAdd');
      [*] = ;               var port : Integer = ParserGetIntValueByKeyByHandle(pOuterBuilding, 'Port');
      [*] = ;               var mood : Integer = ParserGetIntValueByKeyByHandle(pOuterBuilding, 'Mood');
      [*] = ;
      [*] = ;               var randValue : Integer = 7 - (goldCost + gemCost * 2) div 100;
      [*] = ;               if randValue < 2 then
      [*] = ;               randValue := 2;
      [*] = ;
      [*] = ;               var newTaste : Integer = goldAdd + 5 * gemAdd + 3 * port + 3 * mood + _rand_Random(randValue);
      [*] = ;
      [*] = ;               if newTaste > taste then
      [*] = ;               begin
      [*] = ;                  taste := newTaste;
      [*] = ;                  trgBuildID := j;
      [*] = ;                  pTrgProvince := pProvince;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if trgBuildID > 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := pTrgProvince;
      [*] = ;      IntRegister1 := trgBuildID;
      [*] = ;      ExecuteState('BuyOuterBuild');
      [*] = ;
      [*] = ;      var buildName : String = GetLocaleTableListItemByID('outer_build', IntToStr(trgBuildID));
      [*] = ;
      [*] = ;      _gui_ProgressCalculations(_log_name+' Player ' + myPlName + ' builds outer build ' + buildName + '(' + IntToStr(trgBuildID) + ') with taste = ' + IntToStr(taste));
      [*] = ;   end
      [*] = ;   else
      [*] = ;   break;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

