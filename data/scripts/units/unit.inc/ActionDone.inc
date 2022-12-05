section.begin
   Name = ActionDone
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\ACTIONDONE';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;SetGameObjectMyIntValueInd(gc_stack_unit_iActiveAbility, 0);
      [*] = ;SetGameObjectMyBoolValueInd(gc_stack_unit_bActionTaken, true);
      [*] = ;SetGameObjectMyBoolValueInd(gc_stack_unit_bResting, false);
      [*] = ;SetGameObjectMyBoolValueInd(gc_stack_unit_bCanAct, false);
      [*] = ;SetGameObjectMyBoolValueInd(gc_stack_unit_bCanMelee, false);
      [*] = ;SetGameObjectMyBoolValueInd(gc_stack_unit_bCanShoot, false);
      [*] = ;SetGameObjectMyBoolValueInd(gc_stack_unit_bCanCast, false);
      [*] = ;SetGameObjectMyIntValueInd(gc_stack_unit_iMovePoints, 0);
      [*] = ;SetGameObjectMyBoolValueInd(gc_stack_unit_bCanMarch, false);
      [*] = ;_unit_GUIUpdateUnitHUD(GetGameObjectMyHandle);
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
