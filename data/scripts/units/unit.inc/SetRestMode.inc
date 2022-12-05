section.begin
   Name = SetRestMode
   Code : struct.begin
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;
      [*] = ;var lanOrderRandKey0, lanOrderRandKey1 : Integer;
      [*] = ;GetRandomExtKey64(lanOrderRandKey0, lanOrderRandKey1);
      [*] = ;
      [*] = ;SetBoolValueByIndex(gc_stack_unit_bResting, true);
      [*] = ;SetBoolValueByIndex(gc_stack_unit_bCanAct, false);
      [*] = ;SetBoolValueByIndex(gc_stack_unit_bCanMelee, false);
      [*] = ;SetBoolValueByIndex(gc_stack_unit_bCanShoot, false);
      [*] = ;SetBoolValueByIndex(gc_stack_unit_bCanCast, false);
      [*] = ;SetIntValueByIndex(gc_stack_unit_iMovePoints, 0);
      [*] = ;SetIntValueByIndex(gc_stack_unit_iActiveAbility, 0);
      [*] = ;SetBoolValueByIndex(gc_stack_unit_bDoubleShot, false);
      [*] = ;SetBoolValueByIndex(gc_stack_unit_bRoundAttack, false);
      [*] = ;SetBoolValueByIndex(gc_stack_unit_bCrush, false);
      [*] = ;SetBoolValueByIndex(gc_stack_unit_bFireBreath, false);
      [*] = ;SetBoolValueByIndex(gc_stack_unit_bPoisonBite, false);
      [*] = ;SetBoolValueByIndex(gc_stack_unit_bAstralStrike, false);
      [*] = ;SetBoolValueByIndex(gc_stack_unit_bLunge, false);
      [*] = ;gIntRegister_CurSpell := 0;
      [*] = ;
      [*] = ;if myPlHandle = GetPlayerHandleInterfaceIO() then
      [*] = ;begin
      [*] = ;   gIntRegister_MapPickedSpellID := 0;
      [*] = ;   gIntRegister_CurSpellIndex := -1;
      [*] = ;   gIntRegister_SacrificeUID := 0;
      [*] = ;   gIntRegister_TeleportUID := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;if GetIntValueByIndex(gc_stack_unit_iCurStamina) > 0 then // only send parser on voluntary rest
      [*] = ;   _inet_CreateOrderParser(GetGameObjectUniqueIdByHandle(myGOHandle), -1, -1, gc_inet_actiontype_rest, 0, 0, 0, 0, lanOrderRandKey0, lanOrderRandKey1,'SetRestMode');
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

