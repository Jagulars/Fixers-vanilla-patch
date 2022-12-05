section.begin
   Name = query.HeroDeliverToCastle
   Code : struct.begin
      [*] = ;var plHandle : Integer = GetGameObjectPlayerHandleByHandle(gIntRegister_DeadHeroHandle);
      [*] = ;
      [*] = ;IntRegister0 := gIntRegister_TurnsOnHeroRevive;
      [*] = ;GameObjectExecuteStateByHandle(gIntRegister_DeadHeroHandle, 'DeliverToCastle');
      [*] = ;PlayerExecuteStateByHandle(plHandle, 'SelectNextHero');
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
      [*] = ;      ParserSetIntValueByKeyByHandle(p, 'Choice', 2);  // 1 = resurrect, 2 = delivery, 3 = bury
      [*] = ;      ParserSetIntValueByKeyByHandle(p, 'ReviveTurns', gIntRegister_TurnsOnHeroRevive);
      [*] = ;      _lan_LanSendParserToEnemy(gc_LAN_SHARD_PROCEEDHERODEATH, p);
      [*] = ;   end;
      [*] = ;   MapExecuteState('bat.AfterBattle');
      [*] = ;end;
   struct.end
section.end

