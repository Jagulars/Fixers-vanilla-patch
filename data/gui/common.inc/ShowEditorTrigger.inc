section.begin
   Name = ShowEditorTrigger
   Code : struct.begin
      [*] = ;function CreateInputBoxSimple(InputBoxID : String; parentElement : Integer; text, hAlign, vAlign : String; posX, posY, inputWidth, maxLength : Integer; eventState, hint : String; enabled : Boolean; tPosX, tPosY : Integer; thAlign, tvAlign, font : String; r, g, b, a : Float) : Integer;
      [*] = ;begin
      [*] = ;   var elmInputBoxHandle : Integer = _gui_CreateImage(InputBoxID, parentElement, gc_gui_material_blank_0, hAlign, vAlign, posX, posY, inputWidth, 33, 0);
      [*] = ;   SetGUIElementStringTag(elmInputBoxHandle, InputBoxID);
      [*] = ;   var elmHandle : Integer = _gui_CreateImage('', elmInputBoxHandle, 'common.slider.right.end', 'halParentLeft', 'valParentTop', GetGUITextureWidth('common.slider.right.end'), 0, 0, 0, 0);
      [*] = ;   _gui_TileScaleElementToSize(elmHandle, -12, 0);
      [*] = ;   elmHandle := _gui_CreateImage('', elmInputBoxHandle, 'common.slider.right.end', 'halParentLeft', 'valParentTop', inputWidth-GetGUITextureWidth('common.slider.right.end'), 0, 0, 0, 0);
      [*] = ;   _gui_TileScaleElementToSize(elmHandle, 12, 0);
      [*] = ;   elmHandle := _gui_CreateScrollLayer(elmInputBoxHandle, 'common.slider.middle', 'halParentLeft', 'valParentTop', GetGUITextureWidth('common.slider.left.end'), 0, inputWidth-GetGUITextureWidth('common.slider.left.end')-GetGUITextureWidth('common.slider.right.end'), 0);
      [*] = ;
      [*] = ;   var elmInputTextHnd : Integer;
      [*] = ;   if (enabled) then
      [*] = ;   elmInputTextHnd := AddNewElementByClassNameParent('text', 'TXEditControl', 0, elmInputBoxHandle)
      [*] = ;   else
      [*] = ;   elmInputTextHnd := AddNewElementByClassNameParent('text', 'TOSWBaseGuiTextControl', 0, elmInputBoxHandle);
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
      [*] = ;   if (not enabled) then
      [*] = ;   begin
      [*] = ;      SetGUIElementUserBlend(elmInputBoxHandle, 0.4);
      [*] = ;      SetGUIElementUserBlend(elmInputTextHnd, 0.5);
      [*] = ;   end;
      [*] = ;
      [*] = ;   Result := elmInputBoxHandle;
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateMapEditorScroller(ElementName : String; Parent : Integer; hAlign, vAlign, MaterialName : String; posX, posY, sizeX, sizeY, scrollX, scrollY, scrollW, scrollH : Integer; showScroller : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   var elmGuiLayer : Integer = AddNewElementByClassNameParent(ElementName, 'TXGuiLayer', 0, Parent);
      [*] = ;   SetGUIElementAlign(elmGuiLayer, hAlign, vAlign);
      [*] = ;   SetGUIElementAllPositionRect(elmGuiLayer, posX, posY, sizeX, sizeY);
      [*] = ;   SetGUIElementMaterial(elmGuiLayer, MaterialName);
      [*] = ;   SetGUIScrollEnabled(elmGuiLayer, True);
      [*] = ;   var elmVScroll : Integer = GetGUIElementVScroll(elmGuiLayer);
      [*] = ;   SetGUIElementAlign(elmVScroll, 'halParentRight', 'valParentTop');
      [*] = ;   SetGUIElementMaterialOffset(elmVScroll, 2, 0);
      [*] = ;   SetGUIElementAllPositionRect(elmVScroll, scrollX, scrollY, scrollW, scrollH);
      [*] = ;   if (showScroller) then
      [*] = ;   begin
      [*] = ;      SetGUIElementMaterial(elmVScroll, 'map.dialog.scroller.tile');
      [*] = ;      SetGUIScrollButtonSource(elmVScroll, 0, 'map.dialog.scroller.up', true);
      [*] = ;      SetGUIScrollButtonSource(elmVScroll, 2, 'map.dialog.scroller.down', true);
      [*] = ;      SetGUIScrollButtonSource(elmVScroll, 1, 'map.dialog.scroller.slider', true);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   SetGUIElementMaterial(elmVScroll, 'misc.blank.black.alpha.0');
      [*] = ;   Result := elmGuiLayer;
      [*] = ;end;
      [*] = ;
      [*] = ;var fontHandleS, fontHandle, fontHandleL, fontHandleInput : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_small,'',fontHandleS);
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'',fontHandle);
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_large,'',fontHandleL);
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Input',gc_gui_fontsize_default,'',fontHandleInput);
      [*] = ;
      [*] = ;// Check if window was already visible, then no need to FadeIn it when show again
      [*] = ;var prevElmParentHandle : Integer = GetGUIElementIndexByNameParent('triggereditor', _gui_GetLayerI());
      [*] = ;var bVisible : Boolean = False;
      [*] = ;if (prevElmParentHandle<>0) and GetGUIElementVisible(prevElmParentHandle) then
      [*] = ;bVisible := True;
      [*] = ;
      [*] = ;var elmScrollLayer : Integer = GetGUIElementIndexByNameParent('dynamic.scroll_layer', prevElmParentHandle);
      [*] = ;var lastScrollPos : Float = 0;
      [*] = ;if (elmScrollLayer<>0) then
      [*] = ;begin
      [*] = ;   var elmVScroll : Integer = GetGUIElementVScroll(elmScrollLayer);
      [*] = ;   if (elmVScroll<>0) then
      [*] = ;   lastScrollPos := GetGUIScrollBarPosition(elmVScroll);
      [*] = ;end;
      [*] = ;
      [*] = ;var windowposindex : Integer = gc_editor_WindowTrigger;
      [*] = ;if (bVisible) then
      [*] = ;begin
      [*] = ;   var elmHandle : Integer = GetGUIElementIndexByNameParent('dynamic', prevElmParentHandle);
      [*] = ;   gGUIEditor.windowpos[windowposindex].x := GetGUIElementPositionX(elmHandle);
      [*] = ;   gGUIEditor.windowpos[windowposindex].y := GetGUIElementPositionY(elmHandle);
      [*] = ;end;
      [*] = ;var dynamicDragX : Integer = gGUIEditor.windowpos[windowposindex].x;
      [*] = ;var dynamicDragY : Integer = gGUIEditor.windowpos[windowposindex].y;
      [*] = ;
      [*] = ;const cEventState = 'EventEditorTrigger';
      [*] = ;
      [*] = ;var elmParentHandle : Integer = _gui_GetOrCreateElementExtAsImage('triggereditor', _gui_GetLayerI, 'halLeft', 'valTop', 0, 0, GetViewerWidth, GetViewerHeight, 0);
      [*] = ;
      [*] = ;const gc_gui_MaxInnerBuildSlotCount = 21;
      [*] = ;
      [*] = ;const cBtnAccept = 101;
      [*] = ;const cBtnCancel = 102;
      [*] = ;const cBtnExecuteEvent = 103;
      [*] = ;const cBtnAddTrigger = 104;
      [*] = ;const cCheckBoxTriggerEnabled = 200;
      [*] = ;const cCheckBoxActionEnabled = 300;
      [*] = ;const cCheckBoxActionWithHero = 301;
      [*] = ;const cCheckBoxActionEnableProvince = 302;
      [*] = ;const cCheckBoxActionRectangle = 303;
      [*] = ;const cCheckBoxActionAllowBuilding = 304;
      [*] = ;const cCheckBoxActionCustomEvent = 305;
      [*] = ;
      [*] = ;const cTextEmpty = '';
      [*] = ;const cTextAny = 'Any';
      [*] = ;const cTextAll = 'All';
      [*] = ;const cTextGetSelectedHex = 'Get Selected Province';
      [*] = ;const cTextCastle = 'Castle';
      [*] = ;const cTextChooseTrigger = 'Choose trigger';
      [*] = ;const cTextExecuteEvent = 'Evaluate trigger';
      [*] = ;const cTextEnabled = 'Enabled';
      [*] = ;const cTextNone = 'None';
      [*] = ;const cTextTriggerType = 'Trigger type';
      [*] = ;const cTextTriggerHint = 'Hint';
      [*] = ;const cTextTriggerTypeProvCapture = 'Province captured';
      [*] = ;const cTextTriggerTypeSiteCapture = 'Location captured';
      [*] = ;const cTextTriggerTypeHeroDie = 'Hero died';
      [*] = ;const cTextTriggerTypeHeroResurrect = 'Hero resurrected';
      [*] = ;const cTextTriggerTypeTurn = 'Game turn';
      [*] = ;const cTextTriggerTypeHeroComeToProv = 'Hero came to province';
      [*] = ;const cTextTriggerTypeProvGameStart = 'Game started';
      [*] = ;const cTextProvIndex = 'Province';
      [*] = ;const cTextSiteIndex = 'Custom location index';
      [*] = ;const cTextSiteID = 'Location type';
      [*] = ;const cTextSelectHero = 'Select hero';
      [*] = ;const cTextTurn = 'Turn';
      [*] = ;const cTextAddTrigger = '<Add Trigger>';
      [*] = ;const cTextSaveTrigger = 'Save Trigger';
      [*] = ;
      [*] = ;const cTextChooseEvent = 'Choose trigger';
      [*] = ;const cTextChooseAction = 'Choose action';
      [*] = ;const cTextCustomEventFlag = 'Custom event';
      [*] = ;const cTextActionType = 'Action type';
      [*] = ;const cTextActionTypeRunEvent = 'Province event';
      [*] = ;const cTextActionTypeAIEnabled = 'Enable AI';
      [*] = ;const cTextActionTypeHeroRecruitAllow = 'Allow hero recruit';
      [*] = ;const cTextActionTypeTriggerEnabled = 'Enable Trigger';
      [*] = ;const cTextActionTypeBuildingsAllow = 'Allow buildings';
      [*] = ;const cTextActionTypeProvinceEnabled = 'Enable province';
      [*] = ;const cTextActionTypeWinLose = 'Win/Lose';
      [*] = ;const cTextActionTypeRunGenerateMap = 'Generate map';
      [*] = ;const cTextAddAction = '<Add Action>';
      [*] = ;const cTextDelayRun = 'Run event with delay';
      [*] = ;const cTextAllowBuildingFlag = 'Allow/Disallow';
      [*] = ;const cTextQuarter = 'Quarter';
      [*] = ;const cTextQuarterLevel = 'Quarter level';
      [*] = ;const cTextTier = 'Tier';
      [*] = ;const cTextSlotStart = 'Start slot';
      [*] = ;const cTextSlotEnd = 'End slot';
      [*] = ;
      [*] = ;const cTextHeaderDynamicInfo1 = 'Triggers';
      [*] = ;const cTextHeaderDynamicInfo2 = 'Trigger settings';
      [*] = ;const cTextHeaderActionInfo1 = 'Actions';
      [*] = ;const cTextHeaderActionInfo2 = 'Action settings';
      [*] = ;const cTextRequireHero = 'Require hero';
      [*] = ;const cTextEnable = 'Enable';
      [*] = ;const cTextRectangle = 'Rectangle';
      [*] = ;const cTextRectangleLeftTop = 'Left Top province';
      [*] = ;const cTextRectangleRightBottom = 'Right Bottom province';
      [*] = ;const cTextWin = 'Win';
      [*] = ;const cTextLose = 'Lose';
      [*] = ;const cTextGenerationMode = 'Generate mode';
      [*] = ;const cTextFullMapGeneration = 'Full generate';
      [*] = ;const cTextFastMapGeneration = 'Debug fast generate';
      [*] = ;
      [*] = ;const cMarginDelimiter = 6;
      [*] = ;const cMarginDelimiterHalf = cMarginDelimiter div 2;
      [*] = ;const cMarginDropboxTop = 2;
      [*] = ;const cMarginDropboxBottom = 2;
      [*] = ;const cMarginFrame = 4;
      [*] = ;const cMarginStrip = 7;
      [*] = ;const cListEnd = cMarginDelimiter*2;
      [*] = ;
      [*] = ;const cInputBoxWidth = 228-64;
      [*] = ;const cInputBoxWidthWide = 228;
      [*] = ;const cInputTextPosX = 36;
      [*] = ;const cInputTextPosY = 1;
      [*] = ;
      [*] = ;const cMarginFrameTop = -18;
      [*] = ;var xOff : Integer = 0;
      [*] = ;var yOff : Integer = 0;
      [*] = ;
      [*] = ;procedure GetTriggerTypeTextName(ttype : Integer; var tname : String);
      [*] = ;begin
      [*] = ;   case ttype of
      [*] = ;      gc_triggertype_provcapture : tname := cTextTriggerTypeProvCapture;
      [*] = ;      gc_triggertype_sitecapture : tname := cTextTriggerTypeSiteCapture;
      [*] = ;      gc_triggertype_herodie : tname := cTextTriggerTypeHeroDie;
      [*] = ;      gc_triggertype_heroresurrect : tname := cTextTriggerTypeHeroResurrect;
      [*] = ;      gc_triggertype_turn : tname := cTextTriggerTypeTurn;
      [*] = ;      gc_triggertype_herocometoprov : tname := cTextTriggerTypeHeroComeToProv;
      [*] = ;      gc_triggertype_gamestart : tname := cTextTriggerTypeProvGameStart;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure GetTriggerActionTypeTextName(actiontype : Integer; var actname : String);
      [*] = ;begin
      [*] = ;   case actiontype of
      [*] = ;      gc_actiontype_runevent : actname := cTextActionTypeRunEvent;
      [*] = ;      gc_actiontype_aienabled : actname := cTextActionTypeAIEnabled;
      [*] = ;      gc_actiontype_herorecruitallowed : actname := cTextActionTypeHeroRecruitAllow;
      [*] = ;      gc_actiontype_triggerenabled : actname := cTextActionTypeTriggerEnabled;
      [*] = ;      gc_actiontype_buildingallowed : actname := cTextActionTypeBuildingsAllow;
      [*] = ;      gc_actiontype_provinceenabled : actname := cTextActionTypeProvinceEnabled;
      [*] = ;      gc_actiontype_winlose : actname := cTextActionTypeWinLose;
      [*] = ;      gc_actiontype_generatemap : actname := cTextActionTypeRunGenerateMap;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;// dynamic info
      [*] = ;function ShowDynamicInfo(elmParentHandle : Integer; var trigger : TTrigger; inXOff, inYOff, inWidth, inHeight : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var posX : Integer = inXOff;
      [*] = ;   var posY : Integer = inYOff;
      [*] = ;   var width : Integer = inWidth;
      [*] = ;   var height : Integer = inHeight;
      [*] = ;   var elmDynamicInfoHandle : Integer = _gui_CreateFrameBorderExt('dynamic', elmParentHandle, gGUIEditor.windowpos[windowposindex].hal, gGUIEditor.windowpos[windowposindex].val, posX, posY, width, height, True);
      [*] = ;   SetGUIAllowDrag(elmDynamicInfoHandle, True);
      [*] = ;   SetGUIAllowEvents(elmDynamicInfoHandle, True, False, False);
      [*] = ;
      [*] = ;   // scroll layer header
      [*] = ;   var scrollLayerWidth : Integer = GetGUIElementWidth(elmDynamicInfoHandle);
      [*] = ;   var scrollLayerHeight : Integer = GetGUIElementHeight(elmDynamicInfoHandle);
      [*] = ;   var elmStaticScrollLayer : Integer = CreateMapEditorScroller('static_scroll_layer', elmDynamicInfoHandle, 'halParentLeft', 'valParentTop', gc_gui_material_blank_0, 0, 0, scrollLayerWidth, scrollLayerHeight, -17, 0, 32, scrollLayerHeight, True);
      [*] = ;   var elmStripHandle : Integer = _gui_CreateImage('', elmStaticScrollLayer, 'element.strip.240', 'halParentMiddle', 'valParentTop', 0, cMarginFrameTop, 0, 0, 0);
      [*] = ;   var elmTextHandle : Integer = _gui_CreateText('', elmStripHandle, cTextHeaderDynamicInfo1, 'halParentLeft', 'valParentTop', 0, -2, GetGUIElementWidth(elmStripHandle), GetGUIElementHeight(elmStripHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;   posY := 16;
      [*] = ;
      [*] = ;   function CreateEditorChooseTrigger(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var listCount : Integer;
      [*] = ;      var count : Integer = _scenario_FindTriggerFreeIndex(False);
      [*] = ;      if (count<0) then
      [*] = ;      begin
      [*] = ;         count := gc_MaxScenarioTriggers;
      [*] = ;         listCount := count;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      listCount := count+1;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('choosetrigger', elmParent, listCount, 16, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, cTextChooseTrigger, 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      var tname : String = '';
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to count-1 do
      [*] = ;      begin
      [*] = ;         tname := '';
      [*] = ;         GetTriggerTypeTextName(gScenario.triggers[i].ttype, tname);
      [*] = ;         if (gScenario.triggers[i].hint<>'') then
      [*] = ;         tname := IntToStr(i)+': '+gScenario.triggers[i].hint
      [*] = ;         else
      [*] = ;         tname := IntToStr(i)+': '+tname;
      [*] = ;         GUIListBoxAddItem(elmListBoxHandle, tname, i);
      [*] = ;      end;
      [*] = ;      if (count<gc_MaxScenarioTriggers) then
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextAddTrigger, count);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, gGUIEditor.seltrigger);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // enabled flag
      [*] = ;   function CreateEditorTriggerEnabledFlag(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+cMarginDropboxTop;
      [*] = ;
      [*] = ;      var text : String = cTextEnabled;
      [*] = ;      posX := 26;
      [*] = ;      var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('', elmParent, trigger.enabled, text, 'halParentLeft', 'valParentTop', posX, posY, cEventState, '', cCheckBoxTriggerEnabled);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmCheckBoxHandle)+cMarginDropboxBottom;
      [*] = ;
      [*] = ;      Result := elmCheckBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // hint
      [*] = ;   function CreateEditorTriggerHint(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var elmInputHandle : Integer = CreateInputBoxSimple('triggerhint', elmParent, trigger.hint, 'halParentMiddle', 'valParentTop', 0, posY+2, cInputBoxWidthWide, 64, cEventState, 'gui|747', True, cInputTextPosX, cInputTextPosY, 'halLeft', 'valMiddle', fontHandleInput, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmInputHandle, cTextTriggerHint, 'halParentLeft', 'valParentTop', 0, -18, GetGUIElementWidth(elmInputHandle), GetGUIElementHeight(elmInputHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmInputHandle);
      [*] = ;
      [*] = ;      Result := elmInputHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // trigger type
      [*] = ;   function CreateEditorTriggerType(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('triggertype', elmParent, 8, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, cTextTriggerType, 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextNone, 0);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextTriggerTypeProvCapture, gc_triggertype_provcapture);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextTriggerTypeSiteCapture, gc_triggertype_sitecapture);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextTriggerTypeHeroDie, gc_triggertype_herodie);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextTriggerTypeHeroResurrect, gc_triggertype_heroresurrect);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextTriggerTypeTurn, gc_triggertype_turn);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextTriggerTypeHeroComeToProv, gc_triggertype_herocometoprov);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextTriggerTypeProvGameStart, gc_triggertype_gamestart);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, trigger.ttype);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   CreateEditorChooseTrigger(elmStaticScrollLayer, posY);;
      [*] = ;   posY := posY+cMarginDelimiterHalf;
      [*] = ;   CreateEditorTriggerEnabledFlag(elmStaticScrollLayer, posY);
      [*] = ;   posY := posY+cMarginDelimiterHalf;
      [*] = ;   CreateEditorTriggerHint(elmStaticScrollLayer, posY);
      [*] = ;   posY := posY+cMarginDelimiter;
      [*] = ;   CreateEditorTriggerType(elmStaticScrollLayer, posY);
      [*] = ;
      [*] = ;   const cOffY = cMarginDelimiter*4;
      [*] = ;   var scrollLayerStaticHeight : Integer = posY+cOffY;
      [*] = ;   var elmDynamicScrollLayer : Integer = CreateMapEditorScroller('scroll_layer', elmDynamicInfoHandle, 'halParentLeft', 'valParentTop', gc_gui_material_blank_0, 0, scrollLayerStaticHeight, scrollLayerWidth, height-scrollLayerStaticHeight, -17, 0, 32, height-scrollLayerStaticHeight, True);
      [*] = ;
      [*] = ;   posY := posY+cMarginStrip*2;
      [*] = ;   SetGUIElementPositionY(elmDynamicScrollLayer, posY+GetGUITextureHeight('element.strip.240')-23);
      [*] = ;
      [*] = ;   elmStripHandle := _gui_CreateImage('', elmDynamicInfoHandle, 'element.strip.240', 'halParentMiddle', 'valParentTop', 0, posY, 0, 0, 0);
      [*] = ;   elmTextHandle := _gui_CreateText('', elmStripHandle, cTextHeaderDynamicInfo2, 'halParentLeft', 'valParentTop', 0, -2, GetGUIElementWidth(elmStripHandle), GetGUIElementHeight(elmStripHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;   posY := cOffY;
      [*] = ;
      [*] = ;   // province index
      [*] = ;   function CreateEditorProvIndex(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;      var hexCount : Integer = gMapEditor.map.x*gMapEditor.map.y;
      [*] = ;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('provindex', elmParent, hexCount+2, 16, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, cTextProvIndex, 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextGetSelectedHex, -2);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextAny, -1);
      [*] = ;      for i:=0 to hexCount-1 do
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, 'Index:'+IntToStr(i)+' (X:'+IntToStr(gMapEditor.grid[i].x)+' Y:'+IntToStr(gMapEditor.grid[i].y)+')', i);
      [*] = ;      var ind : Integer;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, trigger.provind+2);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // site index
      [*] = ;   {function CreateEditorSiteIndex(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;      var count : Integer = 0;
      [*] = ;      if (trigger.provind>0) then
      [*] = ;      for i:=0 to gc_editor_MaxCustomSitesCount-1 do
      [*] = ;      if (gMapEditor.grid[trigger.provind].sites[i].id>0) then
      [*] = ;      count := count+1;
      [*] = ;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('siteindex', elmParent, count+1, 16, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, cTextSiteIndex, 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextAny, -1);
      [*] = ;      if (trigger.provind>0) then
      [*] = ;      for i:=0 to gc_editor_MaxCustomSitesCount-1 do
      [*] = ;      if (gMapEditor.grid[trigger.provind].sites[i].id>0) then
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, 'Site: '+IntToStr(i)+' '+GetLocaleTableListItemByID('site', IntToStr(gMapEditor.grid[trigger.provind].sites[i].id)), i);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, trigger.siteind+1);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;}
      [*] = ;
      [*] = ;   // site id
      [*] = ;   function CreateEditorSiteID(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var count : Integer = 0;
      [*] = ;      for i:=0 to gPrototypeData.sites.number-1 do
      [*] = ;      begin
      [*] = ;         var pSite : Integer = ParserSelectByHandleByIndex(gPrototypeData.sites.handle, i);
      [*] = ;         var guarded : Integer = ParserGetIntValueByKeyByHandle(pSite, 'Guarded');
      [*] = ;         if (guarded>0) then
      [*] = ;         count := count+1;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('siteid', elmParent, count+1, 16, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, cTextSiteID, 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextAny, -1);
      [*] = ;      for i:=0 to gPrototypeData.sites.number-1 do
      [*] = ;      begin
      [*] = ;         var pSite : Integer = ParserSelectByHandleByIndex(gPrototypeData.sites.handle, i);
      [*] = ;         var guarded : Integer = ParserGetIntValueByKeyByHandle(pSite, 'Guarded');
      [*] = ;         if (guarded>0) then
      [*] = ;         GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('site', IntToStr(i)), i);
      [*] = ;      end;
      [*] = ;      var ind : Integer;
      [*] = ;      if (trigger.siteid<=0) then
      [*] = ;      ind := 0
      [*] = ;      else
      [*] = ;      ind := GetGUIListBoxItemIndexOfTag(elmListBoxHandle, trigger.siteid);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, ind);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // owner index
      [*] = ;   function CreateEditorOwnerIndex(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('ownerind', elmParent, gMapEditor.map.players+1, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'Owner player', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextAny, -1);
      [*] = ;      for i:=0 to gMapEditor.map.players-1 do
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, 'Player.'+IntToStr(i), i);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, trigger.ownerind+1);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // hero index
      [*] = ;   function CreateEditorHeroIndex(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var listcount : Integer = 0;
      [*] = ;      for i:=0 to gc_MaxEditorHeroCount-1 do
      [*] = ;      begin
      [*] = ;         if (gMapEditor.players[trigger.ownerind].heroes[i].class1>0) then
      [*] = ;         listcount := listcount+1;
      [*] = ;      end;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('heroind', elmParent, listcount+1, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, cTextSelectHero, 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextAny, -1);
      [*] = ;      for i:=0 to gc_MaxEditorHeroCount-1 do
      [*] = ;      begin
      [*] = ;         if (gMapEditor.players[trigger.ownerind].heroes[i].class1>0) then
      [*] = ;         begin
      [*] = ;            var text : String = GetLocaleTableListItemByID('hero_names', gMapEditor.players[trigger.ownerind].heroes[i].name);
      [*] = ;            if (text='') then text := gMapEditor.players[trigger.ownerind].heroes[i].name;
      [*] = ;            text := text+' ('+GetLocaleTableListItemByID('hero_class', IntToStr(gMapEditor.players[trigger.ownerind].heroes[i].class1))+')';
      [*] = ;            GUIListBoxAddItem(elmListBoxHandle, text, i);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, trigger.heroind+1);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // turn
      [*] = ;   function CreateEditorTurn(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var elmInputHandle : Integer = CreateInputBoxSimple('turn', elmParent, IntToStr(trigger.turn), 'halParentMiddle', 'valParentTop', 0, posY+2, cInputBoxWidthWide, 7, cEventState, 'gui|747', True, cInputTextPosX, cInputTextPosY, 'halLeft', 'valMiddle', fontHandleInput, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmInputHandle, cTextTurn, 'halParentLeft', 'valParentTop', 0, -18, GetGUIElementWidth(elmInputHandle), GetGUIElementHeight(elmInputHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      _gui_InputBoxSetupNumCharFilter(elmInputHandle, True, False);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmInputHandle);
      [*] = ;
      [*] = ;      Result := elmInputHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (trigger.ttype=gc_triggertype_provcapture) or (trigger.ttype=gc_triggertype_herodie) or (trigger.ttype=gc_triggertype_heroresurrect) or (trigger.ttype=gc_triggertype_herocometoprov) then
      [*] = ;   CreateEditorOwnerIndex(elmDynamicScrollLayer, posY);
      [*] = ;   if (trigger.ttype=gc_triggertype_herodie) or (trigger.ttype=gc_triggertype_heroresurrect) or (trigger.ttype=gc_triggertype_herocometoprov) then
      [*] = ;   CreateEditorHeroIndex(elmDynamicScrollLayer, posY);
      [*] = ;   if (trigger.ttype=gc_triggertype_herocometoprov) or (trigger.ttype=gc_triggertype_provcapture) or (trigger.ttype=gc_triggertype_sitecapture) then
      [*] = ;   CreateEditorProvIndex(elmDynamicScrollLayer, posY);
      [*] = ;   if (trigger.ttype=gc_triggertype_sitecapture) then
      [*] = ;   begin
      [*] = ;      //CreateEditorSiteIndex(elmDynamicScrollLayer, posY);
      [*] = ;      CreateEditorSiteID(elmDynamicScrollLayer, posY);
      [*] = ;   end;
      [*] = ;   if (trigger.ttype=gc_triggertype_turn) then
      [*] = ;   CreateEditorTurn(elmDynamicScrollLayer, posY);
      [*] = ;   posY := posY+cMarginDelimiterHalf;
      [*] = ;
      [*] = ;   // settings scroller
      [*] = ;   SetGUIScrollEnabled(elmDynamicScrollLayer, (posY+GetGUIElementHeight(elmStaticScrollLayer))>GetGUIElementHeight(elmDynamicInfoHandle));
      [*] = ;   SetGUIElementHeight(elmDynamicScrollLayer, posY+cListEnd);
      [*] = ;   var elmVScroll : Integer = GetGUIElementVScroll(elmDynamicScrollLayer);
      [*] = ;   SetGUIScrollBarPosition(elmVScroll, lastScrollPos);
      [*] = ;
      [*] = ;   Result := elmDynamicInfoHandle;
      [*] = ;end;
      [*] = ;
      [*] = ;function ShowActionInfo(elmParentHandle : Integer; var trigger : TTrigger; var action : TTriggerAction; inXOff, inYOff, inWidth, inHeight : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   var posX : Integer = inXOff;
      [*] = ;   var posY : Integer = inYOff;
      [*] = ;   var width : Integer = inWidth;
      [*] = ;   var height : Integer = inHeight;
      [*] = ;   var elmActionInfoHandle : Integer = _gui_CreateFrameBorderExt('action_dynamic', elmParentHandle, gGUIEditor.windowpos[windowposindex].hal, gGUIEditor.windowpos[windowposindex].val, posX, posY, width, height, True);
      [*] = ;   //SetGUIAllowDrag(elmActionInfoHandle, True);
      [*] = ;   SetGUIAllowEvents(elmActionInfoHandle, True, False, False);
      [*] = ;
      [*] = ;   // scroll layer header
      [*] = ;   var scrollLayerWidth : Integer = GetGUIElementWidth(elmActionInfoHandle);
      [*] = ;   var scrollLayerHeight : Integer = GetGUIElementHeight(elmActionInfoHandle);
      [*] = ;   var elmStaticScrollLayer : Integer = CreateMapEditorScroller('static_scroll_layer', elmActionInfoHandle, 'halParentLeft', 'valParentTop', gc_gui_material_blank_0, 0, 0, scrollLayerWidth, scrollLayerHeight, -17, 0, 32, scrollLayerHeight, True);
      [*] = ;   var elmStripHandle : Integer = _gui_CreateImage('', elmStaticScrollLayer, 'element.strip.240', 'halParentMiddle', 'valParentTop', 0, cMarginFrameTop, 0, 0, 0);
      [*] = ;   var elmTextHandle : Integer = _gui_CreateText('', elmStripHandle, cTextHeaderActionInfo1, 'halParentLeft', 'valParentTop', 0, -2, GetGUIElementWidth(elmStripHandle), GetGUIElementHeight(elmStripHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;   posY := 16;
      [*] = ;
      [*] = ;   function CreateEditorChooseAction(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var listCount : Integer;
      [*] = ;      var count : Integer = _scenario_FindTriggerActionFreeIndex(trigger);
      [*] = ;      if (count<0) then
      [*] = ;      begin
      [*] = ;         count := gc_MaxScenarioTriggerActions;
      [*] = ;         listCount := count;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      listCount := count+1;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('chooseaction', elmParent, listCount, 16, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, cTextChooseAction, 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      var tname : String = '';
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to count-1 do
      [*] = ;      begin
      [*] = ;         tname := '';
      [*] = ;         GetTriggerActionTypeTextName(trigger.actions[i].actiontype, tname);
      [*] = ;         if (trigger.actions[i].hint<>'') then
      [*] = ;         tname := IntToStr(i)+': '+trigger.actions[i].hint
      [*] = ;         else
      [*] = ;         tname := IntToStr(i)+': '+tname;
      [*] = ;         GUIListBoxAddItem(elmListBoxHandle, tname, i);
      [*] = ;      end;
      [*] = ;      if (count<gc_MaxScenarioTriggerActions) then
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextAddAction, count);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, gGUIEditor.selaction);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // enabled flag
      [*] = ;   function CreateEditorActionEnabledFlag(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+cMarginDropboxTop;
      [*] = ;
      [*] = ;      var text : String = cTextEnabled;
      [*] = ;      posX := 26;
      [*] = ;      var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('', elmParent, action.enabled, text, 'halParentLeft', 'valParentTop', posX, posY, cEventState, '', cCheckBoxActionEnabled);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmCheckBoxHandle)+cMarginDropboxBottom;
      [*] = ;
      [*] = ;      Result := elmCheckBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // hint
      [*] = ;   function CreateEditorActionHint(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var elmInputHandle : Integer = CreateInputBoxSimple('actionhint', elmParent, action.hint, 'halParentMiddle', 'valParentTop', 0, posY+2, cInputBoxWidthWide, 64, cEventState, 'gui|747', True, cInputTextPosX, cInputTextPosY, 'halLeft', 'valMiddle', fontHandleInput, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmInputHandle, cTextTriggerHint, 'halParentLeft', 'valParentTop', 0, -18, GetGUIElementWidth(elmInputHandle), GetGUIElementHeight(elmInputHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmInputHandle);
      [*] = ;
      [*] = ;      Result := elmInputHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // action type
      [*] = ;   function CreateEditorActionType(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('actiontype', elmParent, 9, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, cTextActionType, 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextNone, 0);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextActionTypeRunEvent, gc_actiontype_runevent);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextActionTypeAIEnabled, gc_actiontype_aienabled);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextActionTypeHeroRecruitAllow, gc_actiontype_herorecruitallowed);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextActionTypeTriggerEnabled, gc_actiontype_triggerenabled);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextActionTypeBuildingsAllow, gc_actiontype_buildingallowed);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextActionTypeProvinceEnabled, gc_actiontype_provinceenabled);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextActionTypeWinLose, gc_actiontype_winlose);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextActionTypeRunGenerateMap, gc_actiontype_generatemap);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, action.actiontype);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   CreateEditorChooseAction(elmStaticScrollLayer, posY);;
      [*] = ;   posY := posY+cMarginDelimiterHalf;
      [*] = ;   CreateEditorActionEnabledFlag(elmStaticScrollLayer, posY);
      [*] = ;   posY := posY+cMarginDelimiterHalf;
      [*] = ;   CreateEditorActionHint(elmStaticScrollLayer, posY);
      [*] = ;   posY := posY+cMarginDelimiter;
      [*] = ;   CreateEditorActionType(elmStaticScrollLayer, posY);
      [*] = ;
      [*] = ;   const cOffY = cMarginDelimiter*4;
      [*] = ;   var scrollLayerStaticHeight : Integer = posY+cOffY;
      [*] = ;   var elmDynamicScrollLayer : Integer = CreateMapEditorScroller('scroll_layer', elmActionInfoHandle, 'halParentLeft', 'valParentTop', gc_gui_material_blank_0, 0, scrollLayerStaticHeight, scrollLayerWidth, height-scrollLayerStaticHeight, -17, 0, 32, height-scrollLayerStaticHeight, True);
      [*] = ;
      [*] = ;   posY := posY+cMarginStrip*2;
      [*] = ;   SetGUIElementPositionY(elmDynamicScrollLayer, posY+GetGUITextureHeight('element.strip.240')-23);
      [*] = ;
      [*] = ;   elmStripHandle := _gui_CreateImage('', elmActionInfoHandle, 'element.strip.240', 'halParentMiddle', 'valParentTop', 0, posY, 0, 0, 0);
      [*] = ;   elmTextHandle := _gui_CreateText('', elmStripHandle, cTextHeaderActionInfo2, 'halParentLeft', 'valParentTop', 0, -2, GetGUIElementWidth(elmStripHandle), GetGUIElementHeight(elmStripHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;   posY := cOffY;
      [*] = ;
      [*] = ;   // is custom event
      [*] = ;   function CreateEditorCustomEventFlag(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+cMarginDropboxTop;
      [*] = ;
      [*] = ;      posX := 26;
      [*] = ;      var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('', elmParent, (action.param3>0), cTextCustomEventFlag, 'halParentLeft', 'valParentTop', posX, posY, cEventState, '', cCheckBoxActionCustomEvent);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmCheckBoxHandle)+cMarginDropboxBottom;
      [*] = ;
      [*] = ;      Result := elmCheckBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // select event
      [*] = ;   function CreateEditorSelectEvent(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      ArrayClear;
      [*] = ;      var count : Integer = 0;
      [*] = ;      var pEvents : Integer;
      [*] = ;      var eventCount : Integer;
      [*] = ;      if (action.param3>0) then
      [*] = ;      begin
      [*] = ;         pEvents := gPrototypeData.scenarioevents.handle;
      [*] = ;         eventCount := gPrototypeData.scenarioevents.number;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         pEvents := gPrototypeData.events.handle;
      [*] = ;         eventCount := gPrototypeData.events.number;
      [*] = ;      end;
      [*] = ;      if (action.param3>0) then
      [*] = ;      begin
      [*] = ;         for i:=eventCount-1 downto 0 do
      [*] = ;         begin
      [*] = ;            var pEvent : Integer = ParserSelectByHandleByIndex(pEvents, i);
      [*] = ;            var id : Integer = ParserGetIntValueByKeyByHandle(pEvent, 'EventID');
      [*] = ;            if (id>0) then
      [*] = ;            ArrayPushValue(id);
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      for i:=eventCount-1 downto 0 do
      [*] = ;      begin
      [*] = ;         begin
      [*] = ;            var pEvent : Integer = ParserSelectByHandleByIndex(pEvents, i);
      [*] = ;            var possibility : Integer = ParserGetIntValueByKeyByHandle(pEvent, 'Possibility');
      [*] = ;            if (possibility>0) then
      [*] = ;            ArrayPushValue(i);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddleExt('selectevent', elmParent, ArrayGetCount, 16, 0, posY, 164{*2+64}, cEventState,'');
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, cTextChooseEvent, 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      for i:=ArrayGetCount-1 downto 0 do
      [*] = ;      begin
      [*] = ;         var eventID : Integer = ArrayPopValue;
      [*] = ;         var eventInd : Integer;
      [*] = ;         if (action.param3>0) then
      [*] = ;         eventInd := eventID-gc_query_ScenarioEventMinIndex
      [*] = ;         else
      [*] = ;         eventInd := eventID;
      [*] = ;         var pEvent : Integer = ParserSelectByHandleByIndex(pEvents, eventInd);
      [*] = ;         var hint : String = ParserGetValueByKeyByHandle(pEvent, 'Hint');
      [*] = ;         if (hint='') then
      [*] = ;         hint := IntToStr(eventID);
      [*] = ;         GUIListBoxAddItem(elmListBoxHandle, hint, eventID);
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, GetGUIListBoxItemIndexOfTag(elmListBoxHandle, action.param1));
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // province index
      [*] = ;   function CreateEditorActionProvIndex(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var hexCount : Integer = gMapEditor.map.x*gMapEditor.map.y;
      [*] = ;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('actionprovindex', elmParent, hexCount+3, 16, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, cTextProvIndex, 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextGetSelectedHex, -3);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextAny, -1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextCastle, -2);
      [*] = ;      for i:=0 to hexCount-1 do
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, 'Index:'+IntToStr(i)+' (X:'+IntToStr(gMapEditor.grid[i].x)+' Y:'+IntToStr(gMapEditor.grid[i].y)+')', i);
      [*] = ;      var ind : integer;
      [*] = ;      if (action.ind=-1) then
      [*] = ;      ind := 1
      [*] = ;      else
      [*] = ;      if (action.ind=-2) then
      [*] = ;      ind := 2
      [*] = ;      else
      [*] = ;      ind := action.ind+3;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, ind);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // with hero flag
      [*] = ;   function CreateEditorWithHeroFlag(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+cMarginDropboxTop;
      [*] = ;
      [*] = ;      posX := 26;
      [*] = ;      var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('', elmParent, action.flag2, cTextRequireHero, 'halParentLeft', 'valParentTop', posX, posY, cEventState, '', cCheckBoxActionWithHero);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmCheckBoxHandle)+cMarginDropboxBottom;
      [*] = ;
      [*] = ;      Result := elmCheckBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // enable province flag
      [*] = ;   function CreateEditorEnable(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+cMarginDropboxTop;
      [*] = ;
      [*] = ;      posX := 26;
      [*] = ;      var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('', elmParent, action.flag1, cTextEnable, 'halParentLeft', 'valParentTop', posX, posY, cEventState, '', cCheckBoxActionEnableProvince);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmCheckBoxHandle)+cMarginDropboxBottom;
      [*] = ;
      [*] = ;      Result := elmCheckBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // rectangle province flag
      [*] = ;   function CreateEditorRectangle(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+cMarginDropboxTop;
      [*] = ;
      [*] = ;      posX := 26;
      [*] = ;      var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('', elmParent, action.flag2, cTextRectangle, 'halParentLeft', 'valParentTop', posX, posY, cEventState, '', cCheckBoxActionRectangle);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmCheckBoxHandle)+cMarginDropboxBottom;
      [*] = ;
      [*] = ;      Result := elmCheckBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // rectangle x1, y1
      [*] = ;   function CreateEditorRectangleX1Y1(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var hexCount : Integer = gMapEditor.map.x*gMapEditor.map.y;
      [*] = ;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('actionrectanglex1y1', elmParent, hexCount+1, 16, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, cTextRectangleLeftTop, 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextGetSelectedHex, -1);
      [*] = ;      for i:=0 to hexCount-1 do
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, 'Index:'+IntToStr(i)+' (X:'+IntToStr(gMapEditor.grid[i].x)+' Y:'+IntToStr(gMapEditor.grid[i].y)+')', i);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, action.param1+1);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // rectangle x2, y2
      [*] = ;   function CreateEditorRectangleX2Y2(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var hexCount : Integer = gMapEditor.map.x*gMapEditor.map.y;
      [*] = ;      if (action.param1>action.param2) then
      [*] = ;      action.param2 := action.param1;
      [*] = ;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('actionrectanglex2y2', elmParent, hexCount-action.param1+1, 16, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, cTextRectangleRightBottom, 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextGetSelectedHex, -1);
      [*] = ;      for i:=action.param1 to hexCount-1 do
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, 'Index:'+IntToStr(i)+' (X:'+IntToStr(gMapEditor.grid[i].x)+' Y:'+IntToStr(gMapEditor.grid[i].y)+')', i);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, action.param2-action.param1+1);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // delay run
      [*] = ;   function CreateEditorActionDelayRun(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('delayrun', elmParent, 31, 16, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, cTextDelayRun, 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextNone, 0);
      [*] = ;      for i:=1 to 30 do
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, IntToStr(i)+' Turns', i);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, action.param2);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // win lose
      [*] = ;   function CreateEditorWinLose(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('winlose', elmParent, 2, 16, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, cTextDelayRun, 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextWin, 0);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextLose, 1);
      [*] = ;      var ind : Integer;
      [*] = ;      if (action.flag1) then
      [*] = ;      ind := 0
      [*] = ;      else
      [*] = ;      ind := 1;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, ind);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // action player index
      [*] = ;   function CreateEditorActionPlayerIndex(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('actionplayerind', elmParent, gMapEditor.map.players+1, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'Player', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextAll, -1);
      [*] = ;      for i:=0 to gMapEditor.map.players-1 do
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, 'Player.'+IntToStr(i), i);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, action.ind+1);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // choose trigger to enable/disable
      [*] = ;   function CreateEditorActionChooseTrigger(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var count : Integer = _scenario_FindTriggerFreeIndex(False);
      [*] = ;      if (count<0) then
      [*] = ;      count := gc_MaxScenarioTriggers;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('actionchoosetrigger', elmParent, count, 16, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, cTextChooseTrigger, 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      var tname : String = '';
      [*] = ;      var i : Integer;
      [*] = ;      for i:=0 to count-1 do
      [*] = ;      begin
      [*] = ;         tname := '';
      [*] = ;         if (gScenario.triggers[i].hint<>'') then
      [*] = ;         tname := IntToStr(i)+': '+gScenario.triggers[i].hint
      [*] = ;         else
      [*] = ;         tname := 'Trigger '+IntToStr(i);
      [*] = ;         GUIListBoxAddItem(elmListBoxHandle, tname, i);
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, action.ind);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // map generate mode
      [*] = ;   function CreateEditorActionGenerateMode(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('generatemode', elmParent, 2, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, cTextGenerationMode, 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextFullMapGeneration, 0);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextFastMapGeneration, 1);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, _gui_BoolToInt(action.flag1));
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // enable province flag
      [*] = ;   function CreateEditorAllowBuildingFlag(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+cMarginDropboxTop;
      [*] = ;
      [*] = ;      posX := 26;
      [*] = ;      var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('', elmParent, action.flag1, cTextAllowBuildingFlag, 'halParentLeft', 'valParentTop', posX, posY, cEventState, '', cCheckBoxActionAllowBuilding);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmCheckBoxHandle)+cMarginDropboxBottom;
      [*] = ;
      [*] = ;      Result := elmCheckBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // quarter
      [*] = ;   function CreateEditorActionQuarter(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var quarterCount : Integer = tagBuildQuarterLast-tagBuildQuarterFirst+1;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('actionquarter', elmParent, quarterCount+1, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, cTextQuarter, 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextAll, 0);
      [*] = ;      for i:=0 to quarterCount-1 do
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('gui', IntToStr(233+i)), i+1);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, action.param1);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // quarter level
      [*] = ;   function CreateEditorActionQuarterLevel(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;      var quarterLevelCount : Integer = 4;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('actionquarterlevel', elmParent, quarterLevelCount+1, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, cTextQuarterLevel, 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextAll, 0);
      [*] = ;      for i:=0 to quarterLevelCount-1 do
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextTier+' '+IntToStr(i+1), i+1);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, action.param2);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // slot start
      [*] = ;   function CreateEditorActionBuildingSlotStart(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var count : Integer = ArrayGetCount;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('actionbuildingslotstart', elmParent, count+1, 16, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, cTextSlotStart, 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextAll, 0);
      [*] = ;      var ind : Integer = -1;
      [*] = ;      for i:=0 to count-1 do
      [*] = ;      begin
      [*] = ;         var encode : Integer = ArrayGetValueByIndex(i);
      [*] = ;         var slot : Integer = encode div 10000;
      [*] = ;         var buildID : Integer = encode mod 10000;
      [*] = ;
      [*] = ;         GUIListBoxAddItem(elmListBoxHandle, IntToStr(slot)+' '+GetLocaleTableListItemByID('inner_build', IntToStr(buildID)), slot);
      [*] = ;         if (slot=action.param3) then
      [*] = ;         ind := i;
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, ind+1);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // slot finish
      [*] = ;   function CreateEditorActionBuildingSlotEnd(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var count : Integer = ArrayGetCount;
      [*] = ;      var ind : Integer;
      [*] = ;      for i:=0 to count-1 do
      [*] = ;      begin
      [*] = ;         var encode : Integer = ArrayGetValueByIndex(i);
      [*] = ;         var slot : Integer = encode div 10000;
      [*] = ;         if (slot=action.param3) then
      [*] = ;         ind := i;
      [*] = ;      end;
      [*] = ;      var listCount : Integer = count-ind;
      [*] = ;
      [*] = ;      if (action.param3>action.param4) then
      [*] = ;      action.param4 := action.param3;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('actionbuildingslotend', elmParent, listCount, 16, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, cTextSlotEnd, 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      ind := 0;
      [*] = ;      var dec : Integer = 0;
      [*] = ;      for i:=0 to count-1 do
      [*] = ;      begin
      [*] = ;         var encode : Integer = ArrayGetValueByIndex(i);
      [*] = ;         var slot : Integer = encode div 10000;
      [*] = ;         if (slot>=action.param3) then
      [*] = ;         begin
      [*] = ;            var buildID : Integer = encode mod 10000;
      [*] = ;            GUIListBoxAddItem(elmListBoxHandle, IntToStr(slot)+' '+GetLocaleTableListItemByID('inner_build', IntToStr(buildID)), slot);
      [*] = ;            if (slot=action.param4) then
      [*] = ;            ind := i-dec;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         dec := dec+1;
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, ind);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var acttype : Integer = action.actiontype;
      [*] = ;   if (acttype>0) then
      [*] = ;   begin
      [*] = ;      if (acttype=gc_actiontype_runevent) then
      [*] = ;      begin
      [*] = ;         CreateEditorCustomEventFlag(elmDynamicScrollLayer, posY);
      [*] = ;         posY := posY+cMarginDelimiterHalf;
      [*] = ;         CreateEditorSelectEvent(elmDynamicScrollLayer, posY);
      [*] = ;         CreateEditorActionProvIndex(elmDynamicScrollLayer, posY);
      [*] = ;         posY := posY+cMarginDelimiterHalf;
      [*] = ;         CreateEditorWithHeroFlag(elmDynamicScrollLayer, posY);
      [*] = ;         posY := posY+cMarginDelimiter;
      [*] = ;         CreateEditorActionDelayRun(elmDynamicScrollLayer, posY);
      [*] = ;      end;
      [*] = ;      if (acttype=gc_actiontype_provinceenabled) then
      [*] = ;      begin
      [*] = ;         posY := posY+cMarginDelimiterHalf;
      [*] = ;         CreateEditorEnable(elmDynamicScrollLayer, posY);
      [*] = ;         CreateEditorRectangle(elmDynamicScrollLayer, posY);
      [*] = ;         posY := posY+cMarginDelimiter;
      [*] = ;         if (action.flag2) then
      [*] = ;         begin
      [*] = ;            CreateEditorRectangleX1Y1(elmDynamicScrollLayer, posY);
      [*] = ;            CreateEditorRectangleX2Y2(elmDynamicScrollLayer, posY);
      [*] = ;         end
      [*] = ;         else
      [*] = ;         CreateEditorActionProvIndex(elmDynamicScrollLayer, posY);
      [*] = ;      end;
      [*] = ;      if (acttype=gc_actiontype_aienabled) or (acttype=gc_actiontype_herorecruitallowed) then
      [*] = ;      begin
      [*] = ;         CreateEditorEnable(elmDynamicScrollLayer, posY);
      [*] = ;         posY := posY+cMarginDelimiter;
      [*] = ;         CreateEditorActionPlayerIndex(elmDynamicScrollLayer, posY);
      [*] = ;      end;
      [*] = ;      if (acttype=gc_actiontype_triggerenabled) then
      [*] = ;      begin
      [*] = ;         CreateEditorEnable(elmDynamicScrollLayer, posY);
      [*] = ;         posY := posY+cMarginDelimiter;
      [*] = ;         CreateEditorActionChooseTrigger(elmDynamicScrollLayer, posY);
      [*] = ;      end;
      [*] = ;      if (acttype=gc_actiontype_winlose) then
      [*] = ;      begin
      [*] = ;         CreateEditorWinLose(elmDynamicScrollLayer, posY);
      [*] = ;      end;
      [*] = ;      if (acttype=gc_actiontype_generatemap) then
      [*] = ;      begin
      [*] = ;         CreateEditorActionGenerateMode(elmDynamicScrollLayer, posY);
      [*] = ;      end;
      [*] = ;      if (acttype=gc_actiontype_buildingallowed) then
      [*] = ;      begin
      [*] = ;         CreateEditorAllowBuildingFlag(elmDynamicScrollLayer, posY);
      [*] = ;         posY := posY+cMarginDelimiter;
      [*] = ;         CreateEditorActionPlayerIndex(elmDynamicScrollLayer, posY);
      [*] = ;         CreateEditorActionQuarter(elmDynamicScrollLayer, posY);
      [*] = ;         CreateEditorActionQuarterLevel(elmDynamicScrollLayer, posY);
      [*] = ;         if (action.param1>0) and (action.param2>0) then
      [*] = ;         begin
      [*] = ;            ArrayClear;
      [*] = ;            for i:=0 to gPrototypeData.innerbuildings.number-1 do
      [*] = ;            begin
      [*] = ;               var pBuild : Integer = ParserSelectByHandleByIndex(gPrototypeData.innerbuildings.handle, i);
      [*] = ;               var quarter : Integer = ParserGetIntValueByKeyByHandle(pBuild, 'Quarter');
      [*] = ;               var quarterLevel : Integer = ParserGetIntValueByKeyByHandle(pBuild, 'QuarterLevel');
      [*] = ;               var slot : Integer = ParserGetIntValueByKeyByHandle(pBuild, 'Slot');
      [*] = ;               if (action.param1<=0) or (action.param1=quarter) then
      [*] = ;               begin
      [*] = ;                  if (action.param2<=0) or (action.param2=quarterLevel) then
      [*] = ;                  begin
      [*] = ;                     //if ((action.param3<=0) and (action.param4<=0)) or ((slot>=action.param3) and (slot<=action.param4)) then
      [*] = ;                     begin
      [*] = ;                        var encode : Integer = slot*10000+i;
      [*] = ;                        ArrayPushValue(encode);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            ArraySort(False);
      [*] = ;            CreateEditorActionBuildingSlotStart(elmDynamicScrollLayer, posY);
      [*] = ;            if (action.param3>0) then
      [*] = ;            CreateEditorActionBuildingSlotEnd(elmDynamicScrollLayer, posY);
      [*] = ;            log('slotStart = '+IntToStr(action.param3)+' slotEnd = '+IntToStr(action.param4));
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // settings scroller
      [*] = ;   SetGUIScrollEnabled(elmDynamicScrollLayer, (posY+GetGUIElementHeight(elmStaticScrollLayer))>GetGUIElementHeight(elmActionInfoHandle));
      [*] = ;   SetGUIElementHeight(elmDynamicScrollLayer, posY+cListEnd);
      [*] = ;   var elmVScroll : Integer = GetGUIElementVScroll(elmDynamicScrollLayer);
      [*] = ;   SetGUIScrollBarPosition(elmVScroll, lastScrollPos);
      [*] = ;
      [*] = ;   Result := elmActionInfoHandle;
      [*] = ;end;
      [*] = ;
      [*] = ;const cCheckBoxHeight = 27;
      [*] = ;const cDropBoxHeight = 37;
      [*] = ;const cNumOfDropBox = 8;//2;
      [*] = ;const cNumOfCheckBox = 2;
      [*] = ;const cNumOfMarginDelimiter = 6;
      [*] = ;const cNumOfStrips = 2;
      [*] = ;var height : Integer = cMarginFrameTop+GetGUITextureHeight('element.strip.240')*cNumOfStrips+cCheckBoxHeight*cNumOfCheckBox+cDropBoxHeight*cNumOfDropBox+GetGUIElementFontHeight(fontHandle)*cNumOfDropBox+cMarginDelimiter*cNumOfMarginDelimiter;
      [*] = ;if (cNumOfDropBox>0) then
      [*] = ;height := height+cMarginDropboxTop;
      [*] = ;var elmDynamicInfoHandle : Integer = ShowDynamicInfo(elmParentHandle, gScenario.temporary.trigger, dynamicDragX, dynamicDragY, 228, height);
      [*] = ;var elmActionInfoHandle : Integer = ShowActionInfo(elmDynamicInfoHandle, gScenario.temporary.trigger, gScenario.temporary.trigger.actions[gGUIEditor.selaction], cMarginFrame, 0, 228, height);
      [*] = ;
      [*] = ;// btn accept/cancel
      [*] = ;const cBtnOffset = 64;
      [*] = ;const cBtnTextOffX = 3;//-1;
      [*] = ;const cBtnTextOffY = -3;//-1;
      [*] = ;
      [*] = ;var bChanges : Boolean = _scenario_IsTriggerEqual(gScenario.temporary.trigger, gScenario.triggers[gGUIEditor.seltrigger]);
      [*] = ;
      [*] = ;const cBtnMaterialName = 'castle.hero.recruit.window.btn.recruit';
      [*] = ;const cBtnOffsetX = 2;
      [*] = ;const cBtnForceSizeX = 112;
      [*] = ;var elmFrameHandle : Integer = _gui_CreateFrameBorderExt('frame', elmDynamicInfoHandle, 'halParentLeft', 'valParentBottom', 0, cMarginFrame, GetGUIElementWidth(elmDynamicInfoHandle), GetGUITextureHeight(cBtnMaterialName+'.normal')+5, True);
      [*] = ;var elmBtnHandle : Integer = _gui_CreateButton('apply', elmFrameHandle, '', cBtnMaterialName, 'halParentLeft', 'valParentMiddle', cBtnOffsetX, 0, cBtnForceSizeX, 0, cEventState, '', cBtnAccept);
      [*] = ;var elmTextHandle : Integer = _gui_CreateText('', elmBtnHandle, 'Apply', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;if (bChanges) then
      [*] = ;SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;
      [*] = ;elmBtnHandle := _gui_CreateButton('reset', elmFrameHandle, '', cBtnMaterialName, 'halParentRightWidth', 'valParentMiddle', -cBtnOffsetX, 0, cBtnForceSizeX, 0, cEventState, '', cBtnCancel);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, 'Reset', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;if (bChanges) then
      [*] = ;SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;
      [*] = ;// Other buttons
      [*] = ;const cBtnCommonBtnMaterialName = 'common.btn';
      [*] = ;const cBtnCommonForceSizeX = 228;
      [*] = ;const cBtnCount = 1;
      [*] = ;elmFrameHandle := _gui_CreateFrameBorderExt('', elmDynamicInfoHandle, 'halParentLeft', 'valParentBottom', 0, 4+GetGUIElementPositionY(elmFrameHandle)+GetGUIElementHeight(elmFrameHandle), GetGUIElementWidth(elmDynamicInfoHandle), GetGUITextureHeight(cBtnMaterialName+'.normal')*cBtnCount+5, True);
      [*] = ;
      [*] = ;var posY : Integer = 3;
      [*] = ;
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', cBtnCommonBtnMaterialName, 'halParentMiddle', 'valParentTop', -1, posY, cBtnCommonForceSizeX, 0, cEventState, 'gui|558.ext', cBtnExecuteEvent);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, cTextExecuteEvent, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;SetGUIElementEnabled(elmBtnHandle, (gMapEditor.temporary.player.castleprovind>-1));
      [*] = ;
      [*] = ;{posY := GetGUIElementPositionY(elmBtnHandle)+GetGUIElementHeight(elmBtnHandle);
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', cBtnCommonBtnMaterialName, 'halParentMiddle', 'valParentTop', -1, posY, cBtnCommonForceSizeX, 0, cEventState, 'gui|559.ext', cBtnAddTrigger);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, cTextAddTrigger, 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;SetGUIElementEnabled(elmBtnHandle, (gMapEditor.temporary.player.castleprovind>-1));}
      [*] = ;
      [*] = ;{posY := GetGUIElementPositionY(elmBtnHandle)+GetGUIElementHeight(elmBtnHandle);
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', cBtnCommonBtnMaterialName, 'halParentMiddle', 'valParentTop', -1, posY, cBtnCommonForceSizeX, 0, cEventState, 'gui|98.ext', cBtnDiplomacy);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, 'gui|98', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;SetGUIElementEnabled(elmBtnHandle, gMapEditor.diplomacy);}
      [*] = ;
      [*] = ;if (not bVisible) then
      [*] = ;_gui_FadeElement(elmParentHandle, gc_gui_FadeTime0_2, true, true, true);
      [*] = ;_gui_RootWindowAddN(elmParentHandle);
      [*] = ;SetGUIElementPressState(elmParentHandle, cEventState);
      [*] = ;
      [*] = ;ExecuteState('GUIInvokeMouseMove');
   struct.end
section.end

