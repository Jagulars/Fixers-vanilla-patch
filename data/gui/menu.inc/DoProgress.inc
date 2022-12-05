section.begin
   Name = DoProgress
   Code : struct.begin
      [*] = ;GUIExecuteState('VVK.DoProgressGUI');
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
      [*] = ;
      [*] = ;   if (gFloatRegister_gDbgFloat0PrevValue <> gIntRegister_dbgX) or (gFloatRegister_gDbgFloat1PrevValue <> gIntRegister_dbgY) or (gFloatRegister_gDbgFloat2PrevValue <> gIntRegister_dbgZ) then
      [*] = ;   begin
      [*] = ;      //ExecuteState('ShowInternetShell');
      [*] = ;      //SetIntValueByName('ElementHandle', GetGUIElementUnderMouse);
      [*] = ;      //ExecuteState('OnMouseEnter');
      [*] = ;   end;
      [*] = ;
      [*] = ;   gFloatRegister_gDbgFloat0PrevValue := gIntRegister_dbgX;
      [*] = ;   gFloatRegister_gDbgFloat1PrevValue := gIntRegister_dbgY;
      [*] = ;   gFloatRegister_gDbgFloat2PrevValue := gIntRegister_dbgZ;
      [*] = ;end;
      [*] = ;
      [*] = ;GUIExecuteState('DoProgressMusic');
      [*] = ;
      [*] = ;if (not IsCameraMoveToPosition()) then
      [*] = ;begin
      [*] = ;   var cameraIndex : Integer = GetIntValueByName('CameraIndex') + 1;
      [*] = ;   var cameraName : String = 'cinema'+IntToStr(cameraIndex);
      [*] = ;   if (not GetCameraExist(cameraName)) then
      [*] = ;   begin
      [*] = ;      cameraIndex := 0;
      [*] = ;      cameraName := 'cinema'+IntToStr(cameraIndex);
      [*] = ;   end;
      [*] = ;   if (GetCameraExist(cameraName)) then
      [*] = ;      CameraInfoLoadToCurrentView(cameraName);
      [*] = ;   SetIntValueByName('cameraIndex', cameraIndex);
      [*] = ;end;
      [*] = ;
      [*] = ;GUIExecuteState('FadeControl');
      [*] = ;
      [*] = ;if (gc_demoVersion=1) and (gIntRegister_DemoQueryIntro=0) then
      [*] = ;begin
      [*] = ;   var queryWindow : Integer = _gui_GetWindow('queryWindow');
      [*] = ;   if (not GetGUIElementVisible(queryWindow)) then
      [*] = ;   begin
      [*] = ;      StringRegister0 := '12001';
      [*] = ;      GUIExecuteState('RequestQueryWindow');
      [*] = ;   end;
      [*] = ;end;
      [*] = ;
      [*] = ;_lan_stimer_Idle(gc_lt_ALL);
      [*] = ;GUIExecuteState('DoLanProgress');
      [*] = ;
      [*] = ;if (gBoolRegister_GUIProgressOnceOnGUIDoCreate) then
      [*] = ;begin
      [*] = ;   if gProfile.simplegraphics then
      [*] = ;      _actor_CheckSimplifiedGraphics();
      [*] = ;   gBoolRegister_GUIProgressOnceOnGUIDoCreate := False;
      [*] = ;end;
      [*] = ;
      [*] = ;_gui_ClampingMouseToScreen();
   struct.end
section.end

