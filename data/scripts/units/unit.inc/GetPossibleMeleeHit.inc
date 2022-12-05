section.begin
   Name = GetPossibleMeleeHit
   Description : struct.begin
      [*] = ;IntRegister0 - target uid
      [*] = ;IntRegister1 - src pos x
      [*] = ;IntRegister2 - src pos y
      [*] = ;IntRegister3 - sector (-3 - +3) 0 - backstab strike
      [*] = ;OUT: IntRegister0 - min hit value
      [*] = ;   IntRegister1 - max hit value
      [*] = ;   IntRegister2 - possibility of target death (0-100)
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\GETPOSSIBLEMELEEHIT';
      [*] = ;var _log_trace : Integer = $40000;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;var tUID : Integer = IntRegister0;
      [*] = ;var mx : Integer = IntRegister1;
      [*] = ;var my : Integer = IntRegister2;
      [*] = ;var sector : Integer = IntRegister3;
      [*] = ;var myGOHandle : Integer = GetGameObjectMyHandle();
      [*] = ;var myUID : Integer = GetGameObjectUniqueIdByHandle(myGOHandle);
      [*] = ;var tGOHandle : Integer = GetGameObjectHandleByUniqueId(tUID);
      [*] = ;var tCurLife : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurLife);
      [*] = ;var ab,death,i : Integer;
      [*] = ;var damage : array [0..3] of Integer;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;IntRegister0 := tUID;
      [*] = ;ExecuteState('GetAttackBonus');
      [*] = ;ab := IntRegister0;
      [*] = ;IntRegister0 := tUID;
      [*] = ;IntRegister1 := sector;
      [*] = ;ExecuteState('GetBackstabBonus');
      [*] = ;ab := ab + IntRegister0;
      [*] = ;
      [*] = ;IntRegister0 := tGOHandle;
      [*] = ;IntRegister1 := round(abs(sector));
      [*] = ;BoolRegister0 := true;
      [*] = ;BoolRegister1 := false;
      [*] = ;BoolRegister2 := GetBoolValueByIndex(gc_stack_unit_bAstralStrike);
      [*] = ;BoolRegister3 := false;
      [*] = ;ExecuteState('GetMeleeHit');
      [*] = ;damage[0] := IntRegister2+ab;
      [*] = ;damage[1] := IntRegister3+ab;
      [*] = ;damage[2] := IntRegister4+ab;
      [*] = ;
      [*] = ;for i := 1 to 2 do
      [*] = ;begin
      [*] = ;   if damage[i] > tCurLife then
      [*] = ;      damage[i] := tCurLife;
      [*] = ;end;
      [*] = ;
      [*] = ;if (_unit_CheckAbility(tGOHandle, gc_ability_flying) = 0) and (_unit_CheckAbility(myGOHandle, gc_ability_cantmove) = 0) then
      [*] = ;begin
      [*] = ;   var ta : Integer = _unit_CheckAbility(myGOHandle, gc_ability_trumpling);
      [*] = ;   for i := 1 to 2 do
      [*] = ;   begin
      [*] = ;      if ((tCurLife - damage[i]) < ta) then
      [*] = ;         damage[i] := tCurLife;
      [*] = ;   end;
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

