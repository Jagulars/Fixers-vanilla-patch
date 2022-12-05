section.begin
   Name = ClearProvinceScenery
   UsedFileName = 
   Description : struct.begin
      [*] = ;Inhabitation/government related scenery, not nature. TerrainScenery for nature.
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\CLEARPROVINCESCENERY';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var runFlags : Integer = IntRegister0;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[Run Flags: '+IntToStr(runFlags)+']',_log_trace);
      [*] = ;
      [*] = ;const cPlayerName = 'prov.pattern';
      [*] = ;const cRaceName = 'buildings';
      [*] = ;const cCMode = 'cmNone';
      [*] = ;
      [*] = ;var uPlHandle : Integer = GetPlayerHandleByName(cPlayerName);
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
      [*] = ;if (runFlags and 2) > 0 then ErrorLogI(_log_name+' does not have a Create method');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

