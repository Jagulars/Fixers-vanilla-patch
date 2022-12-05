section.begin
   Name = FillTerrainPatterns
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.PROVINCE.INC\FILLTERRAINPATTERNS';
      [*] = ;var _log_trace : Integer = $40000;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var pProvince : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_Province_iParserHandle);
      [*] = ;var provIndex : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Index');
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[ProvUID: '+IntToStr(GetGameObjectUniqueIdByHandle(GetGameObjectMyHandle))+']',_log_trace);
      [*] = ;
      [*] = ;const cPatternPlName = 'pattern';
      [*] = ;const cPatternPlRace = 'nature';
      [*] = ;const cPatternPlCMode = 'cmNone';
      [*] = ;
      [*] = ;const cForestPatternCount = 1;//5;
      [*] = ;
      [*] = ;procedure FillPatterns();
      [*] = ;begin
      [*] = ;   var patPlHandle : Integer = _plr_GetOrCreatePlayer(cPatternPlName, cPatternPlRace, cPatternPlCMode, False);
      [*] = ;   var oldGoCount : Integer = GetPlayerGameObjectsCountByHandle(patPlHandle);
      [*] = ;
      [*] = ;   var pStratHexCells : Integer = gStratHexCells.handle;
      [*] = ;   var pPatternCover : Integer = gPatternCoverTerrainTypes.handle;
      [*] = ;
      [*] = ;   var shardVisualID : Integer = 0;
      [*] = ;   if (_worldrule_GetWorldRuleVisualExistByID(3)) then
      [*] = ;      shardVisualID := _worldrule_GetWorldRuleVisualParams(3, 1);
      [*] = ;
      [*] = ;   procedure PruneUnderWaterObjects();
      [*] = ;   begin
      [*] = ;      const cWaterLineOffset = 0.6; // we need this because apparently object center position is not at its terrain contact point
      [*] = ;      
      [*] = ;      var newCount : Integer = GetPlayerGameObjectsCountByHandle(patPlHandle);
      [*] = ;      if newCount > oldGoCount then
      [*] = ;      begin
      [*] = ;         var i, goHandle, nIndex, pNeighbour : Integer;
      [*] = ;         var waterHeight : Float = 0;
      [*] = ;         var maxWaterHeight : Float = -10000;
      [*] = ;         
      [*] = ;         for i := 0 to 5 do
      [*] = ;         begin
      [*] = ;            IntRegister0 := pProvince;
      [*] = ;            IntRegister1 := i;
      [*] = ;            MapExecuteState('map.GetNeighbourHexByIndex');
      [*] = ;            pNeighbour := IntRegister2;
      [*] = ;            if (pNeighbour <> 0) then
      [*] = ;            begin
      [*] = ;               if (ParserGetIntValueByKeyByHandle(pNeighbour, 'TerrainType') = gc_WaterTerrainType) then
      [*] = ;               begin
      [*] = ;                  waterHeight := ParserGetFloatValueByKeyByHandle(pNeighbour, 'WaterHeight');
      [*] = ;                  if (waterHeight > maxWaterHeight) then
      [*] = ;                     maxWaterHeight := waterHeight;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;         
      [*] = ;         if waterHeight <> 0 then
      [*] = ;         for i := newCount-1 downto oldGoCount do
      [*] = ;         begin
      [*] = ;            goHandle := GetGameObjectHandleByIndex(i, patPlHandle);
      [*] = ;            if (GetGameObjectPositionYByHandle(goHandle) < maxWaterHeight + cWaterLineOffset) then
      [*] = ;               AddObjectToDestroyList(goHandle);
      [*] = ;         end;
      [*] = ;         {var goX, goZ, dirX, dirZ, angle, waterHeight : Float;
      [*] = ;         var centerX : Float = ParserGetFloatValueByKeyByHandle(pProvince, 'CenterX');
      [*] = ;         var centerZ : Float = ParserGetFloatValueByKeyByHandle(pProvince, 'CenterY');
      [*] = ;   
      [*] = ;         for i := newCount-1 downto oldGoCount do
      [*] = ;         begin
      [*] = ;            goHandle := GetGameObjectHandleByIndex(i, patPlHandle);
      [*] = ;            goX := GetGameObjectPositionXByHandle(goHandle);
      [*] = ;            goZ := GetGameObjectPositionZByHandle(goHandle);
      [*] = ;            dirX := goX - centerX;
      [*] = ;            dirZ := goZ - centerZ;
      [*] = ;            angle := VectorAngle(dirX, 0, dirZ, 1, 0, 0);
      [*] = ;            nIndex := _map_GetNeighbourHexIndexByAngle(provIndex, angle);
      [*] = ;            pNeighbour := ParserSelectByHandleByIndex(pStratHexCells, nIndex);
      [*] = ;            Log(' nUid '+IntToStr(ParserGetIntValueByKeyByHandle(pNeighbour, 'DummyUID'))+' angle '+FloatToStr(angle));
      [*] = ;            if (pNeighbour <> 0) and (ParserGetIntValueByKeyByHandle(pNeighbour, 'TerrainType') = gc_WaterTerrainType) then
      [*] = ;            begin
      [*] = ;               waterHeight := ParserGetFloatValueByKeyByHandle(pNeighbour, 'WaterHeight');
      [*] = ;               Log('waterHeight ' +FloatToStr(waterHeight)+' goHeight '+FloatToStr(GetGameObjectPositionYByHandle(goHandle)));
      [*] = ;               if (waterHeight <> 0) and (GetGameObjectPositionYByHandle(goHandle) < waterHeight) then
      [*] = ;                  AddObjectToDestroyList(goHandle);
      [*] = ;            end;
      [*] = ;         end;}
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var i, j : Integer;
      [*] = ;   var terrainType : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'TerrainType');
      [*] = ;   var pPriorityList : Integer = 0;
      [*] = ;   var sTerrainType : String = '';
      [*] = ;
      [*] = ;   case terrainType of
      [*] = ;      gc_MountainTerrainType : sTerrainType := 'Mountain';
      [*] = ;      gc_WaterTerrainType : sTerrainType := 'Water';
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         IntRegister0 := terrainType;
      [*] = ;         MapExecuteState('GetTerrainParserByID');
      [*] = ;         var pTerrainType : Integer = IntRegister1;
      [*] = ;         sTerrainType := ParserGetValueByKeyByHandle(pTerrainType, 'Name');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pPatternCover)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pHandle : Integer = ParserSelectByHandleByIndex(pPatternCover, i);
      [*] = ;
      [*] = ;      if SameText(ParserGetValueByKeyByHandle(pHandle, 'TerrainType'), sTerrainType) then
      [*] = ;      begin
      [*] = ;         pPriorityList := pHandle;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (terrainType <> gc_MountainTerrainType) and (pPriorityList <> 0) then
      [*] = ;   begin
      [*] = ;      pPriorityList := ParserSelectByHandleByKey(pPriorityList, 'PatternPriority');
      [*] = ;      //pPriorityList := ParserSelectByHandleByIndex(pPriorityList, 0);
      [*] = ;      //pPriorityList := ParserSelectByHandleByKey(pPriorityList, 'PatternList');
      [*] = ;
      [*] = ;      var x, y, z : Float;
      [*] = ;      var xc, zc : Float;
      [*] = ;      var x0, z0 : Float;
      [*] = ;      var minX : Float = 10000;
      [*] = ;      var maxX : Float = -10000;
      [*] = ;      var minZ : Float = 10000;
      [*] = ;      var maxZ : Float = -10000;
      [*] = ;
      [*] = ;      xc := 0;
      [*] = ;      zc := 0;
      [*] = ;      var pVertices : Integer = ParserSelectByHandleByKey(pProvince, 'Vertices');
      [*] = ;
      [*] = ;      var xv, zv : array [0..5] of Float;
      [*] = ;      for i := 0 to 5 do
      [*] = ;      begin
      [*] = ;         var pVertice : Integer = ParserSelectByHandleByIndex(pVertices, i);
      [*] = ;         x0 := ParserGetFloatValueByKeyByHandle(pVertice, 'X');
      [*] = ;         z0 := ParserGetFloatValueByKeyByHandle(pVertice, 'Y');
      [*] = ;         xv[i] := x0;
      [*] = ;         zv[i] := z0;
      [*] = ;
      [*] = ;         if x0 < minX then
      [*] = ;         minX := x0;
      [*] = ;         if x0 > maxX then
      [*] = ;         maxX := x0;
      [*] = ;         if z0 < minZ then
      [*] = ;         minZ := z0;
      [*] = ;         if z0 > maxZ then
      [*] = ;         maxZ := z0;
      [*] = ;
      [*] = ;         xc := xc + x0;
      [*] = ;         zc := zc + z0;
      [*] = ;      end;
      [*] = ;      //Log('_____________ new hex ______________________');
      [*] = ;      //for i := 0 to 5 do
      [*] = ;      //begin
      [*] = ;         //   Log('(' + FloatToStr(xv[i]) + ', ' + FloatToStr(zv[i]) + ')');
      [*] = ;      //end;
      [*] = ;
      [*] = ;      xc := xc / 6;
      [*] = ;      zc := zc / 6;
      [*] = ;
      [*] = ;      var sAngle : String = ParserGetValueByKeyByHandle(pProvince, 'PatternAngle');
      [*] = ;      var angle : Integer;
      [*] = ;      if sAngle = '' then
      [*] = ;      begin
      [*] = ;         if terrainType <> gc_HillTerrainType then // hill always zero angle
      [*] = ;            angle := Floor(Random * 360)
      [*] = ;            //angle := Floor(Random * 2)*180*pi/2
      [*] = ;         else
      [*] = ;            angle := 0;
      [*] = ;         ParserSetIntValueByKeyByHandle(pProvince, 'PatternAngle', angle);
      [*] = ;      end
      [*] = ;      else
      [*] = ;         angle := StrToInt(sAngle);
      [*] = ;
      [*] = ;      if terrainType = gc_ForestTerrainType then
      [*] = ;      begin
      [*] = ;         for i := 0 to cForestPatternCount-1 do
      [*] = ;         begin
      [*] = ;            x := minX + Random * (maxX - minX);
      [*] = ;            z := minZ + Random * (maxZ - minZ);
      [*] = ;            if (i = 0) or IsPointInHex(x, z, xv[0], zv[0], xv[1], zv[1], xv[2], zv[2], xv[3], zv[3], xv[4], zv[4], xv[5], zv[5]) then
      [*] = ;            begin
      [*] = ;               var prCount : Integer = ParserGetCountByHandle(pPriorityList);
      [*] = ;               var prIndex : Integer = 0;
      [*] = ;
      [*] = ;               if i > 0 then
      [*] = ;                  prIndex := Floor(Random * prCount);
      [*] = ;
      [*] = ;               var pPatternList : Integer = ParserSelectByHandleByIndex(pPriorityList, prIndex);
      [*] = ;               pPatternList := ParserSelectByHandleByKey(pPatternList, 'PatternList');
      [*] = ;               
      [*] = ;               var patternIndex : Integer = _pars_GetIntValueByKeyByHandleDef(pProvince, 'PatternIndex', -1);
      [*] = ;               if patternIndex = -1 then
      [*] = ;                  patternIndex := _misc_GetRandomPatternIndex(pPatternList, shardVisualID, False);
      [*] = ;         
      [*] = ;               var pPattern : Integer = ParserSelectByHandleByIndex(pPatternList, patternIndex);
      [*] = ;               if pPattern <> 0 then
      [*] = ;               begin
      [*] = ;                  ParserSetIntValueByKeyByHandle(pProvince, 'PatternIndex', patternIndex);
      [*] = ;                  var patName : String = ParserGetValueByKeyByHandle(pPattern, 'PatternName');
      [*] = ;
      [*] = ;                  if i = 0 then
      [*] = ;                  begin
      [*] = ;                     StandPattern(patPlHandle, patName, xc, zc, angle);
      [*] = ;                     //Log('pattern position: (' + FloatToStr(xc) + ', ' + FloatToStr(zc) + ')');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     StandPattern(patPlHandle, patName, x, z, angle);
      [*] = ;                     //Log('pattern position: (' + FloatToStr(x) + ', ' + FloatToStr(z) + ')');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (terrainType = gc_HillTerrainType) or (terrainType = gc_SwampTerrainType) or (terrainType = gc_DesertTerrainType) or (terrainType = gc_DeadLandTerrainType) then
      [*] = ;      begin
      [*] = ;         var prIndex : Integer = 0;
      [*] = ;
      [*] = ;         var pPatternList : Integer = ParserSelectByHandleByIndex(pPriorityList, prIndex);
      [*] = ;         pPatternList := ParserSelectByHandleByKey(pPatternList, 'PatternList');
      [*] = ;         var patternIndex : Integer = _pars_GetIntValueByKeyByHandleDef(pProvince, 'PatternIndex', -1);
      [*] = ;         if patternIndex = -1 then
      [*] = ;            patternIndex := _misc_GetRandomPatternIndex(pPatternList, shardVisualID, False);
      [*] = ;         
      [*] = ;         var pPattern : Integer = ParserSelectByHandleByIndex(pPatternList, patternIndex);
      [*] = ;         if pPattern <> 0 then
      [*] = ;         begin
      [*] = ;            ParserSetIntValueByKeyByHandle(pProvince, 'PatternIndex', patternIndex);
      [*] = ;            var patName : String = ParserGetValueByKeyByHandle(pPattern, 'PatternName');
      [*] = ;
      [*] = ;            StandPattern(patPlHandle, patName, xc, zc, angle);
      [*] = ;
      [*] = ;            var pLayerPlaces : Integer = ParserSelectByHandleByKey(pPattern, 'LayerPlaces');
      [*] = ;            if pLayerPlaces <> 0 then
      [*] = ;            begin
      [*] = ;               for i := 0 to ParserGetCountByHandle(pLayerPlaces)-1 do
      [*] = ;               begin
      [*] = ;                  var pLayerPlace : Integer = ParserSelectByHandleByIndex(pLayerPlaces, i);
      [*] = ;                  var posX : Float = ParserGetFloatValueByKeyByHandle(pLayerPlace, 'PosX');
      [*] = ;                  var posY : Float = ParserGetFloatValueByKeyByHandle(pLayerPlace, 'PosY');
      [*] = ;                  var pLayers : Integer = ParserSelectByHandleByKey(pLayerPlace, 'Layers');
      [*] = ;                  if pLayers <> 0 then
      [*] = ;                  begin
      [*] = ;                     patName := ParserGetValueByIndexByHandle(pLayers, Floor(Random * ParserGetCountByHandle(pLayers)));
      [*] = ;                     StandPattern(patPlHandle, patName, xc+posX, zc+posY, angle);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            //Log('pattern position: (' + FloatToStr(xc) + ', ' + FloatToStr(zc) + ')');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      
      [*] = ;      PruneUnderWaterObjects();
      [*] = ;      
      [*] = ;      BoolRegister0 := False;
      [*] = ;      FloatRegister0 := 0;
      [*] = ;      ExecuteState('HideShowObjects');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;FillPatterns();
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

