section.begin
   Name = AI_CalcRangedHit
   Description : struct.begin
      [*] = ;IntRegister0 - target object handle
      [*] = ;OUT: IntRegister1 - hit value
   struct.end
   Code : struct.begin
      [*] = ;BoolRegister0 := true;
      [*] = ;ExecuteState('GetRangedHit');
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

