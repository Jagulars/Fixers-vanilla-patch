section.begin
   Name = battle.GUIUpdateUnitHUD
   Code : struct.begin
      [*] = ;var goHandle : Integer = IntRegister0;
      [*] = ;var perspectiveFactor : Float = Clamp(FloatRegister0, 0, 1);
      [*] = ;
      [*] = ;var hudCollection : Integer = GetGUIElementTopIndexByName('hudunit');
      [*] = ;if hudCollection = 0 then exit;
      [*] = ;var hudHandle : Integer = GetGUIGroupHUDCollectionItemByGameObject(hudCollection, goHandle);
      [*] = ;
      [*] = ;var curLife : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurLife);
      [*] = ;var visLifeMod : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iVisualLifeMod);
      [*] = ;curLife := curLife + visLifeMod;
      [*] = ;
      [*] = ;var b : Boolean = (GetGameObjectPlayableObjectByHandle(goHandle)) and (curLife>0);
      [*] = ;
      [*] = ;var unitUnderMouse : Boolean = (goHandle=GetGameObjectHandleByUniqueId(gIntRegister_EndHexUID));
      [*] = ;
      [*] = ;if (not GetGameObjectVisibleByHandle(goHandle)) or ((not b) {and (not unitUnderMouse)}) then
      [*] = ;begin
      [*] = ;   if (hudHandle<>0) then
      [*] = ;   GUIGroupHUDCollectionDeleteGameObject(hudCollection, goHandle);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;if (hudHandle=0) then
      [*] = ;hudHandle := GUIGroupHUDCollectionAddGameObject(hudCollection, goHandle);
      [*] = ;
      [*] = ;IntRegister0 := gc_battle_unit_iMaxLife;
      [*] = ;GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;var maxLife : Integer = IntRegister1;
      [*] = ;
      [*] = ;var curStamina : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurStamina);
      [*] = ;var visStaminaMod : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iVisualStaminaMod);
      [*] = ;curStamina := curStamina + visStaminaMod;
      [*] = ;
      [*] = ;var curMoral : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurMoral);
      [*] = ;var visMoralMod : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iVisualMoralMod);
      [*] = ;curMoral := curMoral + visMoralMod;
      [*] = ;
      [*] = ;var bCanAct : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_stack_unit_bCanAct);
      [*] = ;var bAvailable : Boolean = (bCanAct);
      [*] = ;var bEnemy : Boolean = (GetGameObjectPlayerHandleByHandle(goHandle)<>GetPlayerHandleInterfaceIO);
      [*] = ;var bFadeAlpha : Boolean = (not bAvailable) and (not bEnemy);
      [*] = ;GameObjectExecuteStateByHandle(goHandle, 'IsStand');
      [*] = ;var bStand : Boolean = BoolRegister0;
      [*] = ;var goGridX : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentX);
      [*] = ;var goGridY : Integer = GetGameObjectIntValueIndByHandle(goHandle, gc_stack_unit_iCurrentY);
      [*] = ;
      [*] = ;var prevElmHnd : Integer = GetGUIElementIndexByNameParent('battle_hud', hudHandle);
      [*] = ;var bUpdate : Boolean = False;
      [*] = ;if (prevElmHnd<>0) then
      [*] = ;begin
      [*] = ;   var prevStringTag : String = GetGUIElementStringTag(prevElmHnd);
      [*] = ;   if (not bStand) then
      [*] = ;   bUpdate := True
      [*] = ;   else
      [*] = ;   if ((gProfile.warbar)<>(_gui_GetDelimiterIntValueByIndex(prevStringTag, 0))) then
      [*] = ;   bUpdate := True
      [*] = ;   else
      [*] = ;   if ((curLife)<>(_gui_GetDelimiterIntValueByIndex(prevStringTag, 1))) then
      [*] = ;   bUpdate := True
      [*] = ;   else
      [*] = ;   if ((curStamina)<>(_gui_GetDelimiterIntValueByIndex(prevStringTag, 2))) then
      [*] = ;   bUpdate := True
      [*] = ;   else
      [*] = ;   if ((curMoral)<>(_gui_GetDelimiterIntValueByIndex(prevStringTag, 3))) then
      [*] = ;   bUpdate := True
      [*] = ;   else
      [*] = ;   if ((_gui_BoolToInt(bFadeAlpha))<>(_gui_GetDelimiterIntValueByIndex(prevStringTag, 4))) then
      [*] = ;   bUpdate := True
      [*] = ;   else
      [*] = ;   if ((goGridX)<>(_gui_GetDelimiterIntValueByIndex(prevStringTag, 5))) or ((goGridY)<>(_gui_GetDelimiterIntValueByIndex(prevStringTag, 6))) then
      [*] = ;   bUpdate := True;
      [*] = ;end
      [*] = ;else
      [*] = ;bUpdate := True;
      [*] = ;
      [*] = ;if (bUpdate) then
      [*] = ;RemoveGUIChildren(hudHandle)
      [*] = ;else
      [*] = ;exit;
      [*] = ;
      [*] = ;const cAlertStamina = 8;
      [*] = ;const cAlertMoral = 6;
      [*] = ;
      [*] = ;const cLifeBackgroundSizeX = 74;
      [*] = ;const cLifeBackgroundSizeY = 12;
      [*] = ;const cLifeMeterSizeX = 70;
      [*] = ;const cLifeMeterSizeY = 8;
      [*] = ;
      [*] = ;const cFontColorYellowR = 1;
      [*] = ;const cFontColorYellowG = 1;
      [*] = ;const cFontColorYellowB = 0;
      [*] = ;
      [*] = ;case gProfile.warbar of
      [*] = ;   0 : begin // Off
      [*] = ;   end;
      [*] = ;   1 : begin // Defaul, show only critical
      [*] = ;      if ((curLife<maxLife) or (curStamina<=cAlertStamina) or (curMoral<=cAlertMoral)) then
      [*] = ;      begin
      [*] = ;         var bAltKey : Boolean = GetBoolValueByName('KeyPressedAlt');
      [*] = ;
      [*] = ;         var fontHandleArialNum : String = 'font.arial.9px.7pt.bold';
      [*] = ;         _gui_GetFont(gc_gui_fontsection_tactics,'Numbers',gc_gui_fontsize_smallest,'',fontHandleArialNum);
      [*] = ;
      [*] = ;         var perspectiveOffsetX : Integer = round(Lerp(-20, 20, perspectiveFactor));
      [*] = ;         var elmParentHandle : Integer = _gui_GetOrCreateElementExtAsImage('battle_hud', hudHandle, 'halParentMiddle', 'valParentTop', perspectiveOffsetX, 0, 0, 0, 0);
      [*] = ;
      [*] = ;         var elmHandle : Integer;
      [*] = ;         if (curLife<>maxLife) then
      [*] = ;         begin
      [*] = ;            var elmLifeBckHandle : Integer = _gui_CreateImage('', elmParentHandle, 'battlehud.life.background', 'halParentMiddle', 'valParentMiddle', 0, 0, cLifeBackgroundSizeX, cLifeBackgroundSizeY, 0);
      [*] = ;            if (curLife>0) then
      [*] = ;            begin
      [*] = ;               elmHandle := _gui_CreateImage('', elmLifeBckHandle, 'battlehud.life', 'halParentLeft', 'valParentMiddle', 2, 0, cLifeMeterSizeX, cLifeMeterSizeY, 0);
      [*] = ;               var meterWidth : Integer = round(cLifeMeterSizeX*curLife/maxLife);
      [*] = ;               if (meterWidth=0) then meterWidth := 1;
      [*] = ;               if (meterWidth>cLifeMeterSizeX) then
      [*] = ;               meterWidth := cLifeMeterSizeX;
      [*] = ;
      [*] = ;               _gui_TileScaleElementToSize(elmHandle, meterWidth, 0);
      [*] = ;               if (not bAvailable) and (not bEnemy) then
      [*] = ;               SetGUIElementUserBlend(elmHandle, 0.4);
      [*] = ;            end;
      [*] = ;
      [*] = ;            elmHandle := _gui_CreateText('', elmLifeBckHandle, IntToStr(curLife), 'halParentLeft', 'valParentTop', 1, 0, cLifeBackgroundSizeX, cLifeBackgroundSizeY, 'halMiddle', 'valMiddle', fontHandleArialNum, cFontColorYellowR, cFontColorYellowG, cFontColorYellowB, 1);
      [*] = ;         end;
      [*] = ;
      [*] = ;         const cIconSizeX = 37;
      [*] = ;         const cIconSizeY = 25;
      [*] = ;         const cIconOffY = -30;
      [*] = ;
      [*] = ;         var matName : String;
      [*] = ;         if (curStamina<=cAlertStamina) then
      [*] = ;         begin
      [*] = ;            if (curStamina>0) then
      [*] = ;            matName := 'battlehud.life.stamina.background'
      [*] = ;            else
      [*] = ;            matName := 'battlehud.life.stamina.background.grey';
      [*] = ;
      [*] = ;            elmHandle := _gui_CreateImage('', elmParentHandle, matName, 'halParentLeft', 'valParentTop', -cIconSizeX, cIconOffY, cIconSizeX, cIconSizeY, 0);
      [*] = ;            if (curStamina>0) then
      [*] = ;            elmHandle := _gui_CreateText('', elmHandle, IntToStr(curStamina), 'halParentLeft', 'valParentTop', 21, 8, 16, 15, 'halMiddle', 'valMiddle', fontHandleArialNum, gc_gui_fontcolor_RedR, gc_gui_fontcolor_RedG, gc_gui_fontcolor_RedB, 1);
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (curMoral<=cAlertMoral) then
      [*] = ;         begin
      [*] = ;            if (curMoral>0) then
      [*] = ;            matName := 'battlehud.life.moral.background'
      [*] = ;            else
      [*] = ;            matName := 'battlehud.life.moral.background.grey';
      [*] = ;            elmHandle := _gui_CreateImage('', elmParentHandle, matName, 'halParentLeft', 'valParentTop', 0, cIconOffY, cIconSizeX, cIconSizeY, 0);
      [*] = ;            if (curMoral>0) then
      [*] = ;            elmHandle := _gui_CreateText('', elmHandle, IntToStr(curMoral), 'halParentLeft', 'valParentTop', 21, 8, 16, 15, 'halMiddle', 'valMiddle', fontHandleArialNum, gc_gui_fontcolor_RedR, gc_gui_fontcolor_RedG, gc_gui_fontcolor_RedB, 1);
      [*] = ;         end;
      [*] = ;
      [*] = ;         SetGUIElementStringTag(elmParentHandle, IntToStr(gProfile.warbar)+gc_gui_DelimiterCharStr+IntToStr(curLife)+gc_gui_DelimiterCharStr+IntToStr(curStamina)+gc_gui_DelimiterCharStr+IntToStr(curMoral)+gc_gui_DelimiterCharStr+IntToStr(_gui_BoolToInt(bFadeAlpha))+gc_gui_DelimiterCharStr+IntToStr(goGridX)+gc_gui_DelimiterCharStr+IntToStr(goGridY));
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   2 : begin // Show all, old school view
      [*] = ;      var bAltKey : Boolean = GetBoolValueByName('KeyPressedAlt');
      [*] = ;
      [*] = ;      var fontHandleArialNum : String = 'font.arial.9px.7pt.bold';
      [*] = ;      _gui_GetFont(gc_gui_fontsection_tactics,'Numbers',gc_gui_fontsize_smallest,'',fontHandleArialNum);
      [*] = ;
      [*] = ;      var perspectiveOffsetX : Integer = round(Lerp(-20, 20, perspectiveFactor));
      [*] = ;      var elmParentHandle : Integer = _gui_GetOrCreateElementExtAsImage('battle_hud', hudHandle, 'halParentMiddle', 'valParentTop', perspectiveOffsetX, 0, 0, 0, 0);
      [*] = ;
      [*] = ;      var elmHandle : Integer;
      [*] = ;      var elmLifeBckHandle : Integer = _gui_CreateImage('', elmParentHandle, 'battlehud.life.background', 'halParentMiddle', 'valParentMiddle', 0, 0, cLifeBackgroundSizeX, cLifeBackgroundSizeY, 0);
      [*] = ;      var bEnemy : Boolean = (GetGameObjectPlayerHandleByHandle(goHandle)<>GetPlayerHandleInterfaceIO);
      [*] = ;      if (curLife>0) then
      [*] = ;      begin
      [*] = ;         elmHandle := _gui_CreateImage('', elmLifeBckHandle, 'battlehud.life', 'halParentLeft', 'valParentMiddle', 2, 0, cLifeMeterSizeX, cLifeMeterSizeY, 0);
      [*] = ;         var meterWidth : Integer = round(cLifeMeterSizeX*curLife/maxLife);
      [*] = ;         if (meterWidth=0) then meterWidth := 1;
      [*] = ;         if (meterWidth>cLifeMeterSizeX) then
      [*] = ;         meterWidth := cLifeMeterSizeX;
      [*] = ;         _gui_TileScaleElementToSize(elmHandle, meterWidth, 0);
      [*] = ;         if (bFadeAlpha) then
      [*] = ;         SetGUIElementUserBlend(elmHandle, 0.4);
      [*] = ;      end;
      [*] = ;      elmHandle := _gui_CreateText('', elmLifeBckHandle, IntToStr(curLife), 'halParentLeft', 'valParentTop', 1, 0, cLifeBackgroundSizeX, cLifeBackgroundSizeY, 'halMiddle', 'valMiddle', fontHandleArialNum, cFontColorYellowR, cFontColorYellowG, cFontColorYellowB, 1);
      [*] = ;
      [*] = ;      const cStaminaBackgroundSizeX = 70;
      [*] = ;      const cStaminaBackgroundSizeY = 4;
      [*] = ;      var elmStaminaBckHandle : Integer = _gui_CreateImage('', elmParentHandle, 'battlehud.stamina.background', 'halParentMiddle', 'valParentMiddle', 0, -8, cStaminaBackgroundSizeX, cStaminaBackgroundSizeY, 0);
      [*] = ;      if (curStamina>0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := gc_battle_unit_iMaxStamina;
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;         var maxStamina : Integer = IntRegister1;
      [*] = ;
      [*] = ;         const cStaminaMeterSizeX = 68;
      [*] = ;         const cStaminaMeterSizeY = 2;
      [*] = ;         elmHandle := _gui_CreateImage('', elmStaminaBckHandle, 'battlehud.stamina', 'halParentLeft', 'valParentMiddle', 1, 0, cStaminaMeterSizeX, cStaminaMeterSizeY, 0);
      [*] = ;         var meterWidth : Integer = round(cStaminaMeterSizeX*curStamina/maxStamina);
      [*] = ;         if (meterWidth=0) then meterWidth := 1;
      [*] = ;         if (meterWidth>cStaminaMeterSizeX) then
      [*] = ;         meterWidth := cStaminaMeterSizeX;
      [*] = ;         _gui_TileScaleElementToSize(elmHandle, meterWidth, 0);
      [*] = ;      end;
      [*] = ;
      [*] = ;      var elmMoralBckHandle : Integer = _gui_CreateImage('', elmParentHandle, 'battlehud.stamina.background', 'halParentMiddle', 'valParentMiddle', 0, -11, cStaminaBackgroundSizeX, cStaminaBackgroundSizeY, 0);
      [*] = ;      if (curMoral>0) then
      [*] = ;      begin
      [*] = ;         IntRegister0 := gc_battle_unit_iMaxMoral;
      [*] = ;         GameObjectExecuteStateByHandle(goHandle, 'GetProperty');
      [*] = ;         var maxMoral : Integer = IntRegister1;
      [*] = ;
      [*] = ;         elmHandle := _gui_CreateImage('', elmMoralBckHandle, 'battlehud.moral', 'halParentLeft', 'valParentMiddle', 1, 0, cStaminaMeterSizeX, cStaminaMeterSizeY, 0);
      [*] = ;         var meterWidth : Integer = round(cStaminaMeterSizeX*curMoral/maxMoral);
      [*] = ;         if (meterWidth=0) then meterWidth := 1;
      [*] = ;         if (meterWidth>cStaminaMeterSizeX) then
      [*] = ;         meterWidth := cStaminaMeterSizeX;
      [*] = ;         _gui_TileScaleElementToSize(elmHandle, meterWidth, 0);
      [*] = ;      end;
      [*] = ;
      [*] = ;      SetGUIElementStringTag(elmParentHandle, IntToStr(gProfile.warbar)+gc_gui_DelimiterCharStr+IntToStr(curLife)+gc_gui_DelimiterCharStr+IntToStr(curStamina)+gc_gui_DelimiterCharStr+IntToStr(curMoral)+gc_gui_DelimiterCharStr+IntToStr(_gui_BoolToInt(bFadeAlpha))+gc_gui_DelimiterCharStr+IntToStr(goGridX)+gc_gui_DelimiterCharStr+IntToStr(goGridY));
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

