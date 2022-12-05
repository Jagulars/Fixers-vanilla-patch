section.begin
   Name = CopyStackFrom
   Description : struct.begin
      [*] = ;IntRegister0 - game object handle
      [*] = ;IntRegister1 - copy flags (see showpahntomform)
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\COPYSTACKFROM';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var goHandle : Integer = IntRegister0;
      [*] = ;var flags : Integer = IntRegister1;
      [*] = ;var v_to_copy : array [0..$20] of Integer;
      [*] = ;var v_to_copy_org : array [0..$20] of Integer;
      [*] = ;var v_copy_type : array [0..$20] of Integer;
      [*] = ;var v_copy_mask : array [0..$20] of Integer;
      [*] = ;var no,i : Integer;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr( IntRegister1)+']',_log_trace);
      [*] = ;
      [*] = ;no := 0;
      [*] = ;v_to_copy[no] := gc_stack_unit_iCurLife; v_to_copy_org[no] := gc_battle_unit_iMaxLife; v_copy_mask[no] := 1; v_copy_type[no] := 0; no := no + 1;
      [*] = ;v_to_copy[no] := gc_stack_unit_iCurMoral; v_to_copy_org[no] := gc_battle_unit_iMaxMoral; v_copy_mask[no] := 4; v_copy_type[no] := 0; no := no + 1;
      [*] = ;v_to_copy[no] := gc_stack_unit_iCurStamina; v_to_copy_org[no] := gc_battle_unit_iMaxStamina; v_copy_mask[no] := 2; v_copy_type[no] := 0; no := no + 1;
      [*] = ;v_to_copy[no] := gc_stack_unit_iCurAmmo; v_to_copy_org[no] := gc_battle_unit_iMaxAmmo; v_copy_mask[no] := 8; v_copy_type[no] := 0; no := no + 1;
      [*] = ;v_to_copy[no] := gc_stack_unit_iLastX; v_to_copy_org[no] := -1; v_copy_mask[no] := 0; v_copy_type[no] := 0; no := no + 1;
      [*] = ;v_to_copy[no] := gc_stack_unit_iLastY; v_to_copy_org[no] := -1; v_copy_mask[no] := 0; v_copy_type[no] := 0; no := no + 1;
      [*] = ;v_to_copy[no] := gc_stack_unit_iCurrentX; v_to_copy_org[no] := -1; v_copy_mask[no] := 0; v_copy_type[no] := 0; no := no + 1;
      [*] = ;v_to_copy[no] := gc_stack_unit_iCurrentY; v_to_copy_org[no] := -1; v_copy_mask[no] := 0; v_copy_type[no] := 0; no := no + 1;
      [*] = ;v_to_copy[no] := gc_stack_unit_bCanAct; v_to_copy_org[no] := -1; v_copy_mask[no] := 0; v_copy_type[no] := 1; no := no + 1;
      [*] = ;v_to_copy[no] := gc_stack_unit_bCanMelee; v_to_copy_org[no] := -1; v_copy_mask[no] := 0; v_copy_type[no] := 1; no := no + 1;
      [*] = ;v_to_copy[no] := gc_stack_unit_bCanShoot; v_to_copy_org[no] := -1; v_copy_mask[no] := 0; v_copy_type[no] := 1; no := no + 1;
      [*] = ;v_to_copy[no] := gc_stack_unit_bCanCast; v_to_copy_org[no] := -1; v_copy_mask[no] := 0; v_copy_type[no] := 1; no := no + 1;
      [*] = ;v_to_copy[no] := gc_stack_unit_bActionTaken; v_to_copy_org[no] := -1; v_copy_mask[no] := 0; v_copy_type[no] := 1; no := no + 1;
      [*] = ;v_to_copy[no] := gc_stack_unit_bResting; v_to_copy_org[no] := -1; v_copy_mask[no] := 0; v_copy_type[no] := 1; no := no + 1;
      [*] = ;
      [*] = ;for i := 0 to no-1 do
      [*] = ;begin
      [*] = ;   if (v_copy_mask[i] = 0) or ((v_copy_mask[i] and flags) <> 0) then
      [*] = ;   begin
      [*] = ;      if v_copy_type[i] = 0 then SetIntValueByIndex(v_to_copy[i], GetGameObjectIntValueIndByHandle(goHandle, v_to_copy[i]) )
      [*] = ;      else SetBoolValueByIndex(v_to_copy[i], GetGameObjectBoolValueIndByHandle(goHandle, v_to_copy[i]) );
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (v_to_copy_org[i] <> -1) and (v_copy_type[i] = 0) then
      [*] = ;         SetIntValueByIndex(v_to_copy[i], _unit_GetProperty(GetGameObjectMyHandle(),v_to_copy_org[i]));
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

