section.begin
   Name = ShowParserLoadList
   Description : struct.begin
      [*] = ;Variables:
      [*] = ;   activeInd - index of currently selected save
   struct.end
   Code : struct.begin
      [*] = ;const cSaveIndexBaseTag = 1000;
      [*] = ;const cMaxItems = $7f;               // 7 bits
      [*] = ;const cVisibleListNo = 13;
      [*] = ;
      [*] = ;var pLoadList : Integer = GetIntValueByName('ParserHandle');
      [*] = ;
      [*] = ;const cEventState = 'EventParserLoadList';
      [*] = ;
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;
      [*] = ;// Check if window was already visible, then no need to FadeIn it when show again
      [*] = ;var prevElmParentHandle : Integer = _gui_GetWindow('load_window');
      [*] = ;var bVisible : Boolean = False;
      [*] = ;if (prevElmParentHandle<>0) and GetGUIElementVisible(prevElmParentHandle) then
      [*] = ;   bVisible := True;
      [*] = ;
      [*] = ;var elmScrollLayer : Integer = _gui_GetWindow('load_window.list.scroll_layer');
      [*] = ;var lastScrollPos : Float = 0;
      [*] = ;if (elmScrollLayer<>0) then
      [*] = ;begin
      [*] = ;   var elmVScroll : Integer = GetGUIElementVScroll(elmScrollLayer);
      [*] = ;   if (elmVScroll<>0) then
      [*] = ;      lastScrollPos := GetGUIScrollBarPosition(elmVScroll);
      [*] = ;end;
      [*] = ;
      [*] = ;var fontHandle, fontHandle2, fontHandle3: String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_small,'',fontHandle);   // HeaderS
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'',fontHandle2); // NormalL
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_largest,'',fontHandle3); // HeaderM
      [*] = ;
      [*] = ;var headerText : String = 'menu|45';
      [*] = ;
      [*] = ;var elmParentHandle : Integer = _gui_CreateLargeWindow(0, 'load_window', 'halParentMiddle', 'valParentMiddle', 0, 0, 857, 499-22, true);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('background', elmParentHandle), 0.65+0.15);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('frame', elmParentHandle), 0.75+0.1);
      [*] = ;var elmHeaderHandle : Integer = GetGUIElementIndexByNameParent('header', elmParentHandle);
      [*] = ;var elmTextHandle : Integer = _gui_CreateText('', elmHeaderHandle, headerText, 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHeaderHandle), GetGUIElementHeight(elmHeaderHandle), 'halMiddle', 'valMiddle', fontHandle3, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;var elmHandle : Integer = _gui_CreateImage('', elmParentHandle, 'gamepanel03.loadgame.table.header', 'halParentLeft', 'valParentTop', 35, 36, 0, 0, 0);
      [*] = ;elmTextHandle := _gui_CreateText('', elmParentHandle, 'gui|750', 'halParentLeft', 'valParentTop', 35+14, 36+4, 280, 43, 'halLeft', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderR, gc_gui_fontcolor_HeaderG, gc_gui_fontcolor_HeaderB, 1);
      [*] = ;//elmTextHandle := _gui_CreateText('', elmParentHandle, 'menu|44', 'halParentLeft', 'valParentTop', 35+14+278, 36+4, 170, 43, 'halLeft', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderR, gc_gui_fontcolor_HeaderG, gc_gui_fontcolor_HeaderB, 1);
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'gamepanel03.loadgame.table.border.middle', 'halParentLeft', 'valParentTop', 35, 79, 0, 0, 0);
      [*] = ;var activeInd : Integer = GetIntValueByName('ActiveInd');
      [*] = ;var activeItemName : String = '';
      [*] = ;var itemCount : Integer = ParserGetCountByHandle(pLoadList);
      [*] = ;   
      [*] = ;if itemCount > cMaxItems then
      [*] = ;begin
      [*] = ;   ErrorLogI('Too many items: '+IntToStr(itemCount));
      [*] = ;   itemCount := cMaxItems;
      [*] = ;end;
      [*] = ;
      [*] = ;{if (activeInd<0) then
      [*] = ;begin
      [*] = ;   activeInd := 0;
      [*] = ;   if itemCount > 0 then
      [*] = ;      SetIntValueByName('ActiveInd', 0);
      [*] = ;end
      [*] = ;else}
      [*] = ;if (activeInd>itemCount-1) then
      [*] = ;   activeInd := itemCount-1;
      [*] = ;
      [*] = ;// Scroll layer and save file list
      [*] = ;var width : Integer = GetGUITextureWidth('gamepanel03.loadgame.table.header');
      [*] = ;var elmTmpLayer : Integer = _gui_CreateImage('list', elmParentHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;var elmGuiLayer : Integer = AddNewElementByClassNameParent('scroll_layer', 'TXGuiLayer', 0, elmTmpLayer);
      [*] = ;SetGUIElementAlign(elmGuiLayer, 'halParentLeft', 'valParentTop');
      [*] = ;SetGUIElementAllPositionRect(elmGuiLayer, 35, 84, width, 28*cVisibleListNo);
      [*] = ;SetGUIElementMaterial(elmGuiLayer, gc_gui_material_blank_0);
      [*] = ;SetGUIScrollEnabled(elmGuiLayer, itemCount>cVisibleListNo);
      [*] = ;var elmVScroll : Integer = GetGUIElementVScroll(elmGuiLayer);
      [*] = ;SetGUIElementAlign(elmVScroll, 'halParentRight', 'valParentTop');
      [*] = ;SetGUIElementMaterialOffset(elmVScroll, 2, 0);
      [*] = ;SetGUIElementAllPositionRect(elmVScroll, -4, 0, 32, 28*cVisibleListNo);
      [*] = ;SetGUIElementMaterial(elmVScroll, 'map.dialog.scroller.tile');
      [*] = ;SetGUIScrollButtonSource(elmVScroll, 0, 'map.dialog.scroller.up', true);
      [*] = ;SetGUIScrollButtonSource(elmVScroll, 2, 'map.dialog.scroller.down', true);
      [*] = ;SetGUIScrollButtonSource(elmVScroll, 1, 'map.dialog.scroller.slider', true);
      [*] = ;SetGUIAllowEvents(elmGuiLayer, True, False, False);
      [*] = ;
      [*] = ;var neededCount : Integer;
      [*] = ;if itemCount < cVisibleListNo then
      [*] = ;   neededCount := cVisibleListNo
      [*] = ;else
      [*] = ;   neededCount := itemCount;
      [*] = ;
      [*] = ;var i, pItem : Integer;
      [*] = ;for i:=0 to neededCount-1 do
      [*] = ;begin
      [*] = ;   var elmLineHandle : Integer = _gui_CreateImage('', elmGuiLayer, 'gamepanel03.loadgame.table.line', 'halParentLeft', 'valParentTop', 0, i*(28)+1, 0, 0, 0);
      [*] = ;   _gui_CreateImage('', elmLineHandle, 'gamepanel03.loadgame.table.border.middle', 'halParentLeft', 'valParentTop', 0, 22, 0, 0, 0);
      [*] = ;end;
      [*] = ;
      [*] = ;var itemName : String;
      [*] = ;
      [*] = ;for i:=0 to itemCount-1 do
      [*] = ;begin
      [*] = ;   pItem := ParserSelectByHandleByIndex(pLoadList, i);
      [*] = ;   itemName := ParserGetValueByKeyByHandle(pItem, 'Name');
      [*] = ;
      [*] = ;   var bChecked : Boolean = i=activeInd;
      [*] = ;   var textW, textH : Integer;
      [*] = ;
      [*] = ;   var posX : Integer = 5;
      [*] = ;   var posY : Integer = 28*i;
      [*] = ;   var tag : Integer = cSaveIndexBaseTag+i;
      [*] = ;   var elmItemHandle : Integer = _gui_CreateButton('savefile', elmGuiLayer, '', gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', posX, posY, 440, 24, cEventState, '', tag);
      [*] = ;   SetGUIElementChecked(elmItemHandle, bChecked);
      [*] = ;   SetGUIElementTextAlign(elmItemHandle, 'halLeft', 'valMiddle', 0, 0);
      [*] = ;   SetGUIElementFont(elmItemHandle, fontHandle);
      [*] = ;   GetGUIElementFontTextFormatRect(fontHandle, itemName, textW, textH);
      [*] = ;   if (textW>250) then
      [*] = ;   begin
      [*] = ;      var length : Integer = StrLength(itemName);
      [*] = ;      var j : Integer;
      [*] = ;      for j:=0 to length-1 do
      [*] = ;      begin
      [*] = ;         var subStr : String = SubStr(itemName, 1, length-j);
      [*] = ;         GetGUIElementFontTextFormatRect(fontHandle, subStr, textW, textH);
      [*] = ;         if (textW<=250) then
      [*] = ;         begin
      [*] = ;            itemName := subStr+' ...';
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   SetGUIElementText(elmItemHandle,itemName);
      [*] = ;   SetGUIElementTextFormatted(elmItemHandle, True);
      [*] = ;
      [*] = ;   var xOff : Integer = 0;
      [*] = ;   var yOff : Integer = 0;
      [*] = ;   var txOff : Integer = 8;
      [*] = ;   var tyOff : Integer = 0;
      [*] = ;   SetGUIElementVisibleProperties(elmItemHandle, 'UpProperty', gc_gui_material_blank_0, xOff, yOff, txOff, tyOff, -1, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;   SetGUIElementVisibleProperties(elmItemHandle, 'HoverProperty', gc_gui_material_blank_0, xOff, yOff, txOff, tyOff, 6, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   SetGUIElementVisibleProperties(elmItemHandle, 'DownProperty', gc_gui_material_blank_0, xOff, yOff, txOff, tyOff, 6, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   SetGUIElementVisibleProperties(elmItemHandle, 'DisableProperty', gc_gui_material_blank_0, xOff, yOff, txOff, tyOff, -1, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   SetGUIElementVisibleProperties(elmItemHandle, 'CheckOnProperty', gc_gui_material_blank_0, xOff, yOff, txOff, tyOff, 6, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;   
      [*] = ;   if (bChecked) then
      [*] = ;   begin
      [*] = ;      SetGUIElementVisibleProperties(elmItemHandle, 'DisableProperty', gc_gui_material_blank_0, xOff, yOff, txOff, tyOff, 1, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;      SetGUIElementVisibleProperties(elmItemHandle, 'CheckOnProperty', gc_gui_material_blank_0, xOff, yOff, txOff, tyOff, 1, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;      SetGUIElementEnabled(elmItemHandle, False);
      [*] = ;      //elmTextHandle := _gui_CreateText('name', elmItemHandle, date, 'halParentLeft', 'valParentTop', 278+8, 0, 163, 24, 'halLeft', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;      activeItemName := itemName;
      [*] = ;   end;
      [*] = ;   //else
      [*] = ;      //elmTextHandle := _gui_CreateText('name', elmItemHandle, date, 'halParentLeft', 'valParentTop', 278+8, 0, 163, 24, 'halLeft', 'valMiddle', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;end;
      [*] = ;// last 13th line bottom border
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'gamepanel03.loadgame.table.border.bottom', 'halParentLeft', 'valParentTop', 35, 79+cVisibleListNo*28, 0, 0, 0);
      [*] = ;
      [*] = ;// scroll height cutter
      [*] = ;var height : Integer = neededCount*28;
      [*] = ;SetGUIElementHeight(elmGuiLayer, height);
      [*] = ;
      [*] = ;// restore scroller position
      [*] = ;SetGUIScrollBarPosition(elmVScroll, lastScrollPos);
      [*] = ;
      [*] = ;// Snapshot
      [*] = ;{var snapRatio : Float = GetViewerWidth()/GetViewerHeight();
      [*] = ;height := 139;
      [*] = ;width := round(height*snapRatio);
      [*] = ;var elmSnapShotHandle : Integer = _gui_CreateImage('snapshot', elmParentHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 680-(width div 2), 53, width, height, 0);
      [*] = ;if ((activeInd >= 0) and (_misc_AssignSaveSnapShotToTexture(activeInd,'misc.snapshot'))) then
      [*] = ;   _gui_CreateImage('', elmSnapShotHandle, 'misc.snapshot', 'halParentLeft', 'valParentTop', 0, 0, width, height, 0);
      [*] = ;
      [*] = ;_gui_CreateScrollLayer(elmSnapShotHandle, 'gamepanel03.snapshot.border.top', 'halParentLeft', 'valParentTop', 0, -11, width, 0);
      [*] = ;_gui_CreateScrollLayer(elmSnapShotHandle, 'gamepanel03.snapshot.border.bottom', 'halParentLeft', 'valParentBottom', 0, 0, width, 0);
      [*] = ;_gui_CreateScrollLayer(elmSnapShotHandle, 'gamepanel03.snapshot.border.left', 'halParentLeft', 'valParentTop', -11, 0, 0, height);
      [*] = ;_gui_CreateScrollLayer(elmSnapShotHandle, 'gamepanel03.snapshot.border.right', 'halParentRight', 'valParentTop', 0, 0, 0, height);
      [*] = ;_gui_CreateImage('', elmSnapShotHandle, 'gamepanel03.snapshot.decor.top', 'halParentMiddle', 'valParentTop', 0, -3-GetGUITextureHeight('gamepanel03.snapshot.decor.top'), 0, 0, 0);
      [*] = ;_gui_CreateImage('', elmSnapShotHandle, 'gamepanel03.snapshot.decor.bottom', 'halParentMiddle', 'valParentBottom', 0, 3, 0, 0, 0);
      [*] = ;_gui_CreateImage('', elmSnapShotHandle, 'gamepanel03.snapshot.decor.left', 'halParentLeft', 'valParentMiddle', -GetGUITextureWidth('gamepanel03.snapshot.decor.left'), 0, 0, 0, 0);
      [*] = ;_gui_CreateImage('', elmSnapShotHandle, 'gamepanel03.snapshot.decor.right', 'halParentRight', 'valParentMiddle', 0, 0, 0, 0, 0);
      [*] = ;_gui_CreateImage('', elmSnapShotHandle, 'gamepanel03.snapshot.corner.top.left', 'halParentLeft', 'valParentTop', -18, -33, 0, 0, 0);
      [*] = ;_gui_CreateImage('', elmSnapShotHandle, 'gamepanel03.snapshot.corner.top.right', 'halParentRight', 'valParentTop', -48, -33, 0, 0, 0);
      [*] = ;_gui_CreateImage('', elmSnapShotHandle, 'gamepanel03.snapshot.corner.bottom.left', 'halParentLeft', 'valParentBottom', -18, -12, 0, 0, 0);
      [*] = ;_gui_CreateImage('', elmSnapShotHandle, 'gamepanel03.snapshot.corner.bottom.right', 'halParentRight', 'valParentBottom', -48, -12, 0, 0, 0);}
      [*] = ;
      [*] = ;// Disabled inputbox
      [*] = ;var inputWidth : Integer = 324;
      [*] = ;var elmInputBoxHandle : Integer = _gui_CreateImage('inputbox', elmParentHandle, gc_gui_material_blank_0, 'halParentLeft', 'valParentTop', 518, 238+5, inputWidth, 45, 0);
      [*] = ;SetGUIElementPressState(elmInputBoxHandle, cEventState); // used outside
      [*] = ;SetGUIElementStringTag(elmInputBoxHandle, 'InputLoad');
      [*] = ;_gui_CreateImage('', elmInputBoxHandle, 'common.slider.left.end', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, 0);
      [*] = ;_gui_CreateImage('', elmInputBoxHandle, 'common.slider.right.end', 'halParentLeft', 'valParentTop', inputWidth-GetGUITextureWidth('common.slider.right.end'), 0, 0, 0, 0);
      [*] = ;_gui_CreateScrollLayer(elmInputBoxHandle, 'common.slider.middle', 'halParentLeft', 'valParentTop', GetGUITextureWidth('common.slider.left.end'), 0, inputWidth-GetGUITextureWidth('common.slider.left.end')-GetGUITextureWidth('common.slider.right.end'), 0);
      [*] = ;SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;SetGUIElementHint(elmHandle, 'menu|49');
      [*] = ;_gui_CreateText('', elmInputBoxHandle, 'menu|43', 'halParentLeft', 'valParentTop', 0, -20, GetGUIElementWidth(elmInputBoxHandle), 20, 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;_gui_CreateText('', elmInputBoxHandle, activeItemName, 'halParentLeft', 'valParentTop', 36, -4, GetGUIElementWidth(elmInputBoxHandle)-72, GetGUIElementHeight(elmInputBoxHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;
      [*] = ;var text : String = '';
      [*] = ;_gui_CreateText('text', elmInputBoxHandle, text, 'halParentLeft', 'valParentTop', 0, 0, inputWidth-97, 35, 'halLeft', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;
      [*] = ;// display current turn of the save
      [*] = ;{if activeInd >= 0 then
      [*] = ;begin
      [*] = ;   var pSaveFile : Integer = _misc_GetSaveGameDescriptionParser(UserGetProfileCustomByIndex(activeInd));
      [*] = ;   var currentTurn : Integer = ParserGetIntValueByKeyByHandle(ParserSelectByHandleByKey(pSaveFile ,'gGame'), 'currentturn');
      [*] = ;
      [*] = ;   text := 'gui|51';
      [*] = ;   _gui_ConvertTableKeyToText(text);
      [*] = ;   if (currentTurn < 0) then
      [*] = ;      text := ''
      [*] = ;   else
      [*] = ;      text := text + ': '+'%color(FFFFFF)%'+IntToStr(currentTurn);
      [*] = ;   elmTextHandle := _gui_CreateText('', elmParentHandle, text, 'halParentLeft', 'valParentTop', 567+20+42, 276, 100, 30, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;end;}
      [*] = ;
      [*] = ;const cBtnLoadTag = 101;
      [*] = ;const cBtnDeleteTag = 102;
      [*] = ;const cBtnCloseTag = 110;
      [*] = ;
      [*] = ;// Load button 
      [*] = ;var elmBtnHandle : Integer = _gui_CreateButton('btnLoad', elmParentHandle, '', 'common.btn', 'halParentLeft', 'valParentTop', 567+20, 306, GetGUITextureWidth('common.btn.normal')-20*2, 0, cEventState, '', cBtnLoadTag);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, 'menu|45', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;
      [*] = ;var bEnabled : Boolean = activeInd >= 0;
      [*] = ;if (not bEnabled) then
      [*] = ;begin
      [*] = ;   SetGUIElementEnabled(elmBtnHandle, bEnabled);
      [*] = ;   SetGUIElementColor(elmTextHandle, 0.5, 0.5, 0.5, 1);
      [*] = ;end;
      [*] = ;
      [*] = ;// Delete button
      [*] = ;elmBtnHandle := _gui_CreateButton('btnDelete', elmParentHandle, '', 'common.btn', 'halParentLeft', 'valParentTop', 567+20, 306+48, GetGUITextureWidth('common.btn.normal')-20*2, 0, cEventState, '', cBtnDeleteTag);
      [*] = ;elmTextHandle := _gui_CreateText('', elmBtnHandle, 'menu|46', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;
      [*] = ;if (not bEnabled) then
      [*] = ;begin
      [*] = ;   SetGUIElementEnabled(elmBtnHandle, bEnabled);
      [*] = ;   SetGUIElementColor(elmTextHandle, 0.5, 0.5, 0.5, 1);
      [*] = ;end;
      [*] = ;
      [*] = ;// Close button
      [*] = ;elmBtnHandle := _gui_CreateButton('btnClose', elmParentHandle, '', 'common.btn', 'halParentLeft', 'valParentTop', 567+20, 306+48*2, GetGUITextureWidth('common.btn.normal')-20*2, 0, cEventState, '', cBtnCloseTag);
      [*] = ;_gui_CreateText('', elmBtnHandle, 'menu|47', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmBtnHandle), GetGUIElementHeight(elmBtnHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;
      [*] = ;
      [*] = ;if (not bVisible) then
      [*] = ;   _gui_FadeElement(elmParentHandle, gc_gui_FadeTime0_2, true, true, true);
      [*] = ;
      [*] = ;_gui_RootWindowAddM(elmParentHandle);
      [*] = ;SetGUIElementPressState(elmParentHandle, cEventState);
      [*] = ;GUIExecuteState('GUIInvokeMouseMove');
   struct.end
section.end

