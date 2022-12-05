section.begin
   Name = ShowMapGeneratorSettings
   UsedFileName =
   Code : struct.begin
      [*] = ;var bInet : Boolean = (gGame.gametype=gc_GameTypeLanShard);
      [*] = ;var bHotseat : Boolean = ((gGame.gameType=gc_GameTypeHotseat) and (gGame.gametype <> gc_GameTypeLanShard));
      [*] = ;var bMaster : Boolean = (not bInet) or bHotSeat or ((bInet) and (GetLanMode()>=2));
      [*] = ;
      [*] = ;// Check if window was already visible, then no need to FadeIn it when show again
      [*] = ;var prevElmParentHandle : Integer = GetGUIElementIndexByNameParent('MapGeneratorSettings', _gui_GetLayerI());
      [*] = ;var bVisible : Boolean = False;
      [*] = ;if (prevElmParentHandle<>0) and GetGUIElementVisible(prevElmParentHandle) then
      [*] = ;   bVisible := True;
      [*] = ;
      [*] = ;var elmParentHandle : Integer = _gui_CreateLargeWindow(0, 'MapGeneratorSettings', 'halParentMiddle', 'valParentMiddle', 0, 0, 730{830 for window with bottom background}, 489, false);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('background', elmParentHandle), 0.65+0.3);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('frame', elmParentHandle), 0.75+0.1);
      [*] = ;
      [*] = ;// ��������� ������������ ����
      [*] = ;var elmHeaderHandle : Integer = GetGUIElementIndexByNameParent('header', elmParentHandle);
      [*] = ;var fontHandle, fontHandle2 : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_small,'',fontHandle);   // HeaderS
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_largest,'',fontHandle2); // NormalL
      [*] = ;var elmTextHandle : Integer = _gui_CreateText('', elmHeaderHandle, 'gui|356', 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHeaderHandle), GetGUIElementHeight(elmHeaderHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;// Body
      [*] = ;const cEventState = 'EventMapGeneratorSettings';
      [*] = ;var localeID : Integer = 357;
      [*] = ;var i, j : Integer;
      [*] = ;for i:=0 to 2 do
      [*] = ;begin
      [*] = ;   for j:=0 to 3 do
      [*] = ;   begin
      [*] = ;      var valueCount : Integer = 5; // starting from 0
      [*] = ;      var sliderID : String;
      [*] = ;      var ind : Integer = (j*10+i);
      [*] = ;      var hint : String;
      [*] = ;      var value : Float = 0;
      [*] = ;      case ind of
      [*] = ;         0 : begin
      [*] = ;            localeID := 357;
      [*] = ;            valueCount := 2; // starting from 0
      [*] = ;            hint := 'message|95.description';
      [*] = ;         end;
      [*] = ;         1 : begin
      [*] = ;            localeID := 655;
      [*] = ;            sliderID := 'wastelands';
      [*] = ;            hint := 'menu|35';
      [*] = ;            value := gMapSettingsTmp.wastelands;
      [*] = ;         end;
      [*] = ;         2 : begin
      [*] = ;            localeID := 365;
      [*] = ;            sliderID := 'population';
      [*] = ;            hint := 'message|103.description';
      [*] = ;            value := gMapSettingsTmp.population;
      [*] = ;         end;
      [*] = ;         10 : begin
      [*] = ;            localeID := 358;
      [*] = ;            sliderID := 'isles';
      [*] = ;            hint := 'message|96.description';
      [*] = ;            value := gMapSettingsTmp.isles;
      [*] = ;         end;
      [*] = ;         11 : begin
      [*] = ;            localeID := 362;
      [*] = ;            sliderID := 'forest';
      [*] = ;            hint := 'message|100.description';
      [*] = ;            value := gMapSettingsTmp.forest;
      [*] = ;         end;
      [*] = ;         12 : begin
      [*] = ;            localeID := 366;
      [*] = ;            sliderID := 'neutrals';
      [*] = ;            hint := 'message|104.description';
      [*] = ;            value := gMapSettingsTmp.neutrals;
      [*] = ;         end;
      [*] = ;         20 : begin
      [*] = ;            localeID := 359;
      [*] = ;            sliderID := 'dissolve';
      [*] = ;            hint := 'message|97.description';
      [*] = ;            value := gMapSettingsTmp.dissolve;
      [*] = ;         end;
      [*] = ;         21 : begin
      [*] = ;            localeID := 363;
      [*] = ;            sliderID := 'hill';
      [*] = ;            hint := 'message|101.description';
      [*] = ;            value := gMapSettingsTmp.hill;
      [*] = ;         end;
      [*] = ;         22 : begin
      [*] = ;            localeID := 367;
      [*] = ;            sliderID := 'resource';
      [*] = ;            hint := 'message|105.description';
      [*] = ;            value := gMapSettingsTmp.resource;
      [*] = ;         end;
      [*] = ;         30 : begin
      [*] = ;            localeID := 361;
      [*] = ;            sliderID := 'water';
      [*] = ;            hint := 'message|99.description';
      [*] = ;            value := gMapSettingsTmp.water;
      [*] = ;         end;
      [*] = ;         31 : begin
      [*] = ;            localeID := 364;
      [*] = ;            sliderID := 'swamp';
      [*] = ;            hint := 'message|102.description';
      [*] = ;            value := gMapSettingsTmp.swamp;
      [*] = ;         end;
      [*] = ;         32 : begin
      [*] = ;            localeID := 368;
      [*] = ;            sliderID := 'site';
      [*] = ;            hint := 'message|106.description';
      [*] = ;            value := gMapSettingsTmp.site;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      var text : String = 'gui|'+IntToStr(localeID);
      [*] = ;      localeID := localeID+1;
      [*] = ;      var tmpX : Integer = 2+i*243;
      [*] = ;      var tmpY : Integer = 30+j*101;
      [*] = ;      var elmHandle : Integer = _gui_CreateImage('', elmParentHandle, 'element.strip.240', 'halParentLeft', 'valParentTop', tmpX, tmpY, 0, 0, 0);
      [*] = ;      elmTextHandle := _gui_CreateText('', elmHandle, text, 'halParentLeft', 'valParentTop', 0, -2, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;      if (ind=0) then
      [*] = ;      begin
      [*] = ;         var elmSliderHandle : Integer = _gui_CreateIntSlider('type', elmParentHandle, 'halParentLeft', 'valParentTop', tmpX, tmpY+38, 228, cEventState, hint, 49, 3, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;         var intValue : Integer = gMapSettingsTmp.typ;
      [*] = ;         case intValue of
      [*] = ;            0 : text := 'gui|384';
      [*] = ;            1 : text := 'gui|383';
      [*] = ;         end;
      [*] = ;         _gui_SetSliderIntValue(elmSliderHandle, intValue, 2, text, false);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         var intValue : Integer = _misc_FloatToIntValueByCount(value, 5);
      [*] = ;         if (ind=12) then
      [*] = ;         begin
      [*] = ;            case intValue of
      [*] = ;               0 : text := 'gui|378';
      [*] = ;               1 : text := 'gui|379';
      [*] = ;               2 : text := 'gui|380';
      [*] = ;               3 : text := 'gui|381';
      [*] = ;               4 : text := 'gui|382';
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            case intValue of
      [*] = ;               0 : text := 'gui|373';
      [*] = ;               1 : text := 'gui|374';
      [*] = ;               2 : text := 'gui|375';
      [*] = ;               3 : text := 'gui|376';
      [*] = ;               4 : text := 'gui|377';
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         _gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_small,'',fontHandle); // NormalL
      [*] = ;         _gui_CreateSlider(sliderID, value, text, elmParentHandle, 'halParentLeft', 'valParentTop', tmpX, tmpY+38, cEventState, hint, 49, 3, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;const cBtnAcceptTag = 100;
      [*] = ;const cBtnCancelTag = 101;
      [*] = ;const cBtnSetDefaultTag = 102;
      [*] = ;const cBtnRandomTag = 103;
      [*] = ;
      [*] = ;var elmHandle : Integer = _gui_CreateImage('', elmParentHandle, 'mainpanel.btnplace.with.frame', 'halParentLeft', 'valParentBottom', 249, -32, 0, 0, 0);
      [*] = ;var elmCheckBox : Integer = _gui_CreateButton('btnAccept', elmHandle, '', 'mainpanel.btn.accept', 'halParentLeft', 'valParentTop', 39, 0, 0, 0, cEventState, 'map.event|28.1', cBtnAcceptTag);
      [*] = ;if not bMaster then
      [*] = ;   SetGUIAllowEvents(elmCheckBox, false, false, false);
      [*] = ;
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'mainpanel.btnplace.with.frame', 'halParentLeft', 'valParentBottom', 249+114, -32, 0, 0, 0);
      [*] = ;_gui_CreateButton('btnCancel', elmHandle, '', 'mainpanel.btn.cancel', 'halParentLeft', 'valParentTop', 39, 0, 0, 0, cEventState, 'map.event|28.2', cBtnCancelTag);
      [*] = ;
      [*] = ;elmHandle := _gui_CreateButton('Reset', elmParentHandle, '', 'common.btn', 'halParentLeft', 'valParentBottom', 512+24-38, -52, 0, 0, cEventState, '', cBtnSetDefaultTag);
      [*] = ;_gui_CreateText('', elmHandle, 'tools|GUI.SET.DEFAULT.GAME', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;
      [*] = ;elmHandle := _gui_CreateButton('Random', elmParentHandle, '', 'common.btn', 'halParentLeft', 'valParentBottom', 18, -52, 0, 0, cEventState, '', cBtnRandomTag);
      [*] = ;_gui_CreateText('', elmHandle, 'gui|230', 'halParentLeft', 'valParentTop', 0, 0, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;
      [*] = ;//elmHandle := _gui_CreateImage('', elmParentHandle, 'mainpanel.btnplace.with.frame', 'halParentLeft', 'valParentBottom', 545, -32, 0, 0, 0);
      [*] = ;//_gui_CreateButton('btnSetDefault', elmHandle, '', 'map.castle.tabs.btn.provincelist', 'halParentLeft', 'valParentTop', 39, 0, 0, 0, cEventState, 'gui|355', cBtnSetDefaultTag);
      [*] = ;
      [*] = ;if (not bVisible) then
      [*] = ;   _gui_FadeElement(elmParentHandle, gc_gui_FadeTime0_4, true, true, true);
      [*] = ;
      [*] = ;_gui_RootWindowAddM(elmParentHandle);
      [*] = ;SetGUIElementPressState(elmParentHandle, cEventState);
      [*] = ;GUIExecuteState('GUIInvokeMouseMove');
   struct.end
section.end

