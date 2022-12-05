section.begin
   Name = EnemyAttack
   Description : struct.begin
      [*] = ;IntRegister0 - attack army
      [*] = ;IntRegister1 - attack hero
   struct.end
   Code : struct.begin
      [*] = ;var pEnemyArmy : Integer = IntRegister0;
      [*] = ;var enHeroHandle : Integer = IntRegister1;
      [*] = ;
      [*] = ;var _log_name : String = 'MAP\MAP.PROVINCE.INC\ENEMYATTACK';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;
      [*] = ;var pProvince : Integer = GetIntValueByIndex(gc_map_GOStack_Province_iParserHandle);
      [*] = ;
      [*] = ;var enPlHandle : Integer = GetGameObjectPlayerHandleByHandle(enHeroHandle);
      [*] = ;var enPlIndex : Integer = GetPlayerIndexByHandle(enPlHandle);
      [*] = ;var enCMode : String = GetPlayerControlModeByHandle(enPlHandle);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[P:'+IntToStr(enPlIndex)+']',_log_trace);
      [*] = ;
      [*] = ;var plHandle : Integer = 0;
      [*] = ;
      [*] = ;ExecuteState('IsUnderSiege');
      [*] = ;var isSiege : Boolean = BoolRegister0;
      [*] = ;var siegePlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;if isSiege and (enPlIndex <> GetPlayerIndexByHandle(siegePlHandle)) then
      [*] = ;   plHandle := siegePlHandle
      [*] = ;else
      [*] = ;begin
      [*] = ;   IntRegister0 := enPlIndex;
      [*] = ;   ExecuteState('GetPlayerIndex');
      [*] = ;   plHandle := GetPlayerHandleByIndex( IntRegister1 );
      [*] = ;end;
      [*] = ;
      [*] = ;var cMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;
      [*] = ;if SameText(cMode, 'cmPlayer') then
      [*] = ;begin
      [*] = ;   IntRegister0 := pEnemyArmy;
      [*] = ;   IntRegister1 := enHeroHandle;
      [*] = ;   IntRegister2 := plHandle;
      [*] = ;   ExecuteState('GetPlayerArmy');
      [*] = ;   var pOwnerArmy : Integer = IntRegister3;
      [*] = ;   var heroHandle : Integer = IntRegister4;
      [*] = ;   var count : Integer = IntRegister5;
      [*] = ;   var isGarrison : Boolean = BoolRegister0;
      [*] = ;   var pArmyUnits : Integer = ParserSelectByHandleByKey(pOwnerArmy, 'Units');
      [*] = ;   var armyCount : Integer = ParserGetCountByHandle(pArmyUnits);
      [*] = ;
      [*] = ;   gIntRegister_BattleAttackArmy := pEnemyArmy;
      [*] = ;   gIntRegister_BattleAttackHeroHandle := enHeroHandle;
      [*] = ;   gIntRegister_BattleAttackPlayer := enPlHandle;
      [*] = ;
      [*] = ;   if count > 1 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := pProvince;
      [*] = ;      PlayerExecuteStateByHandle(plHandle, 'CheckChooseHeroWindow');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if armyCount > 0 then
      [*] = ;      begin
      [*] = ;         if enHeroHandle <> 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := pOwnerArmy;
      [*] = ;            IntRegister1 := heroHandle;
      [*] = ;            GameObjectExecuteStateByHandle(enHeroHandle, 'AttackTargetProvinceArmy');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (gIntRegister_CurrentEventID > 0) and (gIntRegister_CurrentEventID <> gc_gui_query_provStartRebel) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := -1;
      [*] = ;               ExecuteState('GuardAttack');
      [*] = ;            end
      [*] = ;            else
      [*] = ;               ExecuteState('Rebel');
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if SameText(enCMode, 'cmPlayer') then
      [*] = ;         begin
      [*] = ;            StringRegister0 := IntToStr(gc_gui_query_heroAttackProvNoGuard);
      [*] = ;            BoolRegister0 := true;
      [*] = ;            PlayerExecuteStateByHandle(enPlHandle, 'CheckRequestQuery');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            _gv_SetMapLock($10000,_log_name);
      [*] = ;            BoolRegister0 := false;
      [*] = ;            GameObjectExecuteStateByHandle(enHeroHandle, 'CaptureTargetProvince');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   IntRegister0 := pEnemyArmy;
      [*] = ;   IntRegister1 := enHeroHandle;
      [*] = ;   IntRegister2 := plHandle;
      [*] = ;   ExecuteState('GetPlayerArmy');
      [*] = ;   var pDefenderArmy : Integer = IntRegister3;
      [*] = ;   var defHeroHandle : Integer = IntRegister4;
      [*] = ;   var count : Integer = IntRegister5;
      [*] = ;   var isGarrison : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;   var pDefArmyUnits : Integer = ParserSelectByHandleByKey(pDefenderArmy, 'Units');
      [*] = ;   var defArmyCount : Integer = ParserGetCountByHandle(pDefArmyUnits);
      [*] = ;
      [*] = ;   gIntRegister_BattleAttackArmy := pEnemyArmy;
      [*] = ;   gIntRegister_BattleAttackHeroHandle := enHeroHandle;
      [*] = ;   gIntRegister_BattleAttackPlayer := enPlHandle;
      [*] = ;
      [*] = ;   if defArmyCount > 0 then
      [*] = ;   begin
      [*] = ;      gIntRegister_BattleDefendArmy := pDefenderArmy;
      [*] = ;      gIntRegister_BattleDefendHeroHandle := defHeroHandle;
      [*] = ;      gIntRegister_BattleDefendPlayer := GetGameObjectPlayerHandleByHandle(defHeroHandle);
      [*] = ;
      [*] = ;      if enHeroHandle <> 0 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := pDefenderArmy;
      [*] = ;         Intregister1 := defHeroHandle;
      [*] = ;         GameObjectExecuteStateByHandle(enHeroHandle, 'AttackTargetProvinceArmy');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (gIntRegister_CurrentEventID > 0) and (gIntRegister_CurrentEventID <> gc_gui_query_provStartRebel) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := -1;
      [*] = ;            ExecuteState('GuardAttack');
      [*] = ;         end
      [*] = ;         else
      [*] = ;            ExecuteState('Rebel');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

