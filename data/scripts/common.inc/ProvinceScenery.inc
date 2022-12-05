section.begin
   Name = ProvinceScenery
   UsedFileName = 
   Description : struct.begin
      [*] = ;Inhabitation/government related scenery, not nature. TerrainScenery for nature.
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\PROVINCESCENERY';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var runFlags : Integer = IntRegister0;
      [*] = ;
      [*] = ;const cPlayerName = 'prov.pattern';
      [*] = ;const cRaceName = 'buildings';
      [*] = ;const cCMode = 'cmNone';
      [*] = ;
      [*] = ;var uPlHandle : Integer = GetPlayerHandleByName(cPlayerName);
      [*] = ;
      [*] = ;var sTrace : String = _log_name+'[Run Flags: '+IntToStr(runFlags);
      [*] = ;if (runFlags and 1) > 0 then sTrace := sTrace + ', '+cPlayerName+' OC: '+IntToStr(GetPlayerGameObjectsCountByHandle(uPlHandle));
      [*] = ;sTrace := sTrace +']';
      [*] = ;
      [*] = ;_gv_traceState(sTrace,_log_trace);
      [*] = ;
      [*] = ;var pStratHexCells : Integer = gStratHexCells.handle;
      [*] = ;
      [*] = ;procedure StandPatternAndGroup(const pStratHexCell : Integer; const patternName : String; const x, y, angle : Float);
      [*] = ;begin
      [*] = ;   var i, goHandle : Integer;
      [*] = ;   var uid : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'DummyUID');
      [*] = ;
      [*] = ;   var goCount : Integer = GetPlayerGameObjectsCountByHandle(uPlHandle);
      [*] = ;   StandPattern(uPlHandle, patternName, x, y, angle);
      [*] = ;   var grName : String = 'group.prov.' + IntToStr(uid);
      [*] = ;   var grHandle : Integer = GetPlayerGrHandleByHandle(uPlHandle, grName);
      [*] = ;   if grHandle = 0 then
      [*] = ;       grHandle := CreateGroupByPlHandle(uPlHandle, grName);
      [*] = ;
      [*] = ;   for i := GetPlayerGameObjectsCountByHandle(uPlHandle)-1 downto goCount do
      [*] = ;   begin
      [*] = ;      goHandle := GetGameObjectHandleByIndex(i, uPlHandle);
      [*] = ;      GroupAddGameObjectByHandle(grHandle, goHandle);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var dummyHnd : Integer = GetGameObjectHandleByUniqueId(uid);
      [*] = ;   BoolRegister0 := false;
      [*] = ;   FloatRegister0 := 0;
      [*] = ;   GameObjectExecuteStateByHandle(dummyHnd, 'HideShowObjects');
      [*] = ;   ParserSetValueByKeyByHandle(pStratHexCell, 'PatternGroup', grName);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure Create();
      [*] = ;begin
      [*] = ;   if uPlHandle = 0 then
      [*] = ;      uPlHandle := CreatePlayer(cPlayerName, cRaceName, cCMode);
      [*] = ;   
      [*] = ;   var i, j, pStratHexCell, provHandle, pProvOuterBuildings, pProvOuterBuilding, buildID : Integer;
      [*] = ;   for i := ParserGetCountByHandle(pStratHexCells)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      provHandle := GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pStratHexCell, 'DummyUID'));
      [*] = ;
      [*] = ;      if provHandle <> 0 then
      [*] = ;      begin
      [*] = ;         if ParserGetBoolValueByKeyByHandle(pStratHexCell, 'Castle') then
      [*] = ;         begin
      [*] = ;            StandPatternAndGroup(pStratHexCell, 'castle', ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterX'), ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterY'), 0);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            ParserSetValueByKeyByHandle(pStratHexCell, 'UpdateLevel', '1');
      [*] = ;            
      [*] = ;            if gProfile.provincescenery < gc_OuterBuildSceneryLimit then // hate to do it this way but more sophisticated systems cause too much brain damage with invalid floating point operation and access violation errors. I'll just accept that prov.pattern -player can't be split and ProvinceScenery.inc can't be split.
      [*] = ;            begin
      [*] = ;               pProvOuterBuildings := ParserSelectByHandleByKey(pStratHexCell, 'OuterBuildings');
      [*] = ;               if pProvOuterBuildings <> 0 then
      [*] = ;               for j := 0 to 2 do 
      [*] = ;               begin
      [*] = ;                  pProvOuterBuilding := ParserSelectByHandleByIndex(pProvOuterBuildings, j);
      [*] = ;                  buildID := ParserGetIntValueByKeyByHandle(pProvOuterBuilding, 'OuterBuildID');
      [*] = ;                  if buildID > 0 then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := buildID;
      [*] = ;                     IntRegister1 := j;
      [*] = ;                     BoolRegister0 := False;
      [*] = ;                     GameObjectExecuteStateByHandle(provHandle, 'CreateOuterBuildModel');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   IntRegister0 := 0;
      [*] = ;   GUIExecuteState('vvk.map.UpdateProvinceHUD');
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;procedure Clear();
      [*] = ;begin
      [*] = ;   if (uPlHandle<>0) then
      [*] = ;   begin
      [*] = ;      ClearPlayerGameObjectsByHandle(uPlHandle); // clears all player objects from groups they belong in as well.
      [*] = ;      
      [*] = ;      var pStratHexCells : Integer = gStratHexCells.handle;
      [*] = ;      var i, pStratHexCell, dummyUID, provHandle : Integer;
      [*] = ;      
      [*] = ;      for i := ParserGetCountByHandle(pStratHexCells)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;         dummyUID := ParserGetIntValueByKeyByHandle(pStratHexCell, 'DummyUID');
      [*] = ;         provHandle := GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;         if provHandle <> 0 then
      [*] = ;         begin
      [*] = ;            BoolRegister0 := True;
      [*] = ;            FloatRegister0 := 0;
      [*] = ;            GameObjectExecuteStateByHandle(provHandle, 'HideShowObjects');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      
      [*] = ;      var x, y : Float;
      [*] = ;      _map_GetCenterCoord(x, y);
      [*] = ;      var fRadius : Float = GetMapWidth / 2;
      [*] = ;      _map_ClearDecalsInArea(x, y, fRadius, 'torch');
      [*] = ;      
      [*] = ;      for i := 0 to gc_MaxPrunerObjects-1 do
      [*] = ;      begin
      [*] = ;         gProvinceSceneryPruner[i].baseName := '';
      [*] = ;         gProvinceSceneryPruner[i].frequency := 0;
      [*] = ;         gProvinceSceneryPruner[i].count := 0;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (runFlags and 1) > 0 then Clear();
      [*] = ;if (runFlags and 2) > 0 then Create();
      [*] = ;
      [*] = ;sTrace := _log_name;
      [*] = ;if (runFlags and 2) > 0 then sTrace := sTrace + '['+cPlayerName+' OC: '+IntToStr(GetPlayerGameObjectsCountByHandle(uPlHandle))+']';
      [*] = ;
      [*] = ;_gv_traceState(sTrace, $1000000 or _log_trace);
   struct.end
section.end

