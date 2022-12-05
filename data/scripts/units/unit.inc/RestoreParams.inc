section.begin
   Name = RestoreParams 
   UsedFileName = 
   Code : struct.begin
      [*] = ;IntRegister0 := gc_battle_unit_iMaxLife;
      [*] = ;ExecuteState('GetProperty');
      [*] = ;if GetIntValueByIndex(gc_stack_unit_iCurLife) < IntRegister1 then
      [*] = ;SetIntValueByIndex(gc_stack_unit_iCurLife, IntRegister1);
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iMaxStamina;
      [*] = ;ExecuteState('GetProperty');
      [*] = ;SetIntValueByIndex(gc_stack_unit_iCurStamina, IntRegister1);
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iMaxMoral;
      [*] = ;ExecuteState('GetProperty');
      [*] = ;SetIntValueByIndex(gc_stack_unit_iCurMoral, IntRegister1);
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iMaxAmmo;
      [*] = ;ExecuteState('GetProperty');
      [*] = ;SetIntValueByIndex(gc_stack_unit_iCurAmmo, IntRegister1);
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iSpeed;
      [*] = ;ExecuteState('GetProperty');
      [*] = ;SetIntValueByIndex(gc_stack_unit_iMovePoints, IntRegister1);
      [*] = ;
      [*] = ;SetBoolValueByIndex(gc_stack_unit_bCanAct, true);
      [*] = ;SetBoolValueByIndex(gc_stack_unit_bCanMelee, true);
      [*] = ;SetBoolValueByIndex(gc_stack_unit_bCanShoot, true);
      [*] = ;SetBoolValueByIndex(gc_stack_unit_bCanCast, true);
      [*] = ;SetBoolValueByIndex(gc_stack_unit_bResting, false);
      [*] = ;SetBoolValueByIndex(gc_stack_unit_bActionTaken, false);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
