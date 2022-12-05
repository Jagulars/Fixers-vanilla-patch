section.begin
   Name = Initial
   Code : struct.begin
      [*] = ;var myHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myPlHnd  : Integer = GetGameObjectPlayerHandleByHandle(myHandle);
      [*] = ;var myBaseName : String = GetGameObjectMyBaseName();
      [*] = ;
      [*] = ;var scaleMod, speedScaleMod, animInterval : Float = 1;
      [*] = ;
      [*] = ;//if (GetVarsCount=0) or (GetGameObjectUniqueIdByHandle(myHandle)=0) or (not GetGameObjectMyPlayableObject) then
      [*] = ;begin
      [*] = ;   // Setup stack
      [*] = ;   ClearVariables();
      [*] = ;
      [*] = ;   if not gBoolRegister_Loading then
      [*] = ;   begin
      [*] = ;      const objectType = 'ShardHero';
      [*] = ;      _obj_ResetStackVariables(myHandle, objectType);
      [*] = ;   end;
      [*] = ;
      [*] = ;   SetGameObjectMyOnStateEndPointReached('EndPointReached');
      [*] = ;
      [*] = ;   var runNodeFX : String = '';
      [*] = ;
      [*] = ;   // unit type test
      [*] = ;   if (SameText(myBaseName, 'map.warrior')) then
      [*] = ;   begin
      [*] = ;      scaleMod := 0.69;
      [*] = ;      speedScaleMod := 0.77;
      [*] = ;      animInterval := 1.0725;
      [*] = ;      runNodeFX := 'fxwarrior';
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (SameText(myBaseName, 'map.scout')) then
      [*] = ;   begin
      [*] = ;      scaleMod := 0.69;
      [*] = ;      speedScaleMod := 1;
      [*] = ;      animInterval := 1.1625;
      [*] = ;      runNodeFX := 'fxscout';
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (SameText(myBaseName, 'map.commander')) then
      [*] = ;   begin
      [*] = ;      scaleMod := 0.69;
      [*] = ;      speedScaleMod := 1.05;
      [*] = ;      animInterval := 1.15;
      [*] = ;      runNodeFX := 'fxcommander';
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (SameText(myBaseName, 'map.wizard')) then
      [*] = ;   begin
      [*] = ;      scaleMod := 0.69;
      [*] = ;      speedScaleMod := 0.81;
      [*] = ;      animInterval := 1.05;
      [*] = ;      runNodeFX := 'fxwizard';
      [*] = ;   end;
      [*] = ;
      [*] = ;   SetGameObjectMyStateTargetPosition(GetGameObjectMyPositionX,GetGameObjectMyPositionY,GetGameObjectMyPositionZ);
      [*] = ;   GameObjectMyTrackPointClear;
      [*] = ;   SetGameObjectMyTrackPointMovementMode('mmNone');
      [*] = ;   SetGameObjectMyTargetRotatingMode('trmNone');
      [*] = ;   SetGameObjectMyAnimationControlerEnabled(true);
      [*] = ;   SetGameObjectMyAnimationCyclesMode('acmLoop');
      [*] = ;   SetGameObjectMyAnimationMode('aamLoop');
      [*] = ;   //SetGameObjectMyOnStateStartCyclesReached('OnStartCyclesReached');
      [*] = ;   //SetGameObjectMyOnStateEndCyclesReached('OnAnimationReached');
      [*] = ;   //SetGameObjectMyOnStateFBEndCyclesReached('OnAnimationReached');
      [*] = ;   SetGameObjectMyOnStateDistanceToPoint('', 0);
      [*] = ;   SetGameObjectMyTrackPointUseAnimationCycles(true);
      [*] = ;   //SetGameObjectMyOnStateDirectionReached('OnDirectionReached');
      [*] = ;   //SetGameObjectMyOnStateEndPointReached('EndPointReached');
      [*] = ;   //SetGameObjectTrackPointOnStatePresetSwitchReached(myHandle, 'OnPresetSwitch');
      [*] = ;   SetGameObjectSTOHandleByHandle(myHandle, 0);
      [*] = ;   SetGameObjectMyPlayableObject(True);
      [*] = ;   SetGameObjectMyTrackPointAnimationNames('walk', 'idle');
      [*] = ;   SetGameObjectMinFrameBlendByHandle(myHandle, 12);
      [*] = ;   SetGameObjectMaxFrameBlendByHandle(myHandle, 12);
      [*] = ;   SetGameObjectDeferredFrameBlendByHandle(myHandle, false);
      [*] = ;
      [*] = ;   SetGameObjectOnStateDestroyByHandle(myHandle, 'OnDestroy');
      [*] = ;
      [*] = ;   ExecuteState('Idle');
      [*] = ;   SetGameObjectMyCurrentFrame(Floor(Random*GetGameObjectEndFrameByHandle(myHandle)-1));
      [*] = ;
      [*] = ;   _fx_RunNodeFX(myHandle, runNodeFX);
      [*] = ;end;
      [*] = ;
      [*] = ;if not gBoolRegister_Loading then
      [*] = ;ExecuteState('CreateParser');
      [*] = ;
      [*] = ;SetGameObjectScaleByHandle(myHandle, GetGameObjectScaleXByHandle(myHandle)*scaleMod, GetGameObjectScaleYByHandle(myHandle)*scaleMod, GetGameObjectScaleZByHandle(myHandle)*scaleMod);
      [*] = ;var pMy : Integer = ParserSelectGameObject(myHandle);
      [*] = ;speedScaleMod := speedScaleMod*2;
      [*] = ;animInterval := animInterval*2;
      [*] = ;ParserSetFloatValueByKeyByHandle(pMy, 'TPMoveStep', GetGameObjectTrackPointMoveStepByHandle(myHandle)*speedScaleMod);
      [*] = ;ParserSetFloatValueByKeyByHandle(pMy, 'WalkAnimIntervalFactor', animInterval);
      [*] = ;ParserSetFloatValueByKeyByHandle(pMy, 'TPTurnStep', GetGameObjectTrackPointTurnStepByHandle(myHandle)*speedScaleMod);
      [*] = ;
      [*] = ;var effHnd : Integer = GetEffectByKey(myHandle, 'alphaFadeAroundEffect');
      [*] = ;if (effHnd=0) then
      [*] = ;effHnd := EffectCreateWithKey(myHandle, 'TXAlphaFadeAroundEffect', 'alphaFadeAroundEffect', False);
      [*] = ;var boundSphere : Float = GetGameObjectBoundingSphereByHandle(myHandle);
      [*] = ;SetBehaviourFloatProperty(effHnd, 'FilterBoundMin', boundSphere*0.3);
      [*] = ;SetBehaviourFloatProperty(effHnd, 'FilterBoundMax', boundSphere*0.8);
      [*] = ;SetBehaviourStringProperty(effHnd, 'FilterPlrNameAdd', 'PlTrack');
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

