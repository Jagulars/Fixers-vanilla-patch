section.begin
   Name = battle.DoOnMouseLeave
   Code : struct.begin
      [*] = ;var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;//var StringTag : String =  GetGUIElementStringTag(elmHandle);
      [*] = ;//var elmParentHandle : Integer;
      [*] = ;
      [*] = ;if (GetGUIListBoxItemsCount(elmHandle)>0) then
      [*] = ;begin
      [*] = ;   var iconElmHandle : Integer = GetGUIElementIndexByNameParent('icon', elmHandle);
      [*] = ;   if (iconElmHandle<>0) then
      [*] = ;     SetGUIElementMaterial(iconElmHandle, 'gamepanel03.combobox.icon.normal');
      [*] = ;end;
      [*] = ;
      [*] = ;{if (GetGUIElementVisible(_gui_GetWindow('heroupgradeclass'))) and (StrExists(StringTag, 'Class')) then
      [*] = ;begin
      [*] = ;   // Same code also appears in map.DoOnMouseEnter, cause we can upgrade hero in strategic map too
      [*] = ;   elmParentHandle := _gui_GetWindow('heroupgradeclass');
      [*] = ;   RemoveGUIElement(GetGUIElementIndexByNameParent('class_strip', elmParentHandle));
      [*] = ;   RemoveGUIElement(GetGUIElementIndexByNameParent('class_name', elmParentHandle));
      [*] = ;   RemoveGUIElement(GetGUIElementIndexByNameParent('class_description', elmParentHandle));
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;if (GetGUIElementVisible(_gui_GetWindow('map_heroupgrade'))) and (StrExists(StringTag, 'Skill')) then
      [*] = ;begin
      [*] = ;   _gui_RootWindowRemoveWithFade(_gui_GetWindow('heroupgrade_description'),gc_gui_FadeTime0_2);
      [*] = ;   exit;
      [*] = ;end;}
   struct.end
section.end

