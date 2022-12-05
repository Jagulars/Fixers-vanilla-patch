section.begin
   Name = ProvinceFX
   UsedFileName = 
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\PROVINCEFX';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var runFlags : Integer = IntRegister0;
      [*] = ;
      [*] = ;const cPlayerName = 'particles';
      [*] = ;const cRaceName = 'misc';
      [*] = ;const cCMode = 'cmPC';  //cmPC to progress state machine
      [*] = ;
      [*] = ;var uPlHandle : Integer = GetPlayerHandleByName(cPlayerName);
      [*] = ;
      [*] = ;var sTrace : String = _log_name+'[Run Flags: '+IntToStr(runFlags);
      [*] = ;if (runFlags and 1) > 0 then sTrace := sTrace + ', '+cPlayerName+' OC: '+IntToStr(GetPlayerGameObjectsCountByHandle(uPlHandle));
      [*] = ;sTrace := sTrace +']';
      [*] = ;
      [*] = ;_gv_traceState(sTrace,_log_trace);
      [*] = ;
      [*] = ;const cFogBaseName = 'swampfog';
      [*] = ;const cFogCrystalBaseName = 'swampcrystalsfog';
      [*] = ;const cFirebugBaseName = 'firebug';
      [*] = ;const cFirebugCrystalBaseName = 'firebugcrystal';
      [*] = ;const cSandBaseName = 'desertsand';
      [*] = ;
      [*] = ;
      [*] = ;procedure Create();
      [*] = ;begin
      [*] = ;   if (uPlHandle=0) then
      [*] = ;      uPlHandle := CreatePlayer(cPlayerName, cRaceName, cCMode);
      [*] = ;
      [*] = ;   var pStratHexCells : Integer = gStratHexCells.handle;
      [*] = ;   var hexCount : Integer = ParserGetCountByHandle(pStratHexCells);
      [*] = ;   var goHnd : Integer;
      [*] = ;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to hexCount-1 do
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      var TerrainType : Integer = ParserGetIntValueByKeyByHandle(pStratHexCell, 'TerrainType');
      [*] = ;      if TerrainType = gc_SwampTerrainType then
      [*] = ;      begin
      [*] = ;         var posX, posY, posZ : Float;
      [*] = ;         posX := ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterX');
      [*] = ;         posZ := ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterY');
      [*] = ;         posY := RayCastHeight(posX, posZ)+1.5;
      [*] = ;
      [*] = ;         var fogBaseName : String = cFogBaseName;
      [*] = ;         var firebugBaseName : String = cFirebugBaseName;
      [*] = ;
      [*] = ;         // world rule
      [*] = ;         if (_worldrule_GetWorldRuleVisualExistByID(2)) then
      [*] = ;         begin
      [*] = ;            if (_worldrule_GetWorldRuleVisualParams(2, 1)=1) then
      [*] = ;            begin
      [*] = ;               fogBaseName := cFogCrystalBaseName;
      [*] = ;               firebugBaseName := cFirebugCrystalBaseName;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         goHnd := CreatePlayerGameObjectHandle(cPlayerName, cRaceName, fogBaseName, posX, posY, posZ+1);
      [*] = ;
      [*] = ;         var j : Integer;
      [*] = ;         var count : Integer = 1;
      [*] = ;
      [*] = ;         // world rule
      [*] = ;         if (_worldrule_GetWorldRuleVisualExistByID(1)) then
      [*] = ;         count := _worldrule_GetWorldRuleVisualParams(1, 1);
      [*] = ;
      [*] = ;         for j:=0 to count-1 do
      [*] = ;         begin
      [*] = ;            var rndAngle : Float = Random*360;
      [*] = ;            var rndLenght : Float = Lerp(3, 4, Random);
      [*] = ;            var dirX, dirY, dirZ : Float;
      [*] = ;            dirX := rndLenght;
      [*] = ;            dirY := 0;
      [*] = ;            dirZ := 0;
      [*] = ;            VectorRotateY(dirX, dirY, dirZ, rndAngle);
      [*] = ;
      [*] = ;            goHnd := CreatePlayerGameObjectHandle(cPlayerName, cRaceName, firebugBaseName, posX+dirX, posY, posZ+dirZ);
      [*] = ;
      [*] = ;            var tCount : Integer = 6;
      [*] = ;            var angleStep : Float = 360/tCount;
      [*] = ;            var j : Integer;
      [*] = ;            for j:=0 to tCount-1 do
      [*] = ;            begin
      [*] = ;               dirX := rndLenght;
      [*] = ;               dirY := 0;
      [*] = ;               dirZ := 0;
      [*] = ;               VectorRotateY(dirX, dirY, dirZ, rndAngle+angleStep*j);
      [*] = ;               GameObjectTrackPointAddByHandle(goHnd, posX+dirX, RayCastHeight(posX+dirX, posZ+dirZ), posZ+dirZ);
      [*] = ;            end;
      [*] = ;
      [*] = ;            SetGameObjectTrackPointMoveStepIntervalByHandle(goHnd, 500);
      [*] = ;            SetGameObjectTrackPointTurnStepIntervalByHandle(goHnd, 2);
      [*] = ;            SetGameObjectTrackPointCurrentPointIndexByHandle(goHnd, 0);
      [*] = ;            SetGameObjectTrackPointMovementModeByHandle(goHnd, 'mmDoTrackListLoop');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      if TerrainType = gc_DesertTerrainType then
      [*] = ;      begin
      [*] = ;         var posX, posY, posZ : Float;
      [*] = ;         posX := ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterX');
      [*] = ;         posZ := ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterY');
      [*] = ;         posY := RayCastHeight(posX, posZ)+1.5;
      [*] = ;         goHnd := CreatePlayerGameObjectHandle(cPlayerName, cRaceName, cSandBaseName, posX, posY, posZ);
      [*] = ;         //GameObjectExecuteStateByHandle(goHnd, 'initial');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure Clear();
      [*] = ;begin
      [*] = ;   var i, goHandle : Integer;
      [*] = ;   var baseName : String;
      [*] = ;   for i := GetPlayerGameObjectsCountByHandle(uPlHandle)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      goHandle := GetGameObjectHandleByIndex(i, uPlHandle);
      [*] = ;      baseName := GetGameObjectBaseNameByHandle(goHandle);
      [*] = ;      if SameText(baseName, cFogBaseName) or SameText(baseName, cFogCrystalBaseName) or SameText(baseName, cFirebugBaseName) or SameText(baseName, cFirebugCrystalBaseName) or SameText(baseName, cSandBaseName) then
      [*] = ;      begin
      [*] = ;         GameObjectDestroyByHandle(goHandle);
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

