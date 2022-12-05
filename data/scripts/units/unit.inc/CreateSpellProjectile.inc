section.begin
   Name = CreateSpellProjectile
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\CREATESPELLPROJECTILE';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var plHandle : Integer = _plr_GetOrCreatePlayer('projectiles', 'misc', 'cmPlayer', false);
      [*] = ;var ptHandle : Integer = _obj_GetInvisibleOrCreate(plHandle, 'misc', 'weapon.empty', GetGameObjectMyPositionX, GetGameObjectMyPositionY, GetGameObjectMyPositionZ);
      [*] = ;
      [*] = ;var spellID : Integer = GetIntValueByIndex(gc_stack_unit_iSpellID);
      [*] = ;var ptType : Integer = gc_projectile_iSpell+SpellID;
      [*] = ;
      [*] = ;if (ptHandle<>0) then
      [*] = ;begin
      [*] = ;   var myHandle : Integer = GetGameObjectMyHandle();
      [*] = ;   SetGameObjectIntValueIndByHandle(ptHandle, gc_stack_projectile_iOwner, GetGameObjectUniqueIdByHandle(myHandle));
      [*] = ;   SetGameObjectIntValueIndByHandle(ptHandle, gc_stack_projectile_iType, ptType);
      [*] = ;   SetGameObjectIntValueIndByHandle(ptHandle, gc_stack_projectile_iTarget, GetIntValueByIndex(gc_stack_unit_iSpellTargetUID));
      [*] = ;   SetGameObjectFloatValueIndByHandle(ptHandle, gc_stack_projectile_iTPosX, GetIntValueByIndex(gc_stack_unit_iTargetX));
      [*] = ;   SetGameObjectFloatValueIndByHandle(ptHandle, gc_stack_projectile_iTPosY, GetIntValueByIndex(gc_stack_unit_iTargetY));
      [*] = ;   if _log then _Log_map(_log_name+': Projectile launched.');
      [*] = ;   GameObjectExecuteStateByHandle(ptHandle, 'InitialFlySpell');
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iSpellTargetUID, 0);
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iSpellID, 0);
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iTargetX, 0);
      [*] = ;   SetIntValueByIndex(gc_stack_unit_iTargetY, 0);
      [*] = ;
      [*] = ;   //_gui_PlaySound('spells', 'spell'+IntToStr(spellID));
      [*] = ;end
      [*] = ;else
      [*] = ;   ErrorLog('unknown object handle in '+_log_name);
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

