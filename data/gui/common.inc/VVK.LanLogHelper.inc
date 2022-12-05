section.begin
   Name = VVK.LanLogHelper
   Description : struct.begin
      [*] = ;IntRegister0 - mode
      [*] = ;   0 - Is lan event loggable by id
      [*] = ;      IntRegister1 - log mode flags (gIntRegister_LogLanParsers)
      [*] = ;      IntRegister2 - parser id
      [*] = ;      RET: BoolRegister0 - true if loggable
      [*] = ;   1 - log sent parser
      [*] = ;      IntRegister1 - log mode flags (gIntRegister_LogLanParsers)
      [*] = ;      IntRegister2 - parser id
      [*] = ;      IntRegister3 - parser handle
      [*] = ;      StringRegister0 - description string
      [*] = ;   2 - log received parser
      [*] = ;      IntRegister1 - log mode flags (gIntRegister_LogLanParsers)
      [*] = ;      IntRegister2 - parser id
      [*] = ;      IntRegister3 - parser handle
      [*] = ;      IntRegister4 - ID of client from which parser received
      [*] = ;      StringRegister0 - description string
      [*] = ;   3 - start parser transfer
      [*] = ;      IntRegister1 - parser id
      [*] = ;      IntRegister2 - parser handle
      [*] = ;      RET: BoolRegister0 - true if modal window was displayed
      [*] = ;   4 - finish parser transfer
      [*] = ;   5 - get text name of lan event from gLanEvent variable
      [*] = ;      IntRegister1 - event id
      [*] = ;      RET: StringRegister0 - text name of event
      [*] = ;   6 - get text name of parser
      [*] = ;      IntRegister1 - parser id
      [*] = ;      RET: StringRegister0 - text name of event
   struct.end
   Code : struct.begin
      [*] = ;
      [*] = ;procedure GetLogPrefix(var pfx : String);
      [*] = ;begin
      [*] = ;   var ts : String;
      [*] = ;   var l : Integer;
      [*] = ;
      [*] = ;   ts := IntToStr(gIntRegister_LogLanParserUID);
      [*] = ;   gIntRegister_LogLanParserUID := gIntRegister_LogLanParserUID + 1;
      [*] = ;   l := StrLength(ts);
      [*] = ;   if l < 3 then ts := SubStr('000000000000',1,3-l)+ts;
      [*] = ;   pfx := gStringRegister_LogLanParserPfx+'_'+ts+'_';
      [*] = ;end;
      [*] = ;
      [*] = ;procedure LogGetNameFromParserID(id : Integer; var nm : String);
      [*] = ;begin
      [*] = ;   case id of
      [*] = ;      0 : nm := 'NOT_VALID_0';
      [*] = ;      gc_LAN_DUMP : nm := 'DUMP';
      [*] = ;      gc_LAN_HERO : nm := 'HERO';
      [*] = ;      gc_LAN_READY : nm := 'READY';
      [*] = ;      gc_LAN_START : nm := 'START';
      [*] = ;      gc_LAN_READYPLACEMENTMODE : nm := 'READY_PLACEMENT';
      [*] = ;      gc_LAN_EXITPLACEMENTMODE : nm := 'EXIT_PLACEMENT';
      [*] = ;      gc_LAN_ACTION : nm := 'ACTION';
      [*] = ;      gc_LAN_CLIENTENDTURN : nm := 'CLIENTENDTURN';
      [*] = ;      gc_LAN_MASTERENDTURN : nm := 'MASTERENDTURN';
      [*] = ;      gc_LAN_CLIENTWIN : nm := 'CLIENTWIN';
      [*] = ;      gc_LAN_MASTERWIN : nm := 'MASTERWIN';
      [*] = ;      gc_LAN_CLIENTSURRENDER : nm := 'CLIENTSURRENDER';
      [*] = ;      gc_LAN_CLIENTPLACEMENT : nm := 'CLIENTPLACEMENT';
      [*] = ;      gc_LAN_CLIENTPLACEMENTREADY : nm := 'CLIENTPLACEMENTREADY';
      [*] = ;      gc_LAN_SHARD_SETTINGS : nm := 'SHARD_SETTINGS';
      [*] = ;      gc_LAN_SHARD_ENDTURN : nm := 'SHARD_ENDTURN';
      [*] = ;      gc_LAN_SHARD_CALCTURN : nm := 'SHARD_CALCTURN';
      [*] = ;      gc_LAN_MESSAGE : nm := 'MESSAGE';
      [*] = ;      gc_LAN_SHARD_ENDCONFLICTS : nm := 'ENDCONFLICTS';
      [*] = ;      gc_LAN_SHARD_SYNCCONFLICTS : nm := 'SYNCCONFLICTS';
      [*] = ;      gc_LAN_SHARD_PLAYERSINFO : nm := 'PLAYERINFO';
      [*] = ;      gc_LAN_SHARD_SHOWQUERY : nm := 'SHOWQUERY';
      [*] = ;      gc_LAN_SHARD_CHOOSERESULT : nm := 'CHOOSEQUERYRESULT';
      [*] = ;      gc_LAN_SHARD_SHOWPROVHEROES : nm := 'SHOWPROVHEROES';
      [*] = ;      gc_LAN_SHARD_CHOOSEHERO : nm := 'CHOOSEPROVHERO';
      [*] = ;      gc_LAN_SHARD_FADETOBATTLE : nm := 'FADETOBATTLE';
      [*] = ;      gc_LAN_SHARD_BATTLELOADED : nm := 'BATTLELOADED';
      [*] = ;      gc_LAN_SHARD_STARTBATTLE : nm := 'STARTBATTLE';
      [*] = ;      gc_LAN_SHARD_CHECKNEWBATTLE : nm := 'CHECKNEWBATTLE';
      [*] = ;      gc_LAN_SHARD_EXITBATTLE : nm := 'EXITBATTLE';
      [*] = ;      gc_LAN_SHARD_BATADDPLAYERS : nm := 'BATADDPLAYERS';
      [*] = ;      gc_LAN_SHARD_SYNCHERO : nm := 'SYNCHERO';
      [*] = ;      gc_LAN_SHARD_PLAYERLOSE : nm := 'PLAYERLOSE';
      [*] = ;      gc_LAN_SHARD_SYNC_READY : nm := 'SYNC_READY';
      [*] = ;      gc_LAN_SHARD_SYNC_RELEASE : nm := 'SYNC_RELEASE';
      [*] = ;      gc_LAN_SHARD_SYNC_REVOKE : nm := 'SYNC_REVOKE';
      [*] = ;      gc_LAN_SHUTDOWN_GAME : nm := 'EXIT_GAME';
      [*] = ;      gc_LAN_SHARD_DUMPCONFLICTS : nm := 'DUMP_CONFLICTS';
      [*] = ;      gc_LAN_RESEND_PARSER_REQUEST : nm := 'RESEND_PARSER_REQUEST';
	  [*] = ;      gc_LAN_SHARD_PROCEEDHERODEATH : nm := 'PROCEEDHERODEATH';
	  [*] = ;      gc_LAN_SHARD_DIPLOMACYMESSAGE : nm := 'DIPLOMACYMESSAGE';
	  [*] = ;      gc_LAN_SHARD_SYNCTREASURY : nm := 'SYNCTREASURY';
      [*] = ;      else nm := 'UNKNOWN_'+IntToStr(id);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function LogIsLoggableByParserID(log_mode, id : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   Result := false;
      [*] = ;   //if log_mode > 0 then
      [*] = ;   begin
      [*] = ;      Result := true;
      [*] = ;      //if log_mode = 1 then
      [*] = ;      begin
      [*] = ;         case id of
      [*] = ;            //gc_LAN_DUMP,
      [*] = ;            gc_LAN_HERO,
      [*] = ;            //gc_LAN_READY,
      [*] = ;            gc_LAN_START,
      [*] = ;            gc_LAN_READYPLACEMENTMODE,
      [*] = ;            gc_LAN_EXITPLACEMENTMODE,
      [*] = ;            gc_LAN_ACTION,
      [*] = ;            gc_LAN_CLIENTENDTURN,
      [*] = ;            gc_LAN_MASTERENDTURN,
      [*] = ;            gc_LAN_CLIENTWIN, // e
      [*] = ;            gc_LAN_MASTERWIN, // e
      [*] = ;            gc_LAN_CLIENTSURRENDER, // e
      [*] = ;            gc_LAN_CLIENTPLACEMENT,
      [*] = ;            gc_LAN_CLIENTPLACEMENTREADY,
      [*] = ;            gc_LAN_SHARD_SETTINGS,
      [*] = ;            gc_LAN_SHARD_ENDTURN,
      [*] = ;            gc_LAN_SHARD_CALCTURN,
      [*] = ;            gc_LAN_MESSAGE,
      [*] = ;            gc_LAN_SHARD_ENDCONFLICTS, // e
      [*] = ;            gc_LAN_SHARD_SYNCCONFLICTS,
      [*] = ;            gc_LAN_SHARD_PLAYERSINFO,
      [*] = ;            gc_LAN_SHARD_SHOWQUERY,
      [*] = ;            gc_LAN_SHARD_CHOOSERESULT,
      [*] = ;            gc_LAN_SHARD_SHOWPROVHEROES,
      [*] = ;            gc_LAN_SHARD_CHOOSEHERO,
      [*] = ;            gc_LAN_SHARD_FADETOBATTLE,
      [*] = ;            gc_LAN_SHARD_BATTLELOADED,
      [*] = ;            gc_LAN_SHARD_STARTBATTLE,
      [*] = ;            gc_LAN_SHARD_CHECKNEWBATTLE,
      [*] = ;            gc_LAN_SHARD_EXITBATTLE,
      [*] = ;            gc_LAN_SHARD_BATADDPLAYERS,
      [*] = ;            gc_LAN_SHARD_SYNCHERO,
      [*] = ;            gc_LAN_SHARD_PLAYERLOSE,
      [*] = ;            //gc_LAN_SHARD_SYNC_READY,
      [*] = ;            gc_LAN_SHARD_SYNC_RELEASE,
      [*] = ;            gc_LAN_SHARD_SYNC_REVOKE,
      [*] = ;            gc_LAN_SHUTDOWN_GAME,
      [*] = ;            gc_LAN_SHARD_DUMPCONFLICTS,
      [*] = ;            gc_LAN_RESEND_PARSER_REQUEST,
	  [*] = ;            gc_LAN_SHARD_PROCEEDHERODEATH,
	  [*] = ;            gc_LAN_SHARD_DIPLOMACYMESSAGE,
	  [*] = ;            gc_LAN_SHARD_SYNCTREASURY :
      [*] = ;               Result := true;
      [*] = ;            else Result := false;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure LogSentParser(mode : String; log_flags,id,pParser : Integer);
      [*] = ;begin
      [*] = ;   if LogIsLoggableByParserID(log_flags,id) then
      [*] = ;   begin
      [*] = ;      var fnm,ts,ids,tm : String;
      [*] = ;      var l : Integer;
      [*] = ;
      [*] = ;      GetLogPrefix(ts);
      [*] = ;      LogGetNameFromParserID(id,ids);
      [*] = ;      tm := mode;
      [*] = ;      l := StrLength(mode);
      [*] = ;      if l < 6 then tm := SubStr('_________',1,6-l)+tm;
      [*] = ;      fnm := ts+'S_'+tm+'_'+ids+'.dat';
      [*] = ;      ParserSaveToFileByHandle(pParser,'.\log\lanevents\'+fnm);
      [*] = ;      Log('ParserSent: '+fnm);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure LogReceivedParser(mode : String; log_flags,id,pParser,from_id : Integer);
      [*] = ;begin
      [*] = ;   if LogIsLoggableByParserID(log_flags,id) then
      [*] = ;   begin
      [*] = ;      var fnm,ts,ids,tm,tp : String;
      [*] = ;      var l : Integer;
      [*] = ;
      [*] = ;      GetLogPrefix(ts);
      [*] = ;      LogGetNameFromParserID(id,ids);
      [*] = ;      tm := mode;
      [*] = ;      l := StrLength(mode);
      [*] = ;      if l < 6 then tm := SubStr('_________',1,6-l)+tm;
      [*] = ;      if LanMyInfoID() = from_id then tp := 'C'
      [*] = ;      else tp := 'R';
      [*] = ;      fnm := ts+tp+'_'+tm+'_'+ids+'.dat';
      [*] = ;      ParserSaveToFileByHandle(pParser,'.\log\lanevents\'+fnm);
      [*] = ;      Log('ParserReceived: '+fnm);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function StartParserTransfer(id,pParser : Integer) : Boolean;
      [*] = ;begin
      [*] = ;   case id of
      [*] = ;      //gc_LAN_DUMP
      [*] = ;      //gc_LAN_HERO,
      [*] = ;      //gc_LAN_READY = 3
      [*] = ;      //gc_LAN_START = 4
      [*] = ;      //gc_LAN_READYPLACEMENTMODE = 5
      [*] = ;      //gc_LAN_EXITPLACEMENTMODE = 6
      [*] = ;      //gc_LAN_ACTION,
      [*] = ;      //gc_LAN_CLIENTENDTURN,
      [*] = ;      //gc_LAN_MASTERENDTURN,
      [*] = ;      //gc_LAN_CLIENTWIN, // e
      [*] = ;      //gc_LAN_MASTERWIN, // e
      [*] = ;      //gc_LAN_CLIENTSURRENDER, // e
      [*] = ;      //gc_LAN_CLIENTPLACEMENT = 15;
      [*] = ;      //gc_LAN_CLIENTPLACEMENTREADY = 16;
      [*] = ;      //gc_LAN_SHARD_SETTINGS,
      [*] = ;      gc_LAN_SHARD_ENDTURN,
      [*] = ;      gc_LAN_SHARD_CALCTURN,
      [*] = ;      //gc_LAN_MESSAGE = 20;
      [*] = ;      //gc_LAN_SHARD_ENDCONFLICTS, // e
      [*] = ;      gc_LAN_SHARD_SYNCCONFLICTS,
      [*] = ;      gc_LAN_SHARD_PLAYERSINFO,
      [*] = ;      //gc_LAN_SHARD_SHOWQUERY,
      [*] = ;      //gc_LAN_SHARD_CHOOSERESULT,
      [*] = ;      gc_LAN_SHARD_SHOWPROVHEROES,
      [*] = ;      //gc_LAN_SHARD_CHOOSEHERO,
      [*] = ;      gc_LAN_SHARD_FADETOBATTLE,
      [*] = ;      //gc_LAN_SHARD_BATTLELOADED,
      [*] = ;      gc_LAN_SHARD_STARTBATTLE,
      [*] = ;      //gc_LAN_SHARD_CHECKNEWBATTLE,
      [*] = ;      gc_LAN_SHARD_EXITBATTLE,
      [*] = ;      gc_LAN_SHARD_BATADDPLAYERS,
      [*] = ;      gc_LAN_SHARD_SYNCHERO :
      [*] = ;      //gc_LAN_SHARD_PLAYERLOSE,
      [*] = ;      //gc_LAN_SHARD_SYNC_READY,
      [*] = ;      //gc_LAN_SHARD_SYNC_RELEASE,
      [*] = ;      //gc_LAN_RESEND_PARSER_REQUEST :
      [*] = ;         Result := true;
      [*] = ;      else Result := false;
      [*] = ;   end;
      [*] = ;   if Result then
      [*] = ;   begin
      [*] = ;      var p : Integer;
      [*] = ;
      [*] = ;      p := _gui_ShowQuestionDialogWithFade('menu|193', '', 0, '', 0, False, True,0,'');
      [*] = ;      SetGUIElementName(p, 'LanSendParser');
      [*] = ;      p := GetGUIElementIndexByNameParent('btnCancelFrame', p);
      [*] = ;      if (p<>0) then
      [*] = ;         RemoveGUIElement(p);
      [*] = ;      ViewerBufferRender();
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure FinishParserTransfer();
      [*] = ;begin
      [*] = ;   var p : Integer;
      [*] = ;
      [*] = ;   p := _gui_GetWindow('LanSendParser');
      [*] = ;   if p <> 0 then
      [*] = ;      _gui_RootWindowRemoveWithFade(p,0);
      [*] = ;   //_log_values('Lan_Threads',LanGetSendDataThreadCount(),0,0,0,0,0);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure GetLanEventName(id : Integer;var e_name : String);
      [*] = ;begin
      [*] = ;   var nm  : String;
      [*] = ;   case id of
      [*] = ;      leNone                      : nm := 'None';
      [*] = ;      leReady                     : nm := 'Ready';
      [*] = ;      leTerminated                : nm := 'Terminated';
      [*] = ;      leDisconnect                : nm := 'Disconnect';
      [*] = ;      leConnect                   : nm := 'Connect';
      [*] = ;      leError                     : nm := 'Error';
      [*] = ;      leParser                    : nm := 'Parser';
      [*] = ;      leClientInfo                : nm := 'ClientInfo';
      [*] = ;      leServerInfo                : nm := 'ServerInfo';
      [*] = ;      leLocalSrvList              : nm := 'LocalSrvList';
      [*] = ;      leShutdown                  : nm := 'Shutdown';
      [*] = ;      leShellGetAuth              : nm := 'Shell_GetAuth';
      [*] = ;      leShellValidEmail           : nm := 'Shell_ValidEmail';
      [*] = ;      leShellInvalidEmail         : nm := 'Shell_InvalidEmail';
      [*] = ;      leShellLogged               : nm := 'Shell_Logged';
      [*] = ;      leShellCoreVersionFailed    : nm := 'Shell_Core_VersionFailed';
      [*] = ;      leShellDataVersionFailed    : nm := 'Shell_Data_VersionFailed';
      [*] = ;      leShellAuthClientFailed     : nm := 'Shell_Auth_ClientFailed';
      [*] = ;      leShellAuthBannedFailed     : nm := 'Shell_Auth_BannedFailed';
      [*] = ;      leShellAuthCDKeyFailed      : nm := 'Shell_Auth_CDKeyFailed';
      [*] = ;      leShellRegClientFailed      : nm := 'Shell_Reg_ClientFailed';
      [*] = ;      leShellRegCDKeyFailed       : nm := 'Shell_Reg_CDKeyFailed';
      [*] = ;      leShellRegDataFailed        : nm := 'Shell_Reg_DataFailed';
      [*] = ;      leShellMessage              : nm := 'Shell_Message';
      [*] = ;      leShellSessionMessage       : nm := 'Shell_Session_Message';
      [*] = ;      leShellSessionCreate        : nm := 'Shell_Session_Create';
      [*] = ;      leShellSessionJoin          : nm := 'Shell_Session_Join';
      [*] = ;      leShellSessionLeave         : nm := 'Shell_Session_Leave';
      [*] = ;      leShellSessionLock          : nm := 'Shell_Session_Lock';
      [*] = ;      leShellSessionClose         : nm := 'Shell_Session_Close';
      [*] = ;      leShellSessionKick          : nm := 'Shell_Session_Kick';
      [*] = ;      leShellSessionInfo          : nm := 'Shell_Session_Info';
      [*] = ;      leShellClientInfo           : nm := 'Shell_Client_Info';
      [*] = ;      leShellClientConnected      : nm := 'Shell_Client_Connected';
      [*] = ;      leShellClientDisconnected   : nm := 'Shell_Client_Disconnected';
      [*] = ;      leShellClientUpdateInfo     : nm := 'Shell_Client_UpdateInfo';
      [*] = ;      leShellUpdateTopList        : nm := 'Shell_Update_TopList';
      [*] = ;      leSessionParser             : nm := 'Session_Parser';
      [*] = ;      else nm := 'Unknown['+IntToStr(id)+']';
      [*] = ;   end;
      [*] = ;
      [*] = ;   e_name := nm;
      [*] = ;end;
      [*] = ;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;
      [*] = ;case mode of
      [*] = ;   0 : BoolRegister0 := LogIsLoggableByParserID( IntRegister1, IntRegister2);
      [*] = ;   1 : LogSentParser( StringRegister0, IntRegister1, IntRegister2, IntRegister3);
      [*] = ;   2 : LogReceivedParser( StringRegister0, IntRegister1, IntRegister2, IntRegister3, IntRegister4);
      [*] = ;   3 : BoolRegister0 := StartParserTransfer( IntRegister1, IntRegister2);
      [*] = ;   4 : FinishParserTransfer();
      [*] = ;   5 : begin
      [*] = ;      var s : String;
      [*] = ;      GetLanEventName( IntRegister1, s);
      [*] = ;      StringRegister0 := s;
      [*] = ;   end;
      [*] = ;   6 : begin
      [*] = ;      var s : String;
      [*] = ;      LogGetNameFromParserID( IntRegister1, s);
      [*] = ;      StringRegister0 := s;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

