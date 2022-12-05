section.begin
   Name = CreateWindowFromParser
   Code : struct.begin
      [*] = ;var windowName : String = StringRegister0;
      [*] = ;
      [*] = ;   
      [*] = ;procedure CheckString(var str : String);
      [*] = ;begin
      [*] = ;   if StrExists(str, '|') and StrExists(str, '+') then
      [*] = ;   begin
      [*] = ;      var delmPos, plusPos, len : Integer;
      [*] = ;      var workPos : Integer = 0;
      [*] = ;      var tempStr, tempStr2 : String = '';
      [*] = ;      
      [*] = ;      while StrExists(str, '|') do
      [*] = ;      begin
      [*] = ;         delmPos := StrPos('|', str);
      [*] = ;         plusPos := StrPosEx('+', str, workPos);
      [*] = ;         
      [*] = ;         if plusPos < workPos then
      [*] = ;            plusPos := StrLength(str)+1;
      [*] = ;         
      [*] = ;         if delmPos < plusPos then
      [*] = ;         begin
      [*] = ;            tempStr := SubStr(str, workPos, plusPos-workPos);
      [*] = ;            tempStr2 := tempStr;
      [*] = ;            _gui_ConvertTableKeyToText(tempStr2);
      [*] = ;            str := StrReplace(str, tempStr, tempStr2);
      [*] = ;         end;
      [*] = ;         
      [*] = ;         workPos := plusPos+1;
      [*] = ;      end;
      [*] = ;      
      [*] = ;      str := StrReplace(str, '+', '');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;   
      [*] = ;
      [*] = ;function CreateElementFromParser(pElement, parent : Integer) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   
      [*] = ;   var elmType : String = ParserGetValueByKeyByHandle(pElement, 'ElementType');
      [*] = ;   var x : Integer = ParserGetIntValueByKeyByHandle(pElement, 'X');
      [*] = ;   var y : Integer = ParserGetIntValueByKeyByHandle(pElement, 'Y');
      [*] = ;   var width : Integer = ParserGetIntValueByKeyByHandle(pElement, 'Width');
      [*] = ;   var height : Integer = ParserGetIntValueByKeyByHandle(pElement, 'Height');
      [*] = ;   var hAlign : String = ParserGetValueByKeyByHandle(pElement, 'HAlign');
      [*] = ;   var vAlign : String = ParserGetValueByKeyByHandle(pElement, 'VAlign');
      [*] = ;   var name : String = ParserGetValueByKeyByHandle(pElement, 'Name');
      [*] = ;   var text : String = ParserGetValueByKeyByHandle(pElement, 'Text');
      [*] = ;   CheckString(text);
      [*] = ;   var hint : String = ParserGetValueByKeyByHandle(pElement, 'Tooltip');
      [*] = ;   CheckString(hint);
      [*] = ;   var font : String = ParserGetValueByKeyByHandle(pElement, 'Font');
      [*] = ;   var material : String = ParserGetValueByKeyByHandle(pElement, 'Material');
      [*] = ;   var pressState : String = ParserGetValueByKeyByHandle(pElement, 'Press State');
      [*] = ;   var tag : Integer = ParserGetIntValueByKeyByHandle(pElement, 'Tag');
      [*] = ;   var color : TColorRGBA;
      [*] = ;   _gui_GetColorByName(ParserGetValueByKeyByHandle(pElement, 'Color'), color);
      [*] = ;   
      [*] = ;   case elmType of 
      [*] = ;      'Large Window' : begin
      [*] = ;         Result := _gui_CreateLargeWindow(0, name, hAlign, vAlign, x, y, width, height, false);
      [*] = ;                  
      [*] = ;         var fontHandle3 : String;
      [*] = ;         _gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_largest,'',fontHandle3); // HeaderM
      [*] = ;         var elmHeaderHandle : Integer = GetGUIElementIndexByNameParent('header', Result);
      [*] = ;         var header : String = ParserGetValueByKeyByHandle(pElement, 'Header');
      [*] = ;         if header <> '' then
      [*] = ;            _gui_CreateText('', elmHeaderHandle, header, 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHeaderHandle), GetGUIElementHeight(elmHeaderHandle), 'halMiddle', 'valMiddle', fontHandle3, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1)
      [*] = ;         else
      [*] = ;            SetGUIElementVisible(elmHeaderHandle, False);
      [*] = ;      end;
      [*] = ;      'Small Window' : begin
      [*] = ;         Result := _gui_CreateSmallWindow(0, name, hAlign, vAlign, x, y, width, height, false);
      [*] = ;      end;
      [*] = ;      'Dummy Window' : begin
      [*] = ;         Result := _gui_GetOrCreateElement(name, _gui_GetLayerI(), hAlign, vAlign, x, y, GetViewerWidth, GetViewerHeight, 0);
      [*] = ;      end;
      [*] = ;      'Header' : begin
      [*] = ;         var headerSize : String = ParserGetValueByKeyByHandle(pElement, 'Header Size');
      [*] = ;         case headerSize of
      [*] = ;            'Small' : Result := _gui_CreateSmallTextStrip(name, parent, text, hAlign, vAlign, x, y);
      [*] = ;            'Medium' : Result := _gui_CreateTextStrip(name, parent, text, hAlign, vAlign, x, y);
      [*] = ;            'Large' : Result := _gui_CreateLargeTextStrip(name, parent, text, hAlign, vAlign, x, y);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      'Image' : begin
      [*] = ;         Result := _gui_CreateImage(name, parent, material, hAlign, vAlign, x, y, width, height, 0);
      [*] = ;      end;
      [*] = ;      'Tiled Image' : begin
      [*] = ;         Result := _gui_CreateTileScaleImage(name, parent, material, hAlign, vAlign, x, y, width, height, 0);
      [*] = ;      end;
      [*] = ;      'Frame' : begin
      [*] = ;         Result := _gui_CreateFrameBorderExt(name, parent, hAlign, vAlign, x, y, width, height, ParserGetBoolValueByKeyByHandle(pElement, 'Fill'));
      [*] = ;      end;
      [*] = ;      'Text' : begin
      [*] = ;         Result := _gui_CreateText(name, parent, text, hAlign, vAlign, x, y, width, height, 'halMiddle', 'valMiddle', font, color.r, color.g, color.b, color.a);
      [*] = ;      end;
      [*] = ;      'Input' : begin
      [*] = ;         var rect : TRectangle;
      [*] = ;         _sys_FillRect(rect, x, y, width, height);
      [*] = ;         var maxInput : Integer = ParserGetIntValueByKeyByHandle(pElement, 'InputMax');
      [*] = ;         var bCenteredText : Boolean = ParserGetBoolValueByKeyByHandle(pElement, 'Centered Text');
      [*] = ;         Result := _gui_CreateInputControl_VVK(name, parent, '', gc_gui_align_parent_lt, bCenteredText, rect, maxInput, pressState, hint);
      [*] = ;         SetGUIElementAlign(GetGUIElementParentByIndex(Result), hAlign, vAlign);
      [*] = ;      end;
      [*] = ;      'Button' : begin
      [*] = ;         Result := _gui_CreateButton(name, parent, '', material, hAlign, vAlign, x, y, width, height, pressState, hint, tag);
      [*] = ;      end;
      [*] = ;      'Checkbox' : begin
      [*] = ;         Result := _gui_CreateCheckBox(name, parent, false, text, hAlign, vAlign, x, y, pressState, hint, tag);
      [*] = ;         var boxOff : Integer = ParserGetIntValueByKeyByHandle(pElement, 'Box X');
      [*] = ;         var textOff : Integer = ParserGetIntValueByKeyByHandle(pElement, 'Text X');
      [*] = ;         SetGUIElementLogicRect(Result, ParserGetIntValueByKeyByHandle(pElement, 'Click Width'), 23);
      [*] = ;         SetGUIElementTextAlign(Result, ParserGetValueByKeyByHandle(pElement, 'Text Align'), 'valMiddle', 0, 0);
      [*] = ;         SetGUIElementVisibleProperties(Result, 'UpProperty', 'common.checkbox.normal', boxOff, 0, textOff, -1, -1, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;         SetGUIElementVisibleProperties(Result, 'HoverProperty', 'common.checkbox.hover', boxOff, 0, textOff, -1, 6, gc_gui_fontcolor_NormalR*1.25, gc_gui_fontcolor_NormalG*1.25, gc_gui_fontcolor_NormalB*1.25, 1);
      [*] = ;         SetGUIElementVisibleProperties(Result, 'DownProperty', 'common.checkbox.pressed', boxOff, 0, textOff, -1, 6, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;         SetGUIElementVisibleProperties(Result, 'DisableProperty', 'common.checkbox.disabled', boxOff, 0, textOff, -1, -1, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;         SetGUIElementVisibleProperties(Result, 'CheckOnProperty', 'common.checkbox.checkon', boxOff, 0, textOff, -1, 6, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;      end;
      [*] = ;      'Listbox' : begin
      [*] = ;         var pListBoxItems : Integer = ParserSelectByHandleByKey(pElement, 'ListBoxItems');
      [*] = ;         var itemsCount : Integer = ParserGetCountByHandle(pListBoxItems);
      [*] = ;         var maxDisplayed : Integer = ParserGetIntValueByKeyByHandle(pElement, 'Max Displayed');
      [*] = ;         Result := _gui_CreateListBoxMiddleExt(name, parent, itemsCount, maxDisplayed, x, y, width, pressState, hAlign);
      [*] = ;         var i, pListBoxItem : Integer;
      [*] = ;         for i := 0 to itemsCount-1 do
      [*] = ;         begin
      [*] = ;            pListBoxItem := ParserSelectByHandleByIndex(pListBoxItems, i);
      [*] = ;            GUIListBoxAddItem(Result, ParserGetValueByKeyByHandle(pListBoxItem, 'Text'), i);
      [*] = ;         end;
      [*] = ;         SetGUIListBoxItemIndexSilent(Result, 0);
      [*] = ;      end;
      [*] = ;      'Slider' : begin
      [*] = ;         var sliderType : String = ParserGetValueByKeyByHandle(pElement, 'Slider Type');
      [*] = ;         case sliderType of
      [*] = ;            'Knob Slider' : Result := _gui_CreateSlider(name, 0, text, parent, hAlign, vAlign, x, y, pressState, hint, 49, 3, 'halMiddle', 'valMiddle', font, color.r, color.g, color.b, color.a);
      [*] = ;            'Simple Knob Slider' : Result := _gui_CreateSimpleSlider(name, 0, parent, hAlign, vAlign, x, y, pressState); 
      [*] = ;            'Arrow Slider' : Result := _gui_CreateIntSlider(name, parent, hAlign, vAlign, x, y, width, pressState, hint, 49, 3, 'halMiddle', 'valMiddle', font, color.r, color.g, color.b, color.a);
      [*] = ;            'Simple Arrow Slider' : Result := _gui_CreateSimpleIntSlider(name, parent, hAlign, vAlign, x, y, width, pressState, hint, 0); 
      [*] = ;            'Small Arrow Slider' : Result := _gui_CreateSimpleIntSlider(name, parent, hAlign, vAlign, x, y, width, pressState, hint, 1); 
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      'Dummy' : begin
      [*] = ;         Result := _gui_CreateDummy(name, parent, hAlign, vAlign, x, y, width, height, 0);
      [*] = ;      end;
      [*] = ;      else
      [*] = ;         ErrorLogI('Trying to build element type: '+elmType+', but such is not supported');
      [*] = ;   end;
      [*] = ;   
      [*] = ;   ParserSetIntValueByKeyByHandle(pElement, 'Handle', Result);
      [*] = ;   
      [*] = ;   if ParserGetBoolValueByKeyByHandle(pElement, 'Disable Client') and (GetLanMode() = 1) then
      [*] = ;      SetGUIAllowEvents(Result, False, False, False);
      [*] = ;   
      [*] = ;   var i : Integer;
      [*] = ;   var pChildren : Integer = ParserSelectByHandleByKey(pElement, 'Children');
      [*] = ;   for i := 0 to ParserGetCountByHandle(pChildren)-1 do
      [*] = ;   begin
      [*] = ;      CreateElementFromParser(ParserSelectByHandleByIndex(pChildren, i), Result);
      [*] = ;   end;
      [*] = ;   
      [*] = ;   var initState : String = ParserGetValueByKeyByHandle(pElement, 'Init State');
      [*] = ;   if initState <> '' then
      [*] = ;   begin
      [*] = ;      SetIntValueByName('ElementHandle', Result);
      [*] = ;      SetIntValueByName('Tag', tag);
      [*] = ;      SetValueByName('Status', 'Initialize');
      [*] = ;      GUIExecuteState(initState);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var pWindow : Integer = _gui_GetWindowParserByName(windowName);
      [*] = ;if pWindow = 0 then
      [*] = ;begin
      [*] = ;   ErrorLogI('CreateWindowFromParser, window: '+windowName+', parser not found');
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;// Check if window was already visible, then no need to FadeIn it when show again
      [*] = ;var prevElmBaseHandle : Integer = GetGUIElementIndexByNameParent(windowName, _gui_GetLayerI());
      [*] = ;var bVisible : Boolean = (prevElmBaseHandle<>0) and GetGUIElementVisible(prevElmBaseHandle);
      [*] = ;
      [*] = ;var elmBaseHandle : Integer = CreateElementFromParser(pWindow, _gui_GetLayerI());
      [*] = ;
      [*] = ;
      [*] = ;if (not bVisible) then
      [*] = ;_gui_FadeElement(elmBaseHandle, gc_gui_FadeTime0_2, true, true, true);
      [*] = ;
      [*] = ;if ParserGetBoolValueByKeyByHandle(pWindow, 'Modal') then
      [*] = ;   _gui_RootWindowAdd(elmBaseHandle,cRootWindowModal);
      [*] = ;GUIExecuteState('GUIInvokeMouseMove');
   struct.end
section.end

