section.begin
   Name = Destroy
   Code : struct.begin
      [*] = ;var _log_name : String = 'PROJECTILE\PROJECTILE.INC\DESTROY';
      [*] = ;var _log_trace : Integer = $800001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;if gc_RecycleProjectiles and gc_LogRecycling then
      [*] = ;   ErrorLogI('We are supposed to recycle projectiles');
      [*] = ;
      [*] = ;var myHnd : Integer = GetGameObjectMyHandle();
      [*] = ;
      [*] = ;{//if (myHnd <> 0) and (GetIntValueByIndex(gc_stack_projectile_iTarget) <> 0) then
      [*] = ;begin
      [*] = ;   SetIntValueByIndex(gc_stack_projectile_iTarget, 0);
      [*] = ;
      [*] = ;   if (_fx_FindFXHandleByID(myHnd, true, 2)<>0) then
      [*] = ;      _fx_GetOrCreateFXByID(myHnd, 'fxspiderfirefinish', 0, 0, 0, 0, 0, 2)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (_fx_FindFXHandleByID(myHnd, true, 7)<>0) then
      [*] = ;         _fx_GetOrCreateFXByID(myHnd, 'fxstonetrailfinish', 0, 0, 0, 0, 0, 7)
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         _fx_clearFX(myHnd, true, true);
      [*] = ;         //MyGameObjectPFXClear;
      [*] = ;         BehaviourClear(myHnd);
      [*] = ;         AddObjectToDestroyList(myHnd);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   SwitchTo('Nothing');
      [*] = ;end;}
      [*] = ;
      [*] = ;_fx_clearFX(myHnd, true, true);
      [*] = ;//MyGameObjectPFXClear;
      [*] = ;BehaviourClear(myHnd);
      [*] = ;AddObjectToDestroyList(myHnd);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end
