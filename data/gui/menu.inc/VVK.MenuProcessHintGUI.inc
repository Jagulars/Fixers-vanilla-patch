section.begin
   Name = VVK.MenuProcessHintGUI
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
      [*] = ;if _gui_ft_ProcessHintRequest(iElmHandle,extendedHint,'OnHintExt',gProfile.exthintdelay,display_f,temp_str,temp_str_e) then
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
      [*] = ;RemoveGUIChildren(_gui_GetLayer(cTooltipLayer));
      [*] = ;
      [*] = ;if textTooltip = '' then
      [*] = ;begin
      [*] = ;   GUIDelayExecuteState('', 0);
      [*] = ;   exit;
      [*] = ;end;
      [*] = ;
      [*] = ;pressState := GetGUIElementPressState(GetGUIElementUnderMouse());
      [*] = ;
      [*] = ;if extendedHint and (extTextTooltip <> '') then
      [*] = ;   textTooltip := textTooltip+gc_gui_BreakLine+gc_gui_BreakLine+extTextTooltip;
      [*] = ;
      [*] = ;_gui_ft_DisplayCommonTooltip(_gui_GetLayer(cTooltipLayer),iElmHandle,textTooltip,(display_f and 2)<>0,(display_f and 4)<>0);
      [*] = ;
      [*] = ;if (not extendedHint) and ((display_f and 2)<>0) then
      [*] = ;begin
      [*] = ;   SetIntValueByName('HintElmHandle', iElmHandle);
      [*] = ;   _gui_DelayExecuteStateOneInstance('OnHintExt', gProfile.exthintdelay);
      [*] = ;end;
   struct.end
section.end

