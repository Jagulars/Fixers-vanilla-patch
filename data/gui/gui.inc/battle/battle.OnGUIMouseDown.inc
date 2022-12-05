section.begin
   Name = battle.OnGUIMouseDown
   Description : struct.begin
      [*] = ;tag:
      [*] = ;     1 - left mb don
      [*] = ;   101 - left mb up
      [*] = ;     2 - right mb don
      [*] = ;   102 - right mb up
      [*] = ;     3 - middle mb don
      [*] = ;     4 - middle mb up
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\BATTLE\BATTLE.ONGUIMOUSEDOWN';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerHandleInterfaceIO();
      [*] = ;var tag : Integer =  GetIntValueByName('Tag');
      [*] = ;var curGOHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_SelectedUID);
      [*] = ;var curGOAnim : String = GetGameObjectAnimationCycleNameByHandle(curGOHandle);
      [*] = ;var actAbility : Integer = GetGameObjectIntValueIndByHandle(curGOHandle, gc_stack_unit_iActiveAbility);
      [*] = ;var pHexCells : Integer = gHexCells.handle;
      [*] = ;var lan_battle : Boolean = _misc_IsLanBattle();
      [*] = ;
      [*] = ;function GetTrackNodeByUID(uid : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;
      [*] = ;   var i : Integer;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pHexCells)-1 do
      [*] = ;   begin
      [*] = ;      var pHexCell : Integer = ParserSelectByHandleByIndex(pHexCells, i);
      [*] = ;      var cell_uid : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'UID');
      [*] = ;      if cell_uid = uid then
      [*] = ;      begin
      [*] = ;         Result := GetTrackNodeHandleByIndex(i);
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetGameObjectPosition(goHandle, tnHandle : Integer);
      [*] = ;begin
      [*] = ;   var x, y, z : Float;
      [*] = ;   GetTrackNodePositionByHandle(tnHandle, x, y, z);
      [*] = ;   var tnParser : Integer = _map_GetHexByTNHandle(tnHandle);
      [*] = ;
      [*] = ;   var goGridX : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX);
      [*] = ;   var goGridY : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY);
      [*] = ;   var ind : Integer = gc_battle_GridSize * goGridY + goGridX;
      [*] = ;
      [*] = ;   var battleX : Integer = ParserGetIntValueByKeyByHandle(tnParser, 'X');
      [*] = ;   var battleY : Integer = ParserGetIntValueByKeyByHandle(tnParser, 'Y');
      [*] = ;
      [*] = ;   //var uid : Integer = GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;
      [*] = ;   _fx_ShowEnvironmentAroundTacticalUnit(goHandle);
      [*] = ;   SetGameObjectPositionByHandle(goHandle, x, y, z);
      [*] = ;   _fx_HideEnvironmentAroundTacticalUnit(goHandle);
      [*] = ;   GameObjectTrackPointClearByHandle(goHandle);
      [*] = ;
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iBattleX, battleX);
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iBattleY, battleY);
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iLastX, battleX);
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iLastY, battleY);
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX, battleX);
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY, battleY);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure BoostUnitSpeed(goHandle : Integer);
      [*] = ;begin
      [*] = ;   var pGo : Integer = ParserSelectGameObject(goHandle);
      [*] = ;   var tpms : Float = ParserGetFloatValueByKeyByHandle(pGo, 'TPMoveStep');
      [*] = ;   var tpts : Float = ParserGetFloatValueByKeyByHandle(pGo, 'TPTurnStep');
      [*] = ;   var waif : Float = ParserGetFloatValueByKeyByHandle(pGo, 'WalkAnimIntervalFactor');
      [*] = ;
      [*] = ;   IntRegister0 := gc_battle_unit_iSpeed;
      [*] = ;   GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;   var speed : Integer = IntRegister1;
      [*] = ;   var unitID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iUnitID);
      [*] = ;   var pUnit : Integer = _unit_GetUnitParserByID(unitID);
      [*] = ;   var baseSpeed : Integer = ParserGetIntValueByKeyByHandle(pUnit, 'Speed');
      [*] = ;   var effectSpeedBoost : Float = 1;
      [*] = ;   if (baseSpeed<>0) then
      [*] = ;   begin
      [*] = ;      effectSpeedBoost := speed/baseSpeed;
      [*] = ;      if (effectSpeedBoost>2) then
      [*] = ;         effectSpeedBoost := 2
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (effectSpeedBoost<0.5) then
      [*] = ;            effectSpeedBoost := 0.5;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   const cSpeedBoost = gc_battle_speed_max*1.5;
      [*] = ;   var battlespeed : Float = _misc_GetBattleSpeed();
      [*] = ;   if GetGameObjectTrackPointMoveStepByHandle(goHandle)<(tpms*(gc_battle_speed_min+(battlespeed*(gc_battle_speed_max-gc_battle_speed_min)))+0.01) then
      [*] = ;   begin
      [*] = ;      SetGameObjectTrackPointMoveStepByHandle(goHandle, tpms*cSpeedBoost*effectSpeedBoost{*(gc_battle_speed_min+(gProfile.battlespeed*(gc_battle_speed_max-gc_battle_speed_min)))});
      [*] = ;      SetGameObjectTrackPointTurnStepByHandle(goHandle, tpts*cSpeedBoost*effectSpeedBoost{*(gc_battle_speed_min+(gProfile.battlespeed*(gc_battle_speed_max-gc_battle_speed_min)))});
      [*] = ;      SetGameObjectIntervalFactorByHandle(goHandle, waif*cSpeedBoost*effectSpeedBoost{*(gc_battle_speed_min+(gProfile.battlespeed*(gc_battle_speed_max-gc_battle_speed_min)))});
      [*] = ;
      [*] = ;      var behHnd : Integer = GetBehaviourByKey(goHandle, 'flight');
      [*] = ;      if (behHnd<>0) then
      [*] = ;      begin
      [*] = ;         var behSpeed : Float = GetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,0]');
      [*] = ;         var behTime : Float = GetBehaviourFloatProperty(behHnd, 'StartTime[0]');
      [*] = ;         var timeDelta : Float = GetCurrentTime-behTime;
      [*] = ;         SetBehaviourFloatProperty(behHnd, 'StartTime[0]', GetCurrentTime-timeDelta/2);
      [*] = ;         SetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,0]', behSpeed*2);
      [*] = ;         SetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,1]', behSpeed*2);
      [*] = ;         SetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,2]', behSpeed*2);
      [*] = ;         SetBehaviourFloatProperty(behHnd, 'PathsNodesSpeed[0,3]', behSpeed*2);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   //log('baseName = ' + GetGameObjectBaseNameByHandle(goHandle) + ' tpms = ' + FloatToStr(tpms) + ' waif = ' + FloatToStr(waif));
      [*] = ;end;
      [*] = ;
      [*] = ;procedure BoostAllPlayerUnits(plHandle : Integer);
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   for i := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;      var playable : Boolean = GetGameObjectPlayableObjectByHandle(goHandle);
      [*] = ;      if (playable) then
      [*] = ;      begin
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'IsStand');
      [*] = ;         if (not BoolRegister0) then
      [*] = ;            BoostUnitSpeed(goHandle);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;GameObjectRayCastMouseRay();
      [*] = ;GameObjectSortRayCastList();
      [*] = ;
      [*] = ;if (gIntRegister_EndTrackNode=0) then
      [*] = ;begin
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;gIntRegister_EndHexCell := _map_GetHexByTNHandle(gIntRegister_EndTrackNode);
      [*] = ;gIntRegister_EndHexUID := ParserGetIntValueByKeyByHandle(gIntRegister_EndHexCell, 'UID');
      [*] = ;
      [*] = ;if tag = 3 then //Middle Mouse Button
      [*] = ;begin
      [*] = ;   SetIntValueByName('MBTN', 1);
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;if tag = 4 then //Middle Mouse Button
      [*] = ;begin
      [*] = ;   SetIntValueByName('MBTN', 0);
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;if (tag=101) and (not gBoolRegister_BattlePlaceMode) then
      [*] = ;begin
      [*] = ;   if (gIntRegister_BattleCurPlIndex=GetPlayerIndexByHandle(myPlHandle)) then
      [*] = ;   begin
      [*] = ;      var goUID : Integer = gIntRegister_EndHexUID;
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByUniqueId(goUID);
      [*] = ;      var plHandle : Integer = GetGameObjectPlayerHandleByHandle(goHandle);
      [*] = ;
      [*] = ;      var endPointValid : Boolean;
      [*] = ;      var goEnemyUID : Integer;
      [*] = ;      _unit_IsValidEndPoint(curGoHandle, gIntRegister_EndTrackNode, true, false, endPointValid, goEnemyUID);
      [*] = ;
      [*] = ;      var isShoot : Boolean = false;
      [*] = ;      if (curGoHandle<>0) and (goUID<>0) and (plHandle<>myPlHandle) then
      [*] = ;      begin
      [*] = ;         var shoot : Integer = ParserGetIntValueByKeyByHandle(gIntRegister_EndHexCell, 'shoot');
      [*] = ;         if gIntRegister_EndHexUID<>0 then
      [*] = ;         begin
      [*] = ;            if GetIsEnemyPlayersByHandle(GetGameObjectPlayerHandleByHandle(curGOHandle), GetGameObjectPlayerHandleByHandle(GetGameObjectHandleByUniqueId(gIntRegister_EndHexUID))) and
      [*] = ;            GetGameObjectPlayableObjectByHandle(GetGameObjectHandleByUniqueId(gIntRegister_EndHexUID)) then
      [*] = ;               isShoot := (shoot = 2);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (not lan_battle) and (GetPlayerBoolValueIndByHandle(myPlHandle, gc_battle_PLStack_bAutoBattle)) then
      [*] = ;      begin
      [*] = ;         gFloatRegister_UnitMoveSpeedBoost := 2;
      [*] = ;         BoostAllPlayerUnits(myPlHandle);
      [*] = ;      end;
      [*] = ;
      [*] = ;      //log('goUID = ' + IntToStr(goUID) + ' goEnemyUID = ' + IntToStr(goEnemyUID) + ' isShoot = ' + BoolToStr(isShoot) + ' endPointValid = ' + BoolToStr(endPointValid));
      [*] = ;      if (not lan_battle) then
      [*] = ;      begin
      [*] = ;         if ((plHandle=0) or (plHandle<>myPlHandle)) and (not endPointValid) and (not isShoot) then
      [*] = ;            BoostAllPlayerUnits(myPlHandle);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (not lan_battle) then
      [*] = ;      begin
      [*] = ;         gFloatRegister_UnitMoveSpeedBoost := 2;
      [*] = ;
      [*] = ;         PlayerExecuteStateByHandle(myPlHandle, 'GetEnemyPlHandle');
      [*] = ;         BoostAllPlayerUnits( IntRegister0 );
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;GUIExecuteState('battle.IsLockMode');
      [*] = ;if (not BoolRegister0) then
      [*] = ;begin
      [*] = ;   if (tag = 101) then
      [*] = ;   begin
      [*] = ;      var goUID : Integer = gIntRegister_EndHexUID;
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByUniqueId(goUID);
      [*] = ;      var plHandle : Integer = GetGameObjectPlayerHandleByHandle(goHandle);
      [*] = ;
      [*] = ;      if not gBoolRegister_BattlePlaceMode then
      [*] = ;      begin
      [*] = ;         var bActionsAllowed : Boolean = true;
      [*] = ;         if lan_battle then
      [*] = ;            bActionsAllowed := (_gv_GetBattleLock = 0); // ensure there are no actions taken too fast in lan battle 
      [*] = ;   
      [*] = ;         // heal ability
      [*] = ;         if SameText(curGOAnim, 'idle') and ((curGOHandle<>0) and ((actAbility = 24) or (actAbility = 132))) and bActionsAllowed then
      [*] = ;         begin
      [*] = ;            if actAbility = 24 then
      [*] = ;            IntRegister0 := 0
      [*] = ;            else
      [*] = ;            IntRegister0 := 1;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'IsHealTarget');
      [*] = ;            var healTarget : Integer = IntRegister1;
      [*] = ;            if (healTarget=2) and (GetGameObjectPlayerHandleByHandle(goHandle)=myPlHandle) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := goHandle;
      [*] = ;               BoolRegister0 := true;
      [*] = ;               GameObjectExecuteStateByHandle(curGOHandle, 'HealUnit');
      [*] = ;               
      [*] = ;               if (not GetGameObjectBoolValueIndByHandle(curGOHandle, gc_stack_unit_bCanAct)) then
      [*] = ;                  GUIExecuteState('battle.SelectNextUnit');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               IntRegister0 := actAbility;
      [*] = ;               BoolRegister0 := true;
      [*] = ;               ExecuteState('ActivateAbility');
      [*] = ;         
      [*] = ;               GUIExecuteState('battle.CreateControlPanelWindow');
      [*] = ;               GUIExecuteState('battle.UpdateCursor');
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            // cast spell
      [*] = ;            if SameText(curGOAnim, 'idle') and (curGOHandle <> 0) and (gIntRegister_CurSpell > 0) and bActionsAllowed then
      [*] = ;            begin
      [*] = ;               var pHexHandle : Integer = gIntRegister_EndHexCell;
      [*] = ;
      [*] = ;               var pSpell : Integer = ParserSelectByHandleByIndex(gPrototypeData.spells.handle, gIntRegister_CurSpell);
      [*] = ;               var pEffects : Integer = ParserSelectByHandleByKey(pSpell, 'Effects');
      [*] = ;               var pEffect : Integer = ParserSelectByHandleByIndex(pEffects, 0);
      [*] = ;               var abilID : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'AbilityID');
      [*] = ;               var spSacrifice : Boolean = ParserGetBoolValueByKeyByHandle(pSpell, 'Sacrifice');
      [*] = ;               var spArea : Integer = ParserGetIntValueByKeyByHandle(pSpell, 'Area');
      [*] = ;
      [*] = ;               var cast : Boolean = false;
      [*] = ;
      [*] = ;               if spSacrifice and (gIntRegister_SacrificeUID = 0) then
      [*] = ;               begin
      [*] = ;                  GameObjectExecuteStateByHandle(goHandle, 'IsStand');
      [*] = ;                  if (goHandle <> 0) and BoolRegister0 and SameText(GetGameObjectAnimationCycleNameByHandle(goHandle), 'idle') then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := gIntRegister_CurSpell;
      [*] = ;                     IntRegister1 := gIntRegister_SelectedUID;
      [*] = ;                     GameObjectExecuteStateByHandle(goHandle, 'IsSacrifice');
      [*] = ;                     if BoolRegister0 then
      [*] = ;                     begin
      [*] = ;                        gIntRegister_SacrificeUID := goUID;
      [*] = ;
      [*] = ;                        if spArea = 2 then
      [*] = ;                           cast := true;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               if (abilID = 89) and (gIntRegister_TeleportUID = 0) then
      [*] = ;               begin
      [*] = ;                  GameObjectExecuteStateByHandle(goHandle, 'IsStand');
      [*] = ;                  if BoolRegister0 and SameText(GetGameObjectAnimationCycleNameByHandle(goHandle), 'idle') then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := gIntRegister_SelectedUID;
      [*] = ;                     GameObjectExecuteStateByHandle(goHandle, 'IsTeleportTarget');
      [*] = ;                     if BoolRegister0 then
      [*] = ;                        gIntRegister_TeleportUID := goUID;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  cast := true;
      [*] = ;
      [*] = ;               if cast then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := gIntRegister_CurSpell;
      [*] = ;                  IntRegister1 := pHexHandle;
      [*] = ;                  GameObjectExecuteStateByHandle(curGOHandle, 'CanCastSpell');
      [*] = ;                  if (spArea = 2) or BoolRegister0 then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := gIntRegister_CurSpell;
      [*] = ;                     IntRegister1 := pHexHandle;
      [*] = ;                     BoolRegister0 := true;
      [*] = ;                     GameObjectExecuteStateByHandle(curGOHandle, 'CastSpell');
      [*] = ;
      [*] = ;                     if (gBoolRegister_BattleInfiniteMovePoints) then
      [*] = ;                     begin
      [*] = ;                        var goHnd : Integer = GetGameObjectHandleByUniqueId(gIntRegister_SelectedUID);
      [*] = ;                        SetGameObjectBoolValueIndByHandle(goHnd, gc_stack_unit_bCanAct, true);
      [*] = ;                        SetGameObjectBoolValueIndByHandle(goHnd, gc_stack_unit_bActionTaken, false);
      [*] = ;                        IntRegister0 := gc_battle_unit_iSpeed;
      [*] = ;                        GameObjectExecuteStateByHandle(goHnd, 'GetProperty');
      [*] = ;                        var speed : Integer = IntRegister1;
      [*] = ;                        SetGameObjectIntValueIndByHandle(goHnd, gc_stack_unit_iMovePoints, speed);
      [*] = ;                        if (GetGameObjectIntValueIndByHandle(goHnd, gc_stack_unit_iCurStamina)<10) then
      [*] = ;                           SetGameObjectIntValueIndByHandle(goHnd, gc_stack_unit_iCurStamina, 10);
      [*] = ;                        SetGameObjectIntValueIndByHandle(goHnd, gc_stack_unit_iCurAmmo, 10);
      [*] = ;                        GameObjectExecuteStateByHandle(GetGameObjectHandleByUniqueId(gIntRegister_SelectedUID), 'Select');
      [*] = ;                        GUIExecuteState('battle.UpdateSelectedUnit');
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        if (not GetGameObjectBoolValueIndByHandle(curGOHandle, gc_stack_unit_bCanAct)) then
      [*] = ;                           GUIExecuteState('battle.SelectNextUnit');
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     gIntRegister_CurSpell := -1;
      [*] = ;                     gIntRegister_CurSpellIndex := -1;
      [*] = ;                     IntRegister0 := 6; //0 - unit, 1 - item, 2 - spell, 5 - rituals, 6 - spells
      [*] = ;                     IntRegister1 := 0; //0 - hide
      [*] = ;                     GUIExecuteState('DoDragElement');
      [*] = ;                     GUIExecuteState('battle.CreateControlPanelWindow');
      [*] = ;                     GUIExecuteState('battle.UpdateCursor');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     gIntRegister_CurSpell := -1;
      [*] = ;                     gIntRegister_CurSpellIndex := -1;
      [*] = ;                     IntRegister0 := 6; //0 - unit, 1 - item, 2 - spell, 5 - rituals, 6 - spells
      [*] = ;                     IntRegister1 := 0; //0 - hide
      [*] = ;                     GUIExecuteState('DoDragElement');
      [*] = ;                     GUIExecuteState('battle.CreateControlPanelWindow');
      [*] = ;                     GUIExecuteState('battle.UpdateCursor');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if _log then _Log_gui(_log_name+' goUID = ' + IntToStr(goUID));
      [*] = ;               if (goHandle<>0) and (plHandle = GetPlayerHandleInterfaceIO) then
      [*] = ;               begin
      [*] = ;                  GameObjectExecuteStateByHandle(goHandle, 'IsStand');
      [*] = ;                  var isStand : Boolean = BoolRegister0;
      [*] = ;                  var static : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bStatic);
      [*] = ;
      [*] = ;                  if (gIntRegister_SelectedUID<>goUID) then
      [*] = ;                  begin
      [*] = ;                     if (not static) and (isStand) then
      [*] = ;                     begin
      [*] = ;                        if (gBoolRegister_BattleInfiniteMovePoints) then
      [*] = ;                        begin
      [*] = ;                           // hack for weapon fire testing start
      [*] = ;                           var goHnd : Integer = GetGameObjectHandleByUniqueId(goUID);
      [*] = ;                           SetGameObjectBoolValueIndByHandle(goHnd, gc_stack_unit_bCanAct, true);
      [*] = ;                           SetGameObjectBoolValueIndByHandle(goHnd, gc_stack_unit_bActionTaken, false);
      [*] = ;                           IntRegister0 := gc_battle_unit_iSpeed;
      [*] = ;                           GameObjectExecuteStateByHandle(goHnd, 'GetProperty');
      [*] = ;                           var speed : Integer = IntRegister1;
      [*] = ;                           SetGameObjectIntValueIndByHandle(goHnd, gc_stack_unit_iMovePoints, speed);
      [*] = ;                           if (GetGameObjectIntValueIndByHandle(goHnd, gc_stack_unit_iCurStamina)<10) then
      [*] = ;                           SetGameObjectIntValueIndByHandle(goHnd, gc_stack_unit_iCurStamina, 10);
      [*] = ;                           SetGameObjectIntValueIndByHandle(goHnd, gc_stack_unit_iCurAmmo, 10);
      [*] = ;                           // hack for weapon fire testing finish
      [*] = ;                        end;
      [*] = ;
      [*] = ;                        gIntRegister_SelectedUID := goUID;
      [*] = ;                        GameObjectExecuteStateByHandle(GetGameObjectHandleByUniqueId(gIntRegister_SelectedUID), 'Select');
      [*] = ;                        GUIExecuteState('battle.UpdateSelectedUnit');
      [*] = ;
      [*] = ;                        IntRegister0 := -8;
      [*] = ;                        MapExecuteState('CheckTutorialProgress');
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        if (not lan_battle) then
      [*] = ;                           BoostAllPlayerUnits(plHandle);
      [*] = ;                     end;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     if (not isStand) or (not SameText(curGOAnim, 'idle')) then
      [*] = ;                        BoostAllPlayerUnits(plHandle)
      [*] = ;                     else
      [*] = ;                     if bActionsAllowed and (not gBoolRegister_BattlePlaceMode) and (_unit_CheckAbility(goHandle, gc_ability_immobilized) = 0) then
      [*] = ;                     begin
      [*] = ;                        var wX, wY, wZ : Float;
      [*] = ;                        var nearX, nearY, nearZ : Float;
      [*] = ;                        GetCurrentMouseWorldCoord(wX, wY, wZ);
      [*] = ;                        GetTrackNodePositionByHandle(gIntRegister_BeforeEndTrackNode, nearX, nearY, nearZ);
      [*] = ;                        var dist : Float = VectorDistance(wX, 0, wZ, nearX, 0, nearZ);
      [*] = ;                        if (dist>gc_gui_unit_minturncursordist) then
      [*] = ;                        begin
      [*] = ;                           var angle : Float = VectorAngle(wX-nearX, 0, wZ-nearZ, 1, 0, 0);
      [*] = ;                           var ind : Integer = Round(angle / 60);
      [*] = ;
      [*] = ;                           if (wZ-nearZ<0) and ((ind=1) or (ind=2)) then
      [*] = ;                           ind := 6 - ind;
      [*] = ;                           IntRegister0 := ind;
      [*] = ;                           _log_obj('TURN ind: '+IntToStr(ind));
      [*] = ;                           GameObjectExecuteStateByHandle(goHandle, 'Turn');
      [*] = ;                        end
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  DebugDrawClean('Path');
      [*] = ;
      [*] = ;                  var bCanAct : Boolean = GetGameObjectBoolValueIndByHandle(curGOHandle, gc_stack_unit_bCanAct);
      [*] = ;                  GameObjectExecuteStateByHandle(curGOHandle, 'IsStand');
      [*] = ;                  var isStand : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;                  if (curGOHandle <> 0) and bCanAct and isStand and SameText(curGOAnim, 'idle') and bActionsAllowed then
      [*] = ;                  begin
      [*] = ;                     var action : Integer = 0;
      [*] = ;                     if (goHandle <> 0) then
      [*] = ;                     begin
      [*] = ;                        var X, Y, Z : Float;
      [*] = ;                        GetCurrentMouseWorldCoord(X,Y,Z);
      [*] = ;
      [*] = ;                        var tnEndHandle : Integer = GetNearestTrackNodeHandle(x, z, -1);
      [*] = ;                        GetTrackNodePositionByHandle(gIntRegister_BeforeEndTrackNode, x, y, z);
      [*] = ;                        var pHexCell : Integer = _map_GetHexByTNHandle(tnEndHandle);
      [*] = ;                        var shoot : Integer = ParserGetIntValueByKeyByHandle(pHexCell, 'Shoot');
      [*] = ;                        var tPlayable : Boolean = GetGameObjectPlayableObjectByHandle(goHandle);
      [*] = ;                        var tStealthMode : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bStealthMode);
      [*] = ;                        var bCanMelee : Boolean = GetGameObjectBoolValueIndByHandle(curGOHandle, gc_stack_unit_bCanMelee);
      [*] = ;                        var bCanShoot : Boolean = GetGameObjectBoolValueIndByHandle(curGOHandle, gc_stack_unit_bCanShoot);
      [*] = ;
      [*] = ;                        if (goHandle <> 0) and (plHandle <> myPlHandle) and tPlayable then
      [*] = ;                        begin
      [*] = ;                           if (shoot = 2) and (not tStealthMode) and bCanShoot then
      [*] = ;                              action := 2
      [*] = ;                           else
      [*] = ;                           if bCanMelee then
      [*] = ;                              action := 1;
      [*] = ;                        end;
      [*] = ;                     
      [*] = ;                        if action = 0 then
      [*] = ;                           goUID := 0;
      [*] = ;
      [*] = ;                        if (action=2) and (GetBoolValueByName('KeyPressedCtrl')) and bCanMelee then
      [*] = ;                           action := 1;
      [*] = ;                     end;
      [*] = ;                     
      [*] = ;                     IntRegister0 := gIntRegister_BeforeEndTrackNode;
      [*] = ;                     IntRegister1 := goUID;
      [*] = ;                     IntRegister2 := action;
      [*] = ;                     GameObjectExecuteStateByHandle(curGOHandle, 'Position');
      [*] = ;
      [*] = ;                     if (not GetGameObjectBoolValueIndByHandle(curGOHandle, gc_stack_unit_bCanAct)) then
      [*] = ;                        GUIExecuteState('battle.SelectNextUnit');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                     if (not lan_battle) and (not isStand) and (goUID<>0) then
      [*] = ;                        BoostAllPlayerUnits(plHandle);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         GUIExecuteState('battle.UpdateCursor');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      // battle placement mode
      [*] = ;      if not gBoolRegister_ArenaWatcher then
      [*] = ;      begin
      [*] = ;         var selGOHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_SelectedUID);
      [*] = ;
      [*] = ;         if selGOHandle = 0 then
      [*] = ;         begin
      [*] = ;            var plHandle : Integer = GetGameObjectPlayerHandleByHandle(goHandle);
      [*] = ;            if plHandle = GetPlayerHandleInterfaceIO then
      [*] = ;            begin
      [*] = ;               gIntRegister_SelectedUID := GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;               gIntRegister_StartTrackNode := GetTrackNodeByUID(gIntRegister_SelectedUID);
      [*] = ;               GUIExecuteState('battle.CreateControlPanelWindow');
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var lanOrderRandKey0, lanOrderRandKey1 : Integer;
      [*] = ;            GetRandomExtKey64(lanOrderRandKey0, lanOrderRandKey1);
      [*] = ;            if goHandle <> 0 then
      [*] = ;            begin
      [*] = ;               if goHandle <> selGOHandle then
      [*] = ;               begin
      [*] = ;                  var plHandle : Integer = GetGameObjectPlayerHandleByHandle(goHandle);
      [*] = ;                  if plHandle = GetPlayerHandleInterfaceIO then
      [*] = ;                  begin
      [*] = ;                     var selGridX : Integer = GetGameObjectIntValueIndByHandle(selGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;                     var selGridY : Integer = GetGameObjectIntValueIndByHandle(selGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;                     var goGridX : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX);
      [*] = ;                     var goGridY : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY);
      [*] = ;
      [*] = ;                     IntRegister0 := selGridX;
      [*] = ;                     IntRegister1 := selGridY;
      [*] = ;                     BoolRegister0 := true;
      [*] = ;                     GameObjectExecuteStateByHandle(goHandle, 'Replace');
      [*] = ;                     var uid : Integer = GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;                     _inet_CreateOrderParser(uid, selGridX, selGridY, gc_inet_actiontype_teleport, 0, 0, 0, 0, lanOrderRandKey0, lanOrderRandKey1,'battle.OnGUIMouseDown - Arena01');
      [*] = ;
      [*] = ;                     IntRegister0 := goGridX;
      [*] = ;                     IntRegister1 := goGridY;
      [*] = ;                     BoolRegister0 := true;
      [*] = ;                     GameObjectExecuteStateByHandle(selGOHandle, 'Replace');
      [*] = ;                     _inet_CreateOrderParser(gIntRegister_SelectedUID, goGridX, goGridY, gc_inet_actiontype_teleport, 0, 0, 0, 0, lanOrderRandKey0, lanOrderRandKey1,'battle.OnGUIMouseDown - Arena02');
      [*] = ;
      [*] = ;                     // to redraw brush under new hover unit
      [*] = ;                     gIntRegister_GUIBattleTooltipLastEndHexCell := 0;
      [*] = ;                     GUIExecuteState('battle.ResetHexGrid');
      [*] = ;                     GUIExecuteState('battle.UpdateHexGrid');
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var X, Y, Z : Float;
      [*] = ;               GetCurrentMouseWorldCoord(X,Y,Z);
      [*] = ;
      [*] = ;               var tnEndHandle : Integer = GetNearestTrackNodeHandle(x, z, -1);
      [*] = ;               GetTrackNodePositionByHandle(tnEndHandle, x, y, z);
      [*] = ;
      [*] = ;               var tnEndParser : Integer = _map_GetHexByTNHandle(tnEndHandle);
      [*] = ;
      [*] = ;               var endX : Integer = ParserGetIntValueByKeyByHandle(tnEndParser, 'X');
      [*] = ;               var endY : Integer = ParserGetIntValueByKeyByHandle(tnEndParser, 'Y');
      [*] = ;
      [*] = ;               if _log then _Log_gui(_log_name+' X = ' + IntToStr(endX) + '; ' + 'Y = ' + IntToStr(endY));
      [*] = ;               if ((GetPlayerIntValueIndByHandle(myPlHandle, gc_battle_PLStack_iAttackMode) = 1) and (endX < 2)) or
      [*] = ;               ((GetPlayerIntValueIndByHandle(myPlHandle, gc_battle_PLStack_iAttackMode) = 0) and (endX > gc_battle_GridSize - 2 - 1)) then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := endX;
      [*] = ;                  IntRegister1 := endY;
      [*] = ;                  BoolRegister0 := true;
      [*] = ;                  GameObjectExecuteStateByHandle(selGOHandle, 'Replace');
      [*] = ;
      [*] = ;                  if _log then
      [*] = ;                  begin
      [*] = ;                     var p : Integer;
      [*] = ;                     _log_values('S_PL_IO',GetPlayerHandleInterfaceIO(),0,0,0,0,0);
      [*] = ;                     p := gIntRegister_BattleAttackPlayer;
      [*] = ;                     _log_values('S_P1_UID|UID1|UID2|UID3',GetGameObjectUniqueIdByHandle(p),GetGameObjectUniqueIdByHandle(GetGameObjectHandleByIndex(0,p)),GetGameObjectUniqueIdByHandle(GetGameObjectHandleByIndex(1,p)),GetGameObjectUniqueIdByHandle(GetGameObjectHandleByIndex(2,p)),0,0);
      [*] = ;                     p := gIntRegister_BattleDefendPlayer;
      [*] = ;                     _log_values('S_P2_UID|UID1|UID2|UID3',GetGameObjectUniqueIdByHandle(p),GetGameObjectUniqueIdByHandle(GetGameObjectHandleByIndex(0,p)),GetGameObjectUniqueIdByHandle(GetGameObjectHandleByIndex(1,p)),GetGameObjectUniqueIdByHandle(GetGameObjectHandleByIndex(2,p)),0,0);
      [*] = ;                  end;
      [*] = ;
      [*] = ;                  _inet_CreateOrderParser(gIntRegister_SelectedUID, endX, endY, gc_inet_actiontype_teleport, 0, 0, 0, 0, lanOrderRandKey0, lanOrderRandKey1,'battle.OnGUIMouseDown - Arena03');
      [*] = ;               end;
      [*] = ;
      [*] = ;               gIntRegister_GUIBattleTooltipLastEndHexCell := 0;
      [*] = ;               GUIExecuteState('battle.ResetHexGrid');
      [*] = ;               GUIExecuteState('battle.UpdateHexGrid');
      [*] = ;            end;
      [*] = ;
      [*] = ;            gIntRegister_StartTrackNode := 0;
      [*] = ;            gIntRegister_SelectedUID := 0;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      GUIExecuteState('battle.DoDrawHexGrid');
      [*] = ;      GUIExecuteState('battle.CreateControlPanelWindow');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if tag = 102 then
      [*] = ;   begin
      [*] = ;      var pCurCell : Integer = gIntRegister_EndHexCell;
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_EndHexUID);
      [*] = ;      var visible : Boolean = GetGameObjectVisibleByHandle(goHandle);
      [*] = ;
      [*] = ;      if (actAbility<>0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := actAbility;
      [*] = ;         BoolRegister0 := true;
      [*] = ;         ExecuteState('ActivateAbility');
      [*] = ;         
      [*] = ;         GUIExecuteState('battle.CreateControlPanelWindow');
      [*] = ;         GUIExecuteState('battle.UpdateCursor');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (gIntRegister_EndHexUID<>0) and visible then
      [*] = ;      begin
      [*] = ;         var args : String = '';
      [*] = ;
      [*] = ;         _sa_AddAsInt(args,cFT_UnitBattle);
      [*] = ;         _sa_AddAsInt(args,gIntRegister_EndHexUID);
      [*] = ;         _sa_AddAsInt(args,0);
      [*] = ;         _sa_AddAsInt(args,0);
      [*] = ;         StringRegister0 := args;
      [*] = ;         GUIExecuteState('vvk.ShowUnitInfoModal');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var TerrainType : Integer = ParserGetIntValueByKeyByHandle(pCurCell, 'Type');
      [*] = ;         IntRegister0 := TerrainType;
      [*] = ;         GUIExecuteState('battle.GetTerrainInfoByType');
      [*] = ;         var msgID : Integer = IntRegister1;
      [*] = ;         var msgDescrID : Integer = IntRegister2;
      [*] = ;         var table : String = StringRegister0;
      [*] = ;         var tableDescr : String = StringRegister1;
      [*] = ;         var iconMat : String = StringRegister2;
      [*] = ;
      [*] = ;         StringRegister0 := GetLocaleTableListItemByID(table, IntToStr(msgID));
      [*] = ;         StringRegister1 := GetLocaleTableListItemByID(tableDescr, IntToStr(msgDescrID)+'.description');
      [*] = ;         StringRegister2 := iconMat;
      [*] = ;
      [*] = ;         GUIExecuteState('VVK.ShowInfoWindow');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if tag = 102 then
      [*] = ;   begin
      [*] = ;      //_log_values('EndHexUID|SelectedUID|EndTrackNode',gIntRegister_EndHexUID,gIntRegister_SelectedUID,gIntRegister_EndTrackNode,0,0,0);
      [*] = ;      if (gIntRegister_EndHexUID<>0) then
      [*] = ;      begin
      [*] = ;         var args : String = '';
      [*] = ;
      [*] = ;         _sa_AddAsInt(args,cFT_UnitBattle);
      [*] = ;         _sa_AddAsInt(args,gIntRegister_EndHexUID);
      [*] = ;         _sa_AddAsInt(args,0);
      [*] = ;         _sa_AddAsInt(args,0);
      [*] = ;         StringRegister0 := args;
      [*] = ;         GUIExecuteState('vvk.ShowUnitInfoModal');
      [*] = ;      end
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

