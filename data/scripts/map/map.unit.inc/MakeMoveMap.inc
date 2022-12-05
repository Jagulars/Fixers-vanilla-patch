section.begin
   Name = MakeMoveMap
   Description : struct.begin
      [*] = ;BoolRegister0 - pass all neutral provinces
      [*] = ;BoolRegister1 - calc hero speed
      [*] = ;BoolRegister2 - treat enemy provinces as neutral
   struct.end
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;var bPassAll : Boolean = BoolRegister0;
      [*] = ;var getSpeed : Boolean = BoolRegister1;
      [*] = ;var ignoreEnemy : Boolean = BoolRegister2;
      [*] = ;
      [*] = ;if _log then TimeLog('Start building move map');
      [*] = ;
      [*] = ;var pStratHexCells : Integer = gStratHexCells.handle;
      [*] = ;
      [*] = ;var task : Integer = GetIntValueByIndex(gc_map_GOStack_MapUnit_iTask);
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var myPlName : String = GetPlayerNameByHandle(myPlHandle);
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;
      [*] = ;var walkSpeed : Integer;
      [*] = ;if getSpeed then
      [*] = ;begin
      [*] = ;   IntRegister0 := gc_map_hero_iMobility;
      [*] = ;   ExecuteState('GetProperty');
      [*] = ;   walkSpeed := IntRegister1;
      [*] = ;end
      [*] = ;else
      [*] = ;   walkSpeed := 1;
      [*] = ;if _log then Log('walkSpeed: '+IntToStr(walkSpeed));
      [*] = ;
      [*] = ;
      [*] = ;procedure SetMoveMap(const pStratHexCell, turnsSpent, mobilCounter, pathInd : Integer); // how many turns to reach the province
      [*] = ;begin
      [*] = ;   if _log then Log('SetMoveMap: '+IntToStr(turnsSpent)+', mobil: '+IntToStr(mobilCounter)+', prevPathInd: '+IntToStr(pathInd));
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'MoveMap', turnsSpent);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'MobilMap', Max(0, mobilCounter));
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'PrevPathInd', pathInd);
      [*] = ;end;
      [*] = ;
      [*] = ;function GetArrivalMobility(const pFromHex, pDestHex : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := -1;
      [*] = ;   
      [*] = ;   var fromTerType : Integer = ParserGetIntValueByKeyByHandle(pFromHex, 'TerrainType');
      [*] = ;   var toTerType : Integer = ParserGetIntValueByKeyByHandle(pDestHex, 'TerrainType');
      [*] = ;   
      [*] = ;   if (fromTerType <> gc_WaterTerrainType) and (toTerType = gc_WaterTerrainType) then
      [*] = ;      Result := ParserGetIntValueByKeyByHandle(pFromHex, 'Port') // embark
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (fromTerType = gc_WaterTerrainType) and (toTerType <> gc_WaterTerrainType) then // disembark
      [*] = ;         Result := 0
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if ParserGetIntValueByKeyByHandle(pFromHex, 'MoveMap') = 0 then // starting from impassible hex, can only retreat one hex
      [*] = ;         begin
      [*] = ;            IntRegister0 := pFromHex;
      [*] = ;            PlayerExecuteStateByHandle(myPlHandle, 'CanPassProvince');
      [*] = ;            if not bPassAll then
      [*] = ;               BoolRegister0 := BoolRegister0 and (ParserGetIntValueByKeyByHandle(pFromHex, 'LastPlayer') = myPlIndex);
      [*] = ;
      [*] = ;            if not BoolRegister0 then
      [*] = ;               Result := 0;
      [*] = ;         end;
      [*] = ;         
      [*] = ;         if Result = -1 then
      [*] = ;         begin
      [*] = ;            var nIndex : Integer = ParserGetIntValueByKeyByHandle(pDestHex, 'Index');
      [*] = ;            var tnHandle : Integer = GetTrackNodeHandleByIndex(nIndex);
      [*] = ;            var moveCost : Integer = Round(GetTrackNodeDistFactorByHandle(tnHandle));
      [*] = ;               
      [*] = ;            var fromMobilMap : Integer = ParserGetIntValueByKeyByHandle(pFromHex, 'MobilMap');
      [*] = ;            if fromMobilMap <= 0 then
      [*] = ;               Result := walkSpeed + ParserGetIntValueByKeyByHandle(pFromHex, 'Stable') - moveCost
      [*] = ;            else
      [*] = ;               Result := fromMobilMap - moveCost;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetArrivalTurn(const pFromHex, pDestHex : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := ParserGetIntValueByKeyByHandle(pFromHex, 'MoveMap');
      [*] = ;   if ParserGetIntValueByKeyByHandle(pFromHex, 'MobilMap') <= 0 then
      [*] = ;      Result := Result + 1
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var destTerType : Integer = ParserGetIntValueByKeyByHandle(pDestHex, 'TerrainType');
      [*] = ;      if (destTerType = gc_WaterTerrainType) and (ParserGetIntValueByKeyByHandle(pFromHex, 'TerrainType') <> gc_WaterTerrainType) then // if need to embark, a full turn is required
      [*] = ;         Result := Result + 1;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function CheckRoute(const pFromHex, pDestHex : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := False;
      [*] = ;   
      [*] = ;   var dMoveMap : Integer = ParserGetIntValueByKeyByHandle(pDestHex, 'MoveMap');
      [*] = ;   //if _log then Log('CheckRoute: '+IntToStr(ParserGetIntValueByKeyByHandle(pDestHex, 'Index')));
      [*] = ;   //if _log then Log('dMoveMap: '+IntToStr(dMoveMap));
      [*] = ;   
      [*] = ;   if dMoveMap >= -1 then
      [*] = ;   begin
      [*] = ;      var nTerType : Integer = ParserGetIntValueByKeyByHandle(pDestHex, 'TerrainType');
      [*] = ;      //if _log then Log('nTerType: '+IntToStr(nTerType));
      [*] = ;
      [*] = ;      if (nTerType <> gc_MountainTerrainType) then
      [*] = ;      begin
      [*] = ;         var fromTerType : Integer = ParserGetIntValueByKeyByHandle(pFromHex, 'TerrainType');
      [*] = ;         var fromMoveMap : Integer = ParserGetIntValueByKeyByHandle(pFromHex, 'MoveMap');
      [*] = ;         var fromMobilMap : Integer = ParserGetIntValueByKeyByHandle(pFromHex, 'MobilMap');
      [*] = ;         var mobilCounter : Integer = GetArrivalMobility(pFromHex, pDestHex);
      [*] = ;         
      [*] = ;         //if _log then Log('fromTerType: '+IntToStr(fromTerType));
      [*] = ;         //if _log then Log('mobilCounter: '+IntToStr(mobilCounter));
      [*] = ;         
      [*] = ;         if (nTerType <> gc_WaterTerrainType) or (mobilCounter > 0) then
      [*] = ;         begin
      [*] = ;            var turnsRequired : Integer = GetArrivalTurn(pFromHex, pDestHex);
      [*] = ;            //if _log then Log('turnsRequired: '+IntToStr(turnsRequired));
      [*] = ;
      [*] = ;            if (dMoveMap >= 0) and (dMoveMap < turnsRequired) then // already reached with fewer turns
      [*] = ;               Result := False
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var nMobilMap : Integer = ParserGetIntValueByKeyByHandle(pDestHex, 'MobilMap');
      [*] = ;               //if _log then Log('nMobilMap: '+IntToStr(nMobilMap));
      [*] = ;               
      [*] = ;               if (dMoveMap = turnsRequired) and (nMobilMap >= mobilCounter) then // there is another route where more or same mobility is preserved
      [*] = ;                  Result := False
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  IntRegister0 := pFromHex;
      [*] = ;                  PlayerExecuteStateByHandle(myPlHandle, 'CanPassProvince');
      [*] = ;                  var canPass : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;                  if (not bPassAll) and canPass then
      [*] = ;                     canPass := canPass and ((fromMoveMap = 0) or (ParserGetIntValueByKeyByHandle(pFromHex, 'LastPlayer') = myPlIndex)); // can't pass through unpopulated province if someone else has been there last
      [*] = ;                  
      [*] = ;                  IntRegister0 := pDestHex;
      [*] = ;                  PlayerExecuteStateByHandle(myPlHandle, 'CanPassProvince');
      [*] = ;                  var nCanPass : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;                  if (not bPassAll) and nCanPass then
      [*] = ;                     nCanPass := nCanPass and ((dMoveMap = 0) or (ParserGetIntValueByKeyByHandle(pDestHex, 'LastPlayer') = myPlIndex)); // can't pass through unpopulated province if someone else has been there last
      [*] = ;
      [*] = ;                  //if _log then Log('canPass: '+BoolToStr(canPass));
      [*] = ;                  //if _log then Log('nCanPass: '+BoolToStr(nCanPass));
      [*] = ;                  if (not nCanPass) and (not canPass) and (fromTerType <> gc_WaterTerrainType) and (fromTerType <> gc_MountainTerrainType) then
      [*] = ;                     Result := False
      [*] = ;                  else
      [*] = ;                     Result := True;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   //if _log then Log(' ');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CalcHexMoveMap(const pStratHexCell, prevPathInd : Integer);
      [*] = ;begin
      [*] = ;   var hexIndex : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'Index');
      [*] = ;   //if _log then Log('CalcHexMoveMap: '+IntToStr(hexIndex));
      [*] = ;   var terType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;
      [*] = ;   IntRegister0 := pStratHexCell;
      [*] = ;   PlayerExecuteStateByHandle(myPlHandle, 'CanPassProvince');
      [*] = ;   var canPass : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;   if not bPassAll then
      [*] = ;      canPass := canPass and (ParserGetIntValueByKeyByHandle(pStratHexCell, 'LastPlayer') = myPlIndex);
      [*] = ;      
      [*] = ;   var pFromHex : Integer = ParserSelectByHandleByIndex(pStratHexCells, prevPathInd);
      [*] = ;   var turnsSpent : Integer = GetArrivalTurn(pFromHex, pStratHexCell);
      [*] = ;   var mobilCounter : Integer = GetArrivalMobility(pFromHex, pStratHexCell);
      [*] = ;
      [*] = ;   SetMoveMap(pStratHexCell, turnsSpent, mobilCounter, prevPathInd);
      [*] = ;
      [*] = ;   if (terType = gc_WaterTerrainType) or canPass then
      [*] = ;   begin
      [*] = ;      var i, pNeighbour, pDestHex, nIndex : Integer;
      [*] = ;      var pNeighbours : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Neighbours');
      [*] = ;      for i := ParserGetCountByHandle(pNeighbours)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         pNeighbour := ParserSelectByHandleByIndex(pNeighbours, i);
      [*] = ;         nIndex := ParserGetIntValueByKeyByHandle(pNeighbour, 'Index');
      [*] = ;            
      [*] = ;         if nIndex <> prevPathInd then
      [*] = ;         begin
      [*] = ;            pDestHex := ParserSelectByHandleByIndex(pStratHexCells, nIndex);
      [*] = ;         
      [*] = ;            if CheckRoute(pStratHexCell, pDestHex) then
      [*] = ;               CalcHexMoveMap(pDestHex, hexIndex);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   //if _log then Log(' ');
      [*] = ;end;
      [*] = ;
      [*] = ;function FindBestRouteToHexCell(const pStratHexCell : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := False;
      [*] = ;   
      [*] = ;   //if _log then Log('FindBestRouteToHexCell: '+IntToStr(ParserGetIntValueByKeyByHandle(pStratHexCell, 'Index')));
      [*] = ;   //if _log then Log(': ');
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'MoveMap', -1); // -1 is to signify that route has not yet been found but it is available for route calculation
      [*] = ;   
      [*] = ;   var terType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;   
      [*] = ;   var i, pNeighbour, pNeighHex, nIndex, nTerType, dMoveMap : Integer;
      [*] = ;   var nCanPass : Boolean;
      [*] = ;   
      [*] = ;   var pNeighbours : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Neighbours');
      [*] = ;   for i := ParserGetCountByHandle(pNeighbours)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      pNeighbour := ParserSelectByHandleByIndex(pNeighbours, i);
      [*] = ;      nIndex := ParserGetIntValueByKeyByHandle(pNeighbour, 'Index');
      [*] = ;      pNeighHex := ParserSelectByHandleByIndex(pStratHexCells, nIndex);
      [*] = ;      
      [*] = ;      nTerType := ParserGetIntValueByKeyByHandle(pNeighHex, 'TerrainType');
      [*] = ;      if nTerType <> gc_MountainTerrainType then
      [*] = ;      begin
      [*] = ;         dMoveMap := ParserGetIntValueByKeyByHandle(pNeighHex, 'MoveMap');
      [*] = ;         //if _log then Log('nIndex: '+IntToStr(nIndex));
      [*] = ;         //if _log then Log('dMoveMap: '+IntToStr(dMoveMap));
      [*] = ;      
      [*] = ;         if (dMoveMap >= 0) then // only check provinces with confirmed route
      [*] = ;         begin
      [*] = ;            if (nTerType = gc_WaterTerrainType) then
      [*] = ;               nCanPass := True
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               IntRegister0 := pNeighHex;
      [*] = ;               PlayerExecuteStateByHandle(myPlHandle, 'CanPassProvince');
      [*] = ;               nCanPass := BoolRegister0;
      [*] = ;
      [*] = ;               if not bPassAll then
      [*] = ;                  nCanPass := nCanPass and ((dMoveMap = 0) or (ParserGetIntValueByKeyByHandle(pNeighHex, 'LastPlayer') = myPlIndex));
      [*] = ;            end;
      [*] = ;
      [*] = ;            //if _log then Log('nCanPass: '+BoolToStr(nCanPass));
      [*] = ;            if nCanPass and CheckRoute(pNeighHex, pStratHexCell) then
      [*] = ;            begin
      [*] = ;               CalcHexMoveMap(pStratHexCell, nIndex); // calculate the route and possible followups
      [*] = ;               Result := True;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         //if _log then Log(' ');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   //if _log then Log(' ');
      [*] = ;end;
      [*] = ;         
      [*] = ;
      [*] = ;var curUID : Integer = GetIntValueByIndex(gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;IntRegister0 := curUID;
      [*] = ;MapExecuteState('GetProvinceParserByUID');
      [*] = ;var pCurProvince : Integer = IntRegister1;
      [*] = ;var curIndex : Integer = ParserGetIntValueByKeyByHandle(pCurProvince, 'Index');
      [*] = ;
      [*] = ;var provPlName : String = ParserGetValueByKeyByHandle(pCurProvince, 'Player');
      [*] = ;
      [*] = ;var isNeutral : Boolean = _misc_IsProvinceNeutral(pCurProvince);
      [*] = ;
      [*] = ;
      [*] = ;var provCount : Integer = ParserGetCountByHandle(pStratHexCells);
      [*] = ;
      [*] = ;var i, j, pStratHexCell, dummyHandle : Integer;
      [*] = ;
      [*] = ;for i := provCount-1 downto 0 do
      [*] = ;begin
      [*] = ;   pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   dummyHandle := GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pStratHexCell, 'DummyUID'));
      [*] = ;
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'MoveMap', -2);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'MobilMap', -1000);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'PrevPathInd', -1);
      [*] = ;
      [*] = ;   var stable : Integer = 0;
      [*] = ;   var port : Integer = 0;
      [*] = ;   if dummyHandle <> 0 then
      [*] = ;   begin
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle, 'GetStable');
      [*] = ;      if IntRegister0 > 0 then
      [*] = ;         stable := IntRegister0;
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle, 'GetPort');
      [*] = ;      port := IntRegister0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'Stable', stable);
      [*] = ;   ParserSetIntValueByKeyByHandle(pStratHexCell, 'Port', port);
      [*] = ;end;
      [*] = ;
      [*] = ;ExecuteState('IsInEnemyProvince');
      [*] = ;var enemyProv : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;if (enemyProv and (not ignoreEnemy)) or ((gTutorial.map) and (curIndex = 10)) then
      [*] = ;begin
      [*] = ;   // siege or neutral province with enemy hero, or tutorial map start province
      [*] = ;   var pNeighbours : Integer = ParserSelectByHandleByKey(pCurProvince, 'Neighbours');
      [*] = ;   for i := ParserGetCountByHandle(pNeighbours)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pNeighbour : Integer = ParserSelectByHandleByIndex(pNeighbours, i);
      [*] = ;      var ind : Integer = ParserGetIntValueByKeyByHandle(pNeighbour, 'Index');
      [*] = ;      var pDestHex : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;      var plName : String = ParserGetValueByKeyByHandle(pDestHex, 'Player');
      [*] = ;
      [*] = ;      var isNNeutral : Boolean = _misc_IsProvinceNeutral(pDestHex);
      [*] = ;      var lastPlayer : Integer = ParserGetIntValueByKeyByHandle(pDestHex, 'LastPlayer');
      [*] = ;
      [*] = ;      if isNNeutral or SameText(plName, myPlName) then
      [*] = ;      begin
      [*] = ;         SetMoveMap(pDestHex, 1, 0, curIndex);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   SetMoveMap(pCurProvince, 0, 0, -1);
      [*] = ;
      [*] = ;   var curX : Integer = ParserGetIntValueByKeyByHandle(pCurProvince, 'X');
      [*] = ;   var curY : Integer = ParserGetIntValueByKeyByHandle(pCurProvince, 'Y');
      [*] = ;   var ring, sector, rowIndex : Integer;
      [*] = ;   var mapSizeX : Integer = gGame.map.x;
      [*] = ;   var mapSizeY : Integer = gGame.map.y;
      [*] = ;
      [*] = ;   var bCheckNextRing : Boolean = True;
      [*] = ;
      [*] = ;   var x, y : Integer = -1;
      [*] = ;   for ring := 1 to Round(mapSizeX * 1.5) do
      [*] = ;   begin
      [*] = ;      if not bCheckNextRing then
      [*] = ;         break
      [*] = ;      else
      [*] = ;         bCheckNextRing := False;
      [*] = ;      
      [*] = ;      for sector := 0 to 5 do
      [*] = ;      for rowIndex := 0 to ring-1 do
      [*] = ;      begin
      [*] = ;         _map_GetHexOutward(curX, curY, sector, ring, rowIndex, x, y);
      [*] = ;         if (x >= 0) and (x < mapSizeX) and (y >= 0) and (y < mapSizeY) then
      [*] = ;         begin
      [*] = ;            pStratHexCell := _map_GetStratHex(x, y);
      [*] = ;            bCheckNextRing := FindBestRouteToHexCell(pStratHexCell) or bCheckNextRing;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;// logging
      [*] = ;if _log then
      [*] = ;begin
      [*] = ;   TimeLog('End building move map');
      [*] = ;   
      [*] = ;   var str : String = '';
      [*] = ;   for i := provCount-1 downto 0 do
      [*] = ;   begin
      [*] = ;      pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      var provIndex : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'Index');
      [*] = ;      var prevPathInd : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'PrevPathInd');
      [*] = ;      var moveMap : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'MoveMap');
      [*] = ;      var mobilMap : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'MobilMap');
      [*] = ;      Log('ProvIndex: '+IntToStr(provIndex)+', MoveMap: '+IntToStr(moveMap)+', PrevInd: '+IntToStr(prevPathInd)+', MobilMap: '+IntToStr(mobilMap));
      [*] = ;      str := str + IntToStr(provIndex)+IntToStr(Max(-1, moveMap))+',';
      [*] = ;   end;
      [*] = ;   Log(str);
      [*] = ;end;
      [*] = ;
      [*] = ;gIntRegister_MoveMapHeroHandle := myGOHandle;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

