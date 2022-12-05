section.begin
   Name = ShowInternetShellProfile
   Code : struct.begin
      [*] = ;
      [*] = ;function CreateInputBox(InputBoxID : String; parentElement : Integer; text, hAlign, vAlign : String; posX, posY, inputWidth, maxLength : Integer; eventState, hint : String; tPosX, tPosY : Integer; thAlign, tvAlign, font : String; r, g, b, a : Float) : Integer;
      [*] = ;begin
      [*] = ;   var elmInputBoxHandle : Integer = _gui_CreateImage(InputBoxID, parentElement, gc_gui_material_blank_0, hAlign, vAlign, posX, posY, inputWidth, 45, 0);
      [*] = ;   //SetGUIElementPressState(elmInputBoxHandle, eventState);
      [*] = ;   SetGUIElementStringTag(elmInputBoxHandle, InputBoxID);
      [*] = ;   var elmHandle : Integer = _gui_CreateImage('', elmInputBoxHandle, 'common.slider.left.end', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;   elmHandle := _gui_CreateImage('', elmInputBoxHandle, 'common.slider.right.end', 'halParentLeft', 'valParentTop', inputWidth-GetGUITextureWidth('common.slider.right.end'), 0, 0, 0, 0);
      [*] = ;   elmHandle := _gui_CreateScrollLayer(elmInputBoxHandle, 'common.slider.middle', 'halParentLeft', 'valParentTop', GetGUITextureWidth('common.slider.left.end'), 0, inputWidth-GetGUITextureWidth('common.slider.left.end')-GetGUITextureWidth('common.slider.right.end'), 0);
      [*] = ;
      [*] = ;   var elmInputTextHnd : Integer = AddNewElementByClassNameParent('text', 'TXEditControl', 0, elmInputBoxHandle);
      [*] = ;   SetGUIElementMaxTextLength(elmInputTextHnd, maxLength);
      [*] = ;   SetGUIElementHint(elmInputTextHnd, hint);
      [*] = ;   SetGUIElementPressState(elmInputTextHnd, eventState);
      [*] = ;   SetGUIElementFont(elmInputTextHnd, font);
      [*] = ;   SetGUIElementColor(elmInputTextHnd, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;   SetGUIElementAlign(elmInputTextHnd, 'halParentLeft', 'valParentTop');
      [*] = ;   SetGUIElementAllPositionRect(elmInputTextHnd, tPosX, tPosY, inputWidth-72, 35);
      [*] = ;   SetGUIElementTextAlign(elmInputTextHnd, 'halMiddle', 'valMiddle', 0, 0);
      [*] = ;   SetGUIElementText(elmInputTextHnd, text);
      [*] = ;   SetGUIElementTextFormatted(elmInputTextHnd, True);
      [*] = ;   SetGUIElementCursorByIndex(elmInputTextHnd, 6);
      [*] = ;
      [*] = ;   Result := elmInputBoxHandle;
      [*] = ;end;
      [*] = ;
      [*] = ;var prevElmParentHandle : Integer = GetGUIElementIndexByNameParent('shellprofile', _gui_GetLayerI());
      [*] = ;var bVisible : Boolean = False;
      [*] = ;if (prevElmParentHandle<>0) and GetGUIElementVisible(prevElmParentHandle) then
      [*] = ;bVisible := True;
      [*] = ;
      [*] = ;{var elmParentHandle : Integer = _gui_CreateCommonWindow('menu|5', '', 'Profile', 'halMiddle', 'valMiddle', 0, 0, 311+40, 562, false, false, false, 0, false);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('scroll_layer.background', elmParentHandle), 0.75);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('common_window_bkg', elmParentHandle), 0.65);}
      [*] = ;
      [*] = ;var resizerY : Integer = 80;
      [*] = ;
      [*] = ;var elmParentHandle : Integer = _gui_CreateLargeWindow(0, 'shellprofile', 'halParentMiddle', 'valParentMiddle', 0, 0, 344, 562+resizerY, true);
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
      [*] = ;const cEventState = 'EventInternetShellProfile';
      [*] = ;// name [inputbox]
      [*] = ;// var elmInputBoxHandle : Integer = CreateInputBox('name', elmParentHandle, gProfileTmp.name, 'halParentMiddle', 'valParentTop', 0, 34, 324-97+10, cMaxLength, cEventState, 'gui|214', 36, 2, 'halLeft', 'valMiddle', fontHandleInput, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;// nickname
      [*] = ;const cInputFieldHeight = 64;
      [*] = ;const cInputWidth = 237;//322;
      [*] = ;const cMaxNickLength = 16;
      [*] = ;const cMaxEmailLength = 64;
      [*] = ;var relativeMarginT : Integer = relativeMarginT+cInputFieldHeight;
      [*] = ;var elmInputBox : Integer = CreateInputBox('nickname', elmParentHandle, gInetProfileTmp.name, 'halParentMiddle', 'valParentTop', 0, relativeMarginT, cInputWidth, cMaxNickLength, cEventState, '', 36, 2, 'halLeft', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;var elmTextInputBox : Integer = GetGUIElementIndexByNameParent('text', elmInputBox);
      [*] = ;elmTextHandle := _gui_CreateText('', elmInputBox, 'menu|185', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmInputBox), GetGUIElementHeight(elmInputBox), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;//SetGUIElementFocusedHandle(elmTextInputBox);
      [*] = ;
      [*] = ;// password
      [*] = ;relativeMarginT := relativeMarginT+cInputFieldHeight;
      [*] = ;elmInputBox := CreateInputBox('password', elmParentHandle, gInetProfileTmp.netpass, 'halParentMiddle', 'valParentTop', 0, relativeMarginT, cInputWidth, cMaxEmailLength, cEventState, '', 36, 2, 'halLeft', 'valMiddle', fontHandlePassword, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;elmTextInputBox := GetGUIElementIndexByNameParent('text', elmInputBox);
      [*] = ;elmTextHandle := _gui_CreateText('', elmInputBox, 'menu|186', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmInputBox), GetGUIElementHeight(elmInputBox), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;
      [*] = ;// confirmpassword
      [*] = ;relativeMarginT := relativeMarginT+cInputFieldHeight;
      [*] = ;elmInputBox := CreateInputBox('confirmpassword', elmParentHandle, gInetProfileTmp.netpass, 'halParentMiddle', 'valParentTop', 0, relativeMarginT, cInputWidth, cMaxEmailLength, cEventState, '', 36, 2, 'halLeft', 'valMiddle', fontHandlePassword, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;elmTextInputBox := GetGUIElementIndexByNameParent('text', elmInputBox);
      [*] = ;elmTextHandle := _gui_CreateText('', elmInputBox, 'menu|187', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmInputBox), GetGUIElementHeight(elmInputBox), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;
      [*] = ;// shield with color1
      [*] = ;var cr, cg, cb, ca : Float = 1;
      [*] = ;var elmSliderHandle : Integer = _gui_CreateSimpleIntSlider('sign', elmParentHandle, 'halParentMiddle', 'valParentTop', 0, 120+50+resizerY, 45, cEventState, '', 1);
      [*] = ;_gui_SetSliderIntValue(elmSliderHandle, gInetProfileTmp.sign, 26, '', true);
      [*] = ;var elmHerbHandle : Integer = _gui_CreateHerb('', elmSliderHandle, gInetProfileTmp.sign, gInetProfileTmp.color1, gInetProfileTmp.color2, 'halParentMiddle', 'valParentTop', 0, -5);
      [*] = ;
      [*] = ;// color1
      [*] = ;elmSliderHandle := _gui_CreateSimpleIntSlider('color1', elmParentHandle, 'halParentMiddle', 'valParentTop', -117+18, 120+50+resizerY, 14, cEventState, '', 1);
      [*] = ;_gui_SetSliderIntValue(elmSliderHandle, gInetProfileTmp.color1, 16, '', true);
      [*] = ;var elmHandle : Integer = _gui_CreateImage('', elmSliderHandle, 'pixel.255.255.255', 'halParentMiddle', 'valParentTop', 0, 9, 20, 20, 0);
      [*] = ;_gui_GetHerbColorByIndex(gInetProfileTmp.color1, cr, cg, cb);
      [*] = ;SetGUIElementUserColor(elmHandle, cr, cg, cb, ca);
      [*] = ;SetGUIElementUseUserColor(elmHandle, True);
      [*] = ;
      [*] = ;// color2
      [*] = ;elmSliderHandle := _gui_CreateSimpleIntSlider('color2', elmParentHandle, 'halParentMiddle', 'valParentTop', 117-18, 120+50+resizerY, 14, cEventState, '', 1);
      [*] = ;_gui_SetSliderIntValue(elmSliderHandle, gInetProfileTmp.color2, 16, '', true);
      [*] = ;elmHandle := _gui_CreateImage('', elmSliderHandle, 'pixel.255.255.255', 'halParentMiddle', 'valParentTop', 0, 9, 20, 20, 0);
      [*] = ;_gui_GetHerbColorByIndex(gInetProfileTmp.color2, cr, cg, cb);
      [*] = ;SetGUIElementUserColor(elmHandle, cr, cg, cb, ca);
      [*] = ;SetGUIElementUseUserColor(elmHandle, True);
      [*] = ;
      [*] = ;// portrait
      [*] = ;var portrait : String = 'astral.dialog.portrait.'+IntToStr(gInetProfileTmp.avatar-1);
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
      [*] = ;{
      [*] = ;var myInfo : String = LanPublicServerProfInfo;
      [*] = ;var color1, color2, sign, avatar : Integer = 0;
      [*] = ;if (myInfo='') then
      [*] = ;begin
      [*] = ;   color1 := floor(Random*gc_MaxHerbColor);
      [*] = ;   color2 := floor(Random*gc_MaxHerbColor);
      [*] = ;   sign := floor(Random*gc_MaxHerbSign);
      [*] = ;   avatar := 1+floor(Random*20);
      [*] = ;end;
      [*] = ;
      [*] = ;gInetProfile.color1 := color1;
      [*] = ;gInetProfile.color2 := color2;
      [*] = ;gInetProfile.sign := sign;
      [*] = ;gInetProfile.avatar := avatar;
      [*] = ;
      [*] = ;var newInfo : String = IntToStr(color1)+gc_gui_DelimiterCharStr+IntToStr(color2)+gc_gui_DelimiterCharStr+IntToStr(sign)+gc_gui_DelimiterCharStr+IntToStr(avatar);
      [*] = ;LanSetMyProfInfo(newInfo);
      [*] = ;
      [*] = ;// sign1
      [*] = ;// herbcolor1
      [*] = ;// herbcolor2
      [*] = ;// avatar
      [*] = ;
      [*] = ;// buttons
      [*] = ;// accept
      [*] = ;// cancel
   struct.end
section.end

