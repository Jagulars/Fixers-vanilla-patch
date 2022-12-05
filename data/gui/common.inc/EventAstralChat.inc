section.begin
   Name = EventAstralChat
   Code : struct.begin
      [*] = ;var _log_name : String = 'MENU.INC\EVENTASTRALCHAT';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;var status : String = GetValueByName('Status');
      [*] = ;var press : String = GetValueByName('Press');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;
      [*] = ;const cShellClientsList = 'internetshell.rightpanel.players.list';
      [*] = ;const cMuteButton = 'internetshell.rightpanel.profile.mute';
      [*] = ;const cProfileInfo = 'internetshell.rightpanel.profile';
      [*] = ;
      [*] = ;const cListBoxPlayers = 30;
      [*] = ;const cBtnCloseTag = 101;
      [*] = ;const cBtnShrinkTag = 102;
      [*] = ;const cBtnExpandTag = 103;
      [*] = ;const cBtnOpenTag = 104;
      [*] = ;const cBtnMuteTag = 105;
      [*] = ;const cBtnExpandProfileTag = 106;
      [*] = ;
      [*] = ;procedure ShowAstralChat;
      [*] = ;begin
      [*] = ;   if _inet_AstralChatModal then
      [*] = ;      IntRegister0 := 2
      [*] = ;   else
      [*] = ;      IntRegister0 := 0;
      [*] = ;   GUIExecuteState('ShowAstralChat');
      [*] = ;end;
      [*] = ;
      [*] = ;var elmChatInputText : Integer = _gui_GetWindow('internetshell.rightpanel.chat.chatinput.text');//GetGUIElementIndexByNameParent('text', elmChatInput);
      [*] = ;
      [*] = ;if (status='select') then
      [*] = ;begin
      [*] = ;   case tag of
      [*] = ;      cListBoxPlayers : begin
      [*] = ;         _inet_PlayerSelected(elmHandle, true, true);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   if (press='c') then
      [*] = ;   begin
      [*] = ;      case tag of
      [*] = ;         cBtnOpenTag : begin
      [*] = ;            if LanMyInfoID <> 0 then
      [*] = ;            begin
      [*] = ;               ShowAstralChat;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               gConnectIPIndex := 0;
      [*] = ;               GUIExecuteState('DoLanConnect');
      [*] = ;            end;
      [*] = ;            var chatBlink : Boolean = true;
      [*] = ;            _gui_RemoveBlinkElement('btnOpenChatBlink', chatBlink);
      [*] = ;         end;
      [*] = ;         cBtnExpandTag : begin
      [*] = ;            var viewHeight : Integer = GetViewerHeight();
      [*] = ;            var chatSize : Integer = gProfile.astralchatsize;
      [*] = ;            if (chatSize < 14) 
      [*] = ;            or ((chatSize < 18) and ((viewHeight > 800) or (gGame.gameType <> gc_GameTypeNone))) 
      [*] = ;            or ((chatSize < 20) and ((viewHeight > 1000) or (gGame.gameType <> gc_GameTypeNone))) then
      [*] = ;            begin
      [*] = ;               gProfile.astralchatsize := chatSize + 1 + chatSize div 4;
      [*] = ;               ShowAstralChat;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         cBtnShrinkTag : begin
      [*] = ;            var chatSize : Integer = gProfile.astralchatsize;
      [*] = ;            if chatSize > 1 then
      [*] = ;            begin
      [*] = ;               if (gGame.gametype = gc_GameTypeNone) then
      [*] = ;               begin
      [*] = ;                  var viewHeight : Integer = GetViewerHeight();
      [*] = ;                  if (chatSize >= 18) and (viewHeight <= 800) then
      [*] = ;                     chatSize := 14
      [*] = ;                  else
      [*] = ;                  if (chatSize >= 20) and (viewHeight <= 1000) then
      [*] = ;                     chatSize := 18;
      [*] = ;               end;
      [*] = ;               gProfile.astralchatsize := chatSize - 1 - (chatSize-1-chatSize div 4) div 4;
      [*] = ;               ShowAstralChat;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         cBtnCloseTag, gc_gui_hotkey_btnEscape : begin
      [*] = ;            _gui_FadeWindow_VVK(_gui_GetWindow('internetshell'), gc_gui_FadeTime0_2, 1);
      [*] = ;            
      [*] = ;            if (_gui_GetWindow('NewGame') = 0) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := 1;
      [*] = ;               GUIExecuteState('ShowAstralChat');
      [*] = ;            end;
      [*] = ;            
      [*] = ;            if (not gProfile.serverautoconnect) and (GetLanMode = 0) then
      [*] = ;            begin
      [*] = ;               LanShutdown();
      [*] = ;               LanPublicServerLeave();
      [*] = ;            end;
      [*] = ;            var chatBlink : Boolean = true;
      [*] = ;            _gui_RemoveBlinkElement('btnOpenChatBlink', chatBlink);
      [*] = ;         end;
      [*] = ;         cBtnMuteTag : begin
      [*] = ;            var elmPlayerList : Integer = _gui_GetWindow(cShellClientsList);
      [*] = ;            var playerListInd : Integer = GetGUIListBoxItemIndex(elmPlayerList);
      [*] = ;            if playerListInd >= 0 then
      [*] = ;            begin
      [*] = ;               var id : Integer = GetGUIListBoxItemTag(elmPlayerList, playerListInd);
      [*] = ;
      [*] = ;               if id > 0 then
      [*] = ;               begin
      [*] = ;                  var strID : string = IntToStr(id);
      [*] = ;                  var pMutes : Integer = _misc_ParserGetOrCreateByKey('shell.mute', false);
      [*] = ;                  if ParserGetBoolValueByKeyByHandle(pMutes, strID) then //unmute
      [*] = ;                  begin
      [*] = ;                     ParserSetBoolValueByKeyByHandle(pMutes, strID, false);
      [*] = ;                     SetGUIElementChecked(elmHandle, false);
      [*] = ;                  end
      [*] = ;                  else // mute
      [*] = ;                  begin
      [*] = ;                     ParserSetBoolValueByKeyByHandle(pMutes, strID, true);
      [*] = ;                     SetGUIElementChecked(elmHandle, true);
      [*] = ;                     SetGUIElementText(elmChatInputText, '');
      [*] = ;                  end;
      [*] = ;                  {
      [*] = ;                  
      [*] = ;                  //var pMutes : Integer = ParserSelectByHandleByKey(ParserSelectUser(), 'shell.mute');
      [*] = ;                  var mutedCount : Integer = ParserGetCountByHandle(pMutes);
      [*] = ;
      [*] = ;                  var i : Integer;
      [*] = ;                  if mutedCount = 0 then
      [*] = ;                  begin
      [*] = ;                     //var pMutedPlayer : Integer = ParserAddChildByIndex(pMutes, '*');
      [*] = ;                     //ParserSetIntValueByKeyByHandle(pMutedPlayer, 'ID', id);
      [*] = ;                     ParserSetBoolValueByKeyByHandle(pMutes, IntToStr(id), true);
      [*] = ;                     SetGUIElementChecked(elmHandle, true);
      [*] = ;                     SetGUIElementText(elmChatInputText, '');
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                  for i := 0 to mutedCount-1 do
      [*] = ;                  begin
      [*] = ;                     var pMutedPlayer : Integer = ParserSelectByHandleByIndex(pMutes, i);
      [*] = ;                     var pMutedPlayerID : Integer = ParserGetIntValueByKeyByHandle(pMutedPlayer, 'ID');
      [*] = ;
      [*] = ;                     if id = pMutedPlayerID then //unmute the player
      [*] = ;                     begin
      [*] = ;                        ParserSetBoolValueByKeyByHandle(pMutes, IntToStr(id), false);
      [*] = ;                        //ParserFreeByHandle(pMutedPlayer);
      [*] = ;                        SetGUIElementChecked(elmHandle, false);
      [*] = ;                        break;
      [*] = ;                     end
      [*] = ;                     else if (i = mutedCount-1) then //mute the player
      [*] = ;                     begin
      [*] = ;                        //var pMutedPlayer : Integer = ParserAddChildByIndex(pMutes, '*');
      [*] = ;                        //ParserSetIntValueByKeyByHandle(pMutedPlayer, 'ID', id);
      [*] = ;                        ParserSetBoolValueByKeyByHandle(pMutes, IntToStr(id), true);
      [*] = ;                        SetGUIElementChecked(elmHandle, true);
      [*] = ;                        SetGUIElementText(elmChatInputText, '');
      [*] = ;                     end;
      [*] = ;                  end;}
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         cBtnExpandProfileTag : begin
      [*] = ;            var bChecked : Boolean = GetGUIElementChecked(elmHandle);
      [*] = ;            SetGUIElementChecked(elmHandle, not bChecked);
      [*] = ;            ShowAstralChat;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;{var elmParentHandle : Integer = _gui_GetWindow('internetshell');
      [*] = ;
      [*] = ;if GetGUIFocusedElementHandle() = elmChatInputText then
      [*] = ;begin
      [*] = ;   _gui_RootWindowAdd(elmParentHandle, cRootWindowModal);
      [*] = ;   _cmd_RegisterWindowState(elmParentHandle,'VVK.InternetShellCommands','EvLanShellChat');
      [*] = ;end
      [*] = ;else
      [*] = ;   _cmd_UnRegisterWindowState(elmParentHandle);}
      [*] = ;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

