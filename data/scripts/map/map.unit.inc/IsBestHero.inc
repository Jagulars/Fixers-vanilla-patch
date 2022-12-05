section.begin
   Name = IsBestHero
   Description[*] = OUT: BoolRegister0 - is hero best in player's list
   UsedFileName = 
   Code : struct.begin
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;
      [*] = ;var myAIPower : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iAIPower);
      [*] = ;var myLevel : Integer = GetGameObjectMyIntValueInd(gc_map_GOStack_MapUnit_iLevel);
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;var isBest : Boolean = true;
      [*] = ;
      [*] = ;for i := 0 to GetPlayerGameObjectsCountByHandle(myPlHandle)-1 do
      [*] = ;begin
      [*] = ;   var goHandle : Integer = GetGameObjectHandleByIndex(i, myPlHandle);
      [*] = ;
      [*] = ;   if (goHandle <> myGOHandle) and (not GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bBuried)) then
      [*] = ;   begin
      [*] = ;      var AIPower : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iAIPower);
      [*] = ;      
      [*] = ;      if gGame.improvedai or (gProfile.improvedai and (gGame.gameType <> gc_GameTypeLanShard)) then
      [*] = ;      begin
      [*] = ;         if (AIPower >= myAIPower) then // if later recruited hero has same aipower, we can assume that its development is better.
      [*] = ;         begin
      [*] = ;            isBest := false;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iLevel) > myLevel) then
      [*] = ;      begin
      [*] = ;         isBest := false;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;BoolRegister0 := isBest;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
