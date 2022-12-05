section.begin
   Name = ShowProfile
   Code : struct.begin
      [*] = ;var _log_name : String = 'MENU.INC\SHOWPROFILE';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var prevElmParentHandle : Integer = _gui_GetWindow('Profile');
      [*] = ;var bVisible : Boolean = False;
      [*] = ;if (prevElmParentHandle<>0) and GetGUIElementVisible(prevElmParentHandle) then
      [*] = ;   bVisible := True;
      [*] = ;
      [*] = ;{var elmParentHandle : Integer = _gui_CreateCommonWindow('menu|5', '', 'Profile', 'halMiddle', 'valMiddle', 0, 0, 311+40, 562, false, false, false, 0, false);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('scroll_layer.background', elmParentHandle), 0.75);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('common_window_bkg', elmParentHandle), 0.65);}
      [*] = ;
      [*] = ;var elmParentHandle : Integer = _gui_CreateLargeWindow(0, 'Profile', 'halParentMiddle', 'valParentMiddle', 0, 0, 344, 612, true);
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
      [*] = ;
      [*] = ;const cMaxLength = 16;
      [*] = ;const cEventState = 'EventProfile';
      [*] = ;var r_pos : TRectangle;
      [*] = ;_sys_FillRect(r_pos,0,34,404-97+10,0);
      [*] = ;_gui_CreateInputControl_VVK('name',elmParentHandle, gProfileTmp.name, gc_gui_align_parent_mt,true,r_pos,cMaxLength, cEventState, 'gui|214');
      [*] = ;r_pos.pos.y := r_pos.pos.y + 40;
      [*] = ;_gui_CreateInputControl_VVK('land',elmParentHandle, gProfileTmp.land, gc_gui_align_parent_mt,true,r_pos,cMaxLength, cEventState, 'gui|215');
      [*] = ;
      [*] = ;
      [*] = ;const cBtnAcceptTag = 100;
      [*] = ;const cBtnOtherProfileTag = 101;
      [*] = ;const cBtnCancelTag = 102;
      [*] = ;const cBtnCustomDifficultyTag = 103;
      [*] = ;const cBtnAchievementsTag = 104;
      [*] = ;
      [*] = ;// difficulty
      [*] = ;var hint : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_small,'',fontHandle); // NormalL
      [*] = ;hint := GetLocaleTableListItemByID('gui', '218')+gc_gui_BreakLine+gc_gui_BreakLine+GetLocaleTableListItemByID('menu', '36');
      [*] = ;var elmSliderHandle : Integer = _gui_CreateIntSlider('difficulty', elmParentHandle, 'halParentMiddle', 'valParentTop', 0, 184-70, 228, cEventState, hint, 49, 3, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;var intValue : Integer = gProfileTmp.advdiff.basediff;
      [*] = ;var text : String = 'difficulty|'+IntToStr(intValue);
      [*] = ;if (gProfileTmp.advdiff.custom) then
      [*] = ;text := 'gui|767';
      [*] = ;_gui_SetSliderIntValue(elmSliderHandle, intValue, 7, text, false);
      [*] = ;
      [*] = ;var elmBtnHandle : Integer = _gui_CreateButton('btnCustomDifficulty', elmSliderHandle, '', 'tempshell.journal', 'halParentRight', 'valParentMiddle', -66+8, -4, 27, 27, cEventState, 'gui|806', cBtnCustomDifficultyTag);
      [*] = ;
      [*] = ;// shield with color1
      [*] = ;var cr, cg, cb, ca : Float = 1;
      [*] = ;elmSliderHandle := _gui_CreateSimpleIntSlider('sign', elmParentHandle, 'halParentMiddle', 'valParentTop', 0, 120+50, 45, cEventState, '', 1);
      [*] = ;_gui_SetSliderIntValue(elmSliderHandle, gProfileTmp.sign, 26, '', true);
      [*] = ;var elmHerbHandle : Integer = _gui_CreateHerb('', elmSliderHandle, gProfileTmp.sign, gProfileTmp.color1, gProfileTmp.color2, 'halParentMiddle', 'valParentTop', 0, -5);
      [*] = ;
      [*] = ;// color1
      [*] = ;elmSliderHandle := _gui_CreateSimpleIntSlider('color1', elmParentHandle, 'halParentMiddle', 'valParentTop', -117+18, 120+50, 14, cEventState, '', 1);
      [*] = ;_gui_SetSliderIntValue(elmSliderHandle, gProfileTmp.color1, 16, '', true);
      [*] = ;var elmHandle : Integer = _gui_CreateImage('', elmSliderHandle, 'pixel.255.255.255', 'halParentMiddle', 'valParentTop', 0, 9, 20, 20, 0);
      [*] = ;_gui_GetHerbColorByIndex(gProfileTmp.color1, cr, cg, cb);
      [*] = ;SetGUIElementUserColor(elmHandle, cr, cg, cb, ca);
      [*] = ;SetGUIElementUseUserColor(elmHandle, True);
      [*] = ;
      [*] = ;// color2
      [*] = ;elmSliderHandle := _gui_CreateSimpleIntSlider('color2', elmParentHandle, 'halParentMiddle', 'valParentTop', 117-18, 120+50, 14, cEventState, '', 1);
      [*] = ;_gui_SetSliderIntValue(elmSliderHandle, gProfileTmp.color2, 16, '', true);
      [*] = ;elmHandle := _gui_CreateImage('', elmSliderHandle, 'pixel.255.255.255', 'halParentMiddle', 'valParentTop', 0, 9, 20, 20, 0);
      [*] = ;_gui_GetHerbColorByIndex(gProfileTmp.color2, cr, cg, cb);
      [*] = ;SetGUIElementUserColor(elmHandle, cr, cg, cb, ca);
      [*] = ;SetGUIElementUseUserColor(elmHandle, True);
      [*] = ;
      [*] = ;// portrait
      [*] = ;var portrait : String = 'astral.dialog.portrait.'+IntToStr(gProfileTmp.avatar-1);
      [*] = ;var elmPortaitWindow : Integer =_gui_CreateSmallWindow(elmParentHandle, 'portraitwindow', 'halParentMiddle', 'valParentTop', 0, 260, GetGUITextureWidth(portrait), GetGUITextureHeight(portrait), false);
      [*] = ;elmSliderHandle := _gui_CreateSimpleIntSlider('avatar', elmPortaitWindow, 'halParentMiddle', 'valParentTop', 0, 101, 314, cEventState, '', 0);
      [*] = ;var elmPortraitHandle : Integer = _gui_CreateImage('', elmSliderHandle, portrait, 'halParentMiddle', 'valParentTop', 0, -(GetGUITextureWidth(portrait) div 2)+2, 0, 0, 0);
      [*] = ;
      [*] = ;// achievements
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmParentHandle, '', 'common.btn', 'halParentMiddle', 'valParentBottom', 0, -80, 0, 0, cEventState, '', cBtnAchievementsTag);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, 'gui|279', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;
      [*] = ;// buttons (choose another profile, ok)
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'mainpanel.btnplace.with.frame', 'halParentMiddle', 'valParentBottom', 82, -32, 0, 0, 0);
      [*] = ;elmBtnHandle := _gui_CreateButton('btnCancel', elmHandle, '', 'mainpanel.btn.cancel', 'halParentLeft', 'valParentTop', 39, 0, 0, 0, cEventState, 'gui|211', cBtnCancelTag);
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'mainpanel.btnplace.with.frame', 'halParentMiddle', 'valParentBottom', -82, -32, 0, 0, 0);
      [*] = ;elmBtnHandle := _gui_CreateButton('btnAccept', elmHandle, '', 'mainpanel.btn.accept', 'halParentLeft', 'valParentTop', 39, 0, 0, 0, cEventState, 'map.event|28.1', cBtnAcceptTag);
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, gc_gui_material_blank_0{'mainpanel.btnplace.with.frame'}, 'halParentMiddle', 'valParentBottom', 0, -32, 0, 0, 0);
      [*] = ;elmBtnHandle := _gui_CreateButton('btnOtherProfile', elmHandle, '', 'map.castle.tabs.btn.provincelist', 'halParentLeft', 'valParentTop', -25, 0, 0, 0, cEventState, 'gui|349', cBtnOtherProfileTag);
      [*] = ;
      [*] = ;if (not bVisible) then
      [*] = ;_gui_FadeElement(elmParentHandle, gc_gui_FadeTime0_2, true, true, true);
      [*] = ;
      [*] = ;_gui_RootWindowAddM(elmParentHandle);
      [*] = ;SetGUIElementPressState(elmParentHandle, cEventState);
      [*] = ;SetGUIEventStateOnKeyDown(cEventState);
      [*] = ;ExecuteState('GUIInvokeMouseMove');
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

