section.begin
   Name = ShowEditorProvince
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
      [*] = ;function IsProvinceTypeAvailable(provinceType : Integer; grid : TEditorGrid) : Boolean;
      [*] = ;begin
      [*] = ;   Result := False;
      [*] = ;   const cCastleProvType = 7;
      [*] = ;   if (grid.terrain>=0) {and (grid.terrain<=4)} then
      [*] = ;   begin
      [*] = ;      if (grid.castle) then
      [*] = ;      begin
      [*] = ;         if (provinceType=cCastleProvType) then
      [*] = ;         Result := True;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var pProvinceType : Integer = ParserSelectByHandleByIndex(gPrototypeData.provincetypes.handle, provinceType);
      [*] = ;         var pTerrainType : Integer = ParserSelectByHandleByKey(pProvinceType, 'TerrainType');
      [*] = ;         var sTerrainType : String = ParserGetValueByKeyByHandle(ParserSelectByHandleByIndex(gPrototypeData.terraintypes.handle, grid.terrain), 'Name');
      [*] = ;         var freq : Integer = ParserGetIntValueByKeyByHandle(pTerrainType, sTerrainType);
      [*] = ;         if (freq>0) then
      [*] = ;         Result := True;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function IsDefenderAvailable(defenderID : Integer; grid : TEditorGrid) : Boolean;
      [*] = ;begin
      [*] = ;   Result := False;
      [*] = ;   if (grid.terrain>=0) and (grid.terrain<=4) then
      [*] = ;   begin
      [*] = ;      var pDefenderID : Integer = ParserSelectByHandleByIndex(gPrototypeData.defenders.handle, defenderID);
      [*] = ;      var pTerrainType : Integer = ParserSelectByHandleByKey(pDefenderID, 'TerrainType');
      [*] = ;      var sTerrainType : String = ParserGetValueByKeyByHandle(ParserSelectByHandleByIndex(gPrototypeData.terraintypes.handle, grid.terrain), 'Name');
      [*] = ;      var available : Boolean = ParserGetBoolValueByKeyByHandle(pTerrainType, sTerrainType);
      [*] = ;      if (available) then
      [*] = ;      Result := True;
      [*] = ;   end;
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
      [*] = ;const cBtnAccept = 101;
      [*] = ;const cBtnCancel = 102;
      [*] = ;const cBtnOuterBuild = 103;
      [*] = ;const cBtnDefender = 104;
      [*] = ;const cBtnSiteList = 105;
      [*] = ;const cCheckBoxCastle = 601;
      [*] = ;const cCheckBoxResExplored = 602;
      [*] = ;const cCheckBoxEnabled = 603;
      [*] = ;
      [*] = ;var fontHandleS, fontHandle, fontHandleL, fontHandleInput : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_small,'',fontHandleS);
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'',fontHandle);
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_large,'',fontHandleL);
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Input',gc_gui_fontsize_default,'',fontHandleInput);
      [*] = ;
      [*] = ;// Check if window was already visible, then no need to FadeIn it when show again
      [*] = ;var prevElmParentHandle : Integer = GetGUIElementIndexByNameParent('proveditor', _gui_GetLayerI());
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
      [*] = ;var windowposindex : Integer = gc_editor_WindowProvince;
      [*] = ;if (bVisible) then
      [*] = ;begin
      [*] = ;   var elmHandle : Integer = GetGUIElementIndexByNameParent('dynamic', prevElmParentHandle);
      [*] = ;   gGUIEditor.windowpos[windowposindex].x := GetGUIElementPositionX(elmHandle);
      [*] = ;   gGUIEditor.windowpos[windowposindex].y := GetGUIElementPositionY(elmHandle);
      [*] = ;end;
      [*] = ;var dynamicDragX : Integer = gGUIEditor.windowpos[windowposindex].x;
      [*] = ;var dynamicDragY : Integer = gGUIEditor.windowpos[windowposindex].y;
      [*] = ;
      [*] = ;const cEventState = 'EventEditorProvince';
      [*] = ;
      [*] = ;var pProvince : Integer = gGUIEditor.selgridparser;
      [*] = ;var index : Integer = gGUIEditor.selgrid;
      [*] = ;
      [*] = ;var elmParentHandle : Integer = _gui_GetOrCreateElementExtAsImage('proveditor', _gui_GetLayerI, 'halLeft', 'valTop', 0, 0, GetViewerWidth, GetViewerHeight, 0);
      [*] = ;
      [*] = ;const cTextEmpty = '';
      [*] = ;const cTextNone = 'None';
      [*] = ;const cTextUndefined = 'Undefined';
      [*] = ;const cTextRandom = 'Random';
      [*] = ;const cTextNeedCastle = 'Need capital province';
      [*] = ;const cTextNeedPlayerOrTerrain = 'Wrong province type';
      [*] = ;const cTextProvinceEnabled = 'Generate';
      [*] = ;const cTextNoSites = 'No locations';
      [*] = ;const cTextNoFreePlayers = 'All players castles already set. To setup more players, change "max players" in Map settings';
      [*] = ;const cTextHeaderStaticInfo = 'Province';
      [*] = ;const cTextHeaderDynamicInfo = 'Properties';
      [*] = ;const cTextProvName = 'Province name';
      [*] = ;const cTextProvNameHint = 'Use delimiter sign | to set LocaleTableID|LangKey';
      [*] = ;const cUnavailableBtnAlpha = 0.15;
      [*] = ;
      [*] = ;const cMarginDelimiter = 6;
      [*] = ;const cMarginDelimiterHalf = cMarginDelimiter div 2;
      [*] = ;const cMarginDropboxTop = 2;
      [*] = ;const cMarginDropboxBottom = 2;
      [*] = ;const cMarginFrame = 4;
      [*] = ;const cListEnd = cMarginDelimiter*2;
      [*] = ;
      [*] = ;//const cInputBoxWidth = 228-64;
      [*] = ;const cInputBoxWidthWide = 228;
      [*] = ;const cInputTextPosX = 36;
      [*] = ;const cInputTextPosY = 1;
      [*] = ;
      [*] = ;const cMarginFrameTop = -18;
      [*] = ;var xOff : Integer = 0;
      [*] = ;var yOff : Integer = 0;
      [*] = ;
      [*] = ;function ShowStaticInfo(elmParentHandle : Integer; grid : TEditorGrid; inXOff, inYOff, inWidth, inHeight : Integer) : Integer;
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
      [*] = ;   var sizeX : Integer =  GetGUIElementWidth(elmStaticInfoHandle);
      [*] = ;   var sizeY : Integer = GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;   posY := GetGUIElementPositionY(elmStripHandle)+GetGUIElementHeight(elmStripHandle)-3;
      [*] = ;   var text : String = 'Index: '+IntToStr(grid.ind);
      [*] = ;   _gui_CreateText('staticinfotext', elmStaticInfoHandle, text, 'halParentLeft', 'valParentTop', 0, posY, sizeX, sizeY, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;
      [*] = ;   posY := posY+textYOffset;
      [*] = ;   text := 'X: '+IntToStr(grid.x)+' Y: '+IntToStr(grid.y);
      [*] = ;   _gui_CreateText('staticinfotext', elmStaticInfoHandle, text, 'halParentLeft', 'valParentTop', 0, posY, sizeX, sizeY, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;
      [*] = ;   posY := posY+textYOffset;
      [*] = ;   var raceID : Integer = -1;
      [*] = ;   if (grid.terrain<0) or (grid.terrain>4) then
      [*] = ;   text := cTextNone
      [*] = ;   else
      [*] = ;   if (grid.provincetype=0) then
      [*] = ;   text := cTextRandom
      [*] = ;   else
      [*] = ;   if (grid.provincetype>0) then
      [*] = ;   begin
      [*] = ;      var pProvinceType : Integer = ParserSelectByHandleByIndex(gPrototypeData.provincetypes.handle, grid.provincetype);
      [*] = ;      raceID := ParserGetIntValueByKeyByHandle(pProvinceType, 'RaceID');
      [*] = ;      if (raceID=0) then
      [*] = ;      text := cTextNone
      [*] = ;      else
      [*] = ;      text := GetLocaleTableListItemByID('races', IntToStr(RaceID));
      [*] = ;   end
      [*] = ;   else
      [*] = ;   text := cTextNone;
      [*] = ;   text := 'Race: '+text;
      [*] = ;   _gui_CreateText('staticinfotext', elmStaticInfoHandle, text, 'halParentLeft', 'valParentTop', 0, posY, sizeX, sizeY, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;
      [*] = ;   Result := elmStaticInfoHandle;
      [*] = ;end;
      [*] = ;
      [*] = ;// dynamic info
      [*] = ;function ShowDynamicInfo(elmParentHandle : Integer; var grid : TEditorGrid; inXOff, inYOff, inWidth, inHeight : Integer) : Integer;
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
      [*] = ;   // terrain type dropbox
      [*] = ;   function CreateEditorTerrainType(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('terraintype', elmParent, 9, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'Terrain', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextRandom, 0);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('gui', '361'), -1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('map.provinceinfo', 'ProvinceName.Mountain'), -2);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('tooltip', 'map_infopanel_terraintype_plain'), 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('tooltip', 'map_infopanel_terraintype_forest'), 2);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('tooltip', 'map_infopanel_terraintype_hill'), 3);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('tooltip', 'map_infopanel_terraintype_swamp'), 4);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('tooltip', 'map_infopanel_terraintype_desert'), 5);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('tooltip', 'map_infopanel_terraintype_deadLand'), 6);
      [*] = ;      var listIndex : Integer;
      [*] = ;      case grid.terrain of
      [*] = ;         0 : listIndex := 0;
      [*] = ;         gc_WaterTerrainType : listIndex := 1;
      [*] = ;         gc_MountainTerrainType : listIndex := 2;
      [*] = ;         else
      [*] = ;         listIndex := grid.terrain+2;
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, listIndex);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // province type dropbox / depends on availability by terrain type
      [*] = ;   function CreateEditorProvinceType(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var count : Integer = 0;
      [*] = ;      var visibleCount : Integer = 0;
      [*] = ;      for i:=1 to gPrototypeData.provincetypes.number-1 do
      [*] = ;      begin
      [*] = ;         if (IsProvinceTypeAvailable(i, grid)) then
      [*] = ;         count := count+1;
      [*] = ;      end;
      [*] = ;      visibleCount := count;
      [*] = ;      if (count<>1) then
      [*] = ;      visibleCount := visibleCount+1;
      [*] = ;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('provincetype', elmParent, visibleCount, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'Province type', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      var provTypeSelectedInd : Integer = 0;
      [*] = ;      if (grid.terrain=0) then
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextRandom, 0)
      [*] = ;      else
      [*] = ;      if (count=0) then
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextNone, 0)
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var lastProvinceType : Integer = 0;
      [*] = ;         if (count>1) then
      [*] = ;         GUIListBoxAddItem(elmListBoxHandle, cTextRandom, 0);
      [*] = ;         count := 0;
      [*] = ;         for i:=1 to gPrototypeData.provincetypes.number-1 do
      [*] = ;         begin
      [*] = ;            if (IsProvinceTypeAvailable(i, grid)) then
      [*] = ;            begin
      [*] = ;               var name : String = ParserGetValueByKeyByHandle(ParserSelectByHandleByIndex(gPrototypeData.provincetypes.handle, i), 'Name');
      [*] = ;               GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('map.provinceinfo', name), i);
      [*] = ;               count := count+1;
      [*] = ;               lastProvinceType := i;
      [*] = ;               if (i=grid.provincetype) then
      [*] = ;               provTypeSelectedInd := count;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (count=1) then
      [*] = ;         grid.provincetype := lastProvinceType;
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, provTypeSelectedInd);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // province enabled flag
      [*] = ;   function CreateEditorProvinceEnabledFlag(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+cMarginDropboxTop;
      [*] = ;
      [*] = ;      posX := 26;
      [*] = ;      var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('', elmParent, grid.enabled, cTextProvinceEnabled, 'halParentLeft', 'valParentTop', posX, posY, cEventState, '', cCheckBoxEnabled);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmCheckBoxHandle)+cMarginDropboxBottom;
      [*] = ;
      [*] = ;      Result := elmCheckBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // castle province flag
      [*] = ;   function CreateEditorCastleProvinceFlag(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+cMarginDropboxTop;
      [*] = ;
      [*] = ;      var text : String = GetLocaleTableListItemByID('map.provinceinfo', 'ProvinceType.7');
      [*] = ;      var hint : String = GetLocaleTableListItemByID('tooltip', 'map_infopanel_province_type_7.ext');
      [*] = ;      posX := 26;
      [*] = ;      var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('', elmParent, grid.castle, text, 'halParentLeft', 'valParentTop', posX, posY, cEventState, hint, cCheckBoxCastle);
      [*] = ;      var bPlayable : Boolean = True;
      [*] = ;      if (grid.terrain<0) or (grid.terrain>4) then
      [*] = ;      begin
      [*] = ;         bPlayable := False;
      [*] = ;         grid.castle := False;
      [*] = ;         SetGUIElementEnabled(elmCheckBoxHandle, False);
      [*] = ;         SetGUIElementChecked(elmCheckBoxHandle, False);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (not grid.castle) then
      [*] = ;      begin
      [*] = ;         var i : Integer;
      [*] = ;         var bFreePlayers : Boolean = False;
      [*] = ;         for i:=0 to gMapEditor.map.players-1 do
      [*] = ;         begin
      [*] = ;            if (gMapEditor.players[i].castleprovind=-1) or (gMapEditor.players[i].castleprovind=grid.ind) then
      [*] = ;            begin
      [*] = ;               bFreePlayers := True;
      [*] = ;               break;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         if (not bFreePlayers) then
      [*] = ;         begin
      [*] = ;            SetGUIElementEnabled(elmCheckBoxHandle, False);
      [*] = ;            SetGUIElementHint(elmCheckBoxHandle, hint+gc_gui_BreakLine+gc_gui_BreakLine+cTextNoFreePlayers);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmCheckBoxHandle)+cMarginDropboxBottom;
      [*] = ;
      [*] = ;      Result := elmCheckBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // onwer player
      [*] = ;   function CreateEditorOwnerPlayer(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var bPlayable : Boolean = (grid.terrain>=0) or (grid.terrain<=4);
      [*] = ;      var visibleCount : Integer = 0;
      [*] = ;      if (bPlayable) then
      [*] = ;      begin
      [*] = ;         if (grid.castle) then
      [*] = ;         begin
      [*] = ;            for i:=0 to gMapEditor.map.players-1 do
      [*] = ;            begin
      [*] = ;               //log(IntToStr(gMapEditor.players[i].castleprovind));
      [*] = ;               if (gMapEditor.players[i].castleprovind=-1) or (gMapEditor.players[i].castleprovind=grid.ind) then
      [*] = ;               visibleCount := visibleCount+1;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         visibleCount := gMapEditor.map.players;
      [*] = ;      end;
      [*] = ;      if (not grid.castle) then
      [*] = ;      visibleCount := visibleCount+1;
      [*] = ;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('ownerplayer', elmParent, visibleCount, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'Owner player', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      if (not grid.castle) then
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextNone, -1);
      [*] = ;      if (not bPlayable) then
      [*] = ;      begin
      [*] = ;         SetGUIListBoxItemIndexSilent(elmListBoxHandle, 0);
      [*] = ;         SetGUIElementEnabled(elmListBoxHandle, False);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         for i:=0 to gMapEditor.map.players-1 do
      [*] = ;         begin
      [*] = ;            if (grid.castle) then
      [*] = ;            begin
      [*] = ;               if (gMapEditor.players[i].castleprovind=-1) or (gMapEditor.players[i].castleprovind=grid.ind) then
      [*] = ;               GUIListBoxAddItem(elmListBoxHandle, 'Player.'+IntToStr(i), i);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            GUIListBoxAddItem(elmListBoxHandle, 'Player.'+IntToStr(i), i);
      [*] = ;         end;
      [*] = ;         var ind : Integer;
      [*] = ;         if (grid.player=-1) then
      [*] = ;         ind := 0
      [*] = ;         else
      [*] = ;         ind := GetGUIListBoxItemIndexOfTag(elmListBoxHandle, grid.player);
      [*] = ;         if (grid.castle) then
      [*] = ;         SetGUIListBoxItemIndexSilent(elmListBoxHandle, ind)
      [*] = ;         else
      [*] = ;         SetGUIListBoxItemIndexSilent(elmListBoxHandle, grid.player+1);
      [*] = ;      end;
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // defender dropbox
      [*] = ;   function CreateEditorDefender(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var count : Integer = 0;
      [*] = ;      var visibleCount : Integer = 0;
      [*] = ;      if (grid.player<>-1) then
      [*] = ;      begin
      [*] = ;         for i:=1 to gPrototypeData.defenders.number-1 do
      [*] = ;         begin
      [*] = ;            if (IsDefenderAvailable(i, grid)) then
      [*] = ;            count := count+1;
      [*] = ;         end;
      [*] = ;         visibleCount := count;
      [*] = ;      end;
      [*] = ;      visibleCount := visibleCount+1;
      [*] = ;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('defenderid', elmParent, visibleCount, 14, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'Defender', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextNone, 0);
      [*] = ;      var defenderSelectedInd : Integer = 0;
      [*] = ;      if (grid.player<>-1) and (count>0) then
      [*] = ;      begin
      [*] = ;         var lastDefender : Integer = 0;
      [*] = ;         count := 0;
      [*] = ;         for i:=1 to gPrototypeData.defenders.number-1 do
      [*] = ;         begin
      [*] = ;            if (IsDefenderAvailable(i, grid)) then
      [*] = ;            begin
      [*] = ;               GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('defender', IntToStr(i)), i);
      [*] = ;               count := count+1;
      [*] = ;               lastDefender := i;
      [*] = ;               if (i=grid.defenderid) then
      [*] = ;               defenderSelectedInd := count;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (count=1) then
      [*] = ;         grid.defenderid := lastDefender;
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, defenderSelectedInd);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // guard type dropbox
      [*] = ;   function CreateEditorGuardType(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var bGuardTypeNone : Boolean = False;
      [*] = ;      var pProvinceType : Integer = ParserSelectByHandleByIndex(gPrototypeData.provincetypes.handle, grid.provincetype);
      [*] = ;      var pGuardTypes : Integer = ParserSelectByHandleByKey(pProvinceType, 'GuardTypes');
      [*] = ;      var count : Integer = 0;
      [*] = ;      for i:=0 to ParserGetCountByHandle(pGuardTypes)-1 do
      [*] = ;      begin
      [*] = ;         var guardtype : Integer = ParserGetIntValueByKeyByHandle(ParserSelectByHandleByIndex(pGuardTypes, i), 'GuardType');
      [*] = ;         if (guardtype<>0) then
      [*] = ;         count := count+1;
      [*] = ;      end;
      [*] = ;      var visibleCount : Integer = count;
      [*] = ;      if (count<>1) then
      [*] = ;      visibleCount := visibleCount+1;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('guardtype', elmParent, visibleCount, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'Guard type', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      var ind : Integer = 0;
      [*] = ;      if (grid.terrain<0) or (grid.castle) then
      [*] = ;      begin
      [*] = ;         GUIListBoxAddItem(elmListBoxHandle, cTextNone, 0);
      [*] = ;         bGuardTypeNone := True;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var lastGuardType : Integer = 0;
      [*] = ;         if (count>1) then
      [*] = ;         GUIListBoxAddItem(elmListBoxHandle, cTextRandom, 0);
      [*] = ;         if (grid.provincetype=0) then
      [*] = ;         GUIListBoxAddItem(elmListBoxHandle, cTextUndefined, 0)
      [*] = ;         else
      [*] = ;         for i:=0 to count-1 do
      [*] = ;         begin
      [*] = ;            var pGuardType : Integer = ParserSelectByHandleByIndex(pGuardTypes, i);
      [*] = ;            var guardType : Integer = ParserGetIntValueByKeyByHandle(pGuardType 'GuardType');
      [*] = ;            GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('guard_type', IntToStr(guardType)), guardType);
      [*] = ;            lastGuardType := guardType;
      [*] = ;            if (grid.guardtype=guardType) then
      [*] = ;            ind := i+1;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (grid.guardtype=0) and (count=1) then
      [*] = ;         grid.guardtype := lastGuardType;
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, ind);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // guard id dropbox
      [*] = ;   function CreateEditorGuardLevel(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var bGuardTypeNone : Boolean = (grid.terrain<0) or (grid.castle);
      [*] = ;      var pGuardType : Integer = ParserSelectByHandleByIndex(gPrototypeData.guardtypes.handle, grid.guardtype);
      [*] = ;      var pGuardIDs : Integer = ParserSelectByHandleByKey(pGuardType, 'GuardID');
      [*] = ;      var guardIDCount : Integer = 0;
      [*] = ;      if (not bGuardTypeNone) and (grid.guardtype>0) then
      [*] = ;      guardIDCount := ParserGetCountByHandle(pGuardIDs);
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('guardid', elmParent, guardIDCount+1, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'Guard level', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      var ind : Integer = 0;
      [*] = ;      if (bGuardTypeNone) then
      [*] = ;      begin
      [*] = ;         guardIDCount := 0;
      [*] = ;         GUIListBoxAddItem(elmListBoxHandle, cTextNone, 0);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         GUIListBoxAddItem(elmListBoxHandle, cTextUndefined, 0);
      [*] = ;         if (grid.guardtype>0) then
      [*] = ;         begin
      [*] = ;            for i:=0 to guardIDCount-1 do
      [*] = ;            begin
      [*] = ;               var pGuardID : Integer = ParserSelectByHandleByIndex(pGuardIDs, i);
      [*] = ;               var guardID : Integer = ParserGetIntValueByKeyByHandle(pGuardID, 'GuardID');
      [*] = ;               GUIListBoxAddItem(elmListBoxHandle, 'Level '+IntToStr(i+1), guardID);
      [*] = ;               if (grid.guardid=guardID) then
      [*] = ;               ind := i+1;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, ind);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // resource drop box
      [*] = ;   function CreateEditorResource(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var count : Integer;
      [*] = ;      if (grid.terrain>0) and (grid.terrain<5) then
      [*] = ;      count := gPrototypeData.resources.number
      [*] = ;      else
      [*] = ;      count := 1;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBoxMiddle('resourceid', elmParent, count, 0, 0, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'Resource', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, cTextNone, 0);
      [*] = ;      if (count>1) then
      [*] = ;      begin
      [*] = ;         for i:=1 to gPrototypeData.resources.number-1 do
      [*] = ;         GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('resource', IntToStr(i)), i);
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, grid.resourceid);
      [*] = ;
      [*] = ;      // scroll layer footer
      [*] = ;      posY := posY+GetGUIElementHeight(elmListBoxHandle);
      [*] = ;
      [*] = ;      Result := elmListBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // resource explored flag
      [*] = ;   function CreateEditorResourceExploredFlag(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+cMarginDropboxTop;
      [*] = ;
      [*] = ;      var text : String = 'Resource explored';
      [*] = ;      var hint : String = 'Place resource on unexplored lands';
      [*] = ;      posX := 26;
      [*] = ;      var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('', elmParent, grid.resexplored, text, 'halParentLeft', 'valParentTop', posX, posY, cEventState, hint, cCheckBoxResExplored);
      [*] = ;      if (grid.resourceid=0) then
      [*] = ;      begin
      [*] = ;         SetGUIElementEnabled(elmCheckBoxHandle, False);
      [*] = ;         SetGUIElementChecked(elmCheckBoxHandle, False);
      [*] = ;      end;
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmCheckBoxHandle)+cMarginDropboxBottom;
      [*] = ;
      [*] = ;      Result := elmCheckBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   function CreateEditorOuterBuildList(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+cMarginDropboxTop;
      [*] = ;
      [*] = ;      var text : String = 'Resource explored';
      [*] = ;      var hint : String = 'Place resource on unexplored lands';
      [*] = ;      posX := 26;
      [*] = ;
      [*] = ;      var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('', elmParent, grid.resexplored, text, 'halParentLeft', 'valParentTop', posX, posY, cEventState, hint, cCheckBoxResExplored);
      [*] = ;      if (grid.resourceid=0) then
      [*] = ;      begin
      [*] = ;         SetGUIElementEnabled(elmCheckBoxHandle, False);
      [*] = ;         SetGUIElementChecked(elmCheckBoxHandle, False);
      [*] = ;      end;
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmCheckBoxHandle)+cMarginDropboxBottom;
      [*] = ;
      [*] = ;      Result := elmCheckBoxHandle;
      [*] = ;   end;
      [*] = ;
      [*] = ;   // hint
      [*] = ;   function CreateEditorProvinceName(elmParent : Integer; var posY : Integer) : Integer;
      [*] = ;   begin
      [*] = ;      posY := posY+GetGUIElementFontHeight(fontHandle);
      [*] = ;
      [*] = ;      var elmInputHandle : Integer = CreateInputBoxSimple('provincename', elmParent, grid.name, 'halParentMiddle', 'valParentTop', 0, posY+2, cInputBoxWidthWide, 64, cEventState, cTextProvNameHint, True, cInputTextPosX, cInputTextPosY, 'halLeft', 'valMiddle', fontHandleInput, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;      var inputTxtHnd : Integer = GetGUIElementIndexByNameParent('text', elmInputHandle);
      [*] = ;      SetGUIElementHint(inputTxtHnd, cTextProvNameHint);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmInputHandle, cTextProvName, 'halParentLeft', 'valParentTop', 0, -18, GetGUIElementWidth(elmInputHandle), GetGUIElementHeight(elmInputHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;
      [*] = ;      posY := posY+GetGUIElementHeight(elmInputHandle);
      [*] = ;
      [*] = ;      Result := elmInputHandle;
      [*] = ;   end;
      [*] = ;   {if (gMapEditor.grid[i].goldinc>-1) then
      [*] = ;   if (gMapEditor.grid[i].geminc>-1) then
      [*] = ;   var j : Integer;
      [*] = ;   for j:=0 to 2 do
      [*] = ;   begin
      [*] = ;      gMapEditor.grid[i].outerbuild[j];
      [*] = ;   end;}
      [*] = ;   CreateEditorProvinceEnabledFlag(elmDynamicScrollLayer, posY);
      [*] = ;   if (grid.terrain>=0) and (grid.terrain<=4) then
      [*] = ;   begin
      [*] = ;      CreateEditorProvinceName(elmDynamicScrollLayer, posY);
      [*] = ;      posY := posY+cMarginDelimiter;
      [*] = ;      posY := posY+cMarginDelimiter;
      [*] = ;      CreateEditorCastleProvinceFlag(elmDynamicScrollLayer, posY);
      [*] = ;      posY := posY+cMarginDelimiter;
      [*] = ;   end;
      [*] = ;   CreateEditorTerrainType(elmDynamicScrollLayer, posY);
      [*] = ;   if (grid.terrain>=0) then
      [*] = ;   CreateEditorProvinceType(elmDynamicScrollLayer, posY);
      [*] = ;   if (grid.terrain>=0) and (grid.terrain<=4) then
      [*] = ;   begin
      [*] = ;      CreateEditorResource(elmDynamicScrollLayer, posY);
      [*] = ;      posY := posY+cMarginDelimiterHalf;
      [*] = ;      CreateEditorResourceExploredFlag(elmDynamicScrollLayer, posY);
      [*] = ;      posY := posY+cMarginDelimiter;
      [*] = ;      CreateEditorOwnerPlayer(elmDynamicScrollLayer, posY);
      [*] = ;      if (grid.player>-1) then
      [*] = ;      CreateEditorDefender(elmDynamicScrollLayer, posY)
      [*] = ;   end;
      [*] = ;   if (grid.player=-1) and (grid.terrain>=0) then
      [*] = ;   begin
      [*] = ;      CreateEditorGuardType(elmDynamicScrollLayer, posY);
      [*] = ;      CreateEditorGuardLevel(elmDynamicScrollLayer, posY);
      [*] = ;   end;
      [*] = ;
      [*] = ;   // settings scroller
      [*] = ;   SetGUIScrollEnabled(elmDynamicScrollLayer, (posY>GetGUIElementHeight(elmDynamicInfoHandle)));
      [*] = ;   SetGUIElementHeight(elmDynamicScrollLayer, posY+cListEnd);
      [*] = ;   var elmVScroll : Integer = GetGUIElementVScroll(elmDynamicScrollLayer);
      [*] = ;   SetGUIScrollBarPosition(elmVScroll, lastScrollPos);
      [*] = ;
      [*] = ;   Result := elmDynamicInfoHandle;
      [*] = ;end;
      [*] = ;
      [*] = ;const cInfoHeightBasis = 40;
      [*] = ;var staticInfoLineCount : Integer = 3;
      [*] = ;var elmStaticInfoHandle : Integer = ShowStaticInfo(elmParentHandle, gMapEditor.temporary.grid, 0, 0, 228, cInfoHeightBasis+GetGUIElementFontHeight(fontHandle)*staticInfoLineCount);
      [*] = ;
      [*] = ;const cCheckBoxHeight = 27;
      [*] = ;const cDropBoxHeight = 37;
      [*] = ;const cNumOfDropBox = 7;
      [*] = ;const cNumOfCheckBox = 3;
      [*] = ;const cNumOfMarginDelimiter = 3;
      [*] = ;const cNumOfStrips = 1;
      [*] = ;var height : Integer = cMarginFrameTop+GetGUITextureHeight('element.strip.240')*cNumOfStrips+cCheckBoxHeight*cNumOfCheckBox+cMarginDelimiter*cNumOfMarginDelimiter+cMarginDelimiterHalf+cDropBoxHeight*cNumOfDropBox+GetGUIElementFontHeight(fontHandle)*cNumOfDropBox+cListEnd;
      [*] = ;var elmDynamicInfoHandle : Integer = ShowDynamicInfo(elmParentHandle, gMapEditor.temporary.grid, dynamicDragX, dynamicDragY, 228, height);
      [*] = ;
      [*] = ;AttachGUIElementToElement(elmStaticInfoHandle, elmDynamicInfoHandle);
      [*] = ;SetGUIElementPosition(elmStaticInfoHandle, 0, -GetGUIElementHeight(elmStaticInfoHandle)-cMarginFrame);
      [*] = ;GUIElementSendToBack(elmStaticInfoHandle);
      [*] = ;
      [*] = ;// player index
      [*] = ;// checkbox Castle
      [*] = ;// dropbox plIndexes, based on gMapEditor.players
      [*] = ;
      [*] = ;// future vars
      [*] = ;// OuterBuildings
      [*] = ;// LandmarkID
      [*] = ;// InnerBuildings
      [*] = ;
      [*] = ;// ShowEditorGlobalSettings
      [*] = ;// players count
      [*] = ;// map size (6-20)
      [*] = ;// neutrals = 20
      [*] = ;// resource = 2
      [*] = ;// site = 2
      [*] = ;// population = 2
      [*] = ;// worldrule = 0
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
      [*] = ;var bChanges : Boolean = _editor_IsGridEqual(gMapEditor.temporary.grid, gMapEditor.grid[gGUIEditor.selgrid]);
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
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', cBtnCommonBtnMaterialName, 'halParentMiddle', 'valParentTop', -1, posY, cBtnCommonForceSizeX, 0, cEventState, '', cBtnOuterBuild);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, 'gui|93', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;var castle : Boolean = ParserGetBoolValueByKeyByHandle(gGUIEditor.selgridparser, 'Castle');
      [*] = ;if (castle) or (gMapEditor.grid[gGUIEditor.selgrid].terrain<0) or (gMapEditor.grid[gGUIEditor.selgrid].terrain>4) then
      [*] = ;begin
      [*] = ;   SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;   SetGUIElementUserBlend(elmBtnHandle, cUnavailableBtnAlpha)
      [*] = ;end;
      [*] = ;
      [*] = ;posY := GetGUIElementPositionY(elmBtnHandle)+GetGUIElementHeight(elmBtnHandle);
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', cBtnCommonBtnMaterialName, 'halParentMiddle', 'valParentTop', -1, posY, cBtnCommonForceSizeX, 0, cEventState, '', cBtnDefender);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, 'gui|92', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;var bEnabled : Boolean = False;
      [*] = ;if (gMapEditor.grid[gGUIEditor.selgrid].player<0) then
      [*] = ;SetGUIElementUserBlend(elmBtnHandle, cUnavailableBtnAlpha)
      [*] = ;else
      [*] = ;begin
      [*] = ;   var hint : String = '';
      [*] = ;   if (gMapEditor.grid[gGUIEditor.selgrid].terrain<0) or (gMapEditor.grid[gGUIEditor.selgrid].terrain>4) then
      [*] = ;   begin
      [*] = ;      bEnabled := False;
      [*] = ;      hint := cTextNeedPlayerOrTerrain;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var plHandle : Integer = GetPlayerHandleByIndex(gMapEditor.grid[gGUIEditor.selgrid].player);
      [*] = ;      if (plHandle<>0) then
      [*] = ;      begin
      [*] = ;         PlayerExecuteStateByHandle(plHandle, 'GetCastleParser');
      [*] = ;         var pCastleParser : Integer = IntRegister0;
      [*] = ;         if (pCastleParser<>0) then
      [*] = ;         begin
      [*] = ;            var pMyDefenders : Integer = ParserSelectByHandleByKey(pCastleParser, 'Defenders');
      [*] = ;            if (pMyDefenders<>0) then
      [*] = ;            bEnabled := True
      [*] = ;            else
      [*] = ;            hint := cTextNeedCastle;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   if (hint<>'') then
      [*] = ;   SetGUIElementHint(elmBtnHandle, hint);
      [*] = ;end;
      [*] = ;SetGUIElementEnabled(elmBtnHandle, bEnabled);
      [*] = ;
      [*] = ;posY := GetGUIElementPositionY(elmBtnHandle)+GetGUIElementHeight(elmBtnHandle);
      [*] = ;elmBtnHandle := _gui_CreateButton('', elmFrameHandle, '', cBtnCommonBtnMaterialName, 'halParentMiddle', 'valParentTop', -1, posY, cBtnCommonForceSizeX, 0, cEventState, '', cBtnSiteList);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, 'gui|118', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 0.8);
      [*] = ;if (gMapEditor.grid[gGUIEditor.selgrid].terrain<0) then
      [*] = ;begin
      [*] = ;   SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;   SetGUIElementUserBlend(elmBtnHandle, cUnavailableBtnAlpha)
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   var pProvSites : Integer = ParserSelectByHandleByKey(gGUIEditor.selgridparser, 'Sites');
      [*] = ;   var siteCount : Integer = 0;
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to ParserGetCountByHandle(pProvSites)-1 do
      [*] = ;   begin
      [*] = ;      var pProvSite : Integer = ParserSelectByHandleByIndex(pProvSites, i);
      [*] = ;      var siteID : Integer = ParserGetIntValueByKeyByHandle(pProvSite, 'SiteID');
      [*] = ;      if (siteID>0) then
      [*] = ;      siteCount := siteCount + 1;
      [*] = ;   end;
      [*] = ;   if (siteCount=0) then
      [*] = ;   begin
      [*] = ;      SetGUIElementEnabled(elmBtnHandle, False);
      [*] = ;      SetGUIElementHint(elmBtnHandle, cTextNoSites);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (not bVisible) then
      [*] = ;_gui_FadeElement(elmParentHandle, gc_gui_FadeTime0_2, true, true, true);
      [*] = ;_gui_RootWindowAddN(elmParentHandle);
      [*] = ;SetGUIElementPressState(elmParentHandle, cEventState);
      [*] = ;
      [*] = ;ExecuteState('GUIInvokeMouseMove');
   struct.end
section.end

