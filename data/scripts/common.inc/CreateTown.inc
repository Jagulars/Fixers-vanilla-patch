section.begin
   Name = CreateTown
   UsedFileName = 
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\CREATETOWN';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;_gv_traceState(_log_name, _log_trace);
      [*] = ;
      [*] = ;const cPlayerName = 'townQuarter';
      [*] = ;const cRaceName = 'buildings';
      [*] = ;const cCMode = 'cmNone';
      [*] = ;
      [*] = ;var plHandle : Integer = _plr_GetOrCreatePlayer(cPlayerName, cRaceName, cCMode, True);
      [*] = ;
      [*] = ;gFloatRegister_TownPositionX := (GetMapWidth / 2) - gc_map_CastleRightX;
      [*] = ;gFloatRegister_TownPositionY := (GetMapHeight / 2) - gc_map_CastleBottomY;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

