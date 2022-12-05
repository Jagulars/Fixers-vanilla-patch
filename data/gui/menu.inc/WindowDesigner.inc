section.begin
   Name = WindowDesigner
   Description : struct.begin
      [*] = ;
   struct.end
   Code : struct.begin
      [*] = ;var bInit : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;const cFileName = '.\data\gui\windowdesigner.cfg';
      [*] = ;var pWindowDesigner : Integer = _misc_ParserGetOrCreateByKey('window_designer', bInit);
      [*] = ;if bInit then
      [*] = ;begin
      [*] = ;   ParserLoadFromFile(cFileName);
      [*] = ;   ParserSetBoolValueByKeyByHandle(pWindowDesigner, 'AddNew', True);
      [*] = ;   ParserSetBoolValueByKeyByHandle(pWindowDesigner, 'MultiEditChildren', False);
      [*] = ;   //ParserSetBoolValueByKeyByHandle(pWindowDesigner, 'ExternalPaste', False);
      [*] = ;end;
      [*] = ;var pData : Integer = ParserSelectByHandleByKey(pWindowDesigner, 'WindowDesignerData');
      [*] = ;
      [*] = ;
      [*] = ;var pActiveElement : Integer = ParserGetIntValueByKeyByHandle(pWindowDesigner, 'ActiveElement');
      [*] = ;var activeElmHandle : Integer = ParserGetIntValueByKeyByHandle(pActiveElement, 'Handle');
      [*] = ;var activeChildIndex : Integer = ParserGetIntValueByKeyByHandle(pWindowDesigner, 'ActiveChildIndex');
      [*] = ;var bAddNew : Boolean = ParserGetBoolValueByKeyByHandle(pWindowDesigner, 'AddNew');
      [*] = ;var bMultiEditChildren : Boolean = ParserGetBoolValueByKeyByHandle(pWindowDesigner, 'MultiEditChildren');
      [*] = ;var bExternalText : Boolean = ParserGetBoolValueByKeyByHandle(pWindowDesigner, 'ExternalText');
      [*] = ;
      [*] = ;const cEventState = 'EventWindowDesigner';
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
      [*] = ;
      [*] = ;const cWindowBaseTypeCount = 3;
      [*] = ;const cElementTypesCount = 21;
      [*] = ;const cPropertiesWidth = 1380;
      [*] = ;const cPropertyRows = 2;
      [*] = ;const cPropertiesXPadding = 10;
      [*] = ;const cPropertiesYPadding = 16;
      [*] = ;const cIntInputWidth = 110;
      [*] = ;const cIntInputSlotWidth = 160;
      [*] = ;const cStrInputWidth = 200;
      [*] = ;const cStrInputSlotWidth = 190;
      [*] = ;const cListBoxWidth = 190;
      [*] = ;const cCheckBoxWidth = 190;
      [*] = ;
      [*] = ;var fontHandle, fontHandle2, fontHandle3, fontHandleInput : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_small,'',fontHandle);
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'',fontHandle2);
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_large,'',fontHandle3);
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Input',gc_gui_fontsize_default,'',fontHandleInput);
      [*] = ;
      [*] = ;var buttonWidth : Integer = GetGUITextureWidth('common.btn.normal');
      [*] = ;var buttonHeight : Integer = GetGUITextureHeight('common.btn.normal');
      [*] = ;
      [*] = ;var viewWidth : Integer = GetViewerWidth();
      [*] = ;var viewHeight : Integer = GetViewerHeight();
      [*] = ;
      [*] = ;var elmHandle : Integer;
      [*] = ;var rect : TRectangle;
      [*] = ;
      [*] = ;var index : Integer = 0;
      [*] = ;
      [*] = ;function ParserGetBaseWindow() : Integer;
      [*] = ;begin
      [*] = ;   Result := ParserSelectByHandleByKey(pWindowDesigner, 'BaseWindow');
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
      [*] = ;function GetPropertyIndexByValue(propertyName : String; value : String) : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   var pProperty : Integer = GetPropertyByName(propertyName);
      [*] = ;   var pOptions : Integer = ParserSelectByHandleByKey(pProperty, 'Options');
      [*] = ;   var i, pOption : Integer;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pOptions)-1 do
      [*] = ;   begin
      [*] = ;      pOption := ParserSelectByHandleByIndex(pOptions, i);
      [*] = ;      if ParserGetValueByKeyByHandle(pOption, 'Value') = value then
      [*] = ;      begin
      [*] = ;         Result := i;
      [*] = ;         break;
      [*] = ;      end;
      [*] = ;   end;
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
      [*] = ;function IsBase(elmType : String) : Boolean;
      [*] = ;begin
      [*] = ;   Result := (elmType = 'Large Window') or (elmType = 'Small Window') or (elmType = 'Dummy Window');
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CreateHeader(text : String; parent : Integer);
      [*] = ;begin
      [*] = ;   _gui_CreateTextStrip('header', parent, text, 'halParentMiddle', 'valParentTop', 0, -18);
      [*] = ;end;
      [*] = ;
      [*] = ;function CreateButton(name, hint : String; parent, xPos, yPos, tag : Integer) : Integer;
      [*] = ;begin
      [*] = ;   var elmHandle : Integer = _gui_CreateButton(name, parent, '', 'common.btn', 'halParentLeft', 'valParentTop', xPos, yPos, 0, 0, cEventState, hint, tag);
      [*] = ;   _gui_CreateText('text', elmHandle, name, 'halParentLeft', 'valParentTop', 0, 0, buttonWidth, buttonHeight, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;   index := index + 1;
      [*] = ;   Result := elmHandle;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CheckRowLimit(const elmSize : Integer; var xPos, yPos : Integer);
      [*] = ;begin
      [*] = ;   if (xPos + elmSize > cPropertiesWidth) then
      [*] = ;   begin
      [*] = ;      xPos := cPropertiesXPadding;
      [*] = ;      yPos := yPos + buttonHeight + 10;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CreateIntInput(name : String; parent, value : Integer; var xPos, yPos : Integer);
      [*] = ;begin
      [*] = ;   CheckRowLimit(cIntInputSlotWidth, xPos, yPos);
      [*] = ;   
      [*] = ;   var valueText : String = IntToStr(value);
      [*] = ;   
      [*] = ;   _sys_FillRect(rect,xPos+20,yPos+20,cIntInputWidth,0);
      [*] = ;   var elmHandle : Integer = _gui_CreateInputControl_VVK(name, parent, valueText, gc_gui_align_parent_lt, true, rect, 4, cEventState, '');
      [*] = ;   elmHandle := GetGUIElementParentByIndex(elmHandle);
      [*] = ;   _gui_CreateText('header', elmHandle, name, 'halParentLeft', 'valParentTop', 0, -18, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;   _gui_CreateButton('arrowSliderLeft', elmHandle, '', 'common.scroller.left', 'halParentLeft', 'valParentTop', -6, -4, 0, 0, cEventState, '', 0);
      [*] = ;   _gui_CreateButton('arrowSliderRight', elmHandle, '', 'common.scroller.right', 'halParentLeft', 'valParentTop', -6+cIntInputWidth-31, -4, 0, 0, cEventState, '', 0);
      [*] = ;   _gui_CreateButton('arrowSliderLeftTen', elmHandle, '', 'common.scroller.left', 'halParentLeft', 'valParentTop', -30, -4, 0, 0, cEventState, '', 0);
      [*] = ;   _gui_CreateButton('arrowSliderRightTen', elmHandle, '', 'common.scroller.right', 'halParentLeft', 'valParentTop', -6+cIntInputWidth-7, -4, 0, 0, cEventState, '', 0);
      [*] = ;   xPos := xPos + cIntInputSlotWidth;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CreateStringInput(name : String; parent : Integer; fieldText : String; var xPos, yPos : Integer);
      [*] = ;begin
      [*] = ;   CheckRowLimit(cStrInputSlotWidth, xPos, yPos);
      [*] = ;   
      [*] = ;   _sys_FillRect(rect,xPos,yPos+20,cStrInputWidth,0);
      [*] = ;   var elmHandle : Integer = _gui_CreateInputControl_VVK(name, parent, fieldText, gc_gui_align_parent_lt, false, rect, 1000, cEventState, '');
      [*] = ;   elmHandle := GetGUIElementParentByIndex(elmHandle);
      [*] = ;   _gui_CreateText('header', elmHandle, name, 'halParentLeft', 'valParentTop', 0, -18, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;   //_gui_CreateButton('Accept', elmHandle, '', 'mainpanel.btn.accept', 'halParentLeft', 'valParentTop', GetGUIElementWidth(elmHandle), 0, 0, 0, cEventState, 'menu|47', 0);
      [*] = ;   xPos := xPos + cStrInputSlotWidth;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CreatePropertyListBox(propertyName : String; parent : Integer; fieldText : String; var xPos, yPos : Integer);
      [*] = ;begin
      [*] = ;   CheckRowLimit(cListBoxWidth, xPos, yPos);
      [*] = ;   
      [*] = ;   var pProperty : Integer = GetPropertyByName(propertyName);
      [*] = ;   var pOptions : Integer = ParserSelectByHandleByKey(pProperty, 'Options');
      [*] = ;   var itemsCount : Integer = ParserGetCountByHandle(pOptions);
      [*] = ;   elmHandle := _gui_CreateListBoxMiddleExt(propertyName, parent, itemsCount, 0, xPos+20, yPos+20, cListBoxWidth, cEventState, 'halParentLeft');
      [*] = ;   _gui_CreateText('header', elmHandle, propertyName, 'halParentLeft', 'valParentTop', 0, -18, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;   xPos := xPos + cListBoxWidth;
      [*] = ;   var i : Integer;
      [*] = ;   for i := 0 to itemsCount-1 do 
      [*] = ;      GUIListBoxAddItem(elmHandle, ParserGetValueByKeyByHandle(ParserSelectByHandleByIndex(pOptions, i), 'Name'), i);
      [*] = ;      
      [*] = ;   SetGUIListBoxItemIndexSilent(elmHandle, GetPropertyIndexByValue(propertyName, fieldText));
      [*] = ;end;
      [*] = ;
      [*] = ;procedure CreatePropertyCheckBox(propertyName : String; parent : Integer; bChecked : Boolean; var xPos, yPos : Integer);
      [*] = ;begin
      [*] = ;   CheckRowLimit(cCheckBoxWidth, xPos, yPos);
      [*] = ;   
      [*] = ;   var elmCheckBox : Integer = _gui_CreateCheckBox(propertyName, parent, bChecked, propertyName, 'halParentLeft', 'valParentTop', xPos, yPos+25, cEventState, '', 0);
      [*] = ;   xPos := xPos + cCheckBoxWidth;
      [*] = ;end;
      [*] = ;
      [*] = ;function IsBaseType(elmType : String) : Boolean;
      [*] = ;begin
      [*] = ;   Result := (elmType = 'Large Window') or (elmType = 'Small Window') or (elmType = 'Dummy Window');
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;var elmWindowDesigner : Integer = _gui_GetOrCreateElement('Window Designer', _gui_GetLayerI(), 'halLeft', 'valTop', 0, 0, viewWidth, viewHeight, 0);
      [*] = ;var windowBaseElmHandle : Integer = _gui_RootWindowGetBase(activeElmHandle);
      [*] = ;
      [*] = ;// Element Buttons
      [*] = ;var xPos : Integer = 0;
      [*] = ;var yPos : Integer = 20;
      [*] = ;var elmElementTypes : Integer = _gui_CreateFrameBorderExt('Element Types', elmWindowDesigner, 'halParentLeft', 'valParentTop', xPos, yPos, buttonWidth+20, viewHeight, True);
      [*] = ;CreateHeader('Element Types', elmElementTypes);
      [*] = ;
      [*] = ;xPos := 10;
      [*] = ;yPos := 10;
      [*] = ;
      [*] = ;{if activeElmHandle <> 0 then
      [*] = ;begin
      [*] = ;   var elmCheckBoxExternalPaste : Integer = _gui_CreateCheckBox('External Text Paste', elmElementTypes, bExternalText, 'External Text Paste', 'halParentLeft', 'valParentTop', xPos+20, yPos+16, cEventState, '', cCheckBoxExternalPaste);
      [*] = ;   yPos := yPos + buttonHeight;
      [*] = ;end;}
      [*] = ;
      [*] = ;if ParserSelectByHandleByKey(pWindowDesigner, 'BaseWindow') <> 0 then
      [*] = ;begin
      [*] = ;   var elmCheckBoxAddNew : Integer = _gui_CreateCheckBox('Add New', elmElementTypes, bAddNew, 'Add New', 'halParentLeft', 'valParentTop', xPos+20, yPos+16, cEventState, 'If disabled, will switch the type of the currently active element. Othwerwise, adds a new element as a child of the currently active element. Base element will never ber added as a new child.', cCheckBoxAddNew);
      [*] = ;   yPos := yPos + buttonHeight;
      [*] = ;end;
      [*] = ;
      [*] = ;if (activeElmHandle <> 0) and (not IsBaseType(ParserGetValueByKeyByHandle(pActiveElement, 'ElementType'))) then
      [*] = ;   CreateButton('Duplicate', '', elmElementTypes, xPos, yPos + buttonHeight * index, cDuplicateTag);
      [*] = ;
      [*] = ;if (ParserSelectByHandleByKey(pWindowDesigner, 'BaseWindow') = 0) or (windowBaseElmHandle = activeElmHandle) then
      [*] = ;begin
      [*] = ;   CreateButton('Large Window', '', elmElementTypes, xPos, yPos + buttonHeight * index, cElementTypeTagBase+index);
      [*] = ;   CreateButton('Small Window', '', elmElementTypes, xPos, yPos + buttonHeight * index, cElementTypeTagBase+index);
      [*] = ;   CreateButton('Dummy Window', '', elmElementTypes, xPos, yPos + buttonHeight * index, cElementTypeTagBase+index);
      [*] = ;end;
      [*] = ;
      [*] = ;if (ParserSelectByHandleByKey(pWindowDesigner, 'BaseWindow') <> 0) then
      [*] = ;begin
      [*] = ;   CreateButton('Header', '', elmElementTypes, xPos, yPos + buttonHeight * index, cElementTypeTagBase+index+cWindowBaseTypeCount);
      [*] = ;   CreateButton('Image', '', elmElementTypes, xPos, yPos + buttonHeight * index, cElementTypeTagBase+index+cWindowBaseTypeCount);
      [*] = ;   CreateButton('Tiled Image', '', elmElementTypes, xPos, yPos + buttonHeight * index, cElementTypeTagBase+index+cWindowBaseTypeCount);
      [*] = ;   CreateButton('Frame', '', elmElementTypes, xPos, yPos + buttonHeight * index, cElementTypeTagBase+index+cWindowBaseTypeCount);
      [*] = ;   
      [*] = ;   CreateButton('Text', '', elmElementTypes, xPos, yPos + buttonHeight * index, cElementTypeTagBase+index+cWindowBaseTypeCount);
      [*] = ;   CreateButton('Input', '', elmElementTypes, xPos, yPos + buttonHeight * index, cElementTypeTagBase+index+cWindowBaseTypeCount);
      [*] = ;   CreateButton('Button', '', elmElementTypes, xPos, yPos + buttonHeight * index, cElementTypeTagBase+index+cWindowBaseTypeCount);
      [*] = ;   CreateButton('Checkbox', '', elmElementTypes, xPos, yPos + buttonHeight * index, cElementTypeTagBase+index+cWindowBaseTypeCount);
      [*] = ;   CreateButton('Listbox', '', elmElementTypes, xPos, yPos + buttonHeight * index, cElementTypeTagBase+index+cWindowBaseTypeCount);
      [*] = ;   
      [*] = ;   CreateButton('Slider', '', elmElementTypes, xPos, yPos + buttonHeight * index, cElementTypeTagBase+index+cWindowBaseTypeCount);
      [*] = ;   CreateButton('Dummy', '', elmElementTypes, xPos, yPos + buttonHeight * index, cElementTypeTagBase+index+cWindowBaseTypeCount);
      [*] = ;   //CreateButton('Herb', '', elmElementTypes, xPos, yPos + buttonHeight * index, cElementTypeTagBase+index+cWindowBaseTypeCount);
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;// Element Properties
      [*] = ;if activeElmHandle <> 0 then
      [*] = ;begin
      [*] = ;   var activeElmType : String = ParserGetValueByKeyByHandle(pActiveElement, 'ElementType');
      [*] = ;   
      [*] = ;   xPos := 0;
      [*] = ;   yPos := 20;
      [*] = ;   var elmProperties : Integer = _gui_CreateFrameBorderExt('Properties', elmWindowDesigner, 'halMiddle', 'valParentTop', xPos, yPos, cPropertiesWidth, buttonHeight*cPropertyRows+40, True);
      [*] = ;   _gui_CreateLargeTextStrip('header', elmProperties, ParserGetValueByKeyByHandle(pActiveElement, 'Name'), 'halParentMiddle', 'valParentTop', 0, -18);
      [*] = ;   //CreateHeader('Properties', elmProperties);
      [*] = ;   
      [*] = ;   xPos := cPropertiesXPadding;
      [*] = ;   yPos := cPropertiesYPadding;
      [*] = ;
      [*] = ;   var i, j, k, pChild, pElementType, pElmProperties, pElmProperty, pProperty : Integer;
      [*] = ;   var propertyName, propertyType, value : String;
      [*] = ;   var pChildren : Integer = ParserSelectByHandleByKey(pActiveElement, 'Children');
      [*] = ;   var pActiveChild : Integer = ParserSelectByHandleByIndex(pChildren, activeChildIndex);
      [*] = ;   var childCount : Integer = ParserGetCountByHandle(pChildren);
      [*] = ;
      [*] = ;   if bMultiEditChildren and (childCount > 1) then
      [*] = ;   begin
      [*] = ;      var pProperties : Integer = ParserSelectByHandleByKey(pData, 'Properties');
      [*] = ;      for i := 0 to ParserGetCountByHandle(pProperties)-1 do
      [*] = ;      begin
      [*] = ;         pProperty := ParserSelectByHandleByIndex(pProperties, i);
      [*] = ;         propertyType := ParserGetValueByKeyByHandle(pProperty, 'Type');
      [*] = ;         //if propertyType <> 'StringInput' then
      [*] = ;         begin
      [*] = ;            propertyName := ParserGetValueByKeyByHandle(pProperty, 'Name');
      [*] = ;            pElementType := ParserGetElementTypeByName(ParserGetValueByKeyByHandle(pActiveChild, 'ElementType'));
      [*] = ;            value := ParserGetValueByKeyByHandle(pActiveChild, propertyName);
      [*] = ;            
      [*] = ;            for [MAIN]j := 0 to childCount-1 do
      [*] = ;            begin
      [*] = ;               pChild := ParserSelectByHandleByIndex(pChildren, j);
      [*] = ;               pElementType := ParserGetElementTypeByName(ParserGetValueByKeyByHandle(pChild, 'ElementType'));
      [*] = ;               pElmProperties := ParserSelectByHandleByKey(pElementType, 'Properties');
      [*] = ;               for k := 0 to ParserGetCountByHandle(pElmProperties)-1 do
      [*] = ;               begin
      [*] = ;                  pElmProperty := ParserSelectByHandleByIndex(pElmProperties, k);
      [*] = ;                  if (ParserGetValueByKeyByHandle(pElmProperty, 'Name') = propertyName) and ParserGetBoolValueByKeyByHandle(pElmProperty, 'Edit') then
      [*] = ;                  begin
      [*] = ;                     case propertyType of
      [*] = ;                        'StringInput' : CreateStringInput(propertyName, elmProperties, value, xPos, yPos);
      [*] = ;                        'IntInput' : CreateIntInput(propertyName, elmProperties, StrToInt(value), xPos, yPos);
      [*] = ;                        'Listbox' : CreatePropertyListBox(propertyName, elmProperties, value, xPos, yPos);
      [*] = ;                        'Checkbox' : CreatePropertyCheckBox(propertyName, elmProperties, StrToBool(value), xPos, yPos);
      [*] = ;                     end;
      [*] = ;                     break(Main);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      pElementType := ParserGetElementTypeByName(activeElmType);
      [*] = ;      pElmProperties := ParserSelectByHandleByKey(pElementType, 'Properties');
      [*] = ;      for i := 0 to ParserGetCountByHandle(pElmProperties)-1 do
      [*] = ;      begin
      [*] = ;         pElmProperty := ParserSelectByHandleByIndex(pElmProperties, i);
      [*] = ;         if ParserGetBoolValueByKeyByHandle(pElmProperty, 'Edit') then
      [*] = ;         begin
      [*] = ;            propertyName := ParserGetValueByKeyByHandle(pElmProperty, 'Name');
      [*] = ;            pProperty := GetPropertyByName(propertyName);
      [*] = ;            case ParserGetValueByKeyByHandle(pProperty, 'Type') of
      [*] = ;               'StringInput' : CreateStringInput(propertyName, elmProperties, ParserGetValueByKeyByHandle(pActiveElement, propertyName), xPos, yPos);
      [*] = ;               'IntInput' : CreateIntInput(propertyName, elmProperties, ParserGetIntValueByKeyByHandle(pActiveElement, propertyName), xPos, yPos);
      [*] = ;               'Listbox' : CreatePropertyListBox(propertyName, elmProperties, ParserGetValueByKeyByHandle(pActiveElement, propertyName), xPos, yPos);
      [*] = ;               'Checkbox' : CreatePropertyCheckBox(propertyName, elmProperties, ParserGetBoolValueByKeyByHandle(pActiveElement, propertyName), xPos, yPos);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   
      [*] = ;   elmHandle := _gui_CreateImage('', elmProperties, 'mainpanel.btnplace.with.frame', 'halParentRightWidth', 'valParentBottomHeight', 20, 20, 0, 0, 0);
      [*] = ;   _gui_CreateButton('btnApply', elmHandle, '', 'mainpanel.btn.accept', 'halParentLeft', 'valParentTop', 39, 0, 0, 0, cEventState, 'Apply properties', cApplyPropertiesTag);
      [*] = ;   //elmHandle := _gui_CreateButton('Apply Properties', elmProperties, '', 'common.btn', 'halParentRightWidth', 'valParentBottomHeight', 0, 0, 0, 0, cEventState, '', cApplyPropertiesTag);
      [*] = ;   //_gui_CreateText('text', elmHandle, 'Apply', 'halParentLeft', 'valParentTop', 0, 0, buttonWidth, buttonHeight, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;   //CheckRowLimit(buttonWidth, xPos, yPos);
      [*] = ;   //CreateButton('Apply', '', elmProperties, xPos, yPos, cApplyPropertiesTag);
      [*] = ;end;
      [*] = ;
      [*] = ;
      [*] = ;// Window Data
      [*] = ;xPos := 0;
      [*] = ;yPos := 20;
      [*] = ;var elmHierarchy : Integer = _gui_CreateFrameBorderExt('Window', elmWindowDesigner, 'halParentRightWidth', 'valParentTop', xPos, yPos, buttonWidth+20, viewHeight, True);
      [*] = ;CreateHeader('Window', elmHierarchy);
      [*] = ;      
      [*] = ;elmHandle := _gui_CreateButton('exit', elmHierarchy, '', 'common.btn', 'halParentLeft', 'valParentBottomHeight', xPos, -buttonHeight, 0, 0, cEventState, '', cBtnExitToMainMenu);
      [*] = ;_gui_CreateText('text', elmHandle, 'gui|135', 'halParentLeft', 'valParentTop', 0, 0, buttonWidth, buttonHeight, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;   
      [*] = ;xPos := 10;
      [*] = ;yPos := 20;
      [*] = ;elmHandle := CreateButton('Load', '', elmHierarchy, xPos, yPos, cBtnLoadTag);
      [*] = ;SetGUIElementEnabled(elmHandle, ParserGetCountByHandle(gWindows.handle) > 0);
      [*] = ;      
      [*] = ;if activeElmHandle <> 0 then
      [*] = ;begin
      [*] = ;   yPos := yPos + buttonHeight;
      [*] = ;   elmHandle := CreateButton('Save', '', elmHierarchy, xPos, yPos, cSaveTag);
      [*] = ;   SetGUIElementEnabled(elmHandle, ParserGetValueByKeyByHandle(ParserGetBaseWindow, 'Name') <> '');
      [*] = ;      
      [*] = ;   yPos := yPos + buttonHeight + 20;
      [*] = ;   _gui_CreateTextStrip('header', elmHierarchy, 'Hierarchy', 'halParentMiddle', 'valParentTop', 0, yPos);
      [*] = ;   
      [*] = ;   yPos := yPos + buttonHeight;
      [*] = ;   CreateButton('Show/Hide Active', '', elmHierarchy, xPos, yPos, cElementShowActiveTag);
      [*] = ;      
      [*] = ;   yPos := yPos + buttonHeight;
      [*] = ;   CreateButton('Delete Active', '', elmHierarchy, xPos, yPos, cElementDeleteActiveTag);
      [*] = ;      
      [*] = ;   if (windowBaseElmHandle <> activeElmHandle) then
      [*] = ;   begin
      [*] = ;      //yPos := yPos + buttonHeight;
      [*] = ;      //_gui_CreateTextStrip('header', elmHierarchy, ParserGetValueByKeyByHandle(ParserGetParent(ParserGetParent(pActiveElement)), 'Name'), 'halParentMiddle', 'valParentTop', 0, yPos);
      [*] = ;      yPos := yPos + buttonHeight;
      [*] = ;      CreateButton('Select Parent', ParserGetValueByKeyByHandle(ParserGetParent(ParserGetParent(pActiveElement)), 'Name'), elmHierarchy, xPos, yPos, cElementParentTag);
      [*] = ;   end;
      [*] = ;      
      [*] = ;   var pChildren : Integer = ParserSelectByHandleByKey(pActiveElement, 'Children');
      [*] = ;   var childCount : Integer = ParserGetCountByHandle(pChildren);
      [*] = ;   if (childCount > 0) then
      [*] = ;   begin
      [*] = ;      //yPos := yPos + buttonHeight + 20;
      [*] = ;      //_gui_CreateTextStrip('header', elmHierarchy, 'Children', 'halParentMiddle', 'valParentTop', 0, yPos);
      [*] = ;      yPos := yPos + buttonHeight+20;
      [*] = ;      var pChild : Integer = ParserSelectByHandleByIndex(pChildren, activeChildIndex);
      [*] = ;      var elmSlider : Integer = _gui_CreateIntSlider('Children', elmHierarchy, 'halParentLeft', 'valParentTop', xPos, yPos+10, 228, cEventState, '', 49, 3, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;      _gui_CreateText('header', elmSlider, 'Children', 'halParentLeft', 'valParentTop', 0, -18, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      _gui_SetSliderIntValue(elmSlider, activeChildIndex, childCount-1, ParserGetValueByKeyByHandle(pChild, 'Name'), true);
      [*] = ;      xPos := 10;
      [*] = ;      yPos := yPos + buttonHeight;
      [*] = ;      CreateButton('Select Child', '', elmHierarchy, xPos, yPos, cElementChildTag);
      [*] = ;   end;
      [*] = ;   
      [*] = ;   if (windowBaseElmHandle <> activeElmHandle) then
      [*] = ;   begin
      [*] = ;      var parentChildCount : Integer = ParserGetCountByHandle(ParserGetParent(pActiveElement));
      [*] = ;      if (parentChildCount > 1) then
      [*] = ;      begin
      [*] = ;         yPos := yPos + buttonHeight;
      [*] = ;         CreateButton('Select Next', '', elmHierarchy, xPos, yPos, cElementNextChildTag);
      [*] = ;         yPos := yPos + buttonHeight;
      [*] = ;         CreateButton('Select Previous', '', elmHierarchy, xPos, yPos, cElementPreviousChildTag);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;      
      [*] = ;   if (childCount > 1) then
      [*] = ;   begin
      [*] = ;      yPos := yPos + 60;
      [*] = ;      _gui_CreateCheckBox('Multi Edit Children', elmHierarchy, bMultiEditChildren, 'Mass-Edit Children', 'halParentLeft', 'valParentTop', xPos+20, yPos, cEventState, '', cMultiEditChildrenTag);
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

