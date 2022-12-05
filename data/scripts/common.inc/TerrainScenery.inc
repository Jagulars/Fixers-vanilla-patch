section.begin
   Name = TerrainScenery
   UsedFileName = 
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\TERRAINSCENERY';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var runFlags : Integer = IntRegister0;
      [*] = ;
      [*] = ;const cPlayerName = 'pattern';
      [*] = ;const cRaceName = 'nature';
      [*] = ;const cCMode = 'cmNone';
      [*] = ;
      [*] = ;var uPlHandle : Integer = GetPlayerHandleByName(cPlayerName);
      [*] = ;
      [*] = ;var sTrace : String = _log_name+'[Run Flags: '+IntToStr(runFlags);
      [*] = ;if (runFlags and 1) > 0 then
      [*] = ;begin 
      [*] = ;   const cWavesPlName = 'plWaves';
      [*] = ;   sTrace := sTrace + ', '+cPlayerName+' OC: '+IntToStr(GetPlayerGameObjectsCountByHandle(uPlHandle));
      [*] = ;   sTrace := sTrace + ', '+cWavesPlName+' OC: '+IntToStr(GetPlayerGameObjectsCountByHandle(GetPlayerHandleByName(cWavesPlName)));
      [*] = ;end;
      [*] = ;sTrace := sTrace +']';
      [*] = ;
      [*] = ;_gv_traceState(sTrace,_log_trace);
      [*] = ;
      [*] = ;procedure Create();
      [*] = ;begin
      [*] = ;   if uPlHandle = 0 then
      [*] = ;      uPlHandle := CreatePlayer(cPlayerName, cRaceName, cCMode);
      [*] = ;
      [*] = ;   ExecuteState('ShardWater');
      [*] = ;   
      [*] = ;   var pStratHexCells : Integer = gStratHexCells.handle;
      [*] = ;   var i, pStratHexCell, provHandle : Integer;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pStratHexCells)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      provHandle := GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pStratHexCell, 'DummyUID'));
      [*] = ;
      [*] = ;      if provHandle <> 0 then
      [*] = ;      begin
      [*] = ;         GameObjectExecuteStateByHandle(provHandle, 'FillTerrainPatterns');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   ExecuteState('WaterScenery');
      [*] = ;   ExecuteState('MountainScenery');
      [*] = ;
      [*] = ;   if (gGame.gameType <> gc_GameTypeLanBattle) and (gGame.gameType <> gc_GameTypeHotseatBattle) and (not (gMapEditor.enabled and gBoolRegister_EditorFastGeneration)) then
      [*] = ;      MapGeneratorSmoothTiles();
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;procedure Clear();
      [*] = ;begin
      [*] = ;   if (uPlHandle<>0) then
      [*] = ;   begin
      [*] = ;      ClearPlayerGameObjectsByHandle(uPlHandle);
      [*] = ;      ClearPlayerGameObjectsByHandle(GetPlayerHandleByName('plWaves'));
      [*] = ;      _map_ClearWaterFieldsByName(gc_WaterNameShardMap);
      [*] = ;      _map_LevelTerrain();
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

