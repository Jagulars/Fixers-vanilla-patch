section.begin
   Name = ShardWater
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\SHARDWATER';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;const cPatternPlName   = 'pattern';
      [*] = ;const cPatternPlRace   = 'nature';
      [*] = ;const cPatternPlCMode   = 'cmPC';
      [*] = ;
      [*] = ;const cWaterOffset  = 0.15;
      [*] = ;const cSmoothRadius = 5;
      [*] = ;const cSmoothPasses = 10;
      [*] = ;const cSmoothOffset = 3;
      [*] = ;
      [*] = ;var i, j, k, l : Integer;
      [*] = ;
      [*] = ;var curVisualID : Integer = 0;
      [*] = ;if (_worldrule_GetWorldRuleVisualExistByID(3)) then
      [*] = ;   curVisualID := _worldrule_GetWorldRuleVisualParams(3, 1);
      [*] = ;
      [*] = ;var patPlHandle : Integer = _plr_GetOrCreatePlayer(cPatternPlName, cPatternPlRace, cPatternPlCMode, False);
      [*] = ;
      [*] = ;var pStratHexCells : Integer = gStratHexCells.handle;
      [*] = ;var HexCount : Integer = ParserGetCountByHandle(pStratHexCells);
      [*] = ;var GridSize : Integer = _map_GetGridSize();
      [*] = ;
      [*] = ;procedure ClearChecks();
      [*] = ;begin
      [*] = ;   var i, pStratHexCell, terrainType : Integer;
      [*] = ;   for i := 0 to HexCount-1 do
      [*] = ;   begin
      [*] = ;      pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      terrainType := ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;      if terrainType = gc_WaterTerrainType then
      [*] = ;         ParserSetBoolValueByKeyByHandle(pStratHexCell, 'Checked', false);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;var pStratHexCell, pNeighbour, terrainType, checkPoints, pointX, pointY, pVertices, vertInd1, vertInd2, pVertex1, pVertex2 : Integer;
      [*] = ;var x, y, z, x1, y1, x2, y2, centerX, centerY, nX, nY, centerHeight, destHeight, dist, radius, height, lerpFactor : Float;
      [*] = ;
      [*] = ;
      [*] = ;var waterPatternName : String = 'map-water-test-13';
      [*] = ;if (curVisualID=5) then
      [*] = ;   waterPatternName := 'map-water-vulcan-1'
      [*] = ;else
      [*] = ;if (curVisualID=6) then
      [*] = ;   waterPatternName := 'map-water-ice-1';
      [*] = ;
      [*] = ;for i := 0 to HexCount-1 do
      [*] = ;begin
      [*] = ;   pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   terrainType := ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;   if terrainType = gc_WaterTerrainType then
      [*] = ;   begin
      [*] = ;      x := ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterX');
      [*] = ;      z := ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterY');
      [*] = ;
      [*] = ;      StandPattern(patPlHandle, waterPatternName, x, z, 0);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;// carve waterways according to borders
      [*] = ;//const cCanalCheckInterval = 0.5;
      [*] = ;ClearChecks();
      [*] = ;for i := 0 to HexCount-1 do
      [*] = ;begin
      [*] = ;   pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   terrainType := ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;   if terrainType = gc_WaterTerrainType then
      [*] = ;   begin
      [*] = ;      pVertices := ParserSelectByHandleByKey(pStratHexCell, 'Vertices');
      [*] = ;      centerX := ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterX');
      [*] = ;      centerY := ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterY');
      [*] = ;      centerHeight := GetHeightData(Round(centerX), Round(centerY));
      [*] = ;      
      [*] = ;      for vertInd1 := 0 to 5 do
      [*] = ;      begin
      [*] = ;         pVertex1 := ParserSelectByHandleByIndex(pVertices, vertInd1);
      [*] = ;         x1 := ParserGetFloatValueByKeyByHandle(pVertex1, 'X');
      [*] = ;         y1 := ParserGetFloatValueByKeyByHandle(pVertex1, 'Y');
      [*] = ;         
      [*] = ;         // carve corners
      [*] = ;         radius := VectorDistance(x1, 0, y1, centerX, 0, centerY) * 0.5;
      [*] = ;         pointX := Round(Lerp(centerX, x1, 0.5));
      [*] = ;         pointY := Round(Lerp(centerY, y1, 0.5));
      [*] = ;         
      [*] = ;         _map_SetSmoothHeightAroundPoint(pointX, pointY, centerHeight, radius, radius / 2, False);
      [*] = ;         
      [*] = ;         
      [*] = ;          // between water hexes
      [*] = ;         vertInd2 := (vertInd1+1) mod 6;
      [*] = ;         pNeighbour := _map_GetNeighbourByVertices(pStratHexCell, vertInd1, vertInd2);
      [*] = ;         
      [*] = ;         if (pNeighbour <> 0) and (ParserGetIntValueByKeyByHandle(pNeighbour, 'TerrainType') = gc_WaterTerrainType) and (not ParserGetBoolValueByKeyByHandle(pNeighbour, 'Checked')) then
      [*] = ;         begin
      [*] = ;            pVertex2 := ParserSelectByHandleByIndex(pVertices, vertInd2);
      [*] = ;            
      [*] = ;            //nX := ParserGetFloatValueByKeyByHandle(pNeighbour, 'CenterX');
      [*] = ;            //nY := ParserGetFloatValueByKeyByHandle(pNeighbour, 'CenterY');
      [*] = ;            //destHeight := GetHeightData(Round(nX), Round(nY));
      [*] = ;               
      [*] = ;            //height := Lerp(centerHeight, destHeight, 0.5);
      [*] = ;            x2 := ParserGetFloatValueByKeyByHandle(pVertex2, 'X');
      [*] = ;            y2 := ParserGetFloatValueByKeyByHandle(pVertex2, 'Y');
      [*] = ;            pointX := Round(Lerp(x1, x2, 0.5));
      [*] = ;            pointY := Round(Lerp(y1, y2, 0.5));
      [*] = ;            dist := VectorDistance(x1, 0, y1, x2, 0, y2) / 2;
      [*] = ;            //height := Abs(centerHeight - GetHeightData(pointX, pointY));
      [*] = ;               
      [*] = ;            _map_SetSmoothHeightAroundPoint(pointX, pointY, centerHeight, dist, dist / 2, False);
      [*] = ;            //LowerTerrain(pointX, pointY, True, Round(dist), height * 3);
      [*] = ;               
      [*] = ;            //dist := VectorDistance(centerX, 0, centerY, nX, 0, nY);
      [*] = ;            //checkPoints := Round(dist / cCanalCheckInterval);
      [*] = ;            //for k := 1 to checkPoints-1 do
      [*] = ;            //begin
      [*] = ;            //   lerpFactor := k / checkPoints;
      [*] = ;            //   height := Lerp(centerHeight, destHeight, lerpFactor);
      [*] = ;            //   pointX := Round(Lerp(centerX, nX, lerpFactor));
      [*] = ;            //   pointY := Round(Lerp(centerY, nY, lerpFactor));
      [*] = ;            //   SetHeightData(pointX, pointY, height);
      [*] = ;            //end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      ParserSetBoolValueByKeyByHandle(pStratHexCell, 'Checked', True); 
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;// setting water height
      [*] = ;ClearChecks();
      [*] = ;for i := 0 to HexCount-1 do
      [*] = ;begin
      [*] = ;   var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   var TerrainType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;   if TerrainType = gc_WaterTerrainType then
      [*] = ;   begin
      [*] = ;      if not ParserGetBoolValueByKeyByHandle(pStratHexCell, 'Checked') then
      [*] = ;      begin
      [*] = ;         ArrayClear();
      [*] = ;         ArrayPushValue(i);
      [*] = ;         var minHeight : Float = 10000;
      [*] = ;         var ind : Integer = i;
      [*] = ;         var finished : Boolean = false;
      [*] = ;
      [*] = ;         while not finished do
      [*] = ;         begin
      [*] = ;            var curX, curY, curZ : Float;
      [*] = ;            var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;            GetTrackNodePositionByIndex(ind, curX, curY, curZ);
      [*] = ;
      [*] = ;            var height : Float = GetHeightData(Round(curX), Round(curZ));
      [*] = ;            if height < minHeight then
      [*] = ;            begin
      [*] = ;               minHeight := height;
      [*] = ;               //Log('(' + FloatToStr(curX) + ', ' + FloatToStr(curZ) + ') height = ' + FloatToStr(height));
      [*] = ;            end;
      [*] = ;
      [*] = ;            for j := -1 to 1 do
      [*] = ;            begin
      [*] = ;               for k := -1 to 1 do
      [*] = ;               if (j <> 0) or (k <> 0) then
      [*] = ;               begin
      [*] = ;                  var indNext : Integer = ind + j * GridSize + k;
      [*] = ;                  if (indNext >= 0) and (indNext < HexCount) then
      [*] = ;                  begin
      [*] = ;                     var nextX, nextY, nextZ : Float;
      [*] = ;                     GetTrackNodePositionByIndex(indNext, nextX, nextY, nextZ);
      [*] = ;                     var pNextHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, indNext);
      [*] = ;
      [*] = ;                     var dist : Float = VectorDistance(curX, 0, curZ, nextX, 0, nextZ);
      [*] = ;                     var aDist : Float = Sqrt(3) * gc_StratHexSize;
      [*] = ;                     TerrainType := ParserGetIntValueByKeyByHandle(pNextHexCell, 'TerrainType');
      [*] = ;
      [*] = ;                     if (TerrainType = gc_WaterTerrainType) and (ParserGetBoolValueByKeyByHandle(pNextHexCell, 'Checked') = false) and
      [*] = ;                     (dist < aDist + 0.1) then
      [*] = ;                     ArrayPushValue(indNext);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            ParserSetBoolValueByKeyByHandle(pStratHexCell, 'Checked', true);
      [*] = ;
      [*] = ;            finished := true;
      [*] = ;            ind := -1;
      [*] = ;            for j := ArrayGetCount()-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var tmpInd : Integer = ArrayGetValueByIndex(j);
      [*] = ;               var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, tmpInd);
      [*] = ;               if not ParserGetBoolValueByKeyByHandle(pStratHexCell, 'Checked') then
      [*] = ;               begin
      [*] = ;                  ind := tmpInd;
      [*] = ;                  finished := false;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         // setting heights in spot
      [*] = ;         for l := ArrayGetCount-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var ind : Integer = ArrayGetValueByIndex(l);
      [*] = ;            var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;            ParserSetFloatValueByKeyByHandle(pStratHexCell, 'WaterHeight', minHeight + cWaterOffset);
      [*] = ;            
      [*] = ;            //x := ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterX');
      [*] = ;            //z := ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterY');
      [*] = ;
      [*] = ;            //for j := -2 to 2 do
      [*] = ;            //for k := -2 to 2 do
      [*] = ;            //SetHeightData(Round(x+j), Round(z+k), minHeight);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;// setup water planes
      [*] = ;for i := 0 to HexCount-1 do
      [*] = ;begin
      [*] = ;   var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   var TerrainType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;   if TerrainType = gc_WaterTerrainType then
      [*] = ;   begin
      [*] = ;      var x, y, z : Float;
      [*] = ;      GetTrackNodePositionByIndex(i, x, y, z);
      [*] = ;      var w : Float = gc_StratHexSize * Sqrt(3) / 2;
      [*] = ;      var h : Float = gc_StratHexSize * 3 / 4;
      [*] = ;      
      [*] = ;      var waterHeight : Float = ParserGetFloatValueByKeyByHandle(pStratHexCell, 'WaterHeight');
      [*] = ;
      [*] = ;      var LeftUp : Integer = _map_GetHexNeighbourIntValueByAngle(i, 60, 'TerrainType');
      [*] = ;      var RightUp : Integer = _map_GetHexNeighbourIntValueByAngle(i, 120, 'TerrainType');
      [*] = ;      var Left : Integer = _map_GetHexNeighbourIntValueByAngle(i, 0, 'TerrainType');
      [*] = ;      var Right : Integer = _map_GetHexNeighbourIntValueByAngle(i, 180, 'TerrainType');
      [*] = ;      var LeftDown : Integer = _map_GetHexNeighbourIntValueByAngle(i, -60, 'TerrainType');
      [*] = ;      var RightDown : Integer = _map_GetHexNeighbourIntValueByAngle(i, -120, 'TerrainType');
      [*] = ;
      [*] = ;      var minX, minY, maxX, maxY : Float = 0;
      [*] = ;
      [*] = ;      if (LeftUp <> gc_WaterTerrainType) and (RightUp <> gc_WaterTerrainType) then
      [*] = ;      begin
      [*] = ;         if Left <> gc_WaterTerrainType then
      [*] = ;         begin
      [*] = ;            minX := x - 3*w/2;
      [*] = ;            minY := z - 3*h/2;
      [*] = ;            maxX := x + 3*w/2;
      [*] = ;            maxY := z + 3*h/2;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            minX := x - w/2;
      [*] = ;            minY := z - 3*h/2;
      [*] = ;            maxX := x + 3*w/2;
      [*] = ;            maxY := z + 3*h/2;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (LeftUp = gc_WaterTerrainType) and (RightUp = gc_WaterTerrainType) then
      [*] = ;      begin
      [*] = ;         if Left <> gc_WaterTerrainType then
      [*] = ;         begin
      [*] = ;            minX := x - 3*w/2;
      [*] = ;            minY := z - h/2;
      [*] = ;            maxX := x + 3*w/2;
      [*] = ;            maxY := z + 3*h/2;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            minX := x - w/2;
      [*] = ;            minY := z - h/2;
      [*] = ;            maxX := x + 3*w/2;
      [*] = ;            maxY := z + 3*h/2;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (LeftUp <> gc_WaterTerrainType) and (RightUp =  gc_WaterTerrainType) then
      [*] = ;      begin
      [*] = ;         if Left <> gc_WaterTerrainType then
      [*] = ;         begin
      [*] = ;            minX := x - 3*w/2;
      [*] = ;            minY := z - 3*h/2;
      [*] = ;            maxX := x - w/2;
      [*] = ;            maxY := z - h/2;
      [*] = ;            WaterFieldAdd(gc_WaterNameShardMap, minX, minY, maxX, maxY, waterHeight);
      [*] = ;
      [*] = ;            minX := x - 3*w/2;
      [*] = ;            minY := z - h/2;
      [*] = ;            maxX := x + 3*w/2;
      [*] = ;            maxY := z + 3*h/2;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            minX := x - w/2;
      [*] = ;            minY := z - h/2;
      [*] = ;            maxX := x + 3*w/2;
      [*] = ;            maxY := z + 3*h/2;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (LeftUp = gc_WaterTerrainType) and (RightUp <> gc_WaterTerrainType) then
      [*] = ;      begin
      [*] = ;         if (Left <> gc_WaterTerrainType) then
      [*] = ;         begin
      [*] = ;            minX := x + w/2;
      [*] = ;            minY := z - 3*h/2;
      [*] = ;            maxX := x + 3*w/2;
      [*] = ;            maxY := z - h/2;
      [*] = ;            WaterFieldAdd(gc_WaterNameShardMap, minX, minY, maxX, maxY, waterHeight);
      [*] = ;
      [*] = ;            minX := x - 3*w/2;
      [*] = ;            minY := z - h/2;
      [*] = ;            maxX := x + 3*w/2;
      [*] = ;            maxY := z + 3*h/2;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            minX := x + w/2;
      [*] = ;            minY := z - 3*h/2;
      [*] = ;            maxX := x + 3*w/2;
      [*] = ;            maxY := z - h/2;
      [*] = ;            WaterFieldAdd(gc_WaterNameShardMap, minX, minY, maxX, maxY, waterHeight);
      [*] = ;
      [*] = ;            minX := x - w/2;
      [*] = ;            minY := z - h/2;
      [*] = ;            maxX := x + 3*w/2;
      [*] = ;            maxY := z + 3*h/2;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      WaterFieldAdd(gc_WaterNameShardMap, minX, minY, maxX, maxY, waterHeight);
      [*] = ;      //break;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// smooth shores
      [*] = ;for i := 0 to HexCount-1 do
      [*] = ;begin
      [*] = ;   var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   var TerrainType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;   if TerrainType = gc_WaterTerrainType then
      [*] = ;   begin
      [*] = ;      var posX, posY, posZ : Float;
      [*] = ;      GetTrackNodePositionByIndex(i, posX, posY, posZ);
      [*] = ;
      [*] = ;      for j := 0 to 5 do
      [*] = ;      begin
      [*] = ;         TerrainType := _map_GetHexNeighbourIntValueByAngle(i, j*60, 'TerrainType');
      [*] = ;         if TerrainType <> gc_WaterTerrainType then
      [*] = ;         begin
      [*] = ;            var dirX : Float = -(gc_StratHexSize * Sqrt(3) / 2 + cSmoothOffset);
      [*] = ;            var dirY : Float = 0;
      [*] = ;            var dirZ : Float = 0;
      [*] = ;            VectorRotateY(dirX, dirY, dirZ, -j*60);
      [*] = ;
      [*] = ;            for k := 0 to cSmoothPasses-1 do
      [*] = ;            SmoothTerrain(Round(posX + dirX), -Round(posZ + dirZ), true, cSmoothRadius);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+cPatternPlName+' OC: '+IntToStr(GetPlayerGameObjectsCountByHandle(patPlHandle))+']', $1000000 or _log_trace);
   struct.end
section.end

