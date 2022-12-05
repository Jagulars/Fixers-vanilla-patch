section.begin
   Name = DismissUnit
   Description : struct.begin
      [*] = ;IntRegister0 - army parser
      [*] = ;IntRegister1 - unit index
   struct.end
   Code : struct.begin
      [*] = ;var pArmyUnits : Integer = IntRegister0;
      [*] = ;var index : Integer = IntRegister1;
      [*] = ;
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\DISMISSUNIT';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var pUnit : Integer = ParserSelectByHandleByIndex(pArmyUnits, index);
      [*] = ;if (pUnit<>0) then
      [*] = ;begin
      [*] = ;   var myPlHandle : Integer = GetPlayerCurrentPlHandle;
      [*] = ;
      [*] = ;   IntRegister0 := 24;
      [*] = ;   ExecuteState('CheckInnerBuildAbility');
      [*] = ;   if (IntRegister1>0) and ((gIntRegister_MapTurnIteration <> 1) or SameText(GetPlayerControlModeByHandle(myPlHandle), 'cmPC')) then // no selling units during encounters 
      [*] = ;   begin
      [*] = ;      var plGold : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;      IntRegister0 := ParserGetIntValueByKeyByHandle(pUnit, 'UnitID');
      [*] = ;      IntRegister1 := ParserGetIntValueByKeyByHandle(pUnit, 'Level');
      [*] = ;      ExecuteState('GetSellUnitPrice');
      [*] = ;      var gold : Integer = IntRegister2;
      [*] = ;      plGold := plGold + gold;
      [*] = ;      SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGold, plGold);
      [*] = ;      _gui_ProgressCalculations(_log_name+' Sold unit gold refund = ' + IntToStr(gold));
      [*] = ;
      [*] = ;      //plGold := GetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldGain);
      [*] = ;      //SetPlayerIntValueIndByHandle(myPlHandle, gc_map_PLStack_MapUnit_iGoldGain, plGold + gold);
      [*] = ;      
      [*] = ;      if _stats_IsEligible(myPlHandle) then _stats_SimpleUpdate('Gold', 'UnitsSold', gold);
      [*] = ;   end;
      [*] = ;
      [*] = ;   ParserFreeByHandle(pUnit);
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end
