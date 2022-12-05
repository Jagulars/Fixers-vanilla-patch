section.begin
   Name = CheckPlayerLose
   Description : struct.begin
      [*] = ;BoolRegister0 - force lose activity (surrender, etc)
      [*] = ;OUT: BoolRegister1 - is player lose
      [*] = ;OUT: BoolRegister1 - is end of game
   struct.end
   Code : struct.begin
      [*] = ;var bForceLose : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'MAP\MAP.GLOBAL.UNIT.INC\CHECKPLAYERLOSE';
      [*] = ;var _log_trace : Integer = $40001;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;var isPlayerLose : Boolean = false;
      [*] = ;var isEndOfGame : Boolean = false;
      [*] = ;
      [*] = ;var thisPlHandle : Integer = GetPlayerCurrentPlHandle();
      [*] = ;var thisPlIndex : Integer = GetPlayerIndexByHandle(thisPlHandle);
      [*] = ;var thisPlName : String = GetPlayerNameByHandle(thisPlHandle);
      [*] = ;var thisCMode : String  = GetPlayerControlModeByHandle(thisPlHandle);
      [*] = ;var thisProfile : Integer = GetPlayerIntValueIndByHandle(thisPlHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;
      [*] = ;if (gGame.gameType = gc_GameTypeLanShard) and SameText(thisCMode, 'cmPlayer') then
      [*] = ;   thisProfile := gLanShardGame.arrLanPlayers[thisPlIndex].profile.avatar;
      [*] = ;
      [*] = ;var mapPlCount : Integer = _map_GetPlayersCount();
      [*] = ;var pProvinces : Integer = gStratHexCells.handle;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[P:'+thisPlName+',L:'+BoolToStr(bForceLose)+']',_log_trace);
      [*] = ;
      [*] = ;ExecuteState('IsInGame');
      [*] = ;var inGame : Boolean = BoolRegister0;
      [*] = ;if _log then _log_values('InGame_'+BoolToStr(inGame)+'|PlCount|'+thisCMode,0,mapPlCount,thisPlIndex,0,0,0);
      [*] = ;if inGame then
      [*] = ;begin
      [*] = ;   ExecuteState('GetCastleParser');
      [*] = ;   var cProvince : Integer = IntRegister0;
      [*] = ;   var cDummyUID : Integer = ParserGetIntValueByKeyByHandle(cProvince, 'DummyUID');
      [*] = ;   var cDummyHandle : Integer = GetGameObjectHandleByUniqueId(cDummyUID);
      [*] = ;   var provPlName : String = ParserGetValueByKeyByHandle(cProvince, 'Player');
      [*] = ;   var provPlHandle : Integer = GetPlayerHandleByName(provPlName);
      [*] = ;
      [*] = ;   if bForceLose or (provPlHandle <> thisPlHandle) then
      [*] = ;   begin
      [*] = ;      var i, j : Integer;
      [*] = ;      var humanPlCount : Integer = 0;
      [*] = ;      var plCount : Integer = 0;
      [*] = ;      var gl : Integer = 0;
      [*] = ;      var m : Integer = 4;
      [*] = ;      var gi : Integer = 18;
      [*] = ;      var gpi : Integer = 14;
      [*] = ;      var checkQuery : Boolean = (gGame.gameType <> gc_GameTypeLanShard); // only send query to other players from the actual loser in lan games
      [*] = ;
      [*] = ;      BoolRegister0 := false;
      [*] = ;      ExecuteState('SetInGameStatus');
      [*] = ;      isPlayerLose := true;
      [*] = ;
      [*] = ;      if SameText(thisCMode, 'cmPlayer') and (thisPlIndex = gIntRegister_MapMyPlayerIndex) then
      [*] = ;      begin
      [*] = ;         //if (gGame.gameType = gc_GameTypeHotseat) and gBoolRegister_MapResolveConflicts then
      [*] = ;         //   gIntRegister_MapMyPlayerIndex := myPlIndex;
      [*] = ;         var queryID : String = '';
      [*] = ;
      [*] = ;         if gGame.gameType = gc_GameTypeLanShard then
      [*] = ;            queryID := IntToStr(gc_gui_query_lan_playerMyLose)
      [*] = ;         else
      [*] = ;            queryID := IntToStr(gc_gui_query_playerMyLose);
      [*] = ;
      [*] = ;         if gIntRegister_CurGameMode = gc_GameModeTactics then
      [*] = ;            gStringRegister_AfterBattleQuery := queryID
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var resultHandle : Integer = 0;
      [*] = ;
      [*] = ;            if gIntRegister_CurQueryHandle <> 0 then
      [*] = ;               resultHandle := _query_GetExecutedHandle();
      [*] = ;
      [*] = ;            if (resultHandle <> 0) and (QueryMachineIsResultHandle(resultHandle)) then
      [*] = ;               QueryMachineResultSetNextQuery(resultHandle, queryID)
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               StringRegister0 := queryID;
      [*] = ;               GUIExecuteState('map.RequestQueryWindow');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         
      [*] = ;         if (gGame.gameType = gc_GameTypeLanShard) then
      [*] = ;         begin
      [*] = ;            gBoolRegister_MapLose := true;
      [*] = ;            BoolRegister0 := true;
      [*] = ;            IntRegister0 := 1;
      [*] = ;            GUIExecuteState('map.CreateStatistics');
      [*] = ;            
      [*] = ;            if bForceLose then begin var b : Boolean = true; m := 3; for i := 0 to gGame.map.players-1 do if (i <> thisPlIndex) and (gArrDiplomacy[thisPlIndex][i].treaty > 0) then begin b := false;break;end; if b then IntRegister0 := IntRegister0 div 10;end;
      [*] = ;            checkQuery := true;var arr : String = LanPublicServerProfInfo;_sa_SetIntAtIndex(arr,gi,0);{_sa_SetIntAtIndex(arr,gi,_sa_GetAsInt(arr,gi)+IntRegister0*m);}_sa_SetIntAtIndex(arr,gpi,_sa_GetAsInt(arr,gpi)+1);
      [*] = ;            LanSetMyProfInfo(arr);gl := IntRegister0;LanPublicServerRegister();LanPublicServerUpdateClientInfo(LanMyInfoID());_prof_LanEndGame;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      // send messages to all human players unless the loser is a computer, when it will be done on global sync
      [*] = ;      if checkQuery then
      [*] = ;      begin
      [*] = ;         var pParser : Integer = 0;
      [*] = ;         var pLanIDs : Integer = 0;
      [*] = ;         var curPlHandle : Integer = _gv_GetCurrentPlayerHandle();
      [*] = ;         var mapPlHandle : Integer = GetPlayerHandleByIndex(gIntRegister_MapMyPlayerIndex);
      [*] = ;         var queryID : String = '';
      [*] = ;         var isLan : Boolean = (gGame.gameType = gc_GameTypeLanShard) and SameText(thisCMode, 'cmPlayer');
      [*] = ;
      [*] = ;         if (thisProfile > 0) or SameText(thisCMode, 'cmPlayer') then
      [*] = ;         begin
      [*] = ;            if bForceLose then
      [*] = ;               queryID := '16100.23' // I surrender
      [*] = ;            else
      [*] = ;               queryID := IntToStr(gc_gui_query_playerCampPlayerLose);
      [*] = ;         end
      [*] = ;         else
      [*] = ;            queryID := IntToStr(gc_gui_query_playerLocalLordLose);
      [*] = ;
      [*] = ;         if isLan then
      [*] = ;         begin
      [*] = ;            pParser := _misc_ParserGetOrCreateByKey('cpl_CheckPlayerLose',true);
      [*] = ;            pLanIDs := ParserAddChildByIndex(pParser, 'LanIDs');
      [*] = ;            ParserSetIntValueByKeyByHandle(pParser, 'LosePlayer', thisPlIndex);
      [*] = ;            ParserSetValueByKeyByHandle(pParser, 'QueryID', queryID);
      [*] = ;            ParserSetIntValueByKeyByHandle(pParser, 'gl', gl);
      [*] = ;            ParserSetBoolValueByKeyByHandle(pParser, 'Surrender', bForceLose);
      [*] = ;         end;
      [*] = ;
      [*] = ;         for i := 0 to gGame.map.players-1 do
      [*] = ;         begin
      [*] = ;            var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;            //var profile : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iProfile);
      [*] = ;            var cMode : String = GetPlayerControlModeByHandle(plHandle);
      [*] = ;
      [*] = ;            if _plr_IsInGame(plHandle) and (SameText(cMode, 'cmPlayer')) then
      [*] = ;            begin
      [*] = ;               if (i = gIntRegister_MapMyPlayerIndex) and (mapPlHandle = provPlHandle) then // I conquered the enemy stronghold
      [*] = ;               begin
      [*] = ;                  gIntRegister_QueryPlayerIndex := thisPlIndex;
      [*] = ;                  PlayerExecuteStateByHandle(thisPlHandle, 'GetName');
      [*] = ;                  gStringRegister_EnemyPlayerName := StringRegister0;
      [*] = ;
      [*] = ;                  if gIntRegister_CurGameMode = gc_GameModeTactics then
      [*] = ;                     gStringRegister_AfterBattleQuery := queryID
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     var resultHandle : Integer = 0;
      [*] = ;
      [*] = ;                     if gIntRegister_CurQueryHandle <> 0 then
      [*] = ;                        resultHandle := _query_GetExecutedHandle();
      [*] = ;
      [*] = ;                     if (resultHandle <> 0) and (QueryMachineIsResultHandle(resultHandle)) then
      [*] = ;                        QueryMachineResultSetNextQuery(resultHandle, queryID)
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        StringRegister0 := queryID;
      [*] = ;                        GUIExecuteState('map.RequestQueryWindow');
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  if plHandle <> provPlHandle then
      [*] = ;                  begin
      [*] = ;                     if isLan then
      [*] = ;                     begin
      [*] = ;                        var pLanID : Integer = ParserAddChildByIndex(pLanIDs, '*');
      [*] = ;                        ParserSetIntValueByKeyByHandle(pLanID, 'LanID', gLanShardGame.arrLanPlayers[i].lanID);
      [*] = ;                     end
      [*] = ;                     else // for another hotseat player, message will be displayed at the start of their turn
      [*] = ;                     begin
      [*] = ;                        var pPlParser : Integer = ParserSelectPlayer(plHandle);
      [*] = ;                        var pQueries : Integer = ParserSelectByHandleByKey(pPlParser, 'Queries');
      [*] = ;                        var pQuery : Integer = ParserAddChildByIndex(pQueries, '*');
      [*] = ;                        ParserSetValueByKeyByHandle(pQuery, 'QueryID', queryID);
      [*] = ;                        ParserSetIntValueByKeyByHandle(pQuery, 'PlayerIndex', thisPlIndex);
      [*] = ;
      [*] = ;                        ErrorLogI(_log_name+' Query for player ' + IntToStr(i));
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if isLan then
      [*] = ;            _lan_LanSendParser(gc_LAN_SHARD_PLAYERLOSE, pParser);
      [*] = ;      end;
      [*] = ;
      [*] = ;      IntRegister0 := provPlHandle;
      [*] = ;      ExecuteState('DoPlayerLose');
      [*] = ;
      [*] = ;      var endOfGame : Boolean = false;
      [*] = ;      var humanPlHandle : Integer = 0;
      [*] = ;
      [*] = ;      for i := 0 to gGame.map.players-1 do
      [*] = ;      begin
      [*] = ;         var plHandle : Integer = GetPlayerHandleByIndex(i);
      [*] = ;
      [*] = ;         if _plr_IsInGame(plHandle) then
      [*] = ;         begin
      [*] = ;            if SameText(GetPlayerControlModeByHandle(plHandle), 'cmPlayer') then
      [*] = ;            begin
      [*] = ;               humanPlCount := humanPlCount + 1;
      [*] = ;               humanPlHandle := plHandle;
      [*] = ;            end;
      [*] = ;
      [*] = ;            plCount := plCount + 1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if (humanPlCount = 0) or (plCount = 1) then
      [*] = ;      begin
      [*] = ;         if gGame.gameType <> gc_GameTypeLanShard then
      [*] = ;         begin
      [*] = ;            if humanPlCount > 0 then
      [*] = ;            begin
      [*] = ;               gBoolRegister_MapWin := true;
      [*] = ;               if gBoolRegister_MapResolveConflicts then
      [*] = ;               begin
      [*] = ;                  _gv_SetIOHandle(humanPlHandle,_log_name);
      [*] = ;                  gIntRegister_MapMyPlayerIndex := GetPlayerIndexByHandle(humanPlHandle);
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;               gBoolRegister_MapLose := true;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if gIntRegister_CurGameMode = gc_GameModeStrategy then
      [*] = ;         begin
      [*] = ;            if (gGame.gameType = gc_GameTypeHotseat) and (not gBoolRegister_MapResolveConflicts) and gBoolRegister_MapWin then
      [*] = ;            begin
      [*] = ;               gBoolRegister_ShowPlayerHint := true;
      [*] = ;               _gv_SetIOHandle(humanPlHandle,_log_name);
      [*] = ;               gIntRegister_MapMyPlayerIndex := GetPlayerIndexByHandle(humanPlHandle);
      [*] = ;            end;
      [*] = ;
      [*] = ;            GUIExecuteState('map.CheckEndGame');
      [*] = ;         end;
      [*] = ;
      [*] = ;         if gGame.gameType = gc_GameTypeCampaign then
      [*] = ;            MapExecuteState('map.ShardFinishGame');
      [*] = ;
      [*] = ;         isEndOfGame := true;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;   isPlayerLose := true;
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'['+BoolToStr(isPlayerLose)+']',$1000000 or _log_trace);
      [*] = ;
      [*] = ;BoolRegister1 := isPlayerLose;
      [*] = ;BoolRegister2 := isEndOfGame;
      [*] = ;
      [*] = ;SwitchTo('Nothing');
   struct.end
section.end

