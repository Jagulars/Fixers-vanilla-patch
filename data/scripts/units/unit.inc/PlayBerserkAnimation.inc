section.begin
   Name = PlayBerserkAnimation
   Code : struct.begin
      [*] = ;var myAnim : String = GetGameObjectMyAnimationCycleName();// must be stored before animation switch
      [*] = ;if SameText(myAnim, 'berserk') then
      [*] = ;begin
      [*] = ;   SwitchTo('Nothing');
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\PLAYBERSERKANIMATION';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;_unit_ModifyAnimIntervalFactor(myGOHandle, gc_battle_unit_attackspeedmod);
      [*] = ;GameObjectMySwitchToTreeAnimationCyclesDefault('berserk');
      [*] = ;_unit_PlaySound(myGOHandle, 'units', 'berserk');
      [*] = ;
      [*] = ;var stFrame, endFrame : Integer;
      [*] = ;var exist : Boolean = GetGameObjectFrameAnimationDataByHandle(myGOHandle, 'berserk', stFrame, endFrame);
      [*] = ;if exist then
      [*] = ;   _gv_SetBattleLock(1,_log_name)
      [*] = ;else
      [*] = ;begin
      [*] = ;   ErrorLogI(_log_name+' '+GetGameObjectMyCustomName()+' has no animation berserk!');
      [*] = ;   ExecuteState('Idle');
      [*] = ;end;
      [*] = ;
      [*] = ;var cAttack : Integer = GetIntValueByIndex(gc_stack_unit_iCAttackCount);
      [*] = ;
      [*] = ;if cAttack > 0 then
      [*] = ;begin
      [*] = ;   cAttack := cAttack - 1;
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iCAttackCount, cAttack);
      [*] = ;
      [*] = ;   if (not SameText(myAnim, 'idle')) then
      [*] = ;      _gv_SetBattleLock(-1,_log_name);
      [*] = ;end;
      [*] = ;
      [*] = ;if _obj_EnabledByFlag(gc_ObjectFlagBattleFX) and (_fx_FindFXHandleByID(GetGameObjectMyHandle, true, 16) = 0) then
      [*] = ;   _fx_GetOrCreateFXByID(GetGameObjectMyHandle, 'fxberserk', 0, 0, 0, 0, 0, 16);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

