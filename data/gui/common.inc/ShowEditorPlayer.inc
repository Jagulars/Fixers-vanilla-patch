section.begin
   Name = ShowEditorPlayer
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
      [*] = ;procedure CalcPlayerGoldGemSettings(player : TEditorPlayer; var gold, gem : Integer);
      [*] = ;begin
      [*] = ;   if (player.customstartres) then
      [*] = ;   begin
      [*] = ;      gold := player.gold;
      [*] = ;      gem := player.gem;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var diffIndex : Integer;
      [*] = ;      if (player.difficulty>=0) then
      [*] = ;      diffIndex := player.difficulty
      [*] = ;      else
      [*] = ;      diffIndex := 3;
      [*] = ;      var pDifficulty : Integer = ParserSelectByHandleByIndex(gPrototypeData.difficulty.handle, diffIndex);
      [*] = ;      gold := ParserGetIntValueByKeyByHandle(pDifficulty, 'StartGold');
      [*] = ;      gem := ParserGetIntValueByKeyByHandle(pDifficulty, 'StartGem');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;const cBtnAccept = 101;
      [*] = ;const cBtnCancel = 102;
      [*] = ;const cBtnDiplomacy = 103;
      [*] = ;const cBtnInnerBuildings = 104;
      [*] = ;const cBtnHeroesList = 105;
      [*] = ;const cCheckBoxLocalLord = 602;
      [*] = ;const cCheckBoxHuman = 603;
      [*] = ;const cCheckCustomStartResources = 604;
      [*] = ;
      [*] = ;var fontHandleS, fontHandle, fontHandleL, fontHandleInput : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_small,'',fontHandleS);
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'',fontHandle);
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_large,'',fontHandleL);
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Input',gc_gui_fontsize_default,'',fontHandleInput);
      [*] = ;
      [*] = ;// Check if window was already visible, then no need to FadeIn it when show again
      [*] = ;var prevElmParentHandle : Integer = GetGUIElementIndexByNameParent('playereditor', _gui_GetLayerI());
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
      [*] = ;var windowposindex : Integer = gc_editor_WindowPlayer;
      [*] = ;if (bVisible) then
      [*] = ;begin
      [*] = ;   var elmHandle : Integer = GetGUIElementIndexByNameParent('dynamic', prevElmParentHandle);
      [*] = ;   gGUIEditor.windowpos[windowposindex].x := GetGUIElementPositionX(elmHandle);
      [*] = ;   gGUIEditor.windowpos[windowposindex].y := GetGUIElementPositionY(elmHandle);
      [*] = ;end;
      [*] = ;var dynamicDragX : Integer = gGUIEditor.windowpos[windowposindex].x;
      [*] = ;var dynamicDragY : Integer = gGUIEditor.windowpos[windowposindex].y;
      [*] = ;
      [*] = ;const cEventState = 'EventEditorPlayer';
      [*] = ;
      [*] = ;var elmParentHandle : Integer = _gui_GetOrCreateElementExtAsImage('playereditor', _gui_GetLayerI, 'halLeft', 'valTop', 0, 0, GetViewerWidth, GetViewerHeight, 0);
      [*] = ;
      [*] = ;const cTextEmpty = '';
      [*] = ;const cTextNone = 'None';
      [*] = ;const cTextUndefined = 'Undefined';
      [*] = ;const cTextRandom = 'Random';
      [*] = ;const cTextHuman = 'Human';
      [*] = ;const cTextKarma = 'Karma';
      [*] = ;const cTextCustomResources = 'Custom resources';
      [*] = ;const cTextHeaderDynamicInfo1 = 'Select player';
      [*] = ;const cTextHeaderDynamicInfo2 = 'Properties';
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
      [*] = ;const cInputTextPosX = 36;
      [*] = ;const cInputTextPosY = 1;
      [*] = ;
      [*] = ;const cMarginFrameTop = -18;
      [*] = ;var xOff : Integer = 0;
      [*] = ;var yOff : Integer = 0;
      [*] = ;
      [*] = ;// dynamic info
      [*] = ;function ShowDynamicInfo(elmParentHandle : Integer; var player : TEditorPlayer; inXOff, inYOff, inWidth, inHeight : Integer) : Integer;
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
      [*] = ;   // select player
      [*] = ;   function CreateEditorSelectPlayer(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('selectplayer', elmParent, gMapEditor.map.players, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'Choose from list', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      for i:=0 to gMapEditor.map.players-1 do
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, 'Player.'+IntToStr(i), i);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, gGUIEditor.selplayer);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;   CreateEditorSelectPlayer(elmStaticScrollLayer, posY);
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
      [*] = ;   // local lord flag
      [*] = ;   function CreateEditorLocalLordFlag(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+cMarginDropboxTop;
      [*] = ;
      [*] = ;      var text : String = GetLocaleTableListItemByID('gui', '323');
      [*] = ;      posX := 26;
      [*] = ;      var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('', elmParent, player.locallord, text, 'halParentLeft', 'valParentTop', posX, posY, cEventState, '', cCheckBoxLocalLord);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmCheckBoxHandle)+cMarginDropboxBottom;
      [*] = ;
      [*] = ;      Result := elmCheckBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // human flag
      [*] = ;   function CreateEditorHumanFlag(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+cMarginDropboxTop;
      [*] = ;
      [*] = ;      var text : String = cTextHuman;
      [*] = ;      posX := 26;
      [*] = ;      var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('', elmParent, player.human, text, 'halParentLeft', 'valParentTop', posX, posY, cEventState, '', cCheckBoxHuman);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmCheckBoxHandle)+cMarginDropboxBottom;
      [*] = ;
      [*] = ;      Result := elmCheckBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // player id
      [*] = ;   function CreateEditorPlayerID(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var count : Integer;
      [*] = ;      if (player.locallord) or (player.human) then
      [*] = ;      count := 1
      [*] = ;      else
      [*] = ;      count := gPrototypeData.players.number;
      [*] = ;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('playerid', elmParent, count, 12, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'Player ID', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;
      [*] = ;      var ind : Integer = 0;
      [*] = ;      if (player.locallord) then
      [*] = ;      begin
      [*] = ;         GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('gui', '323'), 0);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (player.human) then
      [*] = ;      begin
      [*] = ;         GUIListBoxAddItem(elmListBoxHandle, cTextHuman, 0);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         GUIListBoxAddItem(elmListBoxHandle, cTextUndefined, 0);
      [*] = ;         for i:=1 to gPrototypeData.players.number-1 do
      [*] = ;         GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('players', IntToStr(i)), i);
      [*] = ;         SetGUIListBoxItemIndexSilent(elmListBoxHandle, player.id);
      [*] = ;         if (player.id<0) then
      [*] = ;         ind := 0
      [*] = ;         else
      [*] = ;         ind := player.id;
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, ind);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // difficulty
      [*] = ;   function CreateEditorDifficulty(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('difficulty', elmParent, gPrototypeData.difficulty.number+1, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'gui|218', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextUndefined, -1);
      [*] = ;      for i:=0 to gPrototypeData.difficulty.number-1 do
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('gui', IntToStr(219+i)), i);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, player.difficulty+1);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // union
      [*] = ;   function CreateEditorUnion(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('union', elmParent, gPrototypeData.races.number-1, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'gui|241', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextNone, 0);
      [*] = ;      for i:=2 to gPrototypeData.races.number-1 do
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('races', IntToStr(i)), i);
      [*] = ;      var ind : Integer = 0;
      [*] = ;      if (player.union>1) then
      [*] = ;      ind := player.union-1;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, ind);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // Karma
      [*] = ;   function CreateEditorKarma(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var karma : Integer = player.karma;
      [*] = ;      if (not (gMapEditor.temporary.player.human)) and (gMapEditor.temporary.player.id>-1) then
      [*] = ;      karma := ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(gPrototypeData.players.handle, gMapEditor.temporary.player.id), 'Karma');
      [*] = ;      var bEnabled : Boolean = player.human;
      [*] = ;      var elmInputHandle : Integer = CreateInputBoxSimple('karma', elmParent, IntToStr(karma), 'halParentMiddle', 'valParentTop', 0, posY+2, cInputBoxWidth, 5, cEventState, 'gui|747', bEnabled, cInputTextPosX, cInputTextPosY, 'halLeft', 'valMiddle', fontHandleInput, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;      SetGUIElementEnabled(GetGUIElementIndexByNameParent('text', elmInputHandle), False);
      [*] = ;      _gui_InputBoxSetupNumCharFilter(elmInputHandle, True, True);
      [*] = ;
      [*] = ;      elmTextHandle := _gui_CreateText('', elmInputHandle, cTextKarma, 'halParentLeft', 'valParentTop', 0, -18, GetGUIElementWidth(elmInputHandle), GetGUIElementHeight(elmInputHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmInputHandle);
      [*] = ;
      [*] = ;      Result := elmInputHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // custom starting resources
      [*] = ;   function CreateEditorCustomStartResourcesFlag(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+cMarginDropboxTop;
      [*] = ;
      [*] = ;      posX := 26;
      [*] = ;      var gold, gem : Integer;
      [*] = ;      CalcPlayerGoldGemSettings(player, gold, gem);
      [*] = ;      var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('', elmParent, player.customstartres, cTextCustomResources, 'halParentLeft', 'valParentTop', posX, posY, cEventState, '', cCheckCustomStartResources);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmCheckBoxHandle)+cMarginDropboxBottom;
      [*] = ;
      [*] = ;      Result := elmCheckBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // Gold
      [*] = ;   function CreateEditorGold(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var gold, gem : Integer;
      [*] = ;      CalcPlayerGoldGemSettings(player, gold, gem);
      [*] = ;      var elmInputHandle : Integer = CreateInputBoxSimple('gold', elmParent, IntToStr(gold), 'halParentMiddle', 'valParentTop', 0, posY+2, cInputBoxWidth, 7, cEventState, 'gui|747', player.customstartres, cInputTextPosX, cInputTextPosY, 'halLeft', 'valMiddle', fontHandleInput, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmInputHandle, 'gui|189', 'halParentLeft', 'valParentTop', 0, -18, GetGUIElementWidth(elmInputHandle), GetGUIElementHeight(elmInputHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      _gui_InputBoxSetupNumCharFilter(elmInputHandle, True, False);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmInputHandle);
      [*] = ;
      [*] = ;      Result := elmInputHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // Gem
      [*] = ;   function CreateEditorGem(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var gold, gem : Integer;
      [*] = ;      CalcPlayerGoldGemSettings(player, gold, gem);
      [*] = ;      var elmInputHandle : Integer = CreateInputBoxSimple('gem', elmParent, IntToStr(gem), 'halParentMiddle', 'valParentTop', 0, posY+2, cInputBoxWidth, 7, cEventState, 'gui|747', player.customstartres, cInputTextPosX, cInputTextPosY, 'halLeft', 'valMiddle', fontHandleInput, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmInputHandle, 'gui|190', 'halParentLeft', 'valParentTop', 0, -18, GetGUIElementWidth(elmInputHandle), GetGUIElementHeight(elmInputHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      _gui_InputBoxSetupNumCharFilter(elmInputHandle, True, False);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmInputHandle);
      [*] = ;
      [*] = ;      Result := elmInputHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   CreateEditorLocalLordFlag(elmDynamicScrollLayer, posY);
      [*] = ;   CreateEditorHumanFlag(elmDynamicScrollLayer, posY);
      [*] = ;   posY := posY+cMarginDelimiter;
      [*] = ;   CreateEditorPlayerID(elmDynamicScrollLayer, posY);
      [*] = ;   CreateEditorDifficulty(elmDynamicScrollLayer, posY);
      [*] = ;   CreateEditorUnion(elmDynamicScrollLayer, posY);
      [*] = ;   posY := posY+cMarginDelimiterHalf;
      [*] = ;   CreateEditorCustomStartResourcesFlag(elmDynamicScrollLayer, posY);
      [*] = ;   posY := posY+cMarginDelimiterHalf;
      [*] = ;   CreateEditorGold(elmDynamicScrollLayer, posY);
      [*] = ;   CreateEditorGem(elmDynamicScrollLayer, posY);
      [*] = ;   if (player.human) or ((not player.locallord) and (player.id>0)) then
      [*] = ;   CreateEditorKarma(elmDynamicScrollLayer, posY);
      [*] = ;   posY := posY+cMarginDelimiter;
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
      [*] = ;const cCheckBoxHeight = 27;
      [*] = ;const cDropBoxHeight = 37;
      [*] = ;const cNumOfDropBox = 7;
      [*] = ;const cNumOfCheckBox = 3;
      [*] = ;const cNumOfMarginDelimiter = 4;
      [*] = ;const cNumOfStrips = 2;
      [*] = ;var height : Integer = cMarginFrameTop+GetGUITextureHeight('element.strip.240')*cNumOfStrips+cCheckBoxHeight*cNumOfCheckBox+cDropBoxHeight*cNumOfDropBox+GetGUIElementFontHeight(fontHandle)*cNumOfDropBox+cMarginDelimiter*cNumOfMarginDelimiter;
      [*] = ;if (cNumOfDropBox>0) then
      [*] = ;height := height+cMarginDropboxTop;
      [*] = ;var elmDynamicInfoHandle : Integer = ShowDynamicInfo(elmParentHandle, gMapEditor.temporary.player, dynamicDragX, dynamicDragY, 228, height);
      [*] = ;
      [*] = ;// btn accept/cancel
      [*] = ;const cBtnOffset = 64;
      [*] = ;
      [*] = ;const cBtnTextOffX = 3;//-1;
      [*] = ;const cBtnTextOffY = -3;//-1;
      [*] = ;//var elmBtnHandle : Integer = _gui_CreateButton('', elmDynamicInfoHandle, '', 'common.btn', 'halParentMiddle', 'valParentBottom', 0, 0, 0, 0, cEventState, '', cBtnAccept);
      [*] = ;//var elmTextHandle : Integer = _gui_CreateText('', elmBtnHandle, 'Apply', 'halParentLeft', 'valParentTop', 3, cBtnTextOffY, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;//if (mTreaty=cOfferPeaceBtnTag) or (bMessageSent) then
      [*] = ;//SetGUIElementEnabled(elmBtnHandle, True);
      [*] = ;
      [*] = ;var bChanges : Boolean = _editor_IsPlayerEqual(gMapEditor.temporary.player, gMapEditor.players[gGUIEditor.selplayer]);
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
      [*] = ;const cBtnCount = 3;
      [*] = ;elmFrameHandle := _gui_CreateFrameBorderExt('', elmDynamicInfoHandle, 'halParentLeft', 'valParentBottom', 0, 4+GetGUIElementPositionY(elmFrameHandle)+GetGUIElementHeight(elmFrameHandle), GetGUIElementWidth(elmDynamicInfoHandle), GetGUITextureHeight(cBtnMaterialName+'.normal')*cBtnCount+5, True);
      [*] = ;
      [*] = ;var posY : Integer = 3;
      [*] = ;
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', cBtnCommonBtnMaterialName, 'halParentMiddle', 'valParentTop', -1, posY, cBtnCommonForceSizeX, 0, cEventState, 'gui|558.ext', cBtnInnerBuildings);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, 'gui|558', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;SetGUIElementEnabled(elmBtnHandle, (gMapEditor.temporary.player.castleprovind>-1));
      [*] = ;
      [*] = ;posY := GetGUIElementPositionY(elmBtnHandle)+GetGUIElementHeight(elmBtnHandle);
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', cBtnCommonBtnMaterialName, 'halParentMiddle', 'valParentTop', -1, posY, cBtnCommonForceSizeX, 0, cEventState, 'gui|559.ext', cBtnHeroesList);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, 'gui|586', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;SetGUIElementEnabled(elmBtnHandle, (gMapEditor.temporary.player.castleprovind>-1));
      [*] = ;
      [*] = ;posY := GetGUIElementPositionY(elmBtnHandle)+GetGUIElementHeight(elmBtnHandle);
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', cBtnCommonBtnMaterialName, 'halParentMiddle', 'valParentTop', -1, posY, cBtnCommonForceSizeX, 0, cEventState, 'gui|98.ext', cBtnDiplomacy);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, 'gui|98', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;SetGUIElementEnabled(elmBtnHandle, gMapEditor.diplomacy);
      [*] = ;
      [*] = ;if (not bVisible) then
      [*] = ;_gui_FadeElement(elmParentHandle, gc_gui_FadeTime0_2, true, true, true);
      [*] = ;_gui_RootWindowAddN(elmParentHandle);
      [*] = ;SetGUIElementPressState(elmParentHandle, cEventState);
      [*] = ;
      [*] = ;ExecuteState('GUIInvokeMouseMove');
   struct.end
section.end

