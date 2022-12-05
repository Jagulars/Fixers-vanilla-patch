section.begin
   Name = bat.FinishBattle
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\BAT\BAT.FINISHBATTLE';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;procedure ClearPlayerEffects(plHandle : Integer);
      [*] = ;begin
      [*] = ;   var i, j : Integer;
      [*] = ;   for i := GetPlayerGameObjectsCountByHandle(plHandle)-1 downto 0 do
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(i, plHandle);
      [*] = ;      var curLife : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife);
      [*] = ;      var customName : String = GetGameObjectCustomNameByHandle(goHandle);
      [*] = ;      var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;      var pGOEffects : Integer = ParserSelectByHandleByKey(pGOParser, 'Effects');
      [*] = ;
      [*] = ;      var chIndex : Integer = -1;
      [*] = ;      var destroy : Boolean = false;
      [*] = ;
      [*] = ;      for j := ParserGetCountByHandle(pGOEffects)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pGOEffect : Integer = ParserSelectByHandleByIndex(pGOEffects, j);
      [*] = ;         var abilID : Integer = ParserGetIntValueByKeyByHandle(pGOEffect, 'AbilityID');
      [*] = ;         var power : Integer = ParserGetIntValueByKeyByHandle(pGOEffect, 'Power');
      [*] = ;
      [*] = ;         ParserFreeByHandle(pGOEffect);
      [*] = ;
      [*] = ;         if abilID = gc_ability_change_side then
      [*] = ;            chIndex := power
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if abilID = gc_ability_phantom_form then
      [*] = ;            begin
      [*] = ;               if curLife > 0 then
      [*] = ;               begin
      [*] = ;                  if _log then _Log_map('Converting unit to true form.');
      [*] = ;                  GameObjectExecuteStateByHandle(goHandle, 'ShowTrueForm');
      [*] = ;                  if BoolRegister0 then
      [*] = ;                     destroy := true;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if chIndex >= 0 then
      [*] = ;         begin
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'ChangeSide');
      [*] = ;            SetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife, 0);
      [*] = ;            SetGameObjectPlayableObjectByHandle(goHandle, false);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      
      [*] = ;      if destroy then
      [*] = ;         SetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bSummoned, true);
      [*] = ;      
      [*] = ;      if curLife <= 0 then
      [*] = ;         SetGameObjectVisibleByHandle(goHandle, false);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if gBoolRegister_RealAIBattle then
      [*] = ;   gBoolRegister_BattleSimulate := false;
      [*] = ;
      [*] = ;ExecuteState('bat.GetWinPlayerHandle');
      [*] = ;var winPlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;var aPlHandle : Integer = GetPlayerHandleByName(gc_battle_attackPlayerName);
      [*] = ;var dPlHandle : Integer = GetPlayerHandleByName(gc_battle_defendPlayerName);
      [*] = ;
      [*] = ;// clear units effects
      [*] = ;ClearPlayerEffects(aPlHandle);
      [*] = ;ClearPlayerEffects(dPlHandle);
      [*] = ;
      [*] = ;// update hud when choosing to end a visual battle with quick combat
      [*] = ;if gBoolRegister_QuickBattle and (not gBoolRegister_RealAIBattle) and (not gBoolRegister_IsDefenderAutoBattle) and (not gBoolRegister_IsDefenderBattle) then
      [*] = ;begin
      [*] = ;   gBoolRegister_QuickBattle := false;
      [*] = ;   GUIExecuteState('battle.UnitHUDControl');
      [*] = ;   gBoolRegister_QuickBattle := true;
      [*] = ;end;
      [*] = ;
      [*] = ;SetPlayerIntValueIndByHandle(aPlHandle, gc_battle_PLStack_iIdleMode, gc_battle_idle_skip_global);
      [*] = ;SetPlayerIntValueIndByHandle(dPlHandle, gc_battle_PLStack_iIdleMode, gc_battle_idle_skip_global);
      [*] = ;
      [*] = ;if not gBoolRegister_ArenaBattle then
      [*] = ;begin
      [*] = ;   if (winPlHandle <> 0) then
      [*] = ;   begin
      [*] = ;      if not _misc_IsLanBattle() then
      [*] = ;         PlayerExecuteStateByHandle(winPlHandle, 'GetBattleTrophies')
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if ((winPlHandle = aPlHandle) and (GetPlayerIndexByHandle(gIntRegister_BattleAttackPlayer) = gIntRegister_MapMyPlayerIndex)) or
      [*] = ;            ((winPlHandle = dPlHandle) and (GetPlayerIndexByHandle(gIntRegister_BattleDefendPlayer) = gIntRegister_MapMyPlayerIndex)) then
      [*] = ;         PlayerExecuteStateByHandle(winPlHandle, 'GetBattleTrophies')
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // get site trophies
      [*] = ;   if (gIntRegister_BattleSiteID > 0) and (gIntRegister_BattleSiteLevel > 0) and gBoolRegister_BattleSiteIsGuarded and (winPlHandle = aPlHandle) then
      [*] = ;   begin
      [*] = ;      IntRegister0 := gIntRegister_BattleSiteIndex;
      [*] = ;      IntRegister1 := gIntRegister_BattleSiteLevel;
      [*] = ;      GameObjectExecuteStateByHandle(gIntRegister_BattleAttackHeroHandle, 'GetSiteTrophies');
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;if (not gBoolRegister_ArenaWatcher) then
      [*] = ;begin
      [*] = ;   var plHandle : Integer = gIntRegister_BattleAttackPlayer;
      [*] = ;   var bUpdateStats : Boolean = _stats_IsEligible(plHandle);
      [*] = ;   if bUpdateStats then _stats_SimpleUpdate('General', 'ArenaBattleCount', 1);
      [*] = ;   
      [*] = ;   if (winPlHandle = aPlHandle) then
      [*] = ;   begin
      [*] = ;      var wins : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iArenaWinCount);
      [*] = ;
      [*] = ;      if (gIntRegister_ArenaLeague = 3) and (wins = 9) then
      [*] = ;      begin
      [*] = ;         gIntRegister_AfterBattleEncounterID := gc_gui_query_heroWinOrcaEncounter;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         IntRegister0 := gIntRegister_BattleDefendHeroHandle;
      [*] = ;         GameObjectExecuteStateByHandle(gIntRegister_BattleAttackHeroHandle, 'GetArenaReward');
      [*] = ;         gIntRegister_GoldReward := IntRegister1;
      [*] = ;
      [*] = ;         gStringRegister_AfterBattleQuery := IntToStr(gc_gui_query_heroArenaWinBattle);
      [*] = ;      end;
      [*] = ;
      [*] = ;      if gIntRegister_ArenaLeague = 3 then
      [*] = ;         SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iArenaWinCount, wins + 1);
      [*] = ;
      [*] = ;      if bUpdateStats then _stats_SimpleUpdate('General', 'ArenaBattleWinCount', 1);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if gBoolRegister_IsHumanPlayer or gBoolRegister_IsDefenderBattle or gBoolRegister_IsAutoBattle or gBoolRegister_IsDefenderAutoBattle then
      [*] = ;begin
      [*] = ;   if (not _misc_IsLanBattle) or (LanMyInfoID() = gIntRegsiter_LanBatServerID) then // we must wait until the the battle host determines who is winner, so the result window cannot appear twice.
      [*] = ;      gBoolRegister_GUIBattleResultWindow := True;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   ExecuteState('bat.AddUnitsExperience');
      [*] = ;   ExecuteState('bat.ProceedHeroesDeath');
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

