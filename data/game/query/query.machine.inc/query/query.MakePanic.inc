section.begin
   Name = query.MakePanic
   Code : struct.begin
      [*] = ;var _log_name : String = 'QUERY\QUERY.MAKEPANIC';
      [*] = ;var _log_trace : Integer = $80000;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;IntRegister0 := 2;
      [*] = ;PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO, 'OrderSabotage');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

