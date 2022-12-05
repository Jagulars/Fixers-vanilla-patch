section.begin
   Name = Initial
   Description[*] = ;// gStringRegister_fxTree_NodeName - node name to start
   UsedFileName = 
   Code : struct.begin
      [*] = ;// gStringRegister_fxTree_NodeName - node name to start
      [*] = ;var x, y, z, x2, y2, z2, fValue : Float;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var parent : Integer = GetGameObjectParentHandle(myGOHandle);
      [*] = ;if gc_LogRecycling then
      [*] = ;begin
      [*] = ;   _obj_LogBehaviours(myGOHandle);
      [*] = ;   _obj_LogEffects(myGOHandle);
      [*] = ;end;
      [*] = ;if (not gBoolRegister_Loading) then
      [*] = ;begin
      [*] = ;//GameObjectMyCancelDelayExecuteState();
      [*] = ;//_log_obj('fx GetGameObjectDelayExecuteStateNameByHandle '+GetGameObjectDelayExecuteStateNameByHandle(myGOHandle));
      [*] = ;if (not GetGameObjectIsParent(myGOHandle)) and gc_LogRecycling then
      [*] = ;begin
      [*] = ;   _log_obj('parentHandle: '+IntToStr(parent)+', parentName: '+GetGameObjectBaseNameByHandle(parent));
      [*] = ;end;
      [*] = ;//GetGameObjectOrientationByHandle(myGOHandle,x,y,z,x2,y2,z2);
      [*] = ;//_log_obj('       UpX: '+FloatToStr(x)+' UpY: '+FloatToStr(y)+' UpZ: '+FloatToStr(z)+' DirX: '+FloatToStr(x2)+' DirY: '+FloatToStr(y2)+' DirZ: '+FloatToStr(z2));
      [*] = ;
      [*] = ;
      [*] = ;//_log_obj('CustomName '+GetGameObjectCustomNameByHandle(myGOHandle));
      [*] = ;//GetGameObjectAbsolutePositionByHandle(myGOHandle, x, y, z);
      [*] = ;//_log_obj('AbsolutePosition X: '+FloatToStr(x)+' Y: '+FloatToStr(y)+' Z: '+FloatToStr(z));
      [*] = ;//_log_obj('StateMachineInterval '+IntToStr(GetGameObjectStateMachineIntervalByHandle(myGOHandle)));
      [*] = ;//_log_obj('StateMachineActive '+BoolToStr(GetGameObjectStateMachineActiveByHandle(myGOHandle)));
      [*] = ;//_log_obj('OnStateDestroy '+GetGameObjectOnStateDestroyByHandle(myGOHandle));
      [*] = ;//_log_obj('DeferredFrameBlend '+BoolToStr(GetGameObjectDeferredFrameBlendByHandle(myGOHandle)));
      [*] = ;//_log_obj('MinFrameBlend '+IntToStr(GetGameObjectMinFrameBlendByHandle(myGOHandle)));
      [*] = ;//_log_obj('MaxFrameBlend '+IntToStr(GetGameObjectMaxFrameBlendByHandle(myGOHandle)));
      [*] = ;//_log_obj('AnimationMode '+GetGameObjectAnimationModeByHandle(myGOHandle));
      [*] = ;//_log_obj('AnimationCyclesList '+GetGameObjectAnimationCyclesListByHandle(myGOHandle));
      [*] = ;//_log_obj('AnimationControlerEnabled '+BoolToStr(GetGameObjectAnimationControlerEnabledByHandle(myGOHandle)));
      [*] = ;//_log_obj('AnimationCyclesMode '+BoolToStr(GetGameObjectAnimationCyclesModeByHandle(myGOHandle)));
      [*] = ;//_log_obj('UseIdentityMatrix '+BoolToStr(GetGameObjectUseIdentityMatrix(myGOHandle)));
      [*] = ;//_log_obj('UseNoChildrenRecTransformationChanged '+BoolToStr(GetGameObjectUseNoChildrenRecTransformationChanged(myGOHandle)));
      [*] = ;//GetGameObjectOrientationByHandle(myGOHandle,x,y,z,x2,y2,z2);
      [*] = ;//_log_obj('  AFTER UpX: '+FloatToStr(x)+' UpY: '+FloatToStr(y)+' UpZ: '+FloatToStr(z)+' DirX: '+FloatToStr(x2)+' DirY: '+FloatToStr(y2)+' DirZ: '+FloatToStr(z2));
      [*] = ;
      [*] = ;
      [*] = ;// setup stack
      [*] = ;ClearVariables;
      [*] = ;const objectType = 'FX';
      [*] = ;_obj_ResetStackVariables(myGOHandle, objectType);
      [*] = ;   
      [*] = ;
      [*] = ;//SetFloatValueByName('borntime', GetGameTime());
      [*] = ;//SetValueByName('nodename', nodeName);
      [*] = ;//SetValueByName('nextnode', gStringRegister_fxTree_NodeName);
      [*] = ;//SetIntValueByName('nodetarget', gIntRegister_fxTree_NodeTarget);
      [*] = ;//SetFloatValueByName('coordtargetx', gFloatRegister_fxTree_CoordTargetX);
      [*] = ;//SetFloatValueByName('coordtargety', gFloatRegister_fxTree_CoordTargetY);
      [*] = ;//SetFloatValueByName('coordtargetz', gFloatRegister_fxTree_CoordTargetZ);
      [*] = ;//SetFloatValueByName('sleepTime', gFloatRegister_fxTree_SleepTime);
      [*] = ;
      [*] = if (GetGameObjectUniqueIdByHandle(myGOHandle)<=0) then
      [*] = ;begin
      [*] = ;   GameObjectMakeUniqId(myGOHandle);
      [*] = ;
      [*] = ;   SetGameObjectMyPlayableObject(False);
      [*] = ;   SetGameObjectOnStateStartFrameReachedByHandle(myGOHandle, 'OnStartFrameReached');
      [*] = ;   SetGameObjectOnStateEndFrameReachedByHandle(myGOHandle, 'OnEndFrameReached');
      [*] = ;   SetGameObjectOnStateStartCyclesReachedByHandle(myGOHandle, 'OnStartCyclesReached');
      [*] = ;   SetGameObjectOnStateEndCyclesReachedByHandle(myGOHandle, 'OnEndCyclesReached');
      [*] = ;   SetGameObjectOnStateFBEndCyclesReachedByHandle(myGOHandle, 'OnEndCyclesFBReached');
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   MyGameObjectPFXClear;
      [*] = ;   BehaviourClear(myGOHandle);
      [*] = ;   EffectClear(myGOHandle);
      [*] = ;   ParserClearByHandle(ParserSelectGameObject(myGOHandle));
      [*] = ;   if (not GetGameObjectMyVisible) then
      [*] = ;      ReloadGameObjectProperties(myGOHandle, GetGameObjectRaceNameByHandle(myGOHandle), GetGameObjectMyBaseName);
      [*] = ;   
      [*] = ;      GameObjectMyResetRotations;
      [*] = ;   if GetGameObjectIsParent(myGOHandle) or (not SameText(GetGameObjectRaceNameByHandle(parent), 'misc')) then
      [*] = ;   begin
      [*] = ;      if gc_LogRecycling then
      [*] = ;         _log_obj('Root FX');
      [*] = ;      GameObjectMyResetAndPitchTurnRoll(90, 0, 0);
      [*] = ;   end;
      [*] = ;   //ExecuteState('DoCleanSafe');
      [*] = ;   //GetGameObjectAbsolutePositionByHandle(myGOHandle, x, y, z);
      [*] = ;   //x := GetGameObjectMyPositionX;
      [*] = ;   //y := GetGameObjectMyPositionY;
      [*] = ;   //z := GetGameObjectMyPositionZ;
      [*] = ;   //x := GetGameObjectMyTransformedVirtualDirectionX;
      [*] = ;   //y := GetGameObjectMyTransformedVirtualDirectionY;
      [*] = ;   //z := GetGameObjectMyTransformedVirtualDirectionZ;
      [*] = ;    //  _log_obj('x before '+FloatToStr(x));
      [*] = ;    //  _log_obj('y before '+FloatToStr(y));
      [*] = ;    //  _log_obj('z before '+FloatToStr(z));
      [*] = ;   //SetGameObjectMyPosition(x, y, z);
      [*] = ;   //SetGameObjectAbsolutePositionByHandle(myGOHandle, x, y, z);
      [*] = ;    //  _log_obj('x after '+FloatToStr(GetGameObjectMyTransformedVirtualDirectionX));
      [*] = ;    //  _log_obj('y after '+FloatToStr(GetGameObjectMyTransformedVirtualDirectionY));
      [*] = ;    //  _log_obj('z after '+FloatToStr(GetGameObjectMyTransformedVirtualDirectionZ));
      [*] = ;   
      [*] = ;   fValue := GetGameObjectPitchAngleByHandle(myGOHandle);
      [*] = ;   if fValue <> 0 then
      [*] = ;   begin
      [*] = ;      if gc_LogRecycling then
      [*] = ;      _log_obj('PitchAngle '+FloatToStr(fValue));
      [*] = ;      GameObjectMyPitch(-fValue);
      [*] = ;   end;
      [*] = ;   fValue := GetGameObjectTurnAngleByHandle(myGOHandle);
      [*] = ;   if fValue <> 0 then
      [*] = ;   begin
      [*] = ;      if gc_LogRecycling then
      [*] = ;      _log_obj('TurnAngle '+FloatToStr(fValue));
      [*] = ;      GameObjectMyTurn(-fValue);
      [*] = ;   end;
      [*] = ;   fValue := GetGameObjectRollAngleByHandle(myGOHandle);
      [*] = ;   if fValue <> 0 then
      [*] = ;   begin
      [*] = ;      if gc_LogRecycling then
      [*] = ;      _log_obj('RollAngle '+FloatToStr(fValue));
      [*] = ;      GameObjectMyRoll(-fValue);
      [*] = ;   end;
      [*] = ;   //SetGameObjectMyRollAngle(0.0);
      [*] = ;  // SetGameObjectMyTurnAngle(0.0);
      [*] = ;  // SetGameObjectMyPitchAngle(0.0);
      [*] = ;   //SetGameObjectMyScale(1.0, 1.0, 1.0);
      [*] = ;   //SetGameObjectUseIdentityMatrix(myGOHandle, True);
      [*] = ;   //SetGameObjectUseNoChildrenRecTransformationChanged(myGOHandle, False);
      [*] = ;   //   GameObjectRootSetupIdentityRecTransformationByHandle(myGOHandle);
      [*] = ;   //SetGameObjectMyVisible(True);
      [*] = ;//_log_obj('CollisionDetection '+BoolToStr(GetGameObjectMyCollisionDetection)); // trying to acquire collision data causes access violation
      [*] = ;//_log_obj('CollidedStateName '+GetGameObjectMyCollidedStateName);
      [*] = ;//_log_obj('UnCollidedStateName '+GetGameObjectMyUnCollidedStateName);
      [*] = ;//_log_obj('CollisionPriority '+IntToStr(GetGameObjectCollisionPriorityByHandle(myGOHandle)));
      [*] = ;
      [*] = ;   if (GetGameObjectIsParent(myGOHandle)) then
      [*] = ;   begin
      [*] = ;      SetGameObjectUseIdentityMatrix(myGOHandle, False);
      [*] = ;      SetGameObjectUseNoChildrenRecTransformationChanged(myGOHandle, True);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      SetGameObjectUseIdentityMatrix(myGOHandle, False);
      [*] = ;      SetGameObjectUseNoChildrenRecTransformationChanged(myGOHandle, True);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;SetGameObjectMyStateTargetPosition(GetGameObjectMyPositionX, GetGameObjectMyPositionY, GetGameObjectMyPositionZ);
      [*] = ;SetGameObjectSTOHandleByHandle(myGOHandle, 0);
      [*] = ;
      [*] = ;{if (GetGameObjectIsParent(myGOHandle)) then
      [*] = ;begin
      [*] = ;   //SetGameObjectMyCollisionDetection(True);
      [*] = ;   //SetGameObjectMyCollidedStateName('OnCollided');
      [*] = ;   //SetGameObjectMyUncollidedStateName('OnUncollided');
      [*] = ;   //SetGameObjectCollisionPriorityByHandle(myGOHandle, 1000);
      [*] = ;
      [*] = ;   //SetGameObjectMyRuleCollidedExecFr(5, 90.0, False); // All sectors
      [*] = ;   //SetGameObjectMyRuleCollidedExecEn(5, 90.0, False); // All sectors
      [*] = ;   //SetGameObjectMyRuleCollidedExecNl(5, 90.0, False); // All sectors
      [*] = ;   //SetGameObjectMyRuleUnCollidedExecFr(5, 90.0, False); // All sectors
      [*] = ;   //SetGameObjectMyRuleUnCollidedExecEn(5, 90.0, False); // All sectors
      [*] = ;   //SetGameObjectMyRuleUnCollidedExecNl(5, 90.0, False); // All sectors
      [*] = ; //_log_obj('CollisionDetection '+BoolToStr(GetGameObjectMyCollisionDetection));
      [*] = ;
      [*] = ;   SetGameObjectUseIdentityMatrix(myGOHandle, False);
      [*] = ;   SetGameObjectUseNoChildrenRecTransformationChanged(myGOHandle, True);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   //SetGameObjectMyCollisionDetection(False); // causes access violation
      [*] = ;   SetGameObjectUseIdentityMatrix(myGOHandle, False);
      [*] = ;   SetGameObjectUseNoChildrenRecTransformationChanged(myGOHandle, True);
      [*] = ;end;}
      [*] = ; //  SetGameObjectUseIdentityMatrix(myGOHandle, True);
      [*] = ;  // SetGameObjectUseNoChildrenRecTransformationChanged(myGOHandle, False);
      [*] = ;//      GameObjectRootSetupIdentityRecTransformationByHandle(myGOHandle);
      [*] = ;//SetGameObjectMyStatesTagForceUpdate;
      [*] = ;//ResetGameObjectPrevStatesTagByHandle(myGOHandle);
      [*] = ;
      [*] = ;//SetGameObjectOnStateStartFrameReachedByHandle(myGOHandle, 'OnStartFrameReached');
      [*] = ;//SetGameObjectOnStateEndFrameReachedByHandle(myGOHandle, 'OnEndFrameReached');
      [*] = ;//SetGameObjectOnStateStartCyclesReachedByHandle(myGOHandle, 'OnStartCyclesReached');
      [*] = ;//SetGameObjectOnStateEndCyclesReachedByHandle(myGOHandle, 'OnEndCyclesReached');
      [*] = ;//SetGameObjectOnStateFBEndCyclesReachedByHandle(myGOHandle, 'OnEndCyclesFBReached');
      [*] = ;
      [*] = ;SetGameObjectOnStateDestroyByHandle(myGOHandle, 'OnDestroy');
      [*] = ;
      [*] = ;var nextNode : String = GetValueByName('nextnode');
      [*] = ;if _log_Recycling then
      [*] = ;   _log_obj('fx Initial '+IntToStr(myGOHandle)+' nextNode: '+nextNode);
      [*] = ;if (nextNode<>'') then
      [*] = ;ExecuteState('DoNextNode');
      [*] = ;
      [*] = ;end;
      [*] = ;
      [*] = ;gStringRegister_fxTree_NodeName := '';
      [*] = ;gIntRegister_fxTree_NodeTarget := 0;
      [*] = ;gFloatRegister_fxTree_CoordTargetX := 0;
      [*] = ;gFloatRegister_fxTree_CoordTargetY := 0;
      [*] = ;gFloatRegister_fxTree_CoordTargetZ := 0;
      [*] = ;gFloatRegister_fxTree_SleepTime := 0;
      [*] = ;
      [*] = ;SwitchTo('DoNothing');
   struct.end
section.end

