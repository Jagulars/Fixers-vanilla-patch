section.begin
   Name = OnDamage
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\ONDAMAGE';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle;
      [*] = ;var anim : String = GetGameObjectMyFrameAnimationName;
      [*] = ;var CAttCount : Integer = GetIntValueByIndex(gc_stack_unit_iCAttackCount);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+GetGameObjectMyCustomName+',CAC:'+IntToStr(CAttCount)+',Anim:'+anim+']',_log_trace);
      [*] = ;
      [*] = ;if (CAttCount=0) and ((anim='idle') or (anim='wound')) then // don't interrupt attack animation when counterattacker attacks back before the attacker has fully finished his attack animation.
      [*] = ;begin
      [*] = ;   _unit_ModifyAnimIntervalFactor(myGOHandle, gc_battle_unit_woundspeedmod);
      [*] = ;   GameObjectMySwitchToAnimationCycles('idle', False, False);
      [*] = ;   GameObjectMySwitchToAnimationCycles('wound', False, False);
      [*] = ;end;
      [*] = ;_unit_PlaySound(myGOHandle, 'units', 'wound');
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

