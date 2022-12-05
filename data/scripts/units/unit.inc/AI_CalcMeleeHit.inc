section.begin
   Name = AI_CalcMeleeHit
   Description : struct.begin
      [*] = ;IntRegister0 - target object handle
      [*] = ;OUT: IntRegister1 - hit value
   struct.end
   Code : struct.begin
      [*] = ;var enGOHandle : Integer = IntRegister0;
      [*] = ;var curLife : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurLife);
      [*] = ;var enResting : Boolean = GetGameObjectBoolValueIndByHandle(enGOHandle, gc_stack_unit_bResting);
      [*] = ;var enCurStamina : Integer = GetGameObjectIntValueIndByHandle(enGOHandle, gc_stack_unit_iCurStamina);
      [*] = ;
      [*] = ;IntRegister0 := gc_ability_first_strike;
      [*] = ;ExecuteState('CheckAbility');
      [*] = ;var abil16 : Integer = IntRegister1;
      [*] = ;
      [*] = ;IntRegister0 := gc_ability_cunning;
      [*] = ;ExecuteState('CheckAbility');
      [*] = ;var abil26 : Integer = IntRegister1;
      [*] = ;
      [*] = ;IntRegister0 := gc_ability_first_strike;
      [*] = ;GameObjectExecuteStateByHandle(enGOHandle, 'CheckAbility');
      [*] = ;var enAbil16 : Integer = IntRegister1;
      [*] = ;
      [*] = ;IntRegister0 := gc_ability_immobilized;
      [*] = ;GameObjectExecuteStateByHandle(enGOHandle, 'CheckAbility');
      [*] = ;var enAbil36 : Integer = IntRegister1;
      [*] = ;
      [*] = ;var value : Integer = 0;
      [*] = ;
      [*] = ;// if the target strikes first
      [*] = ;if (enAbil16 > 0) and (not enResting) and (enAbil36 = 0) and (enCurStamina > 0) and (abil26 = 0) and (abil16 = 0) then
      [*] = ;begin
      [*] = ;   IntRegister0 := GetGameObjectMyHandle();
      [*] = ;   IntRegister1 := -1;
      [*] = ;   BoolRegister0 := true;
      [*] = ;   BoolRegister1 := false;
      [*] = ;   BoolRegister2 := false;
      [*] = ;   BoolRegister3 := true;
      [*] = ;   GameObjectExecuteStateByHandle(enGOHandle, 'GetMeleeHit');
      [*] = ;   if IntRegister2 > curLife then
      [*] = ;      value := -100;
      [*] = ;end;
      [*] = ;
      [*] = ;if value = 0 then
      [*] = ;begin
      [*] = ;   IntRegister0 := enGOHandle;
      [*] = ;   IntRegister1 := -1;
      [*] = ;   BoolRegister0 := true;
      [*] = ;   BoolRegister1 := false;
      [*] = ;   BoolRegister2 := false;
      [*] = ;   BoolRegister3 := true;
      [*] = ;   ExecuteState('GetMeleeHit');
      [*] = ;   value := IntRegister2;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister1 := value;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

