section.begin
   Name = RaiseCorpse
   Description[*] = IntRegister0 - target UID
   UsedFileName = 
   Code : struct.begin
      [*] = ;var tUID : Integer = IntRegister0;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;
      [*] = ;var tGOHandle : Integer = GetGameObjectHandleByUniqueId(tUID);
      [*] = ;var unitID : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iUnitID);
      [*] = ;var curLife : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurLife);
      [*] = ;
      [*] = ;var gridX : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;var gridY : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;var ind : Integer = gc_battle_GridSize * gridY + gridX;
      [*] = ;var pHexCell : Integer = ParserSelectByHandleByIndex(gHexCells.handle, ind);
      [*] = ;var layer : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Layer');
      [*] = ;
      [*] = ;var pUnit : Integer = ParserSelectByHandleByIndex(gPrototypeData.units.handle, unitID);
      [*] = ;var unitType : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'UnitType');
      [*] = ;
      [*] = ;if (curLife <= 0) and (unitType <> 2) and (unitType <> 4) and (layer = 0) then
      [*] = ;begin
      [*] = ;   var level : Integer = 0;
      [*] = ;
      [*] = ;   if GetGameObjectMyBoolValueInd(gc_stack_unit_bIsHero) then
      [*] = ;   level := _unit_CheckAbility(myGOHandle, gc_ability_summoning_power) + _unit_CheckAbility(myGOHandle, gc_ability_necro_summoning_power)
      [*] = ;   else
      [*] = ;   level := GetGameObjectMyIntValueInd(gc_stack_unit_iLevel) div 4;
      [*] = ;
      [*] = ;   IntRegister0 := 19;
      [*] = ;   IntRegister1 := level;
      [*] = ;   IntRegister2 := gridX;
      [*] = ;   IntRegister3 := gridY;
      [*] = ;   PlayerExecuteStateByHandle(myPlHandle, 'SummonUnit');
      [*] = ;
      [*] = ;   SetGameObjectVisibleByHandle(tGOHandle, false);
      [*] = ;   SetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentX, -1);
      [*] = ;   SetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentY, -1);
      [*] = ;
      [*] = ;   if not gBoolRegister_BattleSimulate then
      [*] = ;   begin
      [*] = ;      var remainsUID : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iRemainsUID);
      [*] = ;      var remainsHnd : Integer = GetGameObjectHandleByUniqueId(remainsUID);
      [*] = ;      if (remainsHnd <> 0) then
      [*] = ;      begin
      [*] = ;         if gc_RecycleBattleField then
      [*] = ;            _obj_Recycle(remainsHnd)
      [*] = ;         else
      [*] = ;            AddObjectToDestroyList(remainsHnd);
      [*] = ;      end;
      [*] = ;      SetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iRemainsUID, 0);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end
