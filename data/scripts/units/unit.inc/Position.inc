section.begin
   Name = Position
   Description : struct.begin
      [*] = ;IntRegister0 - end track node handle
      [*] = ;IntRegister1 - target UID
      [*] = ;IntRegister2 - target action type
      [*] = ;RET: BoolRegister0 - false if position was not acquired
   struct.end
   Code : struct.begin
      [*] = ;var tnEndHandle : Integer = IntRegister0;
      [*] = ;var tGOUID : Integer = IntRegister1;
      [*] = ;var tAction : Integer = IntRegister2;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\POSITION';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myPlHandle : Integer = GetGameObjectPlayerHandleByHandle(myGOHandle);
      [*] = ;var myGridX : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentX);
      [*] = ;var myGridY : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentY);
      [*] = ;var myGridInd : Integer = gc_battle_GridSize * myGridY + myGridX;
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;
      [*] = ;var pHexCells : Integer = gHexCells.handle;
      [*] = ;
      [*] = ;var endInd : Integer = GetTrackNodeIndexByHandle(tnEndHandle);
      [*] = ;
      [*] = ;var tGOHandle : Integer = GetGameObjectHandleByUniqueId(tGOUID);
      [*] = ;var tGridX : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;var tGridY : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;var tInd : Integer = gc_battle_GridSize * tGridY + tGridX;
      [*] = ;var tCurLife : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurLife);
      [*] = ;var tStealthMode : Boolean = GetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bStealthMode);
      [*] = ;
      [*] = ;var pTarHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, tInd);
      [*] = ;var shoot : Integer = ParserGetIntValueByKeyByHandle(pTarHexCell, 'Shoot');
      [*] = ;//var nextUnit : Boolean = false;
      [*] = ;
      [*] = ;var pElmLog : Integer = 0;
      [*] = ;var pSrcUnit : Integer = 0;
      [*] = ;var pDestUnit : Integer = 0;
      [*] = ;var is_valid : Boolean;
      [*] = ;
      [*] = ;if _log then
      [*] = ;   _gv_traceState(_log_name+'['+GetGameObjectMyCustomName()+',TX: '+IntToStr(tGridX)+',TY: '+IntToStr(tGridY)+',TA: '+IntToStr(tAction)+',SHOOT: '+IntToStr(shoot)+',TUID: '+IntToStr(tGOUID)+']',_log_trace)
      [*] = ;else
      [*] = ;   _gv_traceState(_log_name+'['+GetGameObjectMyCustomName()+',A: '+IntToStr(tAction)+',TUID: '+IntToStr(tGOUID)+']',_log_trace);
      [*] = ;{if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;begin
      [*] = ;   pElmLog := _log_battle_AddNewElement;
      [*] = ;   ParserSetIntValueByKeyByHandle(pElmLog, 'Action', 6);
      [*] = ;   ParserSetIntValueByKeyByHandle(pElmLog, 'Param', endInd);
      [*] = ;
      [*] = ;   pSrcUnit := ParserSelectByHandleByKey(pElmLog, 'SrcUnit');
      [*] = ;   ParserSetIntValueByKeyByHandle(pSrcUnit, 'UID', myUID);
      [*] = ;end;}
      [*] = ;
      [*] = ;var hexDist : Integer = _misc_GetHexDist(myGridX, myGridY, tGridX, tGridY);
      [*] = ;var lunge : Boolean = GetBoolValueByIndex(gc_stack_unit_bLunge);
      [*] = ;IntRegister0 := tnEndHandle;
      [*] = ;BoolRegister0 := true;
      [*] = ;ExecuteState('IsValidEndPoint');
      [*] = ;is_valid := BoolRegister1;
      [*] = ;if lunge and (hexDist = 2) and (tGOHandle <> 0) and (is_valid) then
      [*] = ;begin
      [*] = ;   SetGameObjectMyIntValueInd(gc_stack_unit_iTargetUID, tGOUID);
      [*] = ;
      [*] = ;   BoolRegister0 := true;
      [*] = ;   ExecuteState('Attack');
      [*] = ;
      [*] = ;   BoolRegister0 := false;
      [*] = ;   ExecuteState('CheckAttackAnimation');
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if (tGOHandle <> 0) and (tCurLife > 0) and (not tStealthMode) and (tAction = 2) and (shoot = 2) then
      [*] = ;   begin
      [*] = ;      SetGameObjectMyIntValueInd(gc_stack_unit_iTargetUID, tGOUID);
      [*] = ;      SetGameObjectMyIntValueInd(gc_stack_unit_iActionType, tAction);
      [*] = ;
      [*] = ;      BoolRegister0 := true;
      [*] = ;      ExecuteState('FireAttack');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if is_valid then
      [*] = ;      begin
      [*] = ;         var curTarUID : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iTargetUID);
      [*] = ;         var curTarAction : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iActionType);
      [*] = ;         var curShotCount : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iShotCount);
      [*] = ;
      [*] = ;         if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) and (curTarAction = 2) and (curTarUID > 0) and (curShotCount > 0) then
      [*] = ;            ExecuteState('CreateProjectile')
      [*] = ;         else
      [*] = ;            SetGameObjectMyIntValueInd(gc_stack_unit_iTargetUID, tGOUID);
      [*] = ;
      [*] = ;         SetGameObjectMyIntValueInd(gc_stack_unit_iActionType, tAction);
      [*] = ;
      [*] = ;         var goX : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentX);
      [*] = ;         var goY : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentY);
      [*] = ;         var ind : Integer = gc_battle_GridSize * goY + goX;
      [*] = ;         var tnStartHandle : Integer = GetTrackNodeHandleByIndex(ind);
      [*] = ;
      [*] = ;         // finding path
      [*] = ;         var movePoints : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iMovePoints);
      [*] = ;         var endPoint : Integer = GetTrackNodeTPCount()-1;
      [*] = ;         var pathDist : Float = GetTrackNodePathLength();
      [*] = ;         pathDist := pathDist / (gc_HexSize * Sqrt(3));
      [*] = ;         var moved : Integer = Round(pathDist);
      [*] = ;
      [*] = ;         gIntRegister_StartTrackNode := gIntRegister_EndTrackNode;
      [*] = ;
      [*] = ;         movePoints := movePoints - moved;
      [*] = ;         if movePoints < 0 then
      [*] = ;            movePoints := 0;
      [*] = ;
      [*] = ;         SetGameObjectMyIntValueInd(gc_stack_unit_iMovePoints, movePoints);
      [*] = ;
      [*] = ;         if endPoint > 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := endPoint;
      [*] = ;            ExecuteState('DoPosition');
      [*] = ;
      [*] = ;            if tAction = 1 then
      [*] = ;            begin
      [*] = ;               BoolRegister0 := false;
      [*] = ;               ExecuteState('CheckTargetAction');
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            BoolRegister0 := true;
      [*] = ;            ExecuteState('CheckTargetAction');
      [*] = ;
      [*] = ;            BoolRegister0 := false;
      [*] = ;            ExecuteState('CheckAttackAnimation');
      [*] = ;         end;
      [*] = ;
      [*] = ;         ExecuteState('UpdateTrackNodes');
      [*] = ;
      [*] = ;         var bCanMelee : Boolean = GetGameObjectMyBoolValueInd(gc_stack_unit_bCanMelee);
      [*] = ;         if GetGameObjectMyBoolValueInd(gc_stack_unit_bCanAct) and ((not bCanMelee) or (_unit_CheckAbility(myGOHandle, gc_ability_lunge) = 0)) then
      [*] = ;         begin
      [*] = ;            BoolRegister0 := false;
      [*] = ;            IntRegister0 := GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentX);
      [*] = ;            IntRegister1 := GetGameObjectMyIntValueInd(gc_stack_unit_iCurrentY);
      [*] = ;            ExecuteState('FindNeighbour');
      [*] = ;            var nCount : Integer = IntRegister2;
      [*] = ;
      [*] = ;            var action : Integer = GetGameObjectMyIntValueInd(gc_stack_unit_iActionType);
      [*] = ;         
      [*] = ;            if ((movePoints <= 0) and (nCount = 0)) or ((nCount > 0) and (action = 1) and (_unit_CheckAbility(myGOHandle, gc_ability_swiftness) = 0)) then
      [*] = ;               SetGameObjectMyBoolValueInd(gc_stack_unit_bCanAct, false);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   {if (not gBoolRegister_QuickBattle) and (not gBoolRegister_BattleSimulate) then
      [*] = ;   begin
      [*] = ;      var pLastLogElement : Integer = _log_battle_GetLastLogElement;
      [*] = ;
      [*] = ;      if pElmLog = pLastLogElement then
      [*] = ;      _log_battle_Show
      [*] = ;      else
      [*] = ;      ParserFreeByHandle(pElmLog);
      [*] = ;   end;}
      [*] = ;
      [*] = ;   if GetBoolValueByIndex(gc_stack_unit_bCanAct) then
      [*] = ;      ExecuteState('Select');
      [*] = ;end;
      [*] = ;
      [*] = ;SetBoolValueByIndex(gc_stack_unit_bRunBack, false);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[IsValid: '+BoolToStr(is_valid)+', New Action: '+IntToStr(GetGameObjectMyIntValueInd(gc_stack_unit_iActionType))+']',$1000000 or _log_trace);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;BoolRegister0 := is_valid;
   struct.end
section.end

