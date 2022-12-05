section.begin
   Name = map.CreateHeroUpgradeClass
   Description : struct.begin
      [*] = ;IntRegister0 - hero handle on STRATEGY map!
   struct.end
   Code : struct.begin
      [*] = ;const cEventState ='map.EventHeroUpgradeClass';
      [*] = ;
      [*] = ;var goHandle : Integer = IntRegister0;
      [*] = ;
      [*] = ;var fontHandleT, fontHandleH2, fontHandleH1: String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_default,'',fontHandleT);   // HeaderS
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_large,'',fontHandleH2); // NormalL
      [*] = ;_gui_GetFont(gc_gui_fontsection_strategy,'Text',gc_gui_fontsize_largest,'',fontHandleH1); // HeaderM
      [*] = ;
      [*] = ;// Check if window was already visible, then no need to FadeIn it when show again
      [*] = ;var prevElmParentHandle : Integer = _gui_GetWindow('heroupgradeclass');
      [*] = ;var bVisible : Boolean = False;
      [*] = ;if (prevElmParentHandle<>0) and GetGUIElementVisible(prevElmParentHandle) then
      [*] = ;   bVisible := True;
      [*] = ;
      [*] = ;var elmParentHandle : Integer = _gui_CreateLargeWindow(0, 'heroupgradeclass', 'halParentMiddle', 'valParentMiddle', 0, 0, 483, 460, true);
      [*] = ;var globalxOff : Integer = -94;
      [*] = ;var pGOParser : Integer = ParserSelectGameObject(goHandle);
      [*] = ;var portrait : String = ParserGetValueByKeyByHandle(pGOParser, 'Portrait');
      [*] = ;var elmHandle : Integer = _gui_CreateImage('', elmParentHandle, portrait, 'halParentLeft', 'valParentTop', 121+globalxOff, 28, 0, 0, 0);
      [*] = ;SetGUIElementPressState(elmParentHandle,'EventQueryWindowModal');
      [*] = ;_gui_ft_UnRegister('heroupgradeclass');
      [*] = ;_gui_ft_Register('heroupgradeclass','VVK.FTooltipUpgradeWindow');
      [*] = ;
      [*] = ;var heroName : String;
      [*] = ;_hero_GetName(goHandle, heroName);
      [*] = ;gStringRegister_MyHeroName := heroName;
      [*] = ;var elmHeaderHandle : Integer = GetGUIElementIndexByNameParent('header', elmParentHandle);
      [*] = ;var elmTextHandle : Integer = _gui_CreateText('', elmHeaderHandle, heroName, 'halParentLeft', 'valParentTop', 0, -1, GetGUIElementWidth(elmHeaderHandle), GetGUIElementHeight(elmHeaderHandle), 'halMiddle', 'valMiddle', fontHandleH1, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;
      [*] = ;var text : String = GetLocaleTableListItemByID('message', '11.description');
      [*] = ;GameObjectExecuteStateByHandle(goHandle, 'GetClass');
      [*] = ;var classInd : Integer = IntRegister0;
      [*] = ;gStringRegister_HeroClass := GetLocaleTableListItemByID('hero_class', IntToStr(classInd));
      [*] = ;StringRegister0 := text;
      [*] = ;MapExecuteState('StringReplaceParams');
      [*] = ;text := StringRegister1;
      [*] = ;var textWraped : String = GetGUIWrappedTextFormatByFont(fontHandleT, text, 299-12);
      [*] = ;var elmFrameHandle : Integer = _gui_CreateFrameBorder('frame', elmParentHandle, 'halParentLeft', 'valParentTop', 237+globalxOff, 41+10, 298, 84-10);
      [*] = ;elmTextHandle := _gui_CreateText('', elmFrameHandle, textWraped, 'halParentLeft', 'valParentTop', 6, 6, 298-12, 84-10-12, 'halLeft', 'valMiddle', fontHandleT, gc_gui_fontcolor_NormalR, gc_gui_fontcolor_NormalG, gc_gui_fontcolor_NormalB, 1);
      [*] = ;
      [*] = ;// class to proceed
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'element.strip.451', 'halParentLeft', 'valParentTop', 112+globalxOff, 139, 0, 0, 0);
      [*] = ;elmTextHandle := _gui_CreateText('', elmHandle, 'gui|674', 'halParentLeft', 'valParentTop', 58, 2, 332, 32, 'halMiddle', 'valMiddle', fontHandleH2, gc_gui_fontcolor_HeaderRedR, gc_gui_fontcolor_HeaderRedG, gc_gui_fontcolor_HeaderRedB, 1);
      [*] = ;var i : Integer;
      [*] = ;
      [*] = ;var allowedHeroes : Integer = gGame.allowedheroes;
      [*] = ;var ind, checkFlagNumber : Integer = 0;
      [*] = ;
      [*] = ;// pure class
      [*] = ;var newClassID : Integer = classInd*4+classInd;
      [*] = ;checkFlagNumber := _misc_GetBitFlagByIndex(newClassID - 5);
      [*] = ;      
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'icon.frame.item', 'halParentLeft', 'valParentTop', 199+0*75-5+globalxOff, 183, 0, 0, 0);
      [*] = ;elmHandle := _gui_CreateImage('', elmHandle, 'icon.heroclass.' + IntToStr(newClassID-1), 'halParentLeft', 'valParentTop', 5, 5, 0, 0, 0);
      [*] = ;var elmBtnHandle : Integer = _gui_CreateButton('', elmHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, '', '', 1);
      [*] = ;_gui_ft_AttachHint_I2_S2(elmBtnHandle,'VVK.HintHeroClassCallback',newClassID or $10000,GetGameObjectUniqueIdByHandle(goHandle),cEventState,'');
      [*] = ;//SetGUIElementStringTag(elmBtnHandle, 'Class.' + IntToStr(newClassID));
      [*] = ;      
      [*] = ;     Log(' checkFlagNumber '+IntToStr(checkFlagNumber));
      [*] = ;     Log('(allowedHeroes and checkFlagNumber) '+IntToStr((allowedHeroes and checkFlagNumber)));
      [*] = ;if ((allowedHeroes and checkFlagNumber) > 0) then
      [*] = ;begin
      [*] = ;   SetGUIAllowEvents(elmBtnHandle, false, false, false);
      [*] = ;   elmHandle := _gui_CreateImageSimple('', elmBtnHandle, 'heropanel.icon.52x52.slot.closed', 'halParentMiddle', 'valParentMiddle', 0, 0);
      [*] = ;end;
      [*] = ;     
      [*] = ;// dual-classes
      [*] = ;for i:=0 to 3 do
      [*] = ;begin
      [*] = ;   if ((i+1)<>classInd) then
      [*] = ;   begin
      [*] = ;      var newClassID : Integer = classInd*4+i+1;
      [*] = ;      checkFlagNumber := _misc_GetBitFlagByIndex(newClassID - 5);
      [*] = ;      
      [*] = ;      elmHandle := _gui_CreateImage('', elmParentHandle, 'icon.frame.item', 'halParentLeft', 'valParentTop', 199+(ind+1)*75-5+globalxOff, 183, 0, 0, 0);
      [*] = ;      elmHandle := _gui_CreateImage('', elmHandle, 'icon.heroclass.' + IntToStr(newClassID-1), 'halParentLeft', 'valParentTop', 5, 5, 0, 0, 0);
      [*] = ;      var elmBtnHandle : Integer = _gui_CreateButton('', elmHandle, '', 'heropanel.icon.52x52.slot.cover', 'halParentLeft', 'valParentTop', 0, 0, 0, 0, '', '', 1);
      [*] = ;      _gui_ft_AttachHint_I2_S2(elmBtnHandle,'VVK.HintHeroClassCallback',newClassID or $10000,GetGameObjectUniqueIdByHandle(goHandle),cEventState,'');
      [*] = ;      //SetGUIElementStringTag(elmBtnHandle, 'Class.' + IntToStr(newClassID));
      [*] = ;      ind := ind + 1;
      [*] = ;      
      [*] = ;      if ((allowedHeroes and checkFlagNumber) > 0) then
      [*] = ;      begin
      [*] = ;         SetGUIAllowEvents(elmBtnHandle, false, false, false);
      [*] = ;         elmHandle := _gui_CreateImageSimple('', elmBtnHandle, 'heropanel.icon.52x52.slot.closed', 'halParentMiddle', 'valParentMiddle', 0, 0);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;elmFrameHandle := _gui_CreateFrameBorder('frame', elmParentHandle, 'halParentLeft', 'valParentTop', 411-393, 379-62, 244+203, 105);
      [*] = ;elmHandle := _gui_CreateImage('', elmParentHandle, 'element.strip.240', 'halParentLeft', 'valParentTop', 408-279, 272, 0, 0, 0);
      [*] = ;
      [*] = ;_gui_CreateButton('btn_hero_window', elmParentHandle, '', 'map.mainpanel.btn.nexthero', 'halParentLeft', 'valParentTop', 5, 5, 0, 0, cEventState, 'gui|618', GetGameObjectUniqueIdByHandle(goHandle));
      [*] = ;
      [*] = ;_gui_PlaySound('interface', 'level_up_heroe');
      [*] = ;
      [*] = ;GUIExecuteState('GUIInvokeMouseMove');
   struct.end
section.end

