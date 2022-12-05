section.begin
   Name = EvLanShellChat
   Code : struct.begin
      [*] = ;var _log_name : String = 'MENU.INC\EVLANSHELLCHAT';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;var status : String = GetValueByName('Status');
      [*] = ;var press : String = GetValueByName('Press');
      [*] = ;var tag : Integer = 0;
      [*] = ;if (status='shortcut') then
      [*] = ;begin
      [*] = ;   // Keyboard event
      [*] = ;   case GetValueByName('Key') of
      [*] = ;      'escape','Escape' : tag := 100;
      [*] = ;      'return','Return' : tag := 201;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else if (status='button') then
      [*] = ;begin
      [*] = ;   // Button press
      [*] = ;   if (press='c') then
      [*] = ;      tag := GetIntValueByName('Tag');
      [*] = ;end;
      [*] = ;
      [*] = ;var elmChat : Integer = _gui_GetWindow('internetshell.rightpanel.chat');
      [*] = ;var elmChatHistory : Integer = GetGUIElementIndexByNameParent('history', elmChat);
      [*] = ;var elmChatInput : Integer = GetGUIElementIndexByNameParent('chatinput', elmChat);
      [*] = ;var elmChatInputText : Integer = GetGUIElementIndexByNameParent('text', elmChatInput);
      [*] = ;
      [*] = ;case tag of
      [*] = ;   100 : begin
      [*] = ;      if (GetGUIElementFocusedByHandle(elmChatInputText)) then
      [*] = ;      begin
      [*] = ;         if _log then _log_map(GetGUIElementText(elmChatInputText));
      [*] = ;         SetGUIElementText(elmChatInputText, '');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         SetValueByName('Status','shortcut');
      [*] = ;         SetValueByName('Press','c');
      [*] = ;         SetIntValueByName('Tag',gc_gui_hotkey_btnEscape);
      [*] = ;         GUIExecuteState('EventInternetShell');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   200, 201 : begin
      [*] = ;      // Chat - "send message"
      [*] = ;      // Add 'Send Message' button
      [*] = ;      var msg : String = GetGUIElementText(elmChatInputText);
      [*] = ;      if (StrPos('/', msg)=1) then
      [*] = ;      begin
      [*] = ;         if SameText(msg, '/clr') or SameText(msg, '/clear') then
      [*] = ;         begin
      [*] = ;            GUIListBoxClearSilent(elmChatHistory);
      [*] = ;
      [*] = ;            var pChat : Integer;
      [*] = ;            if (GetGUIElementVisible(elmChatHistory)) then
      [*] = ;               pChat := _misc_ParserGetOrCreateByKey('shell.commonchat',true)
      [*] = ;            else
      [*] = ;               pChat := _misc_ParserGetOrCreateByKey('shell.roomchat',true);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         if SameText(msg, '/help') or SameText(msg, '/?') then
      [*] = ;         begin
      [*] = ;            if _log then _log_map(msg);
      [*] = ;         end;
      [*] = ;         SetGUIElementText(elmChatInputText, '');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if StrExists(msg, GetLocaleTableListItemByID('menu', 'chat_unsupported')) then
      [*] = ;      begin
      [*] = ;         SetGUIElementText(elmChatInputText, '');
      [*] = ;         SetGUIElementFocusedHandle(elmChatInputText);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (msg<>'') then
      [*] = ;      begin
      [*] = ;         var i : Integer = StrPos(':', msg);
      [*] = ;         var idTo, id : Integer = 0;
      [*] = ;         var bTacticalRoom : Boolean = false;
      [*] = ;         var myID : Integer = LanMyInfoID();
      [*] = ;         var nick : String = StrTrim(SubStr(msg, 4, i-4));
      [*] = ;         if (i > 0) then
      [*] = ;         begin
      [*] = ;            id := LanPublicServerGetClientIndexByClientNick(nick);
      [*] = ;            if (id >= 0) then
      [*] = ;            begin
      [*] = ;               msg := SubStr(msg, i+1, StrLength(msg));
      [*] = ;               var pClient : Integer = _misc_ParserGetOrCreateByKey('client_info',true);
      [*] = ;               LanPublicServerGetClientInfoToParserByIndex(id, pClient);
      [*] = ;               idTo := ParserGetIntValueByKeyByHandle(pClient, 'ID');
      [*] = ;               var clientInfo : String = ParserGetValueByKeyByHandle(pClient, 'Info');
      [*] = ;               bTacticalRoom := (_sa_GetAsInt(clientInfo,5)>0);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         SetGUIElementText(elmChatInputText, '');
      [*] = ;         msg := StrTrim(msg);
      [*] = ;
      [*] = ;         if (msg<>'') then
      [*] = ;         begin
      [*] = ;            if idTo = myID then // update profile message
      [*] = ;            begin
      [*] = ;               msg := StrReplace(msg, ' ', '_');
      [*] = ;               msg := StrReplace(msg, '|', '_');
      [*] = ;               msg := StrReplace(msg, '#', '_');
      [*] = ;               gProfile.profilemessage := msg;
      [*] = ;               
      [*] = ;               _inet_UpdateNetworkProfileInfo(false,true);
      [*] = ;               LanPublicServerRegister();
      [*] = ;               LanPublicServerUpdateClientInfo(myID);
      [*] = ;               
      [*] = ;               _inet_PlayerSelected(_gui_GetWindow('internetshell.rightpanel.players.list'), false, true);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if bTacticalRoom then // filter messages separately for battle and shard rooms (legacy)
      [*] = ;                  msg := '[B]'+msg
      [*] = ;               else
      [*] = ;                  msg := '[S]'+msg; // we will use 'S' by default because if we want to chat with players without the mod, they are most likely going to be in the shard room. They will only see the message with the S prefix.
      [*] = ;               LanPublicServerSendMessage(idTo, msg);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (idTo <> 0) and (idTo <> myID) then
      [*] = ;         begin
      [*] = ;            msg := '-->'+nick+': ';
      [*] = ;            SetGUIElementText(elmChatInputText, msg);
      [*] = ;         end;
      [*] = ;
      [*] = ;         SetGUIElementFocusedHandle(elmChatInputText);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

