section.begin
   Name = bat.ShowUnits
   Code : struct.begin
      [*] = ;var i : Integer;
      [*] = ;var plHandle : Integer = GetPlayerHandleByName(gc_battle_attackPlayerName);
      [*] = ;for i := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;   SetGameObjectVisibleByHandle(goHandle, true);
      [*] = ;end;
      [*] = ;
      [*] = ;plHandle := GetPlayerHandleByName(gc_battle_defendPlayerName);
      [*] = ;for i := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;   SetGameObjectVisibleByHandle(goHandle, true);
      [*] = ;end;
      [*] = ;
      [*] = ;GUIExecuteState('battle.UnitHUDControl');
   struct.end
section.end

