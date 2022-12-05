section.begin
   Name = vvk.lan.OnProgressGUI
   Code : struct.begin
      [*] = ;if (gGame.gameType <> gc_GameTypeLanShard) and (gGame.gameType <> gc_GameTypeLanBattle) then
      [*] = ;   exit;
      [*] = ;
      [*] = ;const cEventState = 'EventLanDialogs';
      [*] = ;const cBtnGameTerminate = 110;
      [*] = ;const cShellChatList = 'internetshell.rightpanel.chat.history';
      [*] = ;const cShellClientsList = 'internetshell.rightpanel.players.list';
      [*] = ;const cCannotConnectWindowName = 'cannot_connect';
      [*] = ;const cPlayerLeftWindowName = 'player_left';
      [*] = ;
      [*] = ;var _log_name : String = 'GUI.INC\LAN\VVK.LAN.ONPROGRESSGUI';
      [*] = ;var _log : Boolean = true;
      [*] = ;	
      [*] = ;
      [*] = ;procedure GetLanEventNameByID(const id : Integer; var name : String);
      [*] = ;begin
      [*] = ;   IntRegister0 := 5;
      [*] = ;   IntRegister1 := id;
      [*] = ;   GUIExecuteState('VVK.LanLogHelper');
      [*] = ;   name := StringRegister0;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;function IsEveryoneOnline() : Boolean;
      [*] = ;begin
      [*] = ;   Result := True;
      [*] = ;   
      [*] = ;   if gGame.gameType = gc_GameTypeLanShard then
      [*] = ;   begin
      [*] = ;      var i, id, plHandle : Integer;
      [*] = ;      for i := 0 to gc_MaxLanMapHumanPlayers-1 do
      [*] = ;      begin
      [*] = ;         plHandle := GetPlayerHandleByIndex(i);
      [*] = ;         if _plr_IsInGame(plHandle) then
      [*] = ;         begin
      [*] = ;            id := gLanShardGame.arrlanplayers[i].lanid;
      [*] = ;            if (id > 0) and (not _inet_IsPlayerOnlineByID(id)) then
      [*] = ;            begin
      [*] = ;               Result := False;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if gGame.gameType = gc_GameTypeLanBattle then
      [*] = ;   begin
      [*] = ;      Result := _inet_IsPlayerOnlineByID(gLanHeroServer.lanid) and _inet_IsPlayerOnlineByID(gLanHeroClient.lanid);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;function IsEndOfGame() : Boolean;
      [*] = ;begin
      [*] = ;   case gGame.gameType of
      [*] = ;      gc_GameTypeLanBattle : Result := gBoolRegister_GUIBattleResultWindow;
      [*] = ;      gc_GameTypeLanShard : Result := gBoolRegister_MapLose or gBoolRegister_MapWin;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;function GetExpectedHostID() : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;	
      [*] = ;   if gGame.gameType = gc_GameTypeLanBattle then
      [*] = ;      Result := gLanHeroServer.lanid
      [*] = ;   else
      [*] = ;   if gGame.gameType = gc_GameTypeLanShard then
      [*] = ;   begin
      [*] = ;      var i, plHandle : Integer;
      [*] = ;      for i := 0 to gc_MaxCustomMapPlayer-1 do
      [*] = ;      begin
      [*] = ;         plHandle := GetPlayerHandleByIndex(i);
      [*] = ;         if _plr_IsInGame(plHandle) then
      [*] = ;         begin
      [*] = ;            Result := gLanShardGame.arrlanplayers[i].lanid;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;procedure RecreateLanGame();
      [*] = ;begin
      [*] = ;   if _log then _log_lan('RecreateLanGame');
      [*] = ;   var game_name : String = '-'+IntToStr(LanMyInfoID); // negative (=load) so not anyone can join
      [*] = ;   LanCreateGame('', game_name, '', gc_MaxCustomMapPlayer);
      [*] = ;   LanClSetMyTeam(0);
      [*] = ;   LanSrvSetBattleFieldMode(0);
      [*] = ;   LanSrvSetFogOfWarMode(True);
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;procedure RestartLanGame();
      [*] = ;begin
      [*] = ;   if _log then _log_lan('RestartLanGame');
      [*] = ;   if GetLanMode >= 2 then
      [*] = ;      LanLockServer();
      [*] = ;   LanSrvSetMapFile('');
      [*] = ;   LanDoStart(); // parsers sent will be leParser before LanDoStart, and leSessionParser after.
      [*] = ;end;
      [*] = ;	
      [*] = ;
      [*] = ;var sLe : String;
      [*] = ;var n,i,le, plrID, plInd : Integer;
      [*] = ;
      [*] = ;var myLanID : Integer = LanMyInfoID();
      [*] = ;
      [*] = ;if gBoolRegister_GUIStartup and (myLanID <> 0) then
      [*] = ;begin
      [*] = ;   _lan_timer_Reset(gc_lt_ALL,true,_log_name+'[Startup]');
      [*] = ;         
      [*] = ;   gStringRegister_LanCurrentBattleIDs := '';
      [*] = ;   if (gGame.gameType = gc_GameTypeLanShard) then
      [*] = ;   begin
      [*] = ;      SetFloatValueByName('MapLastLanPing', 0); // so that no regular checks are not performed before all players have finished loading (could cause bug: getting stuck in please wait to end turn)
      [*] = ;      _lan_stimer_Start(gc_lt_map_loading_sync,false);
      [*] = ;   end
      [*] = ;   else 
      [*] = ;   if (gGame.gameType = gc_GameTypeLanBattle) then
      [*] = ;   begin
      [*] = ;      SetFloatValueByName('LastLanPing', 0);
      [*] = ;      _lan_timer_Arm(gc_lt_loading,0,false);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_lan_stimer_Idle(gc_lt_ALL);
      [*] = ;
      [*] = ;n := gIntRegister_LanParsersBufferIndex;
      [*] = ;
      [*] = ;gIntRegister_LanParsersBufferIndex := n xor 1;
      [*] = ;for i := 0 to gIntRegister_LanParsersNumber[n]-1 do
      [*] = ;begin
      [*] = ;   le := gArr_LanParsersQueue[i][n].t;
      [*] = ;   GetLanEventNameByID(le, sLe);
      [*] = ;   if (le <> leParser) and (le <> leSessionParser) then // ID in parser is not player ID but parser ID
      [*] = ;   begin
      [*] = ;      plrID := gArr_LanParsersQueue[i][n].id;
      [*] = ;      plInd := _lan_GetPlayerIndexByLanID(plrID);
      [*] = ;      if (plInd >= 0) and _log then _log_lan(_log_name+'['+sLe+'], Player Index: '+IntToStr(plInd)+', Player LanID: '+IntToStr(plrID));
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if _log then _log_lan(_log_name+'['+sLe+'], Parser ID: '+IntToStr(gArr_LanParsersQueue[i][n].id));
      [*] = ;   
      [*] = ;   case le of
      [*] = ;      leParser, leSessionParser : begin
      [*] = ;         IntRegister0 := gArr_LanParsersQueue[i][n].id;
      [*] = ;         IntRegister1 := gArr_LanParsersQueue[i][n].parser;
      [*] = ;         GUIExecuteState('lan.ProcessParser');
      [*] = ;      end;
      [*] = ;      leReady : begin
      [*] = ;         SetFloatValueByName('LastLanPing', GetCurrentTime());
      [*] = ;         _lan_timer_Reset(gc_lt_loading,false, _log_name+'[leReady]');
      [*] = ;         _lan_timer_Arm(gc_lt_placement,0,true);
      [*] = ;         			   
      [*] = ;         if (myLanID = gIntRegsiter_LanBatServerID) then
      [*] = ;         begin
      [*] = ;            var curPlHandle : Integer = GetPlayerHandleByIndex(gIntRegister_BattleCurPlIndex);
      [*] = ;            var myPlHandle : Integer = GetPlayerHandleInterfaceIO();
      [*] = ;
      [*] = ;            if (myPlHandle=curPlHandle) then
      [*] = ;            begin
      [*] = ;               gIntRegister_InetLanTurn := -1;
      [*] = ;               _lan_timer_Reset(gc_lt_placement,true,_log_name+'[leReady]');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               gIntRegister_InetLanTurn := -2;
      [*] = ;               _lan_LanSendParserToEnemy(gc_LAN_CLIENTPLACEMENT, _pars_ParserEmpty());
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      leTerminated : begin
      [*] = ;      end;
      [*] = ;      leError : begin
      [*] = ;         if _lan_IsPlayerInGame(plrID) then
      [*] = ;         begin
      [*] = ;            _lan_timer_Reset(gc_lt_connect, false, _log_name+'[leError]');
      [*] = ;            _lan_timer_Reset(gc_lt_server_answer, false, _log_name+'[leError]');
      [*] = ;            _lan_timer_Reset(gc_lt_auth, false, _log_name+'[leError]');
      [*] = ;            LanShutDown(); // so IsLanPublicServerMode returns false and reconnection attempt triggers
      [*] = ;            _gui_ShowQuestionDialogWithFade('menu|leError', '', 0, 'DoLanConnect', 0, False, True, $f, cCannotConnectWindowName);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      leShutdown : begin
      [*] = ;         if _lan_IsPlayerInGame(plrID) then
      [*] = ;         begin
      [*] = ;            _lan_timer_Reset(gc_lt_connect, false, _log_name+'[leShutdown]');
      [*] = ;            _lan_timer_Reset(gc_lt_server_answer, false, _log_name+'[leShutdown]');
      [*] = ;            _lan_timer_Reset(gc_lt_auth, false, _log_name+'[leShutdown]');
      [*] = ;            
      [*] = ;            _gui_RootWindowRemoveWithFade(_gui_GetWindow('internetshell'),gc_gui_FadeTime0_2);
      [*] = ;            IntRegister0 := 1;
      [*] = ;            GUIExecuteState('ShowAstralChat');
      [*] = ;      
      [*] = ;            var chatBlink : Boolean;
      [*] = ;            _gui_RemoveBlinkElement('btnOpenChatBlink', chatBlink);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      leShellClientInfo, leShellClientUpdateInfo : _inet_UpdateClientsList(cShellClientsList, 0);
      [*] = ;      leShellMessage : _inet_AddChatMessage(False, cShellChatList);
      [*] = ;      leShellSessionMessage : begin
      [*] = ;         var p : Integer = gArr_LanParsersQueue[i][n].parser;
      [*] = ;         _cmd_Post('.generallanconsolereceive','', IntToStr(ParserGetIntValueByKeyByHandle(p, 'From'))+#128+ParserGetValueByKeyByHandle(p, 'Msg'));
      [*] = ;      end;
      [*] = ;      leShellClientDisconnected : begin // does not trigger if I personally disconnect (if I am host?)
      [*] = ;      end;
      [*] = ;      leShellClientConnected : begin
      [*] = ;         if (not IsEndOfGame) and (_gui_GetWindow(cPlayerLeftWindowName) = 0) then
      [*] = ;         begin
      [*] = ;            if (plrID = myLanID) then // I reconnected to the public server during an online game.
      [*] = ;            begin
      [*] = ;               _gui_RootWindowRemoveWithFade(_gui_GetWindow(cCannotConnectWindowName), gc_gui_FadeTime0_2);
      [*] = ;               _log_lan('Reconnected to the server.');
      [*] = ;               _lan_timer_Reset(gc_lt_auth, false, _log_name+'[leShellClientConnected]');
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if _lan_IsPlayerInGame(plrID) then // another player from my game reconnected to the public server
      [*] = ;               begin
      [*] = ;                  var lanMode : Integer = GetLanMode();
      [*] = ;                  if _log then _log_lan('Player from my game reconnected to the public server.');
      [*] = ;                  
      [*] = ;                  if (lanMode > 0) and IsEveryoneOnline() then // let's terminate the current session so we can recreate
      [*] = ;                  begin
      [*] = ;                     _log_lan('Everyone online again');
      [*] = ;                     if lanMode >= 2 then
      [*] = ;                        LanPublicServerCloseSession();
      [*] = ;                     LanTerminateGame();
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      leConnect : begin
      [*] = ;      end;
      [*] = ;      leDisconnect : begin
      [*] = ;         if (not IsEndOfGame) and (_gui_GetWindow(cPlayerLeftWindowName) = 0) then // player left window will appear only when the player has left the game, not just disconnected. 
      [*] = ;         begin
      [*] = ;            if _lan_IsPlayerInGame(plrID) then
      [*] = ;            begin
      [*] = ;               gBoolRegister_HaltLanProgress := True;
      [*] = ;               _lan_HoldBackupParsers(True);
      [*] = ;               
      [*] = ;               var status : Integer = _lan_stimer_Status(gc_lt_restart_session);
      [*] = ;               if (status <> gc_lan_timer_status_armed) and (status <> gc_lan_timer_status_released) then
      [*] = ;                  _lan_stimer_Start(gc_lt_restart_session, false); // we can start this for everyone here already because it won't deliver ready until GetLanMode > 0.
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      leShellSessionCreate : begin
      [*] = ;      end;
      [*] = ;      leShellSessionInfo : begin
      [*] = ;      end;
      [*] = ;      leShellSessionLock : begin
      [*] = ;      end;
      [*] = ;      leShellSessionLeave : begin
      [*] = ;      end;
      [*] = ;      leShellSessionJoin : begin
      [*] = ;         if (plrID = myLanID) then
      [*] = ;            _lan_timer_Reset(gc_lt_server_answer, false, _log_name+'[leShellSessionJoin]');
      [*] = ;      end;
      [*] = ;      else _log_lan(_log_name+'[Unintended lan event ID: '+IntToStr(le)+', event name: '+sLe+']');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;gIntRegister_LanParsersNumber[n] := 0;
      [*] = ;
      [*] = ;               
      [*] = ;if (not IsLanPublicServerMode) then // not connected and not attempting to connect to the server
      [*] = ;begin
      [*] = ;   _log_lan('Attempt to reconnect');
      [*] = ;   GUIExecuteState('DoLanConnect');
      [*] = ;end
      [*] = ;else
      [*] = ;if myLanID <> 0 then
      [*] = ;begin
      [*] = ;   if GetLanMode = 0 then // Session has been terminated because it needs to be recreated. Create or join recreated session
      [*] = ;   begin
      [*] = ;      var hostID : Integer = GetExpectedHostID(); // get the ID of who should be the host.
      [*] = ;      
      [*] = ;      if hostID > 0 then
      [*] = ;      begin
      [*] = ;         gLanShardGame.masterid := hostID;
      [*] = ;         
      [*] = ;         if hostID = myLanID then
      [*] = ;         begin
      [*] = ;            RecreateLanGame();
      [*] = ;         end
      [*] = ;         else // find the recreated session
      [*] = ;         begin
      [*] = ;            var pSessions : Integer = _misc_ParserGetOrCreateByKey('sessions', True);
      [*] = ;            var pSession : Integer;
      [*] = ;            var bSessionFound : Boolean = False;
      [*] = ;
      [*] = ;            LanPublicServerSessionsToParser(pSessions);
      [*] = ;
      [*] = ;            for i := 0 to ParserGetCountByHandle(pSessions)-1 do
      [*] = ;            begin
      [*] = ;               pSession := ParserSelectByHandleByIndex(pSessions, i);
      [*] = ;               _log_lan('host ID '+IntToStr(ParserGetIntValueByKeyByHandle(pSession, 'Master')));
      [*] = ;               if ParserGetIntValueByKeyByHandle(pSession, 'Master') = hostID then
      [*] = ;               begin
      [*] = ;                  bSessionFound := True;
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;               
      [*] = ;            if bSessionFound then
      [*] = ;            begin
      [*] = ;               _log_lan(_log_name+', Attempt to join session, host ID: '+IntToStr(hostID));
      [*] = ;               _lan_timer_Arm(gc_lt_server_answer, gc_gui_FadeTime0_4, false);
      [*] = ;               LanJoinGame('', IntToStr(hostID), False);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         ErrorLogI('Cannot re-establish lan session. Expected host ID is null');
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if not gBoolRegister_HaltLanProgress then  // no interruptions, progress business as usual
      [*] = ;      begin
      [*] = ;         // checking for the end of turn
      [*] = ;         MapExecuteState('map.LanCheckEndTurn');
      [*] = ;      
      [*] = ;         // checking for the completion of loading process
      [*] = ;         if _lan_stimer_Status(gc_lt_map_loading_sync) = gc_lan_timer_status_released then
      [*] = ;         begin
      [*] = ;            _lan_stimer_Reset(gc_lt_map_loading_sync,true);
      [*] = ;            SetFloatValueByName('MapLastLanPing', GetCurrentTime());
      [*] = ;         end;
      [*] = ;
      [*] = ;         if _lan_stimer_Status(gc_lt_map_start_turn) = gc_lan_timer_status_released then
      [*] = ;         begin
      [*] = ;            _lan_stimer_Reset(gc_lt_map_start_turn,true);
      [*] = ;   
      [*] = ;            if gBoolRegister_LanMapTurnPassed then
      [*] = ;            begin
	   [*] = ;               gBoolRegister_LanMapTurnPassed := false;
	   [*] = ;               _cmd_Post('mapnextturn','','2');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (gIntRegister_CurGameMode = gc_GameModeStrategy) then
      [*] = ;         begin
      [*] = ;            var lastPing : Float = GetFloatValueByName('MapLastLanPing');
      [*] = ;            if (lastPing <> 0) and ((lastPing + gc_PingInterval) < GetCurrentTime()) then
      [*] = ;            begin
      [*] = ;               _lan_LanSendParser(gc_LAN_DUMP, _pars_ParserEmpty());
      [*] = ;               SetFloatValueByName('MapLastLanPing', GetCurrentTime());
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if _lan_stimer_Status(gc_lt_restart_session) = gc_lan_timer_status_released then
      [*] = ;      begin
      [*] = ;         _lan_stimer_Reset(gc_lt_restart_session, True);
      [*] = ;         
      [*] = ;         RestartLanGame();
      [*] = ;         
      [*] = ;         var pParser : Integer = _misc_ParserGetOrCreateByKey('lan_sync_request', True);
      [*] = ;         ParserSetIntValueByKeyByHandle(pParser, 'FromID', myLanID);
      [*] = ;         
      [*] = ;         var lanID : Integer;
      [*] = ;         if gGame.gameType = gc_GameTypeLanShard then
      [*] = ;         begin
      [*] = ;            for i := 0 to gc_MaxCustomMapPlayer-1 do
      [*] = ;            begin
      [*] = ;               lanID := gLanShardGame.arrlanplayers[i].lanid;
      [*] = ;               if (lanID > 0) and (lanID <> myLanID) and _plr_IsInGame(GetPlayerHandleByIndex(i)) then
      [*] = ;                  ParserSetIntValueByKeyByHandle(pParser, 'ParsersReceived_'+IntToStr(lanID), _lan_GetPlayerParsersReceived(lanID));
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if gGame.gameType = gc_GameTypeLanBattle then
      [*] = ;         begin
      [*] = ;            lanID := _inet_GetLanEnemyID();
      [*] = ;            ParserSetIntValueByKeyByHandle(pParser, 'ParsersReceived_'+IntToStr(lanID), _lan_GetPlayerParsersReceived(lanID));
      [*] = ;         end;
      [*] = ;         
      [*] = ;         _lan_LanSendParser(gc_LAN_RESEND_PARSER_REQUEST, pParser);
      [*] = ;         
      [*] = ;         gBoolRegister_HaltLanProgress := False;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

