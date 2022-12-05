section.begin
   Name = bat.ProceedHeroDeath
   Description : struct.begin
      [*] = ;IntRegister0 - hero handle
   struct.end
   Code : struct.begin
      [*] = ;var mapHeroHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'COMMON.INC\BAT\BAT.PROCEEDHERODEATH';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;function GetPlayerWin(plHandle : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   PlayerExecuteStateByHandle(plHandle, 'CheckLose');
      [*] = ;   Result := not BoolRegister0;
      [*] = ;   PlayerExecuteStateByHandle(plHandle, 'IsArmyScared');
      [*] = ;   Result := Result and (not BoolRegister0);
      [*] = ;end;
      [*] = ;
      [*] = ;if mapHeroHandle <> 0 then
      [*] = ;begin
      [*] = ;   var myPlHandle : Integer = 0;
      [*] = ;   var enPlHandle : Integer = 0;
      [*] = ;   var isAttack : Boolean;
      [*] = ;
      [*] = ;   if mapHeroHandle = gIntRegister_BattleAttackHeroHandle then
      [*] = ;   begin
      [*] = ;      myPlHandle := GetPlayerHandleByName(gc_battle_attackPlayerName);
      [*] = ;      enPlHandle := GetPlayerHandleByName(gc_battle_defendPlayerName);
      [*] = ;      isAttack := true;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if mapHeroHandle = gIntRegister_BattleDefendHeroHandle then
      [*] = ;      begin
      [*] = ;         myPlHandle := GetPlayerHandleByName(gc_battle_defendPlayerName);
      [*] = ;         enPlHandle := GetPlayerHandleByName(gc_battle_attackPlayerName);
      [*] = ;         isAttack := false;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;         exit;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //PlayerExecuteStateByHandle(myPlHandle, 'GetEnemyPlHandle');
      [*] = ;   //var enPlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;   var myWin : Boolean = GetPlayerWin(myPlHandle);
      [*] = ;   var enWin : Boolean = GetPlayerWin(enPlHandle);
      [*] = ;
      [*] = ;   PlayerExecuteStateByHandle(myPlHandle, 'GetHeroHandle');
      [*] = ;   var myHeroHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;   PlayerExecuteStateByHandle(enPlHandle, 'GetHeroHandle');
      [*] = ;   var enHeroHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;   var mapPlHandle : Integer = GetGameObjectPlayerHandleByHandle(mapHeroHandle);
      [*] = ;
      [*] = ;   // proceeed dialogs for dead heroes
      [*] = ;   if gBoolRegister_ArenaBattle and gBoolRegister_ArenaWatcher then
      [*] = ;   begin
      [*] = ;      IntRegister0 := mapHeroHandle;
      [*] = ;      BoolRegister0 := false;
      [*] = ;      BoolRegister1 := false;
      [*] = ;      PlayerExecuteStateByHandle(mapPlHandle, 'KillHero');
      [*] = ;      if gc_RecycleHeroes then
      [*] = ;         _obj_Recycle(mapHeroHandle);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (not isAttack) and gBoolRegister_ArenaBattle then
      [*] = ;      begin
      [*] = ;         IntRegister0 := mapHeroHandle;
      [*] = ;         BoolRegister0 := false;
      [*] = ;         BoolRegister1 := false;
      [*] = ;         PlayerExecuteStateByHandle(mapPlHandle, 'KillHero');
      [*] = ;         if gc_RecycleHeroes then
      [*] = ;            _obj_Recycle(mapHeroHandle);
      [*] = ;         gIntRegister_BattleDefendHeroHandle := 0;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (not GetGameObjectPlayableObjectByHandle(myHeroHandle)) or (GetGameObjectIntValueIndByHandle(myHeroHandle, gc_stack_unit_iCurLife) <= 0) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := myPlHandle;
      [*] = ;            BoolRegister0 := myWin;
      [*] = ;            BoolRegister1 := enWin;
      [*] = ;            GameObjectExecuteStateByHandle(mapHeroHandle, 'ProceedDeath');
      [*] = ;            var killed : Boolean = BoolRegister2;
      [*] = ;
      [*] = ;            if killed then
      [*] = ;            begin
      [*] = ;               IntRegister0 := mapHeroHandle;
      [*] = ;               BoolRegister0 := true;
      [*] = ;               BoolRegister1 := false;
      [*] = ;               PlayerExecuteStateByHandle(mapPlHandle, 'KillHero');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

