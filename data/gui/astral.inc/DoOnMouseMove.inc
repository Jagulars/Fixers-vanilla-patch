section.begin
   Name = DoOnMouseMove
   Code : struct.begin
      [*] = ;const cExtHintState = 'DoOnHintGUIExt';
      [*] = ;var mouseX,mouseY,elem,px,py : Integer;
      [*] = ;
      [*] = ;elem := GetGUIElementUnderMouse();
      [*] = ;GetGUIPreviousMouseCoord(px, py);
      [*] = ;GetGUICurrentMouseCoord(mouseX, mouseY);
      [*] = ;SetIntValueByName('MouseDirectionX', mouseX-px);
      [*] = ;SetIntValueByName('MouseDirectionY', mouseY-py);
      [*] = ;
      [*] = ;if (gBoolRegister_GUIForceMouseMove) or ((px<>mouseX) or (py<>mouseY)) then
      [*] = ;begin
      [*] = ;   gIntRegister_AstralUnderCursorShard := 0;
      [*] = ;   gBoolRegister_GUIForceMouseMove := False;
      [*] = ;
      [*] = ;   if (elem <> 0) then
      [*] = ;   begin
      [*] = ;      var tooltipHnd : Integer = GetGUIElementIndexByNameParent('hintWindow', _gui_GetLayer(cTooltipLayer));
      [*] = ;      var elmName : String = GetGUIElementNameByIndex(elem);
      [*] = ;      var top : Integer = _gui_GetLayerI();
      [*] = ;      var windowHandle : Integer;
      [*] = ;
      [*] = ;      if tooltipHnd <> 0 then
      [*] = ;      begin
      [*] = ;         _gui_AlignWindowByCursor_VVK(tooltipHnd);
      [*] = ;         if (GUIDelayTimeExecFind(cExtHintState)>=0) then
      [*] = ;            _gui_DelayExecuteStateOneInstance(cExtHintState, gProfile.exthintdelay);
      [*] = ;      end;
      [*] = ;
      [*] = ;      {if (elmName='bonusdefender') then
      [*] = ;      begin
      [*] = ;         var parentHnd : Integer = GetGUIElementParentByIndex(elem);
      [*] = ;         var parentTag : Integer = GetGUIElementTag(parentHnd);
      [*] = ;         if (parentTag>0) then
      [*] = ;         begin
      [*] = ;            IntRegister0 := parentTag;
      [*] = ;            ExecuteState('ShowDefenderTooltip');
      [*] = ;            if IntRegister0 <> 0 then
      [*] = ;               _gui_RootWindowAddExt(IntRegister0,_gui_RootWindowGetParentZOrder(elem),0,cRootWindowAttrModalNoBlack,'');
      [*] = ;         end;
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         if SameText(elmName, 'defender_icon') then
      [*] = ;         begin
      [*] = ;            var tag : Integer = GetGUIElementTag(elem);
      [*] = ;            var defenderID : Integer = tag-gc_gui_defenders_btnBaseTag;
      [*] = ;
      [*] = ;            IntRegister0 := defenderID;
      [*] = ;            ExecuteState('ShowDefenderTooltip');
      [*] = ;            if IntRegister0 <> 0 then
      [*] = ;               _gui_RootWindowAddExt(IntRegister0,_gui_RootWindowGetParentZOrder(elem),0,cRootWindowAttrModalNoBlack,'');
      [*] = ;         end
      [*] = ;         else
      [*] = ;         begin
      [*] = ;            IntRegister0 := 0;
      [*] = ;            ExecuteState('ShowDefenderTooltip');
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;
      [*] = ;      if SameText(elmName, 'outerbuild_icon') then
      [*] = ;      begin
      [*] = ;         var tag : Integer = GetGUIElementTag(elem);
      [*] = ;         var buildID : Integer = tag-gc_gui_outerbuildings_btnBaseTag;
      [*] = ;
      [*] = ;         IntRegister0 := buildID;
      [*] = ;         ExecuteState('ShowOuterBuildTooltip');
      [*] = ;         if IntRegister0 <> 0 then
      [*] = ;            _gui_RootWindowAddExt(IntRegister0,_gui_RootWindowGetParentZOrder(elem),0,cRootWindowAttrModalNoBlack,'');
      [*] = ;      end
      [*] = ;      else
      [*] = ;      begin
      [*] = ;         IntRegister0 := 0;
      [*] = ;         ExecuteState('ShowOuterBuildTooltip');
      [*] = ;      end;}
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      var goHandle : Integer = GetRayCastIntersectGameObjectFromMouseRay();
      [*] = ;      var captured : Boolean = GetGameObjectBoolValueIndByHandle(goHandle, gc_astral_GOStack_bCaptured);
      [*] = ;
      [*] = ;      if (goHandle <> 0) and (not captured) then
      [*] = ;      begin
      [*] = ;         var uid : Integer = GetGameObjectUniqueIdByHandle(goHandle);
      [*] = ;         var shardInd : Integer = _shard_GetShardByUID(uid);
      [*] = ;         if shardInd >= 0 then
      [*] = ;         begin
      [*] = ;            var plInd : Integer = gShards[shardInd].ipPlayer;
      [*] = ;            var isMain : Boolean = _shard_IsMain(gShards[shardInd]);
      [*] = ;
      [*] = ;            if (plInd < 0) or isMain then
      [*] = ;               gIntRegister_AstralUnderCursorShard := uid;
      [*] = ;         end;
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;
      [*] = ;   _gui_ft_ProcessMouseMove(elem,mouseX,mouseY);
      [*] = ;
      [*] = ;   ExecuteState('UpdateCursor');
      [*] = ;   ExecuteState('CreateShardTooltip');
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
      [*] = ;      ExecuteState('DoMouseUnPressSliderControl');
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

