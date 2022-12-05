section.begin
   Name = ChangeMoral
   Description[*] = ;IntRegister0 - value to change
   UsedFileName = 
   Code : struct.begin
      [*] = ;var moralChange : Integer = IntRegister0;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;
      [*] = ;var fear : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iFear);
      [*] = ;var curMoral : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurMoral);
      [*] = ;
      [*] = ;var gridX : Integer = GetIntValueByIndex(gc_stack_unit_iCurrentX);
      [*] = ;var gridY : Integer = GetIntValueByIndex(gc_stack_unit_iCurrentY);
      [*] = ;var ind : Integer = gc_battle_GridSize * gridY + gridX;
      [*] = ;var pHexCell : Integer = ParserSelectByHandleByIndex(gHexCells.handle, ind);
      [*] = ;var tType : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Type');
      [*] = ;tType := (tType + 1) div 2;
      [*] = ;
      [*] = ;// check for berserk effect
      [*] = ;IntRegister0 := 25;
      [*] = ;ExecuteState('IsAbilityInEffects');
      [*] = ;var bBerserk : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;// check for fearless ability
      [*] = ;IntRegister0 := 19;
      [*] = ;ExecuteState('CheckAbility');
      [*] = ;var bFearless : Boolean = (IntRegister1 > 0);
      [*] = ;
      [*] = ;if (not bBerserk) and (not bFearless) then
      [*] = ;begin
      [*] = ;   if (tType = gc_DeadLandTerrainType) and ((curMoral > 0) or (moralChange > 1)) then
      [*] = ;   begin
      [*] = ;      if _unit_CheckAbility(myGOHandle, gc_ability_deadlands_knowledge) = 0 then
      [*] = ;      moralChange := moralChange - 1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   curMoral := curMoral + moralChange;
      [*] = ;
      [*] = ;   if curMoral <= 0 then
      [*] = ;   begin
      [*] = ;      if fear > 0 then
      [*] = ;      fear := fear - curMoral * 10
      [*] = ;      else
      [*] = ;      fear := 50 - curMoral * 10;
      [*] = ;
      [*] = ;      curMoral := 0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   SetGameObjectMyIntValueInd(gc_stack_unit_iFear, fear);
      [*] = ;   SetGameObjectMyIntValueInd(gc_stack_unit_iCurMoral, curMoral);
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

