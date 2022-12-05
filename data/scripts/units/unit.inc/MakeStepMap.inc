section.begin
   Name = MakeStepMap
   Description[*] = 
   UsedFileName = 
   Code : struct.begin
      [*] = ;// OPTIMIZATION: can be optimized by rewriting it without recursion
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myX : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentX);
      [*] = ;var myY : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentY);
      [*] = ;var myInd : Integer = gc_battle_GridSize * myY + myX;
      [*] = ;var myTNHandle : Integer = GetTrackNodeHandleByIndex(myInd);
      [*] = ;
      [*] = ;var pHexCells : Integer = gHexCells.handle;
      [*] = ;
      [*] = ;var movePoints : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iMovePoints);
      [*] = ;var curStamina : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurStamina);
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iSpeed;
      [*] = ;ExecuteState('GetProperty');
      [*] = ;var speed : Integer = IntRegister1;
      [*] = ;
      [*] = ;var bFirstMove : Boolean = (movePoints = speed);
      [*] = ;
      [*] = ;var bMarch : Boolean = GetGameObjectMyBoolValueInd(gc_stack_unit_bCanMarch);
      [*] = ;
      [*] = ;function TryXYMap(x, y, weight, stam, speed : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   var ind : Integer = gc_battle_GridSize * y + x;
      [*] = ;   var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;   var tnHandle : Integer = GetTrackNodeHandleByIndex(ind);
      [*] = ;
      [*] = ;   // OPTIMIZATION: stamina cost can be cached in hex parser
      [*] = ;   IntRegister0 := pHexCell;
      [*] = ;   ExecuteState('GetHexStaminaCharge');
      [*] = ;   var stamCost : Integer = IntRegister1;
      [*] = ;
      [*] = ;   var land : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Land');
      [*] = ;   var pass : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Pass');
      [*] = ;
      [*] = ;   Result := false;
      [*] = ;
      [*] = ;   if (x >= 0) and (y >= 0) and (x < gc_battle_GridSize) and (y < gc_battle_GridSize) then
      [*] = ;   begin
      [*] = ;      if GetTrackNodeEnabledByHandle(tnHandle) {and (pass > 0)} and ((x <> myX) or (y <> myY)) then
      [*] = ;      begin
      [*] = ;         var moveCost : Integer = Round(GetTrackNodeDistFactorByHandle(tnHandle));
      [*] = ;
      [*] = ;         if (((land = 0) and ((moveCost <= speed) or ((weight = 0) and bFirstMove)))) or (weight + moveCost < land) then
      [*] = ;         begin
      [*] = ;            if stamCost <= stam then
      [*] = ;            Result := true;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function StepMap(x, y, weight, speed, stamCost, stamLeft : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var ind : Integer = gc_battle_GridSize * y + x;
      [*] = ;   var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, ind);
      [*] = ;
      [*] = ;   var isExit : Boolean = false;
      [*] = ;
      [*] = ;   if weight < 0 then
      [*] = ;   weight := 0
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var tnHandle : Integer = GetTrackNodeHandleByIndex(ind);
      [*] = ;      var tnWeight : Integer = Round(GetTrackNodeDistFactorByHandle(tnHandle));
      [*] = ;      weight := weight + tnWeight;
      [*] = ;      speed := speed - tnWeight;
      [*] = ;
      [*] = ;      // OPTIMIZATION: stamina cost can be cached in hex parser
      [*] = ;      IntRegister0 := pHexCell;
      [*] = ;      ExecuteState('GetHexStaminaCharge');
      [*] = ;      stamCost := stamCost + IntRegister1;
      [*] = ;
      [*] = ;      ParserSetIntValueByKeyByHandle(pHexCell, 'Land', weight);
      [*] = ;      ParserSetIntValueByKeyByHandle(pHexCell, 'Pass', 1);
      [*] = ;      if speed < 1 then
      [*] = ;      begin
      [*] = ;         Result := 0;
      [*] = ;         isExit := true;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if not isExit then
      [*] = ;   begin
      [*] = ;      if TryXYMap(x - 1 + y mod 2, y-1, weight, stamLeft - stamCost, speed) then
      [*] = ;      StepMap(x - 1 + y mod 2, y-1, weight, speed, stamCost, stamLeft);
      [*] = ;
      [*] = ;      if TryXYMap(x + y mod 2, y-1, weight, stamLeft - stamCost, speed) then
      [*] = ;      StepMap(x + y mod 2, y-1, weight, speed, stamCost, stamLeft);
      [*] = ;
      [*] = ;      if TryXYMap(x - 1 + y mod 2, y+1, weight, stamLeft - stamCost, speed) then
      [*] = ;      StepMap(x - 1 + y mod 2, y+1, weight, speed, stamCost, stamLeft);
      [*] = ;
      [*] = ;      if TryXYMap(x + y mod 2, y+1, weight, stamLeft - stamCost, speed) then
      [*] = ;      StepMap(x + y mod 2, y+1, weight, speed, stamCost, stamLeft);
      [*] = ;
      [*] = ;      if TryXYMap(x - 1, y, weight, stamLeft - stamCost, speed) then
      [*] = ;      StepMap(x - 1, y, weight, speed, stamCost, stamLeft);
      [*] = ;
      [*] = ;      if TryXYMap(x + 1, y, weight, stamLeft - stamCost, speed) then
      [*] = ;      StepMap(x + 1, y, weight, speed, stamCost, stamLeft);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   Result := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;if gBoolRegister_BattleSimulate then
      [*] = ;begin
      [*] = ;   ExecuteState('MakeSimStepMap');
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if bMarch then
      [*] = ;   begin
      [*] = ;      IntRegister0 := 29;
      [*] = ;      ExecuteState('CheckAbility');
      [*] = ;      var stamCost : Integer = IntRegister1;
      [*] = ;
      [*] = ;      if curStamina >= stamCost then
      [*] = ;      begin
      [*] = ;         movePoints := movePoints + 1;
      [*] = ;         curStamina := curStamina - stamCost;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var i : Integer;
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pHexCells)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, i);
      [*] = ;      ParserSetIntValueByKeyByHandle(pHexCell, 'Land', 0);
      [*] = ;      ParserSetIntValueByKeyByHandle(pHexCell, 'Pass', 0);
      [*] = ;   end;
      [*] = ;
      [*] = ;   StepMap(myX, myY, -1, movePoints, 0, curStamina);
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
