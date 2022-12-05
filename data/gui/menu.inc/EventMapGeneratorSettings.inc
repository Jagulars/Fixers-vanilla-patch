section.begin
   Name = EventMapGeneratorSettings
   UsedFileName =
   Code : struct.begin
      [*] = ;procedure MakeRandom();
      [*] = ;begin
      [*] = ;   gMapSettingsTmp.typ := Round(RandomExt()*1);
      [*] = ;   gMapSettingsTmp.wastelands := (RandomExt());
      [*] = ;   gMapSettingsTmp.population := (RandomExt());
      [*] = ;   gMapSettingsTmp.isles := (RandomExt());
      [*] = ;   gMapSettingsTmp.forest := (RandomExt());
      [*] = ;   gMapSettingsTmp.neutrals := (RandomExt());
      [*] = ;   gMapSettingsTmp.dissolve := (RandomExt());
      [*] = ;   gMapSettingsTmp.hill := (RandomExt());
      [*] = ;   gMapSettingsTmp.resource := (RandomExt());
      [*] = ;   gMapSettingsTmp.water := (RandomExt());
      [*] = ;   gMapSettingsTmp.swamp := (RandomExt());
      [*] = ;   gMapSettingsTmp.site := (RandomExt());
      [*] = ;end;
      [*] = ;
      [*] = ;var sPress  : String = GetValueByName('Press');
      [*] = ;var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var elmName : String =  GetGUIElementNameByIndex(elmHandle);
      [*] = ;
      [*] = ;var status : String = GetValueByName('Status');
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
      [*] = ;      GetGUICurrentMouseCoord(mX, mY);
      [*] = ;      var x2, y2 : Integer;
      [*] = ;      GUIInvalidateParentPositions(elmHandle);
      [*] = ;      GetGUIElementAlignPosition(elmHandle, x2, y2);
      [*] = ;      SetIntValueByName('SliderElementDragX', mX-x2);
      [*] = ;      SetIntValueByName('SliderElementDragY', mY-y2);
      [*] = ;      ExecuteState('GUIInvokeMouseMove');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gIntRegister_GUIScrollSliderHandle<>0) or ((sPress='d') and (elmName='lineSlider')) then
      [*] = ;begin
      [*] = ;   SetIntValueByName('SliderElementDragX', 14);
      [*] = ;   var value : Float = _gui_ModifySliderValueByMouseCoord(elmSliderHandle);
      [*] = ;
      [*] = ;   case sliderID of
      [*] = ;      'wastelands' : gMapSettingsTmp.wastelands := value;
      [*] = ;      'population' : gMapSettingsTmp.population := value;
      [*] = ;      'isles' : gMapSettingsTmp.isles := value;
      [*] = ;      'forest' : gMapSettingsTmp.forest := value;
      [*] = ;      'neutrals' : gMapSettingsTmp.neutrals := value;
      [*] = ;      'dissolve' : gMapSettingsTmp.dissolve := value;
      [*] = ;      'hill' : gMapSettingsTmp.hill := value;
      [*] = ;      'resource' : gMapSettingsTmp.resource := value;
      [*] = ;      'water' : gMapSettingsTmp.water := value;
      [*] = ;      'swamp' : gMapSettingsTmp.swamp := value;
      [*] = ;      'site' : gMapSettingsTmp.site := value;
      [*] = ;   end;
      [*] = ;   var text : String;
      [*] = ;   var intValue : Integer = _misc_FloatToIntValueByCount(value, 5);
      [*] = ;   if (sliderID='neutrals') then
      [*] = ;   begin
      [*] = ;      case intValue of
      [*] = ;         0 : text := 'gui|378';
      [*] = ;         1 : text := 'gui|379';
      [*] = ;         2 : text := 'gui|380';
      [*] = ;         3 : text := 'gui|381';
      [*] = ;         4 : text := 'gui|382';
      [*] = ;      end;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      case intValue of
      [*] = ;         0 : text := 'gui|373';
      [*] = ;         1 : text := 'gui|374';
      [*] = ;         2 : text := 'gui|375';
      [*] = ;         3 : text := 'gui|376';
      [*] = ;         4 : text := 'gui|377';
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   _gui_SetSliderText(elmSliderHandle, text);
      [*] = ;end;
      [*] = ;
      [*] = ;const cBtnAcceptTag = 100;
      [*] = ;const cBtnCancelTag = 101;
      [*] = ;const cBtnSetDefaultTag = 102;
      [*] = ;const cBtnRandomTag = 103;
      [*] = ;
      [*] = ;if (sPress='c') and (gIntRegister_GUIScrollSliderHandle=0) then
      [*] = ;begin
      [*] = ;   if (elmName='arrowSliderLeft') or (elmName='arrowSliderRight') then
      [*] = ;   begin
      [*] = ;      if (sliderID='type') then
      [*] = ;      begin
      [*] = ;         var elmSliderHandle : Integer = GetGUIElementParentByIndex(elmHandle);
      [*] = ;         var value : Integer = gMapSettingsTmp.typ;
      [*] = ;         if (elmName='arrowSliderLeft') then
      [*] = ;         value := value-1
      [*] = ;         else
      [*] = ;         value := value+1;
      [*] = ;         var maxValue : Integer = 1;
      [*] = ;         if (value>maxValue) then value := 0;
      [*] = ;         if (value<0) then value := maxValue;
      [*] = ;         var text : String;
      [*] = ;         case value of
      [*] = ;            0 : text := 'gui|384';
      [*] = ;            1 : text := 'gui|383';
      [*] = ;         end;
      [*] = ;         _gui_SetSliderIntValue(elmSliderHandle, value, maxValue+1, text, False);
      [*] = ;         gMapSettingsTmp.typ := value;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (sliderID='') then
      [*] = ;   begin
      [*] = ;      var tag : Integer = GetIntValueByName('Tag');
      [*] = ;      case tag of
      [*] = ;         cBtnAcceptTag, gc_gui_hotkey_btnEnter : begin
      [*] = ;            gIntRegister_GUIScrollSliderHandle := 0;
      [*] = ;            _prof_MapGeneratorProfileSave(gMapSettingsTmp);
      [*] = ;            _misc_AssignGlobalVars('gMapSettingsTmp', 'gMapSettings');
      [*] = ;            _inet_SendShardGameSettings();
      [*] = ;            _gui_FadeElement(GetGUIElementIndexByNameParent('MapGeneratorSettings', _gui_GetLayerI()), gc_gui_FadeTime0_4, false, true, true);
      [*] = ;            
      [*] = ;            if (gGame.gameType = gc_GameTypeLanShard) then
      [*] = ;               _inet_SendShardGameSettings();
      [*] = ;         end;
      [*] = ;         cBtnCancelTag, gc_gui_hotkey_btnEscape : begin
      [*] = ;            gIntRegister_GUIScrollSliderHandle := 0;
      [*] = ;            _misc_AssignGlobalVars('gMapSettings', 'gMapSettingsTmp');
      [*] = ;            _gui_RootWindowRemoveWithFade(GetGUIElementIndexByNameParent('MapGeneratorSettings', _gui_GetLayerI()),gc_gui_FadeTime0_4);
      [*] = ;         end;
      [*] = ;         cBtnSetDefaultTag : begin
      [*] = ;            gIntRegister_GUIScrollSliderHandle := 0;
      [*] = ;            _map_MapGeneratorDefault(gMapSettingsTmp, False);
      [*] = ;            GUIExecuteState('ShowMapGeneratorSettings');
      [*] = ;         end;
      [*] = ;         cBtnRandomTag : begin
      [*] = ;            gIntRegister_GUIScrollSliderHandle := 0;
      [*] = ;            MakeRandom();
      [*] = ;            GUIExecuteState('ShowMapGeneratorSettings');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

