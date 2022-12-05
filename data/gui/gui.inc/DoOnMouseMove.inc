section.begin
   Name = DoOnMouseMove
   Code : struct.begin
      [*] = ;const cExtHintState = 'DoOnHintGUIExt';
      [*] = ;
      [*] = ;procedure RemoveTooltipWindow(const wnm : String);
      [*] = ;begin
      [*] = ;   var tooltipHnd : Integer = _gui_GetWindow(wnm);
      [*] = ;   if tooltipHnd <> 0 then
      [*] = ;   begin
      [*] = ;      if gc_RecycleGUI then
      [*] = ;         _gui_Show(tooltipHnd,false)
      [*] = ;      else
      [*] = ;         _gui_RootWindowRemoveWithFade(tooltipHnd,0);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;var px, py, cx, cy, elemC, tooltipHnd : Integer;
      [*] = ;
      [*] = ;GetGUIPreviousMouseCoord(px, py);
      [*] = ;GetGUICurrentMouseCoord(cx, cy);
      [*] = ;SetIntValueByName('MouseDirectionX', cx-px);
      [*] = ;SetIntValueByName('MouseDirectionY', cy-py);
      [*] = ;elemC := GetGUIElementUnderMouse();
      [*] = ;
      [*] = ;if (gBoolRegister_GUIForceMouseMove) or ((px<>cx) or (py<>cy)) then
      [*] = ;begin
      [*] = ;   //if (px=cx) and (py=cy) then _log_Values('CX|CY|E',cx,cy,elemC,0,0,0);
      [*] = ;   gBoolRegister_GUIForceMouseMove := False;
      [*] = ;   if (elemC<>0) then
      [*] = ;   begin
      [*] = ;      tooltipHnd := GetGUIElementIndexByNameParent('hintWindow', _gui_GetLayer(cTooltipLayer));
      [*] = ;      if (tooltipHnd<>0) then
      [*] = ;      begin
      [*] = ;         _gui_AlignWindowByCursor_VVK(tooltipHnd);
      [*] = ;
      [*] = ;         if (GUIDelayTimeExecFind(cExtHintState)>=0) then
      [*] = ;            _gui_DelayExecuteStateOneInstance(cExtHintState, gProfile.exthintdelay);
      [*] = ;      end;
      [*] = ;      
      [*] = ;      RemoveTooltipWindow('prov_defender_tooltip');
      [*] = ;   end;
      [*] = ;   RemoveTooltipWindow('battle_tooltip');
      [*] = ;   RemoveTooltipWindow('map_tooltip');
      [*] = ;
      [*] = ;   if (gIntRegister_GUIScrollSliderHandle<>0) then
      [*] = ;   begin
      [*] = ;      if (GetValueByName('Press')='d') and (GetValueByName('Status')='geMouseDown') then
      [*] = ;         GUIExecuteState(GetGUIElementPressState(gIntRegister_GUIScrollSliderHandle))
      [*] = ;      else
      [*] = ;         GUIExecuteState('DoMouseUnPressSliderControl');
      [*] = ;   end;
      [*] = ;
      [*] = ;   tooltipHnd := GetIntValueByName('DragElement');
      [*] = ;   if (tooltipHnd <> 0) then
      [*] = ;      SetGUIElementPosition(tooltipHnd, cx+2, cy+2);
      [*] = ;
      [*] = ;   _gui_ft_ProcessMouseMove(elemC,cx,cy);
      [*] = ;
      [*] = ;   case gIntRegister_CurGameMode of
      [*] = ;      gc_GameModeStrategy : GUIExecuteState('map.DoOnMouseMove');
      [*] = ;      gc_GameModeTactics : GUIExecuteState('battle.DoOnMouseMove');
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

