section.begin
   Name = EventProfile
   Code : struct.begin
      [*] = ;var _log_name : String = 'MENU.INC\EVENTPROFILE';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;const cTabChar = 9;
      [*] = ;
      [*] = ;function SaveProfileWindowInputBoxValues() : Integer;
      [*] = ;begin
      [*] = ;   var elmInputboxText : Integer = _gui_GetWindow('Profile.name.text');
      [*] = ;   var nm,land : String;
      [*] = ;
      [*] = ;   Result := 0;
      [*] = ;   nm := GetGUIElementText(elmInputboxText);
      [*] = ;   elmInputboxText := _gui_GetWindow('Profile.land.text');
      [*] = ;   land := GetGUIElementText(elmInputboxText);
      [*] = ;
      [*] = ;   if ((nm='') or (land = '')) then
      [*] = ;   begin
      [*] = ;      if ((nm='') and (land = '')) then
      [*] = ;         Result := 87
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if ((land='') or (not _prof_IsNameOrLandValid(land))) then
      [*] = ;            Result := 85
      [*] = ;         else
      [*] = ;            Result := 86;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if Result = 0 then
      [*] = ;   begin
      [*] = ;      if (StrLength(nm)<4) or (StrLength(nm)>16) then
      [*] = ;         Result := 130
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if (not _prof_IsNameOrLandValid(nm)) then
      [*] = ;            Result := 131;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if Result = 0 then
      [*] = ;   begin
      [*] = ;      gProfileTmp.name := nm;
      [*] = ;      gProfileTmp.land := land;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var sStatus : String = GetValueByName('Status');
      [*] = ;var sPress  : String = GetValueByName('Press');
      [*] = ;var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var elmName : String =  GetGUIElementNameByIndex(elmHandle);
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;
      [*] = ;const cBtnAcceptTag = 100;
      [*] = ;const cBtnOtherProfileTag = 101;
      [*] = ;const cBtnCancelTag = 102;
      [*] = ;const cBtnCustomDifficultyTag = 103;
      [*] = ;const cBtnAchievementsTag = 104;
      [*] = ;
      [*] = ;if (sStatus = 'key') then
      [*] = ;begin
      [*] = ;   var whd : Integer;
      [*] = ;   var e_name : String;
      [*] = ;
      [*] = ;   if sPress = 'u' then
      [*] = ;   begin
      [*] = ;      case tag of
      [*] = ;         cTabChar : begin
      [*] = ;            e_name := 'name.text';
      [*] = ;            whd := GetGUIFocusedElementHandle();
      [*] = ;            if whd <> 0 then
      [*] = ;            begin
      [*] = ;               var thd,i : Integer;
      [*] = ;               for i := 0 to 1 do
      [*] = ;               begin
      [*] = ;                  if i=1 then
      [*] = ;                     e_name := 'land.text';
      [*] = ;                  thd := GetGUIElementIndexByNameParent(e_name,_gui_GetWindow('Profile'));
      [*] = ;                  if thd = whd then
      [*] = ;                     break;
      [*] = ;               end;
      [*] = ;               if i < 2 then
      [*] = ;               begin
      [*] = ;                  i := i + 1;
      [*] = ;                  if i > 1 then i := 0;
      [*] = ;               end;
      [*] = ;               if i=0 then
      [*] = ;                  e_name := 'name.text'
      [*] = ;               else
      [*] = ;                  e_name := 'land.text';
      [*] = ;            end;
      [*] = ;            whd := GetGUIElementIndexByNameParent(e_name,_gui_GetWindow('Profile'));
      [*] = ;            if whd <> 0 then SetGUIElementFocusedHandle(whd);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   _gv_traceState(_log_name,$1000000 or _log_trace);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;if (sPress='c') then
      [*] = ;begin
      [*] = ;   if (elmName='text') then
      [*] = ;   begin
      [*] = ;      //var elmInputTextHnd : Integer = GetGUIElementIndexByNameParent('text', elmHandle);
      [*] = ;      SetGUIElementTag(elmHandle, 10);
      [*] = ;      SetGUIElementFocusedHandle(elmHandle);
      [*] = ;      //SetGUIEventStateOnKeyDown('KeyPressProfile');
      [*] = ;   end;
      [*] = ;   if (elmName='arrowSliderLeft') or (elmName='arrowSliderRight') then
      [*] = ;   begin
      [*] = ;      var elmSliderHandle : Integer = GetGUIElementParentByIndex(elmHandle);
      [*] = ;      var sliderID : String = GetGUIElementStringTag(elmSliderHandle);
      [*] = ;      case sliderID of
      [*] = ;         'sign' : begin
      [*] = ;            var value : Integer = gProfileTmp.sign;
      [*] = ;            if (elmName='arrowSliderLeft') then
      [*] = ;            value := value-1
      [*] = ;            else
      [*] = ;            value := value+1;
      [*] = ;            var maxValue : Integer = 25;
      [*] = ;            if (value>maxValue) then value := 0;
      [*] = ;            if (value<0) then value := maxValue;
      [*] = ;            _gui_SetSliderIntValue(elmSliderHandle, value, maxValue+1, '', true);
      [*] = ;            gProfileTmp.sign := value;
      [*] = ;         end;
      [*] = ;         'color1' : begin
      [*] = ;            var value : Integer = gProfileTmp.color1;
      [*] = ;            if (elmName='arrowSliderLeft') then
      [*] = ;            value := value-1
      [*] = ;            else
      [*] = ;            value := value+1;
      [*] = ;            var maxValue : Integer = 15;
      [*] = ;            if (value>maxValue) then value := 0;
      [*] = ;            if (value<0) then value := maxValue;
      [*] = ;            _gui_SetSliderIntValue(elmSliderHandle, value, maxValue+1, '', true);
      [*] = ;            gProfileTmp.color1 := value;
      [*] = ;         end;
      [*] = ;         'color2' : begin
      [*] = ;            var value : Integer = gProfileTmp.color2;
      [*] = ;            if (elmName='arrowSliderLeft') then
      [*] = ;               value := value-1
      [*] = ;            else
      [*] = ;               value := value+1;
      [*] = ;            var maxValue : Integer = 15;
      [*] = ;            if (value>maxValue) then value := 0;
      [*] = ;            if (value<0) then value := maxValue;
      [*] = ;            _gui_SetSliderIntValue(elmSliderHandle, value, maxValue+1, '', true);
      [*] = ;            gProfileTmp.color2 := value;
      [*] = ;         end;
      [*] = ;         'avatar' : begin
      [*] = ;            var value : Integer = gProfileTmp.avatar;
      [*] = ;            if (elmName='arrowSliderLeft') then
      [*] = ;            value := value-1
      [*] = ;            else
      [*] = ;            value := value+1;
      [*] = ;            var maxValue : Integer = 20;
      [*] = ;            if (value>maxValue) then value := 1;
      [*] = ;            if (value<1) then value := maxValue;
      [*] = ;            _gui_SetSliderIntValue(elmSliderHandle, value, maxValue+1, '', true);
      [*] = ;            gProfileTmp.avatar := value;
      [*] = ;         end;
      [*] = ;         'difficulty' : begin
      [*] = ;            if (gProfileTmp.advdiff.custom) then
      [*] = ;               gProfileTmp.advdiff.custom := false
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               var value : Integer = gProfileTmp.advdiff.basediff;
      [*] = ;               if (elmName='arrowSliderLeft') then
      [*] = ;                  value := value-1
      [*] = ;               else
      [*] = ;                  value := value+1;
      [*] = ;               var maxValue : Integer = 6;
      [*] = ;               if (value>maxValue) then value := 0;
      [*] = ;               if (value<0) then value := maxValue;
      [*] = ;               var text : String = 'difficulty|'+IntToStr(value);
      [*] = ;               _gui_SetSliderIntValue(elmSliderHandle, value, 7, text, false);
      [*] = ;               gProfileTmp.advdiff.basediff := value;
      [*] = ;               gProfileTmp.difficulty := value;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;      end;
      [*] = ;      SaveProfileWindowInputBoxValues();
      [*] = ;      GUIExecuteState('ShowProfile');
      [*] = ;   end;
      [*] = ;
      [*] = ;   var tag : Integer = GetIntValueByName('Tag');
      [*] = ;   case tag of
      [*] = ;      cBtnAcceptTag, gc_gui_hotkey_btnEnter : begin
      [*] = ;         var r : Integer;
      [*] = ;
      [*] = ;         r := SaveProfileWindowInputBoxValues();
      [*] = ;         if r=0 then
      [*] = ;         begin
      [*] = ;            _misc_AssignGlobalVars('gProfileTmp', 'gProfile');
      [*] = ;            _prof_SaveUserProfile();
      [*] = ;            UserSaveProfile();
      [*] = ;            SetGUIEventStateOnKeyDown('');
      [*] = ;            _gui_RootWindowRemoveWithFade(_gui_GetWindow('Profile'),gc_gui_FadeTime0_2);
      [*] = ;            _cmd_Post('menuaction','mainmenu','');
      [*] = ;         end
      [*] = ;         else
      [*] = ;            _gui_ShowQuestionDialog('menu|'+IntToStr(r), 'EventProfile', 0, '', 0, False, False);
      [*] = ;      end;
      [*] = ;      cBtnCancelTag, gc_gui_hotkey_btnEscape : begin
      [*] = ;         SetGUIEventStateOnKeyDown('');
      [*] = ;         _gui_RootWindowRemoveWithFade(_gui_GetWindow('Profile'),gc_gui_FadeTime0_2);
      [*] = ;         _cmd_Post('menuaction','mainmenu','');
      [*] = ;      end;
      [*] = ;      cBtnOtherProfileTag : begin
      [*] = ;         SaveProfileWindowInputBoxValues;
      [*] = ;         SetGUIEventStateOnKeyDown('');
      [*] = ;         _gui_RootWindowRemoveWithFade(_gui_GetWindow('Profile'),gc_gui_FadeTime0_2);
      [*] = ;         _gui_DelayExecuteStateOneInstance('ShowChooseProfile', gc_gui_FadeTime0_2);
      [*] = ;      end;
      [*] = ;      cBtnCustomDifficultyTag : begin
      [*] = ;         if (not gProfileTmp.advdiff.custom) then
      [*] = ;            _map_SetGameCustomDifficultyOptionsDefault(gProfileTmp.advdiff, False, gProfileTmp.advdiff.basediff);
      [*] = ;         BoolRegister0 := True;
      [*] = ;         GUIExecuteState('ShowCustomDifficulty');
      [*] = ;      end;
      [*] = ;      cBtnAchievementsTag : begin
      [*] = ;         IntRegister0 := 0;
      [*] = ;         IntRegister1 := 1;
      [*] = ;         GUIExecuteState('vvk.ShowAchievListModal');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

