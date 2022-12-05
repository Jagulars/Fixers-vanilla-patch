section.begin
   Name = OnPathTravelStopSpell
   Code : struct.begin
      [*] = ;var _log_name : String = 'PROJECTILE\PROJECTILE.INC\ONPATHTRAVELSTOPSPELL';
      [*] = ;var _log_trace : Integer = $800001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;_gv_SetBattleLock(-1,_log_name);
      [*] = ;
      [*] = ;var myHnd : Integer = GetGameObjectMyHandle();
      [*] = ;var ownerUID : Integer = GetIntValueByIndex(gc_stack_projectile_iOwner);
      [*] = ;var ownerHnd : Integer = GetGameObjectHandleByUniqueId(ownerUID);
      [*] = ;if (ownerHnd<>0) then
      [*] = ;begin
      [*] = ;   ExecuteState('CreateBoomSpell');
      [*] = ;   GameObjectExecuteStateByHandle(ownerHnd, 'ApplyAllVisualParams');
      [*] = ;end
      [*] = ;else
      [*] = ;   SwitchTo('Nothing');
      [*] = ;
      [*] = ;SetIntValueByIndex(gc_stack_projectile_iTarget, 0);
      [*] = ;
      [*] = ;var endState : String;
      [*] = ;if gc_RecycleProjectiles then
      [*] = ;   endState := 'Recycle'
      [*] = ;else
      [*] = ;   endState := 'Destroy';
      [*] = ;
      [*] = ;if (_fx_FindFXHandleByID(myHnd, true, 2)<>0) then
      [*] = ;begin
      [*] = ;   GameObjectMyDelayExecuteState(endState, 5); // allow the trail to finish
      [*] = ;   _fx_GetOrCreateFXByID(myHnd, 'fxspiderfirefinish', 0, 0, 0, 0, 0, 2);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if (_fx_FindFXHandleByID(myHnd, true, 7)<>0) then
      [*] = ;   begin
      [*] = ;      GameObjectMyDelayExecuteState(endState, 5); // allow the trail to finish
      [*] = ;      _fx_GetOrCreateFXByID(myHnd, 'fxstonetrailfinish', 0, 0, 0, 0, 0, 7);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      GameObjectMyDelayExecuteState(endState, 1); // non-delayed destruction will cause access violation error
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

