section.begin
   Name = EventHotseatProfile
   Code : struct.begin
      [*] = ;var _log_name : String = 'MENU.INC\EVENTHOTSEATPROFILE';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;function SaveProfileWindowInputBoxValues : Boolean;
      [*] = ;begin
      [*] = ;   Result := True;
      [*] = ;   var elmInputboxText : Integer = GetGUIElementIndexByNameParent('hotseatprofile.name.text', _gui_GetLayerI());
      [*] = ;   var inputboxValue : String = GetGUIElementText(elmInputboxText);
      [*] = ;   if (inputboxValue='') then
      [*] = ;   Result := False;
      [*] = ;   gHotseatProfileTmp.name := inputboxValue;
      [*] = ;   elmInputboxText := GetGUIElementIndexByNameParent('hotseatprofile.land.text', _gui_GetLayerI());
      [*] = ;   inputboxValue := GetGUIElementText(elmInputboxText);
      [*] = ;   if (inputboxValue='') then
      [*] = ;   Result := False;
      [*] = ;   gHotseatProfileTmp.land := inputboxValue;
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
      [*] = ;      //SetGUIEventStateOnKeyDown('KeyPressProfile');
      [*] = ;   end;
      [*] = ;   if (elmName='arrowSliderLeft') or (elmName='arrowSliderRight') then
      [*] = ;   begin
      [*] = ;      var elmSliderHandle : Integer = GetGUIElementParentByIndex(elmHandle);
      [*] = ;      var sliderID : String = GetGUIElementStringTag(elmSliderHandle);
      [*] = ;      case sliderID of
      [*] = ;         'sign' : begin
      [*] = ;            var value : Integer = gHotseatProfileTmp.sign;
      [*] = ;            if (elmName='arrowSliderLeft') then
      [*] = ;            value := value-1
      [*] = ;            else
      [*] = ;            value := value+1;
      [*] = ;            var maxValue : Integer = 25;
      [*] = ;            if (value>maxValue) then value := 0;
      [*] = ;            if (value<0) then value := maxValue;
      [*] = ;            _gui_SetSliderIntValue(elmSliderHandle, value, maxValue+1, '', true);
      [*] = ;            gHotseatProfileTmp.sign := value;
      [*] = ;         end;
      [*] = ;         'color1' : begin
      [*] = ;            var value : Integer = gHotseatProfileTmp.color1;
      [*] = ;            if (elmName='arrowSliderLeft') then
      [*] = ;            value := value-1
      [*] = ;            else
      [*] = ;            value := value+1;
      [*] = ;            var maxValue : Integer = 15;
      [*] = ;            if (value>maxValue) then value := 0;
      [*] = ;            if (value<0) then value := maxValue;
      [*] = ;            _gui_SetSliderIntValue(elmSliderHandle, value, maxValue+1, '', true);
      [*] = ;            gHotseatProfileTmp.color1 := value;
      [*] = ;         end;
      [*] = ;         'color2' : begin
      [*] = ;            var value : Integer = gHotseatProfileTmp.color2;
      [*] = ;            if (elmName='arrowSliderLeft') then
      [*] = ;            value := value-1
      [*] = ;            else
      [*] = ;            value := value+1;
      [*] = ;            var maxValue : Integer = 15;
      [*] = ;            if (value>maxValue) then value := 0;
      [*] = ;            if (value<0) then value := maxValue;
      [*] = ;            _gui_SetSliderIntValue(elmSliderHandle, value, maxValue+1, '', true);
      [*] = ;            gHotseatProfileTmp.color2 := value;
      [*] = ;         end;
      [*] = ;         'avatar' : begin
      [*] = ;            var value : Integer = gHotseatProfileTmp.avatar;
      [*] = ;            if (elmName='arrowSliderLeft') then
      [*] = ;            value := value-1
      [*] = ;            else
      [*] = ;            value := value+1;
      [*] = ;            var maxValue : Integer = 20;
      [*] = ;            if (value>maxValue) then value := 1;
      [*] = ;            if (value<1) then value := maxValue;
      [*] = ;            _gui_SetSliderIntValue(elmSliderHandle, value, maxValue+1, '', true);
      [*] = ;            gHotseatProfileTmp.avatar := value;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      ExecuteState('ShowHotseatProfile');
      [*] = ;   end;
      [*] = ;
      [*] = ;   var tag : Integer = GetIntValueByName('Tag');
      [*] = ;   case tag of
      [*] = ;      cBtnAcceptTag, gc_gui_hotkey_btnEnter : begin
      [*] = ;         if (SaveProfileWindowInputBoxValues) then
      [*] = ;         begin
      [*] = ;            //_misc_AssignGlobalVars('gProfileTmp', 'gProfile');
      [*] = ;            _inet_AssignHotseatProfile(gHotseatProfileTmp, gArrHotseatProfiles[gIntRegister_ShardHotSeatActivePlayer]);
      [*] = ;            _gui_RootWindowRemoveWithFade(_gui_GetWindow('hotseatprofile'),gc_gui_FadeTime0_2);
      [*] = ;            ExecuteState('ShowNewGame');
      [*] = ;            //_gui_DelayExecuteStateOneInstance('ShowMenu', gc_gui_FadeTime0_2);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var elmInputboxText : Integer = GetGUIElementIndexByNameParent('hotseatprofile.name.text', _gui_GetLayerI());
      [*] = ;            var name : String = GetGUIElementText(elmInputboxText);
      [*] = ;            elmInputboxText := GetGUIElementIndexByNameParent('hotseatprofile.land.text', _gui_GetLayerI());
      [*] = ;            var land : String = GetGUIElementText(elmInputboxText);
      [*] = ;            if (name='') and (land='') then
      [*] = ;            _gui_ShowQuestionDialog('menu|87', 'EventHotseatProfile', 0, '', 0, False, False)
      [*] = ;            else
      [*] = ;            if (name='') then
      [*] = ;            _gui_ShowQuestionDialog('menu|85', 'EventHotseatProfile', 0, '', 0, False, False)
      [*] = ;            else
      [*] = ;            _gui_ShowQuestionDialog('menu|86', 'EventHotseatProfile', 0, '', 0, False, False);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      cBtnCancelTag, gc_gui_hotkey_btnEscape : begin
      [*] = ;         _gui_RootWindowRemoveWithFade(GetGUIElementIndexByNameParent('hotseatprofile', _gui_GetLayerI()),gc_gui_FadeTime0_2);
      [*] = ;         ExecuteState('ShowNewGame');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

