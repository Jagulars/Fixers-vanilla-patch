section.begin
   Name = IsActionsPossible
   Description : struct.begin
      [*] = ;Check whether this object can do any actions this turn (ie he is not dead and not under any ritual influence)
      [*] = ;RET: IntRegister0 = 0 - ritual, < 0 - dead, > 0 actions available
   struct.end
   Code : struct.begin
      [*] = ;if GetBoolValueByIndex(gc_map_GOStack_MapUnit_bIsDead) then
      [*] = ;   IntRegister0 := -1
      [*] = ;else
      [*] = ;begin
      [*] = ;   ExecuteState('CheckFreeze');
      [*] = ;   if BoolRegister0 then
      [*] = ;      IntRegister0 := 0
      [*] = ;   else
      [*] = ;      IntRegister0 := 1;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

