section.begin
   Name = battle.UnitHUDControl
   Code : struct.begin
      [*] = ;//log('battle.UnitHUDControl');
      [*] = ;
      [*] = ;if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;begin
      [*] = ;   var i, j : Integer;
      [*] = ;   
      [*] = ;   var lX, lY, lZ, rX, rY, rZ : Float = 0;
      [*] = ;   ScreenToWorldRayCast(0, (GetViewerHeight div 2), lX, lY, lZ);
      [*] = ;   ScreenToWorldRayCast(GetViewerWidth, (GetViewerHeight div 2), rX, rY, rZ);
      [*] = ;   
      [*] = ;   for i := GetCountOfPlayers-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;      var goHandle : Integer;
      [*] = ;   
      [*] = ;      if GetPlayerRaceTagByHandle(plHandle) = gc_player_Units_RaceTag then
      [*] = ;      begin
      [*] = ;         for j := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;         begin
      [*] = ;            goHandle := GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;            //if GetGameObjectVisibleByHandle(goHandle) then
      [*] = ;            begin
      [*] = ;               var perspectiveFactor : Float = (GetGameObjectPositionXByHandle(goHandle)-lX)/(rX-lX);
      [*] = ;               IntRegister0 := goHandle;
      [*] = ;               FloatRegister0 := perspectiveFactor;
      [*] = ;               ExecuteState('battle.GUIUpdateUnitHUD');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

