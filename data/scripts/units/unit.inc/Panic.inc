section.begin
   Name = Panic
   UsedFileName =
   Code : struct.begin
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var aMod : Integer = GetPlayerIntValueIndByHandle(myPlHandle, gc_battle_PLStack_iAttackMode);
      [*] = ;
      [*] = ;var pHexCells : Integer = gHexCells.handle;
      [*] = ;
      [*] = ;var fear : Integer = GetIntValueByIndex(gc_stack_unit_iFear);
      [*] = ;var curStamina : Integer = GetIntValueByIndex(gc_stack_unit_iCurStamina);
      [*] = ;var myGridX : Integer = GetIntValueByIndex(gc_stack_unit_iCurrentX);
      [*] = ;
      [*] = ;IntRegister0 := gc_ability_immobilized; // immobilized ability
      [*] = ;ExecuteState('CheckAbility');
      [*] = ;var f1 : Boolean = (IntRegister1 > 0);
      [*] = ;
      [*] = ;IntRegister0 := gc_ability_cantmove; // don't move ability
      [*] = ;ExecuteState('CheckAbility');
      [*] = ;var f2 : Boolean = (IntRegister1 > 0);
      [*] = ;
      [*] = ;var tarX : Integer = 0;
      [*] = ;if aMod = 0 then
      [*] = ;   tarX := gc_battle_GridSize - 1;
      [*] = ;
      [*] = ;if gBoolRegister_BattleSimulate or (_rand_Random(100) > fear) or f1 or f2 or (curStamina <= 0) or (myGridX = tarX) then
      [*] = ;begin
      [*] = ;   _fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryParam, gc_battle_unit_iMaxMoral, 0);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   // panic
      [*] = ;   ExecuteState('Select');
      [*] = ;
      [*] = ;   var step : Integer = 1;
      [*] = ;   if aMod = 0 then
      [*] = ;      step := -1;
      [*] = ;
      [*] = ;   var found : Integer = 0;
      [*] = ;
      [*] = ;   while (tarX >= 0) and (tarX <= gc_battle_GridSize-1) do
      [*] = ;   begin
      [*] = ;      var i : Integer;
      [*] = ;
      [*] = ;      ArrayClear();
      [*] = ;      for i := 0 to gc_battle_GridSize-1 do
      [*] = ;      begin
      [*] = ;         var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, gc_battle_GridSize * i + tarX);
      [*] = ;         if ParserGetBoolValueByKeyByHandle(pHexCell, 'Pass') and (ParserGetIntValueByKeyByHandle(pHexCell, 'UID') = 0) then
      [*] = ;            ArrayPushValue(gc_battle_GridSize * i + tarX);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if ArrayGetCount() > 0 then
      [*] = ;         break;
      [*] = ;
      [*] = ;      tarX := tarX + step;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if ArrayGetCount() > 0 then
      [*] = ;   begin
      [*] = ;      var ind : Integer = Floor(randomExt * ArrayGetCount());
      [*] = ;      var hexInd : Integer = ArrayGetValueByIndex(ind);
      [*] = ;
      [*] = ;      _fx_CreateFlyText_VVK(myGOHandle,gc_flytext_CategoryAbility , gc_ability_fear, 0);
      [*] = ;
      [*] = ;      IntRegister0 := GetTrackNodeHandleByIndex(hexInd);
      [*] = ;      ExecuteState('GoToPosition');
      [*] = ;   end
      [*] = ;   else
      [*] = ;      _fx_CreateFlyText_VVK(myGOHandle, gc_flytext_CategoryParam, gc_battle_unit_iMaxMoral, 0);
      [*] = ;end;
      [*] = ;
      [*] = ;SetGameObjectMyIntValueInd(gc_stack_unit_iMovePoints, 0);
      [*] = ;SetGameObjectMyBoolValueInd(gc_stack_unit_bCanAct, false);
      [*] = ;SetGameObjectMyBoolValueInd(gc_stack_unit_bCanMelee, false);
      [*] = ;SetGameObjectMyBoolValueInd(gc_stack_unit_bCanCast, false);
      [*] = ;SetGameObjectMyBoolValueInd(gc_stack_unit_bCanShoot, false);
      [*] = ;SetGameObjectMyBoolValueInd(gc_stack_unit_bActionTaken, true);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
