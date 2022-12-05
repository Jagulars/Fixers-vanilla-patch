section.begin
   Name = EventInternetShellProfile
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
      [*] = ;var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var elmName : String =  GetGUIElementNameByIndex(elmHandle);
      [*] = ;
      [*] = ;const cEventState = 'EventInternetShellProfile';
      [*] = ;const cBtnAcceptTag = 100;
      [*] = ;const cBtnCancelTag = 102;
      [*] = ;
      [*] = ;if (sPress='c') then
      [*] = ;begin
      [*] = ;   if (elmName='text') then
      [*] = ;   begin
      [*] = ;      //var elmInputTextHnd : Integer = GetGUIElementIndexByNameParent('text', elmHandle);
      [*] = ;      SetGUIElementTag(elmHandle, 10);
      [*] = ;      SetGUIElementFocusedHandle(elmHandle);
      [*] = ;      SetGUIEventStateOnKeyDown('KeyPressProfile');
      [*] = ;   end;
      [*] = ;   if (elmName='arrowSliderLeft') or (elmName='arrowSliderRight') then
      [*] = ;   begin
      [*] = ;      var elmSliderHandle : Integer = GetGUIElementParentByIndex(elmHandle);
      [*] = ;      var sliderID : String = GetGUIElementStringTag(elmSliderHandle);
      [*] = ;      case sliderID of
      [*] = ;         'sign' : begin
      [*] = ;            var value : Integer = gInetProfileTmp.sign;
      [*] = ;            if (elmName='arrowSliderLeft') then
      [*] = ;            value := value-1
      [*] = ;            else
      [*] = ;            value := value+1;
      [*] = ;            var maxValue : Integer = 25;
      [*] = ;            if (value>maxValue) then value := 0;
      [*] = ;            if (value<0) then value := maxValue;
      [*] = ;            _gui_SetSliderIntValue(elmSliderHandle, value, maxValue+1, '', true);
      [*] = ;            gInetProfileTmp.sign := value;
      [*] = ;         end;
      [*] = ;         'color1' : begin
      [*] = ;            var value : Integer = gInetProfileTmp.color1;
      [*] = ;            if (elmName='arrowSliderLeft') then
      [*] = ;            value := value-1
      [*] = ;            else
      [*] = ;            value := value+1;
      [*] = ;            var maxValue : Integer = 15;
      [*] = ;            if (value>maxValue) then value := 0;
      [*] = ;            if (value<0) then value := maxValue;
      [*] = ;            _gui_SetSliderIntValue(elmSliderHandle, value, maxValue+1, '', true);
      [*] = ;            gInetProfileTmp.color1 := value;
      [*] = ;         end;
      [*] = ;         'color2' : begin
      [*] = ;            var value : Integer = gInetProfileTmp.color2;
      [*] = ;            if (elmName='arrowSliderLeft') then
      [*] = ;            value := value-1
      [*] = ;            else
      [*] = ;            value := value+1;
      [*] = ;            var maxValue : Integer = 15;
      [*] = ;            if (value>maxValue) then value := 0;
      [*] = ;            if (value<0) then value := maxValue;
      [*] = ;            _gui_SetSliderIntValue(elmSliderHandle, value, maxValue+1, '', true);
      [*] = ;            gInetProfileTmp.color2 := value;
      [*] = ;         end;
      [*] = ;         'avatar' : begin
      [*] = ;            var value : Integer = gInetProfileTmp.avatar;
      [*] = ;            if (elmName='arrowSliderLeft') then
      [*] = ;            value := value-1
      [*] = ;            else
      [*] = ;            value := value+1;
      [*] = ;            var maxValue : Integer = 20;
      [*] = ;            if (value>maxValue) then value := 1;
      [*] = ;            if (value<1) then value := maxValue;
      [*] = ;            _gui_SetSliderIntValue(elmSliderHandle, value, maxValue+1, '', true);
      [*] = ;            gInetProfileTmp.avatar := value;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      ExecuteState('ShowInternetShellProfile');
      [*] = ;   end;
      [*] = ;   
      [*] = ;   var tag : Integer = GetIntValueByName('Tag');
      [*] = ;   case tag of
      [*] = ;      cBtnAcceptTag, gc_gui_hotkey_btnEnter : begin
      [*] = ;         var elmInputboxText : Integer = GetGUIElementIndexByNameParent('shellprofile.nickname.text', _gui_GetLayerI());
      [*] = ;         var nickname : String = GetGUIElementText(elmInputboxText);
      [*] = ;         elmInputboxText := GetGUIElementIndexByNameParent('shellprofile.password.text', _gui_GetLayerI());
      [*] = ;         var password : String = GetGUIElementText(elmInputboxText);
      [*] = ;         elmInputboxText := GetGUIElementIndexByNameParent('shellprofile.confirmpassword.text', _gui_GetLayerI());
      [*] = ;         var confirmpassword : String = GetGUIElementText(elmInputboxText);
      [*] = ;         
      [*] = ;         if (StrLength(nickname)<4) or (StrLength(nickname)>16) then
      [*] = ;         _gui_ShowQuestionDialog('menu|130', cEventState, 0, '', 0, False, True)
      [*] = ;         else
      [*] = ;         if (not IsNickValidChar(nickname)) then // add restricted characters list here
      [*] = ;         _gui_ShowQuestionDialog('menu|131', cEventState, 0, '', 0, False, True)
      [*] = ;         else
      [*] = ;         if (StrLength(password)<5) or (StrLength(password)>16) then
      [*] = ;         _gui_ShowQuestionDialog('menu|132', cEventState, 0, '', 0, False, True)
      [*] = ;         else
      [*] = ;         if (not IsPasswordValid(password)) then
      [*] = ;         _gui_ShowQuestionDialog('menu|133', cEventState, 0, '', 0, False, True)
      [*] = ;         else
      [*] = ;         if (password<>confirmpassword) then
      [*] = ;         _gui_ShowQuestionDialog('menu|134', cEventState, 0, '', 0, False, True)
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            // Set server profile
      [*] = ;            LanSetMyPassword(password);
      [*] = ;            LanSetMyNick(nickname);
      [*] = ;            gInetProfileTmp.name := nickname;
      [*] = ;            gInetProfileTmp.netpass := password;
      [*] = ;            _misc_AssignGlobalVars('gInetProfileTmp', 'gInetProfile');
      [*] = ;            var newInfo : String = IntToStr(gInetProfile.color1)+gc_gui_DelimiterCharStr+IntToStr(gInetProfile.color2)+gc_gui_DelimiterCharStr+IntToStr(gInetProfile.sign)+gc_gui_DelimiterCharStr+IntToStr(gInetProfile.avatar);
      [*] = ;            LanSetMyProfInfo(newInfo);
      [*] = ;            LanPublicServerRegister;
      [*] = ;            LanPublicServerUpdateClientInfo(LanMyInfoID);
      [*] = ;            if (password<>gProfile.netpass) then
      [*] = ;            begin
      [*] = ;               gProfile.netpass := gInetProfile.netpass;
      [*] = ;               _prof_SaveUserProfile;
      [*] = ;               UserSaveProfile;
      [*] = ;            end;
      [*] = ;            _gui_RootWindowRemoveWithFade(GetGUIElementIndexByNameParent('shellprofile', _gui_GetLayerI()),gc_gui_FadeTime0_2);
      [*] = ;            ExecuteState('ShowInternetShell');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cBtnCancelTag, gc_gui_hotkey_btnEscape : begin
      [*] = ;         _gui_RootWindowRemoveWithFade(GetGUIElementIndexByNameParent('shellprofile', _gui_GetLayerI()),gc_gui_FadeTime0_2);
      [*] = ;         ExecuteState('ShowInternetShell');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

