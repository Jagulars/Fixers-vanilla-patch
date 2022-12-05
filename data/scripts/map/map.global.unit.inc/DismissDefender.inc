section.begin
   Name = DismissDefender
   Description : struct.begin
      [*] = ;IntRegister0 - province handle
   struct.end
   Code : struct.begin
      [*] = ;
      [*] = ;var pProvince : Integer = IntRegister0;
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\DISMISSDEFENDER';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var myPlIndex : Integer = GetPlayerIndexByHandle(myPlHandle);
      [*] = ;var plKarma : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iKarma);
      [*] = ;
      [*] = ;var pProvDefender : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;var defID : Integer = ParserGetIntValueByKeyByHandle(pProvDefender, 'DefenderID');
      [*] = ;
      [*] = ;if defID = 0 then
      [*] = ;begin
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister0 := defID;
      [*] = ;MapExecuteState('GetDefenderParserByID');
      [*] = ;var pDefender : Integer = IntRegister1;
      [*] = ;
      [*] = ;var canDismiss : Boolean = ParserGetBoolValueByKeyByHandle(pDefender, 'CanDismiss');
      [*] = ;if canDismiss then
      [*] = ;begin
      [*] = ;   var defKarma : Integer = ParserGetIntValueByKeyByHandle(pProvDefender, 'Karma');
      [*] = ;   plKarma := plKarma - defKarma;
      [*] = ;   SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iKarma, plKarma);
      [*] = ;
      [*] = ;   var pProvDefUnits : Integer = ParserSelectByHandleByKey(pProvDefender, 'Units');
      [*] = ;   ParserClearByHandle(pProvDefUnits);
      [*] = ;
      [*] = ;   ParserSetIntValueByKeyByHandle(pProvDefender, 'DefenderID', 0);
      [*] = ;   ParserSetIntValueByKeyByHandle(pProvDefender, 'Initiative', 0);
      [*] = ;
      [*] = ;   IntRegister0 := defID;
      [*] = ;   IntRegister1 := 5;
      [*] = ;   MapExecuteState('CheckDefenderAbility');
      [*] = ;   if IntRegister2 > 0 then
      [*] = ;   begin
      [*] = ;      if myPlIndex = gIntRegister_MapMyPlayerIndex then
      [*] = ;         MapExecuteState('map.DoShowFog')
      [*] = ;      else
      [*] = ;         ExecuteState('CalcFogMap');
      [*] = ;      gBoolRegister_GUIUpdateMapHexGrid := true;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (myPlHandle=GetPlayerHandleInterfaceIO()) then
      [*] = ;      _map_RefreshProvinceHUD(ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID'));
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

