section.begin
   Name = map.CreateChooseHeroWindow
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\MAP\MAP.CREATECHOOSEHEROWINDOW';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var pProvince : Integer = IntRegister0;
      [*] = ;var addDefender : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;const cEventState = 'map.EventChooseHeroWindow';
      [*] = ;
      [*] = ;function CreateScrollerParentExt(ElementName : String; Parent : Integer; hAlign, vAlign, MaterialName : String; posX, posY, sizeX, sizeY, scrollX, scrollY, scrollH : Integer; showScroller : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   var elmGuiLayer : Integer = AddNewElementByClassNameParent(ElementName, 'TXGuiLayer', 0, Parent);
      [*] = ;   SetGUIElementAlign(elmGuiLayer, hAlign, vAlign);
      [*] = ;   SetGUIElementAllPositionRect(elmGuiLayer, posX, posY, sizeX, sizeY);
      [*] = ;   SetGUIElementMaterial(elmGuiLayer, MaterialName);
      [*] = ;   SetGUIScrollEnabled(elmGuiLayer, True);
      [*] = ;   var elmVScroll : Integer = GetGUIElementVScroll(elmGuiLayer);
      [*] = ;   SetGUIElementAlign(elmVScroll, 'halParentLeft', 'valParentTop');
      [*] = ;   SetGUIElementMaterialOffset(elmVScroll, -1, 0);
      [*] = ;   SetGUIElementAllPositionRect(elmVScroll, scrollX, scrollY, 27, scrollH);
      [*] = ;   if (showScroller) then
      [*] = ;   begin
      [*] = ;      SetGUIElementMaterial(elmVScroll, 'map.dialog.scroller.tile');
      [*] = ;      SetGUIScrollButtonSource(elmVScroll, 0, 'map.dialog.scroller.up', true);
      [*] = ;      SetGUIScrollButtonSource(elmVScroll, 2, 'map.dialog.scroller.down', true);
      [*] = ;      SetGUIScrollButtonSource(elmVScroll, 1, 'map.dialog.scroller.slider', true);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   SetGUIElementMaterial(elmVScroll, 'misc.blank.black.alpha.0');
      [*] = ;   SetGUIAllowEvents(elmGuiLayer, True, False, False);
      [*] = ;   Result := elmGuiLayer;
      [*] = ;end;
      [*] = ;
      [*] = ;_misc_AntiFreezeFinish;
      [*] = ;
      [*] = ;// Check if window was already visible, then no need to FadeIn it when show again
      [*] = ;var prevElmParentHandle : Integer = GetGUIElementIndexByNameParent('dialog_without_image', _gui_GetLayerI());
      [*] = ;var bVisible : Boolean = False;
      [*] = ;if (prevElmParentHandle<>0) and GetGUIElementVisible(prevElmParentHandle) then
      [*] = ;bVisible := True;
      [*] = ;
      [*] = ;var top : Integer = _gui_GetLayerI();
      [*] = ;var elmParentHandle : Integer = _gui_GetOrCreateElement('dialog_without_image', top, 'halLeft', 'valTop', 0, 0, GetViewerWidth, GetViewerHeight, 0);
      [*] = ;SetGUIElementVisible(elmParentHandle, True);
      [*] = ;SetGUIAllowEvents(elmParentHandle, True, False, False);
      [*] = ;
      [*] = ;var matName : String;
      [*] = ;var sizeX, sizeY, posX, posY, yOff : Integer;
      [*] = ;matName := 'map.dialog.window.without.image.answers.background';
      [*] = ;sizeX := GetGUITextureWidth(matName);
      [*] = ;sizeY := GetGUITextureHeight(matName);
      [*] = ;var elmDialogWindowAnswersBackground : Integer = _gui_CreateImage('', elmParentHandle, matName, 'halParentMiddle', 'valParentMiddle', 0, 0, sizeX, sizeY, 0);
      [*] = ;
      [*] = ;matName := 'map.dialog.window.without.image.background';
      [*] = ;sizeX := GetGUITextureWidth(matName);
      [*] = ;sizeY := GetGUITextureHeight(matName);
      [*] = ;var elmDialogWindowBackground : Integer = _gui_CreateImage('', elmParentHandle, matName, 'halParentMiddle', 'valParentMiddle', 0, 0, sizeX, sizeY, 0);
      [*] = ;
      [*] = ;var fontHandleT, fontHandleH1: String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_default,'',fontHandleT);   // Simple text
      [*] = ;_gui_GetFont(gc_gui_fontsection_tactics,'Text',gc_gui_fontsize_largest,'',fontHandleH1); // Header
      [*] = ;
      [*] = ;var headText, mainText : String;
      [*] = ;if (gIntRegister_MapPickedRitualID>0) then
      [*] = ;begin
      [*] = ;   headText := GetLocaleTableListItemByID('gui', '672');
      [*] = ;   mainText := GetLocaleTableListItemByID('gui', '671');
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   headText := GetLocaleTableListItemByID('message', '16');
      [*] = ;   mainText := GetLocaleTableListItemByID('message', '16.description');
      [*] = ;end;
      [*] = ;
      [*] = ;IntRegister0 := pProvince;
      [*] = ;MapExecuteState('map.GetProvinceName');
      [*] = ;gStringRegister_ProvinceName := StringRegister0;
      [*] = ;StringRegister0 := mainText;
      [*] = ;MapExecuteState('StringReplaceParams');
      [*] = ;mainText := StringRegister1;
      [*] = ;
      [*] = ;var elmTextHandle : Integer = _gui_CreateText('head', elmParentHandle, headText, 'halParentMiddle', 'valParentMiddle', 0, -60, 250, 40, 'halMiddle', 'valTop', fontHandleH1, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;{var mainTextWrapped : String = GetGUIWrappedTextFormatByFont(fontHandleT, mainText, 295);
      [*] = ;var mainTextW, mainTextH : Integer;
      [*] = ;GetGUIElementFontTextFormatRect(fontHandleT, mainTextWrapped, mainTextW, mainTextH);
      [*] = ;elmTextHandle := _gui_CreateText('message', elmParentHandle, mainTextWrapped, 'halParentMiddle', 'valParentMiddle', 0, 17, mainTextW, mainTextH, 'halMiddle', 'valMiddle', fontHandleT, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);}
      [*] = ;var mainTextW, mainTextH : Integer;
      [*] = ;var mainTextWrapped : String = GetGUIWrappedTextFormatByFont(fontHandleT, mainText, 320);
      [*] = ;GetGUIElementFontTextFormatRect(fontHandleT, mainTextWrapped, mainTextW, mainTextH);
      [*] = ;var frameW : Integer = mainTextW+12;
      [*] = ;var frameH : Integer = mainTextH+12;
      [*] = ;var elmFrameHandle : Integer = _gui_CreateFrameBorder('frame', elmDialogWindowBackground, 'halParentMiddle', 'valParentMiddle', 0, -25, frameW, 0);
      [*] = ;elmFrameHandle := _gui_CreateFrameBorder('frame', elmDialogWindowBackground, 'halParentMiddle', 'valParentMiddle', 0, -25+105, frameW, 0);
      [*] = ;elmTextHandle := _gui_CreateText('', elmDialogWindowBackground, mainTextWrapped, 'halParentMiddle', 'valParentMiddle', 0, 25, mainTextW, mainTextH, 'halMiddle', 'valMiddle', fontHandleT, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;
      [*] = ;// --- Results text buttons ---
      [*] = ;posX := -15;
      [*] = ;posY := 202;
      [*] = ;sizeX := 271;
      [*] = ;sizeY := 174;
      [*] = ;// --- Layer with scroll
      [*] = ;var elmScrollLayer : Integer = CreateScrollerParentExt('scroll_layer', elmParentHandle, 'halParentMiddle', 'valParentMiddle', 'misc.blank.black.alpha.0', posX, posY, sizeX, sizeY, sizeX, 0, sizeY, false);
      [*] = ;var offsetBetweenResults : Integer = 58;
      [*] = ;
      [*] = ;var plHandle : Integer = GetPlayerHandleByIndex(gIntRegister_MapMyPlayerIndex);
      [*] = ;
      [*] = ;var dummyUID : Integer = ParserGetIntValueByKeyByHandle(pProvince, 'DummyUID');
      [*] = ;var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;
      [*] = ;{IntRegister0 := 0;
      [*] = ;IntRegister1 := 0;
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'GetOwnerArmy');
      [*] = ;var defendersCount : Integer = IntRegister4;}
      [*] = ;IntRegister0 := plHandle;
      [*] = ;GameObjectExecuteStateByHandle(dummyHandle, 'GetHeroesData');
      [*] = ;var heroHandle : Integer = IntRegister1;
      [*] = ;var defendersCount : Integer = IntRegister2;
      [*] = ;if addDefender and BoolRegister0 then
      [*] = ;defendersCount := defendersCount + 1;
      [*] = ;
      [*] = ;if defendersCount>2 then
      [*] = ;posY := 211
      [*] = ;else
      [*] = ;posY := 37+offsetBetweenResults*defendersCount;
      [*] = ;SetGUIElementPositionY(elmDialogWindowAnswersBackground, posY);
      [*] = ;
      [*] = ;const onePageCount = 3;
      [*] = ;if defendersCount>9 then
      [*] = ;defendersCount := 9;
      [*] = ;var i, j  : Integer;
      [*] = ;var isHero : Boolean = False;
      [*] = ;
      [*] = ;for i := 0 to defendersCount-1 do
      [*] = ;begin
      [*] = ;   //var elmItemHandle : Integer = _gui_CreateDummy('', elmScrollLayer, 'halParentLeft', 'valParentTop', 0, 0+offsetBetweenResults*i, 350, offsetBetweenResults, gc_gui_btnDefenderSelectItem);
      [*] = ;   //var elmItemHandle : Integer = _gui_CreateDummy('', elmScrollLayer, 'halParentLeft', 'valParentTop', 0, 0+offsetBetweenResults*i, 350, offsetBetweenResults, gc_gui_btnDefenderSelectItem);
      [*] = ;   var elmItemHandle : Integer = AddNewElementParent('btn', '', gc_gui_selectdefender_btnSelect, elmScrollLayer);
      [*] = ;   SetGUIElementAllPositionRect(elmItemHandle, 0, 0+offsetBetweenResults*i, 300, offsetBetweenResults);
      [*] = ;   SetGUIElementAlign(elmItemHandle, 'halParentLeft', 'valParentTop');
      [*] = ;   SetGUIElementLogicPositionRect(elmItemHandle, 0, 0+offsetBetweenResults*i, 300, offsetBetweenResults);
      [*] = ;   SetGUIAllowEvents(elmItemHandle, True, False, False);
      [*] = ;   SetGUIElementStringTag(elmItemHandle, 'choose_defender');
      [*] = ;   SetGUIElementPressState(elmItemHandle, cEventState);
      [*] = ;   SetGUIElementHoverEnabled(elmItemHandle, true);
      [*] = ;   SetGUIElementEnabled(elmItemHandle, true);
      [*] = ;   var MaterialName : String = 'misc.blank.black.alpha.0';
      [*] = ;   SetGUIElementVisibleProperties(elmItemHandle, 'UpProperty', MaterialName, 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;   SetGUIElementVisibleProperties(elmItemHandle, 'HoverProperty', MaterialName, 0, 0, 0, 0,  6, 0.5, 0.5, 0.5, 1);
      [*] = ;   SetGUIElementVisibleProperties(elmItemHandle, 'DownProperty', MaterialName, 0, 0, 0, 0,  6, 0.5, 0.5, 0.5, 1);
      [*] = ;   SetGUIElementVisibleProperties(elmItemHandle, 'DisableProperty', MaterialName, 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;   SetGUIElementVisibleProperties(elmItemHandle, 'CheckOnProperty', MaterialName, 0, 0, 0, 0,  6, 0.5, 0.5, 0.5, 1);
      [*] = ;
      [*] = ;   var count : Integer = 0;
      [*] = ;   var heroHandle : Integer = 0;
      [*] = ;   var defID : Integer = 0;
      [*] = ;
      [*] = ;   for j := 0 to GetPlayerGameObjectsCountByHandle(plHandle)-1 do
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetGameObjectHandleByIndex(j, plHandle);
      [*] = ;      var isDead : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_bIsDead);
      [*] = ;      var curUID : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_map_GOStack_MapUnit_iCurrentUID);
      [*] = ;
      [*] = ;      if (not isDead) and (curUID = dummyUID) then
      [*] = ;      begin
      [*] = ;         if count = i then
      [*] = ;         begin
      [*] = ;            heroHandle := goHandle;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;         count := count + 1;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if heroHandle = 0 then
      [*] = ;   begin
      [*] = ;      var pProvDefender : Integer = ParserSelectByHandleByKey(pProvince, 'Defender');
      [*] = ;      defID := ParserGetIntValueByKeyByHandle(pProvDefender, 'DefenderID');
      [*] = ;   end;
      [*] = ;
      [*] = ;   var tag : Integer = heroHandle;
      [*] = ;   SetGUIElementTag(elmItemHandle, tag);
      [*] = ;
      [*] = ;   var defName : String;
      [*] = ;   if (heroHandle <> 0) then
      [*] = ;   begin
      [*] = ;      var pHeroParser : Integer = ParserSelectGameObject(heroHandle);
      [*] = ;      var portrait : String = ParserGetValueByKeyByHandle(pHeroParser, 'Portrait');
      [*] = ;      var heroClass1 : Integer = GetGameObjectIntValueIndByHandle(heroHandle, gc_map_GOStack_MapUnit_iClassInd1);
      [*] = ;
      [*] = ;      IntRegister0 := heroClass1;
      [*] = ;      MapExecuteState('GetHeroClassParserByIndex');
      [*] = ;      var pHeroClass : Integer = IntRegister1;
      [*] = ;
      [*] = ;      var className : String = ParserGetValueByKeyByHandle(pHeroClass, 'Class');
      [*] = ;
      [*] = ;      matName := portrait;
      [*] = ;      sizeX := round(GetGUITextureWidth(matName)*0.5)-2;
      [*] = ;      sizeY := round(GetGUITextureHeight(matName)*0.5)-2;
      [*] = ;      var elmHandle : Integer = _gui_CreateImage('portrait', elmItemHandle, matName, 'halParentLeft', 'valParentTop', 2, 2, sizeX, sizeY, 0);
      [*] = ;
      [*] = ;      matName := 'map.heroselection.button.normal';
      [*] = ;      sizeX := round(GetGUITextureWidth(matName)*0.75);
      [*] = ;      sizeY := round(GetGUITextureHeight(matName)*0.75);
      [*] = ;      elmHandle := _gui_CreateImage('button_hero', elmItemHandle, matName, 'halParentLeft', 'valParentTop', 2, 2, sizeX, sizeY, 0);
      [*] = ;
      [*] = ;      matName := 'map.heroselection.browncircle';
      [*] = ;      sizeX := round(GetGUITextureWidth(matName)*0.75);
      [*] = ;      sizeY := round(GetGUITextureHeight(matName)*0.75);
      [*] = ;      elmHandle := _gui_CreateImage('frame', elmItemHandle, matName, 'halParentLeft', 'valParentTop', 0, 0, sizeX, sizeY, 0);
      [*] = ;
      [*] = ;      _hero_GetName(heroHandle, defName);
      [*] = ;      defName := GetGUIWrappedTextFormatByFont(fontHandleT, defName, 350);
      [*] = ;      elmTextHandle := _gui_CreateText('text_name', elmItemHandle, defName, 'halParentLeft', 'valParentTop', 65, 18, 300, 20, 'halLeft', 'valTop', fontHandleT, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      matName := 'icon.defender.'+IntToStr(defID);
      [*] = ;      sizeX := round(GetGUITextureWidth(matName));
      [*] = ;      sizeY := round(GetGUITextureHeight(matName));
      [*] = ;      var elmHandle : Integer = _gui_CreateImage('image', elmItemHandle, matName, 'halParentLeft', 'valParentTop', 2, 2, 52, 52, 0);
      [*] = ;      elmHandle := _gui_CreateImage('button_defender', elmItemHandle, 'icons.52x52.cover.normal', 'halParentLeft', 'valParentTop', 0, 0, 53, 56, 0);
      [*] = ;
      [*] = ;      defName := GetLocaleTableListItemByID('defender', IntToStr(defID));
      [*] = ;      defName := GetGUIWrappedTextFormatByFont(fontHandleT, defName, 350);
      [*] = ;      elmTextHandle := _gui_CreateText('text_name', elmItemHandle, defName, 'halParentLeft', 'valParentTop', 65, 18, 300, 20, 'halLeft', 'valTop', fontHandleT, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;
      [*] = ;      isHero := True;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (defendersCount>onePageCount) then
      [*] = ;   begin
      [*] = ;      var height : Integer = 86;
      [*] = ;      var size : Integer = round(height/(defendersCount+1));
      [*] = ;
      [*] = ;      posX := 127;
      [*] = ;      posY := 158+round(size/2);
      [*] = ;      yOff := round((height-size)/(defendersCount-1)*i);
      [*] = ;      var elmHandle : Integer = _gui_CreateImage('scroll_points_background'+IntToStr(i), elmParentHandle, 'battlepanel.meter.round', 'halParentMiddle', 'valParentMiddle', posX, posY+yOff, size, size, 0);
      [*] = ;      elmHandle := _gui_CreateImage('scroll_points_'+IntToStr(i), elmParentHandle, 'battlepanel.meter.round.brown', 'halParentMiddle', 'valParentMiddle', posX, posY+yOff, size, size, 0);
      [*] = ;      if (i>(onePageCount-1)) then
      [*] = ;         SetGUIElementUserBlend(elmHandle, 0)
      [*] = ;      else
      [*] = ;         SetGUIElementUserBlend(elmHandle, 1);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var allHeight : Integer = offsetBetweenResults*defendersCount;
      [*] = ;SetGUIElementHeight(elmScrollLayer, allHeight); //MUST BE LAST TO MAKE SCROLL CUT WORK
      [*] = ;
      [*] = ;if (defendersCount>onePageCount) then
      [*] = ;begin
      [*] = ;   var elmVScroll : Integer = GetGUIElementVScroll(elmScrollLayer);
      [*] = ;   posX := 127;
      [*] = ;   posY := 138;
      [*] = ;   yOff := 124;
      [*] = ;   var curScrollPos : Float = GetGUIScrollBarPosition(elmVScroll);
      [*] = ;   var elmBtnHandle : Integer = _gui_CreateButton('scroll_up', elmParentHandle, '', 'common.scroller.up', 'halParentMiddle', 'valParentMiddle', posX, posY, 43, 43, cEventState, '', gc_gui_selectdefender_btnScrollUp);
      [*] = ;   if defendersCount <= 3 then
      [*] = ;      SetGUIElementEnabled(elmBtnHandle, false)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if curScrollPos > 0 then
      [*] = ;         SetGUIElementEnabled(elmBtnHandle, true)
      [*] = ;      else
      [*] = ;         SetGUIElementEnabled(elmBtnHandle, false);
      [*] = ;   end;
      [*] = ;
      [*] = ;   elmBtnHandle := _gui_CreateButton('scroll_down', elmParentHandle, '', 'common.scroller.down', 'halParentMiddle', 'valParentMiddle', posX, posY+yOff, 43, 43, cEventState, '', gc_gui_selectdefender_btnScrollDown);
      [*] = ;   if defendersCount <= 3 then
      [*] = ;      SetGUIElementEnabled(elmBtnHandle, false)
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      if curScrollPos < 1 then
      [*] = ;         SetGUIElementEnabled(elmBtnHandle, true)
      [*] = ;      else
      [*] = ;         SetGUIElementEnabled(elmBtnHandle, false);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (not bVisible) then
      [*] = ;   _gui_FadeElement(elmParentHandle, gc_gui_FadeTime0_2, true, true, true);
      [*] = ;
      [*] = ;_gui_RootWindowAdd(elmParentHandle,cRootWindowActive);
      [*] = ;SetGUIElementPressState(elmParentHandle, cEventState);
      [*] = ;GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;
      [*] = ;case gIntRegister_CurGameMode of
      [*] = ;   gc_GameModeStrategy : _gv_SetMapLock(2,_log_name);
      [*] = ;   gc_GameModeTactics : _gv_SetBattleLock(2,_log_name);
      [*] = ;end;
      [*] = ;//elmBtnHandle := _gui_CreateButton('scroll_slider', elmParentHandle, '', 'battlepanel.meter.round.yellow', 'halParentMiddle', 'valParentMiddle', posX, posY+30, 43, 43, cEventState, '', 0);
      [*] = ;
      [*] = ;{elmBtnHandle := _gui_CreateButton('scroll_slider', elmParentHandle, '', 'map.dialog.scroller.slider', 'halParentMiddle', 'valParentMiddle', posX, posY+30, 43, 43, cEventState, '', 0);
      [*] = ;const MaterialName = 'map.dialog.scroller.slider';
      [*] = ;SetGUIElementVisibleProperties(elmBtnHandle, 'UpProperty', MaterialName, 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;SetGUIElementVisibleProperties(elmBtnHandle, 'HoverProperty', MaterialName, 0, 0, 0, 0,  6, 0.5, 0.5, 0.5, 1);
      [*] = ;SetGUIElementVisibleProperties(elmBtnHandle, 'DownProperty', MaterialName, 0, 0, 0, 0,  6, 0.5, 0.5, 0.5, 1);
      [*] = ;SetGUIElementVisibleProperties(elmBtnHandle, 'DisableProperty', MaterialName, 0, 0, 0, 0, -1, 0.5, 0.5, 0.5, 1);
      [*] = ;SetGUIElementVisibleProperties(elmBtnHandle, 'CheckOnProperty', MaterialName, 0, 0, 0, 0,  6, 0.5, 0.5, 0.5, 1);}
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

