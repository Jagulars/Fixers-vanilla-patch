section.begin
   Name = ShowHotseatProfile
   Code : struct.begin
      [*] = ;var _log_name : String = 'MENU.INC\SHOWHOTSEATPROFILE';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var prevElmParentHandle : Integer = GetGUIElementIndexByNameParent('hotseatprofile', _gui_GetLayerI());
      [*] = ;var bVisible : Boolean = False;
      [*] = ;if (prevElmParentHandle<>0) and GetGUIElementVisible(prevElmParentHandle) then
      [*] = ;   bVisible := True;
      [*] = ;
      [*] = ;{var elmParentHandle : Integer = _gui_CreateCommonWindow('menu|5', '', 'Profile', 'halMiddle', 'valMiddle', 0, 0, 311+40, 562, false, false, false, 0, false);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('scroll_layer.background', elmParentHandle), 0.75);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('common_window_bkg', elmParentHandle), 0.65);}
      [*] = ;
      [*] = ;var resizerY : Integer = 20;
      [*] = ;
      [*] = ;var elmParentHandle : Integer = _gui_CreateLargeWindow(0, 'hotseatprofile', 'halParentMiddle', 'valParentMiddle', 0, 0, 344, 562+resizerY, true);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('background', elmParentHandle), 0.65);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('frame', elmParentHandle), 0.75);
      [*] = ;var elmHeaderHandle : Integer = GetGUIElementIndexByNameParent('header', elmParentHandle);
      [*] = ;SetGUIElementVisible(elmHeaderHandle, False);
      [*] = ;elmHeaderHandle := _gui_CreateImage('', elmParentHandle, 'element.header.strip.405', 'halParentMiddle', 'valParentTop', -1, -43, 0, 0, 0);
      [*] = ;var fontHandle : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_largest,'',fontHandle); // HeaderL
      [*] = ;var fontHandleInput : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Input',gc_gui_fontsize_default,'',fontHandleInput);
      [*] = ;var elmTextHandle : Integer = _gui_CreateText('', elmHeaderHandle, 'menu|5', 'halParentLeft', 'valParentTop', 0, 8, GetGUIElementWidth(elmHeaderHandle), GetGUIElementHeight(elmHeaderHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;var fontHandle2, fontHandlePassword : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'',fontHandle2);
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Password',gc_gui_fontsize_default,'',fontHandlePassword);
      [*] = ;
      [*] = ;const cMaxLength = 12;
      [*] = ;const cEventState = 'EventHotseatProfile';
      [*] = ;const cInputFieldHeight = 64;
      [*] = ;const cInputWidth = 307;//322;
      [*] = ;const cMaxNickLength = 16;
      [*] = ;const cMaxEmailLength = 64;
      [*] = ;var relativeMarginT : Integer = relativeMarginT+cInputFieldHeight;
      [*] = ;var r_pos : TRectangle;
      [*] = ;
      [*] = ;_sys_FillRect(r_pos,0, relativeMarginT, cInputWidth,0);
      [*] = ;var elmInputBox : Integer = _gui_CreateInputControl_VVK('name',elmParentHandle,gHotseatProfileTmp.name, gc_gui_align_parent_mt,false,r_pos,cMaxNickLength, cEventState, '');
      [*] = ;elmInputBox := GetGUIElementParentByIndex(elmInputBox);
      [*] = ;_gui_CreateText('', elmInputBox, 'gui|214', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmInputBox), GetGUIElementHeight(elmInputBox), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;
      [*] = ;// land
      [*] = ;relativeMarginT := relativeMarginT+cInputFieldHeight;
      [*] = ;_sys_FillRect(r_pos,0, relativeMarginT, cInputWidth,0);
      [*] = ;elmInputBox := _gui_CreateInputControl_VVK('land',elmParentHandle,gHotseatProfileTmp.land, gc_gui_align_parent_mt,false,r_pos,cMaxLength, cEventState, 'gui|215');
      [*] = ;elmInputBox := GetGUIElementParentByIndex(elmInputBox);
      [*] = ;_gui_CreateText('', elmInputBox, 'gui|215', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmInputBox), GetGUIElementHeight(elmInputBox), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;
      [*] = ;// shield with color1
      [*] = ;var cr, cg, cb, ca : Float = 1;
      [*] = ;var elmSliderHandle : Integer = _gui_CreateSimpleIntSlider('sign', elmParentHandle, 'halParentMiddle', 'valParentTop', 0, 120+50+resizerY, 45, cEventState, '', 1);
      [*] = ;_gui_SetSliderIntValue(elmSliderHandle, gHotseatProfileTmp.sign, 26, '', true);
      [*] = ;var elmHerbHandle : Integer = _gui_CreateHerb('', elmSliderHandle, gHotseatProfileTmp.sign, gHotseatProfileTmp.color1, gHotseatProfileTmp.color2, 'halParentMiddle', 'valParentTop', 0, -5);
      [*] = ;
      [*] = ;// color1
      [*] = ;elmSliderHandle := _gui_CreateSimpleIntSlider('color1', elmParentHandle, 'halParentMiddle', 'valParentTop', -117+18, 120+50+resizerY, 14, cEventState, '', 1);
      [*] = ;_gui_SetSliderIntValue(elmSliderHandle, gHotseatProfileTmp.color1, 16, '', true);
      [*] = ;var elmHandle : Integer = _gui_CreateImage('', elmSliderHandle, 'pixel.255.255.255', 'halParentMiddle', 'valParentTop', 0, 9, 20, 20, 0);
      [*] = ;_gui_GetHerbColorByIndex(gHotseatProfileTmp.color1, cr, cg, cb);
      [*] = ;SetGUIElementUserColor(elmHandle, cr, cg, cb, ca);
      [*] = ;SetGUIElementUseUserColor(elmHandle, True);
      [*] = ;
      [*] = ;// color2
      [*] = ;elmSliderHandle := _gui_CreateSimpleIntSlider('color2', elmParentHandle, 'halParentMiddle', 'valParentTop', 117-18, 120+50+resizerY, 14, cEventState, '', 1);
      [*] = ;_gui_SetSliderIntValue(elmSliderHandle, gHotseatProfileTmp.color2, 16, '', true);
      [*] = ;elmHandle := _gui_CreateImage('', elmSliderHandle, 'pixel.255.255.255', 'halParentMiddle', 'valParentTop', 0, 9, 20, 20, 0);
      [*] = ;_gui_GetHerbColorByIndex(gHotseatProfileTmp.color2, cr, cg, cb);
      [*] = ;SetGUIElementUserColor(elmHandle, cr, cg, cb, ca);
      [*] = ;SetGUIElementUseUserColor(elmHandle, True);
      [*] = ;
      [*] = ;// portrait
      [*] = ;var portrait : String = 'astral.dialog.portrait.'+IntToStr(gHotseatProfileTmp.avatar-1);
      [*] = ;var elmPortaitWindow : Integer = _gui_CreateSmallWindow(elmParentHandle, 'portraitwindow', 'halParentMiddle', 'valParentTop', 0, 260+resizerY, GetGUITextureWidth(portrait), GetGUITextureHeight(portrait), false);
      [*] = ;elmSliderHandle := _gui_CreateSimpleIntSlider('avatar', elmPortaitWindow, 'halParentMiddle', 'valParentTop', 0, 101, 314, cEventState, '', 0);
      [*] = ;var elmPortraitHandle : Integer = _gui_CreateImage('', elmSliderHandle, portrait, 'halParentMiddle', 'valParentTop', 0, -(GetGUITextureWidth(portrait) div 2)+2, 0, 0, 0);
      [*] = ;
      [*] = ;// buttons (choose another profile, ok)
      [*] = ;const cBtnAcceptTag = 100;
      [*] = ;const cBtnCancelTag = 102;
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'mainpanel.btnplace.with.frame', 'halParentMiddle', 'valParentBottom', 82, -32, 0, 0, 0);
      [*] = ;var elmBtnHandle : Integer = _gui_CreateButton('btnCancel', elmHandle, '', 'mainpanel.btn.cancel', 'halParentLeft', 'valParentTop', 39, 0, 0, 0, cEventState, 'gui|211', cBtnCancelTag);
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'mainpanel.btnplace.with.frame', 'halParentMiddle', 'valParentBottom', -82, -32, 0, 0, 0);
      [*] = ;elmBtnHandle := _gui_CreateButton('btnAccept', elmHandle, '', 'mainpanel.btn.accept', 'halParentLeft', 'valParentTop', 39, 0, 0, 0, cEventState, 'map.event|28.1', cBtnAcceptTag);
      [*] = ;
      [*] = ;if (not bVisible) then
      [*] = ;_gui_FadeElement(elmParentHandle, gc_gui_FadeTime0_2, true, true, true);
      [*] = ;
      [*] = ;_gui_RootWindowAdd(elmParentHandle,cRootWindowModal);
      [*] = ;SetGUIElementPressState(elmParentHandle, cEventState);
      [*] = ;ExecuteState('GUIInvokeMouseMove');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

