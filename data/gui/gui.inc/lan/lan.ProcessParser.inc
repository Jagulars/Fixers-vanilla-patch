section.begin
   Name = lan.ProcessParser
   Description : struct.begin
      [*] = ;IntRegister0 - parser ID
      [*] = ;IntRegister1 - parser handle
   struct.end
   Code : struct.begin
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;const cBattleResultDelay = 2;
      [*] = ;
      [*] = ;procedure DumpLogInfo(pLan : Integer);
      [*] = ;begin
      [*] = ;   var attacker : Integer = ParserGetIntValueByKeyByHandle(pLan, 'src_opponent');
      [*] = ;   var src_idx : Integer = ParserGetIntValueByKeyByHandle(pLan, 'src_index');
      [*] = ;   var t_attacker : Integer = ParserGetIntValueByKeyByHandle(pLan, 'target_opponent');
      [*] = ;   var tgt_idx : Integer = ParserGetIntValueByKeyByHandle(pLan, 'target_index');
      [*] = ;   var a_handle : Integer = GetPlayerHandleByName(gc_battle_attackPlayerName);
      [*] = ;   var d_handle : Integer = GetPlayerHandleByName(gc_battle_defendPlayerName);
      [*] = ;   var pl_handle : Integer;
      [*] = ;   var n,i,h,j : Integer;
      [*] = ;   var ts : String;
      [*] = ;
      [*] = ;   if attacker <> 0 then pl_handle := a_handle
      [*] = ;   else pl_handle := d_handle;
      [*] = ;
      [*] = ;   n := GetPlayerGameObjectsCountByHandle(pl_handle);
      [*] = ;   ts := 'SRC_A|OBJECTS|SRC_IDX|'+GetPlayerNameByHandle(pl_handle);
      [*] = ;   ts := ts+'TGT_A|TGT_IDX';
      [*] = ;   _log_valuesl(ts,attacker,n,src_idx,pl_handle,t_attacker,tgt_idx);
      [*] = ;   for j := 0 to 1 do
      [*] = ;   begin
      [*] = ;      if j = 0 then pl_handle := GetPlayerHandleByName(gc_battle_attackPlayerName)
      [*] = ;      else pl_handle := GetPlayerHandleByName(gc_battle_defendPlayerName);
      [*] = ;
      [*] = ;      if j = 0 then _log_lan('_ATTACK_PLAYER: '+GetPlayerNameByHandle(pl_handle))
      [*] = ;      else _log_lan('_DEFEND_PLAYER: '+GetPlayerNameByHandle(pl_handle));
      [*] = ;
      [*] = ;      n := GetPlayerGameObjectsCountByHandle(pl_handle);
      [*] = ;
      [*] = ;      for i := 0 to n-1 do
      [*] = ;      begin
      [*] = ;         h := GetGameObjectHandleByIndex(i,pl_handle);
      [*] = ;         _log_valuesl('__OBJ_IDX|OBJ_HND|OBJ_UID',i,h,GetGameObjectUniqueIdByHandle(h),0,0,0);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure LoadPlayerAndHeroInfo(pParser : Integer; isAttack : Boolean);
      [*] = ;begin
      [*] = ;   var pPlayer : Integer = ParserSelectByHandleByKey(pParser, 'Player');
      [*] = ;   if pPlayer <> 0 then
      [*] = ;   begin
      [*] = ;      var plIndex : Integer = ParserGetIntValueByKeyByHandle(pPlayer, 'Player');
      [*] = ;      var plHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;
      [*] = ;      if plHandle <> 0 then
      [*] = ;      begin
      [*] = ;         IntRegister0 := pPlayer;
      [*] = ;         IntRegister1 := 1;
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'LoadShortInfoFromParser');
      [*] = ;
      [*] = ;         var pHero : Integer = ParserSelectByHandleByKey(pPlayer, 'Hero');
      [*] = ;         if pHero <> 0 then
      [*] = ;         begin
      [*] = ;            var goIndex : Integer = ParserGetIntValueByKeyByHandle(pHero, 'Index');
      [*] = ;            var goHandle : Integer = GetGameObjectHandleByIndex(goIndex, plHandle);
      [*] = ;
      [*] = ;            IntRegister0 := pHero;
      [*] = ;            IntRegister1 := 1;
      [*] = ;            GameObjectExecuteStateByHandle(goHandle, 'LoadInfoFromParser');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if isAttack then
      [*] = ;               IntRegister0 := gIntRegister_BattleAttackHeroHandle
      [*] = ;            else
      [*] = ;               IntRegister0 := gIntRegister_BattleDefendHeroHandle;
      [*] = ;
      [*] = ;            if IntRegister0 <> 0 then
      [*] = ;            begin
      [*] = ;               BoolRegister0 := true;
      [*] = ;               BoolRegister1 := true;
      [*] = ;               PlayerExecuteStateByHandle(plHandle, 'KillHero');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var pID : Integer = IntRegister0;
      [*] = ;var pLan : Integer = IntRegister1;
      [*] = ;var pMachineParser : Integer = ParserSelectStateMachineByHandle(GetMapInitMachineHandle());
      [*] = ;var myPlHandle : Integer = GetPlayerHandleByIndex(gIntRegister_MapMyPlayerIndex);
      [*] = ;
      [*] = ;var _log_name : String = 'GUI.INC\LAN\LAN.PROCESSPARSER';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;
      [*] = ;if _log then
      [*] = ;begin
      [*] = ;   var pnm : String;
      [*] = ;
      [*] = ;   _lan_GetLanParserName(pID,pnm);
      [*] = ;   _gv_traceState(_log_name+'['+pnm+']',_log_trace);
      [*] = ;end
      [*] = ;else
      [*] = ;   _gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;
      [*] = ;case pID of
      [*] = ;//--- ENDTURN
      [*] = ;   gc_LAN_SHARD_ENDTURN : begin
      [*] = ;      if GetLanMode() >= 2 then
      [*] = ;      begin
      [*] = ;         var pSyncInfo : Integer = ParserSelectByHandleByKey(pMachineParser, 'SyncInfo');
      [*] = ;         var pSyncPlayers : Integer = ParserSelectByHandleByKey(pSyncInfo, 'Players');
      [*] = ;         var pSyncPlayer : Integer = ParserAddChildByIndex(pSyncPlayers, '*');
      [*] = ;         ParserCopyFromByHandle(pLan);
      [*] = ;
      [*] = ;         var plIndex : Integer = ParserGetIntValueByKeyByHandle(pLan, 'Player');
      [*] = ;         var plHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;         var pPlStack : Integer = ParserSelectByHandleByKey(pLan, 'PlayerStack');
      [*] = ;         var finished : Boolean = ParserGetBoolValueByIndexByHandle(pPlStack, gc_map_PLStack_MapUnit_bTurnFinished);
      [*] = ;         SetPlayerBoolValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_bTurnFinished, finished);
      [*] = ;         if _log then _log_valuesL('PIDX|PHANDLE|FINISHED',plIndex,plHandle,_gui_BoolToInt(finished),0,0,0);
      [*] = ;
      [*] = ;         //MapExecuteState('map.LanCheckEndTurn');
      [*] = ;      end
      [*] = ;      else
      [*] = ;         ErrorLogI(_log_name+' LAN_SHARD_ENDTURN received by client.');
      [*] = ;   end;
      [*] = ;//--- CALCTURN
      [*] = ;   gc_LAN_SHARD_CALCTURN : begin
      [*] = ;      IntRegister0 := pLan;
      [*] = ;      MapExecuteState('map.LanSyncInfo');
      [*] = ;      MapExecuteState('map.EndTurn');
      [*] = ;   end;
      [*] = ;//--- ENDCONFLICTS
      [*] = ;   gc_LAN_SHARD_ENDCONFLICTS : begin
      [*] = ;      if (_plr_IsInGame(GetPlayerHandleByIndex(gIntRegister_MapMyPlayerIndex))) then
      [*] = ;      begin
      [*] = ;         if gIntRegister_MapMyPlayerIndex <> gIntRegister_ConflictPlayerIndex then
      [*] = ;            gBoolRegister_MapResolveConflicts := false;
      [*] = ;
      [*] = ;         if gIntRegister_CurGameMode = gc_GameModeStrategy then
      [*] = ;         begin
      [*] = ;            MapExecuteState('map.AfterEndTurn');
      [*] = ;            _gv_SetMapLock(-1,_log_name);
      [*] = ;         end
      [*] = ;         else
      [*] = ;            gBoolRegister_AfterEndTurn := true;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;//--- SYNCCONFLICTS
      [*] = ;   gc_LAN_SHARD_SYNCCONFLICTS : begin
      [*] = ;      if (GetLanMode() = 1) and (_plr_IsInGame(GetPlayerHandleByIndex(gIntRegister_MapMyPlayerIndex))) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := pLan;
      [*] = ;         MapExecuteState('map.SyncConflicts');
      [*] = ;
      [*] = ;         _lan_timer_Arm(gc_lt_conflicts,0,true);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;//--- PLAYERSINFO
      [*] = ;   gc_LAN_SHARD_PLAYERSINFO : begin // apparently not used
      [*] = ;      IntRegister0 := pLan;
      [*] = ;      MapExecuteState('map.LanSyncInfo');
      [*] = ;
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByUniqueId(gIntRegister_MapSelectedUID);
      [*] = ;      if goHandle <> 0 then
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'Select');
      [*] = ;   end;
      [*] = ;//--- SHOWQUERY
      [*] = ;   gc_LAN_SHARD_SHOWQUERY : begin
      [*] = ;      //if GetLanMode() = 1 then
      [*] = ;      begin
      [*] = ;         var id : Integer = ParserGetIntValueByKeyByHandle(pLan, 'LanID');
      [*] = ;
      [*] = ;         if id = gIntRegister_MyLanID then
      [*] = ;         begin
      [*] = ;            IntRegister0 := ParserSelectByHandleByKey(pLan, 'Registers');
      [*] = ;            MapExecuteState('map.LoadQueryRegisters');
      [*] = ;
      [*] = ;            if (gIntRegister_CurGameMode = gc_GameModeTactics) and
      [*] = ;               (GetBoolValueByName('FadeFromBattleMode') or gBoolRegister_GUIBattleExitBattleMode) then
      [*] = ;            begin
      [*] = ;               gStringRegister_AfterBattleQuery := ParserGetValueByKeyByHandle(pLan, 'QueryID');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               StringRegister0 := ParserGetValueByKeyByHandle(pLan, 'QueryID');
      [*] = ;               ExecuteState('map.RequestQueryWindow');
      [*] = ;            end;
      [*] = ;
      [*] = ;            _lan_timer_Reset(gc_lt_conflicts,true,'GUI.INC\LAN\LAN.PROCESSPARSER ['+IntToStr(pID)+']');
      [*] = ;         end
      [*] = ;         else
      [*] = ;            _gv_SetMapLock($10001,_log_name);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;//--- CHOOSERESULT
      [*] = ;   gc_LAN_SHARD_CHOOSERESULT : begin
      [*] = ;      if GetLanMode() > 1 then
      [*] = ;      begin
      [*] = ;         gStringRegister_ClientQueryID := '';
      [*] = ;         var queryID : String = ParserGetValueByKeyByHandle(pLan, 'QueryID');
      [*] = ;         var resID : String = ParserGetValueByKeyByHandle(pLan, 'Result');
      [*] = ;         //var lanID : String = ParserGetValueByKeyByHandle(pLan, 'LanID');
      [*] = ;
      [*] = ;         if (_sa_GetNumSafe_D(resID, $2e) > 1) then
      [*] = ;         begin
      [*] = ;            gBoolRegister_WaitLanQueryResult := false;
      [*] = ;
      [*] = ;            var resInd : Integer = _sa_GetAsInt_D(resID,1,$2e);
      [*] = ;            var queryHandle : Integer = QueryMachineCustomQueryCreate(queryID);
      [*] = ;            var resultsHandle : Integer = QueryMachineQueryGetResults(queryHandle);
      [*] = ;            var resultHandle : Integer = QueryMachineResultsGetByIndex(resultsHandle, resInd-1);
      [*] = ;
      [*] = ;            QueryMachineResultDoSelectExecute(resultHandle);
      [*] = ;            var newQueryID : String = QueryMachineQueryGetID(queryHandle);
      [*] = ;
      [*] = ;            if newQueryID = queryID then
      [*] = ;               QueryMachineQueriesRemove(QueryMachineGetCustomQueriesHandle(), queryHandle);
      [*] = ;
      [*] = ;            if gStringRegister_ClientQueryID = '' then
      [*] = ;               _gv_SetMapLock(-1,_log_name);
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         ErrorLogI(_log_name+' LAN_SHARD_CHOOSERESULT received by client.');
      [*] = ;   end;
      [*] = ;//--- SHOWPROVHEROES
      [*] = ;   gc_LAN_SHARD_SHOWPROVHEROES : begin
      [*] = ;      if GetLanMode() = 1 then
      [*] = ;      begin
      [*] = ;         var id : Integer = ParserGetIntValueByKeyByHandle(pLan, 'LanID');
      [*] = ;
      [*] = ;         if id = gIntRegister_MyLanID then
      [*] = ;         begin
      [*] = ;            var provIndex : Integer = ParserGetIntValueByKeyByHandle(pLan, 'ProvIndex');
      [*] = ;            IntRegister0 := ParserSelectByHandleByIndex(gStratHexCells.handle, provIndex);
      [*] = ;            BoolRegister0 := true;
      [*] = ;            GUIExecuteState('map.CreateChooseHeroWindow');
      [*] = ;         end
      [*] = ;         else
      [*] = ;            _gv_SetMapLock($10001,_log_name);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;//--- CHOOSEHERO
      [*] = ;   gc_LAN_SHARD_CHOOSEHERO : begin
      [*] = ;      if GetLanMode() > 1 then
      [*] = ;      begin
      [*] = ;         var provInd : Integer = ParserGetIntValueByKeyByHandle(pLan, 'ProvIndex');
      [*] = ;         var plIndex : Integer = ParserGetIntValueByKeyByHandle(pLan, 'Player');
      [*] = ;         var heroInd : Integer = ParserGetIntValueByKeyByHandle(pLan, 'HeroIndex');
      [*] = ;
      [*] = ;         var plHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;         var heroHandle : Integer = GetGameObjectHandleByIndex(heroInd, plHandle);
      [*] = ;
      [*] = ;         var curPlHandle : Integer = _gv_GetCurrentPlayerHandle();
      [*] = ;         var curGOHandle : Integer = GetGameObjectHandleByIndex(gIntRegister_MapCurHeroIndex, curPlHandle);
      [*] = ;         var tUID : Integer = GetGameObjectIntValueIndByHandle(curGOHandle, gc_map_GOStack_MapUnit_iTargetUID);
      [*] = ;
      [*] = ;         var pProvince : Integer;
      [*] = ;         if curGOHandle <> 0 then
      [*] = ;            pProvince := _misc_GetProvinceParserByUID(tUID)
      [*] = ;         else
      [*] = ;            pProvince := gIntRegister_MapBattleProvince;
      [*] = ;
      [*] = ;         gBoolRegister_WaitLanQueryResult := false;
      [*] = ;
      [*] = ;         IntRegister0 := pProvince;
      [*] = ;         IntRegister1 := heroHandle;
      [*] = ;         ExecuteState('map.ProcessChooseHero');
      [*] = ;      end
      [*] = ;      else
      [*] = ;         ErrorLogI(_log_name+' LAN_SHARD_CHOOSEHERO received by client.');
      [*] = ;   end;
      [*] = ;//--- FADETOBATTLE
      [*] = ;   gc_LAN_SHARD_FADETOBATTLE : begin
      [*] = ;      var id : array [0..$10] of Integer;
      [*] = ;      var id_no,i : Integer;
      [*] = ;      var ids : String = ParserGetValueByKeyByHandle(pLan, 'LanID');
      [*] = ;
      [*] = ;      id[0] := ParserGetIntValueByKeyByHandle(pLan, 'LanID1');
      [*] = ;      id[1] := ParserGetIntValueByKeyByHandle(pLan, 'LanID2');
      [*] = ;      id_no := _sa_GetNum(ids);
      [*] = ;      for i := 0 to id_no-1 do
      [*] = ;         id[i+2] := _sa_GetAsInt(ids,i);
      [*] = ;      id_no := id_no + 2;
      [*] = ;
      [*] = ;      if (GetLanMode() > 1) and (ids <> '') then begin
      [*] = ;         // we have to store current battle id to reroute queries results in a case of human-ai battles
      [*] = ;         Assert((gStringRegister_LanCurrentBattleIDs = ''),_log_name+' gStringRegister_LanCurrentBattleIDs is not empty - '+gStringRegister_LanCurrentBattleIDs);
      [*] = ;         gStringRegister_LanCurrentBattleIDs := ids;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (GetLanMode() > 1) then
      [*] = ;      begin
      [*] = ;         // we have to store current battle ids to reroute queries results in a case of human-ai battles
      [*] = ;         // and exit battle mode if ai-human battle will be after human-human battle
      [*] = ;         Assert((gStringRegister_LanCurrentBattleIDs = ''),_log_name+' gStringRegister_LanCurrentBattleIDs is not empty - '+gStringRegister_LanCurrentBattleIDs);
      [*] = ;         if ids <> '' then
      [*] = ;            gStringRegister_LanCurrentBattleIDs := ids
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            gStringRegister_LanCurrentBattleIDs := '';
      [*] = ;            _sa_AddAsInt(gStringRegister_LanCurrentBattleIDs,id[0]);
      [*] = ;            _sa_AddAsInt(gStringRegister_LanCurrentBattleIDs,id[1]);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      for i := 0 to id_no-1 do
      [*] = ;      begin
      [*] = ;         if id[i] = gIntRegister_MyLanID then // I'm one of the battlers
      [*] = ;            break;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if i < id_no then // I'm one of the battlers
      [*] = ;      begin
      [*] = ;         var pRegisters : Integer = ParserSelectByHandleByKey(pLan, 'Registers');
      [*] = ;         var randKey0, randKey1 : Integer;
      [*] = ;
      [*] = ;         _lan_timer_Reset(gc_lt_conflicts,true,'GUI.INC\LAN\LAN.PROCESSPARSER ['+IntToStr(pID)+']');
      [*] = ;
      [*] = ;         IntRegister0 := pRegisters;
      [*] = ;         MapExecuteState('LoadBattleRegisters');
      [*] = ;
      [*] = ;         randKey0 := ParserGetIntValueByKeyByHandle(pLan, 'RandKey0');
      [*] = ;         randKey1 := ParserGetIntValueByKeyByHandle(pLan, 'RandKey1');
      [*] = ;         SetRandomExtKey64(randKey0, randKey1);
      [*] = ;
      [*] = ;         if i > 1 then // human player-ai player battle
      [*] = ;         begin
      [*] = ;            var lan_flags : Integer = ParserGetIntValueByKeyByHandle(pLan, 'LanFlags');
      [*] = ;
      [*] = ;            if ((lan_flags and 1) <> 0) then
      [*] = ;            begin
      [*] = ;               _gv_SetCurrentPlayer(ParserGetIntValueByKeyByHandle(pRegisters, 'AttackPlayerIndex'),_log_name);
      [*] = ;               gIntRegister_MapCurHeroIndex := ParserGetIntValueByKeyByHandle(pRegisters, 'AttackHeroIndex');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               _gv_SetCurrentPlayer(ParserGetIntValueByKeyByHandle(pRegisters, 'DefendPlayerIndex'),_log_name);
      [*] = ;               gIntRegister_MapCurHeroIndex := ParserGetIntValueByKeyByHandle(pRegisters, 'DefendHeroIndex');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if gIntRegister_CurGameMode = gc_GameModeStrategy then
      [*] = ;         begin
      [*] = ;            GUIExecuteState('vvk.map.StartTacticalBattle');
      [*] = ;            //_gv_SetMapLock($10000,_log_name); // !!!
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            gBoolRegister_BattleSimulate := false;
      [*] = ;            gBoolRegister_QuickBattle := false;
      [*] = ;            MapExecuteState('bat.AddPlayers');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;//--- BATTLELOADED
      [*] = ;   gc_LAN_SHARD_BATTLELOADED : begin // received by both client and server
      [*] = ;      var id1 : Integer = ParserGetIntValueByKeyByHandle(pLan, 'LanID1');
      [*] = ;      var id2 : Integer = ParserGetIntValueByKeyByHandle(pLan, 'LanID2');
      [*] = ;
      [*] = ;      //if GetLanMode() >= 2 then
      [*] = ;      if (gIntRegister_MyLanID = id1) then // server will count players
      [*] = ;      begin
      [*] = ;         gIntRegsiter_LanShardBatReadyCount := gIntRegsiter_LanShardBatReadyCount + 1;
      [*] = ;
      [*] = ;         if gIntRegsiter_LanShardBatReadyCount = 2 then
      [*] = ;         begin
      [*] = ;            var p : Integer = _misc_ParserGetOrCreateByKey('lan_procparser_startbattle',true);
      [*] = ;            if _log then _log_valuesL('BL_BATTLE_SERVER|BATTLE_CLIENT',gIntRegsiter_LanBatServerID,gIntRegsiter_LanBatClientID,0,0,0,0);
      [*] = ;            gIntRegsiter_LanShardBatReadyCount := 0;
      [*] = ;            _inet_LanSendBattleParser(gc_LAN_SHARD_STARTBATTLE,p);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;//--- STARTBATTLE
      [*] = ;   gc_LAN_SHARD_STARTBATTLE : begin
      [*] = ;      var id1 : Integer = ParserGetIntValueByKeyByHandle(pLan, 'LanID1');
      [*] = ;      var id2 : Integer = ParserGetIntValueByKeyByHandle(pLan, 'LanID2');
      [*] = ;      var lan_id : Integer = gIntRegister_MyLanID;
      [*] = ;
      [*] = ;      if _log then _log_valuesL('SB_BATTLE_SERVER|BATTLE_CLIENT',gIntRegsiter_LanBatServerID,gIntRegsiter_LanBatClientID,0,0,0,0);
      [*] = ;      if (lan_id = id1) or (lan_id = id2) then
      [*] = ;      begin
      [*] = ;         GUIExecuteState('VVK.lan.resetbattleglobals');
      [*] = ;         _lan_timer_Reset(gc_lt_loading,false,'GUI.INC\LAN\LAN.PROCESSPARSER ['+IntToStr(pID)+']');
      [*] = ;         _lan_timer_Arm(gc_lt_placement,0,true);
      [*] = ;
      [*] = ;         if (lan_id = gIntRegsiter_LanBatServerID) then
      [*] = ;         begin
      [*] = ;            if (GetPlayerHandleInterfaceIO()=GetPlayerHandleByIndex(gIntRegister_BattleCurPlIndex)) then
      [*] = ;            begin
      [*] = ;               gIntRegister_InetLanTurn := -1;
      [*] = ;               _lan_timer_Reset(gc_lt_placement,true,'GUI.INC\LAN\LAN.PROCESSPARSER ['+IntToStr(pID)+']');
      [*] = ;               //ErrorLog('LanDialogsControl from lan.OnLanEvent');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               gIntRegister_InetLanTurn := -2;
      [*] = ;               _lan_LanSendParserToEnemy( gc_LAN_CLIENTPLACEMENT, _pars_ParserEmpty());
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;//--- CHECKNEWBATTLE
      [*] = ;   gc_LAN_SHARD_CHECKNEWBATTLE : begin
      [*] = ;      if GetLanMode() >= 2 then
      [*] = ;      begin
      [*] = ;         var pAttack : Integer = ParserSelectByHandleByKey(pLan, 'Attack');
      [*] = ;         var pDefend : Integer = ParserSelectByHandleByKey(pLan, 'Defend');
      [*] = ;         var newBattle : Integer = ParserGetIntValueByKeyByHandle(pLan, 'gIntRegister_NewBattle');
      [*] = ;         var dummyUID, dummyHandle, plCount  : Integer;
      [*] = ;
      [*] = ;         if newBattle > 0 then
      [*] = ;            gIntRegister_NewBattle := newBattle;
      [*] = ;
      [*] = ;         LoadPlayerAndHeroInfo(pAttack, true);
      [*] = ;         LoadPlayerAndHeroInfo(pDefend, false);
      [*] = ;
      [*] = ;         gIntRegsiter_LanReadyPlayersCount := gIntRegsiter_LanReadyPlayersCount + 1;
      [*] = ;
      [*] = ;         dummyUID := ParserGetIntValueByKeyByHandle(gIntRegister_MapBattleProvince, 'DummyUID');
      [*] = ;         dummyHandle := GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;         if dummyHandle <> 0 then
      [*] = ;         begin
      [*] = ;            var pLanProvince : Integer = ParserSelectByHandleByKey(pLan, 'Province');
      [*] = ;
      [*] = ;            if pLanProvince <> 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := pLanProvince;
      [*] = ;               IntRegister1 := 1;
      [*] = ;               GameObjectExecuteStateByHandle(dummyHandle, 'LoadInfoFromParser');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         plCount := 1;
      [*] = ;         if _misc_IsLanBattle() then
      [*] = ;            plCount := 2;
      [*] = ;
      [*] = ;         //gStringRegister_LanCurrentBattleIDs := '';
      [*] = ;
      [*] = ;         if gIntRegsiter_LanReadyPlayersCount = plCount then
      [*] = ;         begin
      [*] = ;            gIntRegsiter_LanReadyPlayersCount := 0;
      [*] = ;            MapExecuteState('bat.DoCheckNewBattle');
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         ErrorLogI(_log_name+' LAN_SHARD_CHECKNEWBATTLE received by client.');
      [*] = ;   end;
      [*] = ;//--- EXITBATTLE
      [*] = ;   gc_LAN_SHARD_EXITBATTLE : begin
      [*] = ;      var id : array [0..$10] of Integer;
      [*] = ;      var id_no,i : Integer;
      [*] = ;      var ids : String = ParserGetValueByKeyByHandle(pLan, 'LanID');
      [*] = ;
      [*] = ;      id[0] := ParserGetIntValueByKeyByHandle(pLan, 'LanID1');
      [*] = ;      id[1] := ParserGetIntValueByKeyByHandle(pLan, 'LanID2');
      [*] = ;      id_no := _sa_GetNum(ids);
      [*] = ;      for i := 0 to id_no-1 do
      [*] = ;         id[i+2] := _sa_GetAsInt(ids,i);
      [*] = ;      id_no := id_no + 2;
      [*] = ;
      [*] = ;      for i := 0 to id_no-1 do
      [*] = ;      begin
      [*] = ;         if id[i] = gIntRegister_MyLanID then // I am one of the battlers
      [*] = ;            break;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // when I am one of the battlers
      [*] = ;      if i < id_no then
      [*] = ;         MapExecuteState('bat.DoExitBattleMode');
      [*] = ;
      [*] = ;      if GetLanMode() > 1 then
      [*] = ;      begin
      [*] = ;         gStringRegister_LanCurrentBattleIDs := '';
      [*] = ;         //gIntRegister_NewBattle := 0;
      [*] = ;         if i >= id_no then // when not one of participants in battle, host gotta null maplock here to continue conflict resolution in Nothing. Participants null maplock in bat.switchtomap
      [*] = ;         begin
      [*] = ;            gBoolRegister_MapProceedBattle := false;
      [*] = ;            _gv_SetMapLock($10000,_log_name);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;//--- BATADDPLAYERS
      [*] = ;   gc_LAN_SHARD_BATADDPLAYERS : begin
      [*] = ;      var id1 : Integer = ParserGetIntValueByKeyByHandle(pLan, 'LanID1');
      [*] = ;      var id2 : Integer = ParserGetIntValueByKeyByHandle(pLan, 'LanID2');
      [*] = ;
      [*] = ;      if (gIntRegister_MyLanID = id1) or (gIntRegister_MyLanID = id2) then
      [*] = ;      begin
      [*] = ;         var pRegisters : Integer = ParserSelectByHandleByKey(pLan, 'Registers');
      [*] = ;
      [*] = ;         _lan_timer_Reset(gc_lt_conflicts,false,'GUI.INC\LAN\LAN.PROCESSPARSER ['+IntToStr(pID)+']');
      [*] = ;         _lan_timer_Arm(gc_lt_placement,0,true);
      [*] = ;
      [*] = ;         IntRegister0 := pRegisters;
      [*] = ;         MapExecuteState('LoadBattleRegisters');
      [*] = ;         GUIExecuteState('VVK.lan.resetbattleglobals');
      [*] = ;
      [*] = ;         if gIntRegister_BattleAttackHeroHandle <> 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := ParserSelectByHandleByKey(pLan, 'AttackHero');
      [*] = ;            IntRegister1 := 1;
      [*] = ;            GameObjectExecuteStateByHandle(gIntRegister_BattleAttackHeroHandle, 'LoadInfoFromParser');
      [*] = ;         end;
      [*] = ;
      [*] = ;         if gIntRegister_BattleDefendHeroHandle <> 0 then
      [*] = ;         begin
      [*] = ;            IntRegister0 := ParserSelectByHandleByKey(pLan, 'DefendHero');
      [*] = ;            IntRegister1 := 1;
      [*] = ;            GameObjectExecuteStateByHandle(gIntRegister_BattleDefendHeroHandle, 'LoadInfoFromParser');
      [*] = ;         end;
      [*] = ;
      [*] = ;         SetRandomExtKey64(ParserGetIntValueByKeyByHandle(pLan, 'RandKey0'), ParserGetIntValueByKeyByHandle(pLan, 'RandKey1'));
      [*] = ;
      [*] = ;         MapExecuteState('bat.DoAddPlayers');
      [*] = ;         GUIExecuteState('battle.DrawPath');
      [*] = ;
      [*] = ;         if GetPlayerHandleInterfaceIO() = GetPlayerHandleByIndex(gIntRegister_BattleCurPlIndex) then
      [*] = ;         begin
      [*] = ;            gIntRegister_InetLanTurn := -1;
      [*] = ;            _lan_timer_Reset(gc_lt_placement,true,'GUI.INC\LAN\LAN.PROCESSPARSER ['+IntToStr(pID)+']');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            gIntRegister_InetLanTurn := -2;
      [*] = ;            _lan_LanSendParserToEnemy( gc_LAN_CLIENTPLACEMENT, _pars_ParserEmpty());
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;//--- SYNCHERO
      [*] = ;   gc_LAN_SHARD_SYNCHERO : begin
      [*] = ;      //var id : Integer = ParserGetIntValueByKeyByHandle(pLan, 'LanID');
      [*] = ;
      [*] = ;      //if id = gIntRegister_MyLanID then
      [*] = ;      begin
      [*] = ;         var pHero : Integer = ParserSelectByHandleByKey(pLan, 'Hero');
      [*] = ;         if pHero <> 0 then
      [*] = ;         begin
      [*] = ;            var plIndex : Integer = ParserGetIntValueByKeyByHandle(pHero, 'Player');
      [*] = ;            var plHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;            var goIndex : Integer = ParserGetIntValueByKeyByHandle(pHero, 'Index');
      [*] = ;            var goHandle : Integer = GetGameObjectHandleByIndex(goIndex, plHandle);
      [*] = ;
      [*] = ;            if goHandle <> 0 then
      [*] = ;            begin
      [*] = ;               IntRegister0 := pHero;
      [*] = ;               IntRegister1 := 1;
      [*] = ;               GameObjectExecuteStateByHandle(goHandle, 'LoadInfoFromParser');
      [*] = ;            end;
      [*] = ;         end
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;//--- PROCEEDHERODEATH
      [*] = ;   gc_LAN_SHARD_PROCEEDHERODEATH : begin // Required to get correct processing from bat.AfterBattle by having value of gc_map_GOStack_MapUnit_bIsDead correct.
      [*] = ;      var heroHandle : Integer = 0;
      [*] = ;      if ParserGetBoolValueByKeyByHandle(pLan, 'Attacker') then
      [*] = ;         heroHandle := gIntRegister_BattleAttackHeroHandle
      [*] = ;      else
      [*] = ;         heroHandle := gIntRegister_BattleDefendHeroHandle;
      [*] = ;      
      [*] = ;      if heroHandle <> 0 then
      [*] = ;      begin
      [*] = ;         var choice : Integer = ParserGetIntValueByKeyByHandle(pLan, 'Choice');
      [*] = ;         case choice of
      [*] = ;            1 : begin
      [*] = ;               BoolRegister0 := false;
      [*] = ;               GameObjectExecuteStateByHandle(heroHandle, 'Resurrect');
      [*] = ;            end;
      [*] = ;            2 : begin
      [*] = ;               IntRegister0 := ParserGetIntValueByKeyByHandle(pLan, 'ReviveTurns');
      [*] = ;               GameObjectExecuteStateByHandle(heroHandle, 'DeliverToCastle');
      [*] = ;            end;
      [*] = ;            3 : begin
      [*] = ;               var plHandle : Integer = GetGameObjectPlayerHandleByHandle(heroHandle);
      [*] = ;
      [*] = ;               IntRegister0 := heroHandle;
      [*] = ;               BoolRegister0 := false;
      [*] = ;               BoolRegister1 := false;
      [*] = ;               PlayerExecuteStateByHandle(plHandle, 'KillHero');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      MapExecuteState('bat.AfterBattle');
      [*] = ;   end;
      [*] = ;   gc_LAN_SHARD_SYNCTREASURY : begin // not used, as treasury is synced with gc_LAN_SHARD_DIPLOMACYMESSAGE
      [*] = ;      var requestPlInd : Integer = ParserGetIntValueByKeyByHandle(pLan, 'RequestPlayer');
      [*] = ;      var deliverPlInd : Integer = ParserGetIntValueByKeyByHandle(pLan, 'DeliverPlayer');
      [*] = ;      var mode : Integer = ParserGetIntValueByKeyByHandle(pLan, 'Mode');
      [*] = ;      var myPlIndex : Integer = gIntRegister_MapMyPlayerIndex;
      [*] = ;      
      [*] = ;      if (((requestPlInd = myPlIndex) or (requestPlInd = -1)) and (mode = 1)) or ((deliverPlInd = myPlIndex) and (mode = 0)) then
      [*] = ;      begin
      [*] = ;         case mode of
      [*] = ;            0 : begin // sync requested
      [*] = ;               var p : Integer = _misc_ParserGetOrCreateByKey('lan_sync_treasury', true);
      [*] = ;            
      [*] = ;               ParserSetIntValueByKeyByHandle(p, 'RequestPlayer', requestPlInd);
      [*] = ;               ParserSetIntValueByKeyByHandle(p, 'DeliverPlayer', myPlIndex);
      [*] = ;               ParserSetIntValueByKeyByHandle(p, 'Mode', 1); 
      [*] = ;            
      [*] = ;               var pSendTreasury : Integer = ParserAddChildByIndex(p, 'Treasury');
      [*] = ;               var pTreasury : Integer = ParserSelectByHandleByKey(ParserSelectPlayer(GetPlayerHandleByIndex(myPlIndex)), 'Treasury');
      [*] = ;               ParserCopyToByHandle(pSendTreasury);
      [*] = ;   
      [*] = ;               _lan_LanSendParser(gc_LAN_SHARD_SYNCTREASURY, p);
      [*] = ;            end;
      [*] = ;            1 : begin // sync delivered
      [*] = ;               var pTreasury : Integer = ParserSelectByHandleByKey(ParserSelectPlayer(GetPlayerHandleByIndex(deliverPlInd)), 'Treasury');
      [*] = ;               ParserClearByHandle(pTreasury);
      [*] = ;               ParserSelectByHandleByKey(pLan, 'Treasury');
      [*] = ;               ParserCopyToByHandle(pTreasury);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   gc_LAN_SHARD_DIPLOMACYMESSAGE : begin
      [*] = ;      var proposePlayerInd : Integer = ParserGetIntValueByKeyByHandle(pLan, 'ProposePlayer');
      [*] = ;      var answerPlayerInd : Integer = ParserGetIntValueByKeyByHandle(pLan, 'AnswerPlayer');
	   [*] = ;      var messagePlInd : Integer = ParserGetIntValueByKeyByHandle(pLan, 'MessagePlayer');
      [*] = ;               
      [*] = ;      // sync treasury each time a message is received.
      [*] = ;      if messagePlInd >= 0 then
      [*] = ;      begin
      [*] = ;         var pTreasury : Integer = ParserSelectByHandleByKey(ParserSelectPlayer(GetPlayerHandleByIndex(messagePlInd)), 'Treasury');
      [*] = ;         ParserClearByHandle(pTreasury);
      [*] = ;         ParserSelectByHandleByKey(pLan, 'Treasury');
      [*] = ;         ParserCopyToByHandle(pTreasury);
      [*] = ;      end;
      [*] = ;               
      [*] = ;      if (proposePlayerInd >= 0) and (answerPlayerInd >= 0) and (proposePlayerInd <> answerPlayerInd) then
      [*] = ;      begin
      [*] = ;         var proposePlHandle : Integer = GetPlayerHandleByIndex(proposePlayerInd);
      [*] = ;         var answerPlHandle : Integer = GetPlayerHandleByIndex(answerPlayerInd);
      [*] = ;         
      [*] = ;         var myPlIndex : Integer = gIntRegister_MapMyPlayerIndex;
      [*] = ;         
      [*] = ;         var deal : Integer = ParserGetIntValueByKeyByHandle(pLan, 'Deal');
      [*] = ;         case deal of
      [*] = ;            -3 : begin // proposal withdrawn
      [*] = ;               if (gArrDiplomacy[proposePlayerInd][answerPlayerInd].message.deal < 1) then // ensure that already sealed deal cannot be withdrawn because of internet lag
      [*] = ;               begin
      [*] = ;                  gArrDiplomacy[proposePlayerInd][answerPlayerInd].message.deal := -3;
      [*] = ;                  _diplomacy_Escrow(proposePlayerInd, answerPlayerInd, false);
      [*] = ;               
      [*] = ;                  if answerPlayerInd = myPlIndex then
      [*] = ;                  begin
      [*] = ;                     if ((gArrDiplomacy[proposePlayerInd][answerPlayerInd].displayPriority and $ff) = 0) then // if their proposal has been viewed
      [*] = ;                     begin
      [*] = ;                        _diplomacy_UpdateDisplayPriority(myPlIndex, 1);
      [*] = ;                        gArrDiplomacy[proposePlayerInd][answerPlayerInd].displayPriority := (gArrDiplomacy[proposePlayerInd][answerPlayerInd].displayPriority and $ffff00) + 1;
      [*] = ;                     end
      [*] = ;                     else // no need to inform of their withdrawn offer if the offer was never viewed in the first place.
      [*] = ;                        gArrDiplomacy[proposePlayerInd][answerPlayerInd].displayPriority := gArrDiplomacy[proposePlayerInd][answerPlayerInd].displayPriority and $ffff00;
      [*] = ;                     
      [*] = ;                     gArrDiplomacy[answerPlayerInd][proposePlayerInd].answer := 0;
      [*] = ;                     
      [*] = ;                     if (gIntRegister_DiplomacyWindowMode > 0) then
      [*] = ;                     begin
      [*] = ;                        if (gIntRegister_DiplomacyActivePlayerID = proposePlayerInd) then
      [*] = ;                        begin
      [*] = ;                           if (gIntRegister_DiplomacyWindowMode = 4) then // when currently viewing the offer that is now withdrawn
      [*] = ;                           begin
      [*] = ;                              _diplomacy_ClearMessage(gDiplMessage);
      [*] = ;                              gIntRegister_DiplomacyWindowMode := 1;
      [*] = ;                           end;
      [*] = ;                           GUIExecuteState('map.CreateDiplomacyWindow');
      [*] = ;                        end
      [*] = ;                        else // instant blink
      [*] = ;                        if (gArrDiplomacy[proposePlayerInd][answerPlayerInd].displayPriority > 0) then
      [*] = ;                        begin
      [*] = ;                           var elmPortrait : Integer = GetGUIElementIndexByNameParent('dip_background.round_portrait_'+IntToStr(proposePlayerInd)+'_border', _gui_GetWindow('diplomacy'));
      [*] = ;                           _gui_CreateBlinkElement('btnDiplomacyPlayer_'+IntToStr(proposePlayerInd), elmPortrait, 'gamepanel01.btn.round.73x73.highlight', false, 0, 0, 0, 0);
      [*] = ;                        end
      [*] = ;                        else // remove blink
      [*] = ;                        if (gArrDiplomacy[proposePlayerInd][answerPlayerInd].displayPriority = 0) then
      [*] = ;                        begin
      [*] = ;                           var placeHolder : Boolean;
      [*] = ;                           _gui_RemoveBlinkElement('btnDiplomacyPlayer_'+IntToStr(proposePlayerInd), placeHolder);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            -2 : begin // ally peace refused
	   [*] = ;               if messagePlInd >= 0 then
	   [*] = ;               begin
      [*] = ;                  IntRegister0 := proposePlayerInd;
      [*] = ;                  IntRegister1 := answerPlayerInd;
      [*] = ;                  PlayerExecuteStateByHandle(GetPlayerHandleByIndex(messagePlInd), 'RefusePeaceFromUnion');
	   [*] = ;               end;
      [*] = ;            end;
      [*] = ;            -1 : begin // proposal refused
      [*] = ;               IntRegister0 := proposePlayerInd;
      [*] = ;               PlayerExecuteStateByHandle(answerPlHandle, 'HumanCancelDeal');
      [*] = ;            end;
      [*] = ;            0 : begin //receive proposal
      [*] = ;               if (gArrDiplomacy[proposePlayerInd][answerPlayerInd].message.deal <= 0) and (gArrDiplomacy[answerPlayerInd][proposePlayerInd].message.deal <= 0) then // ensure that no new messages are delivered because of internet lag if a deal has already been sealed
      [*] = ;               begin
      [*] = ;                  _diplomacy_Escrow(proposePlayerInd, answerPlayerInd, false); // release escrow of previous message
      [*] = ;                  
      [*] = ;                  IntRegister0 := 3; // unpack a message
      [*] = ;                  IntRegister1 := pLan;
      [*] = ;                  IntRegister2 := proposePlayerInd;
      [*] = ;                  IntRegister3 := answerPlayerInd;
      [*] = ;                  GUIExecuteState('VVK.DiplomacyHelper');
      [*] = ;                  if answerPlayerInd = myPlIndex then
      [*] = ;                     _diplomacy_AssignMessage(gArrDiplomacy[proposePlayerInd][answerPlayerInd].queryWindowMessage, gArrDiplomacy[proposePlayerInd][answerPlayerInd].message);
      [*] = ;               
      [*] = ;                  gArrDiplomacy[answerPlayerInd][proposePlayerInd].answer := 0;
      [*] = ;                  _diplomacy_Escrow(proposePlayerInd, answerPlayerInd, true);
      [*] = ;               
      [*] = ;                  if answerPlayerInd = myPlIndex then
      [*] = ;                  begin
      [*] = ;                     _diplomacy_UpdateDisplayPriority(myPlIndex, 1);
      [*] = ;                     gArrDiplomacy[proposePlayerInd][answerPlayerInd].displayPriority := (gArrDiplomacy[proposePlayerInd][answerPlayerInd].displayPriority and $ffff00) + 1;
      [*] = ;                  
      [*] = ;                     if (gIntRegister_DiplomacyWindowMode > 0) then
      [*] = ;                     begin
      [*] = ;                        if (gIntRegister_DiplomacyActivePlayerID = proposePlayerInd) then
      [*] = ;                        begin
      [*] = ;                           if (gIntRegister_DiplomacyWindowMode = 4) then // when already viewing their previous offer that is now replaced by a new one
      [*] = ;                           begin
      [*] = ;                              _diplomacy_ClearMessage(gDiplMessage);
      [*] = ;                              _diplomacy_AssignMessage(gDiplMessage, gArrDiplomacy[proposePlayerInd][answerPlayerInd].message);
      [*] = ;                              _diplomacy_AssignTrade(gDiplMessage.tradeTake, gArrDiplomacy[proposePlayerInd][answerPlayerInd].message.tradeGive);
      [*] = ;                              _diplomacy_AssignTrade(gDiplMessage.tradeGive, gArrDiplomacy[proposePlayerInd][answerPlayerInd].message.tradeTake);
      [*] = ;                              //gIntRegister_DiplomacyWindowMode := 4;
      [*] = ;                           end;
      [*] = ;                           GUIExecuteState('map.CreateDiplomacyWindow');
      [*] = ;                        end
      [*] = ;                        else
      [*] = ;                        begin
      [*] = ;                           var elmPortrait : Integer = GetGUIElementIndexByNameParent('dip_background.round_portrait_'+IntToStr(proposePlayerInd)+'_border', _gui_GetWindow('diplomacy'));
      [*] = ;                           _gui_CreateBlinkElement('btnDiplomacyPlayer_'+IntToStr(proposePlayerInd), elmPortrait, 'gamepanel01.btn.round.73x73.highlight', false, 0, 0, 0, 0);
      [*] = ;                        end;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  {else
      [*] = ;                  if (gArrDiplomacy[proposePlayerInd][answerPlayerInd].message.treaty = gc_TreatyPeace) then // If offering peace to a union war ask me if I agree.
      [*] = ;                  begin
      [*] = ;                     var allyPlIndex, enemyPlIndex : Integer = -1;
      [*] = ;                     if (gArrDiplomacy[myPlIndex][proposePlayerInd].treaty = gc_TreatyUnion) then
      [*] = ;                     begin
      [*] = ;                        allyPlIndex := proposePlayerInd;
      [*] = ;                        enemyPlIndex := answerPlayerInd;
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     if (gArrDiplomacy[myPlIndex][answerPlayerInd].treaty = gc_TreatyUnion) then
      [*] = ;                     begin
      [*] = ;                        allyPlIndex := answerPlayerInd;
      [*] = ;                        enemyPlIndex := proposePlayerInd;
      [*] = ;                     end;
      [*] = ;                     
      [*] = ;                     if (allyPlIndex >= 0) then
      [*] = ;                     begin
      [*] = ;                        _diplomacy_UpdateDisplayPriority(myPlIndex, $10000);
      [*] = ;                        gArrDiplomacy[proposePlayerInd][myPlIndex].displayPriority := (gArrDiplomacy[proposePlayerInd][myPlIndex].displayPriority and $ffff) + $10000;
      [*] = ;                  
      [*] = ;                        if (gIntRegister_DiplomacyWindowMode > 0) then
      [*] = ;                        if (gArrDiplomacy[enemyPlIndex][myPlIndex].message.treaty <> gc_TreatyPeace) and (gArrDiplomacy[myPlIndex][enemyPlIndex].message.treaty <> gc_TreatyPeace) then
      [*] = ;                        begin
      [*] = ;                           PlayerExecuteStateByHandle(proposePlHandle, 'GetName');
      [*] = ;                           gStringRegister_EnemyPlayerName := StringRegister0;
      [*] = ;                           gIntRegister_QueryPlayerIndex := proposePlayerInd;
      [*] = ;
      [*] = ;                           PlayerExecuteStateByHandle(answerPlHandle, 'GetName');
      [*] = ;                           gStringRegister_EnemyPlayerNameDiplomacy := StringRegister0;
      [*] = ;                           gIntRegister_QueryPlayerIndex1 := answerPlayerInd;
      [*] = ;              
      [*] = ;                           StringRegister0 := IntToStr(gc_gui_query_diplAskPeaceFromUnion);
      [*] = ;                           GUIExecuteState('map.RequestQueryWindow');
      [*] = ;                        else;
      [*] = ;                     end;
      [*] = ;                  end;}
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            1 : begin // proposal/message accepted, the deal will be processed when the turn is passed
      [*] = ;               
      [*] = ;               // in case the offer was withdrawn/changed at the same time the other player accepted it, re-initiate it.
      [*] = ;               _diplomacy_Escrow(proposePlayerInd, answerPlayerInd, false);
      [*] = ;               IntRegister0 := 3; // unpack message
      [*] = ;               IntRegister1 := pLan;
      [*] = ;               IntRegister2 := proposePlayerInd;
      [*] = ;               IntRegister3 := answerPlayerInd;
      [*] = ;               GUIExecuteState('VVK.DiplomacyHelper');
      [*] = ;                  
      [*] = ;               _diplomacy_Escrow(proposePlayerInd, answerPlayerInd, true);
      [*] = ;               if proposePlayerInd = myPlIndex then
      [*] = ;                  _diplomacy_AssignMessage(gArrDiplomacy[proposePlayerInd][answerPlayerInd].queryWindowMessage, gArrDiplomacy[proposePlayerInd][answerPlayerInd].message);
      [*] = ;               
      [*] = ;               IntRegister0 := proposePlayerInd;
      [*] = ;               PlayerExecuteStateByHandle(answerPlHandle, 'HumanAcceptDeal');
      [*] = ;            end;
      [*] = ;            2 : begin // ally peace accept
	   [*] = ;               if messagePlInd >= 0 then
	   [*] = ;               begin
      [*] = ;                  IntRegister0 := proposePlayerInd;
      [*] = ;                  IntRegister1 := answerPlayerInd;
      [*] = ;                  PlayerExecuteStateByHandle(GetPlayerHandleByIndex(messagePlInd), 'AcceptPeaceFromUnion');
	   [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end; 
      [*] = ;//--- PLAYERLOSE
      [*] = ;   gc_LAN_SHARD_PLAYERLOSE : begin
      [*] = ;      var lose_idx : Integer = ParserGetIntValueByKeyByHandle(pLan, 'LosePlayer');
      [*] = ;
      [*] = ;      if (lose_idx <> gIntRegister_MapMyPlayerIndex) then
      [*] = ;      begin
      [*] = ;         BoolRegister0 := true;
      [*] = ;         IntRegister0 := 1;
      [*] = ;         GUIExecuteState('map.CreateStatistics');
      [*] = ;            
      [*] = ;         // end the game unless the loser is not the host of the game and there are more human players left
      [*] = ;         var i : Integer;
      [*] = ;         var bEndGame : Boolean = true;
      [*] = ;         if (lose_idx <> 0) then
      [*] = ;         for i := 1 to gGame.map.players-1 do
      [*] = ;         if (i <> lose_idx) then
      [*] = ;         begin
      [*] = ;            var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;            if _plr_IsInGame(plHandle) and SameText(GetPlayerControlModeByHandle(plHandle), 'cmPlayer') then
      [*] = ;            begin
      [*] = ;               bEndGame := false;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         var bSurrender : Boolean = ParserGetBoolValueByKeyByHandle(pLan, 'Surrender');
      [*] = ;         var g : Integer = ParserGetIntValueByKeyByHandle(pLan, 'gl');
      [*] = ;         //var ph : Integer = GetPlayerHandleByIndex(gIntRegister_MapMyPlayerIndex);
      [*] = ;         //var lose_h : Integer = GetPlayerHandleByIndex(lose_idx);
      [*] = ;         var arr : String = LanPublicServerProfInfo;_sa_SetIntAtIndex(arr,18,0);
      [*] = ;         //var arr : String = LanPublicServerProfInfo;_sa_SetIntAtIndex(arr,18,Round(5*g*Clamp((g*5)/Max(10,IntRegister0*5),0,1.5))+_sa_GetAsInt(arr,18));
      [*] = ;
      [*] = ;         // temporary solution for limited human players
      [*] = ;         if bEndGame then
      [*] = ;         begin
      [*] = ;            _prof_LanEndGame;
      [*] = ;            gIntRegister_QueryPlayerIndex := lose_idx;
	   [*] = ;            gBoolRegister_MapWin := true;
      [*] = ;            
      [*] = ;            if gIntRegister_CurGameMode = gc_GameModeTactics then
      [*] = ;               gStringRegister_AfterBattleQuery := IntToStr(gc_gui_query_lan_playerWin)
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var queryHandle : Integer;
      [*] = ;
      [*] = ;               if gIntRegister_CurQueryHandle <> 0 then
      [*] = ;                  queryHandle := _query_GetExecutedHandle()
      [*] = ;               else
      [*] = ;                  queryHandle := 0;
      [*] = ;            
      [*] = ;               if (queryHandle <> 0) and (QueryMachineIsResultHandle(queryHandle)) then
      [*] = ;                  QueryMachineResultSetNextQuery(queryHandle, IntToStr(gc_gui_query_lan_playerWin))
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  StringRegister0 := IntToStr(gc_gui_query_lan_playerWin);
      [*] = ;                  GUIExecuteState('map.RequestQueryWindow');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            _sa_SetIntAtIndex(arr,14,_sa_GetAsInt(arr,14)+1);_sa_SetIntAtIndex(arr,16,_sa_GetAsInt(arr,16)+1);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var pQuery : Integer = ParserAddChildByIndex(ParserSelectByHandleByKey(ParserSelectPlayer(myPlHandle), 'Queries'), '*');
      [*] = ;            ParserSetValueByKeyByHandle(pQuery, 'QueryID', ParserGetValueByKeyByHandle(pLan, 'QueryID'));
      [*] = ;            ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex', lose_idx);
      [*] = ;         end;
      [*] = ;         LanSetMyProfInfo(arr);LanPublicServerRegister();
      [*] = ;         LanPublicServerUpdateClientInfo(LanMyInfoID());
      [*] = ;
      [*] = ;         {PlayerExecuteStateByHandle(ph, 'PlayerWin');
      [*] = ;         // we will call query manually
      [*] = ;         gBoolRegister_MapWin := false;
      [*] = ;         gBoolRegister_GUIMapCheckEndGame := false;
      [*] = ;         if lose_h <> 0 then
      [*] = ;            PlayerExecuteStateByHandle(lose_h, 'GetName')
      [*] = ;         else
      [*] = ;            StringRegister0 := '???';
      [*] = ;         gStringRegister_EnemyPlayerName := StringRegister0;
      [*] = ;         StringRegister0 := IntToStr(gc_gui_query_lan_playerWin);
      [*] = ;         GUIExecuteState('map.RequestQueryWindow');}
      [*] = ;      end;
      [*] = ;//server: check if loading in progress, then add 1 to counter
      [*] = ;//all: change control to pc, set ingame flag to false
      [*] = ;//all: display information query regarding lost player
      [*] = ;{
      [*] = ;      var pLanIDs : Integer = ParserSelectByHandleByKey(pLan, 'LanIDs');
      [*] = ;      var i, j : Integer;
      [*] = ;
      [*] = ;      for i := ParserGetCountByHandle(pLanIDs)-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var pLanID : Integer = ParserSelectByHandleByIndex(pLanIDs, i);
      [*] = ;         var lanID : Integer = ParserGetIntValueByKeyByHandle(pLanID, 'LanID');
      [*] = ;         if lanID = gIntRegister_MyLanID then
      [*] = ;         begin
      [*] = ;            var plIndex : Integer = ParserGetIntValueByKeyByHandle(pLan, 'LosePlayer');
      [*] = ;            var queryID : String = ParserGetValueByKeyByHandle(pLan, 'QueryID');
      [*] = ;            var losePlHandle : Integer = GetPlayerHandleByIndex(plIndex);
      [*] = ;            PlayerExecuteStateByHandle(losePlHandle, 'GetCastleParser');
      [*] = ;            var pCastle : Integer = IntRegister0;
      [*] = ;            var plName : String = ParserGetValueByKeyByHandle(pCastle, 'Player');
      [*] = ;            var plHandle : Integer = GetPlayerHandleByName(plName);
      [*] = ;
      [*] = ;            IntRegister0 := plHandle;
      [*] = ;            PlayerExecuteStateByHandle(losePlHandle, 'DoPlayerLose');
      [*] = ;
      [*] = ;            var pPlParser : Integer = ParserSelectPlayer(myPlHandle);
      [*] = ;            var pQueries : Integer = ParserSelectByHandleByKey(pPlParser, 'Queries');
      [*] = ;            var add : Boolean = true;
      [*] = ;
      [*] = ;            for j := ParserGetCountByHandle(pQueries)-1 downto 0 do
      [*] = ;            begin
      [*] = ;               var pQuery : Integer = ParserSelectByHandleByIndex(pQueries, j);
      [*] = ;               var qID : String = ParserGetValueByKeyByHandle(pQuery, 'QueryID');
      [*] = ;               var plInd : Integer = ParserGetIntValueByKeyByHandle(pQuery, 'PlayerIndex');
      [*] = ;               if SameText(qID, queryID) and (plInd = plIndex) then
      [*] = ;               begin
      [*] = ;                  add := false;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;
      [*] = ;            if add then
      [*] = ;            begin
      [*] = ;               var pQuery : Integer = ParserAddChildByIndex(pQueries, '*');
      [*] = ;               ParserSetValueByKeyByHandle(pQuery, 'QueryID', queryID);
      [*] = ;               ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex', plIndex);
      [*] = ;            end;
      [*] = ;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;}
      [*] = ;   end;
      [*] = ;//--- SYNC_READY
      [*] = ;   gc_LAN_SHARD_SYNC_READY : begin
      [*] = ;      var timerID : Integer = ParserGetIntValueByKeyByHandle(pLan,'TimerID');
      [*] = ;      _lan_stimer_Ready(timerID, ParserGetIntValueByKeyByHandle(pLan,'LanID'));
      [*] = ;   end;
      [*] = ;//--- SYNC_RELEASE
      [*] = ;   gc_LAN_SHARD_SYNC_RELEASE : begin
      [*] = ;      _lan_stimer_Release(ParserGetIntValueByKeyByHandle(pLan,'TimerID'));
      [*] = ;      //_gui_PlaySound('interface','end_turn');
      [*] = ;   end;
      [*] = ;//--- SYNC_REVOKE
      [*] = ;   gc_LAN_SHARD_SYNC_REVOKE : begin
      [*] = ;      _lan_stimer_Revoke(ParserGetIntValueByKeyByHandle(pLan,'TimerID'),ParserGetIntValueByKeyByHandle(pLan,'LanID'),true);
      [*] = ;   end;
      [*] = ;//--- SHUTDOWN_GAME
      [*] = ;   gc_LAN_SHUTDOWN_GAME : begin
      [*] = ;      {var m : Integer = ParserGetIntValueByKeyByHandle(pLan, 'ExitMode');
      [*] = ;
      [*] = ;      if (gGame.gameType <> gc_GameTypeLanShard) and (ParserGetIntValueByKeyByHandle(pLan, 'Repeat') = 0) then
      [*] = ;      begin
      [*] = ;         var p : Integer = _misc_ParserGetOrCreateByKey('lan_controlgamemodechange',true);
      [*] = ;
      [*] = ;         ParserSetIntValueByKeyByHandle(p, 'ExitMode', m);
      [*] = ;         ParserSetIntValueByKeyByHandle(p, 'Repeat', 1);
      [*] = ;         _lan_LanSendParserToEnemy( gc_LAN_SHUTDOWN_GAME, p);
      [*] = ;      end;}
      [*] = ;
      [*] = ;      const cPlayerLeftWindowName = 'player_left';
      [*] = ;      const cBtnGameTerminate = 110;
      [*] = ;      _gui_ShowQuestionDialogWithFade('menu|player_left_game', '', 0, 'EventLanDialogs', cBtnGameTerminate, False, True, $f, cPlayerLeftWindowName);
      [*] = ;
      [*] = ;      {LanPublicServerCloseSession();
      [*] = ;      LanTerminateGame();
      [*] = ;      _misc_ParserGetOrCreateByKey('LanSync',true);
      [*] = ;
      [*] = ;      if m = gc_gui_ModeExitLanGame then
      [*] = ;         _run_ExitGame()
      [*] = ;      else
      [*] = ;         _run_DoCreateMenu();}
      [*] = ;   end;
      [*] = ;//--- EXITPLACEMENTMODE
      [*] = ;   gc_LAN_EXITPLACEMENTMODE : begin
      [*] = ;      _misc_ParserGetOrCreateByKey('battle_placement', false);
      [*] = ;      ParserCopyFromByHandle(pLan);
      [*] = ;      
      [*] = ;      _lan_timer_Reset(gc_lt_placement,true,'GUI.INC\LAN\LAN.PROCESSPARSER ['+IntToStr(pID)+']');
      [*] = ;      
      [*] = ;      SetPlayerBoolValueIndByHandle(GetPlayerHandleByName(gc_battle_attackPlayerName), gc_battle_PLStack_bCheckSabotage, false);
      [*] = ;      SetPlayerBoolValueIndByHandle(GetPlayerHandleByName(gc_battle_defendPlayerName), gc_battle_PLStack_bCheckSabotage, false);
      [*] = ;      
      [*] = ;      MapExecuteState('bat.CheckSabotage');
      [*] = ;   end;
      [*] = ;//--- CLIENTPLACEMENT
      [*] = ;   gc_LAN_CLIENTPLACEMENT : begin
      [*] = ;      _misc_ParserGetOrCreateByKey('battle_placement', false);
      [*] = ;      ParserCopyFromByHandle(pLan);
      [*] = ;      
      [*] = ;      _lan_timer_Reset(gc_lt_placement,true,'GUI.INC\LAN\LAN.PROCESSPARSER ['+IntToStr(pID)+']');
      [*] = ;   end;
      [*] = ;//--- CLIENTPLACEMENTREADY
      [*] = ;   gc_LAN_CLIENTPLACEMENTREADY : begin
      [*] = ;      var pPlacement : Integer = _misc_ParserGetOrCreateByKey('battle_placement', false);
      [*] = ;      ParserCopyFromByHandle(pLan);
      [*] = ;      
      [*] = ;      var lan_id : Integer = gIntRegister_MyLanID;
      [*] = ;
      [*] = ;      if lan_id = gIntRegsiter_LanBatServerID then
      [*] = ;      begin
      [*] = ;         if (gIntRegister_InetLanTurn=-1) then
      [*] = ;         begin
      [*] = ;            if _log then _log_lan('master -- starts game');
      [*] = ;            _lan_LanSendParserToEnemy( gc_LAN_EXITPLACEMENTMODE, pPlacement);
      [*] = ;            _lan_timer_Reset(gc_lt_placement,true,'GUI.INC\LAN\LAN.PROCESSPARSER ['+IntToStr(pID)+']');
      [*] = ;            
      [*] = ;            SetPlayerBoolValueIndByHandle(GetPlayerHandleByName(gc_battle_attackPlayerName), gc_battle_PLStack_bCheckSabotage, false);
      [*] = ;            SetPlayerBoolValueIndByHandle(GetPlayerHandleByName(gc_battle_defendPlayerName), gc_battle_PLStack_bCheckSabotage, false);
      [*] = ;      
      [*] = ;            MapExecuteState('bat.CheckSabotage');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            //my placement
      [*] = ;            if _log then _log_lan('master -- my placement');
      [*] = ;            _lan_timer_Reset(gc_lt_placement,true,'GUI.INC\LAN\LAN.PROCESSPARSER ['+IntToStr(pID)+']');
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if lan_id = gIntRegsiter_LanBatClientID then
      [*] = ;            ErrorLogI(_log_name+' gc_LAN_CLIENTPLACEMENTREADY : Server = '+IntToStr(gIntRegsiter_LanBatServerID))
      [*] = ;         else
      [*] = ;            ErrorLogI(_log_name+' gc_LAN_CLIENTPLACEMENTREADY : Wrong destination - '+IntToStr(lan_id));
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;//--- MASTERENDTURN
      [*] = ;   gc_LAN_MASTERENDTURN : begin
      [*] = ;      gIntRegister_LanSwitchToClientTurn := ParserGetIntValueByKeyByHandle(pLan, 'ActionSyncEnum');
      [*] = ;   end;
      [*] = ;//--- CLIENTENDTURN
      [*] = ;   gc_LAN_CLIENTENDTURN : begin
      [*] = ;      gIntRegister_LanSwitchToMasterTurn := ParserGetIntValueByKeyByHandle(pLan, 'ActionSyncEnum');
      [*] = ;   end;
      [*] = ;//--- DUMP
      [*] = ;   gc_LAN_DUMP : begin
      [*] = ;   end;
      [*] = ;//--- ACTION
      [*] = ;   gc_LAN_ACTION : begin
      [*] = ;      var unit_handle : Integer;
      [*] = ;
      [*] = ;      //if _log then DumpLogInfo(pLan);
      [*] = ;
      [*] = ;      unit_handle := GetGameObjectHandleByUniqueId(_lan_ConvertToBattleUID(ParserGetIntValueByKeyByHandle(pLan, 'src_index')));
      [*] = ;      if (unit_handle=0) then
      [*] = ;         ErrorLogI(_log_name+' leSessionParser invalid handle idx='+ParserGetValueByKeyByHandle(pLan, 'src_index'))
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var actionSyncEnum : Integer = ParserGetIntValueByKeyByHandle(pLan, 'ActionSyncEnum');
      [*] = ;         if _log then _log_lan('lan.ProcessParser, ActionSyncEnum '+IntToStr(actionSyncEnum));
      [*] = ;         
      [*] = ;         var pLanSyncs : Integer = _misc_ParserGetOrCreateByKey('LanSync',false);
      [*] = ;         var pLanSync : Integer;
      [*] = ;
      [*] = ;         pLanSync := ParserAddChildByIndex(pLanSyncs, '*');
      [*] = ;         ParserSelectByHandle(pLan);
      [*] = ;         ParserCopyToByHandle(pLanSync);
      [*] = ;
      [*] = ;         if (actionSyncEnum=(gIntRegister_InetLanActionSyncEnum+1)) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := pLanSync;
      [*] = ;            GameObjectExecuteStateByHandle(unit_handle,'EvaluateOrderParser');
      [*] = ;            _inet_ExecuteLanSyncParser();
      [*] = ;         end
      [*] = ;         else
      [*] = ;             ErrorLogI(_log_name+' ActionSyncEnum unsyncronised : actionSyncEnum='+IntToStr(actionSyncEnum)+' InetLanActionSyncEnum+1='+IntToStr(gIntRegister_InetLanActionSyncEnum+1));
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;//--- CLIENTWIN
      [*] = ;   gc_LAN_CLIENTWIN : begin
      [*] = ;      MapExecuteState('bat.WinBattle');
      [*] = ;      SetFloatValueByName('guiBattleResultWindowDelay', GetGameTime()-cBattleResultDelay-1);
      [*] = ;      //if (gIntRegister_BattleAttackHeroHandle <> 0) then
      [*] = ;      //   SetGameObjectBoolValueIndByHandle(gIntRegister_BattleAttackHeroHandle, gc_map_GOStack_MapUnit_bIsDead, true);
      [*] = ;      gBoolRegister_GUIBattleResultWindow := True;
      [*] = ;   end;
      [*] = ;//--- MASTERWIN
      [*] = ;   gc_LAN_MASTERWIN : begin
      [*] = ;      MapExecuteState('bat.LoseBattle');
      [*] = ;      SetFloatValueByName('guiBattleResultWindowDelay', GetGameTime()-cBattleResultDelay-1);
      [*] = ;      gBoolRegister_GUIBattleResultWindow := True;
      [*] = ;   end;
      [*] = ;//--- CLIENTSURRENDER
      [*] = ;   gc_LAN_CLIENTSURRENDER : begin
      [*] = ;      _lan_LanSendParserToEnemy( gc_LAN_MASTERWIN, _pars_ParserEmpty());
      [*] = ;      if (gIntRegister_MyLanID = gIntRegsiter_LanBatServerID) then
      [*] = ;      begin
      [*] = ;         MapExecuteState('bat.WinBattle');
      [*] = ;
      [*] = ;         SetFloatValueByName('guiBattleResultWindowDelay', GetGameTime()-cBattleResultDelay-1);
      [*] = ;         gBoolRegister_GUIBattleResultWindow := True;
      [*] = ;         LanSrvSetClientScore(LanMyInfoID(), 1);
      [*] = ;         LanSrvSetClientScore(_inet_GetLanEnemyID(), -1);
      [*] = ;         LanPublicServerCloseSession();
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   gc_LAN_RESEND_PARSER_REQUEST : begin
      [*] = ;      var fromID : Integer = ParserGetIntValueByKeyByHandle(pLan, 'FromID');
      [*] = ;      
      [*] = ;      var pPlayerSyncData : Integer = _lan_GetPlayerSyncData(fromID);
      [*] = ;      if pPlayerSyncData <> 0 then
      [*] = ;      begin
      [*] = ;         var parsersReceived : Integer = _pars_GetIntValueByKeyByHandleDef(pLan, 'ParsersReceived_'+IntToStr(gIntRegister_MyLanID), -1);
      [*] = ;         if parsersReceived >= 0 then
      [*] = ;         begin
      [*] = ;            var i, pBackup, pBackupParser, parserID : Integer;
      [*] = ;            var pPlayerBackupParsers : Integer = ParserSelectByHandleByKey(pPlayerSyncData, 'BackupParsers');
      [*] = ;            var backupCount : Integer = ParserGetCountByHandle(pPlayerBackupParsers);
      [*] = ;            var parsersSent : Integer = ParserGetIntValueByKeyByHandle(pPlayerSyncData, 'ParsersSent');
      [*] = ;            var requestCount : Integer = parsersSent - parsersReceived;
      [*] = ;            var startIndex : Integer = backupCount - requestCount;
      [*] = ;            if startIndex < 0 then
      [*] = ;            begin
      [*] = ;               ErrorLogI('Cannot send all asked backup parsers, missing parsers count: '+IntToStr(Round(Abs(startIndex)))+', asked parsers count: '+IntToStr(Round(Abs(requestCount))));
      [*] = ;               startIndex := 0;
      [*] = ;            end;
      [*] = ;            
      [*] = ;            for i := startIndex to backupCount-1 do
      [*] = ;            begin
      [*] = ;               pBackup := ParserSelectByHandleByIndex(pPlayerBackupParsers, i);
      [*] = ;               parserID := ParserGetIntValueByKeyByHandle(pBackup, 'ParserID');
      [*] = ;               if parserID > 0 then
      [*] = ;               begin
      [*] = ;                  pBackupParser := ParserSelectByHandleByKey(pBackup, 'Parser');
      [*] = ;                  _lan_StartParserTransfer(parserID, pBackupParser);
      [*] = ;                  LanPublicServerSendSessionParser(fromID, parserID, pBackupParser);
      [*] = ;                  _lan_FinishParserTransfer();
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

