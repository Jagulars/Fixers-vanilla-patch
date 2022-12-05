section.begin
   Name = CheckTargetAction
   Description : struct.begin
      [*] = ;BoolRegister0 - is send parser for lan battle
   struct.end
   Code : struct.begin
      [*] = ;var sendParser : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\CHECKTARGETACTION';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name+'['+GetGameObjectMyCustomName()+']',_log_trace);
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;
      [*] = ;var myPosX : Float = GetGameObjectPositionXByHandle(myGOHandle);
      [*] = ;var myPosZ : Float = GetGameObjectPositionZByHandle(myGOHandle);
      [*] = ;
      [*] = ;var tpCount : Integer = GetGameObjectMyTrackPointCount;
      [*] = ;var tpX, tpY, tpZ : Float;
      [*] = ;
      [*] = ;if tpCount > 0 then
      [*] = ;   GetGameObjectMyTrackPointCoordsByIndex(tpCount-1, tpX, tpY, tpZ)
      [*] = ;else
      [*] = ;begin
      [*] = ;   tpX := GetGameObjectMyPositionX;
      [*] = ;   tpY := GetGameObjectMyPositionY;
      [*] = ;   tpZ := GetGameObjectMyPositionZ;
      [*] = ;end;
      [*] = ;
      [*] = ;var pHexCells : Integer = gHexCells.handle;
      [*] = ;
      [*] = ;var tUID : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iTargetUID);
      [*] = ;var tGOHandle : Integer = GetGameObjectHandleByUniqueId(tUID);
      [*] = ;var tCurLife : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurLife);
      [*] = ;var action : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iActionType);
      [*] = ;
      [*] = ;if action = 4 then
      [*] = ;begin
      [*] = ;   BoolRegister0 := sendParser;
      [*] = ;   ExecuteState('EatCorpse');
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   // TODO : Faust talk, next if was added by us
      [*] = ;   if (GetBoolValueByIndex(gc_stack_unit_bCanAct)) then
      [*] = ;      ExecuteState('Select');
      [*] = ;
      [*] = ;   if (tGOHandle <> 0) and (tCurLife > 0) then
      [*] = ;   begin
      [*] = ;      var tPosX : Float = GetGameObjectPositionXByHandle(tGOHandle);
      [*] = ;      var tPosZ : Float = GetGameObjectPositionZByHandle(tGOHandle);
      [*] = ;
      [*] = ;      var tGridX : Integer =  GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;      var tGridY : Integer =  GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;      var tInd : Integer = gc_battle_GridSize * tGridY + tGridX;
      [*] = ;      var pTarHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, tInd);
      [*] = ;
      [*] = ;      //var tTNHandle : Integer = GetNearestTrackNodeHandle(tPosX, tPosZ, -1);
      [*] = ;      var tTNHandle : Integer = GetTrackNodeHandleByIndex(tInd);
      [*] = ;
      [*] = ;      case action of
      [*] = ;         1 : begin
      [*] = ;            if (_unit_CheckAbility(myGOHandle, gc_ability_does_not_fight) = 0) then
      [*] = ;            begin
      [*] = ;               if VectorDistance(tpX, 0, tpZ, tPosX, 0, tPosZ) < gc_HexSize * Sqrt(3) * 1.5 then // if not lunge attack
      [*] = ;               begin
      [*] = ;                  BoolRegister0 := sendParser;
      [*] = ;                  ExecuteState('Attack');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            SetIntValueByIndex(gc_stack_unit_iActionType, 0);
      [*] = ;         end;
      [*] = ;         2 : begin
      [*] = ;            //IntRegister0 := tTNHandle;
      [*] = ;            //ExecuteState('IsShootEndPoint');
      [*] = ;            //if BoolRegister0 then
      [*] = ;            if ParserGetIntValueByKeyByHandle(pTarHexCell, 'Shoot') = 2 then
      [*] = ;            begin
      [*] = ;               BoolRegister0 := sendParser;
      [*] = ;               ExecuteState('FireAttack');
      [*] = ;               SetIntValueByIndex(gc_stack_unit_iActionType, 0);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         3 : begin
      [*] = ;            if ParserGetIntValueByKeyByHandle(pTarHexCell, 'Shoot') > 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := tGOHandle;
      [*] = ;               BoolRegister0 := sendParser;
      [*] = ;               ExecuteState('HealUnit');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[ACTION: '+IntToStr(action)+']',$1000000 or _log_trace);
   struct.end
section.end

