section.begin
   Name = EventInternetLogin
   Code : struct.begin
      [*] = ;function IsEmailValidChar(text : String) : Boolean;
      [*] = ;begin
      [*] = ;   Result := True;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=1 to StrLength(text) do
      [*] = ;   begin
      [*] = ;      var symbol : String = SubStr(text, i, 1);
      [*] = ;      if (symbol<=#32) or (symbol>#126) or (symbol=#34) or (symbol=#40) or (symbol=#41) or (symbol=#44) or (symbol=#58) or (symbol=#59) or (symbol=#60)
      [*] = ;      or (symbol=#62) or (symbol=#91) or (symbol=#92) or (symbol=#93) then
      [*] = ;      begin
      [*] = ;         Result := False;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function IsEmailValidFormat(email : String) : Boolean;
      [*] = ;begin
      [*] = ;   if (StrExists(email, '@')) and
      [*] = ;   (StrExists(email, '.')) and
      [*] = ;   (not StrExists(email, '@.')) and
      [*] = ;   (not StrExists(email, '.@')) and
      [*] = ;   (not StrExists(email, '..')) and
      [*] = ;   (SubStr(email, 0, 1)<>'.') and
      [*] = ;   (SubStr(email, StrLength(email), 1)<>'.') and
      [*] = ;   IsEmailValidChar(email) then
      [*] = ;   Result := True
      [*] = ;   else
      [*] = ;   Result := False;
      [*] = ;end;
      [*] = ;
      [*] = ;var sPress  : String = GetValueByName('Press');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var elmName : String =  GetGUIElementNameByIndex(elmHandle);
      [*] = ;
      [*] = ;const cEventState = 'EventInternetLogin';
      [*] = ;const cBtnAcceptTag = 101;
      [*] = ;const cBtnCancelTag = 102;
      [*] = ;
      [*] = ;var bNeedRegister : Boolean = False;
      [*] = ;
      [*] = ;if (sPress='c') then
      [*] = ;begin
      [*] = ;   case tag of
      [*] = ;      cBtnAcceptTag, gc_gui_hotkey_btnEnter : begin
      [*] = ;         var elmInputboxText : Integer = GetGUIElementIndexByNameParent('internetlogin.email.text', _gui_GetLayerI());
      [*] = ;         var inputboxValue : String = GetGUIElementText(elmInputboxText);
      [*] = ;
      [*] = ;         if (inputboxValue<>'') then
      [*] = ;         begin
      [*] = ;            if (IsEmailValidFormat(inputboxValue)) then
      [*] = ;            begin
      [*] = ;               gInetProfile.netemail := inputboxValue;
      [*] = ;               // Login with e-mail
      [*] = ;               gFloatRegister_InetLanTimerWaitServerAnswer := GetCurrentTime+gc_gui_FadeTime0_4;
      [*] = ;               LanSetMyEmail(gInetProfile.netemail);
      [*] = ;               LanPublicServerUserExist(gInetProfile.netemail);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            _gui_ShowQuestionDialog('menu|128', cEventState, 0, '', 0, False, True)
      [*] = ;         end
      [*] = ;         else
      [*] = ;         _gui_ShowQuestionDialog('menu|127', cEventState, 0, '', 0, False, True)
      [*] = ;      end;
      [*] = ;      cBtnCancelTag, gc_gui_hotkey_btnEscape : begin
      [*] = ;         //ParserFree('net');
      [*] = ;         gConnectIPIndex := -1;
      [*] = ;         LanShutdown;
      [*] = ;         _gui_RootWindowRemoveWithFade(GetGUIElementIndexByNameParent('internetlogin', _gui_GetLayerI()),gc_gui_FadeTime0_2);
      [*] = ;         if ((GetLanMode = 0) and ((gGame.gameType = gc_GameTypeLanShard) or (gGame.gameType = gc_GameTypeLanBattle))) then
      [*] = ;            _gui_DelayExecuteStateOneInstance('ShowMultiplayer', gc_gui_FadeTime0_2);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

