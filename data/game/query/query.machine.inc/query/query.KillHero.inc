section.begin
   Name = query.KillHero
   UsedFileName =
   Code : struct.begin
      [*] = ;var plHandle : Integer = GetGameObjectPlayerHandleByHandle(gIntRegister_DeadHeroHandle);
      [*] = ;var dummyUID : Integer = GetGameObjectIntValueIndByHandle(gIntRegister_DeadHeroHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;
      [*] = ;IntRegister0 := gIntRegister_DeadHeroHandle;
      [*] = ;BoolRegister0 := true;
      [*] = ;BoolRegister1 := false;
      [*] = ;PlayerExecuteStateByHandle(plHandle, 'KillHero');
      [*] = ;
      [*] = ;IntRegister0 := dummyUID;
      [*] = ;GUIExecuteState('map.DoHeroDismissUpdateGUI');
      [*] = ;
      [*] = ;//if gIntRegister_CurGameMode = 2 then
      [*] = ;//if gIntRegister_MapBattleProvince <> 0 then
      [*] = ;//MapExecuteState('bat.CheckNewBattle');
      [*] = ;
      [*] = ;//var oldQueryHandle : Integer = gIntRegister_CurQueryHandle;
      [*] = ;var isLanBattle : Boolean = _misc_IsLanBattle;
      [*] = ;if (gIntRegister_DeadHeroHandle = gIntRegister_BattleAttackHeroHandle) and (not isLanBattle) then
      [*] = ;begin
      [*] = ;   IntRegister0 := gIntRegister_BattleDefendHeroHandle;
      [*] = ;   MapExecuteState('bat.ProceedHeroDeath');
      [*] = ;
      [*] = ;   //if gIntRegister_CurQueryHandle = oldQueryHandle then
      [*] = ;   if QueryMachineResultGetNextQuery(_query_GetExecutedHandle) = '' then
      [*] = ;   MapExecuteState('bat.AfterBattle');
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if isLanBattle then
      [*] = ;   begin
      [*] = ;      var p : Integer = _misc_ParserGetOrCreateByKey('lan_herodeathchoice',true);
      [*] = ;      ParserSetBoolValueByKeyByHandle(p, 'Attacker', (gIntRegister_DeadHeroHandle = gIntRegister_BattleAttackHeroHandle));
      [*] = ;      ParserSetIntValueByKeyByHandle(p, 'Choice', 3); // 1 = resurrect, 2 = delivery, 3 = bury
      [*] = ;      _lan_LanSendParserToEnemy(gc_LAN_SHARD_PROCEEDHERODEATH, p);
      [*] = ;   end;
      [*] = ;   MapExecuteState('bat.AfterBattle');
      [*] = ;end;
   struct.end
section.end

