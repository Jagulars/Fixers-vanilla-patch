section.begin
   Name = battle.UpdateCursor
   Code : struct.begin
      [*] = ;var bUnit : Boolean = false;
      [*] = ;
      [*] = ;var myPlHandle : Integer = GetPlayerHandleInterfaceIO;
      [*] = ;
      [*] = ;var x, y, z : Float;
      [*] = ;GetCurrentMouseWorldCoord(x,y,z);
      [*] = ;
      [*] = ;var curX, curY, curZ : Float;
      [*] = ;GetTrackNodePositionByHandle(gIntRegister_EndTrackNode, curX, curY, curZ);
      [*] = ;
      [*] = ;if GetGUIElementUnderMouse() = 0 then
      [*] = ;begin
      [*] = ;   GUIExecuteState('battle.IsLockMode');
      [*] = ;   var lockMode : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;   if lockMode then
      [*] = ;      SetGUICursorByName('crHourGlass')
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var pHexHandle : Integer = gIntRegister_EndHexCell;
      [*] = ;      var goUID : Integer = ParserGetIntValueByKeyByHandle(pHexHandle, 'UID');
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByUniqueId(goUID);
      [*] = ;
      [*] = ;      IntRegister0 := pHexHandle;
      [*] = ;      FloatRegister0 := x;
      [*] = ;      FloatRegister1 := z;
      [*] = ;      MapExecuteState('bat.IsPointInHex');
      [*] = ;      if BoolRegister0 then
      [*] = ;      begin
      [*] = ;         if (not gBoolRegister_BattlePlaceMode) and (gIntRegister_BattleCurPlIndex <> GetPlayerIndexByHandle(myPlHandle)) then
      [*] = ;            SetGUICursorByName('crHourGlass')
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var selGOHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_SelectedUID);
      [*] = ;            var actAbility : Integer = GetGameObjectIntValueIndByHandle(selGOHandle, gc_stack_unit_iActiveAbility);
      [*] = ;
      [*] = ;            if gIntRegister_CurSpell > 0 then
      [*] = ;            begin
      [*] = ;               var canCast : Boolean = false;
      [*] = ;
      [*] = ;               var pSpell : Integer = ParserSelectByHandleByIndex(gPrototypeData.spells.handle, gIntRegister_CurSpell);
      [*] = ;               var pEffects : Integer = ParserSelectByHandleByKey(pSpell, 'Effects');
      [*] = ;               var pEffect : Integer = ParserSelectByHandleByIndex(pEffects, 0);
      [*] = ;               var abilID : Integer = ParserGetIntValueByKeyByHandle(pEffect, 'AbilityID');
      [*] = ;               var bSacrifice : Boolean = ParserGetBoolValueByKeyByHandle(pSpell, 'Sacrifice');
      [*] = ;
      [*] = ;               if bSacrifice and (gIntRegister_SacrificeUID = 0) then
      [*] = ;               begin
      [*] = ;                  if goHandle <> 0 then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := gIntRegister_CurSpell;
      [*] = ;                     IntRegister1 := gIntRegister_SelectedUID;
      [*] = ;                     GameObjectExecuteStateByHandle(goHandle, 'IsSacrifice');
      [*] = ;                     canCast := BoolRegister0;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               // teleport
      [*] = ;               if (abilID = gc_ability_teleport) then
      [*] = ;               begin
      [*] = ;                  if gIntRegister_TeleportUID = 0 then
      [*] = ;                  begin
      [*] = ;                     if goHandle <> 0 then
      [*] = ;                     begin
      [*] = ;                        IntRegister0 := gIntRegister_SelectedUID;
      [*] = ;                        GameObjectExecuteStateByHandle(goHandle, 'IsTeleportTarget');
      [*] = ;                        canCast := BoolRegister0;
      [*] = ;                     end;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := gIntRegister_TeleportUID;
      [*] = ;                     IntRegister1 := pHexHandle;
      [*] = ;                     MapExecuteState('bat.IsTeleportHex');
      [*] = ;                     canCast := BoolRegister0;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  IntRegister0 := gIntRegister_CurSpell;
      [*] = ;                  IntRegister1 := pHexHandle;
      [*] = ;                  GameObjectExecuteStateByHandle(selGOHandle, 'CanCastSpell');
      [*] = ;                  canCast := BoolRegister0;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if not canCast then
      [*] = ;                  SetGUICursorByName('crInvMagic')
      [*] = ;               else
      [*] = ;                  SetGUICursorByName('crMagic');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if (actAbility = gc_ability_healing) or (actAbility = gc_ability_repair) then
      [*] = ;            begin
      [*] = ;               var goHandle : Integer = GetGameObjectHandleByUniqueId(goUID);
      [*] = ;               if actAbility = gc_ability_healing then
      [*] = ;                  IntRegister0 := 0
      [*] = ;               else
      [*] = ;                  IntRegister0 := 1;
      [*] = ;               GameObjectExecuteStateByHandle(goHandle, 'IsHealTarget');
      [*] = ;               if (IntRegister1 = 2) and (goUID<>0) and (GetGameObjectPlayerHandleByHandle(goHandle)=myPlHandle) then
      [*] = ;                  SetGUICursorByName('crMagic')
      [*] = ;               else
      [*] = ;                  SetGUICursorByName('crInvMagic')
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var goUID : Integer = ParserGetIntValueByKeyByHandle(pHexHandle, 'UID');
      [*] = ;               var bCanAct : Boolean = GetGameObjectBoolValueIndByHandle(selGOHandle, gc_stack_unit_bCanAct);
      [*] = ;
      [*] = ;               if (goUID<>0) then
      [*] = ;               begin
      [*] = ;                  bUnit := true;
      [*] = ;                  var goHandle : Integer = GetGameObjectHandleByUniqueId(goUID);
      [*] = ;                  var plHandle : Integer = GetGameObjectPlayerHandleByHandle(goHandle);
      [*] = ;
      [*] = ;                  if (plHandle=myPlHandle) then
      [*] = ;                  begin
      [*] = ;                     if (goUID=gIntRegister_SelectedUID) then
      [*] = ;                     begin
      [*] = ;                        GameObjectExecuteStateByHandle(goHandle, 'IsStand');
      [*] = ;                        var isStand : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;                        var wX, wY, wZ : Float;
      [*] = ;                        var nearX, nearY, nearZ : Float;
      [*] = ;                        GetCurrentMouseWorldCoord(wX, wY, wZ);
      [*] = ;                        GetTrackNodePositionByHandle(gIntRegister_BeforeEndTrackNode, nearX, nearY, nearZ);
      [*] = ;                        var dist : Float = VectorDistance(wX, 0, wZ, nearX, 0, nearZ);
      [*] = ;                        if (not gBoolRegister_BattlePlaceMode) and (isStand) and (dist>gc_gui_unit_minturncursordist) then
      [*] = ;                        begin
      [*] = ;                           var angle : Float = VectorAngle(wX-nearX, 0, wZ-nearZ, 1, 0, 0);
      [*] = ;                           var ind : Integer = Round(angle / 60);
      [*] = ;
      [*] = ;                           if (wZ-nearZ<0) and ((ind=1) or (ind=2)) then
      [*] = ;                              ind := 6 - ind;
      [*] = ;
      [*] = ;                           var cursorName : String;
      [*] = ;                           case ind of
      [*] = ;                              0 : cursorName := 'crTurnLeft';
      [*] = ;                              1 : cursorName := 'crTurnLeftTop';
      [*] = ;                              2 : cursorName := 'crTurnRightTop';
      [*] = ;                              3 : cursorName := 'crTurnRight';
      [*] = ;                              4 : cursorName := 'crTurnRightBottom';
      [*] = ;                              5 : cursorName := 'crTurnLeftBottom';
      [*] = ;                           end;
      [*] = ;                           SetGUICursorByName(cursorName);
      [*] = ;                        end
      [*] = ;                        else
      [*] = ;                           SetGUICursorByName('crHand');
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                        SetGUICursorByName('crHand');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     //var selGOHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_SelectedUID);
      [*] = ;                     if selGOHandle <> 0 then
      [*] = ;                     begin
      [*] = ;                        var isShoot, isShootable : Boolean;
      [*] = ;
      [*] = ;                        _unit_IsMyShootEndPoint(selGOHandle, gIntRegister_EndTrackNode, gBoolRegister_BattlePlaceMode, isShoot, isShootable);
      [*] = ;
      [*] = ;                        if isShoot and GetGameObjectBoolValueIndByHandle(selGOHandle, gc_stack_unit_bCanShoot) and (not GetBoolValueByName('KeyPressedCtrl')) then
      [*] = ;                           SetGUICursorByName('crFire')
      [*] = ;                        else
      [*] = ;                        begin
      [*] = ;                           var endPointValid : Boolean;
      [*] = ;                           var goEnemyUID : Integer;
      [*] = ;
      [*] = ;                           _unit_IsValidEndPoint(selGOHandle, gIntRegister_EndTrackNode, true, false, endPointValid, goEnemyUID);
      [*] = ;
      [*] = ;                           if endPointValid then
      [*] = ;                           begin
      [*] = ;                              var bCanMelee : Boolean = GetGameObjectBoolValueIndByHandle(selGOHandle, gc_stack_unit_bCanMelee);
      [*] = ;                              if bCanMelee and bCanAct and (_unit_CheckAbility(selGOHandle, gc_ability_does_not_fight) = 0) then
      [*] = ;                              begin
      [*] = ;                                 var nearX, nearY, nearZ : Float;
      [*] = ;                                 GetTrackNodePositionByHandle(gIntRegister_BeforeEndTrackNode, nearX, nearY, nearZ);
      [*] = ;
      [*] = ;                                 var angle : Float = VectorAngle(nearX - curX, 0, nearZ - curZ, 1, 0, 0);
      [*] = ;                                 var ind : Integer = Round(angle / 60);
      [*] = ;
      [*] = ;                                 if nearZ - curZ < 0 then
      [*] = ;                                    ind := 6 - ind;
      [*] = ;
      [*] = ;                                 var goX : Integer = GetGameObjectIntValueIndByHandle(selGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;                                 var goY : Integer = GetGameObjectIntValueIndByHandle(selGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;                                 var endX : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX);
      [*] = ;                                 var endY : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY);
      [*] = ;                                 var dist : Integer = _misc_GetHexDist(goX, goY, endX, endY);
      [*] = ;
      [*] = ;                                 var cursorName : String;
      [*] = ;                                 var lunge : Boolean = GetGameObjectBoolValueIndByHandle(selGOHandle, gc_stack_unit_bLunge);
      [*] = ;
      [*] = ;                                 if lunge and (dist = 2) then
      [*] = ;                                    cursorName := 'crAttack'
      [*] = ;                                 else
      [*] = ;                                 case ind of
      [*] = ;                                    0 : cursorName := 'crAttackRight';
      [*] = ;                                    1 : cursorName := 'crAttackRightBottom';
      [*] = ;                                    2 : cursorName := 'crAttackLeftBottom';
      [*] = ;                                    3 : cursorName := 'crAttackLeft';
      [*] = ;                                    4 : cursorName := 'crAttackLeftTop';
      [*] = ;                                    5 : cursorName := 'crAttackRightTop';
      [*] = ;                                 end;
      [*] = ;                                 SetGUICursorByName(cursorName);
      [*] = ;                              end
      [*] = ;                              else
      [*] = ;                                 SetGUICursorByName('crInvAttack');
      [*] = ;                           end
      [*] = ;                           else
      [*] = ;                           begin
      [*] = ;                              IntRegister0 := gc_battle_unit_iRangedAttack;
      [*] = ;                              GameObjectExecuteStateByHandle(selGOHandle, 'GetProperty');
      [*] = ;                              if ((IntRegister1>0) and (GetGameObjectIntValueIndByHandle(selGOHandle, gc_stack_unit_iCurAmmo)>0)) and (not IsShoot) then
      [*] = ;                                 SetGUICursorByName('crInvFire')
      [*] = ;                              else
      [*] = ;                                 SetGUICursorByName('crInvAttack');
      [*] = ;                           end;
      [*] = ;                        end;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                        SetGUICursorByName('crDefault'); // no one selected and undermouse is enemy unit
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;
      [*] = ;               if not bUnit then
      [*] = ;               begin
      [*] = ;                  if gIntRegister_SelectedUID <> 0 then
      [*] = ;                  begin
      [*] = ;                     var X, Y, Z : Float;
      [*] = ;                     GetCurrentMouseWorldCoord(X,Y,Z);
      [*] = ;                     var tnHandle : Integer = GetNearestTrackNodeHandle(x, z, -1);
      [*] = ;
      [*] = ;                     var selGOHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_SelectedUID);
      [*] = ;                     var endPointValid : Boolean;
      [*] = ;                     var goEnemyUID : Integer;
      [*] = ;                     _unit_IsValidEndPoint(selGOHandle, tnHandle, true, false, endPointValid, goEnemyUID);
      [*] = ;
      [*] = ;                     if endPointValid then
      [*] = ;                        SetGUICursorByName('crMove')
      [*] = ;                     else
      [*] = ;                        SetGUICursorByName('crInvMove');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                     SetGUICursorByName('crDefault');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         SetGUICursorByName('crDefault'); // not on battlefield and not on GUI Element
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   var elmCursor : Integer = GetGUIElementCursorByIndex(GetGUIElementUnderMouse);
      [*] = ;   if (elmCursor>0) then
      [*] = ;      SetGUICursorByIndex(elmCursor)
      [*] = ;   else
      [*] = ;      SetGUICursorByName('crDefault');
      [*] = ;end;
   struct.end
section.end

