section.begin
   Name = OrderSabotage
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\GLOBAL.INC\ORDERSABOTAGE';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;var sabIndex : Integer = IntRegister0;
      [*] = ;
      [*] = ;if _misc_BattleBothHuman then // sabotage is not processed until both players have placed units.
      [*] = ;begin
      [*] = ;   var pPlacement : Integer = _misc_ParserGetOrCreateByKey('battle_placement', false);
      [*] = ;   var pSabotages : Integer = ParserSelectByHandleByKey(pPlacement, 'Sabotage');
      [*] = ;   if pSabotages = 0 then
      [*] = ;      pSabotages := ParserAddChildByIndex(pPlacement, 'Sabotage');
      [*] = ;   
      [*] = ;   var pSabotage : Integer = ParserAddChildByIndex(pSabotages, '*');
      [*] = ;   ParserSetIntValueByKeyByHandle(pSabotage, 'SabotageIndex', sabIndex);
      [*] = ;   ParserSetIntValueByKeyByHandle(pSabotage, 'PlayerIndex', GetPlayerIndexByHandle(myPlHandle));
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   IntRegister0 := sabIndex;
      [*] = ;   PlayerExecuteStateByHandle(myPlHandle, 'MakeSabotage');
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

