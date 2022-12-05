section.begin
   Name = ShowTutorial
   Description : struct.begin
      [*] = ;IntRegister0 - index of tutorial message
   struct.end
   Code : struct.begin
      [*] = ;var ind : Integer = IntRegister0;
      [*] = ;
      [*] = ;var _log_name : String = 'COMMON.INC\SHOWTUTORIAL';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;var _log : Boolean = true;
      [*] = ;
      [*] = ;// _gui_CreateSmallWindow
      [*] = ;//
      [*] = ;function _gui_MODIFIED_CreateSmallWindow(parent : Integer; elementName, hAlign, vAlign : String; posX, posY, sizeX, sizeY : Integer; modal : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   procedure ResizeTextureToWidth(elmHandle : Integer; elementName : String; width : Integer);
      [*] = ;   begin
      [*] = ;      var elmBackgroundHandle : Integer = GetGUIElementIndexByNameParent('material', elmHandle);
      [*] = ;      if (elmBackgroundHandle<>0) then
      [*] = ;      begin
      [*] = ;         var texWidth : Integer = GetGUITextureWidth(GetGUIElementMaterial(elmBackgroundHandle));
      [*] = ;         if (width>texWidth) then
      [*] = ;         SetGUIElementWidth(elmBackgroundHandle, width);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var elmMyParent : Integer;
      [*] = ;   if (parent=0) or (modal) then
      [*] = ;      elmMyParent := _gui_GetLayerI()
      [*] = ;   else
      [*] = ;      elmMyParent := parent;
      [*] = ;   var elmParentHandle : Integer = _gui_GetOrCreateElementExtAsImage(elementName, elmMyParent, hAlign, vAlign, posX, posY, sizeX, sizeY, 0);
      [*] = ;   var elmBackgroundHandle : Integer = _gui_GetOrCreateElementExtAsImage('background', elmParentHandle, 'halParentLeft', 'valParentTop', 0, 0, sizeX, sizeY, 0);
      [*] = ;   var elmFrameHandle : Integer = _gui_GetOrCreateElementExtAsImage('frame', elmParentHandle, 'halParentLeft', 'valParentTop', 0, 0, sizeX, sizeY, 0);
      [*] = ;   if (modal) then
      [*] = ;      _gui_RootWindowAddM(elmParentHandle);
      [*] = ;
      [*] = ;   var elmHandle : Integer = _gui_CreateImage('', elmBackgroundHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, sizeX, sizeY, 0);
      [*] = ;   SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;   elmHandle := _gui_CreateScrollLayer(elmBackgroundHandle, 'common.window.background', 'halParentLeft', 'valParentTop', 0, 0, sizeX, sizeY);
      [*] = ;   ResizeTextureToWidth(elmHandle, 'material', sizeX);
      [*] = ;
      [*] = ;   elmHandle := _gui_CreateScrollLayer(elmFrameHandle, 'gamepanel03.snapshot.border.top', 'halParentLeft', 'valParentTop', 0, -11, sizeX, 0);
      [*] = ;   elmHandle := _gui_CreateScrollLayer(elmFrameHandle, 'gamepanel03.snapshot.border.bottom', 'halParentLeft', 'valParentBottom', 0, 0, sizeX, 0);
      [*] = ;   elmHandle := _gui_CreateScrollLayer(elmFrameHandle, 'gamepanel03.snapshot.border.left', 'halParentLeft', 'valParentTop', -11, 0, 0, sizeY);
      [*] = ;   elmHandle := _gui_CreateScrollLayer(elmFrameHandle, 'gamepanel03.snapshot.border.right', 'halParentRight', 'valParentTop', 0, 0, 0, sizeY);
      [*] = ;   //elmHandle := _gui_CreateImage('', elmFrameHandle, 'gamepanel03.snapshot.decor.top', 'halParentMiddle', 'valParentTop', 0, -3-GetGUITextureHeight('gamepanel03.snapshot.decor.top'), 0, 0, 0);
      [*] = ;   //elmHandle := _gui_CreateImage('', elmFrameHandle, 'gamepanel03.snapshot.decor.bottom', 'halParentMiddle', 'valParentBottom', 0, 3, 0, 0, 0);
      [*] = ;   //elmHandle := _gui_CreateImage('', elmFrameHandle, 'gamepanel03.snapshot.decor.left', 'halParentLeft', 'valParentMiddle', -GetGUITextureWidth('gamepanel03.snapshot.decor.left'), 0, 0, 0, 0);
      [*] = ;   //elmHandle := _gui_CreateImage('', elmFrameHandle, 'gamepanel03.snapshot.decor.right', 'halParentRight', 'valParentMiddle', 0, 0, 0, 0, 0);
      [*] = ;   elmHandle := _gui_CreateImage('', elmFrameHandle, 'gamepanel03.snapshot.corner.top.left', 'halParentLeft', 'valParentTop', -18, -33, 0, 0, 0);
      [*] = ;   elmHandle := _gui_CreateImage('', elmFrameHandle, 'gamepanel03.snapshot.corner.top.right', 'halParentRight', 'valParentTop', -48, -33, 0, 0, 0);
      [*] = ;   elmHandle := _gui_CreateImage('', elmFrameHandle, 'gamepanel03.snapshot.corner.bottom.left', 'halParentLeft', 'valParentBottom', -18, -12, 0, 0, 0);
      [*] = ;   elmHandle := _gui_CreateImage('', elmFrameHandle, 'gamepanel03.snapshot.corner.bottom.right', 'halParentRight', 'valParentBottom', -48, -12, 0, 0, 0);
      [*] = ;
      [*] = ;   Result := elmParentHandle;
      [*] = ;end;
      [*] = ;
      [*] = ;function AddTutorialHistory(hintIndex : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := -1;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to gc_MaxTutorialHistory-1 do
      [*] = ;   begin
      [*] = ;      if (gArrTutorialHistory[i]=0) then
      [*] = ;      begin
      [*] = ;         gArrTutorialHistory[i] := hintIndex;
      [*] = ;         Result := i;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetTutorialLastIndex() : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=1 to gc_MaxTutorialHistory-1 do
      [*] = ;   begin
      [*] = ;      if (gArrTutorialHistory[i]=0) then
      [*] = ;      begin
      [*] = ;         Result := i-1;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetTutorialExist(hintIndex : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := -1;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to gc_MaxTutorialHistory-1 do
      [*] = ;   begin
      [*] = ;      if round(Abs(gArrTutorialHistory[i]))=round(Abs(hintIndex)) then
      [*] = ;      begin
      [*] = ;         Result := i;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure ClearTutorialHistory();
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to gc_MaxTutorialHistory-1 do
      [*] = ;      gArrTutorialHistory[i] := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gGame.gameType = gc_GameTypeCampaign) and (gProfile.mestutor or gTutorial.map) and (ind<>0) then
      [*] = ;begin
      [*] = ;   gIntRegister_TutCurCastleMode := gIntRegister_GUICurCastleMode;
      [*] = ;   gIntRegister_TutCurCastleTabMode := gIntRegister_GUICurCastleTabMode;
      [*] = ;   gIntRegister_TutCurHeroMode := gIntRegister_GUICurHeroMode;
      [*] = ;
      [*] = ;   if _log then _Log_gui(_log_name+': '+ IntToStr(ind)+' TutorialHistoryIndex='+IntToStr(gIntRegister_TutorialHistoryIndex));
      [*] = ;   ind := round(Abs(ind));
      [*] = ;   var tutorialText : String = GetLocaleTableListItemByID('tutorial', IntToStr(ind)+'.description');
      [*] = ;   StringRegister0 := tutorialText;
      [*] = ;   MapExecuteState('StringReplaceParams');
      [*] = ;   tutorialText := StringRegister1;
      [*] = ;
      [*] = ;   // Check if window was already visible, then no need to FadeIn it when show again
      [*] = ;   var prevElmParentHandle : Integer = GetGUIElementIndexByNameParent('showtutorial', _gui_GetLayer(cTutorialLayer));
      [*] = ;   var bVisible : Boolean = False;
      [*] = ;   if (prevElmParentHandle<>0) and GetGUIElementVisible(prevElmParentHandle) then
      [*] = ;      bVisible := True;
      [*] = ;
      [*] = ;   var fontHandle : String;
      [*] = ;   _gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'',fontHandle);
      [*] = ;
      [*] = ;   var elmParentHandle : Integer = _gui_GetOrCreateElementExtAsImage('showtutorial', _gui_GetLayer(cTutorialLayer), 'halParentLeft', 'valParentTop', 0, 0, GetViewerWidth, GetViewerHeight, 0);
      [*] = ;   SetGUIElementStringTag(elmParentHandle, IntToStr(ind));
      [*] = ;
      [*] = ;   const cTextMarginLeft = 14;
      [*] = ;   const cTextMarginTop = 12;
      [*] = ;   const cImageMarginLeft = 0;
      [*] = ;   const cImageMarginTop = 0;
      [*] = ;   const cWrapWidthMin = 350;
      [*] = ;   const cWrapWidthMax = 350;
      [*] = ;   const cWrapHeightMin = 58+24;
      [*] = ;   const cWrapWidthScreenPercent = 0.2;
      [*] = ;   var wrapWidth : Integer = round(cWrapWidthScreenPercent*GetViewerWidth);
      [*] = ;   if (wrapWidth<cWrapWidthMin) then
      [*] = ;      wrapWidth := cWrapWidthMin
      [*] = ;   else
      [*] = ;      if (wrapWidth>cWrapWidthMax) then
      [*] = ;         wrapWidth := cWrapWidthMax;
      [*] = ;   var wrappedText : String = GetGUIWrappedTextFormatByFont(fontHandle, tutorialText, wrapWidth);
      [*] = ;   var width, height : Integer;
      [*] = ;   GetGUIElementFontTextFormatRect(fontHandle, wrappedText, width, height);
      [*] = ;   if (height<cWrapHeightMin) then
      [*] = ;      height := cWrapHeightMin;
      [*] = ;
      [*] = ;   var elmTooltipHandle : Integer = _gui_MODIFIED_CreateSmallWindow(elmParentHandle, 'smallwindow', 'halParentLeft', 'valParentTop', 24+18, 24+9, wrapWidth+cTextMarginLeft*2, height+cTextMarginTop*2, False);
      [*] = ;   //var elmHandle : Integer = _gui_CreateCommonWindow('', tutorialText, '', 'halParentLeft', 'valParentTop', 18, 18, 0, 0, False, False, False, 6, True);
      [*] = ;   //AttachGUIElementToElement(elmHandle, tmp);
      [*] = ;   //SetGUIElementPosition(elmHandle, 0, 0);
      [*] = ;   //const cBtnClose = 100;
      [*] = ;   //const cEventState = 'EventTutorial';
      [*] = ;   //_gui_CreateButton('button', elmHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmHandle)+16, GetGUIElementHeight(elmHandle) div 2, cEventState, 'menu|47', cBtnClose);
      [*] = ;
      [*] = ;   var elmHandle : Integer = _gui_CreateImage('background', elmTooltipHandle, 'common.tooltip.new.background', 'halParentLeft', 'valParentTop', cImageMarginLeft, cImageMarginTop, wrapWidth+cTextMarginLeft*2, height+cTextMarginTop*2, 0);
      [*] = ;   _gui_CreateText('text', elmHandle, wrappedText, 'halParentLeft', 'valParentTop', cTextMarginLeft, cTextMarginTop, wrapWidth, height, 'halLeft', 'valTop', fontHandle, gc_gui_fontcolor_NormalDarkR, gc_gui_fontcolor_NormalDarkG, gc_gui_fontcolor_NormalDarkB, 1);
      [*] = ;
      [*] = ;   const cBtnClose = 100;
      [*] = ;   const cEventState = 'EventTutorial';
      [*] = ;   _gui_CreateButton('button', elmHandle, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, wrapWidth+cTextMarginLeft*2, height+cTextMarginTop*2, cEventState, 'menu|47', cBtnClose);
      [*] = ;
      [*] = ;   //var elmSliderHandle : Integer = _gui_CreateSimpleIntSlider('history', elmTooltipHandle, 'halParentLeft', 'valParentMiddle', -41, gIntRegister_dbgY, GetGUIElementWidth(elmTooltipHandle)+82, cEventState, '', 0);
      [*] = ;   elmHandle := _gui_CreateImage('', elmTooltipHandle, 'gamepanel03.snapshot.decor.left', 'halParentLeft', 'valParentTop', -GetGUITextureWidth('gamepanel03.snapshot.decor.left'), -20+gIntRegister_dbgZ, 0, 0, 0);
      [*] = ;   elmHandle := _gui_CreateImage('', elmTooltipHandle, 'gamepanel03.snapshot.decor.right', 'halParentRight', 'valParentTop', 0, -20+gIntRegister_dbgZ, 0, 0, 0);
      [*] = ;   var elmSliderHandle : Integer = _gui_CreateSimpleIntSlider('history', elmTooltipHandle, 'halParentLeft', 'valParentTop', -41, 20+gIntRegister_dbgZ, GetGUIElementWidth(elmTooltipHandle)+82, cEventState, '', 0);
      [*] = ;
      [*] = ;   if (not bVisible) then
      [*] = ;      _gui_FadeElement(elmParentHandle, gc_gui_FadeTime0_2, true, true, false)
      [*] = ;   else
      [*] = ;      SetGUIElementFadeStart(elmParentHandle, False);
      [*] = ;   //_gui_FadeElement(elmParentHandle, 0, true, true, false);
      [*] = ;
      [*] = ;   gIntRegister_TutorialCurrentHint := ind;
      [*] = ;   if (ind<>0) then
      [*] = ;   begin
      [*] = ;      var existIndex : Integer = GetTutorialExist(ind);
      [*] = ;      if (existIndex=-1) then
      [*] = ;      begin
      [*] = ;         var newIndex : Integer = AddTutorialHistory(gIntRegister_TutorialCurrentHint);
      [*] = ;         gIntRegister_TutorialHistoryIndex := newIndex;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         gIntRegister_TutorialHistoryIndex := existIndex;
      [*] = ;
      [*] = ;      var lastHistoryIndex : Integer = GetTutorialLastIndex();
      [*] = ;      var elmBtnArrowLeftHandle : Integer = GetGUIElementIndexByNameParent('arrowSliderLeft', elmSliderHandle);
      [*] = ;      var elmBtnArrowRightHandle : Integer = GetGUIElementIndexByNameParent('arrowSliderRight', elmSliderHandle);
      [*] = ;      if (gIntRegister_TutorialHistoryIndex<=0) and GetGUIElementEnabled(elmBtnArrowLeftHandle) then
      [*] = ;         SetGUIElementEnabled(elmBtnArrowLeftHandle, False);
      [*] = ;      if (gIntRegister_TutorialHistoryIndex>0) and (not GetGUIElementEnabled(elmBtnArrowLeftHandle)) then
      [*] = ;         SetGUIElementEnabled(elmBtnArrowLeftHandle, True);
      [*] = ;      if (gIntRegister_TutorialHistoryIndex>=lastHistoryIndex) and GetGUIElementEnabled(elmBtnArrowRightHandle) then
      [*] = ;         SetGUIElementEnabled(elmBtnArrowRightHandle, False);
      [*] = ;      if (gIntRegister_TutorialHistoryIndex<lastHistoryIndex) and (not GetGUIElementEnabled(elmBtnArrowRightHandle)) then
      [*] = ;         SetGUIElementEnabled(elmBtnArrowRightHandle, True);
      [*] = ;   end;
      [*] = ;   gBoolRegister_GUIUpdateInterfacePanel := true;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gProfile.mestutor) and (gArrTutorialHistory[0]<>0) then
      [*] = ;begin
      [*] = ;   const cBtnShowTutorial = 200;
      [*] = ;   var tmpElmHandle : Integer = GetGUIElementIndexByNameParent('showtutorialbtn', _gui_GetLayer(cTutorialLayer));
      [*] = ;   if (tmpElmHandle<>0) then
      [*] = ;      SetGUIElementVisible(tmpElmHandle, False);
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

