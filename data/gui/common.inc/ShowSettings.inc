section.begin
   Name = ShowSettings
   Code : struct.begin
      [*] = ;var pConfig : Integer = _misc_ParserGetOrCreateByKey('Config',false);
      [*] = ;if (ParserGetCountByHandle(pConfig)=0) then
      [*] = ;   ParserLoadFromFileByHandle(pConfig,'.\data\resources\config.res');
      [*] = ;
      [*] = ;procedure GetConfigEngineOption(configName : String; pConfig : Integer; var valueIndex, valueCount : Integer; var caption, key : String);
      [*] = ;begin
      [*] = ;   //var curValue : Integer = GetProjectOptionAsInteger(configName);
      [*] = ;   var curValue : String = GetProjectOptionAsString(configName);
      [*] = ;   if (pConfig<>0) then
      [*] = ;   begin
      [*] = ;      var pEngine : Integer = ParserSelectByHandleByKey(pConfig, 'engine');
      [*] = ;      if (pEngine<>0) then
      [*] = ;      begin
      [*] = ;         var pEngineConfigs : Integer = ParserSelectByHandleByKey(pEngine, 'config');
      [*] = ;         if (pEngineConfigs<>0) then
      [*] = ;         begin
      [*] = ;            var pEngineConfig : Integer = ParserSelectByHandleByIndex(pEngineConfigs, ParserFindChildIndexByEqualChildKey('Name', configName));
      [*] = ;            if (pEngineConfig<>0) then
      [*] = ;            begin
      [*] = ;               var pGui : Integer = ParserSelectByHandleByKey(pEngineConfig, 'Gui');
      [*] = ;               if (pGui<>0) then
      [*] = ;               begin
      [*] = ;                  caption := ParserGetValueByKeyByHandle(pGui, 'Caption');
      [*] = ;                  var pValues : Integer = ParserSelectByHandleByKey(pEngineConfig, 'Values');
      [*] = ;                  if (pValues<>0) then
      [*] = ;                  begin
      [*] = ;                     valueIndex := ParserFindChildIndexByEqualChildKey('value', curValue);
      [*] = ;                     //valueIndex := ParserFindChildIndexByEqualChildKey('value', IntToStr(curValue));
      [*] = ;                     var pValue : Integer = ParserSelectByHandleByIndex(pValues, valueIndex);
      [*] = ;                     key := ParserGetValueByKeyByHandle(pValue, 'key');
      [*] = ;                     valueCount := ParserGetCountByHandle(pValues);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure FillListBoxWithResolutions(listBoxHandle : Integer);
      [*] = ;begin
      [*] = ;   var pParser : Integer = _misc_ParserGetOrCreateByKey('showsettings_tmp',true);
      [*] = ;   GetAvailableResolutionsToActiveParser(False, 1000, 768);
      [*] = ;   var pParserWide : Integer = _misc_ParserGetOrCreateByKey('showsettings_tmpwide',true);
      [*] = ;   GetAvailableResolutionsToActiveParser(True, 1000, 768);
      [*] = ;   if (ParserGetCountByHandle(pParser)=0) then
      [*] = ;   begin
      [*] = ;      ErrorLogI('Valid resolutions not found');
      [*] = ;      GetAvailableResolutionsToActiveParser(False, 512, 512);
      [*] = ;   end;
      [*] = ;   var kRows : Integer = min(8, ParserGetCountByHandle(pParser)+ParserGetCountByHandle(pParserWide));
      [*] = ;   //var kRows : Integer = ParserGetCountByHandle(pParser);
      [*] = ;   GUIListBoxClear(listBoxHandle);
      [*] = ;   SetGUIListBoxVisibleRows(listBoxHandle, kRows);
      [*] = ;   var iTmpHandle : Integer = GetGUIComboBoxListBoxHandle(listBoxHandle);
      [*] = ;   SetGUIElementHeight(iTmpHandle, (GetGUIElementFontHeight(GetGUIElementFont(iTmpHandle))+4)*kRows+10);
      [*] = ;   SetGUIElementLogicHeight(iTmpHandle, GetGUIElementHeight(iTmpHandle));
      [*] = ;
      [*] = ;   if kRows < (ParserGetCountByHandle(pParser)+ParserGetCountByHandle(pParserWide)) then
      [*] = ;   begin
      [*] = ;      // - setup scroller
      [*] = ;      var elmVScroll : Integer = GetGUIListBoxScrollerHandle(iTmpHandle);
      [*] = ;      SetGUIElementAlign(elmVScroll, 'halParentRight', 'valParentTop');
      [*] = ;      SetGUIElementMaterialOffset(elmVScroll, 2, 0);
      [*] = ;      SetGUIElementAllPositionRect(elmVScroll, -32, 4, 32, GetGUIElementHeight(iTmpHandle)-6);
      [*] = ;      SetGUIElementMaterial(elmVScroll, 'map.dialog.scroller.tile');
      [*] = ;      SetGUIScrollButtonSource(elmVScroll, 0, 'map.dialog.scroller.up', true);
      [*] = ;      SetGUIScrollButtonSource(elmVScroll, 2, 'map.dialog.scroller.down', true);
      [*] = ;      SetGUIScrollButtonSource(elmVScroll, 1, 'map.dialog.scroller.slider', true);
      [*] = ;      SetGUIAllowEvents(elmVScroll, True, False, False);
      [*] = ;      SetGUIElementTextAlign(iTmpHandle, 'halMiddle', 'valMiddle', -10, -5);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   SetGUIElementTextAlign(iTmpHandle, 'halMiddle', 'valMiddle', 0, -5);
      [*] = ;
      [*] = ;   var i : Integer;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pParser)-1 do
      [*] = ;   begin
      [*] = ;      ParserSelectByHandleByIndex(pParser, i);
      [*] = ;      GUIListBoxAddItem(listBoxHandle, ParserGetValueByKey('Width') + ' x ' + ParserGetValueByKey('Height') + ' ' + ParserGetValueByKey('MaxFrequency') + 'Hz', ParserGetIntValueByKey('Index'));
      [*] = ;      if ParserGetBoolValueByKey('Default') then
      [*] = ;      SetGUIListBoxItemIndexSilent(listBoxHandle, i);
      [*] = ;   end;
      [*] = ;   for i := 0 to ParserGetCountByHandle(pParserWide)-1 do
      [*] = ;   begin
      [*] = ;      ParserSelectByHandleByIndex(pParserWide, i);
      [*] = ;      GUIListBoxAddItem(listBoxHandle, ParserGetValueByKey('Width') + ' x ' + ParserGetValueByKey('Height') + ' ' + ParserGetValueByKey('MaxFrequency') + 'Hz', ParserGetIntValueByKey('Index'));
      [*] = ;      if ParserGetBoolValueByKey('Default') then
      [*] = ;      SetGUIListBoxItemIndexSilent(listBoxHandle, ParserGetCountByHandle(pParser)+i);
      [*] = ;   end;
      [*] = ;
      [*] = ;   if GetGUIListBoxItemIndex(listBoxHandle) < 0 then
      [*] = ;      SetGUIListBoxItemIndexSilent(listBoxHandle, 0);
      [*] = ;end;
      [*] = ;
      [*] = ;procedure FillListBoxWithConfigEngineOption(configName, curValue : String; listBoxHandle, pConfig : Integer; var valueIndex, valueCount : Integer; var caption, key : String);
      [*] = ;begin
      [*] = ;   if (pConfig<>0) then
      [*] = ;   begin
      [*] = ;      var pEngine : Integer = ParserSelectByHandleByKey(pConfig, 'engine');
      [*] = ;      if (pEngine<>0) then
      [*] = ;      begin
      [*] = ;         var pEngineConfigs : Integer = ParserSelectByHandleByKey(pEngine, 'config');
      [*] = ;         if (pEngineConfigs<>0) then
      [*] = ;         begin
      [*] = ;            var pEngineConfig : Integer = ParserSelectByHandleByIndex(pEngineConfigs, ParserFindChildIndexByEqualChildKey('Name', configName));
      [*] = ;            if (pEngineConfig<>0) then
      [*] = ;            begin
      [*] = ;               var pGui : Integer = ParserSelectByHandleByKey(pEngineConfig, 'Gui');
      [*] = ;               if (pGui<>0) then
      [*] = ;               begin
      [*] = ;                  caption := ParserGetValueByKeyByHandle(pGui, 'Caption');
      [*] = ;                  var pValues : Integer = ParserSelectByHandleByKey(pEngineConfig, 'Values');
      [*] = ;                  if (pValues<>0) then
      [*] = ;                  begin
      [*] = ;                     //GUIListBoxClear(listBoxHandle);
      [*] = ;                     valueIndex := ParserFindChildIndexByEqualChildKey('value', curValue);
      [*] = ;                     valueCount := ParserGetCountByHandle(pValues);
      [*] = ;                     var i : Integer;
      [*] = ;                     var stringTag : String = '';
      [*] = ;                     for i:=0 to valueCount-1 do
      [*] = ;                     begin
      [*] = ;                        var pValue : Integer = ParserSelectByHandleByIndex(pValues, i);
      [*] = ;                        key := ParserGetValueByKeyByHandle(pValue, 'key');
      [*] = ;                        GUIListBoxAddItem(listBoxHandle, GetLocaleTableListItemByID('tools', key), i);
      [*] = ;
      [*] = ;                        var value : String = ParserGetValueByKeyByHandle(pValue, 'value');
      [*] = ;                        if (stringTag<>'') then
      [*] = ;                           stringTag := stringTag+'|'+value
      [*] = ;                        else
      [*] = ;                           stringTag := value;
      [*] = ;                     end;
      [*] = ;                     SetGUIElementStringTag(listBoxHandle, stringTag);
      [*] = ;                     // combobox setup start
      [*] = ;                     var kRows : Integer = min(9, valueCount);
      [*] = ;                     SetGUIListBoxVisibleRows(listBoxHandle, kRows);
      [*] = ;                     var iTmpHandle : Integer = GetGUIComboBoxListBoxHandle(listBoxHandle);
      [*] = ;                     SetGUIElementHeight(iTmpHandle, (GetGUIElementFontHeight(GetGUIElementFont(iTmpHandle))+4)*kRows+10);
      [*] = ;                     SetGUIElementLogicHeight(iTmpHandle, GetGUIElementHeight(iTmpHandle));
      [*] = ;                     if (kRows<valueCount) then
      [*] = ;                     begin
      [*] = ;                        SetGUIElementTextAlign(iTmpHandle, 'halMiddle', 'valMiddle', -10, -5);
      [*] = ;                        // - setup scroller
      [*] = ;                        var elmVScroll : Integer = GetGUIListBoxScrollerHandle(iTmpHandle);
      [*] = ;                        SetGUIElementAlign(elmVScroll, 'halParentRight', 'valParentTop');
      [*] = ;                        SetGUIElementMaterialOffset(elmVScroll, 2, 0);
      [*] = ;                        SetGUIElementAllPositionRect(elmVScroll, -32, 4, 32, GetGUIElementHeight(iTmpHandle)-6);
      [*] = ;                        SetGUIElementMaterial(elmVScroll, 'map.dialog.scroller.tile');
      [*] = ;                        SetGUIScrollButtonSource(elmVScroll, 0, 'map.dialog.scroller.up', true);
      [*] = ;                        SetGUIScrollButtonSource(elmVScroll, 2, 'map.dialog.scroller.down', true);
      [*] = ;                        SetGUIScrollButtonSource(elmVScroll, 1, 'map.dialog.scroller.slider', true);
      [*] = ;                        SetGUIAllowEvents(elmVScroll, True, False, False);
      [*] = ;                     end
      [*] = ;                     else
      [*] = ;                        SetGUIElementTextAlign(iTmpHandle, 'halMiddle', 'valMiddle', 0, -5);
      [*] = ;
      [*] = ;                     //if GetGUIListBoxItemIndex(listBoxHandle) < 0 then
      [*] = ;                     //SetGUIListBoxItemIndexSilent(listBoxHandle, 0)
      [*] = ;                     //else
      [*] = ;                     SetGUIListBoxItemIndexSilent(listBoxHandle, valueIndex);
      [*] = ;                     // combobox setup finish
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure GetCheckBoxStringTagWithConfigEngineOption(var stringTag : String; const configName, curValue : String; const pConfig : Integer; var valueIndex : Integer; var caption : String);
      [*] = ;begin
      [*] = ;   stringTag := '';
      [*] = ;   //var curValue : String = GetProjectOptionAsString(configName);
      [*] = ;   if (pConfig<>0) then
      [*] = ;   begin
      [*] = ;      var pEngine : Integer = ParserSelectByHandleByKey(pConfig, 'engine');
      [*] = ;      if (pEngine<>0) then
      [*] = ;      begin
      [*] = ;         var pEngineConfigs : Integer = ParserSelectByHandleByKey(pEngine, 'config');
      [*] = ;         if (pEngineConfigs<>0) then
      [*] = ;         begin
      [*] = ;            var pEngineConfig : Integer = ParserSelectByHandleByIndex(pEngineConfigs, ParserFindChildIndexByEqualChildKey('Name', configName));
      [*] = ;            if (pEngineConfig<>0) then
      [*] = ;            begin
      [*] = ;               var pGui : Integer = ParserSelectByHandleByKey(pEngineConfig, 'Gui');
      [*] = ;               if (pGui<>0) then
      [*] = ;               begin
      [*] = ;                  caption := ParserGetValueByKeyByHandle(pGui, 'Caption');
      [*] = ;                  var pValues : Integer = ParserSelectByHandleByKey(pEngineConfig, 'Values');
      [*] = ;                  if (pValues<>0) then
      [*] = ;                  begin
      [*] = ;                     //GUIListBoxClear(listBoxHandle);
      [*] = ;                     valueIndex := ParserFindChildIndexByEqualChildKey('value', curValue);
      [*] = ;                     var valueCount : Integer = ParserGetCountByHandle(pValues);
      [*] = ;                     if (valueCount>2) then
      [*] = ;                     ErrorLog('GetCheckBoxStringTagWithConfigEngineOption : valueCount>2');
      [*] = ;                     var i : Integer;
      [*] = ;                     for i:=0 to valueCount-1 do
      [*] = ;                     begin
      [*] = ;                        var pValue : Integer = ParserSelectByHandleByIndex(pValues, i);
      [*] = ;                        var value : String = ParserGetValueByKeyByHandle(pValue, 'value');
      [*] = ;                        if (stringTag<>'') then
      [*] = ;                        stringTag := stringTag+'|'+value
      [*] = ;                        else
      [*] = ;                        stringTag := value;
      [*] = ;                     end;
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;const cYOff = 52;
      [*] = ;const cEventState = 'EventSettings';
      [*] = ;var btnWidth : Integer = GetGUITextureWidth('common.btn.normal');
      [*] = ;var btnHeight : Integer = GetGUITextureHeight('common.btn.normal');
      [*] = ;
      [*] = ;function DrawButtonSettingsTabCheckable(const text : String; const parent : Integer; var py : Integer; btnTag : Integer; const bEnabled, bChecked : Boolean) : Integer;
      [*] = ;begin
      [*] = ;   var fontHandle : String;
      [*] = ;   _gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'',fontHandle);
      [*] = ;
      [*] = ;   var elmBtnHandle : Integer = _gui_CreateButton('', parent, '', 'common.btn', 'halParentLeft', 'valParentTop', 15, py, btnWidth, btnHeight, cEventState, '', btnTag);
      [*] = ;   var elmTextHandle : Integer = _gui_CreateText('', elmBtnHandle, text, 'halParentLeft', 'valParentTop', 0, 0, btnWidth, btnHeight, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;   SetGUIElementUserBlend(elmBtnHandle, 0.7);
      [*] = ;   if (bChecked) then
      [*] = ;   begin
      [*] = ;      SetGUIElementVisibleProperties(elmBtnHandle, 'CheckOnProperty', 'common.btn.pressed', 0, 0, 0, 0, 0, 0.5, 0.5, 0.5, 1);
      [*] = ;      SetGUIElementVisibleProperties(elmBtnHandle, 'UpProperty', 'common.btn.pressed', 0, 0, 0, 0, 0, 0.5, 0.5, 0.5, 1);
      [*] = ;      SetGUIElementVisibleProperties(elmBtnHandle, 'HoverProperty', 'common.btn.pressed', 0, 0, 0, 0, 0, 0.5, 0.5, 0.5, 1);
      [*] = ;   end;
      [*] = ;   //SetGUIElementVisibleProperties(elmParentHandle, 'CheckOnProperty', 'common.checkbox.checkon', xOff, yOff, txOff, tyOff, 6, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;   //var elmTextHandle : Integer = _gui_CreateText('', parent, text, 'halParentMiddle', 'valParentTop', 0, py, btnWidth, btnHeight, 'halMiddle', 'valMiddle', , gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;   if (not bEnabled) then
      [*] = ;   begin
      [*] = ;      SetGUIElementEnabled(elmBtnHandle, bEnabled);
      [*] = ;      SetGUIElementColor(elmTextHandle, 0.5, 0.5, 0.5, 1);
      [*] = ;   end;
      [*] = ;
      [*] = ;   py := py+cYOff;
      [*] = ;   Result := elmBtnHandle;
      [*] = ;end;
      [*] = ;
      [*] = ;var fontHandle, fontHandle2, fontHandle3: String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_small,'',fontHandle);   // HeaderS
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_default,'',fontHandle2); // NormalL
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_large,'',fontHandle3); // HeaderM
      [*] = ;
      [*] = ;const sGroupPanel1 = 'halParentRight';
      [*] = ;const sGroupPanel2 = 'halParentRight';
      [*] = ;const sGroupPanel0 = 'halParentRight';
      [*] = ;const iGroupPanelOffset1 = -247;
      [*] = ;const iGroupPanelOffset2 = -247;
      [*] = ;const iGroupPanelOffset0 = -247;
      [*] = ;const iGroupYOffset = 32+15;
	   [*] = ;const cCheckBoxOffsetX = 31;
      [*] = ;const topMargin = 43;
      [*] = ;//const panelWidth = 324;
      [*] = ;//const leftPadding = 7;
      [*] = ;
      [*] = ;// Check if window was already visible, then no need to FadeIn it when show again
      [*] = ;var prevElmParentHandle : Integer = GetGUIElementIndexByNameParent('Settings', _gui_GetLayerI());
      [*] = ;var bVisible : Boolean = False;
      [*] = ;if (prevElmParentHandle<>0) and GetGUIElementVisible(prevElmParentHandle) then
      [*] = ;bVisible := True;
      [*] = ;
      [*] = ;const cTabSound = 1;
      [*] = ;const cTabVideo = 2;
      [*] = ;const cTabInterface = 3;
      [*] = ;const cTabGameplay = 4;
      [*] = ;const cTabCombat = 5;
      [*] = ;const cTabInternet = 6;
      [*] = ;
      [*] = ;const cBtnAcceptTag = 100;
      [*] = ;const cBtnCancelTag = 101;
      [*] = ;const cBtnSetDefaultTag = 102;
      [*] = ;const cCheckboxMute = 121;
      [*] = ;const cCheckboxImprovedAI = 122;
      [*] = ;const cCheckboxClampingMouse = 123;
      [*] = ;const cCheckboxSimpleGraphics = 124;
      [*] = ;const cCheckboxAutoConnect = 125;
      [*] = ;const cCheckboxNotifyNewGame = 126;
      [*] = ;const cCheckboxShowAdvanced = 127;
      [*] = ;const cCheckboxShowScenery = 128;
      [*] = ;const cCheckboxShowControls = 129;
      [*] = ;const cCheckboxShowProvinceHUD = 130;
      [*] = ;const cCheckboxShowMessages = 131;
      [*] = ;//const cCheckboxBell = 131;
      [*] = ;
      [*] = ;const cBtnSound = 301;
      [*] = ;const cBtnVideo = 302;
      [*] = ;const cBtnInterface = 303;
      [*] = ;const cBtnGameplay = 304;
      [*] = ;const cBtnCombat = 305;
      [*] = ;const cBtnInternet = 306;
      [*] = ;
      [*] = ;const cSwitchResolutionApprove = 401;
      [*] = ;const cSwitchResolutionCancel = 402;
      [*] = ;
      [*] = ;const cMapFlagsBaseTag = 1000;
      [*] = ;const cMessageFlagsBaseTag = 1100;
      [*] = ;const cCombatFlagsBaseTag = 1200;
      [*] = ;const cSceneryFlagsBaseTag = 1300;
      [*] = ;
      [*] = ;const cExpandedAdvancedVideo = 1;
      [*] = ;const cExpandedScenery = 2;
      [*] = ;const cExpandedControls = 3;
      [*] = ;const cExpandedProvinceHUD = 4;
      [*] = ;const cExpandedMessages = 5;
      [*] = ;
      [*] = ;function GetExpandedWindowMode() : Integer;
      [*] = ;begin
      [*] = ;   Result := 0;
      [*] = ;   
      [*] = ;   if (gIntRegister_GUISettingTab = cTabVideo) then 
      [*] = ;   begin
      [*] = ;      if GetGUIElementChecked(GetGUIElementIndexByNameParent('video.expand_advancedvideo', prevElmParentHandle)) then
      [*] = ;         Result := cExpandedAdvancedVideo
      [*] = ;      else
      [*] = ;      if GetGUIElementChecked(GetGUIElementIndexByNameParent('video.expand_scenery', prevElmParentHandle)) then
      [*] = ;         Result := cExpandedScenery;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (gIntRegister_GUISettingTab = cTabInterface) then 
      [*] = ;   begin
      [*] = ;      if GetGUIElementChecked(GetGUIElementIndexByNameParent('interface.expand_controls', prevElmParentHandle)) then
      [*] = ;         Result := cExpandedControls
      [*] = ;      else
      [*] = ;      if GetGUIElementChecked(GetGUIElementIndexByNameParent('interface.expand_provhud', prevElmParentHandle)) then
      [*] = ;         Result := cExpandedProvinceHUD
      [*] = ;      else
      [*] = ;      if GetGUIElementChecked(GetGUIElementIndexByNameParent('interface.expand_messages', prevElmParentHandle)) then
      [*] = ;         Result := cExpandedMessages;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var expandedWindow : Integer = GetExpandedWindowMode();
      [*] = ;
      [*] = ;//SetBoolValueByName('ShowSettingsInProgress', True);
      [*] = ;var elmParentHandle, elmHeaderHandle, elmTextHandle : Integer;
      [*] = ;if expandedWindow > 0 then
      [*] = ;begin
      [*] = ;   elmParentHandle := _gui_CreateLargeWindow(0, 'Settings', 'halParentMiddle', 'valParentMiddle', 0+(242 div 2), 5, 960-440-20+242, 816-390-20+43, true);
      [*] = ;   elmHeaderHandle := GetGUIElementIndexByNameParent('header', elmParentHandle);
      [*] = ;   SetGUIElementPositionX(elmHeaderHandle, GetGUIElementPositionX(elmHeaderHandle)-(242 div 2));
      [*] = ;   elmTextHandle := _gui_CreateText('', elmHeaderHandle, 'menu|6', 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHeaderHandle), GetGUIElementHeight(elmHeaderHandle), 'halMiddle', 'valMiddle', fontHandle3, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   elmParentHandle := _gui_CreateLargeWindow(0, 'Settings', 'halParentMiddle', 'valParentMiddle', 0, 5, 960-440-20, 816-390-20+43, true);
      [*] = ;   var elmHeaderHandle : Integer = GetGUIElementIndexByNameParent('header', elmParentHandle);
      [*] = ;   var elmTextHandle : Integer = _gui_CreateText('', elmHeaderHandle, 'menu|6', 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHeaderHandle), GetGUIElementHeight(elmHeaderHandle), 'halMiddle', 'valMiddle', fontHandle3, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;end;
      [*] = ;
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('background', elmParentHandle), 0.65);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('frame', elmParentHandle), 0.75);
      [*] = ;
      [*] = ;var py : Integer = topMargin;
      [*] = ;DrawButtonSettingsTabCheckable('menu|26', elmParentHandle, py, cBtnSound, true, gIntRegister_GUISettingTab=cTabSound);
      [*] = ;DrawButtonSettingsTabCheckable('menu|91', elmParentHandle, py, cBtnVideo, true, gIntRegister_GUISettingTab=cTabVideo);
      [*] = ;DrawButtonSettingsTabCheckable('menu|97', elmParentHandle, py, cBtnInterface, true, gIntRegister_GUISettingTab=cTabInterface);
      [*] = ;DrawButtonSettingsTabCheckable('menu|89', elmParentHandle, py, cBtnGameplay, true, gIntRegister_GUISettingTab=cTabGameplay);
      [*] = ;DrawButtonSettingsTabCheckable('menu|84', elmParentHandle, py, cBtnCombat, true, gIntRegister_GUISettingTab=cTabCombat);
      [*] = ;DrawButtonSettingsTabCheckable('menu|internet', elmParentHandle, py, cBtnInternet, true, gIntRegister_GUISettingTab=cTabInternet);
      [*] = ;
      [*] = ;case gIntRegister_GUISettingTab of
      [*] = ;   cTabSound :
      [*] = ;   begin
      [*] = ;      // Sound
      [*] = ;      var posX : Integer = iGroupPanelOffset1;
      [*] = ;      var posY : Integer = iGroupYOffset;
      [*] = ;      var elmSoundHandle : Integer = _gui_CreateImage('sound', elmParentHandle, 'element.strip.240', sGroupPanel1, 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmSoundHandle, 'menu|26', 'halParentLeft', 'valParentTop', 0, -2, GetGUIElementWidth(elmSoundHandle), GetGUIElementHeight(elmSoundHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;      var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('', elmSoundHandle, (gProfileTmp.sndmute=1), 'menu|88', 'halParentLeft', 'valParentTop', cCheckBoxOffsetX, 43, cEventState, '', cCheckboxMute);
      [*] = ;      posY := 67;
      [*] = ;      var elmSliderHandle : Integer = _gui_CreateSimpleSlider('sndmaster', gProfileTmp.sndmaster, elmSoundHandle, 'halParentLeft', 'valParentTop', 20, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmSliderHandle, 'menu|27', 'halParentLeft', 'valParentTop', 29, -4, GetGUIElementWidth(elmSliderHandle), GetGUIElementHeight(elmSliderHandle), 'halLeft', 'valMiddle', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      posY := posY+42;
      [*] = ;      elmSliderHandle := _gui_CreateSimpleSlider('sndmusic', gProfileTmp.sndmusic, elmSoundHandle, 'halParentLeft', 'valParentTop', 20, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmSliderHandle, 'menu|30', 'halParentLeft', 'valParentTop', 29, -4, GetGUIElementWidth(elmSliderHandle), GetGUIElementHeight(elmSliderHandle), 'halLeft', 'valMiddle', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      posY := posY+42;
      [*] = ;      elmSliderHandle := _gui_CreateSimpleSlider('sndambient', gProfileTmp.sndambient, elmSoundHandle, 'halParentLeft', 'valParentTop', 20, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmSliderHandle, 'menu|28', 'halParentLeft', 'valParentTop', 29, -4, GetGUIElementWidth(elmSliderHandle), GetGUIElementHeight(elmSliderHandle), 'halLeft', 'valMiddle', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      posY := posY+42;
      [*] = ;      elmSliderHandle := _gui_CreateSimpleSlider('sndfx', gProfileTmp.sndfx, elmSoundHandle, 'halParentLeft', 'valParentTop', 20, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmSliderHandle, 'menu|29', 'halParentLeft', 'valParentTop', 29, -4, GetGUIElementWidth(elmSliderHandle), GetGUIElementHeight(elmSliderHandle), 'halLeft', 'valMiddle', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      posY := posY+42;
      [*] = ;      elmSliderHandle := _gui_CreateSimpleSlider('sndinterface', gProfileTmp.sndinterface, elmSoundHandle, 'halParentLeft', 'valParentTop', 20, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmSliderHandle, 'menu|31', 'halParentLeft', 'valParentTop', 29, -4, GetGUIElementWidth(elmSliderHandle), GetGUIElementHeight(elmSliderHandle), 'halLeft', 'valMiddle', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      
      [*] = ;      //posY := posY + 68;
      [*] = ;      //var text : String = GetLocaleTableListItemByID('menu', 'bell') + ' (' + GetLocaleTableListItemByID('gui', '448') + ')';
      [*] = ;      //elmCheckBoxHandle := _gui_CreateCheckBox('', elmSoundHandle, gProfileTmp.bell, text, 'halParentLeft', 'valParentTop', cCheckBoxOffsetX, posY, cEventState, '', cCheckboxBell);
      [*] = ;      
      [*] = ;      
      [*] = ;      //var elmListBoxHandle : Integer = _gui_CreateListBox('bell', elmSoundHandle, 8, 5, posY, cEventState);
      [*] = ;      //var text : String = GetLocaleTableListItemByID('menu', 'bell') + ' (' + GetLocaleTableListItemByID('gui', '448') + ')';
      [*] = ;      
      [*] = ;      //elmTextHandle := _gui_CreateText('header', elmListBoxHandle, text, 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      //GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('gui', '416'), 0); // always
      [*] = ;      
      [*] = ;      //var i : Integer;
      [*] = ;      //text := GetLocaleTableListItemByID('menu', 'seconds');
      [*] = ;      //for i := 1 to 6 do
      [*] = ;      //GUIListBoxAddItem(elmListBoxHandle, IntToStr(_misc_GetBellTimerByIndex(i))+' '+text, i);
      [*] = ;      
      [*] = ;      //GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('gui', '414'), 7); // never
      [*] = ;      //SetGUIListBoxItemIndexSilent(elmListBoxHandle, gProfileTmp.bell);
      [*] = ;      //SetGUIElementHint(elmListBoxHandle, '');
      [*] = ;   end;
      [*] = ;   cTabVideo :
      [*] = ;   begin
      [*] = ;      // Video
      [*] = ;      var pConfig : Integer = _misc_ParserGetOrCreateByKey('Config',false);
      [*] = ;      if (ParserGetCountByHandle(pConfig)=0) then
      [*] = ;         ParserLoadFromFile('.\data\resources\config.res');
      [*] = ;      
      [*] = ;      var posX : Integer = iGroupPanelOffset2;
      [*] = ;      if (expandedWindow = cExpandedAdvancedVideo) or (expandedWindow = cExpandedScenery) then
      [*] = ;      posX := posX-242;
      [*] = ;      var posY : Integer = iGroupYOffset;
      [*] = ;      var elmVideoHandle : Integer = _gui_CreateImage('video', elmParentHandle, 'element.strip.240', sGroupPanel2, 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmVideoHandle, 'menu|91', 'halParentLeft', 'valParentTop', 0, -2, GetGUIElementWidth(elmVideoHandle), GetGUIElementHeight(elmVideoHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;      
      [*] = ;   
      [*] = ;      var valueIndex, valueCount, elmListBoxHandle : Integer;
      [*] = ;      var caption, key, curPreset : String = '';
      [*] = ;      var yOff : Integer = 60;
      [*] = ;      var settingIndex : Integer = 0;
      [*] = ;      posX := 6;
      [*] = ;      posY := 64;
      [*] = ;      
      [*] = ;      // Video Preset
      [*] = ;      _gui_CreateVideoPresetListBox(posX, posY+yOff*settingIndex);
      [*] = ;      Inc(settingIndex, 1);
      [*] = ;   
      [*] = ;      // resolution
      [*] = ;      if (GetDisplayMode = 'dmFullScreen') then
      [*] = ;      begin
      [*] = ;         elmListBoxHandle := _gui_CreateListBox(gc_ProjOptionsResolution, elmVideoHandle, 0, posX, posY+yOff*settingIndex, cEventState);
      [*] = ;         elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'menu|94', 'halParentLeft', 'valParentTop', 0, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;         //var bWide : Boolean = (abs(GetViewerWidth/GetViewerHeight - 16.0/9.0) < 0.1) or (abs(GetViewerWidth/GetViewerHeight - 16.0/10.0) < 0.1);
      [*] = ;         FillListBoxWithResolutions(elmListBoxHandle);
      [*] = ;         Inc(settingIndex, 1);
      [*] = ;      end;
      [*] = ;   
      [*] = ;      // light change
      [*] = ;      elmListBoxHandle := _gui_CreateListBox(gc_ProjOptionsLightChange, elmVideoHandle, 0, posX, posY+yOff*settingIndex, cEventState);
      [*] = ;      FillListBoxWithConfigEngineOption(gc_ProjOptionsLightChange, IntToStr(gProfileTmp.lightchange), elmListBoxHandle, pConfig, valueIndex, valueCount, caption, key);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'tools|CFG.PROFILE.LIGHTCHANGE', 'halParentLeft', 'valParentTop', 0, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      Inc(settingIndex, 1);
      [*] = ;   
      [*] = ;      // simplified graphics
      [*] = ;      posY := 290; //boxes should not overlap with any of the dropdown options that become visible in the preset dropdown menu, or there will be problems, because they will get triggered when selecting from the drop down menu
      [*] = ;      //_gui_CreateCheckBox('', elmVideoHandle, gProfileTmp.simplegraphics, GetLocaleTableListItemByID('tools','CFG.PROFILE.LOWESTMODE'), 'halParentLeft', 'valParentTop', cCheckBoxOffsetX, posY, cEventState, '', cCheckboxSimpleGraphics);
      [*] = ;   
      [*] = ;      // sub-menus
      [*] = ;      posY := posY + 20;
      [*] = ;      var text : String = GetLocaleTableListItemByID('gui', 'scenery');
      [*] = ;      if expandedWindow = cExpandedScenery then
      [*] = ;         text := text + '   <<'
      [*] = ;      else
      [*] = ;         text := text + '   >>';
      [*] = ;      var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('expand_scenery', elmVideoHandle, expandedWindow = cExpandedScenery, text, 'halParentLeft', 'valParentTop', cCheckBoxOffsetX, posY, cEventState, '', cCheckboxShowScenery);
      [*] = ;      posY := posY + 20;
      [*] = ;      
      [*] = ;      text := GetLocaleTableListItemByID('menu','92');
      [*] = ;      if expandedWindow = cExpandedAdvancedVideo then
      [*] = ;         text := text + '   <<'
      [*] = ;      else
      [*] = ;         text := text + '   >>';
      [*] = ;      elmCheckBoxHandle := _gui_CreateCheckBox('expand_advancedvideo', elmVideoHandle, expandedWindow = cExpandedAdvancedVideo, text, 'halParentLeft', 'valParentTop', cCheckBoxOffsetX, posY, cEventState, '', cCheckboxShowAdvanced);
      [*] = ;   
      [*] = ;      if expandedWindow = cExpandedAdvancedVideo then
      [*] = ;      begin
      [*] = ;         // advanced video
      [*] = ;         posX := iGroupPanelOffset2;
      [*] = ;         posY := iGroupYOffset;
      [*] = ;         var elmAdvancedVideoHandle : Integer = _gui_CreateImage('advanced', elmParentHandle, 'element.strip.240', sGroupPanel2, 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;         elmTextHandle := _gui_CreateText('', elmAdvancedVideoHandle, 'menu|92', 'halParentLeft', 'valParentTop', 0, -2, GetGUIElementWidth(elmAdvancedVideoHandle), GetGUIElementHeight(elmAdvancedVideoHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;   
      [*] = ;         posX := 6;
      [*] = ;         posY := 64;
      [*] = ;         settingIndex := 0;
      [*] = ;   
      [*] = ;         // anti-aliasing
      [*] = ;         elmListBoxHandle := _gui_CreateListBox(gc_ProjOptionsAntiAliasing, elmAdvancedVideoHandle, 0, posX, posY+yOff*settingIndex, cEventState);
      [*] = ;         FillListBoxWithConfigEngineOption(gc_ProjOptionsAntiAliasing, gVideoSettingsTmp.antialiasing, elmListBoxHandle, pConfig, valueIndex, valueCount, caption, key);
      [*] = ;         elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'tools|'+caption, 'halParentLeft', 'valParentTop', 0, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;         Inc(settingIndex, 1);
      [*] = ;   
      [*] = ;         // texture filter
      [*] = ;         elmListBoxHandle := _gui_CreateListBox(gc_ProjOptionsTextureFilter, elmAdvancedVideoHandle, 0, posX, posY+yOff*settingIndex, cEventState);
      [*] = ;         FillListBoxWithConfigEngineOption(gc_ProjOptionsTextureFilter, gVideoSettingsTmp.texturefilter, elmListBoxHandle, pConfig, valueIndex, valueCount, caption, key);
      [*] = ;         elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'tools|'+caption, 'halParentLeft', 'valParentTop', 0, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;         Inc(settingIndex, 1);
      [*] = ;   
      [*] = ;         // shader version
      [*] = ;         elmListBoxHandle := _gui_CreateListBox(gc_ProjOptionsShaderType, elmAdvancedVideoHandle, 0, posX, posY+yOff*settingIndex, cEventState);
      [*] = ;         FillListBoxWithConfigEngineOption(gc_ProjOptionsShaderType, gVideoSettingsTmp.shadertype, elmListBoxHandle, pConfig, valueIndex, valueCount, caption, key);
      [*] = ;         elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'tools|'+caption, 'halParentLeft', 'valParentTop', 0, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;         Inc(settingIndex, 1);
      [*] = ;   
      [*] = ;         // water reflaction
      [*] = ;         elmListBoxHandle := _gui_CreateListBox(gc_ProjOptionsWaterReflection, elmAdvancedVideoHandle, 0, posX, posY+yOff*settingIndex, cEventState);
      [*] = ;         FillListBoxWithConfigEngineOption(gc_ProjOptionsWaterReflection, gVideoSettingsTmp.waterreflection, elmListBoxHandle, pConfig, valueIndex, valueCount, caption, key);
      [*] = ;         elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'tools|'+caption, 'halParentLeft', 'valParentTop', 0, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;         Inc(settingIndex, 1);
      [*] = ;   
      [*] = ;         // shadowmap
      [*] = ;         var stringTag : String;
      [*] = ;         posY := posY+yOff*settingIndex-16;
      [*] = ;         settingIndex := 0;
      [*] = ;         GetCheckBoxStringTagWithConfigEngineOption(stringTag, gc_ProjOptionsShadowEnabled, BoolToStr(gVideoSettingsTmp.shadowenabled), pConfig, valueIndex, caption);
      [*] = ;         elmCheckBoxHandle := _gui_CreateCheckBox(gc_ProjOptionsShadowEnabled, elmAdvancedVideoHandle, gVideoSettingsTmp.shadowenabled, 'tools|'+caption, 'halParentLeft', 'valParentTop', cCheckBoxOffsetX, posY+20*settingIndex, cEventState, '', cCheckboxShowAdvanced);
      [*] = ;         SetGUIElementStringTag(elmCheckBoxHandle, stringTag);
      [*] = ;         Inc(settingIndex, 1);
      [*] = ;   
      [*] = ;         // hdr
      [*] = ;         GetCheckBoxStringTagWithConfigEngineOption(stringTag, gc_ProjOptionsHDRType, gVideoSettingsTmp.hdrtype, pConfig, valueIndex, caption);
      [*] = ;         elmCheckBoxHandle := _gui_CreateCheckBox(gc_ProjOptionsHDRType, elmAdvancedVideoHandle, (valueIndex=1), 'tools|'+caption, 'halParentLeft', 'valParentTop', cCheckBoxOffsetX, posY+20*settingIndex, cEventState, '', cCheckboxShowAdvanced);
      [*] = ;         SetGUIElementStringTag(elmCheckBoxHandle, stringTag);
      [*] = ;         Inc(settingIndex, 1);
      [*] = ;   
      [*] = ;         // v-sync
      [*] = ;         GetCheckBoxStringTagWithConfigEngineOption(stringTag, gc_ProjOptionsVSyncMode, gVideoSettingsTmp.vsyncmode, pConfig, valueIndex, caption);
      [*] = ;         elmCheckBoxHandle := _gui_CreateCheckBox(gc_ProjOptionsVSyncMode, elmAdvancedVideoHandle, (valueIndex=1), 'tools|'+caption, 'halParentLeft', 'valParentTop', cCheckBoxOffsetX, posY+20*settingIndex, cEventState, '', cCheckboxShowAdvanced);
      [*] = ;         SetGUIElementStringTag(elmCheckBoxHandle, stringTag);
      [*] = ;         Inc(settingIndex, 1);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if expandedWindow = cExpandedScenery then
      [*] = ;      begin
      [*] = ;         // Scenery
      [*] = ;         posX := iGroupPanelOffset2;
      [*] = ;         posY := iGroupYOffset;
      [*] = ;         var elmSceneryHandle : Integer = _gui_CreateImage('scenery', elmParentHandle, 'element.strip.240', sGroupPanel2, 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;         elmTextHandle := _gui_CreateText('', elmSceneryHandle, 'gui|scenery', 'halParentLeft', 'valParentTop', 0, -2, GetGUIElementWidth(elmSceneryHandle), GetGUIElementHeight(elmSceneryHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;         
      [*] = ;         procedure CreateSceneryListBox(const elmName, sHeader : String; const posX, posY, silentIndex : Integer);
      [*] = ;         begin
      [*] = ;            var elmListBoxHandle : Integer = _gui_CreateListBox(elmName, elmSceneryHandle, 5, posX, posY, cEventState);
      [*] = ;            _gui_FillGraphicsListBox(elmListBoxHandle);
      [*] = ;            SetGUIListBoxItemIndexSilent(elmListBoxHandle, silentIndex);
      [*] = ;            var elmTextHandle : Integer = _gui_CreateText('header', elmListBoxHandle, sHeader, 'halParentLeft', 'valParentTop', posX-4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;         end;
      [*] = ;         
      [*] = ;         posX := 6;
      [*] = ;         posY := 64;
      [*] = ;         CreateSceneryListBox('shard_decor', 'gui|616', posX, posY, gProfileTmp.shardscenery);
      [*] = ;         
      [*] = ;         posY := posY + yOff;
      [*] = ;         CreateSceneryListBox('prov_decor', 'gui|745', posX, posY, gProfileTmp.provincescenery);
      [*] = ;         
      [*] = ;         posY := posY + yOff;
      [*] = ;         CreateSceneryListBox('town_decor', 'gui|577', posX, posY, gProfileTmp.townscenery);
      [*] = ;         
      [*] = ;         posY := posY + yOff;
      [*] = ;         CreateSceneryListBox('battle_decor', 'gui|combat', posX, posY, gProfileTmp.battlescenery);
      [*] = ;         
      [*] = ;         posY := posY + 44;
      [*] = ;         const cBoxesCount = 3;
      [*] = ;         var i, tag, elmCheckBoxHandle : Integer;
      [*] = ;         var bChecked : Boolean;
      [*] = ;         var hint : String = '';
      [*] = ;         for i := 0 to cBoxesCount-1 do
      [*] = ;         begin
      [*] = ;            bChecked := False;
      [*] = ;            tag := cSceneryFlagsBaseTag+i;
      [*] = ;            case i of
      [*] = ;               0 : begin 
      [*] = ;                  text := GetLocaleTableListItemByID('gui','scenery') + ' (' + GetLocaleTableListItemByID('tutorial','70') + ')';
      [*] = ;                  bChecked := (gProfileTmp.objectflags and gc_ObjectFlagAstralDecor) = 0;
      [*] = ;               end;
      [*] = ;               1 : begin 
      [*] = ;                  text := GetLocaleTableListItemByID('gui','252') + ' (' + GetLocaleTableListItemByID('message','phud.131072') + ')';
      [*] = ;                  bChecked := (gProfileTmp.objectflags and gc_ObjectFlagRitual) = 0;
      [*] = ;               end;
      [*] = ;               2 : begin 
      [*] = ;                  text := GetLocaleTableListItemByID('gui','252') + ' (' + GetLocaleTableListItemByID('gui','combat') + ')';
      [*] = ;                  bChecked := (gProfileTmp.objectflags and gc_ObjectFlagBattleFX) = 0;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            elmCheckBoxHandle := _gui_CreateCheckBox('', elmSceneryHandle, bChecked, text, 'halParentLeft', 'valParentTop', cCheckBoxOffsetX, posY+20*i, cEventState, hint, tag);
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   cTabInterface :
      [*] = ;   begin
      [*] = ;      // Interface
      [*] = ;      var posX : Integer = iGroupPanelOffset2;
      [*] = ;      if (expandedWindow = cExpandedControls) or (expandedWindow = cExpandedProvinceHUD) or (expandedWindow = cExpandedMessages) then
      [*] = ;      posX := posX-242;
      [*] = ;      var posY : Integer = iGroupYOffset;
      [*] = ;      var elmInterfaceHandle : Integer = _gui_CreateImage('interface', elmParentHandle, 'element.strip.240', sGroupPanel0, 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmInterfaceHandle, 'menu|97', 'halParentLeft', 'valParentTop', 0, -2, GetGUIElementWidth(elmInterfaceHandle), GetGUIElementHeight(elmInterfaceHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;      var i, tag, elmCheckBoxHandle : Integer;
      [*] = ;      var bChecked : Boolean;
      [*] = ;      var hint,text : String;
      [*] = ;      
      [*] = ;      text := GetLocaleTableListItemByID('menu','96');
      [*] = ;      if expandedWindow = cExpandedControls then
      [*] = ;         text := text + '   <<'
      [*] = ;      else
      [*] = ;         text := text + '   >>';
      [*] = ;      elmCheckBoxHandle := _gui_CreateCheckBox('expand_controls', elmInterfaceHandle, expandedWindow = cExpandedControls, text, 'halParentLeft', 'valParentTop', cCheckBoxOffsetX, posY, cEventState, '', cCheckboxShowControls);
      [*] = ;      
      [*] = ;      posY := posY + 24;
      [*] = ;      text := GetLocaleTableListItemByID('gui','269');
      [*] = ;      if expandedWindow = cExpandedProvinceHUD then
      [*] = ;         text := text + '   <<'
      [*] = ;      else
      [*] = ;         text := text + '   >>';
      [*] = ;      elmCheckBoxHandle := _gui_CreateCheckBox('expand_provhud', elmInterfaceHandle, expandedWindow = cExpandedProvinceHUD, text, 'halParentLeft', 'valParentTop', cCheckBoxOffsetX, posY, cEventState, '', cCheckboxShowProvinceHUD);
      [*] = ;      
      [*] = ;      posY := posY + 24;
      [*] = ;      text := GetLocaleTableListItemByID('gui','407');
      [*] = ;      if expandedWindow = cExpandedMessages then
      [*] = ;         text := text + '   <<'
      [*] = ;      else
      [*] = ;         text := text + '   >>';
      [*] = ;      elmCheckBoxHandle := _gui_CreateCheckBox('expand_messages', elmInterfaceHandle, expandedWindow = cExpandedMessages, text, 'halParentLeft', 'valParentTop', cCheckBoxOffsetX, posY, cEventState, '', cCheckboxShowMessages);
      [*] = ;         
      [*] = ;      posY := posY + 26;
      [*] = ;      var elmSliderHandle : Integer = _gui_CreateSimpleSlider('exthintdelay', gProfileTmp.exthintdelay, elmInterfaceHandle, 'halParentLeft', 'valParentTop', 28, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmSliderHandle, 'menu|exthintdelay', 'halParentLeft', 'valParentTop', 29, -4, GetGUIElementWidth(elmSliderHandle), GetGUIElementHeight(elmSliderHandle), 'halLeft', 'valMiddle', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      
      [*] = ;      if expandedWindow = cExpandedControls then
      [*] = ;      begin
      [*] = ;         // Controls
      [*] = ;         posX := iGroupPanelOffset2;
      [*] = ;         posY := iGroupYOffset;
      [*] = ;         var elmMapScrollHandle : Integer = _gui_CreateImage('controls', elmParentHandle, 'element.strip.240', sGroupPanel2, 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;         elmTextHandle := _gui_CreateText('', elmMapScrollHandle, 'gui|411', 'halParentLeft', 'valParentTop', 0, -2, GetGUIElementWidth(elmMapScrollHandle), GetGUIElementHeight(elmMapScrollHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;         
      [*] = ;         posX := 20;
      [*] = ;         posY := 43;
      [*] = ;         var elmSliderHandle : Integer = _gui_CreateSimpleSlider('scrollspeed', gProfileTmp.scrollspeed, elmMapScrollHandle, 'halParentLeft', 'valParentTop', posX, posY, cEventState);
      [*] = ;         elmTextHandle := _gui_CreateText('', elmSliderHandle, 'menu|32', 'halParentLeft', 'valParentTop', 29, -4, GetGUIElementWidth(elmSliderHandle), GetGUIElementHeight(elmSliderHandle), 'halLeft', 'valMiddle', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;   
      [*] = ;         elmSliderHandle := _gui_CreateSimpleSlider('keyspeed', gProfileTmp.keyspeed, elmMapScrollHandle, 'halParentLeft', 'valParentTop', posX, posY+45*1, cEventState);
      [*] = ;         elmTextHandle := _gui_CreateText('', elmSliderHandle, 'menu|33', 'halParentLeft', 'valParentTop', 29, -4, GetGUIElementWidth(elmSliderHandle), GetGUIElementHeight(elmSliderHandle), 'halLeft', 'valMiddle', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;   
      [*] = ;         elmSliderHandle := _gui_CreateSimpleSlider('wheelspeed', gProfileTmp.wheelspeed, elmMapScrollHandle, 'halParentLeft', 'valParentTop', posX, posY+45*2, cEventState);
      [*] = ;         elmTextHandle := _gui_CreateText('', elmSliderHandle, 'menu|34', 'halParentLeft', 'valParentTop', 29, -4, GetGUIElementWidth(elmSliderHandle), GetGUIElementHeight(elmSliderHandle), 'halLeft', 'valMiddle', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;   
      [*] = ;         elmCheckBoxHandle := _gui_CreateCheckBox('', elmMapScrollHandle, gProfileTmp.clampingmouse, 'gui|749', 'halParentLeft', 'valParentTop', cCheckBoxOffsetX, posY+45*3+14+8, cEventState, 'gui|749.ext', cCheckboxClampingMouse);
      [*] = ;         {var i : Integer;
      [*] = ;         for i:=0 to 0 do
      [*] = ;         begin
      [*] = ;            var text : String;
      [*] = ;            case i of
      [*] = ;               0 : begin
      [*] = ;                  text := 'gui|411';
      [*] = ;               end;
      [*] = ;               1 : begin
      [*] = ;                  text := 'gui|412';
      [*] = ;               end;
      [*] = ;               2 : begin
      [*] = ;                  text := 'gui|413';
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            var elmMapScrollHandle : Integer = _gui_CreateImage('', elmControlsHandle, 'element.strip.240', sGroupPanel1, 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;            elmTextHandle := _gui_CreateText('', elmMapScrollHandle, 'gui|411', 'halParentLeft', 'valParentTop', 0, -2, GetGUIElementWidth(elmMapScrollHandle), GetGUIElementHeight(elmMapScrollHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;            if (i=0) then
      [*] = ;            begin
      [*] = ;               posX := 20;
      [*] = ;               posY := 35;
      [*] = ;               var elmSliderHandle : Integer = _gui_CreateSimpleSlider('scrollspeed', gProfileTmp.scrollspeed, elmMapScrollHandle, 'halParentLeft', 'valParentTop', posX, posY, cEventState);
      [*] = ;               elmTextHandle := _gui_CreateText('', elmSliderHandle, 'menu|32', 'halParentLeft', 'valParentTop', 29, -4, GetGUIElementWidth(elmSliderHandle), GetGUIElementHeight(elmSliderHandle), 'halLeft', 'valMiddle', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;   
      [*] = ;               elmSliderHandle := _gui_CreateSimpleSlider('keyspeed', gProfileTmp.keyspeed, elmMapScrollHandle, 'halParentLeft', 'valParentTop', posX, posY+45*1, cEventState);
      [*] = ;               elmTextHandle := _gui_CreateText('', elmSliderHandle, 'menu|33', 'halParentLeft', 'valParentTop', 29, -4, GetGUIElementWidth(elmSliderHandle), GetGUIElementHeight(elmSliderHandle), 'halLeft', 'valMiddle', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;   
      [*] = ;               elmSliderHandle := _gui_CreateSimpleSlider('wheelspeed', gProfileTmp.wheelspeed, elmMapScrollHandle, 'halParentLeft', 'valParentTop', posX, posY+45*2, cEventState);
      [*] = ;               elmTextHandle := _gui_CreateText('', elmSliderHandle, 'menu|34', 'halParentLeft', 'valParentTop', 29, -4, GetGUIElementWidth(elmSliderHandle), GetGUIElementHeight(elmSliderHandle), 'halLeft', 'valMiddle', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;   
      [*] = ;                elmCheckBoxHandle : Integer = _gui_CreateCheckBox('', elmMapScrollHandle, gProfileTmp.clampingmouse, 'gui|749', 'halParentLeft', 'valParentTop', cCheckBoxOffsetX, posY+45*3+14+8, cEventState, 'gui|749.ext', cCheckboxClampingMouse);
      [*] = ;            end;
      [*] = ;         end;}
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if expandedWindow = cExpandedProvinceHUD then
      [*] = ;      begin
      [*] = ;         // Province HUD
      [*] = ;         posX := iGroupPanelOffset2;
      [*] = ;         posY := iGroupYOffset;
      [*] = ;         var elmProvHUDHandle : Integer = _gui_CreateImage('provhud', elmParentHandle, 'element.strip.240', sGroupPanel2, 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;         elmTextHandle := _gui_CreateText('', elmProvHUDHandle, 'gui|269', 'halParentLeft', 'valParentTop', 0, -2, GetGUIElementWidth(elmProvHUDHandle), GetGUIElementHeight(elmProvHUDHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;         
      [*] = ;         const cBoxesCount = 12;
      [*] = ;         for i:=0 to cBoxesCount-1 do
      [*] = ;         begin
      [*] = ;            bChecked := False;
      [*] = ;            tag := cMapFlagsBaseTag+i;
      [*] = ;            case i of
      [*] = ;               0 : begin 
      [*] = ;                  text := GetLocaleTableListItemByID('tooltip','map_infopanel_province_name');
      [*] = ;                  hint := '';
      [*] = ;                  bChecked := (gProfileTmp.provHudFlags and gc_gui_provhudflag_name) > 0;
      [*] = ;               end;
      [*] = ;               1 : begin 
      [*] = ;                  text := 'message|33';
      [*] = ;                  hint := '';
      [*] = ;                  bChecked := (gProfileTmp.provHudFlags and gc_gui_provhudflag_type) > 0;
      [*] = ;               end;
      [*] = ;               2 : begin 
      [*] = ;                  text := 'gui|403';
      [*] = ;                  hint := '';
      [*] = ;                  bChecked := (gProfileTmp.provHudFlags and gc_gui_provhudflag_level) > 0;
      [*] = ;               end;
      [*] = ;               3 : begin 
      [*] = ;                  text := 'gui|421';
      [*] = ;                  hint := 'message|60.description';
      [*] = ;                  bChecked := (gProfileTmp.provHudFlags and gc_gui_provhudflag_overpop) > 0;
      [*] = ;               end;
      [*] = ;               4 : begin 
      [*] = ;                  text := 'gui|418';
      [*] = ;                  hint := 'message|57.description';
      [*] = ;                  bChecked := (gProfileTmp.provHudFlags and gc_gui_provhudflag_mood) > 0;
      [*] = ;               end;
      [*] = ;               5 : begin 
      [*] = ;                  text := 'gui|419';
      [*] = ;                  hint := 'message|58.description';
      [*] = ;                  bChecked := (gProfileTmp.provHudFlags and gc_gui_provhudflag_unrest) > 0;
      [*] = ;               end;
      [*] = ;               6 : begin 
      [*] = ;                  text := 'gui|420';
      [*] = ;                  hint := 'message|59.description';
      [*] = ;                  bChecked := (gProfileTmp.provHudFlags and gc_gui_provhudflag_guard) > 0;
      [*] = ;               end;
      [*] = ;               7 : begin 
      [*] = ;                  text := 'gui|422';
      [*] = ;                  hint := 'message|61.description';
      [*] = ;                  bChecked := (gProfileTmp.provHudFlags and gc_gui_provhudflag_quest) > 0;
      [*] = ;               end;
      [*] = ;               8 : begin 
      [*] = ;                  text := 'gui|423';
      [*] = ;                  hint := 'message|62.description';
      [*] = ;                  bChecked := (gProfileTmp.provHudFlags and gc_gui_provhudflag_arena) > 0;
      [*] = ;               end;
      [*] = ;               9 : begin 
      [*] = ;                  text := 'gui|424';
      [*] = ;                  hint := 'message|63.description';
      [*] = ;                  bChecked := (gProfileTmp.provHudFlags and gc_gui_provhudflag_shop) > 0;
      [*] = ;               end;
      [*] = ;               10 : begin 
      [*] = ;                  text := 'gui|425';
      [*] = ;                  hint := 'message|64.description';
      [*] = ;                  bChecked := (gProfileTmp.provHudFlags and gc_gui_provhudflag_lair) > 0;
      [*] = ;               end;
      [*] = ;               11 : begin 
      [*] = ;                  text := 'gui|426';
      [*] = ;                  hint := 'message|65.description';
      [*] = ;                  bChecked := (gProfileTmp.provHudFlags and gc_gui_provhudflag_temple) > 0;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            posX := 31;
      [*] = ;            posY := 43+20*i;
      [*] = ;            elmCheckBoxHandle := _gui_CreateCheckBox('', elmProvHUDHandle, bChecked, text , 'halParentLeft', 'valParentTop', cCheckBoxOffsetX, posY, cEventState, hint, tag);
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if expandedWindow = cExpandedMessages then
      [*] = ;      begin
      [*] = ;         // Messages
      [*] = ;         posX := iGroupPanelOffset2;
      [*] = ;         posY := iGroupYOffset;
      [*] = ;         var elmMessageHandle : Integer = _gui_CreateImage('messages', elmParentHandle, 'element.strip.240', sGroupPanel2, 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;         elmTextHandle := _gui_CreateText('', elmMessageHandle, 'gui|407', 'halParentLeft', 'valParentTop', 0, -2, GetGUIElementWidth(elmMessageHandle), GetGUIElementHeight(elmMessageHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;         
      [*] = ;         const cBoxesCount = 9;
      [*] = ;         for i:=0 to cBoxesCount-1 do
      [*] = ;         begin
      [*] = ;            bChecked := False;
      [*] = ;            hint := 'message|'+IntToStr(66+i)+'.description';
      [*] = ;            var text : String = 'gui|'+IntToStr(427+i);
      [*] = ;            var tag : Integer = cMessageFlagsBaseTag+i;
      [*] = ;            case i of
      [*] = ;               0 : bChecked := gProfileTmp.mestutor;
      [*] = ;               1 : bChecked := gProfileTmp.meslimitpopulation;
      [*] = ;               2 : bChecked := gProfileTmp.mesloafers;
      [*] = ;               3 : bChecked := gProfileTmp.messaleunits;
      [*] = ;               4 : bChecked := gProfileTmp.mesremoval;
      [*] = ;               5 : bChecked := gProfileTmp.mesdismisguard;
      [*] = ;               6 : bChecked := gProfileTmp.mesdestroybuilds;
      [*] = ;               7 : begin 
      [*] = ;                  text := 'message|107';
      [*] = ;                  hint := 'message|107.description';
      [*] = ;                  bChecked := gProfileTmp.mesbuildinner;
      [*] = ;               end;
      [*] = ;               8 : begin
      [*] = ;                  text := 'message|108';
      [*] = ;                  hint := 'message|108.description';
      [*] = ;                  bChecked := gProfileTmp.mesbuildouter;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            var posY : Integer = 43+20*i;
      [*] = ;            elmCheckBoxHandle := _gui_CreateCheckBox('', elmMessageHandle, bChecked, text, 'halParentLeft', 'valParentTop', cCheckBoxOffsetX, posY, cEventState, hint, tag);
      [*] = ;         end;
      [*] = ;         posY := 43+20*(cBoxesCount+1)-16;
      [*] = ;         elmSliderHandle := _gui_CreateSlider('mesbuildgold', gProfileTmp.mesbuildgold, IntToStr(Round(gProfileTmp.mesbuildgold * 100))+'% %style(Symbols)%0%style(default)%', elmMessageHandle, 'halParentLeft', 'valParentTop', cCheckBoxOffsetX-20, posY, 'EventSettings', 'message|109', 49, 3, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;         posY := posY + 46;
      [*] = ;         elmSliderHandle := _gui_CreateSlider('mesbuildgem', gProfileTmp.mesbuildgem, IntToStr(Round(gProfileTmp.mesbuildgem * 100))+'% %style(Symbols)%1%style(default)%', elmMessageHandle, 'halParentMiddle', 'valParentBottomHeight', cCheckBoxOffsetX-20, posY, 'EventSettings', 'message|110', 49, 3, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   cTabGameplay :
      [*] = ;   begin
      [*] = ;      // Gameplay
      [*] = ;      var posX : Integer = iGroupPanelOffset1;
      [*] = ;      var posY : Integer = iGroupYOffset;
      [*] = ;      var elmGameplayHandle : Integer = _gui_CreateImage('gameplay', elmParentHandle, 'element.strip.240', sGroupPanel1, 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmGameplayHandle, 'menu|89', 'halParentLeft', 'valParentTop', 0, -2, GetGUIElementWidth(elmGameplayHandle), GetGUIElementHeight(elmGameplayHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBox('autosave', elmGameplayHandle, 6, 6, 67, cEventState);
      [*] = ;      //var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('', elmGameplayHandle, gProfileTmp.autosave, 'menu|90', 'halParentLeft', 'valParentTop', cCheckBoxOffsetX, 43, cEventState, '', cCheckboxAutosave);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'menu|90', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
	   [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('gui', '414'), 0);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('menu', 'every_turn_1'), 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('menu', 'every_turn_2'), 2);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('menu', 'every_turn_3'), 3);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('menu', 'every_turn_5'), 5);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('menu', 'every_turn_10'), 10);
      [*] = ;      var curIndex : Integer = gProfileTmp.autosave;
      [*] = ;      if curIndex > 5 then
      [*] = ;      begin
      [*] = ;         curIndex := 10;
      [*] = ;         gProfileTmp.autosave := 10;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if curIndex > 3 then
      [*] = ;      begin
      [*] = ;         curIndex := 5;
      [*] = ;         gProfileTmp.autosave := 5;
      [*] = ;      end;
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, curIndex);
      [*] = ;      elmListBoxHandle := _gui_CreateListBox('autolvlup', elmGameplayHandle, 5, 6, 120, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'gui|412', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('gui', '414'), 0);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('gui', '656'), 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('gui', '657'), 2);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('gui', '658'), 3);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('gui', '416'), 4);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, gProfileTmp.autolvlup);
      [*] = ;      SetGUIElementHint(elmListBoxHandle, 'message|73.description');
      [*] = ;   
      [*] = ;      //elmListBoxHandle := _gui_CreateListBox('autocombat', elmGameplayHandle, 3, 6, 96+64, cEventState);
      [*] = ;      //elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'gui|413', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      //GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('gui', '414'), 0);
      [*] = ;      //GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('gui', '415'), 1);
      [*] = ;      //GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('gui', '416'), 2);
      [*] = ;      //SetGUIListBoxItemIndexSilent(elmListBoxHandle, gProfileTmp.autocombat);
      [*] = ;      //SetGUIElementHint(elmListBoxHandle, 'message|74.description');
      [*] = ;      
      [*] = ;      var bChecked : Boolean = gProfileTmp.improvedai;
      [*] = ;      var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('', elmGameplayHandle, bChecked, 'menu|improved_ai', 'halParentLeft', 'valParentTop', cCheckBoxOffsetX, 160, cEventState, 'menu|improved_ai.description', cCheckboxImprovedAI);
      [*] = ;   end;
      [*] = ;   cTabCombat :
      [*] = ;   begin
      [*] = ;      // Combat settings
      [*] = ;      var posX : Integer = iGroupPanelOffset1;
      [*] = ;      var posY : Integer = iGroupYOffset;
      [*] = ;      var elmCombatSettingsHandle : Integer = _gui_CreateImage('battle', elmParentHandle, 'element.strip.240', sGroupPanel1, 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmCombatSettingsHandle, 'menu|84', 'halParentLeft', 'valParentTop', 0, -2, GetGUIElementWidth(elmCombatSettingsHandle), GetGUIElementHeight(elmCombatSettingsHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;   
      [*] = ;      
      [*] = ;      // Battle speed sliders
      [*] = ;      var sBattlespeed : String = GetLocaleTableListItemByID('menu', '66');
      [*] = ;      var tmpStr : String = sBattlespeed + ' ('+GetLocaleTableListItemByID('gui','155')+')';
      [*] = ;      posX := 20;
      [*] = ;      posY := 35;
      [*] = ;      var elmSliderHandle : Integer = _gui_CreateSimpleSlider('battlespeed', gProfileTmp.battlespeed, elmCombatSettingsHandle, 'halParentLeft', 'valParentTop', posX, posY, cEventState);
      [*] = ;      _gui_CreateText('', elmSliderHandle, tmpStr, 'halParentLeft', 'valParentTop', 29, -4, GetGUIElementWidth(elmSliderHandle), GetGUIElementHeight(elmSliderHandle), 'halLeft', 'valMiddle', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      var elmKnob : Integer = GetGUIElementIndexByNameParent('btnSlider', elmSliderHandle);
      [*] = ;      SetGUIElementHint(elmKnob, IntToStr(Round(_misc_CalcBattleSpeedModifiedByValue(gProfileTmp.battlespeed, 10))));
      [*] = ;      SetGUIElementUserColor(elmKnob, gc_gui_fontcolor_RedR, gc_gui_fontcolor_RedG, gc_gui_fontcolor_RedB, 1);
      [*] = ;      if gProfileTmp.battlespeed >= 1 then
      [*] = ;         SetGUIElementUseUserColor(elmKnob, True);
      [*] = ;      
      [*] = ;      tmpStr := sBattlespeed + ' ('+GetLocaleTableListItemByID('hint','16')+')';
      [*] = ;      posX := 20;
      [*] = ;      posY := 80;
      [*] = ;      elmSliderHandle := _gui_CreateSimpleSlider('battlespeedally', gProfileTmp.battlespeedally, elmCombatSettingsHandle, 'halParentLeft', 'valParentTop', posX, posY, cEventState);
      [*] = ;      _gui_CreateText('', elmSliderHandle, tmpStr, 'halParentLeft', 'valParentTop', 29, -4, GetGUIElementWidth(elmSliderHandle), GetGUIElementHeight(elmSliderHandle), 'halLeft', 'valMiddle', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      elmKnob := GetGUIElementIndexByNameParent('btnSlider', elmSliderHandle);
      [*] = ;      SetGUIElementHint(elmKnob, IntToStr(Round(_misc_CalcBattleSpeedModifiedByValue(gProfileTmp.battlespeedally, 10))));
      [*] = ;      SetGUIElementUserColor(elmKnob, gc_gui_fontcolor_RedR, gc_gui_fontcolor_RedG, gc_gui_fontcolor_RedB, 1);
      [*] = ;      if gProfileTmp.battlespeedally >= 1 then
      [*] = ;         SetGUIElementUseUserColor(elmKnob, True);
      [*] = ;   
      [*] = ;      
      [*] = ;      // Info panels
      [*] = ;      posY := posY+64;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBox('warbar', elmCombatSettingsHandle, 3, 6, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'menu|58', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('menu', '59'), 0);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('menu', '60'), 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('menu', '61'), 2);
      [*] = ;      //GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('menu', '62'), 3);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, gProfileTmp.warbar);
      [*] = ;      //SetGUIElementHint(elmListBoxHandle, 'message|73.description');
      [*] = ;   
      [*] = ;      // Flytexts
      [*] = ;      posY := posY+54;
      [*] = ;      tmpStr := GetLocaleTableListItemByID('menu', '67') + ' ('+GetLocaleTableListItemByID('ability', '14')+')';
      [*] = ;      elmListBoxHandle := _gui_CreateListBox('flytext', elmCombatSettingsHandle, 3, 6, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, tmpStr, 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('menu', '59'), 0);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('menu', '60'), 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('menu', '61'), 2);
      [*] = ;      //GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('menu', '62'), 3);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, gProfileTmp.battle_flytext);
      [*] = ;   
      [*] = ;      // Hero spellcasting
      [*] = ;      posY := posY+54;
      [*] = ;      elmListBoxHandle := _gui_CreateListBox('warautospell', elmCombatSettingsHandle, 4, 6, posY, cEventState);
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'menu|71', 'halParentLeft', 'valParentTop', -4, -18, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('menu', '72'), 0);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('menu', '73'), 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('menu', '74'), 2);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('menu', '75'), 3);
      [*] = ;      SetGUIListBoxItemIndexSilent(elmListBoxHandle, gProfileTmp.warautospell);
      [*] = ;      //SetGUIElementHint(elmListBoxHandle, 'message|74.description');
      [*] = ;   
      [*] = ;      
      [*] = ;      // Checkboxes
      [*] = ;      const cBoxesCount = 3;
      [*] = ;      var i, tag, elmCheckBoxHandle : Integer;
      [*] = ;      var hint, name : String = '';
      [*] = ;      var bChecked : Boolean;
      [*] = ;      for i:=1 to cBoxesCount do
      [*] = ;      begin
      [*] = ;         tag := cCombatFlagsBaseTag+i;
      [*] = ;         case i of
      [*] = ;            //0 : begin
      [*] = ;               //   bChecked := gProfileTmp.warbar;
      [*] = ;               //   name := 'menu|58';
      [*] = ;            //end;
      [*] = ;            1 : begin
      [*] = ;               bChecked := gProfileTmp.wargrid;
      [*] = ;               name := 'menu|63';
      [*] = ;            end;
      [*] = ;            2 : begin
      [*] = ;               bChecked := gProfileTmp.brushunderunit;
      [*] = ;               name := 'menu|100';
      [*] = ;            end;
      [*] = ;            3 : begin
      [*] = ;               bChecked := gProfileTmp.warendturn;
      [*] = ;               name := 'menu|64';
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         posY := 33+20*(i-1)+260;
      [*] = ;         elmCheckBoxHandle := _gui_CreateCheckBox('', elmCombatSettingsHandle, bChecked, name, 'halParentLeft', 'valParentTop', cCheckBoxOffsetX, posY, cEventState, hint, tag);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   cTabInternet :
      [*] = ;   begin
      [*] = ;      // internet settings
      [*] = ;      var posX : Integer = iGroupPanelOffset1;
      [*] = ;      var posY : Integer = iGroupYOffset;
      [*] = ;      var elmInternetSettingsHandle : Integer = _gui_CreateImage('internet', elmParentHandle, 'element.strip.240', sGroupPanel1, 'valParentTop', posX, posY, 0, 0, 0);
      [*] = ;      var elmCheckBoxHandle : Integer = _gui_CreateCheckBox('', elmInternetSettingsHandle, gProfileTmp.serverautoconnect, 'menu|autoconnect', 'halParentLeft', 'valParentTop', cCheckBoxOffsetX, 43, cEventState, 'menu|autoconnect.description', cCheckboxAutoConnect);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmInternetSettingsHandle, 'menu|internet', 'halParentLeft', 'valParentTop', 0, -2, GetGUIElementWidth(elmInternetSettingsHandle), GetGUIElementHeight(elmInternetSettingsHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;   
      [*] = ;      posX := 6;
      [*] = ;      posY := 104;
      [*] = ;      var elmListBoxHandle : Integer = _gui_CreateListBox('chatnotifications', elmInternetSettingsHandle, 3, posX, posY, cEventState);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('gui', '414'), 0); //never
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('menu', 'private_message'), 1);
      [*] = ;      GUIListBoxAddItem(elmListBoxHandle, GetLocaleTableListItemByID('menu', 'any_message'), 2);
      [*] = ;      if gProfileTmp.chatnotifications >= 4 then
      [*] = ;         SetGUIListBoxItemIndexSilent(elmListBoxHandle, gProfileTmp.chatnotifications-4)
      [*] = ;      else
      [*] = ;         SetGUIListBoxItemIndexSilent(elmListBoxHandle, gProfileTmp.chatnotifications);
      [*] = ;      SetGUIElementHint(elmListBoxHandle, 'menu|chat_notifications');
      [*] = ;      elmTextHandle := _gui_CreateText('header', elmListBoxHandle, 'menu|chat_notifications', 'halParentLeft', 'valParentTop', posX-4, -24, GetGUIElementWidth(elmListBoxHandle), GetGUIElementHeight(elmListBoxHandle), 'halMiddle', 'valTop', fontHandle2, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;   
      [*] = ;      posY := posY + 38;
      [*] = ;      elmCheckBoxHandle := _gui_CreateCheckBox('newgame_notify', elmInternetSettingsHandle, ((gProfileTmp.chatnotifications and 4) > 0), 'menu|12', 'halParentLeft', 'valParentTop', cCheckBoxOffsetX, posY, cEventState, 'menu|open_game_notification', cCheckboxNotifyNewGame);
      [*] = ;      if not gProfileTmp.serverautoconnect then
      [*] = ;      begin
      [*] = ;         SetGUIElementUserBlend(elmListBoxHandle, 0.35);
      [*] = ;         SetGUIAllowEvents(elmListBoxHandle, False, False, False);
      [*] = ;         SetGUIElementUserBlend(elmCheckBoxHandle, 0.35);
      [*] = ;         SetGUIAllowEvents(elmCheckBoxHandle, False, False, False);
      [*] = ;      end;
      [*] = ;   
      [*] = ;      posX := 20;
      [*] = ;      posY := posY + 36;
      [*] = ;      var elmSliderHandle : Integer = _gui_CreateSimpleSlider('chatopacity', gProfileTmp.chatopacity, elmInternetSettingsHandle, 'halParentLeft', 'valParentTop', posX, posY, cEventState);
      [*] = ;      _gui_CreateText('', elmSliderHandle, 'menu|chat_opacity', 'halParentLeft', 'valParentTop', 29, -4, GetGUIElementWidth(elmSliderHandle), GetGUIElementHeight(elmSliderHandle), 'halLeft', 'valMiddle', fontHandle, gc_gui_fontcolor_BrownR, gc_gui_fontcolor_BrownG, gc_gui_fontcolor_BrownB, 1);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;   
      [*] = ;
      [*] = ;// Buttons OK/Cancel/Default
      [*] = ;var expandedOffSet : Integer;
      [*] = ;if expandedWindow > 0 then
      [*] = ;   expandedOffSet := -(242 div 2)
      [*] = ;else
      [*] = ;   expandedOffSet := 0;
      [*] = ;
      [*] = ;var elmHandle : Integer = _gui_CreateImage('', elmParentHandle, 'mainpanel.btnplace.with.frame', 'halParentMiddle', 'valParentBottom', -57-123+expandedOffSet, -32, 0, 0, 0);
      [*] = ;_gui_CreateButton('btnAccept', elmHandle, '', 'mainpanel.btn.accept', 'halParentLeft', 'valParentTop', 39, 0, 0, 0, cEventState, 'map.event|28.1', cBtnAcceptTag);
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'mainpanel.btnplace.with.frame', 'halParentMiddle', 'valParentBottom', 57-123+expandedOffSet, -32, 0, 0, 0);
      [*] = ;_gui_CreateButton('btnCancel', elmHandle, '', 'mainpanel.btn.cancel', 'halParentLeft', 'valParentTop', 39, 0, 0, 0, cEventState, 'map.event|28.2', cBtnCancelTag);
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'mainpanel.btnplace.with.frame', 'halParentMiddle', 'valParentBottom', 239-20-92+expandedOffSet, -32, 0, 0, 0);
      [*] = ;var hint : String;
      [*] = ;//if (gIntRegister_GUISettingTab=cTabVideo) then
      [*] = ;//   hint := 'menu|101' // autodetect
      [*] = ;//else
      [*] = ;   hint := 'gui|355';
      [*] = ;_gui_CreateButton('btnSetDefault', elmHandle, '', 'map.castle.tabs.btn.provincelist', 'halParentLeft', 'valParentTop', 39, 0, 0, 0, cEventState, hint, cBtnSetDefaultTag);
      [*] = ;
      [*] = ;if (not bVisible) then
      [*] = ;   _gui_FadeElement(elmParentHandle, gc_gui_FadeTime0_2, true, true, true);
      [*] = ;
      [*] = ;gIntRegister_GUIScrollSliderHandle := 0;
      [*] = ;_gui_RootWindowAdd(elmParentHandle,cRootWindowModal);
      [*] = ;SetGUIElementPressState(elmParentHandle, cEventState);
      [*] = ;GUIExecuteState('GUIInvokeMouseMove');
   struct.end
section.end

