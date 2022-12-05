section.begin
   Name = DoPathStaminaCharge
   UsedFileName = 
   Code : struct.begin
      [*] = ;var oldLife : Integer = GetIntValueByIndex(gc_stack_unit_iCurLife);
      [*] = ;var oldStamina : Integer = GetIntValueByIndex(gc_stack_unit_iCurStamina);
      [*] = ;var oldMoral : Integer = GetIntValueByIndex(gc_stack_unit_iCurMoral);
      [*] = ;
      [*] = ;ExecuteState('GetPathStaminaCharge');
      [*] = ;var charge : Integer = IntRegister0;
      [*] = ;IntRegister0 := -charge;
      [*] = ;ExecuteState('ChangeStamina');
      [*] = ;
      [*] = ;if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;begin
      [*] = ;   var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;   _unit_SetupStatsTextData(myGOHandle, GetGameObjectUniqueIdByHandle(myGOHandle), oldLife, oldStamina, oldMoral);
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
