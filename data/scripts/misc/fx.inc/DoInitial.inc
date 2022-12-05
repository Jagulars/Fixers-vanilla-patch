section.begin
   Name = DoInitial
   Description[*] = ;// gStringRegister_fxTree_NodeName - node name to start
   UsedFileName = 
   Code : struct.begin
      [*] = ;// gStringRegister_fxTree_NodeName - node name to start
      [*] = ;var nextNode : String = gStringRegister_fxTree_NodeName; // order to nextNode
      [*] = ;
      [*] = ;var goMyHnd : Integer = GetGameObjectMyHandle;
      [*] = ;
      [*] = ;ClearVariables;
      [*] = ;const objectType = 'FX';
      [*] = ;_obj_ResetStackVariables(goMyHnd, objectType);
      [*] = ;
      [*] = ;if (GetGameObjectUniqueIdByHandle(goMyHnd)<=0) then
      [*] = ;GameObjectMakeUniqId(goMyHnd);
      [*] = ;
      [*] = ;SetGameObjectMyStateTargetPosition(GetGameObjectMyPositionX, GetGameObjectMyPositionY, GetGameObjectMyPositionZ);
      [*] = ;SetGameObjectSTOHandleByHandle(goMyHnd, 0);
      [*] = ;
      [*] = ;SetGameObjectMyPlayableObject(False);
      [*] = ;if (GetGameObjectIsParent(goMyHnd)) then
      [*] = ;begin
      [*] = ;   SetGameObjectMyCollisionDetection(True);
      [*] = ;   SetGameObjectMyCollidedStateName('OnCollided');
      [*] = ;   SetGameObjectMyUncollidedStateName('OnUncollided');
      [*] = ;   SetGameObjectCollisionPriorityByHandle(goMyHnd, 1000);
      [*] = ;
      [*] = ;   SetGameObjectMyRuleCollidedExecFr(5, 90.0, False); // All sectors
      [*] = ;   SetGameObjectMyRuleCollidedExecEn(5, 90.0, False); // All sectors
      [*] = ;   SetGameObjectMyRuleCollidedExecNl(5, 90.0, False); // All sectors
      [*] = ;   SetGameObjectMyRuleUnCollidedExecFr(5, 90.0, False); // All sectors
      [*] = ;   SetGameObjectMyRuleUnCollidedExecEn(5, 90.0, False); // All sectors
      [*] = ;   SetGameObjectMyRuleUnCollidedExecNl(5, 90.0, False); // All sectors
      [*] = ;end;
      [*] = ;
      [*] = ;//SetGameObjectMyStatesTagForceUpdate;
      [*] = ;//ResetGameObjectPrevStatesTagByHandle(goMyHnd);
      [*] = ;
      [*] = ;SetGameObjectOnStateStartFrameReachedByHandle(goMyHnd, 'OnStartFrameReached');
      [*] = ;SetGameObjectOnStateEndFrameReachedByHandle(goMyHnd, 'OnEndFrameReached');
      [*] = ;SetGameObjectOnStateStartCyclesReachedByHandle(goMyHnd, 'OnStartCyclesReached');
      [*] = ;SetGameObjectOnStateEndCyclesReachedByHandle(goMyHnd, 'OnEndCyclesReached');
      [*] = ;SetGameObjectOnStateFBEndCyclesReachedByHandle(goMyHnd, 'OnEndCyclesFBReached');
      [*] = ;
      [*] = ;SetGameObjectOnStateDestroyByHandle(goMyHnd, 'OnDestroy');
      [*] = ;
      [*] = ;if (nextNode<>'') then
      [*] = ;ExecuteState('DoNextNode');
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

