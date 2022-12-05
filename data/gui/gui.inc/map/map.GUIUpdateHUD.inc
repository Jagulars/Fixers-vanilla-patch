section.begin
   Name = map.GUIUpdateHUD
   Code : struct.begin
      [*] = ;var i, j : Integer;
      [*] = ;for i := GetCountOfPlayers-1 downto 0 do
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;   var raceTag : Integer = GetPlayerRaceTagByHandle(plHandle);
      [*] = ;   var cMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;
      [*] = ;   if (raceTag = gc_map_PlayerRaceTag) and (plHandle=GetPlayerHandleInterfaceIO) {and SameText(cMode, 'cmPlayer')} then
      [*] = ;   begin
      [*] = ;      for j := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;         if (GetGameObjectRaceTag(goHandle)=gc_map_PlayerRaceTag) and (not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bBuried)) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := goHandle;
      [*] = ;            ExecuteState('map.GUIUpdateHeroHUD');
      [*] = ;
      [*] = ;            IntRegister0 := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID); //DummyUID - if 0, then get activeHero current UID
      [*] = ;            IntRegister1 := 0; //setActiveHeroUID - if 0, then choose first picked hero
      [*] = ;            IntRegister2 := 0; //goUIDEndPointReached
      [*] = ;            ExecuteState('map.CreateHeroMultiHUD');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;{for i := GetCountOfPlayers-1 downto 0 do
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;   var raceTag : Integer = GetPlayerRaceTagByHandle(plHandle);
      [*] = ;
      [*] = ;   if (raceTag = gc_map_PlayerRaceTag) and (plHandle=GetPlayerHandleInterfaceIO) then
      [*] = ;   begin
      [*] = ;      for j := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var goHandle : Integer = GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;         if (GetGameObjectRaceTag(goHandle)=gc_map_PlayerRaceTag) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID); //DummyUID - if 0, then get activeHero current UID
      [*] = ;            IntRegister1 := 0; //setActiveHeroUID - if 0, then choose first picked hero
      [*] = ;            IntRegister2 := 0; //goUIDEndPointReached
      [*] = ;            ExecuteState('map.CreateHeroMultiHUD');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;}
   struct.end
section.end

