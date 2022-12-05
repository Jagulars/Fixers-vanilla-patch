section.begin
   Name = Initial
   UsedFileName = 
   Code : struct.begin
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var baseName : String = GetGameObjectMyBaseName;
      [*] = ;      
      [*] = ;if gc_LogRecycling then
      [*] = ;   _log_obj('Initial, '+baseName);
      [*] = ;      
      [*] = ;if (not gBoolRegister_Loading) then
      [*] = ;begin
      [*] = ;   var x, y, z : Float;
      [*] = ;   
      [*] = ;   var delayStateName : String = GetGameObjectDelayExecuteStateNameByHandle(myGOHandle);
      [*] = ;   if delayStateName <> '' then
      [*] = ;   begin
      [*] = ;      GameObjectMyCancelDelayExecuteState();
      [*] = ;      if gc_LogRecycling then
      [*] = ;         _log_obj('GetGameObjectDelayExecuteStateNameByHandle '+delayStateName);
      [*] = ;   end;
      [*] = ;      
      [*] = ;   if gc_LogRecycling then
      [*] = ;   begin
      [*] = ;      var animName : String = GetGameObjectMyFrameAnimationName;
      [*] = ;      if animName <> '' then
      [*] = ;         _log_obj('GetGameObjectMyFrameAnimationName '+animName);
      [*] = ;      
      [*] = ;      _obj_LogBehaviours(myGOHandle);
      [*] = ;      _obj_LogEffects(myGOHandle);
      [*] = ;   end;
      [*] = ;   
      [*] = ;   //x := GetGameObjectMyPositionX;
      [*] = ;   //y := GetGameObjectMyPositionY;
      [*] = ;   //z := GetGameObjectMyPositionZ;
      [*] = ;   
      [*] = ;   MyGameObjectPFXClear;
      [*] = ;   BehaviourClear(myGOHandle);
      [*] = ;   EffectClear(myGOHandle);
      [*] = ;   GameObjectMyResetRotations;
      [*] = ;   if GetGameObjectIsParent(myGOHandle) or (not SameText(GetGameObjectRaceNameByHandle(GetGameObjectParentHandle(myGOHandle)), 'misc')) then
      [*] = ;   begin
      [*] = ;      GameObjectMyResetAndPitchTurnRoll(90, 0, 0);
      [*] = ;      if gc_LogRecycling then
      [*] = ;         _log_obj('Root FX');
      [*] = ;   end;
      [*] = ;   //GameObjectMyRotateAbsolute(0, 0, 0);
      [*] = ;   //SetGameObjectMyPosition(x, y, z);
      [*] = ;   //SetGameObjectMyRollAngle(0.0);
      [*] = ;   //SetGameObjectMyTurnAngle(0.0);
      [*] = ;   //SetGameObjectMyPitchAngle(0.0);
      [*] = ;   
      [*] = ;   var frame : Integer = GetGameObjectMyCurrentFrame;
      [*] = ;   if frame <> 0 then
      [*] = ;   begin
      [*] = ;      SetGameObjectMyCurrentFrame(0);
      [*] = ;      if gc_LogRecycling then
      [*] = ;         _log_obj('GetGameObjectMyCurrentFrame '+IntToStr(frame));
      [*] = ;   end;
      [*] = ;   SetGameObjectMyAnimationMode('aamPlayOnce');
      [*] = ;   if (not GetGameObjectMyVisible) then
      [*] = ;   begin
      [*] = ;      ReloadGameObjectProperties(myGOHandle, GetGameObjectRaceNameByHandle(myGOHandle), baseName);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;SwitchTo('DoNothing');
   struct.end
section.end
