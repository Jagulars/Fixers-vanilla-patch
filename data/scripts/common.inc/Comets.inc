section.begin
   Name = Comets
   UsedFileName =
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\COMETS';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var runFlags : Integer = IntRegister0;
      [*] = ;
      [*] = ;const cPlayerName = 'mapPlMeteors';
      [*] = ;const cRaceName = 'misc';
      [*] = ;const cCMode = 'cmPlayer'; // to progress outside view
      [*] = ;
      [*] = ;var uPlHandle : Integer = GetPlayerHandleByName(cPlayerName);
      [*] = ;
      [*] = ;var sTrace : String = _log_name+'[Run Flags: '+IntToStr(runFlags);
      [*] = ;if (runFlags and 1) > 0 then sTrace := sTrace + ', '+cPlayerName+' OC: '+IntToStr(GetPlayerGameObjectsCountByHandle(uPlHandle));
      [*] = ;sTrace := sTrace +']';
      [*] = ;
      [*] = ;_gv_traceState(sTrace,_log_trace);
      [*] = ;
      [*] = ;const cCometCount = 5;
      [*] = ;const cCometBaseName = 'mapcomet';
      [*] = ;
      [*] = ;procedure Create();
      [*] = ;begin
      [*] = ;   if (uPlHandle=0) then
      [*] = ;      uPlHandle := CreatePlayer(cPlayerName, cRaceName, cCMode);
      [*] = ;
      [*] = ;   var i : Integer;
      [*] = ;   var goHandle : Integer;
      [*] = ;   for i:=0 to cCometCount-1 do
      [*] = ;   begin
      [*] = ;      goHandle := CreatePlayerGameObjectHandle(cPlayerName, cRaceName, cCometBaseName, 0, 0, 0);
      [*] = ;      SetGameObjectUseNoSPCullByHandle(goHandle, True);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure Clear();
      [*] = ;begin
      [*] = ;   if (uPlHandle<>0) then
      [*] = ;      ClearPlayerGameObjectsByHandle(uPlHandle);
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
