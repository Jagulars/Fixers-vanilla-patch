section.begin
   Name = LanEventDefault
   Code : struct.begin
      [*] = ;const cShellChatList = 'internetshell.rightpanel.chat.history';
      [*] = ;const cShellClientsList = 'internetshell.rightpanel.players.list';
      [*] = ;const cShellShardGamesList = 'internetshell.leftpanel.shardgames.list';
      [*] = ;const cShellLadderList = 'inetShellDialog.ladder.list';
      [*] = ;const cShellProfile = 'inetShellDialog.profile';
      [*] = ;
      [*] = ;const cBtnRefreshTag = 103;
      [*] = ;
      [*] = ;var _log_name : String = 'MENU.INC\LANEVENTDEFAULT';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;procedure DumpLanEvent();
      [*] = ;begin
      [*] = ;   var id : Integer = gLanEvent;
      [*] = ;   var log_event : Integer = 1;
      [*] = ;   var pid : Integer = 0;
      [*] = ;
      [*] = ;   if (id = leSessionParser) or (id = leParser) then
      [*] = ;   begin
      [*] = ;      pid := LanGetParserID();
      [*] = ;      {case pid of
      [*] = ;         gc_LAN_DUMP,
      [*] = ;         gc_LAN_SHARD_SYNC_READY,
      [*] = ;         gc_LAN_SHARD_SYNC_RELEASE :
      [*] = ;            log_event := 0;
      [*] = ;      end;}
      [*] = ;   end;
      [*] = ;
      [*] = ;   if log_event <> 0 then
      [*] = ;   begin
      [*] = ;      var nm,nmp : String;
      [*] = ;
      [*] = ;      IntRegister0 := 5;
      [*] = ;      IntRegister1 := id;
      [*] = ;      GUIExecuteState('VVK.LanLogHelper');
      [*] = ;      nm := StringRegister0;
      [*] = ;
      [*] = ;      IntRegister0 := 6;
      [*] = ;      IntRegister1 := pid;
      [*] = ;      GUIExecuteState('VVK.LanLogHelper');
      [*] = ;      nmp := StringRegister0;
      [*] = ;
      [*] = ;      _log_valuesl('THREADS|ID|'+nm+'|From|To|'+nmp+'[Tag]',LanGetSendDataThreadCount(),LanMyInfoID(),gLanEvent,LanPublicServerGetRegIDFrom(),LanPublicServerGetRegIDTo(),GetIntValueByName('Tag'));
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure UpdateLanShardGame();
      [*] = ;begin
      [*] = ;   var pSession : Integer = _misc_ParserGetOrCreateByKey('session_info', True);
      [*] = ;   var mapname : string;
      [*] = ;
      [*] = ;   if _log then _Log_lan(_log_name+' UpdateLanShardGame, ClientsCount='+IntToStr(LanGetClientsCount()));
      [*] = ;
      [*] = ;   LanPublicServerGetSessionInfoToParserByClientID(LanMyInfoID(),pSession);
      [*] = ;   if _log then ParserSaveToFileByHandle(pSession, '.\log\session_info.dat');
      [*] = ;   mapname := ParserGetValueByKeyByHandle(pSession, 'MapName');
      [*] = ;   if _log then _Log_lan(_log_name+' UpdateLanShardGame : mapname='+mapname);
      [*] = ;   Assert((mapname <> ''),_log_name+' UpdateLanShardGame - empty map name');
      [*] = ;   if mapname <> '' then
      [*] = ;   begin
      [*] = ;      if _inet_IsSaveGameMapName(mapname) then
      [*] = ;      begin
      [*] = ;         if _gui_GetWindow(cLanLoadGameSyncName) = 0 then
      [*] = ;         begin
      [*] = ;            var save_name,players : String;
      [*] = ;            var uid : Integer;
      [*] = ;
      [*] = ;            _inet_GetInetShardSaveParamsFromMap(mapname,save_name,uid,players);
      [*] = ;            StringRegister0 := ParserGetValueByKeyByHandle(pSession, 'GameName');
      [*] = ;            StringRegister1 := players;
      [*] = ;            GUIExecuteState('vvk.ShowLanLoadGameProgress');
      [*] = ;         end
      [*] = ;         else
      [*] = ;            _inet_RefreshLoadGameProgress(0);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var i,masterID,id,cno : Integer;
      [*] = ;         var players : array [0..(gc_MaxCustomMapPlayer+2)] of Integer;
      [*] = ;         var bValid : Boolean = False;
      [*] = ;
      [*] = ;         masterID := ParserGetIntValueByKeyByHandle(pSession, 'Master');
      [*] = ;         players[0] := masterID;
      [*] = ;
      [*] = ;         cno := 1;
      [*] = ;         for i:=0 to gc_MaxCustomMapPlayer-1 do
      [*] = ;         begin
      [*] = ;            id := LanGetClientIDByIndex(i);
      [*] = ;            if id <> 0 then
      [*] = ;            begin
      [*] = ;               if (id<>masterID) then
      [*] = ;               begin
      [*] = ;                  players[cno] := id;
      [*] = ;                  cno := cno + 1;
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  bValid := True;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (bValid) then
      [*] = ;         begin
      [*] = ;            var bInit : Boolean = (_gui_GetWindow('NewGame') = 0);
      [*] = ;            
      [*] = ;            if GetLanMode >= 2 then
      [*] = ;            begin
      [*] = ;               var name,info : String;
      [*] = ;               var pClient : Integer;
      [*] = ;
      [*] = ;               for i := cno to gc_MaxCustomMapPlayer-1 do
      [*] = ;                  players[i] := 0;
      [*] = ;               cno := 0;
      [*] = ;
      [*] = ;               // verify human players
      [*] = ;               for i:=0 to gc_MaxCustomMapPlayer-1 do
      [*] = ;               begin
      [*] = ;                  id := players[i];
      [*] = ;
      [*] = ;                  if (cno < gc_MaxLanMapHumanPlayers) and ((gMapSettings.arrplayers[i].control <> 0) or (id <> 0)) then
      [*] = ;                  begin
      [*] = ;                     cno := cno + 1;
      [*] = ;                     gMapSettings.arrplayers[i].control := 1;
      [*] = ;                     if id <> 0 then
      [*] = ;                     begin
      [*] = ;                        pClient := _misc_ParserGetOrCreateByKey('client_info', True);
      [*] = ;                        LanPublicServerGetClientInfoToParserByClientID(id, pClient);
      [*] = ;                        name := ParserGetValueByKeyByHandle(pClient, 'Nick');
      [*] = ;                        info := ParserGetValueByKeyByHandle(pClient, 'Info');
      [*] = ;                        gLanShardGame.arrlanplayers[i].lanid := id;
      [*] = ;                        gLanShardGame.arrlanplayers[i].profile.name := name;
      [*] = ;                        gLanShardGame.arrlanplayers[i].profile.land := name; // in online games, stronghold name is the same as player name.
      [*] = ;                        gLanShardGame.arrlanplayers[i].profile.color1 := _sa_GetAsInt(info, 0);
      [*] = ;                        gLanShardGame.arrlanplayers[i].profile.color2 := _sa_GetAsInt(info, 1);
      [*] = ;                        gLanShardGame.arrlanplayers[i].profile.sign := _sa_GetAsInt(info, 2);
      [*] = ;                        gLanShardGame.arrlanplayers[i].profile.avatar := _sa_GetAsInt(info, 3);
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                     begin
      [*] = ;                        gLanShardGame.arrlanplayers[i].lanid := 0;
      [*] = ;                        _inet_ClearHotseatProfile(gLanShardGame.arrlanplayers[i].profile);
      [*] = ;                     end;
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  begin
      [*] = ;                     if gMapSettings.arrplayers[i].control <> 0 then // more human players than is allowed
      [*] = ;                     begin
      [*] = ;                        gMapSettings.arrplayers[i].control := 0;
      [*] = ;                        gLanShardGame.arrlanplayers[i].lanid := 0;
      [*] = ;                        _inet_ClearHotseatProfile(gLanShardGame.arrlanplayers[i].profile);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;                  if _log then _Log_lan(_log_name+' UpdateLanShardGame idx='+IntToStr(i)+' id='+IntToStr(id)+' control='+IntToStr(gMapSettings.arrplayers[i].control));
      [*] = ;               end;
      [*] = ;               
      [*] = ;               var password : String;
      [*] = ;               _inet_GetInetShardPasswordByMapName(mapname, password);
      [*] = ;               _inet_MakeInetShardMapParamsString(mapname, password);
      [*] = ;               LanSrvSetMapFile(mapname);
      [*] = ;               
      [*] = ;               _inet_SendShardGameSettings();
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if bInit then
      [*] = ;               _lan_timer_Reset(gc_lt_server_answer,false,'MENU.INC\LANEVENTDEFAULT');
      [*] = ;            
      [*] = ;            GUIExecuteState('ShowNewGame');
      [*] = ;            
      [*] = ;            if (_gui_GetWindow('MapGeneratorSettings')<>0) then
      [*] = ;            begin
      [*] = ;               GUIExecuteState('ShowMapGeneratorSettings');
      [*] = ;            end;
      [*] = ;            if (_gui_GetWindow('Gameplay Settings')<>0) then
      [*] = ;            begin
      [*] = ;               StringRegister0 := 'Gameplay Settings';
      [*] = ;               GUIExecuteState('CreateWindowFromParser');
      [*] = ;            end;
      [*] = ;            if (_gui_GetWindow('Genesis Mode')<>0) then
      [*] = ;            begin
      [*] = ;               StringRegister0 := 'Genesis Mode';
      [*] = ;               GUIExecuteState('CreateWindowFromParser');
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if _log then _Log_lan(_log_name+' UpdateLanShardGame, bValid = False');
      [*] = ;            //for i:=0 to gc_MaxCustomMapPlayer-1 do
      [*] = ;            //begin
      [*] = ;            //   gLanShardGame.arrlanplayers[i].lanid := 0;
      [*] = ;            //   if i <> 0 then gMapSettings.arrplayers[i].control := 0;
      [*] = ;            //   _inet_ClearHotseatProfile(gLanShardGame.arrlanplayers[i].profile);
      [*] = ;            //end;
      [*] = ;            //gMapSettings.players := 0;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;//------------------------------------------------------------------------------
      [*] = ;procedure OnTerminateGame();
      [*] = ;begin
      [*] = ;   if _log then _Log_lan(_log_name+' OnTerminateGame : SwitchToInetShell(ShellPageIndex = 1)');
      [*] = ;end;
      [*] = ;
      [*] = ;//------------------------------------------------------------------------------
      [*] = ;procedure DoStartBattle();
      [*] = ;begin
      [*] = ;   if _log then _Log_lan(_log_name+' DoStartBattle');
      [*] = ;   _misc_ParserGetOrCreateByKey('LanSync',true);
      [*] = ;   LanSrvSetMapFile('');
      [*] = ;   LanDoStart();
      [*] = ;   GUIExecuteState('DoInetBattle');
      [*] = ;end;
      [*] = ;
      [*] = ;//------------------------------------------------------------------------------
      [*] = ;procedure DoStartShardGame(pLan : Integer);
      [*] = ;begin
      [*] = ;   if _log then _Log_lan(_log_name+' DoStartShardGame');
      [*] = ;   LanSrvSetMapFile('');
      [*] = ;   LanDoStart();
      [*] = ;   IntRegister0 := pLan;
      [*] = ;   GUIExecuteState('DoInetShardGame');
      [*] = ;end;
      [*] = ;
      [*] = ;//------------------------------------------------------------------------------
      [*] = ;procedure OnConnect(); // someone connects to you, or you connect to someone
      [*] = ;begin
      [*] = ;   var iID : Integer = GetIntValueByName('Tag');
      [*] = ;   if (gGame.gameType = gc_GameTypeLanBattle) and (GetLanMode()=1) and (iID<>LanMyInfoID()) then // connect as client
      [*] = ;   begin
      [*] = ;      var pInetBattle : Integer = _misc_ParserGetOrCreateByKey('led_oc_hero', True);
      [*] = ;
      [*] = ;      if _log then _Log_lan(_log_name+' OnConnect : GetLanMode=1; LanMyInfoID='+IntToStr(LanMyInfoID));
      [*] = ;      StateMachineGlobalVariablesSaveToParser(pInetBattle, 'gInetBattle', False, False);
      [*] = ;      var curhero : Integer = ParserGetIntValueByKeyByHandle(pInetBattle, 'curhero');
      [*] = ;      var pHeroes : Integer = ParserSelectByHandleByKey(pInetBattle, 'hero');
      [*] = ;      var pHero : Integer = ParserSelectByHandleByIndex(pHeroes, curhero);
      [*] = ;      ParserSetIntValueByKeyByHandle(pHero, 'lanid', LanMyInfoID());
      [*] = ;      ParserSetIntValueByKeyByHandle(pHero, 'allowedterrains', gInetShell.allowedterrains);
      [*] = ;      StateMachineGlobalVariablesLoadFromParser(pHero, 'gLanHeroClient', False, False);
      [*] = ;      _lan_LanSendParser(gc_LAN_HERO, pHero);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if (gGame.gameType=gc_GameTypeLanShard) then
      [*] = ;      begin
      [*] = ;         if _log then _Log_lan(_log_name+' OnConnect : gGame.gameType=gc_GameTypeLanShard');
      [*] = ;         if (GetLanMode = 1) then
      [*] = ;         begin
      [*] = ;            _lan_LanSendParser(gc_LAN_READY, _pars_ParserEmpty);
      [*] = ;            
      [*] = ;            var pSession : Integer = _misc_ParserGetOrCreateByKey('session_info', True);
      [*] = ;            LanPublicServerGetSessionInfoToParserByClientID(LanMyInfoID(),pSession);
      [*] = ;            
      [*] = ;            if _inet_IsSaveGameMapName(ParserGetValueByKeyByHandle(pSession, 'MapName')) then // if not saved game, don't update UI before the shard settings are received from the host.
      [*] = ;               UpdateLanShardGame();
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   //_gui_PlaySound('interface','end_turn');
      [*] = ;end;
      [*] = ;
      [*] = ;//------------------------------------------------------------------------------
      [*] = ;procedure ServerInfoUpdate();
      [*] = ;begin
      [*] = ;   if _log then _Log_lan(_log_name+' ServerInfoUpdate');
      [*] = ;end;
      [*] = ;
      [*] = ;//------------------------------------------------------------------------------
      [*] = ;procedure ParserReceived();
      [*] = ;begin
      [*] = ;   if (GetLanMode()<>0) then
      [*] = ;   begin
      [*] = ;      if _log then _Log_lan(_log_name+' OnParser : GetLanMode = '+IntToStr(GetLanMode)+' LanGetParserID = '+IntToStr(LanGetParserID()));
      [*] = ;      var pLan : Integer = LanSelectParser();
      [*] = ;      var from_id : Integer = LanPublicServerGetRegIDFrom();
      [*] = ;
      [*] = ;      _lan_LogReceivedParser('A'+IntToStr(from_id),LanGetParserID(),pLan,from_id);
      [*] = ;
      [*] = ;      if (GetLanMode()>=2) then // host
      [*] = ;      begin
      [*] = ;         case (LanGetParserID()) of
      [*] = ;            gc_LAN_HERO : begin
      [*] = ;               var myModVersion : String = gc_DataModName + '_' + gc_DataModVersion;
      [*] = ;                     
      [*] = ;               if _inet_IsSameVersionByID(from_id, myModVersion) then
      [*] = ;               begin
      [*] = ;                  var randKey0, randKey1 : Integer;
      [*] = ;                  var pInetBattle : Integer = _misc_ParserGetOrCreateByKey('led_pr_hero', True);
      [*] = ;
      [*] = ;                  GenerateMapRandKey(randKey0, randKey1);
      [*] = ;                  StateMachineGlobalVariablesSaveToParser(pInetBattle, 'gInetBattle', False, False);
      [*] = ;                  var curhero : Integer = ParserGetIntValueByKeyByHandle(pInetBattle, 'curhero');
      [*] = ;                  var pHeroes : Integer = ParserSelectByHandleByKey(pInetBattle, 'hero');
      [*] = ;                  var pHero : Integer = ParserSelectByHandleByIndex(pHeroes, curhero);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pHero, 'randkey0', randkey0);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pHero, 'randkey1', randkey1);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pHero, 'lanid', LanMyInfoID());
      [*] = ;                  ParserSetIntValueByKeyByHandle(pHero, 'allowedterrains', gInetShell.allowedterrains);
      [*] = ;                  StateMachineGlobalVariablesLoadFromParser(pLan, 'gLanHeroClient', False, False);
      [*] = ;                  StateMachineGlobalVariablesLoadFromParser(pHero, 'gLanHeroServer', False, False);
      [*] = ;                  gLanHeroClient.randkey0 := randKey0;
      [*] = ;                  gLanHeroClient.randkey1 := randKey1;
      [*] = ;                  _lan_LanSendParser(gc_LAN_HERO,pHero);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            gc_LAN_READY : begin
      [*] = ;               if gGame.gameType = gc_GameTypeLanBattle then
      [*] = ;               begin
      [*] = ;                  _lan_LanSendParser(gc_LAN_START,_pars_ParserEmpty());
      [*] = ;                  LanLockServer();
      [*] = ;                  DoStartBattle();
      [*] = ;               end
      [*] = ;               else
      [*] = ;               if (gGame.gameType = gc_GameTypeLanShard) then
      [*] = ;               begin
      [*] = ;                  if GetLanMode >= 2 then
      [*] = ;                     UpdateLanShardGame();
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (GetLanMode()=1) then // client
      [*] = ;         begin
      [*] = ;            case (LanGetParserID()) of
      [*] = ;               gc_LAN_HERO : begin
      [*] = ;                  StateMachineGlobalVariablesLoadFromParser(pLan, 'gLanHeroServer', False, False);
      [*] = ;                  gLanHeroClient.randkey0 := gLanHeroServer.randKey0;
      [*] = ;                  gLanHeroClient.randkey1 := gLanHeroServer.randKey1;
      [*] = ;                  _lan_LanSendParser(gc_LAN_READY, _pars_ParserEmpty());
      [*] = ;               end;
      [*] = ;               gc_LAN_START : begin
      [*] = ;                  case gGame.gameType of
      [*] = ;                     gc_GameTypeLanBattle : DoStartBattle();
      [*] = ;                     gc_GameTypeLanShard : DoStartShardGame(pLan);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               gc_LAN_SHARD_SETTINGS : begin
      [*] = ;                  var pMapSettings : Integer = ParserSelectByHandleByKey(pLan, 'gMapSettings');
      [*] = ;                  var pLanShardGame : Integer = ParserSelectByHandleByKey(pLan, 'gLanShardGame');
      [*] = ;
      [*] = ;                  StateMachineGlobalVariablesLoadFromParser(pMapSettings, 'gMapSettings', False, False);
      [*] = ;                  StateMachineGlobalVariablesLoadFromParser(pLanShardGame, 'gLanShardGame', False, False);
      [*] = ;
      [*] = ;                  UpdateLanShardGame();
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;//------------------------------------------------------------------------------
      [*] = ;procedure CreateSession(elmName : String);
      [*] = ;begin
      [*] = ;   var idfrom : Integer = LanPublicServerGetRegIDFrom();
      [*] = ;
      [*] = ;   if _log then _Log_lan(_log_name+' CreateSession');
      [*] = ;   _inet_UpdateClientsList(cShellClientsList,0);
      [*] = ;   _inet_UpdateShardGamesList(cShellShardGamesList);
      [*] = ;
      [*] = ;   if (idFrom=LanMyInfoID()) then
      [*] = ;   begin
      [*] = ;      if (gGame.gameType=gc_GameTypeLanShard) then
      [*] = ;      begin
      [*] = ;         _lan_timer_Reset(gc_lt_server_answer,false,'MENU.INC\LANEVENTDEFAULT');
      [*] = ;         _gui_RootWindowRemoveWithFade(_gui_GetWindow('internetcreateshardcustom'),gc_gui_FadeTime0_2);
      [*] = ;         UpdateLanShardGame();
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         _gui_FadeWindow_VVK(_gui_GetWindow('internetshell'), gc_gui_FadeTime0_2, 2);
      [*] = ;         const cEventState = 'EventInternetShell';
      [*] = ;         const cBtnCancelPlaySearch = 303;
      [*] = ;         _lan_timer_Reset(gc_lt_server_answer,false,'MENU.INC\LANEVENTDEFAULT');
      [*] = ;         var windowHandle : Integer = _gui_ShowQuestionDialog('menu|188', '', 0, cEventState, cBtnCancelPlaySearch, False, True); //LAN.SHELL.CREATING.GAME
      [*] = ;         _gui_CreateAstralChatButton(windowHandle, -54, -15);
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else // someone else creates a session
      [*] = ;   begin
      [*] = ;      var pSession : Integer = _misc_ParserGetOrCreateByKey('session_info', True);
      [*] = ;      LanPublicServerGetSessionInfoToParserByClientID(idfrom, pSession);
      [*] = ;      if (pSession<>0) then
      [*] = ;      begin
      [*] = ;         var mapname : String = ParserGetValueByKeyByHandle(pSession, 'MapName');
      [*] = ;         if _inet_IsSaveGameMapName(mapname) then 
      [*] = ;         begin
      [*] = ;            if _inet_IsSaveValidForClient(LanMyInfoID, mapname) > 0 then // I have participated in this saved game
      [*] = ;            begin
      [*] = ;               _gui_PlaySound('interface', 'end_turn');
      [*] = ;               if (_gui_GetWindow('internetshell.rightpanel.chat.history') = 0) then
      [*] = ;                  _gui_CreateBlinkElement('btnOpenChatBlink', _gui_GetWindow('open_chat_button.btnOpen'), gc_gui_material_blink_btn_round, false, 0, 0, 0, 0);
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if ((gProfile.chatnotifications and 4) > 0) and (_gui_GetWindow('internetshell.rightpanel.chat.history') = 0) then
      [*] = ;            _gui_CreateBlinkElement('btnOpenChatBlink', _gui_GetWindow('open_chat_button.btnOpen'), gc_gui_material_blink_btn_round, false, 0, 0, 0, 0);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;//------------------------------------------------------------------------------
      [*] = ;procedure UpdateSession(elmroomname, elmclientname : String);
      [*] = ;begin
      [*] = ;   //var idfrom : Integer = LanPublicServerGetRegIDFrom();
      [*] = ;
      [*] = ;   if _log then _Log_lan(_log_name+' UpdateSession');
      [*] = ;   _inet_UpdateClientsList(elmclientname,0);
      [*] = ;   _inet_UpdateShardGamesList(cShellShardGamesList);
      [*] = ;
      [*] = ;   //if (gGame.gameType=gc_GameTypeLanShard) then
      [*] = ;   //begin
      [*] = ;   //   if (GetLanMode()=1) then
      [*] = ;   //   begin
      [*] = ;   //      var pSession : Integer = _misc_ParserGetOrCreateByKey('session_info', True);
      [*] = ;   //      LanPublicServerGetSessionInfoToParserByClientID(LanMyInfoID(), pSession);
      [*] = ;   //      if (pSession<>0) then
      [*] = ;   //      begin
      [*] = ;   //         var mapname : String = ParserGetValueByKeyByHandle(pSession, 'MapName');
      [*] = ;   //         if (mapname<>'') then
      [*] = ;   //         begin
      [*] = ;   //            if _log then _Log_lan(_log_name+' UpdateSession : ShowNewGame idfrom='+IntToStr(idfrom));
      [*] = ;   //            if (not _inet_IsSaveGameMapName(mapname)) then
      [*] = ;   //               _inet_GetInetShardMapParamsByMapNameToMapSettings(mapname);
      [*] = ;   //            UpdateLanShardGame();
      [*] = ;   //         end;
      [*] = ;   //      end;
      [*] = ;   //   end
      [*] = ;   //   else
      [*] = ;   //   begin
      [*] = ;   //      if (GetLanMode()>=2) then
      [*] = ;   //         UpdateLanShardGame();
      [*] = ;   //   end;
      [*] = ;   //end;
      [*] = ;end;
      [*] = ;
      [*] = ;//------------------------------------------------------------------------------
      [*] = ;procedure JoinSession(elmroomname, elmclientname : String); // this comes before OnConnect
      [*] = ;begin
      [*] = ;   var idfrom : Integer = LanPublicServerGetRegIDFrom();
      [*] = ;   var idto : Integer = LanPublicServerGetRegIDTo();
      [*] = ;
      [*] = ;   _inet_UpdateClientsList(elmclientname,0);
      [*] = ;   _inet_UpdateShardGamesList(cShellShardGamesList);
      [*] = ;
      [*] = ;   if _log then _Log_lan(_log_name+' JoinSession : GetLanMode = '+IntToStr(GetLanMode)+' idfrom = '+IntToStr(idfrom)+' idto = '+IntToStr(idto));
      [*] = ;   if (GetLanMode()>1) and (idto=LanMyInfoID()) then //someone attempts to join your room
      [*] = ;   begin
      [*] = ;      if _log then _Log_lan(_log_name+' JoinSession : (idto=LanMyInfoID)');
      [*] = ;      _gui_PlaySound('interface','end_turn');
      [*] = ;      //if (gGame.gameType=gc_GameTypeLanShard) then
      [*] = ;      //   UpdateLanShardGame();
      [*] = ;   end;
      [*] = ;
      [*] = ;   //if (idfrom=LanMyInfoID()) and (GetLanMode()=1) then //you join a room as a client
      [*] = ;   //begin
      [*] = ;   //   var pSession : Integer = _misc_ParserGetOrCreateByKey('session_info', True);
      [*] = ;   //   var mapname : String;
      [*] = ;      
      [*] = ;   //   LanPublicServerGetSessionInfoToParserByClientID(LanMyInfoID(), pSession);
      [*] = ;   //   mapname := ParserGetValueByKeyByHandle(pSession, 'MapName');
      [*] = ;   //   if (mapname <> '') and (not _inet_IsSaveGameMapName(mapname)) then
      [*] = ;   //      _inet_GetInetShardMapParamsByMapNameToMapSettings(mapname);
      [*] = ;   //end;
      [*] = ;end;
      [*] = ;
      [*] = ;//------------------------------------------------------------------------------
      [*] = ;procedure LeaveSession(elmRoomName, elmClientName : String); // if game is terminated, this comes after
      [*] = ;begin
      [*] = ;   var idFrom : Integer = LanPublicServerGetRegIDFrom();
      [*] = ;   var idto : Integer = LanPublicServerGetRegIDTo();
      [*] = ;   
      [*] = ;   function IsMySessionByClientID(const clientID : Integer) : Boolean;
      [*] = ;   begin
      [*] = ;      Result := False;
      [*] = ;         
      [*] = ;      var i : Integer;
      [*] = ;      for i := 0 to gc_MaxCustomMapPlayer-1 do
      [*] = ;      if gLanShardGame.arrlanplayers[i].lanid = clientID then
      [*] = ;      begin
      [*] = ;         Result := True;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if _log then _Log_lan(_log_name+' LeaveSession, ID: '+(IntToStr(idFrom)));
      [*] = ;   if (idFrom=LanMyInfoID()) then // you leave
      [*] = ;   begin
      [*] = ;      _inet_ClearLanShardGame();
      [*] = ;      _gui_RootWindowRemoveWithFade(_gui_GetWindow('NewGame'),gc_gui_FadeTime0_2);
      [*] = ;      _gui_RootWindowRemoveWithFade(_gui_GetWindow('MapGeneratorSettings'),gc_gui_FadeTime0_2);
      [*] = ;      _gui_RootWindowRemoveWithFade(_gui_GetWindow('Gameplay Settings'),gc_gui_FadeTime0_2);
      [*] = ;      _gui_RootWindowRemoveWithFade(_gui_GetWindow('Genesis Mode'),gc_gui_FadeTime0_2);
      [*] = ;      _gui_RootWindowRemoveWithFade(_gui_GetWindow(cLanLoadGameSyncName),gc_gui_FadeTime0_2);
      [*] = ;      GUIExecuteState('ShowInternetShell');
      [*] = ;   end
      [*] = ;   else // someone else leaves a shard game I'm involved in
      [*] = ;   if IsMySessionByClientID(idFrom) then
      [*] = ;   begin
      [*] = ;      if (gLanShardGame.masterid = LanMyInfoID) then // client leaves, you are the master
      [*] = ;      begin
      [*] = ;         var elmHnd : Integer = _gui_GetWindow('NewGame');
      [*] = ;
      [*] = ;         if elmHnd = 0 then
      [*] = ;            elmHnd := _gui_GetWindow(cLanLoadGameSyncName);
      [*] = ;
      [*] = ;         if (elmHnd<>0) then
      [*] = ;            UpdateLanShardGame();
      [*] = ;      end
      [*] = ;      else  // master leaves, you are a client
      [*] = ;      begin
      [*] = ;         _inet_ClearLanShardGame();
      [*] = ;         _gui_RootWindowRemoveWithFade(_gui_GetWindow('NewGame'),gc_gui_FadeTime0_2);
      [*] = ;         _gui_RootWindowRemoveWithFade(_gui_GetWindow('MapGeneratorSettings'),gc_gui_FadeTime0_2);
      [*] = ;         _gui_RootWindowRemoveWithFade(_gui_GetWindow('Gameplay Settings'),gc_gui_FadeTime0_2);
      [*] = ;         _gui_RootWindowRemoveWithFade(_gui_GetWindow('Genesis Mode'),gc_gui_FadeTime0_2);
      [*] = ;         _gui_RootWindowRemoveWithFade(_gui_GetWindow(cLanLoadGameSyncName),gc_gui_FadeTime0_2);
      [*] = ;         _gui_PlaySound('interface','end_turn');
      [*] = ;         GUIExecuteState('ShowInternetShell');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   _inet_UpdateClientsList(elmClientName,0);
      [*] = ;   _inet_UpdateShardGamesList(elmRoomName);
      [*] = ;end;
      [*] = ;
      [*] = ;//------------------------------------------------------------------------------
      [*] = ;procedure LockSession(elmRoomName, elmClientName : String);
      [*] = ;begin
      [*] = ;   var idFrom : Integer = LanPublicServerGetRegIDFrom();
      [*] = ;
      [*] = ;   if _log then _Log_lan(_log_name+' LockSession');
      [*] = ;   _inet_UpdateClientsList(elmclientname,0);
      [*] = ;   _inet_UpdateShardGamesList(cShellShardGamesList);
      [*] = ;
      [*] = ;   if (gIntRegister_InetSelectedPlayerID=idFrom) then
      [*] = ;      gIntRegister_InetSelectedPlayerID := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;//------------------------------------------------------------------------------
      [*] = ;procedure ConnectClient(elmRoomName, elmClientName : String);
      [*] = ;begin
      [*] = ;   if _log then _Log_lan(_log_name+' ConnectClient');
      [*] = ;   _inet_UpdateClientsList(elmClientName,0);
      [*] = ;   _inet_RefreshLoadGameProgress(0);
      [*] = ;end;
      [*] = ;
      [*] = ;//------------------------------------------------------------------------------
      [*] = ;procedure DisconnectClient(elmClientName : String);
      [*] = ;begin
      [*] = ;   var idFrom : Integer = LanPublicServerGetRegIDFrom();
      [*] = ;
      [*] = ;   if _log then _Log_lan(_log_name+' DisconnectClient');
      [*] = ;   _inet_UpdateClientsList(elmClientName,idFrom);
      [*] = ;   _inet_RefreshLoadGameProgress(idFrom);
      [*] = ;end;
      [*] = ;
      [*] = ;//------------------------------------------------------------------------------
      [*] = ;procedure TopUsersUpdate(elmladdername : String);
      [*] = ;begin
      [*] = ;   var elmhandle : Integer = _gui_GetWindow(elmladdername);
      [*] = ;   if (elmHandle<>0) then
      [*] = ;   begin
      [*] = ;      GUIListBoxClearSilent(elmhandle);
      [*] = ;
      [*] = ;      var i : Integer;
      [*] = ;      var pLan : Integer = LanSelectParser;
      [*] = ;      for i:=0 to ParserGetCountByHandle(pLan)-1 do
      [*] = ;      begin
      [*] = ;         var pitem : Integer = ParserSelectByHandleByIndex(pLan, i);
      [*] = ;         var sline : String = IntToStr(i+1) + #9;
      [*] = ;         sline := sline + ParserGetValueByKeyByHandle(pitem, 'nick') + #9;
      [*] = ;         sline := sline + ParserGetValueByKeyByHandle(pitem, 'country') + #9;
      [*] = ;         //sline := sline + IntToStr(GetRankIndex(ParserGetIntValueByKeyByHandle(pitem, 'score'))) + #9;
      [*] = ;         sline := sline + ParserGetValueByKeyByHandle(pitem, 'score') + #9;
      [*] = ;         sline := sline + ParserGetValueByKeyByHandle(pitem, 'games') + #9;
      [*] = ;         sline := sline + ParserGetValueByKeyByHandle(pitem, 'wins') + #9;
      [*] = ;
      [*] = ;         if ParserGetIntValueByKeyByHandle(pitem, 'games')>0 then
      [*] = ;            sline := sline + IntToStr(Round(100*ParserGetIntValueByKeyByHandle(pitem, 'wins')/ParserGetIntValueByKeyByHandle(pitem, 'games'))) + '%' + #9
      [*] = ;         else
      [*] = ;            sline := sline + '0%'+ #9;
      [*] = ;
      [*] = ;         GUIListBoxAddItem(elmhandle, sline, 0);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;//------------------------------------------------------------------------------
      [*] = ;procedure UpdateClientInfo(elmClientName, elmprofilename : String);
      [*] = ;begin
      [*] = ;   if _log then _Log_lan(_log_name+' UpdateClient');
      [*] = ;   
      [*] = ;   var exclude_id : Integer = 0;//LanMyInfoID();
      [*] = ;   if (gGame.gameType = gc_GameTypeLanShard) or (gGame.gameType = gc_GameTypeLanBattle) then
      [*] = ;   begin
      [*] = ;      _inet_UpdateShardGamesList(cShellShardGamesList);
      [*] = ;      if GetLanMode = 0 then
      [*] = ;         exclude_id := 0;
      [*] = ;   end;
      [*] = ;   _inet_UpdateClientsList(elmClientName,exclude_id);
      [*] = ;
      [*] = ;   {if gShellViewProfID=LanPublicServerGetRegIDFrom() then
      [*] = ;   begin
      [*] = ;      gShellViewProfID := 0;
      [*] = ;      var pClient : Integer = _misc_ParserGetOrCreateByKey('client_info', True);
      [*] = ;      if LanPublicServerGetClientInfoToParserByClientID(LanPublicServerGetRegIDFrom(), pclient) then
      [*] = ;      begin
      [*] = ;         if _log then _Log_lan('UpdateClientInfo : SwitchToInetShell(ShellPageIndex = 2)');
      [*] = ;         ParserSelectByHandle(pclient);
      [*] = ;         var profHandle : Integer = _gui_GetWindow(elmprofilename);
      [*] = ;         // Update edit button
      [*] = ;         var elmHandle : Integer = GetGUIElementIndexByNameParent('btnedit', profHandle);
      [*] = ;         SetGUIElementEnabled(elmHandle, LanPublicServerGetRegIDFrom() = LanMyInfoID());
      [*] = ;         // Update nick name
      [*] = ;         elmHandle := GetGUIElementIndexByNameParent('right.name', profHandle);
      [*] = ;         SetGUIElementText(elmHandle,  ParserGetValueByKeyByHandle(pclient, 'nick'));
      [*] = ;         // Update rank
      [*] = ;         //elmHandle := GetGUIElementIndexByNameParent('right.rank', profHandle);
      [*] = ;         //SetGUIElementText(elmHandle, IntToStr(GetRankIndex(ParserGetIntValueByKeyByHandle(pclient, 'score'))));
      [*] = ;         // Update score
      [*] = ;         elmHandle := GetGUIElementIndexByNameParent('right.score', profHandle);
      [*] = ;         SetGUIElementText(elmHandle,  IntToStr(ParserGetIntValueByKeyByHandle(pclient, 'score')));
      [*] = ;         // Update my country
      [*] = ;         elmHandle := GetGUIElementIndexByNameParent('right.country', profHandle);
      [*] = ;         SetGUIElementText(elmHandle,  ParserGetValueByKeyByHandle(pclient, 'country'));
      [*] = ;         // Update played games count
      [*] = ;         elmHandle := GetGUIElementIndexByNameParent('right.games', profHandle);
      [*] = ;         SetGUIElementText(elmHandle,  IntToStr(ParserGetIntValueByKeyByHandle(pclient, 'gamesplayed')));
      [*] = ;         // Update wins count
      [*] = ;         elmHandle := GetGUIElementIndexByNameParent('right.win', profHandle);
      [*] = ;         SetGUIElementText(elmHandle,  IntToStr(ParserGetIntValueByKeyByHandle(pclient, 'gameswin')));
      [*] = ;         // Update percent of success
      [*] = ;         elmHandle := GetGUIElementIndexByNameParent('right.winpercent', profHandle);
      [*] = ;         if ParserGetIntValueByKeyByHandle(pclient, 'gamesplayed') > 0 then
      [*] = ;            SetGUIElementText(elmHandle, IntToStr(Round(100 * ParserGetIntValueByKeyByHandle(pclient, 'gameswin') / ParserGetIntValueByKeyByHandle(pclient, 'gamesplayed'))) + '%')
      [*] = ;         else
      [*] = ;            SetGUIElementText(elmHandle, '0%');
      [*] = ;         // Update last played game time
      [*] = ;         elmHandle := GetGUIElementIndexByNameParent('right.lasttime', profHandle);
      [*] = ;         SetGUIElementText(elmHandle, ParserGetValueByKeyByHandle(pclient, 'lastgame'));
      [*] = ;         // Update personal info
      [*] = ;         elmHandle := GetGUIElementIndexByNameParent('right.info', profHandle);
      [*] = ;         SetGUIElementText(elmHandle, ParserGetValueByKeyByHandle(pclient, 'info'));
      [*] = ;      end;
      [*] = ;   end;}
      [*] = ;end;
      [*] = ;
      [*] = ;//------------------------------------------------------------------------------
      [*] = ;function ErrorOccur() : Boolean;
      [*] = ;begin
      [*] = ;   Result := true;
      [*] = ;   if gConnectIPIndex>=0 then
      [*] = ;   begin
      [*] = ;      gConnectIPIndex := gConnectIPIndex + 1;
      [*] = ;      GUIExecuteState('DoLanConnect');
      [*] = ;      if gConnectIPIndex>=0 then
      [*] = ;      begin
      [*] = ;         Result := false;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if Result then
      [*] = ;   begin
      [*] = ;      _lan_timer_Reset(gc_lt_ALL,false,'MENU.INC\LANEVENTDEFAULT');
      [*] = ;
      [*] = ;      case gLanEvent of
      [*] = ;         leShellCoreVersionFailed :
      [*] = ;         begin
      [*] = ;            _gui_ShowQuestionDialog('menu|leShellCoreVersionFailed', 'EvLanConnect', 20, 'EvLanConnect', 10, False, False) //LAN.SHELL.UPDATE.NEEDED
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            _gui_ShowQuestionDialog('menu|leError', '', 0, 'EvLanConnect', 10, False, True) //LAN.SHELL.SERVER.CONNECTION.ERROR
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if _log then _Log_lan(_log_name+' ErrorOccur : OnLanEvent');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;//------------------------------------------------------------------------------
      [*] = ;procedure LoginError();
      [*] = ;begin
      [*] = ;   _lan_timer_Reset(gc_lt_ALL,false,'MENU.INC\LANEVENTDEFAULT');
      [*] = ;   var action : String = '';
      [*] = ;   if ((GetLanMode = 0) and ((gGame.gameType = gc_GameTypeLanShard) or (gGame.gameType = gc_GameTypeLanBattle))) then
      [*] = ;      action := '#menuaction|multiplayer';
      [*] = ;
      [*] = ;   if gLanEvent=leShellAuthBannedFailed then
      [*] = ;      _gui_ShowQuestionDialog('menu|leShellAuthBannedFailed', '', 0, action, 0, False, True) //LAN.SHELL.ACCOUNT.BANNED
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if gLanEvent=leShellAuthClientFailed then
      [*] = ;         _gui_ShowQuestionDialog('menu|137', '', 0, action, 0, False, True) //LAN.SHELL.INVALID.PASSWORD
      [*] = ;      else
      [*] = ;      //if gLanEvent=leShellAuthCDKeyFailed then
      [*] = ;         _gui_ShowQuestionDialog('menu|135', '', 0, action, 0, False, True); //LAN.SHELL.INVALID.SERIAL
      [*] = ;   end;
      [*] = ;
      [*] = ;   if _log then _Log_lan(_log_name+' LoginError : ToolQuestionDialog');
      [*] = ;end;
      [*] = ;
      [*] = ;//------------------------------------------------------------------------------
      [*] = ;procedure RegError();
      [*] = ;begin
      [*] = ;   _lan_timer_Reset(gc_lt_ALL,false,'MENU.INC\LANEVENTDEFAULT');
      [*] = ;   var action : String = '';
      [*] = ;   if ((GetLanMode = 0) and ((gGame.gameType = gc_GameTypeLanShard) or (gGame.gameType = gc_GameTypeLanBattle))) then
      [*] = ;      action := '#menuaction|multiplayer';
      [*] = ;
      [*] = ;   if gLanEvent=leShellRegClientFailed then
      [*] = ;      _gui_ShowQuestionDialog('menu|leShellRegClientFailed', '', 0, action, 0, False, True) //LAN.SHELL.EMAIL.USED
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if gLanEvent=leShellRegDataFailed then
      [*] = ;         _gui_ShowQuestionDialog('menu|leShellRegDataFailed', '', 0, action, 0, False, True) //LAN.SHELL.INVALID.REG.DATA
      [*] = ;      else
      [*] = ;         //if gLanEvent = leShellRegCDKeyFailed then
      [*] = ;         _gui_ShowQuestionDialog('menu|leShellRegCDKeyFailed', '', 0, action, 0, False, True);
      [*] = ;   end;
      [*] = ;
      [*] = ;   if _log then _Log_lan(_log_name+' RegError : '+IntToStr(gLanEvent));
      [*] = ;end;
      [*] = ;
      [*] = ;procedure DataVersionFailed();
      [*] = ;begin
      [*] = ;   _lan_timer_Reset(gc_lt_ALL,false,'MENU.INC\LANEVENTDEFAULT');
      [*] = ;   if IsFileExists('update.exe') then
      [*] = ;      _gui_ShowQuestionDialog('menu|leShellDataVersionFailed', 'EvLanConnect', 20, 'EvLanConnect', 10, False, False)
      [*] = ;   else
      [*] = ;      _gui_ShowQuestionDialog('menu|leShellDataVersionFailedNoUpdater', 'EvLanConnect', 20, 'EvLanConnect', 10, False, False);
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;if IsLanPublicServerMode() and (gInetEventLock <> 1) then
      [*] = ;begin
      [*] = ;   if _log then DumpLanEvent();
      [*] = ;
      [*] = ;   case gLanEvent of
      [*] = ;      leTerminated : OnTerminateGame();
      [*] = ;      leError,
      [*] = ;      leShellCoreVersionFailed : ErrorOccur();
      [*] = ;      leShellDataVersionFailed : DataVersionFailed();
      [*] = ;      leShellGetAuth : begin
      [*] = ;         _lan_timer_Reset(gc_lt_connect,false,'MENU.INC\LANEVENTDEFAULT');
      [*] = ;         if ((GetLanMode = 0) and ((gGame.gameType = gc_GameTypeLanShard) or (gGame.gameType = gc_GameTypeLanBattle))) then
      [*] = ;            _misc_FadeMenu('main_menu',1);
      [*] = ;         _lan_timer_Arm(gc_lt_server_answer,gc_gui_FadeTime0_4,false);
      [*] = ;         LanSetMyEmail(gProfile.netemail);
      [*] = ;         LanPublicServerUserExist(gProfile.netemail);
      [*] = ;      end;
      [*] = ;      leShellValidEmail : begin
      [*] = ;         _lan_timer_Reset(gc_lt_server_answer,false,'MENU.INC\LANEVENTDEFAULT');
      [*] = ;         gInetProfile.netemail := gProfile.netemail;
      [*] = ;         gInetProfile.netpass := gProfile.netkey;
      [*] = ;         gInetProfile.netkey := gProfile.netkey;
      [*] = ;         if gBoolRegister_UseNameAsNick then
      [*] = ;            gInetProfile.name := gProfile.name
      [*] = ;         else
      [*] = ;            gInetProfile.name := gProfile.nick;
      [*] = ;
      [*] = ;         _lan_timer_Arm(gc_lt_auth,gc_gui_FadeTime0_4,false);
      [*] = ;         LanSetMyPassword(gInetProfile.netpass);
      [*] = ;         LanSetMyCDKey(gInetProfile.netkey);
      [*] = ;         _inet_UpdateNetworkProfileInfo(false,true);
      [*] = ;         LanSetMyNick(gInetProfile.name);
      [*] = ;         LanSetMyCountry('');
      [*] = ;         LanPublicServerLogin();
      [*] = ;      end;
      [*] = ;      leShellInvalidEmail : begin
      [*] = ;         var s : String;
      [*] = ;
      [*] = ;         LanShutDown();
      [*] = ;         if gGame.gameType = gc_GameTypeLanShard then
      [*] = ;            s := 'menuaction|lanshard'
      [*] = ;         else
      [*] = ;            s := 'menuaction|lanbattle';
      [*] = ;         _cmd_Post('menuaction','lanprofile',s);
      [*] = ;      end;
      [*] = ;      leShellLogged : begin
      [*] = ;         _inet_UpdateNetworkProfileInfo(false,true);
      [*] = ;         LanSetMyNick(gInetProfile.name);
      [*] = ;         LanPublicServerRegister();
      [*] = ;         LanPublicServerUpdateClientInfo(LanMyInfoID());
      [*] = ;      end;
      [*] = ;      //
      [*] = ;      leShellAuthClientFailed,
      [*] = ;      leShellAuthBannedFailed,
      [*] = ;      leShellAuthCDKeyFailed : LoginError();
      [*] = ;      //
      [*] = ;      leShellRegClientFailed,
      [*] = ;      leShellRegCDKeyFailed,
      [*] = ;      leShellRegDataFailed  : RegError();
      [*] = ;      //
      [*] = ;      leShellMessage        : _inet_AddChatMessage(False, cShellChatList);
      [*] = ;      leShellSessionMessage : _inet_AddChatMessage(True, cShellChatList);
      [*] = ;      //
      [*] = ;      leShellSessionCreate : CreateSession(cShellShardGamesList);
      [*] = ;      leShellSessionJoin   : JoinSession(cShellShardGamesList, cShellClientsList);
      [*] = ;      leShellSessionLeave  : LeaveSession(cShellShardGamesList, cShellClientsList);
      [*] = ;      leShellSessionInfo   : UpdateSession(cShellShardGamesList, cShellClientsList);
      [*] = ;      leShellSessionLock   : LockSession(cShellShardGamesList, cShellClientsList);
      [*] = ;      //
      [*] = ;      leShellClientConnected : begin
      [*] = ;         var idFrom : Integer = LanPublicServerGetRegIDFrom();
      [*] = ;         var myInfoID : Integer = LanMyInfoID();
      [*] = ;         var exclude_id : Integer = 0;//myInfoID;
      [*] = ;         if (idFrom=myInfoID) then
      [*] = ;         begin
      [*] = ;            _lan_timer_Reset(gc_lt_ALL,false,'MENU.INC\LANEVENTDEFAULT [leShellClientConnected]');
      [*] = ;
      [*] = ;            gStringRegister_LogLanParserPfx := DateTimeNow('YYMMDD')+'\'+DateTimeNow('HHNN');
      [*] = ;
      [*] = ;            gInetProfile.id := myInfoID;
      [*] = ;            gInetProfile.name := LanMyInfoName();
      [*] = ;            gInetProfile.wins := LanPublicServerProfGamesWin();
      [*] = ;            
      [*] = ;            _inet_UpdateNetworkProfileInfo(false,true);
      [*] = ;            LanPublicServerRegister();
      [*] = ;            LanPublicServerUpdateClientInfo(myInfoID);
      [*] = ;            gIntRegister_MyLanID := myInfoID;
      [*] = ;            
      [*] = ;            // because we are now in menu, send shut down order in case someone remained in a game where I am no longer in.
      [*] = ;            var p : Integer = _misc_ParserGetOrCreateByKey('lan_controlgamemodechange',true);
      [*] = ;            ParserSetIntValueByKeyByHandle(p, 'ExitMode', gc_gui_ModeSwitchToLanMenu);
      [*] = ;            LanSendParser(gc_LAN_SHUTDOWN_GAME, p);
      [*] = ;            
      [*] = ;            // Update GUI
      [*] = ;            if ((GetLanMode = 0) and ((gGame.gameType = gc_GameTypeLanShard) or (gGame.gameType = gc_GameTypeLanBattle))) then
      [*] = ;            begin
      [*] = ;               _gui_FadeWindow_VVK(_gui_GetWindow('internetshell'), 0, 1);// astral chat must be removed before entering lobby or everything will disappear when creating a room
      [*] = ;               exclude_id := 0;
      [*] = ;               
      [*] = ;               GUIExecuteState('ShowInternetShell');
      [*] = ;               if gGame.gameType <> gc_GameTypeLanShard then
      [*] = ;                  _gui_ShowQuestionDialog('menu|multiplayer_version_reminder', '',0,'', 0,false,true)
      [*] = ;               else
      [*] = ;                  _gui_ShowQuestionDialog('gui|network_disclaimer2', '',0,'', 0,false,true);
      [*] = ;
      [*] = ;               _inet_UpdateShardGamesList(cShellShardGamesList);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if _inet_AstralChatModal then
      [*] = ;               IntRegister0 := 2
      [*] = ;               else
      [*] = ;               IntRegister0 := 0;
      [*] = ;               GUIExecuteState('ShowAstralChat');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         // ConnectClient(cShellShardGamesList,cShellClientsList);
      [*] = ;         if _log then _Log_lan(_log_name+' ConnectClient');
      [*] = ;         _inet_UpdateClientsList(cShellClientsList, exclude_id);
      [*] = ;         if ((GetLanMode = 0) and ((gGame.gameType = gc_GameTypeLanShard) or (gGame.gameType = gc_GameTypeLanBattle))) or (idFrom <> myInfoID) then
      [*] = ;            _inet_RefreshLoadGameProgress(0);
      [*] = ;      end;
      [*] = ;      leShellClientDisconnected : DisconnectClient(cShellClientsList);
      [*] = ;      leShellClientInfo, leShellClientUpdateInfo : UpdateClientInfo(cShellClientsList, cShellProfile);
      [*] = ;      //
      [*] = ;      // NOTE: recursive in connection cycle : - leShutdown          : ExecuteState('SwitchToMenu');
      [*] = ;      //
      [*] = ;      leConnect : OnConnect();
      [*] = ;      leParser : ParserReceived();
      [*] = ;      leServerInfo : ServerInfoUpdate();
      [*] = ;      leShellUpdateTopList : TopUsersUpdate(cShellLadderList);
      [*] = ;      //
      [*] = ;      leShutdown : begin
      [*] = ;         if _log then _Log_lan(_log_name+' leShutdown');
      [*] = ;         
      [*] = ;         if (LanPublicServerGetRegIDFrom = LanMyInfoID) then
      [*] = ;         begin
      [*] = ;            _lan_timer_Reset(gc_lt_ALL,true,'MENU.INC\LANEVENTDEFAULT [leShutdown]');
      [*] = ;            
      [*] = ;            _gui_RootWindowRemoveWithFade(_gui_GetWindow('internetshell'),gc_gui_FadeTime0_2);
      [*] = ;            IntRegister0 := 1;
      [*] = ;            GUIExecuteState('ShowAstralChat');
      [*] = ;      
      [*] = ;            var chatBlink : Boolean;
      [*] = ;            _gui_RemoveBlinkElement('btnOpenChatBlink', chatBlink);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      else begin
      [*] = ;         if _log then _Log_lan(_log_name+' unhandled lan event=' + IntToStr(gLanEvent));
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

