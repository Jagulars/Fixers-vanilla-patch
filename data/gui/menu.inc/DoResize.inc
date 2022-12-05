section.begin
   Name = DoResize
   UsedFileName =
   Code : struct.begin
      [*] = ;Log('DoResizeGUI');
      [*] = ;ExecuteState('DoUpdateCamera');
      [*] = ;
      [*] = ;_gui_RootWindowInit();
      [*] = ;
      [*] = ;//NeedRestartGUI(); // should be disabled or the main menu is not created if resizing happens
   struct.end
section.end

