section.begin
   Name = DoCreate
   Code : struct.begin
      [*] = ;var _log_name : String = 'GUI.INC\DOCREATE';
      [*] = ;var _log_trace : Integer = $10001;
      [*] = ;_gv_traceState(_log_name+'[InterfaceLayer element count: '+IntToStr(GetGUIElementChildrenCount(_gui_GetLayerI))+' TooltipLayer element count: '+IntToStr(GetGUIElementChildrenCount(_gui_GetLayer(cTooltipLayer)))+']',_log_trace);
      [*] = ;
      [*] = ;GUIClearElements();
      [*] = ;_gui_ClearLayers();
      [*] = ;SetRecordEnabled(False);
      [*] = ;
      [*] = ;//TEST CODE : For hinting tutor
      [*] = ;{if GetUserBoolValue('Debug') then
      [*] = ;begin
      [*] = ;   var i : Integer;
      [*] = ;   for i:=0 to 100 do
      [*] = ;   begin
      [*] = ;      var qmTriggerState : Integer = StateMachineGetIntValueByName(QueryMachineGetStateMachineHandle, 'msg.'+IntToStr(i));
      [*] = ;      if (qmTriggerState>0) then
      [*] = ;         StateMachineSetIntValueByName(QueryMachineGetStateMachineHandle, 'msg.'+IntToStr(i), 0);
      [*] = ;
      [*] = ;      qmTriggerState := StateMachineGetIntValueByName(QueryMachineGetStateMachineHandle, 'blk.'+IntToStr(i));
      [*] = ;      if (qmTriggerState>0) then
      [*] = ;         StateMachineSetIntValueByName(QueryMachineGetStateMachineHandle, 'blk.'+IntToStr(i), 0);
      [*] = ;
      [*] = ;      qmTriggerState := StateMachineGetIntValueByName(QueryMachineGetStateMachineHandle, 'hnt.'+IntToStr(i));
      [*] = ;      if (qmTriggerState>0) then
      [*] = ;         StateMachineSetIntValueByName(QueryMachineGetStateMachineHandle, 'hnt.'+IntToStr(i), 0);
      [*] = ;
      [*] = ;      qmTriggerState := StateMachineGetIntValueByName(QueryMachineGetStateMachineHandle, 'tut.'+IntToStr(i));
      [*] = ;      if (qmTriggerState>0) then
      [*] = ;         StateMachineSetIntValueByName(QueryMachineGetStateMachineHandle, 'tut.'+IntToStr(i), 0);
      [*] = ;   end;
      [*] = ;end;}
      [*] = ;
      [*] = ;SetCameraPropertiesFromFile('.\data\cameras\camera.cfg');
      [*] = ;
      [*] = ;if (gIntRegister_GUIShardGameMode = gc_gui_ModeMap) and (gIntRegister_GUICurCastleMode <> 0) then
      [*] = ;begin
      [*] = ;   LogI('Looks like we were pushed to game from editor while switch to editor was in a castle mode.');
      [*] = ;   gIntRegister_GUICurCastleMode := 0;
      [*] = ;   if GetCameraExist('@lastStratCamera') then
      [*] = ;   begin
      [*] = ;      SetCameraInfoSmoothingChange(false);
      [*] = ;      CameraInfoLoadToCurrentView('@lastStratCamera');
      [*] = ;      SetCameraInfoSmoothingChange(true);
      [*] = ;      GUIExecuteState('DoBlendLighting');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;if (gProfile.lightchange>2) then
      [*] = ;begin
      [*] = ;   SetMapFloatValue('LightTime', 0);
      [*] = ;   GUIExecuteState('DoBlendLighting');
      [*] = ;end;
      [*] = ;
      [*] = ;if (gIntRegister_GUICurCastleMode <> 0) then
      [*] = ;begin
      [*] = ;   LogI('Switch to castle mode from mode '+IntToStr(gIntRegister_GUIShardGameMode));
      [*] = ;   IntRegister0 := gc_gui_ModeMap;
      [*] = ;   FloatRegister0 := gc_gui_FadeTime0_4;
      [*] = ;   StringRegister0 := '-1';
      [*] = ;   GUIExecuteState('VVK.SwitchGameMode');
      [*] = ;end;
      [*] = ;
      [*] = ;{if GetUserValue('UserBattleHUDMode') = '' then
      [*] = ;begin
      [*] = ;   SetUserIntValue('UserBattleHUDMode', 0);
      [*] = ;   gIntRegister_UserBattleHUDMode := 0;
      [*] = ;end
      [*] = ;else
      [*] = ;   gIntRegister_UserBattleHUDMode := GetUserIntValue('UserBattleHUDMode');}
      [*] = ;
      [*] = ;gBoolRegister_StandHeroAtProvCenter := False;
      [*] = ;
      [*] = ;StringRegister0 := '';
      [*] = ;MapExecuteState('ResizeCamera');
      [*] = ;
      [*] = ;SetCameraElasticTargetObject(0);
      [*] = ;SetCameraElasticMoveTurnOff();
      [*] = ;SetCameraElasticRotationTurnOff();
      [*] = ;SetCameraControlMode('ccmNone');
      [*] = ;SetCameraInfoSmoothingChange(false);
      [*] = ;SetCameraBounded(false);
      [*] = ;SetCameraDynamicFocalLength(true);
      [*] = ;
      [*] = ;SetGUIBaseControlVisible(true);
      [*] = ;
      [*] = ;if GetMapValue('StartTime') = '' then
      [*] = ;   SetMapFloatValue('StartTime', GetCurrentTime());
      [*] = ;
      [*] = ;GUIExecuteState('GUIInitialize');
      [*] = ;GUIExecuteState('SwitchToGame');
      [*] = ;
      [*] = ;if gIntRegister_CurGameMode = gc_GameModeStrategy then
      [*] = ;  GUIExecuteState('map.DoCreate');
      [*] = ;
      [*] = ;SetGUIEventStateOnKeyDown('');
      [*] = ;
      [*] = ;GUIExecuteState('lan.DoCreate');
      [*] = ;
      [*] = ;if (gBoolRegister_IsHotSeat) and (gIntRegister_CurGameMode<>gc_GameModeTactics) then
      [*] = ;   GUIExecuteState('map.SwitchToBattle');
      [*] = ;
      [*] = ;if (gIntRegister_GUIRouteOnGUIRestart<>0) then
      [*] = ;begin
      [*] = ;   case gIntRegister_GUIRouteOnGUIRestart of
      [*] = ;      1 : begin
      [*] = ;         GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;         gIntRegister_GUIRouteOnGUIRestart := 0;
      [*] = ;         GUIExecuteState('ShowSettings');
      [*] = ;         _gui_FadeWindow_VVK(_gui_GetWindow('Settings'),0,0);
      [*] = ;      end;
      [*] = ;      2 : begin
      [*] = ;         GUIExecuteState('GUIInvokeMouseMove');
      [*] = ;         gIntRegister_GUIRouteOnGUIRestart := 0;
      [*] = ;         GUIExecuteState('ShowSettings');
      [*] = ;         _gui_FadeWindow_VVK(_gui_GetWindow('Settings'),0,0);
      [*] = ;
      [*] = ;         const cSwitchResolutionApprove = 401;
      [*] = ;         const cSwitchResolutionCancel = 402;
      [*] = ;         _gui_ShowQuestionDialog('menu|98', 'EventSettings', cSwitchResolutionApprove, 'EventSettings', cSwitchResolutionCancel, true, false);
      [*] = ;      end;
      [*] = ;   end;
      [*] = ;   //GUIDelayExecuteState('GUIInvokeMouseMove', 1);
      [*] = ;end;
      [*] = ;
      [*] = ;//_gui_UpdateSettingsLowest(gProfile.settingslowest);
      [*] = ;
      [*] = ;_gv_traceState(_log_name+'[InterfaceLayer element count: '+IntToStr(GetGUIElementChildrenCount(_gui_GetLayerI))+' TooltipLayer element count: '+IntToStr(GetGUIElementChildrenCount(_gui_GetLayer(cTooltipLayer)))+']',$1000000 or _log_trace);
   struct.end
section.end

