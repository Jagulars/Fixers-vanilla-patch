section.begin
   Name = ShowTrueForm
   Description : struct.begin
      [*] = ;OUT:  IntRegister0 - true form handle
      [*] = ;      IntRegister1 - true form UID (null if no true form exists)
      [*] = ;      BoolRegister0 - true if transformation took place
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\SHOWTRUEFORM';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var trueHandle : Integer = myGOHandle;
      [*] = ;var tfUID : Integer = GetIntValueByIndex(gc_stack_unit_iTrueFormUID);
      [*] = ;var goHandle : Integer;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(tfUID)+']',_log_trace);
      [*] = ;
      [*] = ;if tfUID = 0 then goHandle := 0
      [*] = ;else goHandle := GetGameObjectHandleByUniqueId(tfUID);
      [*] = ;
      [*] = ;if goHandle <> 0 then
      [*] = ;begin
      [*] = ;   var pMyEffects : Integer = ParserSelectByHandleByKey(ParserSelectGameObject(myGOHandle), 'Effects');
      [*] = ;   var pMySpells : Integer = ParserSelectByHandleByKey(ParserSelectGameObject(myGOHandle), 'Spells');
      [*] = ;   var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;   var pGOEffects : Integer = ParserSelectByHandleByKey(pGOParser, 'Effects');
      [*] = ;   var pGOSpells : Integer = ParserSelectByHandleByKey(pGOParser, 'Spells');
      [*] = ;   var unitID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iUnitID);
      [*] = ;
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iTrueFormUID,0);
      [*] = ;   SetGameObjectPlayableObjectByHandle(goHandle, true);
      [*] = ;   SetGameObjectVisibleByHandle(goHandle, true);
      [*] = ;
      [*] = ;   trueHandle := goHandle;
      [*] = ;
      [*] = ;   IntRegister0 := myGOHandle;
      [*] = ;   IntRegister1 := $ffff;
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'CopyStackFrom');
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iUnitID, unitID);
      [*] = ;
      [*] = ;   ParserClearByHandle(pGOEffects);
      [*] = ;   ParserSelectByHandle(pGOEffects);
      [*] = ;   ParserCopyFromByHandle(pMyEffects);
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'CalcAbilities');
      [*] = ;
      [*] = ;   if ParserGetCountByHandle(pMySpells) > 0 then // make sure we won't zero out spells after dragon form spell
      [*] = ;   begin
      [*] = ;      if _log then _log_gui(_log_name+'Spells copied.');
      [*] = ;      ParserSelectByHandle(pGOSpells);
      [*] = ;      ParserCopyFromByHandle(pMySpells);
      [*] = ;   end;
      [*] = ;
      [*] = ;   var newMaxLife : Integer = _unit_GetProperty(goHandle, gc_battle_unit_iMaxLife);
      [*] = ;   var newCurLife : Integer = Floor(newMaxLife * GetIntValueByIndex(gc_stack_unit_iCurLife) / _unit_GetProperty(myGOHandle, gc_battle_unit_iMaxLife));
      [*] = ;   newCurLife := Round(Clamp(newCurLife, 1, newMaxLife));
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife, newCurLife);
      [*] = ;
      [*] = ;   var speed : Integer = _unit_GetProperty(myGOHandle, gc_battle_unit_iSpeed);
      [*] = ;   if speed < 1 then speed := 1;
      [*] = ;   var newMovePoints : Integer = Floor(_unit_GetProperty(goHandle, gc_battle_unit_iSpeed) * GetIntValueByIndex(gc_stack_unit_iMovePoints) / speed);
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iMovePoints, newMovePoints);
      [*] = ;
      [*] = ;   var maxAmmo : Integer = _unit_GetProperty(myGOHandle, gc_battle_unit_iMaxAmmo);
      [*] = ;   if maxAmmo > GetIntValueByIndex(gc_stack_unit_iCurAmmo) then
      [*] = ;      SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurAmmo, maxAmmo);
      [*] = ;
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iCurLife, 0);
      [*] = ;   SetGameObjectMyPlayableObject(false);
      [*] = ;   SetGameObjectMyVisible(false);
      [*] = ;
      [*] = ;   var x, y, z : Float;
      [*] = ;   var gridX : Integer = GetIntValueByIndex(gc_stack_unit_iCurrentX);
      [*] = ;   var gridY : Integer = GetIntValueByIndex(gc_stack_unit_iCurrentY);
      [*] = ;   var ind : Integer = gc_battle_GridSize * gridY + gridX;
      [*] = ;   var pHexCell : Integer = ParserSelectByHandleByIndex(gHexCells.handle, ind);
      [*] = ;   ParserSetIntValueByKeyByHandle(pHexCell, 'UID', 0);
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iCurrentX, -1);
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iCurrentY, -1);
      [*] = ;   if _log then _log_values('X|Y|IDX|HexCell',gridX,gridY,ind,pHexCell,0,0);
      [*] = ;
      [*] = ;   GetTrackNodePositionByIndex(ind, x, y, z);
      [*] = ;   SetGameObjectPositionByHandle(goHandle, x, y, z);
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'WriteToGrid');
      [*] = ;
      [*] = ;   _fx_ShowEnvironmentAroundTacticalUnit(myGOHandle);
      [*] = ;   _fx_HideEnvironmentAroundTacticalUnit(goHandle);
      [*] = ;   _unit_GUIUpdateUnitHUD(goHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;
      [*] = ;IntRegister0 := trueHandle;
      [*] = ;IntRegister1 := tfUID;
      [*] = ;BoolRegister0 := (trueHandle <> myGOHandle);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

