section.begin
   Name = bat.AfterVirtualBattle
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\BAT\BAT.AFTERVIRTUALBATTLE';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;const cAttackPlayerName = 'virt.player.attack';
      [*] = ;const cDefendPlayerName = 'virt.player.defend';
      [*] = ;
      [*] = ;SetActiveTrackNodeList(0);
      [*] = ;_gv_SetMapLock($10000,_log_name);
      [*] = ;
      [*] = ;var attackPlHandle : Integer = GetPlayerHandleByName(cAttackPlayerName);
      [*] = ;var defendPlHandle : Integer = GetPlayerHandleByName(cDefendPlayerName);
      [*] = ;
      [*] = ;
      [*] = ;// returning gems spent in virtual battle
      [*] = ;if gIntRegister_BattleAttackPlayer <> 0 then
      [*] = ;begin
      [*] = ;   var plGem : Integer = GetPlayerIntValueIndByHandle(gIntRegister_BattleAttackPlayer, gc_map_PLStack_MapUnit_iGem);
      [*] = ;   var gemSpent : Integer = GetPlayerIntValueIndByHandle(attackPlHandle, gc_battle_PLStack_iGemSpent);
      [*] = ;   plGem := plGem + gemSpent;
      [*] = ;   SetPlayerIntValueIndByHandle(gIntRegister_BattleAttackPlayer, gc_map_PLStack_MapUnit_iGem, plGem);
      [*] = ;end;
      [*] = ;
      [*] = ;if gIntRegister_BattleDefendPlayer <> 0 then
      [*] = ;begin
      [*] = ;   var plGem : Integer = GetPlayerIntValueIndByHandle(gIntRegister_BattleDefendPlayer, gc_map_PLStack_MapUnit_iGem);
      [*] = ;   var gemSpent : Integer = GetPlayerIntValueIndByHandle(defendPlHandle, gc_battle_PLStack_iGemSpent);
      [*] = ;   plGem := plGem + gemSpent;
      [*] = ;   SetPlayerIntValueIndByHandle(gIntRegister_BattleDefendPlayer, gc_map_PLStack_MapUnit_iGem, plGem);
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;gBoolRegister_VirtualBattleHeroDied := false;
      [*] = ;var heroHandle : Integer = _unit_GetHeroHandle(attackPlHandle); 
      [*] = ;if (heroHandle <> 0) and (not GetGameObjectPlayableObjectByHandle(heroHandle)) then
      [*] = ;   gBoolRegister_VirtualBattleHeroDied := true;
      [*] = ;
      [*] = ;
      [*] = ;var i, goHandle : Integer;
      [*] = ;for i := GetPlayerGameObjectsCountByHandle(attackPlHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   goHandle := GetGameObjectHandleByIndex(i, attackPlHandle);
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX, -1);
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY, -1);
      [*] = ;end;
      [*] = ;
      [*] = ;for i := GetPlayerGameObjectsCountByHandle(defendPlHandle)-1 downto 0 do
      [*] = ;begin
      [*] = ;   goHandle := GetGameObjectHandleByIndex(i, defendPlHandle);
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX, -1);
      [*] = ;   SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY, -1);
      [*] = ;end;
      [*] = ;
      [*] = ;ExecuteState('bat.GetStrengthDisparity');
      [*] = ;var strength : Integer = IntRegister0;
      [*] = ;
      [*] = ;SetPlayerIntValueIndByHandle(attackPlHandle, gc_battle_PLStack_iIdleMode, gc_battle_idle_skip_global);
      [*] = ;SetPlayerIntValueIndByHandle(defendPlHandle, gc_battle_PLStack_iIdleMode, gc_battle_idle_skip_global);
      [*] = ;
      [*] = ;
      [*] = ;if gc_RecycleVirtualUnits then
      [*] = ;   _plr_RecycleGameObjects(attackPlHandle)
      [*] = ;else
      [*] = ;   ClearPlayerGameObjectsByHandle(attackPlHandle);
      [*] = ;PlayerSwitchToByHandle(attackPlHandle, 'Nothing');
      [*] = ;
      [*] = ;if gc_RecycleVirtualUnits then
      [*] = ;   _plr_RecycleGameObjects(defendPlHandle)
      [*] = ;else
      [*] = ;   ClearPlayerGameObjectsByHandle(defendPlHandle);
      [*] = ;PlayerSwitchToByHandle(defendPlHandle, 'Nothing');
      [*] = ;
      [*] = ;
      [*] = ;if _log then _Log_Map(_log_name+' Battle ends after ' + IntToStr(gIntRegister_BattleCurrentTurn) + ' turns');
      [*] = ;if _log then _Log_Map(_log_name+' Result = ' + IntToStr(strength));
      [*] = ;
      [*] = ;gIntRegister_VirtualBattleResult := strength;
      [*] = ;gBoolRegister_BattleEndBattle := true;
      [*] = ;gIntRegister_BattleCurPlIndex := -1;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

