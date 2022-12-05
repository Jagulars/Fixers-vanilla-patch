section.begin
   Name = map.DrawHexGrid
   Code : struct.begin
      [*] = ;//TimeLog('Draw grid');
      [*] = ;var cInHexReachR : Float = 0.75;
      [*] = ;var cInHexReachG : Float = 0.75;
      [*] = ;var cInHexReachB : Float = 0;
      [*] = ;var cInHexReachA : Float = 0.75;
      [*] = ;var cOutHexReachR : Float = 0.75;
      [*] = ;var cOutHexReachG : Float = 0.75;
      [*] = ;var cOutHexReachB : Float = 0;
      [*] = ;var cOutHexReachA : Float = 0.0;
      [*] = ;var cHexReachSize : Float = 0.03;
      [*] = ;
      [*] = ;var GridSize : Integer = _map_GetGridSize();
      [*] = ;
      [*] = ;var pGridVertices : Integer = gGridVertices.handle;
      [*] = ;var pStratHexCells : Integer = gStratHexCells.handle;
      [*] = ;var pGridVertice  : Integer;
      [*] = ;
      [*] = ;DebugDrawClean('Grid');
      [*] = ;DebugDrawClean('');
      [*] = ;
      [*] = ;procedure DrawHexByTrackNodeIndex(DVZone, tnIndex : Integer);
      [*] = ;begin
      [*] = ;   var x, y, x0, y0 : Integer;
      [*] = ;   var x1, y1, x2, y2 : Integer;
      [*] = ;
      [*] = ;   var indX, indY, ind : Integer;
      [*] = ;   indX := tnIndex div GridSize;
      [*] = ;   indY := tnIndex mod GridSize;
      [*] = ;
      [*] = ;   if indY mod 2 = 0 then
      [*] = ;   begin
      [*] = ;      if indY < GridSize-1 then
      [*] = ;      ind := (indY div 2) * (4 * GridSize + 4) + 2 * indX
      [*] = ;      else
      [*] = ;      ind := (indY div 2) * (4 * GridSize + 4) + 2 * indX;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   ind := (indY div 2) * (4 * GridSize + 4) + 2 * indX + 2 * GridSize + 1;
      [*] = ;
      [*] = ;   pGridVertice := ParserSelectByHandleByIndex(pGridVertices, ind);
      [*] = ;   x0 := ParserGetIntValueByKeyByHandle(pGridVertice, 'X');
      [*] = ;   y0 := ParserGetIntValueByKeyByHandle(pGridVertice, 'Y');
      [*] = ;   pGridVertice := ParserSelectByHandleByIndex(pGridVertices, ind+1);
      [*] = ;   x1 := ParserGetIntValueByKeyByHandle(pGridVertice, 'X');
      [*] = ;   y1 := ParserGetIntValueByKeyByHandle(pGridVertice, 'Y');
      [*] = ;   pGridVertice := ParserSelectByHandleByIndex(pGridVertices, ind+2);
      [*] = ;   x2 := ParserGetIntValueByKeyByHandle(pGridVertice, 'X');
      [*] = ;   y2 := ParserGetIntValueByKeyByHandle(pGridVertice, 'Y');
      [*] = ;
      [*] = ;   GUIDataViewerZonePointListAdd(DVZone, x0, 0.1, y0);
      [*] = ;   GUIDataViewerZonePointListAdd(DVZone, x1, 0.1, y1);
      [*] = ;   GUIDataViewerZonePointListAdd(DVZone, x2, 0.1, y2);
      [*] = ;
      [*] = ;   if (GridSize mod 2 = 1) and (indY = GridSize-1) then
      [*] = ;   ind := ind - 1;
      [*] = ;
      [*] = ;   pGridVertice := ParserSelectByHandleByIndex(pGridVertices, ind+2*GridSize+4);
      [*] = ;   x := ParserGetIntValueByKeyByHandle(pGridVertice, 'X');
      [*] = ;   y := ParserGetIntValueByKeyByHandle(pGridVertice, 'Y');
      [*] = ;   pGridVertice := ParserSelectByHandleByIndex(pGridVertices, ind+2*GridSize+3);
      [*] = ;   x1 := ParserGetIntValueByKeyByHandle(pGridVertice, 'X');
      [*] = ;   y1 := ParserGetIntValueByKeyByHandle(pGridVertice, 'Y');
      [*] = ;   pGridVertice := ParserSelectByHandleByIndex(pGridVertices, ind+2*GridSize+2);
      [*] = ;   x2 := ParserGetIntValueByKeyByHandle(pGridVertice, 'X');
      [*] = ;   y2 := ParserGetIntValueByKeyByHandle(pGridVertice, 'Y');
      [*] = ;
      [*] = ;   GUIDataViewerZonePointListAdd(DVZone, x, 0.1, y);
      [*] = ;   GUIDataViewerZonePointListAdd(DVZone, x1, 0.1, y1);
      [*] = ;   GUIDataViewerZonePointListAdd(DVZone, x2, 0.1, y2);
      [*] = ;
      [*] = ;   GUIDataViewerZonePointListAdd(DVZone, x0, 0.1, y0);
      [*] = ;end;
      [*] = ;
      [*] = ;ExecuteState('map.InitViewerZones');
      [*] = ;
      [*] = ;var arrTerrainColors : array[0..8] of TColorRGBA;
      [*] = ;arrTerrainColors[2+gc_MountainTerrainType].r := 1;
      [*] = ;arrTerrainColors[2+gc_MountainTerrainType].g := 0;
      [*] = ;arrTerrainColors[2+gc_MountainTerrainType].b := 0;
      [*] = ;arrTerrainColors[2+gc_MountainTerrainType].a := 0.5;
      [*] = ;
      [*] = ;arrTerrainColors[2+gc_WaterTerrainType].r := 0;
      [*] = ;arrTerrainColors[2+gc_WaterTerrainType].g := 0;
      [*] = ;arrTerrainColors[2+gc_WaterTerrainType].b := 1;
      [*] = ;arrTerrainColors[2+gc_WaterTerrainType].a := 0.75;
      [*] = ;
      [*] = ;arrTerrainColors[2+gc_PlainTerrainType].r := 0.3;
      [*] = ;arrTerrainColors[2+gc_PlainTerrainType].g := 1.0;
      [*] = ;arrTerrainColors[2+gc_PlainTerrainType].b := 0.6;
      [*] = ;arrTerrainColors[2+gc_PlainTerrainType].a := 0.35;
      [*] = ;
      [*] = ;arrTerrainColors[2+gc_ForestTerrainType].r := 0;
      [*] = ;arrTerrainColors[2+gc_ForestTerrainType].g := 0.5;
      [*] = ;arrTerrainColors[2+gc_ForestTerrainType].b := 0.5;
      [*] = ;arrTerrainColors[2+gc_ForestTerrainType].a := 0.6;
      [*] = ;
      [*] = ;arrTerrainColors[2+gc_HillTerrainType].r := 0;
      [*] = ;arrTerrainColors[2+gc_HillTerrainType].g := 0.5;
      [*] = ;arrTerrainColors[2+gc_HillTerrainType].b := 0;
      [*] = ;arrTerrainColors[2+gc_HillTerrainType].a := 0.75;
      [*] = ;
      [*] = ;arrTerrainColors[2+gc_SwampTerrainType].r := 0;
      [*] = ;arrTerrainColors[2+gc_SwampTerrainType].g := 0;
      [*] = ;arrTerrainColors[2+gc_SwampTerrainType].b := 0.5;
      [*] = ;arrTerrainColors[2+gc_SwampTerrainType].a := 0.5;
      [*] = ;
      [*] = ;arrTerrainColors[2+gc_DesertTerrainType].r := 0.75;
      [*] = ;arrTerrainColors[2+gc_DesertTerrainType].g := 0.75;
      [*] = ;arrTerrainColors[2+gc_DesertTerrainType].b := 0;
      [*] = ;arrTerrainColors[2+gc_DesertTerrainType].a := 0.5;
      [*] = ;
      [*] = ;arrTerrainColors[2+gc_DeadLandTerrainType].r := 0.75;
      [*] = ;arrTerrainColors[2+gc_DeadLandTerrainType].g := 0;
      [*] = ;arrTerrainColors[2+gc_DeadLandTerrainType].b := 0.75;
      [*] = ;arrTerrainColors[2+gc_DeadLandTerrainType].a := 0.5;
      [*] = ;
      [*] = ;var cellCount : Integer = ParserGetCountByHandle(pStratHexCells);
      [*] = ;var mapSize : Integer = floor(sqrt(cellCount));
      [*] = ;var i : Integer;
      [*] = ;for i := 0 to cellCount-1 do
      [*] = ;begin
      [*] = ;   var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   if (gGame.fog) and (ParserGetIntValueByIndexByHandle(ParserSelectByHandleByKey(pStratHexCell, 'Fog'), gIntRegister_MapMyPlayerIndex) > 1) then
      [*] = ;      continue;
      [*] = ;   
      [*] = ;   var pHexVertices : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Vertices');
      [*] = ;
      [*] = ;   if (gMapEditor.enabled) then
      [*] = ;   begin
      [*] = ;      var terrainType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;      if (gMapEditor.grid[i].terrain<>terrainType) and (gMapEditor.grid[i].terrain<>0) then
      [*] = ;      begin
      [*] = ;         cInHexReachR := arrTerrainColors[2+gMapEditor.grid[i].terrain].r;
      [*] = ;         cInHexReachG := arrTerrainColors[2+gMapEditor.grid[i].terrain].g;
      [*] = ;         cInHexReachB := arrTerrainColors[2+gMapEditor.grid[i].terrain].b;
      [*] = ;         cInHexReachA := arrTerrainColors[2+gMapEditor.grid[i].terrain].a;
      [*] = ;         cOutHexReachR := cInHexReachR;
      [*] = ;         cOutHexReachG := cInHexReachG;
      [*] = ;         cOutHexReachB := cInHexReachB;
      [*] = ;         cOutHexReachA := 0;
      [*] = ;         cHexReachSize := 0.25;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         cInHexReachR := 0.75;
      [*] = ;         cInHexReachG := 0.75;
      [*] = ;         cInHexReachB := 0;
      [*] = ;         cInHexReachA := 0.75;
      [*] = ;         cOutHexReachR := 0.75;
      [*] = ;         cOutHexReachG := 0.75;
      [*] = ;         cOutHexReachB := 0;
      [*] = ;         cOutHexReachA := 0.0;
      [*] = ;         cHexReachSize := 0.03;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var DVZone : Integer = GUIAddDataViewerZoneColorExt(cHexReachSize, cInHexReachR,cInHexReachG,cInHexReachB,cInHexReachA,cOutHexReachR,cOutHexReachG,cOutHexReachB,cOutHexReachA);
      [*] = ;
      [*] = ;   var x, y : Float;
      [*] = ;   var j : Integer;
      [*] = ;   for j := 0 to ParserGetCountByHandle(pHexVertices)-1 do
      [*] = ;   begin
      [*] = ;      var pHexVertice : Integer = ParserSelectByHandleByIndex(pHexVertices, j);
      [*] = ;      x := ParserGetFloatValueByKeyByHandle(pHexVertice, 'X');
      [*] = ;      y := ParserGetFloatValueByKeyByHandle(pHexVertice, 'Y');
      [*] = ;      GUIDataViewerZonePointListAdd(DVZone, x, 0.1, y);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var pHexVertice : Integer = ParserSelectByHandleByIndex(pHexVertices, 0);
      [*] = ;   x := ParserGetFloatValueByKeyByHandle(pHexVertice, 'X');
      [*] = ;   y := ParserGetFloatValueByKeyByHandle(pHexVertice, 'Y');
      [*] = ;   GUIDataViewerZonePointListAdd(DVZone, x, 0.1, y);
      [*] = ;end;
      [*] = ;
      [*] = ;function IsOwnerByIndex(pStratHexCells, ind : Integer; comparePlayer : String) : Boolean;
      [*] = ;begin
      [*] = ;   if (ind>=0) and (ind<ParserGetCountByHandle(pStratHexCells)) then
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, ind);
      [*] = ;      var bNeutral : Boolean = _misc_IsProvinceNeutral(pStratHexCell);
      [*] = ;      var lastPlayer : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'LastPlayer');
      [*] = ;      var player : String = ParserGetValueByKeyByHandle(pStratHexCell, 'Player');
      [*] = ;      if (bNeutral) and (lastPlayer>=0) then
      [*] = ;      player := GetPlayerNameByIndex(lastPlayer);
      [*] = ;      Result := (player=comparePlayer);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      Result := False;
      [*] = ;      //log('IsOwnerByIndex : ind out of bounds : ind = '+IntToStr(ind));
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;for i := 0 to cellCount-1 do
      [*] = ;begin
      [*] = ;   var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;   if (gGame.fog) and (ParserGetIntValueByIndexByHandle(ParserSelectByHandleByKey(pStratHexCell, 'Fog'), gIntRegister_MapMyPlayerIndex) > 1) then
      [*] = ;      continue;
      [*] = ;   
      [*] = ;   var pHexVertices : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Vertices');
      [*] = ;
      [*] = ;   var player : String = ParserGetValueByKeyByHandle(pStratHexCell, 'Player');
      [*] = ;   var bNeutral : Boolean = _misc_IsProvinceNeutral(pStratHexCell);
      [*] = ;   var lastPlayer : Integer =  ParserGetIntValueByKeyByHandle(pStratHexCell, 'LastPlayer');
      [*] = ;   if (bNeutral) and (lastPlayer>=0) then
      [*] = ;   player := GetPlayerNameByIndex(lastPlayer);
      [*] = ;   var plHandle : Integer = GetPlayerHandleByName(player);
      [*] = ;   if (plHandle<>0) then
      [*] = ;   begin
      [*] = ;      var bPlayerHex : Boolean = (player<>'') or ((bNeutral) and (lastPlayer>=0));
      [*] = ;
      [*] = ;      var x, y : Float;
      [*] = ;      var nextX, nextY : Float;
      [*] = ;      var bLeft : Boolean = (i>=mapSize) and (i>=mapSize) and (IsOwnerByIndex(pStratHexCells, i-mapSize, player));
      [*] = ;      var bRight : Boolean = (i<mapSize*mapSize) and (IsOwnerByIndex(pStratHexCells, i+mapSize, player));
      [*] = ;
      [*] = ;      var bLeftTop : Boolean = ((i mod 2)<>0) and (IsOwnerByIndex(pStratHexCells, i-1, player));
      [*] = ;      if ((i mod 2)=0) and (i>mapSize+1) then
      [*] = ;      if (IsOwnerByIndex(pStratHexCells, i-mapSize-1, player)) then
      [*] = ;      bLeftTop := True;
      [*] = ;
      [*] = ;      var bRightTop : Boolean = ((i mod 2)=0) and (IsOwnerByIndex(pStratHexCells, i-1, player));
      [*] = ;      if ((i mod 2)<>0) then
      [*] = ;      if (IsOwnerByIndex(pStratHexCells, i+mapSize-1, player)) then
      [*] = ;      bRightTop := True;
      [*] = ;
      [*] = ;      var bLeftBottom : Boolean = ((i mod 2)<>0) and (IsOwnerByIndex(pStratHexCells, i+1, player));
      [*] = ;      var bRightBottom : Boolean = ((i mod 2)=0) and (IsOwnerByIndex(pStratHexCells, i+1, player));
      [*] = ;      if ((i mod 2)<>0) then
      [*] = ;      if (IsOwnerByIndex(pStratHexCells, i+mapSize+1, player)) then
      [*] = ;      bRightBottom := True;
      [*] = ;
      [*] = ;      if ((i mod 2)=0) and (i>mapSize-1) then
      [*] = ;      if (IsOwnerByIndex(pStratHexCells, i-mapSize+1, player)) then
      [*] = ;      bLeftBottom := True;
      [*] = ;
      [*] = ;      if ((i mod mapSize)=mapSize-1) then
      [*] = ;      begin
      [*] = ;         bLeftBottom := False;
      [*] = ;         bRightBottom := False;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (i mod mapSize)=0 then
      [*] = ;      begin
      [*] = ;         bLeftTop := False;
      [*] = ;         bRightTop := False;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var cr, cg, cb : Float = 1;
      [*] = ;      //var cr1, cg1, cb1 : Float = 1;
      [*] = ;
      [*] = ;      var plIndex : Integer = GetPlayerIndexByHandle(plHandle);
      [*] = ;      _gui_GetBorderPaletteColorByIndex(plIndex, cr, cg, cb);
      [*] = ;
      [*] = ;      var j : Integer;
      [*] = ;      for j:=0 to ParserGetCountByHandle(pHexVertices)-1 do
      [*] = ;      begin
      [*] = ;         if (not bPlayerHex) or
      [*] = ;         (j=3) and (bRightBottom) or
      [*] = ;         (j=0) and (bLeftTop) or
      [*] = ;         (j=4) and (bLeftBottom) or
      [*] = ;         (j=1) and (bRightTop) or
      [*] = ;         (j=5) and (bLeft) or
      [*] = ;         (j=2) and (bRight) then
      [*] = ;         begin
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var indNext : Integer = j+1;
      [*] = ;            if (indNext>5) then
      [*] = ;            indNext := indNext-6;
      [*] = ;            var DVZone : Integer = GUIAddDataViewerZoneColorExt(cHexReachSize*8,cR,cG,cB,cInHexReachA,cR,cG,cB,cOutHexReachA);
      [*] = ;            var pNextHexVertice : Integer = ParserSelectByHandleByIndex(pHexVertices, indNext);
      [*] = ;            nextX := ParserGetFloatValueByKeyByHandle(pNextHexVertice, 'X');
      [*] = ;            nextY := ParserGetFloatValueByKeyByHandle(pNextHexVertice, 'Y');
      [*] = ;            var pHexVertice : Integer = ParserSelectByHandleByIndex(pHexVertices, j);
      [*] = ;            x := ParserGetFloatValueByKeyByHandle(pHexVertice, 'X');
      [*] = ;            y := ParserGetFloatValueByKeyByHandle(pHexVertice, 'Y');
      [*] = ;            GUIDataViewerZonePointListAdd(DVZone, x, 0.1, y);
      [*] = ;            GUIDataViewerZonePointListAdd(DVZone, nextX, 0.1, nextY);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

