section.begin
   Name = query.HeroResurrect
   Code : struct.begin
      [*] = ;BoolRegister0 := true;
      [*] = ;GameObjectExecuteStateByHandle(gIntRegister_DeadHeroHandle, 'Resurrect');
      [*] = ;
      [*] = ;if gIntRegister_MapSelectedUID = 0 then
      [*] = ;   PlayerExecuteStateByHandle(GetPlayerHandleInterfaceIO(), 'SelectNextHero');
      [*] = ;
      [*] = ;var isLanBattle : Boolean = _misc_IsLanBattle;
      [*] = ;if (gIntRegister_DeadHeroHandle = gIntRegister_BattleAttackHeroHandle) and (not isLanBattle) then
      [*] = ;begin
      [*] = ;   IntRegister0 := gIntRegister_BattleDefendHeroHandle;
      [*] = ;   MapExecuteState('bat.ProceedHeroDeath');
      [*] = ;
      [*] = ;   if QueryMachineResultGetNextQuery(_query_GetExecutedHandle) = '' then
      [*] = ;      MapExecuteState('bat.AfterBattle');
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if isLanBattle then
      [*] = ;   begin
      [*] = ;      var p : Integer = _misc_ParserGetOrCreateByKey('lan_herodeathchoice',true);
      [*] = ;      ParserSetBoolValueByKeyByHandle(p, 'Attacker', (gIntRegister_DeadHeroHandle = gIntRegister_BattleAttackHeroHandle));
      [*] = ;      ParserSetIntValueByKeyByHandle(p, 'Choice', 1); // 1 = resurrect, 2 = delivery, 3 = bury
      [*] = ;      _lan_LanSendParserToEnemy(gc_LAN_SHARD_PROCEEDHERODEATH, p);
      [*] = ;   end;
      [*] = ;   MapExecuteState('bat.AfterBattle');
      [*] = ;end;
   struct.end
section.end

