section.begin
   Name = bat.AfterWatchBattle
   UsedFileName =
   Code : struct.begin
      [*] = ;if gIntRegister_ArenaChosenSide > 0 then
      [*] = ;begin
      [*] = ;   var curPlHandle : Integer = _gv_GetCurrentPlayerHandle();
      [*] = ;   
      [*] = ;   var bUpdateStats : Boolean = _stats_IsEligible(curPlHandle);
      [*] = ;   if bUpdateStats then _stats_SimpleUpdate('General', 'ArenaBetCount', 1);
      [*] = ;   
      [*] = ;   var plGold : Integer = GetPlayerIntValueIndByHandle(curPlHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;
      [*] = ;   ExecuteState('bat.GetWinPlayerHandle');
      [*] = ;   var winPlHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;   if winPlHandle <> 0 then
      [*] = ;   begin
      [*] = ;      var aMode : Integer = GetPlayerIntValueIndByHandle(winPlHandle, gc_battle_PLStack_iAttackMode);
      [*] = ;      if ((gIntRegister_ArenaChosenSide = 1) and (aMode = 1)) or ((gIntRegister_ArenaChosenSide = 2) and (aMode = 0)) then
      [*] = ;      begin
      [*] = ;         if bUpdateStats then _stats_SimpleUpdate('General', 'ArenaBetWinCount', 1);
      [*] = ;         gIntRegister_GoldReward := 2 * gIntRegister_ArenaBet;
      [*] = ;
      [*] = ;         plGold := plGold + gIntRegister_GoldReward;
      [*] = ;         SetPlayerIntValueIndByHandle(curPlHandle, gc_map_PLStack_MapUnit_iGold, plGold);
      [*] = ;         if bUpdateStats then _stats_SimpleUpdate('Gold', 'ArenaBetProfit', gIntRegister_ArenaBet);
      [*] = ;
      [*] = ;         //plGold := GetPlayerIntValueIndByHandle(curPlHandle, gc_map_PLStack_MapUnit_iGoldGain);
      [*] = ;         //SetPlayerIntValueIndByHandle(curPlHandle, gc_map_PLStack_MapUnit_iGoldGain, plGold + gIntRegister_ArenaBet); // gain is only the profit
      [*] = ;
      [*] = ;         gStringRegister_AfterBattleQuery := IntToStr(gc_gui_query_heroArenaWinBetSide);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if bUpdateStats then _stats_SimpleUpdate('Gold', 'ArenaBetLosses', gIntRegister_ArenaBet);
      [*] = ;         gStringRegister_AfterBattleQuery := IntToStr(gc_gui_query_heroArenaLoseBetSide);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      plGold := plGold + gIntRegister_ArenaBet;
      [*] = ;      SetPlayerIntValueIndByHandle(curPlHandle, gc_map_PLStack_MapUnit_iGold, plGold);
      [*] = ;
      [*] = ;      gStringRegister_AfterBattleQuery := IntToStr(gc_gui_query_heroArenaDrawBet);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;//ExecuteState('bat.ProceedHeroesDeath');
      [*] = ;IntRegister0 := gIntRegister_BattleAttackHeroHandle;
      [*] = ;ExecuteState('bat.ProceedHeroDeath');
      [*] = ;IntRegister0 := gIntRegister_BattleDefendHeroHandle;
      [*] = ;ExecuteState('bat.ProceedHeroDeath');
      [*] = ;
      [*] = ;ExecuteState('bat.ExitBattleMode');
   struct.end
section.end

