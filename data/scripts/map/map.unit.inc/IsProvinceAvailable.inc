section.begin
   Name = IsProvinceAvailable
   Description : struct.begin
      [*] = ;IntRegister0 - province parser
      [*] = ;OUT: BoolRegister0 - is province available
   struct.end
   Code : struct.begin
      [*] = ;var pProvince : Integer = IntRegister0;
      [*] = ;var pathNeeded : Boolean = {BoolRegister0}true;
      [*] = ;
      [*] = ;var _log_name : String = 'MAP\MAP.UNIT.INC\ISPROVINCEAVAILABLE';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var myHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myHandle);
      [*] = ;var myPlName : String = GetPlayerNameByHandle(myPlHandle);
      [*] = ;
      [*] = ;var pHeroProvince : Integer = _misc_GetProvinceParserByUID(GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iCurrentUID));
      [*] = ;var startInd : Integer = ParserGetIntValueByKeyByHandle(pHeroProvince, 'Index');
      [*] = ;var tnStart : Integer = GetTrackNodeHandleByIndex(startInd);
      [*] = ;
      [*] = ;var action : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iActionType);
      [*] = ;
      [*] = ;var i, j : Integer;
      [*] = ;var isAvailable : Boolean = true;
      [*] = ;
      [*] = ;var endInd : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'Index');
      [*] = ;var tnEndHandle : Integer = GetTrackNodeHandleByIndex(endInd);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[A:'+IntToStr(action)+']',_log_trace);
      [*] = ;if action = gc_UnitTaskSiege then
      [*] = ;begin
      [*] = ;   isAvailable := false;
      [*] = ;   var count : Integer = GetTrackNodeNeighboursCountByHandle(tnStart);
      [*] = ;
      [*] = ;   for j := 0 to count-1 do
      [*] = ;   begin
      [*] = ;      var tnHandle : Integer = GetTrackNodeNeighbourHandleByHandleByIndex(tnStart, j);
      [*] = ;      if tnHandle = tnEndHandle then
      [*] = ;      begin
      [*] = ;         var tnX, tnY, tnZ : Float;
      [*] = ;         GetTrackNodePositionByHandle(tnHandle, tnX, tnY, tnZ);
      [*] = ;
      [*] = ;         FloatRegister0 := tnX;
      [*] = ;         FloatRegister1 := tnZ;
      [*] = ;         MapExecuteState('map.GetHexByCoord');
      [*] = ;         var pProvince : Integer = IntRegister0;
      [*] = ;
      [*] = ;         var provPlayer : String = ParserGetValueByKeyByHandle(pProvince, 'Player');
      [*] = ;         if SameText(provPlayer, myPlName) then
      [*] = ;         begin
      [*] = ;            isAvailable := true;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if (tnEndHandle <> 0) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := gc_map_hero_iMobility;
      [*] = ;      ExecuteState('GetProperty');
      [*] = ;      var speed : Integer = IntRegister1;
      [*] = ;
      [*] = ;      var moveMap : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'MoveMap');
      [*] = ;
      [*] = ;      //if not path then
      [*] = ;      if moveMap < 0 then
      [*] = ;         isAvailable := false
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var tpCount : Integer = GetTrackNodeTPCount();
      [*] = ;         var dist : Integer = 0;
      [*] = ;
      [*] = ;         for j := tpCount-1 downto 1 do
      [*] = ;         begin
      [*] = ;            var tnX, tnZ : Float;
      [*] = ;            GetTrackNodeTPByIndex(j, tnX, tnZ);
      [*] = ;            var tnHandle : Integer = GetNearestTrackNodeHandle(tnX, tnZ, -1);
      [*] = ;            dist := dist + Round(GetTrackNodeDistFactorByHandle(tnHandle));
      [*] = ;         end;
      [*] = ;
      [*] = ;         _gui_ProgressCalculations(_log_name+' UID: '+IntToStr(ParserGetIntValueByKeyByHandle(pProvince,'DummyUID'))+', Distance = ' + IntToStr(dist));
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      isAvailable := false;
      [*] = ;end;
      [*] = ;
      [*] = ;if gTutorial.map then
      [*] = ;begin
      [*] = ;   IntRegister0 := pProvince;
      [*] = ;   ExecuteState('CheckTutorialProvRestrict');
      [*] = ;   isAvailable := isAvailable and (not BoolRegister0);
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+BoolToStr(isAvailable)+']',$1000000 or _log_trace);
      [*] = ;
      [*] = ;BoolRegister0 := isAvailable;
   struct.end
section.end

