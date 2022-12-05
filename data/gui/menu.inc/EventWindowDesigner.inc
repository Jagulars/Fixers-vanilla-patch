section.begin
   Name = EventWindowDesigner
   Code : struct.begin
      [*] = ;var pWindowDesigner : Integer = _misc_ParserGetOrCreateByKey('window_designer', false);
      [*] = ;var pData : Integer = ParserSelectByHandleByKey(pWindowDesigner, 'WindowDesignerData');
      [*] = ;
      [*] = ;var pActiveElement : Integer = ParserGetIntValueByKeyByHandle(pWindowDesigner, 'ActiveElement');
      [*] = ;var activeElmHandle : Integer = ParserGetIntValueByKeyByHandle(pActiveElement, 'Handle');
      [*] = ;var activeChildIndex : Integer = ParserGetIntValueByKeyByHandle(pWindowDesigner, 'ActiveChildIndex');
      [*] = ;
      [*] = ;const cBaseWindowVisualOffset = 220;
      [*] = ;
      [*] = ;const cBtnExitToMainMenu = 1;
      [*] = ;const cBtnLoadTag = 2;
      [*] = ;const cLoadTag = 3;
      [*] = ;const cSaveTag = 4;
      [*] = ;const cDuplicateTag = 5;
      [*] = ;const cElementShowActiveTag = 6;
      [*] = ;const cElementDeleteActiveTag = 7;
      [*] = ;const cElementConfirmDeleteActiveTag = 8;
      [*] = ;const cElementParentTag = 9;
      [*] = ;const cElementChildTag = 10;
      [*] = ;const cElementNextChildTag = 11;
      [*] = ;const cElementPreviousChildTag = 12;
      [*] = ;const cApplyPropertiesTag = 13;
      [*] = ;const cCheckBoxAddNew = 14;
      [*] = ;const cMultiEditChildrenTag = 15;
      [*] = ;//const cCheckBoxExternalPaste = 15;
      [*] = ;const cElementTypeTagBase = 100;
      [*] = ;const cElementPropertyTagBase = 200;
      [*] = ;
      [*] = ;var key : String = GetValueByName('Key');
      [*] = ;var sPress  : String = GetValueByName('Press');
      [*] = ;var status  : String = GetValueByName('Status');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var elmName : String = GetGUIElementNameByIndex(elmHandle);
      [*] = ;
      [*] = ;procedure BlinkElement(elmHandle : Integer);
      [*] = ;begin
      [*] = ;   var elmBlinkHandle : Integer = AddNewElementByClassNameParent('pointer_blink', 'TOSWImageGuiControl', 0, elmHandle);
      [*] = ;   SetGUIElementAlign(elmBlinkHandle, 'halParentLeft', 'valParentTop');
      [*] = ;   SetGUIElementMaterial(elmBlinkHandle, gc_gui_material_blink_btn_square);
      [*] = ;   SetGUIAllowEvents(elmBlinkHandle, False, False, False);
      [*] = ;   var width : Integer = Max(20, GetGUIElementWidth(elmHandle));
      [*] = ;   var height : Integer = Max(20, GetGUIElementHeight(elmHandle));
      [*] = ;   
      [*] = ;   SetGUIElementAllPositionRect(elmBlinkHandle, 0, 0, width, height);
      [*] = ;   SetGUIElementVisible(elmBlinkHandle, True);
      [*] = ;   
      [*] = ;   SetGUIElementFadeStart(elmBlinkHandle, false);
      [*] = ;   SetGUIElementFadeAutoDestroy(elmBlinkHandle, true);
      [*] = ;   SetGUIElementFadeInEnabled(elmBlinkHandle, true);
      [*] = ;   SetGUIElementFadeOutEnabled(elmBlinkHandle, true);
      [*] = ;   SetGUIElementFreezeEnabled(elmBlinkHandle, true);
      [*] = ;   SetGUIElementFadeCount(elmBlinkHandle, 1);
      [*] = ;   SetGUIElementFadingTimes(elmBlinkHandle, 0.5, 0);
      [*] = ;   SetGUIElementFadeStart(elmBlinkHandle, true);
      [*] = ;end;
      [*] = ;
      [*] = ;function ParserGetBaseWindow() : Integer;
      [*] = ;begin
      [*] = ;   Result := ParserSelectByHandleByKey(pWindowDesigner, 'BaseWindow');
      [*] = ;   if Result = 0 then
      [*] = ;      Result := ParserAddChildByIndex(pWindowDesigner, 'BaseWindow');
      [*] = ;end;
      [*] = ;
      [*] = ;function ParserGetElementTypeByName(elmTypeName : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var pElementTypes : Integer = ParserSelectByHandleByKey(pData, 'ElementTypes');
      [*] = ;   var i, pElementType : Integer;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pElementTypes)-1 do
      [*] = ;   begin
      [*] = ;      pElementType := ParserSelectByHandleByIndex(pElementTypes, i);
      [*] = ;      if ParserGetValueByKeyByHandle(pElementType, 'Name') = elmTypeName then
      [*] = ;      begin
      [*] = ;         Result := pElementType;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetPropertyByName(propertyName : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var pProperties : Integer = ParserSelectByHandleByKey(pData, 'Properties');
      [*] = ;   var i, pProperty : Integer;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pProperties)-1 do
      [*] = ;   begin
      [*] = ;      pProperty := ParserSelectByHandleByIndex(pProperties, i);
      [*] = ;      if ParserGetValueByKeyByHandle(pProperty, 'Name') = propertyName then
      [*] = ;      begin
      [*] = ;         Result := pProperty;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure GetPropertyTypeByName(propertyName : String; var propertyType : String);
      [*] = ;begin
      [*] = ;   var pProperty : Integer = GetPropertyByName(propertyName);
      [*] = ;   propertyType := ParserGetValueByKeyByHandle(pProperty, 'Type');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure GetPropertyValueByIndex(propertyName : String; index : Integer; var value : String);
      [*] = ;begin
      [*] = ;   var pProperty : Integer = GetPropertyByName(propertyName);
      [*] = ;   var pOptions : Integer = ParserSelectByHandleByKey(pProperty, 'Options');
      [*] = ;   var pOption : Integer = ParserSelectByHandleByIndex(pOptions, index);
      [*] = ;   value := ParserGetValueByKeyByHandle(pOption, 'Value');
      [*] = ;end;
      [*] = ;
      [*] = ;function GetPropertyMaxValue(propertyName : String) : Integer;
      [*] = ;begin
      [*] = ;   var pProperty : Integer = GetPropertyByName(propertyName);
      [*] = ;   if ParserIsValueExistsByKeyByHandle(pProperty, 'Max') then
      [*] = ;      Result := ParserGetIntValueByKeyByHandle(pProperty, 'Max')
      [*] = ;   else
      [*] = ;      Result := 1000000000;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetPropertyMinValue(propertyName : String) : Integer;
      [*] = ;begin
      [*] = ;   var pProperty : Integer = GetPropertyByName(propertyName);
      [*] = ;   if ParserIsValueExistsByKeyByHandle(pProperty, 'Min') then
      [*] = ;      Result := ParserGetIntValueByKeyByHandle(pProperty, 'Min')
      [*] = ;   else
      [*] = ;      Result := -1000000000;
      [*] = ;end;
      [*] = ;
      [*] = ;function GetElementPropertyByName(elmTypeName, propertyName : String) : Integer;
      [*] = ;begin
      [*] = ;   var pElementType : Integer = ParserGetElementTypeByName(elmTypeName);
      [*] = ;   var pProperties : Integer = ParserSelectByHandleByKey(pElementType, 'Properties');
      [*] = ;   var i, pProperty : Integer;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pProperties)-1 do
      [*] = ;   begin
      [*] = ;      pProperty := ParserSelectByHandleByIndex(pProperties, i);
      [*] = ;      if ParserGetValueByKeyByHandle(pProperty, 'Name') = propertyName then
      [*] = ;      begin
      [*] = ;         Result := pProperty;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;function GetIntPropertyDefault(elmTypeName, propertyName : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := ParserGetIntValueByKeyByHandle(GetElementPropertyByName(elmTypeName, propertyName), 'Default');
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;function GetFloatPropertyDefault(elmTypeName, propertyName : String) : Float;
      [*] = ;begin
      [*] = ;   Result := ParserGetFloatValueByKeyByHandle(GetElementPropertyByName(elmTypeName, propertyName), 'Default');
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;function GetBoolPropertyDefault(elmTypeName, propertyName : String) : Boolean;
      [*] = ;begin
      [*] = ;   Result := ParserGetBoolValueByKeyByHandle(GetElementPropertyByName(elmTypeName, propertyName), 'Default');
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;procedure GetPropertyDefault(elmTypeName, propertyName : String; var value : String);
      [*] = ;begin
      [*] = ;   var pProperty : Integer = GetElementPropertyByName(elmTypeName, propertyName);
      [*] = ;   if pProperty <> 0 then
      [*] = ;      value := ParserGetValueByKeyByHandle(pProperty, 'Default')
      [*] = ;   else
      [*] = ;      value := '';
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;function ParserGetByName(pParser : Integer; name : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   
      [*] = ;   var i, pChild : Integer;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pParser)-1 do
      [*] = ;   begin
      [*] = ;      pChild := ParserSelectByHandleByIndex(pParser, i);
      [*] = ;      if SameText(ParserGetValueByKeyByHandle(pChild, 'Name'), name) then
      [*] = ;      begin
      [*] = ;         Result := pChild;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;procedure GenerateName(elmType : String; pParent : Integer; var name : String);
      [*] = ;begin
      [*] = ;   var pChildren : Integer = ParserSelectByHandleByKey(pParent, 'Children');
      [*] = ;   var count : Integer = 0;
      [*] = ;   var i, pChild : Integer;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pChildren)-1 do
      [*] = ;   begin
      [*] = ;      pChild := ParserSelectByHandleByIndex(pChildren, i);
      [*] = ;      if ParserGetValueByKeyByHandle(pChild, 'ElementType') = elmType then
      [*] = ;         count := count + 1;
      [*] = ;   end;
      [*] = ;   name := elmType+' '+IntToStr(count);
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;function IsBaseType(elmType : String) : Boolean;
      [*] = ;begin
      [*] = ;   Result := (elmType = 'Large Window') or (elmType = 'Small Window') or (elmType = 'Dummy Window');
      [*] = ;end;
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
      [*] = ;function DesignerCreateElementFromParser(pElement, parent : Integer) : Integer;
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
      [*] = ;   //var pressState : String = ParserGetValueByKeyByHandle(pElement, 'PressState'); // press states are not used within the designer
      [*] = ;   //var tag : Integer = ParserGetIntValueByKeyByHandle(pElement, 'Tag'); // tags are not used within the designer
      [*] = ;   var color : TColorRGBA;
      [*] = ;   _gui_GetColorByName(ParserGetValueByKeyByHandle(pElement, 'Color'), color);
      [*] = ;   
      [*] = ;   case elmType of 
      [*] = ;      'Large Window' : begin
      [*] = ;         Result := _gui_CreateLargeWindow(0, name, 'halMiddle', 'valTop', 0, cBaseWindowVisualOffset, width, height, false);
      [*] = ;                  
      [*] = ;         var fontHandle3 : String;
      [*] = ;         _gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_largest,'',fontHandle3); // HeaderM
      [*] = ;         var elmHeaderHandle : Integer = GetGUIElementIndexByNameParent('header', Result);
      [*] = ;         var header : String = ParserGetValueByKeyByHandle(pElement, 'Header');
      [*] = ;         if header <> '' then
      [*] = ;            _gui_CreateText('', elmHeaderHandle, header, 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHeaderHandle), GetGUIElementHeight(elmHeaderHandle), 'halMiddle', 'valMiddle', fontHandle3, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1)
      [*] = ;        else
      [*] = ;           SetGUIElementVisible(elmHeaderHandle, False);
      [*] = ;      end;
      [*] = ;      'Small Window' : begin
      [*] = ;         Result := _gui_CreateSmallWindow(0, name, 'halMiddle', 'valTop', 0, cBaseWindowVisualOffset, width, height, false);
      [*] = ;      end;
      [*] = ;      'Dummy Window' : begin
      [*] = ;         Result := _gui_GetOrCreateElement(name, _gui_GetLayerI(), 'halMiddle', 'valTop', 0, cBaseWindowVisualOffset, GetViewerWidth, GetViewerHeight, 0);
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
      [*] = ;         Result := _gui_CreateInputControl_VVK(name, parent, '', gc_gui_align_parent_lt, bCenteredText, rect, maxInput, '', hint);
      [*] = ;         SetGUIElementAlign(GetGUIElementParentByIndex(Result), hAlign, vAlign);
      [*] = ;      end;
      [*] = ;      'Button' : begin
      [*] = ;         Result := _gui_CreateButton(name, parent, '', material, hAlign, vAlign, x, y, width, height, '', hint, 0);
      [*] = ;      end;
      [*] = ;      'Checkbox' : begin
      [*] = ;         Result := _gui_CreateCheckBox(name, parent, false, text, hAlign, vAlign, x, y, '', hint, 0);
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
      [*] = ;         Result := _gui_CreateListBoxMiddleExt(name, parent, itemsCount, maxDisplayed, x, y, width, '', hAlign);
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
      [*] = ;            'Knob Slider' : Result := _gui_CreateSlider(name, 0, text, parent, hAlign, vAlign, x, y, '', hint, 49, 3, 'halMiddle', 'valMiddle', font, color.r, color.g, color.b, color.a);
      [*] = ;            'Simple Knob Slider' : Result := _gui_CreateSimpleSlider(name, 0, parent, hAlign, vAlign, x, y, ''); 
      [*] = ;            'Arrow Slider' : Result := _gui_CreateIntSlider(name, parent, hAlign, vAlign, x, y, width, '', hint, 49, 3, 'halMiddle', 'valMiddle', font, color.r, color.g, color.b, color.a);
      [*] = ;            'Simple Arrow Slider' : Result := _gui_CreateSimpleIntSlider(name, parent, hAlign, vAlign, x, y, width, '', hint, 0); 
      [*] = ;            'Small Arrow Slider' : Result := _gui_CreateSimpleIntSlider(name, parent, hAlign, vAlign, x, y, width, '', hint, 1); 
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
      [*] = ;   var i : Integer;
      [*] = ;   var pChildren : Integer = ParserSelectByHandleByKey(pElement, 'Children');
      [*] = ;   for i := 0 to ParserGetCountByHandle(pChildren)-1 do
      [*] = ;   begin
      [*] = ;      DesignerCreateElementFromParser(ParserSelectByHandleByIndex(pChildren, i), Result);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;procedure RemoveWindow();
      [*] = ;begin
      [*] = ;   var pBase : Integer = ParserGetBaseWindow;
      [*] = ;   var baseElmHandle : Integer = ParserGetIntValueByKeyByHandle(pBase, 'Handle');
      [*] = ;   _gui_RootWindowRemoveWithFade(baseElmHandle,0);
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;procedure BuildWindow();
      [*] = ;begin
      [*] = ;   DesignerCreateElementFromParser(ParserGetBaseWindow, _gui_GetLayerI);
      [*] = ;   BoolRegister0 := false;
      [*] = ;   ExecuteState('WindowDesigner');
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;function GetFocusedTextHandle() : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   
      [*] = ;   var elmProperties : Integer = _gui_GetWindow('Window Designer.Properties');
      [*] = ;   var i, childHandle, elmInput : Integer;
      [*] = ;   var elmName, propertyType : String;
      [*] = ;   
      [*] = ;   for i := 0 to GetGUIElementChildrenCount(elmProperties)-1 do
      [*] = ;   begin
      [*] = ;      childHandle := GetGUIElementChildrenByIndex(elmProperties, i);
      [*] = ;      elmName := GetGUIElementNameByIndex(childHandle);
      [*] = ;      GetPropertyTypeByName(elmName, propertyType);
      [*] = ;      
      [*] = ;      if (propertyType = 'StringInput') or (propertyType = 'IntInput') then
      [*] = ;      begin
      [*] = ;         elmInput := GetGUIElementIndexByNameParent('text' childHandle);
      [*] = ;         if (GetGUIElementFocusedByHandle(elmInput)) then
      [*] = ;         begin
      [*] = ;            Result := elmInput;
      [*] = ;            break;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;procedure ApplyProperties();
      [*] = ;begin
      [*] = ;   procedure ApplyToElement(pElement : Integer; propertyType, propertyName, value : String);
      [*] = ;   begin
      [*] = ;      if (propertyType = 'StringInput') or (propertyType = 'Listbox') then
      [*] = ;         ParserSetValueByKeyByHandle(pElement, propertyName, value)
      [*] = ;      else
      [*] = ;      if (propertyType = 'IntInput') then
      [*] = ;      begin
      [*] = ;         var intValue : Integer = StrToInt(value);
      [*] = ;         intValue := Min(GetPropertyMaxValue(propertyName), intValue);
      [*] = ;         intValue := Max(GetPropertyMinValue(propertyName), intValue);
      [*] = ;         ParserSetIntValueByKeyByHandle(pElement, propertyName, intValue);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var elmProperties : Integer = _gui_GetWindow('Window Designer.Properties');
      [*] = ;   if elmProperties <> 0 then
      [*] = ;   begin
      [*] = ;      var i, childHandle, elmInput, valueChange : Integer;
      [*] = ;      var propertyName, propertyType, value, activeChildValue : String;
      [*] = ;      
      [*] = ;      var pChildren : Integer = ParserSelectByHandleByKey(pActiveElement, 'Children');
      [*] = ;      var childCount : Integer = ParserGetCountByHandle(pChildren);
      [*] = ;      var bMultiEditChildren : Boolean = ParserGetBoolValueByKeyByHandle(pWindowDesigner, 'MultiEditChildren') and (childCount > 1);
      [*] = ;      
      [*] = ;      for i := 0 to GetGUIElementChildrenCount(elmProperties)-1 do
      [*] = ;      begin
      [*] = ;         childHandle := GetGUIElementChildrenByIndex(elmProperties, i);
      [*] = ;         propertyName := GetGUIElementNameByIndex(childHandle);
      [*] = ;         GetPropertyTypeByName(propertyName, propertyType);
      [*] = ;      
      [*] = ;         if (propertyType = 'StringInput') or (propertyType = 'IntInput') or (propertyType = 'Listbox') then
      [*] = ;         begin
      [*] = ;            activeChildValue := ParserGetValueByKeyByHandle(ParserSelectByHandleByIndex(pChildren, activeChildIndex), propertyName);
      [*] = ;      
      [*] = ;            if (propertyType = 'Listbox') then
      [*] = ;            begin
      [*] = ;               var index : Integer = GetGUIListBoxItemTag(childHandle, GetGUIListBoxItemIndex(childHandle));
      [*] = ;               GetPropertyValueByIndex(propertyName, index, value);
      [*] = ;               
      [*] = ;               if ((value = '') and (not bMultiEditChildren)) or (bMultiEditChildren and (activeChildValue = value)) then // during multiedit don't assign values at all if active child value is not changed, which means it was not touched. Assigning it would mean every child would get the same value unintentionally.
      [*] = ;                  continue;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               elmInput := GetGUIElementIndexByNameParent('text' childHandle);
      [*] = ;               if elmInput <> 0 then
      [*] = ;               begin
      [*] = ;                  value := GetGUIElementText(elmInput);
      [*] = ;                  
      [*] = ;                  if bMultiEditChildren then
      [*] = ;                  begin
      [*] = ;                     if (activeChildValue = value) then // during multiedit don't assign values at all if active child value is not changed, which means it was not touched. Assigning it would mean every child would get the same value unintentionally.
      [*] = ;                        continue
      [*] = ;                     else
      [*] = ;                     if (propertyType = 'IntInput') then
      [*] = ;                     begin
      [*] = ;                        valueChange := StrToInt(value) - StrToInt(activeChildValue);
      [*] = ;                        SetGUIElementText(elmInput, IntToStr(StrToInt(value) + valueChange));
      [*] = ;                     end;
      [*] = ;                 end;
      [*] = ;               end
      [*] = ;               else
      [*] = ;                  continue;
      [*] = ;            end;
      [*] = ;      
      [*] = ;            if bMultiEditChildren then
      [*] = ;            begin
      [*] = ;               var j, k, pChild, pElementType, pElmProperties, pElmProperty : Integer;
      [*] = ;            
      [*] = ;               for j := 0 to childCount-1 do
      [*] = ;               begin
      [*] = ;                  pChild := ParserSelectByHandleByIndex(pChildren, j);
      [*] = ;                  pElementType := ParserGetElementTypeByName(ParserGetValueByKeyByHandle(pChild, 'ElementType'));
      [*] = ;                  pElmProperties := ParserSelectByHandleByKey(pElementType, 'Properties');
      [*] = ;                  
      [*] = ;                  for k := 0 to ParserGetCountByHandle(pElmProperties)-1 do
      [*] = ;                  begin
      [*] = ;                     pElmProperty := ParserSelectByHandleByIndex(pElmProperties, k);
      [*] = ;                     if (ParserGetValueByKeyByHandle(pElmProperty, 'Name') = propertyName) and ParserGetBoolValueByKeyByHandle(pElmProperty, 'Edit') then
      [*] = ;                     begin
      [*] = ;                        if (propertyType = 'IntInput') then
      [*] = ;                           value := IntToStr(ParserGetIntValueByKeyByHandle(pChild, propertyName) + valueChange);
      [*] = ;                        
      [*] = ;                        ApplyToElement(pChild, propertyType, propertyName, value);
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               ApplyToElement(pActiveElement, propertyType, propertyName, value);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      
      [*] = ;      RemoveWindow();
      [*] = ;      BuildWindow();
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;procedure RemoveIrrelevantData(pParser : Integer);
      [*] = ;begin
      [*] = ;   ParserSetIntValueByKeyByHandle(pParser, 'Handle', 0);
      [*] = ;   
      [*] = ;   var i, pChild : Integer;
      [*] = ;   var pChildren : Integer = ParserSelectByHandleByKey(pParser, 'Children');
      [*] = ;   for i := 0 to ParserGetCountByHandle(pChildren)-1 do
      [*] = ;   begin
      [*] = ;      pChild := ParserSelectByHandleByIndex(pChildren, i);
      [*] = ;      RemoveIrrelevantData(pChild);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;
      [*] = ;var elmSliderHandle : Integer;
      [*] = ;if (gIntRegister_GUIScrollSliderHandle<>0) then
      [*] = ;   elmSliderHandle := gIntRegister_GUIScrollSliderHandle
      [*] = ;else
      [*] = ;   elmSliderHandle := GetGUIElementParentByIndex(elmHandle);
      [*] = ;var sliderID : String = GetGUIElementStringTag(elmSliderHandle);
      [*] = ;
      [*] = ;if (elmName='btnSlider') or (elmName='lineSlider') then
      [*] = ;begin
      [*] = ;   if (status='geMouseDown') then
      [*] = ;   begin
      [*] = ;      gIntRegister_GUIScrollSliderHandle := elmSliderHandle;
      [*] = ;
      [*] = ;      var mX, my : Integer;
      [*] = ;      var x2, y2 : Integer;
      [*] = ;      GetGUICurrentMouseCoord(mX, mY);
      [*] = ;      GUIInvalidateParentPositions(elmHandle);
      [*] = ;      GetGUIElementAlignPosition(elmHandle, x2, y2);
      [*] = ;      SetIntValueByName('SliderElementDragX', mX-x2);
      [*] = ;      SetIntValueByName('SliderElementDragY', mY-y2);
      [*] = ;      GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gIntRegister_GUIScrollSliderHandle<>0) or ((sPress='d') and (elmName='lineSlider')) then
      [*] = ;begin
      [*] = ;   SetIntValueByName('SliderElementDragX', 14);
      [*] = ;   var value : Float = _gui_ModifySliderValueByMouseCoord(elmSliderHandle);
      [*] = ;   var maxValue : Integer = GetGUIElementTag(elmSliderHandle);
      [*] = ;   _gui_SetSliderText(elmSliderHandle, IntToStr(Round(value * maxValue)));
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;var propertyType : String;
      [*] = ;GetPropertyTypeByName(elmName, propertyType);
      [*] = ;
      [*] = ;{Log('key: '+key);
      [*] = ;Log('sPress: '+sPress);
      [*] = ;Log('status: '+status);
      [*] = ;Log('tag: '+IntToStr(tag));
      [*] = ;Log('elmName: '+elmName);
      [*] = ;Log('propertyType: '+propertyType);
      [*] = ;Log(' ');}
      [*] = ;
      [*] = ;if (propertyType='Listbox') then
      [*] = ;begin
      [*] = ;   ApplyProperties();
      [*] = ;end
      [*] = ;else
      [*] = ;if (sPress='c') then
      [*] = ;begin
      [*] = ;   if (propertyType = 'Checkbox') then
      [*] = ;   begin
      [*] = ;      var pChildren : Integer = ParserSelectByHandleByKey(pActiveElement, 'Children');
      [*] = ;      var childCount : Integer = ParserGetCountByHandle(pChildren);
      [*] = ;      var bMultiEditChildren : Boolean = ParserGetBoolValueByKeyByHandle(pWindowDesigner, 'MultiEditChildren') and (childCount > 1);
      [*] = ;      
      [*] = ;      var bChecked : Boolean = not GetGUIElementChecked(elmHandle);
      [*] = ;      SetGUIElementChecked(elmHandle, bChecked);
      [*] = ;      
      [*] = ;      if bMultiEditChildren then
      [*] = ;      begin
      [*] = ;         var i, j, pChild, pElementType, pElmProperties, pElmProperty : Integer;
      [*] = ;            
      [*] = ;         for i := 0 to childCount-1 do
      [*] = ;         begin
      [*] = ;            pChild := ParserSelectByHandleByIndex(pChildren, i);
      [*] = ;            pElementType := ParserGetElementTypeByName(ParserGetValueByKeyByHandle(pChild, 'ElementType'));
      [*] = ;            pElmProperties := ParserSelectByHandleByKey(pElementType, 'Properties');
      [*] = ;            for j := 0 to ParserGetCountByHandle(pElmProperties)-1 do
      [*] = ;            begin
      [*] = ;               pElmProperty := ParserSelectByHandleByIndex(pElmProperties, j);
      [*] = ;               if (ParserGetValueByKeyByHandle(pElmProperty, 'Name') = elmName) and ParserGetBoolValueByKeyByHandle(pElmProperty, 'Edit') then
      [*] = ;               begin
      [*] = ;                  ParserSetBoolValueByKeyByHandle(pChild, elmName, bChecked);
      [*] = ;                  break;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         ParserSetBoolValueByKeyByHandle(pActiveElement, elmName, bChecked);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if StrExists(elmName, 'arrowSliderLeft') or StrExists(elmName, 'arrowSliderRight') then
      [*] = ;   begin
      [*] = ;      var elmSliderHandle : Integer = GetGUIElementParentByIndex(elmHandle);
      [*] = ;      var sliderID : String = GetGUIElementStringTag(elmSliderHandle);
      [*] = ;      
      [*] = ;      if (sliderID = 'Children') then
      [*] = ;      begin
      [*] = ;         var pChildren : Integer = ParserSelectByHandleByKey(pActiveElement, 'Children');
      [*] = ;         var maxValue : Integer = ParserGetCountByHandle(pChildren)-1;
      [*] = ;         if StrExists(elmName, 'arrowSliderLeft') then
      [*] = ;            activeChildIndex := activeChildIndex-1
      [*] = ;         else
      [*] = ;            activeChildIndex := activeChildIndex+1;
      [*] = ;         if (activeChildIndex > maxValue) then activeChildIndex := 0;
      [*] = ;         if (activeChildIndex < 0) then activeChildIndex := maxValue;
      [*] = ;         
      [*] = ;         var pChild : Integer = ParserSelectByHandleByIndex(pChildren, activeChildIndex);
      [*] = ;         var childHandle : Integer = ParserGetIntValueByKeyByHandle(pChild, 'Handle');
      [*] = ;         var childName : String = GetGUIElementNameByIndex(childHandle);
      [*] = ;         _gui_SetSliderIntValue(elmSliderHandle, activeChildIndex, 8, childName, true);
      [*] = ;         ParserSetIntValueByKeyByHandle(pWindowDesigner, 'ActiveChildIndex', activeChildIndex);
      [*] = ;         BlinkElement(childHandle);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var elmInput : Integer = GetGUIElementIndexByNameParent('text' elmSliderHandle);
      [*] = ;         var value : Integer = StrToInt(GetGUIElementText(elmInput));
      [*] = ;         var change : Integer = 0;
      [*] = ;         if StrExists(elmName, 'arrowSliderLeft') then
      [*] = ;            change := -1
      [*] = ;         else
      [*] = ;            change := 1;
      [*] = ;         
      [*] = ;         if StrExists(elmName, 'Ten') then
      [*] = ;            change := change * 10;
      [*] = ;      
      [*] = ;         SetGUIElementText(elmInput, IntToStr(value+change));
      [*] = ;         ApplyProperties();
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if SameText(key, 'LButton') then
      [*] = ;   begin
      [*] = ;      if (tag >= cElementTypeTagBase) and (tag < cElementPropertyTagBase) then
      [*] = ;      begin
      [*] = ;         var elmAddNewBtn : Integer = _gui_GetWindow('Window Designer.Element Types.Add New');
      [*] = ;         var bAddNew : Boolean = (elmAddNewBtn = 0) or (GetGUIElementChecked(elmAddNewBtn) and (not IsBaseType(elmName)));
      [*] = ;
      [*] = ;         if not bAddNew then
      [*] = ;         begin
      [*] = ;            ParserSetValueByKeyByHandle(pActiveElement, 'ElementType', elmName);
      [*] = ;            RemoveWindow();
      [*] = ;            BuildWindow();
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            var font, hAlign, vAlign, hint, colorName, material, text, name : String;
      [*] = ;            var newElmHandle, pNewElement : Integer = 0;
      [*] = ;            var color : TColorRGBA;
      [*] = ;            var x : Integer = GetIntPropertyDefault(elmName, 'X');
      [*] = ;            var y : Integer = GetIntPropertyDefault(elmName, 'Y');
      [*] = ;            var width : Integer = GetIntPropertyDefault(elmName, 'Width');
      [*] = ;            var height : Integer = GetIntPropertyDefault(elmName, 'Height');
      [*] = ;            GetPropertyDefault(elmName, 'HAlign', hAlign);
      [*] = ;            GetPropertyDefault(elmName, 'VAlign', vAlign);
      [*] = ;            GetPropertyDefault(elmName, 'Tooltip', hint);
      [*] = ;            GetPropertyDefault(elmName, 'Text', text);
      [*] = ;            GetPropertyDefault(elmName, 'Font', font);
      [*] = ;            GetPropertyDefault(elmName, 'Material', material);
      [*] = ;            GetPropertyDefault(elmName, 'Color', colorName);
      [*] = ;            _gui_GetColorByName(colorName, color);
      [*] = ;            GenerateName(elmName, pActiveElement, name);
      [*] = ;            
      [*] = ;            case elmName of
      [*] = ;               'Large Window' :
      [*] = ;               begin
      [*] = ;                  newElmHandle := _gui_CreateLargeWindow(0, name, 'halMiddle', 'valTop', x, cBaseWindowVisualOffset, width, height, false);
      [*] = ;                  pNewElement := ParserAddChildByIndex(pWindowDesigner, 'BaseWindow');
      [*] = ;                  ParserSetValueByKeyByHandle(pNewElement, 'Header', name);
      [*] = ;                  
      [*] = ;                  var fontHandle3 : String;
      [*] = ;                  _gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_largest,'',fontHandle3); // HeaderM
      [*] = ;                  var elmHeaderHandle : Integer = GetGUIElementIndexByNameParent('header', newElmHandle);
      [*] = ;                  var elmTextHandle : Integer = _gui_CreateText('', elmHeaderHandle, name, 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHeaderHandle), GetGUIElementHeight(elmHeaderHandle), 'halMiddle', 'valMiddle', fontHandle3, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;               end;
      [*] = ;               'Small Window' :
      [*] = ;               begin
      [*] = ;                  newElmHandle := _gui_CreateSmallWindow(0, name, 'halMiddle', 'valTop', x, cBaseWindowVisualOffset, width, height, false);
      [*] = ;                  pNewElement := ParserAddChildByIndex(pWindowDesigner, 'BaseWindow');
      [*] = ;               end;
      [*] = ;               'Dummy Window' :
      [*] = ;               begin
      [*] = ;                  newElmHandle := _gui_GetOrCreateElement(name, _gui_GetLayerI(), 'halMiddle', 'valTop', x, cBaseWindowVisualOffset, width, height, 0);
      [*] = ;                  pNewElement := ParserAddChildByIndex(pWindowDesigner, 'BaseWindow');
      [*] = ;               end;
      [*] = ;               'Header' : begin
      [*] = ;                  var headerSize : String;
      [*] = ;                  GetPropertyDefault(elmName, 'Header Size', headerSize);
      [*] = ;                  case headerSize of
      [*] = ;                     'Small' : newElmHandle := _gui_CreateSmallTextStrip(name, activeElmHandle, text, hAlign, vAlign, x, y);
      [*] = ;                     'Medium' : newElmHandle := _gui_CreateTextStrip(name, activeElmHandle, text, hAlign, vAlign, x, y);
      [*] = ;                     'Large' : newElmHandle := _gui_CreateLargeTextStrip(name, activeElmHandle, text, hAlign, vAlign, x, y);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;               'Image' : begin
      [*] = ;                  newElmHandle := _gui_CreateImage(name, activeElmHandle, material, hAlign, vAlign, x, y, width, height, 0);
      [*] = ;               end;
      [*] = ;               'Tiled Image' : begin
      [*] = ;                  newElmHandle := _gui_CreateTileScaleImage(name, activeElmHandle, material, hAlign, vAlign, x, y, width, height, 0);
      [*] = ;               end;
      [*] = ;               'Frame' : begin
      [*] = ;                  newElmHandle := _gui_CreateFrameBorderExt(name, activeElmHandle, hAlign, vAlign, x, y, width, height, GetBoolPropertyDefault(elmName, 'Fill'));
      [*] = ;               end;
      [*] = ;               'Text' : begin
      [*] = ;                  newElmHandle := _gui_CreateText(name, activeElmHandle, text, hAlign, vAlign, x, y, width, height, 'halMiddle', 'valMiddle', font, color.r, color.g, color.b, color.a);
      [*] = ;               end;
      [*] = ;               'Input' : begin
      [*] = ;                  var rect : TRectangle;
      [*] = ;                  _sys_FillRect(rect, x, y, width, height);
      [*] = ;                  newElmHandle := _gui_CreateInputControl_VVK(name, activeElmHandle, '', gc_gui_align_parent_lt, GetBoolPropertyDefault(elmName, 'Centered Text'), rect, GetIntPropertyDefault(elmName, 'Max Input'), '', hint);
      [*] = ;                  SetGUIElementAlign(GetGUIElementParentByIndex(newElmHandle), hAlign, vAlign);
      [*] = ;               end;
      [*] = ;               'Button' : begin
      [*] = ;                  newElmHandle := _gui_CreateButton(name, activeElmHandle, '', material, hAlign, vAlign, x, y, width, height, '', hint, 0);
      [*] = ;               end;
      [*] = ;               'Checkbox' : begin
      [*] = ;                  newElmHandle := _gui_CreateCheckBox(name, activeElmHandle, False, text, hAlign, vAlign, x, y, '', hint, 0);
      [*] = ;               end;
      [*] = ;               'Listbox' : begin
      [*] = ;                  newElmHandle := _gui_CreateListBoxMiddleExt(name, activeElmHandle, 0, 0, x, y, width, '', hAlign);
      [*] = ;               end;
      [*] = ;               'Slider' : begin
      [*] = ;                  var sliderType : String;
      [*] = ;                  GetPropertyDefault(elmName, 'Slider Type', sliderType);
      [*] = ;                  case sliderType of
      [*] = ;                     'Knob Slider' : newElmHandle := _gui_CreateSlider(name, 0, '', activeElmHandle, hAlign, vAlign, x, y, '', hint, 49, 3, 'halMiddle', 'valMiddle', font, color.r, color.g, color.b, color.a);
      [*] = ;                     'Simple Knob Slider' : newElmHandle := _gui_CreateSimpleSlider(name, 0, activeElmHandle, hAlign, vAlign, x, y, ''); 
      [*] = ;                     'Arrow Slider' : newElmHandle := _gui_CreateIntSlider(name, activeElmHandle, hAlign, vAlign, x, y, width, '', hint, 49, 3, 'halMiddle', 'valMiddle', font, color.r, color.g, color.b, color.a);
      [*] = ;                     'Simple Arrow Slider' : newElmHandle := _gui_CreateSimpleIntSlider(name, activeElmHandle, hAlign, vAlign, x, y, width, '', hint, 0); 
      [*] = ;                     'Small Arrow Slider' : newElmHandle := _gui_CreateSimpleIntSlider(name, activeElmHandle, hAlign, vAlign, x, y, width, '', hint, 1); 
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;              'Dummy' : begin
      [*] = ;                  newElmHandle := _gui_CreateDummy(name, activeElmHandle, hAlign, vAlign, x, y, width, height, 0);
      [*] = ;               end;
      [*] = ;               else
      [*] = ;                  ErrorLogI('Trying to add element type: '+elmName+', but such is not supported');
      [*] = ;            end;
      [*] = ;         
      [*] = ;            if newElmHandle <> 0 then
      [*] = ;            begin
      [*] = ;               if pNewElement = 0 then
      [*] = ;               begin
      [*] = ;                  var pChildren : Integer = ParserSelectByHandleByKey(pActiveElement, 'Children');
      [*] = ;                  if pChildren = 0 then
      [*] = ;                     pChildren := ParserAddChildByIndex(pActiveElement, 'Children');
      [*] = ;                  pNewElement := ParserAddChildByIndex(pChildren, '*');
      [*] = ;               end;
      [*] = ;               
      [*] = ;               ParserSetIntValueByKeyByHandle(pNewElement, 'Handle', newElmHandle);
      [*] = ;               ParserSetValueByKeyByHandle(pNewElement, 'ElementType', elmName);
      [*] = ;               ParserSetValueByKeyByHandle(pNewElement, 'Name', name);
      [*] = ;               
      [*] = ;               var pElementType : Integer = ParserGetElementTypeByName(elmName);
      [*] = ;               var pProperties : Integer = ParserSelectByHandleByKey(pElementType, 'Properties');
      [*] = ;               var i, pProperty : Integer;
      [*] = ;               var propertyName : String;
      [*] = ;               for i := 0 to ParserGetCountByHandle(pProperties)-1 do
      [*] = ;               begin
      [*] = ;                  pProperty := ParserSelectByHandleByIndex(pProperties, i);
      [*] = ;                  propertyName := ParserGetValueByKeyByHandle(pProperty, 'Name');
      [*] = ;                  if (propertyName <> 'Name') and (propertyName <> 'Header') then
      [*] = ;                     ParserSetValueByKeyByHandle(pNewElement, propertyName, ParserGetValueByKeyByHandle(pProperty, 'Default'));
      [*] = ;               end;
      [*] = ;               if elmName = 'Listbox' then ParserAddChildByIndex(pNewElement, 'ListBoxItems');
      [*] = ;               ParserAddChildByIndex(pNewElement, 'Children');
      [*] = ;               
      [*] = ;               ParserSetIntValueByKeyByHandle(pWindowDesigner, 'ActiveElement', pNewElement);
      [*] = ;               ParserSetIntValueByKeyByHandle(pWindowDesigner, 'ActiveChildIndex', 0);
      [*] = ;            
      [*] = ;               BoolRegister0 := false;
      [*] = ;               ExecuteState('WindowDesigner');
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         case tag of
      [*] = ;            cBtnExitToMainMenu, gc_gui_hotkey_btnEscape : 
      [*] = ;            begin
      [*] = ;               ParserSaveToFileByHandle(gWindows.handle, '.\data\gui\designerwindows.cfg');
      [*] = ;               
      [*] = ;               var baseElmHandle : Integer = ParserGetIntValueByKeyByHandle(ParserGetBaseWindow, 'Handle');
      [*] = ;               if baseElmHandle <> 0 then
      [*] = ;                  _gui_RootWindowRemoveWithFade(baseElmHandle, gc_gui_FadeTime0_4);
      [*] = ;               ParserFreeByHandle(pWindowDesigner);
      [*] = ;               
      [*] = ;               var elmDesigner : Integer = _gui_GetWindow('Window Designer');
      [*] = ;               _gui_RootWindowRemoveWithFade(elmDesigner, gc_gui_FadeTime0_4);
      [*] = ;               GUIExecuteState('ShowTools');
      [*] = ;            end;
      [*] = ;            cBtnLoadTag : // open load window
      [*] = ;            begin
      [*] = ;               SetIntValueByName('ParserHandle', gWindows.handle);
      [*] = ;               SetValueByName('ReturnState', 'EventWindowDesigner');
      [*] = ;               SetIntValueByName('ReturnTag', cLoadTag);
      [*] = ;               SetIntValueByName('ActiveInd', -1);
      [*] = ;               GUIExecuteState('ShowParserLoadList');
      [*] = ;            end;
      [*] = ;            cLoadTag : // actual load
      [*] = ;            begin
      [*] = ;               var pWindow : Integer = GetIntValueByName('ParserHandle');
      [*] = ;               SetIntValueByName('ParserHandle', 0);
      [*] = ;               var pBaseWindow : Integer = ParserGetBaseWindow;
      [*] = ;               if ParserGetIntValueByKeyByHandle(pBaseWindow, 'Handle') <> 0 then
      [*] = ;               begin
      [*] = ;                  RemoveWindow();
      [*] = ;                  ParserClearByHandle(pBaseWindow);
      [*] = ;               end;
      [*] = ;               ParserCopyFromByHandle(pWindow);
      [*] = ;               
      [*] = ;               BuildWindow();
      [*] = ;               ParserSetIntValueByKeyByHandle(pWindowDesigner, 'ActiveElement', pBaseWindow);
      [*] = ;               ParserSetIntValueByKeyByHandle(pWindowDesigner, 'ActiveChildIndex', 0);
      [*] = ;               
      [*] = ;               BoolRegister0 := false;
      [*] = ;               ExecuteState('WindowDesigner');
      [*] = ;            end;
      [*] = ;            cSaveTag : 
      [*] = ;            begin
      [*] = ;               var pBaseWindow : Integer = ParserGetBaseWindow;
      [*] = ;               var baseName : String = ParserGetValueByKeyByHandle(pBaseWindow, 'Name');
      [*] = ;               if (baseName <> '') then
      [*] = ;               begin
      [*] = ;                  var pSavedWindow : Integer = ParserGetByName(gWindows.handle, baseName);
      [*] = ;                  if (pSavedWindow = 0) then
      [*] = ;                     pSavedWindow := ParserAddChildByIndex(gWindows.handle, '*')
      [*] = ;                  else
      [*] = ;                     ParserClearByHandle(pSavedWindow);
      [*] = ;                  
      [*] = ;                  ParserCopyFromByHandle(pBaseWindow);
      [*] = ;                  RemoveIrrelevantData(pSavedWindow);
      [*] = ;                  ParserSaveToFileByHandle(gWindows.handle, '.\data\gui\designerwindows.cfg');
      [*] = ;                  
      [*] = ;                  BoolRegister0 := false;
      [*] = ;                  ExecuteState('WindowDesigner');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            cDuplicateTag : 
      [*] = ;            begin
      [*] = ;               var pParentChildren : Integer = ParserGetParent(pActiveElement);
      [*] = ;               var pNewElement : Integer = ParserAddChildByIndex(pParentChildren, '*');
      [*] = ;               ParserCopyFromByHandle(pActiveElement);
      [*] = ;               ParserSetIntValueByKeyByHandle(pWindowDesigner, 'ActiveElement', pNewElement);
      [*] = ;               
      [*] = ;               RemoveWindow();
      [*] = ;               BuildWindow();
      [*] = ;            end;
      [*] = ;            cElementShowActiveTag : 
      [*] = ;            begin
      [*] = ;               BlinkElement(activeElmHandle);
      [*] = ;               SetGUIElementVisible(activeElmHandle, not GetGUIElementVisible(activeElmHandle));
      [*] = ;            end;
      [*] = ;            cElementDeleteActiveTag : 
      [*] = ;            begin
      [*] = ;               BlinkElement(ParserGetIntValueByKeyByHandle(pActiveElement, 'Handle'));
      [*] = ;               _gui_ShowQuestionDialog('gui|are_you_sure', 'EventWindowDesigner', cElementConfirmDeleteActiveTag, '', 0, false, false);
      [*] = ;            end;
      [*] = ;            cElementConfirmDeleteActiveTag : 
      [*] = ;            begin
      [*] = ;               ParserSetIntValueByKeyByHandle(pWindowDesigner, 'ActiveChildIndex', 0);
      [*] = ;               
      [*] = ;               if pActiveElement = ParserGetBaseWindow then
      [*] = ;               begin
      [*] = ;                  ParserSetIntValueByKeyByHandle(pWindowDesigner, 'ActiveElement', 0);
      [*] = ;                  var baseElmHandle : Integer = ParserGetIntValueByKeyByHandle(pActiveElement, 'Handle');
      [*] = ;                  _gui_RootWindowRemoveWithFade(baseElmHandle, gc_gui_FadeTime0_2);
      [*] = ;                  ParserFreeByHandle(pActiveElement);
      [*] = ;                  BoolRegister0 := false;
      [*] = ;                  ExecuteState('WindowDesigner');
      [*] = ;               end
      [*] = ;               else
      [*] = ;               begin
      [*] = ;                  var pNewActive : Integer;
      [*] = ;                  var pChildren : Integer = ParserGetParent(pActiveElement);
      [*] = ;                  var childCount : Integer = ParserGetCountByHandle(pChildren);
      [*] = ;                  if childCount > 1 then // select next child
      [*] = ;                  begin
      [*] = ;                     var newChildIndex : Integer = ParserGetIndexOf(pActiveElement) + 1;
      [*] = ;                     if newChildIndex >= childCount then
      [*] = ;                        newChildIndex := 0;
      [*] = ;               
      [*] = ;                     pNewActive := ParserSelectByHandleByIndex(pChildren, newChildIndex);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                     pNewActive := ParserGetParent(pChildren);
      [*] = ;                  
      [*] = ;                  ParserSetIntValueByKeyByHandle(pWindowDesigner, 'ActiveElement', pNewActive);
      [*] = ;                  ParserSetIntValueByKeyByHandle(pWindowDesigner, 'ActiveChildIndex', 0); 
      [*] = ;                  
      [*] = ;                  ParserFreeByHandle(pActiveElement);
      [*] = ;                  RemoveWindow();
      [*] = ;                  BuildWindow();
      [*] = ;                  BlinkElement(ParserGetIntValueByKeyByHandle(pNewActive, 'Handle'));
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            cElementParentTag : 
      [*] = ;            begin
      [*] = ;               var pNewActive : Integer = ParserGetParent(ParserGetParent(pActiveElement));
      [*] = ;               BlinkElement(ParserGetIntValueByKeyByHandle(pNewActive, 'Handle'));
      [*] = ;               ParserSetIntValueByKeyByHandle(pWindowDesigner, 'ActiveElement', pNewActive);
      [*] = ;               ParserSetIntValueByKeyByHandle(pWindowDesigner, 'ActiveChildIndex', 0);
      [*] = ;            
      [*] = ;               BoolRegister0 := false;
      [*] = ;               ExecuteState('WindowDesigner');
      [*] = ;            end;
      [*] = ;            cElementChildTag : 
      [*] = ;            begin
      [*] = ;               var pChildren : Integer = ParserSelectByHandleByKey(pActiveElement, 'Children');
      [*] = ;               var pChild : Integer = ParserSelectByHandleByIndex(pChildren, ParserGetIntValueByKeyByHandle(pWindowDesigner, 'ActiveChildIndex'));
      [*] = ;               ParserSetIntValueByKeyByHandle(pWindowDesigner, 'ActiveElement', pChild);
      [*] = ;               ParserSetIntValueByKeyByHandle(pWindowDesigner, 'ActiveChildIndex', 0);
      [*] = ;               BlinkElement(ParserGetIntValueByKeyByHandle(pChild, 'Handle'));
      [*] = ;            
      [*] = ;               BoolRegister0 := false;
      [*] = ;               ExecuteState('WindowDesigner');
      [*] = ;            end;
      [*] = ;            cElementNextChildTag : 
      [*] = ;            begin
      [*] = ;               var pChildren : Integer = ParserGetParent(pActiveElement);
      [*] = ;               var newChildIndex : Integer = ParserGetIndexOf(pActiveElement) + 1;
      [*] = ;               if newChildIndex >= ParserGetCountByHandle(pChildren) then
      [*] = ;                  newChildIndex := 0;
      [*] = ;               
      [*] = ;               var pChild : Integer = ParserSelectByHandleByIndex(pChildren, newChildIndex);
      [*] = ;               ParserSetIntValueByKeyByHandle(pWindowDesigner, 'ActiveElement', pChild);
      [*] = ;               ParserSetIntValueByKeyByHandle(pWindowDesigner, 'ActiveChildIndex', 0); 
      [*] = ;               BlinkElement(ParserGetIntValueByKeyByHandle(pChild, 'Handle'));
      [*] = ;            
      [*] = ;               BoolRegister0 := false;
      [*] = ;               ExecuteState('WindowDesigner');
      [*] = ;            end;
      [*] = ;            cElementPreviousChildTag : 
      [*] = ;            begin
      [*] = ;               var pChildren : Integer = ParserGetParent(pActiveElement);
      [*] = ;               var newChildIndex : Integer = ParserGetIndexOf(pActiveElement) - 1;
      [*] = ;               if newChildIndex < 0 then
      [*] = ;                  newChildIndex := ParserGetCountByHandle(pChildren)-1;
      [*] = ;               
      [*] = ;               var pChild : Integer = ParserSelectByHandleByIndex(pChildren, newChildIndex);
      [*] = ;               ParserSetIntValueByKeyByHandle(pWindowDesigner, 'ActiveElement', pChild);
      [*] = ;               ParserSetIntValueByKeyByHandle(pWindowDesigner, 'ActiveChildIndex', 0); 
      [*] = ;               BlinkElement(ParserGetIntValueByKeyByHandle(pChild, 'Handle'));
      [*] = ;            
      [*] = ;               BoolRegister0 := false;
      [*] = ;               ExecuteState('WindowDesigner');
      [*] = ;            end;
      [*] = ;            cApplyPropertiesTag : ApplyProperties();
      [*] = ;            cCheckBoxAddNew : 
      [*] = ;            begin
      [*] = ;               var bChecked : Boolean = not GetGUIElementChecked(elmHandle);
      [*] = ;               ParserSetBoolValueByKeyByHandle(pWindowDesigner, 'AddNew', bChecked);
      [*] = ;               SetGUIElementChecked(elmHandle, bChecked);
      [*] = ;            end;
      [*] = ;            cMultiEditChildrenTag : 
      [*] = ;            begin
      [*] = ;               var bChecked : Boolean = not GetGUIElementChecked(elmHandle);
      [*] = ;               ParserSetBoolValueByKeyByHandle(pWindowDesigner, 'MultiEditChildren', bChecked);
      [*] = ;               SetGUIElementChecked(elmHandle, bChecked);
      [*] = ;               
      [*] = ;               BoolRegister0 := false;
      [*] = ;               ExecuteState('WindowDesigner');
      [*] = ;            end;
      [*] = ;            {cCheckBoxExternalPaste : 
      [*] = ;            begin
      [*] = ;               var bChecked : Boolean = not GetGUIElementChecked(elmHandle);
      [*] = ;               ParserSetBoolValueByKeyByHandle(pWindowDesigner, 'ExternalPaste', bChecked);
      [*] = ;               SetGUIElementChecked(elmHandle, bChecked);
      [*] = ;            end;}
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

