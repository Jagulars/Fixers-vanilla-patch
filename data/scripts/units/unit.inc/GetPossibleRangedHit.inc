section.begin
   Name = GetPossibleRangedHit
   Description : struct.begin
      [*] = ;IntRegister0 - target uid
      [*] = ;OUT: IntRegister0 - min hit value
      [*] = ;     IntRegister1 - max hit value
      [*] = ;     IntRegister2 - possibility of target death (0-100)
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\GETPOSSIBLERANGEDHIT';
      [*] = ;var _log_trace : Integer = $40000;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;var tUID : Integer = IntRegister0;
      [*] = ;var tGOHandle : Integer = GetGameObjectHandleByUniqueId(tUID);
      [*] = ;var tCurLife : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurLife);
      [*] = ;var death,i,ca : Integer;
      [*] = ;var damage : array [0..3] of Integer;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;ca := GetGameObjectMyIntValueInd(gc_stack_unit_iCurAmmo);
      [*] = ;if ca > 0 then
      [*] = ;begin
      [*] = ;   IntRegister0 := tGOHandle;
      [*] = ;   BoolRegister0 := false;
      [*] = ;   ExecuteState('GetRangedHit');
      [*] = ;   damage[1] := IntRegister2;
      [*] = ;   damage[2] := IntRegister3;
      [*] = ;   if (ca > 1) and (GetIntValueByIndex(gc_stack_unit_iActiveAbility) = gc_ability_double_shot) then
      [*] = ;   begin
      [*] = ;      for i := 1 to 2 do
      [*] = ;         damage[i] := damage[i] * 2;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   for i := 1 to 2 do
      [*] = ;      damage[i] := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;for i := 1 to 2 do
      [*] = ;begin
      [*] = ;   if damage[i] > tCurLife then
      [*] = ;      damage[i] := tCurLife;
      [*] = ;end;
      [*] = ;
      [*] = ;if damage[1] >= tCurLife then
      [*] = ;   death := 100
      [*] = ;else
      [*] = ;begin
      [*] = ;   if damage[2] < tCurLife then
      [*] = ;      death := 0
      [*] = ;   else
      [*] = ;      death := 50;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;
      [*] = ;IntRegister0 := damage[1];
      [*] = ;IntRegister1 := damage[2];
      [*] = ;IntRegister2 := death;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

