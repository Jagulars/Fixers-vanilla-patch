section.begin
   Name = ShowPhantomForm
   Description : struct.begin
      [*] = ;IntRegister0  - phantom form unit id
      [*] = ;IntRegister1 - copy flags
      [*] = ;   &1    - copy life
      [*] = ;   &2    - copy stamina
      [*] = ;   &4    - copy morale
      [*] = ;   &8    - copy ammo
      [*] = ;   &0x10 - copy spells
      [*] = ;OUT:  IntRegister0 - phantom form handle
      [*] = ;      IntRegister1 - phantom form UID
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\SHOWPHANTOMFORM';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var phantom_id : Integer = IntRegister0;
      [*] = ;var copy_flags : Integer = IntRegister1;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var pMyParser : Integer = ParserSelectGameObject(myGOHandle);
      [*] = ;var pMyEffects : Integer = ParserSelectByHandleByKey(pMyParser, 'Effects');
      [*] = ;var pMySpells : Integer = ParserSelectByHandleByKey(pMyParser, 'Spells');
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(phantom_id)+','+IntToStr(copy_flags)+']',_log_trace);
      [*] = ;
      [*] = ;IntRegister0 := phantom_id;
      [*] = ;IntRegister1 := GetIntValueByIndex(gc_stack_unit_iCurrentX);
      [*] = ;IntRegister2 := GetIntValueByIndex(gc_stack_unit_iCurrentY);
      [*] = ;PlayerExecuteStateByHandle(myPlHandle, 'AddUnit');
      [*] = ;var newGOHandle : Integer = IntRegister3;
      [*] = ;var newUID : Integer = GetGameObjectUniqueIdByHandle(newGOHandle);
      [*] = ;
      [*] = ;var pNewParser : Integer = ParserSelectGameObject(newGOHandle);
      [*] = ;var pNewEffects : Integer = ParserSelectByHandleByKey(pNewParser, 'Effects');
      [*] = ;var pNewSpells : Integer = ParserAddChildByIndex(pNewParser, 'Spells');
      [*] = ;
      [*] = ;var unitID : Integer = GetGameObjectIntValueIndByHandle(newGOHandle, gc_stack_unit_iUnitID);
      [*] = ;IntRegister0 := myGOHandle;
      [*] = ;IntRegister1 := (copy_flags and $f);
      [*] = ;GameObjectExecuteStateByHandle(newGOHandle, 'CopyStackFrom');
      [*] = ;SetGameObjectIntValueIndByHandle(newGOHandle, gc_stack_unit_iUnitID, unitID);
      [*] = ;
      [*] = ;ParserClearByHandle(pNewEffects);
      [*] = ;ParserSelectByHandle(pNewEffects);
      [*] = ;ParserCopyFromByHandle(pMyEffects);
      [*] = ;GameObjectExecuteStateByHandle(newGOHandle, 'CalcAbilities');
      [*] = ;
      [*] = ;if ((copy_flags and $10) <> 0) then
      [*] = ;begin
      [*] = ;   ParserSelectByHandle(pNewSpells);
      [*] = ;   ParserCopyFromByHandle(pMySpells);
      [*] = ;end;
      [*] = ;
      [*] = ;var curLife : Integer = GetIntValueByIndex(gc_stack_unit_iCurLife);
      [*] = ;var maxLife : Integer = _unit_GetProperty(myGOHandle, gc_battle_unit_iMaxLife);
      [*] = ;var newMaxLife : Integer = _unit_GetProperty(newGOHandle, gc_battle_unit_iMaxLife);
      [*] = ;var newCurLife : Integer = Floor(newMaxLife * curLife / maxLife);
      [*] = ;newCurLife := Round(Clamp(newCurLife, 1, newMaxLife));
      [*] = ;SetGameObjectIntValueIndByHandle(newGOHandle, gc_stack_unit_iCurLife, newCurLife);
      [*] = ;
      [*] = ;var movePoints : Integer = GetIntValueByIndex(gc_stack_unit_iMovePoints);
      [*] = ;var speed : Integer = _unit_GetProperty(myGOHandle, gc_battle_unit_iSpeed);
      [*] = ;if speed < 1 then
      [*] = ;   speed := 1;
      [*] = ;var newSpeed : Integer = _unit_GetProperty(newGOHandle, gc_battle_unit_iSpeed);
      [*] = ;var newMovePoints : Integer = Floor(newSpeed * movePoints / speed);
      [*] = ;SetGameObjectIntValueIndByHandle(newGOHandle, gc_stack_unit_iMovePoints, newMovePoints);
      [*] = ;
      [*] = ;var tfUID : Integer = GetIntValueByIndex(gc_stack_unit_iTrueFormUID);
      [*] = ;if tfUID = 0 then
      [*] = ;   tfUID := GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;
      [*] = ;SetGameObjectIntValueIndByHandle(newGOHandle, gc_stack_unit_iTrueFormUID, tfUID);
      [*] = ;
      [*] = ;SetIntValueByIndex(gc_stack_unit_iCurLife, 0);
      [*] = ;SetGameObjectMyPlayableObject(false);
      [*] = ;SetGameObjectMyVisible(false);
      [*] = ;SetIntValueByIndex(gc_stack_unit_iCurrentX, -1);
      [*] = ;SetIntValueByIndex(gc_stack_unit_iCurrentY, -1);
      [*] = ;
      [*] = ;var gridX : Integer = GetGameObjectIntValueIndByHandle(newGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;var gridY : Integer = GetGameObjectIntValueIndByHandle(newGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;var ind : Integer = gc_battle_GridSize * gridY + gridX;
      [*] = ;var pHexCell : Integer = ParserSelectByHandleByIndex(gHexCells.handle, ind);
      [*] = ;ParserSetIntValueByKeyByHandle(pHexCell, 'UID', 0);
      [*] = ;
      [*] = ;//var x, y, z : Float;
      [*] = ;//GetTrackNodePositionByIndex(ind, x, y, z);
      [*] = ;//SetGameObjectPositionByHandle(newGOHandle, x, y, z);
      [*] = ;GameObjectExecuteStateByHandle(newGOHandle, 'WriteToGrid');
      [*] = ;
      [*] = ;// interface stuff that should not be here!
      [*] = ;if gIntRegister_SelectedUID = GetGameObjectUniqueIdByHandle(myGOHandle) then
      [*] = ;begin
      [*] = ;   gIntRegister_SelectedUID := newUID;
      [*] = ;   GUIExecuteState('battle.UpdateSelectedUnit');
      [*] = ;end;
      [*] = ;
      [*] = ;_fx_ShowEnvironmentAroundTacticalUnit(myGOHandle);
      [*] = ;_unit_GUIUpdateUnitHUD(newGOHandle);
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;
      [*] = ;IntRegister0 := newGOHandle;
      [*] = ;IntRegister1 := newUID;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

