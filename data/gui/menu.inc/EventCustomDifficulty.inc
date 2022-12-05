section.begin
   Name = EventCustomDifficulty
   Code : struct.begin
      [*] = ;var _log_name : String = 'MENU.INC\EVENTCUSTOMDIFFICULTY';
      [*] = ;var _log_trace : Integer = $10000;
      [*] = ;_gv_traceState(_log_name,_log_trace);
      [*] = ;
      [*] = ;var _log : Boolean = true;
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
      [*] = ;      var x2, y2 : Integer;
      [*] = ;      GetGUICurrentMouseCoord(mX, mY);
      [*] = ;      GUIInvalidateParentPositions(elmHandle);
      [*] = ;      GetGUIElementAlignPosition(elmHandle, x2, y2);
      [*] = ;      SetIntValueByName('SliderElementDragX', mX-x2);
      [*] = ;      SetIntValueByName('SliderElementDragY', mY-y2);
      [*] = ;      GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;   end;
      [*] = ;
      [*] = ;end;
      [*] = ;
      [*] = ;var valueCount : Integer = 5;
      [*] = ;var minValue : Integer = 0;
      [*] = ;var maxValue : Integer = 100;
      [*] = ;if (sliderID<>'') and IsDelimiterCharExists(sliderID, gc_gui_DelimiterChar) then
      [*] = ;begin
      [*] = ;   minValue := _gui_GetDelimiterIntValueByIndex(sliderID, 2);
      [*] = ;   maxValue := _gui_GetDelimiterIntValueByIndex(sliderID, 3);
      [*] = ;   valueCount := _gui_GetDelimiterIntValueByIndex(sliderID, 1);
      [*] = ;   _gui_GetDelimiterValueByIndex(sliderID, 0, sliderID);
      [*] = ;end;
      [*] = ;
      [*] = ;if (gIntRegister_GUIScrollSliderHandle<>0) or ((sPress='d') and (elmName='lineSlider')) then
      [*] = ;begin
      [*] = ;   SetIntValueByName('SliderElementDragX', 14);
      [*] = ;   var fvalue : Float = _gui_ModifySliderValueByMouseCoord(elmSliderHandle);
      [*] = ;   var value : Integer = _misc_FloatToIntValueByCount(fvalue, valueCount+1);
      [*] = ;   var stepValue : Integer = (maxValue-minValue) div valueCount;
      [*] = ;   var intValue : Integer = round(minValue+(value*stepValue));
      [*] = ;
      [*] = ;   if _log then _Log_values(_log_name+'_MIN|MAX|COUNT|CURR',minValue,maxValue,valueCount,intValue,0,0);
      [*] = ;   case sliderID of
      [*] = ;      'basediff' : begin
      [*] = ;         gProfileTmp.advdiff.basediff := value;
      [*] = ;         gProfileTmp.difficulty := value;
      [*] = ;      end;
      [*] = ;      'neutralhp' : gProfileTmp.advfloatdiff.neutralhp := fvalue;
      [*] = ;      'defenderhp' : gProfileTmp.advfloatdiff.defenderhp := fvalue;
      [*] = ;      'expmod' : gProfileTmp.advfloatdiff.expmod := fvalue;
      [*] = ;      'startgold' : gProfileTmp.advfloatdiff.startgold := fvalue;
      [*] = ;      'startgem' : gProfileTmp.advfloatdiff.startgem := fvalue;
      [*] = ;      'goldincomeadd' : gProfileTmp.advfloatdiff.goldincomeadd := fvalue;
      [*] = ;      'gemincomeadd' : gProfileTmp.advfloatdiff.gemincomeadd := fvalue;
      [*] = ;      'corruption' : gProfileTmp.advfloatdiff.corruption := fvalue;
      [*] = ;   end;
      [*] = ;   case sliderID of
      [*] = ;      'neutralhp' : gProfileTmp.advdiff.neutralhp := intValue;
      [*] = ;      'defenderhp' : gProfileTmp.advdiff.defenderhp := intValue;
      [*] = ;      'expmod' : gProfileTmp.advdiff.expmod := intValue;
      [*] = ;      'startgold' : gProfileTmp.advdiff.startgold := intValue;
      [*] = ;      'startgem' : gProfileTmp.advdiff.startgem := intValue;
      [*] = ;      'goldincomeadd' : gProfileTmp.advdiff.goldincomeadd := intValue;
      [*] = ;      'gemincomeadd' : gProfileTmp.advdiff.gemincomeadd := intValue;
      [*] = ;      'corruption' : gProfileTmp.advdiff.corruption := intValue;
      [*] = ;   end;
      [*] = ;
      [*] = ;   var text : String = IntToStr(intValue);
      [*] = ;   if (sliderID='corruption') then
      [*] = ;   begin
      [*] = ;      case value of
      [*] = ;         0 : text := 'gui|'+IntToStr(779+value);
      [*] = ;         1 : text := 'gui|'+IntToStr(779+value);
      [*] = ;         2 : text := 'gui|'+IntToStr(779+value);
      [*] = ;         3 : text := 'gui|'+IntToStr(779+value);
      [*] = ;         4 : text := 'gui|'+IntToStr(779+value);
      [*] = ;         5 : text := 'gui|'+IntToStr(779+value);
      [*] = ;         6 : text := 'gui|'+IntToStr(779+value);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   //if (sliderID='expmod') then
      [*] = ;   //text := IntToStr((Round(100/round(minValue+(value*stepValue))*100) div 5)*5);
      [*] = ;   _gui_SetSliderText(elmSliderHandle, text);
      [*] = ;
      [*] = ;   elmHandle := _gui_GetWindow('CustomDifficulty.score');
      [*] = ;   if (elmHandle<>0) then
      [*] = ;      RemoveGUIElement(elmHandle);
      [*] = ;   var cHeaderFontSize : String;
      [*] = ;   _gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_largest,'',cHeaderFontSize);
      [*] = ;   var score : Integer = _misc_CalcScoreModifier(gProfileTmp);
      [*] = ;   var elmParentHandle : Integer = _gui_GetWindow('CustomDifficulty');
      [*] = ;   _gui_CreateText('score', elmParentHandle, IntToStr(score)+'%', 'halParentMiddle', 'valParentBottomHeight', 4, -54+GetGUIElementFontHeight(cHeaderFontSize), 74, 0, 'halMiddle', 'valMiddle', cHeaderFontSize, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;   //log('scores='+IntToStr(scores)+' elmhnd='+IntToStr(elmHandle));
      [*] = ;   //SetGUIElementText(elmHandle, IntToStr(scores)+'%');
      [*] = ;end;
      [*] = ;
      [*] = ;const cBtnAcceptTag = 100;
      [*] = ;const cBtnCancelTag = 101;
      [*] = ;const cBtnSetDefaultTag = 102;
      [*] = ;if (sPress='c') and (gIntRegister_GUIScrollSliderHandle=0) then
      [*] = ;begin
      [*] = ;   if (elmName='arrowSliderLeft') or (elmName='arrowSliderRight') then
      [*] = ;   begin
      [*] = ;      if (StrExists(sliderID, 'basediff')) then
      [*] = ;      begin
      [*] = ;         var elmSliderHandle : Integer = GetGUIElementParentByIndex(elmHandle);
      [*] = ;         var value : Integer = gProfileTmp.advdiff.basediff;
      [*] = ;         if (elmName='arrowSliderLeft') then
      [*] = ;            value := value-1
      [*] = ;         else
      [*] = ;            value := value+1;
      [*] = ;         if (value>maxValue) then value := minValue;
      [*] = ;         if (value<minValue) then value := maxValue;
      [*] = ;         _gui_SetSliderIntValue(elmSliderHandle, value, valueCount+1, 'difficulty|'+IntToStr(value), false);
      [*] = ;         gProfileTmp.advdiff.basediff := value;
      [*] = ;         gProfileTmp.difficulty := value;
      [*] = ;         _map_SetGameCustomDifficultyOptionsDefault(gProfileTmp.advdiff, False, value);
      [*] = ;         BoolRegister0 := True;
      [*] = ;         GUIExecuteState('ShowCustomDifficulty');
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (sliderID='') then
      [*] = ;   begin
      [*] = ;      var tag : Integer = GetIntValueByName('Tag');
      [*] = ;      case tag of
      [*] = ;         cBtnAcceptTag, gc_gui_hotkey_btnEnter : begin
      [*] = ;            gIntRegister_GUIScrollSliderHandle := 0;
      [*] = ;            gProfileTmp.advdiff.custom := True;
      [*] = ;            _misc_AssignGlobalVars('gProfileTmp', 'gProfile');
      [*] = ;            _misc_AssignDifficulty(gProfile.advdiff, gMapSettings.arrplayers[0].advdiff);
      [*] = ;            _gui_RootWindowRemoveWithFade(_gui_GetWindow('CustomDifficulty'),gc_gui_FadeTime0_2);
      [*] = ;            var prevElmParentHandle : Integer = _gui_GetWindow('Profile');
      [*] = ;            if (prevElmParentHandle<>0) then
      [*] = ;            begin
      [*] = ;               // works only if difficulty slider is alone.
      [*] = ;               var elmHnd : Integer = GetGUIElementIndexByNameParent('slider.textSlider', prevElmParentHandle);
      [*] = ;               SetGUIElementText(elmHnd, GetLocaleTableListItemByID('gui', '767'));
      [*] = ;            end;
      [*] = ;            prevElmParentHandle := _gui_GetWindow('NewGame');
      [*] = ;            if (prevElmParentHandle<>0) then
      [*] = ;            begin
      [*] = ;               // works only if difficulty slider is alone.
      [*] = ;               var elmHnd : Integer = GetGUIElementIndexByNameParent('player.slider.textSlider', prevElmParentHandle);
      [*] = ;               SetGUIElementText(elmHnd, GetLocaleTableListItemByID('gui', '767'));
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;         cBtnCancelTag, gc_gui_hotkey_btnEscape : begin
      [*] = ;            gIntRegister_GUIScrollSliderHandle := 0;
      [*] = ;            //_misc_AssignGlobalVars('gProfile', 'gProfileTmp');
      [*] = ;            _gui_RootWindowRemoveWithFade(_gui_GetWindow('CustomDifficulty'),gc_gui_FadeTime0_4);
      [*] = ;         end;
      [*] = ;         cBtnSetDefaultTag : begin
      [*] = ;            gIntRegister_GUIScrollSliderHandle := 0;
      [*] = ;            _map_SetGameCustomDifficultyOptionsDefault(gProfileTmp.advdiff, False, gProfileTmp.advdiff.basediff);
      [*] = ;            BoolRegister0 := True;
      [*] = ;            GUIExecuteState('ShowCustomDifficulty');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

