section.begin
   Name = DeathAnimReady
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\DEATHANIMREADY';
      [*] = ;//var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var deathAnimReady : Integer = Max(0, GetIntValueByIndex(gc_stack_unit_iDeathAnimReady) - 1);
      [*] = ;SetIntValueByIndex(gc_stack_unit_iDeathAnimReady, deathAnimReady);
      [*] = ;if _log then _log_obj(_log_name+'['+GetGameObjectMyCustomName+', Now: '+IntToStr(deathAnimReady)+']');
   struct.end
section.end

