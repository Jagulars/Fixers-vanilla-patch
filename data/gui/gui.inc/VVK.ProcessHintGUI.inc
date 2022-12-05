section.begin
   Name = VVK.ProcessHintGUI
   Description : struct.begin
      [*] = ;BoolRegister0 = true for extended hint
      [*] = ;
      [*] = ;if hint string starts with '#' then this is floating tooltip with callback.
      [*] = ;for details see common.inc/VVK.FTooltipInnerBuilding
   struct.end
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;var extendedHint : Boolean = BoolRegister0;
      [*] = ;var iElmHandle : Integer = GetIntValueByName('ElementHandle');
      [*] = ;var textTooltip,extTextTooltip,temp_str,temp_str_e,pressState : String;
      [*] = ;var display_f,display_f2 : Integer;
      [*] = ;var ehd : Integer;
      [*] = ;
      [*] = ;display_f := 0;
      [*] = ;display_f2 := 0;
      [*] = ;if _gui_ft_ProcessHintRequest(iElmHandle,extendedHint,'DoOnHintGUIExt',gProfile.exthintdelay,display_f,temp_str,temp_str_e) then
      [*] = ;   exit;
      [*] = ;
      [*] = ;if ((display_f and 1) <> 0) then
      [*] = ;begin
      [*] = ;   textTooltip := temp_str;
      [*] = ;   if extendedHint and (temp_str_e <> '') then
      [*] = ;      textTooltip := textTooltip+gc_gui_BreakLine+gc_gui_BreakLine+temp_str_e;
      [*] = ;end
      [*] = ;else
      [*] = ;   textTooltip := GetGUIElementHint(iElmHandle);
      [*] = ;
      [*] = ;if _gui_ft_ProcessHintCallback(iElmHandle,extendedHint,'VVK.HintCommonCallback',textTooltip,display_f2,temp_str,temp_str_e) then
      [*] = ;   exit;
      [*] = ;
      [*] = ;if ((display_f2 and 1) <> 0) then
      [*] = ;begin
      [*] = ;   textTooltip := temp_str;
      [*] = ;   extTextTooltip := temp_str_e;
      [*] = ;end;
      [*] = ;display_f := display_f or display_f2;
      [*] = ;
      [*] = ;//RemoveGUIChildren(_gui_GetLayer(cTooltipLayer));
      [*] = ;var layer : Integer = _gui_GetLayer(cTooltipLayer);
      [*] = ;var i, elmHandle : Integer;
      [*] = ;for i := GetGUIElementChildrenCount(layer)-1 downto 0 do
      [*] = ;begin
      [*] = ;   elmHandle := GetGUIElementChildrenByIndex(layer, i);
      [*] = ;   if gc_RecycleGUI and _gui_IsRecycledElement(elmHandle) then
      [*] = ;      _gui_Show(elmHandle, false)
      [*] = ;   else
      [*] = ;      RemoveGUIElement(elmHandle);
      [*] = ;end;
      [*] = ;
      [*] = ;if textTooltip = '' then
      [*] = ;begin
      [*] = ;   GUIDelayExecuteState('', 0);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;const firstUID = 7000;
      [*] = ;const firstUID2 = 100;
      [*] = ;pressState := GetGUIElementPressState(iElmHandle);
      [*] = ;
      [*] = ;if extendedHint and (extTextTooltip <> '') then
      [*] = ;   textTooltip := textTooltip+gc_gui_BreakLine+gc_gui_BreakLine+extTextTooltip;
      [*] = ;
      [*] = ;_gui_ft_DisplayCommonTooltip(_gui_GetLayer(cTooltipLayer),iElmHandle,textTooltip,(display_f and 2)<>0,(display_f and 4)<>0);
      [*] = ;
      [*] = ;if gc_RecycleGUI then
      [*] = ;begin
      [*] = ;   _gui_Show(_gui_GetWindow('prov_defender_tooltip'),false);
      [*] = ;   _gui_Show(_gui_GetWindow('map_tooltip'),false);
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   _gui_RootWindowRemoveWithFade(_gui_GetWindow('prov_defender_tooltip'),0);
      [*] = ;   _gui_RootWindowRemoveWithFade(_gui_GetWindow('map_tooltip'),0);
      [*] = ;end;
      [*] = ;
      [*] = ;if (not extendedHint) and ((display_f and 2)<>0) then
      [*] = ;begin
      [*] = ;   SetIntValueByName('HintElmHandle', iElmHandle);
      [*] = ;   _gui_DelayExecuteStateOneInstance('DoOnHintGUIExt', gProfile.exthintdelay);
      [*] = ;end;
   struct.end
   OldCode : struct.begin
      [*] = ;if (iElmHandle<>0) then
      [*] = ;begin
      [*] = ;   if (textTooltip='') then
      [*] = ;   begin
      [*] = ;      var elmName : String = GetGUIElementNameByIndex(iElmHandle);
      [*] = ;      if (elmName<>'') and not SameText(elmName, 'blank') then
      [*] = ;         textTooltip := 'tooltip|'+elmName;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (iElmHandle<>0) and (textTooltip<>'') then
      [*] = ;begin
      [*] = ;   var sLocalHintExt : String = '';
      [*] = ;   var sLocalHint : String;
      [*] = ;
      [*] = ;   const cDelimiterChar = 124; // 124 == |
      [*] = ;   const cQuoteChar = 34; // 34 == "
      [*] = ;   var delimiterStringCount : Integer = _sa_GetNumSafe(textTooltip);
      [*] = ;   //var showExtHintMark : Boolean = False;
      [*] = ;   if (delimiterStringCount>=2) then
      [*] = ;   begin
      [*] = ;      var tableID,keyID : String;
      [*] = ;
      [*] = ;      _sa_Get(textTooltip,0,tableID);
      [*] = ;      _sa_Get(textTooltip,1,keyID);
      [*] = ;      if (tableID='tooltip') then
      [*] = ;      begin
      [*] = ;         sLocalHint := GetLocaleTableListItemByID(tableID, keyID);
      [*] = ;         if (sLocalHint='') then
      [*] = ;         begin
      [*] = ;            if (gFloatRegister_DoDebugHintAlpha>0) then
      [*] = ;              textTooltip := keyID
      [*] = ;            else
      [*] = ;              exit;
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;         sLocalHint := GetLocaleTableListItemByID(tableID, keyID);
      [*] = ;
      [*] = ;      if ((sLocalHint<>'') or (gFloatRegister_DoDebugHintAlpha>0)) then
      [*] = ;      begin
      [*] = ;         const cDelimiterDotChar = 46; // 46 == .
      [*] = ;         var StringTag : String = GetGUIElementStringTag(iElmHandle);
      [*] = ;         var StringTagDelim0 : String;
      [*] = ;         _gui_GetDelimiterValueByIndex(StringTag, 0, StringTagDelim0);
      [*] = ;
      [*] = ;         if IsDelimiterCharExists(StringTag, cDelimiterDotChar) then
      [*] = ;         begin
      [*] = ;            if StrExists(StringTag, 'provradial') then
      [*] = ;            begin
      [*] = ;               var text : String = GetDelimiterStringByIndex(StringTag, cDelimiterDotChar, cQuoteChar, 1);
      [*] = ;               if (text<>'') then
      [*] = ;                  sLocalHint := sLocalHint+text;
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if SameText(StringTagDelim0, 'HintMood') or SameText(StringTagDelim0, 'HintUnrest') or SameText(StringTagDelim0, 'HintUnrestMeter') then
      [*] = ;         begin
      [*] = ;            gIntRegister_MoodDummyUID := _gui_GetDelimiterIntValueByIndex(StringTag, 1);
      [*] = ;         end;
      [*] = ;
      [*] = ;         if (delimiterStringCount>=6) then
      [*] = ;         begin
      [*] = ;            var hk_command,hk_attr,temp_str : String;
      [*] = ;
      [*] = ;            _sa_Get(textTooltip,5,hk_command);
      [*] = ;            if SubStr(hk_command,1,1) = '#' then
      [*] = ;            begin
      [*] = ;               // new format
      [*] = ;               var c_str,hkey : String;
      [*] = ;               var i,n : Integer;
      [*] = ;
      [*] = ;               c_str := SubStr(hk_command,2,StrLength(hk_command));
      [*] = ;               n := _sa_GetNum_D(c_str,$2c) div 2;
      [*] = ;               temp_str := '';
      [*] = ;               for i := 0 to n-1 do
      [*] = ;               begin
      [*] = ;                  _sa_Get_D(c_str,i*2,$2c,hk_command);
      [*] = ;                  _sa_Get_D(c_str,i*2+1,$2c,hk_attr);
      [*] = ;                  _cmd_GetHotKey(StrToLowerCase(hk_command),hk_attr,hkey);
      [*] = ;                  if hkey <> '' then
      [*] = ;                     _sa_Add_D(temp_str,hkey,',');
      [*] = ;               end;
      [*] = ;            end
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               _sa_Get(textTooltip,6,hk_attr);
      [*] = ;               _cmd_GetHotKey(StrToLowerCase(hk_command),hk_attr,temp_str);
      [*] = ;            end;
      [*] = ;            if temp_str <> '' then
      [*] = ;               sLocalHint := sLocalHint + ' ('+StrToUpperCase(temp_str)+')';
      [*] = ;         end;
      [*] = ;
      [*] = ;         var keyIDExt : String = keyID+'.ext';
      [*] = ;         sLocalHintExt := GetLocaleTableListItemByID(tableID, keyIDExt);
      [*] = ;         if (sLocalHintExt='') then
      [*] = ;         begin
      [*] = ;            if (StrExists(StringTag, 'HintDef')) then
      [*] = ;            begin
      [*] = ;               keyIDExt := keyID+'.description';
      [*] = ;               sLocalHintExt := GetLocaleTableListItemByID(tableID, keyIDExt);
      [*] = ;            end
      [*] = ;            else
      [*] = ;            if StrExists(StringTag, 'HintMood') then
      [*] = ;            begin
      [*] = ;               keyIDExt := 'map_infopanel_mood.ext';
      [*] = ;               sLocalHintExt := GetLocaleTableListItemByID('tooltip', keyIDExt);
      [*] = ;            end;
      [*] = ;         end;
      [*] = ;
      [*] = ;         if extendedHint then
      [*] = ;         begin
      [*] = ;            if (sLocalHintExt<>'') then
      [*] = ;               sLocalHint := sLocalHint + gc_gui_BreakLine + gc_gui_BreakLine + sLocalHintExt
      [*] = ;            else
      [*] = ;            begin
      [*] = ;               if (gFloatRegister_DoDebugHintAlpha>0) then
      [*] = ;               begin
      [*] = ;                  if (sLocalHint='') then
      [*] = ;                     textTooltip := keyID + gc_gui_BreakLine + gc_gui_BreakLine + keyIDExt
      [*] = ;                  else
      [*] = ;                     sLocalHint := sLocalHint + gc_gui_BreakLine + gc_gui_BreakLine + tableID + '|' + keyIDExt;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;            if StrExists(sLocalHint, '%ability_power%') then
      [*] = ;            begin
      [*] = ;               var powerElmHandle : Integer = GetGUIElementIndexByNameParent('unitinfo_ability_power', iElmHandle);
      [*] = ;               if (powerElmHandle<>0) then
      [*] = ;               begin
      [*] = ;                  var abilPower : Integer = GetGUIElementTag(powerElmHandle);
      [*] = ;                  gIntRegister_AbilityPower := abilPower;
      [*] = ;               end;
      [*] = ;            end;
      [*] = ;         end
      [*] = ;         else
      [*] = ;            if (sLocalHintExt<>'') then
      [*] = ;               display_f := display_f or 2;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if sLocalHint<>'' then
      [*] = ;         textTooltip := sLocalHint;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (textTooltip<>'') then
      [*] = ;   begin
      [*] = ;      StringRegister0 := textToolTip;
      [*] = ;      MapExecuteState('StringReplaceParams');
      [*] = ;      textToolTip := StringRegister1;
      [*] = ;   end;
      [*] = ;
      [*] = ;   const firstUID = 7000;
      [*] = ;   const firstUID2 = 100;
      [*] = ;   var pressState : String = GetGUIElementPressState(GetGUIElementUnderMouse());
      [*] = ;
      [*] = ;   if (SameText(pressState, 'ShowInfoWindow'))
      [*] = ;   or (SameText(pressState, 'battle.EventControlPanelWindow')) or ((SameText(pressState, 'battle.EventUnitUpgradeWindow')) and (iElmTag>firstUID)) then
      [*] = ;     display_f := display_f or 4;
      [*] = ;
      [*] = ;   _gui_ft_DisplayCommonTooltip(_gui_GetLayer(cTooltipLayer),iElmHandle,textTooltip,(display_f and 2)<>0,(display_f and 4)<>0);
      [*] = ;
      [*] = ;      var elmProvDefenderTooltip : Integer = _gui_GetWindow('prov_defender_tooltip');
      [*] = ;      if elmProvDefenderTooltip <> 0 then
      [*] = ;         _gui_RootWindowRemoveWithFade(elmProvDefenderTooltip,0);
      [*] = ;
      [*] = ;      var elmMapTooltip : Integer = _gui_GetWindow('map_tooltip');
      [*] = ;      if elmMapTooltip <> 0 then
      [*] = ;         _gui_RootWindowRemoveWithFade(elmMapTooltip,0);
      [*] = ;
      [*] = ;      if (not extendedHint) and ((sLocalHintExt<>'') or ((display_f and 2)<>0)) then
      [*] = ;      begin
      [*] = ;         SetIntValueByName('HintElmHandle', iElmHandle);
      [*] = ;         _gui_DelayExecuteStateOneInstance('DoOnHintGUIExt', 1.0);
      [*] = ;      end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   GUIDelayExecuteState('', 0);
      [*] = ;end;
   struct.end
section.end

