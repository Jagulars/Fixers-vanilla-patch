section.begin
   Name = DoResizeGUI
   Code : struct.begin
      [*] = ;Log('DoResizeGUI');
      [*] = ;
      [*] = ;ExecuteState('ResizeCamera');
      [*] = ;ExecuteState('GUICreateMouseControls');
      [*] = ;//ExecuteState('CreateHUD');
      [*] = ;
      [*] = ;SetCameraInfoSmoothingChange(True);
      [*] = ;IntRegister0 := 0;
      [*] = ;ExecuteState('SetCameraTarget');
      [*] = ;//NeedRestartGUI;
      [*] = ;
      [*] = ;_gui_RootWindowInit();
   struct.end
section.end

