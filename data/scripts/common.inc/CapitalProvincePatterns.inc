section.begin
   Name = CapitalProvincePatterns
   UsedFileName = 
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\CAPITALPROVINCEPATTERNS';
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
      [*] = ;   var i, pStratHexCell : Integer;
      [*] = ;   for i := ParserGetCountByHandle(pStratHexCells)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      if ParserGetBoolValueByKeyByHandle(pStratHexCell, 'Castle') then
      [*] = ;         StandPatternAndGroup(pStratHexCell, 'castle', ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterX'), ParserGetFloatValueByKeyByHandle(pStratHexCell, 'CenterY'), 0);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (runFlags and 1) > 0 then ErrorLogI(_log_name+' does not have a Clear method');
      [*] = ;if (runFlags and 2) > 0 then Create();
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

