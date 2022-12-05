section.begin
   Name = bat.ResetData
   Description : struct.begin
      [*] = ;BoolRegister0 - check cancel orders
   struct.end
   Code : struct.begin
      [*] = ;var checkCancel : Boolean = BoolRegister0;
      [*] = ;var inGameA, inGameD : Boolean;
      [*] = ;
      [*] = ;var _log_name : String = 'COMMON.INC\BAT\BAT.RESETDATA';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;var _log : Boolean = false;
      [*] = ;var i,ph : Integer;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+BoolToStr(checkCancel)+']',_log_trace);
      [*] = ;
      [*] = ;procedure CheckHeroTutorial(goHandle, plHandle : Integer);
      [*] = ;begin
      [*] = ;   var plIndex : Integer = GetPlayerIndexByHandle(plHandle);
      [*] = ;   if (plIndex = gIntRegister_MapMyPlayerIndex) and (goHandle <> 0) then
      [*] = ;   begin
      [*] = ;      if GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := -2;
      [*] = ;         ExecuteState('CheckTutorialProgress');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gIntRegister_BattleAttackPlayer <> 0) and IsPlayerByHandle(gIntRegister_BattleAttackPlayer) then
      [*] = ;   PlayerExecuteStateByHandle(gIntRegister_BattleAttackPlayer, 'IsInGame')
      [*] = ;else
      [*] = ;begin
      [*] = ;   if (gIntRegister_BattleAttackPlayer <> 0) then
      [*] = ;      BoolRegister0 := false
      [*] = ;   else
      [*] = ;      BoolRegister0 := true;
      [*] = ;end;
      [*] = ;inGameA := BoolRegister0;
      [*] = ;
      [*] = ;if (gIntRegister_BattleDefendPlayer <> 0) and IsPlayerByHandle(gIntRegister_BattleDefendPlayer) then
      [*] = ;   PlayerExecuteStateByHandle(gIntRegister_BattleDefendPlayer, 'IsInGame')
      [*] = ;else
      [*] = ;begin
      [*] = ;   if (gIntRegister_BattleDefendPlayer <> 0) then
      [*] = ;      BoolRegister0 := false
      [*] = ;   else
      [*] = ;      BoolRegister0 := true;
      [*] = ;end;
      [*] = ;inGameD := BoolRegister0;
      [*] = ;
      [*] = ;// cancel hero orders
      [*] = ;if checkCancel and ((not gBoolRegister_MapResolveConflicts) or (_misc_GetConflictPlayerCount() = 0)) then
      [*] = ;begin
      [*] = ;   if _log then _Log_map('Cancelling attacker actions '+BoolToStr( inGameA ));
      [*] = ;   if inGameA and (gIntRegister_BattleAttackHeroHandle <> 0) and IsGameObjectByHandle(gIntRegister_BattleAttackHeroHandle) then
      [*] = ;   begin
      [*] = ;      var action : Integer = GetGameObjectIntValueIndByHandle(gIntRegister_BattleAttackHeroHandle, gc_map_GOStack_MapUnit_iActionType);
      [*] = ;      // if hero moved, attacked site, sieged province or attacked own defender
      [*] = ;      case action of
      [*] = ;         gc_UnitTaskAttackOwnDefender, gc_UnitTaskMove : GameObjectExecuteStateByHandle(gIntRegister_BattleAttackHeroHandle, 'CancelOrders');
      [*] = ;         gc_UnitTaskSiege : begin
      [*] = ;            // siege
      [*] = ;            GameObjectExecuteStateByHandle(gIntRegister_BattleAttackHeroHandle, 'IsInEnemyProvince');
      [*] = ;            if not BoolRegister0 then
      [*] = ;               GameObjectExecuteStateByHandle(gIntRegister_BattleAttackHeroHandle, 'CancelOrders');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if _log then _Log_map('Cancelling defender actions '+BoolToStr( inGameD ));
      [*] = ;   if inGameD and (gIntRegister_BattleDefendHeroHandle <> 0) and IsGameObjectByHandle(gIntRegister_BattleDefendHeroHandle) then
      [*] = ;   begin
      [*] = ;      var action : Integer = GetGameObjectIntValueIndByHandle(gIntRegister_BattleDefendHeroHandle, gc_map_GOStack_MapUnit_iActionType);
      [*] = ;      // if hero attacked site
      [*] = ;      if (action = gc_UnitTaskAttackSite) then
      [*] = ;         GameObjectExecuteStateByHandle(gIntRegister_BattleDefendHeroHandle, 'CancelOrders');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if _log then _Log_map('Checking attacker tutorial');
      [*] = ;if inGameA then CheckHeroTutorial(gIntRegister_BattleAttackHeroHandle, gIntRegister_BattleAttackPlayer);
      [*] = ;if _log then _Log_map('Checking defender tutorial');
      [*] = ;if inGameD then CheckHeroTutorial(gIntRegister_BattleDefendHeroHandle, gIntRegister_BattleDefendPlayer);
      [*] = ;if _log then _Log_map('Done checking');
      [*] = ;
      [*] = ;var pPlParser : Integer = ParserSelectPlayer(GetPlayerHandleByName(gc_battle_defendPlayerName));
      [*] = ;var pPlTowers : Integer = ParserSelectByHandleByKey(pPlParser, 'Towers');
      [*] = ;ParserClearByHandle(pPlTowers);
      [*] = ;
      [*] = ;_misc_ParserGetOrCreateByKey('battle_placement', true);
      [*] = ;
      [*] = ;// clear all battle units and objects
      [*] = ;var bVisibleBattle : Boolean = _misc_IsVisibleBattle();
      [*] = ;for i := 0 to 3 do
      [*] = ;begin
      [*] = ;   case i of
      [*] = ;      0 : ph := GetPlayerHandleByName(gc_battle_virtAttackPlayerName);
      [*] = ;      1 : ph := GetPlayerHandleByName(gc_battle_virtDefendPlayerName);
      [*] = ;      2 : ph := GetPlayerHandleByName(gc_battle_attackPlayerName);
      [*] = ;      3 : ph := GetPlayerHandleByName(gc_battle_defendPlayerName);
      [*] = ;   end;
      [*] = ;   if ph <> 0 then
      [*] = ;   begin
      [*] = ;      if bVisibleBattle or (not gc_RecycleVirtualUnits) then
      [*] = ;         ClearPlayerGameObjectsByHandle(ph)
      [*] = ;      else
      [*] = ;         _plr_RecycleGameObjects(ph);
      [*] = ;      SetPlayerControlModeByHandle(ph, 'cmNone');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister0 := 1;
      [*] = ;ExecuteState('bat.BackgroundScenery');
      [*] = ;
      [*] = ;IntRegister0 := 1;
      [*] = ;ExecuteState('bat.FieldScenery');
      [*] = ;
      [*] = ;const cPointerPlName = 'PlTrackBattle';
      [*] = ;var pointerPlayer : Integer = GetPlayerHandleByName(cPointerPlName);
      [*] = ;if gc_RecyclePointers then
      [*] = ;   _plr_RecycleGameObjects(pointerPlayer)
      [*] = ;else
      [*] = ;   ClearPlayerGameObjectsByHandle(pointerPlayer);
      [*] = ;
      [*] = ;gIntRegister_BattleCurPlIndex := -1;
      [*] = ;gIntRegister_BattleSiteIndex := -1;
      [*] = ;gIntRegister_BattleGuardIndex := -1;
      [*] = ;gIntRegister_BattleDefenderIndex := -1;
      [*] = ;gIntRegister_BattleSiteID := -1;
      [*] = ;gIntRegister_BattleSiteLevel := 0;
      [*] = ;gBoolRegister_BattleSiteIsGuarded := false;
      [*] = ;gIntRegister_MapBattleProvince := 0;
      [*] = ;
      [*] = ;gIntRegister_BattleAttackPlayer := 0;
      [*] = ;gIntRegister_BattleAttackHeroHandle := 0;
      [*] = ;gIntRegister_BattleAttackArmy := 0;
      [*] = ;gIntRegister_BattleDefendPlayer := 0;
      [*] = ;gIntRegister_BattleDefendHeroHandle := 0;
      [*] = ;gIntRegister_BattleDefendArmy := 0;
      [*] = ;gIntRegister_NewBattle := 0;
      [*] = ;
      [*] = ;gBoolRegister_IsHumanPlayer := false;
      [*] = ;gBoolRegister_IsDefenderBattle := false;
      [*] = ;gBoolRegister_IsAutoBattle := false;
      [*] = ;gBoolRegister_IsDefenderAutoBattle := false;
      [*] = ;
      [*] = ;gBoolRegister_ArenaBattle := false;
      [*] = ;gBoolRegister_ArenaWatcher := false;
      [*] = ;gIntRegister_ArenaLeague := 0;
      [*] = ;gIntRegister_ArenaReward := 0;
      [*] = ;gIntRegister_ArenaChosenSide := 0;
      [*] = ;gIntRegister_ArenaBet := 0;
      [*] = ;
      [*] = ;gIntRegister_ConflictHeroUID1 := 0;
      [*] = ;gIntRegister_ConflictHeroUID2 := 0;
      [*] = ;
      [*] = ;gBoolRegister_ResetBattleData := false;
      [*] = ;gBoolRegister_RealAIBattle := false;
      [*] = ;//gBoolRegister_InBattle := false;
      [*] = ;
      [*] = ;gBoolRegister_BtnBatEndTurnEnabled := true;
      [*] = ;
      [*] = ;if gGame.gameType = gc_GameTypeLanShard then
      [*] = ;begin
      [*] = ;   gIntRegsiter_LanBatServerID := 0;
      [*] = ;   gIntRegsiter_LanBatClientID := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_SetBattleLock($10000,_log_name);
      [*] = ;  
      [*] = ;_misc_ResetNecromancyData();
      [*] = ;
      [*] = ;MapExecuteState('bat.ClearGrid');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

