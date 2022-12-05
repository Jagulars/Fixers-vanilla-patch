section.begin
   Name = GoMarch
   Code : struct.begin
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var abil29 : Integer = _unit_CheckAbility(myGOHandle, gc_ability_march);
      [*] = ;
      [*] = ;if abil29 > 0 then
      [*] = ;begin
      [*] = ;   var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;   var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;   var lanOrderRandKey0, lanOrderRandKey1 : Integer;
      [*] = ;
      [*] = ;   GetRandomExtKey64(lanOrderRandKey0, lanOrderRandKey1);
      [*] = ;
      [*] = ;   IntRegister0 := -abil29;
      [*] = ;   ExecuteState('ChangeStamina');
      [*] = ;
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iMovePoints, GetIntValueByIndex(gc_stack_unit_iMovePoints) + 1);
      [*] = ;
      [*] = ;   _fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryAbility, gc_ability_march, 0);
      [*] = ;
      [*] = ;   SetBoolValueByIndex(gc_stack_unit_bCanMarch, false);
	  [*] = ;   SetBoolValueByIndex(gc_stack_unit_bActionTaken, true);
      [*] = ;
      [*] = ;   _inet_CreateOrderParser(myUID, -1, -1, gc_inet_actiontype_activateability, 0, gc_ability_march, 0, 0, lanOrderRandKey0, lanOrderRandKey1,'GoMarch');
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

