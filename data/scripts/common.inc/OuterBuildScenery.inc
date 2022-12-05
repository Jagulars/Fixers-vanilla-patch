section.begin
   Name = OuterBuildScenery
   UsedFileName = 
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\OUTERBUILDSCENERY';
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
      [*] = ;var pStratHexCells : Integer = gStratHexCells.handle;
      [*] = ;
      [*] = ;procedure Create();
      [*] = ;begin
      [*] = ;   if uPlHandle = 0 then
      [*] = ;      uPlHandle := CreatePlayer(cPlayerName, cRaceName, cCMode);
      [*] = ;   
      [*] = ;   // create outer build models
      [*] = ;   var i, j, pStratHexCell, provHandle, pProvOuterBuildings, pProvOuterBuilding, buildID : Integer;
      [*] = ;   for i := ParserGetCountByHandle(pStratHexCells)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      provHandle := GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pStratHexCell, 'DummyUID'));
      [*] = ;
      [*] = ;      if (provHandle <> 0) and (not ParserGetBoolValueByKeyByHandle(pStratHexCell, 'Castle')) then
      [*] = ;      begin
      [*] = ;         pProvOuterBuildings := ParserSelectByHandleByKey(pStratHexCell, 'OuterBuildings');
      [*] = ;         if pProvOuterBuildings <> 0 then
      [*] = ;         for j := 0 to 2 do 
      [*] = ;         begin
      [*] = ;            pProvOuterBuilding := ParserSelectByHandleByIndex(pProvOuterBuildings, j);
      [*] = ;            buildID := ParserGetIntValueByKeyByHandle(pProvOuterBuilding, 'OuterBuildID');
      [*] = ;            if buildID > 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := buildID;
      [*] = ;               IntRegister1 := j;
      [*] = ;               BoolRegister0 := False;
      [*] = ;               GameObjectExecuteStateByHandle(provHandle, 'CreateOuterBuildModel');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (runFlags and 1) > 0 then ErrorLogI(_log_name+' does not have a Clear method');
      [*] = ;if (runFlags and 2) > 0 then Create();
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

