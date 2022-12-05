section.begin
   Name = map.ChooseHeroUpgrade
   Code : struct.begin
      [*] = ;var sPress  : String = GetValueByName('Press');
      [*] = ;
      [*] = ;if sPress <> 'c' then
      [*] = ;   exit;
      [*] = ;
      [*] = ;var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var initMachine : Integer = GetMapInitMachineHandle();
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;
      [*] = ;if GetGUIElementNameByIndex(elmHandle) = 'btn_hero_window' then
      [*] = ;begin
      [*] = ;   gIntRegister_GUICurHeroMode := gc_HeroPanelBothPanels;
      [*] = ;   gIntRegister_GUIActiveHeroUID1 := tag;
      [*] = ;   GUIExecuteState('map.CreateHeroWindow');
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   var heroHandle : Integer = StrToInt(GetGUIElementStringTag(elmHandle));
      [*] = ;   var skillID : Integer = tag - gc_gui_battle_btnSkillsBaseTag;
      [*] = ;
      [*] = ;   _gui_RootWindowRemoveWithFade(_gui_GetWindow('map_heroupgrade'),0);
      [*] = ;
      [*] = ;   IntRegister0 := skillID;
      [*] = ;   BoolRegister0 := false;
      [*] = ;   GameObjectExecuteStateByHandle(heroHandle, 'AddSkill');
      [*] = ;   GameObjectExecuteStateByHandle(heroHandle, 'IsLevelUp');
      [*] = ;   if BoolRegister0 then
      [*] = ;   begin
      [*] = ;      var oldLevel : Integer = GetGameObjectIntValueIndByHandle(heroHandle, gc_map_GOStack_MapUnit_iLevel);
      [*] = ;
      [*] = ;      IntRegister0 := heroHandle;
      [*] = ;      if (oldLevel+1=10) then
      [*] = ;         GUIExecuteState('map.CreateHeroUpgradeClass')
      [*] = ;      else
      [*] = ;         GUIExecuteState('map.CreateHeroUpgradeWindow');
      [*] = ;   end
      [*] = ;   else
      [*] = ;      GUIExecuteState('CheckUnitUpgrade');
      [*] = ;end;
   struct.end
section.end

