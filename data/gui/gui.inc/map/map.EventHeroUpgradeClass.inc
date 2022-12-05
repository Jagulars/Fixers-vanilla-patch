section.begin
   Name = map.EventHeroUpgradeClass
   Code : struct.begin
      [*] = ;var sPress  : String = GetValueByName('Press');
      [*] = ;
      [*] = ;if sPress <> 'c' then
      [*] = ;   exit;
      [*] = ;
      [*] = ;var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;
      [*] = ;if GetGUIElementNameByIndex(elmHandle) = 'btn_hero_window' then
      [*] = ;begin
      [*] = ;   gIntRegister_GUICurHeroMode := gc_HeroPanelBothPanels;
      [*] = ;   gIntRegister_GUIActiveHeroUID1 := tag;
      [*] = ;   GUIExecuteState('map.CreateHeroWindow');
      [*] = ;end
      [*] = ;else
      [*] = ;if (sPress='c') and (tag = 1) then
      [*] = ;begin
      [*] = ;   // proceed with new class
      [*] = ;   var str : String;
      [*] = ;   _sa_Get_D(GetGUIElementHint(elmHandle),2,$23,str);
      [*] = ;   var heroHandle : Integer = GetGameObjectHandleByUniqueId(_sa_GetAsInt(str,1));
      [*] = ;   var newClassID : Integer = _sa_GetAsInt(str,0);
      [*] = ;   var classInd2 : Integer = (newClassID - 1) mod 4 + 1;
      [*] = ;   SetGameObjectIntValueIndByHandle(heroHandle, gc_map_GOStack_MapUnit_iClassInd2, classInd2);
      [*] = ;   _log_gui('New class should be ' + GetLocaleTableListItemByID('hero_class', IntToStr(newClassID)));
      [*] = ;
      [*] = ;   _gui_RootWindowRemoveWithFade(_gui_GetWindow('heroupgradeclass'),0);
      [*] = ;   IntRegister0 := heroHandle;
      [*] = ;   GUIExecuteState('map.CreateHeroUpgradeWindow');
      [*] = ;end;
   struct.end
section.end

