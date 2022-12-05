section.begin
   Name = Initial
   Code : struct.begin
      [*] = ;if gc_RecycleProjectiles and gc_LogRecycling then
      [*] = ;   Log('Initial, '+GetGameObjectMyBaseName);
      [*] = ;
      [*] = ;if (not gBoolRegister_Loading) then
      [*] = ;begin
      [*] = ;   var myHandle : Integer = GetGameObjectMyHandle;
      [*] = ;   if gc_RecycleProjectiles then
      [*] = ;   begin
      [*] = ;      if gc_LogRecycling then
      [*] = ;      begin
      [*] = ;         _obj_LogBehaviours(myHandle);
      [*] = ;         _obj_LogEffects(myHandle);
      [*] = ;      end;
      [*] = ;      GameObjectMyCancelDelayExecuteState;
      [*] = ;      MyGameObjectPFXClear;
      [*] = ;      BehaviourClear(myHandle);
      [*] = ;      EffectClear(myHandle);
      [*] = ;      if (not GetGameObjectMyVisible) then
      [*] = ;      begin
      [*] = ;         //if gc_LogRecycling then
      [*] = ;         //   Log('Reload object properties');
      [*] = ;         //ReloadGameObjectProperties(myHandle, GetGameObjectRaceNameByHandle(myHandle), GetGameObjectMyBaseName); // causes access violation for some reason
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   ClearVariables();
      [*] = ;   const objectType = 'Projectile';
      [*] = ;   _obj_ResetStackVariables(myHandle, objectType);
      [*] = ;
      [*] = ;   //GameObjectMakeUniqId(GetGameObjectMyHandle);
      [*] = ;
      [*] = ;   SetGameObjectMyRuleCollidedExecFr(5, 90.0, False); // Front with 35 fov
      [*] = ;   SetGameObjectMyRuleCollidedExecEn(5, 90.0, False); // All sectors
      [*] = ;   SetGameObjectMyRuleCollidedExecNl(5, 90.0, False); // no collisions
      [*] = ;
      [*] = ;   {SetGameObjectMyCollisionDetection(False);
      [*] = ;   SetGameObjectMyRuleCollidedExecFr(5, 90.0, False); // All sectors
      [*] = ;   SetGameObjectMyRuleCollidedExecEn(5, 90.0, False); // All sectors
      [*] = ;   SetGameObjectMyRuleCollidedExecNl(5, 90.0, False); // All sectors
      [*] = ;   SetGameObjectMyRuleUnCollidedExecFr(5, 90.0, False); // All sectors
      [*] = ;   SetGameObjectMyRuleUnCollidedExecEn(5, 90.0, False); // All sectors
      [*] = ;   SetGameObjectMyRuleUnCollidedExecNl(5, 90.0, False); // All sectors}
      [*] = ;end;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

