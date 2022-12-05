section.begin
   Name = CreateRoad
   Code : struct.begin
      [*] = ;var _log_name : String = 'MAP\MAP.PROVINCE.INC\CREATEROAD';
      [*] = ;var _log_trace : Integer = $40000;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var pProvince : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_Province_iParserHandle);
      [*] = ;var provIndex : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Index');
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[ProvUID: '+IntToStr(GetGameObjectUniqueIdByHandle(GetGameObjectMyHandle))+']',_log_trace);
      [*] = ;
      [*] = ;var sRoadPreset : String = 'map.medium.road';
      [*] = ;if (_worldrule_GetWorldRuleVisualExistByID(3)) then
      [*] = ;begin
      [*] = ;   if (_worldrule_GetWorldRuleVisualParams(3, 1)=5) then
      [*] = ;      sRoadPreset := 'map.medium.road_vulcan'
      [*] = ;   else
      [*] = ;   if (_worldrule_GetWorldRuleVisualParams(3, 1)=6) then
      [*] = ;      sRoadPreset := 'map.medium.road_ice';
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;procedure ClearObjectsInLine(const x1, y1, x2, y2, step : Float);
      [*] = ;begin
      [*] = ;   var lpixel : Float;
      [*] = ;   var lRatio : Float;
      [*] = ;   var x, y : Float;
      [*] = ;   var lMaxAxisLength : Float = VectorDistance(x1, 0, y1, x2, 0, y2);
      [*] = ;
      [*] = ;   //const cNatureRaceTag = 30;
      [*] = ;   const cNaturePlName = 'pattern';
      [*] = ;   var plHnd : Integer = GetPlayerHandleByName(cNaturePlName);
      [*] = ;   if plHnd <> 0 then
      [*] = ;   begin
      [*] = ;      while (lpixel<lMaxAxisLength) do
      [*] = ;      begin
      [*] = ;         lRatio := lpixel / lMaxAxisLength;
      [*] = ;         x := x1 + (x2 - x1) * lRatio;
      [*] = ;         y := y1 + (y2 - y1) * lRatio;
      [*] = ;         GetGameObjectsInRadius(x, y, step, false, true, plHnd, 0, 0, false, false, false, false, false, false);
      [*] = ;         var i : Integer;
      [*] = ;         for i:=0 to GetGameObjectListCount-1 do
      [*] = ;         begin
      [*] = ;            var goHnd : Integer = GetGameObjectListByIndex(i);
      [*] = ;            var goPosX : Float = GetGameObjectPositionXByHandle(goHnd);
      [*] = ;            var goPosZ : Float = GetGameObjectPositionZByHandle(goHnd);
      [*] = ;
      [*] = ;            if (not GetGameObjectPlayableObjectByHandle(goHnd)) and (VectorDistance(x, 0, y, goPosX, 0, goPosZ)<step) then
      [*] = ;            AddObjectToDestroyList(goHnd);
      [*] = ;         end;
      [*] = ;         lpixel := lpixel+step*0.5;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;procedure CreateVisuals(const sRoadPreset : String; const x1, z1, x2, z2 : Float);
      [*] = ;begin
      [*] = ;   ArrayAffineVectorClear;
      [*] = ;   const step = 0.5;
      [*] = ;   ArrayAffineVectorPush(x1, 0, z1);
      [*] = ;   ArrayAffineVectorPush(x2, 0, z2);
      [*] = ;   DecalSetManagerBuildConnections64(sRoadPreset, false, false, false, Floor(Random*1024), Floor(Random*1024));
      [*] = ;   ClearObjectsInLine(x1, z1, x2, z2, step);
      [*] = ;
      [*] = ;	// create sign
      [*] = ;   if (Random<0.5) then
      [*] = ;   begin
      [*] = ;      const cPlayerName = 'signs';
      [*] = ;      const cRaceName = 'nature';
      [*] = ;      const cBaseName = 'sign';
      [*] = ;      var posX : Float = (x1+x2)/2 + (0.5-Random);
      [*] = ;      var posZ : Float = (z1+z2)/2 + (0.5-Random);
      [*] = ;      var posY : Float = RayCastHeight(posX, posZ);
      [*] = ;      var goHandle : Integer = CreatePlayerGameObjectHandle(cPlayerName, cRaceName, cBaseName, posX, posY, posZ);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function IsRoadAvailable(const pStratHexCell : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := (ParserGetIntValueByKeyByHandle(pStratHexCell, 'Stable') > 0);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CheckNeighbours();
      [*] = ;begin
      [*] = ;   var i, j, pNeighbour, pNeighbourProv : Integer;
      [*] = ;   var pProvNeighbours : Integer = ParserSelectByHandleByKey(pProvince, 'Neighbours');
      [*] = ;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pProvNeighbours)-1 do
      [*] = ;   begin
      [*] = ;      pNeighbour := ParserSelectByHandleByIndex(pProvNeighbours, i);
      [*] = ;      pNeighbourProv := ParserSelectByHandleByIndex(gStratHexCells.handle, ParserGetIntValueByKeyByHandle(pNeighbour, 'Index'));
      [*] = ;      
      [*] = ;      if IsRoadAvailable(pNeighbourProv) and (ParserGetIntValueByKeyByHandle(pNeighbour, 'Road') = 0) then
      [*] = ;      begin
      [*] = ;         var centerX : Float = ParserGetFloatValueByKeyByHandle(pProvince, 'CenterX');
      [*] = ;         var centerY : Float = ParserGetFloatValueByKeyByHandle(pProvince, 'CenterY');
      [*] = ;         var nextCellCenterX : Float = ParserGetFloatValueByKeyByHandle(pNeighbourProv, 'CenterX');
      [*] = ;         var nextCellCenterY : Float = ParserGetFloatValueByKeyByHandle(pNeighbourProv, 'CenterY');
      [*] = ;
      [*] = ;         CreateVisuals(sRoadPreset, centerX, centerY, nextCellCenterX, nextCellCenterY);
      [*] = ;
      [*] = ;         ParserSetIntValueByKeyByHandle(pNeighbour, 'Road', 1);
      [*] = ;         
      [*] = ;         var pProvNeighbours : Integer = ParserSelectByHandleByKey(pNeighbourProv, 'Neighbours');
      [*] = ;         for j := 0 to ParserGetCountByHandle(pProvNeighbours)-1 do
      [*] = ;         begin
      [*] = ;            pNeighbour := ParserSelectByHandleByIndex(pProvNeighbours, j);
      [*] = ;            if ParserGetIntValueByKeyByHandle(pNeighbour, 'Index') = provIndex then
      [*] = ;            begin
      [*] = ;               ParserSetIntValueByKeyByHandle(pNeighbour, 'Road', 1);
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if IsRoadAvailable(pProvince) then
      [*] = ;   CheckNeighbours();
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

