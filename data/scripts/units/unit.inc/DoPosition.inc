section.begin
   Name = DoPosition
   Description : struct.begin
      [*] = ;IntRegister0 - track point index in track node track point list
   struct.end
   Code : struct.begin
      [*] = ;var endTPIndex : Integer = IntRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\DOPOSITION';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;if endTPIndex = 0 then
      [*] = ;   exit;
      [*] = ;
      [*] = ;var pHexCells : Integer = gHexCells.handle;
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(GetGameObjectMyHandle());
      [*] = ;var myX : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentX);
      [*] = ;var myY : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentY);
      [*] = ;var endX, endY : Float;
      [*] = ;var x, y, z : Float;
      [*] = ;var i,cX,cY : Integer;
      [*] = ;var lanOrderRandKey0, lanOrderRandKey1 : Integer;
      [*] = ;
      [*] = ;GetRandomExtKey64(lanOrderRandKey0, lanOrderRandKey1);
      [*] = ;
      [*] = ;GetTrackNodeTPByIndex(endTPIndex, endX, endY);
      [*] = ;var tnEndHandle : Integer = GetNearestTrackNodeHandle(endX, endY, -1);
      [*] = ;var endHexParser : Integer = _map_GetHexByTNHandle(tnEndHandle);
      [*] = ;
      [*] = ;GetTrackNodeTPByIndex(endTPIndex-1, x, y);
      [*] = ;var befEndParser : Integer = _map_GetHexByTNHandle(GetNearestTrackNodeHandle(x, y, -1));
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+ParserGetValueByKeyByHandle(endHexParser, 'Name')+',ETP:'+IntToStr(endTPIndex)+']',_log_trace);
      [*] = ;GameObjectMyTrackPointClear();
      [*] = ;for i := 1 to endTPIndex do
      [*] = ;begin
      [*] = ;   GetTrackNodeTPByIndex(i, x, y);
      [*] = ;   GameObjectMyTrackPointAdd(x, 0, y);
      [*] = ;   //Log('Add + (' + FloatToStr(x) + ', ' + FloatToStr(y) + ') track point');
      [*] = ;end;
      [*] = ;
      [*] = ;SetGameObjectMyTrackPointCurrentPointIndex(0);
      [*] = ;
      [*] = ;if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;   ExecuteState('Move')
      [*] = ;else
      [*] = ;begin
      [*] = ;   ExecuteState('DoPathStaminaCharge');
      [*] = ;   GetTrackNodePositionByHandle(tnEndHandle, x, y, z);
      [*] = ;   SetGameObjectMyPosition(x, y, z);
      [*] = ;
      [*] = ;   BoolRegister0 := false;
      [*] = ;   ExecuteState('CheckTargetAction');
      [*] = ;end;
      [*] = ;
      [*] = ;SetGameObjectMyBoolValueInd(gc_stack_unit_bLunge, false);
      [*] = ;
      [*] = ;ParserSetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pHexCells, gc_battle_GridSize * myY + myX), 'UID', 0);
      [*] = ;GetTrackNodePositionByHandle(tnEndHandle, x, y, z);
      [*] = ;ParserSetIntValueByKeyByHandle(endHexParser, 'UID', myUID);
      [*] = ;
      [*] = ;SetGameObjectMyIntValueInd(gc_stack_unit_iLastX, myX);
      [*] = ;SetGameObjectMyIntValueInd(gc_stack_unit_iLastY, myY);
      [*] = ;cX := ParserGetIntValueByKeyByHandle(endHexParser, 'X');
      [*] = ;cY := ParserGetIntValueByKeyByHandle(endHexParser, 'Y');
      [*] = ;SetGameObjectMyIntValueInd(gc_stack_unit_iCurrentX, cX);
      [*] = ;SetGameObjectMyIntValueInd(gc_stack_unit_iCurrentY, cY);
      [*] = ;SetGameObjectMyIntValueInd(gc_stack_unit_iFacing, _map_GetFacing(befEndParser, endHexParser));
      [*] = ;SetGameObjectMyBoolValueInd(gc_stack_unit_bActionTaken, true);
      [*] = ;
      [*] = ;if ((myX <> cX) or (myY <> cY)) and (GetIntValueByIndex(gc_stack_unit_iActiveAbility) = gc_ability_double_shot) then
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iActiveAbility, 0);
      [*] = ;
      [*] = ;if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;begin
      [*] = ;   var pElmLog : Integer = _log_battle_AddNewElement();
      [*] = ;   ParserSetIntValueByKeyByHandle(pElmLog, 'Action', 6);
      [*] = ;   ParserSetIntValueByKeyByHandle(pElmLog, 'Param', gc_battle_GridSize * cY + cX);
      [*] = ;   ParserSetIntValueByKeyByHandle(ParserSelectByHandleByKey(pElmLog, 'SrcUnit'), 'UID', myUID);
      [*] = ;   _log_battle_Show();
      [*] = ;end;
      [*] = ;
      [*] = ;if (not GetBoolValueByIndex(gc_stack_unit_bRunBack)) and (GetIntValueByIndex(gc_stack_unit_iFear) <= 0) then // don't send parser if movement caused by panic or slyboots
      [*] = ;   _inet_CreateOrderParser(myUID, cX, cY, gc_inet_actiontype_move, 0, 0, GetIntValueByIndex(gc_stack_unit_iTargetUID), 0, lanOrderRandKey0, lanOrderRandKey1, 'DoPosition');
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

