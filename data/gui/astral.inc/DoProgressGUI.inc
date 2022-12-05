section.begin
   Name = DoProgressGUI
   Code : struct.begin
      [*] = ;//var _log_name : String = 'ASTRAL.INC\DOPROGRESSGUI';
      [*] = ;//var _log_trace : Integer = $10000;
      [*] = ;//_gv_traceState(_log_name,_log_trace);
      [*] = ;  
      [*] = ;GUIExecuteState('DoProgressMusic');
      [*] = ;
      [*] = ;GUIExecuteState('FadeControl');
      [*] = ;GUIExecuteState('VVK.DoProgressGUI');
      [*] = ;if (not GetBoolValueByName('StartBattleFlag')) then
      [*] = ;   GUIExecuteState('ControlCamera')
      [*] = ;else
      [*] = ;   GUIExecuteState('StartBattle');
      [*] = ;
      [*] = ;if (_gv_GetAstralLock() = 0) and GetBoolValueByName('AttackShardFlag') then
      [*] = ;   GUIExecuteState('DoAttackShard');
      [*] = ;
      [*] = ;// gui development tools
      [*] = ;if GetUserBoolValue('GUIDebug') then
      [*] = ;begin
      [*] = ;   var iTag : Integer = GetIntValueByName('Tag');
      [*] = ;   case iTag of
      [*] = ;      661: gIntRegister_dbgX := gIntRegister_dbgX-1;
      [*] = ;      662: gIntRegister_dbgX := gIntRegister_dbgX+1;
      [*] = ;      663: gIntRegister_dbgY := gIntRegister_dbgY-1;
      [*] = ;      664: gIntRegister_dbgY := gIntRegister_dbgY+1;
      [*] = ;      671: gIntRegister_dbgX := gIntRegister_dbgX-10;
      [*] = ;      672: gIntRegister_dbgX := gIntRegister_dbgX+10;
      [*] = ;      673: gIntRegister_dbgY := gIntRegister_dbgY-10;
      [*] = ;      674: gIntRegister_dbgY := gIntRegister_dbgY+10;
      [*] = ;      681: gIntRegister_dbgZ := gIntRegister_dbgZ-1;
      [*] = ;      682: gIntRegister_dbgZ := gIntRegister_dbgZ+1;
      [*] = ;   end;
      [*] = ;   if (gFloatRegister_gDbgFloat0PrevValue <> gIntRegister_dbgX) or (gFloatRegister_gDbgFloat1PrevValue <> gIntRegister_dbgY) or (gFloatRegister_gDbgFloat2PrevValue <> gIntRegister_dbgZ) then
      [*] = ;   begin
      [*] = ;      //ExecuteState('ShowFinishCampaign');
      [*] = ;      //SetIntValueByName('ElementHandle', GetGUIElementUnderMouse);
      [*] = ;      //ExecuteState('OnMouseEnter');
      [*] = ;   end;
      [*] = ;
      [*] = ;   gFloatRegister_gDbgFloat0PrevValue := gIntRegister_dbgX;
      [*] = ;   gFloatRegister_gDbgFloat1PrevValue := gIntRegister_dbgY;
      [*] = ;   gFloatRegister_gDbgFloat2PrevValue := gIntRegister_dbgZ;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gc_demoVersion=1) then
      [*] = ;   GUIExecuteState('UpdateHUDRestict');
      [*] = ;
      [*] = ;if (gc_demoVersion=1) and (gIntRegister_DemoQueryCampaign=0) then
      [*] = ;begin
      [*] = ;   var queryWindow : Integer = _gui_GetWindow('queryWindow');
      [*] = ;   if (not GetGUIElementVisible(queryWindow)) then
      [*] = ;   begin
      [*] = ;      StringRegister0 := '12003';
      [*] = ;      GUIExecuteState('RequestQueryWindow');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gStringRegister_CampaignQueryID<>'') then
      [*] = ;begin
      [*] = ;   var queryWindow : Integer = _gui_GetWindow('queryWindow');
      [*] = ;   if (not GetGUIElementVisible(queryWindow)) then
      [*] = ;   begin
      [*] = ;      StringRegister0 := gStringRegister_CampaignQueryID;
      [*] = ;      GUIExecuteState('RequestQueryWindow');
      [*] = ;      gStringRegister_CampaignQueryID := '';
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gIntRegister_CurQueryHandle = 0) and gBoolRegister_GUIShowFinishCampaign and (gIntRegister_GUIShowFinishCampaignIndex>=0) and (not GetGUIElementVisible(GetGUIElementIndexByNameParent('ShowFinishCampaign', _gui_GetLayerI()))) then
      [*] = ;begin
      [*] = ;   IntRegister0 := gIntRegister_GUIShowFinishCampaignIndex;
      [*] = ;   GUIExecuteState('ShowFinishCampaign');
      [*] = ;end;
      [*] = ;
      [*] = ;if gBoolRegister_GUIUpdateInterfacePanel then
      [*] = ;begin
      [*] = ;   GUIExecuteState('CreateControlPanel');
      [*] = ;   gBoolRegister_GUIUpdateInterfacePanel := false;
      [*] = ;end;
      [*] = ;
      [*] = ;if gBoolRegister_GUISaveAstral then
      [*] = ;begin
      [*] = ;   gBoolRegister_GUISaveAstral := false;
      [*] = ;   StringRegister0 := 'campaign';
      [*] = ;   BoolRegister0 := True;
      [*] = ;   IntRegister0 := 0;
      [*] = ;   MapExecuteState('SaveMap');
      [*] = ;end;
      [*] = ;
      [*] = ;if (gBoolRegister_GUIProgressOnceOnGUIDoCreate) then
      [*] = ;begin
      [*] = ;   if gProfile.simplegraphics then
      [*] = ;      _actor_CheckSimplifiedGraphics();
      [*] = ;   gBoolRegister_GUIProgressOnceOnGUIDoCreate := False;
      [*] = ;end;
      [*] = ;
      [*] = ;_gui_ClampingMouseToScreen();
      [*] = ;
      [*] = ;//_gv_traceState(_log_name,$1000000 or _log_trace);
   struct.end
section.end

