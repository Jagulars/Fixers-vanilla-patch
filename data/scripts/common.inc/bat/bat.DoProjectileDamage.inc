section.begin
   Name = bat.DoProjectileDamage
   Description : struct.begin
      [*] = ;IntRegister0 - attacker uid
      [*] = ;IntRegister1 - target uid
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\BAT\BAT.DOPROJECTILEDAMAGE';
      [*] = ;var _log_trace : Integer = $20000;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;function DamageNeighbours(attacker_h, target_h, tx, ty : Integer; friend : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   var i,pNeighbours,uid,nGOHandle : Integer;
      [*] = ;
      [*] = ;   BoolRegister0 := not friend;
      [*] = ;   IntRegister0 := tx;
      [*] = ;   IntRegister1 := ty;
      [*] = ;   GameObjectExecuteStateByHandle(target_h, 'FindNeighbour');
      [*] = ;   Result := IntRegister2;
      [*] = ;   pNeighbours := ParserSelectByHandleByKey(ParserSelectGameObject(target_h), 'Neighbours');
      [*] = ;   if _log then _Log_valuesM('N|NP',IntRegister2,ParserGetCountByHandle(pNeighbours),0,0,0,0);
      [*] = ;
      [*] = ;   for i := ParserGetCountByHandle(pNeighbours)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      uid := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pNeighbours,i), 'UID');
      [*] = ;      nGOHandle := GetGameObjectHandleByUniqueId(uid);
      [*] = ;
      [*] = ;      if _unit_CheckAbility(nGOHandle,gc_ability_fire_immunity) = 0 then
      [*] = ;      begin
      [*] = ;         if _log then _Log_valuesM('__UID',uid,0,0,0,0,0);
      [*] = ;         IntRegister0 := uid;
      [*] = ;         BoolRegister0 := true;
      [*] = ;         GameObjectExecuteStateByHandle(attacker_h, 'DoFireDamage');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var attUID : Integer = IntRegister0;
      [*] = ;var tarUID : Integer = IntRegister1;
      [*] = ;var aGOHandle : Integer = GetGameObjectHandleByUniqueId(attUID);
      [*] = ;var tGOHandle : Integer = GetGameObjectHandleByUniqueId(tarUID);
      [*] = ;var tGridX : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentX);
      [*] = ;var tGridY : Integer = GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurrentY);
      [*] = ;var n : Integer = 0;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[X:'+IntToStr(tGridX)+',Y:'+IntToStr(tGridY)+']',_log_trace);
      [*] = ;
      [*] = ;//GameObjectExecuteStateByHandle(tGOHandle, 'IsTarget');
      [*] = ;//var tCount : Integer = IntRegister0;
      [*] = ;
      [*] = ;if (aGOHandle <> 0) and (GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurLife) > 0) then
      [*] = ;begin
      [*] = ;   IntRegister0 := tarUID;
      [*] = ;   BoolRegister0 := false;
      [*] = ;   GameObjectExecuteStateByHandle(aGOHandle, 'DoFireDamage');
      [*] = ;
      [*] = ;   if _unit_CheckAbility(aGOHandle, gc_ability_fire_ammo) > 0 then
      [*] = ;   begin
      [*] = ;      n := DamageNeighbours(aGOHandle, tGOHandle, tGridX, tGridY, true);
      [*] = ;      n := n + DamageNeighbours(aGOHandle, tGOHandle, tGridX, tGridY, false);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if GetGameObjectIntValueIndByHandle(tGOHandle, gc_stack_unit_iCurLife) <= 0 then
      [*] = ;begin
      [*] = ;   var pTarParser : Integer = ParserSelectGameObject(tGOHandle);
      [*] = ;   if ParserGetIntValueByKeyByHandle(pTarParser, 'BerserkUID') <> 0 then
      [*] = ;      ParserSetIntValueByKeyByHandle(pTarParser, 'BerserkUID', 0);
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+IntToStr(n)+']',$1000000 or _log_trace);
   struct.end
section.end

