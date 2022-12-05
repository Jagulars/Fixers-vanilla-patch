section.begin
   Name = query.MakeFalseAlarm
   Code : struct.begin
      [*] = ;var _log_name : String = 'QUERY\QUERY.MAKEFALSEALARM';
      [*] = ;var _log_trace : Integer = $80000;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;IntRegister0 := 0;
      [*] = ;PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO, 'OrderSabotage');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

