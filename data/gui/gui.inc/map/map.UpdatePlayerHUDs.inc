section.begin
   Name = map.UpdatePlayerHUDs
   Code : struct.begin
      [*] = ;var plHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;var hudUnitCollection : Integer = GetGUIElementTopIndexByName('hudhero');
      [*] = ;GUIGroupHUDCollectionClear(hudUnitCollection);
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;for i := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;   if (not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bBuried)) then
      [*] = ;      SetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iUpdate, 1);
      [*] = ;end;
   struct.end
   Description[*] = ;IntRegister0 - player handle
section.end

