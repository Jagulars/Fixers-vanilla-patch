section.begin
   Name = Roads
   UsedFileName = 
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\ROADS';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var runFlags : Integer = IntRegister0;
      [*] = ;
      [*] = ;const cPlayerName = 'signs';
      [*] = ;const cRaceName = 'nature';
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
      [*] = ;procedure Create();
      [*] = ;begin
      [*] = ;   if (uPlHandle=0) then
      [*] = ;      uPlHandle := CreatePlayer(cPlayerName, cRaceName, cCMode);
      [*] = ;
      [*] = ;   var pStratHexCells : Integer = gStratHexCells.handle;
      [*] = ;   var i, pStratHexCell, dummyHandle : Integer;
      [*] = ;
      [*] = ;   for i:=0 to ParserGetCountByHandle(pStratHexCells)-1 do
      [*] = ;   begin
      [*] = ;      pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      dummyHandle := GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pStratHexCell, 'DummyUID'));
      [*] = ;      if dummyHandle <> 0 then
      [*] = ;      begin
      [*] = ;         GameObjectExecuteStateByHandle(dummyHandle, 'CreateRoad');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure Clear();
      [*] = ;begin
      [*] = ;   if (uPlHandle<>0) then
      [*] = ;      ClearPlayerGameObjectsByHandle(uPlHandle);
      [*] = ;
      [*] = ;   var x, y : Float;
      [*] = ;   _map_GetCenterCoord(x, y);
      [*] = ;   var fRadius : Float = GetMapWidth / 2;
      [*] = ;   _map_ClearDecalsInArea(x, y, fRadius, 'map.road');
      [*] = ;
      [*] = ;   var i, j, pStratHexCell, pNeighbours : Integer;
      [*] = ;   var pStratHexCells : Integer = gStratHexCells.handle;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pStratHexCells)-1 do
      [*] = ;   begin
      [*] = ;      pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      pNeighbours := ParserSelectByHandleByKey(pStratHexCell, 'Neighbours');
      [*] = ;
      [*] = ;      for j := 0 to ParserGetCountByHandle(pNeighbours)-1 do
      [*] = ;      begin
      [*] = ;         ParserSetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pNeighbours, j), 'Road', 0);
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

