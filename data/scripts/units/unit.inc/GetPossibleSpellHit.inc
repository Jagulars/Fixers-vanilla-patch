section.begin
   Name = GetPossibleSpellHit
   Description : struct.begin
      [*] = ;IntRegister0 - target uid
      [*] = ;IntRegister1 - spell id
      [*] = ;OUT:
      [*] = ;   BoolRegister0 - negative spell
      [*] = ;   IntRegister0 - min hit value (-1 if spell not valid)
      [*] = ;   IntRegister1 - max hit value (-1 if no damage could be calculated)
      [*] = ;   IntRegister2 - possibility of target death (0-100)
      [*] = ;   IntRegister3 - real spell duration
      [*] = ;   IntRegister4 - real spell power
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'UNITS\UNIT.INC\GETPOSSIBLESPELLHIT';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;var tUID : Integer = IntRegister0;
      [*] = ;var spellID : Integer = IntRegister1;
      [*] = ;var tGOHandle : Integer = GetGameObjectHandleByUniqueId(tUID);
      [*] = ;var spell : Integer;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(tUID)+','+IntToStr(spellID)+']',_log_trace);
      [*] = ;
      [*] = ;IntRegister0 := spellID;
      [*] = ;MapExecuteState('GetSpellParserByID');
      [*] = ;spell := IntRegister1;
      [*] = ;
      [*] = ;IntRegister0 := spellID;
      [*] = ;IntRegister1 := GetGameObjectUniqueIdByHandle(GetGameObjectMyHandle());
      [*] = ;GameObjectExecuteStateByHandle(tGOHandle, 'IsSpellTarget');
      [*] = ;if BoolRegister1 then
      [*] = ;begin
      [*] = ;   var tCurLife : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurLife);
      [*] = ;   var death,i,j,effects,effect,id,d,power : Integer;
      [*] = ;   var damage : array [0..3] of Integer;
      [*] = ;   var resistPower,defensePower,resist,attack,defense,power_mod,duration_mod,res,duration,resistDuration : Integer;
      [*] = ;   var negative,friendly,damage_calculated : Boolean;
      [*] = ;
      [*] = ;   if GetGameObjectPlayerHandleByHandle(GetGameObjectMyHandle()) = GetGameObjectPlayerHandleByHandle(tGOHandle) then friendly := true
      [*] = ;   else friendly := false;
      [*] = ;   negative := ParserGetBoolValueByKeyByHandle(spell, 'Negative');
      [*] = ;
      [*] = ;   resistPower := ParserGetIntValueByKeyByHandle(spell, 'ResistPower');
      [*] = ;   resistDuration := ParserGetIntValueByKeyByHandle(spell, 'ResistDuration');
      [*] = ;   defensePower := ParserGetIntValueByKeyByHandle(spell, 'DefencePower');
      [*] = ;
      [*] = ;   IntRegister0 := tUID;
      [*] = ;   IntRegister1 := spellID;
      [*] = ;   ExecuteState('GetSpellRuntimeAttributes');
      [*] = ;   resist := IntRegister0;
      [*] = ;   attack := IntRegister1;
      [*] = ;   defense := IntRegister2;
      [*] = ;   power_mod := IntRegister3;
      [*] = ;   duration_mod := IntRegister4;
      [*] = ;
      [*] = ;   if _log then _Log_valuesM('RESIST|ATTACK|DEFENSE|P_MOD|D_MOD',resist,attack,defense,power_mod,duration_mod,0);
      [*] = ;   for i := 0 to 2 do
      [*] = ;      damage[i] := 0;
      [*] = ;
      [*] = ;   duration := 0;
      [*] = ;   damage_calculated := false;
      [*] = ;
      [*] = ;   effects := ParserSelectByHandleByKey(spell, 'Effects');
      [*] = ;   for i := 0 to ParserGetCountByHandle(effects)-1 do
      [*] = ;   begin
      [*] = ;      effect := ParserSelectByHandleByIndex(effects, i);
      [*] = ;      id := ParserGetIntValueByKeyByHandle(effect, 'AbilityID');
      [*] = ;      d := ParserGetIntValueByKeyByHandle(effect, 'Duration');
      [*] = ;      power := ParserGetIntValueByKeyByHandle(effect, 'Power');
      [*] = ;
      [*] = ;      if power > 0 then
      [*] = ;         power := power + power_mod
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if power < 0 then
      [*] = ;            power := power - power_mod;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (d > 0) or (damage_calculated) then
      [*] = ;      begin
      [*] = ;         if d > 0 then
      [*] = ;         begin
      [*] = ;            // special case for web
      [*] = ;            if id = gc_ability_web then
      [*] = ;            begin
      [*] = ;               if resist <= 3 then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := gc_upgrade_web;
      [*] = ;                  GameObjectExecuteStateByHandle(tGOHandle, 'GetEffectParserByUpgradeID');
      [*] = ;                  var pGOEffect : Integer = IntRegister1;
      [*] = ;                  
      [*] = ;                  if (pGOEffect = 0) then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := gc_spell_web;
      [*] = ;                     GameObjectExecuteStateByHandle(tGOHandle, 'GetEffectParserBySpellID');
      [*] = ;                     pGOEffect := IntRegister1;
      [*] = ;                  end;
      [*] = ;                  if (pGOEffect <> 0) then
      [*] = ;                     d := 1
      [*] = ;                  else
      [*] = ;                  if d > attack then
      [*] = ;                     d := 3
      [*] = ;                  else
      [*] = ;                     d := 2;
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  d := 0;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               d := d + duration_mod;
      [*] = ;               if negative and (not friendly) and (resistDuration > 0) then
      [*] = ;                  d := d - resist;
      [*] = ;            end;
      [*] = ;            duration := max(duration,d);
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         case id of
      [*] = ;            gc_ability_life : begin
      [*] = ;               if (not negative) and friendly then
      [*] = ;               begin
      [*] = ;                  damage[1] := damage[0];
      [*] = ;                  damage[2] := damage[0];
      [*] = ;                  damage_calculated := true;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if resistPower > 0 then
      [*] = ;                     res := resist
      [*] = ;                  else
      [*] = ;                     res := 0;
      [*] = ;                  if defensePower > 0 then
      [*] = ;                     res := res + defense;
      [*] = ;
      [*] = ;                  IntRegister0 := power;
      [*] = ;                  IntRegister1 := res;
      [*] = ;                  BoolRegister0 := false;
      [*] = ;                  MapExecuteState('bat.GetHit');
      [*] = ;                  damage[1] := IntRegister3;
      [*] = ;                  damage[2] := IntRegister4;
      [*] = ;                  damage_calculated := true;
      [*] = ;                  negative := true;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            gc_ability_ammo : begin
      [*] = ;               if negative then
      [*] = ;               begin
      [*] = ;                  if resistPower > 0 then
      [*] = ;                     res := resist
      [*] = ;                  else
      [*] = ;                     res := 0;
      [*] = ;
      [*] = ;                  IntRegister0 := power;
      [*] = ;                  IntRegister1 := res;
      [*] = ;                  BoolRegister0 := false;
      [*] = ;                  MapExecuteState('bat.GetHit');
      [*] = ;                  damage[1] := IntRegister3;
      [*] = ;                  damage[2] := IntRegister4;
      [*] = ;                  damage_calculated := true;
      [*] = ;
      [*] = ;                  var curAmmo : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurAmmo);
      [*] = ;                  for j := 1 to 2 do
      [*] = ;                  if curAmmo < damage[j] then
      [*] = ;                     damage[j] := curAmmo;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            gc_ability_dispel : begin
      [*] = ;               if GetGameObjectBoolValueIndByHandle(tGOHandle, gc_stack_unit_bSummoned) then
      [*] = ;               begin
      [*] = ;                  res := power+ParserGetIntValueByKeyByHandle(effect,'Power')*2;
      [*] = ;                  if res > resist then
      [*] = ;                  begin
      [*] = ;                     IntRegister0 := res;
      [*] = ;                     IntRegister1 := resist;
      [*] = ;                     BoolRegister0 := false;
      [*] = ;                     MapExecuteState('bat.GetHit');
      [*] = ;                     damage[1] := IntRegister3;
      [*] = ;                     damage[2] := IntRegister4;
      [*] = ;                     damage_calculated := true;
      [*] = ;                     negative := true;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            gc_ability_suicide : begin
      [*] = ;               res := 0;
      [*] = ;               if (resistPower > 0) then
      [*] = ;                  res := resist;
      [*] = ;
      [*] = ;               if (res <= power) then
      [*] = ;               begin
      [*] = ;                  IntRegister0 := tGOHandle;
      [*] = ;                  IntRegister1 := -1;
      [*] = ;                  BoolRegister0 := true;
      [*] = ;                  BoolRegister1 := false;
      [*] = ;                  BoolRegister2 := false;
      [*] = ;                  BoolRegister3 := false;
      [*] = ;                  ExecuteState('GetMeleeHit');
      [*] = ;                  damage[1] := IntRegister3 * 2;
      [*] = ;                  damage[2] := IntRegister4 * 2;
      [*] = ;                  damage_calculated := true;
      [*] = ;                  negative := true;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   death := 0;
      [*] = ;   if damage_calculated then
      [*] = ;   begin
      [*] = ;      if negative then
      [*] = ;      begin
      [*] = ;         for i := 1 to 2 do
      [*] = ;         begin
      [*] = ;            if damage[i] > tCurLife then
      [*] = ;               damage[i] := tCurLife;
      [*] = ;         end;
      [*] = ;         if damage[1] >= tCurLife then
      [*] = ;            death := 100
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if damage[2] < tCurLife then
      [*] = ;               death := 0
      [*] = ;            else
      [*] = ;               death := 50;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      damage[1] := 0;
      [*] = ;      damage[2] := -1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   _gv_traceState(_log_name+'['+IntToStr(damage[1])+','+IntToStr(damage[2])+']',$1000000 or _log_trace);
      [*] = ;
      [*] = ;   IntRegister0 := damage[1];
      [*] = ;   IntRegister1 := damage[2];
      [*] = ;   IntRegister2 := death;
      [*] = ;   IntRegister3 := duration;
      [*] = ;   IntRegister4 := power;
      [*] = ;   BoolRegister0 := negative;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   _gv_traceState(_log_name+'[Spell is not valid]',$1000000 or _log_trace);
      [*] = ;
      [*] = ;   IntRegister0 := -1;
      [*] = ;   IntRegister1 := -1;
      [*] = ;   IntRegister2 := 0;
      [*] = ;   IntRegister3 := 0;
      [*] = ;   IntRegister4 := 0;
      [*] = ;   BoolRegister0 := false;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

