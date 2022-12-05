section.begin
   Name = ShowCustomDifficulty
   Description : struct.begin
      [*] = ;BoolRegister0 - bSetDefault
   struct.end
   Code : struct.begin
      [*] = ;var bSetDefault : Boolean = BoolRegister0;
      [*] = ;
      [*] = ;// Check if window was already visible, then no need to FadeIn it when show again
      [*] = ;var prevElmParentHandle : Integer = GetGUIElementIndexByNameParent('CustomDifficulty', _gui_GetLayerI());
      [*] = ;var bVisible : Boolean = False;
      [*] = ;if (prevElmParentHandle<>0) and GetGUIElementVisible(prevElmParentHandle) then
      [*] = ;bVisible := True;
      [*] = ;
      [*] = ;var elmParentHandle : Integer = _gui_CreateLargeWindow(0, 'CustomDifficulty', 'halParentMiddle', 'valParentMiddle', 0, 0, 730{830 for window with bottom background}, 489-70, false);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('background', elmParentHandle), 0.65+0.3);
      [*] = ;SetGUIElementUserBlend(GetGUIElementIndexByNameParent('frame', elmParentHandle), 0.75+0.1);
      [*] = ;
      [*] = ;// ��������� ������������ ����
      [*] = ;var elmHeaderHandle : Integer = GetGUIElementIndexByNameParent('header', elmParentHandle);
      [*] = ;var fontHandle, fontHandle2 : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_small,'',fontHandle);   // HeaderS
      [*] = ;_gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_largest,'',fontHandle2); // NormalL
      [*] = ;var elmTextHandle : Integer = _gui_CreateText('', elmHeaderHandle, 'gui|768', 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHeaderHandle), GetGUIElementHeight(elmHeaderHandle), 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;// Body
      [*] = ;const cEventState = 'EventCustomDifficulty';
      [*] = ;var localeID : String;
      [*] = ;var i, j : Integer;
      [*] = ;
      [*] = ;for i:=0 to 2 do
      [*] = ;begin
      [*] = ;   for j:=0 to 2 do
      [*] = ;   begin
      [*] = ;      var valueCount : Integer = 5;
      [*] = ;      var sliderID : String;
      [*] = ;      var ind : Integer = (j*10+i);
      [*] = ;      var hint : String;
      [*] = ;      var fvalue : Float = 0;
      [*] = ;      var value : Integer = 0;
      [*] = ;      var minValue : Integer = 0;
      [*] = ;      var maxValue : Integer = 100;
      [*] = ;      var stepValue : Integer = 1;
      [*] = ;      case ind of
      [*] = ;         0 : begin
      [*] = ;            localeID := 'gui|769';
      [*] = ;            stepValue := 1;
      [*] = ;            minValue := 0;
      [*] = ;            maxValue := 6;
      [*] = ;            sliderID := 'basediff';
      [*] = ;            value := gProfileTmp.advdiff.basediff;
      [*] = ;         end;
      [*] = ;         1 : begin
      [*] = ;            localeID := 'gui|770';
      [*] = ;            stepValue := 5;
      [*] = ;            minValue := 45;
      [*] = ;            maxValue := 145;
      [*] = ;            sliderID := 'neutralhp';
      [*] = ;            value := gProfileTmp.advdiff.neutralhp;
      [*] = ;            fvalue := gProfileTmp.advfloatdiff.neutralhp;
      [*] = ;            if (bSetDefault) then
      [*] = ;            begin
      [*] = ;               fvalue := (value-minValue)/(maxValue-minValue);
      [*] = ;               gProfileTmp.advfloatdiff.neutralhp := fvalue;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         2 : begin
      [*] = ;            localeID := 'gui|771';
      [*] = ;            stepValue := 5;
      [*] = ;            minValue := 70;
      [*] = ;            maxValue := 100;
      [*] = ;            sliderID := 'defenderhp';
      [*] = ;            value := gProfileTmp.advdiff.defenderhp;
      [*] = ;            fvalue := gProfileTmp.advfloatdiff.defenderhp;
      [*] = ;            if (bSetDefault) then
      [*] = ;            begin
      [*] = ;               fvalue := (value-minValue)/(maxValue-minValue);
      [*] = ;               gProfileTmp.advfloatdiff.defenderhp := fvalue;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         10 : begin
      [*] = ;            localeID := 'gui|772';
      [*] = ;            stepValue := 5;
      [*] = ;            minValue := 70; //80
      [*] = ;            maxValue := 125;//140
      [*] = ;            sliderID := 'expmod';
      [*] = ;            value := gProfileTmp.advdiff.expmod;
      [*] = ;            fvalue := gProfileTmp.advfloatdiff.expmod;
      [*] = ;            if (bSetDefault) then
      [*] = ;            begin
      [*] = ;               fvalue := (value-minValue)/(maxValue-minValue);
      [*] = ;               gProfileTmp.advfloatdiff.expmod := fvalue;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         11 : begin
      [*] = ;            localeID := 'gui|773';
      [*] = ;            stepValue := 10;
      [*] = ;            minValue := 500;
      [*] = ;            maxValue := 1000;
      [*] = ;            sliderID := 'startgold';
      [*] = ;            value := gProfileTmp.advdiff.startgold;
      [*] = ;            fvalue := gProfileTmp.advfloatdiff.startgold;
      [*] = ;            if (bSetDefault) then
      [*] = ;            begin
      [*] = ;               fvalue := (value-minValue)/(maxValue-minValue);
      [*] = ;               gProfileTmp.advfloatdiff.startgold := fvalue;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         12 : begin
      [*] = ;            localeID := 'gui|774';
      [*] = ;            stepValue := 5;
      [*] = ;            minValue := 20;
      [*] = ;            maxValue := 100;
      [*] = ;            sliderID := 'startgem';
      [*] = ;            value := gProfileTmp.advdiff.startgem;
      [*] = ;            fvalue := gProfileTmp.advfloatdiff.startgem;
      [*] = ;            if (bSetDefault) then
      [*] = ;            begin
      [*] = ;               fvalue := (value-minValue)/(maxValue-minValue);
      [*] = ;               gProfileTmp.advfloatdiff.startgem := fvalue;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         20 : begin
      [*] = ;            localeID := 'gui|775';
      [*] = ;            stepValue := 1;
      [*] = ;            minValue := 0;
      [*] = ;            maxValue := 20;
      [*] = ;            sliderID := 'goldincomeadd';
      [*] = ;            value := gProfileTmp.advdiff.goldincomeadd;
      [*] = ;            fvalue := gProfileTmp.advfloatdiff.goldincomeadd;
      [*] = ;            if (bSetDefault) then
      [*] = ;            begin
      [*] = ;               fvalue := (value-minValue)/(maxValue-minValue);
      [*] = ;               gProfileTmp.advfloatdiff.goldincomeadd := fvalue;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         21 : begin
      [*] = ;            localeID := 'gui|776';
      [*] = ;            stepValue := 1;
      [*] = ;            minValue := 0;
      [*] = ;            maxValue := 7;
      [*] = ;            sliderID := 'gemincomeadd';
      [*] = ;            value := gProfileTmp.advdiff.gemincomeadd;
      [*] = ;            fvalue := gProfileTmp.advfloatdiff.gemincomeadd;
      [*] = ;            if (bSetDefault) then
      [*] = ;            begin
      [*] = ;               fvalue := (value-minValue)/(maxValue-minValue);
      [*] = ;               gProfileTmp.advfloatdiff.gemincomeadd := fvalue;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         22 : begin
      [*] = ;            localeID := 'gui|777';
      [*] = ;            stepValue := 1;
      [*] = ;            minValue := 0;
      [*] = ;            maxValue := 6;
      [*] = ;            sliderID := 'corruption';
      [*] = ;            value := gProfileTmp.advdiff.corruption;
      [*] = ;            fvalue := gProfileTmp.advfloatdiff.corruption;
      [*] = ;            if (bSetDefault) then
      [*] = ;            begin
      [*] = ;               fvalue := (value-minValue)/(maxValue-minValue);
      [*] = ;               gProfileTmp.advfloatdiff.corruption := fvalue;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;      hint := localeID;
      [*] = ;
      [*] = ;      valueCount := (maxValue-minValue) div stepValue;
      [*] = ;      _sa_AddAsInt(sliderID,valueCount);
      [*] = ;      _sa_AddAsInt(sliderID,minValue);
      [*] = ;      _sa_AddAsInt(sliderID,maxValue);
      [*] = ;
      [*] = ;      var text : String = localeID;
      [*] = ;      var tmpX : Integer = 2+i*243;
      [*] = ;      var tmpY : Integer = 30+j*101;
      [*] = ;      var elmHandle : Integer = _gui_CreateImage('', elmParentHandle, 'element.strip.240', 'halParentLeft', 'valParentTop', tmpX, tmpY, 0, 0, 0);
      [*] = ;      _gui_CreateText('', elmHandle, text, 'halParentLeft', 'valParentTop', 0, -2, GetGUIElementWidth(elmHandle), GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;      if (ind=0) then
      [*] = ;      begin
      [*] = ;         var elmSliderHandle : Integer = _gui_CreateIntSlider(sliderID, elmParentHandle, 'halParentLeft', 'valParentTop', tmpX, tmpY+38, 228, cEventState, hint, 49, 3, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;         var text : String = 'difficulty|'+IntToStr(value);
      [*] = ;         _gui_SetSliderIntValue(elmSliderHandle, value, valueCount+1, text, false);
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         value := _misc_FloatToIntValueByCount(fvalue, valueCount+1);
      [*] = ;         var text : String = IntToStr(round(minValue+(value*stepValue)));
      [*] = ;         if (ind=22) then
      [*] = ;         begin
      [*] = ;            case value of
      [*] = ;               0 : text := 'gui|'+IntToStr(779+value);
      [*] = ;               1 : text := 'gui|'+IntToStr(779+value);
      [*] = ;               2 : text := 'gui|'+IntToStr(779+value);
      [*] = ;               3 : text := 'gui|'+IntToStr(779+value);
      [*] = ;               4 : text := 'gui|'+IntToStr(779+value);
      [*] = ;               5 : text := 'gui|'+IntToStr(779+value);
      [*] = ;               6 : text := 'gui|'+IntToStr(779+value);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         _gui_GetFont(gc_gui_fontsection_menu,'Text',gc_gui_fontsize_small,'',fontHandle); // NormalL
      [*] = ;         _gui_CreateSlider(sliderID, fvalue, text, elmParentHandle, 'halParentLeft', 'valParentTop', tmpX, tmpY+38, cEventState, hint, 49, 3, 'halMiddle', 'valMiddle', fontHandle, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   var score : Integer = _misc_CalcScoreModifier(gProfileTmp);
      [*] = ;   var cHeaderFontSize : String;
      [*] = ;   _gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_largest,'',cHeaderFontSize);
      [*] = ;   elmTextHandle := _gui_CreateText('', elmParentHandle, 'gui|778', 'halParentMiddle', 'valParentBottomHeight', 4, -54, 200, 0, 'halMiddle', 'valMiddle', fontHandle2, gc_gui_fontcolor_NormalWhiteR, gc_gui_fontcolor_NormalWhiteG, gc_gui_fontcolor_NormalWhiteB, 1);
      [*] = ;   elmTextHandle := _gui_CreateText('score', elmParentHandle, IntToStr(score)+'%', 'halParentMiddle', 'valParentBottomHeight', 4, -54+GetGUIElementFontHeight(cHeaderFontSize), 74, 0, 'halMiddle', 'valMiddle', cHeaderFontSize, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;   var elmHandle : Integer = _gui_CreateImage('', elmParentHandle, gc_gui_material_blank_0, 'halParentMiddle', 'valParentBottomHeight', 4, -54+16, 160, 48, 0);
      [*] = ;   SetGUIElementHint(elmHandle, 'gui|778');
      [*] = ;   SetGUIAllowEvents(elmHandle, True, False, False);
      [*] = ;   logi('scores='+IntToStr(score)+' elmhnd='+IntToStr(elmTextHandle)+' score created');
      [*] = ;end;
      [*] = ;
      [*] = ;const cBtnAcceptTag = 100;
      [*] = ;const cBtnCancelTag = 101;
      [*] = ;const cBtnSetDefaultTag = 102;
      [*] = ;var elmHandle : Integer = _gui_CreateImage('', elmParentHandle, 'mainpanel.btnplace.with.frame', 'halParentLeft', 'valParentBottom', 249, -32, 0, 0, 0);
      [*] = ;var elmBtnHandle : Integer = _gui_CreateButton('btnAccept', elmHandle, '', 'mainpanel.btn.accept', 'halParentLeft', 'valParentTop', 39, 0, 0, 0, cEventState, 'map.event|28.1', cBtnAcceptTag);
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'mainpanel.btnplace.with.frame', 'halParentLeft', 'valParentBottom', 249+114, -32, 0, 0, 0);
      [*] = ;elmBtnHandle := _gui_CreateButton('btnCancel', elmHandle, '', 'mainpanel.btn.cancel', 'halParentLeft', 'valParentTop', 39, 0, 0, 0, cEventState, 'map.event|28.2', cBtnCancelTag);
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'mainpanel.btnplace.with.frame', 'halParentLeft', 'valParentBottom', 545, -32, 0, 0, 0);
      [*] = ;elmBtnHandle := _gui_CreateButton('btnSetDefault', elmHandle, '', 'map.castle.tabs.btn.provincelist', 'halParentLeft', 'valParentTop', 39, 0, 0, 0, cEventState, 'gui|355', cBtnSetDefaultTag);
      [*] = ;
      [*] = ;if (not bVisible) then
      [*] = ;   _gui_FadeWindow_VVK(elmParentHandle,gc_gui_FadeTime0_4,0);
      [*] = ;
      [*] = ;_gui_RootWindowAddM(elmParentHandle);
      [*] = ;SetGUIElementPressState(elmParentHandle, cEventState);
      [*] = ;ExecuteState('GUIInvokeMouseMove');
   struct.end
section.end

