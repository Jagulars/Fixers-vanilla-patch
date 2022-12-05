section.begin
   Name = SwitchStealthModeFlag
   Code : struct.begin
      [*] = ;var sendParser : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;var lanOrderRandKey0, lanOrderRandKey1 : Integer;
      [*] = ;var bStealthMode : Boolean = GetBoolValueByIndex(gc_stack_unit_bStealthMode);
      [*] = ;var f : Integer;
      [*] = ;
      [*] = ;GetRandomExtKey64(lanOrderRandKey0, lanOrderRandKey1);
      [*] = ;
      [*] = ;if not bStealthMode then
      [*] = ;begin
      [*] = ;   IntRegister0 := -1 * _unit_CheckAbility(myGOHandle, gc_ability_stealth);
      [*] = ;   ExecuteState('ChangeStamina');
      [*] = ;end;
      [*] = ;
      [*] = ;bStealthMode := not bStealthMode;
      [*] = ;SetBoolValueByIndex(gc_stack_unit_bStealthMode, bStealthMode);
      [*] = ;
      [*] = ;if sendParser then
      [*] = ;   _inet_CreateOrderParser(myUID, -1, -1, gc_inet_actiontype_activateability, 0, gc_ability_stealth, 0, 0, lanOrderRandKey0, lanOrderRandKey1,'SwitchStealthModeFlag');
      [*] = ;
      [*] = ;if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;begin
      [*] = ;   if bStealthMode then
      [*] = ;      _fx_CreateAlphaFadeEffect(myGOHandle, 1, 1, 0.6, 'Stealth')
      [*] = ;   else
      [*] = ;      _fx_DestroyAlphaFadeEffect(myGOHandle, 1, 1, 'Stealth');
      [*] = ;
      [*] = ;   if bStealthMode then f := 1
      [*] = ;   else f := -1;
      [*] = ;
      [*] = ;   _fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryAbility, gc_ability_stealth, f);
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

