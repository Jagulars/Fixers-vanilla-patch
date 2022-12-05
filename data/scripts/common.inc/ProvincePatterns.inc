section.begin
   Name = ProvincePatterns
   UsedFileName = 
   Description : struct.begin
      [*] = ;Inhabitation scenery, not nature. TerrainScenery for nature.
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\PROVINCEPATTERNS';
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
      [*] = ;   var i, j, pStratHexCell, provHandle : Integer;
      [*] = ;   for i := ParserGetCountByHandle(pStratHexCells)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      pStratHexCell := ParserSelectByHandleByIndex(pStratHexCells, i);
      [*] = ;      provHandle := GetGameObjectHandleByUniqueId(ParserGetIntValueByKeyByHandle(pStratHexCell, 'DummyUID'));
      [*] = ;
      [*] = ;      if provHandle <> 0 then
      [*] = ;      begin
      [*] = ;         if not ParserGetBoolValueByKeyByHandle(pStratHexCell, 'Castle') then
      [*] = ;         begin
      [*] = ;            ParserSetValueByKeyByHandle(pStratHexCell, 'UpdateLevel', '1');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   IntRegister0 := 0;
      [*] = ;   GUIExecuteState('vvk.map.UpdateProvinceHUD');
      [*] = ;end;
      [*] = ;
      [*] = ;if (runFlags and 1) > 0 then ErrorLogI(_log_name+' does not have a Clear method');
      [*] = ;if (runFlags and 2) > 0 then Create();
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

