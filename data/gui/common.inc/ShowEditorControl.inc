section.begin
   Name = ShowEditorControl
   Code : struct.begin
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
      [*] = ;var fontHandleS, fontHandle, fontHandleL : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_small,'',fontHandleS);
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'',fontHandle);
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_large,'',fontHandleL);
      [*] = ;
      [*] = ;// Check if window was already visible, then no need to FadeIn it when show again
      [*] = ;var prevElmParentHandle : Integer = GetGUIElementIndexByNameParent('editorcontrol', _gui_GetLayerI());
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
      [*] = ;var windowposindex : Integer = gc_editor_WindowControl;
      [*] = ;if (bVisible) then
      [*] = ;begin
      [*] = ;   var elmHandle : Integer = GetGUIElementIndexByNameParent('dynamic', prevElmParentHandle);
      [*] = ;   gGUIEditor.windowpos[windowposindex].x := GetGUIElementPositionX(elmHandle);
      [*] = ;   gGUIEditor.windowpos[windowposindex].y := GetGUIElementPositionY(elmHandle);
      [*] = ;end;
      [*] = ;var dynamicDragX : Integer = gGUIEditor.windowpos[windowposindex].x;
      [*] = ;var dynamicDragY : Integer = gGUIEditor.windowpos[windowposindex].y;
      [*] = ;
      [*] = ;const cEventState = 'EventEditorControl';
      [*] = ;const cBtnAccept = 101;
      [*] = ;const cBtnCancel = 102;
      [*] = ;const cBtnSaveToFile = 103;
      [*] = ;const cBtnLoadFromFile = 104;
      [*] = ;const cBtnGenerateMap = 105;
      [*] = ;const cBtnGetCurrentMapData = 106;
      [*] = ;const cBtnClearMapData = 107;
      [*] = ;const cBtnCopy = 108;
      [*] = ;const cBtnPaste = 109;
      [*] = ;const cBtnFastGenerateMap = 110;
      [*] = ;const cBtnRunMap = 111;
      [*] = ;const cBtnQuestionDialogGenerateMap = 130;
      [*] = ;const cBtnQuestionDialogFastGenerateMap = 131;
      [*] = ;const cCheckBoxDiplomacy = 601;
      [*] = ;const cCheckBoxFog = 602;
      [*] = ;
      [*] = ;var elmParentHandle : Integer = _gui_GetOrCreateElementExtAsImage('editorcontrol', _gui_GetLayerI, 'halLeft', 'valTop', 0, 0, GetViewerWidth, GetViewerHeight, 0);
      [*] = ;
      [*] = ;const cTextEmpty = '';
      [*] = ;const cTextNone = 'None';
      [*] = ;const cTextUndefined = 'Undefined';
      [*] = ;const cTextRandom = 'Random';
      [*] = ;const cTextHeaderStaticInfo = 'Map settings';
      [*] = ;const cTextHeaderDynamicInfo = 'Properties';
      [*] = ;
      [*] = ;{const cMarginDropboxToCheckbox = 12;
      [*] = ;const cMarginCheckboxToDropbox = 28;
      [*] = ;const cMarginCheckboxToCheckbox = 4;}
      [*] = ;const cMarginDelimiter = 6;
      [*] = ;const cMarginDelimiterHalf = cMarginDelimiter div 2;
      [*] = ;const cMarginDropboxTop = 2;
      [*] = ;const cMarginDropboxBottom = 2;
      [*] = ;const cMarginFrame = 4;
      [*] = ;const cListEnd = cMarginDelimiter*2;
      [*] = ;
      [*] = ;const cMarginFrameTop = -18;
      [*] = ;var xOff : Integer = 0;
      [*] = ;var yOff : Integer = 0;
      [*] = ;
      [*] = ;function ShowStaticInfo(elmParentHandle : Integer; mapeditor : TMapEditor; map : TMap; inXOff, inYOff, inWidth, inHeight : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var textYOffset : Integer = GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;   var posX : Integer = inXOff;
      [*] = ;   var posY : Integer = inYOff;
      [*] = ;   var width : Integer = inWidth;
      [*] = ;   var height : Integer = inHeight;
      [*] = ;
      [*] = ;   var elmStaticInfoHandle : Integer = _gui_CreateFrameBorderExt('static', elmParentHandle, 'halParentLeft', 'valParentTop', posX, posY, width, height, True);
      [*] = ;   var elmStripHandle : Integer = _gui_CreateImage('', elmStaticInfoHandle, 'element.strip.240', 'halParentMiddle', 'valParentTop', 0, cMarginFrameTop, 0, 0, 0);
      [*] = ;   var elmTextHandle : Integer = _gui_CreateText('', elmStripHandle, cTextHeaderStaticInfo, 'halParentLeft', 'valParentTop', 0, -2, GetGUIElementWidth(elmStripHandle), GetGUIElementHeight(elmStripHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;   //SetGUIAllowDrag(elmStaticInfoHandle, True);
      [*] = ;   SetGUIAllowEvents(elmStaticInfoHandle, True, False, False);
      [*] = ;
      [*] = ;   var sizeX : Integer = GetGUIElementWidth(elmStaticInfoHandle);
      [*] = ;   var sizeY : Integer = GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;   posY := GetGUIElementPositionY(elmStripHandle)+GetGUIElementHeight(elmStripHandle)-3;
      [*] = ;   var text : String = 'ID: '+IntToStr(mapeditor.id);
      [*] = ;   _gui_CreateText('staticinfotext', elmStaticInfoHandle, text, 'halParentLeft', 'valParentTop', 0, posY, sizeX, sizeY, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;
      [*] = ;   posY := posY+textYOffset;
      [*] = ;   text := 'Name: '+mapeditor.name;
      [*] = ;   _gui_CreateText('staticinfotext', elmStaticInfoHandle, text, 'halParentLeft', 'valParentTop', 0, posY, sizeX, sizeY, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;
      [*] = ;   posY := posY+textYOffset;
      [*] = ;   text := 'Map size: '+IntToStr(map.x)+'x'+IntToStr(map.y);
      [*] = ;   _gui_CreateText('staticinfotext', elmStaticInfoHandle, text, 'halParentLeft', 'valParentTop', 0, posY, sizeX, sizeY, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;
      [*] = ;   Result := elmStaticInfoHandle;
      [*] = ;end;
      [*] = ;
      [*] = ;// dynamic info
      [*] = ;function ShowDynamicInfo(elmParentHandle : Integer; temporary : TEditorTemporary; map : TMap; inXOff, inYOff, inWidth, inHeight : Integer) : Integer;
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
      [*] = ;   var elmDynamicScrollLayer : Integer = CreateMapEditorScroller('scroll_layer', elmDynamicInfoHandle, 'halParentLeft', 'valParentTop', gc_gui_material_blank_0, 0, 0, scrollLayerWidth, scrollLayerHeight, -17, 0, 32, scrollLayerHeight, True);
      [*] = ;
      [*] = ;   var elmStripHandle : Integer = _gui_CreateImage('', elmDynamicInfoHandle, 'element.strip.240', 'halParentMiddle', 'valParentTop', 0, cMarginFrameTop, 0, 0, 0);
      [*] = ;   var elmTextHandle : Integer = _gui_CreateText('', elmStripHandle, cTextHeaderDynamicInfo, 'halParentLeft', 'valParentTop', 0, -2, GetGUIElementWidth(elmStripHandle), GetGUIElementHeight(elmStripHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;   posY := GetGUIElementPositionY(elmStripHandle)+GetGUIElementHeight(elmStripHandle);
      [*] = ;
      [*] = ;   function CreateEditorFogOfWarFlag(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+cMarginDropboxTop;
      [*] = ;
      [*] = ;      var text : String = GetLocaleTableListItemByID('gui', '680');
      [*] = ;      var hint : String = '';
      [*] = ;      posX := 26;
      [*] = ;      var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('', elmParent, temporary.fog, text, 'halParentLeft', 'valParentTop', posX, posY, cEventState, hint, cCheckBoxFog);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmCheckBoxHandle)+cMarginDropboxBottom;
      [*] = ;
      [*] = ;      Result := elmCheckBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   function CreateEditorDiplomacyFlag(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+cMarginDropboxTop;
      [*] = ;
      [*] = ;      var text : String = GetLocaleTableListItemByID('gui', '681');
      [*] = ;      var hint : String = '';
      [*] = ;      posX := 26;
      [*] = ;      var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('', elmParent, temporary.diplomacy, text, 'halParentLeft', 'valParentTop', posX, posY, cEventState, hint, cCheckBoxDiplomacy);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmCheckBoxHandle)+cMarginDropboxBottom;
      [*] = ;
      [*] = ;      Result := elmCheckBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   function CreateEditorMapSize(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      const valueCount = 8;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('mapsize', elmParent, valueCount, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'Map size', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      for i:=0 to valueCount-1 do
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('shard', IntToStr(i)), i);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, (map.x-6) div 2);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   function CreateEditorPlayers(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('players', elmParent, gc_MaxCustomMapPlayer-1, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'Players', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      for i:=2 to gc_MaxCustomMapPlayer do
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, IntToStr(i), i);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, map.players-2);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   function CreateEditorNeutrals(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      const valueCount = 5;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('neutrals', elmParent, valueCount, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'Neutrals strength', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      for i:=0 to valueCount-1 do
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('gui', IntToStr(382-i)), i);
      [*] = ;
      [*] = ;      var ind : Integer = 0;
      [*] = ;      case map.neutrals of
      [*] = ;         9..12 : ind := 1;
      [*] = ;         5..8 : ind := 2;
      [*] = ;         2..4 : ind := 3;
      [*] = ;         0..1 : ind := 4;
      [*] = ;         else //13..20
      [*] = ;         ind := 0;
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, ind);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   function CreateEditorResources(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      const valueCount = 5;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('resources', elmParent, valueCount, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'Resource density', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      for i:=0 to valueCount-1 do
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('gui', IntToStr(373+i)), i);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, map.resource);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   function CreateEditorSite(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      const valueCount = 5;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('sites', elmParent, valueCount, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'Site density', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      for i:=0 to valueCount-1 do
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('gui', IntToStr(373+i)), i);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, map.site);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   function CreateEditorPopulation(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      const valueCount = 5;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('population', elmParent, valueCount, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'Population', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      for i:=0 to valueCount-1 do
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('gui', IntToStr(373+i)), i);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, map.population);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   function CreateEditorWorldRule(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      var i,elmListBoxHandle,wr_no : Integer;
      [*] = ;      var wr_array : array [0..gc_max_worldrules] of Integer;
      [*] = ;      var pWorldRule,worldRuleID : Integer;
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;      wr_no := 0;
      [*] = ;      for i:=0 to gPrototypeData.worldrules.number-1 do
      [*] = ;      begin
      [*] = ;         pWorldRule :=  ParserSelectByHandleByIndex(gPrototypeData.worldrules.handle,i);
      [*] = ;         worldRuleID := ParserGetIntValueByKeyByHandle(pWorldRule, 'WorldRuleID');
      [*] = ;         if (worldRuleID>0) then
      [*] = ;         begin
      [*] = ;            wr_array[wr_no] := i;
      [*] = ;            wr_no := wr_no + 1;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      elmListBoxHandle := _gui_CreateListBoxMiddle('worldrule', elmParent, wr_no+1, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'World rule', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextNone, 0);
      [*] = ;      for i:=0 to wr_no-1 do
      [*] = ;      begin
      [*] = ;         GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('worldrule', IntToStr(wr_array[i])),wr_array[i]);
      [*] = ;      end;
      [*] = ;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, temporary.worldrule);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   CreateEditorFogOfWarFlag(elmDynamicScrollLayer, posY);
      [*] = ;   CreateEditorDiplomacyFlag(elmDynamicScrollLayer, posY);
      [*] = ;   posY := posY+cMarginDelimiter;
      [*] = ;   CreateEditorMapSize(elmDynamicScrollLayer, posY);
      [*] = ;   CreateEditorPlayers(elmDynamicScrollLayer, posY);
      [*] = ;   CreateEditorWorldRule(elmDynamicScrollLayer, posY);
      [*] = ;   CreateEditorNeutrals(elmDynamicScrollLayer, posY);
      [*] = ;   //CreateEditorResources(elmDynamicScrollLayer, posY);
      [*] = ;   CreateEditorSite(elmDynamicScrollLayer, posY);
      [*] = ;   CreateEditorPopulation(elmDynamicScrollLayer, posY);
      [*] = ;
      [*] = ;   // settings scroller
      [*] = ;   SetGUIScrollEnabled(elmDynamicScrollLayer, (posY>GetGUIElementHeight(elmDynamicInfoHandle)));
      [*] = ;   SetGUIElementHeight(elmDynamicScrollLayer, posY);
      [*] = ;   var elmVScroll : Integer = GetGUIElementVScroll(elmDynamicScrollLayer);
      [*] = ;   SetGUIScrollBarPosition(elmVScroll, lastScrollPos);
      [*] = ;
      [*] = ;   Result := elmDynamicInfoHandle;
      [*] = ;end;
      [*] = ;
      [*] = ;const cInfoHeightBasis = 40;
      [*] = ;var staticInfoLineCount : Integer = 3;
      [*] = ;var h : Integer = cInfoHeightBasis+GetGUIElementFontHeight(fontHandle)*staticInfoLineCount;
      [*] = ;var elmStaticInfoHandle : Integer = ShowStaticInfo(elmParentHandle, gMapEditor, gMapEditor.map, 0, 0, 228, h);
      [*] = ;
      [*] = ;const cListStart = 4;
      [*] = ;const cListFinish = 17;
      [*] = ;
      [*] = ;const cCheckBoxHeight = 27;
      [*] = ;const cDropBoxHeight = 37;
      [*] = ;const cNumOfDropBox = 6;
      [*] = ;const cNumOfCheckBox = 2;
      [*] = ;const cNumOfMarginDelimiter = 3;
      [*] = ;const cNumOfStrips = 1;
      [*] = ;var height : Integer = cMarginFrameTop+GetGUITextureHeight('element.strip.240')*cNumOfStrips+cCheckBoxHeight*cNumOfCheckBox+cDropBoxHeight*cNumOfDropBox+GetGUIElementFontHeight(fontHandle)*cNumOfDropBox+cMarginDelimiter*cNumOfMarginDelimiter;
      [*] = ;if (cNumOfDropBox>0) then
      [*] = ;height := height+cMarginDropboxTop;
      [*] = ;
      [*] = ;//var height : Integer = cListStart+cCheckBoxHeight*2+cDropBoxHeight*6+GetGUIElementFontHeight(fontHandle)*6+cListFinish;
      [*] = ;var elmDynamicInfoHandle : Integer = ShowDynamicInfo(elmParentHandle, gMapEditor.temporary, gMapEditor.temporary.map, dynamicDragX, dynamicDragY, 228, height);
      [*] = ;AttachGUIElementToElement(elmStaticInfoHandle, elmDynamicInfoHandle);
      [*] = ;SetGUIElementPosition(elmStaticInfoHandle, 0, -GetGUIElementHeight(elmStaticInfoHandle)-cMarginFrame);
      [*] = ;GUIElementSendToBack(elmStaticInfoHandle);
      [*] = ;
      [*] = ;// btn accept/cancel
      [*] = ;const cBtnOffset = 64;
      [*] = ;
      [*] = ;const cBtnTextOffX = 3;//-1;
      [*] = ;const cBtnTextOffY = -3;//-1;
      [*] = ;
      [*] = ;var bChanges : Boolean = _editor_IsMapSettingsEqual(gMapEditor, gMapEditor.temporary);
      [*] = ;
      [*] = ;const cBtnMaterialName = 'castle.hero.recruit.window.btn.recruit';
      [*] = ;const cBtnOffsetX = 2;
      [*] = ;const cBtnForceSizeX = 112;
      [*] = ;var elmFrameHandle : Integer = _gui_CreateFrameBorderExt('', elmDynamicInfoHandle, 'halParentLeft', 'valParentBottom', 0, 4, GetGUIElementWidth(elmDynamicInfoHandle), GetGUITextureHeight(cBtnMaterialName+'.normal')+5, True);
      [*] = ;var elmBtnHandle : Integer = _gui_CreateButton('', elmFrameHandle, '', cBtnMaterialName, 'halParentLeft', 'valParentMiddle', cBtnOffsetX, 0, cBtnForceSizeX, 0, cEventState, '', cBtnAccept);
      [*] = ;var elmTextHandle : Integer = _gui_CreateText('', elmBtnHandle, 'Apply', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;if (bChanges) then
      [*] = ;SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', cBtnMaterialName, 'halParentRightWidth', 'valParentMiddle', -cBtnOffsetX, 0, cBtnForceSizeX, 0, cEventState, '', cBtnCancel);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, 'Reset', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;if (bChanges) then
      [*] = ;SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;
      [*] = ;// Other buttons
      [*] = ;const cBtnCommonBtnMaterialName = 'common.btn';
      [*] = ;const cBtnCommonForceSizeX = 228;
      [*] = ;const cBtnCount = 9;
      [*] = ;elmFrameHandle := _gui_CreateFrameBorderExt('', elmDynamicInfoHandle, 'halParentLeft', 'valParentBottom', 0, 4+GetGUIElementPositionY(elmFrameHandle)+GetGUIElementHeight(elmFrameHandle), GetGUIElementWidth(elmDynamicInfoHandle), GetGUITextureHeight(cBtnMaterialName+'.normal')*cBtnCount+5, True);
      [*] = ;
      [*] = ;var posY : Integer = 3;
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', cBtnCommonBtnMaterialName, 'halParentMiddle', 'valParentTop', -1, posY, cBtnCommonForceSizeX, 0, cEventState, '', cBtnCopy);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, 'Copy', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;
      [*] = ;posY := GetGUIElementPositionY(elmBtnHandle)+GetGUIElementHeight(elmBtnHandle);
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', cBtnCommonBtnMaterialName, 'halParentMiddle', 'valParentTop', -1, posY, cBtnCommonForceSizeX, 0, cEventState, '', cBtnPaste);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, 'Paste', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;
      [*] = ;posY := GetGUIElementPositionY(elmBtnHandle)+GetGUIElementHeight(elmBtnHandle);
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', cBtnCommonBtnMaterialName, 'halParentMiddle', 'valParentTop', -1, posY, cBtnCommonForceSizeX, 0, cEventState, '', cBtnClearMapData);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, 'Clear grid data', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;
      [*] = ;posY := GetGUIElementPositionY(elmBtnHandle)+GetGUIElementHeight(elmBtnHandle);
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', cBtnCommonBtnMaterialName, 'halParentMiddle', 'valParentTop', -1, posY, cBtnCommonForceSizeX, 0, cEventState, '', cBtnGetCurrentMapData);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, 'Get from current map', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;
      [*] = ;posY := GetGUIElementPositionY(elmBtnHandle)+GetGUIElementHeight(elmBtnHandle);
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', cBtnCommonBtnMaterialName, 'halParentMiddle', 'valParentTop', -1, posY, cBtnCommonForceSizeX, 0, cEventState, '', cBtnSaveToFile);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, 'Save to file', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;
      [*] = ;posY := GetGUIElementPositionY(elmBtnHandle)+GetGUIElementHeight(elmBtnHandle);
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', cBtnCommonBtnMaterialName, 'halParentMiddle', 'valParentTop', -1, posY, cBtnCommonForceSizeX, 0, cEventState, '', cBtnLoadFromFile);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, 'Load from file', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;
      [*] = ;posY := GetGUIElementPositionY(elmBtnHandle)+GetGUIElementHeight(elmBtnHandle);
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', cBtnCommonBtnMaterialName, 'halParentMiddle', 'valParentTop', -1, posY, cBtnCommonForceSizeX, 0, cEventState, '', cBtnGenerateMap);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, 'Generate map', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;
      [*] = ;posY := GetGUIElementPositionY(elmBtnHandle)+GetGUIElementHeight(elmBtnHandle);
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', cBtnCommonBtnMaterialName, 'halParentMiddle', 'valParentTop', -1, posY, cBtnCommonForceSizeX, 0, cEventState, '', cBtnFastGenerateMap);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, 'Fast generate map', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;
      [*] = ;posY := GetGUIElementPositionY(elmBtnHandle)+GetGUIElementHeight(elmBtnHandle);
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', cBtnCommonBtnMaterialName, 'halParentMiddle', 'valParentTop', -1, posY, cBtnCommonForceSizeX, 0, cEventState, '', cBtnRunMap);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, 'Play map', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;
      [*] = ;if (not bVisible) then
      [*] = ;_gui_FadeElement(elmParentHandle, gc_gui_FadeTime0_2, true, true, true);
      [*] = ;_gui_RootWindowAddN(elmParentHandle);
      [*] = ;SetGUIElementPressState(elmParentHandle, cEventState);
      [*] = ;
      [*] = ;ExecuteState('GUIInvokeMouseMove');
   struct.end
section.end

