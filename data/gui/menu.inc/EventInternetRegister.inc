section.begin
   Name = EventInternetRegister
   Code : struct.begin
      [*] = ;function IsNickValidChar(text : String) : Boolean;
      [*] = ;begin
      [*] = ;   Result := True;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=1 to StrLength(text) do
      [*] = ;   begin
      [*] = ;      var symbol : String = SubStr(text, i, 1);
      [*] = ;      if (symbol<=#45) or (symbol=#47) or ((symbol>=#58) and (symbol<=#64)) or (symbol=#92) or (symbol=#94) or (symbol=#95) or (symbol=#96) or (symbol>=#123) then
      [*] = ;      //if (symbol<=#32) or (symbol>#126) or (symbol=#34) or (symbol=#40) or (symbol=#41) or (symbol=#44) or (symbol=#58) or (symbol=#59) or (symbol=#60)
      [*] = ;      //or (symbol=#62) {or (symbol=#91)} or (symbol=#92) {or (symbol=#93)} then
      [*] = ;      begin
      [*] = ;         Result := False;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function IsStringValidChar(text : String; minChar, maxChar : String) : Boolean;
      [*] = ;begin
      [*] = ;   Result := True;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=1 to StrLength(text) do
      [*] = ;   begin
      [*] = ;      var symbol : String = SubStr(text, i, 1);
      [*] = ;      if (symbol<minChar) and (symbol>maxChar) then
      [*] = ;      begin
      [*] = ;         Result := False;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function IsPasswordValid(password : String) : Boolean;
      [*] = ;begin
      [*] = ;   Result := True;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=1 to StrLength(password) do
      [*] = ;   begin
      [*] = ;      var symbol : String = SubStr(password, i, 1);
      [*] = ;      if ((symbol<#33) and (symbol>#126)) or (symbol=#124) then
      [*] = ;      begin
      [*] = ;         Result := False;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
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
      [*] = ;if (sPress='c') then
      [*] = ;begin
      [*] = ;   case tag of
      [*] = ;      cBtnAcceptTag, gc_gui_hotkey_btnEnter : begin
      [*] = ;         var elmInputboxText : Integer = GetGUIElementIndexByNameParent('internetregister.nickname.text', _gui_GetLayerI());
      [*] = ;         var nickname : String = GetGUIElementText(elmInputboxText);
      [*] = ;         elmInputboxText := GetGUIElementIndexByNameParent('internetregister.password.text', _gui_GetLayerI());
      [*] = ;         var password : String = GetGUIElementText(elmInputboxText);
      [*] = ;         elmInputboxText := GetGUIElementIndexByNameParent('internetregister.confirmpassword.text', _gui_GetLayerI());
      [*] = ;         var confirmpassword : String = GetGUIElementText(elmInputboxText);
      [*] = ;         elmInputboxText := GetGUIElementIndexByNameParent('internetregister.internetgamekey.text', _gui_GetLayerI());
      [*] = ;         var internetgamekey : String = GetGUIElementText(elmInputboxText);
      [*] = ;
      [*] = ;         if (nickname='') or (password='') or (internetgamekey='') then
      [*] = ;         _gui_ShowQuestionDialog('menu|129', cEventState, 0, '', 0, False, True)
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            if (StrLength(nickname)<4) or (StrLength(nickname)>16) then
      [*] = ;            _gui_ShowQuestionDialog('menu|130', cEventState, 0, '', 0, False, True)
      [*] = ;            else
      [*] = ;            if (not IsNickValidChar(nickname)) then // add restricted characters list here
      [*] = ;            _gui_ShowQuestionDialog('menu|131', cEventState, 0, '', 0, False, True)
      [*] = ;            else
      [*] = ;            if (StrLength(password)<5) or (StrLength(password)>16) then
      [*] = ;            _gui_ShowQuestionDialog('menu|132', cEventState, 0, '', 0, False, True)
      [*] = ;            else
      [*] = ;            if (not IsPasswordValid(password)) then
      [*] = ;            _gui_ShowQuestionDialog('menu|133', cEventState, 0, '', 0, False, True)
      [*] = ;            else
      [*] = ;            if (password<>confirmpassword) then
      [*] = ;            _gui_ShowQuestionDialog('menu|134', cEventState, 0, '', 0, False, True)
      [*] = ;            else
      [*] = ;            if (internetgamekey='') then
      [*] = ;            _gui_ShowQuestionDialog('menu|135', cEventState, 0, '', 0, False, True)
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               // Register
      [*] = ;               gFloatRegister_InetLanTimerWaitServerAnswer := GetCurrentTime+gc_gui_FadeTime0_4;
      [*] = ;
      [*] = ;               gInetProfile.netpass := password;
      [*] = ;
      [*] = ;               var email : String = gInetProfile.netemail;
      [*] = ;               LanSetMyEmail(gInetProfile.netemail);
      [*] = ;               LanSetMyPassword(password);
      [*] = ;               LanSetMyCDKey(internetgamekey);
      [*] = ;               LanSetMyNick(nickname);
      [*] = ;               LanSetMyCountry('');
      [*] = ;               _inet_UpdateNetworkProfileInfo(false,true);
      [*] = ;               LanPublicServerRegister;
      [*] = ;               LanPublicServerUpdateClientInfo(LanMyInfoID());
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cBtnCancelTag, gc_gui_hotkey_btnEscape : begin
      [*] = ;         _gui_RootWindowRemoveWithFade(GetGUIElementIndexByNameParent('internetregister', _gui_GetLayerI()),gc_gui_FadeTime0_2);
      [*] = ;         _gui_DelayExecuteStateOneInstance('ShowInternetLogin', gc_gui_FadeTime0_2);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

