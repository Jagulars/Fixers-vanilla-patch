section.begin
   Name = astral.BackToCampaign
   Code : struct.begin
      [*] = ;var _log_name : String = 'COMMON.INC\ASTRAL\ASTRAL.BACKTOCAMPAIGN';
      [*] = ;var _log_trace : Integer = $20001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var exitFlag : Integer = gIntRegister_ShardBattleResult;
      [*] = ;var loseEnergy : Boolean = false;
      [*] = ;var lostShard : Boolean = false;
      [*] = ;
      [*] = ;// after shard battle actions
      [*] = ;if (gIntRegister_CampAttackPlayer >= 0) and (gIntRegister_CampDefendPlayer >= 0) then
      [*] = ;begin
      [*] = ;   // after world attack
      [*] = ;   if gCampaign.defender then
      [*] = ;   begin
      [*] = ;      case exitFlag of
      [*] = ;         1 : begin
      [*] = ;            IntRegister0 := 1;
      [*] = ;            ExecuteState('astral.FinishCampaign');
      [*] = ;         end;
      [*] = ;         2 : begin
      [*] = ;            gCampaign.arrCampPlayers[0].sizeBonus := gCampaign.arrCampPlayers[0].sizeBonus + 1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      case exitFlag of
      [*] = ;         1 : begin
      [*] = ;            loseEnergy := true;
      [*] = ;         end;
      [*] = ;         2 : begin
      [*] = ;            var pProfile : Integer = ParserSelectByHandleByIndex(gPrototypeData.players.handle, gIntRegister_CampDefendPlayer);
      [*] = ;            var defEvent : Integer = ParserGetIntValueByKeyByHandle(pProfile, 'EventDefeat');
      [*] = ;
      [*] = ;            if defEvent > 0 then
      [*] = ;            _camp_AddEvent(defEvent);
      [*] = ;
      [*] = ;            gCampaign.arrCampPlayers[0].killScore := gCampaign.arrCampPlayers[0].killScore + 1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;if gCampaign.activeShard >= 0 then
      [*] = ;begin
      [*] = ;   // shard attack
      [*] = ;   case exitFlag of
      [*] = ;      1 : begin
      [*] = ;         lostShard := true;
      [*] = ;      end;
      [*] = ;      2 : begin
      [*] = ;         //gCampaign.arrCampPlayers[0].sizeBonus := gCampaign.arrCampPlayers[0].sizeBonus + 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if loseEnergy then
      [*] = ;begin
      [*] = ;   var energyIncome : Integer = _camp_player_GetEnergyIncome(gCampaign.arrCampPlayers[0]);
      [*] = ;   var lose : Integer = 1 + energyIncome div 30 + _rand_Random(energyIncome div 12);
      [*] = ;   gCampaign.arrCampPlayers[0].energyDrain := lose;
      [*] = ;
      [*] = ;   gIntRegister_AstralEnergy := lose;
      [*] = ;   _camp_AddEvent(gc_gui_query_campWorldAttackLose);
      [*] = ;end;
      [*] = ;
      [*] = ;ExecuteState('astral.ResetData');
      [*] = ;
      [*] = ;gIntRegister_AstralSelectedShard := 0;
      [*] = ;_gv_SetAstralLock($10000,_log_name);
      [*] = ;
      [*] = ;gGame.currentTurn := -1;
      [*] = ;
      [*] = ;if (gCampaign.activeShard >= 0) then
      [*] = ;begin
      [*] = ;   var shUID : Integer = gShards[gCampaign.activeShard].uid;
      [*] = ;
      [*] = ;   if gShards[gCampaign.activeShard].ipPlayer >= 0 then
      [*] = ;   begin
      [*] = ;      IntRegister0 := gShards[gCampaign.activeShard].ipPlayer;
      [*] = ;      IntRegister1 := shUID;
      [*] = ;      BoolRegister0 := false;
      [*] = ;      ExecuteState('astral.CaptureShard');
      [*] = ;
      [*] = ;      gCampaign.activeShard := -1;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var shardHandle : Integer = GetGameObjectHandleByUniqueId(shUID);
      [*] = ;      GameObjectExecuteStateByHandle(shardHandle, 'DoDestroy');
      [*] = ;
      [*] = ;      BoolRegister0 := false;
      [*] = ;      BoolRegister1 := true;
      [*] = ;      ExecuteState('astral.EndTurn');
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   // tutorial map
      [*] = ;   ExecuteState('astral.Main');
      [*] = ;end;
      [*] = ;
      [*] = ;var i : Integer;
      [*] = ;for i := 0 to gGame.map.players-1 do
      [*] = ;gGame.arrPlayerSet[i] := 0;
      [*] = ;
      [*] = ;ExecuteState('astral.IsEndGame');
      [*] = ;
      [*] = ;SetBoolValueByName('LoadAstral', false);
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

