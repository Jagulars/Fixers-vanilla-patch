section.begin
   Name = VVK.LanProfileRegisterCommands
   UsedFileName =
   Description : struct.begin
      [*] = ;IntRegister0 - execution mode (0-execute, 1-return status)
      [*] = ;IntRegister1 - command id
      [*] = ;IntRegister3 - (!) window handle to which this one attached
      [*] = ;StringRegister0 - command name
      [*] = ;StringRegister1 - command parameters (from cfg file)
      [*] = ;StringRegister2 - state parameters (passed in RegisterWindowState)
      [*] = ;StringRegister3 - extra state parameters (passed in PostCommand)
      [*] = ;RETURNS:
      [*] = ;   IntRegister2 - (&0xff: 1 - command available, stop execution, 2 - command unavailable, stop execution, 0 - not supported, continue execution)
      [*] = ;                  high 24 bits are for user defined check availability attributes!
      [*] = ;   StringRegister0 - string array
      [*] = ;      int: element tag
      [*] = ;      int: button extra status (1 - show as checked)
      [*] = ;      str: text resource section and name split by # sign, or empty string if old scheme (menu#(tag&0x7fff)) should be used
   struct.end
   Code : struct.begin
      [*] = ;var _log_name : String = 'MENU.INC\VVK.LANPROFILEREGISTERCOMMANDS';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;procedure UpdateConnectionState(windowHandle,state,lan_state : Integer);
      [*] = ;begin
      [*] = ;   if windowHandle <> 0 then
      [*] = ;   begin
      [*] = ;      var whd : Integer;
      [*] = ;      var status_id : String;
      [*] = ;
      [*] = ;      status_id := '';
      [*] = ;      case (state and $7f) of
      [*] = ;         $7f : begin // some lan error
      [*] = ;            case lan_state of
      [*] = ;               leTerminated : status_id := 'leError';
      [*] = ;               leError : status_id := 'leError';
      [*] = ;               leShellCoreVersionFailed : status_id := 'leShellCoreVersionFailed';
      [*] = ;               leShellDataVersionFailed : status_id := 'leShellDataVersionFailedNoUpdater';
      [*] = ;               leShellRegClientFailed : status_id := 'leShellRegClientFailed';
      [*] = ;               leShellRegCDKeyFailed : status_id := 'leShellRegCDKeyFailed';
      [*] = ;               leShellRegDataFailed : status_id := 'leShellRegDataFailed';
      [*] = ;               leShellAuthClientFailed : status_id := '137';
      [*] = ;               leShellAuthBannedFailed : status_id := 'leShellAuthBannedFailed';
      [*] = ;               leShellAuthCDKeyFailed : status_id := '135';
      [*] = ;               else  status_id := 'leError';
      [*] = ;            end;
      [*] = ;            status_id := GetLocaleTableListItemByID('menu',status_id);
      [*] = ;         end;
      [*] = ;         $7e : begin
      [*] = ;            status_id := 'No server records found!';
      [*] = ;         end;
      [*] = ;         $7d : status_id := 'Disconnecting...';
      [*] = ;         1 : status_id := 'Connecting to public server...';
      [*] = ;         2 : begin
      [*] = ;            status_id := 'Checking account data...';
      [*] = ;         end;
      [*] = ;         3 : begin
      [*] = ;            if ((state and $80) = 0) then
      [*] = ;               status_id := 'Logging into existing account...'
      [*] = ;            else
      [*] = ;               status_id := 'Creating new account...';
      [*] = ;         end;
      [*] = ;         4 : begin
      [*] = ;            if ((state and $80) = 0) then
      [*] = ;               status_id := 'Update succeeded'
      [*] = ;            else
      [*] = ;               status_id := 'Registration succeeded.';
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      whd := _gui_ShowQuestionDialogWithFade(status_id,'',0,'#.menulanevent|cancel|0',0,false,true,$f,cLanRegisterStatusWindowName);
      [*] = ;      if _log then _Log_lan(_log_name+' WHD: '+ IntToStr(whd)+', State: '+ IntToStr(state));
      [*] = ;      if whd <> windowHandle then
      [*] = ;         ErrorLog(_log_name+' status window handles differ.');
      [*] = ;      SetGUIElementTag(whd,state);
      [*] = ;      _cmd_RegisterWindowState(whd,'VVK.LanProfileRegisterCommands','');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure RegistrationSucceeded(windowHandle,state : Integer );
      [*] = ;begin
      [*] = ;   var cmd,c1,c2,c3 : String;
      [*] = ;
      [*] = ;   LanShutdown();
      [*] = ;
      [*] = ;   if _log then _log_values(_log_name+'_STATE',state,0,0,0,0,0);
      [*] = ;
      [*] = ;   UpdateConnectionState(windowHandle,state,0);
      [*] = ;   cmd := GetGUIElementStringTag(windowHandle);
      [*] = ;   if cmd = '' then
      [*] = ;      cmd := 'menuaction|multiplayer';
      [*] = ;   if state = $84 then
      [*] = ;   begin
      [*] = ;      var whd : Integer;
      [*] = ;
      [*] = ;      whd := GetGUIElementIndexByNameParent('btnCancelFrame.btnCancel',windowHandle);
      [*] = ;      if whd <> 0 then
      [*] = ;         SetGUIElementStringTag(whd,'#'+cmd);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      _gui_RootWindowRemoveWithFade(windowHandle,gc_gui_FadeTime0_2);
      [*] = ;
      [*] = ;      _sa_Get(cmd,0,c1);
      [*] = ;      _sa_Get(cmd,1,c2);
      [*] = ;      _sa_Get(cmd,2,c3);
      [*] = ;      _cmd_Post(c1,c2,c3);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ProcessLanEvent( e_id : Integer);
      [*] = ;begin
      [*] = ;   var whd, state : Integer;
      [*] = ;
      [*] = ;   whd := _gui_GetWindow(cLanRegisterStatusWindowName);
      [*] = ;   state := GetGUIElementTag(whd);
      [*] = ;   if state = 0 then // startup
      [*] = ;   begin
      [*] = ;      var port : Integer;
      [*] = ;      var ip : String;
      [*] = ;
      [*] = ;      if _inet_GetConnectionIP(ip,port) then
      [*] = ;      begin
      [*] = ;         if _log then _Log_lan(_log_name+' Connecting to : ' + ip + '['+IntToStr(port)+']');
      [*] = ;
      [*] = ;         state := state + 1;
      [*] = ;         UpdateConnectionState(whd,state,0);
      [*] = ;         LanShutdown();
      [*] = ;         LanPublicServerEnter(ip,port);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         state := $fe;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if IsLanPublicServerMode() and (gInetEventLock <> 1) then
      [*] = ;      begin
      [*] = ;         case e_id of
      [*] = ;            leTerminated, leError, leShellCoreVersionFailed, leShellDataVersionFailed : begin
      [*] = ;               state := $ff;
      [*] = ;               UpdateConnectionState(whd,state,e_id);
      [*] = ;            end;
      [*] = ;            leShellGetAuth : begin
      [*] = ;               state := state + 1;
      [*] = ;               UpdateConnectionState(whd,state,0);
      [*] = ;               LanSetMyEmail(gProfile.netemail);
      [*] = ;               LanPublicServerUserExist(gProfile.netemail);
      [*] = ;            end;
      [*] = ;            leShellValidEmail : begin
      [*] = ;               gInetProfile.netemail := gProfile.netemail;
      [*] = ;               gInetProfile.netpass := gProfile.netkey;
      [*] = ;               gInetProfile.netkey := gProfile.netkey;
      [*] = ;               if gBoolRegister_UseNameAsNick then
      [*] = ;                  gInetProfile.name := gProfile.name
      [*] = ;               else
      [*] = ;                  gInetProfile.name := gProfile.nick;
      [*] = ;
      [*] = ;               state := state + 1;
      [*] = ;               UpdateConnectionState(whd,state,0);
      [*] = ;
      [*] = ;               LanSetMyPassword(gInetProfile.netpass);
      [*] = ;               LanSetMyCDKey(gInetProfile.netkey);
      [*] = ;               LanPublicServerLogin();
      [*] = ;            end;
      [*] = ;            leShellInvalidEmail : begin
      [*] = ;               gInetProfile.netemail := gProfile.netemail;
      [*] = ;               gInetProfile.netpass := gProfile.netkey;
      [*] = ;               gInetProfile.netkey := gProfile.netkey;
      [*] = ;               if gBoolRegister_UseNameAsNick then
      [*] = ;                  gInetProfile.name := gProfile.name
      [*] = ;               else
      [*] = ;                  gInetProfile.name := gProfile.nick;
      [*] = ;
      [*] = ;               state := (state + 1) or $80;
      [*] = ;               UpdateConnectionState(whd,state,0);
      [*] = ;
      [*] = ;               LanSetMyEmail(gInetProfile.netemail);
      [*] = ;               LanSetMyPassword(gInetProfile.netpass);
      [*] = ;               LanSetMyCDKey(gInetProfile.netkey);
      [*] = ;               LanSetMyCountry(StrToUpperCase(GetLocaleTableListItemByID('menu','lang_id')));
      [*] = ;               LanPublicServerRegister();
      [*] = ;            end;
      [*] = ;            leShellLogged : begin
      [*] = ;               state := state + 1;
      [*] = ;               _inet_UpdateNetworkProfileInfo(false,true);
      [*] = ;               LanSetMyNick(gInetProfile.name);
      [*] = ;               LanPublicServerRegister();
      [*] = ;               LanPublicServerUpdateClientInfo(LanMyInfoID());
      [*] = ;               RegistrationSucceeded(whd,state);
      [*] = ;            end;
      [*] = ;            //
      [*] = ;            leShellRegClientFailed,
      [*] = ;            leShellRegCDKeyFailed,
      [*] = ;            leShellRegDataFailed,
      [*] = ;            leShellAuthClientFailed,
      [*] = ;            leShellAuthBannedFailed,
      [*] = ;            leShellAuthCDKeyFailed : begin
      [*] = ;               state := $ff;
      [*] = ;               UpdateConnectionState(whd,state,e_id);
      [*] = ;            end;
      [*] = ;            leShutdown : state := $fd;
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if _log then
      [*] = ;               begin
      [*] = ;                  var en : String;
      [*] = ;
      [*] = ;                  _lan_GetLanEventName(e_id,en);
      [*] = ;                  _Log_lan(_log_name+' Unhandled lan event: ' + en);
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CancelRegistration();
      [*] = ;begin
      [*] = ;   var whd : Integer;
      [*] = ;
      [*] = ;   whd := _gui_GetWindow(cLanRegisterStatusWindowName);
      [*] = ;
      [*] = ;   LanPublicServerLeave();
      [*] = ;   LanTerminateGame();
      [*] = ;   LanShutdown();
      [*] = ;   _gui_RootWindowRemoveWithFade(whd,gc_gui_FadeTime0_2);
      [*] = ;   _cmd_Post('menuaction','multiplayer','');
      [*] = ;end;
      [*] = ;
      [*] = ;var mode : Integer = IntRegister0;
      [*] = ;var cmd : String = StringRegister0;
      [*] = ;var cmd_attr : String = StringRegister1;
      [*] = ;var reg_attr : String = StringRegister2;
      [*] = ;var user_attr : String = StringRegister3;
      [*] = ;var res,i,whd,bhd,thd,posx : Integer;
      [*] = ;var ret_str,temp_str : String;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;res := 0;
      [*] = ;ret_str := '';
      [*] = ;
      [*] = ;case cmd of
      [*] = ;   '.menulanevent' : begin
      [*] = ;      if _log then
      [*] = ;      begin
      [*] = ;         _lan_GetLanEventName( StrToInt(user_attr),temp_str);
      [*] = ;         _log_lan(_log_name+' '+cmd_attr+': '+temp_str+'['+ user_attr+']');
      [*] = ;      end;
      [*] = ;      case cmd_attr of
      [*] = ;         'lan' : begin
      [*] = ;            res := 1;
      [*] = ;            if mode = 0 then ProcessLanEvent(StrToInt(user_attr));
      [*] = ;         end;
      [*] = ;         'cancel' : begin
      [*] = ;            res := 1;
      [*] = ;            if mode = 0 then CancelRegistration();
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;
      [*] = ;IntRegister2 := res;
      [*] = ;StringRegister0 := ret_str;
   struct.end
section.end

