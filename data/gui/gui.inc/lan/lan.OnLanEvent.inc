section.begin
   Name = lan.OnLanEvent
   Code : struct.begin
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
      [*] = ;      _lan_GetLanEventName(id,nm);
      [*] = ;      _lan_GetLanParserName(pid,nmp);
      [*] = ;      _log_valuesl('IP|ID|'+nm+'|From|To|'+nmp+'|[Tag]',LanMyInfoIP(),LanMyInfoID(),gLanEvent,LanPublicServerGetRegIDFrom(),LanPublicServerGetRegIDTo(),GetIntValueByName('Tag'));
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;var le : Integer = gLanEvent;
      [*] = ;var bOnlineGame : Boolean = (gGame.gameType = gc_GameTypeLanShard) or (gGame.gameType = gc_GameTypeLanBattle);
      [*] = ;var bTransfer : Boolean = (not bOnlineGame);
      [*] = ;if (not bTransfer) then
      [*] = ;begin
      [*] = ;   case le of
      [*] = ;      leShellCoreVersionFailed,
      [*] = ;      leShellDataVersionFailed,
      [*] = ;      leShellGetAuth,
      [*] = ;      leShellValidEmail,
      [*] = ;      leShellInvalidEmail,
      [*] = ;      leShellLogged,
      [*] = ;      leShellAuthClientFailed,
      [*] = ;      leShellAuthBannedFailed,
      [*] = ;      leShellAuthCDKeyFailed,
      [*] = ;      leShellRegClientFailed,
      [*] = ;      leShellRegCDKeyFailed,
      [*] = ;      leShellRegDataFailed : bTransfer := True;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;if bTransfer then // when in single player mode or when attempting to re-establish connection during online game
      [*] = ;begin
      [*] = ;   if _log then _log_lan('lan.OnLanEvent transfer to LanEventDefault');
      [*] = ;   GUIExecuteState('LanEventDefault');
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;if _log then DumpLanEvent();
      [*] = ;
      [*] = ;var myID : Integer = LanMyInfoID();
      [*] = ;var fromID : Integer = LanPublicServerGetRegIDFrom();
      [*] = ;IntRegister0 := le;
      [*] = ;IntRegister1 := fromID;
      [*] = ;IntRegister2 := LanPublicServerGetRegIDTo();
      [*] = ;IntRegister3 := GetIntValueByName('Tag');
      [*] = ;case le of
      [*] = ;   leSessionParser, leParser :
      [*] = ;   begin
      [*] = ;      var parser : Integer = LanSelectParser();
      [*] = ;      var parserID : Integer = LanGetParserID();
      [*] = ;      
      [*] = ;      if ((gLanEvent=leSessionParser) and (myID = IntRegister2)) or
      [*] = ;         ((gLanEvent=leParser) and _lan_IsPlayerInGame(fromID)) then
      [*] = ;      begin
      [*] = ;         var pPlayerSyncData : Integer = _lan_GetPlayerSyncData(fromID);
      [*] = ;         if (pPlayerSyncData <> 0) then
      [*] = ;         begin
      [*] = ;            if (not gBoolRegister_HaltLanProgress) and _lan_ParserBackupable(parserID, parser) then // during halt we will not update ParsersReceived counter so we can ask for the right number of parsers once the halt is over. ParsersReceived necessitates that there are no gaps.
      [*] = ;            begin
      [*] = ;               var parsersReceived : Integer = ParserGetIntValueByKeyByHandle(pPlayerSyncData, 'ParsersReceived');
      [*] = ;               ParserSetIntValueByKeyByHandle(pPlayerSyncData, 'ParsersReceived', parsersReceived + 1);
      [*] = ;            end;
      [*] = ;        
      [*] = ;            if not ParserGetBoolValueByKeyByHandle(pPlayerSyncData, 'Hold') then
      [*] = ;            begin
      [*] = ;               _lan_ClearPlayerBackupParsers(fromID); // in this function, we will always retain some because the player might have just disconnected and we might have sent something their way during this short timeframe it takes to deliver the parser from their end to mine.
      [*] = ;            end
      [*] = ;            else // we will retain all backups when there's just been a disconnect
      [*] = ;            begin
      [*] = ;               const cHoldTimer = 60;
      [*] = ;               var holdTimer : Float = ParserGetFloatValueByKeyByHandle(pPlayerSyncData, 'HoldTimer');
      [*] = ;               if holdTimer = 0 then // when the player reconnects and sends his first parser
      [*] = ;                  ParserSetFloatValueByKeyByHandle(pPlayerSyncData, 'HoldTimer', GetCurrentTime + cHoldTimer) // safety time-frame so that we should never clear backups without knowing that a player has not disconnected again, and has received all the parsers he missed by the previous disconnect
      [*] = ;               else
      [*] = ;               if GetCurrentTime > holdTimer then
      [*] = ;                  ParserSetBoolValueByKeyByHandle(pPlayerSyncData, 'Hold', False);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         
      [*] = ;         if (not gBoolRegister_HaltLanProgress) or _lan_ParserToProgressHalt(parserID, parser) then // during halt we will only progress parsers to resolve the halt. Once halt is finished, we will ask for all missed parsers again
      [*] = ;         begin
      [*] = ;            IntRegister4 := parserID;
      [*] = ;            IntRegister5 := parser;
      [*] = ;            GUIExecuteState('vvk.lan.PushLanEvent');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   leShellSessionMessage : begin
      [*] = ;      StringRegister0 := LanPublicServerGetRegMessage();
      [*] = ;      GUIExecuteState('vvk.lan.PushLanEvent');
      [*] = ;   end;
      [*] = ;   else GUIExecuteState('vvk.lan.PushLanEvent');
      [*] = ;end;
   struct.end
section.end

