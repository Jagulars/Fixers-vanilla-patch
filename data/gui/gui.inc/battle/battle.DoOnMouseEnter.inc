section.begin
   Name = battle.DoOnMouseEnter
   Code : struct.begin
      [*] = ;var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;//var StringTag : String =  GetGUIElementStringTag(elmHandle);
      [*] = ;//var HintTag : String = GetGUIElementHint(elmHandle);
      [*] = ;//var posX, posY : Integer;
      [*] = ;//var width, height : Integer;
      [*] = ;//var text : String;
      [*] = ;//var fontHandleT, fontHandleH2, fontHandleH1, fonthandleN: String;
      [*] = ;//_gui_GetFont(gc_gui_fontsection_tactics,'Text',gc_gui_fontsize_default,'',fontHandleT);   // Simple text
      [*] = ;//_gui_GetFont(gc_gui_fontsection_tactics,'Text',gc_gui_fontsize_large,'',fontHandleH2); // Header lvl 2
      [*] = ;//_gui_GetFont(gc_gui_fontsection_tactics,'Text',gc_gui_fontsize_largest,'',fontHandleH1); // Header lvl 1
      [*] = ;//_gui_GetFont(gc_gui_fontsection_tactics,'Numbers',gc_gui_fontsize_default,'',fontHandleN); // Numbers, costs
      [*] = ;
      [*] = ;if (GetGUIListBoxItemsCount(elmHandle)>0) then
      [*] = ;begin
      [*] = ;   var iconElmHandle : Integer = GetGUIElementIndexByNameParent('icon', elmHandle);
      [*] = ;   if (iconElmHandle<>0) then
      [*] = ;      SetGUIElementMaterial(iconElmHandle, 'gamepanel03.combobox.icon.hover');
      [*] = ;end;
      [*] = ;
      [*] = ;{if (GetGUIElementVisible(_gui_GetWindow('map_heroupgrade'))) and (StrExists(HintTag, 'HintHeroSkillCallback')) then
      [*] = ;begin
      [*] = ;   // Same code also appears in map.DoOnMouseEnter, cause we can upgrade hero in strategic map too
      [*] = ;   var elmParentHandle : Integer = _gui_GetWindow('map_heroupgrade');
      [*] = ;   var plHandle : Integer = GetPlayerHandleInterfaceIO;
      [*] = ;   PlayerExecuteStateByHandle(plHandle, 'GetHeroHandle');
      [*] = ;   var heroHandle : Integer = IntRegister0;
      [*] = ;   var mapHeroHandle : Integer = GetGameObjectHandleByUniqueId(GetGameObjectIntValueIndByHandle(heroHandle, gc_stack_unit_iHeroUID));
      [*] = ;   var str : String;
      [*] = ;   _sa_Get_D(HintTag,2,$23,str);
      [*] = ;   var skillID : Integer = _sa_GetAsInt(str,0);
      [*] = ;   IntRegister0 := skillID;
      [*] = ;   GameObjectExecuteStateByHandle(mapHeroHandle, 'GetSkillLevel');
      [*] = ;   var skillLevel : Integer = IntRegister1;
      [*] = ;   var textHeader : String = GetLocaleTableListItemByID('skill', IntToStr(skillID)) + ' ' + IntToStr(skillLevel+1);
      [*] = ;   var text : String = GetLocaleTableListItemByID('skill', IntToStr(skillID)+'.description');
      [*] = ;
      [*] = ;   GUIInvalidateParentPositions(elmParentHandle);
      [*] = ;   var pX, pY : Integer;
      [*] = ;   GetGUIElementAlignPosition(elmParentHandle, pX, pY);
      [*] = ;   var elmCommonWindow : Integer = GetGUIElementIndexByNameParent('common_window', elmParentHandle);
      [*] = ;   if (elmCommonWindow<>0) then
      [*] = ;   RemoveGUIElement(elmCommonWindow);
      [*] = ;   elmCommonWindow := _gui_CreateCommonWindow(textHeader, text, 'heroupgrade_description', 'halParentLeft', 'valParentTop', px-15, GetGUIElementHeight(elmParentHandle)+pY+12, 375, 0, false, false, false, 4, false);
      [*] = ;   AttachGUIElementToElement(elmCommonWindow, elmParentHandle);
      [*] = ;   SetGUIElementAlign(elmCommonWindow, 'halParentLeft', 'valParentBottom');
      [*] = ;   //SetGUIElementPositionY(elmCommonWindow, 400);
      [*] = ;   SetGUIElementPosition(elmCommonWindow, -12, 10);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;if (GetGUIElementVisible(_gui_GetWindow('heroupgradeclass'))) and (StrExists(StringTag, 'Class')) then
      [*] = ;begin
      [*] = ;   // Same code also appears in map.DoOnMouseEnter, cause we can upgrade hero in strategic map too
      [*] = ;   var elmParentHandle : Integer = _gui_GetWindow('heroupgradeclass');
      [*] = ;   RemoveGUIElement(GetGUIElementIndexByNameParent('class_name', elmParentHandle));
      [*] = ;   RemoveGUIElement(GetGUIElementIndexByNameParent('class_description', elmParentHandle));
      [*] = ;   var plHandle : Integer = GetPlayerHandleInterfaceIO;
      [*] = ;   PlayerExecuteStateByHandle(plHandle, 'GetHeroHandle');
      [*] = ;   var heroHandle : Integer = IntRegister0;
      [*] = ;   var mapHeroHandle : Integer = GetGameObjectHandleByUniqueId(GetGameObjectIntValueIndByHandle(heroHandle, gc_stack_unit_iHeroUID));
      [*] = ;   var newClassID : Integer = StrToInt(StrReplace(StringTag, 'Class.', ''));
      [*] = ;   var text : String = GetLocaleTableListItemByID('hero_class', IntToStr(newClassID));
      [*] = ;   var elmTextHandle : Integer = _gui_CreateText('class_name', elmParentHandle, text, 'halParentLeft', 'valParentTop', 167, 275, 168, 32, 'halMiddle', 'valMiddle', fontHandleH2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;   text := GetLocaleTableListItemByID('hero_class', IntToStr(newClassID)+'.description');
      [*] = ;   var textWrapped : String = GetGUIWrappedTextFormatByFont(fontHandleT, text, 435);
      [*] = ;   var width, height : Integer;
      [*] = ;   GetGUIElementFontTextFormatRect(fontHandleT, textWrapped, width, height);
      [*] = ;   elmTextHandle := _gui_CreateText('class_description', elmParentHandle, textWrapped, 'halParentLeft', 'valParentTop', 24, 325, width, height, 'halLeft', 'valTop', fontHandleT, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   exit;
      [*] = ;end;}
   struct.end
section.end

