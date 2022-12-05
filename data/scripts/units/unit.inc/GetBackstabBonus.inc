section.begin
   Name = GetBackstabBonus
   Description : struct.begin
      [*] = ;IntRegister0 - target uid
      [*] = ;IntRegister1 - sector (-3 - +3) (3-facing each other,0-backstab strike)
      [*] = ;RET: IntRegister0 - backstab bonus
   struct.end
   Code : struct.begin
      [*] = ;var sector : Integer = IntRegister1;
      [*] = ;var bb : Integer = 0;
      [*] = ;
      [*] = ;if (not _map_CheckGenesisMode(gc_GM_RearAttack)) and (_unit_CheckAbility(GetGameObjectHandleByUniqueId( IntRegister0 ), gc_ability_backstab_immunity) = 0) then
      [*] = ;begin
      [*] = ;   case round(abs(sector)) of
      [*] = ;      0 : bb := gc_BackstabBonus;
      [*] = ;      1 : bb := gc_SidestabBonus;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister0 := bb;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
