section.begin
   Name = AIHeroLevelUp
   Code : struct.begin
      [*] = ;var level : Integer = GetIntValueByIndex(gc_map_GOStack_MapUnit_iLevel) + 1;
      [*] = ;
      [*] = ;if level = 10 then
      [*] = ;begin
      [*] = ;   var allowedHeroes : Integer = gGame.allowedheroes;
      [*] = ;   var class1 : Integer = GetIntValueByIndex(gc_map_GOStack_MapUnit_iClassInd1);
      [*] = ;   
      [*] = ;   var ind, i, checkFlagNumber : Integer;
      [*] = ;   _rand_ClearRoll();
      [*] = ;   for i := 1 to 4 do
      [*] = ;   begin
      [*] = ;      checkFlagNumber := _misc_GetBitFlagByIndex((class1-1) * 4 + i-1);
      [*] = ;      
      [*] = ;      if ((allowedHeroes and checkFlagNumber) = 0) then
      [*] = ;      begin
      [*] = ;         gArrRollerN[ind] := i;
      [*] = ;         gArrRollerP[ind] := 10;
      [*] = ;         ind := ind + 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   SetIntValueByIndex(gc_map_GOStack_MapUnit_iClassInd2, _rand_Roll(false));
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister0 := -1;
      [*] = ;IntRegister1 := -1;
      [*] = ;ExecuteState('GetRandomSkill');
      [*] = ;
      [*] = ;IntRegister0 := IntRegister2;
      [*] = ;BoolRegister0 := true;
      [*] = ;ExecuteState('AddSkill');
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

