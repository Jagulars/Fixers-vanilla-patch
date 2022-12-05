section.begin
   Name = ResetHint
   Code : struct.begin
      [*] = ;var tooltipHnd : Integer = GetGUIElementIndexByNameParent('hintWindow', _gui_GetLayer(cTooltipLayer));
      [*] = ;if (tooltipHnd<>0) then
      [*] = ;begin
      [*] = ;   if gc_RecycleGUI and _gui_IsRecycledElement(tooltipHnd) then
      [*] = ;      _gui_Show(tooltipHnd, false)
      [*] = ;   else
      [*] = ;      RemoveGUIElement(tooltipHnd);
      [*] = ;end;
      [*] = ;gBoolRegister_ShowExtendedHint := False;
      [*] = ;gBoolRegister_DebugForceExtendedHint := False;
      [*] = ;tooltipHnd := GUIDelayTimeExecFind('DoOnHintGUIExt');
      [*] = ;if tooltipHnd >= 0 then
      [*] = ;   GUIDelayTimeExecDelete(tooltipHnd, False);
      [*] = ;//if (tooltipHnd<>0) and (GetGUIElementVisible(tooltipHnd)) then
      [*] = ;//SetGUIElementVisible(tooltipHnd, False);
      [*] = ;//var delayIndex : Integer = GUIDelayTimeExecFind('DoOnHintGUIExt');
      [*] = ;//GUIDelayTimeExecDelete(delayIndex, False);
   struct.end
section.end

