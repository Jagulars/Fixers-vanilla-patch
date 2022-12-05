section.begin
   Name = battle.SetPlacementMode
   Code : struct.begin
      [*] = ;gBoolRegister_BattlePlaceMode := true;
      [*] = ;
      [*] = ;//if (not _misc_IsLanBattle()) then
      [*] = ;begin
      [*] = ;   IntRegister0 := 0;
      [*] = ;   GUIExecuteState('DoShowScreenMessage');
      [*] = ;end;
   struct.end
section.end

