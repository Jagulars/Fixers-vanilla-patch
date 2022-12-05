section.begin
   Name = map.UpdateMouseMove
   Code : struct.begin
      [*] = ;var _log : Boolean = false;
      [*] = ;
      [*] = ;var x, y, z : Float;
      [*] = ;var arX, arY : array [0..5] of Float;
      [*] = ;var pStratHexCell : Integer = gIntRegister_MapUnderCursorHex;
      [*] = ;var needUpdate : Boolean = false;
      [*] = ;var mouseX, mouseY : Integer;
      [*] = ;var windowHandle : Integer;
      [*] = ;var top : Integer = _gui_GetLayerI();
      [*] = ;
      [*] = ;GetCurrentMouseWorldCoord(x, y, z);
      [*] = ;GetGUICurrentMouseCoord(mouseX, mouseY);
      [*] = ;
      [*] = ;if pStratHexCell <> 0 then
      [*] = ;begin
      [*] = ;   var pVertices : Integer = ParserSelectByHandleByKey(pStratHexCell, 'Vertices');
      [*] = ;   var i : Integer;
      [*] = ;
      [*] = ;   for i := 0 to 5 do
      [*] = ;   begin
      [*] = ;      var pVertice : Integer = ParserSelectByHandleByIndex(pVertices, i);
      [*] = ;      var x0 : Float = ParserGetFloatValueByKeyByHandle(pVertice, 'X');
      [*] = ;      var z0 : Float = ParserGetFloatValueByKeyByHandle(pVertice, 'Y');
      [*] = ;
      [*] = ;      arX[i] := x0;
      [*] = ;      arY[i] := z0;
      [*] = ;   end;
      [*] = ;
      [*] = ;   if not IsPointInHex(x, z, arX[0], arY[0], arX[1], arY[1], arX[2], arY[2], arX[3], arY[3], arX[4], arY[4], arX[5], arY[5]) then
      [*] = ;      needUpdate := true;
      [*] = ;end
      [*] = ;else
      [*] = ;   needUpdate := true;
      [*] = ;
      [*] = ;if needUpdate and (GetGUIElementUnderMouse() = 0) and (_gui_RootWindowGetTopmost(cRootWindowModal) = 0) and (gIntRegister_GUICurCastleMode = 0) and (GetTrackNodeCount()>0) then
      [*] = ;begin
      [*] = ;   FloatRegister0 := x;
      [*] = ;   FloatRegister1 := z;
      [*] = ;   MapExecuteState('map.GetHexByCoord');
      [*] = ;   var MapUnderCursorHex : Integer = IntRegister0;
      [*] = ;
      [*] = ;   var isPlayable : Boolean = false;
      [*] = ;   var pProvFog : Integer = ParserSelectByHandleByKey(MapUnderCursorHex, 'Fog');
      [*] = ;   var fog : Integer = ParserGetIntValueByIndexByHandle(pProvFog, gIntRegister_MapMyPlayerIndex);
      [*] = ;
      [*] = ;   var prevMapUnderCursorHex : Integer = gIntRegister_MapUnderCursorHex;
      [*] = ;   gIntRegister_MapUnderCursorHex := MapUnderCursorHex;
      [*] = ;   var dummyUID : Integer = ParserGetIntValueByKeyByHandle(MapUnderCursorHex, 'DummyUID');
      [*] = ;   var dummyHandle : Integer = GetGameObjectHandleByUniqueId(dummyUID);
      [*] = ;   if ((fog < 1) or (not gGame.fog)) and (MapUnderCursorHex <> 0) and (dummyHandle <> 0) then
      [*] = ;   begin
      [*] = ;      GameObjectExecuteStateByHandle(dummyHandle, 'IsPlayable');
      [*] = ;      isPlayable := BoolRegister0;
      [*] = ;
      [*] = ;      if (isPlayable) then
      [*] = ;         GUIExecuteState('map.DrawUnderCursorHex');
      [*] = ;   end;
      [*] = ;
      [*] = ;   if (prevMapUnderCursorHex<>MapUnderCursorHex) then
      [*] = ;   begin
      [*] = ;      gBoolRegister_GUIUpdateInterfacePanel := True;
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gIntRegister_GUICurCastleMode<>0) then
      [*] = ;begin
      [*] = ;   if (GetGUIElementUnderMouse()=0) then
      [*] = ;   begin
      [*] = ;      GUIExecuteState('map.GetBuildIDUnderMouse');
      [*] = ;      gIntRegister_CastleUnderCursorBuildID := IntRegister0;
      [*] = ;   end
      [*] = ;   else
      [*] = ;      gIntRegister_CastleUnderCursorBuildID := 0;
      [*] = ;end;
      [*] = ;
      [*] = ;GUIExecuteState('map.UpdateCursor');
      [*] = ;
      [*] = ;var lastProvHudHandle : Integer = GetIntValueByName('ProvHUDHandle');
      [*] = ;if (GetGUIElementUnderMouse()=0) and (gIntRegister_GUICurCastleMode=0) then
      [*] = ;begin
      [*] = ;   if (lastProvHudHandle=0) then
      [*] = ;   begin
      [*] = ;      if (GetIntValueByName('DragElement')=0) then
      [*] = ;         GUIExecuteState('map.CreateProvinceTooltip');
      [*] = ;      GUIExecuteState('map.CreateTooltip');
      [*] = ;   end;
      [*] = ;end
      [*] = ;else
      [*] = ;begin
      [*] = ;   var delayInd : Integer = GUIDelayTimeExecFind('map.CreateProvinceTooltipExt');
      [*] = ;   if (delayInd>=0) then
      [*] = ;      GUIDelayTimeExecDelete(delayInd, False);
      [*] = ;end;
      [*] = ;
      [*] = ;{if (GetGUIElementUnderMouse()<>0) then
      [*] = ;begin
      [*] = ;   var ehd : Integer = GetGUIElementUnderMouse();
      [*] = ;   var elmName : String = GetGUIElementNameByIndex(ehd);
      [*] = ;   var tag : Integer = GetGUIElementTag(ehd);
      [*] = ;
      [*] = ;   if SameText(elmName, 'outerbuild_icon') then
      [*] = ;   begin
      [*] = ;      var buildID : Integer = tag-gc_gui_outerbuildings_btnBaseTag;
      [*] = ;      IntRegister0 := buildID;
      [*] = ;      ExecuteState('ShowOuterBuildTooltip');
      [*] = ;      if IntRegister0 <> 0 then
      [*] = ;         _gui_RootWindowAddExt(IntRegister0,cRootWindowModal,0,cRootWindowAttrModalNoBlack,'');
      [*] = ;         //_gui_RootWindowAddExt(IntRegister0,_gui_RootWindowGetParentZOrder(elmHandle),0,cRootWindowAttrModalNoBlack);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      IntRegister0 := 0;
      [*] = ;      ExecuteState('ShowOuterBuildTooltip');
      [*] = ;   end;
      [*] = ;
      [*] = ;   if SameText(elmName, 'defender_icon') then
      [*] = ;   begin
      [*] = ;      var defenderID : Integer = tag-gc_gui_defenders_btnBaseTag;
      [*] = ;      IntRegister0 := defenderID;
      [*] = ;      ExecuteState('ShowDefenderTooltip');
      [*] = ;      if IntRegister0 <> 0 then
      [*] = ;         _gui_RootWindowAddExt(IntRegister0,cRootWindowModal,0,cRootWindowAttrModalNoBlack,'');
      [*] = ;         //_gui_RootWindowAddExt(IntRegister0,_gui_RootWindowGetParentZOrder(elmHandle),0,cRootWindowAttrModalNoBlack);
      [*] = ;   end
      [*] = ;   else
      [*] = ;   begin
      [*] = ;      IntRegister0 := 0;
      [*] = ;      ExecuteState('ShowDefenderTooltip');
      [*] = ;   end;
      [*] = ;
      [*] = ;end;}
      [*] = ;
      [*] = ;GUIExecuteState('map.ProvHUDControl');
      [*] = ;if (not gBoolRegister_MapTurnFinished) or (GetGUIElementUnderMouse()<>0) or (lastProvHudHandle<>0) or (GetIntValueByName('DragElement')<>0) then
      [*] = ;begin
      [*] = ;   var elmProvDefenderTooltip : Integer = _gui_GetWindow('prov_defender_tooltip');
      [*] = ;   if elmProvDefenderTooltip <> 0 then
      [*] = ;   begin
      [*] = ;      if gc_RecycleGUI then
      [*] = ;         _gui_Show(elmProvDefenderTooltip,false)
      [*] = ;      else
      [*] = ;         _gui_RootWindowRemoveWithFade(elmProvDefenderTooltip,0);
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (not gBoolRegister_MapTurnFinished) or (GetGUIElementUnderMouse()<>0) or (lastProvHudHandle<>0) then
      [*] = ;begin
      [*] = ;   var elmMapTooltip : Integer = _gui_GetWindow('map_tooltip');
      [*] = ;   if elmMapTooltip <> 0 then
      [*] = ;   begin
      [*] = ;      if gc_RecycleGUI then
      [*] = ;         _gui_Show(elmMapTooltip,false)
      [*] = ;      else
      [*] = ;         _gui_RootWindowRemoveWithFade(elmMapTooltip,0);
      [*] = ;   end;
      [*] = ;end;
   struct.end
section.end

