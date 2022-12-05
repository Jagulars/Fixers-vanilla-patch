section.begin
   Name = OnMouseMove
   UsedFileName =
   Code : struct.begin
      [*] = ;const cExtHintState = 'DoOnHintGUIExt';
      [*] = ;var mouseX,mouseY,elem,px,py : Integer;
      [*] = ;
      [*] = ;GetGUIPreviousMouseCoord(px, py);
      [*] = ;GetGUICurrentMouseCoord(mouseX, mouseY);
      [*] = ;SetIntValueByName('MouseDirectionX', mouseX-px);
      [*] = ;SetIntValueByName('MouseDirectionY', mouseY-py);
      [*] = ;
      [*] = ;if (gBoolRegister_GUIForceMouseMove) or ((px<>mouseX) or (py<>mouseY)) then
      [*] = ;begin
      [*] = ;   gBoolRegister_GUIForceMouseMove := False;
      [*] = ;
      [*] = ;   elem := GetGUIElementUnderMouse();
      [*] = ;   if (elem<>0) then
      [*] = ;   begin
      [*] = ;      var tooltipHnd : Integer = GetGUIElementIndexByNameParent('hintWindow', _gui_GetLayer(cTooltipLayer));
      [*] = ;      if (tooltipHnd<>0) then
      [*] = ;      begin
      [*] = ;         _gui_AlignWindowByCursor_VVK(tooltipHnd);
      [*] = ;         if (GUIDelayTimeExecFind(cExtHintState)>=0) then
      [*] = ;            _gui_DelayExecuteStateOneInstance(cExtHintState, gProfile.exthintdelay);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   _gui_ft_ProcessMouseMove(GetGUIElementUnderMouse(),mouseX,mouseY);
      [*] = ;
      [*] = ;   GUIExecuteState('DoUpdateCursor');
      [*] = ;
      [*] = ;   if (gIntRegister_GUIScrollSliderHandle<>0) then
      [*] = ;   begin
      [*] = ;      if ((GetValueByName('Press')='d') and (GetValueByName('Status')='geMouseDown')) or
      [*] = ;      ((GetValueByName('Press')='in') and (GetValueByName('Status')='fade')) then
      [*] = ;      begin
      [*] = ;         var eventState : String = GetGUIElementPressState(gIntRegister_GUIScrollSliderHandle);
      [*] = ;         ExecuteState(eventState);
      [*] = ;      end
      [*] = ;      else
      [*] = ;         ExecuteState('DoMouseUnPressSliderControl');
      [*] = ;   end;
      [*] = ;
      [*] = ;   elem := GetIntValueByName('DragElement');
      [*] = ;   if (elem<>0) then
      [*] = ;      SetGUIElementPosition(elem, mouseX, mouseY);
      [*] = ;end;
   struct.end
section.end

