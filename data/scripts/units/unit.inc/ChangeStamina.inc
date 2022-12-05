section.begin
   Name = ChangeStamina
   Description : struct.begin
      [*] = ;IntRegister0 - value to change
   struct.end
   Code : struct.begin
      [*] = ;var staminaChange : Integer = IntRegister0;
      [*] = ;
      [*] = ;// check for tireless ability
      [*] = ;IntRegister0 := gc_ability_tireless;
      [*] = ;ExecuteState('CheckAbility');
      [*] = ;
      [*] = ;if IntRegister1 = 0 then
      [*] = ;begin
      [*] = ;   var curStamina : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurStamina);
      [*] = ;   var oldStamina : Integer = curStamina;
      [*] = ;   curStamina := curStamina + staminaChange;
      [*] = ;
      [*] = ;   if curStamina < 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := curStamina;
      [*] = ;      ExecuteState('ChangeMoral');
      [*] = ;      curStamina := 0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   IntRegister0 := gc_battle_unit_iMaxStamina;
      [*] = ;   ExecuteState('GetProperty');
      [*] = ;   var maxStamina : Integer = IntRegister1;
      [*] = ;
      [*] = ;   if curStamina > maxStamina then
      [*] = ;      curStamina := maxStamina;
      [*] = ;
      [*] = ;   SetGameObjectMyIntValueInd(gc_stack_unit_iCurStamina, curStamina);
      [*] = ;
      [*] = ;   if oldStamina > curStamina then
      [*] = ;   begin
      [*] = ;      var stUsed : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iStaminaUsed);
      [*] = ;      stUsed := stUsed + (oldStamina - curStamina);
      [*] = ;      SetGameObjectMyIntValueInd(gc_stack_unit_iStaminaUsed, stUsed);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
