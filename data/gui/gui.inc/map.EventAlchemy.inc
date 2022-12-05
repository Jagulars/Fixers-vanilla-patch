section.begin
   Name = map.EventAlchemy
   Code : struct.begin
      [*] = ;var fontHandleH : String;
      [*] = ;_gui_GetFont(gc_gui_fontsection_tactics,'Text',gc_gui_fontsize_largest,'',fontHandleH); // HeaderM
      [*] = ;
      [*] = ;procedure DrawTransGoldGemBlock(elmParentHandle : Integer);
      [*] = ;begin
      [*] = ;   var plHandle : Integer = GetPlayerHandleInterfaceIO;
      [*] = ;   var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;   var plGem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;   var min : Integer = -plGem;
      [*] = ;   var max : Integer = plGold div 25;
      [*] = ;   var transGold : Integer = 0;
      [*] = ;   var transGem : Integer = 0;
      [*] = ;   if (gFloatRegister_AlchemySlider<0.5) then
      [*] = ;   transGem := Round((gFloatRegister_AlchemySlider-0.5)*plGem*2)
      [*] = ;   else
      [*] = ;   if (gFloatRegister_AlchemySlider>0.5) then
      [*] = ;   transGem := Round((gFloatRegister_AlchemySlider-0.5)*(plGold div 25)*2);
      [*] = ;
      [*] = ;   if (transGem<0) then
      [*] = ;   transGold := -transGem
      [*] = ;   else
      [*] = ;   if (transGem>0) then
      [*] = ;   transGold := -transGem*25;
      [*] = ;
      [*] = ;   var sTransGold : String = IntToStr(transGold);
      [*] = ;   var sTransGem : String = IntToStr(transGem);
      [*] = ;   var cR, cG, cB, cA : Float = 1;
      [*] = ;   if (transGold>0) then
      [*] = ;   begin
      [*] = ;      sTransGold := '+'+sTransGold;
      [*] = ;      cR := gc_gui_fontcolor_GreenR;
      [*] = ;      cG := gc_gui_fontcolor_GreenG;
      [*] = ;      cB := gc_gui_fontcolor_GreenB;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (transGold<0) then
      [*] = ;   begin
      [*] = ;      cR := gc_gui_fontcolor_RedR;
      [*] = ;      cG := gc_gui_fontcolor_RedG;
      [*] = ;      cB := gc_gui_fontcolor_RedB;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      cR := gc_gui_fontcolor_NormalR;
      [*] = ;      cG := gc_gui_fontcolor_NormalG;
      [*] = ;      cB := gc_gui_fontcolor_NormalB;
      [*] = ;   end;
      [*] = ;   var elmHandle : Integer = GetGUIElementIndexByNameParent('decorleft', elmParentHandle);
      [*] = ;   if (elmHandle<>0) then
      [*] = ;   RemoveGUIElement(elmHandle);
      [*] = ;   elmHandle := _gui_CreateImage('decorleft', elmParentHandle, 'alchemy.decor.left', 'halParentLeft', 'valParentTop', 0, 30, 0, 0, 0);
      [*] = ;   var elmTextHandle : Integer = _gui_CreateText('plgold', elmHandle, IntToStr(plGold), 'halParentRight', 'valParentTop', -2, -14, 75, GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandleH, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;   elmTextHandle := _gui_CreateText('transgold', elmHandle, sTransGold, 'halParentRight', 'valParentTop', -2, 14, 75, GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandleH, cR, cG, cB, 1);
      [*] = ;   elmHandle := _gui_CreateImage('goldicon', elmHandle, 'castle.building.icon.gold.big', 'halParentLeft', 'valParentMiddle', 11, -3, 0, 0, 0); //map.infopanel.gold
      [*] = ;
      [*] = ;   if (transGem>0) then
      [*] = ;   begin
      [*] = ;      sTransGem := '+'+sTransGem;
      [*] = ;      cR := gc_gui_fontcolor_GreenR;
      [*] = ;      cG := gc_gui_fontcolor_GreenG;
      [*] = ;      cB := gc_gui_fontcolor_GreenB;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   if (transGem<0) then
      [*] = ;   begin
      [*] = ;      cR := gc_gui_fontcolor_NormalR;
      [*] = ;      cG := gc_gui_fontcolor_NormalG;
      [*] = ;      cB := gc_gui_fontcolor_NormalB;
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      cR := gc_gui_fontcolor_NormalWhiteR;
      [*] = ;      cG := gc_gui_fontcolor_NormalWhiteG;
      [*] = ;      cB := gc_gui_fontcolor_NormalWhiteB;
      [*] = ;   end;
      [*] = ;   elmHandle := GetGUIElementIndexByNameParent('decorright', elmParentHandle);
      [*] = ;   if (elmHandle<>0) then
      [*] = ;   RemoveGUIElement(elmHandle);
      [*] = ;   elmHandle := _gui_CreateImage('decorright', elmParentHandle, 'alchemy.decor.right', 'halParentRightWidth', 'valParentTop', 0, 30, 0, 0, 0);
      [*] = ;   elmTextHandle := _gui_CreateText('plgem', elmHandle, IntToStr(plGem), 'halParentLeft', 'valParentTop', -75+2, -14, 75, GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandleH, gc_gui_fontcolor_YellowR, gc_gui_fontcolor_YellowG, gc_gui_fontcolor_YellowB, 1);
      [*] = ;   elmTextHandle := _gui_CreateText('transgem', elmHandle, sTransGem, 'halParentLeft', 'valParentTop', -75+2, 14, 75, GetGUIElementHeight(elmHandle), 'halMiddle', 'valMiddle', fontHandleH, cR, cG, cB, 1);
      [*] = ;   elmHandle := _gui_CreateImage('gemicon', elmHandle, 'castle.building.icon.crystal.big', 'halParentRightWidth', 'valParentMiddle', -12, -3, 0, 0, 0); //map.infopanel.crystals
      [*] = ;end;
      [*] = ;
      [*] = ;var tag : Integer = GetIntValueByName('Tag');
      [*] = ;var press  : String = GetValueByName('Press');
      [*] = ;var status  : String = GetValueByName('Status');
      [*] = ;var elmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var elmName : String =  GetGUIElementNameByIndex(elmHandle);
      [*] = ;
      [*] = ;const cBtnAcceptTag = 101;
      [*] = ;const cBtnCancelTag = 102;
      [*] = ;
      [*] = ;var elmSliderHandle : Integer;
      [*] = ;if (gIntRegister_GUIScrollSliderHandle<>0) then
      [*] = ;elmSliderHandle := gIntRegister_GUIScrollSliderHandle
      [*] = ;else
      [*] = ;elmSliderHandle := GetGUIElementParentByIndex(elmHandle);
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
      [*] = ;      GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gIntRegister_GUIScrollSliderHandle<>0) or ((press='d') and (elmName='lineSlider')) then
      [*] = ;begin
      [*] = ;   SetIntValueByName('SliderElementDragX', 14);
      [*] = ;   var value : Float = _gui_ModifySliderValueByMouseCoord(elmSliderHandle);
      [*] = ;   case sliderID of
      [*] = ;      'alchemy' : begin
      [*] = ;         gFloatRegister_AlchemySlider := value;
      [*] = ;         var elmHandle : Integer = GetGUIElementIndexByNameParent('alchemy', _gui_GetLayerI);
      [*] = ;         DrawTransGoldGemBlock(elmHandle);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (press='c') and (sliderID='') then
      [*] = ;begin
      [*] = ;   case tag of
      [*] = ;      cBtnAcceptTag, gc_gui_hotkey_btnEnter : begin
      [*] = ;         var plHandle : Integer = GetPlayerHandleInterfaceIO;
      [*] = ;         var plGold : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold);
      [*] = ;         var plGem : Integer = GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem);
      [*] = ;         var transGold : Integer = 0;
      [*] = ;         var transGem : Integer = 0;
      [*] = ;         if (gFloatRegister_AlchemySlider<0.5) then
      [*] = ;         transGem := Round((gFloatRegister_AlchemySlider-0.5)*plGem*2)
      [*] = ;         else
      [*] = ;         if (gFloatRegister_AlchemySlider>0.5) then
      [*] = ;         transGem := Round((gFloatRegister_AlchemySlider-0.5)*(plGold div 25)*2);
      [*] = ;
      [*] = ;         if (transGem<0) then
      [*] = ;         transGold := -transGem
      [*] = ;         else
      [*] = ;         if (transGem>0) then
      [*] = ;         transGold := -transGem*25;
      [*] = ;
      [*] = ;         plGold := plGold+transGold;
      [*] = ;         plGem := plGem+transGem;
      [*] = ;         SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold, plGold);
      [*] = ;         SetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem, plGem);
      [*] = ;
      [*] = ;         gFloatRegister_AlchemySlider := 0.5;
      [*] = ;         GUIExecuteState('map.CreateAlchemy');
      [*] = ;
      [*] = ;         {var whd : Integer;
      [*] = ;         var windowHandle : Integer = _gui_GetWindow(gc_gui_CPBottomName);
      [*] = ;         // gold
      [*] = ;         whd := GetGUIElementIndexByNameParent('mainpanel_player_gold',windowHandle);
      [*] = ;         if whd <> 0 then
      [*] = ;            SetGUIElementText(whd,IntToStr(GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGold)));
      [*] = ;         // gem
      [*] = ;         whd := GetGUIElementIndexByNameParent('mainpanel_player_gem',windowHandle);
      [*] = ;         if whd <> 0 then
      [*] = ;            SetGUIElementText(whd,IntToStr(GetPlayerIntValueIndByHandle(plHandle, gc_map_PLStack_MapUnit_iGem)));}
      [*] = ;         GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;         //ExecuteState('vvk.map.UpdateMainPanel');
      [*] = ;         //ExecuteState('VVK.map.CreateMainPanel');
      [*] = ;      end;
      [*] = ;      cBtnCancelTag, gc_gui_hotkey_btnEscape : begin
      [*] = ;         gIntRegister_GUIScrollSliderHandle := 0;
      [*] = ;         _gui_RootWindowRemoveWithFade(_gui_GetWindow('alchemy'),gc_gui_FadeTime0_2);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

