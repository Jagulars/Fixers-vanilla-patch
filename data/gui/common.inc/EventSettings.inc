section.begin
   Name = EventSettings
   Code : struct.begin
      [*] = ;var pConfig : Integer = _misc_ParserGetOrCreateByKey('Config',false);
      [*] = ;if (ParserGetCountByHandle(pConfig)=0) then
      [*] = ;   ParserLoadFromFileByHandle(pConfig,'.\data\resources\config.res');
      [*] = ;
      [*] = ;procedure UpdateProvResHUD(bTemporary : Boolean);
      [*] = ;begin
      [*] = ;   var provHudFlags : Integer = gProfile.provhudflags;
      [*] = ;   if (bTemporary) then
      [*] = ;      gProfile.provhudflags := gProfileTmp.provhudflags;
      [*] = ;   
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to ParserGetCountByHandle(gStratHexCells.handle)-1 do
      [*] = ;   begin
      [*] = ;      var pStratHexCell : Integer = ParserSelectByHandleByIndex(gStratHexCells.handle, i);
      [*] = ;      IntRegister0 := pStratHexCell;
      [*] = ;      GUIExecuteState('map.GUIUpdateResHUD');
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (bTemporary) then
      [*] = ;      gProfile.provhudflags := provHudFlags;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure SetupVideoPreset(pConfig : Integer; value : String);
      [*] = ;begin
      [*] = ;   if (pConfig<>0) then
      [*] = ;   begin
      [*] = ;      var pEngine : Integer = ParserSelectByHandleByKey(pConfig, 'engine');
      [*] = ;      if (pEngine<>0) then
      [*] = ;      begin
      [*] = ;         var pEngineConfigs : Integer = ParserSelectByHandleByKey(pEngine, 'config');
      [*] = ;         if (pEngineConfigs<>0) then
      [*] = ;         begin
      [*] = ;            var pEngineConfig : Integer = ParserSelectByHandleByIndex(pEngineConfigs, ParserFindChildIndexByEqualChildKey('Name', value));
      [*] = ;            if (pEngineConfig<>0) then
      [*] = ;            begin
      [*] = ;               var pGui : Integer = ParserSelectByHandleByKey(pEngineConfig, 'Gui');
      [*] = ;               if (pGui<>0) then
      [*] = ;               begin
      [*] = ;                  var pOnClick : Integer = ParserSelectByHandleByKey(pGui, 'OnClick');
      [*] = ;                  if (pOnClick<>0) then
      [*] = ;                  begin
      [*] = ;                     gVideoSettingsTmp.hdrtype := ParserGetValueByKeyByHandle(pOnClick, gc_ProjOptionsHDRType);
      [*] = ;                     gVideoSettingsTmp.shadertype := ParserGetValueByKeyByHandle(pOnClick, gc_ProjOptionsShaderType);
      [*] = ;                     gVideoSettingsTmp.antialiasing := ParserGetValueByKeyByHandle(pOnClick, gc_ProjOptionsAntiAliasing);
      [*] = ;                     gVideoSettingsTmp.texturefilter := ParserGetValueByKeyByHandle(pOnClick, gc_ProjOptionsTextureFilter);
      [*] = ;                     gVideoSettingsTmp.waterreflection := ParserGetValueByKeyByHandle(pOnClick, gc_ProjOptionsWaterReflection);
      [*] = ;                     gVideoSettingsTmp.shadowenabled := ParserGetBoolValueByKeyByHandle(pOnClick, gc_ProjOptionsShadowEnabled);
      [*] = ;                     gProfileTmp.simplegraphics := ParserGetBoolValueByKeyByHandle(pOnClick, 'SimpleGraphics');
      [*] = ;                     gProfileTmp.objectflags := ParserGetIntValueByKeyByHandle(pOnClick, 'ObjectFlags');
      [*] = ;                     gProfileTmp.shardscenery := ParserGetIntValueByKeyByHandle(pOnClick, 'ShardScenery');
      [*] = ;                     gProfileTmp.townscenery := ParserGetIntValueByKeyByHandle(pOnClick, 'TownScenery');
      [*] = ;                     gProfileTmp.provincescenery := ParserGetIntValueByKeyByHandle(pOnClick, 'ProvinceScenery');
      [*] = ;                     gProfileTmp.battlescenery := ParserGetIntValueByKeyByHandle(pOnClick, 'BattleScenery');
      [*] = ;
      [*] = ;                     if (GetProjectOptionAsString(gc_ProjOptionsAntiAliasing)<>gVideoSettingsTmp.antialiasing)
      [*] = ;                     or (GetProjectOptionAsString(gc_ProjOptionsTextureFilter)<>gVideoSettingsTmp.texturefilter)
      [*] = ;                     or (GetProjectOptionAsString(gc_ProjOptionsShaderType)<>gVideoSettingsTmp.shadertype)
      [*] = ;                     or (GetProjectOptionAsString(gc_ProjOptionsWaterReflection)<>gVideoSettingsTmp.waterreflection)
      [*] = ;                     or (GetProjectOptionAsBoolean(gc_ProjOptionsShadowEnabled)<>gVideoSettingsTmp.shadowenabled) then
      [*] = ;                     begin
      [*] = ;                        CadencerProgress;
      [*] = ;                        ViewerBufferRender;
      [*] = ;                     end;
      [*] = ;
      [*] = ;                     if (GetProjectOptionAsString(gc_ProjOptionsAntiAliasing)<>gVideoSettingsTmp.antialiasing) then
      [*] = ;                        SetProjectOptionAsString(gc_ProjOptionsAntiAliasing, gVideoSettingsTmp.antialiasing);
      [*] = ;                     if (GetProjectOptionAsString(gc_ProjOptionsTextureFilter)<>gVideoSettingsTmp.texturefilter) then
      [*] = ;                        SetProjectOptionAsString(gc_ProjOptionsTextureFilter, gVideoSettingsTmp.texturefilter);
      [*] = ;                     if (GetProjectOptionAsString(gc_ProjOptionsShaderType)<>gVideoSettingsTmp.shadertype) then
      [*] = ;                     begin
      [*] = ;                        SetProjectOptionAsString(gc_ProjOptionsShaderType, gVideoSettingsTmp.shadertype);
      [*] = ;                        if gVideoSettingsTmp.shadertype <> 'stNone' then
      [*] = ;                           gProfileTmp.simplegraphics := False; // shaders should be disabled with imposters
      [*] = ;                     end;
      [*] = ;                     if (GetProjectOptionAsString(gc_ProjOptionsWaterReflection)<>gVideoSettingsTmp.waterreflection) then
      [*] = ;                        SetProjectOptionAsString(gc_ProjOptionsWaterReflection, gVideoSettingsTmp.waterreflection);
      [*] = ;
      [*] = ;                     _gui_SetProjectOptionsHDRType(gVideoSettingsTmp.hdrtype);
      [*] = ;
      [*] = ;                     if (GetProjectOptionAsBoolean(gc_ProjOptionsShadowEnabled)<>gVideoSettingsTmp.shadowenabled) then
      [*] = ;                        SetProjectOptionAsBoolean(gc_ProjOptionsShadowEnabled, gVideoSettingsTmp.shadowenabled);
      [*] = ;                  end;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;procedure RecalcPreset();
      [*] = ;begin
      [*] = ;   _gui_CreateVideoPresetListBox(0, 0);
      [*] = ;end;
      [*] = ;
      [*] = ;var sPress  : String = GetValueByName('Press');
      [*] = ;var sStatus  : String = GetValueByName('Status');
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;var status : String = GetValueByName('Status');
      [*] = ;var uElmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var uElmName : String =  GetGUIElementNameByIndex(uElmHandle);
      [*] = ;
      [*] = ;var elmSliderHandle : Integer;
      [*] = ;if (gIntRegister_GUIScrollSliderHandle<>0) then
      [*] = ;elmSliderHandle := gIntRegister_GUIScrollSliderHandle
      [*] = ;else
      [*] = ;elmSliderHandle := GetGUIElementParentByIndex(uElmHandle);
      [*] = ;var sliderID : String = GetGUIElementStringTag(elmSliderHandle);
      [*] = ;
      [*] = ;if (uElmName='btnSlider') or (uElmName='lineSlider') then
      [*] = ;begin
      [*] = ;   if (status='geMouseDown') then
      [*] = ;   begin
      [*] = ;      gIntRegister_GUIScrollSliderHandle := elmSliderHandle;
      [*] = ;
      [*] = ;      var mX, my : Integer;
      [*] = ;      GetGUICurrentMouseCoord(mX, mY);
      [*] = ;      var x2, y2 : Integer;
      [*] = ;      GUIInvalidateParentPositions(uElmHandle);
      [*] = ;      GetGUIElementAlignPosition(uElmHandle, x2, y2);
      [*] = ;      SetIntValueByName('SliderElementDragX', mX-x2);
      [*] = ;      SetIntValueByName('SliderElementDragY', mY-y2);
      [*] = ;      GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gIntRegister_GUIScrollSliderHandle<>0) or ((sPress='d') and (uElmName='lineSlider')) then
      [*] = ;begin
      [*] = ;   SetIntValueByName('SliderElementDragX', 14);
      [*] = ;   var value : Float = _gui_ModifySliderValueByMouseCoord(elmSliderHandle);
      [*] = ;   case sliderID of
      [*] = ;      'sndmaster' : begin
      [*] = ;         gProfileTmp.sndmaster := value;
      [*] = ;         SetProjectOptionAsFloat('Sound.Master', gProfileTmp.sndmaster);
      [*] = ;      end;
      [*] = ;      'sndmusic' : begin
      [*] = ;         gProfileTmp.sndmusic := value;
      [*] = ;         SetProjectOptionAsFloat('svgMusic', gProfileTmp.sndmusic);
      [*] = ;      end;
      [*] = ;      'sndambient' : begin
      [*] = ;         gProfileTmp.sndambient := value;
      [*] = ;         SetProjectOptionAsFloat('svgAmbient', gProfileTmp.sndambient);
      [*] = ;      end;
      [*] = ;      'sndfx' : begin
      [*] = ;         gProfileTmp.sndfx := value;
      [*] = ;         SetProjectOptionAsFloat('svgSFX', gProfileTmp.sndfx);
      [*] = ;      end;
      [*] = ;      //'sndvoice' : begin
      [*] = ;         //   gProfileTmp.sndvoice := value;
      [*] = ;         //   SetProjectOptionAsFloat('svgVoice', gProfileTmp.sndvoice);
      [*] = ;      //end;
      [*] = ;      'sndinterface' : begin
      [*] = ;         gProfileTmp.sndinterface := value;
      [*] = ;         SetProjectOptionAsFloat('svgInterface', gProfileTmp.sndinterface);
      [*] = ;      end;
      [*] = ;      'scrollspeed' : gProfileTmp.scrollspeed := value;
      [*] = ;      'keyspeed' : gProfileTmp.keyspeed := value;
      [*] = ;      'wheelspeed' : gProfileTmp.wheelspeed := value;
      [*] = ;      'battlespeed' : begin
      [*] = ;         gProfileTmp.battlespeed := value;
      [*] = ;         var elmKnob : Integer = GetGUIElementIndexByNameParent('btnSlider', elmSliderHandle);
      [*] = ;         SetGUIElementHint(elmKnob, IntToStr(Round(_misc_CalcBattleSpeedModifiedByValue(gProfileTmp.battlespeed, 10))));
      [*] = ;         if gProfileTmp.battlespeed >= 1 then
      [*] = ;            SetGUIElementUseUserColor(elmKnob, True)
      [*] = ;         else
      [*] = ;            SetGUIElementUseUserColor(elmKnob, False);
      [*] = ;      end;
      [*] = ;      'battlespeedally' : begin
      [*] = ;         gProfileTmp.battlespeedally := value;
      [*] = ;         var elmKnob : Integer = GetGUIElementIndexByNameParent('btnSlider', elmSliderHandle);
      [*] = ;         SetGUIElementHint(elmKnob, IntToStr(Round(_misc_CalcBattleSpeedModifiedByValue(gProfileTmp.battlespeedally, 10))));
      [*] = ;         if gProfileTmp.battlespeedally >= 1 then
      [*] = ;            SetGUIElementUseUserColor(elmKnob, True)
      [*] = ;         else
      [*] = ;            SetGUIElementUseUserColor(elmKnob, False);
      [*] = ;      end;
      [*] = ;      'exthintdelay' : gProfileTmp.exthintdelay := value;
      [*] = ;      'chatopacity' : begin
      [*] = ;         gProfileTmp.chatopacity := value;
      [*] = ;         if gIntRegister_AstralChatMode = 0 then //update opacity in real time
      [*] = ;         begin
      [*] = ;            var storedOpacity : Float = gProfile.chatopacity;
      [*] = ;            gProfile.chatopacity := value;
      [*] = ;            IntRegister0 := 0;
      [*] = ;            GUIExecuteState('ShowAstralChat');
      [*] = ;            gProfile.chatopacity := storedOpacity;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      'mesbuildgold' : begin
      [*] = ;         gProfileTmp.mesbuildgold := value;
      [*] = ;         _gui_SetSliderText(elmSliderHandle, IntToStr(Round(value * 100))+'% %style(Symbols)%0%style(default)%');
      [*] = ;      end;
      [*] = ;      'mesbuildgem' : begin
      [*] = ;         gProfileTmp.mesbuildgem := value;
      [*] = ;         _gui_SetSliderText(elmSliderHandle, IntToStr(Round(value * 100))+'% %style(Symbols)%1%style(default)%');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
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
      [*] = ;const cExpandedMessages = 4;
      [*] = ;
      [*] = ;procedure GetTabElementName(var sTab : String);
      [*] = ;begin
      [*] = ;   case gIntRegister_GUISettingTab of
      [*] = ;      cTabSound : sTab := 'sound';
      [*] = ;      cTabVideo : sTab := 'video';
      [*] = ;      cTabInterface : sTab := 'interface';
      [*] = ;      cTabGameplay : sTab := 'gameplay';
      [*] = ;      cTabCombat : sTab := 'battle';
      [*] = ;      cTabInternet : sTab := 'internet';
      [*] = ;      else sTab := '';
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (sPress='c') and ((uElmName=gc_ProjOptionsVSyncMode) or (uElmName=gc_ProjOptionsHDRType) or (uElmName=gc_ProjOptionsShadowEnabled)) then
      [*] = ;begin
      [*] = ;   var stringTag : String = GetGUIElementStringTag(uElmHandle);
      [*] = ;   var delimiterStringCount : Integer = GetDelimiterStringCount(stringTag, gc_gui_DelimiterChar, gc_gui_QuoteChar);
      [*] = ;   var value0, value1, newValue : String = '';
      [*] = ;   if (IsDelimiterCharExists(stringTag, gc_gui_DelimiterChar)) and (delimiterStringCount>=2) then
      [*] = ;   begin
      [*] = ;      value0 := GetDelimiterStringByIndex(stringTag, gc_gui_DelimiterChar, gc_gui_QuoteChar, 0);
      [*] = ;      value1 := GetDelimiterStringByIndex(stringTag, gc_gui_DelimiterChar, gc_gui_QuoteChar, 1);
      [*] = ;   end;
      [*] = ;   case uElmName of
      [*] = ;      gc_ProjOptionsVSyncMode : begin
      [*] = ;         var bChecked : Boolean = (not GetGUIElementChecked(uElmHandle));
      [*] = ;         if (bChecked) then
      [*] = ;         newValue := value1
      [*] = ;         else
      [*] = ;         newValue := value0;
      [*] = ;         gVideoSettingsTmp.vsyncmode := newValue;
      [*] = ;         SetGUIElementChecked(uElmHandle, bChecked);
      [*] = ;         SetProjectOptionAsString(gc_ProjOptionsVSyncMode, newValue);
      [*] = ;      end;
      [*] = ;      gc_ProjOptionsHDRType : begin
      [*] = ;         var bChecked : Boolean = (not GetGUIElementChecked(uElmHandle));
      [*] = ;         if (bChecked) then
      [*] = ;         newValue := value1
      [*] = ;         else
      [*] = ;         newValue := value0;
      [*] = ;         gVideoSettingsTmp.hdrtype := newValue;
      [*] = ;         SetGUIElementChecked(uElmHandle, bChecked);
      [*] = ;         _gui_SetProjectOptionsHDRType(newValue);
      [*] = ;         RecalcPreset();
      [*] = ;      end;
      [*] = ;      gc_ProjOptionsShadowEnabled : begin
      [*] = ;         var bChecked : Boolean = (not GetGUIElementChecked(uElmHandle));
      [*] = ;         gVideoSettingsTmp.shadowenabled := bChecked;
      [*] = ;         SetGUIElementChecked(uElmHandle, bChecked);
      [*] = ;         SetProjectOptionAsBoolean(gc_ProjOptionsShadowEnabled, bChecked);
      [*] = ;         RecalcPreset();
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;if (sStatus='select') and (sPress<>'d') then // listbox selection
      [*] = ;begin
      [*] = ;   procedure SwitchListBox(var value : Integer; parentName : String);
      [*] = ;   begin
      [*] = ;      if parentName = '' then
      [*] = ;         GetTabElementName(parentName);
      [*] = ;      var elmListBoxHandle : Integer = _gui_GetWindow('Settings.' +parentName+ '.' + uElmName);
      [*] = ;      value := GetGUIListBoxItemTag(elmListBoxHandle, GetGUIListBoxItemIndex(elmListBoxHandle));
      [*] = ;   end;
      [*] = ;   case uElmName of
      [*] = ;      'autosave' : SwitchListBox(gProfileTmp.autosave, '');
      [*] = ;      'autolvlup' : SwitchListBox(gProfileTmp.autolvlup, '');
      [*] = ;      'autocombat' : SwitchListBox(gProfileTmp.autocombat, '');
      [*] = ;      'warautospell' : SwitchListBox(gProfileTmp.warautospell, '');
      [*] = ;      'flytext' : SwitchListBox(gProfileTmp.battle_flytext, '');
      [*] = ;      'warbar' : begin
      [*] = ;         SwitchListBox(gProfileTmp.warbar, '');
      [*] = ;
      [*] = ;         if (gIntRegister_CurGameMode=gc_GameModeTactics) then
      [*] = ;         begin
      [*] = ;            var tmp : Boolean = gProfile.brushunderunit;
      [*] = ;            gProfile.brushunderunit := gProfileTmp.brushunderunit;
      [*] = ;            var tmp2 : Boolean = gProfile.wargrid;
      [*] = ;            gProfile.wargrid := gProfileTmp.wargrid;
      [*] = ;            var tmp3 : Integer = gProfile.warbar;
      [*] = ;            gProfile.warbar := gProfileTmp.warbar;
      [*] = ;
      [*] = ;            GUIExecuteState('battle.UnitHUDControl');
      [*] = ;            gProfile.brushunderunit := tmp;
      [*] = ;            gProfile.wargrid := tmp2;
      [*] = ;            gProfile.warbar := tmp3;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      'chatnotifications' : begin
      [*] = ;         var listBoxValue : Integer;
      [*] = ;         SwitchListBox(listBoxValue, '');
      [*] = ;         gProfileTmp.chatnotifications := (listBoxValue or (gProfileTmp.chatnotifications and 4));
      [*] = ;      end;
      [*] = ;      'shard_decor' : begin 
      [*] = ;         SwitchListBox(gProfileTmp.shardscenery, 'scenery');
      [*] = ;         RecalcPreset();
      [*] = ;      end;
      [*] = ;      'prov_decor' : begin 
      [*] = ;         SwitchListBox(gProfileTmp.provincescenery, 'scenery');
      [*] = ;         RecalcPreset();
      [*] = ;      end;
      [*] = ;      'town_decor' : begin 
      [*] = ;         SwitchListBox(gProfileTmp.townscenery, 'scenery');
      [*] = ;         RecalcPreset();
      [*] = ;      end;
      [*] = ;      'battle_decor' : begin 
      [*] = ;         SwitchListBox(gProfileTmp.battlescenery, 'scenery');
      [*] = ;         RecalcPreset();
      [*] = ;      end;
      [*] = ;      gc_ProjOptionsResolution : // Video Resolution
      [*] = ;      begin
      [*] = ;         var elmListBoxHandle : Integer = _gui_GetWindow('Settings.video.'+gc_ProjOptionsResolution);
      [*] = ;         var i : Integer = GetGUIListBoxItemTag(elmListBoxHandle, GetGUIListBoxItemIndex(elmListBoxHandle));
      [*] = ;         if (i > 0) and (i <> GetCurrentResolutionMode) then
      [*] = ;         begin
      [*] = ;            _misc_ParserGetOrCreateByKey('settings_fullscreen',true);
      [*] = ;            ParserSetIntValueByKey('mode', GetCurrentResolutionMode);
      [*] = ;            gIntRegister_GUIRouteOnGUIRestart := 2;
      [*] = ;            gBoolRegister_GUIStartup := true;
      [*] = ;            if (GetDisplayMode <> 'dmWindow') and (GetDisplayMode <> 'dmWindowFullScreen') then
      [*] = ;               SetFullScreenMode(i);
      [*] = ;            NeedRestartGUI();
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var stringTag : String = GetGUIElementStringTag(uElmHandle);
      [*] = ;         if (stringTag<>'') then
      [*] = ;         begin
      [*] = ;            tag := GetGUIElementTag(uElmHandle);
      [*] = ;            var ind : Integer = GetGUIListBoxItemIndex(uElmHandle);
      [*] = ;            var value : String = '';
      [*] = ;   
      [*] = ;            var delimiterStringCount : Integer = GetDelimiterStringCount(stringTag, gc_gui_DelimiterChar, gc_gui_QuoteChar);
      [*] = ;            if (IsDelimiterCharExists(stringTag, gc_gui_DelimiterChar)) and (delimiterStringCount>=(ind-1)) then
      [*] = ;            value := GetDelimiterStringByIndex(stringTag, gc_gui_DelimiterChar, gc_gui_QuoteChar, ind);
      [*] = ;   
      [*] = ;            case uElmName of
      [*] = ;               gc_ProjOptionsLightChange : begin
      [*] = ;                  gProfileTmp.lightchange := StrToInt(value);
      [*] = ;                  var tmp : Integer = gProfile.lightchange;
      [*] = ;                  gProfile.lightchange := gProfileTmp.lightchange;
      [*] = ;                  if (gProfileTmp.lightchange>2) then
      [*] = ;                  SetMapFloatValue('LightTime', 0);
      [*] = ;                  ExecuteState('DoBlendLighting');
      [*] = ;                  gProfile.lightchange := tmp;
      [*] = ;               end;
      [*] = ;               gc_ProjOptionsPreset : begin
      [*] = ;                  if (gVideoSettingsTmp.preset<>value) then
      [*] = ;                  begin
      [*] = ;                     gVideoSettingsTmp.preset := value;
      [*] = ;                     SetupVideoPreset(pConfig, gVideoSettingsTmp.preset);
      [*] = ;                     GUIExecuteState('ShowSettings');
      [*] = ;                  end;
      [*] = ;                  //_gui_DelayExecuteStateOneInstance('ShowSettings', gc_gui_FadeTime0_2);
      [*] = ;                  //var delayIndex : Integer = GUIDelayTimeExecFind('ShowSettings');
      [*] = ;                  //GUIDelayTimeExecDelete(delayIndex, False);
      [*] = ;                  //_gui_DelayExecuteStateOneInstance('ShowSettings', gc_gui_FadeTime0_2);
      [*] = ;                  //SetValueByName(sStatus, '');
      [*] = ;               end;
      [*] = ;               gc_ProjOptionsAntiAliasing : begin
      [*] = ;                  gVideoSettingsTmp.antialiasing := value;
      [*] = ;                  SetProjectOptionAsString(gc_ProjOptionsAntiAliasing, value);
      [*] = ;                  RecalcPreset();
      [*] = ;               end;
      [*] = ;               gc_ProjOptionsTextureFilter : begin
      [*] = ;                  //SetGUICursorByName('crHourGlass');
      [*] = ;                  gVideoSettingsTmp.texturefilter := value;
      [*] = ;                  SetProjectOptionAsString(gc_ProjOptionsTextureFilter, value);
      [*] = ;                  //SetGUICursorByName('crDefault');
      [*] = ;                  RecalcPreset();
      [*] = ;               end;
      [*] = ;               gc_ProjOptionsShaderType : begin
      [*] = ;                  gVideoSettingsTmp.shadertype := value;
      [*] = ;                  SetProjectOptionAsString(gc_ProjOptionsShaderType, value);
      [*] = ;                  RecalcPreset();
      [*] = ;               end;
      [*] = ;               gc_ProjOptionsWaterReflection : begin
      [*] = ;                  gVideoSettingsTmp.waterreflection := value;
      [*] = ;                  SetProjectOptionAsString(gc_ProjOptionsWaterReflection, value);
      [*] = ;                  RecalcPreset();
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;if (sPress='c') and (gIntRegister_GUIScrollSliderHandle=0) then
      [*] = ;begin
      [*] = ;   if (sliderID='') then
      [*] = ;   begin
      [*] = ;      if (tag >= cMapFlagsBaseTag) and (tag < cMapFlagsBaseTag+100) then
      [*] = ;      begin
      [*] = ;         var ind : Integer = tag-cMapFlagsBaseTag;
      [*] = ;         var bChecked : Boolean = (not GetGUIElementChecked(uElmHandle));
      [*] = ;         
      [*] = ;         var bitFlag : Integer;
      [*] = ;         case ind of
      [*] = ;            0 : bitFlag := gc_gui_provhudflag_name;
      [*] = ;            1 : bitFlag := gc_gui_provhudflag_type;
      [*] = ;            2 : bitFlag := gc_gui_provhudflag_level;
      [*] = ;            3 : bitFlag := gc_gui_provhudflag_overpop;
      [*] = ;            4 : bitFlag := gc_gui_provhudflag_mood;
      [*] = ;            5 : bitFlag := gc_gui_provhudflag_unrest;
      [*] = ;            6 : bitFlag := gc_gui_provhudflag_guard;
      [*] = ;            7 : bitFlag := gc_gui_provhudflag_quest;
      [*] = ;            8 : bitFlag := gc_gui_provhudflag_arena;
      [*] = ;            9 : bitFlag := gc_gui_provhudflag_shop;
      [*] = ;            10 : bitFlag := gc_gui_provhudflag_lair;
      [*] = ;            11 : bitFlag := gc_gui_provhudflag_temple;
      [*] = ;         end;
      [*] = ;         gProfileTmp.provHudFlags := gProfileTmp.provHudFlags xor bitFlag;
      [*] = ;         
      [*] = ;         SetGUIElementChecked(uElmHandle, bChecked);
      [*] = ;
      [*] = ;         if (gIntRegister_CurGameMode=gc_GameModeStrategy) then
      [*] = ;            UpdateProvResHUD(True);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (tag >= cMessageFlagsBaseTag) and (tag < cMessageFlagsBaseTag+100) then
      [*] = ;      begin
      [*] = ;         var ind : Integer = tag-cMessageFlagsBaseTag;
      [*] = ;         var bChecked : Boolean = (not GetGUIElementChecked(uElmHandle));
      [*] = ;         case ind of
      [*] = ;            0 : gProfileTmp.mestutor := bChecked;
      [*] = ;            1 : gProfileTmp.meslimitpopulation := bChecked;
      [*] = ;            2 : gProfileTmp.mesloafers := bChecked;
      [*] = ;            3 : gProfileTmp.messaleunits := bChecked;
      [*] = ;            4 : gProfileTmp.mesremoval := bChecked;
      [*] = ;            5 : gProfileTmp.mesdismisguard := bChecked;
      [*] = ;            6 : gProfileTmp.mesdestroybuilds := bChecked;
      [*] = ;            7 : gProfileTmp.mesbuildinner := bChecked;
      [*] = ;            8 : gProfileTmp.mesbuildouter := bChecked;
      [*] = ;         end;
      [*] = ;         SetGUIElementChecked(uElmHandle, bChecked);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (tag >= cCombatFlagsBaseTag) and (tag < cCombatFlagsBaseTag+100) then
      [*] = ;      begin
      [*] = ;         var ind : Integer = tag-cCombatFlagsBaseTag;
      [*] = ;         var bChecked : Boolean = (not GetGUIElementChecked(uElmHandle));
      [*] = ;         case ind of
      [*] = ;            //0 : begin
      [*] = ;               //   gProfileTmp.warbar := bChecked;
      [*] = ;               //
      [*] = ;               //   var tmp : Boolean = gProfile.brushunderunit;
      [*] = ;               //   gProfile.brushunderunit := gProfileTmp.brushunderunit;
      [*] = ;               //   var tmp2 : Boolean = gProfile.wargrid;
      [*] = ;               //   gProfile.wargrid := gProfileTmp.wargrid;
      [*] = ;               //   var tmp3 : Boolean = gProfile.warbar;
      [*] = ;               //   gProfile.warbar := gProfileTmp.warbar;
      [*] = ;               //
      [*] = ;               //   ExecuteState('battle.UnitHUDControl');
      [*] = ;               //   gProfile.brushunderunit := tmp;
      [*] = ;               //   gProfile.wargrid := tmp2;
      [*] = ;               //   gProfile.warbar := tmp3;
      [*] = ;            //end;
      [*] = ;            1 : begin
      [*] = ;               gProfileTmp.wargrid := bChecked;
      [*] = ;               if (gIntRegister_CurGameMode=gc_GameModeTactics) then
      [*] = ;               begin
      [*] = ;                  var tmp : Boolean = gProfile.brushunderunit;
      [*] = ;                  gProfile.brushunderunit := gProfileTmp.brushunderunit;
      [*] = ;                  var tmp2 : Boolean = gProfile.wargrid;
      [*] = ;                  gProfile.wargrid := gProfileTmp.wargrid;
      [*] = ;                  var tmp3 : Integer = gProfile.warbar;
      [*] = ;                  gProfile.warbar := gProfileTmp.warbar;
      [*] = ;                  
      [*] = ;                  GUIExecuteState('battle.DoDrawHexGrid');						   
      [*] = ;                  gProfile.brushunderunit := tmp;
      [*] = ;                  gProfile.wargrid := tmp2;
      [*] = ;                  gProfile.warbar := tmp3;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            2 : begin
      [*] = ;               gProfileTmp.brushunderunit := bChecked;
      [*] = ;
      [*] = ;               if (gIntRegister_CurGameMode=gc_GameModeTactics) then
      [*] = ;               begin
      [*] = ;                  var tmp : Boolean = gProfile.brushunderunit;
      [*] = ;                  gProfile.brushunderunit := gProfileTmp.brushunderunit;
      [*] = ;                  var tmp2 : Boolean = gProfile.wargrid;
      [*] = ;                  gProfile.wargrid := gProfileTmp.wargrid;
      [*] = ;                  var tmp3 : Integer = gProfile.warbar;
      [*] = ;                  gProfile.warbar := gProfileTmp.warbar;
      [*] = ;
      [*] = ;                  GUIExecuteState('battle.DoDrawHexGrid');
      [*] = ;                  gProfile.brushunderunit := tmp;
      [*] = ;                  gProfile.wargrid := tmp2;
      [*] = ;                  gProfile.warbar := tmp3;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            3 : begin
      [*] = ;               gProfileTmp.warendturn := bChecked;
      [*] = ;               if (gIntRegister_CurGameMode=gc_GameModeTactics) then
      [*] = ;               begin
      [*] = ;                  if (gProfileTmp.warendturn) then
      [*] = ;                  begin
      [*] = ;                     var elmBlinkElement : Integer = _gui_GetWindow('blinker_top.blink_battle_endturn');
      [*] = ;                     if elmBlinkElement <> 0 then
      [*] = ;                        RemoveGUIElement(elmBlinkElement);
      [*] = ;                  end
      [*] = ;                  else
      [*] = ;                     GUIExecuteState('battle.CreateControlPanelWindow');
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         SetGUIElementChecked(uElmHandle, bChecked);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      if (tag >= cSceneryFlagsBaseTag) and (tag < cSceneryFlagsBaseTag+100) then
      [*] = ;      begin
      [*] = ;         var ind : Integer = tag-cSceneryFlagsBaseTag;
      [*] = ;         var bChecked : Boolean = (not GetGUIElementChecked(uElmHandle));
      [*] = ;         SetGUIElementChecked(uElmHandle, bChecked);
      [*] = ;         
      [*] = ;         var bitFlag : Integer;
      [*] = ;         case ind of
      [*] = ;            0 : bitFlag := gc_ObjectFlagAstralDecor;
      [*] = ;            1 : bitFlag := gc_ObjectFlagRitual;
      [*] = ;            2 : bitFlag := gc_ObjectFlagBattleFX;
      [*] = ;         end;
      [*] = ;         gProfileTmp.objectflags := gProfileTmp.objectflags xor bitFlag;
      [*] = ;         RecalcPreset();
      [*] = ;      end
      [*] = ;      else
      [*] = ;      case tag of
      [*] = ;         cSwitchResolutionApprove : begin
      [*] = ;            GUIExecuteState('ShowSettings');
      [*] = ;         end;
      [*] = ;         cSwitchResolutionCancel : begin
      [*] = ;            var parser : Integer = _misc_ParserGetOrCreateByKey('settings_fullscreen',false);
      [*] = ;            gIntRegister_GUIRouteOnGUIRestart := 1;
      [*] = ;            gBoolRegister_GUIStartup := true;
      [*] = ;            if (GetDisplayMode <> 'dmWindow') and (GetDisplayMode <> 'dmWindowFullScreen') then
      [*] = ;               SetFullScreenMode(ParserGetIntValueByKeyByHandle(parser,'mode'));
      [*] = ;            NeedRestartGUI();
      [*] = ;            GUIExecuteState('ShowSettings');
      [*] = ;         end;
      [*] = ;         cCheckboxMute : begin
      [*] = ;            var bChecked : Boolean = (not GetGUIElementChecked(uElmHandle));
      [*] = ;            if (bChecked) then
      [*] = ;               gProfileTmp.sndmute := 1
      [*] = ;            else
      [*] = ;               gProfileTmp.sndmute := 0;
      [*] = ;            SetSoundManagerMuteMode('svgInterface', (gProfileTmp.sndmute=1));
      [*] = ;            SetSoundManagerMuteMode('svgAmbient', (gProfileTmp.sndmute=1));
      [*] = ;            SetSoundManagerMuteMode('svgMusic', (gProfileTmp.sndmute=1));
      [*] = ;            SetSoundManagerMuteMode('svgSFX', (gProfileTmp.sndmute=1));
      [*] = ;            SetSoundManagerMuteMode('svgVoice', (gProfileTmp.sndmute=1));
      [*] = ;            SetGUIElementChecked(uElmHandle, bChecked);
      [*] = ;         end;
      [*] = ;         cCheckboxClampingMouse : begin
      [*] = ;            var bChecked : Boolean = (not GetGUIElementChecked(uElmHandle));
      [*] = ;            if (bChecked) then
      [*] = ;               gProfileTmp.clampingmouse := True
      [*] = ;            else
      [*] = ;               gProfileTmp.clampingmouse  := False;
      [*] = ;            SetGUIElementChecked(uElmHandle, bChecked);
      [*] = ;         end;
      [*] = ;         cCheckboxShowAdvanced : begin
      [*] = ;            var bChecked : Boolean = (not GetGUIElementChecked(uElmHandle));
      [*] = ;            SetGUIElementChecked(uElmHandle, bChecked);
      [*] = ;            if bChecked then
      [*] = ;               SetGUIElementChecked(GetGUIElementIndexByNameParent('expand_scenery', GetGUIElementParentByIndex(uElmHandle)), False);
      [*] = ;            
      [*] = ;            gIntRegister_GUISettingTab := cTabVideo;
      [*] = ;            GUIExecuteState('ShowSettings');
      [*] = ;         end;
      [*] = ;         cCheckboxShowScenery : begin
      [*] = ;            var bChecked : Boolean = not GetGUIElementChecked(uElmHandle);
      [*] = ;            SetGUIElementChecked(uElmHandle, bChecked);
      [*] = ;            if bChecked then
      [*] = ;               SetGUIElementChecked(GetGUIElementIndexByNameParent('expand_advancedvideo', GetGUIElementParentByIndex(uElmHandle)), False);
      [*] = ;            
      [*] = ;            gIntRegister_GUISettingTab := cTabVideo;
      [*] = ;            GUIExecuteState('ShowSettings');
      [*] = ;         end;
      [*] = ;         cCheckboxShowControls : begin
      [*] = ;            var bChecked : Boolean = not GetGUIElementChecked(uElmHandle);
      [*] = ;            SetGUIElementChecked(uElmHandle, bChecked);
      [*] = ;            if bChecked then
      [*] = ;            begin
      [*] = ;               SetGUIElementChecked(GetGUIElementIndexByNameParent('expand_provhud', GetGUIElementParentByIndex(uElmHandle)), False);
      [*] = ;               SetGUIElementChecked(GetGUIElementIndexByNameParent('expand_messages', GetGUIElementParentByIndex(uElmHandle)), False);
      [*] = ;            end;
      [*] = ;            
      [*] = ;            gIntRegister_GUISettingTab := cTabInterface;
      [*] = ;            GUIExecuteState('ShowSettings');
      [*] = ;         end;
      [*] = ;         cCheckboxShowProvinceHUD : begin
      [*] = ;            var bChecked : Boolean = not GetGUIElementChecked(uElmHandle);
      [*] = ;            SetGUIElementChecked(uElmHandle, bChecked);
      [*] = ;            if bChecked then
      [*] = ;            begin
      [*] = ;               SetGUIElementChecked(GetGUIElementIndexByNameParent('expand_controls', GetGUIElementParentByIndex(uElmHandle)), False);
      [*] = ;               SetGUIElementChecked(GetGUIElementIndexByNameParent('expand_messages', GetGUIElementParentByIndex(uElmHandle)), False);
      [*] = ;            end;
      [*] = ;            
      [*] = ;            gIntRegister_GUISettingTab := cTabInterface;
      [*] = ;            GUIExecuteState('ShowSettings');
      [*] = ;         end;
      [*] = ;         cCheckboxShowMessages : begin
      [*] = ;            var bChecked : Boolean = not GetGUIElementChecked(uElmHandle);
      [*] = ;            SetGUIElementChecked(uElmHandle, bChecked);
      [*] = ;            if bChecked then
      [*] = ;            begin
      [*] = ;               SetGUIElementChecked(GetGUIElementIndexByNameParent('expand_controls', GetGUIElementParentByIndex(uElmHandle)), False);
      [*] = ;               SetGUIElementChecked(GetGUIElementIndexByNameParent('expand_provhud', GetGUIElementParentByIndex(uElmHandle)), False);
      [*] = ;            end;
      [*] = ;            
      [*] = ;            gIntRegister_GUISettingTab := cTabInterface;
      [*] = ;            GUIExecuteState('ShowSettings');
      [*] = ;         end;
      [*] = ;         cCheckboxSimpleGraphics : begin
      [*] = ;            var bChecked : Boolean = not GetGUIElementChecked(uElmHandle);
      [*] = ;            SetGUIElementChecked(uElmHandle, bChecked);
      [*] = ;            gProfileTmp.simplegraphics := bChecked;
      [*] = ;            if bChecked and (gVideoSettingsTmp.shadertype<>'stNone') then
      [*] = ;            begin
      [*] = ;               gVideoSettingsTmp.shadertype := 'stNone'; // shaders should be disabled with imposters
      [*] = ;            end;
      [*] = ;            RecalcPreset();
      [*] = ;         end;
      [*] = ;         //cCheckboxBell : begin
      [*] = ;         //   var bChecked : Boolean = (not GetGUIElementChecked(uElmHandle));
      [*] = ;         //   if (bChecked) then
      [*] = ;         //      gProfileTmp.bell := True
      [*] = ;         //   else
      [*] = ;         //      gProfileTmp.bell  := False;
      [*] = ;         //   SetGUIElementChecked(uElmHandle, bChecked);
      [*] = ;         //end;
      [*] = ;         cBtnAcceptTag, gc_gui_hotkey_btnEnter : 
      [*] = ;         begin
      [*] = ;            var sceneryFlags : Integer = _obj_GetCheckSceneryFlags(gProfileTmp.objectflags, gProfileTmp.shardscenery, gProfileTmp.townscenery, gProfileTmp.provincescenery, gProfileTmp.battlescenery);
      [*] = ;            var bCheckSimplifiedGraphics : Boolean = (gProfile.simplegraphics <> gProfileTmp.simplegraphics);
      [*] = ;            
      [*] = ;            if (gProfileTmp.provincescenery >= gc_ProvincePopulationSceneryLimit) and (gProfile.provincescenery < gc_ProvincePopulationSceneryLimit) then // when hiding province occupation buildings, turn on the type icons
      [*] = ;               gProfileTmp.provhudflags := gProfileTmp.provhudflags or gc_gui_provhudflag_type;
      [*] = ;            
      [*] = ;            gIntRegister_GUIScrollSliderHandle := 0;
      [*] = ;            _misc_AssignGlobalVars('gProfileTmp', 'gProfile');
      [*] = ;            _misc_AssignGlobalVars('gVideoSettingsTmp', 'gVideoSettings');
      [*] = ;            
      [*] = ;            if (gProfileTmp.chatnotifications = 0) or (not gProfileTmp.serverautoconnect) then
      [*] = ;            begin
      [*] = ;               var chatBlink : Boolean;
      [*] = ;               _gui_RemoveBlinkElement('btnOpenChatBlink', chatBlink);
      [*] = ;            end;
      [*] = ;            
      [*] = ;            if (not gProfile.serverautoconnect) and (gProfileTmp.serverautoconnect) and (not IsLanPublicServerMode()) then
      [*] = ;            begin
      [*] = ;               gConnectIPIndex := 0;
      [*] = ;               GUIExecuteState('DoLanConnect');
      [*] = ;            end
      [*] = ;            else 
      [*] = ;            if (not gProfileTmp.serverautoconnect) and (IsLanPublicServerMode) and (gIntRegister_AstralChatMode = 1) and (GetLanMode = 0) then
      [*] = ;            begin
      [*] = ;               LanShutdown();
      [*] = ;               LanPublicServerLeave();
      [*] = ;            end;
      [*] = ;            
      [*] = ;            //if (gIntRegister_AstralChatMode = 0) then
      [*] = ;            //begin
      [*] = ;            //   //_gui_RootWindowRemoveWithFade(_gui_GetWindow('internetshell'),0);
      [*] = ;            //   IntRegister0 := 0;
      [*] = ;            //   GUIExecuteState('ShowAstralChat');
      [*] = ;            //end;
      [*] = ;            
      [*] = ;            _prof_SaveUserProfile;
      [*] = ;            UserSaveProfile;
      [*] = ;            
      [*] = ;            _gui_RootWindowRemoveWithFade(_gui_GetWindow('Settings'),gc_gui_FadeTime0_2);
      [*] = ;            
      [*] = ;            if (gIntRegister_CurGameMode=gc_GameModeMenu) then
      [*] = ;               _gui_DelayExecuteStateOneInstance('ShowMenu', gc_gui_FadeTime0_2);
      [*] = ;            if (gIntRegister_CurGameMode=gc_GameModeTactics) then //combat settings
      [*] = ;               GUIExecuteState('battle.DoDrawHexGrid');
      [*] = ;            
      [*] = ;            SetProjectOptionAsFloat('Sound.Master', gProfile.sndmaster);
      [*] = ;            SetProjectOptionAsFloat('svgMusic', gProfile.sndmusic);
      [*] = ;            SetProjectOptionAsFloat('svgAmbient', gProfile.sndambient);
      [*] = ;            SetProjectOptionAsFloat('svgSFX', gProfile.sndfx);
      [*] = ;            //SetProjectOptionAsFloat('svgVoice', gProfile.sndvoice);
      [*] = ;            SetProjectOptionAsFloat('svgInterface', gProfile.sndinterface);
      [*] = ;            
      [*] = ;            SetProjectOptionAsString(gc_ProjOptionsAntiAliasing, gVideoSettings.antialiasing);
      [*] = ;            _gui_SetProjectOptionsHDRType(gVideoSettings.hdrtype);
      [*] = ;            SetProjectOptionAsString(gc_ProjOptionsVSyncMode, gVideoSettings.vsyncmode);
      [*] = ;            SetProjectOptionAsBoolean(gc_ProjOptionsShadowEnabled, gVideoSettings.shadowenabled);
      [*] = ;            SetProjectOptionAsString(gc_ProjOptionsTextureFilter, gVideoSettings.texturefilter);
      [*] = ;            SetProjectOptionAsString(gc_ProjOptionsShaderType, gVideoSettings.shadertype);
      [*] = ;            SetProjectOptionAsString(gc_ProjOptionsWaterReflection, gVideoSettings.waterreflection);
      [*] = ;
      [*] = ;            _misc_ParserGetOrCreateByKey('Config',true);
      [*] = ;         
      [*] = ;            if (sceneryFlags > 0) then
      [*] = ;            begin
      [*] = ;               IntRegister0 := sceneryFlags;
      [*] = ;               ExecuteState('CheckScenery');
      [*] = ;            end;
      [*] = ;            if bCheckSimplifiedGraphics then
      [*] = ;               _actor_CheckSimplifiedGraphics();
      [*] = ;
      [*] = ;            if (gIntRegister_CurGameMode=gc_GameModeStrategy) then
      [*] = ;               UpdateProvResHUD(False);
      [*] = ;         end;
      [*] = ;         cBtnCancelTag, gc_gui_hotkey_btnEscape : 
      [*] = ;         begin
      [*] = ;            gIntRegister_GUIScrollSliderHandle := 0;
      [*] = ;            _misc_AssignGlobalVars('gProfile', 'gProfileTmp');
      [*] = ;            _misc_AssignGlobalVars('gVideoSettings', 'gVideoSettingsTmp');
      [*] = ;            
      [*] = ;            _gui_RootWindowRemoveWithFade(_gui_GetWindow('Settings'),gc_gui_FadeTime0_2);
      [*] = ;            
      [*] = ;            if (gIntRegister_CurGameMode=gc_GameModeMenu) then
      [*] = ;               _gui_DelayExecuteStateOneInstance('ShowMenu', gc_gui_FadeTime0_2);
      [*] = ;            if (gIntRegister_CurGameMode=gc_GameModeTactics) then //combat settings
      [*] = ;               GUIExecuteState('battle.DoDrawHexGrid');
      [*] = ;            
      [*] = ;            SetProjectOptionAsFloat('Sound.Master', gProfile.sndmaster);
      [*] = ;            SetProjectOptionAsFloat('svgMusic', gProfile.sndmusic);
      [*] = ;            SetProjectOptionAsFloat('svgAmbient', gProfile.sndambient);
      [*] = ;            SetProjectOptionAsFloat('svgSFX', gProfile.sndfx);
      [*] = ;            //SetProjectOptionAsFloat('svgVoice', gProfile.sndvoice);
      [*] = ;            SetProjectOptionAsFloat('svgInterface', gProfile.sndinterface);
      [*] = ;
      [*] = ;            SetProjectOptionAsString(gc_ProjOptionsAntiAliasing, gVideoSettings.antialiasing);
      [*] = ;            _gui_SetProjectOptionsHDRType(gVideoSettings.hdrtype);
      [*] = ;            SetProjectOptionAsString(gc_ProjOptionsVSyncMode, gVideoSettings.vsyncmode);
      [*] = ;            SetProjectOptionAsBoolean(gc_ProjOptionsShadowEnabled, gVideoSettings.shadowenabled);
      [*] = ;            SetProjectOptionAsString(gc_ProjOptionsTextureFilter, gVideoSettings.texturefilter);
      [*] = ;            SetProjectOptionAsString(gc_ProjOptionsShaderType, gVideoSettings.shadertype);
      [*] = ;            SetProjectOptionAsString(gc_ProjOptionsWaterReflection, gVideoSettings.waterreflection);
      [*] = ;
      [*] = ;            if (gIntRegister_AstralChatMode = 0) then
      [*] = ;            begin
      [*] = ;               //_gui_RootWindowRemoveWithFade(_gui_GetWindow('internetshell'),0);
      [*] = ;               IntRegister0 := 0;
      [*] = ;               GUIExecuteState('ShowAstralChat');
      [*] = ;            end;
      [*] = ;
      [*] = ;            _misc_ParserGetOrCreateByKey('Config',true);
      [*] = ;
      [*] = ;            if (gIntRegister_CurGameMode=gc_GameModeStrategy) then
      [*] = ;               UpdateProvResHUD(False);
      [*] = ;         end;
      [*] = ;         cBtnSetDefaultTag : 
      [*] = ;         begin
      [*] = ;            gIntRegister_GUIScrollSliderHandle := 0;
      [*] = ;            if (gIntRegister_GUISettingTab = cTabVideo) then
      [*] = ;            begin
      [*] = ;               gVideoSettingsTmp.preset := gc_ProjOptionsPresetMedium; // TODO : HATE : DO AUTODETECT HERE
      [*] = ;               SetupVideoPreset(pConfig, gVideoSettingsTmp.preset);
      [*] = ;            end
      [*] = ;            else
      [*] = ;               _prof_SetGameOptionsDefault(gProfileTmp, gIntRegister_GUISettingTab);
      [*] = ;            GUIExecuteState('ShowSettings');
      [*] = ;
      [*] = ;            if (gIntRegister_GUISettingTab = cTabCombat) and (gIntRegister_CurGameMode=gc_GameModeTactics) then
      [*] = ;            begin
      [*] = ;               var tmp : Boolean = gProfile.brushunderunit;
      [*] = ;               gProfile.brushunderunit := gProfileTmp.brushunderunit;
      [*] = ;               var tmp2 : Boolean = gProfile.wargrid;
      [*] = ;               gProfile.wargrid := gProfileTmp.wargrid;
      [*] = ;               var tmp3 : Integer = gProfile.warbar;
      [*] = ;               gProfile.warbar := gProfileTmp.warbar;
      [*] = ;
      [*] = ;               GUIExecuteState('battle.UnitHUDControl');
      [*] = ;               GUIExecuteState('battle.DoDrawHexGrid');
      [*] = ;               gProfile.brushunderunit := tmp;
      [*] = ;               gProfile.wargrid := tmp2;
      [*] = ;               gProfile.warbar := tmp3;
      [*] = ;            end;
      [*] = ;            SetProjectOptionAsFloat('Sound.Master', gProfileTmp.sndmaster);
      [*] = ;            SetProjectOptionAsFloat('svgMusic', gProfileTmp.sndmusic);
      [*] = ;            SetProjectOptionAsFloat('svgAmbient', gProfileTmp.sndambient);
      [*] = ;            SetProjectOptionAsFloat('svgSFX', gProfileTmp.sndfx);
      [*] = ;            //SetProjectOptionAsFloat('svgVoice', gProfileTmp.sndvoice);
      [*] = ;            SetProjectOptionAsFloat('svgInterface', gProfileTmp.sndinterface);
      [*] = ;            SetSoundManagerMuteMode('svgInterface', (gProfileTmp.sndmute=1));
      [*] = ;            SetSoundManagerMuteMode('svgAmbient', (gProfileTmp.sndmute=1));
      [*] = ;            SetSoundManagerMuteMode('svgMusic', (gProfileTmp.sndmute=1));
      [*] = ;            SetSoundManagerMuteMode('svgSFX', (gProfileTmp.sndmute=1));
      [*] = ;            SetSoundManagerMuteMode('svgVoice', (gProfileTmp.sndmute=1));
      [*] = ;         end;
      [*] = ;         cCheckboxAutoConnect : 
      [*] = ;         begin
      [*] = ;            var bChecked : Boolean = (not GetGUIElementChecked(uElmHandle));
      [*] = ;            if (bChecked) then
      [*] = ;               gProfileTmp.serverautoconnect := True
      [*] = ;            else
      [*] = ;               gProfileTmp.serverautoconnect := False;
      [*] = ;            
      [*] = ;            SetGUIElementChecked(uElmHandle, bChecked);
      [*] = ;            
      [*] = ;            var elmNotifHandle : Integer = GetGUIElementIndexByNameParent('Settings.internet.chatnotifications', _gui_GetLayerI()); // No messages can be received when not connected anyway.
      [*] = ;            SetGUIAllowEvents(elmNotifHandle, bChecked, False, False);
      [*] = ;            if bChecked then
      [*] = ;               SetGUIElementUserBlend(elmNotifHandle, 1.0)
      [*] = ;            else
      [*] = ;               SetGUIElementUserBlend(elmNotifHandle, 0.35);
      [*] = ;            
      [*] = ;            elmNotifHandle := GetGUIElementIndexByNameParent('Settings.internet.newgame_notify', _gui_GetLayerI()); 
      [*] = ;            SetGUIAllowEvents(elmNotifHandle, bChecked, False, False);
      [*] = ;            if bChecked then
      [*] = ;               SetGUIElementUserBlend(elmNotifHandle, 1.0)
      [*] = ;            else
      [*] = ;               SetGUIElementUserBlend(elmNotifHandle, 0.35);
      [*] = ;         end;
      [*] = ;         cCheckboxNotifyNewGame : begin
      [*] = ;            var bChecked : Boolean = (not GetGUIElementChecked(uElmHandle));
      [*] = ;            if (bChecked) then
      [*] = ;               gProfileTmp.chatnotifications := gProfileTmp.chatnotifications + 4
      [*] = ;            else
      [*] = ;               gProfileTmp.chatnotifications := gProfileTmp.chatnotifications - 4;
      [*] = ;            
      [*] = ;            SetGUIElementChecked(uElmHandle, bChecked);
      [*] = ;         end;
      [*] = ;         cCheckboxImprovedAI : begin
      [*] = ;            var bChecked : Boolean = (not GetGUIElementChecked(uElmHandle));
      [*] = ;            if (bChecked) then
      [*] = ;               gProfileTmp.improvedai := True
      [*] = ;            else
      [*] = ;               gProfileTmp.improvedai := False;
      [*] = ;            
      [*] = ;            SetGUIElementChecked(uElmHandle, bChecked);
      [*] = ;         end;
      [*] = ;         cBtnSound : begin
      [*] = ;            gIntRegister_GUISettingTab := cTabSound;
      [*] = ;            GUIExecuteState('ShowSettings');
      [*] = ;         end;
      [*] = ;         cBtnVideo : begin
      [*] = ;            gIntRegister_GUISettingTab := cTabVideo;
      [*] = ;            GUIExecuteState('ShowSettings');
      [*] = ;         end;
      [*] = ;         cBtnInterface : begin
      [*] = ;            gIntRegister_GUISettingTab := cTabInterface;
      [*] = ;            GUIExecuteState('ShowSettings');
      [*] = ;         end;
      [*] = ;         cBtnGameplay : begin
      [*] = ;            gIntRegister_GUISettingTab := cTabGameplay;
      [*] = ;            GUIExecuteState('ShowSettings');
      [*] = ;         end;
      [*] = ;         cBtnCombat : begin
      [*] = ;            gIntRegister_GUISettingTab := cTabCombat;
      [*] = ;            GUIExecuteState('ShowSettings');
      [*] = ;         end;
      [*] = ;         cBtnInternet : begin
      [*] = ;            gIntRegister_GUISettingTab := cTabInternet;
      [*] = ;            GUIExecuteState('ShowSettings');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

