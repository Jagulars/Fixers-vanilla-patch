section.begin
   Name = DoPositionByCoords
   Description : struct.begin
      [*] = ;IntRegister0 - x
      [*] = ;IntRegister1 - y
      [*] = ;IntRegister2 - target UID
      [*] = ;IntRegister3 - action type
   struct.end
   Code : struct.begin
      [*] = ;var posX : Integer = IntRegister0;
      [*] = ;var posY : Integer = IntRegister1;
      [*] = ;var tUID : Integer = IntRegister2;
      [*] = ;var aType : Integer = IntRegister3;
      [*] = ;
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\DOPOSITIONBYCOORDS';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name+'['+GetGameObjectMyCustomName()+']',_log_trace);
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;
      [*] = ;var myX : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentX);
      [*] = ;var myY : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentY);
      [*] = ;
      [*] = ;var tGOHandle : Integer = GetGameObjectHandleByUniqueId(tUID);
      [*] = ;
      [*] = ;var movePoints : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iMovePoints);
      [*] = ;var dist : Integer = Round(Abs(posX - myX));
      [*] = ;
      [*] = ;var endX : Integer = posX;
      [*] = ;var endY : Integer = myY;
      [*] = ;
      [*] = ;if dist > movePoints then
      [*] = ;begin
      [*] = ;   if myX < posX then
      [*] = ;      endX := myX + movePoints
      [*] = ;   else
      [*] = ;      endX := myX - movePoints;
      [*] = ;
      [*] = ;   tUID := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;SetGameObjectMyIntValueInd(gc_stack_unit_iLastX, myX);
      [*] = ;SetGameObjectMyIntValueInd(gc_stack_unit_iLastY, myY);
      [*] = ;SetGameObjectMyIntValueInd(gc_stack_unit_iCurrentX, endX);
      [*] = ;SetGameObjectMyIntValueInd(gc_stack_unit_iCurrentY, endY);
      [*] = ;SetGameObjectMyBoolValueInd(gc_stack_unit_bActionTaken, true);
      [*] = ;
      [*] = ;var ind : Integer = gc_battle_GridSize * myY + myX;
      [*] = ;var pHexCell : Integer = ParserSelectByHandleByIndex(gHexCells.handle, ind);
      [*] = ;ParserSetIntValueByKeyByHandle(pHexCell, 'UID', 0);
      [*] = ;ind := gc_battle_GridSize * endY + endX;
      [*] = ;pHexCell := ParserSelectByHandleByIndex(gHexCells.handle, ind);
      [*] = ;ParserSetIntValueByKeyByHandle(pHexCell, 'UID', myUID);
      [*] = ;
      [*] = ;movePoints := movePoints - Round(Abs(myX - endX));
      [*] = ;SetGameObjectMyIntValueInd(gc_stack_unit_iMovePoints, movePoints);
      [*] = ;
      [*] = ;ind := gc_battle_GridSize * endY + endX;
      [*] = ;var tnHandle : Integer = GetTrackNodeHandleByIndex(ind);
      [*] = ;var x, y, z : Float;
      [*] = ;GetTrackNodePositionByHandle(tnHandle, x, y, z);
      [*] = ;SetGameObjectMyPosition(x, y, z);
      [*] = ;
      [*] = ;if tUID > 0 then
      [*] = ;begin
      [*] = ;   SetGameObjectMyIntValueInd(gc_stack_unit_iTargetUID, tUID);
      [*] = ;
      [*] = ;   BoolRegister0 := false;
      [*] = ;   case aType of
      [*] = ;      1 : begin
      [*] = ;         ExecuteState('Attack');
      [*] = ;      end;
      [*] = ;      2 : begin
      [*] = ;         ExecuteState('FireAttack');
      [*] = ;      end;
      [*] = ;      3 : begin
      [*] = ;         IntRegister0 := tGOHandle;
      [*] = ;         ExecuteState('HealUnit');
      [*] = ;      end;
      [*] = ;      4 : ExecuteState('EatCorpse');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if movePoints = 0 then
      [*] = ;   SetGameObjectMyBoolValueInd(gc_stack_unit_bCanAct, false);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

